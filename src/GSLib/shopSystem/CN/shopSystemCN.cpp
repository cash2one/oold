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

bool CShopSystemCN::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CShopSystemCN::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{	
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}


bool CShopSystemCN::_startSystem()
{	
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CShopSystemCN::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	return GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CShopSystemCN::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}



}//GM

}

}//GSLib
