
#ifndef __GSLIB_FRIENDSYSTEM_GM_FRIENDSYSTEMGM_H__
#define __GSLIB_FRIENDSYSTEM_GM_FRIENDSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbSystem/keyTable.h>
#include <GSLib/dbSystem/keyIndexTable.h>
#include <BSLib/utility/hashMap.h>
#include <GSLib/friendSystem/DB/tableFriendDB.h>
#include <GSLib/dbSystem/keyTable.h>

namespace GSLib
{

namespace FriendSystem
{

namespace CN
{

class CFriendSystemCN : public GSLib::DBSystem::CDBCommonSystem
	, BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
{
public:
	CFriendSystemCN();
	virtual ~CFriendSystemCN();

	BSLIB_SINGLETON_DECLARE(CFriendSystemCN);

	virtual BSLib::uint16 ICommonSystem_getFuncType() { return GSLib::EFUNCTYPE_FRIENDSYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

public:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _ICommonSystem_startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

public:
	bool		createAndUpdateQueue(const SRoleKey& a_role, BSLib::uint32 a_left);
	bool		tryToUpdateQueue(const SRoleKey& a_role, BSLib::uint32 a_left);
	bool		delQueue(); //todo 以后优化之用

	bool		newFriendRequest(const SRoleKey& a_role, const SRoleKey& a_destRole);
	bool		delFriendRequest(const SRoleKey& a_role, const SRoleKey& a_destRole);
	bool		newFriendTotal(const SRoleKey& a_role, std::vector<SRoleKey>& a_destRoles);
	bool		checkNewFriendConditon(const SRoleKey& a_role, const SRoleKey& a_destRole);
	bool		checkNewFriendConfirmConditon(const SRoleKey& a_role, const SRoleKey& a_destRole);

	bool		newUnfriendRequest(const SRoleKey& a_role, const SRoleKey& a_destRole);
	bool		delUnfriendRequest(const SRoleKey& a_role, const SRoleKey& a_destRole);
	bool		newUnfriendTotal(const SRoleKey& a_role, std::vector<SRoleKey>& a_destRoles);

	bool		newQuasiFriendRequest(const SRoleKey& a_role, const SRoleKey& a_destRole);
	bool		delQuasiFriendRequest(const SRoleKey& a_role, const SRoleKey& a_destRole);
	bool		newQuasFriendTotal(const SRoleKey& a_role, std::vector<SRoleKey>& a_destRoles);
	

	void		onRoleOnline(std::string a_key);
	void		onRoleOffline(std::string a_key);
private:
	virtual bool	exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);
	virtual bool	_cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, DBSystem::CKeyTablePtr& a_keyTable,
											EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	bool			_dbUpdate(DB::SRoleFriendPendingQueueData* a_queue);
	bool			_dbDel(DB::SRoleFriendPendingQueueData* a_queue);
	DB::SRoleFriendPendingQueueData*
					_getData(std::string a_key);
private:
	BSLib::Utility::CHashMap<std::string, DB::SRoleFriendPendingQueueData*> m_friendPendingQueue; 
	DBSystem::CKeyTablePtr m_dbPtr;

public:
	BSLib::Utility::CHashMap<std::string, BSLib::uint32> m_onlineRoles;
};

}//GM

}

}//GSLib

#endif
