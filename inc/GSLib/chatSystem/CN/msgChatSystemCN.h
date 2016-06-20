//////////////////////////////////////////////////////////////////////
//	created:	2014/10/10
//	filename: 	GSLib\chatSystem\CN\msgChatSystemCN.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_CHATSYSTEM_CN_MSGCHATSYSTEMCN_H__
#define __GSLIB_CHATSYSTEM_CN_MSGCHATSYSTEMCN_H__

#include <GSLib/chatSystem/msgNumIDChatSystem.h>

namespace GSLib
{

namespace ChatSystem
{

const BSLib::uint32 MsgIDChatSystemGM2CNReqPrivateChat = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_CHATSYSTEM, EMSGNUMID_CHATSYSTEM_GM2CN_REQ_PRIVATE_CHAT);
class CMsgChatSystemGM2CNReqPrivateChat: public GFLib::CMessage
{
public:
	CMsgChatSystemGM2CNReqPrivateChat() 
	: GFLib::CMessage(MsgIDChatSystemGM2CNReqPrivateChat)
	, m_hasEquip(false)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_receiverKey;
		stream << m_content;
		stream << (m_hasEquip ? (BSLib::int8)1 : (BSLib::int8)0);
		if (m_hasEquip) {
			stream << m_equipStream;
		}
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_receiverKey;
		stream >> m_content;
		BSLib::int8 hasEquipt = 0;
		stream >> hasEquipt;
		m_hasEquip = hasEquipt > 0;
		if (m_hasEquip) {
			stream >> m_equipStream;
		}
		return true;
	}

public:
	GSLib::SRoleKey m_receiverKey;
	std::string m_content;
	bool m_hasEquip;
	BSLib::Utility::CStream m_equipStream;
};



}//ChatSystem

}//GSLib

#endif//__GSLIB_CHATSYSTEM_CN_MSGCHATSYSTEMCN_H__
