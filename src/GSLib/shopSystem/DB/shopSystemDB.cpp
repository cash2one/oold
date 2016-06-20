#include <GSLib/shopSystem/DB/shopSystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/shopSystem/DB/tableShopDB.h>


namespace GSLib
{

namespace ShopSystem
{	

namespace DB
{

BSLIB_SINGLETON_DEFINE(CShopSystemDB);

CShopSystemDB::CShopSystemDB()
{
	;
}

CShopSystemDB::~CShopSystemDB()
{
	;
}

bool CShopSystemDB::_init()
{	
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CShopSystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CShopSystemDB::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CShopSystemDB::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CShopSystemDB::_startSystem()
{	
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER,
		GSLib::EFUNCTYPE_SHOPSYSTEM, EMODULETYPE_SHOP, EDBTABLEID_ROLE_SHOP_DATA);

	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CShopSystemDB::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CShopSystemDB::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

}//DB

}

}//GSLib
