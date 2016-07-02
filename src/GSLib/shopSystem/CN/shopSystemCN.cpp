#include <GSLib/shopSystem/CN/shopSystemCN.h>
#include <BSLib/utility/dateTime.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <sstream>
#include <time.h>
#include <GSLib/shopSystem/GM/msgShopSystemGM.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/shopSystem/msgShopSystem.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/playerSystem/CN/playerCN.h>
#include <GSLib/playerSystem/CN/playerCNMgr.h>
#include <GSLib/playerSystem/CN/roleModuleCNMgr.h>
#include <GSLib/shopSystem/CN/roleShopModuleCN.h>

namespace GSLib
{

namespace ShopSystem
{

namespace CN
{

BSLIB_SINGLETON_DEFINE(CShopSystemCN);

CShopSystemCN::CShopSystemCN()
{	

}

CShopSystemCN::~CShopSystemCN()
{
	;
}

void CShopSystemCN::update(BSLib::uint64 a_delayMilliseconds)
{
	;
}

bool CShopSystemCN::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CShopSystemCN::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CShopSystemCN::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CShopSystemCN::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{	
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}


bool CShopSystemCN::_ICommonSystem_startSystem()
{	
	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_startSystem();
}

void CShopSystemCN::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CShopSystemCN::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}



}//GM

}

}//GSLib
