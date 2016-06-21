#ifndef __GSLIB_PLAYERSYSTEM_GM_ROLEBAGMMGR_H__
#define __GSLIB_PLAYERSYSTEM_GM_ROLEBAGMMGR_H__
#include <GSLib/tracer.h>
#include <BSLib/utility/baseDef.h>
#include <BSLib/utility/hashMap.h>
#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <GSLib/itemSystem/GM/itemAttributeGM.h>
#include <GSLib/playerSystem/baseDef.h>
#include <BSLib/utility/table.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/playerSystem/GM/bagItem.h>


namespace GSLib
{

namespace PlayerSystem
{

namespace GM
{

class CRoleBagGMMgr
{
public:
	CRoleBagGMMgr();
	virtual ~CRoleBagGMMgr();

public:
   bool initBagFromDB(const BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>* tables,GSLib::PlayerSystem::GM::CRoleGM* a_role);
   void final();
   void serializeToClient(BSLib::uint32& a_totalitemCount,BSLib::Utility::CStream& stream) const;  //todo 能量球开关,过滤 
   bool serializeToDB(BagIndex a_index,DB::SRoleBagItemData& a_itemData) const;

   bool serializeToClient(GSLib::PlayerSystem::GM::CRoleGM* a_role,BSLib::uint32& a_itemCount,BSLib::Utility::CStream& stream); //todo 能量球开关,过滤
   bool serializeNengLiangQiuToClient(GSLib::PlayerSystem::GM::CRoleGM* a_role,BSLib::uint32& a_itemCount,BSLib::Utility::CStream& stream);

   bool removeItemCount(SItemInstanceID a_itemInstanceID,BSLib::uint32 a_count,std::vector<BSLib::uint32>& a_notifyIndexArray,std::vector<BSLib::uint32>& a_notifyCountArray);
   bool removeItem(BagIndex a_index,BSLib::uint32 a_count);

   bool addItemCount(SItemInstanceID a_itemInstanceID,BSLib::uint32 a_count,std::vector<BSLib::uint32>& a_notifyIndexArray,std::vector<BSLib::uint32>& a_notifyCountArray);
   bool addItemByIndex(BagIndex a_index,SItemInstanceID a_instanceTPID,GSLib::ItemSystem::GM::EItemType a_type,BSLib::uint32 a_count);

public:
   CItemTPIDList* getItemTPIDList(SItemInstanceID a_itemInstanceID) const;
   // 索引操作
   ItemTPID _getItemTPIDByIndex(BagIndex a_index) const;
   InstanceID _getInstanceIDByIndex(BagIndex a_index) const;
   SItemInstanceID getItemInstanceID(BagIndex a_index) const;
   bool getIndexByItemInstanceID(const SItemInstanceID& a_itemInstanceID,BagIndex& bagIndex);
   bool getIndexByInstanceID(BSLib::uint32 a_instanceID,BagIndex& bagIndex);
   bool setItemInstanceID(BagIndex a_index,SItemInstanceID a_itemInstanceTPID);

   // 扩大背包上限
   bool addPosCount(BSLib::uint32 addPositionCount);

public:
   BSLib::uint32 getItemCountByIndex(BagIndex a_index) const;
   BSLib::uint32 getItemCount(const SItemInstanceID& a_itemInstanceID) const;
   bool getItemByIndex(BagIndex a_index,SBagItem& a_bagItem) const;

   BSLib::uint32 getPosCount() const { return m_IndexArray.size();}
   BSLib::uint32 getUsedPosCount() const {return m_usedPosCount;}
   BSLib::uint32 getEmptyPosCount() const;

   BSLib::uint32 getNeedEmptyPosCount(const SItemInstanceID& a_itemInstanceID,BSLib::uint32 a_addCount) const;
   BSLib::uint32 getNeedEmptyPosCount(const std::vector<SItemInstanceID>& a_itemTPIDArray, const std::vector<BSLib::uint32>& a_itemCountArray) const;

   bool isValidItem(ItemTPID a_itemTPID) const;

   EAddResult isableAddItem(const std::vector<SItemInstanceID>& a_itemTPIDArray, const std::vector<BSLib::uint32>& a_itemCountArray,bool a_force);
   bool isableAddItem(const ItemSystem::GM::CPrizeItem& a_item,bool a_force,EAddResult& a_reason,InstanceID a_instaceID = 0);

   bool getDesIndex(const ItemSystem::GM::CPrizeItem& a_item,BSLib::uint32 a_instanceID, std::vector<SDesItem>& a_desIndexArray,bool force = false);
   bool combineItems(const std::vector<ItemSystem::GM::CPrizeItem>& a_srcItemArray,std::vector<SItemInstanceID>& a_desTPIDArray, std::vector<BSLib::uint32>& a_desCountArray) const;

   bool isBagFull() const;

   // 调试输出
   std::string getBagToLogString() const 
   {
       BSLib::Utility::CStringA log;
       log.format("当前使用格子数usedIndexCount=%d][背包大小itemBag.size=%d]", m_usedPosCount, m_IndexArray.size());
       return log;
   }

private:
   EAddResult _isableAddItem(const SItemInstanceID &a_itemInstanceID,BSLib::uint32 a_count,bool a_force);
   BagIndex _getNotFullPosIndex(SItemInstanceID a_itemInstanceID) const;
    bool _initConfigItem(BSLib::uint32 a_tpid,BSLib::uint32 a_count,BSLib::uint32 a_instanceID = 0);
    bool _getEmptyPosIndex(BSLib::uint32 a_needCount,bool a_force,std::vector<BSLib::uint32>& a_desIndex);
    BSLib::uint32 _getItemStackLimit(ItemTPID a_tpid);
    void _updateBagItemCount();

private:
	BSLib::uint32 m_usedPosCount;                                // 占用的总格子数
	BSLib::uint32 m_showCount;									 // 显示已被占用的个数
    std::vector<SItemInstanceID> m_IndexArray;                   // 存储格子中实例ID
    std::map<SItemInstanceID,CItemTPIDList*> m_bagItemMap;       // 存储每个实例ID个数
};

}//GM

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GM_ROLEBAGMMGR_H__

