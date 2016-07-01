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

bool CPlayerSystemGT::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CPlayerSystemGT::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}

bool CPlayerSystemGT::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CPlayerSystemGT::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CPlayerSystemGT::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerLeave(a_serverID, a_key);
}

}//GT

}//PlayerSystem

}//GSLib

