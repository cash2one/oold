//////////////////////////////////////////////////////////////////////
//	created:	2014/09/26
//	filename: 	GSLib\playerSystem\DB\playerSystemDB.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_DB_PLAYERSYSTEMDB_H__
#define __GSLIB_PLAYERSYSTEM_DB_PLAYERSYSTEMDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace DB
{

class CPlayerSystemDB : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CPlayerSystemDB();
	virtual ~CPlayerSystemDB();

	BSLIB_SINGLETON_DECLARE(CPlayerSystemDB);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_PLAYERSYSTEM; }

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

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_DB_PLAYERSYSTEMDB_H__
