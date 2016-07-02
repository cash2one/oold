#include <BSLib/utility/file/dirInfo.h>
#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include <GSLib/prizeSystem/GM/prizeSystemGM.h>
#include <GSLib/prizeSystem/GM/rolePrizeModule.h>
#include <GSLib/prizeSystem/GM/prizeConfig.h>
#include <GSLib/tracer.h>
#include <GSLib/playerSystem/GM/playerGMMgr.h>

namespace GSLib
{

namespace PrizeSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CPrizeSystemGM);

CPrizeSystemGM::CPrizeSystemGM()
{
	;
}

CPrizeSystemGM::~CPrizeSystemGM()
{
	;
}

void CPrizeSystemGM::update(BSLib::uint64 a_delayMilliseconds)
{
	m_dateTimer.update();
}

bool CPrizeSystemGM::_init()
{
	GSLib::PlayerSystem::GM::CRoleModuleGMMgr::singleton().addCreateRoleModuleFun(EMODULECTYPE_PRIZE, GSLib::PlayerSystem::GM::createRoleModuleFun<CRolePrizeModule>);
	
	STimeHandle handle;
	handle.m_id = 1;
	handle.m_type = EDATETIMER_DAILY;
	handle.m_hour = 00;
	handle.m_minute = 00;
	m_dateTimer.addTimer(handle, this);

	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CPrizeSystemGM::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CPrizeSystemGM::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{	
	// TODO:加载 prize xml
	std::string prizePath = a_configPath;
	prizePath += "\\prize\\t_prize_config.xml";
	BSLib::Utility::CDirInfo::standardization(prizePath);

	if( !CPrizeConfig::singleton().loadConfigFile(prizePath)){
		BSLIB_LOG_ERROR(ETT_GSLIB_PRIZESYSTEM, "加载 prize配置文件失败, %s", prizePath.c_str());
		return false;
	}

	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CPrizeSystemGM::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CPrizeSystemGM::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CPrizeSystemGM::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CPrizeSystemGM::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

void CPrizeSystemGM::cb(BSLib::uint32 a_id)
{

	using namespace GSLib::PlayerSystem::GM;
	typedef std::list<CRoleGM*> RoleList;
	RoleList roles;
	CPlayerGMMgr::singleton().getActiveRolesGM(roles);
	for(RoleList::iterator it = roles.begin(); it != roles.end(); ++it)
	{	
		CRoleGM * role = *it;
		if(NULL == role)
			continue;

		CRolePrizeModule *rolePrize = (CRolePrizeModule *)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
		if (NULL ==rolePrize)
			continue;
		
		rolePrize->initToClient();
	}
}

}//GM

}//PrizeSystem

}//GSLib

