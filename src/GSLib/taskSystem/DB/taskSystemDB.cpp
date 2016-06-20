//////////////////////////////////////////////////////////////////////
//	created:	2014/10/09
//	filename: src\GSLib\taskSystem\DB\taskSystemDB.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/taskSystem/DB/taskSystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/taskSystem/DB/tableTaskDB.h>


namespace GSLib
{

namespace TaskSystem
{	

namespace DB
{

BSLIB_SINGLETON_DEFINE(CTaskSystemDB);

CTaskSystemDB::CTaskSystemDB()
{
	;
}

CTaskSystemDB::~CTaskSystemDB()
{
	;
}

bool CTaskSystemDB::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CTaskSystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CTaskSystemDB::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CTaskSystemDB::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CTaskSystemDB::_startSystem()
{
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_TASKSYSTEM, EMODULECTYPE_TASK, EDBABLEID_ROLE_DAILY_TASK_DATA);
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_TASKSYSTEM, EMODULECTYPE_TASK, EDBABLEID_ROLE_MAIN_TASK_DATA);
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_TASKSYSTEM, EMODULECTYPE_TASK, EDBABLEID_ROLE_PET_TASK_DATA);
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_TASKSYSTEM, EMODULECTYPE_TASK, EDBABLEID_ROLE_TASK_SYSTEM_DATA);

	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CTaskSystemDB::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CTaskSystemDB::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

}//DB

}//TaskSystem

}//GSLib
