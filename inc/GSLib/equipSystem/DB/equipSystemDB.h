#ifndef __GSLIB_EQUIPSYSTEM_DB_EQUIPSYSTEMDB_H__
#define __GSLIB_EQUIPSYSTEM_DB_EQUIPSYSTEMDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace EquipSystem
{

namespace DB
{

class CEquipSystemDB : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CEquipSystemDB();
	virtual ~CEquipSystemDB();

	BSLIB_SINGLETON_DECLARE(CEquipSystemDB);

	virtual BSLib::uint16 ICommonSystem_getFuncType() { return GSLib::EFUNCTYPE_EQUIPSYSTEM; }

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

}//EquipSystem

}//GSLib

#endif//__GSLIB_EQUIPSYSTEM_DB_EQUIPSYSTEMDB_H__

