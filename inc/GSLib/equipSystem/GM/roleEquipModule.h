#ifndef __GSLIB_EQUIPSYSTEM_GM_ROLEEQUIPMODULE_H__
#define __GSLIB_EQUIPSYSTEM_GM_ROLEEQUIPMODULE_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/uniqueID.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/equipSystem/baseDef.h>
#include <GSLib/equipSystem/GM/roleEquipGM.h>
#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/equipSystem/msgEquipSystem.h>
#include <GSLib/taskSystem/GM/roleTaskModule.h>
#include <GSLib/itemSystem/GM/itemDataGM.h>

namespace GSLib
{

namespace EquipSystem
{

namespace GM
{

class CRoleEquipModule : public GSLib::PlayerSystem::GM::CRoleModuleGM,BSLib::Utility::CUniqueIDMgr<EquipID>
{
public:
	CRoleEquipModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CRoleEquipModule();

public:
	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void updateDataToDB();
    virtual void updateDataToDB(EquipID a_equipID);

	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual void cbSelectTableData(BSLib::uint32 a_sessionID, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream);
    virtual void onRoleDelete();

    virtual bool checkUniqueID(EquipID a_equipID);

    bool updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave = false);
	bool updateTableData(EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize,  bool a_needSave = false);
    
	void _notifyEquipUpdateDataToClient(EquipID a_equipID);
    bool _dbRemoveItem(BSLib::uint32 a_equipID);

    bool removeTableData(BSLib::Utility::CStream& a_steam, EDBTableID a_tableID, bool a_needSave = false);
    bool removeTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, EDBTableID a_tableID, bool a_needSave = false);

	 bool sellEquip(ItemTPID a_id);

public:
	void _onMsgEquipSystemGC2GMReqResetAttr(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgEquipSystemGC2GMReqNextAddLevelEquip(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgEquipSystemGC2GMReqDisassemblyEquip(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgEquipSystemGC2GMReqGetDisassemblyEquipResult(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgEquipSystemGC2GMReqEquipData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgEquipSystemGC2GMReqCondition(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgEquipSystemGC2GMReqSaveOperation(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgEquipSystemGC2GMReqGetEquipItem(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgEquipSystemGC2GMReqUpgradeLevel(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgEquipSystemGC2GMReqUpgradeQuality(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgEquipSystemGC2GMReqChangeEquipStatus(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    
	void _onMsgEquipSystemGC2GMReqGemCombine(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgEquipSystemGC2GMReqChangeGemStatus(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

public:
    bool getEquipIDList(BSLib::Utility::CStream& stream) const;
    const SBattleAttribute& getTotalBattleAttr() const;
    CRoleEquipGM* randEquip(BSLib::uint32 a_tpid,bool a_statusOn,bool a_foreAdd,bool a_notify,BSLib::uint32& a_index,const std::string& a_reason);

    bool removeEquip(EquipID a_equipID);
    bool getDataForBag(EquipID a_equipID,BSLib::Utility::CStream& stream) const;
    bool getEquipDataForBag(EquipID a_equipID,ItemTPID a_tpid,BSLib::Utility::CStream& stream) const;
    bool isEquipStatusOn(EquipID a_equipID) const;

	CRoleEquipGM* getEquip(EquipID a_equipID) const;
	
	ItemTPID getFashionTPID();	// 获取时装 tpid


private:
    void _updateEquipTotalBattleAttr(bool a_notify = true);
    void updateEquipStatus();

	bool _getEquipList(std::list<CEquipData> &roleEquipList) const;
    bool _getEquipData(EEquipStatus a_status,BSLib::uint32& a_equipCount,BSLib::Utility::CStream& stream) const;
    bool _getAllEquipData(BSLib::uint32& a_equipCount,BSLib::Utility::CStream& stream) const;

    CRoleEquipGM* _createEquipGM(DB::SRoleEquipData& a_equipData);

private:
    EDisassemblyEquipResult _disassemblyEquipList(const std::vector<EquipID>& a_equipIDList);
    EDisassemblyEquipResult _checkDisassemblyEquip(EquipID a_equipID);
    EDisassemblyEquipResult _disassemblyEquip(EquipID a_equipID);
    EGetDisassemblyEquipResult _getDisassemblyEquipResultList(const std::vector<EquipID>& a_equipIDList,BSLib::Utility::CStream& a_stream);
    EGetDisassemblyEquipResult _getDisassemblyEquipResult(EquipID a_equipID,std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray);

    EUpgradeLevelResult _upgradeLevel(EquipID a_equipID);
	//EUpgradeQualityResult _upgradeQuality(EquipID a_equipID,ItemTPID a_itemTPID,SQualityReuslt& a_qualityResult);
    EResetAttrResult _resetAttr(EquipID a_equipID,EResetEquipType a_resetEquipType,const std::vector<BSLib::uint32>& a_lockAttrIndexArray, EquipID a_itemEquipID);
	EResetAttrResult _exchangeAttr(EquipID a_equipID, EquipID a_itemEquipID);
    EGemCombineResult _combineGems(EGemsCombineType type,ItemTPID a_gemTPID,ItemTPID& a_newGemTPID);
    EGemUpdateStatusResult _addGemsToEquip(EquipID a_equipID,ItemTPID a_gemTPID,EGemSlot a_index);
    EGemUpdateStatusResult _removeGemFromEquip(EquipID a_equipID,ItemTPID a_gemTPID,EGemSlot a_index);

	void _updateDailyTask(GSLib::TaskSystem::GM::EDailyTaskType a_dailyTaskType);
public:
	bool loadGameConfig(const std::string& a_configPath);

private:
	CRoleEquipGM* _getEquip(EquipID a_equipID) const;
    bool _getOperationCondition(EquipID a_equipID,EEquipOperation a_operation ,CConditionData& a_conditionData) const;
    GSLib::PlayerSystem::GM::CRoleBagModuleGM * _getBag();
    
    EquipID _getEquipID(EEquipType a_equipType);
    void _setEquipStatus(CRoleEquipGM* a_equip,EEquipStatus a_status);
    void _setRoleEquip(EEquipType a_equipType,EquipID a_equipID);
    EChangeStatusResult _equipOff(EquipID a_equipID,BSLib::uint32& a_index);

    BSLib::uint32 _getResetAttrNeedGold(BSLib::uint32 a_lockCount,BSLib::uint32 a_equipLevel);
    BSLib::uint32 _getResetAttrNeedDiamond(BSLib::uint32 a_lockCount,BSLib::uint32 a_equipLevel);

    bool _getItemDataArray(const std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray,BSLib::Utility::CStream& a_stream) const;
    bool _combineItems(const std::vector<ItemSystem::GM::CPrizeItem>& a_srcItemArray, std::vector<ItemSystem::GM::CPrizeItem>& a_desItemArray) const;
    void _updateBagEquip(EquipID a_equipID);
    void _outputGameLog(const std::string& a_gameLable, const char* a_format, ...);
    std::string getRoleInfor() const;
	void _checkExpiredEquip(); // 检测是否有过期的时装

private:
    SBattleAttribute m_totalEquipBattleAttr;            // 身上装备总属性值
    EquipID m_roleEquipID[EQUIP_TYPE_COUNT];            // 身上装备ID
    BSLib::Utility::CHashMap<EquipID, CRoleEquipGM*> m_equipHashMap;
    BSLib::Utility::CUniqueID<EquipID> m_uniqueIDByEquipID;
};

}//GM

}//EquipSystem

}//GSLib

#endif//__GSLIB_EQUIPSYSTEM_GM_ROLEEQUIPMODULE_H__

