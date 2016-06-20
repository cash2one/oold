//////////////////////////////////////////////////////////////////////
//	created:	2014/07/28
//	filename: 	GSLib\loginSystem\DB\netPlayerDBMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_LOGINSYSTEM_DB_NETPLAYERDBMGR_H__
#define __GSLIB_LOGINSYSTEM_DB_NETPLAYERDBMGR_H__

#include <GSLib/loginSystem/DB/netPlayerDB.h>

namespace GSLib
{

namespace LoginSystem
{

namespace DB
{

class CNetPlayerDBMgr
{
public:
	CNetPlayerDBMgr();
	virtual ~CNetPlayerDBMgr();

	virtual CNetPlayerDB* createNetPlayerDB(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName) = 0;
	virtual CNetPlayerDB* getNetPlayerDB(const GFLib::SAccountKey& a_accountKey) = 0;
	virtual void removeNetPlayerDB(const GFLib::SAccountKey& a_accountKey) = 0;

public:
	static CNetPlayerDBMgr* getSingleton() { return m_singleton; }

private:
	static CNetPlayerDBMgr* m_singleton;
};

}//DB

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_DB_NETPLAYERDBMGR_H__
