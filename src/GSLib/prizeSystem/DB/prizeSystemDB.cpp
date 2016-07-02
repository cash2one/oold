#include <GSLib/prizeSystem/DB/prizeSystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/prizeSystem/DB/tablePrizeDB.h>


namespace GSLib
{

namespace PrizeSystem
{	

namespace DB
{

BSLIB_SINGLETON_DEFINE(CPrizeSystemDB);

CPrizeSystemDB::CPrizeSystemDB()
{
	;
}

CPrizeSystemDB::~CPrizeSystemDB()
{
	;
}

bool CPrizeSystemDB::_init()
{	
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CPrizeSystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CPrizeSystemDB::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CPrizeSystemDB::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CPrizeSystemDB::_ICommonSystem_startSystem()
{	
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER,
		GSLib::EFUNCTYPE_PRIZESYSTEM, EMODULECTYPE_PRIZE, EDBABLEID_ROLE_PRIZE_DATA);

	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_startSystem();
}

void CPrizeSystemDB::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CPrizeSystemDB::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

}//DB

}//PrizeSystem

}//GSLib
