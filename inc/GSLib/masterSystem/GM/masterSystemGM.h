
#ifndef __GSLIB_MASTERSYSTEM_GM_MASTERSYSTEMGM_H__
#define __GSLIB_MASTERSYSTEM_GM_MASTERSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbSystem/keyTable.h>
#include <BSLib/database/dbTableRow.h>
#include <GSLib/masterSystem/msgMasterSystem.h>
#include <GSLib/dbSystem/keyTable.h>
#include <GSLib/dbSystem/keyIndexTable.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/dbSystem/LG/dbSystemLG.h>

namespace GSLib
{

namespace MasterSystem
{

namespace GM
{

enum TaskType
{	
	eAccountTask,
	eAccountPwd,
	eAccountForbid,
};
struct Task
{
	BSLib::uint32  id;
	TaskType	type;
	BSLib::uint32 stubId;
};

struct AccountTask
	:public Task
{
	GSLib::DBSystem::LG::SAccountData  accountData;
	std::vector<GSLib::PlayerSystem::DB::SRoleData> roles;
};

struct AccountPwd
	:public Task
{
	GSLib::DBSystem::LG::SAccountData  accountData;
	DBSystem::CKeyTablePtr accountPtr;
	std::string accountName;
	std::string newPwd;
};

struct AccountForbid
	:public Task
{
	GSLib::DBSystem::LG::SAccountData  accountData;
	DBSystem::CKeyTablePtr accountPtr;
	std::string accountName;
	BSLib::uint32 newState;
};

class CMasterSystemGM : public GSLib::DBSystem::CDBCommonSystem
	, BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
{
public:
	CMasterSystemGM();
	virtual ~CMasterSystemGM();

	BSLIB_SINGLETON_DECLARE(CMasterSystemGM);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_MASTERSYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

public:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonServer_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);


	virtual bool _cbSelectGlobalKeyTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, DBSystem::CKeyTablePtr& a_keyTable,
		EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	virtual bool _cbSelectGlobalKeyIndexTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, DBSystem::CKeyIndexTablePtr& a_keyTable,
		EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
private:
	virtual bool	exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);
	BSLib::uint32	nextCount();
	void			_onAccountTask(BSLib::uint32 a_id, bool success);
	void			_onAccountPwd(BSLib::uint32 a_id, bool success);
	void			_onAccountForbid(BSLib::uint32 a_id, bool success);
	void			_onAccountTaskExec1(AccountTask * task, const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);
	void			_onAccountTaskExec2(AccountTask * task, const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);
	void			_onAccountPwdExec(AccountPwd * task, const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);
	void			_onAccountForbidExec(AccountForbid * task, const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);
	Task*			_getTask(BSLib::uint32 a_id);

private:
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqAccountSearch);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqAccountPwd);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqAccountForbid);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqBroadcast);

private:
	std::string m_cnKey;
	std::map<BSLib::uint32, Task* > m_taskMap;
	BSLib::uint32 m_count;
	BSLib::uint32 m_curSession;
	EDBTableID	m_tableID;
};

}//GM

}

}//GSLib

#endif
