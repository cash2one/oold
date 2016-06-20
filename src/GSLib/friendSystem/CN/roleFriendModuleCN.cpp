#include <GSLib/friendSystem/CN/roleFriendModuleCN.h>
#include <GSLib/friendSystem/CN/msgFriendSystemCN.h>
#include <GSLib/playerSystem/CN/playerCN.h>
#include <GSLib/friendSystem/CN/friendSystemCN.h>
#include <GSLib/friendSystem/GM/msgFriendSystemGM.h>
#include <GSLib/friendSystem/msgFriendSystem.h>
#include <GSLib/tracer.h>
#include <GSLib/friendSystem/GM/friendSystemGM.h>
#include <GSLib/playerSystem/CN/roleCN.h>
#include <algorithm>
#include <GSLib/playerSystem/CN/playerCNMgr.h>
#include <GSLib/playerSystem/CN/roleBaseInfoCNMgr.h>
#include <BSLib/utility/convert.h>

namespace GSLib
{
namespace FriendSystem
{

namespace CN
{

CRoleFriendModuleCN::CRoleFriendModuleCN(GSLib::PlayerSystem::CN::CRoleCN* a_roleCN, EModuleType a_moduleType)
	:GSLib::PlayerSystem::CN::CRoleModuleCN(a_roleCN, a_moduleType)
{

}

CRoleFriendModuleCN::~CRoleFriendModuleCN()
{

}

void CRoleFriendModuleCN::preInit(bool isFirst)
{
}

void CRoleFriendModuleCN::postInit(bool isFirst)
{
	if(isFirst)
	{
		_firstInit();
	}
}

void CRoleFriendModuleCN::initToClient()
{	
	CFriendSystemCN::singleton().onRoleOnline(m_myfriend.m_role.getDBKey());
	_onRoleOnline();
}

void CRoleFriendModuleCN::onRoleActive()
{
	
}

void CRoleFriendModuleCN::onRoleInactive()
{
	CFriendSystemCN::singleton().onRoleOffline(m_myfriend.m_role.getDBKey());
}

void CRoleFriendModuleCN::init(bool isFirst)
{
}

void CRoleFriendModuleCN::final()
{

}

void CRoleFriendModuleCN::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDFriendSystemGC2CNReqFriendsOpen, 
		&BSLib::Framework::CreateCMessage<CMsgFriendSystemGC2CNReqFriendsOpen>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDFriendSystemGC2CNReqFriendsOpen, &CRoleFriendModuleCN::_onMsgFriendSystemGC2CNReqFriendsOpen, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDFriendSystemGC2CNReqFriendsAdd, 
		&BSLib::Framework::CreateCMessage<CMsgFriendSystemGC2CNReqFriendsAdd>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDFriendSystemGC2CNReqFriendsAdd, &CRoleFriendModuleCN::_onMsgFriendSystemGC2CNReqFriendsAdd, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDFriendSystemGC2CNAckFriendsAddConfirm, 
		&BSLib::Framework::CreateCMessage<CMsgFriendSystemGC2CNAckFriendsAddConfirm>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDFriendSystemGC2CNAckFriendsAddConfirm, &CRoleFriendModuleCN::_onMsgFriendSystemGC2CNAckFriendsAddConfirm, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDFriendSystemGC2CNReqFriendsDel, 
		&BSLib::Framework::CreateCMessage<CMsgFriendSystemGC2CNReqFriendsDel>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDFriendSystemGC2CNReqFriendsDel, &CRoleFriendModuleCN::_onMsgFriendSystemGC2CNReqFriendsDel, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDFriendSystemGC2CNReqFriendsNewStrangers, 
		&BSLib::Framework::CreateCMessage<CMsgFriendSystemGC2CNReqFriendsNewStrangers>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDFriendSystemGC2CNReqFriendsNewStrangers, &CRoleFriendModuleCN::_onMsgFriendSystemGC2CNReqFriendsNewStrangers, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDFriendSystemGC2CNReqFriendsSearch, 
		&BSLib::Framework::CreateCMessage<CMsgFriendSystemGC2CNReqFriendsSearch>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDFriendSystemGC2CNReqFriendsSearch, &CRoleFriendModuleCN::_onMsgFriendSystemGC2CNReqFriendsSearch, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDFriendSystemGM2CNNtfFriendsExtendCapacity, 
		&BSLib::Framework::CreateCMessage<CMsgFriendSystemGM2CNNtfFriendsExtendCapacity>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDFriendSystemGM2CNNtfFriendsExtendCapacity, &CRoleFriendModuleCN::_onMsgFriendSystemGM2CNNtfFriendsExtendCapacity, this);

}

void CRoleFriendModuleCN::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(msgIDFriendSystemGC2CNReqFriendsOpen);
	a_msgExecMgr->delMsgExecPtr(msgIDFriendSystemGC2CNReqFriendsAdd);
	a_msgExecMgr->delMsgExecPtr(msgIDFriendSystemGC2CNAckFriendsAddConfirm);
	a_msgExecMgr->delMsgExecPtr(msgIDFriendSystemGC2CNReqFriendsDel);
	a_msgExecMgr->delMsgExecPtr(msgIDFriendSystemGC2CNReqFriendsNewStrangers);
	a_msgExecMgr->delMsgExecPtr(msgIDFriendSystemGC2CNReqFriendsSearch);
	a_msgExecMgr->delMsgExecPtr(msgIDFriendSystemGM2CNNtfFriendsExtendCapacity);
}

void CRoleFriendModuleCN::updateDataToDB()
{

}

void CRoleFriendModuleCN::_onMsgFriendSystemGC2CNReqFriendsOpen(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	//CMsgFriendSystemGC2CNReqFriendsOpen *req = (CMsgFriendSystemGC2CNReqFriendsOpen *)a_msg;

	CMsgFriendSystemCN2GCAckFriendsOpen ack;
	_roleGetState(m_myfriend.m_friends, ack.m_friends);
	ack.m_capacity = FRIEND_LIST_MAX_SIZE + m_myfriend.m_paidCount;
	sendMsgToClient(ack);
}

bool CRoleFriendModuleCN::_sendFriendChangeToGM(BSLib::uint32 a_type, const SRoleKey& a_role)
{
	CMsgFriendSystemCN2GMNtfFriendsChange ntf;
	ntf.m_changeType = a_type;
	ntf.m_changes.push_back(a_role);
	return sendMsgToGameServer(ntf);
}

void CRoleFriendModuleCN::_replyResult(const SRoleKey& a_frindRole, FriendResult a_fr)
{
	CMsgFriendSystemCN2GCNtfFriendsAddResult ack;
	std::vector<SRoleKey> roles;
	roles.push_back(a_frindRole);
	std::vector<SFriendInfo> info;
	_roleGetState(roles, info);
	if( 0 == info.size())
		return;

	ack.addFriendInfo(info[0], a_fr);
	sendMsgToClient(ack);
}

bool CRoleFriendModuleCN::_sendAddConfirmMsg(const SRoleKey& a_role)
{	
	CMsgFriendSystemCN2GCReqFriendsAddConfirm ack;
	std::vector<SFriendInfo> InfoVec;
	std::vector<SRoleKey> roleVec;
	roleVec.push_back(a_role);
	if(!_roleGetState(roleVec, InfoVec))
	{
		return false;
	}
	
	if( 1 != InfoVec.size())
	{
		return false;
	}

	ack.addFriendShortInfo(InfoVec[0]);
	return sendMsgToClient(ack);
}

CRoleFriendModuleCN*
CRoleFriendModuleCN::_roleGet(const SRoleKey& a_role)
{
	if(m_myfriend.m_role == a_role)
		return this;
	
	using namespace PlayerSystem::CN;
	CRoleCN* role = CPlayerCNMgr::singleton().getRoleCN(a_role);
	if(NULL == role)
		return NULL;

	CRoleFriendModuleCN* m = (CRoleFriendModuleCN *)role->getPlayerModuleCN(EMODULETYPE_FRIEND);
	return m;
}

FriendResult CRoleFriendModuleCN::_rolePreCheckAddCondition(const SRoleKey& a_role, const SRoleKey& a_friendRole)
{
	// 不合适的条件
	// 1. 已满
	// 2. 已存在
	CRoleFriendModuleCN * role = _roleGet(a_role);
	if(NULL == role)
		return eFriendResultNotExisted;

// 	if(FRIEND_LIST_MAX_SIZE + role->m_myfriend.m_paidCount == role->m_myfriend.m_friends.size())
// 	{
// 		return eFriendResultMaxFriend;
// 	}

	if(FRIEND_REQUEST_MAX_SIZE == role->m_myfriend.m_requests.size())
	{
		return eFriendResultMaxReq;
	}
	
	std::vector<SRoleKey>::iterator it = std::find(role->m_myfriend.m_requests.begin(), role->m_myfriend.m_requests.end(), a_friendRole);
	if( it != role->m_myfriend.m_requests.end())
		return eFriendResultOK;

	it = std::find(role->m_myfriend.m_friends.begin(), role->m_myfriend.m_friends.end(), a_friendRole);
	
	if( it != role->m_myfriend.m_friends.end())
		return eFriendResultIsMyFriend;

	return eFriendResultOK;
}

FriendResult CRoleFriendModuleCN::_rolePostCheckAddCondition(const SRoleKey& a_role, const SRoleKey& a_friendRole)
{	
	// 不合适的条件
	// 1. 已满
	// 2. 已存在
	CRoleFriendModuleCN * role = _roleGet(a_role);
	if(NULL == role)
		return eFriendResultNotExisted;

	if(FRIEND_LIST_MAX_SIZE + role->m_myfriend.m_paidCount == role->m_myfriend.m_friends.size())
	{
		return eFriendResultMaxFriend;
	}

	std::vector<SRoleKey>::iterator it =  
		std::find(role->m_myfriend.m_friends.begin(), role->m_myfriend.m_friends.end(), a_friendRole);
	if(it != role->m_myfriend.m_friends.end())
		return eFriendResultIsMyFriend;

	return eFriendResultOK;
}

BSLib::uint32 CRoleFriendModuleCN::_roleGetLeftSpace(const SRoleKey& a_role)
{
	CRoleFriendModuleCN * role = _roleGet(a_role);
	if(NULL == role)
		return 0;
	
	return FRIEND_LIST_MAX_SIZE + role->m_myfriend.m_paidCount - role->m_myfriend.m_friends.size();
}

bool CRoleFriendModuleCN::_roleAddFriend(const SRoleKey& a_role, const SRoleKey& a_friendRole)
{
	CRoleFriendModuleCN * role = _roleGet(a_role);
	if(NULL == role)
		return false;
	
	role->_sendFriendChangeToGM(1, a_friendRole);
	role->m_myfriend.m_friends.push_back(a_friendRole);
	return role->_dbUpdate();
}

bool CRoleFriendModuleCN::_roleAddRequestFriend(const SRoleKey& a_role, const SRoleKey& a_friendRole)
{
	CRoleFriendModuleCN * role = _roleGet(a_role);
	if(NULL == role)
		return false;
	
	std::vector<SRoleKey>::iterator it = std::find(role->m_myfriend.m_requests.begin(), role->m_myfriend.m_requests.end(), a_friendRole);
	if( it != role->m_myfriend.m_requests.end())
		return false;

	role->m_myfriend.m_requests.push_back(a_friendRole);
	BSLib::Utility::CDateTime now = BSLib::Utility::CDateTime::getCurrentTime();
	role->m_myfriend.m_requestTimes.push_back(now.getSeconds());
	return role->_dbUpdate();
}

bool CRoleFriendModuleCN::_roleDelFriend(const SRoleKey& a_role, const SRoleKey& a_friendRole)
{
	CRoleFriendModuleCN * role = _roleGet(a_role);
	if(NULL == role)
		return false;

	std::vector<SRoleKey>::iterator it = std::find(role->m_myfriend.m_friends.begin(), role->m_myfriend.m_friends.end(), a_friendRole);
	if( it == role->m_myfriend.m_friends.end())
		return false;
	
	role->_sendFriendChangeToGM(2, a_friendRole);
	role->m_myfriend.m_friends.erase(it);
	return role->_dbUpdate();
}

void CRoleFriendModuleCN::_onCleanOverdueRequest()
{
	BSLib::Utility::CDateTime now = BSLib::Utility::CDateTime::getCurrentTime();
	BSLib::uint64 now_s = now.getSeconds();
	std::vector<SRoleKey> tobeDel;

	std::vector<SRoleKey>::iterator it = m_myfriend.m_requests.begin();
	std::vector<BSLib::uint64>::iterator time_it = m_myfriend.m_requestTimes.begin();
	for(; it != m_myfriend.m_requests.end() && time_it != m_myfriend.m_requestTimes.end(); ++it, ++time_it)
	{
		if(now_s - *time_it >= FRIEND_REQUEST_OVERDUE)
		{
			tobeDel.push_back(*it);
		}
	}

	// 清除已是好友的请求
	for(it = m_myfriend.m_requests.begin(); it != m_myfriend.m_requests.end(); ++it)
	{
		std::vector<SRoleKey>::iterator findIt = std::find(m_myfriend.m_friends.begin(), m_myfriend.m_friends.end(), *it);
		if(findIt != m_myfriend.m_friends.end())
			tobeDel.push_back(*it);
	}


	for(std::vector<SRoleKey>::iterator del_it = tobeDel.begin(); del_it != tobeDel.end(); ++del_it)
	{
		_roleDelRequestFriend(m_myfriend.m_role, *del_it);
	}
}

bool CRoleFriendModuleCN::_roleIsAStranger(const std::string& a_role)
{	
	for(std::vector<SRoleKey>::iterator it = m_myfriend.m_friends.begin();
		it != m_myfriend.m_friends.end(); ++it)
	{
		if( a_role == (*it).getDBKey())
			return false;
	}
	
	return true;
}

bool CRoleFriendModuleCN::_roleDelRequestFriend(const SRoleKey& a_role, const SRoleKey& a_friendRole)
{
	CRoleFriendModuleCN * role = _roleGet(a_role);
	if(NULL == role)
		return false;

	std::vector<SRoleKey>::iterator it = role->m_myfriend.m_requests.begin();
	std::vector<BSLib::uint64>::iterator time_it = role->m_myfriend.m_requestTimes.begin();
	for(; it != role->m_myfriend.m_requests.end() && time_it != role->m_myfriend.m_requestTimes.end(); ++it, ++time_it)
	{
		if( *it == a_friendRole)
		{
			role->m_myfriend.m_requests.erase(it);
			role->m_myfriend.m_requestTimes.erase(time_it);
			break;
		}
	}

	return role->_dbUpdate();
}

void CRoleFriendModuleCN::_onMsgFriendSystemGC2CNReqFriendsAdd(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	

	CMsgFriendSystemGC2CNReqFriendsAdd *req = (CMsgFriendSystemGC2CNReqFriendsAdd *)a_msg;
	for(BSLib::uint32 i = 0; i < req->m_friends.size(); i++)
	{	

		if(m_myfriend.m_role == req->m_friends[i])
			continue;

		FriendResult fr = _rolePreCheckAddCondition(m_myfriend.m_role, req->m_friends[i]);
		if( eFriendResultOK != fr)
		{	
			//返回消息, 好友的条件不符
			_replyResult(m_myfriend.m_role, fr);
			continue;
		}

		if(_roleIsOnline(req->m_friends[i]))
		{	
			fr = _rolePreCheckAddCondition(req->m_friends[i], m_myfriend.m_role);
			if(eFriendResultOK == fr)
			{	
				CRoleFriendModuleCN* other = _roleGet(req->m_friends[i]);
				if(NULL != other)
				{	
					if(other->_roleAddRequestFriend(other->m_myfriend.m_role, m_myfriend.m_role))
					{
						other->_sendAddConfirmMsg(m_myfriend.m_role);
						CFriendSystemCN::singleton().createAndUpdateQueue(m_myfriend.m_role, _roleGetLeftSpace(m_myfriend.m_role));
					}
					
					// 返回消息
					_replyResult(req->m_friends[i], eFriendResultReqReceived);
				}
			}
			else
			{
				_replyResult(req->m_friends[i], fr);
			}
		}
		else
		{	
			if(CFriendSystemCN::singleton().checkNewFriendConditon(req->m_friends[i], m_myfriend.m_role))
			{
				 CFriendSystemCN::singleton().createAndUpdateQueue(m_myfriend.m_role, _roleGetLeftSpace(m_myfriend.m_role));
				 CFriendSystemCN::singleton().newFriendRequest(req->m_friends[i], m_myfriend.m_role);
			}

			// 返回消息
			_replyResult(req->m_friends[i], eFriendResultReqSended);
		}
		
	}
}

void CRoleFriendModuleCN::_onMsgFriendSystemGC2CNAckFriendsAddConfirm(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgFriendSystemGC2CNAckFriendsAddConfirm *req = (CMsgFriendSystemGC2CNAckFriendsAddConfirm *)a_msg;
	
	// 拒绝
	if( 2 == req->m_type)
	{
		for(BSLib::uint32 i = 0; i < req->m_friends.size(); i++)
		{
			_roleDelRequestFriend(m_myfriend.m_role, req->m_friends[i]);
		}
	
		return;
	}
	
	// 同意
	for(BSLib::uint32 i = 0; i < req->m_friends.size(); i++)
	{	
		FriendResult myRes = _rolePostCheckAddCondition(m_myfriend.m_role, req->m_friends[i]);
		if( eFriendResultOK != myRes)
		{
			_replyResult(m_myfriend.m_role, myRes);
			continue;
		}

		if(_roleIsOnline(req->m_friends[i]))
		{ // 在线	
			CRoleFriendModuleCN* myFriend = _roleGet(req->m_friends[i]);
			FriendResult friendRes = _rolePostCheckAddCondition(req->m_friends[i], m_myfriend.m_role);
			
			if( eFriendResultOK != friendRes)
			{
				_replyResult(req->m_friends[i], friendRes);
				continue;
			}

			_roleAddFriend(m_myfriend.m_role, req->m_friends[i]);
			_roleAddFriend(req->m_friends[i], m_myfriend.m_role);

			CFriendSystemCN::singleton().tryToUpdateQueue(m_myfriend.m_role, _roleGetLeftSpace(m_myfriend.m_role));
			CFriendSystemCN::singleton().tryToUpdateQueue(req->m_friends[i], _roleGetLeftSpace(req->m_friends[i]));

			// 通知对方
			myFriend->_replyResult(m_myfriend.m_role, eFriendResultFriended);

			_replyResult(req->m_friends[i], efriendResultSuccess);

			
			// 删除请求
			_roleDelRequestFriend(m_myfriend.m_role, req->m_friends[i]);
		}
		else
		{ // 离线
			if(CFriendSystemCN::singleton().checkNewFriendConfirmConditon(req->m_friends[i], m_myfriend.m_role))
			{
				_roleAddFriend(m_myfriend.m_role, req->m_friends[i]);
				CFriendSystemCN::singleton().tryToUpdateQueue(m_myfriend.m_role, _roleGetLeftSpace(m_myfriend.m_role));
				CFriendSystemCN::singleton().newQuasiFriendRequest(req->m_friends[i], m_myfriend.m_role);
				_replyResult(req->m_friends[i], efriendResultSuccess);
			}
			else
			{
				_replyResult(req->m_friends[i], eFriendResultFriended);
			}
			
			//删除请求
			_roleDelRequestFriend(m_myfriend.m_role, req->m_friends[i]);
		}

		
	}
}


void CRoleFriendModuleCN::_onMsgFriendSystemGC2CNReqFriendsDel(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgFriendSystemGC2CNReqFriendsDel *req = (CMsgFriendSystemGC2CNReqFriendsDel *)a_msg;
	CMsgFriendSystemCN2GCAckFriendsDel ack;
	for(BSLib::uint32 i = 0; i < req->m_friends.size(); i++)
	{	
		bool success = true;
		if(_roleIsOnline(req->m_friends[i]))
		{
			success = _roleDelFriend(m_myfriend.m_role, req->m_friends[i]);
			success = success && _roleDelFriend(req->m_friends[i], m_myfriend.m_role);

			CFriendSystemCN::singleton().tryToUpdateQueue(m_myfriend.m_role, _roleGetLeftSpace(m_myfriend.m_role));
			CFriendSystemCN::singleton().tryToUpdateQueue(req->m_friends[i], _roleGetLeftSpace(req->m_friends[i]));
		}
		else
		{	
			success = _roleDelFriend(m_myfriend.m_role, req->m_friends[i]);
			CFriendSystemCN::singleton().tryToUpdateQueue(m_myfriend.m_role, _roleGetLeftSpace(m_myfriend.m_role));

			CFriendSystemCN::singleton().newUnfriendRequest(req->m_friends[i], m_myfriend.m_role);
		}

		ack.m_friends.push_back(req->m_friends[i]);
	}

	sendMsgToClient(ack);
}

void CRoleFriendModuleCN::_onMsgFriendSystemGC2CNReqFriendsNewStrangers(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	//CMsgFriendSystemGC2CNReqFriendsNewStrangers *req = (CMsgFriendSystemGC2CNReqFriendsNewStrangers *)a_msg;

	CMsgFriendSystemCN2GCAckFriendsNewStrangers ack;
	typedef BSLib::Utility::CHashMap<std::string, BSLib::uint32> KeyHashMap;
	KeyHashMap::iterator self_it = CFriendSystemCN::singleton().m_onlineRoles.find(m_myfriend.m_role.getDBKey());
	do 
	{
		if( self_it ==CFriendSystemCN::singleton().m_onlineRoles.end())
			break;
		
		std::set<std::string> keySet;
		using namespace PlayerSystem::CN;
		KeyHashMap::iterator forward_it = self_it;
		++forward_it;
		for(; forward_it != CFriendSystemCN::singleton().m_onlineRoles.end() 
			&& FRIEND_RECOMMAND_SIZE != keySet.size(); ++forward_it)
		{
			if(!_roleIsAStranger(forward_it->first))
				continue;

			keySet.insert(forward_it->first);
		}

		KeyHashMap::iterator backward_it = CFriendSystemCN::singleton().m_onlineRoles.begin();
		for(; backward_it != CFriendSystemCN::singleton().m_onlineRoles.end()
			&& FRIEND_RECOMMAND_SIZE != keySet.size() && backward_it != self_it; ++backward_it)
		{
			if(!_roleIsAStranger(backward_it->first))
				continue;

			keySet.insert(backward_it->first);
		}


		for(std::set<std::string>::iterator it = keySet.begin();
			it != keySet.end(); ++it)
		{
			CRoleBaseInfoCN * base = CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleKey(*it);
			if(NULL == base)
				continue;

			SFriendInfo info;
			info.m_role = base->getRoleKey();
			info.m_name = base->getRoleName();
			info.m_level = base->getRoleLevel();
			info.m_job = base->getRoleTPID();
			info.m_state = _roleIsOnline(info.m_role) ? 1 : 0;
			info.m_power = base->getCombat();
			info.m_roleID = base->getRoleID();
			ack.addFriend(info);
		}
	
	} while (false);
	sendMsgToClient(ack);
}

void CRoleFriendModuleCN::_onMsgFriendSystemGM2CNNtfFriendsExtendCapacity(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgFriendSystemGM2CNNtfFriendsExtendCapacity * req = (CMsgFriendSystemGM2CNNtfFriendsExtendCapacity *)a_msg;
	m_myfriend.m_paidCount += req->m_size;
	_dbUpdate();
	CFriendSystemCN::singleton().tryToUpdateQueue(m_myfriend.m_role, _roleGetLeftSpace(m_myfriend.m_role));
}

void CRoleFriendModuleCN::_onMsgFriendSystemGC2CNReqFriendsSearch(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgFriendSystemGC2CNReqFriendsSearch *req = (CMsgFriendSystemGC2CNReqFriendsSearch *)a_msg;
	
	CMsgFriendSystemCN2GCAckFriendsSearch ack;
	using namespace PlayerSystem::CN;
	CRoleBaseInfoCN * base = NULL;
	base = CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleName(req->m_buff);
	SFriendInfo info;
	if(NULL != base)
	{	
		info.m_role = base->getRoleKey();
		info.m_name = base->getRoleName();
		info.m_level = base->getRoleLevel();
		info.m_job = base->getRoleTPID();
		info.m_state = _roleIsOnline(info.m_role) ? 1 : 0;
		info.m_power = base->getCombat();
		info.m_roleID = base->getRoleID();
		ack.addFriend(info);
	}
	
	base = CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleID(BSLib::Utility::CConvert::toUint64(req->m_buff));
	if(NULL != base)
	{	
		info.m_role = base->getRoleKey();
		info.m_name = base->getRoleName();
		info.m_level = base->getRoleLevel();
		info.m_job = base->getRoleTPID();
		info.m_state = _roleIsOnline(info.m_role) ? 1 : 0;
		info.m_power = base->getCombat();
		info.m_roleID = base->getRoleID();
		ack.addFriend(info);
	}
	
	sendMsgToClient(ack);
}

bool CRoleFriendModuleCN::_firstInit()
{	
	PlayerSystem::CN::CRoleCN * role = getRoleCN();
	m_myfriend.m_role = role->getRoleKey();
	return _dbUpdate();
}

bool CRoleFriendModuleCN::_roleGetState(std::vector<SRoleKey>& a_roles, std::vector<SFriendInfo>& a_states)
{	
	using namespace PlayerSystem::CN;
	for(BSLib::uint32 i = 0; i < a_roles.size(); i++)
	{	
		CRoleBaseInfoCN * base = 
			CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleKey(a_roles[i].getDBKey());
		SFriendInfo info;
		info.m_role = a_roles[i];
		if(NULL != base)
		{
			info.m_name = base->getRoleName();
			info.m_level = base->getRoleLevel();
			info.m_job = base->getRoleTPID();
			info.m_state = _roleIsOnline(a_roles[i]) ? 1 : 0;
			info.m_power = base->getCombat();
			info.m_vip	= base->getVipLevel();
			info.m_roleID = base->getRoleID();
		}
		a_states.push_back(info);
	}

	return true;
}

bool CRoleFriendModuleCN::_roleIsOnline(const SRoleKey& a_role)
{	
	PlayerSystem::CN::CRoleCN* role = PlayerSystem::CN::CPlayerCNMgr::singleton().getRoleCN(a_role);
	if(NULL == role)
	{
		return false;
	}
	
	return role->isActive();
}

void CRoleFriendModuleCN::_onRoleOnline()
{	
	std::vector<SRoleKey> vec;
	if(CFriendSystemCN::singleton().newUnfriendTotal(m_myfriend.m_role, vec))
	{
		for(BSLib::uint32 i = 0; i < vec.size(); i++)
		{
			_roleDelFriend(m_myfriend.m_role, vec[i]);
			CFriendSystemCN::singleton().delUnfriendRequest(m_myfriend.m_role, vec[i]);
		}
	}

	vec.clear();
	if(CFriendSystemCN::singleton().newQuasFriendTotal(m_myfriend.m_role, vec))
	{
		for(BSLib::uint32 i = 0; i < vec.size(); i++)
		{
			if(eFriendResultOK == _rolePostCheckAddCondition(m_myfriend.m_role, vec[i]))
			{
				_roleAddFriend(m_myfriend.m_role, vec[i]);
			}
			CFriendSystemCN::singleton().delQuasiFriendRequest(m_myfriend.m_role, vec[i]);
		}
	}

	vec.clear();
	if(CFriendSystemCN::singleton().newFriendTotal(m_myfriend.m_role, vec))
	{
		for(BSLib::uint32 i = 0; i < vec.size(); i++)
		{
			if(eFriendResultOK == _rolePreCheckAddCondition(m_myfriend.m_role, vec[i]))
			{
				_roleAddRequestFriend(m_myfriend.m_role, vec[i]);
			}
			CFriendSystemCN::singleton().delFriendRequest(m_myfriend.m_role, vec[i]);
		}
	}

	CFriendSystemCN::singleton().tryToUpdateQueue(m_myfriend.m_role, _roleGetLeftSpace(m_myfriend.m_role));
	
	// 清除过期请求
	_onCleanOverdueRequest();

	// 通知客户端好友请求
	for(std::vector<SRoleKey>::iterator ntf_it = m_myfriend.m_requests.begin();
		ntf_it != m_myfriend.m_requests.end(); ++ntf_it)
	{
		_sendAddConfirmMsg(*ntf_it);
	}
}

bool CRoleFriendModuleCN::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable,
											   EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	if(EDBTABLEID_ROLE_FRIEND_DATA == a_tableID){
		a_keyTable->traversal(*this);
		m_dbPtr = a_keyTable;
		return true;
	}

	return false;
}

bool CRoleFriendModuleCN::_dbUpdate()
{	
	if(m_dbPtr == NULL)
	{
		return false;
	}
	
	BSLib::Utility::CStream stream;
	m_myfriend.serializeTo(stream);
	m_dbPtr->update(stream);
	m_dbPtr->saveDataToDBServer(m_myfriend.getDBKey(), true);
	return true;
}

bool CRoleFriendModuleCN::exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{
	BSLib::Utility::CStream stream;
	a_value->serializeTo(stream);
	return m_myfriend.deserializeFrom(stream);
}

void CRoleFriendModuleCN::getMyFriends(std::vector<SRoleKey>& a_roles)
{
	std::copy(m_myfriend.m_friends.begin(), m_myfriend.m_friends.end(), std::back_inserter(a_roles));
}


} // CN


}
}