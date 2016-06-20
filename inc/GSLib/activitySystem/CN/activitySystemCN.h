
#ifndef __GSLIB_ACTIVITYSYSTEM_GM_ACTIVITYSYSTEMGM_H__
#define __GSLIB_ACTIVITYSYSTEM_GM_ACTIVITYSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbSystem/keyTable.h>
#include <GSLib/dbSystem/keyIndexTable.h>

namespace GSLib
{

namespace ActivitySystem
{

namespace CN
{

class CActivitySystemCN : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CActivitySystemCN();
	virtual ~CActivitySystemCN();

	BSLIB_SINGLETON_DECLARE(CActivitySystemCN);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_ACTIVITYSYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

public:
	virtual bool _init();	// test
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);


	
};

}//GM

}

}//GSLib

#endif
