
#ifndef __GSLIB_FRIENDSYSTEM_MSGFRIENDSYSTEMGC_H__
#define __GSLIB_FRIENDSYSTEM_MSGFRIENDSYSTEMGC_H__

#include <GSLib/friendSystem/msgNumIDFriendSystem.h>
#include <GSLib/baseDef.h>
#include <GSLib/friendSystem/commhdr.h>

namespace GSLib
{

namespace FriendSystem
{	
	// �򿪽��淵��
	const BSLib::uint32 msgIDFriendSystemCN2GCAckFriendsOpen = 
		GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_CN2GC_ACK_FRIENDS_OPEN);
	class CMsgFriendSystemCN2GCAckFriendsOpen: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemCN2GCAckFriendsOpen() : GFLib::CMessage(msgIDFriendSystemCN2GCAckFriendsOpen)
		{
			m_capacity = 0;
		}

		void addFriend(const SFriendInfo& a_info)
		{
			m_friends.push_back(a_info);
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	
			BSLib::uint32 size = m_friends.size();
			stream << size;
			std::vector<SFriendInfo>::const_iterator it = m_friends.begin();
			for(; it != m_friends.end(); ++it)
			{
				(*it)._serializeTo(stream);
			}
			stream << m_capacity;
			return true;
		}
	public:
		std::vector<SFriendInfo> m_friends;
		BSLib::uint32	m_capacity;

	};	

	// ��Ӻ���������֤
	const BSLib::uint32 msgIDFriendSystemCN2GCReqFriendsAddConfirm = 
		GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_CN2GC_REQ_FRIENDS_ADD_CONFIRM);
	class CMsgFriendSystemCN2GCReqFriendsAddConfirm: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemCN2GCReqFriendsAddConfirm() : GFLib::CMessage(msgIDFriendSystemCN2GCReqFriendsAddConfirm)
		{

		}

		void addFriendShortInfo(const SFriendInfo& a_info)
		{
			m_friends.push_back(a_info);
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	

			BSLib::uint32 size = m_friends.size();
			stream << size;
			std::vector<SFriendInfo>::const_iterator it = m_friends.begin();
			for(; it != m_friends.end(); ++it)
			{
				(*it)._serializeTo(stream);
			}
			return true;
		}

	public:
		std::vector<SFriendInfo> m_friends;
	};

	// ��Ӻ��ѽ������
	const BSLib::uint32 msgIDFriendSystemCN2GCNtfFriendsAddResult = 
		GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_CN2GC_NTF_FRIENDS_ADD_RESULT);
	class CMsgFriendSystemCN2GCNtfFriendsAddResult: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemCN2GCNtfFriendsAddResult() : GFLib::CMessage(msgIDFriendSystemCN2GCNtfFriendsAddResult)
		{

		}

		void addFriendInfo(const SFriendInfo& a_info, BSLib::uint32 a_result)
		{
			m_friends.push_back(a_info);
			m_result.push_back(a_result);
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	

			BSLib::uint32 size = m_friends.size();
			stream << size;
			std::vector<SFriendInfo>::const_iterator it = m_friends.begin();
			for(; it != m_friends.end(); ++it)
			{
				(*it)._serializeTo(stream);
			}
			
			stream << size;
			for(BSLib::uint32 i = 0; i < size; i++)
			{
				stream << m_result[i];
			}
			return true;
		}

	public:
		std::vector<SFriendInfo> m_friends;
		std::vector<BSLib::uint32> m_result;
	};



	// ɾ������ ����
	const BSLib::uint32 msgIDFriendSystemCN2GCAckFriendsDel = 
		GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_CN2GC_ACK_FRIENDS_DEL);
	class CMsgFriendSystemCN2GCAckFriendsDel: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemCN2GCAckFriendsDel() : GFLib::CMessage(msgIDFriendSystemCN2GCAckFriendsDel)
		{

		}

		void addFriend(const SRoleKey& a_info)
		{
			m_friends.push_back(a_info);
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	
			BSLib::uint32 size = m_friends.size();
			stream << size;
			std::vector<SRoleKey>::const_iterator it = m_friends.begin();
			for(; it != m_friends.end(); ++it)
			{
				stream << (*it).getAccountID();
				stream << (*it).getZoneID();
				stream << (*it).getIndex();
			}
			return true;
		}

	public:
		std::vector<SRoleKey> m_friends;	// ɾ���ɹ���
	};	


	// �����Ƽ����ѷ���
	const BSLib::uint32 msgIDFriendSystemCN2GCAckFriendsNewStrangers = 
		GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_CN2GC_ACK_FRIENDS_NEW_STRANGERS);
	class CMsgFriendSystemCN2GCAckFriendsNewStrangers: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemCN2GCAckFriendsNewStrangers() : GFLib::CMessage(msgIDFriendSystemCN2GCAckFriendsNewStrangers)
		{

		}

		void addFriend(const SFriendInfo& a_info)
		{
			m_friends.push_back(a_info);
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	

			BSLib::uint32 size = m_friends.size();
			stream << size;
			std::vector<SFriendInfo>::const_iterator it = m_friends.begin();
			for(; it != m_friends.end(); ++it)
			{
				(*it)._serializeTo(stream);
			}
			return true;
		}

	public:
		std::vector<SFriendInfo> m_friends;	// ɾ���ɹ���
	};


	// �������ѷ���
	const BSLib::uint32 msgIDFriendSystemCN2GCAckFriendsSearch = 
		GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_CN2GC_ACK_FRIENDS_SEARCH);
	class CMsgFriendSystemCN2GCAckFriendsSearch: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemCN2GCAckFriendsSearch() : GFLib::CMessage(msgIDFriendSystemCN2GCAckFriendsSearch)
		{

		}

		void addFriend(const SFriendInfo& a_info)
		{
			m_friends.push_back(a_info);
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	
			BSLib::uint32 size = m_friends.size();
			stream << size;
			std::vector<SFriendInfo>::const_iterator it = m_friends.begin();
			for(; it != m_friends.end(); ++it)
			{
				(*it)._serializeTo(stream);
			}
			return true;
		}

	public:
		std::vector<SFriendInfo> m_friends;
	};


	// ���ظ�������
	const BSLib::uint32 msgIDFriendSystemGM2GCAckFriendsNewLocal = 
		GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_FRIENDSYSTEM, EMSGID_FRIENDSYSTEM_GM2GC_ACK_FRIENDS_LOCAL);
	class CMsgFriendSystemGM2GCAckFriendsLocal: public GFLib::CMessage
	{
	public:
		CMsgFriendSystemGM2GCAckFriendsLocal() : GFLib::CMessage(msgIDFriendSystemGM2GCAckFriendsNewLocal)
		{

		}

		void addFriend(const SFriendInfo& a_info)
		{
			m_friends.push_back(a_info);
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	

			BSLib::uint32 size = m_friends.size();
			stream << size;
			std::vector<SFriendInfo>::const_iterator it = m_friends.begin();
			for(; it != m_friends.end(); ++it)
			{
				(*it)._serializeTo(stream);
			}
			return true;
		}

	public:
		std::vector<SFriendInfo> m_friends;	// ɾ���ɹ���
	};


}

}//GSLib

#endif
