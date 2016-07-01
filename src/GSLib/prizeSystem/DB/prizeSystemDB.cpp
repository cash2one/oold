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

bool CPrizeSystemDB::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CPrizeSystemDB::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}

bool CPrizeSystemDB::_startSystem()
{	
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER,
		GSLib::EFUNCTYPE_PRIZESYSTEM, EMODULECTYPE_PRIZE, EDBABLEID_ROLE_PRIZE_DATA);

	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CPrizeSystemDB::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CPrizeSystemDB::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerLeave(a_serverID, a_key);
}

}//DB

}//PrizeSystem

}//GSLib
