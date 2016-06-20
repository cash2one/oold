#include <GSLib/shopSystem/CN/roleShopModuleCN.h>
#include <GSLib/shopSystem/CN/msgShopSystemCN.h>
#include <GSLib/playerSystem/CN/playerCN.h>
#include <GSLib/shopSystem/CN/shopSystemCN.h>
#include <GSLib/shopSystem/GM/msgShopSystemGM.h>

namespace GSLib
{
namespace ShopSystem
{

namespace CN
{

	CRoleShopModuleCN::CRoleShopModuleCN(GSLib::PlayerSystem::CN::CRoleCN* a_roleCN, EModuleType a_moduleType)
		:GSLib::PlayerSystem::CN::CRoleModuleCN(a_roleCN, a_moduleType)
	{

	}

	CRoleShopModuleCN::~CRoleShopModuleCN()
	{

	}

	void CRoleShopModuleCN::preInit(bool isFirst)
	{
	
	}

	void CRoleShopModuleCN::postInit(bool isFirst)
	{

	}

	void CRoleShopModuleCN::initToClient()
	{

	}

	void CRoleShopModuleCN::init(bool isFirst)
	{

	}

	void CRoleShopModuleCN::final()
	{

	}

	void CRoleShopModuleCN::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
	{
	}

	void CRoleShopModuleCN::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
	{
	}

	void CRoleShopModuleCN::updateDataToDB()
	{

	}

	void CRoleShopModuleCN::cbSelectTableData(BSLib::uint32 a_sessionID, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream)
	{

	}

}


}
}