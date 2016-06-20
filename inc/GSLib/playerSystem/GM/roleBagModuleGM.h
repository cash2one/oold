//////////////////////////////////////////////////////////////////////
//	created:	2014/09/3
//	filename: 	GSLib\playerSystem\GM\roleBagModuleGM.h
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_GM_ROLEBAGMODULE_H__
#define __GSLIB_PLAYERSYSTEM_GM_ROLEBAGMODULE_H__
#include <GSLib/tracer.h>
#include <BSLib/utility/baseDef.h>
#include <BSLib/utility/hashMap.h>
#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <GSLib/itemSystem/GM/itemAttributeGM.h>
#include <GSLib/playerSystem/baseDef.h>
#include <BSLib/utility/table.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/playerSystem/GM/bagItem.h>
#include <GSLib/playerSystem/GM/roleBagGMMgr.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace GM
{
class CRoleBagModuleGM : public CRoleModuleGM
{
public:
	CRoleBagModuleGM(CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CRoleBagModuleGM();

public:
	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	void _onMsgPlayerSystemGC2GMReqGetBagData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgPlayerSystemGC2GMReqUseBagItemData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPlayerSystemGC2GMReqSoldBagItemData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	virtual void onRoleDelete();
	virtual void updateDataToDB();
    virtual void updateDataToDB(BagIndex a_index);

	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);

	bool updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave = false);
	bool updateTableData(EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize,  bool a_needSave = false);

	bool removeTableData(BSLib::Utility::CStream& a_steam, EDBTableID a_tableID, bool a_needSave = false);
	bool removeTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, EDBTableID a_tableID, bool a_needSave = false);

public:
    BSLib::uint32 getBagSize()const;

    // 背包接口
public:
	bool getItemByIndex(BSLib::uint32 a_index, SBagItem & a_BagItem) const;

    EAddResult addItem(const std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray,bool a_forceAdd,bool a_notify = true,const std::string& a_reason = "");
    EAddResult addItem(const ItemSystem::GM::CPrizeItem& a_item,bool a_force,bool a_notify = true,const std::string& a_reason = "");

    bool isableAddItem(const ItemSystem::GM::CPrizeItem& a_item,bool a_force,EAddResult& a_reason);
    EAddResult isableAddItems(const std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray,bool a_force = false);

    bool addEquip(const SItemInstanceID& a_itemInstanceID,bool a_forceAdd,bool a_notify,BSLib::uint32& a_index);

    // 使用物品
    EUseResult useItem(const std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray,bool a_notify = true,const std::string& a_reason = "");
    EUseResult useItem(const ItemSystem::GM::CPrizeItem& a_item,bool a_notify = true,const std::string& a_reason = "");
    EUseResult isableUseItem(const ItemSystem::GM::CPrizeItem& a_item);
    EUseResult isableUseItem(const std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray);

public:
    bool removeItemCount(ItemTPID a_itemTPID,GSLib::ItemSystem::GM::EItemType a_type,BSLib::uint32 a_rmCount,const std::string& a_reason = "",bool a_notify=false);
    bool removeItemByIndex(BagIndex a_index,const std::string& a_reason = "",bool a_notify=false);

    // 删除物品
    // 数量不足则全部删除
    bool forceRemoveItemCount(ItemTPID a_itemTPID,BSLib::uint32 a_rmCount,const std::string& a_reason = "",bool a_notify = false);

    BSLib::uint32 getItemCount(ItemTPID a_itemTPID) const;
    BSLib::uint32 getInstanceIDByIndex(BagIndex a_index);
    BSLib::uint32 getIndexByItemInstanceID(const SItemInstanceID& a_itemInstanceID);

    bool getIndexByItemInstanceID(const SItemInstanceID& a_itemInstanceID,BagIndex& bagIndex);

    bool isBagFull() const;

    bool sellItemNotInBag(ItemTPID a_tpid,BSLib::uint32 a_count,bool a_notify = true);

    bool notifyBagItemCount(BagIndex a_index,bool a_notify = true,bool a_save = true);		//todo 通知 能量球过滤
private:
    // 使用物品
    bool _useItemByIndex(BagIndex a_index,bool a_notify = false);
    bool _sellItemByIndex(BagIndex a_index,BSLib::uint32 a_count,bool a_notify = false);

	// 资源相关
	EUseResult _isableUseRes(const ItemSystem::GM::CPrizeItem& a_item);
    EUseResult _isableUseRes(const ItemTPID& a_itemTPID, const BSLib::uint32& a_count);
	EUseResult _isableUseRes(const std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray);

    EAddResult _addRes(const ItemSystem::GM::CPrizeItem& a_item,bool a_notify = true,const std::string& a_reason = "");
	EAddResult _addMutiRes(const std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray,bool a_notify = true);
	EUseResult _useRes(const ItemSystem::GM::CPrizeItem& a_item,bool a_notify = true,const std::string& a_reason = "");

	// 背包相关
	EUseResult _useBagItem(const ItemSystem::GM::CPrizeItem& a_item ,bool a_notify = true);
    EAddResult _addBagItem(const ItemSystem::GM::CPrizeItem& a_item ,bool a_force = false,bool a_notify = true,BSLib::uint32 instanceID = 0,const std::string& a_reason = "");
    EAddResult _addBagItems(const std::vector<SItemInstanceID>& a_itemInstanceIDs, const std::vector<BSLib::uint32>& a_itemCounts,bool a_force = false,bool a_notify = true);

    // 装备相关
    EAddResult _addEquipItem(const ItemSystem::GM::CPrizeItem& a_item,bool a_forceAdd,bool a_notify,const std::string& a_reason = "");
    bool _addEquip(const SItemInstanceID& a_itemInstanceID,bool a_force,bool a_notify,BagIndex& a_index);
    bool _randEquip(ItemTPID a_tpid,bool a_statusOn,bool a_force,bool a_notify,BagIndex& a_index,const std::string& a_reason);

private:	
    bool _nofityBagItemToClient(BagIndex a_index);		//todo 通知 能量球过滤
	bool _nodifyBagDataToClient(const SBagItem& a_bagItem);	// todo 能量球过滤
    void _notifyBagDataToClient();		//todo 通知 能量球过滤
    
private:
    bool _useItem(ItemTPID a_itemTPID,BSLib::uint32 a_count,bool a_notify = false);
	bool _dbRemoveItem(BSLib::uint32 a_itemIndex);
    void _outputGameLog(const std::string& a_gameLable, const char* a_format, ...);
    std::string getRoleInfor() const;

private:
    CRoleBagGMMgr* m_bagMgr;
};

}//GM

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GM_ROLEBAGMODULE_H__
