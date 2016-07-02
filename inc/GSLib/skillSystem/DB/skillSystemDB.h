#ifndef __GSLIB_SKILLSYSTEM_DB_SKILLSYSTEMDB_H__
#define __GSLIB_SKILLSYSTEM_DB_SKILLSYSTEMDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace SkillSystem
{

namespace DB
{

class CSkillSystemDB : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CSkillSystemDB();
	virtual ~CSkillSystemDB();

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_SKILLPSYSTEM; }

	BSLIB_SINGLETON_DECLARE(CSkillSystemDB);

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

}//SkillSystem

}//GSLib

#endif//__GSLIB_SKILLSYSTEM_DB_SKILLSYSTEMDB_H__

