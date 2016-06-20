#include <GSLib/masterSystem/DB/masterSystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/masterSystem/DB/tableMasterDB.h>


namespace GSLib
{

namespace MasterSystem
{	

namespace DB
{

BSLIB_SINGLETON_DEFINE(CMasterSystemDB);

CMasterSystemDB::CMasterSystemDB()
{
	;
}

CMasterSystemDB::~CMasterSystemDB()
{
	;
}

bool CMasterSystemDB::_init()
{	
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CMasterSystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CMasterSystemDB::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CMasterSystemDB::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CMasterSystemDB::_startSystem()
{	
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CMasterSystemDB::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CMasterSystemDB::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

}//DB

}

}//GSLib
