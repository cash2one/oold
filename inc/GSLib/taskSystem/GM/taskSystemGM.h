#ifndef __GSLIB_TASKSYSTEM_GM_TASKSYSTEMGM_H__
#define __GSLIB_TASKSYSTEM_GM_TASKSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace TaskSystem
{

namespace GM
{

class CTaskSystemGM : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CTaskSystemGM();
	virtual ~CTaskSystemGM();

	BSLIB_SINGLETON_DECLARE(CTaskSystemGM);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_TASKSYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

public:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonServer_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);
public:
	BSLib::uint64 getLastTaskSystemDataResetTime() const;
	BSLib::uint64 getNextTaskSystemDataResetTime() const;

private:
	bool _initTaskSystemData();
	bool _taskSystemTimerCallBack(BSLib::uint64, void*);

private:
	BSLib::uint64 m_lastTaskSystemDataResetTime;
	BSLib::uint64 m_nextTaskSystemDataResetTime;

};

}//GM

}//TaskSystem

}//GSLib

#endif//__GSLIB_TASKSYSTEM_GM_TASKSYSTEMGM_H__

