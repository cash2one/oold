//////////////////////////////////////////////////////////////////////
//	created:	2014/11/12
//	filename: 	GSLib\chatSystem\GM\chatMgr.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef	__GSLIB_CHATSYSTEM_GM_CHATMGR_H__
#define __GSLIB_CHATSYSTEM_GM_CHATMGR_H__

#include <list>
#include <BSLib/utility/singleton.h>
#include <GSLib/chatSystem/GM/chatContent.h>

namespace GSLib
{

namespace ChatSystem
{

namespace GM
{
class CChatMgr
{
public:
	BSLIB_SINGLETON_DECLARE(CChatMgr);
public:
	CChatMgr();
	~CChatMgr();
public:
	void addWorldContent(CChatContent &content);
	void addAnnounceContent(CChatContent &chatContent);

	const std::list<CChatContent>& getWorldContent();
	const std::list<CChatContent>& getAnnounceContent();
private:
	std::list<CChatContent> m_listWorldContent;
	std::list<CChatContent> m_listAnnounceContent;
};
}//GM

}//ChatSystem

}//GSLib

#endif//__GSLIB_CHATSYSTEM_GM_CHATMGR_H__
