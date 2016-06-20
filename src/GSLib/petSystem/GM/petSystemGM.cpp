//////////////////////////////////////////////////////////////////////
//	created:	2014/09/10
//	filename: 	src\GSLib\petSystem\GM\petSystemGM.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
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

bool CPetSystemGM::_loadGameConfig(const std::string& a_configPath)
{
    if(!CPetConfigGMMgr::singleton().loadGameConfig(a_configPath)){
        return false;
    }
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CPetSystemGM::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CPetSystemGM::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CPetSystemGM::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CPetSystemGM::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

BSLib::Utility::CTimerServer* CPetSystemGM::getTimerServer()
{
    return _getTimerServer();
}




}//GM

}//PetSystem

}//GSLib
