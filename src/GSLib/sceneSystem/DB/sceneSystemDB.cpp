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

bool CSceneSystemDB::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CSceneSystemDB::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
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

void CSceneSystemDB::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CSceneSystemDB::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

}//DB

}//SceneSystem

}//GSLib

