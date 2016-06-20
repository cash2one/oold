#ifndef msgFriendSystemCN_h__
#define msgFriendSystemCN_h__
#include <GSLib/serverType.h>
#include <GSLib/friendSystem/msgNumIDFriendSystem.h>

namespace GSLib
{

namespace FriendSystem
{
	// 打开界面
	const BSLib::uint32 msgIDFriendSystemGC2CNReqFriendsOpen = 
		GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_GC2CN_REQ_FRIENDS_OPEN);
	class CMsgFriendSystemGC2CNReqFriendsOpen: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemGC2CNReqFriendsOpen() : GFLib::CMessage(msgIDFriendSystemGC2CNReqFriendsOpen)
		{

		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{	
			return true;
		}

	public:

	};
	
	// 添加好友
	const BSLib::uint32 msgIDFriendSystemGC2CNReqFriendsAdd = 
		GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_GC2CN_REQ_FRIENDS_ADD);
	class CMsgFriendSystemGC2CNReqFriendsAdd: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemGC2CNReqFriendsAdd() : GFLib::CMessage(msgIDFriendSystemGC2CNReqFriendsAdd)
		{

		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{	
			std::vector<SRoleKey>::iterator it = m_friends.begin();
			BSLib::uint32 size = 0;
			stream >> size;
			for(BSLib::uint32 i = 0; i < size; i++)
			{
				GFLib::AccountID account = 0;
				GFLib::ZoneID zone = 0;
				GSLib::RoleIndex index = 0;
				stream >> account;
				stream >> zone;
				stream >> index;
				m_friends.push_back(SRoleKey(account, zone, index));
			}
			return true;
		}

	public:
		std::vector<SRoleKey> m_friends;
	};


	// 添加好友 验证返回
	const BSLib::uint32 msgIDFriendSystemGC2CNAckFriendsAddConfirm = 
		GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_GC2CN_ACK_FRIENDS_ADD_CONFIRM);
	class CMsgFriendSystemGC2CNAckFriendsAddConfirm: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemGC2CNAckFriendsAddConfirm() : GFLib::CMessage(msgIDFriendSystemGC2CNAckFriendsAddConfirm)
			,m_type(0)
		{

		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{	
			stream >> m_type;
			BSLib::uint32 size = 0;
			stream >> size;
			for(BSLib::uint32 i = 0; i < size; i++)
			{
				GFLib::AccountID account = 0;
				GFLib::ZoneID zone = 0;
				GSLib::RoleIndex index = 0;
				stream >> account;
				stream >> zone;
				stream >> index;
				m_friends.push_back(SRoleKey(account, zone, index));
			}
			return true;
		}

	public:
		BSLib::uint32 m_type;
		std::vector<SRoleKey> m_friends;
	};

	// 删除好友
	const BSLib::uint32 msgIDFriendSystemGC2CNReqFriendsDel = 
		GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_GC2CN_REQ_FRIENDS_DEL);
	class CMsgFriendSystemGC2CNReqFriendsDel: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemGC2CNReqFriendsDel() : GFLib::CMessage(msgIDFriendSystemGC2CNReqFriendsDel)
		{

		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{	
			std::vector<SRoleKey>::iterator it = m_friends.begin();
			BSLib::uint32 size = 0;
			stream >> size;
			for(BSLib::uint32 i = 0; i < size; i++)
			{
				GFLib::AccountID account = 0;
				GFLib::ZoneID zone = 0;
				GSLib::RoleIndex index = 0;
				stream >> account;
				stream >> zone;
				stream >> index;
				m_friends.push_back(SRoleKey(account, zone, index));
			}
			return true;
		}

	public:
		std::vector<SRoleKey> m_friends;
	};

	// 请求推荐的好友
	const BSLib::uint32 msgIDFriendSystemGC2CNReqFriendsNewStrangers = 
		GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_GC2CN_REQ_FRIENDS_NEW_STRANGERS);
	class CMsgFriendSystemGC2CNReqFriendsNewStrangers: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemGC2CNReqFriendsNewStrangers() : GFLib::CMessage(msgIDFriendSystemGC2CNReqFriendsNewStrangers)
		{

		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{	
			return true;
		}

	public:
	};

	// 搜索好友
	const BSLib::uint32 msgIDFriendSystemGC2CNReqFriendsSearch = 
		GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_GC2CN_REQ_FRIENDS_SEARCH);
	class CMsgFriendSystemGC2CNReqFriendsSearch: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemGC2CNReqFriendsSearch() : GFLib::CMessage(msgIDFriendSystemGC2CNReqFriendsSearch)
			,m_type(0)
		{

		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{	
			stream >> m_type;
			stream >> m_buff;
			return true;
		}

	public:
		BSLib::uint32 m_type; // 0:昵称搜索 1:id搜索
		std::string  m_buff;
	};

	// 扩充好友上限
	const BSLib::uint32 msgIDFriendSystemGM2CNNtfFriendsExtendCapacity = 
		GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_GM2CN_NTF_FRIENDS_EXTEND_CAPACITY);
	class CMsgFriendSystemGM2CNNtfFriendsExtendCapacity: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemGM2CNNtfFriendsExtendCapacity() : GFLib::CMessage(msgIDFriendSystemGM2CNNtfFriendsExtendCapacity)
			,m_size(0)
		{

		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{	
			stream >> m_size;
			return true;
		}

		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << m_size;
			return true;
		}

	public:
		BSLib::uint32 m_size;
	};
}
}

#endif 
