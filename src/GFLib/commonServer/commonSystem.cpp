#include <GFLib/commonServer/commonSystem.h>

namespace GFLib
{

namespace CommonServer
{

CCommonSystem::CCommonSystem()
{
	;
}

CCommonSystem::~CCommonSystem()
{
	;
}

bool CCommonSystem::_init()
{
	return true;
}

void CCommonSystem::_final()
{
	;
}

bool CCommonSystem::_loadGameConfig(const std::string& a_configPath)
{
	return true;
}

bool CCommonSystem::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return true;
}

bool CCommonSystem::_initCommand(BSLib::Utility::CCmdExecMgr* a_cmdExecMgr)
{
	return true;
}

bool CCommonSystem::_prepStartSystem()
{
	return true;
}

bool CCommonSystem::_startSystem()
{
	return true;
}

bool CCommonSystem::_postStartSystem()
{
	return true;
}

void CCommonSystem::_cbServerEnter(const SServerID& a_serverID, const std::string& a_key)
{
	;
}

void CCommonSystem::_cbServerLeave(const SServerID& a_serverID, const std::string& a_key)
{
	;
}

}//CommonServe

}//GFLib
