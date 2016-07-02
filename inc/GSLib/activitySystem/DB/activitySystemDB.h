#ifndef __GSLIB_ACTIVITYSYSTEM_DB_ACTIVITYSYSTEMDB_H__
#define __GSLIB_ACTIVITYSYSTEM_DB_ACTIVITYSYSTEMDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace ActivitySystem
{

namespace DB
{

class CActivitySystemDB : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CActivitySystemDB();
	virtual ~CActivitySystemDB();
public:
	BSLIB_SINGLETON_DECLARE(CActivitySystemDB);
public:
	virtual BSLib::uint16 getFuncType();
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);
};

}//DB

}

}//GSLib

#endif

