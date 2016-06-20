
#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include <GSLib/friendSystem/GM/friendSystemGM.h>
#include <GSLib/playerSystem/GM/playerGMMgr.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/friendSystem/msgFriendSystem.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/friendSystem/GM/roleFriendModule.h>

namespace GSLib
{

namespace FriendSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CFriendSystemGM);

CFriendSystemGM::CFriendSystemGM()
{	

}

CFriendSystemGM::~CFriendSystemGM()
{
	;
}

void CFriendSystemGM::update(BSLib::uint64 a_delayMilliseconds)
{
}

bool CFriendSystemGM::_init()
{	
	GSLib::PlayerSystem::GM::CRoleModuleGMMgr::singleton().addCreateRoleModuleFun(EMODULETYPE_FRIEND,
		GSLib::PlayerSystem::GM::createRoleModuleFun<CRoleFriendModule>);

	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CFriendSystemGM::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CFriendSystemGM::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CFriendSystemGM::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{	
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CFriendSystemGM::_startSystem()
{	
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CFriendSystemGM::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::CCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CFriendSystemGM::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::CCommonSystem::_cbServerLeave(a_serverID, a_key);
}


}//GM

}

}//GSLib
