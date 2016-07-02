#include <GSLib/npcSystem/GM/npcSystemGM.h>

namespace GSLib
{

namespace NPCSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CNPCSystemGM);

CNPCSystemGM::CNPCSystemGM()
{
	;
}

CNPCSystemGM::~CNPCSystemGM()
{
	;
}

void CNPCSystemGM::update(BSLib::uint64 a_delayMilliseconds)
{
	;
}

bool CNPCSystemGM::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CNPCSystemGM::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CNPCSystemGM::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CNPCSystemGM::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CNPCSystemGM::_ICommonSystem_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_startSystem();
}

void CNPCSystemGM::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CNPCSystemGM::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

}//GM

}//NPCSystem

}//GSLib

