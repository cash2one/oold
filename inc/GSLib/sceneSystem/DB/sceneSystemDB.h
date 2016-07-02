#ifndef __GSLIB_SCENESYSTEM_DB_SCENESYSTEMDB_H__
#define __GSLIB_SCENESYSTEM_DB_SCENESYSTEMDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace SceneSystem
{

namespace DB
{

class CSceneSystemDB : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CSceneSystemDB();
	virtual ~CSceneSystemDB();

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_SCENESYSTEM; }

	BSLIB_SINGLETON_DECLARE(CSceneSystemDB);

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

}//SceneSystem

}//GSLib

#endif//__GSLIB_SKILLSYSTEM_DB_SKILLSYSTEMDB_H__

