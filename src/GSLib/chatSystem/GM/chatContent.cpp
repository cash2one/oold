//////////////////////////////////////////////////////////////////////
//	created:	2014/11/12
//	filename: 	GSLib\chatSystem\GM\chatContent.cpp
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/chatSystem/GM/chatContent.h>

namespace GSLib
{

namespace ChatSystem
{
namespace GM
{

CChatContent::CChatContent()
:m_senderName("")
,m_VIPLevel(0)
,m_channel(CHAT_CHANNEL_PRIVATE)
,m_content("")
,m_hasEquip(false)
{

}

CChatContent::~CChatContent()
{

}

void CChatContent::serializeTo(BSLib::Utility::CStream & a_stream) const
{
	a_stream << m_roleKey;
	a_stream << m_senderName;
	a_stream << m_VIPLevel;
	a_stream << (BSLib::int8)m_channel;
	a_stream << m_content;
}


}//GM

}//ChatSystem

}//GSLib

