#include <GSLib/tracer.h>
#include <GSLib/playerSystem/CN/roleCN.h>
#include <GSLib/playerSystem/CN/roleModuleCNMgr.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace CN
{


CRoleCN::CRoleCN(CPlayerCN* a_playerCN)
: m_playerCN(a_playerCN)
{
	m_playerModuleList.resize(EMODULECTYPE_MAX, NULL);
}

CRoleCN::CRoleCN(const GSLib::SRoleKey& a_roleKey, CPlayerCN* a_playerCN,BSLib::uint32 a_TPID,std::string a_roldName)
: m_playerCN(a_playerCN) 
, m_roleKey(a_roleKey)
, m_roleName(a_roldName)
, m_TPID(a_TPID)
{
	m_playerModuleList.resize(EMODULECTYPE_MAX, NULL);
}

CRoleCN::~CRoleCN()
{
	;
}

void CRoleCN::preInit(bool isFirst)
{
	_preInitModule(isFirst);
}

void CRoleCN::postInit(bool isFirst)
{
	_postInitModule(isFirst);
}

void CRoleCN::initToClient()
{
	_initToClient();
}

void CRoleCN::final()
{
	_finalModule();
}

void CRoleCN::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	_initModuleMsg(a_msgExecMgr); 
}

void CRoleCN::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	_freeModuleMsg(a_msgExecMgr);
}

void CRoleCN::updateDataToDB()
{
	_updateModuleDataToDB();
}

bool CRoleCN::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	return _cbSelectKeyTableData(a_keyTable, a_tableID, a_moduleType, a_sessionID);
}

bool CRoleCN::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	return _cbSelectKeyIndexTableData(a_keyTable, a_tableID, a_moduleType, a_sessionID);
}

void CRoleCN::_preInitModule(bool isFirst)
{
	std::vector<CRoleModuleCN*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleCN* module = m_playerModuleList[i_module];
		if (module != NULL) {
			continue;
		}
		module = CRoleModuleCNMgr::singleton().createRoleModule(this, (EModuleType)i_module);
		if (module == NULL) {
			continue;
		}
		m_playerModuleList[i_module] = module;
		module->preInit(isFirst);
	}
}

void CRoleCN::_postInitModule(bool isFirst)
{
	std::vector<CRoleModuleCN*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleCN* module = m_playerModuleList[i_module];
		if (module == NULL) {
			continue;
		}
		module->postInit(isFirst);
	}
}


void CRoleCN::_finalModule()
{
	std::vector<CRoleModuleCN*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleCN* module = m_playerModuleList[i_module];
		if (module != NULL) {
			module->final();
			BSLIB_SAFE_DELETE(module);
		}
	}
	m_playerModuleList.clear();
}

void CRoleCN::_initToClient()
{
	std::vector<CRoleModuleCN*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleCN* module = m_playerModuleList[i_module];
		if (module != NULL) {
			BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_initToClient[i_module=%d]", i_module);
			module->initToClient();
		}
	}
}

void CRoleCN::_initModuleMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	std::vector<CRoleModuleCN*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleCN* module = m_playerModuleList[i_module];
		if (module != NULL) {
			module->initMsg(a_msgExecMgr);
		}
	} 
}

void CRoleCN::_freeModuleMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	std::vector<CRoleModuleCN*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleCN* module = m_playerModuleList[i_module];
		if (module != NULL) {
			module->freeMsg(a_msgExecMgr);
		}
	} 
}

void CRoleCN::onRoleActive()
{
	_onRoleActive();
}

void CRoleCN::onRoleInactive()
{
	_onRoleInactive();
}

void CRoleCN::cbPlayerOnline()
{
	std::vector<CRoleModuleCN*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleCN* module = m_playerModuleList[i_module];
		if (module != NULL) {
			BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "cbModuleRoleOffline[i_module=%d]", i_module);
			module->cbPlayerOnline();
		}
	}
}

void CRoleCN::cbPlayerOffline()
{
	std::vector<CRoleModuleCN*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleCN* module = m_playerModuleList[i_module];
		if (module != NULL) {
			BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "cbModuleRoleOffline[i_module=%d]", i_module);
			module->cbPlayerOffline();
		}
	}
}



void CRoleCN::_onRoleActive()
{
	std::vector<CRoleModuleCN*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleCN* module = m_playerModuleList[i_module];
		if (module != NULL) {
			BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_cbModuleRoleOnline[i_module=%d]", i_module);
			module->onRoleActive();
		}
	}
}

void CRoleCN::_onRoleInactive()
{
	std::vector<CRoleModuleCN*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleCN* module = m_playerModuleList[i_module];
		if (module != NULL) {
			BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "cbModuleRoleOffline[i_module=%d]", i_module);
			module->onRoleInactive();
		}
	}
}

CRoleModuleCN* CRoleCN::getPlayerModuleCN(EModuleType a_moduleType)
{
	if (a_moduleType >= (EModuleType)m_playerModuleList.size()) {
		return NULL;
	}
	return m_playerModuleList[a_moduleType];
}

void CRoleCN::_updateModuleDataToDB()
{
	std::vector<CRoleModuleCN*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleCN* module = m_playerModuleList[i_module];
		if (module != NULL) {
			module->updateDataToDB();
		}
	}
}

bool CRoleCN::_cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	CRoleModuleCN* module = getPlayerModuleCN(a_moduleType);
	if (module == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "模块不存在[ModuleType=%d]", a_moduleType);
		return false;
	}
	return module->cbSelectKeyTableData(a_keyTable, a_tableID, a_sessionID);
}

bool CRoleCN::_cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	CRoleModuleCN* module = getPlayerModuleCN(a_moduleType);
	if (module == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "模块不存在[ModuleType=%d]", a_moduleType);
		return false;
	}
	return module->cbSelectKeyIndexTableData(a_keyTable, a_tableID, a_sessionID);
}

bool CRoleCN::isActive() const {
	return (m_roleStatus == STATUS_ACTIVE);
}

void CRoleCN::setRoleStatus(ERoleStatus a_roleStatus)
{ 
	if(a_roleStatus == m_roleStatus){
		return;
	}
	m_roleStatus = a_roleStatus;
}


}//CN

}//PlayerSystem

}//GSLib

