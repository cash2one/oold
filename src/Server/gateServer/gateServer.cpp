//////////////////////////////////////////////////////////////////////
//	created:	2014/07/17
//	filename: 	src\Server\gateServer\gateServer.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////

#include <BSLib/utility/random.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/stubMgr.h>
#include <GFLib/commonServer/message/msgLabel.h>
#include <GSLib/funType.h>
#include <GSLib/loginSystem/GT/loginSystemGT.h>
#include <GSLib/playerSystem/GT/playerSystemGT.h>
#include <GSLib/dbSystem/GT/dbSystemGT.h>
#include "gateServer.h"
#include "common/tracer.h"
#include "common/serverDef.hpp"
#include "gateStub.h"

#if defined(_DEBUG) && defined(_VLD)
#undef _DLL
#include <vld/inc/vld.h>
#endif

BSLIB_FRAMEWORK_MAIN(CGateServer::main);

BSLIB_SINGLETON_DEFINE(CGateServer);

#ifndef GATESERVER_MAJOR_VERSION
#define GATESERVER_MAJOR_VERSION 0
#endif

#ifndef GATESERVER_MINOR_VERSION
#define GATESERVER_MINOR_VERSION 0
#endif

#ifndef GATESERVER_MICRO_VERSION
#define GATESERVER_MICRO_VERSION 0
#endif

#define _TEXT__(x) #x
#define _TEXT_(x) _TEXT__(x)

#define GATESERVER_VERSION_TEXT _TEXT_(GATESERVER_MAJOR_VERSION)"."_TEXT_(GATESERVER_MINOR_VERSION)"."_TEXT_(GATESERVER_MICRO_VERSION)


CGateServer::CGateServer()
{
	Server::initServerType();
}

CGateServer::~CGateServer()
{
	;
}

GFLib::ServerType CGateServer::getServerType()
{
	return GSLib::SRVTYPE_GATESERVER;
}

std::string CGateServer::getServerVersion()
{
	BSLib::Utility::CStringA strVersion;
	strVersion += GATESERVER_VERSION_TEXT;
	return strVersion;
}

int CGateServer::main()
{
	return CGateServer::singleton()._main();
}

bool CGateServer::_callback()
{
	BSLib::Network::SNetInfor netInfor;
	BSLib::Network::CNetServer::getNetInfor(netInfor, *BSLib::Framework::CMainThread::getRealTime());
	if (netInfor.m_tcpStubsInfor.m_connectTotal != m_tcpStubsInfor.m_connectTotal ||
		netInfor.m_tcpStubsInfor.m_stubCount != m_tcpStubsInfor.m_stubCount ||
		netInfor.m_tcpStubsInfor.m_stubOkayCount != m_tcpStubsInfor.m_stubOkayCount || 
		netInfor.m_tcpStubsInfor.m_stubVerifyCount != m_tcpStubsInfor.m_stubVerifyCount) {

			BSLIB_LOG_TRACE(Server::ETT_SERVER_COMMON, "[ConnectCount=%d][StubCount=%d][OkeyStubCount=%d][VerifyStubCount=%d]"
				,m_tcpStubsInfor.m_connectTotal
				,m_tcpStubsInfor.m_stubCount
				,m_tcpStubsInfor.m_stubOkayCount
				,m_tcpStubsInfor.m_stubVerifyCount);

			m_tcpStubsInfor = netInfor.m_tcpStubsInfor;
	}

	return GFLib::CommonServer::CCommonServer::_callback();
}

int CGateServer::_final()
{
	return GFLib::CommonServer::CCommonServer::_final();
}

bool CGateServer::_initSystem(GFLib::CommonServer::CCommonSystemMgr* commanSystemMgr)
{
	Server::initTraceType();

	commanSystemMgr->addSystem(&GSLib::LoginSystem::GT::CLoginSystemGT::singleton());
	commanSystemMgr->addSystem(&GSLib::DBSystem::GT::CDBSystemGT::singleton());
	commanSystemMgr->addSystem(&GSLib::PlayerSystem::GT::CPlayerSystemGT::singleton());

	return GFLib::CommonServer::CCommonServer::_initSystem(commanSystemMgr);
}

bool CGateServer::_loadGameConfig(const std::string& a_configPath)
{
	return GFLib::CommonServer::CCommonServer::_loadGameConfig(a_configPath);
}

void CGateServer::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	GFLib::CommonServer::CCommonServer::_initServerMsg(a_msgExecMgr);
}

void CGateServer::_cbServerEnter(GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::CCommonServer::_cbServerEnter(a_serverID, a_key);
}

void CGateServer::_cbServerLeave(GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::CCommonServer::_cbServerLeave(a_serverID, a_key);
}

GFLib::CommonServer::CCommonClientPtr CGateServer::_cbCreateClient(GFLib::SServerID& a_serverID, const std::string& a_serverKey)
{
	switch (a_serverID.getServerType())
	{
	case GSLib::SRVTYPE_GAMESERVER:
		{
			GFLib::CommonServer::CCommonClientPtr commonClientPtr = new GFLib::CommonServer::CCommonClient(a_serverID, a_serverKey);
			return commonClientPtr;
		}
	case GSLib::SRVTYPE_CENTERSERVER:
		{
			GFLib::CommonServer::CCommonClientPtr commonClientPtr = new GFLib::CommonServer::CCommonClient(a_serverID, a_serverKey);
			return commonClientPtr;
		}
	case GSLib::SRVTYPE_LOGINSERVER:
		{
			GFLib::CommonServer::CCommonClientPtr commonClientPtr = new GFLib::CommonServer::CCommonClient(a_serverID, a_serverKey);
			return commonClientPtr;
		}
	case GSLib::SRVTYPE_DATASERVER:
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

BSLib::Network::CNetStubPtr CGateServer::_cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData)
{

	BSLib::int64 flag = (BSLib::int64)tempData;
	BSLib::Network::CNetStubPtr netStubPtr = NULL;
	switch (flag) {
		case 0:
			netStubPtr = new CGateStub(netConnPtr);
			break;
		default:
			break;
	}
	if (netStubPtr != NULL) {
		netStubPtr->setNeedPing(getNeedPing());
	}
	return netStubPtr;
}
