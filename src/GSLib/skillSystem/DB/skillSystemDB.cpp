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

bool CSkillSystemDB::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CSkillSystemDB::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CSkillSystemDB::_ICommonSystem_startSystem()
{
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_SKILLPSYSTEM, EMODULECTYPE_SKILL, EDBTABLEID_ROLE_SKILL_DATA);
	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_startSystem();
}

void CSkillSystemDB::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CSkillSystemDB::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

}//DB

}//SkillSystem

}//GSLib

