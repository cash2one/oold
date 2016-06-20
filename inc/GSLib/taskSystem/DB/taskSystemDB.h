//////////////////////////////////////////////////////////////////////
//	created:	2014/10/09
//	filename: 	GSLib\taskSystem\DB\taskSystemDB.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_TASKSYSTEM_DB_TASKSYSTEMDB_H__
#define __GSLIB_TASKSYSTEM_DB_TASKSYSTEMDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace TaskSystem
{

namespace DB
{

class CTaskSystemDB : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CTaskSystemDB();
	virtual ~CTaskSystemDB();

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_TASKSYSTEM; }

	BSLIB_SINGLETON_DECLARE(CTaskSystemDB);

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

}//TaskSystem

}//GSLib

#endif//__GSLIB_TASKSYSTEM_DB_TASKSYSTEMDB_H__
