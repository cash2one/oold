
#include <BSLib/utility/random.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/stubMgr.h>
#include <GFLib/commonServer/message/msgLabel.h>
#include <GSLib/funType.h>
#include <GSLib/loginSystem/CN/loginSystemCN.h>
#include <GSLib/dbSystem/CN/dbSystemCN.h>
#include <GSLib/playerSystem/CN/playerSystemCN.h>
#include <GSLib/chatSystem/CN/chatSystemCN.h>
#include <GSLib/mailSystem/CN/mailSystemCN.h>
#include "centerServer.h"
#include "common/tracer.h"
#include "common/serverDef.hpp"
#include <GSLib/friendSystem/CN/friendSystemCN.h>
#include <GSLib/rankSystem/CN/rankSystemCN.h>
#include <GSLib/sceneSystem/CN/sceneSystemCN.h>
#include <GSLib/masterSystem/CN/masterSystemCN.h>

#if defined(_DEBUG) && defined(_VLD)
#undef _DLL
#include <vld/inc/vld.h>
#endif

BSLIB_FRAMEWORK_MAIN(CCenterServer::main);

BSLIB_SINGLETON_DEFINE(CCenterServer);

#ifndef CENTERSERVER_MAJOR_VERSION
#define CENTERSERVER_MAJOR_VERSION 0
#endif

#ifndef CENTERSERVER_MINOR_VERSION
#define CENTERSERVER_MINOR_VERSION 0
#endif

#ifndef CENTERSERVER_MICRO_VERSION
#define CENTERSERVER_MICRO_VERSION 0
#endif

#define _TEXT__(x) #x
#define _TEXT_(x) _TEXT__(x)

#define CENTERSERVER_VERSION_TEXT _TEXT_(CENTERSERVER_MAJOR_VERSION)"."_TEXT_(CENTERSERVER_MINOR_VERSION)"."_TEXT_(CENTERSERVER_MICRO_VERSION)


CCenterServer::CCenterServer()
{
	Server::initServerType();
}

CCenterServer::~CCenterServer()
{
	;
}

GFLib::ServerType CCenterServer::ICommonServer_getServerType()
{
	return GSLib::SRVTYPE_CENTERSERVER;
}

std::string CCenterServer::ICommonServer_getServerVersion()
{
	BSLib::Utility::CStringA strVersion;
	strVersion += CENTERSERVER_VERSION_TEXT;
	return strVersion;
}

int CCenterServer::main()
{
	return CCenterServer::singleton()._IThread_main();
}

int CCenterServer::_IThread_final()
{
	return GFLib::CommonServer::ICommonServer::_IThread_final();
}

bool CCenterServer::ICommonServer_initSystem(GFLib::CommonServer::CCommonSystemMgr* commanSystemMgr)
{
	Server::initTraceType();

	commanSystemMgr->addSystem(&GSLib::LoginSystem::CN::CLoginSystemCN::singleton());
	commanSystemMgr->addSystem(&GSLib::DBSystem::CN::CDBSystemCN::singleton());
	commanSystemMgr->addSystem(&GSLib::PlayerSystem::CN::CPlayerSystemCN::singleton());
	commanSystemMgr->addSystem(&GSLib::ChatSystem::CN::CChatSystemCN::singleton());
	commanSystemMgr->addSystem(&GSLib::MailSystem::CN::CMailSystemCN::singleton());
	commanSystemMgr->addSystem(&GSLib::FriendSystem::CN::CFriendSystemCN::singleton());
	commanSystemMgr->addSystem(&GSLib::RankSystem::CN::CRankSystemCN::singleton());
	commanSystemMgr->addSystem(&GSLib::SceneSystem::CN::CSceneSystemCN::singleton());
	commanSystemMgr->addSystem(&GSLib::MasterSystem::CN::CMasterSystemCN::singleton());

	return GFLib::CommonServer::ICommonServer::ICommonServer_initSystem(commanSystemMgr);
}

bool CCenterServer::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return GFLib::CommonServer::ICommonServer::ICommonServer_loadGameConfig(a_configPath);;
}

void CCenterServer::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	GFLib::CommonServer::ICommonServer::ICommonServer_initServerMsg(a_msgExecMgr);
}

void CCenterServer::ICommonServer_cbServerEnter(GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::ICommonServer::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CCenterServer::ICommonServer_cbServerLeave(GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::ICommonServer::ICommonServer_cbServerLeave(a_serverID, a_key);
}

GFLib::CommonServer::CCommonClientPtr CCenterServer::_ICommonServer_cbCreateClient(GFLib::SServerID& a_serverID, const std::string& a_serverKey)
{
	switch (a_serverID.getServerType())
	{
	case GSLib::SRVTYPE_DATASERVER:
		{
			GFLib::CommonServer::CCommonClientPtr commonClientPtr = new GFLib::CommonServer::CCommonClient(a_serverID, a_serverKey);
			return commonClientPtr;
		}
	case GSLib::SRVTYPE_LOGINSERVER:
		{
			GFLib::CommonServer::CCommonClientPtr commonClientPtr = new GFLib::CommonServer::CCommonClient(a_serverID, a_serverKey);
			return commonClientPtr;
		}
	case GSLib::SRVTYPE_SUPERSERVER:
		{
			GFLib::CommonServer::CCommonClientPtr commonClientPtr = new GFLib::CommonServer::CCommonClient(a_serverID, a_serverKey);
			return commonClientPtr;
		}
	default:
		{
			;
		}
	}

	return GFLib::CommonServer::ICommonServer::_ICommonServer_cbCreateClient(a_serverID, a_serverKey);
}

BSLib::Network::CNetStubPtr CCenterServer::_INetServer_cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData)
{

	BSLib::int64 flag = (BSLib::int64)tempData;
	BSLib::Network::CNetStubPtr netStubPtr = NULL;
	switch (flag) {
		case 1:
			netStubPtr = new GFLib::CommonServer::IStub(netConnPtr);
			break;
		case 0:
		default:
			break;
	}
	if (netStubPtr != NULL) {
		netStubPtr->setNeedPing(getNeedPing());
	}
	return netStubPtr;
}

