#ifndef __GSLIB_FRIENDSYSTEM_CN_ROLEFRIENDMODULECN_H__
#define __GSLIB_FRIENDSYSTEM_CN_ROLEFRIENDMODULECN_H__
#include <GSLib/playerSystem/CN/roleModuleCN.h>
#include <GSLib/dbSystem/keyIndexTable.h>
#include <GSLib/friendSystem/DB/tableFriendDB.h>
#include <GSLib/friendSystem/commhdr.h>

namespace GSLib
{

namespace FriendSystem
{

namespace CN
{
class CRoleFriendModuleCN : public GSLib::PlayerSystem::CN::CRoleModuleCN
	, BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
{
public:
	CRoleFriendModuleCN(GSLib::PlayerSystem::CN::CRoleCN* a_roleCN, EModuleType a_moduleType);
	virtual ~CRoleFriendModuleCN();

	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void init(bool isFirst);
	virtual void initToClient();
	virtual void onRoleActive();
	virtual void onRoleInactive();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void updateDataToDB();
	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);


	void	getMyFriends(std::vector<SRoleKey>& a_roles);
private:
	virtual bool	exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);
	void			_onMsgFriendSystemGC2CNReqFriendsOpen(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void			_onMsgFriendSystemGC2CNReqFriendsAdd(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void			_onMsgFriendSystemGC2CNAckFriendsAddConfirm(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void			_onMsgFriendSystemGC2CNReqFriendsDel(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void			_onMsgFriendSystemGC2CNReqFriendsNewStrangers(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void			_onMsgFriendSystemGC2CNReqFriendsSearch(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void			_onMsgFriendSystemGM2CNNtfFriendsExtendCapacity(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	bool			_dbUpdate();
	
	bool			_firstInit();
	void			_onRoleOnline();
	void			_onCleanOverdueRequest();

	bool			_roleGetState(std::vector<SRoleKey>& a_roles, std::vector<SFriendInfo>& a_states);
	bool			_roleIsOnline(const SRoleKey& a_role);
	FriendResult	_rolePostCheckAddCondition(const SRoleKey& a_role, const SRoleKey& a_friendRole);
	FriendResult	_rolePreCheckAddCondition(const SRoleKey& a_role, const SRoleKey& a_friendRole);
	CRoleFriendModuleCN*
					_roleGet(const SRoleKey& a_role);
	BSLib::uint32	_roleGetLeftSpace(const SRoleKey& a_role);
	bool			_roleAddFriend(const SRoleKey& a_role, const SRoleKey& a_friendRole);
	bool			_roleDelFriend(const SRoleKey& a_role, const SRoleKey& a_friendRole);
	bool			_roleAddRequestFriend(const SRoleKey& a_role, const SRoleKey& a_friendRole);
	bool			_roleDelRequestFriend(const SRoleKey& a_role, const SRoleKey& a_friendRole);
	bool			_roleIsAStranger(const std::string& a_role);

	bool			_sendAddConfirmMsg(const SRoleKey& a_role);

	bool			_sendFriendChangeToGM(BSLib::uint32 a_type, const SRoleKey& a_role);
	void			_replyResult(const SRoleKey& a_frindRole, FriendResult a_fr);

private:
	DB::SRoleFriendData		m_myfriend; 
	DBSystem::CKeyTablePtr	m_dbPtr;
};

} // CN


}

}



#endif
