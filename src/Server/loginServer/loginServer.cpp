#include <BSLib/utility/random.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/stubMgr.h>
#include <GFLib/commonServer/message/msgLabel.h>
#include <GSLib/funType.h>
#include <GSLib/loginSystem/LG/loginSystemLG.h>
#include <GSLib/dbSystem/LG/dbSystemLG.h>
#include "loginServer.h"
#include "common/tracer.h"
#include "common/serverDef.hpp"
#include "loginStub.h"

#if defined(_DEBUG) && defined(_VLD)
#undef _DLL
#include <vld/inc/vld.h>
#endif

BSLIB_FRAMEWORK_MAIN(CLoginServer::main);

BSLIB_SINGLETON_DEFINE(CLoginServer);

#ifndef LOGINSERVER_MAJOR_VERSION
#define LOGINSERVER_MAJOR_VERSION 0
#endif

#ifndef LOGINSERVER_MINOR_VERSION
#define LOGINSERVER_MINOR_VERSION 0
#endif

#ifndef LOGINSERVER_MICRO_VERSION
#define LOGINSERVER_MICRO_VERSION 0
#endif

#define _TEXT__(x) #x
#define _TEXT_(x) _TEXT__(x)

#define LOGINSERVER_VERSION_TEXT _TEXT_(LOGINSERVER_MAJOR_VERSION)"."_TEXT_(LOGINSERVER_MINOR_VERSION)"."_TEXT_(LOGINSERVER_MICRO_VERSION)


CLoginServer::CLoginServer()
{
	Server::initServerType();
}

CLoginServer::~CLoginServer()
{
	;
}

GFLib::ServerType CLoginServer::getServerType()
{
	return GSLib::SRVTYPE_LOGINSERVER;
}

std::string CLoginServer::getServerVersion()
{
	BSLib::Utility::CStringA strVersion;
	strVersion += LOGINSERVER_VERSION_TEXT;
	return strVersion;
}

int CLoginServer::main()
{
	return CLoginServer::singleton()._IThread_main();
}

bool CLoginServer::_init()
{
	if (!GFLib::CommonServer::CCommonServer::_IThread_init()) {
		return false;
	}
	return true;
}

int CLoginServer::_final()
{
	return GFLib::CommonServer::CCommonServer::_IThread_final();
}

bool CLoginServer::_initSystem(GFLib::CommonServer::CCommonSystemMgr* commanSystemMgr)
{
	Server::initTraceType();
	
	commanSystemMgr->addSystem(&GSLib::LoginSystem::LG::CLoginSystemLG::singleton());
	commanSystemMgr->addSystem(&GSLib::DBSystem::LG::CDBSystemLG::singleton());

	return GFLib::CommonServer::CCommonServer::_initSystem(commanSystemMgr);
}

bool CLoginServer::_loadGameConfig(const std::string& a_configPath)
{
	return GFLib::CommonServer::CCommonServer::_loadGameConfig(a_configPath);
}

void CLoginServer::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	GFLib::CommonServer::CCommonServer::_initServerMsg(a_msgExecMgr);
}

void CLoginServer::_cbServerEnter(GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::CCommonServer::_cbServerEnter(a_serverID, a_key);
}

void CLoginServer::_cbServerLeave(GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::CCommonServer::_cbServerLeave(a_serverID, a_key);
}

GFLib::CommonServer::CCommonClientPtr CLoginServer::_cbCreateClient(GFLib::SServerID& a_serverID, const std::string& a_serverKey)
{
	switch (a_serverID.getServerType())
	{
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

	return GFLib::CommonServer::CCommonServer::_cbCreateClient(a_serverID, a_serverKey);
}

BSLib::Network::CNetStubPtr CLoginServer::_cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData)
{
	BSLib::int64 flag = (BSLib::int64)tempData;
	BSLib::Network::CNetStubPtr netStubPtr = NULL;
	switch (flag) {
		case 0:
			netStubPtr = new CLoginStub(netConnPtr);
			break;
		case 1:
			netStubPtr = new GFLib::CommonServer::IStub(netConnPtr);
			break;
		default:
			break;
	}
	if (netStubPtr != NULL) {
		netStubPtr->setNeedPing(getNeedPing());
	}
	return netStubPtr;
}



