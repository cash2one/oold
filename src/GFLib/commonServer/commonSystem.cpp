#include <GFLib/commonServer/commonSystem.h>

namespace GFLib
{

namespace CommonServer
{

ICommonSystem::ICommonSystem()
{
	;
}

ICommonSystem::~ICommonSystem()
{
	;
}

bool ICommonSystem::_init()
{
	return true;
}

void ICommonSystem::_final()
{
	;
}

bool ICommonSystem::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return true;
}

bool ICommonSystem::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return true;
}

bool ICommonSystem::_ICommonSystem_initCommand(BSLib::Utility::CCmdExecMgr* a_cmdExecMgr)
{
	return true;
}

bool ICommonSystem::_ICommonSystem_prepStartSystem()
{
	return true;
}

bool ICommonSystem::_ICommonSystem_startSystem()
{
	return true;
}

bool ICommonSystem::_ICommonSystem_postStartSystem()
{
	return true;
}

void ICommonSystem::ICommonSystem_cbServerEnter(const SServerID& a_serverID, const std::string& a_key)
{
	;
}

void ICommonSystem::ICommonSystem_cbServerLeave(const SServerID& a_serverID, const std::string& a_key)
{
	;
}

}//CommonServe

}//GFLib
