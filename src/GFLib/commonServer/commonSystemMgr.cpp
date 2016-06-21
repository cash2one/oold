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

bool CCommonSystemMgr::addSystem(CCommonSystem* a_commonSystem)
{
	if (a_commonSystem == NULL) {
		return false;
	}
	BSLib::uint16 funType = a_commonSystem->getFuncType(); 
	if (m_funSystemHashMap.find(funType) != m_funSystemHashMap.end()) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "����ϵͳ����[%d]ʧ��", funType);
		return false;
	}
	m_funSystemHashMap.setValue(funType, a_commonSystem);
	return true;
}

CCommonSystem* CCommonSystemMgr::getSystem(BSLib::uint16 a_funType)
{
	CCommonSystem* commonSystem = NULL;
	m_funSystemHashMap.getValue(a_funType, commonSystem);
	return commonSystem;
}

bool CCommonSystemMgr::init(BSLib::Utility::CTimerServer* a_timerServer)
{
	BSLib::Utility::CHashMap<BSLib::uint16, CCommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		CCommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		if (!funSystem->_init()) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "��ʼϵͳ����[%d]ʧ��", it->first);
			return false;
		}
		funSystem->_setTimerServer(a_timerServer);
	}
	return true;
}

void CCommonSystemMgr::final()
{
	BSLib::Utility::CHashMap<BSLib::uint16, CCommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		CCommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		funSystem->_final();
	}
	m_funSystemHashMap.clear();
}

bool CCommonSystemMgr::loadGameConfig(const std::string& a_configPath)
{
	BSLib::Utility::CHashMap<BSLib::uint16, CCommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		CCommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		if (!funSystem->_loadGameConfig(a_configPath)) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "����ϵͳ����[%d]����ʧ��", it->first);
			return false;
		}
	}
	return true;
}

void CCommonSystemMgr::initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Utility::CHashMap<BSLib::uint16, CCommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		CCommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		if (!funSystem->_initServerMsg(a_msgExecMgr)) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "����ϵͳ����[%d]��Ϣʧ��", it->first);
		}
	}
}

void CCommonSystemMgr::initCommand(BSLib::Utility::CCmdExecMgr* a_cmdExecMgr)
{
	BSLib::Utility::CHashMap<BSLib::uint16, CCommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		CCommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		if (!funSystem->_initCommand(a_cmdExecMgr)) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "����ϵͳ����[%d]����ʧ��", it->first);;
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
	BSLib::Utility::CHashMap<BSLib::uint16, CCommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		CCommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		funSystem->_cbServerEnter(a_serverID, a_key);
	}
}

void CCommonSystemMgr::cbServerLeave(const SServerID& a_serverID, const std::string& a_key)
{
	BSLib::Utility::CHashMap<BSLib::uint16, CCommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		CCommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		funSystem->_cbServerLeave(a_serverID, a_key);
	}
}


bool CCommonSystemMgr::_prepStartSystem()
{
	BSLib::Utility::CHashMap<BSLib::uint16, CCommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		CCommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		if (!funSystem->_prepStartSystem()) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "Ԥ������ϵͳ����[%d]ʧ��", it->first);
			return false;
		}
	}
	return true;
}

bool CCommonSystemMgr::_startSystem()
{
	BSLib::Utility::CHashMap<BSLib::uint16, CCommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		CCommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		if (!funSystem->_startSystem()) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "����ϵͳ����[%d]ʧ��", it->first);
			return false;
		}
	}
	return true;
}

bool CCommonSystemMgr::_postStartSystem()
{
	BSLib::Utility::CHashMap<BSLib::uint16, CCommonSystem*>::iterator it = m_funSystemHashMap.begin();
	for (; it != m_funSystemHashMap.end(); ++it) {
		CCommonSystem* funSystem = it->second;
		if (funSystem == NULL) {
			continue;
		}
		if (!funSystem->_postStartSystem()) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "��������ϵͳ����[%d]ʧ��", it->first);
			return false;
		}
	}
	return true;
}

}//CommonServer

}//GFLib

