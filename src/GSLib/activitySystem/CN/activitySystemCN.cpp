#include <GSLib/activitySystem/CN/activitySystemCN.h>
#include <BSLib/utility/dateTime.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <sstream>
#include <time.h>
#include <GSLib/activitySystem/GM/msgActivitySystemGM.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/activitySystem/msgActivitySystem.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/playerSystem/CN/playerCN.h>
#include <GSLib/playerSystem/CN/playerCNMgr.h>
#include <GSLib/playerSystem/CN/roleModuleCNMgr.h>
#include <GSLib/activitySystem/CN/roleActivityModuleCN.h>

namespace GSLib
{

namespace ActivitySystem
{

namespace CN
{

BSLIB_SINGLETON_DEFINE(CActivitySystemCN);

CActivitySystemCN::CActivitySystemCN()
{	

}

CActivitySystemCN::~CActivitySystemCN()
{
	;
}

void CActivitySystemCN::update(BSLib::uint64 a_delayMilliseconds)
{
	;
}

bool CActivitySystemCN::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CActivitySystemCN::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CActivitySystemCN::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CActivitySystemCN::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{	
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}


bool CActivitySystemCN::_startSystem()
{	
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CActivitySystemCN::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	return GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CActivitySystemCN::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}



}//GM

}

}//GSLib
