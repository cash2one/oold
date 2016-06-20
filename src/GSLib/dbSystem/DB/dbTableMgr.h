//////////////////////////////////////////////////////////////////////
//	created:	2014/08/30
//	filename: 	src\GSLib\dbSystem\DB\dbTableMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_DBSYSTEM_DB_DBTABLEMGR_H__
#define __GSLIB_DBSYSTEM_DB_DBTABLEMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/database/dbConnection.h>
#include <GSLib/baseDef.h>
#include <GSLib/dbTableID.h>
//#include <GSLib/dbSystem/dbTableID.h>

namespace GSLib
{

namespace DBSystem
{

namespace DB
{

struct SDBTableInfor 
{
public:
	SDBTableInfor(const std::string& a_dbTableName, const BSLib::Database::SDbColumn* a_dbTableColumn)
		: m_dbTableName(a_dbTableName), m_dbTableColumn(a_dbTableColumn) {}

public:
	std::string m_dbTableName;
	const BSLib::Database::SDbColumn* m_dbTableColumn;
};


class CDBTableMgr
{
public:
	CDBTableMgr();
	virtual ~CDBTableMgr();

	BSLIB_SINGLETON_DECLARE(CDBTableMgr);

public:
	bool init();
	void final();

	bool selectTableData(GFLib::AccountID a_accountID, GFLib::ZoneID a_zoneID, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream);
	bool updateTableData(EDBTableID a_tableID, BSLib::Utility::CStream& a_stream);

private:
	void _initDBTableInfor();
	void _closeDBTableInfor();

private:
	BSLib::Database::CDbConnection m_dbConnectionLocal;
	BSLib::Database::CDbConnection m_dbConnectionGlobal;
	
	BSLib::Utility::CHashMap<EDBTableID, SDBTableInfor*> m_dbTableInforHashMap;
};

}//DB

}//LoginSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_DB_DBTABLEMGR_H__