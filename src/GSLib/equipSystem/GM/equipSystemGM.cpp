#include <BSLib/framework/message/msgExecMgr.h>
#include <GSLib/equipSystem/GM/equipSystemGM.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/tracer.h>
#include <GSLib/serverType.h>
#include <GSLib/funType.h>
#include <GSLib/loginSystem/GM/netPlayerGMMgr.h>
#include <GSLib/loginSystem/GM/netPlayerGM.h>
#include <GSLib/equipSystem/GM/equipSystemGM.h>
#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include <GSLib/equipSystem/GM/roleEquipModule.h>
#include "equipConfigGMMgr.h"

namespace GSLib
{

namespace EquipSystem
{	

namespace GM
{

BSLIB_SINGLETON_DEFINE(CEquipSystemGM);

CEquipSystemGM::CEquipSystemGM()
{
	;
}

CEquipSystemGM::~CEquipSystemGM()
{
	;
}

bool CEquipSystemGM::_init()
{
	GSLib::PlayerSystem::GM::CRoleModuleGMMgr::singleton().addCreateRoleModuleFun(EMODULECTYPE_EQUIP, GSLib::PlayerSystem::GM::createRoleModuleFun<CRoleEquipModule>);

    GSLib::DBSystem::CDBCommonSystem::_init();
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CEquipSystemGM::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CEquipSystemGM::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CEquipSystemGM::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}

bool CEquipSystemGM::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CEquipSystemGM::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CEquipSystemGM::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerLeave(a_serverID, a_key);
}

}//GM

}//EquipSystem

}//GSLib

