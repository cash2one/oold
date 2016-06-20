//////////////////////////////////////////////////////////////////////
//	created:	2014/10/09
//	filename: 	GSLib\chatSystem\GM\chatSystemGM.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_CHATSYSTEM_GM_CHATSYSTEMGM_H__
#define __GSLIB_CHATSYSTEM_GM_CHATSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace ChatSystem
{

namespace GM
{

class CChatSystemGM : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CChatSystemGM();
	virtual ~CChatSystemGM();

	BSLIB_SINGLETON_DECLARE(CChatSystemGM);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_CHATSYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

	void sendAnnounce(const std::string &a_content) const;

public:
	virtual bool _init();
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

	bool enableGMChatCommand() const;
public:
	bool m_enableGMChatCommand; 
};

}//GM

}//ChatSystem

}//GSLib

#endif//__GSLIB_CHATSYSTEM_GM_CHATSYSTEMGM_H__
