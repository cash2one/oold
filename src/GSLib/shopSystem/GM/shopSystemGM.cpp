
#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include <GSLib/shopSystem/GM/shopSystemGM.h>
#include <GSLib/playerSystem/GM/playerGMMgr.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/shopSystem/msgShopSystem.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/shopSystem/GM/roleShopModule.h>

namespace GSLib
{

namespace ShopSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CShopSystemGM);

CShopSystemGM::CShopSystemGM()
:m_shopConfig(NULL)
{	

}

CShopSystemGM::~CShopSystemGM()
{
	;
}

void CShopSystemGM::update(BSLib::uint64 a_delayMilliseconds)
{
}

bool CShopSystemGM::_init()
{	
	GSLib::PlayerSystem::GM::CRoleModuleGMMgr::singleton().addCreateRoleModuleFun(EMODULETYPE_SHOP, GSLib::PlayerSystem::GM::createRoleModuleFun<CRoleShopModule>);

	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CShopSystemGM::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CShopSystemGM::ICommonServer_loadGameConfig(const std::string& a_configPath)
{	
	m_configPath = a_configPath;
	if(!reloadConfig())
		return false;

	if(! m_cardConfig.loadConfigFile(a_configPath))
		return false;

	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CShopSystemGM::reloadConfig()
{	
	CShopConfig* newConfig = new CShopConfig;
	if(newConfig->loadConfigFile(m_configPath))
	{
		std::swap(newConfig, m_shopConfig);
		delete newConfig;
		return true;
	}
	
	return false;
}

bool CShopSystemGM::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{	
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}

bool CShopSystemGM::_startSystem()
{	
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CShopSystemGM::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::CCommonSystem::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CShopSystemGM::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::CCommonSystem::ICommonServer_cbServerLeave(a_serverID, a_key);
}

CShopConfig& CShopSystemGM::getConfig()
{
	return *m_shopConfig;
}

}//GM

}

}//GSLib
