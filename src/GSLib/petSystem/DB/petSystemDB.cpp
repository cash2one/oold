#include <GSLib/petSystem/DB/petSystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/petSystem/DB/tablePetDB.h>


namespace GSLib
{

namespace PetSystem
{	

namespace DB
{

BSLIB_SINGLETON_DEFINE(CPetSystemDB);

CPetSystemDB::CPetSystemDB()
{
	;
}

CPetSystemDB::~CPetSystemDB()
{
	;
}

bool CPetSystemDB::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CPetSystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CPetSystemDB::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CPetSystemDB::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CPetSystemDB::_ICommonSystem_startSystem()
{
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_PETSYSTEM, EMODULECTYPE_PET, EDBTABLEID_ROLE_PET_DATA,"");
	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_startSystem();
}

void CPetSystemDB::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CPetSystemDB::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}


}//LG

}//PetSystem

}//GSLib

