#include <GSLib/playerSystem/CN/playerSystemCN.h>
#include <GSLib/playerSystem/CN/roleBagModuleCN.h>
#include <GSLib/playerSystem/msgPlayerSystem.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/playerSystem/CN/roleCN.h>
#include <GSLib/playerSystem/CN/playerCN.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace CN
{
CRoleBagModuleCN::CRoleBagModuleCN(CRoleCN* a_roleCN, EModuleType a_moduleType)
: CRoleModuleCN(a_roleCN, a_moduleType)
{

}

CRoleBagModuleCN::~CRoleBagModuleCN()
{
}

void CRoleBagModuleCN::preInit(bool isFirst)
{
}

void CRoleBagModuleCN::postInit(bool isFirst)
{
}

void CRoleBagModuleCN::initToClient()
{

}

void CRoleBagModuleCN::final()
{
	;
}

void CRoleBagModuleCN::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
}

void CRoleBagModuleCN::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{

}


void CRoleBagModuleCN::updateDataToDB()
{
}

bool CRoleBagModuleCN::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	return true;
}

bool CRoleBagModuleCN::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	return true;
}

bool CRoleBagModuleCN::updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave)
{
    CRoleCN* role = getRoleCN();
    if(role == NULL){
        return false;
    }
	const SRoleKey& roleKey = role->getRoleKey();
	std::string tableKey = roleKey.getDBKey();
	if (!GSLib::PlayerSystem::CN::CPlayerSystemCN::singleton().updateTableData(tableKey, a_tableIndex, a_name, a_tableID, a_stream, a_needSave)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新表[TableID=%d]失败%s", a_tableID, roleKey.toLogString().c_str());
		return false;
	}
	return true;
}

bool CRoleBagModuleCN::updateTableData(EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize, bool a_needSave)
{
	if (!GSLib::PlayerSystem::CN::CPlayerSystemCN::singleton().updateTableData("", "", "", a_tableID, a_data, a_dataSize, a_needSave)) {
        CRoleCN* role = getRoleCN();
        if(role == NULL){
            return false;
        }
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新表[TableID=%d]失败%s", a_tableID, role->getRoleKey().toLogString().c_str());
		return false;
	}
	return true;
}

}//CN

}//PlayerSystem

}//GSLib
