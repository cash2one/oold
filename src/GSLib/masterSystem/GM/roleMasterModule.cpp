
#include <GSLib/masterSystem/GM/roleMasterModule.h>
#include <GSLib/masterSystem/msgMasterSystem.h>
#include <GSLib/tracer.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/masterSystem/DB/tableMasterDB.h>
#include <GSLib/masterSystem/GM/masterSystemGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <map>


namespace GSLib
{

namespace MasterSystem
{

namespace GM
{

CRoleMasterModule::CRoleMasterModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType)
:  GSLib::PlayerSystem::GM::CRoleModuleGM(a_roleGM, a_moduleType)
{
}

CRoleMasterModule::~CRoleMasterModule()
{
	;
}

void CRoleMasterModule::preInit(bool isFirst)
{	

}

void CRoleMasterModule::postInit(bool isFirst)
{

}

void CRoleMasterModule::initToClient()
{	
}

void CRoleMasterModule::final()
{
	;
}

void CRoleMasterModule::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
}

void CRoleMasterModule::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
}

void CRoleMasterModule::updateDataToDB()
{
}


}//GM

}

}//GSLib