#include <GSLib/activitySystem/CN/roleActivityModuleCN.h>
#include <GSLib/activitySystem/CN/msgActivitySystemCN.h>
#include <GSLib/playerSystem/CN/playerCN.h>
#include <GSLib/activitySystem/CN/activitySystemCN.h>
#include <GSLib/activitySystem/GM/msgActivitySystemGM.h>

namespace GSLib
{
namespace ActivitySystem
{

namespace CN
{

	CRoleActivityModuleCN::CRoleActivityModuleCN(GSLib::PlayerSystem::CN::CRoleCN* a_roleCN, EModuleType a_moduleType)
		:GSLib::PlayerSystem::CN::CRoleModuleCN(a_roleCN, a_moduleType)
	{

	}

	CRoleActivityModuleCN::~CRoleActivityModuleCN()
	{

	}

	void CRoleActivityModuleCN::preInit(bool isFirst)
	{
	
	}

	void CRoleActivityModuleCN::postInit(bool isFirst)
	{

	}

	void CRoleActivityModuleCN::initToClient()
	{

	}

	void CRoleActivityModuleCN::init(bool isFirst)
	{

	}

	void CRoleActivityModuleCN::final()
	{

	}

	void CRoleActivityModuleCN::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
	{
	}

	void CRoleActivityModuleCN::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
	{
	}

	void CRoleActivityModuleCN::updateDataToDB()
	{

	}

	void CRoleActivityModuleCN::cbSelectTableData(BSLib::uint32 a_sessionID, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream)
	{

	}

}


}
}