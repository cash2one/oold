#include <GSLib/achieveSystem/DB/achieveSystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/achieveSystem/DB/tableAchieveDB.h>


namespace GSLib
{

namespace AchieveSystem
{	

namespace DB
{

BSLIB_SINGLETON_DEFINE(CAchieveSystemDB);

CAchieveSystemDB::CAchieveSystemDB()
{
	;
}

CAchieveSystemDB::~CAchieveSystemDB()
{
	;
}

bool CAchieveSystemDB::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CAchieveSystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CAchieveSystemDB::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CAchieveSystemDB::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}

bool CAchieveSystemDB::_startSystem()
{
    GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_ACHIEVESYSTEM, EMODULECTYPE_ACHIEVE, EDBTABLEID_ROLE_ACHIEVE_DATA);
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CAchieveSystemDB::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CAchieveSystemDB::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerLeave(a_serverID, a_key);
}

}//LG

}//AchieveSystem

}//GSLib

