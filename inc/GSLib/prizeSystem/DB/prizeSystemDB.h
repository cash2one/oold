#ifndef __GSLIB_PRIZESYSTEM_DB_PRIZESYSTEMDB_H__
#define __GSLIB_PRIZESYSTEM_DB_PRIZESYSTEMDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace PrizeSystem
{

namespace DB
{

class CPrizeSystemDB : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CPrizeSystemDB();
	virtual ~CPrizeSystemDB();

	BSLIB_SINGLETON_DECLARE(CPrizeSystemDB);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_PRIZESYSTEM; }

public:
	virtual bool _init();
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);
};

}//DB

}//PrizeSystem

}//GSLib

#endif
