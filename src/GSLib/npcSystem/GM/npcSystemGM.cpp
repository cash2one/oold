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

bool CNPCSystemGM::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CNPCSystemGM::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CNPCSystemGM::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CNPCSystemGM::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CNPCSystemGM::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

}//GM

}//NPCSystem

}//GSLib

