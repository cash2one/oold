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

bool CItemSystemGM::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	if (!CItemGMMgr::singleton().loadGameConfig(a_configPath)){
		return false;
	}
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CItemSystemGM::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CItemSystemGM::_ICommonSystem_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_startSystem();
}

void CItemSystemGM::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CItemSystemGM::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

}//GM

}//ItemSystem

}//GSLib

