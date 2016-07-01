#include <BSLib/utility/random.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/stubMgr.h>
#include <GFLib/commonServer/message/msgLabel.h>
#include <GSLib/funType.h>
#include <GSLib/loginSystem/DB/loginSystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/playerSystem/DB/playerSystemDB.h>
#include <GSLib/skillSystem/DB/skillSystemDB.h>
#include <GSLib/itemSystem/DB/itemSystemDB.h>
#include <GSLib/equipSystem/DB/equipSystemDB.h>
#include <GSLib/mailSystem/DB/mailSystemDB.h>
#include <GSLib/petSystem/DB/petSystemDB.h>
#include <GSLib/sceneSystem/DB/sceneSystemDB.h>
#include <GSLib/prizeSystem/DB/prizeSystemDB.h>
#include <GSLib/taskSystem/DB/taskSystemDB.h>
#include <GSLib/shopSystem/DB/shopSystemDB.h>
#include <GSLib/activitySystem/DB/activitySystemDB.h>
#include "dataServer.h"
#include "common/tracer.h"
#include "common/serverDef.hpp"
#include <GSLib/friendSystem/DB/friendSystemDB.h>
#include <GSLib/rankSystem/DB/rankSystemDB.h>
#include <GSLib/masterSystem/DB/masterSystemDB.h>

#if defined(_DEBUG) && defined(_VLD)
#undef _DLL
#include <vld/inc/vld.h>
#endif

BSLIB_FRAMEWORK_MAIN(CDataServer::main);

BSLIB_SINGLETON_DEFINE(CDataServer);

#ifndef DATASERVER_MAJOR_VERSION
#define DATASERVER_MAJOR_VERSION 0
#endif

#ifndef DATASERVER_MINOR_VERSION
#define DATASERVER_MINOR_VERSION 0
#endif

#ifndef DATASERVER_MICRO_VERSION
#define DATASERVER_MICRO_VERSION 0
#endif

#define _TEXT__(x) #x
#define _TEXT_(x) _TEXT__(x)

#define DATASERVER_VERSION_TEXT _TEXT_(DATASERVER_MAJOR_VERSION)"."_TEXT_(DATASERVER_MINOR_VERSION)"."_TEXT_(DATASERVER_MICRO_VERSION)


CDataServer::CDataServer()
{
	Server::initServerType();
}

CDataServer::~CDataServer()
{
	;
}

GFLib::ServerType CDataServer::ICommonServer_getServerType()
{
	return GSLib::SRVTYPE_DATASERVER;
}

std::string CDataServer::ICommonServer_getServerVersion()
{
	BSLib::Utility::CStringA strVersion;
	//strVersion.format("%d.", GFLib::ESRVTYPE_GATEWAY);
	strVersion += DATASERVER_VERSION_TEXT;
	return strVersion;
}

int CDataServer::main()
{
	return CDataServer::singleton()._IThread_main();
}

int CDataServer::_final()
{
	return GFLib::CommonServer::ICommonServer::_IThread_final();
}

bool CDataServer::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return true;
}

bool CDataServer::ICommonServer_initSystem(GFLib::CommonServer::CCommonSystemMgr* commanSystemMgr)
{
	Server::initTraceType();

	commanSystemMgr->addSystem(&GSLib::LoginSystem::DB::CLoginSystemDB::singleton());
	commanSystemMgr->addSystem(&GSLib::DBSystem::DB::CDBSystemDB::singleton());
	commanSystemMgr->addSystem(&GSLib::PlayerSystem::DB::CPlayerSystemDB::singleton());
	commanSystemMgr->addSystem(&GSLib::SkillSystem::DB::CSkillSystemDB::singleton());
	commanSystemMgr->addSystem(&GSLib::EquipSystem::DB::CEquipSystemDB::singleton());
	commanSystemMgr->addSystem(&GSLib::MailSystem::DB::CMailSystemDB::singleton());
	commanSystemMgr->addSystem(&GSLib::PetSystem::DB::CPetSystemDB::singleton());
	commanSystemMgr->addSystem(&GSLib::SceneSystem::DB::CSceneSystemDB::singleton());
	commanSystemMgr->addSystem(&GSLib::PrizeSystem::DB::CPrizeSystemDB::singleton());
	commanSystemMgr->addSystem(&GSLib::TaskSystem::DB::CTaskSystemDB::singleton());
	commanSystemMgr->addSystem(&GSLib::ShopSystem::DB::CShopSystemDB::singleton());
	commanSystemMgr->addSystem(&GSLib::ActivitySystem::DB::CActivitySystemDB::singleton());
	commanSystemMgr->addSystem(&GSLib::FriendSystem::DB::CFriendSystemDB::singleton());
	commanSystemMgr->addSystem(&GSLib::RankSystem::DB::CRankSystemDB::singleton());
	commanSystemMgr->addSystem(&GSLib::MasterSystem::DB::CMasterSystemDB::singleton());

	return GFLib::CommonServer::ICommonServer::ICommonServer_initSystem(commanSystemMgr);
}

void CDataServer::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	GFLib::CommonServer::ICommonServer::ICommonServer_initServerMsg(a_msgExecMgr);
}

GFLib::CommonServer::CCommonClientPtr CDataServer::_cbCreateClient(GFLib::SServerID& a_serverID, const std::string& a_serverKey)
{
	switch (a_serverID.ICommonServer_getServerType())
	{
	case GSLib::SRVTYPE_CHARGESERVER:
		{
			GFLib::CommonServer::CCommonClientPtr commonClientPtr = new GFLib::CommonServer::CCommonClient(a_serverID, a_serverKey);
			return commonClientPtr;
		}
	default:
		{
			;
		}
	}
	return GFLib::CommonServer::ICommonServer::_cbCreateClient(a_serverID, a_serverKey);
}

BSLib::Network::CNetStubPtr CDataServer::_cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData)
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

