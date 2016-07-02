#include <BSLib/utility/random.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/stubMgr.h>
#include <GFLib/commonServer/message/msgLabel.h>
#include <GSLib/funType.h>
#include <GSLib/loginSystem/GM/loginSystemGM.h>
#include <GSLib/dbSystem/GM/dbSystemGM.h>
#include <GSLib/playerSystem/GM/playerSystemGM.h>
#include <GSLib/sceneSystem/GM/sceneSystemGM.h>
#include <GSLib/equipSystem/GM/equipSystemGM.h>
#include <GSLib/itemSystem/GM/itemSystemGM.h>
#include <GSLib/skillSystem/GM/skillSystemGM.h>
#include <GSLib/npcSystem/GM/npcSystemGM.h>
#include <GSLib/petSystem/GM/petSystemGM.h>
#include <GSLib/prizeSystem/GM/prizeSystemGM.h>
#include <GSLib/taskSystem/GM/taskSystemGM.h>
#include <GSLib/chatSystem/GM/chatSystemGM.h>
#include <GSLib/mailSystem/GM/mailSystemGM.h>
#include <GSLib/rankSystem/GM/rankSystemGM.h>
#include <GSLib/taskSystem/GM/msgTaskSystemGM.h>
#include <GSLib/shopSystem/GM/shopSystemGM.h>
#include <GSLib/activitySystem/GM/activitySystemGM.h>
#include <GSLib/friendSystem/GM/friendSystemGM.h>
#include <GSLib/achieveSystem/GM/achieveSystemGM.h>
#include <GSLib/uniqueIDType.h>
#include <GSLib/masterSystem/GM/masterSystemGM.h>


#include "gameServer.h"
#include "common/tracer.h"
#include "common/serverDef.hpp"

#if defined(_DEBUG) && defined(_VLD)
#undef _DLL
#include <vld/inc/vld.h>
#endif

BSLIB_FRAMEWORK_MAIN(CGameServer::main);

BSLIB_SINGLETON_DEFINE(CGameServer);

#ifndef GAMESERVER_MAJOR_VERSION
#define GAMESERVER_MAJOR_VERSION 0
#endif

#ifndef GAMESERVER_MINOR_VERSION
#define GAMESERVER_MINOR_VERSION 0
#endif

#ifndef GAMESERVER_MICRO_VERSION
#define GAMESERVER_MICRO_VERSION 0
#endif

#define _TEXT__(x) #x
#define _TEXT_(x) _TEXT__(x)

#define GAMESERVER_VERSION_TEXT _TEXT_(GAMESERVER_MAJOR_VERSION)"."_TEXT_(GAMESERVER_MINOR_VERSION)"."_TEXT_(GAMESERVER_MICRO_VERSION)

#define  GAMESERVER_MSGQUEUE_WAIT_TIMEOUT 15

CGameServer::CGameServer()
{
	Server::initServerType();
}

CGameServer::~CGameServer()
{
	;
}

GFLib::ServerType CGameServer::ICommonServer_getServerType()
{
	return GSLib::SRVTYPE_GAMESERVER;
}

std::string CGameServer::ICommonServer_getServerVersion()
{
	BSLib::Utility::CStringA strVersion;
	strVersion += GAMESERVER_VERSION_TEXT;
	return strVersion;
}

int CGameServer::main()
{
	return CGameServer::singleton()._IThread_main();
}

bool CGameServer::_IThread_init()
{
	return GFLib::CommonServer::ICommonServer::_IThread_init();
}

bool CGameServer::_IThread_callback()
{
	BSLib::int64 delayTimer = GFLib::CommonServer::ICommonServer::getDelayTimer();
	
	GFLib::CommonServer::ICommonServer::_parseMsg();
	
	GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().update(delayTimer);
	GSLib::SceneSystem::GM::CSceneSystemGM::singleton().update(delayTimer);
	GSLib::NPCSystem::GM::CNPCSystemGM::singleton().update(delayTimer);
	GSLib::PetSystem::GM::CPetSystemGM::singleton().update(delayTimer);
	GSLib::PrizeSystem::GM::CPrizeSystemGM::singleton().update(delayTimer);

	//GFLib::CommonServer::CEventMgr::singleton().updateEvent();

//	GFLib::CommonServer::ICommonServer::_parseMsg();
	

//  	BSLib::uint64 id = GFLib::CommonServer::CUniqueIDMgr::singleton().getInt64ZoneUniqueID(GSLib::EUNIQUEIDTYPE_MAILID);
//  	BSLIB_LOG_DEBUG(Server::ETT_SERVER_COMMON, "@@@@@@@[%llX]", id);

	return true;
}

int CGameServer::_IThread_final()
{
	return GFLib::CommonServer::ICommonServer::_IThread_final();
}

bool CGameServer::ICommonServer_initSystem(GFLib::CommonServer::CCommonSystemMgr* commanSystemMgr)
{
	Server::initTraceType();

	commanSystemMgr->addSystem(&GSLib::LoginSystem::GM::CLoginSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::DBSystem::GM::CDBSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::SceneSystem::GM::CSceneSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::EquipSystem::GM::CEquipSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::ItemSystem::GM::CItemSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::SkillSystem::GM::CSkillSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::NPCSystem::GM::CNPCSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::PetSystem::GM::CPetSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::PrizeSystem::GM::CPrizeSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::TaskSystem::GM::CTaskSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::ChatSystem::GM::CChatSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::MailSystem::GM::CMailSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::RankSystem::GM::CRankSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::ShopSystem::GM::CShopSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::ActivitySystem::GM::CActivitySystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::FriendSystem::GM::CFriendSystemGM::singleton());
    commanSystemMgr->addSystem(&GSLib::AchieveSystem::GM::CAchieveSystemGM::singleton());
	commanSystemMgr->addSystem(&GSLib::MasterSystem::GM::CMasterSystemGM::singleton());

	return GFLib::CommonServer::ICommonServer::ICommonServer_initSystem(commanSystemMgr);
}

bool CGameServer::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return true;
}

void CGameServer::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	GFLib::CommonServer::ICommonServer::ICommonServer_initServerMsg(a_msgExecMgr);
}

void CGameServer::ICommonServer_cbServerEnter(GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::ICommonServer::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CGameServer::ICommonServer_cbServerLeave(GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::ICommonServer::ICommonServer_cbServerLeave(a_serverID, a_key);
}

GFLib::CommonServer::CCommonClientPtr CGameServer::_ICommonServer_cbCreateClient(GFLib::SServerID& a_serverID, const std::string& a_serverKey)
{
	switch (a_serverID.ICommonServer_getServerType())
	{
	case GSLib::SRVTYPE_CENTERSERVER:
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

	return GFLib::CommonServer::ICommonServer::_ICommonServer_cbCreateClient(a_serverID, a_serverKey);
}

BSLib::Network::CNetStubPtr CGameServer::_INetServer_cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData)
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

