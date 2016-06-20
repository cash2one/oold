#include <GSLib/masterSystem/CN/roleMasterModuleCN.h>
#include <GSLib/masterSystem/CN/msgMasterSystemCN.h>
#include <GSLib/playerSystem/CN/playerCN.h>
#include <GSLib/masterSystem/CN/masterSystemCN.h>
#include <GSLib/masterSystem/GM/msgMasterSystemGM.h>

namespace GSLib
{
namespace MasterSystem
{

namespace CN
{

CRoleMasterModuleCN::CRoleMasterModuleCN(GSLib::PlayerSystem::CN::CRoleCN* a_roleCN, EModuleType a_moduleType)
	:GSLib::PlayerSystem::CN::CRoleModuleCN(a_roleCN, a_moduleType)
{

}

CRoleMasterModuleCN::~CRoleMasterModuleCN()
{

}

void CRoleMasterModuleCN::preInit(bool isFirst)
{

}

void CRoleMasterModuleCN::postInit(bool isFirst)
{

}

void CRoleMasterModuleCN::initToClient()
{

}

void CRoleMasterModuleCN::init(bool isFirst)
{

}

void CRoleMasterModuleCN::final()
{

}

void CRoleMasterModuleCN::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
}

void CRoleMasterModuleCN::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
}

void CRoleMasterModuleCN::updateDataToDB()
{

}

void CRoleMasterModuleCN::cbSelectTableData(BSLib::uint32 a_sessionID, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream)
{

}

}


}
}