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

bool CPetSystemDB::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CPetSystemDB::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}

bool CPetSystemDB::_startSystem()
{
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_PETSYSTEM, EMODULECTYPE_PET, EDBTABLEID_ROLE_PET_DATA,"");
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CPetSystemDB::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CPetSystemDB::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerLeave(a_serverID, a_key);
}


}//LG

}//PetSystem

}//GSLib

