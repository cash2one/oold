#ifndef __GSLIB_FRIENDSYSTEM_COMMHDR_H__
#define __GSLIB_FRIENDSYSTEM_COMMHDR_H__
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace FriendSystem
{

#define  FRIEND_LIST_MAX_SIZE		120
#define  FRIEND_REQUEST_MAX_SIZE	50
// 1天后过期
#define  FRIEND_REQUEST_OVERDUE		(24 * 60 *60)
// 推荐
#define  FRIEND_RECOMMAND_SIZE		10

enum FriendResult
{	
	eFriendResultOK,				// 没问题,可以向下执行, 不需返回提示

	// 条件不满足
	eFriendResultNotExisted,		// 玩家不存在
	eFriendResultIsMyFriend,		// 已经是好友
	eFriendResultMaxReq,			// 好友请求已达上限(我的,还是他的, 通过role id判断)
	eFriendResultMaxFriend,			// 好友已满
	
	// 状态返回
	eFriendResultReqSended,			// 你的请求发送成功(对方离线)
	eFriendResultReqReceived,		// 对方收到了好友申请信息(对方在线)
	eFriendResultFriended,			// 对方通过了好友申请
	efriendResultSuccess,			// 添加好友成功
};

struct  SFriendShortInfo
{	
	SFriendShortInfo()
	:m_role(0, 0, 0)
	{
	}
	
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_role.getAccountID();
		stream << m_role.getZoneID();
		stream << m_role.getIndex();
		stream << m_name;
		return true;
	}
	
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		GFLib::AccountID account = 0;
		GFLib::ZoneID zone = 0;
		GSLib::RoleIndex index = 0;
		stream >> account;
		stream >> zone;
		stream >> index;
		m_role.setAccountID(account);
		m_role.setZoneID(zone);
		m_role.setIndex(index);
		stream >> m_name;
		return true;
	}

	SRoleKey		m_role;
	std::string		m_name;
};

struct  SFriendInfo 
	:public SFriendShortInfo
{	
	SFriendInfo()
		:m_state(0)
		,m_job(1)
		,m_level(1)
		,m_power(1)
		,m_positon(0)
		,m_vip(0)
		,m_roleID(0)
	{
	}

	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{	
		SFriendShortInfo::_serializeTo(stream);
		stream << m_state;
		stream << m_job;
		stream << m_level;
		stream << m_power;
		stream << m_positon;
		stream << m_vip;
		stream << m_roleID;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{	
		SFriendShortInfo::_serializeFrom(stream);
		stream >> m_state;
		stream >> m_job;
		stream >> m_level;
		stream >> m_power;
		stream >> m_positon;
		stream >> m_vip;
		stream >> m_roleID;
		return true;
	}


	BSLib::uint32	m_state;	// 0 offline, 1 online
	BSLib::uint32	m_job;		// 1 , 2, 3
	BSLib::uint32	m_level;
	BSLib::uint32	m_power;
	BSLib::uint32	m_positon;
	BSLib::uint32	m_vip;
	BSLib::uint64	m_roleID;
};

} // FriendSystem

} // GSLib


#endif