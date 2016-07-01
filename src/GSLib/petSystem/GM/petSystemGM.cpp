#include <GSLib/petSystem/GM/petSystemGM.h>
#include <GSLib/petSystem/GM/petModule.h>
#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include "petConfigGMMgr.h"

namespace GSLib
{

namespace PetSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CPetSystemGM);

CPetSystemGM::CPetSystemGM()
{
	;
}

CPetSystemGM::~CPetSystemGM()
{
	;
}

void CPetSystemGM::update(BSLib::uint64 a_delayMilliseconds)
{
	;
}

bool CPetSystemGM::_init()
{
	GSLib::PlayerSystem::GM::CRoleModuleGMMgr::singleton().addCreateRoleModuleFun(EMODULECTYPE_PET, GSLib::PlayerSystem::GM::createRoleModuleFun<CPetModule>);
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CPetSystemGM::_final()
{
    CPetConfigGMMgr::singleton().final();
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CPetSystemGM::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
    if(!CPetConfigGMMgr::singleton().loadGameConfig(a_configPath)){
        return false;
    }
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CPetSystemGM::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}

bool CPetSystemGM::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CPetSystemGM::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CPetSystemGM::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerLeave(a_serverID, a_key);
}

BSLib::Utility::CTimerServer* CPetSystemGM::getTimerServer()
{
    return _getTimerServer();
}




}//GM

}//PetSystem

}//GSLib

