//////////////////////////////////////////////////////////////////////
//	created:	2014/10/09
//	filename: 	GSLib\mailSystem\DB\MailSystemDB.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_MAILSYSTEM_DB_MAILSYSTEMDB_H__
#define __GSLIB_MAILSYSTEM_DB_MAILSYSTEMDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace MailSystem
{

namespace DB
{

class CMailSystemDB : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CMailSystemDB();
	virtual ~CMailSystemDB();

	BSLIB_SINGLETON_DECLARE(CMailSystemDB);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_MAILSYSTEM; }

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

}//MailSystem

}//GSLib

#endif//__GSLIB_MAILSYSTEM_DB_MAILSYSTEMDB_H__
