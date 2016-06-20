//////////////////////////////////////////////////////////////////////
//	created:	2014/09/26
//	filename: 	src\GSLib\petSystem\DB\petSystemDB.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
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

bool CPetSystemDB::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CPetSystemDB::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CPetSystemDB::_startSystem()
{
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_PETSYSTEM, EMODULECTYPE_PET, EDBTABLEID_ROLE_PET_DATA,"");
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CPetSystemDB::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CPetSystemDB::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}


}//LG

}//PetSystem

}//GSLib
