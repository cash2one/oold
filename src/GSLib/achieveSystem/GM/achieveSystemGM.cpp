#include <GSLib/achieveSystem/GM/achieveSystemGM.h>
#include <GSLib/achieveSystem/GM/achieveDataGMMgr.h>
#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include <GSLib/achieveSystem/GM/achieveModule.h>
namespace GSLib
{

namespace AchieveSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CAchieveSystemGM);

CAchieveSystemGM::CAchieveSystemGM()
{
	;
}

CAchieveSystemGM::~CAchieveSystemGM()
{
	;
}

bool CAchieveSystemGM::_init()
{
    GSLib::PlayerSystem::GM::CRoleModuleGMMgr::singleton().addCreateRoleModuleFun(EMODULECTYPE_ACHIEVE, GSLib::PlayerSystem::GM::createRoleModuleFun<CAchieveModule>);
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CAchieveSystemGM::_final()
{
	CAchieveConfigDataGMMgr::singleton().final();
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CAchieveSystemGM::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	if (!CAchieveConfigDataGMMgr::singleton().loadGameConfig(a_configPath)){
		return false;
	}
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CAchieveSystemGM::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}

bool CAchieveSystemGM::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CAchieveSystemGM::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CAchieveSystemGM::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerLeave(a_serverID, a_key);
}

}//GM

}//AchieveSystem

}//GSLib

