//////////////////////////////////////////////////////////////////////
//	created:	2014/08/28
//	filename: 	src\GSLib\dbSystem\DB\playerDBMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_DBSYSTEM_DB_PLAYERLOGINDB_H__
#define __GSLIB_DBSYSTEM_DB_PLAYERLOGINDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/loginSystem/DB/netPlayerDBMgr.h>
#include "DB/playerDB.h"

namespace GSLib
{

namespace DBSystem
{

namespace DB
{

class CPlayerDBMgr :public GSLib::LoginSystem::DB::CNetPlayerDBMgr
{
public:

	CPlayerDBMgr();
	virtual ~CPlayerDBMgr();

	BSLIB_SINGLETON_DECLARE(CPlayerDBMgr);

public:
	bool init();
	void final();

	virtual GSLib::LoginSystem::DB::CNetPlayerDB* createNetPlayerDB(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName);
	virtual GSLib::LoginSystem::DB::CNetPlayerDB* getNetPlayerDB(const GFLib::SAccountKey& a_accountKey);
	virtual void removeNetPlayerDB(const GFLib::SAccountKey& a_accountKey);

	CPlayerDB* getPlayerDB(const GFLib::SAccountKey& a_accountKey);

private:
	BSLib::Utility::CHashMap<GFLib::SAccountKey, CPlayerDB*> m_accountHashMap;
};

}//DB

}//DBSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_DB_PLAYERLOGINDB_H__
