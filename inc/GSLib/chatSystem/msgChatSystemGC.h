#ifndef __GSLIB_CHATSYSTEM_MSGCHATSYSTEMGC_H__
#define __GSLIB_CHATSYSTEM_MSGCHATSYSTEMGC_H__

#include <GSLib/chatSystem/msgNumIDChatSystem.h>
#include <BSLib/utility/baseDef.h>
#include <GSLib/chatSystem/GM/chatContent.h>

namespace GSLib
{

namespace ChatSystem
{

const BSLib::uint32 MsgIDChatSystemGM2GCAckChat = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_CHATSYSTEM, EMSGNUMID_CHATSYSTEM_GC2GM_ACK_CHAT);
class CMsgChatSystemGM2GCAckChat: public GFLib::CMessage
{
public:
	CMsgChatSystemGM2GCAckChat() 
		:GFLib::CMessage(MsgIDChatSystemGM2GCAckChat)
		,m_result(CHAT_RESULT_SUCCESS)
	{
		;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::int8)m_result;
		return true;
	}
public:
	EChatResult m_result;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDChatSystemGM2GCAckChat2All = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_CHATSYSTEM, EMSGNUMID_CHATSYSTEM_GC2GM_ACK_CHAT2ALL);
class CMsgChatSystemGM2GCAckChat2All: public GFLib::CMessage
{
public:
	CMsgChatSystemGM2GCAckChat2All() 
	:GFLib::CMessage(MsgIDChatSystemGM2GCAckChat2All)
	,m_senderName("")
	,m_VIPLevel(0)
	,m_channel(CHAT_CHANNEL_PRIVATE)
	,m_content("")
	,m_hasEquip(false)
	{
		;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_senderKey;
		stream << m_senderName;
		stream << m_VIPLevel;
		stream << (BSLib::int8)m_channel;
		if (m_channel == CHAT_CHANNEL_PRIVATE) {
			stream << m_receiverKey;
		}
		stream << m_content;
		stream << (m_hasEquip ? (BSLib::int8)1 : (BSLib::int8)0);
		if (m_hasEquip) {
			stream << m_equipStream;
		}

		return true;
	}
public:
	GSLib::SRoleKey m_senderKey;
	std::string m_senderName;
	BSLib::uint32 m_VIPLevel;
	EChatChanel m_channel;
	GSLib::SRoleKey m_receiverKey;
	std::string m_content;
	bool m_hasEquip;
	BSLib::Utility::CStream m_equipStream;
};

const BSLib::uint32 MsgIDChatSystemGM2GCAckInitChatData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_CHATSYSTEM, EMSGNUMID_CHATSYSTEM_GC2GM_ACK_INIT_CHAT_DATA);
class CMsgChatSystemGM2GCAckInitChatData: public GFLib::CMessage
{
public:
	CMsgChatSystemGM2GCAckInitChatData()
	:GFLib::CMessage(MsgIDChatSystemGM2GCAckInitChatData)
	{

	};
	CMsgChatSystemGM2GCAckInitChatData(const std::list<GM::CChatContent> listWorlContent, const std::list<GM::CChatContent> listAnnounceContent) 
	:GFLib::CMessage(MsgIDChatSystemGM2GCAckInitChatData)
	,m_listWorlContent(listWorlContent)
	,m_listAnnounceContent(listAnnounceContent)
	{
		;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		BSLib::uint16 size = (BSLib::uint16)m_listWorlContent.size();
		stream << size;
		for (std::list<GM::CChatContent>::const_iterator itr = m_listWorlContent.begin(); itr != m_listWorlContent.end(); ++itr) {
			itr->serializeTo(stream);
		}

		size = (BSLib::uint16)m_listAnnounceContent.size();
		stream << size;
		for (std::list<GM::CChatContent>::const_iterator itr = m_listAnnounceContent.begin(); itr != m_listAnnounceContent.end(); ++itr) {
			itr->serializeTo(stream);
		}

		return true;
	}
public:
	const std::list<GM::CChatContent> m_listWorlContent;
	const std::list<GM::CChatContent> m_listAnnounceContent;
};


}//ChatSystem

}//GSLib

#endif//__GSLIB_CHATSYSTEM_MSGCHATSYSTEMGC_H__

