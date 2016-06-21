#include <GSLib/itemSystem/GM/itemSystemGM.h>
#include <GSLib/itemSystem/GM/itemGMMgr.h>
namespace GSLib
{

namespace ItemSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CItemSystemGM);

CItemSystemGM::CItemSystemGM()
{
	;
}

CItemSystemGM::~CItemSystemGM()
{
	;
}

bool CItemSystemGM::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CItemSystemGM::_final()
{
	CItemGMMgr::singleton().final();
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CItemSystemGM::_loadGameConfig(const std::string& a_configPath)
{
	if (!CItemGMMgr::singleton().loadGameConfig(a_configPath)){
		return false;
	}
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CItemSystemGM::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CItemSystemGM::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CItemSystemGM::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CItemSystemGM::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

}//GM

}//ItemSystem

}//GSLib

