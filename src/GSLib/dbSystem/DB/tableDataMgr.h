
#ifndef __GSLIB_DBSYSTEM_DB_TABLEDATAMGR_H__
#define __GSLIB_DBSYSTEM_DB_TABLEDATAMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/database/dbConnection.h>
#include <BSLib/database/dbKeyTable.h>
#include <BSLib/database/dbKeyIndexTable.h>
#include <GSLib/baseDef.h>
#include <GSLib/dbTableID.h>
#include <GSLib/moduleType.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace DBSystem
{

namespace DB
{

class CTableDataMgr
{
public:
	CTableDataMgr();
	virtual ~CTableDataMgr();

	BSLIB_SINGLETON_DECLARE(CTableDataMgr);

public:
	bool init();
	void final();

	bool loadTableData(EDBTableID a_tableID, const std::string& a_sqlWhere = "");
	bool loadTableData(const std::string& a_key, const std::string& a_index, EDBTableID a_tableID, const std::string& a_strWhere = "");
	bool selectTableData(const std::string& a_key, const std::string& a_index, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream,const std::string& a_strWhere = "");
	bool updateTableData(const std::string& a_key, const std::string& a_index, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream);
	bool saveTableData(const std::string& a_key, const std::string& a_index, EDBTableID a_tableID);
	void saveAllTableData(const std::string& a_key, const std::string& a_index);
	bool removeTableData(const std::string& a_key, const std::string& a_index, EDBTableID a_tableID);
	bool closeTableData(const std::string& a_key, const std::string& a_index, EDBTableID a_tableID);

private:
	//从DB加载数据
	void _closeDBTableInfor();

	const SDbColumnInfor* _getTableDataInfor(EDBTableID a_tableID);

	bool _selectKeyTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, BSLib::Utility::CStream& a_stream, const std::string& a_strWhere = "");
	bool _directSelectKeyTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, BSLib::Utility::CStream& a_stream, const std::string& a_strWhere);
	bool _selectKeyIndexTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_index, BSLib::Utility::CStream& a_stream, const std::string& a_strWhere = "");
	bool _directSelectKeyIndexTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_index, BSLib::Utility::CStream& a_stream, const std::string& a_strWhere);

	bool _updateKeyTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_name, BSLib::Utility::CStream& a_stream);
	bool _updateKeyIndexTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_index, const std::string& a_name, BSLib::Utility::CStream& a_stream);

	bool _removeKeyTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key);
	bool _removeKeyIndexTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_index);

	bool _closeKeyTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key);
	bool _closeKeyIndexTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_index);

	bool _getKeyTable(BSLib::Database::CDBKeyTable*& a_table, const std::string& a_key, const SDbColumnInfor* a_tableDataInfo, const std::string& a_strWhere = "");
	bool _getKeyIndexTable(BSLib::Database::CDBKeyIndexTable*& a_table, const std::string& a_key, const std::string& a_index, const SDbColumnInfor* a_tableDataInfor, const std::string& a_strWhere = "");

	bool _loadKeyTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_strWhere = "");
	bool _loadKeyIndexTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_index,  const std::string& a_strWhere = "");

	bool _loadKeyTableByWhere(const SDbColumnInfor* a_tableDataInfor, const std::string& a_sqlWhere);
	bool _loadKeyIndexTableByWhere(const SDbColumnInfor* a_tableDataInfor, const std::string& a_sqlWhere);

	bool _saveKeyTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key);
	bool _saveKeyIndexTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_index);

	void _saveAllKeyTable(const std::string& a_key);
	void _saveAllKeyIndexTable(const std::string& a_key, const std::string& a_index);

private:
	BSLib::Database::CDbConnection m_dbConnectionLocal;
	BSLib::Database::CDbConnection m_dbConnectionGlobal;

	BSLib::Utility::CHashMap<EDBTableID, BSLib::Database::CDBKeyTable*> m_keyTablesHashMap;
	BSLib::Utility::CHashMap<EDBTableID, BSLib::Database::CDBKeyIndexTable*> m_keyIndexTablesHashMap;
};

}//DB

}//LoginSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_DB_TABLEDATAMGR_H__

