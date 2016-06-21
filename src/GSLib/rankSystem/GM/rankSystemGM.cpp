#include <GSLib/rankSystem/GM/rankSystemGM.h>
#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include <GSLib/rankSystem/GM/roleRankModule.h>

namespace GSLib
{

namespace RankSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CRankSystemGM);

CRankSystemGM::CRankSystemGM()
{
	;
}

CRankSystemGM::~CRankSystemGM()
{
	;
}

void CRankSystemGM::update(BSLib::uint64 a_delayMilliseconds)
{
	;
}

bool CRankSystemGM::_init()
{
	GSLib::PlayerSystem::GM::CRoleModuleGMMgr::singleton().addCreateRoleModuleFun(EMODULECTYPE_RANK, GSLib::PlayerSystem::GM::createRoleModuleFun<CRoleRankModule>);

	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CRankSystemGM::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CRankSystemGM::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CRankSystemGM::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CRankSystemGM::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CRankSystemGM::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::CCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CRankSystemGM::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::CCommonSystem::_cbServerLeave(a_serverID, a_key);
}

}//GM

}//RankSystem

}//GSLib

