//////////////////////////////////////////////////////////////////////
//	created:	2014/11/12
//	filename: 	GSLib\chatSystem\GM\chatMgr.cpp
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/chatSystem/GM/chatMgr.h>
#include <GSLib/chatSystem/chatSystemDefine.h>

namespace GSLib
{

namespace ChatSystem
{
namespace GM
{

BSLIB_SINGLETON_DEFINE(CChatMgr);
CChatMgr::CChatMgr()
{

}

CChatMgr::~CChatMgr()
{

}

void CChatMgr::addWorldContent(CChatContent &content)
{
	if (m_listWorldContent.size() >= (int)C_MAX_WORLD_CHAT_BUFFERD_CONTENT_COUNT ) {
		m_listWorldContent.pop_back();
	}
	m_listWorldContent.push_front(content);
}

void CChatMgr::addAnnounceContent(CChatContent &content)
{
	if (m_listAnnounceContent.size() >= (int)C_MAX_ANNOUNCE_CHAT_BUFFERD_CONTENT_COUNT ) {
		m_listAnnounceContent.pop_back();
	}
	m_listAnnounceContent.push_front(content);
}

const std::list<CChatContent>& CChatMgr::getWorldContent()
{
	return m_listWorldContent;
}

const std::list<CChatContent>& CChatMgr::getAnnounceContent()
{
	return m_listAnnounceContent;
}


}//GM

}//ChatSystem

}//GSLib

