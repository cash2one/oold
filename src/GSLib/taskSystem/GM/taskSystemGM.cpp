#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include <GSLib/taskSystem/GM/taskSystemGM.h>
#include <GSLib/taskSystem/GM/roleTaskModule.h>
#include <GSLib/taskSystem/GM/taskDataMgr.h>
#include <BSLib/utility/timerServer.h>
#include <GSLib/taskSystem/GM/roleTaskModule.h>
#include <GSLib/playerSystem/GM/playerGMMgr.h>
#include <GSLib/tracer.h>

namespace GSLib
{

namespace TaskSystem
{

namespace GM
{

const BSLib::uint32 C_ONE_DAY_SECONDS = 24 * 60 *60;

BSLIB_SINGLETON_DEFINE(CTaskSystemGM);

CTaskSystemGM::CTaskSystemGM()
{
	;
}

CTaskSystemGM::~CTaskSystemGM()
{
	;
}

void CTaskSystemGM::update(BSLib::uint64 a_delayMilliseconds)
{
	;
}

bool CTaskSystemGM::_init()
{
	GSLib::PlayerSystem::GM::CRoleModuleGMMgr::singleton().addCreateRoleModuleFun(EMODULECTYPE_TASK, GSLib::PlayerSystem::GM::createRoleModuleFun<CRoleTaskModule>);
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CTaskSystemGM::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CTaskSystemGM::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	std::string fileName = a_configPath + "\\task";
	if (!CTaskDataMgr::singleton().loadConfig(fileName)) {
		return false;
	}
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CTaskSystemGM::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}

bool CTaskSystemGM::_startSystem()
{
	_initTaskSystemData();
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CTaskSystemGM::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CTaskSystemGM::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerLeave(a_serverID, a_key);
}

BSLib::uint64 CTaskSystemGM::getLastTaskSystemDataResetTime() const
{
	return m_lastTaskSystemDataResetTime;
}

BSLib::uint64 CTaskSystemGM::getNextTaskSystemDataResetTime() const
{
	return m_nextTaskSystemDataResetTime;
}

bool CTaskSystemGM::_initTaskSystemData()
{
	BSLib::uint32 resetHour = CTaskDataMgr::singleton().getTaskSystemResetHour();
	BSLib::uint32 resetMinute = CTaskDataMgr::singleton().getTaskSystemResetMinte();
	BSLib::Utility::CDateTime curDate = BSLib::Utility::CDateTime::getCurrentTime();
	BSLib::Utility::CDateTime resetDate;	
	resetDate.setDataTime(curDate.getYear(), curDate.getMonth(), curDate.getDay(), resetHour, resetMinute, 0);
	if (curDate.getSeconds() > resetDate.getSeconds()) {
		m_lastTaskSystemDataResetTime = resetDate.getSeconds();
		m_nextTaskSystemDataResetTime = resetDate.getSeconds() + C_ONE_DAY_SECONDS;
	} else {
		m_lastTaskSystemDataResetTime = resetDate.getSeconds() - C_ONE_DAY_SECONDS;
		m_nextTaskSystemDataResetTime = resetDate.getSeconds();
	}

	BSLib::Utility::CTimerServer *timer = _getTimerServer();
	if (timer == NULL) {
		BSLIB_LOG_INFO(ETT_GSLIB_TASKSYSTEM, "CTaskSystemGM::_initTaskSystemData fail, timer = [NULL]");
		return false;
	}
	BSLib::uint64 timeDelay = (m_nextTaskSystemDataResetTime - BSLib::Utility::CDateTime::getCurrentTime().getSeconds()) *  1000;
	BSLib::uint32 timeInterval = C_ONE_DAY_SECONDS * 1000;
	timer->addTimer(&CTaskSystemGM::_taskSystemTimerCallBack, this, 0, 0, timeInterval, (BSLib::uint32)timeDelay, -1);
	BSLIB_LOG_INFO(ETT_GSLIB_TASKSYSTEM, "---Add task system reset timer %d-%d-%d-%d:%d delay[%dms]---", curDate.getYear(),curDate.getMonth(),curDate.getDay(), curDate.getHour(), curDate.getMinute(), timeDelay);

	return true;
}

bool CTaskSystemGM::_taskSystemTimerCallBack(BSLib::uint64, void*)
{
	BSLib::Utility::CDateTime curDate = BSLib::Utility::CDateTime::getCurrentTime();
	m_lastTaskSystemDataResetTime = m_nextTaskSystemDataResetTime;
	m_nextTaskSystemDataResetTime += C_ONE_DAY_SECONDS;
	BSLIB_LOG_INFO(ETT_GSLIB_TASKSYSTEM, "---_taskSystemTimerCallBack %d-%d-%d-%d:%d---", curDate.getYear(),curDate.getMonth(),curDate.getDay(), curDate.getHour(), curDate.getMinute());
	std::list<GSLib::PlayerSystem::GM::CRoleGM*> listRoles;
	GSLib::PlayerSystem::GM::CPlayerGMMgr::singleton().getActiveRolesGM(listRoles);
	for (std::list<GSLib::PlayerSystem::GM::CRoleGM*>::iterator itr = listRoles.begin(); itr != listRoles.end(); ++itr) {
		GSLib::PlayerSystem::GM::CRoleGM *role = *itr;
		if (role != NULL) {
			GSLib::TaskSystem::GM::CRoleTaskModule *roleTaskModule = (GSLib::TaskSystem::GM::CRoleTaskModule *)role->getPlayerModuleGM(EMODULECTYPE_TASK);
			if (roleTaskModule != NULL) {
				roleTaskModule->onTaskSystemDataReset();
			}
		}
	}

	return true;
}


}//GM

}//TaskSystem

}//GSLib

