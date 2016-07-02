#ifndef __GSLIB_PETSYSTEM_DB_PETSYSTEMDB_H__
#define __GSLIB_PETSYSTEM_DB_PETSYSTEMDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace PetSystem
{

namespace DB
{

class CPetSystemDB : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CPetSystemDB();
	virtual ~CPetSystemDB();

	BSLIB_SINGLETON_DECLARE(CPetSystemDB);

	virtual BSLib::uint16 ICommonSystem_getFuncType() { return GSLib::EFUNCTYPE_PETSYSTEM; }

public:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _ICommonSystem_startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);
};

}//DB

}//PetSystem

}//GSLib

#endif//__GSLIB_PETSYSTEM_DB_PETSYSTEMDB_H__

