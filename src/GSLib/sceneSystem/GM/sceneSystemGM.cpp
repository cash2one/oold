#include <GSLib/tracer.h>
#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include <GSLib/sceneSystem/GM//roleSceneModule.h>
#include <GSLib/sceneSystem/GM/sceneSystemGM.h>
#include <GSLib/sceneSystem/GM/sceneGMMgr.h>
#include <GSLib/sceneSystem/GM/sceneSystemDataMgr.h>
#include <GSLib/playerSystem/GM/playerGMMgr.h>
#include <GSLib/sceneSystem/GM/roleSceneModule.h>
#include "GM/originalSceneMgr.h"
#include "GM/btree/sceneGMBTMgr.h"
#include "GM/fsm/sceneGMFSMMgr.h"
#include <GFLib/commonServer/commonServer.h>

namespace GSLib
{

namespace SceneSystem
{	

namespace GM
{
BSLIB_SINGLETON_DEFINE(CSceneSystemGM);

CSceneSystemGM::CSceneSystemGM()
:m_lastStageEnterTimeResetTime(0)
,m_nextStageEnterTimeResetTime(0)
,m_lastDailyContinuousStageResetTime(0)
,m_nextDailyContinuousStageResetTime(0)
,m_lastRoleDailyStageHelperResetTime(0)
,m_nextRoleDailyStageHelperResetTime(0)
,m_arenaRecordIndex(0)
,m_lastArenaResetTime(0)
,m_nextArenaResetTime(0)
,m_lastInstanceStageResetTime(0)
,m_nextInstanceStageResetTime(0)
{
	;
}

CSceneSystemGM::~CSceneSystemGM()
{
	;
}

void CSceneSystemGM::update(BSLib::uint64 a_delayMilliseconds)
{
	CSceneGMMgr::singleton().update(a_delayMilliseconds);
}

bool CSceneSystemGM::_init()
{
	GFLib::CommonServer::CCommonServer* server = GFLib::CommonServer::CCommonServer::getCommonServer();
	if (server == NULL){
		return false;
	}
	m_serverID = server->getServerID().m_number;

	if (!CSceneGMBTMgr::singleton().init()) {
		return false;
	}
	if (!CSceneGMFSMMgr::singleton().init()) {
		return false;
	}
	if (!COriginalSceneMgr::singleton().init()) {
		return false;;
	}
	if (!CSceneGMMgr::singleton().init()) {
		return false;
	}
	GSLib::PlayerSystem::GM::CRoleModuleGMMgr::singleton().addCreateRoleModuleFun(EMODULECTYPE_SCENE, GSLib::PlayerSystem::GM::createRoleModuleFun<CRoleSceneModule>);
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CSceneSystemGM::_final()
{
	CSceneGMMgr::singleton().final();
	COriginalSceneMgr::singleton().final();
	CSceneGMFSMMgr::singleton().final();
	CSceneGMBTMgr::singleton().final();
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CSceneSystemGM::_loadGameConfig(const std::string& a_configPath)
{
	if (!COriginalSceneMgr::singleton().loadGameConfig(a_configPath)) {
		return false;
	}
	if (!CSceneSystemDataMgr::singleton().loadConfig(a_configPath)) {
		return false;
	}
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CSceneSystemGM::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CSceneSystemGM::_startSystem()
{
	_initContinuousStageData();
	_initStageHelperResetTimer();
	_initArenaResetTimer();
	_initInstanceStageTimer();
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CSceneSystemGM::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CSceneSystemGM::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

BSLib::int32 CSceneSystemGM::getLastContinuousStageResetTime() const
{
	return m_lastDailyContinuousStageResetTime;
}

BSLib::int32 CSceneSystemGM::getLastStageHelperResetTime() const
{
	return m_lastRoleDailyStageHelperResetTime;
}

BSLib::int32 CSceneSystemGM::getLastArenaResetTime() const
{
	return m_lastArenaResetTime;
}

BSLib::int32 CSceneSystemGM::getLastInstanceStageResetTime() const
{
	return m_lastInstanceStageResetTime;
}

BSLib::uint64 CSceneSystemGM::genArenaRecordID(BSLib::int32 a_time)
{
	return ((BSLib::uint64)m_serverID << 60) | ((BSLib::uint64)a_time << 32) | m_arenaRecordIndex++;
}

void CSceneSystemGM::_initContinuousStageData()
{
	_setDailyResetTime(m_lastDailyContinuousStageResetTime, m_nextDailyContinuousStageResetTime, 6, 0);
	BSLib::uint64 timeDelay = (m_nextDailyContinuousStageResetTime - BSLib::Utility::CDateTime::getCurrentTime().getSeconds()) *  1000;
	BSLib::uint32 timeInterval = ONE_DAY_SECONDS * 1000;
	BSLib::Utility::CTimerServer *timer = _getTimerServer();
	if (timer == NULL) {
		BSLIB_LOG_INFOR(ETT_GSLIB_ACTIVITYSYSTEM, "CSceneSystemGM::_initContinuousStageData fail, timer = [NULL]");
		return;
	}
	const BSLib::Utility::CDateTime & curDate = BSLib::Utility::CDateTime::getCurrentTime();
	timer->addTimer(&CSceneSystemGM::_onContinuousStageResetCallback, this, 0, 0, timeInterval, (BSLib::uint32)timeDelay, -1);
	BSLIB_LOG_INFOR(ETT_GSLIB_SCENESYSTEM, "---Add daily continuous stage reset timer %d-%d-%d-%d:%d delay[%dms]---", curDate.getYear(),curDate.getMonth(),curDate.getDay(), curDate.getHour(), curDate.getMinute(), timeDelay);
}

void CSceneSystemGM::_initStageHelperResetTimer()
{
	_setDailyResetTime(m_lastRoleDailyStageHelperResetTime, m_nextRoleDailyStageHelperResetTime, 0, 0);
	BSLib::uint64 timeDelay = (m_nextRoleDailyStageHelperResetTime - BSLib::Utility::CDateTime::getCurrentTime().getSeconds()) *  1000;
	BSLib::uint32 timeInterval = ONE_DAY_SECONDS * 1000;
	BSLib::Utility::CTimerServer *timer = _getTimerServer();
	if (timer == NULL) {
		BSLIB_LOG_INFOR(ETT_GSLIB_ACTIVITYSYSTEM, "CSceneSystemGM::_initStageHelperResetTimer fail, timer = [NULL]");
		return;
	}
	const BSLib::Utility::CDateTime & curDate = BSLib::Utility::CDateTime::getCurrentTime();
	timer->addTimer(&CSceneSystemGM::_onStageGetHlepResetCallback, this, 0, 0, timeInterval, (BSLib::uint32)timeDelay, -1);
	BSLIB_LOG_INFOR(ETT_GSLIB_SCENESYSTEM, "---Add daily stage helper reset timer %d-%d-%d-%d:%d delay[%dms]---", curDate.getYear(),curDate.getMonth(),curDate.getDay(), curDate.getHour(), curDate.getMinute(), timeDelay);
}

void CSceneSystemGM::_initArenaResetTimer()
{
	_setDailyResetTime(m_lastArenaResetTime, m_nextArenaResetTime, 0, 0);
	BSLib::uint64 timeDelay = (m_nextArenaResetTime - BSLib::Utility::CDateTime::getCurrentTime().getSeconds()) *  1000;
	BSLib::uint32 timeInterval = ONE_DAY_SECONDS * 1000;
	BSLib::Utility::CTimerServer *timer = _getTimerServer();
	if (timer == NULL) {
		BSLIB_LOG_INFOR(ETT_GSLIB_ACTIVITYSYSTEM, "CSceneSystemGM::_initArenaResetTimer fail, timer = [NULL]");
		return;
	}
	const BSLib::Utility::CDateTime & curDate = BSLib::Utility::CDateTime::getCurrentTime();
	timer->addTimer(&CSceneSystemGM::_onArenaResetCallback, this, 0, 0, timeInterval, (BSLib::uint32)timeDelay, -1);
	BSLIB_LOG_INFOR(ETT_GSLIB_SCENESYSTEM, "---Add Arena reset timer %d-%d-%d-%d:%d delay[%dms]---", curDate.getYear(),curDate.getMonth(),curDate.getDay(), curDate.getHour(), curDate.getMinute(), timeDelay);
}

void CSceneSystemGM::_initInstanceStageTimer()
{
	_setDailyResetTime(m_lastInstanceStageResetTime, m_nextInstanceStageResetTime, 0, 0);
	BSLib::uint64 timeDelay = (m_nextInstanceStageResetTime - BSLib::Utility::CDateTime::getCurrentTime().getSeconds()) *  1000;
	BSLib::uint32 timeInterval = ONE_DAY_SECONDS * 1000;
	BSLib::Utility::CTimerServer *timer = _getTimerServer();
	if (timer == NULL) {
		BSLIB_LOG_INFOR(ETT_GSLIB_ACTIVITYSYSTEM, "CSceneSystemGM::_initInstanceStageTimer fail, timer = [NULL]");
		return;
	}
	const BSLib::Utility::CDateTime & curDate = BSLib::Utility::CDateTime::getCurrentTime();
	timer->addTimer(&CSceneSystemGM::_onInstanceStageResetCallback, this, 0, 0, timeInterval, (BSLib::uint32)timeDelay, -1);
	BSLIB_LOG_INFOR(ETT_GSLIB_SCENESYSTEM, "---Add instance stage reset timer %d-%d-%d-%d:%d delay[%dms]---", curDate.getYear(),curDate.getMonth(),curDate.getDay(), curDate.getHour(), curDate.getMinute(), timeDelay);
}

bool CSceneSystemGM::_onContinuousStageResetCallback(BSLib::uint64 a_num, void* a_para)
{
	m_lastDailyContinuousStageResetTime = m_nextDailyContinuousStageResetTime;
	m_nextDailyContinuousStageResetTime += ONE_DAY_SECONDS;
	const BSLib::Utility::CDateTime & curDate = BSLib::Utility::CDateTime::getCurrentTime();
	BSLIB_LOG_INFOR(ETT_GSLIB_ACTIVITYSYSTEM, "---_continuousStageResetCallback %d-%d-%d-%d:%d---", curDate.getYear(),curDate.getMonth(),curDate.getDay(), curDate.getHour(), curDate.getMinute());
	std::list<GSLib::PlayerSystem::GM::CRoleGM*> listRoles;
	GSLib::PlayerSystem::GM::CPlayerGMMgr::singleton().getActiveRolesGM(listRoles);
	for (std::list<GSLib::PlayerSystem::GM::CRoleGM*>::iterator itr = listRoles.begin(); itr != listRoles.end(); ++itr) {
		GSLib::PlayerSystem::GM::CRoleGM *role = *itr;
		if (role != NULL) {
			GSLib::SceneSystem::GM::CRoleSceneModule *roleSceneModule = (GSLib::SceneSystem::GM::CRoleSceneModule *)role->getPlayerModuleGM(EMODULECTYPE_SCENE);
			if (roleSceneModule != NULL) {
				roleSceneModule->onContinuousStageDailyReset();
			}
		}
	}

	return true;
}

void CSceneSystemGM::_setDailyResetTime(BSLib::int32 & a_lastRestTime, BSLib::int32 & a_nextResetTime, BSLib::int32 a_dailyResetHour, BSLib::int32 a_dailyResetMinute)
{
	BSLib::Utility::CDateTime curDate = BSLib::Utility::CDateTime::getCurrentTime();
	BSLib::Utility::CDateTime resetDate;	
	resetDate.setDataTime(curDate.getYear(), curDate.getMonth(), curDate.getDay(), a_dailyResetHour, a_dailyResetMinute, 0);
	if (curDate.getSeconds() > resetDate.getSeconds()) {
		a_lastRestTime = (BSLib::int32)resetDate.getSeconds();
		a_nextResetTime = (BSLib::int32)resetDate.getSeconds() + ONE_DAY_SECONDS;
	} else {
		a_lastRestTime = (BSLib::int32)resetDate.getSeconds() - ONE_DAY_SECONDS;
		a_nextResetTime = (BSLib::int32)resetDate.getSeconds();
	}
}

bool CSceneSystemGM::_onStageGetHlepResetCallback(BSLib::uint64 a_num, void* a_para)
{
	m_lastRoleDailyStageHelperResetTime = m_nextRoleDailyStageHelperResetTime;
	m_nextRoleDailyStageHelperResetTime += ONE_DAY_SECONDS;
	const BSLib::Utility::CDateTime & curDate = BSLib::Utility::CDateTime::getCurrentTime();
	BSLIB_LOG_INFOR(ETT_GSLIB_ACTIVITYSYSTEM, "---_continuousStageResetCallback %d-%d-%d-%d:%d---", curDate.getYear(),curDate.getMonth(),curDate.getDay(), curDate.getHour(), curDate.getMinute());
	std::list<GSLib::PlayerSystem::GM::CRoleGM*> listRoles;
	GSLib::PlayerSystem::GM::CPlayerGMMgr::singleton().getActiveRolesGM(listRoles);
	for (std::list<GSLib::PlayerSystem::GM::CRoleGM*>::iterator itr = listRoles.begin(); itr != listRoles.end(); ++itr) {
		GSLib::PlayerSystem::GM::CRoleGM *role = *itr;
		if (role != NULL) {
			GSLib::SceneSystem::GM::CRoleSceneModule *roleSceneModule = (GSLib::SceneSystem::GM::CRoleSceneModule *)role->getPlayerModuleGM(EMODULECTYPE_SCENE);
			if (roleSceneModule != NULL) {
				roleSceneModule->onStageHelperDailyReset();
			}
		}
	}

	return true;
}

bool CSceneSystemGM::_onArenaResetCallback(BSLib::uint64 a_num, void* a_para)
{
	m_lastArenaResetTime = m_nextArenaResetTime;
	m_nextArenaResetTime += ONE_DAY_SECONDS;
	const BSLib::Utility::CDateTime & curDate = BSLib::Utility::CDateTime::getCurrentTime();
	BSLIB_LOG_INFOR(ETT_GSLIB_ACTIVITYSYSTEM, "---_onArenaResetCallback %d-%d-%d-%d:%d---", curDate.getYear(),curDate.getMonth(),curDate.getDay(), curDate.getHour(), curDate.getMinute());
	std::list<GSLib::PlayerSystem::GM::CRoleGM*> listRoles;
	GSLib::PlayerSystem::GM::CPlayerGMMgr::singleton().getActiveRolesGM(listRoles);
	for (std::list<GSLib::PlayerSystem::GM::CRoleGM*>::iterator itr = listRoles.begin(); itr != listRoles.end(); ++itr) {
		GSLib::PlayerSystem::GM::CRoleGM *role = *itr;
		if (role != NULL) {
			GSLib::SceneSystem::GM::CRoleSceneModule *roleSceneModule = (GSLib::SceneSystem::GM::CRoleSceneModule *)role->getPlayerModuleGM(EMODULECTYPE_SCENE);
			if (roleSceneModule != NULL) {
				roleSceneModule->onArenaReset();
			}
		}
	}

	return true;
}

bool CSceneSystemGM::_onInstanceStageResetCallback(BSLib::uint64 a_num, void* a_para)
{
	m_lastInstanceStageResetTime = m_nextInstanceStageResetTime;
	m_nextInstanceStageResetTime += ONE_DAY_SECONDS;
	const BSLib::Utility::CDateTime & curDate = BSLib::Utility::CDateTime::getCurrentTime();
	BSLIB_LOG_INFOR(ETT_GSLIB_ACTIVITYSYSTEM, "---_onInstanceStageResetCallback %d-%d-%d-%d:%d---", curDate.getYear(),curDate.getMonth(),curDate.getDay(), curDate.getHour(), curDate.getMinute());
	std::list<GSLib::PlayerSystem::GM::CRoleGM*> listRoles;
	GSLib::PlayerSystem::GM::CPlayerGMMgr::singleton().getActiveRolesGM(listRoles);
	for (std::list<GSLib::PlayerSystem::GM::CRoleGM*>::iterator itr = listRoles.begin(); itr != listRoles.end(); ++itr) {
		GSLib::PlayerSystem::GM::CRoleGM *role = *itr;
		if (role != NULL) {
			GSLib::SceneSystem::GM::CRoleSceneModule *roleSceneModule = (GSLib::SceneSystem::GM::CRoleSceneModule *)role->getPlayerModuleGM(EMODULECTYPE_SCENE);
			if (roleSceneModule != NULL) {
			}
		}
	}

	return true;
}


}//GM

}//SceneSystem

}//GSLib

