#ifndef __GSLIB_CHATSYSTEM_MSGCHATSYSTEMGM_H__
#define __GSLIB_CHATSYSTEM_MSGCHATSYSTEMGM_H__

#include <GSLib/chatSystem/msgNumIDChatSystem.h>
#include <GSLib/chatSystem/chatSystemDefine.h>
#include <GSLib/chatSystem/chatSystemError.h>
#include <GSLib/chatSystem/GM/chatSystemData.h>

namespace GSLib
{

namespace ChatSystem
{

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDChatSystemGC2GMReqChat = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_CHATSYSTEM, EMSGNUMID_CHATSYSTEM_GC2GM_REQ_CHAT);
class CMsgChatSystemGC2GMReqChat: public GFLib::CMessage
{
public:
	CMsgChatSystemGC2GMReqChat()
	:GFLib::CMessage(MsgIDChatSystemGC2GMReqChat)
	,m_channel(CHAT_CHANNEL_PRIVATE)
	,m_content("")
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_receiverKey;
		BSLib::int8 channel = 0;
		stream >> channel;
		m_channel = (EChatChanel)channel;
		stream >> m_content;
		m_equipID.serializeFrom(stream);

		return true;
	}
public:
	GSLib::SRoleKey m_receiverKey;
	EChatChanel m_channel;
	std::string m_content;
	GM::CChatEquipID m_equipID;
};

}//ChatSystem

}//GSLib

#endif//__GSLIB_CHATSYSTEM_MSGCHATSYSTEMGM_H__

