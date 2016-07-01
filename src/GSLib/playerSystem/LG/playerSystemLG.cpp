#include <GSLib/playerSystem/LG/playerSystemLG.h>


namespace GSLib
{

namespace PlayerSystem
{	

namespace LG
{

BSLIB_SINGLETON_DEFINE(CPlayerSystemLG);

CPlayerSystemLG::CPlayerSystemLG()
{
	;
}

CPlayerSystemLG::~CPlayerSystemLG()
{
	;
}

bool CPlayerSystemLG::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CPlayerSystemLG::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CPlayerSystemLG::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CPlayerSystemLG::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}

bool CPlayerSystemLG::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CPlayerSystemLG::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CPlayerSystemLG::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerLeave(a_serverID, a_key);
}

}//LG

}//PlayerSystem

}//GSLib

