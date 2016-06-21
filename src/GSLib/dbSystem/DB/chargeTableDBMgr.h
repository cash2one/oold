
#ifndef __GSLIB_DBSYSTEM_DB_CHARGETABLEDBMGR_H__
#define __GSLIB_DBSYSTEM_DB_CHARGETABLEDBMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/database/dbConnection.h>

namespace GSLib
{

namespace DBSystem
{

namespace DB
{

class CChargeTableDBMgr
{
public:
	CChargeTableDBMgr();
	~CChargeTableDBMgr();

	BSLIB_SINGLETON_DECLARE(CChargeTableDBMgr);

public:
	bool init();
	void final();

	bool getRoleChargeList(const SRoleKey& a_roleKey, std::vector<SChargeList>& a_chargeList);

protected:
private:
	BSLib::Database::CDbConnection m_dbConnectionLocal;
};

}//DB

}//DBSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_DB_CHARGETABLEDBMGR_H__
