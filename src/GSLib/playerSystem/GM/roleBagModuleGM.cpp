 //////////////////////////////////////////////////////////////////////
//	created:	2014/08/29
//	filename: 	src\GSLib\playerSystem\GM\roleBagModule.cpp
//	author:	    zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <stdarg.h>
#include <GSLib/playerSystem/GM/playerSystemGM.h>
#include <GSLib/playerSystem/GM/roleBagModuleGM.h>
#include <GSLib/playerSystem/msgPlayerSystem.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/itemSystem/GM/itemGMMgr.h>
#include <GSLib/equipSystem/GM/roleEquipModule.h>
#include "roleConfigGMMgr.h"

namespace GSLib
{

namespace PlayerSystem
{	

namespace GM
{
using namespace GSLib::ItemSystem::GM;

CRoleBagModuleGM::CRoleBagModuleGM(CRoleGM* a_roleGM, EModuleType a_moduleType)
: CRoleModuleGM(a_roleGM, a_moduleType)
{
   m_bagMgr = new CRoleBagGMMgr();
}

CRoleBagModuleGM::~CRoleBagModuleGM()
{
    BSLIB_SAFE_DELETE(m_bagMgr);
}

BSLib::uint32 CRoleBagModuleGM::getBagSize()const
{
    CRoleGM *role = getRoleGM();
    if(role == NULL){
        return EBAGPOSITION_MAX_COUNT;
    }
    //return role->getBagSize();
	return EBAGPOSITION_MAX_COUNT;
}

bool CRoleBagModuleGM::removeItemCount(ItemTPID a_itemTPID,GSLib::ItemSystem::GM::EItemType a_type,BSLib::uint32 a_rmCount,const std::string& a_reason,bool a_notify)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[删除物品][a_itemTPID=%d][a_reason=%s][a_notify=%d]",a_itemTPID,a_reason.c_str(),a_notify);
    std::vector<BSLib::uint32> indexArray;
    std::vector<BSLib::uint32> countArray;
    indexArray.clear();
    countArray.clear();
    SItemInstanceID rmItemEntityID(a_itemTPID,0);
    if(!m_bagMgr->removeItemCount(rmItemEntityID,a_rmCount,indexArray,countArray)){
        return false;
    }
   
    for (BSLib::uint32 j= 0; j<indexArray.size(); ++j){
        notifyBagItemCount(indexArray[j],a_notify,true);
    }

	_outputGameLog("t_resource","[f_type=%d][f_resource_id=%u][f_count=%u][][f_source=%s][AddEquip]", -1, a_itemTPID, a_rmCount, a_reason.c_str());

    return false;
}

bool CRoleBagModuleGM::removeItemByIndex(BagIndex a_index,const std::string& a_reason,bool a_notify)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[删除背包中物品][a_index=%d][a_reason=%s][a_notify=%d]",a_index,a_reason.c_str(),a_notify);
    BSLib::uint32 count = m_bagMgr->getItemCountByIndex(a_index);
    if(!m_bagMgr->removeItem(a_index,count)){
         BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[删除背包中物品,失败][a_index=%d][a_reason=%s][count=%d]",a_index,a_reason.c_str(),count);
        return false;
    }
    notifyBagItemCount(a_index,a_notify,true);
    return true;
}

bool CRoleBagModuleGM::forceRemoveItemCount(ItemTPID a_itemTPID,BSLib::uint32 a_rmCount,const std::string& a_reason,bool a_notify)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[强制删除背包中物品][a_itemTPID=%d][a_rmCount=%d][a_reason=%s][a_notify=%d]",a_itemTPID,a_rmCount,a_reason.c_str(),a_notify);
    SItemInstanceID itemEntityID(a_itemTPID,0);
    CItemTPIDList* itemList = m_bagMgr->getItemTPIDList(itemEntityID);
    if(itemList == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[BAGDATA][itemList == NULL][a_itemTPID=%d][a_rmCount=%d]",a_itemTPID,a_rmCount);
        return false;
    }
    BSLib::uint32 rmCount = a_rmCount;
    const BSLib::uint32 curTotalCount = itemList->getTotalCount();
    if(curTotalCount < rmCount){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[BAGDATA][DELETE_ERROR][a_itemTPID=%d][curTotalCount=%d][a_rmCount=%d]",a_itemTPID,curTotalCount,a_rmCount);
        rmCount = curTotalCount;
    }

    return removeItemCount(a_itemTPID,GSLib::ItemSystem::GM::EITEM_TP_IVALID,rmCount,a_reason,a_notify);
}

bool CRoleBagModuleGM::_useItemByIndex(BagIndex a_index,bool a_notify)
{
	if((a_index < 0) || (a_index>(m_bagMgr->getPosCount()-1))){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[背包中索引越界][a_index = %d]",a_index);
		return false;
	}

    SItemInstanceID itemInstanceID = m_bagMgr->getItemInstanceID(a_index);
    BSLib::uint32 tpid = itemInstanceID.getItemTPID();
	if(tpid == 0){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[item == NULL]背包中无此物品[tpid = %d]",tpid);
		return false;
	}

	if(!CItemGMMgr::singleton().isUse(tpid)){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[不可使用物品][tpid = %d]",tpid);
       return false;
	}
    const BSLib::uint32 rmCount = 1;
    const BSLib::uint32 curCount = m_bagMgr->getItemCountByIndex(a_index);
    if(curCount < rmCount){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[数量不足][a_index=%d][curCount=%d]", a_index,curCount);
        return false;
    }
     
    EItemType type = CItemGMMgr::singleton().getType(tpid);
    switch (type)
    {
    case EITEM_TP_PROP_VITALITY:
        {
            if(!m_bagMgr->removeItem(a_index,rmCount)){
                BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[删除背包中物品,失败][a_index=%d][rmCount=%d]",a_index,rmCount);
                return false;
            }
             notifyBagItemCount(a_index,a_notify,true);
            BSLib::uint32 addVitality = CItemGMMgr::singleton().getAddVitality(tpid);
            PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
            if (roleGM == NULL) {
                BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[roleGM == NULL]");
                return false;
            }
            roleGM->modifyRoleResource(ATTR_VITALITY,addVitality,"USE_PROP",true);

        }
        break;
    case EITEM_TP_PROP_MEDICINE:
        {
            ;
        }
        break;
    default: 
        {
            ;
        }
        break;
    }

	return true;
}


bool CRoleBagModuleGM::sellItemNotInBag(ItemTPID a_tpid,BSLib::uint32 a_count,bool a_notify)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "soldItem[a_tpid=%d][count=%d]", a_tpid,a_count);
    BSLib::uint32 price= CItemGMMgr::singleton().getPrice(a_tpid);
    GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
    if (roleGM == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[roleGM == NULL]");
        return false;
    }
    if(price > 0){
        BSLib::int64 gold = price * a_count;
        if(!roleGM->modifyGold(gold,"SOLD_ITEM",a_notify)){
            BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "modifyGold[price=%d][gold=%lld]",price,gold);
            return false;
        }
    }
    return true;
}

bool CRoleBagModuleGM::notifyBagItemCount(BagIndex a_index,bool a_notify,bool a_save)
{
    if(a_notify){
        _nofityBagItemToClient(a_index);
    }
    if(a_save){
        updateDataToDB(a_index);
    }

    return true;
}

bool CRoleBagModuleGM::_sellItemByIndex(BagIndex a_index,BSLib::uint32 a_count,bool a_notify)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "sellItemByIndex[a_index=%d][count=%d][notify=%d]", a_index,a_count,a_notify);
	if((a_index < 0) || (a_index>(m_bagMgr->getPosCount()-1))){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "sellItemByIndex背包中索引越界[a_index = %d]",a_index);
		return false;
	}

    SItemInstanceID itemInstanceID = m_bagMgr->getItemInstanceID(a_index);
    const ItemTPID tpid = itemInstanceID.getItemTPID();
    if(tpid == 0){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[item == NULL]背包中无此物品[tpid = %d][a_count = %d]",tpid,a_count);
        return false;
    }

    if(!CItemGMMgr::singleton().isSell(tpid)){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[不可使用物品][tpid = %d]",tpid);
        return false;
    }

    if(m_bagMgr->getItemCountByIndex(a_index) < a_count){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[数量不足][a_count=%d]", a_count);
        return false;
    }

    GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
    if (roleGM == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[roleGM == NULL]");
        return false;
    }

    const EMainType mainType = CItemGMMgr::singleton().getMainType(tpid);
    if(mainType == EMAIN_TP_EQUIP){
        using namespace EquipSystem::GM;
        CRoleEquipModule* equipModule = (CRoleEquipModule*)roleGM->getPlayerModuleGM(EMODULECTYPE_EQUIP);
        if(equipModule == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[获取装备模块失败][tpid=%d]", tpid);
            return false;
        }
        const EquipID equipID = itemInstanceID.getInstanceID();
        const EItemType type = CItemGMMgr::singleton().getType(tpid);
        if(!equipModule->removeEquip(equipID)){
            BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[出售装备失败][equipID=%d]", equipID);
            return false;
        }
       // _outputGameLog("RemoveEquip","[Type=SOLD_EQUIP][EquipID=%d][EquipTPID=%d][EquipType=%d]",equipID,tpid, type);
    }

    if(!m_bagMgr->removeItem(a_index,a_count)){
        return false;
    }
    notifyBagItemCount(a_index,a_notify,true);

    BSLib::uint32 price= CItemGMMgr::singleton().getPrice(tpid);
	if(price > 0){
		BSLib::int64 gold = price * a_count;
		if(!roleGM->modifyGold(gold,"SOLD_ITEM",a_notify)){
			BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "modifyGold[price=%d][gold=%lld]",price,gold);
			return false;
		}
	}
	
	_outputGameLog("t_resource","[f_type=%d][f_resource_id=%u][f_count=%u][][f_source=%s][RemoveEquip]", -1, tpid, a_count, "SOLD_EQUIP");
	return true;
}

BSLib::uint32 CRoleBagModuleGM::getItemCount(ItemTPID a_itemTPID) const
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getItemCount[a_itemTPID=%d]", a_itemTPID);
    return m_bagMgr->getItemCount(SItemInstanceID(a_itemTPID,0));
}

BSLib::uint32 CRoleBagModuleGM::getInstanceIDByIndex(BagIndex a_index)
{
    SItemInstanceID itemInstanceID = m_bagMgr->getItemInstanceID(a_index);
    return itemInstanceID.getInstanceID();
}

bool CRoleBagModuleGM::getIndexByItemInstanceID(const SItemInstanceID& a_itemInstanceID,BagIndex& bagIndex)
{
    return m_bagMgr->getIndexByItemInstanceID(a_itemInstanceID,bagIndex);
}

void CRoleBagModuleGM::preInit(bool isFirst)
{
	if(isFirst) {
        BSLib::Utility::CHashMap<BSLib::uint32, SBagInitConfig*> bagInitData = CRoleConfigGMMgr::singleton().getBagInitConfig();
        BSLib::Utility::CHashMap<BSLib::uint32, SBagInitConfig*>::iterator it = bagInitData.begin();
        for (; it != bagInitData.end(); ++it) {
            SBagInitConfig* item = it->second;
            if (item == NULL) {
                continue;
            }
            CPrizeItem prizeItem;
            prizeItem.m_itemTPID = item->m_tpid;
            prizeItem.m_itemType = CItemGMMgr::singleton().getType(item->m_tpid);
            prizeItem.m_itemCount = item->m_count;
            addItem(prizeItem,false,false,"INIT_ITEM");
        }
	}
}

void CRoleBagModuleGM::postInit(bool isFirst)
{
}

void CRoleBagModuleGM::initToClient()
{
    _notifyBagDataToClient();
}

void CRoleBagModuleGM::final()
{
    if(m_bagMgr != NULL){
        m_bagMgr->final();
    }
}

void CRoleBagModuleGM::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqGetBagData, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqGetBagData>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqGetBagData, &CRoleBagModuleGM::_onMsgPlayerSystemGC2GMReqGetBagData, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqUseBagItemData, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqUseBagItemData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqUseBagItemData, &CRoleBagModuleGM::_onMsgPlayerSystemGC2GMReqUseBagItemData, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqSoldBagItemData, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqSoldBagItemData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqSoldBagItemData, &CRoleBagModuleGM::_onMsgPlayerSystemGC2GMReqSoldBagItemData, this);
}

void CRoleBagModuleGM::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(MsgIDPlayerSystemGC2GMReqGetBagData);
	a_msgExecMgr->delMsgExecPtr(MsgIDPlayerSystemGC2GMReqUseBagItemData);
	a_msgExecMgr->delMsgExecPtr(MsgIDPlayerSystemGC2GMReqSoldBagItemData);
}

void CRoleBagModuleGM::_onMsgPlayerSystemGC2GMReqGetBagData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	
	CMsgPlayerSystemGC2GMReqGetBagData *req = (CMsgPlayerSystemGC2GMReqGetBagData *)a_msg;

    CMsgPlayerSystemGM2GCAckGetBagData ack;
    ack.m_retCode = EINITPLAYERDATA_RESULT_SUCCESS;
    GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
    if (roleGM == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[roleGM == NULL]");
        ack.m_retCode = EINITPLAYERDATA_RESULT_FAIL;
        sendMsgToClient(ack);
        return ;
    }

	if( 0 == req->m_type)
	{
		ack.m_bagSize = getBagSize();
		ack.m_usedBagPosCount = m_bagMgr->getUsedPosCount();
		m_bagMgr->serializeToClient(roleGM,ack.m_usedBagPosCount,ack.m_stream);
	}
	else
	{
		m_bagMgr->serializeNengLiangQiuToClient(roleGM,ack.m_usedBagPosCount,ack.m_stream);
	}

    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "AckGetBagData[m_bagPosCount=%d][m_usedBagPositionCount=%d]", m_bagMgr->getPosCount(),m_bagMgr->getUsedPosCount());
    sendMsgToClient(ack);
}

void CRoleBagModuleGM::_onMsgPlayerSystemGC2GMReqUseBagItemData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgPlayerSystemGC2GMReqUseBagItemData* req = (CMsgPlayerSystemGC2GMReqUseBagItemData*)a_msg;
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[收到使用物品请求][m_itemType=%d][m_index=%d]",req->m_itemType,req->m_index);
	CMsgPlayerSystemGM2GCAckUseBagItemData ack;
	
	bool bSuccess = _useItemByIndex(req->m_index,true);
	ack.m_retCode = bSuccess ? EUSEBAGITEMDATA_RESULT_SUCCESS : EUSEBAGITEMDATA_RESULT_FAIL;
	sendMsgToClient(ack);
}

void CRoleBagModuleGM::_onMsgPlayerSystemGC2GMReqSoldBagItemData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgPlayerSystemGC2GMReqSoldBagItemData* req = (CMsgPlayerSystemGC2GMReqSoldBagItemData*)a_msg;
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[收到销售物品请求][m_itemIndex=%d][m_itemCount=%d]",req->m_index,req->m_itemCount);
	CMsgPlayerSystemGM2GCAckSoldBagItemData ack;
	bool bSuccess = _sellItemByIndex(req->m_index,req->m_itemCount,true);
	ack.m_retCode = bSuccess?ESOLDBAGITEMDATA_RESULT_SUCCESS:ESOLDBAGITEMDATA_RESULT_FAIL;
	sendMsgToClient(ack);
}

void CRoleBagModuleGM::onRoleDelete(){

}

void CRoleBagModuleGM::updateDataToDB()
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[CRoleBagModuleGM::updateDataToDB()][背包数据更新]");
    GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
    if (roleGM == NULL) {
        return ;
    }

    GSLib::PlayerSystem::DB::CRoleBagData bagData;
    DB::SRoleBagItemData bagItemData;
    for (BSLib::uint32 index = 0; index<m_bagMgr->getPosCount();++index){
        bagItemData.m_accountID = roleGM->getAccountID();
        bagItemData.m_zoneID = roleGM->getZoneID();
        bagItemData.m_roleIndex = roleGM->getRoleIndex();
        m_bagMgr->serializeToDB(index,bagItemData);
        bagData.m_bagItemArray.push_back(bagItemData);
    }

    BSLib::Utility::CStream stream;
    stream.reset();
    bagData.serializeTo(stream);
    if (!updateTableData("","",EDBTABLEID_ROLE_BAG_DATA,stream,true)){
        BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "更新背包信息失败");
    }
}

void CRoleBagModuleGM::updateDataToDB(BagIndex a_index)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[CRoleBagModuleGM::updateDataToDB()][a_index =%d]",a_index);
    GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
    if (roleGM == NULL) {
        return ;
    }

    SItemInstanceID itemInstanceID = m_bagMgr->getItemInstanceID(a_index);
    BSLib::uint32 tpid = itemInstanceID.getItemTPID();

    if(0 == tpid){
        _dbRemoveItem(a_index);
        return;
    }

    GSLib::PlayerSystem::DB::CRoleBagData bagData;
    DB::SRoleBagItemData bagItemData;
    bagItemData.m_accountID = roleGM->getAccountID();
    bagItemData.m_zoneID = roleGM->getZoneID();
    bagItemData.m_roleIndex = roleGM->getRoleIndex();
    m_bagMgr->serializeToDB(a_index,bagItemData);
    bagData.m_bagItemArray.push_back(bagItemData);

    BSLib::Utility::CStream stream;
    stream.reset();
    bagData.serializeTo(stream);
    if (!updateTableData("","",EDBTABLEID_ROLE_BAG_DATA,stream,true)){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新背包信息失败");
    }
}

bool CRoleBagModuleGM::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[cbSelectKeyTableData][a_sessionID=%d][a_tableID=%d]",a_sessionID,a_tableID);
	return true;
}

bool CRoleBagModuleGM::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
    // 防止数据重复添加
    if(a_sessionID == GSLIB_SESSIONID_CREATE_ROLE_FINISH){
        return true;
    }

	GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
	if (roleGM == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[cbSelectKeyIndexTableData][roleGM == NULL]");
		return true;
	}
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[cbSelectKeyIndexTableData][a_sessionID=%d][a_tableID=%d][AccountID=%lld][index=%d]",a_sessionID,a_tableID,roleGM->getAccountID(),roleGM->getRoleIndex());
	const BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>* tables = a_keyTable->getRows(roleGM->getRoleDBKey());
    if(tables == NULL){
        return true;
    }

	m_bagMgr->initBagFromDB(tables,roleGM);
	
	return true;
}

bool CRoleBagModuleGM::updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave)
{
    CRoleGM* role = getRoleGM();
    if(role == NULL){
        return false;
    }
	const SRoleKey& roleKey = role->getRoleKey();
	std::string tableKey = roleKey.getDBKey();
	if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().updateTableData(tableKey, a_tableIndex, a_name, a_tableID, a_stream, a_needSave)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新表[TableID=%d]失败%s", a_tableID, roleKey.toLogString().c_str());
		return false;
	}
	return true;
}

bool CRoleBagModuleGM::updateTableData(EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize, bool a_needSave)
{
	if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().updateTableData("", "", "", a_tableID, a_data, a_dataSize, a_needSave)) {
        CRoleGM* role = getRoleGM();
        if(role == NULL){
            return false;
        }
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新表[TableID=%d]失败%s", a_tableID, role->getRoleKey().toLogString().c_str());
		return false;
	}
	return true;
}

bool CRoleBagModuleGM::removeTableData(BSLib::Utility::CStream& a_steam, EDBTableID a_tableID, bool a_needSave)
{
	if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().removeTableData(a_steam, a_tableID, a_needSave)) {
        CRoleGM* role = getRoleGM();
        if(role == NULL){
            return false;
        }
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "删除表[TableID=%d]失败%s", a_tableID, role->getRoleKey().toLogString().c_str());
		return false;
	}
	return true;
}

bool CRoleBagModuleGM::removeTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, EDBTableID a_tableID, bool a_needSave)
{
	if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().removeTableData(a_tabkeKey, a_tableIndex, a_tableID, a_needSave)) {
        CRoleGM* role = getRoleGM();
        if(role == NULL){
            return false;
        }
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "删除表[TableID=%d]失败%s", a_tableID, role->getRoleKey().toLogString().c_str());
		return false;
	}
	return true;
}

bool CRoleBagModuleGM::_nofityBagItemToClient(BagIndex a_index)
{   
    SBagItem item;
    item.m_count= 0;
    item.m_tpid = 0;
    item.m_index =a_index;
    item.m_type = GSLib::ItemSystem::GM::EITEM_TP_IVALID;
    m_bagMgr->getItemByIndex(a_index,item); 
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[背包通知修改][m_index=%d][m_count=%d][m_type=%d]", item.m_index, item.m_count,item.m_type);
    return _nodifyBagDataToClient(item);
}

bool CRoleBagModuleGM::_nodifyBagDataToClient(const SBagItem& a_bagItem)
{
    GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
    if (roleGM == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[roleGM == NULL]");
        return false;
    }

	// 过滤 能量球
	if(EITEM_TP_EQUIP_NENGLIANGQIU == a_bagItem.m_type)
	{
		return false;
	}

	CMsgPlayerSystemGM2GCNtfUpdateBagItemData ntf;
	ntf.m_retCode = EUPDATEBAGITEMDATA_RESULT_SUCCESS;
	ntf.m_itemType = a_bagItem.m_type;
	ntf.m_bagItemTPID = a_bagItem.m_tpid;
	ntf.m_bagItemPositin = a_bagItem.m_index;
	ntf.m_usedBagPositionCount = a_bagItem.m_count;

    EquipSystem::GM::CRoleEquipModule* equipModule = (EquipSystem::GM::CRoleEquipModule*)roleGM->getPlayerModuleGM(EMODULECTYPE_EQUIP);
    if(equipModule == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[获取装备模块失败]");
        return false;
    }

    if(CItemGMMgr::singleton().getMainType(a_bagItem.m_tpid) == EMAIN_TP_EQUIP){
        SItemInstanceID itemInstanceID = m_bagMgr->getItemInstanceID(a_bagItem.m_index);
        EquipID equipID = itemInstanceID.getInstanceID();
        if (equipModule->isEquipStatusOn(equipID)){
            removeItemByIndex(a_bagItem.m_index,"DATA_RECOVERY",true);
            return false;
        }
        BSLib::Utility::CStream itemStream;
        itemStream.reset();
        if(!equipModule->getEquipDataForBag(equipID,a_bagItem.m_tpid,itemStream)){
            BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[_nodifyBagDataToClient][获取装备详细信息失败][equipID=%d]", equipID);
            return false;
        }
        ntf.m_stream << equipID;
        ntf.m_stream << itemStream;
    }
    else{
        BSLib::uint32 itemInstanceID = 0;
        BSLib::uint32 addLevel = 0;
        BSLib::uint32 gemsCount = 0;
        ntf.m_stream << itemInstanceID;
        ntf.m_stream << addLevel;
        ntf.m_stream << gemsCount;
    }

	return sendMsgToClient(ntf);
}

bool CRoleBagModuleGM::_useItem(ItemTPID a_itemTPID,BSLib::uint32 a_count,bool a_notify)
{
    BSLib::int32 newItemCount = getItemCount(a_itemTPID) - a_count;
    if(newItemCount < 0){
        return false;
    }
    // TODO: 1 添加物品的使用效果
    //       2 消耗掉物品
    return true;
}

bool CRoleBagModuleGM::_dbRemoveItem(BSLib::uint32 a_itemIndex)
{
	BSLib::Utility::CStream stream;
	stream.reset();
	CRoleGM* role = getRoleGM();
	if(role == NULL){
		return false;
	}

	std::string dbKey = role->getRoleDBKey();
	std::string dbIndex;
	dbIndex.append((char*)&a_itemIndex, sizeof(a_itemIndex));
	return removeTableData(dbKey,dbIndex,EDBTABLEID_ROLE_BAG_DATA,true);
}

EAddResult CRoleBagModuleGM::addItem(const std::vector<CPrizeItem>& a_itemArray,bool a_force,bool a_notify,const std::string& a_reason)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[背包多物品添加addItem:a_itemArray.size=%d][a_force=%d][a_notify=%d][a_reason=%s]", a_itemArray.size(),a_force,a_notify,a_reason.c_str());
    std::vector<SItemInstanceID> itemTPIDArray;
    std::vector<BSLib::uint32> itemCountArray;
    m_bagMgr->combineItems(a_itemArray,itemTPIDArray,itemCountArray);
    if(!a_force){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[背包addItem:a_itemArray.size=%d]", a_itemArray.size());
        EAddResult isAddBagResult = m_bagMgr->isableAddItem(itemTPIDArray,itemCountArray,a_force);
        if( EADDITEM_SUCCESS != isAddBagResult){
            BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[背包addItem:a_itemArray.size=%d,添加物品失败,Result=%d]", a_itemArray.size(),isAddBagResult);
            return isAddBagResult;
        }
    }

    EAddResult isAddBagResult = m_bagMgr->isableAddItem(itemTPIDArray,itemCountArray,a_force);
    if( EADDITEM_SUCCESS == isAddBagResult){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[背包开始添加物品addItem:itemTPIDArray.size=%d]", itemTPIDArray.size());
        _addBagItems(itemTPIDArray,itemCountArray,a_force,a_notify);
        return EADDITEM_SUCCESS;
    }

    BSLib::uint32 needPositionCount = m_bagMgr->getNeedEmptyPosCount(itemTPIDArray,itemCountArray);
    BSLib::uint32 emptyPositionCount = m_bagMgr->getEmptyPosCount();
    if(needPositionCount > emptyPositionCount){
        BSLib::uint32 addSize = needPositionCount - emptyPositionCount;
        m_bagMgr->addPosCount(addSize);
    }

    EAddResult isAddBagResult2 = m_bagMgr->isableAddItem(itemTPIDArray,itemCountArray,a_force);
    if( EADDITEM_SUCCESS == isAddBagResult2){
        _addBagItems(itemTPIDArray,itemCountArray,a_force,a_notify);
        return EADDITEM_SUCCESS;
    }

    return EADDITEM_INVALID_ITEM;
}

EUseResult CRoleBagModuleGM::useItem(const std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray,bool a_notify,const std::string& a_reason)
{
    EUseResult result = isableUseItem(a_itemArray);
    if( EUSEITEM_SUCCESS != result){
        return result;
    }

    for(BSLib::uint32 i=0;i<a_itemArray.size();++i){
        const ItemSystem::GM::CPrizeItem *item = &a_itemArray[i];
        if(NULL == item){
            return EUSEITEM_INVALID_ITEM;
        }
        useItem(*item,a_notify);
    }
    return EUSEITEM_SUCCESS;
}

bool CRoleBagModuleGM::getItemByIndex(BSLib::uint32 a_index, SBagItem & a_BagItem) const
{
	return m_bagMgr->getItemByIndex(a_index, a_BagItem);
}

EAddResult CRoleBagModuleGM::addItem(const ItemSystem::GM::CPrizeItem& a_item,bool a_forceAdd,bool a_notify,const std::string& a_reason)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM,"%sAddItem[m_itemTPID=%d][m_itemCount=%d][a_force=%d][a_notify=%d][a_reason=%s]",getRoleInfor().c_str(), a_item.m_itemTPID, a_item.m_itemCount,a_forceAdd,a_notify,a_reason.c_str());
    ItemSystem::GM::EMainType type = ItemSystem::GM::CItemGMMgr::singleton().getMainType(a_item.m_itemTPID);
    switch(type)
    {
    case EMAIN_TP_ITEM:
        {
            return _addBagItem(a_item,a_forceAdd,a_notify,0,a_reason);
        }
    case EMAIN_TP_EQUIP:
        {
            return _addEquipItem(a_item,a_forceAdd,a_notify,a_reason);
        }
    case EMAIN_TP_RESOURCE:
        {
            return _addRes(a_item,a_notify,a_reason);
        }
    case EMAIN_TP_IVALID:
        {
            return EADDITEM_INVALID_ITEM;
        }
    default:
        {
            return EADDITEM_INVALID_ITEM;
        }
    }
}

bool CRoleBagModuleGM::isBagFull() const
{
    return m_bagMgr->isBagFull();
}

bool CRoleBagModuleGM::addEquip(const SItemInstanceID& a_itemInstanceID,bool a_force,bool a_notify,BSLib::uint32& a_index)
{
    return _addEquip(a_itemInstanceID,a_force,a_notify,a_index);
}

EUseResult CRoleBagModuleGM::useItem(const ItemSystem::GM::CPrizeItem& a_item,bool a_notify,const std::string& a_reason)
{
    ItemSystem::GM::EMainType type = ItemSystem::GM::CItemGMMgr::singleton().getMainType(a_item.m_itemTPID);
    switch(type)
    {
    case EMAIN_TP_ITEM:
        {
            return _useBagItem(a_item);
        }
    case EMAIN_TP_RESOURCE:
        {
            return _useRes(a_item);
        }
    case EMAIN_TP_IVALID:
        {
            return EUSEITEM_INVALID_ITEM;
        }
    default:
        {
            return EUSEITEM_INVALID_ITEM;
        }
    }
}

EUseResult CRoleBagModuleGM::isableUseItem(const ItemSystem::GM::CPrizeItem& a_item)
{
    if(!m_bagMgr->isValidItem(a_item.m_itemTPID)){
        return EUSEITEM_INVALID_ITEM;
    }

    ItemSystem::GM::EMainType mainType = ItemSystem::GM::CItemGMMgr::singleton().getMainType(a_item.m_itemTPID);
    if(mainType == ItemSystem::GM::EMAIN_TP_RESOURCE){
        return EUSEITEM_SUCCESS;
    }

    bool isUse = ItemSystem::GM::CItemGMMgr::singleton().isUse(a_item.m_itemTPID);
    if (!isUse){
        return EUSEITEM_USELIMIT_ITEM;
    }

    if(!(getItemCount(a_item.m_itemTPID) < a_item.m_itemCount)){
        return EUSEITEM_NOTENOUGH_ITEM;
    }

    return EUSEITEM_SUCCESS;
}

EUseResult CRoleBagModuleGM::isableUseItem(const std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray)
{
    for(BSLib::uint32 i=0;i< a_itemArray.size(); ++i){
       ItemSystem::GM::CPrizeItem item = a_itemArray[i];
       EUseResult result = isableUseItem(item);
       if(result != EUSEITEM_SUCCESS){
           return result;
       }
    }
    return EUSEITEM_SUCCESS;
}

bool CRoleBagModuleGM::isableAddItem(const ItemSystem::GM::CPrizeItem& a_item,bool a_force,EAddResult& a_reason)
{
     return m_bagMgr->isableAddItem(a_item,a_force,a_reason);
}

EAddResult CRoleBagModuleGM::isableAddItems(const std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray,bool a_force)
{
    std::vector<SItemInstanceID> itemTPIDArray;
    std::vector<BSLib::uint32> itemCountArray;
    m_bagMgr->combineItems(a_itemArray,itemTPIDArray,itemCountArray);
    if(!a_force){
        return m_bagMgr->isableAddItem(itemTPIDArray,itemCountArray,a_force);
    }
    return EADDITEM_SUCCESS;
}

EUseResult CRoleBagModuleGM::_isableUseRes(const ItemSystem::GM::CPrizeItem& a_item)
{
    return _isableUseRes(a_item.m_itemTPID,a_item.m_itemCount);
}

EUseResult CRoleBagModuleGM::_isableUseRes(const ItemTPID& a_itemTPID, const BSLib::uint32& a_count)
{
    if(!m_bagMgr->isValidItem(a_itemTPID)){
        return EUSEITEM_INVALID_ITEM;
    }

    CRoleGM * role = getRoleGM();
    if( NULL == role){
        return EUSEITEM_FAIL;
    }

    bool bSuccess = false;
    ItemSystem::GM::EItemType type = ItemSystem::GM::CItemGMMgr::singleton().getType(a_itemTPID);
    switch (type)
    {
    case ItemSystem::GM::EITEM_TP_VIR_GOLD:
        {
            BSLib::int64 addValue = 0 - a_count;
            bSuccess = role->isableModifyGold(addValue);
        }
        break;
	case EITEM_TP_VIR_LIGHT_POWER:
		{
			BSLib::int32 addValue =  0 - a_count;
			bSuccess = role->isableModifyResource(ATTR_LIGHT_POWER, addValue);
		}
		break;
    case ItemSystem::GM::EITEM_TP_VIR_PVPCOIN:
        {
            BSLib::int32 addValue = 0 - a_count;
            bSuccess = role->isableModifyResource(ATTR_PVPCOIN, addValue);
        }
        break;
    case ItemSystem::GM::EITEM_TP_VIR_EXP:
        {
            BSLib::int64 addValue = 0 - a_count;
            bSuccess = role->isableModifyExp(addValue);
        }
        break;
    case ItemSystem::GM::EITEM_TP_VIR_VITALITY:
        {
            BSLib::int32 addValue = 0 - a_count;
            bSuccess = role->isableModifyResource(ATTR_VITALITY,addValue);
        }
        break;
    default:
        {
           
            
        }
        break;
    }

    if(bSuccess){
        return EUSEITEM_SUCCESS;
    }

    return EUSEITEM_FAIL;
}

EUseResult CRoleBagModuleGM::_isableUseRes(const std::vector<CPrizeItem>& a_itemArray)
{
    for(BSLib::uint32 i=0;i<a_itemArray.size();++i){
        EUseResult result = _isableUseRes(a_itemArray[i]);
        if(result != EUSEITEM_SUCCESS){
            return result;
        }
    }
    return EUSEITEM_SUCCESS;
}

EAddResult CRoleBagModuleGM::_addRes(const CPrizeItem& a_item,bool a_notify,const std::string& a_reason)
{
    if(!m_bagMgr->isValidItem(a_item.m_itemTPID)){
        return EADDITEM_INVALID_ITEM;
    }

    if(CItemGMMgr::singleton().getMainType(a_item.m_itemTPID) != EMAIN_TP_RESOURCE){
        return EADDITEM_INVALID_ITEM;
    }
    CRoleGM * role = getRoleGM();
    if( NULL == role){
        return EADDITEM_FAIL;
    }

    bool bSuccess = false;
    EItemType type = CItemGMMgr::singleton().getType(a_item.m_itemTPID);
    switch (type)
    {
    case EITEM_TP_VIR_GOLD:
        {
            BSLib::int64 addValue = a_item.m_itemCount;
            bSuccess = role->modifyGold(addValue,a_reason,a_notify);
        }
        break;
	case EITEM_TP_VIR_LIGHT_POWER:
		{
            BSLib::int32 addValue = a_item.m_itemCount;
			bSuccess = role->modifyRoleResource(ATTR_LIGHT_POWER,addValue, a_reason, a_notify);
		}
		break;
    case EITEM_TP_VIR_EXP:
        {
            BSLib::int64 addValue = a_item.m_itemCount;
            bSuccess = role->modifyExp(addValue,a_reason,a_notify);
        }
        break;
    case EITEM_TP_VIR_PVPCOIN:
        {
            BSLib::int32 addValue = a_item.m_itemCount;
            bSuccess = role->modifyRoleResource(ATTR_PVPCOIN,addValue,a_reason,a_notify);
        }
        break;
    case EITEM_TP_VIR_DIAMOND:
        {
            BSLib::int32 addValue = a_item.m_itemCount;
            bSuccess = role->modifyRoleResource(ATTR_BIND_DIAMOND,addValue,a_reason,a_notify);
        }
        break;
    case EITEM_TP_VIR_BAGEXPAND:
        {
            BSLib::int32 addValue = a_item.m_itemCount;
            bSuccess = role->modifyRoleResource(ATTR_BAG_SIZE,addValue,a_reason,a_notify);
        }
        break;
    case EITEM_TP_VIR_VIPSCORE:
        {
            BSLib::int32 addValue = a_item.m_itemCount;
            bSuccess = role->modifyRoleResource(ATTR_VIP_SCORE,addValue,a_reason,a_notify);
        }
        break;
    case EITEM_TP_VIR_VITALITY:
        {
            BSLib::int32 addValue = a_item.m_itemCount;
            bSuccess = role->modifyRoleResource(ATTR_VITALITY,addValue,a_reason,a_notify);
        }
    default:
        {
            ;
        }
        break;
    }

    if(bSuccess){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM,"%sAddRes[Type=%s][ResID=%d][ResType=%d][AddCount=%d]",getRoleInfor().c_str(),a_reason.c_str(),a_item.m_itemTPID, a_item.m_itemType, a_item.m_itemCount);
        return EADDITEM_SUCCESS;
    }

    return EADDITEM_FAIL;
}

EAddResult CRoleBagModuleGM::_addMutiRes(const std::vector<CPrizeItem>& a_itemArray,bool a_notify)
{
    for(BSLib::uint32 i = 0;i<a_itemArray.size();++i){
        _addRes(a_itemArray[i],a_notify);
    }

    return EADDITEM_SUCCESS;
}

EUseResult CRoleBagModuleGM::_useRes(const CPrizeItem& a_item,bool a_notify,const std::string& a_reason)
{
    if(!m_bagMgr->isValidItem(a_item.m_itemTPID)){
        return EUSEITEM_INVALID_ITEM;
    }

    CRoleGM * role = getRoleGM();
    if( NULL == role){
        return EUSEITEM_FAIL;
    }

    bool bSuccess = false;
    EItemType type = CItemGMMgr::singleton().getType(a_item.m_itemTPID);
    switch (type)
    {
    case ItemSystem::GM::EITEM_TP_VIR_GOLD:
        {
            BSLib::int64 addValue = 0 - a_item.m_itemCount;
            bSuccess = role->modifyGold(addValue,a_reason,a_notify);
        }
        break;
	case EITEM_TP_VIR_LIGHT_POWER:
		{
			BSLib::int32 addValue = a_item.m_itemCount;
			bSuccess = role->modifyRoleResource(ATTR_LIGHT_POWER, addValue, a_reason, a_notify);
		}
		break;
    case ItemSystem::GM::EITEM_TP_VIR_EXP:
        {
            BSLib::int64 addValue = 0 - a_item.m_itemCount;
            bSuccess = role->modifyExp(addValue,a_reason,a_notify);
        }
        break;
    case ItemSystem::GM::EITEM_TP_VIR_PVPCOIN:
        {
            BSLib::int32 addValue = 0 - a_item.m_itemCount;
            bSuccess = role->modifyRoleResource(ATTR_PVPCOIN,addValue,a_reason,a_notify);
        }
        break;
    case ItemSystem::GM::EITEM_TP_VIR_DIAMOND:
        {
            BSLib::int32 addValue = 0 - a_item.m_itemCount;
            bSuccess = role->modifyRoleResource(ATTR_BIND_DIAMOND,addValue,a_reason,a_notify);
        }
        break;

    case ItemSystem::GM::EITEM_TP_VIR_VITALITY:
        {
            BSLib::int32 addValue = 0 - a_item.m_itemCount;
            bSuccess = role->modifyRoleResource(ATTR_VITALITY,addValue,a_reason,a_notify);
        }
        break;
    default:
        {
            ;
        }
        break;
    }

    if(bSuccess){
		_outputGameLog("t_resource","[f_type=%d][f_resource_id=%u][f_count=%u][][f_source=%s][RemoveRes]", -1, a_item.m_itemTPID, a_item.m_itemCount, "UseRes");
        return EUSEITEM_SUCCESS;
    }

    return EUSEITEM_FAIL;
}

EUseResult CRoleBagModuleGM::_useBagItem(const CPrizeItem& a_item,bool a_notify)
{
    EUseResult ret = isableUseItem(a_item);
    if(!(ret == EUSEITEM_SUCCESS)){
        return ret;
    }
    if(!_useItem(a_item.m_itemTPID,a_item.m_itemCount,a_notify)){
        return EUSEITEM_FAIL;
    }

    return EUSEITEM_SUCCESS;
}

EAddResult CRoleBagModuleGM::_addBagItem(const CPrizeItem& a_item,bool a_force,bool a_notify,BSLib::uint32 a_instanceID,const std::string& a_reason)
{
    EAddResult reason = EADDITEM_INVALID_ITEM;
    if(!isableAddItem(a_item,a_force,reason)){
        return reason;
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_addItemByTPID[a_itemTPID=%d][a_itemType=%d][count=%d]", a_item.m_itemTPID, a_item.m_itemType, a_item.m_itemCount);
    std::vector<SDesItem> desItems;
    if(!m_bagMgr->getDesIndex(a_item,a_instanceID,desItems,a_force)){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "getDesIndex[a_itemTPID=%d][a_itemType=%d][count=%d]", a_item.m_itemTPID, a_item.m_itemType, a_item.m_itemCount);
        return EADDITEM_FAIL;
    }
    
    
    for(BSLib::uint32 i=0;i<desItems.size();++i){
        SDesItem& desItem = desItems[i];
        SItemInstanceID itemEntityID(desItem.m_tpid,a_instanceID);
        if(!m_bagMgr->addItemByIndex(desItem.m_index,itemEntityID,desItem.m_type,desItem.m_count)){
            BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[addItemByIndex][m_index=%d][TPID=%d][type=%d][count=%d][添加物品失败]", desItem.m_index, desItem.m_tpid, desItem.m_type, desItem.m_count);
            return EADDITEM_FAIL;
        }
        notifyBagItemCount(desItem.m_index,a_notify,true);
    }
    desItems.clear();

	_outputGameLog("t_resource","[f_type=%d][f_resource_id=%u][f_count=%u][][f_source=%s][AddBagItem]", 1, a_item.m_itemTPID, a_item.m_itemCount, a_reason.c_str());
    return EADDITEM_SUCCESS;
}

EAddResult CRoleBagModuleGM::_addEquipItem(const CPrizeItem& a_item,bool a_force,bool a_notify,const std::string& a_reason)
{
    EAddResult reason = EADDITEM_INVALID_ITEM;
    if(!isableAddItem(a_item,a_force,reason)){
        return reason;
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_addEquipItem[a_itemTPID=%d][count=%d]", a_item.m_itemTPID,a_item.m_itemCount);

    for(BSLib::uint32 i=0;i<a_item.m_itemCount;++i){
        BSLib::uint32 index = 0;
        if(!_randEquip(a_item.m_itemTPID,false,a_force,a_notify,index,a_reason)){
            BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "_addEquipItem[a_itemTPID=%d][count=%d][生成装备失败]", a_item.m_itemTPID, a_item.m_itemCount,a_reason);
        }
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_addEquipItem[a_itemTPID=%d][count=%d][index=%d]", a_item.m_itemTPID, a_item.m_itemCount,index);
    }

    return EADDITEM_SUCCESS;
}

bool CRoleBagModuleGM::_addEquip(const SItemInstanceID& a_itemInstanceID,bool a_force,bool a_notify,BagIndex& a_index)
{
    BSLib::uint32 instanceID = a_itemInstanceID.getInstanceID();
    BSLib::uint32 tpid = a_itemInstanceID.getItemTPID();
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_addEquip[装备放入背包][a_tpid=%d][a_instanceID=%d]", tpid, instanceID);
    ItemSystem::GM::CPrizeItem item;
    item.m_itemTPID = a_itemInstanceID.getItemTPID();
    item.m_itemCount = 1;
    item.m_itemType = GSLib::ItemSystem::GM::EITEM_TP_IVALID;
    EAddResult reason = EADDITEM_INVALID_ITEM;
    if(!isableAddItem(item,a_force,reason)){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "isableAddItem失败[装备放入背包][a_tpid=%d][a_instanceID=%d]", tpid, instanceID);
        return false;
    }
 
    std::vector<SDesItem> desItemArray;
    if(!m_bagMgr->getDesIndex(item,instanceID,desItemArray,a_force)){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "getDesIndex[a_itemTPID=%d][type=%d][count=%d]", item.m_itemTPID, item.m_itemType, item.m_itemCount);
        return false;
    }

    if(desItemArray.size() != 1){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_addEquip[装备放入背包desItemArray.size() != 1][a_tpid=%d][a_instanceID=%d]", tpid, instanceID);
        return false;
    }
    SItemInstanceID itemEntityID(desItemArray[0].m_tpid,instanceID);
    if(!m_bagMgr->addItemByIndex(desItemArray[0].m_index,itemEntityID,desItemArray[0].m_type,desItemArray[0].m_count)){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "addItemByIndex失败[装备放入背包][a_tpid=%d][a_instanceID=%d]", tpid, instanceID);
        return false;
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[装备放入背包,通知修改][a_tpid=%d][a_instanceID=%d]", tpid, instanceID);
    notifyBagItemCount(desItemArray[0].m_index,a_notify,true);
    a_index = desItemArray[0].m_index;
    desItemArray.clear();

    return true;
}

bool CRoleBagModuleGM::_randEquip(ItemTPID a_tpid,bool a_statusOn,bool a_force,bool a_notify,BagIndex& a_index,const std::string& a_reason)
{
    CRoleGM* role = getRoleGM();
    if(role == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[获取角色模块失败][a_tpid=%d]", a_tpid);
        return false;
    }
    using namespace EquipSystem::GM;
    CRoleEquipModule* equipModule = (CRoleEquipModule*)role->getPlayerModuleGM(EMODULECTYPE_EQUIP);
    if(equipModule == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[获取装备模块失败][a_tpid=%d]", a_tpid);
        return false;
    }
    if(NULL == equipModule->randEquip(a_tpid,a_statusOn,a_force,a_notify,a_index,a_reason)){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[随机生成装备失败][a_tpid=%d]", a_tpid);
        return false;
    }

    return true;
}

EAddResult CRoleBagModuleGM::_addBagItems(const std::vector<SItemInstanceID>& a_itemInstanceIDs, const std::vector<BSLib::uint32>& a_itemCounts,bool a_force,bool a_notify)
{
    for(BSLib::uint32 i=0;i<a_itemInstanceIDs.size();++i){
        ItemTPID tpid = a_itemInstanceIDs[i].getItemTPID();
        EItemType type = CItemGMMgr::singleton().getType(tpid);
        CPrizeItem item(tpid,type,a_itemCounts[i]);
        addItem(item,a_force,a_notify);
    }

    return EADDITEM_SUCCESS;
}

void CRoleBagModuleGM::_notifyBagDataToClient()
{
    GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
    if (roleGM == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[roleGM == NULL]");
        return ;
    }
 
    CMsgPlayerSystemGM2GCNtfBagData ntf;
    ntf.m_bagSize = getBagSize();
    ntf.m_usedBagPosCount = m_bagMgr->getUsedPosCount();
    m_bagMgr->serializeToClient(roleGM,ntf.m_usedBagPosCount,ntf.m_stream);
    sendMsgToClient(ntf);
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM,"%s_notifyBagDataToClient[m_bagPosCount=%d][m_usedBagPosCount=%d]",getRoleInfor().c_str(), m_bagMgr->getPosCount(),m_bagMgr->getUsedPosCount());
}

void CRoleBagModuleGM::_outputGameLog(const std::string& a_gameLable, const char* a_format, ...)
{
    GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
    if (roleGM == NULL) {
        return ;
    }
    std::string strFormat;

    va_list args;
    va_start(args, a_format);

    BSLib::Utility::stringFormat(strFormat, a_format, args);

    va_end(args);

    roleGM->outputGameLog(a_gameLable,"%s",strFormat.c_str());
}

std::string CRoleBagModuleGM::getRoleInfor() const
{
    GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
    if (roleGM == NULL) {
        return "";
    }
    return roleGM->getRoleLogString();
}


}//GM

}//PlayerSystem

}//GSLib
