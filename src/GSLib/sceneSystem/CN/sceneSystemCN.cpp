//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	src\GSLib\sceneSystem\CN\sceneSystemCN.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/tracer.h>
#include <GSLib/sceneSystem/CN/sceneSystemCN.h>
#include <GSLib/sceneSystem/CN/roleSceneModuleCN.h>
#include <GSLib/playerSystem/CN/roleModuleCNMgr.h>

namespace GSLib
{

namespace SceneSystem
{	

namespace CN
{
BSLIB_SINGLETON_DEFINE(CSceneSystemCN);

CSceneSystemCN::CSceneSystemCN()
{
	;
}

CSceneSystemCN::~CSceneSystemCN()
{
	;
}

bool CSceneSystemCN::_init()
{
	GSLib::PlayerSystem::CN::CRoleModuleCNMgr::singleton().addCreateRoleModuleFun(EMODULECTYPE_SCENE, GSLib::PlayerSystem::CN::createRoleModuleFun<CRoleSceneModuleCN>);
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CSceneSystemCN::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CSceneSystemCN::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CSceneSystemCN::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CSceneSystemCN::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CSceneSystemCN::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CSceneSystemCN::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

}//CN

}//SceneSystem

}//GSLib
