#include <GSLib/playerSystem/GT/playerSystemGT.h>
#include <GSLib/playerSystem/GT/playerGTMgr.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace GT
{

BSLIB_SINGLETON_DEFINE(CPlayerSystemGT);

CPlayerSystemGT::CPlayerSystemGT()
{
	;
}

CPlayerSystemGT::~CPlayerSystemGT()
{
	;
}

bool CPlayerSystemGT::_init()
{
	CPlayerGTMgr::singleton().init();
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CPlayerSystemGT::_final()
{
	CPlayerGTMgr::singleton().final();
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CPlayerSystemGT::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CPlayerSystemGT::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CPlayerSystemGT::_ICommonSystem_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_startSystem();
}

void CPlayerSystemGT::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CPlayerSystemGT::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

}//GT

}//PlayerSystem

}//GSLib

