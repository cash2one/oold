//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	src\GSLib\playerSystem\GT\playerSystemGT.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
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

bool CPlayerSystemGT::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CPlayerSystemGT::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CPlayerSystemGT::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CPlayerSystemGT::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CPlayerSystemGT::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

}//GT

}//PlayerSystem

}//GSLib
