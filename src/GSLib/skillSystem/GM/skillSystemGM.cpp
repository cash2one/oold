#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include <GSLib/skillSystem/GM/skillSystemGM.h>
#include <GSLib/skillSystem/GM/skillAttrMgr.h>
#include <GSLib/skillSystem/GM/roleSkillModule.h>

namespace GSLib
{

namespace SkillSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CSkillSystemGM);

CSkillSystemGM::CSkillSystemGM()
{
	;
}

CSkillSystemGM::~CSkillSystemGM()
{
	;
}

bool CSkillSystemGM::_init()
{
	GSLib::PlayerSystem::GM::CRoleModuleGMMgr::singleton().addCreateRoleModuleFun(EMODULECTYPE_SKILL, GSLib::PlayerSystem::GM::createRoleModuleFun<CRoleSkillModule>);
	
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CSkillSystemGM::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CSkillSystemGM::_loadGameConfig(const std::string& a_configPath)
{
	if (!CSkillDataMgr::singleton().loadGameConfig(a_configPath)) {
		return false;;
	}
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CSkillSystemGM::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CSkillSystemGM::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CSkillSystemGM::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CSkillSystemGM::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

}//GM

}//SkillSystem

}//GSLib

