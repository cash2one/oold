//////////////////////////////////////////////////////////////////////
//	created:	2014/08/28
//	filename: 	src\GSLib\dbSystem\DB\playerDB.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_DBSYSTEM_DB_PLAYERDB_H__
#define __GSLIB_DBSYSTEM_DB_PLAYERDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/loginSystem/DB/netPlayerDB.h>
#include <GSLib/dbSystem/msgDBSystem.h>

namespace GSLib
{

namespace DBSystem
{

namespace DB
{

class CPlayerDB :public GSLib::LoginSystem::DB::CNetPlayerDB
{
public:
	CPlayerDB(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName);
	virtual ~CPlayerDB();

	void final();

protected:
	virtual void _cbInitPlayer();
	virtual void _cbFinalPlayer();

	virtual void _cbPlayerOnline();
	virtual void _cbPlayerOffline();
};

}//DB

}//PlayerSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_DB_PLAYERDB_H__
