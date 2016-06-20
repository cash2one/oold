
#ifndef __GSLIB_FRIENDSYSTEM_MSGFRIENDSYSTEMGM_H__
#define __GSLIB_FRIENDSYSTEM_MSGFRIENDSYSTEMGM_H__

#include <GSLib/friendSystem/msgNumIDFriendSystem.h>

namespace GSLib
{

namespace FriendSystem
{	


	// 请求附近的人
	const BSLib::uint32 msgIDFriendSystemGC2GMReqFriendsLocal = 
		GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_GC2GM_REQ_FRIENDS_LOCAL);
	class CMsgFriendSystemGC2GMReqFriendsLocal: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemGC2GMReqFriendsLocal() : GFLib::CMessage(msgIDFriendSystemGC2GMReqFriendsLocal)
		{

		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{	
			return true;
		}

	public:
	};


	const BSLib::uint32 msgIDFriendSystemCN2GMNtfFriendsChange = 
		GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_CN2GM_NTF_FRIENDS_CHANGE);
	class CMsgFriendSystemCN2GMNtfFriendsChange: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemCN2GMNtfFriendsChange() : GFLib::CMessage(msgIDFriendSystemCN2GMNtfFriendsChange)
		{
			m_changeType = 0;
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{	
			stream >> m_changeType;
			BSLib::uint32 size = 0;
			stream >> size;
			for(BSLib::uint32 i = 0; i < size; i++)
			{
				SRoleKey key;
				key.serializeFrom(stream);
				m_changes.push_back(key);
			}
			return true;
		}

		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	
			std::vector<SRoleKey>::const_iterator it = m_changes.begin();
			BSLib::uint32 size = m_changes.size();
			stream << m_changeType;
			stream << size;
			for(; it != m_changes.end(); ++it)
			{
				it->serializeTo(stream);
			}
			return true;
		}

	public:
		std::vector<SRoleKey> m_changes;
		BSLib::uint32 m_changeType; // 1:新增 , 2:删除
	};
}

}//GSLib

#endif
