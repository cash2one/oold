#include <GSLib/activitySystem/DB/activitySystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/activitySystem/DB/tableActivityDB.h>


namespace GSLib
{

namespace ActivitySystem
{	

namespace DB
{


CActivitySystemDB::CActivitySystemDB()
{
	;
}

CActivitySystemDB::~CActivitySystemDB()
{
	;
}

BSLIB_SINGLETON_DEFINE(CActivitySystemDB);

BSLib::uint16 CActivitySystemDB::getFuncType()
{
	return GSLib::EFUNCTYPE_ACTIVITYSYSTEM;
}

bool CActivitySystemDB::_init()
{	
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CActivitySystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CActivitySystemDB::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CActivitySystemDB::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}

bool CActivitySystemDB::_startSystem()
{	
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_ACTIVITYSYSTEM, EMODULETYPE_ACTIVITY, EDBABLEID_ROLE_ATTENDENCE_DATA);
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_ACTIVITYSYSTEM, EMODULETYPE_ACTIVITY, EDBTABLEID_ROLE_DRAW_CARD_DATA);
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CActivitySystemDB::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CActivitySystemDB::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerLeave(a_serverID, a_key);
}


}//DB

}

}//GSLib

