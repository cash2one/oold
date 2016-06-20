 //////////////////////////////////////////////////////////////////////
//	created:	2014/08/29
//	filename: 	src\GSLib\playerSystem\GM\roleBagModule.cpp
//	author:	    zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/playerSystem/GM/playerSystemGM.h>
#include <GSLib/playerSystem/GM/roleBagGMMgr.h>
#include <GSLib/playerSystem/msgPlayerSystem.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/itemSystem/GM/itemGMMgr.h>
#include "roleConfigGMMgr.h"
#include <GSLib/equipSystem/GM/roleEquipModule.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace GM
{
using namespace GSLib::ItemSystem::GM;

CRoleBagGMMgr::CRoleBagGMMgr()
: m_usedPosCount(0)
,m_showCount(0)
{
   m_IndexArray.resize(999,SItemInstanceID(0,0));
   m_bagItemMap.clear();
}

CRoleBagGMMgr::~CRoleBagGMMgr()
{
    m_IndexArray.clear();
    m_bagItemMap.clear();
}

bool CRoleBagGMMgr::initBagFromDB(const BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>* a_tables,GSLib::PlayerSystem::GM::CRoleGM* a_role)
{
    if(a_tables == NULL){
        return false;
    }

    m_usedPosCount = a_tables->size();
    if(m_usedPosCount > m_IndexArray.size()){
        BSLib::uint32 addSize = m_usedPosCount - m_IndexArray.size();
        addPosCount(addSize);
    }

    EquipSystem::GM::CRoleEquipModule* equipModule = (EquipSystem::GM::CRoleEquipModule*)a_role->getPlayerModuleGM(EMODULECTYPE_EQUIP);
    BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::const_iterator it = a_tables->begin();
    for (; it != a_tables->end(); ++it) {
        BSLib::Database::CDBTableRow* row = it->second;
        if (row == NULL) {
            continue;
        }
        DB::SRoleBagItemData item;
        if (!row->serializeTo(&item, sizeof(item))) {
            continue;
        }
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[BAGDATA][initBagFromDB][TPID=%d][Type=%d][Count=%d][Position=%d]",
            item.m_itemTPID,item.m_itemType,item.m_itemCount,item.m_index);
        SItemInstanceID itemEntityID(item.m_itemTPID,item.m_instanceID);
        
        if(equipModule != NULL){
            if(CItemGMMgr::singleton().getMainType(item.m_itemTPID) == EMAIN_TP_EQUIP){
                BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[数据校验][a_itemTPID=%d][m_instanceID=%d][m_itemCount=%d]",item.m_itemTPID,item.m_instanceID,item.m_itemCount);
                EquipID equipID = (EquipID)item.m_instanceID;
                BSLib::Utility::CStream tempStream;
                tempStream.reset();
                if(!equipModule->getEquipDataForBag(equipID,item.m_itemTPID,tempStream)){
                    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[丢弃背包中无效实例装备][a_itemTPID=%d][m_instanceID=%d][m_itemCount=%d]",item.m_itemTPID,item.m_instanceID,item.m_itemCount);
                    continue;
                }
                if (equipModule->isEquipStatusOn(equipID)){
                    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[丢弃背包中状态无效实例装备][a_itemTPID=%d][m_instanceID=%d][m_itemCount=%d]",item.m_itemTPID,item.m_instanceID,item.m_itemCount);
                    continue;
                }

                BagIndex itemIndex = 0;
                if(getIndexByInstanceID(item.m_instanceID,itemIndex)){
                    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[丢弃背包中重复实例装备][a_itemTPID=%d][m_instanceID=%d][m_itemCount=%d]",item.m_itemTPID,item.m_instanceID,item.m_itemCount);
                    continue;
                }
            }
        }
        addItemByIndex(item.m_index,itemEntityID,(EItemType)item.m_itemType,item.m_itemCount);
    }
    _updateBagItemCount();

    return true;
}

void CRoleBagGMMgr::final()
{
    std::map<SItemInstanceID,CItemTPIDList*>::iterator it = m_bagItemMap.begin();
    for(;it != m_bagItemMap.end();++it){
        CItemTPIDList* item = it->second;
        if(item == NULL){
            continue;
        }
        item->final();
        BSLIB_SAFE_DELETE(item); 
    }
    m_bagItemMap.clear();
}

void CRoleBagGMMgr::serializeToClient(BSLib::uint32& a_totalitemCount,BSLib::Utility::CStream& stream) const
{
    stream.reset();
    BSLib::uint32 curCount = 0;
    std::map<SItemInstanceID,CItemTPIDList*>::const_iterator it = m_bagItemMap.begin();
    for (; it != m_bagItemMap.end(); ++it) {
        CItemTPIDList* item = it->second;
        if (item == NULL) {
            continue;
        }
		
		if( EITEM_TP_EQUIP_NENGLIANGQIU == item->m_type)
		{
			continue;
		}

        BSLib::uint32 count = 0;
        item->serializeTo(count,stream);
        curCount += count;
    }
    a_totalitemCount = curCount;
}

bool CRoleBagGMMgr::serializeNengLiangQiuToClient(GSLib::PlayerSystem::GM::CRoleGM* a_role,BSLib::uint32& a_itemCount,BSLib::Utility::CStream& stream)
{
	if(a_role == NULL){
		return true;
	}

	EquipSystem::GM::CRoleEquipModule* equipModule = (EquipSystem::GM::CRoleEquipModule*)a_role->getPlayerModuleGM(EMODULECTYPE_EQUIP);
	if(equipModule == NULL){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[获取装备模块失败]");
		return false;
	}

	stream.reset();
	BSLib::uint32 curCount = 0;
	std::vector<SItemInstanceID>::const_iterator it = m_IndexArray.begin();
	for (BSLib::uint32 index = 0; index < m_IndexArray.size(); ++index) {
		SItemInstanceID itemEntityID = getItemInstanceID(index);
		if (itemEntityID.isEmpty()){
			continue;
		}
		CItemTPIDList* list = getItemTPIDList(itemEntityID);
		if(list == NULL){
			continue;
		}

		SBagItem bagItem;
		if(!list->getItemByIndex(index,bagItem)){
			continue;
		}

		if( EITEM_TP_EQUIP_NENGLIANGQIU != bagItem.m_type)
		{
			continue;
		}

		BSLib::Utility::CStream itemStream;
		itemStream.reset();
		bagItem.serializeTo(itemStream);

		ItemTPID tpid = itemEntityID.getItemTPID();
		BSLib::uint32 InstanceID = itemEntityID.getInstanceID();
		if(CItemGMMgr::singleton().getMainType(tpid) == EMAIN_TP_EQUIP){
			BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[BAGDATA][装备数据][a_itemTPID=%d][curCount=%d]",tpid,curCount);
			EquipID equipID = (EquipID)InstanceID;
			BSLib::Utility::CStream tempStream;
			tempStream.reset();
			if(!equipModule->getEquipDataForBag(equipID,tpid,tempStream)){
				BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[serializeToClient][获取装备详细数据失败][equipID=%d]", equipID);
				if(!removeItem(index,1)){
					BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[删除背包中无效实例装备,失败][a_index=%d][equipID=%d]",index,equipID);
				}
				continue;
			}
			if (equipModule->isEquipStatusOn(equipID)){
				BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[删除背包中物品,DATA_RECOVERY][a_index=%d][equipID=%d]",index,equipID);
				if(!removeItem(index,1)){
					BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[删除背包中装备,失败][a_index=%d][equipID=%d]",index,equipID);
				}
				continue;
			}

			itemStream << tempStream;
		}
		else{
			BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[BAGDATA][普通道具][a_itemTPID=%d][curCount=%d]",tpid,curCount);
			BSLib::uint32 addLevel = 0;
			BSLib::uint32 gemsCount = 0;
			itemStream << addLevel;
			itemStream << gemsCount;
		}
		stream << itemStream;
		curCount ++;
	}
	a_itemCount = curCount;
	return true;
}

bool CRoleBagGMMgr::serializeToClient(GSLib::PlayerSystem::GM::CRoleGM* a_role,BSLib::uint32& a_itemCount,BSLib::Utility::CStream& stream)
{
    if(a_role == NULL){
        return true;
    }

    EquipSystem::GM::CRoleEquipModule* equipModule = (EquipSystem::GM::CRoleEquipModule*)a_role->getPlayerModuleGM(EMODULECTYPE_EQUIP);
    if(equipModule == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[获取装备模块失败]");
        return false;
    }

    stream.reset();
    BSLib::uint32 curCount = 0;
    std::vector<SItemInstanceID>::const_iterator it = m_IndexArray.begin();
    for (BSLib::uint32 index = 0; index < m_IndexArray.size(); ++index) {
        SItemInstanceID itemEntityID = getItemInstanceID(index);
        if (itemEntityID.isEmpty()){
            continue;
        }
        CItemTPIDList* list = getItemTPIDList(itemEntityID);
        if(list == NULL){
            continue;
        }

        SBagItem bagItem;
        if(!list->getItemByIndex(index,bagItem)){
            continue;
        }

		if( EITEM_TP_EQUIP_NENGLIANGQIU == bagItem.m_type)
		{
			continue;
		}
       
        BSLib::Utility::CStream itemStream;
        itemStream.reset();
        bagItem.serializeTo(itemStream);

        ItemTPID tpid = itemEntityID.getItemTPID();
        BSLib::uint32 InstanceID = itemEntityID.getInstanceID();
        if(CItemGMMgr::singleton().getMainType(tpid) == EMAIN_TP_EQUIP){
            BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[BAGDATA][装备数据][a_itemTPID=%d][curCount=%d]",tpid,curCount);
            EquipID equipID = (EquipID)InstanceID;
            BSLib::Utility::CStream tempStream;
            tempStream.reset();
            if(!equipModule->getEquipDataForBag(equipID,tpid,tempStream)){
                BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[serializeToClient][获取装备详细数据失败][equipID=%d]", equipID);
                if(!removeItem(index,1)){
                    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[删除背包中无效实例装备,失败][a_index=%d][equipID=%d]",index,equipID);
                }
                continue;
            }
            if (equipModule->isEquipStatusOn(equipID)){
                BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[删除背包中物品,DATA_RECOVERY][a_index=%d][equipID=%d]",index,equipID);
                if(!removeItem(index,1)){
                    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[删除背包中装备,失败][a_index=%d][equipID=%d]",index,equipID);
                }
                continue;
            }
           
            itemStream << tempStream;
        }
        else{
            BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[BAGDATA][普通道具][a_itemTPID=%d][curCount=%d]",tpid,curCount);
            BSLib::uint32 addLevel = 0;
            BSLib::uint32 gemsCount = 0;
            itemStream << addLevel;
            itemStream << gemsCount;
        }
        stream << itemStream;
        curCount ++;
    }
    a_itemCount = curCount;
    return true;
}

bool CRoleBagGMMgr::serializeToDB(BagIndex a_index,DB::SRoleBagItemData& bagItemData) const
{
    SItemInstanceID itemEntityID = getItemInstanceID(a_index);
    if (itemEntityID.isEmpty()){
        return false;
    }

    CItemTPIDList* list = getItemTPIDList(itemEntityID);
    if(list == NULL){
        return false;
    }

    bagItemData.m_instanceID = itemEntityID.getInstanceID();
    return list->getItem(a_index,bagItemData);
}

bool CRoleBagGMMgr::removeItemCount(SItemInstanceID a_itemInstanceID,BSLib::uint32 a_count,std::vector<BSLib::uint32>& a_notifyIndexArray,std::vector<BSLib::uint32>& a_notifyCountArray)
{
    CItemTPIDList* itemList = getItemTPIDList(a_itemInstanceID);
    if(itemList == NULL){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[removeItemCount][itemList == NULL][a_itemTPID=%lld][a_count=%d]",a_itemInstanceID.getItemTPID(),a_count);
        return false;
    }
    BSLib::uint32 removeCount = a_count;
    BSLib::uint32 totalCount = itemList->getTotalCount();
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[removeItemCount][removeCount=%d][totalCount=%d]",removeCount,totalCount);
    if(removeCount > totalCount){
        return false;
    }
    if(!itemList->removeItemCount(a_count,a_notifyIndexArray,a_notifyCountArray)){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[removeItemCount][ERROR][removeCount=%d][totalCount=%d]",removeCount,totalCount);
        return false;
    }
    for(BSLib::uint32 i=0;i< a_notifyCountArray.size(); ++i){
        
        if(a_notifyCountArray[i] == 0){
           BSLib::uint32 index = a_notifyIndexArray[i];
           setItemInstanceID(index,SItemInstanceID(0,0));
        }
    }
    return true;
}

bool CRoleBagGMMgr::removeItem(BagIndex a_index,BSLib::uint32 a_count)
{
    SItemInstanceID item = getItemInstanceID(a_index);
    CItemTPIDList* itemList = getItemTPIDList(item);
    if(itemList == NULL){
        return false;
    }
    BSLib::uint32 itemCount = itemList->getItemCount(a_index);
    if(itemCount < a_count){
        return false;
    }

    itemCount -= a_count;
    if(!itemList->setIndexItemCount(a_index,itemCount)){
        return false;
    }
    if(itemCount == 0){
       setItemInstanceID(a_index,SItemInstanceID(0,0));
    }

    return true;
}

bool CRoleBagGMMgr::addItemCount(SItemInstanceID a_itemInstanceID,BSLib::uint32 a_count,std::vector<BSLib::uint32>& a_notifyIndexArray,std::vector<BSLib::uint32>& a_notifyCountArray)
{
    CItemTPIDList* itemList = getItemTPIDList(a_itemInstanceID);
    if(itemList == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[BAGDATA][a_itemTPID=%d][a_count=%d]",a_itemInstanceID.getItemTPID(),a_count);
        return false;
    }

    BSLib::uint32 removeCount = a_count;
    if(removeCount > itemList->getTotalCount()){
        return false;
    }

    itemList->removeItemCount(a_count,a_notifyIndexArray,a_notifyCountArray);
    for(BSLib::uint32 i=0;i< a_notifyCountArray.size(); ++i){
        if(a_notifyCountArray[i] == 0){
            BSLib::uint32 index = a_notifyIndexArray[i];
            setItemInstanceID(index,SItemInstanceID(0,0));
        }
    }

    return true;
}

bool CRoleBagGMMgr::addItemByIndex(BagIndex a_index,SItemInstanceID a_itemInstanceID,EItemType a_type,BSLib::uint32 a_count)
{
    if(a_type >= EITEM_TP_MAX){
        return false;
    }

    if((a_index < 0) || (a_index>(getPosCount()-1))){
        return false;
    }

    // 加入格子中
    setItemInstanceID(a_index,a_itemInstanceID);
    // 更新物品数量
    CItemTPIDList* itemList = getItemTPIDList(a_itemInstanceID);
    if(itemList == NULL){
        CItemTPIDList* item = new CItemTPIDList(a_itemInstanceID,a_index,a_count,a_type);
        if(item == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[BAGDATA][_addItemToMap][new 内存失败]");
            return false;
        }
        m_bagItemMap.insert(std::pair<SItemInstanceID, CItemTPIDList*>(a_itemInstanceID,item));
        return true;
    }
    BSLib::uint32 oldCount = itemList->getItemCount(a_index);
    BSLib::uint32 totalCount = oldCount + a_count;
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[添加物品][addItemByIndex][oldCount=%d][a_count=%d][totalCount=%d]",oldCount,a_count,totalCount);
    return itemList->setIndexItemCount(a_index,totalCount);
}

CItemTPIDList* CRoleBagGMMgr::getItemTPIDList(SItemInstanceID a_itemInstanceID) const
{
    std::map<SItemInstanceID,CItemTPIDList*>::const_iterator it = m_bagItemMap.find(a_itemInstanceID);
    if( it == m_bagItemMap.end()){
        return NULL;
    }

    return it->second;
}



SItemInstanceID CRoleBagGMMgr::getItemInstanceID(BagIndex a_index) const
{
    if(a_index > m_IndexArray.size()){
        return SItemInstanceID(0,0);
    }
    return m_IndexArray[a_index];
}


bool CRoleBagGMMgr::getIndexByItemInstanceID(const SItemInstanceID& a_itemInstanceID,BagIndex& bagIndex)
{
    for(BSLib::uint32 index=0;index<m_IndexArray.size();++index){
        SItemInstanceID itemEntityID = getItemInstanceID(index);
        if(a_itemInstanceID == itemEntityID){
            bagIndex = index;
            return true; 
        }
    }
    return false;
}

bool CRoleBagGMMgr::getIndexByInstanceID(BSLib::uint32 a_instanceID,BagIndex& bagIndex)
{
    for(BSLib::uint32 index=0;index<m_IndexArray.size();++index){
        SItemInstanceID itemEntityID = getItemInstanceID(index);
        if(a_instanceID == itemEntityID.getInstanceID()){
            bagIndex = index;
            return true; 
        }
    }
    return false;
}

bool CRoleBagGMMgr::setItemInstanceID(BagIndex a_index,SItemInstanceID a_itemInstanceTPID)
{
    SItemInstanceID instanceTPID = getItemInstanceID(a_index);
    if(instanceTPID != a_itemInstanceTPID){
       m_IndexArray[a_index] = a_itemInstanceTPID;
    }
    _updateBagItemCount();
    return true;
}

bool CRoleBagGMMgr::_initConfigItem(ItemTPID a_tpid,BSLib::uint32 a_count,BSLib::uint32 a_instanceID)
{ 
    SItemInstanceID newItemEntityID(a_tpid,a_instanceID);
    // TODO:初始物品数量超出背包大小时,多余的物品将被丢弃，不支持超出36格
    for(BSLib::uint32 index=0;index<m_IndexArray.size();++index){
        SItemInstanceID itemEntityID = getItemInstanceID(index);
        if(!itemEntityID.isEmpty()){
            continue;
        }
        EItemType type = CItemGMMgr::singleton().getType(a_tpid);
        addItemByIndex(index,newItemEntityID,type,a_count);
		if(EITEM_TP_EQUIP_NENGLIANGQIU != type)
		{
			m_showCount++;
		}
        m_usedPosCount++;
        return true;
    }
    return false;
}

bool CRoleBagGMMgr::addPosCount(BSLib::uint32 a_count)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "addPosCount[before][a_count=%d][m_bagPosCount=%d]", a_count,getPosCount());
    for(BSLib::uint32 i=0;i<a_count;i++){
        m_IndexArray.push_back(SItemInstanceID(0,0));
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "addPosCount[after][a_count=%d][m_bagPosCount=%d]", a_count,getPosCount());
    return true;
}

BSLib::uint32 CRoleBagGMMgr::getItemCountByIndex(BagIndex a_index) const
{
    SItemInstanceID itemEntityID = getItemInstanceID(a_index);
    CItemTPIDList *list = getItemTPIDList(itemEntityID);
    if(list == NULL){
        return 0;
    }
    return list->getItemCount(a_index);
}

BSLib::uint32 CRoleBagGMMgr::getItemCount(const SItemInstanceID& a_itemInstanceID) const
{
    CItemTPIDList *list = getItemTPIDList(a_itemInstanceID);
    if(list == NULL){
        return 0;
    }
    return list->getTotalCount();
}

bool CRoleBagGMMgr::getItemByIndex(BagIndex a_index,SBagItem& a_bagItem) const
{
    SItemInstanceID itemEntityID = getItemInstanceID(a_index);
    if (itemEntityID.isEmpty()){
        return false;
    }
    CItemTPIDList* list = getItemTPIDList(itemEntityID);
    if(list == NULL){
        return false;
    }
    return list->getItemByIndex(a_index,a_bagItem);
}

BSLib::uint32 CRoleBagGMMgr::getEmptyPosCount()const 
 {
     BSLib::uint32 bagSize = m_IndexArray.size();
     if(m_usedPosCount >= m_IndexArray.size()){
         return 0;
     }
     return (EBAGPOSITION_MAX_COUNT - m_showCount);
 }

BSLib::uint32 CRoleBagGMMgr::getNeedEmptyPosCount(const SItemInstanceID& a_itemInstanceID,BSLib::uint32 a_addCount) const
{
    BSLib::uint32 needEmptyPosCount = 0;
    const ItemTPID tpid = a_itemInstanceID.getItemTPID();
    EMainType mainType = CItemGMMgr::singleton().getMainType(tpid);
    if ((mainType != EMAIN_TP_ITEM) &&(mainType != EMAIN_TP_EQUIP)){
        return needEmptyPosCount;
    }

    if ((mainType == EMAIN_TP_EQUIP)){

		if( EITEM_TP_EQUIP_NENGLIANGQIU == CItemGMMgr::singleton().getType(tpid))
		{
			// 能量球表现上不占位置
			return needEmptyPosCount;
		}	
		
        needEmptyPosCount += a_addCount;
        return needEmptyPosCount;
    }
    
    if(!CItemGMMgr::singleton().isRepeated(tpid)){
        needEmptyPosCount += a_addCount;
        return needEmptyPosCount;
    }

    const BSLib::uint32 stackCount = CItemGMMgr::singleton().getStackCount(tpid);
    if (stackCount <= 1){
        needEmptyPosCount += a_addCount;
        return needEmptyPosCount;
    }

    BSLib::uint32 curTotalCount = 0;
    CItemTPIDList* list = getItemTPIDList(a_itemInstanceID);
    if(list != NULL){
       curTotalCount = list->getTotalCount();
    }
    // 未满空间
    BSLib::uint32 posLeftCount = stackCount - (curTotalCount%stackCount);
    if(posLeftCount == stackCount){
        posLeftCount = 0;
    }
    // 需要空间
    if(a_addCount <= posLeftCount){
        return needEmptyPosCount;
    }
    // 需要格子
    needEmptyPosCount = (a_addCount - posLeftCount)/(stackCount+1) + 1;

    return needEmptyPosCount;
}

BSLib::uint32 CRoleBagGMMgr::getNeedEmptyPosCount(const std::vector<SItemInstanceID>& a_itemTPIDArray, const std::vector<BSLib::uint32>& a_itemCountArray) const
{
    if(a_itemTPIDArray.size() != a_itemTPIDArray.size()){
        return 0;
    }

    BSLib::uint32 needEmptyPosCount = 0;
    for(BSLib::uint32 i=0;i<a_itemTPIDArray.size();++i){
        BSLib::uint32 addCount = getNeedEmptyPosCount(a_itemTPIDArray[i],a_itemCountArray[i]);
        needEmptyPosCount += addCount;
    }

    return needEmptyPosCount;
}

bool CRoleBagGMMgr::isValidItem(ItemTPID a_itemTPID) const
{
    return CItemGMMgr::singleton().isValid(a_itemTPID);
}


EAddResult CRoleBagGMMgr::isableAddItem(const std::vector<SItemInstanceID>& a_itemTPIDArray, const std::vector<BSLib::uint32>& a_itemCountArray,bool a_force)
{
    if(a_itemTPIDArray.size() != a_itemCountArray.size()){
        return EADDITEM_FAIL;
    }
    BSLib::uint32 needPosCount = 0;
    for(BSLib::uint32 i=0;i<a_itemTPIDArray.size();++i){
        BSLib::uint32 addCount = getNeedEmptyPosCount(a_itemTPIDArray[i],a_itemCountArray[i]);
        needPosCount += addCount;
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "isableAddItem[emptyPosCount=%d][needPosCount=%d]",getEmptyPosCount(),needPosCount);
    if (getEmptyPosCount() < needPosCount){
        return EADDITEM_BAG_NOTENOUGH_POSITION;
    }

    return EADDITEM_SUCCESS;
}

bool CRoleBagGMMgr::isableAddItem(const ItemSystem::GM::CPrizeItem& a_item,bool a_force,EAddResult& a_reason,InstanceID a_instaceID)
{
    SItemInstanceID itemEntityID(a_item.m_itemTPID,a_instaceID);
    a_reason = _isableAddItem(itemEntityID,a_item.m_itemCount,a_force);
    return (EADDITEM_SUCCESS==a_reason)?true:false;
}

bool CRoleBagGMMgr::getDesIndex(const CPrizeItem& a_item,BSLib::uint32 a_instanceID, std::vector<SDesItem>& a_desIndexArray,bool force)
{
    a_desIndexArray.clear();
    SItemInstanceID itemEntityID(a_item.m_itemTPID,a_instanceID);
    bool isRepeated = CItemGMMgr::singleton().isRepeated(a_item.m_itemTPID);
    EMainType mainType = CItemGMMgr::singleton().getMainType(a_item.m_itemTPID);
    if (mainType == EMAIN_TP_EQUIP){
       isRepeated = false; 
    }
    const BSLib::uint32 maxStackCount = CItemGMMgr::singleton().getStackCount(a_item.m_itemTPID);
    EItemType type = CItemGMMgr::singleton().getType(a_item.m_itemTPID);
    // 不可重复物品添加
    if(!isRepeated){
        std::vector<BSLib::uint32> newIndexArray ;
        const BSLib::uint32 needPosCounts = a_item.m_itemCount; 

        if(!_getEmptyPosIndex(needPosCounts,force,newIndexArray)){
            BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "不可重复物品获取格子索引失败getDesIndex[emptyPosCount=%d][needPosCount=%d]",getEmptyPosCount(),needPosCounts);
            return false;
        }
        if(newIndexArray.size() != needPosCounts){
            BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "不可重复物品获取格子索引失败getDesIndex[newIndexArray.size()=%d][needPosCount=%d]",newIndexArray.size(),needPosCounts);
            return false;
        }
        for(BSLib::uint32 i=0;i<needPosCounts;++i){     
            SDesItem addItem;
            addItem.m_index = newIndexArray[i];
            addItem.m_type = type;
            addItem.m_tpid = a_item.m_itemTPID;
            addItem.m_count = 1;
            a_desIndexArray.push_back(addItem);
        }
        return true;
    }

    // 可重复物品添加
    BSLib::uint32 needEmptyPosCount = getNeedEmptyPosCount(itemEntityID,a_item.m_itemCount);
    BSLib::uint32 positionIndex = _getNotFullPosIndex(itemEntityID);
    // 没有未满的格子
    if(positionIndex == INVALID_BAG_POSITION_INDEX){
        std::vector<BSLib::uint32> newIndexArray ;
        if(!_getEmptyPosIndex(needEmptyPosCount,force,newIndexArray)){
            return false;
        }
        if(newIndexArray.size() != needEmptyPosCount){
            return false;
        }
        BSLib::uint32 itemCount = a_item.m_itemCount;
        for(BSLib::uint32 i=0;i<needEmptyPosCount;++i){
            SDesItem addItem;
            addItem.m_index = newIndexArray[i];
            addItem.m_type = type;
            addItem.m_tpid = a_item.m_itemTPID;
            if(itemCount > maxStackCount){
                addItem.m_count = maxStackCount;
                itemCount -=maxStackCount;
            }
            else{
                addItem.m_count = itemCount;
                itemCount = 0;
            }
            a_desIndexArray.push_back(addItem);
        }
        if(itemCount != 0){
            return false;
        }
        return true;
    }

    // 有未满的格子
    BSLib::uint32 inputCount = 0;
    if (INVALID_BAG_POSITION_INDEX != positionIndex){
        // 填满格子
        if(needEmptyPosCount == 0){
            SDesItem addItem;
            addItem.m_index = positionIndex;
            addItem.m_type = type;
            addItem.m_tpid = a_item.m_itemTPID;
            addItem.m_count = a_item.m_itemCount;
            a_desIndexArray.push_back(addItem);
            return true;
        }

        // 填满旧格子
        BSLib::uint32 filledCount = getItemCountByIndex(positionIndex);
        inputCount = maxStackCount - filledCount;
        SDesItem addItem;
        addItem.m_index = positionIndex;
        addItem.m_count = type;
        addItem.m_tpid = a_item.m_itemTPID;
        addItem.m_count = inputCount;
        a_desIndexArray.push_back(addItem);
        BSLib::uint32 desItemCount = a_item.m_itemCount - inputCount;

        // 新格子中添加物品
        std::vector<BSLib::uint32> newIndexArray ;
        if(!_getEmptyPosIndex(needEmptyPosCount,force,newIndexArray)){
            return false;
        }
        if(newIndexArray.size() != needEmptyPosCount){
            return false;
        }
        for(BSLib::uint32 i=0;i<needEmptyPosCount;++i){
            addItem.m_index = newIndexArray[i];
            addItem.m_type = type;
            addItem.m_tpid = a_item.m_itemTPID;
            if(desItemCount > maxStackCount){
                addItem.m_count = maxStackCount;
                desItemCount -= maxStackCount;
            }
            else{
                addItem.m_count = desItemCount;
                desItemCount = 0;
            }
            a_desIndexArray.push_back(addItem);
        }

        if(desItemCount != 0){
            return false;
        }
        return true;
    }

    return false;
}

bool CRoleBagGMMgr::combineItems(const std::vector<CPrizeItem>& a_srcItemArray,std::vector<SItemInstanceID>& a_desTPIDArray, std::vector<BSLib::uint32>& a_desCountArray) const
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
    a_desTPIDArray.clear();
    a_desCountArray.clear();
    for( ; it != bonusMap.end(); ++it) {
        SItemInstanceID item(it->first,0);
        a_desTPIDArray.push_back(item);
        a_desCountArray.push_back(it->second);
    }
    bonusMap.clear();

    return true;
}

bool CRoleBagGMMgr::isBagFull() const
{
	return m_showCount == EBAGPOSITION_MAX_COUNT;
//     if(m_usedPosCount >= m_IndexArray.size()){
//         return true; 
//     }
//     return false;
}


EAddResult CRoleBagGMMgr::_isableAddItem(const SItemInstanceID& a_itemInstanceID,BSLib::uint32 a_count,bool a_force)
{
    if(!isValidItem(a_itemInstanceID.getItemTPID())){
        return EADDITEM_INVALID_ITEM;
    }
    EMainType mainType = ItemSystem::GM::CItemGMMgr::singleton().getMainType(a_itemInstanceID.getItemTPID());
    if ((mainType != EMAIN_TP_ITEM) &&(mainType != EMAIN_TP_EQUIP)){
        return EADDITEM_INVALID_ITEM;
    }
    BSLib::uint32 needPosCount = getNeedEmptyPosCount(a_itemInstanceID,a_count);
    if(needPosCount > getEmptyPosCount()){
        return EADDITEM_BAG_NOTENOUGH_POSITION;
    }
    return EADDITEM_SUCCESS;
}

BagIndex CRoleBagGMMgr::_getNotFullPosIndex(SItemInstanceID a_itemInstanceID) const
{
    const ItemTPID tpid = a_itemInstanceID.getItemTPID();
    using namespace ItemSystem::GM;
    if(!CItemGMMgr::singleton().isRepeated(tpid)){
        return INVALID_BAG_POSITION_INDEX;
    }

    EMainType mainType = CItemGMMgr::singleton().getMainType(tpid);
    if (mainType != EMAIN_TP_ITEM){
        return INVALID_BAG_POSITION_INDEX;
    }

    CItemTPIDList* itemList = getItemTPIDList(a_itemInstanceID);
    if(itemList == NULL){
        return INVALID_BAG_POSITION_INDEX;
    }
    return itemList ->getFirstNotFullIndex();
}

bool CRoleBagGMMgr::_getEmptyPosIndex(BSLib::uint32 a_needCount,bool a_force,std::vector<BSLib::uint32>& a_desIndex)
{
    BSLib::uint32 needCount = a_needCount;
    a_desIndex.clear();
    for(BSLib::uint32 i=0;i<getPosCount();++i){
        if(0 == _getItemTPIDByIndex(i)){
            a_desIndex.push_back(i);
            needCount--;
        }
        if(needCount == 0){
            return true;
        }
    }

    if(!a_force){
        return false;
    }

    addPosCount(needCount);

    for(BSLib::uint32 index=0;index<getPosCount();++index){
        if(0 == _getItemTPIDByIndex(index)){
            a_desIndex.push_back(index);
            needCount--;
        }
        if(needCount == 0){
            return true;
        }
    }

    return false;
}

ItemTPID CRoleBagGMMgr::_getItemTPIDByIndex(BagIndex a_index) const
{
    SItemInstanceID item = getItemInstanceID(a_index);
    return item.getItemTPID();
}

InstanceID CRoleBagGMMgr::_getInstanceIDByIndex(BagIndex a_index) const
{
    SItemInstanceID item = getItemInstanceID(a_index);
    return item.getInstanceID();
}

BSLib::uint32 CRoleBagGMMgr::_getItemStackLimit(ItemTPID a_tpid)
{
    return 99;
}

void CRoleBagGMMgr::_updateBagItemCount()
{
    BSLib::uint32 itemCount = 0;
	BSLib::uint32 showNum = 0;
    for(BSLib::uint32 index=0;index<m_IndexArray.size();++index){
        SItemInstanceID itemEntityID = getItemInstanceID(index);
        if(itemEntityID.isEmpty()){
            continue;
        }

		ItemSystem::GM::CItemDataGM* item =  ItemSystem::GM::CItemGMMgr::singleton().getItem(itemEntityID.getItemTPID());
		if( NULL != item && EITEM_TP_EQUIP_NENGLIANGQIU != item->getType())
		{
			showNum++;
		}
		else
		{
			
		}
        itemCount++;
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_updateBagItemCount[m_usedPosCount:%d->%d]", m_usedPosCount,itemCount);
    m_usedPosCount = itemCount;
	m_showCount = showNum;
}

}//GM

}//PlayerSystem

}//GSLib
