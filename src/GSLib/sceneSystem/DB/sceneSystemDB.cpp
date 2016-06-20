//////////////////////////////////////////////////////////////////////
//	created:	2014/11/6
//	filename: 	src\GSLib\sceneSystem\DB\sceneSystemDB.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/sceneSystem/DB/sceneSystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/sceneSystem/DB/tableSceneDB.h>


namespace GSLib
{

namespace SceneSystem
{	

namespace DB
{

BSLIB_SINGLETON_DEFINE(CSceneSystemDB);

CSceneSystemDB::CSceneSystemDB()
{
	;
}

CSceneSystemDB::~CSceneSystemDB()
{
	;
}

bool CSceneSystemDB::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CSceneSystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CSceneSystemDB::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CSceneSystemDB::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CSceneSystemDB::_startSystem()
{
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_SCENESYSTEM, EMODULECTYPE_SCENE, EDBTABLEID_ROLE_SCENE_ARENA_ROLE_DATA);
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_SCENESYSTEM, EMODULECTYPE_SCENE, EDBTABLEID_ROLE_SCENE_ARENA_CHALLENGE_RECORD);
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_SCENESYSTEM, EMODULECTYPE_SCENE, EDBTABLEID_ROLE_STORY_INSTANCE_PROGRESS_DATA);
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_SCENESYSTEM, EMODULECTYPE_SCENE, EDBTABLEID_ROLE_STAGE_DATA);
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_SCENESYSTEM, EMODULECTYPE_SCENE, EDBTABLEID_ROLE_INSTANCE_PRIZE_DATA);
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_SCENESYSTEM, EMODULECTYPE_SCENE, EDBTABLEID_ROLE_CONTINUOUS_INSTANCE_DATA);
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_SCENESYSTEM, EMODULECTYPE_SCENE, EDBTABLEID_ROLE_CONTINUOUS_INSTANCE_PROGRESS_DATA);
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_SCENESYSTEM, EMODULECTYPE_SCENE, EDBTABLEID_ROLE_CONTINUOUS_STAGE_RESULT_DATA);
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_SCENESYSTEM, EMODULECTYPE_SCENE, EDBTABLEID_ROLE_STAGE_SYSTEM_DATA);

	//center
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_CENTERSERVER, GSLib::EFUNCTYPE_SCENESYSTEM, EMODULECTYPE_SCENE, EDBTABLEID_ROLE_SCENE_ARENA_CHALLENGE_RECORD);

	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CSceneSystemDB::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CSceneSystemDB::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

}//DB

}//SceneSystem

}//GSLib
