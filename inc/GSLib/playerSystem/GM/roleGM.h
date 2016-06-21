#ifndef __GSLIB_PLAYERSYSTEM_GM_ROLE_H__
#define __GSLIB_PLAYERSYSTEM_GM_ROLE_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/dateTime.h>

#include <GFLib/commonServer/commonSystem.h>

#include <GSLib/playerSystem/GM/roleResource.h>
#include <GSLib/playerSystem/baseDef.h>

#include <GSLib/playerSystem/GM/roleBagModuleGM.h>
#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/skillSystem/DB/tableSkillDB.h>
#include <GSLib/friendSystem/GM/friendSystemGM.h>
#include <GSLib/prizeSystem/GM/rolePrizeModule.h>

namespace GSLib
{

namespace EquipSystem
{
namespace GM
{
	class CRoleEquipGM;
	class CRoleEquipModule;
}
}

namespace SceneSystem
{
namespace GM
{
class CRoleSceneModule;
}
}

namespace FriendSystem
{

	namespace GM
	{
		class CRoleFriendModule;
	}

}

namespace ChatSystem
{

namespace GM
{
	class CRoleChatModule;
}

}

namespace PlayerSystem
{

namespace GM
{

class CPlayerGM;


class CRoleAllData{
public:
    CRoleAllData()
    {
    } 
    ~CRoleAllData()
    {
    } 

public:
    DB::SRoleData roleData;
    SkillSystem::DB::CRoleSkillData roleSkillData;
};

struct SVipLevelGift
{
    BSLib::uint32 m_vipLevel;
    BSLib::uint32 m_giftStatus;
};

class CRoleGM
{
public:
	CRoleGM(const GSLib::SRoleKey& a_roleKey, CPlayerGM* a_playerGM,RoleID a_roleID);
    CRoleGM(const GSLib::SRoleKey& a_roleKey, CPlayerGM* a_playerGM,RoleID a_roleID, BSLib::uint32 a_roleTPID, const std::string& a_roldName);
	virtual ~CRoleGM();

public:
	void init(bool isFirst = false);
	void preInit(bool isFirst = false);
	void postInit(bool isFirst = false);
	void initToClient();
	void final();
	
	void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	void updateDataToDB(bool a_first = false);

	void outputGameLog(const std::string& a_gameLable, const char* a_format, ...);
    std::string getRoleLogString() const;

private:
    void _updateRoleDataToDB(bool a_first);
    void _updateVipGiftDataToDB(bool a_first);

public:
	bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
    bool cbSelectGlobalMultiTableData(EModuleType a_srcModuleType,BSLib::uint32 a_sessionID,void* a_ptr,BSLib::uint32 a_state,std::vector<GSLib::DBSystem::SSelectTablesResult>& a_ackSelectTablesResultArray,std::vector<GSLib::DBSystem::CKeyTablePtr>& a_keyTablePtrArray,std::vector<GSLib::DBSystem::CKeyIndexTablePtr>& a_keyIndexTablePtrArray);

    void selectRoleData(const SRoleKey& a_roleKey,BSLib::uint32 a_sessionID,EModuleType a_srcModuleType,void* a_ptr = NULL);

public:
	void initRoleDataFromDB(const DB::SRoleData& a_roleData);
    bool getRoleDBData(DB::SRoleData& a_roleData) const;
	bool getRoleData(BSLib::Utility::CStream& a_stream);
    void getRoleBaseInfo(BSLib::Utility::CStream& a_stream);

	CPlayerGM* getPlayerGM() { return m_playerGM; }	
	CRoleModuleGM* getPlayerModuleGM(EModuleType a_moduleType);
	CRoleBagModuleGM * getRoleBag();
	EquipSystem::GM::CRoleEquipModule * getEquipModule() const;
	ChatSystem::GM::CRoleChatModule * getChatModule() const;
	FriendSystem::GM::CRoleFriendModule * getFriendModule() const;
	SceneSystem::GM::CRoleSceneModule * getSceneModule() const;
	PrizeSystem::GM::CRolePrizeModule * getPrizeModule() const;

public:
	bool sendMsgToClient(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToClient(GFLib::CMessage& msg);

	bool sendMsgToGateServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToGateServer(GFLib::CMessage& msg);

	bool sendMsgToDataServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToDataServer(GFLib::CMessage& msg);

	bool sendMsgToCenterServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToCenterServer(GFLib::CMessage& msg);

public:
	bool updateTableData(EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave = false);
	bool updateTableData(EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize, bool a_needSave = false);
	bool updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave = false);
	bool updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize, bool a_needSave = false);

	bool notifySaveAllTableDataToDB();
	bool notifySaveTableDataToDB(EDBTableID a_tableID);
public:
	RoleIndex getRoleIndex() const { return m_roleKey.getIndex(); }
	GFLib::ZoneID getZoneID() const { return m_roleKey.getZoneID(); }
	GFLib::AccountID getAccountID() const { return m_roleKey.getAccountID(); }
	const GFLib::SAccountKey& getAccountKey() const { return m_roleKey.getAccountKey(); }
	const GSLib::SRoleKey& getRoleKey() const { return m_roleKey; }
    const std::string getRoleDBKey() const {return m_roleKey.getDBKey();}

	const std::string getName() const ;
    BSLib::uint64 getRoleID() const;
	BSLib::uint32 getTPID() const;

public:
    BSLib::uint32 getSceneID() const ;
	BSLib::uint32 getLevel() const;
	BSLib::uint64 getExp() const ;
    BSLib::uint64 getGold() const ;

    BSLib::uint32 getStarLevel() const;
    BSLib::uint32 getQuality() const;
	BSLib::uint32 getPVPCoin() const;
	BSLib::uint32 getVitality() const;
	BSLib::uint32 getMaxVitality() const;
	BSLib::uint32 getPOP() const;
	BSLib::uint32 getTotalDiamond() const;
    BSLib::uint32 getBagSize() const;
    BSLib::uint32 getChargeDiamond() const;
    BSLib::uint32 getBindDiamond() const ;
    BSLib::uint32 getHP() const;
    BSLib::uint32 getSP() const;

	BSLib::uint32 getSkillPoint() const;
	BSLib::uint32 getSkillPointUpdateTime();
    BSLib::uint32 getVitalityUpdateTime();

public:
    BSLib::uint32 getVipLevel() const;
    BSLib::uint32 getVipScore() const;
    BSLib::uint32 getActiveDegree() const;
    
    BSLib::uint32 getTotalUseChargeDiamond()const;
    BSLib::uint32 getTotalUseBindDiamond()const;
    BSLib::uint32 getTotalChargeDiamond()const;
    BSLib::uint32 getResValue(ERoleResID a_resID) const;

	BSLib::uint32 getLightPower() const;

public:
    BSLib::uint32 getBattleAttr(EAttrID a_attrID) const;
    BSLib::uint32 getRoleTotalBattleAttr(EAttrID a_attrID) const;
    const SBattleAttribute& getRoleBattleAttr() const;
    const SBattleAttribute& getRoleTotalBattleAttr() const;
	BSLib::uint32 getCombat() const;
	BSLib::uint32 getHistoryMaxCombat() const;

    void updateBaseBattleAttr();
    bool updateTotalBattleAttr(bool a_notify = true);
    void updateCombat();

public:
	bool isActive() const { return (m_roleStatus == STATUS_ACTIVE);}
	bool isLoading() const { return (m_roleStatus == STATUS_LOADING);}

	ERoleStatus getRoleStatus()const { return m_roleStatus;}
	void setRoleStatus(ERoleStatus a_roleStatus);

	void onRoleActive();
	void onRoleInactive();
    void onRoleDelete();

public:
	bool isableModifyResource(ERoleResID a_resID,BSLib::int32 a_addValue) const;
	bool isableModifyGold(BSLib::int64 a_addValue) const;
	bool isableModifyExp(BSLib::int64 a_addValue) const;

	bool modifyRoleResource(ERoleResID a_resID,BSLib::int32 a_addValue,std::string a_reason,bool a_notify = true);
	bool modifyGold(BSLib::int64 a_addValue,std::string a_reason,bool a_notify = true);
	bool modifyExp(BSLib::int64 a_addValue,std::string a_reason,bool a_notify);

	bool addDiamond(BSLib::uint32 a_value,std::string a_reason,bool a_notify = true);
	bool delDiamond(BSLib::uint32 a_value,std::string a_reason,bool a_notify = true);

    bool chargeVipScore(BSLib::uint32 a_vipScore);

    bool addUpgradeVipLevelGift(BSLib::uint32 a_oldVipLevel,BSLib::uint32 a_vipLevel);
    bool addVipGift(BSLib::uint32 a_vipLevel,BSLib::uint32 a_giftStatus);
    bool updateVipGift(BSLib::uint32 a_vipLevel,BSLib::uint32 a_status);
    bool eraseVipGift(BSLib::uint32 a_vipLevel);
    void removeAllVipLevelGift();

    bool getCurrentVipGiftLevel(BSLib::uint32& a_vipLevel) const;
    bool getVipGift(BSLib::uint32 a_level);

	bool addLightPower(BSLib::uint32 a_value,std::string a_reason,bool a_notify = true);
	bool delLightPower(BSLib::uint32 a_value,std::string a_reason,bool a_notify = true);

	BSLib::uint32 getMaxPurchaseGoldTimes() const;
	BSLib::uint32 getPurchaseGoldNeedDiamond(BSLib::uint32 a_times) const;
	BSLib::uint32 getPurchasedGoldCount(BSLib::uint32 a_times) const;

private:
	bool _modifyDiamond(BSLib::int32 a_addValue,std::string a_reason,bool a_notify = true);
    bool _checkUpgrade(bool a_notify);
    bool _checkRoleVipLevelUpgrade(bool a_notify);

	void _initRoleData(bool isFirst = false);
    bool _initRoleResourceByConfig();
    bool _initRoleAttrByConfig();
    bool _initRoleSkillByConfig();

    void _deleteRoleDataToDB();

private:
	void _onRoleActive();
	void _onRoleInactive();

	void _preInitModule(bool isFirst = false);
	void _postInitModule(bool isFirst = false);
	void _initToClient();
	void _finalModule();

	void _initModuleMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	void _freeModuleMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

    void _onRoleDelete();
	void _updateModuleDataToDB();

    bool _cbGetRoleTableData(const GSLib::SRoleKey& a_roleKey,GSLib::DBSystem::ETableKeyType a_TableKeyType,GSLib::DBSystem::CKeyIndexTablePtr& a_keyIndexTable, GSLib::DBSystem::CKeyTablePtr& a_keyTable,EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID,BSLib::Utility::CStream& a_stream);
	bool _cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	bool _cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);

    bool _cbSelectGlobalMultiTableData(EModuleType a_srcModuleType,BSLib::uint32 a_sessionID,void*a_ptr,BSLib::uint32 a_state,std::vector<GSLib::DBSystem::SSelectTablesResult>& a_ackSelectTablesResultArray,std::vector<GSLib::DBSystem::CKeyTablePtr>& a_keyTablePtrArray,std::vector<GSLib::DBSystem::CKeyIndexTablePtr>& a_keyIndexTablePtrArray);
    bool _cbSelectMultiTableData(bool a_success,BSLib::uint32 a_sessionID,EModuleType a_srcModuleType,void* a_ptr,CRoleAllData& a_roleAllData);
    bool _cbSelectGetTableData(const GSLib::SRoleKey& a_roleKey,GSLib::DBSystem::ETableKeyType a_TableKeyType,GSLib::DBSystem::CKeyIndexTablePtr& a_keyIndexTable, GSLib::DBSystem::CKeyTablePtr& a_keyTable,EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID,BSLib::Utility::CStream& a_stream);

private:
	void _setRoleName(const std::string& a_roleName);
	void _setExp(const BSLib::uint64 value);
    void _setGold(const BSLib::uint64 value);

	void _setResource(ERoleResID a_resID,const BSLib::uint32 value);
	bool _updateGold(BSLib::int64 a_addValue,std::string a_reason);
	void _setRoleStatus(ERoleStatus a_roleStatus);

    bool _cbInitRoleVipGiftData(const DB::SRoleVipGiftData& a_giftData);
    BSLib::int32 _getWeekday(const BSLib::Utility::CDateTime& a_curTime) const;
    BSLib::uint64 _getVipGiftRefreshTime() const;

    BSLib::uint64 _getPreVipGiftRefreshTime() const { return m_vipGiftRefreshTime; }
    bool _refreshVipGiftTime();
    bool _refreshVipGift();

private:
    bool _notifyUpdateRoleResource(ERoleResID a_resID);
    bool _notifyUpdateRoleUInt64Resource(ERoleResID a_resID);
    bool _notifyBagSizeToClient();
    bool _notifyUpdateRoleDataToCenter();
    bool _notifyRoleBattleAttributeToClient();

private:

    CPlayerGM* m_playerGM;
    std::vector<CRoleModuleGM*> m_playerModuleList;

    GSLib::SRoleKey m_roleKey;
    std::string m_roleName;
    BSLib::uint64 m_roleID;
    BSLib::uint32 m_roleTPID;

    BSLib::uint32 m_combat;
	BSLib::uint32 m_historyCombatPower;
    ERoleStatus m_roleStatus; 

    BSLib::uint32 m_invalidFlag;

    BSLib::uint64 m_createTime;        // 创建时间
    BSLib::uint64 m_lastLoginTime;     // 上次登录时间
    BSLib::uint64 m_loginTime;         // 本次登录时间
    BSLib::uint64 m_lastQuitTime;      // 上次退出时间

    SRoleResource m_roleResource;
    SBattleAttribute m_battleAttr;
    SBattleAttribute m_totalBattleAttr;
    
	BSLib::Utility::CDateTime m_roleLastSkillUpdateTime;
	BSLib::Utility::CDateTime m_roleLastVitalityUpdateTime;

    BSLib::uint64 m_vipGiftRefreshTime;
    std::map<BSLib::uint32,SVipLevelGift*> m_vipLevelGiftMap;
    
};

}//GM

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GM_ROLE_H__

