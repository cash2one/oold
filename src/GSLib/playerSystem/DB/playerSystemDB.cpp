#include <GSLib/playerSystem/DB/playerSystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/playerSystem/DB/msgPlayerSystemDB.h>
#include <GSLib/tracer.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace DB
{

BSLIB_SINGLETON_DEFINE(CPlayerSystemDB);

CPlayerSystemDB::CPlayerSystemDB()
{
	;
}

CPlayerSystemDB::~CPlayerSystemDB()
{
	;
}

bool CPlayerSystemDB::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CPlayerSystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CPlayerSystemDB::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CPlayerSystemDB::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CPlayerSystemDB::_ICommonSystem_startSystem()
{
    GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByGlobal(GSLib::SRVTYPE_CENTERSERVER, GSLib::EFUNCTYPE_PLAYERSYSTEM, EMODULECTYPE_NULL, EDBTABLEID_ROLE_DATA,"InvalidFlag=0");
 	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByPlayer(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_PLAYERSYSTEM, EMODULECTYPE_NULL, EDBTABLEID_PLAYER_DATA);
 	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByPlayer(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_PLAYERSYSTEM, EMODULECTYPE_NULL, EDBTABLEID_ROLE_DATA,"InvalidFlag=0");
 	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_PLAYERSYSTEM, EMODULECTYPE_NULL, EDBTABLEID_ROLE_VIPGIFT_DATA);
 	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_PLAYERSYSTEM, EMODULECTYPE_BAG, EDBTABLEID_ROLE_BAG_DATA,"");

 	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_startSystem();
}

void CPlayerSystemDB::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CPlayerSystemDB::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

}//LG

}//PlayerSystem

}//GSLib

