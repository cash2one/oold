
#include <BSLib/utility/random.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/stubMgr.h>
#include <GFLib/commonServer/message/msgLabel.h>
#include <GSLib/funType.h>
#include <GSLib/loginSystem/SP/loginSystemSP.h>
#include "superServer.h"
#include "common/tracer.h"
#include "common/serverDef.hpp"
#include "gmStub.h"
#include <GSLib/masterSystem/SP/masterSystemSP.h>

#if defined(_DEBUG) && defined(_VLD)
#undef _DLL
#include <vld/inc/vld.h>
#endif

BSLIB_FRAMEWORK_MAIN(CSuperServer::main);

BSLIB_SINGLETON_DEFINE(CSuperServer);

#ifndef SUPERSERVER_MAJOR_VERSION
#define SUPERSERVER_MAJOR_VERSION 0
#endif

#ifndef SUPERSERVER_MINOR_VERSION
#define SUPERSERVER_MINOR_VERSION 0
#endif

#ifndef SUPERSERVER_MICRO_VERSION
#define SUPERSERVER_MICRO_VERSION 0
#endif

#define _TEXT__(x) #x
#define _TEXT_(x) _TEXT__(x)

#define SUPERSERVER_VERSION_TEXT _TEXT_(SUPERSERVER_MAJOR_VERSION)"."_TEXT_(SUPERSERVER_MINOR_VERSION)"."_TEXT_(SUPERSERVER_MICRO_VERSION)


CSuperServer::CSuperServer()
{
	Server::initServerType();
}

CSuperServer::~CSuperServer()
{
	;
}

GFLib::ServerType CSuperServer::ICommonServer_getServerType()
{
	return GSLib::SRVTYPE_SUPERSERVER;
}

std::string CSuperServer::ICommonServer_getServerVersion()
{
	BSLib::Utility::CStringA strVersion;
	strVersion += SUPERSERVER_VERSION_TEXT;
	return strVersion;
}

int CSuperServer::main()
{
	return CSuperServer::singleton()._IThread_main();
}

bool CSuperServer::_IThread_init()
{
	if (!GFLib::CommonServer::ICommonServer::_IThread_init()) {
		return false;
	}

	return true;
}

bool CSuperServer::_IThread_callback()
{
// 	BSLib::uint64 id_1 = GFLib::CommonServer::CUniqueIDMgr::singleton().getInt64ZoneUniqueID(1);
// 	BSLib::uint64 id_2 = GFLib::CommonServer::CUniqueIDMgr::singleton().getInt64ZoneUniqueID(2);
// 	BSLIB_LOG_INFO(Server::ETT_SERVER_COMMON, "@@@[%llX][%llX]", id_1, id_2);
	return GFLib::CommonServer::ICommonServer::_IThread_callback();
}

int CSuperServer::_IThread_final()
{
	return GFLib::CommonServer::ICommonServer::_IThread_final();
}

bool CSuperServer::ICommonServer_initSystem(GFLib::CommonServer::CCommonSystemMgr* commanSystemMgr)
{
	Server::initTraceType();
	
	commanSystemMgr->addSystem(&GSLib::LoginSystem::SP::CLoginSystemSP::singleton());
	commanSystemMgr->addSystem(&GSLib::MasterSystem::SP::CMasterSystemSP::singleton());

	return GFLib::CommonServer::ICommonServer::ICommonServer_initSystem(commanSystemMgr);
}

bool CSuperServer::ICommonServer_loadGameConfig(const std::string& a_configPath)
{	
	return GFLib::CommonServer::ICommonServer::ICommonServer_loadGameConfig(a_configPath);
}

void CSuperServer::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{	
	GFLib::CommonServer::ICommonServer::ICommonServer_initServerMsg(a_msgExecMgr);
}

void CSuperServer::ICommonServer_cbServerEnter(GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	if(a_serverID.m_type == GSLib::SRVTYPE_CENTERSERVER)
	{
		m_cnServers.insert(std::make_pair(a_key, a_serverID));
	}

	GFLib::CommonServer::ICommonServer::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CSuperServer::ICommonServer_cbServerLeave(GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	if(a_serverID.m_type == GSLib::SRVTYPE_CENTERSERVER)
	{	
		std::map<std::string, GFLib::SServerID>::iterator it = m_cnServers.find(a_key);
		if(it != m_cnServers.end())
			m_cnServers.erase(it);
	}

	GFLib::CommonServer::ICommonServer::ICommonServer_cbServerLeave(a_serverID, a_key);
}

GFLib::CommonServer::CCommonClientPtr CSuperServer::_ICommonServer_cbCreateClient(GFLib::SServerID& a_serverID, const std::string& a_serverKey)
{
	switch (a_serverID.ICommonServer_getServerType())
	{
	case GSLib::SRVTYPE_AUTHCODESERVER:
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

BSLib::Network::CNetStubPtr CSuperServer::_INetServer_cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData)
{
	BSLib::int64 flag = (BSLib::int64)tempData;
	BSLib::Network::CNetStubPtr netStubPtr = NULL;
	switch (flag) {
		case 2:
			netStubPtr = new CGMStub(netConnPtr);
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

                                                                                                                                                                                                                                                                                                                                                                                                     

