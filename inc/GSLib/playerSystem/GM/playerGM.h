//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	GSLib\playerSystem\GM\CPlayerGM.h
//	author:	     zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_GM_PLAYERGM_H__
#define __GSLIB_PLAYERSYSTEM_GM_PLAYERGM_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>
#include <BSLib/utility/memory/objectMgr.h>
#include <BSLib/utility/uniqueID.h>
#include <GSLib/loginSystem/GM/netPlayerGM.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/sceneSystem/GM/battleEntityGM.h>
#include <GSLib/playerSystem/msgPlayerSystem.h>
#include <GSLib/dbSystem/keyIndexTable.h>
#include <GSLib/dbSystem/keyTable.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace GM
{

// 角色状态
typedef enum
{
	ESTATUS_NULL = 0,     // 未知
	ESTATUS_OFFLINE = 1,  // 下线
	ESTATUS_ONLINE = 2,   // 在线
}EPlayerStatus;


class CPlayerGM :public GSLib::LoginSystem::GM::CNetPlayerGM
{
public:
	CPlayerGM(EntityID a_entityID, const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName);
	virtual ~CPlayerGM();
 
public:
	bool setCurRoleIndex(RoleIndex a_curRoleIndex);
    bool chargeVipScore(BSLib::uint32 a_vipScore);

	CRoleGM* getCurRole();
	CRoleGM* getRole(RoleIndex a_roleIndex);
    CRoleGM* getRoleByName(std::string a_roleName);
    RoleIndex getCurRoleIndex() const { return m_curRoleIndex; }
	BSLib::uint32 getRoleCount() const {return m_roleHashMap.size();}
    BSLib::uint32 getVipScore() const { return m_vipScore; }

    bool isOnline() const ;
	bool isInvalidRoleIndex(RoleIndex a_roleIndex) const { return m_roleHashMap.find(a_roleIndex) == m_roleHashMap.end(); }
    
protected:
	virtual void _cbInitPlayer();
	virtual void _cbFinalPlayer();

	virtual void _cbPlayerOnline();
	virtual void _cbPlayerOffline();

public:
	virtual EntityID getEntityID() const;
	virtual EntityTPID getTPID() const;
	virtual std::string getName() const;

public:
    void updateDataToDB();
	bool updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave = false);
	bool updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize, bool a_needSave = false);

private:
	virtual void _cbInitMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	void _onMsgPlayerSystemGC2GMReqInitPlayerData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgPlayerSystemGC2GMReqCreateRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgPlayerSystemGC2GMReqSelectRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPlayerSystemGC2GMReqDeleteRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPlayerSystemGC2GMReqGetRoleData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPlayerSystemGC2GMReqGetVipLevelGift(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPlayerSystemGC2GMReqVipLevelGiftStatus(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

    void _onMsgPlayerSystemGC2GMReqUpdateSkillPoint(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPlayerSystemGC2GMReqRoleQuit(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

    void _onMsgPlayerSystemCN2GMAckSelectRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgPlayerSystemCN2GMAckInitPlayerData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgPlayerSystemCN2GMAckRoleQuit(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPlayerSystemCN2GMAckCreateRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPlayerSystemCN2GMAckGetRoleData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

    void _onMsgPlayerSystemGC2GMReqGetVitality(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPlayerSystemGC2GMReqBuyVitality(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPlayerSystemGC2GMReqBuyVitalityDiamond(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgPlayerSystemGC2GMReqPurchaseGold(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgPlayerSystemGC2GMReqGetPurchaseGoldInfo(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgPlayerSystemDB2CMNtfChargeList(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);


private:
    bool _deleteRole(RoleIndex a_roleIndex,CMsgPlayerSystemGM2GCAckDeleteRole& a_ack);
    bool _deleteRole(RoleIndex a_roleIndex);
	
public:
	bool cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID,  EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	bool cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID,  EModuleType a_moduleType, BSLib::uint32 a_sessionID);

    bool cbSelectGlobalKeyTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID,  EModuleType a_moduleType, BSLib::uint32 a_sessionID);
    bool cbSelectGlobalKeyIndexTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID,  EModuleType a_moduleType, BSLib::uint32 a_sessionID);
    bool cbSelectGlobalMultiTableData(const GSLib::SRoleKey& a_srcRoleKey,EModuleType a_srcModuleType,  BSLib::uint32 a_sessionID,void* a_ptr,BSLib::uint32 a_state,std::vector<GSLib::DBSystem::SSelectTablesResult>& a_ackSelectTablesResultArray,std::vector<GSLib::DBSystem::CKeyTablePtr>& a_keyTablePtrArray,std::vector<GSLib::DBSystem::CKeyIndexTablePtr>& a_keyIndexTablePtrArray);

private:
	bool _cbKeyTableInitPlayerData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, BSLib::uint32 a_sessionID);
	bool _cbKeyIndexTableInitRoleData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, BSLib::uint32 a_sessionID);
	
	bool _cbTableInitPlayerFinish(const GSLib::SRoleKey& a_roleKey);
	bool _cbTableInitRoleFinish(const GSLib::SRoleKey& a_roleKey, BSLib::uint32 a_sessionID);
	bool _cbTableInitRoleEnd();

	bool _cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID,  EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	bool _cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID,  EModuleType a_moduleType, BSLib::uint32 a_sessionID);

    bool _cbSelectGlobalRoleNameKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, BSLib::uint32 a_sessionID);

private:
    void _updateRoleNameDataToDB();
    bool _createRole(GSLib::DBSystem::CKeyTablePtr& a_keyTable);
	bool _createRole(const std::string& a_roleName,BSLib::int32 a_roleType,RoleID a_roleID, RoleIndex& a_roleIndex);
    void _cbCreateRoleResult(ECreateRoleResult a_result,CRoleGM* a_role = NULL);

    bool _sendMsgCreateRoleToCenterServer(const CRoleGM& a_role);

	void _removeAllRole();
	void _removeRole(RoleIndex a_RoleIndex);

private:
    void _setPlayerStatus(EPlayerStatus a_playerStatus) { m_playerStatus = a_playerStatus; }
	void _setCurRoleIndex(RoleIndex a_curRoleIndex){ m_curRoleIndex = a_curRoleIndex; }
    void _setMaxRoleIndex(BSLib::uint32 a_maxRoleIndex){ m_maxRoleIndex = a_maxRoleIndex; }
    void _setVipScore(BSLib::uint32 a_vipScore){ m_vipScore = a_vipScore; }

    bool _getNewRoleIndex(RoleIndex& a_newRoleIndex) const;

    RoleIndex _getMaxRoleIndex() const { return m_maxRoleIndex; }
    RoleIndex _getCurRoleIndex() const { return m_curRoleIndex;}

	BSLib::uint32 _getSceneTypeID() const { return PLAYERSYSTEM_DEFAULT_SCENE_TYPEID;}
	BSLib::uint32 _getVipScore() const { return m_vipScore;}

private:
	CRoleBagModuleGM * getItemPackage();

    void _getRoleList(BSLib::Utility::CStream& a_stream) const;

	bool _addRole(CRoleGM* a_role);
    bool _setRole(RoleIndex a_roleIndex,CRoleGM* a_role);

private:
	EPlayerStatus m_playerStatus; 
	GSLib::EntityID m_entityID;
	RoleIndex m_curRoleIndex;
    RoleIndex m_maxRoleIndex;
	BSLib::uint32 m_vipScore;
	BSLib::Utility::CHashMap<RoleIndex, CRoleGM*> m_roleHashMap;

    DB::SRoleNameData m_roleNameData;
    BSLib::uint32 m_newRoleTPID;
};

}//GM

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GM_PLAYERSYSTEMGM_H__
