//////////////////////////////////////////////////////////////////////
//	created:	2014/10/10
//	filename: 	GSLib\chatSystem\CN\chatSystemCN.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_CHATSYSTEM_CN_CHATSYSTEMCN_H__
#define __GSLIB_CHATSYSTEM_CN_CHATSYSTEMCN_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace ChatSystem
{

namespace CN
{

class CChatSystemCN : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CChatSystemCN();
	virtual ~CChatSystemCN();

	BSLIB_SINGLETON_DECLARE(CChatSystemCN);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_CHATSYSTEM; }

public:
	virtual bool _init();
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);
private:
	void _onMsgChatSystemGM2CNReqPrivateChat(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
};

}//CN

}//ChatSystem

}//GSLib

#endif//__GSLIB_CHATSYSTEM_CN_CHATSYSTEMCN_H__
