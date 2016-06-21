#include <stdarg.h>
#include <GSLib/tracer.h>
#include <GSLib/equipSystem/GM/roleEquipModule.h>
#include <GSLib/equipSystem/msgEquipSystem.h>
#include <GSLib/dbSystem/GM/dbSystemGM.h>
#include <GSLib/equipSystem/DB/tableEquipDB.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/playerSystem/GM/playerSystemGM.h>
#include "equipConfigGMMgr.h"
#include <GSLib/equipSystem/GM/equipSystemGM.h>
#include <GSLib/prizeSystem/GM/rolePrizeModule.h>
#include <GSLib/itemSystem/GM/itemGMMgr.h>
#include <BSLib/utility/random.h>
#include <math.h>
namespace GSLib
{

namespace EquipSystem
{	

namespace GM
{

CRoleEquipModule::CRoleEquipModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType)
: GSLib::PlayerSystem::GM::CRoleModuleGM(a_roleGM, a_moduleType)
, m_uniqueIDByEquipID(1, MAX_EQUIP_EQUIPID, (BSLib::uint32)INVALID_EQUIPID)
{
    m_uniqueIDByEquipID.setUniqueIDMgr(this);
    for(BSLib::uint32 i=EQUIP_INVALID;i<EQUIP_NUMBER; ++i){
        m_roleEquipID[i]=0;
    }

}

CRoleEquipModule::~CRoleEquipModule()
{
	;
}

void CRoleEquipModule::preInit(bool isFirst)
{
}

void CRoleEquipModule::postInit(bool isFirst)
{
   
}

void CRoleEquipModule::initToClient()
{
	_checkExpiredEquip();
}

void CRoleEquipModule::final()
{
    BSLib::Utility::CHashMap<EquipID, CRoleEquipGM*>::iterator it = m_equipHashMap.begin();
    for (; it != m_equipHashMap.end(); ++it) {
        CRoleEquipGM* data =  it->second;
        if (data == NULL) {
            continue;
        }
        data->final();
        BSLIB_SAFE_DELETE(data);
    }
    m_equipHashMap.clear();
}

void CRoleEquipModule::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDEquipSystemGC2GMReqEquipData, &BSLib::Framework::CreateCMessage<CMsgEquipSystemGC2GMReqEquipData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDEquipSystemGC2GMReqEquipData, &CRoleEquipModule::_onMsgEquipSystemGC2GMReqEquipData, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDEquipSystemGC2GMReqInitRoleEquipData, &BSLib::Framework::CreateCMessage<CMsgEquipSystemGC2GMReqGetEquipItem>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDEquipSystemGC2GMReqInitRoleEquipData, &CRoleEquipModule::_onMsgEquipSystemGC2GMReqGetEquipItem, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDEquipSystemGC2GMReqCondition, &BSLib::Framework::CreateCMessage<CMsgEquipSystemGC2GMReqCondition>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDEquipSystemGC2GMReqCondition, &CRoleEquipModule::_onMsgEquipSystemGC2GMReqCondition, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDEquipSystemGC2GMReqSaveOperation, &BSLib::Framework::CreateCMessage<CMsgEquipSystemGC2GMReqSaveOperation>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDEquipSystemGC2GMReqSaveOperation, &CRoleEquipModule::_onMsgEquipSystemGC2GMReqSaveOperation, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDEquipSystemGC2GMReqUpgradeLevel, &BSLib::Framework::CreateCMessage<CMsgEquipSystemGC2GMReqUpgradeLevel>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDEquipSystemGC2GMReqUpgradeLevel, &CRoleEquipModule::_onMsgEquipSystemGC2GMReqUpgradeLevel, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDEquipSystemGC2GMReqUpgradeQuality, &BSLib::Framework::CreateCMessage<CMsgEquipSystemGC2GMReqUpgradeQuality>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDEquipSystemGC2GMReqUpgradeQuality, &CRoleEquipModule::_onMsgEquipSystemGC2GMReqUpgradeQuality, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDEquipSystemGC2GMReqChangeEquipStatus, &BSLib::Framework::CreateCMessage<CMsgEquipSystemGC2GMReqChangeEquipStatus>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDEquipSystemGC2GMReqChangeEquipStatus, &CRoleEquipModule::_onMsgEquipSystemGC2GMReqChangeEquipStatus, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDEquipSystemGC2GMReqResetAttr, &BSLib::Framework::CreateCMessage<CMsgEquipSystemGC2GMReqResetAttr>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDEquipSystemGC2GMReqResetAttr, &CRoleEquipModule::_onMsgEquipSystemGC2GMReqResetAttr, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDEquipSystemGC2GMReqGemCombine, &BSLib::Framework::CreateCMessage<CMsgEquipSystemGC2GMReqGemCombine>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDEquipSystemGC2GMReqGemCombine, &CRoleEquipModule::_onMsgEquipSystemGC2GMReqGemCombine, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDEquipSystemGC2GMReqChangeGemStatus, &BSLib::Framework::CreateCMessage<CMsgEquipSystemGC2GMReqChangeGemStatus>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDEquipSystemGC2GMReqChangeGemStatus, &CRoleEquipModule::_onMsgEquipSystemGC2GMReqChangeGemStatus, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDEquipSystemGC2GMReqNextAddLevelEquip, &BSLib::Framework::CreateCMessage<CMsgEquipSystemGC2GMReqNextAddLevelEquip>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDEquipSystemGC2GMReqNextAddLevelEquip, &CRoleEquipModule::_onMsgEquipSystemGC2GMReqNextAddLevelEquip, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDEquipSystemGC2GMReqDisassemblyEquip, &BSLib::Framework::CreateCMessage<CMsgEquipSystemGC2GMReqDisassemblyEquip>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDEquipSystemGC2GMReqDisassemblyEquip, &CRoleEquipModule::_onMsgEquipSystemGC2GMReqDisassemblyEquip, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDEquipSystemGC2GMReqGetDisassemblyEquipResult, &BSLib::Framework::CreateCMessage<CMsgEquipSystemGC2GMReqGetDisassemblyEquipResult>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDEquipSystemGC2GMReqGetDisassemblyEquipResult, &CRoleEquipModule::_onMsgEquipSystemGC2GMReqGetDisassemblyEquipResult, this);

}

void CRoleEquipModule::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(MsgIDEquipSystemGC2GMReqInitRoleEquipData);
	a_msgExecMgr->delMsgExecPtr(MsgIDEquipSystemGC2GMReqEquipData);
	a_msgExecMgr->delMsgExecPtr(MsgIDEquipSystemGC2GMReqCondition);
	a_msgExecMgr->delMsgExecPtr(MsgIDEquipSystemGC2GMReqSaveOperation);

	a_msgExecMgr->delMsgExecPtr(MsgIDEquipSystemGC2GMReqUpgradeLevel);
	a_msgExecMgr->delMsgExecPtr(MsgIDEquipSystemGC2GMReqUpgradeQuality);
	a_msgExecMgr->delMsgExecPtr(MsgIDEquipSystemGC2GMReqChangeEquipStatus);
	a_msgExecMgr->delMsgExecPtr(MsgIDEquipSystemGC2GMReqResetAttr);

	a_msgExecMgr->delMsgExecPtr(MsgIDEquipSystemGC2GMReqGemCombine);
	a_msgExecMgr->delMsgExecPtr(MsgIDEquipSystemGC2GMReqChangeGemStatus);

	a_msgExecMgr->delMsgExecPtr(MsgIDEquipSystemGC2GMReqNextAddLevelEquip);
	a_msgExecMgr->delMsgExecPtr(MsgIDEquipSystemGC2GMReqDisassemblyEquip);
	a_msgExecMgr->delMsgExecPtr(MsgIDEquipSystemGC2GMReqGetDisassemblyEquipResult);
}

void CRoleEquipModule::updateDataToDB()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[updateDataToDB]");
	GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
	if (roleGM == NULL) {
		return ;
	}

    BSLib::Utility::CHashMap<EquipID, CRoleEquipGM*>::iterator it = m_equipHashMap.begin();
	for(;it != m_equipHashMap.end();++it){
		CRoleEquipGM* equip = it->second;
		if(equip == NULL){
			BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[GETEQUIP_ERROR]updateDataToDB[m_equipHashMap.size=%d][equip == NULL]",m_equipHashMap.size());
			continue;
		}
		DB::SRoleEquipData roleEquipData;
        roleEquipData.clearEquipData();
		roleEquipData.m_accountID = roleGM->getAccountID();
		roleEquipData.m_zoneID = roleGM->getZoneID();
		roleEquipData.m_roleIndex = roleGM->getRoleIndex();
		equip->getEquipData(roleEquipData);
        BSLib::Utility::CStream a_stream;
        a_stream.reset();
        roleEquipData.serializeTo(a_stream);
        if (!updateTableData("","",EDBTABLEID_ROLE_EQUIP_DATA,a_stream,true)){
            BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[DBWRITE_ERROR]更新装备信息失败");
        }
	}
}


void CRoleEquipModule::updateDataToDB(EquipID a_equipID)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[updateDataToDB][a_equipID=%d]",a_equipID);
    GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
    if (roleGM == NULL) {
        return ;
    }
    CRoleEquipGM* equip = _getEquip(a_equipID);
    if(equip == NULL){
        return;
    }
    DB::SRoleEquipData roleEquipData;
    roleEquipData.clearEquipData();
    roleEquipData.m_accountID = roleGM->getAccountID();
    roleEquipData.m_zoneID = roleGM->getZoneID();
    roleEquipData.m_roleIndex = roleGM->getRoleIndex();
    equip->getEquipData(roleEquipData);
    BSLib::Utility::CStream a_stream;
    a_stream.reset();
    roleEquipData.serializeTo(a_stream);
    if (!updateTableData("","",EDBTABLEID_ROLE_EQUIP_DATA,a_stream,true)){
        BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[DBWRITE_ERROR]更新装备失败");
    }
}

bool CRoleEquipModule::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[cbSelectKeyTableData][a_sessionID=%d][a_tableID=%d]",a_sessionID,a_tableID);
	return true;
}

bool CRoleEquipModule::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[cbSelectKeyIndexTableData][a_sessionID=%d][a_tableID=%d]",a_sessionID,a_tableID);
	GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
	if (roleGM == NULL) {
		return true;
	}
	const BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>* tables = a_keyTable->getRows(roleGM->getRoleDBKey());
	if (tables == NULL) {
		return true;
	}
	BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::const_iterator it = tables->begin();
	for (; it != tables->end(); ++it) {
		BSLib::Database::CDBTableRow* row = it->second;
		if (row == NULL) {
			continue;
		}
		DB::SRoleEquipData equip;
        BSLib::Utility::CStream equipStream;
		 if (!row->serializeTo(equipStream)) {
			continue;
		}
        equip.serializeFrom(equipStream);
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "数据库读取装备：装备基础属性[m_equipAttr=%s]",equip.m_equipAttr.toLogString().c_str());
        _createEquipGM(equip);
	}
    _updateEquipTotalBattleAttr(false);

	return true;
}
void CRoleEquipModule::cbSelectTableData(BSLib::uint32 a_sessionID, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[cbSelectTableData][a_sessionID=%d][a_tableID=%d]",a_sessionID,a_tableID);
	if (a_tableID == EDBTABLEID_ROLE_EQUIP_DATA) {
	}
	if (a_stream.readSize() <= 0) {
		return;
	}
}

bool CRoleEquipModule::updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave)
{
    PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if (role == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "获取当前角色失败");
        return false;
    }
    const SRoleKey& roleKey = role->getRoleKey();
	std::string tableKey = roleKey.getDBKey();
	if (!GSLib::EquipSystem::GM::CEquipSystemGM::singleton().updateTableData(tableKey, a_tableIndex, a_name, a_tableID, a_stream, a_needSave)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "更新表[TableID=%d]失败%s", a_tableID, roleKey.toLogString().c_str());
		return false;
	}
	return true;
}

bool CRoleEquipModule::updateTableData(EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize, bool a_needSave)
{
	if (!GSLib::EquipSystem::GM::CEquipSystemGM::singleton().updateTableData("", "", "", a_tableID, a_data, a_dataSize, a_needSave)) {
        PlayerSystem::GM::CRoleGM* role = getRoleGM();
        if (role == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "获取当前角色失败");
            return false;
        }
        const SRoleKey& roleKey = role->getRoleKey();
		BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[DBWRITE_ERROR]更新表[TableID=%d]失败%s", a_tableID, roleKey.toLogString().c_str());
		return false;
	}
	return true;
}

void CRoleEquipModule::onRoleDelete()
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[CRoleEquipModule::onRoleDelete()][冻结装备数据]");
}

bool CRoleEquipModule::checkUniqueID(EquipID a_equipID)
{
    return m_equipHashMap.find(a_equipID) != m_equipHashMap.end();
}

void CRoleEquipModule::_notifyEquipUpdateDataToClient(EquipID a_equipID)
{
	CMsgEquipSystemGM2GCAckUpdateRoleEquipData ack;
	CRoleEquipGM* equip = _getEquip(a_equipID);
	if(equip == NULL){
		BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "获取装备失败[a_equipID == %d]",a_equipID);
		ack.m_retCode = EINITEQUIPDATA_RESULT_FAIL;
		sendMsgToClient(ack);
		return;
	}
	bool bSuccess = equip->serializeTo(ack.m_stream);
	ack.m_retCode = bSuccess?EINITEQUIPDATA_RESULT_SUCCESS:EINITEQUIPDATA_RESULT_FAIL;
	sendMsgToClient(ack);
	BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[_notifyEquipUpdateDataToClient][a_equipID=%d]", a_equipID);
}

bool CRoleEquipModule::removeTableData(BSLib::Utility::CStream& a_steam, EDBTableID a_tableID, bool a_needSave)
{
    if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().removeTableData(a_steam, a_tableID, a_needSave)) {
        GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
        if(role == NULL){
            return false;
        }
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "删除表[TableID=%d]失败%s", a_tableID, role->getRoleKey().toLogString().c_str());
        return false;
    }
    return true;
}

bool CRoleEquipModule::removeTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, EDBTableID a_tableID, bool a_needSave)
{
    if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().removeTableData(a_tabkeKey, a_tableIndex, a_tableID, a_needSave)) {
        GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
        if(role == NULL){
            return false;
        }
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "删除表[TableID=%d]失败%s", a_tableID, role->getRoleKey().toLogString().c_str());
        return false;
    }
    return true;
}
bool CRoleEquipModule::_dbRemoveItem(BSLib::uint32 a_equipID)
{
    BSLib::Utility::CStream stream;
    stream.reset();
    PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if(role == NULL){
        return false;
    }

    std::string dbKey = role->getRoleDBKey();
    std::string dbIndex;
    dbIndex.append((char*)&a_equipID, sizeof(a_equipID));
    return removeTableData(dbKey,dbIndex,EDBTABLEID_ROLE_EQUIP_DATA,true);
}


void CRoleEquipModule::_onMsgEquipSystemGC2GMReqResetAttr(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	
	_checkExpiredEquip();
	CMsgEquipSystemGC2GMReqResetAttr* req = (CMsgEquipSystemGC2GMReqResetAttr*)a_msg;
	CMsgEquipSystemGM2GCAckResetAttr ack;
    if(req->m_resetEquipType == ERESET_EQUIP_TYPE_XILIAN)
	{
		ack.m_retCode = _resetAttr(req->m_equipID,req->m_resetEquipType,req->m_lockAttrIndexArray, req->m_itemEquipID);
	}
	else
	{
		ack.m_retCode = _exchangeAttr(req->m_equipID, req->m_itemEquipID);
	}

    if(ack.m_retCode == ERESETATTR_RESULT_SUCCESS){
        CRoleEquipGM* equip = _getEquip(req->m_equipID);
        if(equip == NULL){
            BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr洗练获取装备失败[a_equipID == %d]",getRoleInfor().c_str(),req->m_equipID);
            ack.m_retCode = ERESETATTR_RESULT_FAIL;
            sendMsgToClient(ack);
            return;
        }
        equip->serializeTo(ack.m_stream);
    }
    sendMsgToClient(ack);
}

void CRoleEquipModule::_onMsgEquipSystemGC2GMReqGetEquipItem(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	_checkExpiredEquip();

    CMsgEquipSystemGC2GMReqGetEquipItem* req = (CMsgEquipSystemGC2GMReqGetEquipItem*)a_msg;
    CMsgEquipSystemGM2GCAckGetEquipItem ack;
    CRoleEquipGM* equip = NULL;
    if(req->m_reqType == 0){
      BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sGetEquipItem通过装备ID获取装备[a_equipID == %d]",getRoleInfor().c_str(),req->m_reqID);
       equip = _getEquip(req->m_reqID);
    }
    else if(req->m_reqType == 1){
       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sGetEquipItem","通过格子索引ID获取装备[posIndex == %d]",getRoleInfor().c_str(),req->m_reqID);
        GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = _getBag();
        if(bag == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "获取背包失败[posIndex == %d]",req->m_reqID);
            ack.m_retCode = EINITEQUIPDATA_RESULT_FAIL;
            sendMsgToClient(ack);
            return;
        }
        EquipID equipID = bag->getInstanceIDByIndex(req->m_reqID);
        equip = _getEquip(equipID);
        if(equip == NULL){
           BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sGetEquipItem获取装备失败,当前格子中无装备[posIndex = %d]",getRoleInfor().c_str(),req->m_reqID);
        }
    }
    
    if(equip == NULL){
       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sGetEquipItem获取装备失败[m_reqID == %d]",getRoleInfor().c_str(),req->m_reqID);
        ack.m_retCode = EINITEQUIPDATA_RESULT_FAIL;
        sendMsgToClient(ack);
        return;
    }
    bool bSuccess = equip->serializeTo(ack.m_stream);
    ack.m_retCode = bSuccess?EINITEQUIPDATA_RESULT_SUCCESS:EINITEQUIPDATA_RESULT_FAIL;
    sendMsgToClient(ack);
}

void CRoleEquipModule::_onMsgEquipSystemGC2GMReqNextAddLevelEquip(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	
	_checkExpiredEquip();

    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "_onMsgEquipSystemGC2GMReqGetEquipItem请求获取角色身上装备");
    CMsgEquipSystemGC2GMReqNextAddLevelEquip* req = (CMsgEquipSystemGC2GMReqNextAddLevelEquip*)a_msg;
    CMsgEquipSystemGM2GCAckNextAddLevelEquip ack;
    CRoleEquipGM* equip = NULL;
   BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sNextAddLevelEquip通过装备ID获取装备[a_equipID == %d]",getRoleInfor().c_str(),req->m_equipID);
    equip = _getEquip(req->m_equipID);

    if(equip == NULL){
       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sNextAddLevelEquip[EGETEQUIP_RESULT_EQUIP_NOT_EXIST][a_equipID == %d]",getRoleInfor().c_str(),req->m_equipID);
        ack.m_retCode = EGETEQUIP_RESULT_EQUIP_NOT_EXIST;
        sendMsgToClient(ack);
        return;
    }
    bool bSuccess = equip->getNextAddLevelData(ack.m_stream);
    ack.m_retCode = bSuccess?EGETEQUIP_RESULT_SUCCESS:EGETEQUIP_RESULT_FAIL;
    sendMsgToClient(ack);
}

void CRoleEquipModule::_onMsgEquipSystemGC2GMReqDisassemblyEquip(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	
	_checkExpiredEquip();
    CMsgEquipSystemGC2GMReqDisassemblyEquip* req = (CMsgEquipSystemGC2GMReqDisassemblyEquip*)a_msg;
    CMsgEquipSystemGM2GCAckDisassemblyEquip ack;
    ack.m_retCode = _disassemblyEquipList(req->m_equipIDArray);
    sendMsgToClient(ack);
}

void CRoleEquipModule::_onMsgEquipSystemGC2GMReqGetDisassemblyEquipResult(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	
	_checkExpiredEquip();
    CMsgEquipSystemGC2GMReqGetDisassemblyEquipResult* req = (CMsgEquipSystemGC2GMReqGetDisassemblyEquipResult*)a_msg;
    CMsgEquipSystemGM2GCAckGetDisassemblyEquipResult ack;
    ack.m_retCode = _getDisassemblyEquipResultList(req->m_equipIDArray,ack.m_stream);
    sendMsgToClient(ack);
}

void CRoleEquipModule::_onMsgEquipSystemGC2GMReqEquipData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	_checkExpiredEquip();

    CMsgEquipSystemGC2GMReqEquipData* req = (CMsgEquipSystemGC2GMReqEquipData*)a_msg;
    updateEquipStatus();
    CMsgEquipSystemGM2GCAckEquipData ack;
    bool bSuccess = false;
    switch(req->m_type){
        case REQ_EQUIP_ON:
            {
               bSuccess = _getEquipData(EQUIP_STATUS_ON,ack.m_equipCount,ack.m_stream);
            }
            break;
        case REQ_EQUIP_OFF:
            {
                bSuccess = _getEquipData(EQUIP_STATUS_OFF,ack.m_equipCount,ack.m_stream);
            }
            break;
        case REQ_EQUIP_ALL:
            {
                bSuccess = _getAllEquipData(ack.m_equipCount,ack.m_stream);
            }
            break;
        default:break;
    }
    ack.m_retCode = bSuccess?EEQUIPDATA_RESULT_SUCCESS:EEQUIPDATA_RESULT_FAIL;
    sendMsgToClient(ack);
}

void CRoleEquipModule::_onMsgEquipSystemGC2GMReqCondition(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	_checkExpiredEquip();

    CMsgEquipSystemGC2GMReqCondition* req = (CMsgEquipSystemGC2GMReqCondition*)a_msg;
   BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sReqCondition请求获取装备操作条件[m_equipID=%d][m_operation=%d]",getRoleInfor().c_str(),req->m_equipID,req->m_operation);
    CMsgEquipSystemGM2GCAckCondition ack;
    CConditionData condition;
    if(!_getOperationCondition(req->m_equipID,(EEquipOperation)req->m_operation,condition)){
       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sReqCondition装备操作条件获取失败[EquipID=%d][op=%d]",getRoleInfor().c_str(),req->m_equipID,req->m_operation);
        ack.m_retCode = ECONDITION_RESULT_FAIL;
        sendMsgToClient(ack);
        return ;
    }
    condition.serializeTo(ack.m_stream);
    ack.m_retCode = ECONDITION_RESULT_SUCCESS;
    sendMsgToClient(ack);
}

void CRoleEquipModule::_onMsgEquipSystemGC2GMReqSaveOperation(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	_checkExpiredEquip();

     CMsgEquipSystemGC2GMReqSaveOperation* req = (CMsgEquipSystemGC2GMReqSaveOperation*)a_msg;

	CMsgEquipSystemGM2GCAckSaveOperation ack;
	ack.m_equipID = req->m_equipID;
	do 
	{
		// 获取装备
		CRoleEquipGM *equip = _getEquip(req->m_equipID);
		if (NULL == equip){
			BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr[ERESETATTR_RESULT_EQUIP_NOT_EXIST][洗练获取装备失败][a_equipID=%d]",getRoleInfor().c_str(),req->m_equipID);
			ack.m_retCode =  ERESETATTR_RESULT_EQUIP_NOT_EXIST;
			break;
		}

		if( true != equip->m_canUndo)
		{
			ack.m_retCode =  ERESETATTR_RESULT_FAIL;
			break;
		}

		GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
		if(role == NULL){
			BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[GETROLE_ERROR][获取角色模块失败]");
			ack.m_retCode =  ERESETATTR_RESULT_FAIL;
			break;
		}

		BSLib::uint32 needDiamond = 20;
		BSLib::uint32 curDiamond = role->getTotalDiamond();
		if(curDiamond < needDiamond){
			BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr[ERESETATTR_RESULT_DIAMOND_LIMIT][m_equipID=%d][curDiamond=%d][needDiamond=%d]",getRoleInfor().c_str(),equip->getEquipID(),curDiamond,needDiamond);
			ack.m_retCode =  ERESETATTR_RESULT_DIAMOND_LIMIT;
			break;
		}

		BSLib::uint32 diamond = needDiamond;
		if(!role->delDiamond(diamond,"EQUIP_RESET",true)){
			BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr[ERESETATTR_RESULT_FAIL][m_equipID=%d][curDiamond=%d][needDiamond=%d]",getRoleInfor().c_str(),equip->getEquipID(),curDiamond,needDiamond);
			ack.m_retCode =  ERESETATTR_RESULT_FAIL;
			break;
		}

		equip->setAttachAttr(equip->m_oldAttach);
		equip->m_canUndo = false;

		equip->updateEquipBattleAttr();
		updateDataToDB(req->m_equipID);
		_updateEquipTotalBattleAttr(true);
		
		ack.m_retCode = ERESETATTR_RESULT_SUCCESS;
	} while (false);
	
	sendMsgToClient(ack);
}

void CRoleEquipModule::_onMsgEquipSystemGC2GMReqUpgradeLevel(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	_checkExpiredEquip();

    CMsgEquipSystemGC2GMReqUpgradeLevel* req = (CMsgEquipSystemGC2GMReqUpgradeLevel*)a_msg;
    CMsgEquipSystemGM2GCAckUpgradeLevel ack;
    ack.m_retCode = _upgradeLevel(req->m_equipID);
    if(ack.m_retCode == EUPGRADELEVEL_RESULT_SUCCESS){
        CRoleEquipGM* equip = _getEquip(req->m_equipID);
        if(equip == NULL){
           BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sUpgradeEquipLevel[EUPGRADELEVEL_RESULT_EQUIP_NOT_EXIST][a_equipID = %d]",getRoleInfor().c_str(),req->m_equipID);
            ack.m_retCode = EUPGRADELEVEL_RESULT_EQUIP_NOT_EXIST;
            sendMsgToClient(ack);
            return;
        }
        ack.m_retCode = EUPGRADELEVEL_RESULT_SUCCESS;
        equip->serializeTo(ack.m_stream);
       
    }
    sendMsgToClient(ack);
}

void CRoleEquipModule::_onMsgEquipSystemGC2GMReqUpgradeQuality(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
// 	CMsgEquipSystemGC2GMReqUpgradeQuality* req = (CMsgEquipSystemGC2GMReqUpgradeQuality*)a_msg;
//     CMsgEquipSystemGM2GCAckUpgradeQuality ack;
//     ack.m_retCode = _upgradeQuality(req->m_equipID,req->m_itemTPID,m_qualityResult);
//     if(ack.m_retCode == EUPGRADELEVEL_RESULT_SUCCESS){
//         CRoleEquipGM* equip = _getEquip(req->m_equipID);
//         if(equip == NULL){
//             BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "获取装备失败[a_equipID == %d]",req->m_equipID);
//             ack.m_retCode = EUPGRATEQUALITY_EEQUIPRESUlT_FAIL;
//             sendMsgToClient(ack);
//             return;
//         }
//         ack.m_retCode = EUPGRATEQUALITY_EEQUIPRESUlT_SUCCESS;
//         equip->serializeEquipOptionResultTo(EQUIP_UPGRADE_QUALITY,m_qualityResult.m_quality,m_qualityResult.m_battleAttr,ack.m_stream);
//     }
//     sendMsgToClient(ack);
}

void CRoleEquipModule::_onMsgEquipSystemGC2GMReqChangeEquipStatus(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	
	_checkExpiredEquip();

    CMsgEquipSystemGC2GMReqChangeEquipStatus* req = (CMsgEquipSystemGC2GMReqChangeEquipStatus*)a_msg;
    CMsgEquipSystemGM2GCAckChangeEquipStatus ack;
    ack.m_equipID = req->m_equipID;
    ack.m_itemIndex = req->m_itemIndex;
    ack.m_status = req->m_status;
    GSLib::PlayerSystem::GM::CRoleGM* curRole = getRoleGM();
    if (curRole == NULL) {
        return ;
    }
    GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = curRole->getRoleBag();
    if(bag == NULL){
        return ;
    }
    if(req->m_status == EQUIP_STATUS_ON){
        BSLib::uint32 equipID = req->m_equipID;
        CRoleEquipGM* equip = _getEquip(equipID);
        if(equip == NULL){
           BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sChangeEquipStatus[ECHANGESTATUS_RESULT_FAIL][装备不存在][m_equipID=%d]",getRoleInfor().c_str(),req->m_equipID);
            ack.m_retCode = ECHANGESTATUS_RESULT_FAIL;
            sendMsgToClient(ack);
            return;
        }
        BSLib::uint32 proType = ItemSystem::GM::CItemGMMgr::singleton().getProLimit(equip->getTPID());
        BSLib::uint32 curType = curRole->getTPID();
        if ((proType !=0)&&(curType != proType)&&(proType != 0)){
           BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sChangeEquipStatus[ECHANGESTATUS_RESULT_INVALID_EQUIP_PROTYPE][m_equipID=%d][proType=%d][curType=%d]",getRoleInfor().c_str(),equipID,proType,curType);
            ack.m_retCode = ECHANGESTATUS_RESULT_INVALID_EQUIP_PROTYPE;
            sendMsgToClient(ack);
            return;
        }

        BSLib::uint32 minLevel = ItemSystem::GM::CItemGMMgr::singleton().getLevelLimit(equip->getTPID());
        BSLib::uint32 curLevel = curRole->getLevel();
        if (curLevel < minLevel){
           BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sChangeEquipStatus[ECHANGESTATUS_RESULT_ROLE_LEVEL_LIMIT][m_equipID=%d][curLevel=%d][minLevel=%d]",getRoleInfor().c_str(),equipID,curLevel,minLevel);
            ack.m_retCode = ECHANGESTATUS_RESULT_ROLE_LEVEL_LIMIT;
            sendMsgToClient(ack);
            return;
        }
        
        // 当前状态判断
        if(equip->getEquipStatus() == EQUIP_STATUS_ON){
           BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sChangeEquipStatus[ECHANGESTATUS_RESULT_STATUS_ERROR][已在在身上][m_equipID=%d]",getRoleInfor().c_str(),req->m_equipID);
            ack.m_retCode = ECHANGESTATUS_RESULT_STATUS_ERROR;
            sendMsgToClient(ack);
            return;
        }
       
        EEquipType type = equip->getType();
        // 先保存旧的EquipID
        EquipID oldEquipID = _getEquipID(type);
       
        SItemInstanceID instanceID;
        instanceID.setInstanceID(equip->getEquipID());
        instanceID.setItemTPID(equip->getTPID());
        BagIndex itemIndex = 0;
        if(!bag->getIndexByItemInstanceID(instanceID,itemIndex)){
           BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sChangeEquipStatus[ECHANGESTATUS_RESULT_STATUS_NOT_INBAG][m_equipID=%d]",getRoleInfor().c_str(),req->m_equipID);
            ack.m_retCode = ECHANGESTATUS_RESULT_STATUS_NOT_INBAG;
            sendMsgToClient(ack);
            return;
        }

        if(!bag->removeItemByIndex(itemIndex,"穿上装备",true)){
           BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sChangeEquipStatus[ECHANGESTATUS_RESULT_STATUS_NOT_INBAG][背包中装备删除失败][itemIndex=%d][m_equipID=%d]",getRoleInfor().c_str(),itemIndex,req->m_equipID);
            ack.m_retCode = ECHANGESTATUS_RESULT_STATUS_NOT_INBAG;
            sendMsgToClient(ack);
            return;
        }
         _setEquipStatus(equip,EQUIP_STATUS_ON);
        // 若当前类型装备已经存在，则替换掉装备,要先穿后，脱否则背包可能放不下
        if(oldEquipID != 0){
            CRoleEquipGM* oldEquip = _getEquip(oldEquipID);
           BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sChangeEquipStatus[替换旧装备,修改旧装备状态][m_equipID=%d]",getRoleInfor().c_str(),oldEquipID);
            oldEquip->setEquipStatus(EQUIP_STATUS_OFF);
            SItemInstanceID itemInstanceID(oldEquip->getTPID(),oldEquipID);
            BSLib::uint32 index = 0;
            bag->addEquip(itemInstanceID,false,true,index);
            updateDataToDB(oldEquipID);
        }
         updateDataToDB(equipID);
        _updateEquipTotalBattleAttr(true);
        ack.m_equipID = equip->getEquipID();
        ack.m_retCode = ECHANGESTATUS_RESULT_SUCCESS;
        sendMsgToClient(ack);
        return;
    }
    else if(req->m_status == EQUIP_STATUS_OFF){
        ack.m_retCode = _equipOff(req->m_equipID,ack.m_itemIndex);
        updateDataToDB(req->m_equipID);
        _updateEquipTotalBattleAttr(true);
        sendMsgToClient(ack);
        return;
    }
    ack.m_retCode = ECHANGESTATUS_RESULT_FAIL;
    sendMsgToClient(ack);
}

void CRoleEquipModule::_onMsgEquipSystemGC2GMReqGemCombine(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	
	_checkExpiredEquip();

	BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "_onMsgEquipSystemGC2GMReqGemCombine");
	CMsgEquipSystemGC2GMReqGemCombine* req = (CMsgEquipSystemGC2GMReqGemCombine*)a_msg;
    BSLib::uint32 gemTPID = req->m_gemTPID;
    EGemsCombineType type = (EGemsCombineType)req->m_type;
    CMsgEquipSystemGM2GCAckGemCombine ack;
    ack.m_retCode = _combineGems(type,gemTPID,ack.m_newGemTPID);
    sendMsgToClient(ack);
}

void CRoleEquipModule::_onMsgEquipSystemGC2GMReqChangeGemStatus(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	_checkExpiredEquip();

    CMsgEquipSystemGC2GMReqChangeGemStatus* req = (CMsgEquipSystemGC2GMReqChangeGemStatus*)a_msg;
    CMsgEquipSystemGM2GCAckChangeGemStatus ack;
    EGemStatus opStatus = (EGemStatus)req->m_operation;
    EGemSlot slotIndex =(EGemSlot)req->m_gemSlot;
    if(opStatus == GEM_STATUS_ON){
        ack.m_retCode = _addGemsToEquip(req->m_equipID,req->m_gemTPID,slotIndex);
    }
    else if(opStatus == GEM_STATUS_OFF){
        ack.m_retCode = _removeGemFromEquip(req->m_equipID,req->m_gemTPID,slotIndex);
    }
    else{
        ack.m_retCode = EGEM_UPDATESTATUS_RESULT_FAIL;
    }
    if(ack.m_retCode == EGEM_UPDATESTATUS_RESULT_SUCCESS){
        CRoleEquipGM* equip = _getEquip(req->m_equipID);
        if(equip == NULL){
           BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sChangeGemStatus[EGEM_UPDATESTATUS_RESULT_EQUIP_NOT_EXIST][a_equipID == %d]",getRoleInfor().c_str(),req->m_equipID);
            ack.m_retCode = EGEM_UPDATESTATUS_RESULT_EQUIP_NOT_EXIST;
            sendMsgToClient(ack);
            return;
        }
        equip->serializeTo(ack.m_stream);
    }
    sendMsgToClient(ack);
}

bool CRoleEquipModule::getEquipIDList(BSLib::Utility::CStream& stream) const
{
    for(BSLib::uint32 i=EQUIP_INVALID;i<EQUIP_NUMBER; ++i){
        stream << m_roleEquipID[i];
    }
    for(BSLib::uint32 i=EQUIP_INVALID;i<EQUIP_NUMBER; ++i){
        CRoleEquipGM* equip = _getEquip(m_roleEquipID[i]);
        BSLib::uint32 equipTPID = 0;
        if(equip == NULL){
            equipTPID = 0;
        }
        else{
           equipTPID = equip->getTPID();
        }
        stream << equipTPID;
    }
    return true;
}

const SBattleAttribute& CRoleEquipModule::getTotalBattleAttr() const
{
    return m_totalEquipBattleAttr; 
}

void CRoleEquipModule::_updateEquipTotalBattleAttr(bool a_notify)
{
    m_totalEquipBattleAttr.cleanAttr();
    SBattleAttribute battleValue;
    BSLib::Utility::CHashMap<EquipID, CRoleEquipGM*>::iterator it = m_equipHashMap.begin();
    for(;it != m_equipHashMap.end();++it){
        CRoleEquipGM* equip = it->second;
        if(equip == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[GETEQUIP_ERROR]getTotleEquipBattleAttr[m_equipHashMap.size=%d][equip == NULL]",m_equipHashMap.size());
            continue;
        }
        if(equip->getEquipStatus() == EQUIP_STATUS_OFF){
            continue;
        }
        battleValue.cleanAttr();
        equip->getTotalBattleAttr(battleValue);
        m_totalEquipBattleAttr.addAttr(battleValue);
    }

    GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if(role == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[GETROLE_ERROR][获取角色模块失败]");
        return ;
    }
    role->updateTotalBattleAttr(a_notify);
}

bool CRoleEquipModule::_getEquipList(std::list<CEquipData> &roleEquipList) const
{
    BSLib::Utility::CHashMap<EquipID, CRoleEquipGM*>::const_iterator it = m_equipHashMap.begin();
	for(;it != m_equipHashMap.end();++it){
		CRoleEquipGM* equip = it->second;
		if(equip == NULL){
			BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[GETEQUIP_ERROR]updateDataToDB[m_equipHashMap.size=%d][equip == NULL]",m_equipHashMap.size());
			continue;
		}
		CEquipData equipData;
		equip->getEquipDetailData(equipData);
		roleEquipList.push_back(equipData);
	}

	return true;
}

bool CRoleEquipModule::_getEquipData(EEquipStatus a_status,BSLib::uint32& a_equipCount,BSLib::Utility::CStream& stream) const
{
    a_equipCount = m_equipHashMap.size();
    stream.reset();
    BSLib::Utility::CHashMap<EquipID, CRoleEquipGM*>::const_iterator it = m_equipHashMap.begin();
    for(;it != m_equipHashMap.end();++it){
        CRoleEquipGM* equip = it->second;
        if(equip == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[GETEQUIP_ERROR]_getStatuOnEquipData[m_equipHashMap.size=%d][equip == NULL]",m_equipHashMap.size());
            return false;
        }
        if (equip->getEquipStatus() != a_status){
            a_equipCount--;
            continue;
        }
        equip->serializeTo(stream);
    }
    return true;
}

bool CRoleEquipModule::_getAllEquipData(BSLib::uint32& a_equipCount,BSLib::Utility::CStream& stream) const
{
    a_equipCount = m_equipHashMap.size();
    stream.reset();
    BSLib::Utility::CHashMap<EquipID, CRoleEquipGM*>::const_iterator it = m_equipHashMap.begin();
    for(;it != m_equipHashMap.end();++it){
        CRoleEquipGM* equip = it->second;
        if(equip == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[GETEQUIP_ERROR]_getEquipData[m_equipHashMap.size=%d][equip == NULL]",m_equipHashMap.size());
            return false;
        }
        equip->serializeTo(stream);
    }
    return true;
}

void CRoleEquipModule::updateEquipStatus()
{
    BSLib::Utility::CHashMap<EquipID, CRoleEquipGM*>::const_iterator it = m_equipHashMap.begin();
    for(;it != m_equipHashMap.end();++it){
        CRoleEquipGM* equip = it->second;
        if(equip == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[GETEQUIP_ERROR]_getEquipData[m_equipHashMap.size=%d][equip == NULL]",m_equipHashMap.size());
            return;
        }
        EEquipType equipType = equip->getType();
        EquipID equipID = equip->getEquipID();
        EquipID curOnEquipID = _getEquipID(equipType);
        if ((equip->getEquipStatus() == EQUIP_STATUS_ON) && (curOnEquipID != equipID)){
           BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sUpdateEquipStatus[修正装备状态][a_equipID == %d]",getRoleInfor().c_str(),equipID);
            BagIndex index = 0;
            _equipOff(equipID,index);
            updateDataToDB(equipID);
            _updateEquipTotalBattleAttr(true);
        }
    }
}

CRoleEquipGM* CRoleEquipModule::randEquip(BSLib::uint32 a_tpid,bool a_statusOn,bool a_foreAdd,bool a_notify,BSLib::uint32& a_index,const std::string& a_reason)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[randEquip][a_tpid=%d][根据装备tpid创建装备]",a_tpid);
    BSLib::uint32 equipTPID = a_tpid;
    ItemSystem::GM::EItemType type = ItemSystem::GM::EITEM_TP_IVALID;
    EQualityID qualityID = QUALITY_INVALID;
    BSLib::uint32 level = 0;
    SBattleAttribute attr;		//基础属性
    SBattleAttribute addAttr;	//强化属性
    CAttachAttr attachAttrs;	//附加属性
	
	BSLib::uint32 specfun1 = 0;
    if(!CEquipConfigGMMgr::singleton().randNewEquip(equipTPID,type,qualityID,level,attr,attachAttrs, specfun1)){
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "randEquip[忽略装备配置m_equipTPID=%d]",equipTPID);
        return NULL;
    }

    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "randEquip：装备基础属性[m_equipAttr=%s]",attr.toLogString().c_str());
    BSLib::uint32 slotCount = CEquipConfigGMMgr::singleton().getEquipSlotCount(qualityID);
    EquipID equipID = m_uniqueIDByEquipID.allocateID();
    if (!m_uniqueIDByEquipID.isValidID(equipID)) {
        BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[装备ID分配失败]");
        return NULL;
    }

    EEquipStatus curStatus = a_statusOn?EQUIP_STATUS_ON:EQUIP_STATUS_OFF;
    DB::SRoleEquipData equipData;
    equipData.m_equipID = equipID;
    equipData.m_equipTPID = equipTPID;
    equipData.m_equipQuality = qualityID;
    equipData.m_resetSum = 0;
    equipData.m_equipAddAttr = addAttr;
    equipData.m_equipAttachAttr = attachAttrs;
    equipData.m_equipAttr = attr;
    equipData.m_equipStatus = curStatus;
    equipData.m_slotCount = slotCount;
	equipData.m_equipLevel = level;

    for(BSLib::uint32 i=0;i<EQUIP_COLOR_GEMS_COUNT;++i){
        equipData.m_equipColorGemsCount[i] = 0;
    }
	
	if( 0 != specfun1)
	{	
		// 过期时间
		equipData.m_equipColorGemsCount[0] =  BSLib::Utility::CDateTime::getCurrentTime().getSeconds() + specfun1 * 60;
	}

    for(BSLib::uint32 i=0;i<4;++i){
        equipData.m_slotGemTPID[i] = 0;
    }

    CRoleEquipGM* equip = _createEquipGM(equipData);
    if(equip == NULL){
        return NULL;
    }

	if(EQUIP_NENGLIANGQIU == equip->getType())
	{
		equip->setEquipAddLevel(1);
	}

    GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = _getBag();
    if(bag == NULL){
        return NULL;
    }
    if(!a_statusOn){
        SItemInstanceID itemInstanceID(equip->getTPID(),equip->getEquipID());
        if(!bag->addEquip(itemInstanceID,a_foreAdd,a_notify,a_index)){
            return NULL;
        }
    }

    _outputGameLog("t_resource","[f_type=%d][f_resource_id=%u][f_count=%u][][f_source=%s][AddEquip]", 1, equipTPID, 1, a_reason.c_str());

    return equip;
}


bool CRoleEquipModule::removeEquip(EquipID a_equipID)
{
    CRoleEquipGM* equip = NULL;
    BSLib::Utility::CHashMap<EquipID, CRoleEquipGM*>::iterator it = m_equipHashMap.find(a_equipID);
    if( it != m_equipHashMap.end())
    {
        equip = it->second;
        if (equip->getEquipStatus() == EQUIP_STATUS_ON){
            EEquipType type = equip->getType();
            _setRoleEquip(type,0);
        }
        BSLIB_SAFE_DELETE(equip);
        m_equipHashMap.erase(it);
        _dbRemoveItem(a_equipID);
        return true;
    }
    return false;
}

bool CRoleEquipModule::getDataForBag(EquipID a_equipID,BSLib::Utility::CStream& stream) const
{
    CRoleEquipGM* equip = NULL;
    BSLib::Utility::CHashMap<EquipID, CRoleEquipGM*>::const_iterator it = m_equipHashMap.find(a_equipID);
    if( it != m_equipHashMap.end())
    {
        equip = it->second;
        equip->getDataForBag(stream); 
        return true;
    }
    return false;
}

bool CRoleEquipModule::getEquipDataForBag(EquipID a_equipID,ItemTPID a_tpid,BSLib::Utility::CStream& stream) const
{
    CRoleEquipGM* equip = NULL;
    BSLib::Utility::CHashMap<EquipID, CRoleEquipGM*>::const_iterator it = m_equipHashMap.find(a_equipID);
    if( it != m_equipHashMap.end())
    {
        equip = it->second;
        if(equip->getTPID() != a_tpid){
            return false;
        }
        equip->getDataForBag(stream); 
        return true;
    }
    return false;
}

bool CRoleEquipModule::isEquipStatusOn(EquipID a_equipID) const
{
    CRoleEquipGM* equip = NULL;
    BSLib::Utility::CHashMap<EquipID, CRoleEquipGM*>::const_iterator it = m_equipHashMap.find(a_equipID);
    if( it != m_equipHashMap.end())
    {
        equip = it->second;
        EEquipStatus status = equip->getEquipStatus();
        if(status == EQUIP_STATUS_ON){
            return true;
        }
    }
    return false;
}

CRoleEquipGM* CRoleEquipModule::getEquip(EquipID a_equipID) const
{
	return _getEquip(a_equipID);
}

CRoleEquipGM* CRoleEquipModule::_createEquipGM(DB::SRoleEquipData& a_equipData)
{
    ItemSystem::GM::EItemType type = ItemSystem::GM::CItemGMMgr::singleton().getType(a_equipData.m_equipTPID);
    EEquipType equipType = (EEquipType)type;
	CRoleEquipGM* pEquip = NULL;

	pEquip = new CRoleEquipGM(equipType,a_equipData);
	if (pEquip == NULL){
		BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[NEWEQUIP_ERROR]createEquipGM[a_equipType=%d][a_equipID=%d][a_equipTPID=%d]",equipType,a_equipData.m_equipID,a_equipData.m_equipTPID);
		return NULL;
	}

    if(a_equipData.m_equipStatus == EQUIP_STATUS_ON){
        _setRoleEquip(equipType,a_equipData.m_equipID);
    }

    pEquip->initGems(a_equipData.m_slotCount,a_equipData.m_slotGemTPID);
    m_equipHashMap.setValue(a_equipData.m_equipID,pEquip);

	return pEquip;
}

EDisassemblyEquipResult CRoleEquipModule::_disassemblyEquipList(const std::vector<EquipID>& a_equipIDList)
{
    BSLib::uint32 count = a_equipIDList.size();
    for(BSLib::uint32 i=0;i<count; ++i){
        EquipID equipID = a_equipIDList[i];
        EDisassemblyEquipResult result = _checkDisassemblyEquip(equipID);
        if(result != EDISASSEMBLYEQUIP_RESULT_SUCCESS){
            return result;
        }
    }
    for(BSLib::uint32 i=0;i<count; ++i){
        EquipID equipID = a_equipIDList[i];
        EDisassemblyEquipResult result = _disassemblyEquip(equipID);
        if(result != EDISASSEMBLYEQUIP_RESULT_SUCCESS){
            return result;
        }
    }
    // 更新装备总属性
    _updateEquipTotalBattleAttr(true);

    return EDISASSEMBLYEQUIP_RESULT_SUCCESS;
}

EDisassemblyEquipResult CRoleEquipModule::_checkDisassemblyEquip(EquipID a_equipID)
{
    CRoleEquipGM* equip = NULL;
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "通过装备ID获取装备[a_equipID == %d]",a_equipID);
    equip = _getEquip(a_equipID);
    if(equip == NULL){
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "获取装备失败[a_equipID == %d]",a_equipID);
        return EDISASSEMBLYEQUIP_RESULT_EQUIP_NOT_EXIST;
    }

    GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if(role == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[GETROLE_ERROR][获取角色模块失败]");
        return EDISASSEMBLYEQUIP_RESULT_FAIL;
    }

    GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = _getBag();
    if(bag == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[GETBAG_ERROR][获取背包模块失败]");
        return EDISASSEMBLYEQUIP_RESULT_FAIL;
    }
    return EDISASSEMBLYEQUIP_RESULT_SUCCESS;
}

bool CRoleEquipModule::sellEquip(ItemTPID a_id)
{	
	std::vector<ItemSystem::GM::CPrizeItem> a_itemArray;
	BSLib::uint32 levelNum = 0;
	BSLib::uint32 upgradeNumLow = 0;
	BSLib::uint32 upgradeNumMid = 0;
	BSLib::uint32 upgradeNumHigh = 0;
	

	levelNum = 1;
	upgradeNumLow = 1;
	upgradeNumMid = 0;
	upgradeNumHigh = 0;

	GSLib::ItemSystem::GM::CItemDataGM* data = GSLib::ItemSystem::GM::CItemGMMgr::singleton().getItem(a_id);
	if( NULL == data)
		return false;


	if( 0 != upgradeNumLow){	
		ItemSystem::GM::CPrizeItem item;
		item.m_itemTPID = EQUIP_UPGRADE_GEM_LOW;
		item.m_itemType = ItemSystem::GM::EITEM_TP_EQUIP_UPGRADE_MATERIAL;
		item.m_itemCount = upgradeNumLow;
		a_itemArray.push_back(item);
	}

	if( 0 != upgradeNumMid){
		ItemSystem::GM::CPrizeItem item;
		item.m_itemTPID = EQUIP_UPGRADE_GEM_MID;
		item.m_itemType = ItemSystem::GM::EITEM_TP_EQUIP_UPGRADE_MATERIAL;
		item.m_itemCount = upgradeNumMid;
		a_itemArray.push_back(item);
	}

	if( 0 != upgradeNumHigh){
		ItemSystem::GM::CPrizeItem item;
		item.m_itemTPID = EQUIP_UPGRADE_GEM_HIGH;
		item.m_itemType = ItemSystem::GM::EITEM_TP_EQUIP_UPGRADE_MATERIAL;
		item.m_itemCount = upgradeNumHigh;
		a_itemArray.push_back(item);
	}

	if(0 != levelNum){	
		ItemSystem::GM::CPrizeItem item;
		BSLib::uint32 num = 0;
		item.m_itemTPID = CEquipConfigGMMgr::singleton().getEquipUpgradeMetarialByEquipLevel(data->getLevel(), 0, num);
		item.m_itemType = ItemSystem::GM::EITEM_TP_EQUIP_QUALITY_MATERIAL;
		item.m_itemCount = levelNum;
		a_itemArray.push_back(item);
	}

	
	GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
	if(role == NULL){
		BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "获取角色模块失败]");
		return false;
	}

	GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = _getBag();
	if(bag == NULL){
		BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "获取背包模块失败]");
		return false;
	}

	PrizeSystem::GM::CRolePrizeModule *prizeModue = (PrizeSystem::GM::CRolePrizeModule *)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
	if (prizeModue == NULL) {
		return false;
	}
	std::string sender = toMailString("系统信息");
	std::string title = toMailString("装备拆解获得材料");
	std::string content = toMailString("由于背包已满，拆解装备获得的材料以邮件发送，道具如下：");
	prizeModue->prizeRequest(a_itemArray,sender,title,content,"DISASSEMBLY_EQUIP");

	return true;
}

EDisassemblyEquipResult CRoleEquipModule::_disassemblyEquip(EquipID a_equipID)
{
    CRoleEquipGM* equip = NULL;
    equip = _getEquip(a_equipID);
    if(equip == NULL){
       // _outputGameLog("DisassemblyEquip","[EDISASSEMBLYEQUIP_RESULT_EQUIP_NOT_EXIST][获取装备失败][EquipID=%d]",a_equipID);
        return EDISASSEMBLYEQUIP_RESULT_EQUIP_NOT_EXIST;
    }

    GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if(role == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "获取角色模块失败]");
        return EDISASSEMBLYEQUIP_RESULT_FAIL;
    }

    GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = _getBag();
    if(bag == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "获取背包模块失败]");
        return EDISASSEMBLYEQUIP_RESULT_FAIL;
    }
    // 背包判断
    using namespace ItemSystem::GM;
    std::vector<CPrizeItem> itemArray;
    equip->getDisassemblyEquipResult(itemArray);

    // 装备状态
    EEquipStatus status = equip->getEquipStatus();
    if(status == EQUIP_STATUS_OFF){
        SItemInstanceID instanceID;
        instanceID.setInstanceID(equip->getEquipID());
        instanceID.setItemTPID(equip->getTPID());
        BagIndex itemIndex = 0;
        if(bag->getIndexByItemInstanceID(instanceID,itemIndex)){
            if(!bag->removeItemByIndex(itemIndex,"销毁装备",true)){
                return EDISASSEMBLYEQUIP_RESULT_FAIL;
            }
        }
    }

    const BSLib::uint32 equipTPID = equip->getTPID();
    const BSLib::uint32 equipType = equip->getType();
    if(!removeEquip(equip->getEquipID())){
        return EDISASSEMBLYEQUIP_RESULT_FAIL;
    }
    
    PrizeSystem::GM::CRolePrizeModule *prizeModue = (PrizeSystem::GM::CRolePrizeModule *)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
    if (prizeModue == NULL) {
        return EDISASSEMBLYEQUIP_RESULT_FAIL;
    }
    std::string sender = toMailString("系统信息");
    std::string title = toMailString("装备拆解获得材料");
    std::string content = toMailString("由于背包已满，拆解装备获得的材料以邮件发送，道具如下：");
    prizeModue->prizeRequest(itemArray,sender,title,content,"DISASSEMBLY_EQUIP");
	_outputGameLog("t_resource","[f_type=%d][f_resource_id=%u][f_count=%u][][f_source=%s][RemoveEquip]", -1, equipTPID, 1, "DisassemblyEquip");
    return EDISASSEMBLYEQUIP_RESULT_SUCCESS;
}

EGetDisassemblyEquipResult CRoleEquipModule::_getDisassemblyEquipResultList(const std::vector<EquipID>& a_equipIDList,BSLib::Utility::CStream& a_stream)
{
    std::vector<ItemSystem::GM::CPrizeItem> itemArray;
    itemArray.clear();
    BSLib::uint32 count = a_equipIDList.size();
    for(BSLib::uint32 i=0;i<count; ++i){
        EquipID equipID = a_equipIDList[i];
        EGetDisassemblyEquipResult result = _getDisassemblyEquipResult(equipID,itemArray);
        if(result != EGETDISASSEMBLYEQUIP_RESULT_SUCCESS){
           return result;
        }
    }
    std::vector<ItemSystem::GM::CPrizeItem> desItemArray;
    _combineItems(itemArray,desItemArray);
    _getItemDataArray(desItemArray,a_stream);
    return EGETDISASSEMBLYEQUIP_RESULT_SUCCESS;
}

EGetDisassemblyEquipResult CRoleEquipModule::_getDisassemblyEquipResult(EquipID a_equipID,std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray)
{
    CRoleEquipGM* equip = NULL;
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "通过装备ID获取装备[a_equipID == %d]",a_equipID);
    equip = _getEquip(a_equipID);
    if(equip == NULL){
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "获取装备失败[a_equipID == %d]",a_equipID);
        return EGETDISASSEMBLYEQUIP_RESULT_EQUIP_NOT_EXIST;
    }
    equip->getDisassemblyEquipResult(a_itemArray);
    
    return EGETDISASSEMBLYEQUIP_RESULT_SUCCESS;
}

EUpgradeLevelResult CRoleEquipModule::_upgradeLevel(EquipID a_equipID)
{
    CRoleEquipGM* equip = _getEquip(a_equipID);
    if(equip == NULL){
       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sUpgradeEquipLevel[EUPGRADELEVEL_RESULT_EQUIP_NOT_EXIST][a_equipID == %d]",getRoleInfor().c_str(),a_equipID);
        return EUPGRADELEVEL_RESULT_EQUIP_NOT_EXIST;
    }

	CConditionData condition;
	if( EQUIP_NENGLIANGQIU == equip->getType())
		_getOperationCondition(a_equipID,EQUIP_UPGRADE_NENGLIANGQIU,condition);
	else
		_getOperationCondition(a_equipID,EQUIP_UPGRADE_LEVEL,condition);

    GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if(role == NULL){
         return EUPGRADELEVEL_RESULT_FAIL;
    }

    GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = _getBag();
    if(bag == NULL){
        return EUPGRADELEVEL_RESULT_FAIL;
    }

    for(BSLib::uint32 i=0;i<condition.m_itemArray.size(); ++i){
        ItemSystem::GM::CPrizeItem& item = condition.m_itemArray[i];
        BSLib::uint32 curGemCount = bag->getItemCount(item.m_itemTPID);
        if(item.m_itemCount > curGemCount){
          BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sUpgradeEquipLevel[EUPGRADELEVEL_RESULT_METARIAL_LIMIT][m_equipID=%d][curGemCount=%d][needCount=%d]",getRoleInfor().c_str(),a_equipID,curGemCount,item.m_itemCount);
           return EUPGRADELEVEL_RESULT_METARIAL_LIMIT;
        }
    }


    BSLib::uint32 lv = equip->getLevel();
	BSLib::uint32 nextLevel = equip->getEquipAddLevel() + 1;
	EQualityID quality = equip->getQuality();
	BSLib::uint32 limitLv = CEquipConfigGMMgr::singleton().getEquipUpgradeMaxLevelByQuality(equip->getType(), quality);
	if(nextLevel > limitLv){
		BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sUpgradeEquipLevel[EUPGRADELEVEL_RESULT_LEVEL_LIMIT][m_equipID=%d][lv=%d]",getRoleInfor().c_str(),a_equipID,lv);
		return EUPGRADELEVEL_RESULT_LEVEL_LIMIT;
	}
	
	BSLib::uint32 newLevel = 0;
	if( EQUIP_NENGLIANGQIU == equip->getType())
		newLevel = nextLevel;
	else
		newLevel = CEquipConfigGMMgr::singleton().equipGrade(equip->getEquipAddLevel());

	// 金币判断
	BSLib::uint64 curGold = role->getGold();
	BSLib::uint64 needGold = condition.m_gold;
// 	double temp = 1 + lv / 17;
// 	BSLib::uint64 needGold = 40 * nextLevel * pow(temp, 3.0) + 5;
// 	needGold /= 10;
// 	needGold *= 10;
	if(curGold < needGold){
		BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%upgradeLevel[ERESETATTR_RESULT_GOLD_LIMIT][m_equipID=%d][curGold=%lld][needGold=%lld]",getRoleInfor().c_str(),equip->getEquipID(),curGold,needGold);
		return EUPGRADELEVEL_RESULT_GOLD_LIMIT;
	}

	// 光子力判断
	if( 0 != condition.m_guangzili && condition.m_guangzili > role->getLightPower())
	{
		return EUPGRADELEVEL_RESULT_METARIAL_LIMIT;
	}


    for(BSLib::uint32 i=0;i<condition.m_itemArray.size(); ++i){
        ItemSystem::GM::CPrizeItem& item = condition.m_itemArray[i];
       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sUpgradeEquipLevel[m_equipID=%d][itemTPID=%d][needCount=%d]",getRoleInfor().c_str(),a_equipID,item.m_itemTPID,item.m_itemCount);
        bag->removeItemCount(item.m_itemTPID,item.m_itemType,item.m_itemCount,"EQUIP_UPGRADE_ADDLEVEL",true);
    }

	BSLib::int64 gold = 0 - (BSLib::int64)needGold;
	if(!role->modifyGold(gold,"EQUIP_UPGRADE",true)){
		return EUPGRADELEVEL_RESULT_FAIL;
	}

	if(0 != condition.m_guangzili &&  !role->delLightPower(condition.m_guangzili, "EQUIP_UPGRADE_ADDLEVEL", true))
	{
		return EUPGRADELEVEL_RESULT_FAIL;
	}
	
	equip->setEquipAddLevel(newLevel);
    equip->modifyBattleAddAttr();
    equip->updateEquipBattleAttr();
    _updateBagEquip(a_equipID);
    updateDataToDB(a_equipID);
    _updateEquipTotalBattleAttr(true);

   BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sUpgradeEquipLevel[EUPGRADELEVEL_RESULT_SUCCESS][m_equipID=%d][newLevel=%d]",getRoleInfor().c_str(),a_equipID,newLevel);

	return EUPGRADELEVEL_RESULT_SUCCESS;
}

// EUpgradeQualityResult CRoleEquipModule::_upgradeQuality(EquipID a_equipID,ItemTPID a_itemTPID,SQualityReuslt& a_qualityResult)
// {
// 	CRoleEquipGM *roleEquip = _getEquip(a_equipID);
// 	if (NULL == roleEquip){
//         BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "获取装备失败[a_equipID == %d]",a_equipID);
//         return EUPGRATEQUALITY_RESULT_EQUIP_NOT_EXIST;
// 	}
// 
//     if(roleEquip->getQuality() == QUALITY_ORANGE){
//         BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "装备达到熔炼等级上限[m_equipID=%d][QUALITY_ORANGE]",a_equipID);
//         return EUPGRATEQUALITY_RESULT_QUALITY_LIMIT;
//     }
// 
//     GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = _getBag();
//     if(bag == NULL){
//         BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[GETBAG_ERROR][获取背包模块失败]");
//         return EUPGRATEQUALITY_EEQUIPRESUlT_FAIL;
//     }
//     
//     BSLib::uint32 curItemCount = bag->getItemCount(a_itemTPID);
//     if(curItemCount<1){
//         BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "装备熔炼材料不足[m_equipID=%d][curItemCount=%d][a_itemTPID=%d]",a_equipID,curItemCount,a_itemTPID);
//         return EUPGRATEQUALITY_RESULT_METARIAL_LIMIT;
//     }
// 
//     GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
//     if(role == NULL){
//         BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[GETROLE_ERROR][获取角色模块失败]");
//         return EUPGRATEQUALITY_EEQUIPRESUlT_FAIL;
//     }
//     
//     // 道具价值
//     float proValue = ItemSystem::GM::CItemGMMgr::singleton().getItemValue(a_itemTPID);
//     // 金币消耗
//     BSLib::uint64 needGold = (BSLib::uint64)(proValue * 5000);
//     BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[a_itemTPID=%d]道具价值[proValue=%d]金币消耗[needGold=%lld]",a_itemTPID,proValue,needGold);
// 
//     // 条件1：金币足够
//     BSLib::uint64 curGold = role->getGold();
//     if(curGold < needGold){
//         BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "装备熔炼金币不足[m_equipID=%d][curGold=%lld][needGold=%lld]",a_equipID,curGold,needGold);
//         return EUPGRATEQUALITY_RESULT_GOLD_LIMIT;
//     }
//     bag->removeItemCount(a_itemTPID,GSLib::ItemSystem::GM::EITEM_TP_EQUIP_QUALITY_MATERIAL,1,"UPDATE_QUALITY",true);
//     BSLib::int64 gold = 0 - (BSLib::int64)needGold;
//     if(!role->modifyGold(gold,"UPDATE_QUALITY",true)){
//         return EUPGRATEQUALITY_EEQUIPRESUlT_FAIL;
//     }
//     // 计算当前等级的属性值和
//     // 属性值
//     SBattleAttribute a1;
//     SBattleAttribute a2;
//     SBattleAttribute a3;
//     EQualityID q2= roleEquip->getQuality();
//     EQualityID q1= (EQualityID)((BSLib::uint32)q2-1);
//     EQualityID q3= (EQualityID)((BSLib::uint32)q2+1);
//     // 属性价值
//     float f1 = 0;//装备熔炼属性价值
//     float f2 = 0;//装备熔炼属性价值
//     float f3 = 0;//装备熔炼属性价值
// 
//     if(q1 != QUALITY_INVALID){
//         CEquipConfigGMMgr::singleton().getEquipBaseAttr(roleEquip->getTPID(),roleEquip->getLevel(),q1,a1);
//         f1 = CEquipConfigGMMgr::singleton().getCurQualityAddAttrValue(a1);
//     }
//     a2 = roleEquip->getBattleAttr();
//     f2 = CEquipConfigGMMgr::singleton().getCurQualityAddAttrValue(a2);
//     CEquipConfigGMMgr::singleton().getEquipBaseAttr(roleEquip->getTPID(),roleEquip->getLevel(),q3,a3);
//     f3 = CEquipConfigGMMgr::singleton().getCurQualityAddAttrValue(a3);
// 
//     BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "装备熔炼品级[q1=%d][q2=%d][q3=%d]",q1,q2,q3);
//     BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "装备熔炼属性价值[f1=%f][f2=%f][f3=%f]",f1,f2,f3);
//     BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "装备熔炼属性值[a1=%s][a2=%s][a3=%s]",a1.toLogString().c_str(),a2.toLogString().c_str(),a3.toLogString().c_str());
// 
//     BSLib::uint32 s1 = CEquipConfigGMMgr::singleton().getQualityValue(proValue,q1);
//     BSLib::uint32 s2 = CEquipConfigGMMgr::singleton().getQualityValue(proValue,q2);
//     BSLib::uint32 s3 = CEquipConfigGMMgr::singleton().getQualityValue(proValue,q3);
//     BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "装备熔炼[道具价值proValue=%d][s1=%d][s2=%d][s3=%d]",proValue,s1,s2,s3);
// 
//     BSLib::uint32 p1 = (BSLib::uint32)s1*100;
//     BSLib::uint32 p2 = p1+(BSLib::uint32)s2*100;
//     BSLib::uint32 p3 = p2+(BSLib::uint32)s3*100;
//     BSLib::uint32 Q = BSLib::Utility::CRandom::randomBetween(1,p3);
//     BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "装备熔炼[p1=%d][p2=%d][p3=%d]",p1,p2,p3);
//     a_qualityResult.m_equipID = a_equipID;
//     if(Q <= p1){
//         a_qualityResult.m_quality = q1;
//         a_qualityResult.m_battleAttr = a1;
//         BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "装备熔炼降级[m_equipID=%d][m_quality=%d][attr=%s]",a_equipID,a_qualityResult.m_quality,a_qualityResult.m_battleAttr.toLogString().c_str());
//     }
//     else if(Q <= p2){
//         a_qualityResult.m_quality = roleEquip->getQuality();
//         a_qualityResult.m_battleAttr = roleEquip->getBattleAttr();
//         BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "装备熔炼品级不变[m_equipID=%d][m_quality=%d][attr=%s]",a_equipID,a_qualityResult.m_quality,a_qualityResult.m_battleAttr.toLogString().c_str());
//     }
//     else if(Q <= p3){
//         a_qualityResult.m_quality = q3;
//         a_qualityResult.m_battleAttr = a3;
//          BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "装备熔炼升级[m_equipID=%d][m_quality=%d][attr=%s]",a_equipID,a_qualityResult.m_quality,a_qualityResult.m_battleAttr.toLogString().c_str());
//     }
//     else{// impossible
//         a_qualityResult.m_quality = roleEquip->getQuality();
//         a_qualityResult.m_battleAttr = roleEquip->getBattleAttr();
//         BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "熔炼品级不变[m_equipID=%d][m_quality=%d][attr=%s]",a_equipID,a_qualityResult.m_quality,a_qualityResult.m_battleAttr.toLogString().c_str());
//     }
//     a_qualityResult.m_save = true;
//     return EUPGRATEQUALITY_EEQUIPRESUlT_SUCCESS;
// }

EResetAttrResult CRoleEquipModule::_exchangeAttr(EquipID a_equipID, EquipID a_itemEquipID)
{
	// 获取装备
	CRoleEquipGM *equip = _getEquip(a_equipID);
	if (NULL == equip){
		BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr[ERESETATTR_RESULT_EQUIP_NOT_EXIST][洗练获取装备失败][a_equipID=%d]",getRoleInfor().c_str(),a_equipID);
		return ERESETATTR_RESULT_EQUIP_NOT_EXIST;
	}

	CRoleEquipGM *itemEquip = _getEquip(a_itemEquipID);
	if (NULL == itemEquip){
		BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr[ERESETATTR_RESULT_EQUIP_NOT_EXIST][洗练获取材料装备失败][a_equipID=%d]",getRoleInfor().c_str(),a_itemEquipID);
		return ERESETATTR_RESULT_EQUIP_NOT_EXIST;
	}

	if(equip->getQuality() < QUALITY_BLUE || itemEquip->getQuality() < QUALITY_BLUE)
	{
		return ERESETATTR_RESULT_FAIL;
	}

	if(equip->getType() != itemEquip->getType())
	{
		return ERESETATTR_RESULT_FAIL;
	}
	
	GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
	if(role == NULL){
		BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[GETROLE_ERROR][获取角色模块失败]");
		return ERESETATTR_RESULT_FAIL;
	}
	float fLevel = equip->getLevel();
	float fneedGold = 33.0 * pow(fLevel, 2) - 68.0 * fLevel + 4035.0 + 0.5;
	BSLib::uint64 needGold = fneedGold;
	BSLib::uint64 curGold = role->getGold();
	if(curGold < needGold){
		BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr[ERESETATTR_RESULT_GOLD_LIMIT][m_equipID=%d][curGold=%lld][needGold=%lld]",getRoleInfor().c_str(),equip->getEquipID(),curGold,needGold);
		return ERESETATTR_RESULT_GOLD_LIMIT;
	}
	BSLib::int64 gold = 0 - (BSLib::int64)needGold;
	if(!role->modifyGold(gold,"EQUIP_RESET",true)){
		return ERESETATTR_RESULT_FAIL;
	}
	

	CAttachAttr itemAttr;
	itemEquip->getAttachAttr(itemAttr);
	CAttachAttr attachAttr;
	equip->getAttachAttr(attachAttr);

	equip->setAttachAttr(itemAttr);
	itemEquip->setAttachAttr(attachAttr);

	equip->updateEquipBattleAttr();
	itemEquip->updateEquipBattleAttr();
	updateDataToDB(a_equipID);
	updateDataToDB(a_itemEquipID);
	_updateEquipTotalBattleAttr(true);

	return ERESETATTR_RESULT_SUCCESS;
}

EResetAttrResult CRoleEquipModule::_resetAttr(EquipID a_equipID,EResetEquipType a_resetEquipType,
											  const std::vector<BSLib::uint32>& a_lockAttrIndexArray, EquipID a_itemEquipID)
{
    // 获取装备
    CRoleEquipGM *equip = _getEquip(a_equipID);
    if (NULL == equip){
       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr[ERESETATTR_RESULT_EQUIP_NOT_EXIST][洗练获取装备失败][a_equipID=%d]",getRoleInfor().c_str(),a_equipID);
        return ERESETATTR_RESULT_EQUIP_NOT_EXIST;
    }

	CRoleEquipGM *itemEquip = _getEquip(a_itemEquipID);
	if (NULL == itemEquip){
		BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr[ERESETATTR_RESULT_EQUIP_NOT_EXIST][洗练获取材料装备失败][a_equipID=%d]",getRoleInfor().c_str(),a_itemEquipID);
		return ERESETATTR_RESULT_EQUIP_NOT_EXIST;
	}


    // 锁定规则
    CAttachAttr attachAttr;
    equip->getAttachAttr(attachAttr);
    BSLib::uint32 attachAttrCount = attachAttr.getAttrCount();
	if( 1 != a_lockAttrIndexArray.size()){
		return ERESETATTR_RESULT_LOCK_COUNT_LIMIT;
	}
	
	bool needNewSlot = false; //需要新插口
	if( attachAttrCount == 6)
	{
		if( a_lockAttrIndexArray[0] > 5)
		{
			return ERESETATTR_RESULT_LOCK_COUNT_LIMIT;
		}
	}
	else if(attachAttrCount < 6)
	{
		if( a_lockAttrIndexArray[0] > attachAttrCount)
		{
			return ERESETATTR_RESULT_LOCK_COUNT_LIMIT;
		}
		else if(a_lockAttrIndexArray[0] == attachAttrCount)
		{	
			needNewSlot = true;
		}
	}

	if(itemEquip->getQuality() < QUALITY_BLUE)
	{
		return ERESETATTR_RESULT_FAIL;
	}

	if(equip->getType() != itemEquip->getType())
	{
		return ERESETATTR_RESULT_FAIL;
	}

	if(itemEquip->getEquipStatus() == EQUIP_STATUS_ON)
	{
		return ERESETATTR_RESULT_FAIL;
	}

	CAttachAttr itemAttr;
	itemEquip->getAttachAttr(itemAttr);
	if(0 == itemAttr.getAttrCount())
	{
		return ERESETATTR_RESULT_FAIL;
	}	

    GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if(role == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[GETROLE_ERROR][获取角色模块失败]");
        return ERESETATTR_RESULT_FAIL;
    }
	
	float fLevel = equip->getLevel();
	float fneedGold = 5.5 * pow(fLevel, 2) - 12.0 * fLevel + 707.0 + 0.5;
    BSLib::uint64 needGold = fneedGold;
    BSLib::uint64 curGold = role->getGold();
    if(curGold < needGold){
       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr[ERESETATTR_RESULT_GOLD_LIMIT][m_equipID=%d][curGold=%lld][needGold=%lld]",getRoleInfor().c_str(),equip->getEquipID(),curGold,needGold);
        return ERESETATTR_RESULT_GOLD_LIMIT;
    }
    BSLib::int64 gold = 0 - (BSLib::int64)needGold;
    if(!role->modifyGold(gold,"EQUIP_RESET",true)){
        return ERESETATTR_RESULT_FAIL;
    }


	BSLib::uint32 sum = 0;
	std::vector<BSLib::uint32> rateArray;
	for(BSLib::uint32 i = 0; i < itemAttr.getAttrCount(); i++)
	{	
		CAttribute tempAtt;
		itemAttr.getAttr(i, tempAtt);
		BSLib::uint32 tempRate = CEquipConfigGMMgr::singleton().getResetRate(tempAtt.getQuality());
		rateArray.insert(rateArray.end(), tempRate, i);
		sum += tempRate;
	}
	if( 0 == sum)
	{
		return ERESETATTR_RESULT_FAIL;
	}

	BSLib::uint32 randNum = BSLib::Utility::CRandom::randomBetween(0, sum - 1);
	BSLib::uint32 selected = rateArray[randNum];
	CAttribute selectedAtt;
	itemAttr.getAttr(selected, selectedAtt);

	// 交换属性
	equip->m_oldAttach = attachAttr;
	selectedAtt.setAttrIndex(a_lockAttrIndexArray[0]);
	if(needNewSlot)
	{
		attachAttr.m_attrArray.push_back(selectedAtt);
	}
	else
	{
		attachAttr.setAttr(a_lockAttrIndexArray[0], selectedAtt);
	}
	equip->setAttachAttr(attachAttr);
	equip->m_canUndo = true;	

	// 装备状态
	EEquipStatus status = equip->getEquipStatus();
	if(status == EQUIP_STATUS_OFF){
		SItemInstanceID instanceID;
		instanceID.setInstanceID(equip->getEquipID());
		instanceID.setItemTPID(equip->getTPID());
		BagIndex itemIndex = 0;
		GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = _getBag();
		if(bag != NULL)
		{
			if(bag->getIndexByItemInstanceID(instanceID,itemIndex)){
				if(!bag->removeItemByIndex(itemIndex,"洗练销毁装备",true)){
					return ERESETATTR_RESULT_FAIL;
				}
			}
		}
	}
	removeEquip(a_itemEquipID);


//     GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
//     if(role == NULL){
//         BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[GETROLE_ERROR][获取角色模块失败]");
//         return ERESETATTR_RESULT_FAIL;
//     }
// 
//     BSLib::uint32 equipLevel = equip->getLevel();
    
//     // 条件1：金币足够
//     if(a_resetEquipType == ERESET_EQUIP_TYPE_NORMAL){
//         BSLib::uint64 needGold = _getResetAttrNeedGold(lockAttrIndexCount,equipLevel);
//         BSLib::uint64 curGold = role->getGold();
//         if(curGold < needGold){
//            BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr[ERESETATTR_RESULT_GOLD_LIMIT][m_equipID=%d][curGold=%lld][needGold=%lld]",getRoleInfor().c_str(),equip->getEquipID(),curGold,needGold);
//             return ERESETATTR_RESULT_GOLD_LIMIT;
//         }
//         BSLib::int64 gold = 0 - (BSLib::int64)needGold;
//         if(!role->modifyGold(gold,"EQUIP_RESET",true)){
//             return ERESETATTR_RESULT_FAIL;
//         }
//     }
//     else  if(a_resetEquipType == ERESET_EQUIP_TYPE_HIGH){
//         BSLib::uint32 needDiamond = _getResetAttrNeedDiamond(lockAttrIndexCount,equipLevel);
//         BSLib::uint32 curDiamond = role->getTotalDiamond();
//         if(curDiamond < needDiamond){
//            BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr[ERESETATTR_RESULT_DIAMOND_LIMIT][m_equipID=%d][curDiamond=%d][needDiamond=%d]",getRoleInfor().c_str(),equip->getEquipID(),curDiamond,needDiamond);
//             return ERESETATTR_RESULT_DIAMOND_LIMIT;
//         }
//         BSLib::uint32 diamond = needDiamond;
//         if(!role->delDiamond(diamond,"EQUIP_RESET",true)){
//            BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr[ERESETATTR_RESULT_FAIL][m_equipID=%d][curDiamond=%d][needDiamond=%d]",getRoleInfor().c_str(),equip->getEquipID(),curDiamond,needDiamond);
//             return ERESETATTR_RESULT_FAIL;
//         }
//     }
//     else{
//       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr[ERESETATTR_RESULT_FAIL][m_equipID=%d]",getRoleInfor().c_str(),equip->getEquipID());
//        return ERESETATTR_RESULT_FAIL;
//     }
   
//     CAttachAttr newAttachAttr;
//     std::vector<BSLib::uint32>::const_iterator it = a_lockAttrIndexArray.begin();
//     for(;it != a_lockAttrIndexArray.end(); ++it){
//         BSLib::uint32 index = *it;
//         CAttribute attr;
//         attachAttr.getAttr(index,attr);
//         newAttachAttr.m_attrArray.push_back(attr);
//     }
// 
//     float S = equip->getResetSum();
//     CEquipConfigGMMgr::singleton().randNewEquipAttachAttr(equip->getQuality(),equip->getLevel(),S,a_lockAttrIndexArray,newAttachAttr);
// 
//    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr[ERESETATTR_RESULT_SUCCESS][装备洗练后的附加属性][m_equipID=%d][%s]",getRoleInfor().c_str(),equip->getEquipID(),newAttachAttr.toLogString().c_str());
//     // 保存修改
//     equip->setAttachAttr(newAttachAttr);


    equip->updateEquipBattleAttr();
    updateDataToDB(a_equipID);
    _updateEquipTotalBattleAttr(true);

    return ERESETATTR_RESULT_SUCCESS;
}

EGemCombineResult CRoleEquipModule::_combineGems(EGemsCombineType type,BSLib::uint32 a_gemTPID,BSLib::uint32& a_newGemTPID)
{
   if(!ItemSystem::GM::CItemGMMgr::singleton().getCombineGemTPID(a_gemTPID,a_newGemTPID)){
      BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sCombineGems[EGEM_COMBINE_RESULT_INVALID_GEMTPID][a_gemTPID=%d][a_newGemTPID=%d]",getRoleInfor().c_str(),a_gemTPID,a_newGemTPID);
        return EGEM_COMBINE_RESULT_INVALID_GEMTPID;
   }

   GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = _getBag();
    if(bag == NULL){
        return EGEM_COMBINE_RESULT_FAIL;
    }
    const BSLib::uint32 gemCount = bag->getItemCount(a_gemTPID);
    BSLib::uint32 needCount = 3;
    BSLib::uint32 newGemCount = 1;
    if (needCount > gemCount){
      BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sCombineGems[needCount=%d][newGemCount=%d][a_newGemTPID=%d]",getRoleInfor().c_str(),needCount,newGemCount,a_newGemTPID);
       return EGEM_COMBINE_RESULT_METARIAL_LIMIT;
    }
    if(type == EGEMS_COMBINE_TYPE_ALL){
        newGemCount = gemCount / needCount;
        needCount = newGemCount * needCount;
    }
    
 
    //bag->addItem(item,true,true,"GEMS_COMBINE");
    GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if(role == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "获取角色模块失败]");
        return EGEM_COMBINE_RESULT_FAIL;
    }
    PrizeSystem::GM::CRolePrizeModule *prizeModue = (PrizeSystem::GM::CRolePrizeModule *)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
    if (prizeModue == NULL) {
        return EGEM_COMBINE_RESULT_FAIL;
    }
    bag->removeItemCount(a_gemTPID,ItemSystem::GM::EITEM_TP_GEMS,needCount,"GEMS_COMBINE",true);
    std::vector<ItemSystem::GM::CPrizeItem> itemArray;
    ItemSystem::GM::CPrizeItem item;
    item.m_itemCount = newGemCount;
    item.m_itemTPID = a_newGemTPID;
    item.m_itemType = ItemSystem::GM::EITEM_TP_GEMS;
    itemArray.push_back(item);
    std::string sender = toMailString("系统信息");
    std::string title = toMailString("宝石合成");
    std::string content = toMailString("由于背包已满，合成后的宝石以邮件发送，宝石如下：");
    prizeModue->prizeRequest(itemArray,sender,title,content,"GEMS_COMBINE");
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sCombineGems宝石合并[needCount=%d][newGemCount=%d][a_newGemTPID=%d]",getRoleInfor().c_str(),needCount,newGemCount,a_newGemTPID);
    return EGEM_COMBINE_RESULT_SUCCESS;
}

EGemUpdateStatusResult CRoleEquipModule::_addGemsToEquip(EquipID a_equipID,ItemTPID a_gemTPID,EGemSlot a_index)
{
    CRoleEquipGM* equip = _getEquip(a_equipID);
    if(equip == NULL){
       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sAddGemsToEquip[EGEM_UPDATESTATUS_RESULT_EQUIP_NOT_EXIST][a_equipID == %d]",getRoleInfor().c_str(),a_equipID);
        return EGEM_UPDATESTATUS_RESULT_EQUIP_NOT_EXIST;
    }
    BSLib::uint32 slotCount = (BSLib::uint32)a_index + 1;
    BSLib::uint32 posCount = equip->getSlotCount();
    if(slotCount > posCount){
       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sAddGemsToEquip[EGEM_UPDATESTATUS_RESULT_EQUIP_NOT_EXIST][index=%d]",getRoleInfor().c_str(),a_index);
        return EGEM_UPDATESTATUS_RESULT_INVALID_SLOT_INDEX;
    }

    const BSLib::uint32 gemTPID = equip->getGemTPID(a_index);
    if(gemTPID != 0){
       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sAddGemsToEquip[EGEM_UPDATESTATUS_RESULT_GEM_EXIST][index=%d][gemTPID=%d]",getRoleInfor().c_str(),a_index,gemTPID);
        return EGEM_UPDATESTATUS_RESULT_GEM_EXIST;
    }

    GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = _getBag();
    if(bag == NULL){
        return EGEM_UPDATESTATUS_RESULT_FAIL;
    }
    BSLib::uint32 gemCount = bag->getItemCount(a_gemTPID);
    const BSLib::uint32 needCount = 1;
    if (needCount > gemCount){
       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sAddGemsToEquip[EGEM_UPDATESTATUS_RESULT_NOT_ENOUGH_GEM][needCount=%d][gemCount=%d]",getRoleInfor().c_str(),needCount,gemCount);
        return EGEM_UPDATESTATUS_RESULT_NOT_ENOUGH_GEM;
    }

    bag->removeItemCount(a_gemTPID,ItemSystem::GM::EITEM_TP_GEMS,needCount,"ADD_EEQUIP_GEMS",true);
    equip->setGemTPID(a_index,a_gemTPID);
    equip->updateEquipBattleAttr();
    updateDataToDB(a_equipID);
    _updateEquipTotalBattleAttr(true);
    return EGEM_UPDATESTATUS_RESULT_SUCCESS;
}


EGemUpdateStatusResult CRoleEquipModule::_removeGemFromEquip(EquipID a_equipID,ItemTPID a_gemTPID,EGemSlot a_index)
{
    CRoleEquipGM* equip = _getEquip(a_equipID);
    if(equip == NULL){
       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sRemoveGemFromEquip[EGEM_UPDATESTATUS_RESULT_EQUIP_NOT_EXIST][a_equipID=%d]",getRoleInfor().c_str(),a_equipID);
        return EGEM_UPDATESTATUS_RESULT_EQUIP_NOT_EXIST;
    }
    BSLib::uint32 posCount = equip->getSlotCount();
    BSLib::uint32 slotCount = (BSLib::uint32)a_index + 1;
    if(slotCount > posCount){
       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sRemoveGemFromEquip[EGEM_UPDATESTATUS_RESULT_INVALID_SLOT_INDEX][slotCount=%d][posCount=%d]",getRoleInfor().c_str(),slotCount,posCount);
        return EGEM_UPDATESTATUS_RESULT_INVALID_SLOT_INDEX;
    }
    BSLib::uint32 itemTPID = equip->getGemTPID(a_index);
    if(itemTPID == 0){
       BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sRemoveGemFromEquip[EGEM_UPDATESTATUS_RESULT_GEM_NOT_INSLOT][itemTPID=%d]",getRoleInfor().c_str(),itemTPID);
        return EGEM_UPDATESTATUS_RESULT_GEM_NOT_INSLOT;
    }

    GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = _getBag();
    if(bag == NULL){
        return EGEM_UPDATESTATUS_RESULT_FAIL;
    }
  
    GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if(role == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "获取角色模块失败]");
        return EGEM_UPDATESTATUS_RESULT_FAIL;
    }
    if(bag->isBagFull()){
        return EGEM_UPDATESTATUS_RESULT_BAGFULL;
    }
    
    ItemSystem::GM::CPrizeItem item;
    item.m_itemCount = 1;
    item.m_itemTPID = itemTPID;
    item.m_itemType = ItemSystem::GM::EITEM_TP_GEMS;
    if(PlayerSystem::GM::EADDITEM_SUCCESS != bag->addItem(item,false,true,"REMOVE_EQUIP_GEM")){
        return EGEM_UPDATESTATUS_RESULT_FAIL;
    }
    equip->setGemTPID(a_index,0);
    equip->updateEquipBattleAttr();
    updateDataToDB(a_equipID);
    _updateEquipTotalBattleAttr(true);
    return EGEM_UPDATESTATUS_RESULT_SUCCESS;
}

void CRoleEquipModule::_updateDailyTask(GSLib::TaskSystem::GM::EDailyTaskType a_dailyTaskType)
{
    GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if(role == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[获取角色模块失败]");
        return;
    }
	GSLib::TaskSystem::GM::CRoleTaskModule *taskModule = (GSLib::TaskSystem::GM::CRoleTaskModule *)role->getPlayerModuleGM(EMODULECTYPE_TASK);
	if (taskModule != NULL) {
		taskModule->updateDailyTask(a_dailyTaskType);
	}
}

bool CRoleEquipModule::loadGameConfig(const std::string& a_configPath)
{
	return true;
}

CRoleEquipGM* CRoleEquipModule::_getEquip(EquipID a_equipID) const
{
    CRoleEquipGM* equip = NULL;
    BSLib::Utility::CHashMap<EquipID, CRoleEquipGM*>::const_iterator it = m_equipHashMap.find(a_equipID);
    if( it != m_equipHashMap.end())
    {
        equip = it->second;
    }
    return equip;
}

bool CRoleEquipModule::_getOperationCondition(EquipID a_equipID,EEquipOperation a_operation ,CConditionData& a_conditionData) const
{
    CRoleEquipGM* equip = _getEquip(a_equipID);
    if(equip == NULL){
        return false;
    }
    switch(a_operation){
        case EQUIP_UPGRADE_LEVEL:
            {
               return equip->getUpgradeCondition(a_conditionData);
            }
        case EQUIP_RESET_ATTR:
            {
                return false;
            }

		case EQUIP_UPGRADE_NENGLIANGQIU:
			{
				return equip->getUpgradeNengLiangQiuCond(a_conditionData);
			}
        default:
            {
                return false;
            } 
    }
}

GSLib::PlayerSystem::GM::CRoleBagModuleGM * CRoleEquipModule::_getBag()
{
    GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if(role == NULL){
        return NULL;
    }
    return role->getRoleBag();
}

void CRoleEquipModule::_setEquipStatus(CRoleEquipGM* a_equip,EEquipStatus a_status)
{   
    if(a_equip == NULL){
        return;
    }
    EEquipStatus curStatus = a_equip->getEquipStatus();
    // 脱装
    if(a_status == EQUIP_STATUS_OFF){
        if (curStatus == EQUIP_STATUS_ON){
            EEquipType type = a_equip->getType();
            _setRoleEquip(type,0);
            a_equip->setEquipStatus(a_status);
        }
    }
    // 穿装
    else if(a_status == EQUIP_STATUS_ON){
        // 穿装之前先自动卸下当前装备
        if (curStatus == EQUIP_STATUS_OFF){
            EEquipType type = a_equip->getType();
           _setRoleEquip(type,a_equip->getEquipID());
            a_equip->setEquipStatus(a_status);
        }
    }
}

EquipID CRoleEquipModule::_getEquipID(EEquipType a_equipType)
{   // 脱装
    EEquipType type = a_equipType;
    if((type <=EQUIP_INVALID) || (type >=EQUIP_NUMBER)){
        return 0;
    }
    BSLib::uint32 equipIndex = (BSLib::uint32)type - 1;
    return m_roleEquipID[equipIndex];
}

ItemTPID CRoleEquipModule::getFashionTPID()
{
	EquipID id = _getEquipID(EQUIP_FASHION);
	if( 0 == id)
		return 0;

	CRoleEquipGM* equip = _getEquip(id);
	if(NULL == equip)
		return 0;

	return equip->getTPID();
}

void CRoleEquipModule::_setRoleEquip(EEquipType a_equipType,EquipID a_equipID)
{   
     EEquipType type = a_equipType;
     if((type <=EQUIP_INVALID) || (type >=EQUIP_NUMBER)){
        return;
     }
     BSLib::uint32 equipIndex = (BSLib::uint32)type - 1;
     m_roleEquipID[equipIndex] = a_equipID;
}

EChangeStatusResult CRoleEquipModule::_equipOff(EquipID a_equipID,BSLib::uint32& a_index)
{
    GSLib::PlayerSystem::GM::CRoleGM* curRole = getRoleGM();
    if (curRole == NULL) {
        return ECHANGESTATUS_RESULT_FAIL;
    }

    GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = curRole->getRoleBag();
    if(bag == NULL){
        return ECHANGESTATUS_RESULT_FAIL;
    }

    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[脱下装备][m_equipID=%d]",a_equipID);
    CRoleEquipGM* equip = _getEquip(a_equipID);
    if(equip == NULL){
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[脱下装备失败,装备不存在][m_equipID=%d]",a_equipID);
        return ECHANGESTATUS_RESULT_FAIL;
    }
    if(equip->getEquipStatus() == EQUIP_STATUS_OFF){
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[脱下装备失败,装备已脱下][m_equipID=%d]",a_equipID);
        return ECHANGESTATUS_RESULT_STATUS_ERROR;
    }
    if(bag->isBagFull()){
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[脱下装备失败,背包已满][m_equipID=%d]",a_equipID);
        return ECHANGESTATUS_RESULT_STATUS_BAGFULL;
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[脱下装备,修改装备状态][m_equipID=%d]",a_equipID);
    _setEquipStatus(equip,EQUIP_STATUS_OFF);
    SItemInstanceID itemInstanceID(equip->getTPID(),equip->getEquipID());
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[脱下装备,放入背包][m_equipID=%d][index=%d]",a_equipID,a_index);
    bag->addEquip(itemInstanceID,false,true,a_index);
    
    return ECHANGESTATUS_RESULT_SUCCESS;
}

BSLib::uint32 CRoleEquipModule::_getResetAttrNeedGold(BSLib::uint32 a_lockCount,BSLib::uint32 a_equipLevel)
{
    BSLib::uint32 gold = 0;
    float lv = (float)a_equipLevel;
    float base = (float)(CEquipConfigGMMgr::singleton().getRound(lv/25) * 5 +5.0f)/3;
    BSLib::uint32 a = CEquipConfigGMMgr::singleton().getRound(base)*100;
    // 锁定部分
    float attach = a_lockCount * 0.5f + 1.0f;
    BSLib::uint32 b = CEquipConfigGMMgr::singleton().getRound(attach);
    gold = b*a; 
    return gold;
}

BSLib::uint32 CRoleEquipModule::_getResetAttrNeedDiamond(BSLib::uint32 a_lockCount,BSLib::uint32 a_equipLevel)
{
    BSLib::uint32 diamond = 0;
    float lv = (float)a_equipLevel;
    BSLib::uint32 a = CEquipConfigGMMgr::singleton().getRound(lv/25) * 5 + 5;
    // 锁定部分
    float attach = a_lockCount * 0.5f + 1.0f;
    BSLib::uint32 b = CEquipConfigGMMgr::singleton().getRound(attach);
    diamond = b*a; 
    return diamond;
}

bool CRoleEquipModule::_getItemDataArray(const std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray,BSLib::Utility::CStream& a_stream) const
{
    BSLib::uint32 count = a_itemArray.size();
    a_stream << count;
    for(BSLib::uint32 i = 0; i < count; i++) {
        ItemSystem::GM::CPrizeItem item = a_itemArray[i];
        item.serializeTo(a_stream);
    }
    return true;
}

bool CRoleEquipModule::_combineItems(const std::vector<ItemSystem::GM::CPrizeItem>& a_srcItemArray, std::vector<ItemSystem::GM::CPrizeItem>& a_desItemArray) const
{
    std::map<ItemTPID, BSLib::uint32> bonusMap;
    for(BSLib::uint32 i = 0; i < a_srcItemArray.size(); i++) {
        std::map<ItemTPID, BSLib::uint32>::iterator it = bonusMap.find(a_srcItemArray[i].m_itemTPID);
        if( it != bonusMap.end()) {
            it->second = it->second + a_srcItemArray[i].m_itemCount;
        }
        else {
            bonusMap.insert( std::make_pair(a_srcItemArray[i].m_itemTPID, a_srcItemArray[i].m_itemCount));
        }
    }
    std::map<BSLib::uint32, BSLib::uint32>::iterator it = bonusMap.begin();
    a_desItemArray.clear();
    for( ; it != bonusMap.end(); ++it) {
        ItemSystem::GM::CPrizeItem item;
        item.m_itemTPID = it->first;
        item.m_itemCount = it->second;
        item.m_itemType = ItemSystem::GM::CItemGMMgr::singleton().getType(item.m_itemTPID);
        a_desItemArray.push_back(item);
    }
    bonusMap.clear();

    return true;
}

void CRoleEquipModule::_updateBagEquip(EquipID a_equipID)
{
    CRoleEquipGM* equip = _getEquip(a_equipID);
    if(equip == NULL){
        return;
    }

    if(equip->isStatusOn()){
        return;
    }

    GSLib::PlayerSystem::GM::CRoleGM* curRole = getRoleGM();
    if (curRole == NULL) {
        return ;
    }

    GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = curRole->getRoleBag();
    if(bag == NULL){
        return ;
    }

    SItemInstanceID instanceID;
    instanceID.setInstanceID(equip->getEquipID());
    instanceID.setItemTPID(equip->getTPID());
    BagIndex itemIndex = 0;
    if(!bag->getIndexByItemInstanceID(instanceID,itemIndex)){
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%s[获取装备背包中位置失败][m_equipID=%d]",getRoleInfor().c_str(),a_equipID);
        return;
    }

    bag->notifyBagItemCount(itemIndex,true,false);
}

void CRoleEquipModule::_outputGameLog(const std::string& a_gameLable, const char* a_format, ...)
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

std::string CRoleEquipModule::getRoleInfor() const
{
    GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
    if (roleGM == NULL) {
        return "";
    }
    return roleGM->getRoleLogString();
}

void CRoleEquipModule::_checkExpiredEquip()
{	
	std::vector<EquipID> todel;
	CRoleEquipGM* equip = NULL;
	BSLib::Utility::CHashMap<EquipID, CRoleEquipGM*>::iterator it = m_equipHashMap.begin();
	for(; it != m_equipHashMap.end(); ++it)
	{
		equip = it->second;
		if( EQUIP_FASHION_TYPE != equip->getType())
			continue;
		
		BSLib::uint64  now = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
		if(now >= equip->m_equipColorGemsCount[0])
			todel.push_back(it->first);
	}

	for(std::vector<EquipID>::iterator it = todel.begin(); it != todel.end(); ++it)
	{
		CRoleEquipGM *equip = _getEquip(*it);
		// 装备状态
		EEquipStatus status = equip->getEquipStatus();
		if(status == EQUIP_STATUS_OFF){
			SItemInstanceID instanceID;
			instanceID.setInstanceID(equip->getEquipID());
			instanceID.setItemTPID(equip->getTPID());
			BagIndex itemIndex = 0;
			GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = _getBag();
			if(bag != NULL)
			{
				if(bag->getIndexByItemInstanceID(instanceID,itemIndex)){
					if(!bag->removeItemByIndex(itemIndex,"洗练销毁装备",true)){
						continue;
					}
				}
			}
		}

		removeEquip(*it);
	}
	
}

}//GM

}//EquipSystem

}//GSLib

