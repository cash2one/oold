//////////////////////////////////////////////////////////////////////
//	created:	2014/09/26
//	filename: 	src\GSLib\skillSystem\DB\skillSystemDB.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/skillSystem/DB/skillSystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/skillSystem/DB/tableSkillDB.h>


namespace GSLib
{

namespace SkillSystem
{	

namespace DB
{

BSLIB_SINGLETON_DEFINE(CSkillSystemDB);

CSkillSystemDB::CSkillSystemDB()
{
	;
}

CSkillSystemDB::~CSkillSystemDB()
{
	;
}

bool CSkillSystemDB::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CSkillSystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CSkillSystemDB::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CSkillSystemDB::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CSkillSystemDB::_startSystem()
{
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_SKILLPSYSTEM, EMODULECTYPE_SKILL, EDBTABLEID_ROLE_SKILL_DATA);
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CSkillSystemDB::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CSkillSystemDB::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

}//DB

}//SkillSystem

}//GSLib
