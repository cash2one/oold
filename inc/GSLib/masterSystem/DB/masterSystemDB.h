
#ifndef __GSLIB_MASTERSYSTEM_DB_MASTERSYSTEMDB_H__
#define __GSLIB_MASTERSYSTEM_DB_MASTERSYSTEMDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace MasterSystem
{

namespace DB
{

class CMasterSystemDB : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CMasterSystemDB();
	virtual ~CMasterSystemDB();

	BSLIB_SINGLETON_DECLARE(CMasterSystemDB);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_MASTERSYSTEM; }

public:
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
