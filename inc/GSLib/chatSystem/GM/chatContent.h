//////////////////////////////////////////////////////////////////////
//	created:	2014/11/12
//	filename: 	GSLib\chatSystem\GM\chatContent.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef	__GSLIB_CHATSYSTEM_GM_CHATCONTENT_H__
#define __GSLIB_CHATSYSTEM_GM_CHATCONTENT_H__

#include <list>
#include <BSLib/utility/baseDef.h>
#include <BSLib/utility/stream.h>
#include <GSLib/chatSystem/chatSystemDefine.h>

namespace GSLib
{

namespace ChatSystem
{

namespace GM
{
class CChatContent
{
public:
	CChatContent();
	~CChatContent();
public:
	void serializeTo(BSLib::Utility::CStream &a_stream) const;
public:
	GSLib::SRoleKey m_roleKey;
	std::string m_senderName;
	BSLib::uint32 m_VIPLevel;
	EChatChanel m_channel;
	std::string m_content;
	bool m_hasEquip;
	BSLib::Utility::CStream m_equipStream;
};
}//GM

}//ChatSystem

}//GSLib

#endif//__GSLIB_CHATSYSTEM_GM_CHATCONTENT_H__
