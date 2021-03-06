#ifndef __GSLIB_ACTIVITYSYSTEM_GM_ACTIVITYSYSTEMGM_H__
#define __GSLIB_ACTIVITYSYSTEM_GM_ACTIVITYSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbSystem/keyTable.h>
#include <BSLib/database/dbTableRow.h>

namespace GSLib
{

namespace ActivitySystem
{

namespace GM
{

class CActivitySystemGM : public GSLib::DBSystem::CDBCommonSystem
{
		enum{	ONE_DAY_SECONDS = 24 * 60 *60, };
public:
	CActivitySystemGM();
	virtual ~CActivitySystemGM();

	BSLIB_SINGLETON_DECLARE(CActivitySystemGM);

	virtual BSLib::uint16 ICommonSystem_getFuncType() { return GSLib::EFUNCTYPE_ACTIVITYSYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

public:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _ICommonSystem_startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);
public:
	BSLib::int32 getLastDailyFreeGoldDrawCardTimeTime() const;
private:
	bool _freeGoldDrawCardDailyCountResetCallback(BSLib::uint64 a_num, void* a_para);
	void _initDailyFreeGoldDrawCardData();	
	void _setDailyResetTime(BSLib::int32 & a_lastRestTime, BSLib::int32 & a_nextResetTime,  BSLib::int32 a_dailyResetHour, BSLib::int32 a_dailyResetMinute);
private:
	BSLib::int32 m_lastDailyFreeGoldDrawCardResetTime;
	BSLib::int32 m_nextDailyFreeGoldDrawCardResetTime;
	
};

}//GM

}//ActivitySystem

}//GSLib

#endif

