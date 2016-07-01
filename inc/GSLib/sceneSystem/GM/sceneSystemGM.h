#ifndef __GSLIB_SCENESYSTEM_GM_SCENESYSTEMGM_H__
#define __GSLIB_SCENESYSTEM_GM_SCENESYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class CSceneSystemGM : public GSLib::DBSystem::CDBCommonSystem
{
	enum{	ONE_DAY_SECONDS = 24 * 60 *60, };
public:
	CSceneSystemGM();
	virtual ~CSceneSystemGM();

	BSLIB_SINGLETON_DECLARE(CSceneSystemGM);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_SCENESYSTEM; }

public:
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
	BSLib::int32 getLastContinuousStageResetTime() const;
	BSLib::int32 getLastStageHelperResetTime() const;
	BSLib::int32 getLastArenaResetTime() const;
	BSLib::int32 getLastInstanceStageResetTime() const;
	BSLib::uint64 genArenaRecordID(BSLib::int32 a_time);
private:
	void _initContinuousStageData();
	void _initStageHelperResetTimer();
	void _initArenaResetTimer();
	void _initInstanceStageTimer();

	bool _onContinuousStageResetCallback(BSLib::uint64 a_num, void* a_para);
	void _setDailyResetTime(BSLib::int32 & a_lastRestTime, BSLib::int32 & a_nextResetTime,  BSLib::int32 a_dailyResetHour, BSLib::int32 a_dailyResetMinute);
	bool _onStageGetHlepResetCallback(BSLib::uint64 a_num, void* a_para);
	bool _onArenaResetCallback(BSLib::uint64 a_num, void* a_para);
	bool _onInstanceStageResetCallback(BSLib::uint64 a_num, void* a_para);
private:
	BSLib::uint64 m_lastStageEnterTimeResetTime;
	BSLib::uint64 m_nextStageEnterTimeResetTime;
	BSLib::int32 m_lastDailyContinuousStageResetTime;
	BSLib::int32 m_nextDailyContinuousStageResetTime;

	BSLib::int32 m_lastRoleDailyStageHelperResetTime;
	BSLib::int32 m_nextRoleDailyStageHelperResetTime;

	BSLib::int32 m_lastArenaResetTime;
	BSLib::int32 m_nextArenaResetTime;

	BSLib::int32 m_lastInstanceStageResetTime;
	BSLib::int32 m_nextInstanceStageResetTime;

	BSLib::uint32 m_arenaRecordIndex;
	BSLib::uint8 m_serverID;
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_SCENESYSTEMGM_H__

