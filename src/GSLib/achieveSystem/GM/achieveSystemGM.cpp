//////////////////////////////////////////////////////////////////////
//	created:	2014/09/09
//	filename: 	src\GSLib\achieveSystem\GM\achieveSystemGM.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
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

bool CAchieveSystemGM::_loadGameConfig(const std::string& a_configPath)
{
	if (!CAchieveConfigDataGMMgr::singleton().loadGameConfig(a_configPath)){
		return false;
	}
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CAchieveSystemGM::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CAchieveSystemGM::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CAchieveSystemGM::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CAchieveSystemGM::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

}//GM

}//AchieveSystem

}//GSLib
