#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/tracer.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include "DB/playerDB.h"
#include "DB/tableDataMgr.h"

namespace GSLib
{

namespace DBSystem
{	

namespace DB
{


CPlayerDB::CPlayerDB(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName)
: LoginSystem::DB::CNetPlayerDB(a_accountKey, a_accountName)
{
	;
}

CPlayerDB::~CPlayerDB()
{
	;
}

void CPlayerDB::final()
{
	;
}

void CPlayerDB::_cbInitPlayer()
{
	const std::string& accountKey = getAccountKey().getDBKey();
	if (!CDBSystemDB::singleton().loadInitTableByPlayer(accountKey, "")) {
		_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SERVER_ERROR);
		return ;
	}
	BSLib::Utility::CStringA sqlWhere;
	sqlWhere.format("AccountID=%lld AND ZoneID=%d", getAccountID(), getZoneID());
	if (!CDBSystemDB::singleton().loadInitTableByRole(sqlWhere)) {
		_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SERVER_ERROR);
		return ;
	}

	_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SUCCESS);
}

void CPlayerDB::_cbFinalPlayer()
{
// 	const GFLib::SAccountKey& accountKey = getAccountKey();
// 	const std::string& dbKey = accountKey.getDBKey();
// 
// 	BSLIB_LOG_INFO(ETT_GSLIB_DBSYSTEM, "%s cbFinalPlayer保存到DB", accountKey.toLogString().c_str());
// 
// 	CDBSystemDB::singleton().saveAllTableData(dbKey);
}

void CPlayerDB::_cbPlayerOnline()
{
	;
}

void CPlayerDB::_cbPlayerOffline()
{
// 	const GFLib::SAccountKey& accountKey = getAccountKey();
// 	const std::string& dbKey = accountKey.getDBKey();
// 
// 	BSLIB_LOG_INFO(ETT_GSLIB_DBSYSTEM, "%s cbPlayerOffline保存到DB", accountKey.toLogString().c_str());
// 
// 	CDBSystemDB::singleton().saveAllTableData(dbKey);
}

}//DB

}//DBSystem

}//GSLib

