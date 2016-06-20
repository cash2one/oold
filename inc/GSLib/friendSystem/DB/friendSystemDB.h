
#ifndef __GSLIB_FRIENDSYSTEM_DB_FRIENDSYSTEMDB_H__
#define __GSLIB_FRIENDSYSTEM_DB_FRIENDSYSTEMDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace FriendSystem
{

namespace DB
{

class CFriendSystemDB : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CFriendSystemDB();
	virtual ~CFriendSystemDB();

	BSLIB_SINGLETON_DECLARE(CFriendSystemDB);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_FRIENDSYSTEM; }

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

}

}//GSLib

#endif
