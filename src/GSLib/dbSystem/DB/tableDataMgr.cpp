#include <GFLib/commonServer/commonServer.h>
#include <GSLib/tracer.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include "DB/tableDataMgr.h"
#include "DB/tableData.h"
#include "DB/playerDB.h"

namespace GSLib
{

namespace DBSystem
{

namespace DB
{

BSLIB_SINGLETON_DEFINE(CTableDataMgr);

CTableDataMgr::CTableDataMgr()
{
	;
}

CTableDataMgr::~CTableDataMgr()
{
	;
}

bool CTableDataMgr::init()
{
	const std::string& serverName = GFLib::CommonServer::CCommonServer::getCommonServer()->getServerTypeName();
	const std::string localMysqlDB = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "LocalMySQLDB");
	if (localMysqlDB.empty()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "获取本地数据库参数失败");
		return false;
	}
	if (!m_dbConnectionLocal.connect(localMysqlDB, false)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "连接数据库失败");
		return false;
	}

	const std::string globalMysqlDB = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "GlobalMySQLDB");
	if (globalMysqlDB.empty()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "获取全局数据库参数失败");
		return false;
	}
	if (!m_dbConnectionGlobal.connect(globalMysqlDB, false)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "连接数据库失败");
		return false;
	}

	return true;
}

void CTableDataMgr::final()
{
	_closeDBTableInfor();

	m_dbConnectionLocal.close();
	m_dbConnectionGlobal.close();
}

bool CTableDataMgr::loadTableData(EDBTableID a_tableID, const std::string& a_sqlWhere)
{
	const SDbColumnInfor* tableInfor = _getTableDataInfor(a_tableID);
	if (tableInfor == NULL) {
		return false;
	}
	switch(tableInfor->m_tableKeyType) 
	{
	case ETABLEKEYTYPE_KEY:
		{
			return _loadKeyTableByWhere(tableInfor, a_sqlWhere);
		}
	case ETABLEKEYTYPE_KEY_INDEX:
		{
			return _loadKeyIndexTableByWhere(tableInfor, a_sqlWhere);
		}
	default:
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select数据失败[TableID=%d][TableName=%s]", a_tableID, tableInfor->m_dbTableName.c_str());
	}
	return false;
}

bool CTableDataMgr::loadTableData(const std::string& a_key, const std::string& a_index, EDBTableID a_tableID, const std::string& a_strWhere)
{
	const SDbColumnInfor* tableInfor = _getTableDataInfor(a_tableID);
	if (tableInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "load talbe失败[TableID=%d]", a_tableID);
		return false;
	}
	switch(tableInfor->m_tableKeyType) 
	{
	case ETABLEKEYTYPE_KEY:
		{
			return _loadKeyTable(tableInfor, a_key,a_strWhere);
		}
	case ETABLEKEYTYPE_KEY_INDEX:
		{
			return _loadKeyIndexTable(tableInfor, a_key, a_index,a_strWhere);
		}
	default:
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "load talbe失败[TableID=%d][TableName=%s]", a_tableID, tableInfor->m_dbTableName.c_str());
	}
	return false;
}

bool CTableDataMgr::selectTableData(const std::string& a_key, const std::string& a_index, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, const std::string& a_strWhere)
{
	const SDbColumnInfor* tableInfor = _getTableDataInfor(a_tableID);
	if (tableInfor == NULL) {
		return false;
	}
	switch(tableInfor->m_tableKeyType) 
	{
	case ETABLEKEYTYPE_KEY:
		{
			return _selectKeyTable(tableInfor, a_key, a_stream,a_strWhere);
		}
	case ETABLEKEYTYPE_KEY_INDEX:
		{
			return _selectKeyIndexTable(tableInfor, a_key, a_index, a_stream,a_strWhere);
		}
	default:
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select数据失败[TableID=%d][TableName=%s]", a_tableID, tableInfor->m_dbTableName.c_str());
	}
	return false;
}

bool CTableDataMgr::updateTableData(const std::string& a_key, const std::string& a_index, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream)
{
	const SDbColumnInfor* tableInfor = _getTableDataInfor(a_tableID);
	if (tableInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "update数据失败,表不存在[TableID=%d]", a_tableID);
		return false;
	}
	switch(tableInfor->m_tableKeyType) 
	{
	case ETABLEKEYTYPE_KEY:
		{
			return _updateKeyTable(tableInfor, a_key, a_name, a_stream);
		}
	case ETABLEKEYTYPE_KEY_INDEX:
		{
			return _updateKeyIndexTable(tableInfor, a_key, a_index, a_name, a_stream);
		}
	default:
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "update数据失败[TableID=%d][TableName=%s]", a_tableID, tableInfor->m_dbTableName.c_str());
	}
	return false;
}

bool CTableDataMgr::saveTableData(const std::string& a_key, const std::string& a_index, EDBTableID a_tableID)
{
	const SDbColumnInfor* tableInfor = _getTableDataInfor(a_tableID);
	if (tableInfor == NULL) {
		return false;
	}

	BSLIB_LOG_INFO(ETT_GSLIB_DBSYSTEM, "save数据[TableID=%d][TableName=%s]", a_tableID, tableInfor->m_dbTableName.c_str());

	switch(tableInfor->m_tableKeyType) 
	{
	case ETABLEKEYTYPE_KEY:
		{
			return _saveKeyTable(tableInfor, a_key);
		}
	case ETABLEKEYTYPE_KEY_INDEX:
		{
			return _saveKeyIndexTable(tableInfor, a_key, a_index);
		}
	default:
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "save数据失败[TableID=%d][TableName=%s]", a_tableID, tableInfor->m_dbTableName.c_str());
	}
	return false;
}

void CTableDataMgr::saveAllTableData(const std::string& a_key, const std::string& a_index)
{
	_saveAllKeyTable(a_key);
	_saveAllKeyIndexTable(a_key, a_index);
}

bool CTableDataMgr::removeTableData(const std::string& a_key, const std::string& a_index, EDBTableID a_tableID)
{
	const SDbColumnInfor* tableInfor = _getTableDataInfor(a_tableID);
	if (tableInfor == NULL) {
		return false;
	}
	switch(tableInfor->m_tableKeyType) 
	{
	case ETABLEKEYTYPE_KEY:
		{
			return _removeKeyTable(tableInfor, a_key);
		}
	case ETABLEKEYTYPE_KEY_INDEX:
		{
			return _removeKeyIndexTable(tableInfor, a_key, a_index);
		}
	default:
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "remove数据失败[TableID=%d][TableName=%s]", a_tableID, tableInfor->m_dbTableName.c_str());
	}
	return false;
}

bool CTableDataMgr::closeTableData(const std::string& a_key, const std::string& a_index, EDBTableID a_tableID)
{
	const SDbColumnInfor* tableInfor = _getTableDataInfor(a_tableID);
	if (tableInfor == NULL) {
		return false;
	}
	switch(tableInfor->m_tableKeyType) 
	{
	case ETABLEKEYTYPE_KEY:
		{
			return _closeKeyTable(tableInfor, a_key);
		}
	case ETABLEKEYTYPE_KEY_INDEX:
		{
			return _closeKeyIndexTable(tableInfor, a_key, a_index);
		}
	default:
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "close数据失败[TableID=%d][TableName=%s]", a_tableID, tableInfor->m_dbTableName.c_str());
	}
	return false;
}

void CTableDataMgr::_closeDBTableInfor()
{
	BSLib::Utility::CHashMap<EDBTableID, BSLib::Database::CDBKeyTable*>::iterator it_key = m_keyTablesHashMap.begin();
	for (; it_key != m_keyTablesHashMap.end(); ++it_key) {
		BSLib::Database::CDBKeyTable* talbe = it_key->second;
		if (talbe == NULL) {
			continue;
		}
		const SDbColumnInfor* columnInfor = _getTableDataInfor(it_key->first);
		if (columnInfor == NULL) {
			talbe->removeAll();
			BSLIB_SAFE_DELETE(talbe);
			continue;
		}
		BSLIB_LOG_INFO(ETT_GSLIB_DBSYSTEM, "保存数据库[%s]", columnInfor->m_dbTableName.c_str());

		_saveKeyTable(columnInfor, "");

		BSLIB_SAFE_DELETE(talbe);
	}
	m_keyTablesHashMap.clear();

	BSLib::Utility::CHashMap<EDBTableID, BSLib::Database::CDBKeyIndexTable*>::iterator it_keyIndex = m_keyIndexTablesHashMap.begin();
	for (; it_keyIndex != m_keyIndexTablesHashMap.end(); ++it_keyIndex) {
		BSLib::Database::CDBKeyIndexTable* talbe = it_keyIndex->second;
		if (talbe == NULL) {
			continue;
		}
		const SDbColumnInfor* columnInfor = _getTableDataInfor(it_keyIndex->first);
		if (columnInfor == NULL) {
			talbe->removeAll();
			BSLIB_SAFE_DELETE(talbe);
			continue;
		}
		BSLIB_LOG_INFO(ETT_GSLIB_DBSYSTEM, "保存数据库[%s]", columnInfor->m_dbTableName.c_str());

		_saveKeyIndexTable(columnInfor, "", "");

		BSLIB_SAFE_DELETE(talbe);
	}
	m_keyIndexTablesHashMap.clear();
}

const SDbColumnInfor* CTableDataMgr::_getTableDataInfor(EDBTableID a_tableID)
{
	return CDBSystemDB::singleton().getDbColumnInfor(a_tableID);
}

bool CTableDataMgr::_selectKeyTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, BSLib::Utility::CStream& a_stream, const std::string& a_strWhere)
{
	BSLib::Database::CDBKeyTable* table = NULL;
	_getKeyTable(table, a_key, a_tableDataInfor,a_strWhere);
	if (table == NULL) {
		return false;
	}

	return table->serializeTo(a_key, a_stream);

	//return _directSelectKeyTable(a_tableDataInfor, a_key, a_stream, a_strWhere);
}

bool CTableDataMgr::_directSelectKeyTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, BSLib::Utility::CStream& a_stream, const std::string& a_strWhere)
{
	const BSLib::Database::SDbColumn* dbColumn = a_tableDataInfor->m_dbTableColumn;
	if (dbColumn == NULL) {
		return false;
	}

	BSLib::Database::CDbConnection* dbConnection = NULL;
	switch (a_tableDataInfor->m_connectType) {
		case EDBCNNCTTYPE_LOCAL:
			dbConnection = &m_dbConnectionLocal;
			break;
		case EDBCNNCTTYPE_GLOBAL:
			dbConnection = &m_dbConnectionGlobal;
			break;
	}

	BSLib::Database::CDBKeyTable* table = new BSLib::Database::CDBKeyTable(dbColumn);
	if (!table->loadDataFromDBByWhere(dbConnection, a_tableDataInfor->m_dbTableName, a_key,a_strWhere)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从数据库加载数据失败[TableID=%d][TableName=%s]", a_tableDataInfor->m_tableID, a_tableDataInfor->m_dbTableName.c_str());
		BSLIB_SAFE_DELETE(table);
		return false;
	}
	table->serializeTo(a_key, a_stream);
	BSLIB_SAFE_DELETE(table);
	return true;
}

bool CTableDataMgr::_selectKeyIndexTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_index, BSLib::Utility::CStream& a_stream, const std::string& a_strWhere)
{
	BSLib::Database::CDBKeyIndexTable* table = NULL;
	_getKeyIndexTable(table, a_key, a_index, a_tableDataInfor,a_strWhere);
	if (table == NULL) {
		return false;
	}
	return table->serializeTo(a_key, a_index, a_stream);

	//return _directSelectKeyIndexTable(a_tableDataInfor, a_key, a_index, a_stream, a_strWhere);
}

bool CTableDataMgr::_directSelectKeyIndexTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_index, BSLib::Utility::CStream& a_stream, const std::string& a_strWhere)
{
	const BSLib::Database::SDbColumn* dbColumn = a_tableDataInfor->m_dbTableColumn;
	if (dbColumn == NULL) {
		return false;
	}

	BSLib::Database::CDbConnection* dbConnection = NULL;
	switch (a_tableDataInfor->m_connectType) {
		case EDBCNNCTTYPE_LOCAL:
			dbConnection = &m_dbConnectionLocal;
			break;
		case EDBCNNCTTYPE_GLOBAL:
			dbConnection = &m_dbConnectionGlobal;
			break;
	}

	BSLib::Database::CDBKeyIndexTable* table = new BSLib::Database::CDBKeyIndexTable(dbColumn);
	if (!table->loadDataFromDBByWhere(dbConnection, a_tableDataInfor->m_dbTableName, a_strWhere)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从数据库加载数据失败[TableID=%d][TableName=%s]", a_tableDataInfor->m_tableID, a_tableDataInfor->m_dbTableName.c_str());
		BSLIB_SAFE_DELETE(table);
		return false;
	}
	return table->serializeTo(a_key, a_index, a_stream);
	BSLIB_SAFE_DELETE(table);
	return true;	
}

bool CTableDataMgr::_updateKeyTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_name, BSLib::Utility::CStream& a_stream)
{
	BSLib::Database::CDBKeyTable* table = NULL;
	_getKeyTable(table, a_key, a_tableDataInfor);
	if (table == NULL) {
		return false;
	}
	return table->update(a_key, a_name, a_stream);
}

bool CTableDataMgr::_updateKeyIndexTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_index, const std::string& a_name, BSLib::Utility::CStream& a_stream)
{
	BSLib::Database::CDBKeyIndexTable* table = NULL;
	_getKeyIndexTable(table, a_key, a_index, a_tableDataInfor);
	if (table == NULL) {
		return false;
	}
	return table->update(a_key, a_index, a_name, a_stream);
}

bool CTableDataMgr::_removeKeyTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key)
{
	BSLib::Database::CDBKeyTable* table = NULL;
	_getKeyTable(table, a_key, a_tableDataInfor);
	if (table == NULL) {
		return false;
	}
	table->remove(a_key);
	return true;
}

bool CTableDataMgr::_removeKeyIndexTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_index)
{
	BSLib::Database::CDBKeyIndexTable* table = NULL;
	_getKeyIndexTable(table, a_key, a_index, a_tableDataInfor);
	if (table == NULL) {
		return false;
	}
	table->remove(a_key, a_index);
	return true;
}

bool CTableDataMgr::_closeKeyTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key)
{
	if (a_key.empty()) {
		BSLib::Database::CDBKeyTable* table = NULL;
		m_keyTablesHashMap.getValue(a_tableDataInfor->m_tableID, table);
		if (table != NULL) {
			table->clear();
		}
	} else {
		BSLib::Database::CDBKeyTable* table = NULL;
		m_keyTablesHashMap.getValue(a_tableDataInfor->m_tableID, table);
		if (table != NULL) {
			table->clear(a_key);
		}
	}
	return true;
}

bool CTableDataMgr::_closeKeyIndexTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_index)
{
	if (a_key.empty()) {
		if (a_index.empty()) {
			BSLib::Database::CDBKeyIndexTable* table = NULL;
			m_keyIndexTablesHashMap.getValue(a_tableDataInfor->m_tableID, table);
			if (table != NULL) {
				table->clear();
			}
			return true;
		}
		return false;
	} else {
		BSLib::Database::CDBKeyIndexTable* table = NULL;
		m_keyIndexTablesHashMap.getValue(a_tableDataInfor->m_tableID, table);
		if (table != NULL) {
			table->clear(a_key, a_index);	
		}
	}
	return true;
}

bool CTableDataMgr::_getKeyTable(BSLib::Database::CDBKeyTable*& a_table, const std::string& a_key, const SDbColumnInfor* a_tableDataInfor, const std::string& a_strWhere)
{
	a_table = NULL;
	m_keyTablesHashMap.getValue(a_tableDataInfor->m_tableID, a_table);
	if (a_table == NULL) {
		if (!_loadKeyTable(a_tableDataInfor, a_key,a_strWhere)) {
			return false;
		}
		m_keyTablesHashMap.getValue(a_tableDataInfor->m_tableID, a_table);
		return a_table != NULL;
	}
	if (a_key.empty()) {
        if(a_strWhere.empty()){
            return true;
        }
        if (!_loadKeyTable(a_tableDataInfor, a_key,a_strWhere)) {
            return false;
        }
	}
	if (a_table->getRow(a_key) != NULL) {
		return true;
	}
	if (!_loadKeyTable(a_tableDataInfor, a_key,a_strWhere)) {
		return false;
	}
	return true;
}

bool CTableDataMgr::_getKeyIndexTable(BSLib::Database::CDBKeyIndexTable*& a_table, const std::string& a_key, const std::string& a_index, const SDbColumnInfor* a_tableDataInfor, const std::string& a_strWhere)
{
	a_table = NULL;
	m_keyIndexTablesHashMap.getValue(a_tableDataInfor->m_tableID, a_table);
	if (a_table == NULL) {
		if (!_loadKeyIndexTable(a_tableDataInfor, a_key, a_index,a_strWhere)) {
			return false;
		}
		m_keyIndexTablesHashMap.getValue(a_tableDataInfor->m_tableID, a_table);
		return a_table != NULL;
	}
	if (a_key.empty()) {
        if(a_strWhere.empty()){
            return true;
        }
        if (!_loadKeyIndexTableByWhere(a_tableDataInfor,a_strWhere)) {
            return false;
        }
		return true;
	}
	if (a_index.empty()) {
		if (a_table->getRows(a_key) != NULL) {
			return true;
		}
		if (!_loadKeyIndexTable(a_tableDataInfor, a_key, a_index,a_strWhere)) {
			return false;
		}
		return true;
	}
	if (a_table->getRow(a_key, a_index) != NULL) {
		return true;
	}
	if (!_loadKeyIndexTable(a_tableDataInfor, a_key, a_index,a_strWhere)) {
		return false;
	}
	return true;
}

bool CTableDataMgr::_loadKeyTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_strWhere)
{
	const BSLib::Database::SDbColumn* dbColumn = a_tableDataInfor->m_dbTableColumn;
	if (dbColumn == NULL) {
		return false;
	}

	BSLib::Database::CDbConnection* dbConnection = NULL;
	switch (a_tableDataInfor->m_connectType) {
		case EDBCNNCTTYPE_LOCAL:
			dbConnection = &m_dbConnectionLocal;
			break;
		case EDBCNNCTTYPE_GLOBAL:
			dbConnection = &m_dbConnectionGlobal;
			break;
	}

	BSLib::Database::CDBKeyTable* table = NULL;
	m_keyTablesHashMap.getValue(a_tableDataInfor->m_tableID, table);
	if (table == NULL) {
		BSLib::Database::CDBKeyTable* table = new BSLib::Database::CDBKeyTable(dbColumn);
		if (table == NULL) {
			return false;
		}
		if (!table->loadDataFromDBByWhere(dbConnection, a_tableDataInfor->m_dbTableName, a_key,a_strWhere)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从数据库加载数据失败[TableID=%d][TableName=%s]", a_tableDataInfor->m_tableID, a_tableDataInfor->m_dbTableName.c_str());
			BSLIB_SAFE_DELETE(table);
			return false;
		}	
		m_keyTablesHashMap.setValue(a_tableDataInfor->m_tableID, table);
		return true;
	}
	if (!table->loadDataFromDBByWhere(dbConnection, a_tableDataInfor->m_dbTableName, a_key,a_strWhere)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从数据库加载数据失败[TableID=%d][TableName=%s]", a_tableDataInfor->m_tableID, a_tableDataInfor->m_dbTableName.c_str());
		return false;
	}	
	return true;
}

bool CTableDataMgr::_loadKeyIndexTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_index, const std::string& a_strWhere)
{
	const BSLib::Database::SDbColumn* dbColumn = a_tableDataInfor->m_dbTableColumn;
	if (dbColumn == NULL) {
		return false;
	}
	BSLib::Database::CDbConnection* dbConnection = NULL;
	switch (a_tableDataInfor->m_connectType) {
		case EDBCNNCTTYPE_LOCAL:
			dbConnection = &m_dbConnectionLocal;
			break;
		case EDBCNNCTTYPE_GLOBAL:
			dbConnection = &m_dbConnectionGlobal;
			break;
	}

	BSLib::Database::CDBKeyIndexTable* table = NULL;
	m_keyIndexTablesHashMap.getValue(a_tableDataInfor->m_tableID, table);
	if (table == NULL) {
		table = new BSLib::Database::CDBKeyIndexTable(dbColumn);
		if (table == NULL) {
			return false;
		}
		if (!table->loadDataFromDBByWhere(dbConnection, a_tableDataInfor->m_dbTableName, a_key, a_index,a_strWhere)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从数据库加载数据失败[TableID=%d][TableName=%s]", a_tableDataInfor->m_tableID, a_tableDataInfor->m_dbTableName.c_str());
			BSLIB_SAFE_DELETE(table);
			return false;
		}
		m_keyIndexTablesHashMap.setValue(a_tableDataInfor->m_tableID, table);
		return true;
	}
	if (!table->loadDataFromDBByWhere(dbConnection, a_tableDataInfor->m_dbTableName, a_key, a_index,a_strWhere)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从数据库加载数据失败[TableID=%d][TableName=%s]", a_tableDataInfor->m_tableID, a_tableDataInfor->m_dbTableName.c_str());
		return false;
	}
	return true;
}

bool CTableDataMgr::_loadKeyTableByWhere(const SDbColumnInfor* a_tableDataInfor, const std::string& a_sqlWhere)
{
	const BSLib::Database::SDbColumn* dbColumn = a_tableDataInfor->m_dbTableColumn;
	if (dbColumn == NULL) {
		return false;
	}

	BSLib::Database::CDbConnection* dbConnection = NULL;
	switch (a_tableDataInfor->m_connectType) {
		case EDBCNNCTTYPE_LOCAL:
			dbConnection = &m_dbConnectionLocal;
			break;
		case EDBCNNCTTYPE_GLOBAL:
			dbConnection = &m_dbConnectionGlobal;
			break;
	}

	BSLib::Database::CDBKeyTable* table = NULL;
	m_keyTablesHashMap.getValue(a_tableDataInfor->m_tableID, table);
	if (table == NULL) {
		BSLib::Database::CDBKeyTable* table = new BSLib::Database::CDBKeyTable(dbColumn);
		if (table == NULL) {
			return false;
		}
		if (!table->loadDataFromDBByWhere(dbConnection, a_tableDataInfor->m_dbTableName, a_sqlWhere)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从数据库加载数据失败[TableID=%d][TableName=%s]", a_tableDataInfor->m_tableID, a_tableDataInfor->m_dbTableName.c_str());
			BSLIB_SAFE_DELETE(table);
			return false;
		}	
		m_keyTablesHashMap.setValue(a_tableDataInfor->m_tableID, table);
		return true;
	}
	if (!table->loadDataFromDBByWhere(dbConnection, a_tableDataInfor->m_dbTableName, a_sqlWhere)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从数据库加载数据失败[TableID=%d][TableName=%s]", a_tableDataInfor->m_tableID, a_tableDataInfor->m_dbTableName.c_str());
		return false;
	}	
	return true;
}

bool CTableDataMgr::_loadKeyIndexTableByWhere(const SDbColumnInfor* a_tableDataInfor, const std::string& a_sqlWhere)
{
	const BSLib::Database::SDbColumn* dbColumn = a_tableDataInfor->m_dbTableColumn;
	if (dbColumn == NULL) {
		return false;
	}
	BSLib::Database::CDbConnection* dbConnection = NULL;
	switch (a_tableDataInfor->m_connectType) {
		case EDBCNNCTTYPE_LOCAL:
			dbConnection = &m_dbConnectionLocal;
			break;
		case EDBCNNCTTYPE_GLOBAL:
			dbConnection = &m_dbConnectionGlobal;
			break;
	}

	BSLib::Database::CDBKeyIndexTable* table = NULL;
	m_keyIndexTablesHashMap.getValue(a_tableDataInfor->m_tableID, table);
	if (table == NULL) {
		table = new BSLib::Database::CDBKeyIndexTable(dbColumn);
		if (table == NULL) {
			return false;
		}
		if (!table->loadDataFromDBByWhere(dbConnection, a_tableDataInfor->m_dbTableName, a_sqlWhere)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从数据库加载数据失败[TableID=%d][TableName=%s]", a_tableDataInfor->m_tableID, a_tableDataInfor->m_dbTableName.c_str());
			BSLIB_SAFE_DELETE(table);
			return false;
		}
		m_keyIndexTablesHashMap.setValue(a_tableDataInfor->m_tableID, table);
		return true;
	}
	if (!table->loadDataFromDBByWhere(dbConnection, a_tableDataInfor->m_dbTableName, a_sqlWhere)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从数据库加载数据失败[TableID=%d][TableName=%s]", a_tableDataInfor->m_tableID, a_tableDataInfor->m_dbTableName.c_str());
		return false;
	}
	return true;
}

bool CTableDataMgr::_saveKeyTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key)
{
	BSLib::Database::CDbConnection* dbConnection = NULL;
	switch (a_tableDataInfor->m_connectType) {
		case EDBCNNCTTYPE_LOCAL:
			dbConnection = &m_dbConnectionLocal;
			break;
		case EDBCNNCTTYPE_GLOBAL:
			dbConnection = &m_dbConnectionGlobal;
			break;
	}

	BSLib::Database::CDBKeyTable* table = NULL;
	m_keyTablesHashMap.getValue(a_tableDataInfor->m_tableID, table);
	if (table == NULL) {
		return true;
	}
	//dbConnection->setTransactions(true);
	if (!table->saveDataToDB(dbConnection, a_tableDataInfor->m_dbTableName, a_key)) {
		//dbConnection->setTransactions(false);
		return false;
	}
	//dbConnection->commit();
	//dbConnection->setTransactions(false);
	return true;
}

bool CTableDataMgr::_saveKeyIndexTable(const SDbColumnInfor* a_tableDataInfor, const std::string& a_key, const std::string& a_index)
{
	BSLib::Database::CDbConnection* dbConnection = NULL;
	switch (a_tableDataInfor->m_connectType) {
		case EDBCNNCTTYPE_LOCAL:
			dbConnection = &m_dbConnectionLocal;
			break;
		case EDBCNNCTTYPE_GLOBAL:
			dbConnection = &m_dbConnectionGlobal;
			break;
	}
	BSLib::Database::CDBKeyIndexTable* table = NULL;
	m_keyIndexTablesHashMap.getValue(a_tableDataInfor->m_tableID, table);
	if (table == NULL) {
		return true;
	}
	//dbConnection->setTransactions(true);
	if (!table->saveDataToDB(dbConnection, a_tableDataInfor->m_dbTableName, a_key, a_index)) {
		//dbConnection->rollback();
		//dbConnection->setTransactions(false);
		return false;
	}
	//dbConnection->commit();
	//dbConnection->setTransactions(false);
	return true;
}


void CTableDataMgr::_saveAllKeyTable(const std::string& a_key)
{
	BSLib::Utility::CHashMap<EDBTableID, BSLib::Database::CDBKeyTable*>::iterator it_key = m_keyTablesHashMap.begin();
	for (; it_key != m_keyTablesHashMap.end(); ++it_key) {
		BSLib::Database::CDBKeyTable* talbe = it_key->second;
		if (talbe == NULL) {
			continue;
		}
		const SDbColumnInfor* columnInfor = _getTableDataInfor(it_key->first);
		if (columnInfor == NULL) {
			continue;
		}
		_saveKeyTable(columnInfor, a_key);
	}
}

void CTableDataMgr::_saveAllKeyIndexTable(const std::string& a_key, const std::string& a_index)
{
	BSLib::Utility::CHashMap<EDBTableID, BSLib::Database::CDBKeyIndexTable*>::iterator it_keyIndex = m_keyIndexTablesHashMap.begin();
	for (; it_keyIndex != m_keyIndexTablesHashMap.end(); ++it_keyIndex) {
		BSLib::Database::CDBKeyIndexTable* talbe = it_keyIndex->second;
		if (talbe == NULL) {
			continue;
		}
		const SDbColumnInfor* columnInfor = _getTableDataInfor(it_keyIndex->first);
		if (columnInfor == NULL) {
			continue;
		}
		_saveKeyIndexTable(columnInfor, a_key, a_index);
	}
}

}//DB

}//LoginSystem

}//GSLib

