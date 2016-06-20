//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	src\GSLib\playerSystem\LG\playerSystemLG.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
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

bool CPlayerSystemLG::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CPlayerSystemLG::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CPlayerSystemLG::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CPlayerSystemLG::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CPlayerSystemLG::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

}//LG

}//PlayerSystem

}//GSLib
