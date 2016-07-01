#ifndef __GSLIB_ACHIEVESYSTEM_DB_ACHIEVESYSTEMDB_H__
#define __GSLIB_ACHIEVESYSTEM_DB_ACHIEVESYSTEMDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace AchieveSystem
{

namespace DB
{

class CAchieveSystemDB : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CAchieveSystemDB();
	virtual ~CAchieveSystemDB();

	BSLIB_SINGLETON_DECLARE(CAchieveSystemDB);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_ACHIEVESYSTEM; }

public:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonServer_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);
};

}//DB

}//AchieveSystem

}//GSLib

#endif//__GSLIB_ACHIEVESYSTEM_DB_ACHIEVESYSTEMDB_H__

