//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	GSLib\playerSystem\CN\CPlayerCN.h
//	author:	     zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_CN_PLAYERCN_H__
#define __GSLIB_PLAYERSYSTEM_CN_PLAYERCN_H__

#include <BSLib/utility/memory/objectMgr.h>
#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/playerSystem/baseDef.h>
#include <GSLib/playerSystem/CN/roleCN.h>
#include <GSLib/loginSystem/CN/netPlayerCN.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace CN
{

// 玩家状态
typedef enum
{
	ESTATUS_NULL = 0,     // 未知
	ESTATUS_OFFLINE = 1,  // 下线
	ESTATUS_ONLINE = 2,   // 在线
}EPlayerStatus;

class CPlayerCN :public GSLib::LoginSystem::CN::CNetPlayerCN
{
public:
	CPlayerCN(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName);
	CPlayerCN(EntityID a_entityID, const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName);
	virtual ~CPlayerCN();

public:
	virtual bool init();
	virtual void final();

protected:
	virtual void _cbInitPlayer();
	virtual void _cbFinalPlayer();

	virtual void _cbPlayerOnline();
	virtual void _cbPlayerOffline();

private:
    void _cbInitMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	void _OnMsgPlayerSystemGM2CNReqCreateRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _OnMsgPlayerSystemGM2CNReqInitPlayerData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _OnMsgPlayerSystemGM2CNReqInitSelectRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _OnMsgPlayerSystemGM2CNReqRoleQuit(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _OnMsgPlayerSystemGM2CNReqGetRoleData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _OnMsgPlayerSystemGM2CNNtfUpdateRoleData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

    bool _createRole(BSLib::Utility::CStream a_stream);
	bool _createRole(const std::string& a_roleName,BSLib::int32 a_roleTPID,RoleIndex a_roleIndex);
	bool setCurRoleIndex(RoleIndex a_curRoleIndex);

public:
	bool cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID,  EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	bool cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID,  EModuleType a_moduleType, BSLib::uint32 a_sessionID);


public:
	void setPlayerID(BSLib::uint64 a_playerID){ m_playerID = a_playerID; }

	virtual EntityID getEntityID() const;
public:
	RoleIndex getCurRoleIndex(){ return m_curRoleIndex; }
	BSLib::uint64 getPlayerID(){ return m_playerID; }

	CRoleCN * getCurRole();
	CRoleCN * getRole(RoleIndex index);

	bool isOnline() const ;

private:
	bool _cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID,  EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	bool _cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID,  EModuleType a_moduleType, BSLib::uint32 a_sessionID);

    bool _cbTableInitRoleFinish(const GSLib::SRoleKey& a_roleKey,BSLib::uint32 a_sessionID);
	bool _cbTableInitRoleEnd();

    void _setCurRoleIndex(RoleIndex a_curRoleIndex) { m_curRoleIndex = a_curRoleIndex; }
    void _setVipLevel(BSLib::uint32 a_vipLevel) { m_vipLevel = a_vipLevel; }
    void _setPlayerStatus(EPlayerStatus a_playerStatus) { m_playerStatus = a_playerStatus; }

    BSLib::uint32 _getSceneTypeID() const { return PLAYERSYSTEM_DEFAULT_SCENE_TYPEID;}
    RoleIndex _getCurRoleIndex() const { return m_curRoleIndex;}

private:
	BSLib::uint64 m_playerID;
    BSLib::uint32 m_vipLevel;
	RoleIndex m_curRoleIndex;
	
	EPlayerStatus m_playerStatus; 
	BSLib::Utility::CHashMap<RoleIndex, CRoleCN*> m_roleHashMap;
};

}//CN

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_CN_PLAYERSYSTEMCN_H__
