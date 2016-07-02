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

bool CRankSystemGM::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CRankSystemGM::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CRankSystemGM::_ICommonSystem_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_startSystem();
}

void CRankSystemGM::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::ICommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CRankSystemGM::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::ICommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

}//GM

}//RankSystem

}//GSLib

