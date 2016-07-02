#include <GSLib/equipSystem/DB/equipSystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/equipSystem/DB/tableEquipDB.h>


namespace GSLib
{

namespace EquipSystem
{	

namespace DB
{

BSLIB_SINGLETON_DEFINE(CEquipSystemDB);

CEquipSystemDB::CEquipSystemDB()
{
	;
}

CEquipSystemDB::~CEquipSystemDB()
{
	;
}

bool CEquipSystemDB::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CEquipSystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CEquipSystemDB::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CEquipSystemDB::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CEquipSystemDB::_startSystem()
{
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_EQUIPSYSTEM, EMODULECTYPE_EQUIP, EDBTABLEID_ROLE_EQUIP_DATA,"");
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CEquipSystemDB::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CEquipSystemDB::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}


}//LG

}//EquipSystem

}//GSLib

