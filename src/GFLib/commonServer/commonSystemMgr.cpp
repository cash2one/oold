#include <GFLib/commonServer/commonSystemMgr.h>
#include <GFLib/commonServer/tracer.h>

namespace GFLib
{

namespace CommonServer
{

BSLIB_SINGLETON_DEFINE(CCommonSystemMgr)

CCommonSystemMgr::CCommonSystemMgr()
{
	;
}

CCommonSystemMgr::~CCommonSystemMgr()
{
	;
}

bool CCommonSystemMgr::addSystem(ICommonSystem* a_commonSystem)
{
	if (a_commonSystem == NULL) {
		return false;
	}
	BSLib::uint16 funType = a_commonSystem->ICommonSystem_getFuncType(); 
	if (m_funSystemHashMap.find(funType) != m_funSystemHashMap.end()) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "增加系统功能[%d]失败", funType);
		return false;
	}
	m_funSystemHashMap.setValue(funType, a_commonSystem);
	return true;
}

ICommonSystem* CCommonSystemMgr::getSystem(BSLib::uint16 a_funType)
{
	ICommonSystem* commonSystem = NULL;
	m_funSystemHashMap.getValue(a_funType, commonSystem);
	return commonSystem;
}

bool CCommonSystemMgr::init(BSLib::Utility::CTimerServer* a_timerServer)
{
	BSLib::Utility::CHashMap<BSLib::uint16, ICommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		ICommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		if (!funSystem->_init()) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "初始系统功能[%d]失败", it->first);
			return false;
		}
		funSystem->_setTimerServer(a_timerServer);
	}
	return true;
}

void CCommonSystemMgr::final()
{
	BSLib::Utility::CHashMap<BSLib::uint16, ICommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		ICommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		funSystem->_final();
	}
	m_funSystemHashMap.clear();
}

bool CCommonSystemMgr::loadGameConfig(const std::string& a_configPath)
{
	BSLib::Utility::CHashMap<BSLib::uint16, ICommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		ICommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		if (!funSystem->ICommonSystem_loadGameConfig(a_configPath)) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "加载系统功能[%d]配置失败", it->first);
			return false;
		}
	}
	return true;
}

void CCommonSystemMgr::initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Utility::CHashMap<BSLib::uint16, ICommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		ICommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		if (!funSystem->ICommonSystem_initServerMsg(a_msgExecMgr)) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "加载系统功能[%d]消息失败", it->first);
		}
	}
}

void CCommonSystemMgr::initCommand(BSLib::Utility::CCmdExecMgr* a_cmdExecMgr)
{
	BSLib::Utility::CHashMap<BSLib::uint16, ICommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		ICommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		if (!funSystem->_ICommonSystem_initCommand(a_cmdExecMgr)) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "加载系统功能[%d]命令失败", it->first);;
		}
	}
}

bool CCommonSystemMgr::startSystem()
{
	if (!_prepStartSystem()) {
		return false;
	}
	if (!_startSystem()) {
		return false;
	}
	if (!_postStartSystem()) {
		return false;
	}
	return true;
}


void CCommonSystemMgr::cbServerEnter(const SServerID& a_serverID, const std::string& a_key)
{
	BSLib::Utility::CHashMap<BSLib::uint16, ICommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		ICommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		funSystem->ICommonSystem_cbServerEnter(a_serverID, a_key);
	}
}

void CCommonSystemMgr::cbServerLeave(const SServerID& a_serverID, const std::string& a_key)
{
	BSLib::Utility::CHashMap<BSLib::uint16, ICommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		ICommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		funSystem->ICommonSystem_cbServerLeave(a_serverID, a_key);
	}
}


bool CCommonSystemMgr::_prepStartSystem()
{
	BSLib::Utility::CHashMap<BSLib::uint16, ICommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		ICommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		if (!funSystem->_ICommonSystem_prepStartSystem()) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "预期启动系统功能[%d]失败", it->first);
			return false;
		}
	}
	return true;
}

bool CCommonSystemMgr::_startSystem()
{
	BSLib::Utility::CHashMap<BSLib::uint16, ICommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		ICommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		if (!funSystem->_ICommonSystem_startSystem()) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "启动系统功能[%d]失败", it->first);
			return false;
		}
	}
	return true;
}

bool CCommonSystemMgr::_postStartSystem()
{
	BSLib::Utility::CHashMap<BSLib::uint16, ICommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		ICommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		if (!funSystem->_ICommonSystem_postStartSystem()) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "后置启动系统功能[%d]失败", it->first);
			return false;
		}
	}
	return true;
}

}//CommonServer

}//GFLib

