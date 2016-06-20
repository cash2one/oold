//////////////////////////////////////////////////////////////////////
//	created:	2014/07/29
//	filename: 	GSLib\playerSystem\CN\role.h
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_CN_ROLE_H__
#define __GSLIB_PLAYERSYSTEM_CN_ROLE_H__
#include <GSLib/baseDef.h>
#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>

#include <GSLib/playerSystem/CN/roleModuleCN.h>
namespace GSLib
{

namespace PlayerSystem
{

namespace CN
{
// 角色状态
typedef enum
{
	STATUS_NULL = 0,     // 未知
	STATUS_ACTIVE = 1,  // 激活
	STATUS_INACTIVE = 2,   // 未激活
	STATUS_LOADING = 3,	 // 正在加载数据
}ERoleStatus;

class CPlayerCN;
class CRoleCN
{
public:
	CRoleCN(CPlayerCN* a_playerCN);
	CRoleCN(const GSLib::SRoleKey& a_roleKey, CPlayerCN* a_playerCN,BSLib::uint32 a_TPID,std::string a_roldName);
	virtual ~CRoleCN();

	void init(bool isFirst = false);
	void preInit(bool isFirst = false);
	void postInit(bool isFirst = false);

	void initToClient();
	void final();

	void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	void updateDataToDB();

	bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);

public:
	CPlayerCN* getPlayerCN() { return m_playerCN; }	

	// 常用属性获取
public:
	RoleIndex getRoleIndex() const { return m_roleKey.getIndex(); }
	GFLib::ZoneID getZoneID() const { return m_roleKey.getZoneID(); }
	GFLib::AccountID getAccountID() const { return m_roleKey.getAccountID(); }
	const GFLib::SAccountKey& getAccountKey() const { return m_roleKey.getAccountKey(); }
	const GSLib::SRoleKey& getRoleKey() const { return m_roleKey; }

	std::string  getName() const { return m_roleName;}
	bool isActive() const;
	void setRoleStatus(ERoleStatus a_roleStatus);
	
	void setLevel(BSLib::uint32 a_level){ m_level = a_level; }
	void setCombat(BSLib::uint32 a_combat){ m_combat = a_combat; }

public:
	void onRoleActive();
	void onRoleInactive();

	void cbPlayerOnline();
	void cbPlayerOffline();
    CRoleModuleCN* getPlayerModuleCN(EModuleType a_moduleType);

private:
	void _initRoleData(bool isFirst = false);

	// 模块操作
private:
	void _onRoleActive();
	void _onRoleInactive();

	void _preInitModule(bool isFirst = false);
	void _postInitModule(bool isFirst = false);
	void _initToClient();
	void _finalModule();

	void _initModuleMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	void _freeModuleMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	void _updateModuleDataToDB();

	bool _cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	bool _cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);

private:
	CPlayerCN* m_playerCN;
	std::vector<CRoleModuleCN*> m_playerModuleList;
	GSLib::SRoleKey m_roleKey;
	ERoleStatus m_roleStatus;
	std::string m_roleName;
	BSLib::uint32 m_TPID;
	BSLib::uint32 m_level;
	BSLib::uint32 m_combat;
};

}//CN

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_CN_ROLE_H__
