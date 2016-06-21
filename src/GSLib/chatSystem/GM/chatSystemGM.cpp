#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include <GSLib/chatSystem/GM/chatSystemGM.h>
#include <GSLib/chatSystem/GM/roleChatModule.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/chatSystem/msgChatSystemGC.h>
#include <GSLib/loginSystem/GT/msgLoginSystemGT.h>
#include <GFLib/commonServer/serviceMgr.h>

namespace GSLib
{

namespace ChatSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CChatSystemGM);

CChatSystemGM::CChatSystemGM()
:m_enableGMChatCommand(false)
{
	;
}

CChatSystemGM::~CChatSystemGM()
{
	;
}

void CChatSystemGM::update(BSLib::uint64 a_delayMilliseconds)
{
	;
}

bool CChatSystemGM::_init()
{
	GSLib::PlayerSystem::GM::CRoleModuleGMMgr::singleton().addCreateRoleModuleFun(EMODULECTYPE_CHAT, GSLib::PlayerSystem::GM::createRoleModuleFun<CRoleChatModule>);

	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CChatSystemGM::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CChatSystemGM::_loadGameConfig(const std::string& a_configPath)
{
	GFLib::CommonServer::CCommonServer* srv = GFLib::CommonServer::CCommonServer::getCommonServer();
	std::string serverName = srv->getServerTypeName();
	m_enableGMChatCommand = (BSLib::Framework::CSysConfig::singleton().getValueInt(serverName, "EnableGMChatCommand") != 0);

	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CChatSystemGM::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CChatSystemGM::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CChatSystemGM::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CChatSystemGM::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

bool CChatSystemGM::enableGMChatCommand() const
{
	return m_enableGMChatCommand;
}

void CChatSystemGM::sendAnnounce(const std::string &a_content) const
{
	CMsgChatSystemGM2GCAckChat2All msgAck2All;
	msgAck2All.m_channel = CHAT_CHANNEL_ANNOUNCE;
	msgAck2All.m_content = a_content;
	GSLib::LoginSystem::CMsgLoginSystemXS2GTNtfBroadcastMsg ntfBroadcastMsg;
	if (!msgAck2All.serializeTo(ntfBroadcastMsg.m_subMsg)) {
		return;
	}
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServerType(SRVTYPE_GATESERVER, ntfBroadcastMsg);
}

}//GM

}//ChatSystem

}//GSLib

