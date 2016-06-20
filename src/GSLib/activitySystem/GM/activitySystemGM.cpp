//////////////////////////////////////////////////////////////////////
//	created:	2014/12/5
//	filename: 	GSLib\activitySystem\GM\activitySystemGM.cpp
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include <GSLib/activitySystem/GM/activitySystemGM.h>
#include <GSLib/playerSystem/GM/playerGMMgr.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/activitySystem/msgActivitySystem.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/activitySystem/GM/activitySystemDataMgr.h>
#include <GSLib/moduleType.h>
#include <GSLib/activitySystem/GM/roleActivityModule.h>

namespace GSLib
{

namespace ActivitySystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CActivitySystemGM);

CActivitySystemGM::CActivitySystemGM()
:m_lastDailyFreeGoldDrawCardResetTime(0)
,m_nextDailyFreeGoldDrawCardResetTime(0)
{	

}

CActivitySystemGM::~CActivitySystemGM()
{
	;
}

void CActivitySystemGM::update(BSLib::uint64 a_delayMilliseconds)
{
}

bool CActivitySystemGM::_init()
{
	GSLib::PlayerSystem::GM::CRoleModuleGMMgr::singleton().addCreateRoleModuleFun(EMODULETYPE_ACTIVITY, GSLib::PlayerSystem::GM::createRoleModuleFun<CRoleActivityModule>);
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CActivitySystemGM::_final()
{
	GFLib::CommonServer::CCommonSystem::_final();
}

bool CActivitySystemGM::_loadGameConfig(const std::string& a_configPath)
{
	if (!CActivitySystemDataMgr::singleton().loadActivityConfig(a_configPath)) {
		return false;
	}

	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CActivitySystemGM::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{	
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CActivitySystemGM::_startSystem()
{	
	_initDailyFreeGoldDrawCardData();
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CActivitySystemGM::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::CCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CActivitySystemGM::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::CCommonSystem::_cbServerLeave(a_serverID, a_key);
}

BSLib::int32 CActivitySystemGM::getLastDailyFreeGoldDrawCardTimeTime() const
{
	return m_lastDailyFreeGoldDrawCardResetTime;
}

bool CActivitySystemGM::_freeGoldDrawCardDailyCountResetCallback(BSLib::uint64 a_num, void* a_para)
{
	m_lastDailyFreeGoldDrawCardResetTime = m_nextDailyFreeGoldDrawCardResetTime;
	m_nextDailyFreeGoldDrawCardResetTime += ONE_DAY_SECONDS;
	const BSLib::Utility::CDateTime & curDate = BSLib::Utility::CDateTime::getCurrentTime();
	BSLIB_LOG_INFOR(ETT_GSLIB_ACTIVITYSYSTEM, "---_continuousStageResetCallback %d-%d-%d-%d:%d---", curDate.getYear(),curDate.getMonth(),curDate.getDay(), curDate.getHour(), curDate.getMinute());
	std::list<GSLib::PlayerSystem::GM::CRoleGM*> listRoles;
	GSLib::PlayerSystem::GM::CPlayerGMMgr::singleton().getActiveRolesGM(listRoles);
	for (std::list<GSLib::PlayerSystem::GM::CRoleGM*>::iterator itr = listRoles.begin(); itr != listRoles.end(); ++itr) {
		GSLib::PlayerSystem::GM::CRoleGM *role = *itr;
		if (role != NULL) {
			GSLib::ActivitySystem::GM::CRoleActivityModule *roleActivityModule = (GSLib::ActivitySystem::GM::CRoleActivityModule *)role->getPlayerModuleGM(EMODULETYPE_ACTIVITY);
			if (roleActivityModule != NULL) {
				roleActivityModule->onDailyFreeGoldDrawCardCountResetCallback();
			}
		}
	}
	return true;
}

void CActivitySystemGM::_initDailyFreeGoldDrawCardData()
{
	_setDailyResetTime(m_lastDailyFreeGoldDrawCardResetTime, m_nextDailyFreeGoldDrawCardResetTime, 0, 0);
	BSLib::uint64 timeDelay = (m_nextDailyFreeGoldDrawCardResetTime - BSLib::Utility::CDateTime::getCurrentTime().getSeconds()) *  1000;
	BSLib::uint32 timeInterval = ONE_DAY_SECONDS * 1000;
	BSLib::Utility::CTimerServer *timer = _getTimerServer();
	if (timer == NULL) {
		BSLIB_LOG_INFOR(ETT_GSLIB_ACTIVITYSYSTEM, "CActivitySystemGM::_initDailyFreeGoldDrawCardData fail, timer = [NULL]");
		return;
	}
	const BSLib::Utility::CDateTime & curDate = BSLib::Utility::CDateTime::getCurrentTime();
	timer->addTimer(&CActivitySystemGM::_freeGoldDrawCardDailyCountResetCallback, this, 0, 0, timeInterval, (BSLib::uint32)timeDelay, -1);
	BSLIB_LOG_INFOR(ETT_GSLIB_ACTIVITYSYSTEM, "---Add daily free gold draw card count reset timer %d-%d-%d-%d:%d delay[%dms]---", curDate.getYear(),curDate.getMonth(),curDate.getDay(), curDate.getHour(), curDate.getMinute(), timeDelay);
}


void CActivitySystemGM::_setDailyResetTime(BSLib::int32 & a_lastRestTime, BSLib::int32 & a_nextResetTime, BSLib::int32 a_dailyResetHour, BSLib::int32 a_dailyResetMinute)
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




}//GM

}

}//GSLib
