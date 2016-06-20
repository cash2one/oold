//////////////////////////////////////////////////////////////////////
//	created:	2014/10/24
//	filename: 	src\BSLib\database\dbKeyIndexTable.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/tracer.h>
#include <BSLib/database/dbKeyIndexTable.h>
#include "mysqlConnectionPool.h"
#include "dbThreadTask.h"

namespace BSLib
{

namespace Database
{

CDBKeyIndexTable::CDBKeyIndexTable(const SDbColumn* a_dbColumn)
: m_dbTableHead(a_dbColumn)
{
	;
}

CDBKeyIndexTable::~CDBKeyIndexTable()
{
	clear();;
}

//导入导出数据
bool CDBKeyIndexTable::serializeTo(BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState, bool a_resetState)
{
	std::vector<std::string> removeKeyList;

	BSLib::Utility::CHashMap<std::string,  BSLib::Utility::CHashMap<std::string, CDBTableRow*>* >::const_iterator it_tableKey = m_tableRowsHashMap.begin();
	for (; it_tableKey != m_tableRowsHashMap.end(); ++it_tableKey) {
		std::vector<std::string> removeIndexList;

		BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = it_tableKey->second;
		if (indexTableRows == NULL) {
			removeKeyList.push_back(it_tableKey->first);
			continue;
		}
		if (!_serializeTo(indexTableRows, a_stream, a_tableRowState, a_resetState)) {
			return false;
		}
		if (indexTableRows->empty()) {
			removeKeyList.push_back(it_tableKey->first);
		}
	}
	for (BSLib::uint32 i=0; i<removeKeyList.size(); ++i) {
		BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = NULL;
		m_tableRowsHashMap.getValue(removeKeyList[i], indexTableRows);
		if (indexTableRows != NULL) {
			BSLIB_SAFE_DELETE(indexTableRows);
		}
		m_tableRowsHashMap.remove(removeKeyList[i]);
	}
	removeKeyList.clear();
	return true;
}

bool CDBKeyIndexTable::serializeTo(const std::string& a_key, BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState, bool a_resetState)
{
	if (a_key.empty()) {
		return serializeTo(a_stream, a_tableRowState, a_resetState);
	}
	BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = NULL;
	m_tableRowsHashMap.getValue(a_key, indexTableRows);
	if (indexTableRows == NULL) {
		return true;
	}
	if (!_serializeTo(indexTableRows, a_stream, a_tableRowState, a_resetState)) {
		return false;
	}
	if (indexTableRows->empty()) {
		BSLIB_SAFE_DELETE(indexTableRows);
		m_tableRowsHashMap.remove(a_key);
	}
	return true;
}

bool CDBKeyIndexTable::serializeTo(const std::string& a_key, const std::string& a_index, BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState, bool a_resetState)
{
	if (a_key.empty()) {
		return serializeTo(a_stream, a_tableRowState, a_resetState);
	}
	if (a_index.empty()) {
		return serializeTo(a_key, a_stream, a_tableRowState, a_resetState);
	}
	BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = NULL;
	m_tableRowsHashMap.getValue(a_key, indexTableRows);
	if (indexTableRows == NULL) {
		return true;
	}
	CDBTableRow* row = NULL;
	indexTableRows->getValue(a_index, row);
	if (row == NULL) {
		return true;
	}
	if (a_tableRowState == EDBTBLRWST_NULL) {
		if (row->getRowState() != EDBTBLRWST_REMOVE) {
			if (!row->serializeTo(a_stream)) {
				return false;
			}
		}
		return true;
	} 
	EDBTableRowState rowState = row->getRowState();
	if (a_tableRowState == rowState){
		if (!row->serializeTo(a_stream)) {
			return false;
		}
		if (a_resetState) {
			if (a_tableRowState == EDBTBLRWST_UPDATE) {
				row->setRowState(EDBTBLRWST_NULL);
			} else if(a_tableRowState == EDBTBLRWST_REMOVE) {
				BSLIB_SAFE_DELETE(row);
				indexTableRows->remove(a_index);

				if (indexTableRows->empty()) {
					BSLIB_SAFE_DELETE(indexTableRows);
					m_tableRowsHashMap.remove(a_key);
				}
			}
		}
	}
	return true;
}

bool CDBKeyIndexTable::serializeFrom(BSLib::Utility::CStream& a_stream)
{
	while (a_stream.readReady()) {
		CDBTableRow* tableRow = _createTableRow(a_stream);
		if (tableRow == NULL) {
			return false;
		}
		if (!_addTableRow(tableRow)) {
			BSLIB_SAFE_DELETE(tableRow);
			return false;
		}
	}
	return true;
}

bool CDBKeyIndexTable::serializeKeyIndexTo(BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState, bool a_resetState)
{
	std::vector<std::string> removeKeyList;

	BSLib::Utility::CHashMap<std::string,  BSLib::Utility::CHashMap<std::string, CDBTableRow*>* >::const_iterator it_tableKey = m_tableRowsHashMap.begin();
	for (; it_tableKey != m_tableRowsHashMap.end(); ++it_tableKey) {
		std::vector<std::string> removeIndexList;

		BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = it_tableKey->second;
		if (indexTableRows == NULL) {
			removeKeyList.push_back(it_tableKey->first);
			continue;
		}
		if (!_serializeKeyIndexTo(indexTableRows, a_stream, a_tableRowState, a_resetState)) {
			return false;
		}
		if (indexTableRows->empty()) {
			removeKeyList.push_back(it_tableKey->first);
		}
	}
	for (BSLib::uint32 i=0; i<removeKeyList.size(); ++i) {
		BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = NULL;
		m_tableRowsHashMap.getValue(removeKeyList[i], indexTableRows);
		if (indexTableRows != NULL) {
			BSLIB_SAFE_DELETE(indexTableRows);
		}
		m_tableRowsHashMap.remove(removeKeyList[i]);
	}
	removeKeyList.clear();
	return true;
}

bool CDBKeyIndexTable::update(const std::string& a_key, const std::string& a_index, const std::string& a_itemName, void* a_buffer, BSLib::uint32 a_buffSize)
{
	BSLib::Utility::CStream stream;
	stream.write((char*)a_buffer, a_buffSize);
	return update(a_key, a_index, a_itemName, stream);
}

//更新或添加数据
bool CDBKeyIndexTable::update(const std::string& a_key, const std::string& a_index, const std::string& a_itemName, BSLib::Utility::CStream& a_stream)
{
	if (a_itemName.empty()) {
		return update(a_key, a_index, a_stream);
	}
	CDBTableRow* tableRow = getRow(a_key, a_index);
	if (tableRow == NULL) {
		return false;
	}
	return tableRow->update(a_itemName, a_stream);
}

bool CDBKeyIndexTable::update(const std::string& a_key, const std::string& a_index, BSLib::int32 a_itemNumber, void* a_buffer, BSLib::uint32 a_buffSize)
{
	BSLib::Utility::CStream stream;
	stream.write((char*)a_buffer, a_buffSize);
	return update(a_key, a_index, a_itemNumber, stream);
}

bool CDBKeyIndexTable::update(const std::string& a_key, const std::string& a_index, BSLib::int32 a_itemNumber, BSLib::Utility::CStream& a_stream)
{
	if (a_itemNumber < 0) {
		return update(a_key, a_index, a_stream);
	}
	CDBTableRow* tableRow = getRow(a_key, a_index);
	if (tableRow == NULL) {
		return false;
	}
	return tableRow->update(a_itemNumber, a_stream);
}

bool CDBKeyIndexTable::update(const std::string& a_key, const std::string& a_index, void* a_buffer, BSLib::uint32 a_buffSize)
{
	BSLib::Utility::CStream stream;
	stream.write((char*)a_buffer, a_buffSize);
	return update(a_key, stream);
}

bool CDBKeyIndexTable::update(const std::string& a_key, const std::string& a_index, BSLib::Utility::CStream& a_stream)
{
	if (a_key.empty()) {
		return update(a_stream);
	}
	if (a_index.empty()) {
		return update(a_key, a_stream);
	}
	CDBTableRow* tableRow = _createTableRow(a_stream);
	if (tableRow == NULL) {
		return false;
	}
	if (!a_key.empty()) {
		if (tableRow->getKey() != a_key) {
			BSLIB_SAFE_DELETE(tableRow);
			return false;
		}
	}
	if (!a_index.empty()) {
		if (tableRow->getIndex() != a_index) {
			BSLIB_SAFE_DELETE(tableRow);
			return false;
		}
	}
	tableRow->setRowState(EDBTBLRWST_UPDATE);
	if (!_addTableRow(tableRow)) {
		BSLIB_SAFE_DELETE(tableRow);
		return false;
	}
	return true;
}

bool CDBKeyIndexTable::update(BSLib::Utility::CStream& a_stream)
{
	while (a_stream.readReady()) {
		CDBTableRow* tableRow = _createTableRow(a_stream);
		if (tableRow == NULL) {
			return false;
		}
		tableRow->setRowState(EDBTBLRWST_UPDATE);
		if (!_addTableRow(tableRow)) {
			BSLIB_SAFE_DELETE(tableRow);
			return false;
		}
	}
	return true;
}

bool CDBKeyIndexTable::update(const std::string& a_key, BSLib::Utility::CStream& a_stream)
{
	while (a_stream.readReady()) {
		CDBTableRow* tableRow = _createTableRow(a_stream);
		if (tableRow == NULL) {
			return false;
		}
		if (!a_key.empty()) {
			if (tableRow->getKey() != a_key) {
				BSLIB_SAFE_DELETE(tableRow);
				return false;
			}
		}
		tableRow->setRowState(EDBTBLRWST_UPDATE);
		if (!_addTableRow(tableRow)) {
			BSLIB_SAFE_DELETE(tableRow);
			return false;
		}
	}
	return true;
}

//删除本行数据
void CDBKeyIndexTable::remove(const std::string& a_key)
{
	if (a_key.empty()) {
		removeAll();
		return;
	}
	BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = NULL;
	m_tableRowsHashMap.getValue(a_key, indexTableRows);
	if (indexTableRows == NULL) {
		return ;
	}
	BSLib::Utility::CHashMap<std::string, CDBTableRow*>::iterator it = indexTableRows->begin();
	for (; it != indexTableRows->end(); ++it) {
		CDBTableRow* row = it->second;
		if (row != NULL) {
			row->remove();
		}
	}
}

void CDBKeyIndexTable::remove(const std::string& a_key, const std::string& a_index)
{
	if (a_key.empty()) {
		removeAll();
		return;
	}
	if (a_index.empty()) {
		remove(a_key);
		return;
	}
	CDBTableRow* row = getRow(a_key, a_index);
	if (row == NULL) {
		return;
	}
	row->remove();
}

void CDBKeyIndexTable::removeAll()
{
	BSLib::Utility::CHashMap<std::string,  BSLib::Utility::CHashMap<std::string, CDBTableRow*>* >::const_iterator it_tableKey = m_tableRowsHashMap.begin();
	for (; it_tableKey != m_tableRowsHashMap.end(); ++it_tableKey) {
		BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = it_tableKey->second;
		if (indexTableRows == NULL) {
			continue;;
		}
		BSLib::Utility::CHashMap<std::string, CDBTableRow*>::const_iterator it_tableIndex = indexTableRows->begin();
		for (; it_tableIndex != indexTableRows->end(); ++it_tableIndex) {
			CDBTableRow* row = it_tableIndex->second;
			if (row != NULL) {
				row->remove();
			}
		}
	}
}

void CDBKeyIndexTable::clear(const std::string& a_key)
{
	if (a_key.empty()) {
		clear();
		return ;
	}
	BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = NULL;
	m_tableRowsHashMap.getValue(a_key, indexTableRows);
	if (indexTableRows == NULL) {
		return ;
	}
	BSLib::Utility::CHashMap<std::string, CDBTableRow*>::const_iterator it_tableIndex = indexTableRows->begin();
	for (; it_tableIndex != indexTableRows->end(); ++it_tableIndex) {
		CDBTableRow* row = it_tableIndex->second;
		if (row != NULL) {
			BSLIB_SAFE_DELETE(row);
		}
	}
	indexTableRows->clear();
	BSLIB_SAFE_DELETE(indexTableRows);
	m_tableRowsHashMap.remove(a_key);
}

void CDBKeyIndexTable::clear(const std::string& a_key, const std::string& a_index)
{
	if (a_key.empty()) {
		clear();
		return;
	}
	if (a_index.empty()) {
		clear(a_key);
		return ;
	}
	BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = NULL;
	m_tableRowsHashMap.getValue(a_key, indexTableRows);
	if (indexTableRows == NULL) {
		return ;
	}
	CDBTableRow* row = NULL;
	indexTableRows->getValue(a_index, row);
	if (row == NULL) {
		return;
	}
	BSLIB_SAFE_DELETE(row);
	indexTableRows->remove(a_index);
	if (indexTableRows->empty()) {
		BSLIB_SAFE_DELETE(indexTableRows);
		m_tableRowsHashMap.remove(a_key);
	}
}

void CDBKeyIndexTable::clear()
{
	BSLib::Utility::CHashMap<std::string,  BSLib::Utility::CHashMap<std::string, CDBTableRow*>* >::const_iterator it_tableKey = m_tableRowsHashMap.begin();
	for (; it_tableKey != m_tableRowsHashMap.end(); ++it_tableKey) {
		BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = it_tableKey->second;
		if (indexTableRows == NULL) {
			continue;;
		}
		BSLib::Utility::CHashMap<std::string, CDBTableRow*>::const_iterator it_tableIndex = indexTableRows->begin();
		for (; it_tableIndex != indexTableRows->end(); ++it_tableIndex) {
			CDBTableRow* row = it_tableIndex->second;
			if (row != NULL) {
				row->clear();
				BSLIB_SAFE_DELETE(row);
			}
		}
		indexTableRows->clear();
		BSLIB_SAFE_DELETE(indexTableRows);
	}
	m_tableRowsHashMap.clear();
}

const BSLib::Utility::CHashMap<std::string, CDBTableRow*>* CDBKeyIndexTable::getRows(const std::string& a_key)
{
	BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = NULL;
	m_tableRowsHashMap.getValue(a_key, indexTableRows);
	return indexTableRows;
}

CDBTableRow* CDBKeyIndexTable::getRow(const std::string& a_key, const std::string& a_index)
{
	const BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = getRows(a_key);
	if (indexTableRows == NULL) {
		return NULL;
	}
	CDBTableRow* row = NULL;
	indexTableRows->getValue(a_index, row);
	return row;
}

CDBTableRow& CDBKeyIndexTable::operator ()(const std::string& a_key, const std::string& a_index)
{
	CDBTableRow* tableRow = new CDBTableRow(&m_dbTableHead);
	if (tableRow == NULL) {
		throw BSLib::Utility::CException("null");
	}
	if (!tableRow->create(a_key, a_index)) {
		BSLIB_SAFE_DELETE(tableRow);
		throw BSLib::Utility::CException("null");
	}
	if (_addTableRow(tableRow)) {
		BSLIB_SAFE_DELETE(tableRow);
		throw BSLib::Utility::CException("null");
	}
	return *tableRow;
}

//从DB加载数据
bool CDBKeyIndexTable::loadDataFromDBByWhere(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_sqlWhere)
{
	const SDbColumn* columnInfor = m_dbTableHead.getColumnInfor();
	if (columnInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取表头信息失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	BSLib::Utility::CStream stream;

	if (a_dbConnection->executeSelect(a_dbTableName, a_sqlWhere, "", columnInfor, stream) < 0) {
		return false;
	}
	if (m_dbTableHead.isAutoIncrement()) {
		if (!m_dbTableHead.getAutoIncrement(a_dbConnection, a_dbTableName)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取表头自动增加值失败[TableName=%s]", a_dbTableName.c_str());
			return false;
		}
	}
	return serializeFrom(stream);
}

bool CDBKeyIndexTable::loadDataFromDBByWhere(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_key, const std::string& a_index, const std::string& a_strWhere)
{
    BSLib::Utility::CStringA sqlWhere;
    if (a_key.empty()) {
        if(a_strWhere.empty()){
            return loadDataFromDB(a_dbConnection, a_dbTableName);
        }
        BSLIB_LOG_DEBUG(ETT_BSLIB_DATABASE, "[a_key.empty()][!a_strWhere.empty()][TableName=%s]", a_dbTableName.c_str());
        sqlWhere += a_strWhere;
        return loadDataFromDBByWhere(a_dbConnection,a_dbTableName,a_strWhere);
    }
    const SDbColumn* columnInfor = m_dbTableHead.getColumnInfor();
    if (columnInfor == NULL) {
        BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取表头信息失败[TableName=%s]", a_dbTableName.c_str());
        return false;
    }
    if (!m_dbTableHead.getKeyStrWhere(a_dbConnection, a_key, sqlWhere)){
        BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取Key数据失败信息失败[TableName=%s]", a_dbTableName.c_str());
        return false;
    }
    if (!a_index.empty()) {
        BSLib::Utility::CStringA sqlWhereIndex;
        if (!m_dbTableHead.getIndexStrWhere(a_dbConnection, a_index, sqlWhereIndex)){
            BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取Index数据失败信息失败[TableName=%s]", a_dbTableName.c_str());
            return false;
        }
        sqlWhere += " AND ";
        sqlWhere += sqlWhereIndex;
    }
    if(!a_strWhere.empty()){
        sqlWhere += " AND ";
        sqlWhere += a_strWhere;
    }

    BSLib::Utility::CStream stream;
    if (a_dbConnection->executeSelect(a_dbTableName, sqlWhere, "", columnInfor, stream) < 0) {
        return false;
    }
	if (m_dbTableHead.isAutoIncrement()) {
		if (!m_dbTableHead.getAutoIncrement(a_dbConnection, a_dbTableName)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取表头自动增加值失败[TableName=%s]", a_dbTableName.c_str());
			return false;
		}
	}
    return serializeFrom(stream);
}

bool CDBKeyIndexTable::loadDataFromDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName)
{
	const SDbColumn* columnInfor = m_dbTableHead.getColumnInfor();
	if (columnInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取表头信息失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	BSLib::Utility::CStream stream;

	if (a_dbConnection->executeSelect(a_dbTableName, "", "", columnInfor, stream) < 0) {
		return false;
	}
	if (m_dbTableHead.isAutoIncrement()) {
		if (!m_dbTableHead.getAutoIncrement(a_dbConnection, a_dbTableName)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取表头自动增加值失败[TableName=%s]", a_dbTableName.c_str());
			return false;
		}
	}
	return serializeFrom(stream);
}

bool CDBKeyIndexTable::loadDataFromDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_key, const std::string& a_index)
{
	if (a_key.empty()) {
		return loadDataFromDB(a_dbConnection, a_dbTableName);
	}
	const SDbColumn* columnInfor = m_dbTableHead.getColumnInfor();
	if (columnInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取表头信息失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	BSLib::Utility::CStringA sqlWhere;
	if (!m_dbTableHead.getKeyStrWhere(a_dbConnection, a_key, sqlWhere)){
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取Key数据失败信息失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	if (!a_index.empty()) {
		BSLib::Utility::CStringA sqlWhereIndex;
		if (!m_dbTableHead.getIndexStrWhere(a_dbConnection, a_index, sqlWhereIndex)){
			BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取Index数据失败信息失败[TableName=%s]", a_dbTableName.c_str());
			return false;
		}
		sqlWhere += " AND ";
		sqlWhere += sqlWhereIndex;
	}
	
	BSLib::Utility::CStream stream;
	if (a_dbConnection->executeSelect(a_dbTableName, sqlWhere, "", columnInfor, stream) < 0) {
		return false;
	}
	if (m_dbTableHead.isAutoIncrement()) {
		if (!m_dbTableHead.getAutoIncrement(a_dbConnection, a_dbTableName)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取表头自动增加值失败[TableName=%s]", a_dbTableName.c_str());
			return false;
		}
	}
	return serializeFrom(stream);
}
/*
//保存数据到DB
bool CDBKeyIndexTable::saveDataToDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName)
{
	const SDbColumn* columnInfor = m_dbTableHead.getColumnInfor();
	if (columnInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取表头信息失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	BSLib::Utility::CStream stream;
	if (!serializeTo(stream, EDBTBLRWST_UPDATE)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取更新序列化数据失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	while (stream.readReady()) {
		if (!a_dbConnection->executeReplace(a_dbTableName, columnInfor, stream)) {
			return false;
		}
	}
	_resetTableRowState(EDBTBLRWST_UPDATE);
	stream.reset();
	if (!serializeTo(stream, EDBTBLRWST_REMOVE)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取删除序列化数据失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	while (stream.readReady()) {
		if (!a_dbConnection->executeDelete(a_dbTableName, columnInfor, stream)) {
			return false;
		}
	}
	_resetTableRowState(EDBTBLRWST_REMOVE);
	return true;
}

bool CDBKeyIndexTable::saveDataToDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_key, const std::string& a_index)
{
	const SDbColumn* columnInfor = m_dbTableHead.getColumnInfor();
	if (columnInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取表头信息失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	BSLib::Utility::CStream stream;
	if (!serializeTo(a_key, a_index, stream, EDBTBLRWST_UPDATE)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取更新序列化数据失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	while (stream.readReady()) {
		if (!a_dbConnection->executeReplace(a_dbTableName, columnInfor, stream)) {
			return false;
		}
	}
	_resetTableRowState(EDBTBLRWST_UPDATE);
	stream.reset();
	if (!serializeTo(stream, EDBTBLRWST_REMOVE)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取删除序列化数据失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	while (stream.readReady()) {
		if (!a_dbConnection->executeDelete(a_dbTableName, columnInfor, stream)) {
			return false;
		}
	}
	_resetTableRowState(EDBTBLRWST_REMOVE);
	return true;
}
*/

//保存数据到DB
bool CDBKeyIndexTable::saveDataToDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName)
{
	const SDbColumn* columnInfor = m_dbTableHead.getColumnInfor();
	if (columnInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取表头信息失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}

	BSLib::Utility::CThreadTaskPtr taskPtr = NULL;
	CDBReplaceTask* taskReplace = new CDBReplaceTask();
	if (taskReplace == NULL) {
		return false;
	}
	taskPtr = taskReplace;
	taskReplace->m_handle = a_dbConnection->getHandle();
	taskReplace->m_column = columnInfor;
	taskReplace->m_tableName = a_dbTableName;

	if (!serializeTo(taskReplace->m_outDataBuffer, EDBTBLRWST_UPDATE)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取更新序列化数据失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	if (CMysqlConnectionPool::singleton().isValid()) {
		CMysqlConnectionPool::singleton().pushTask(taskPtr);
	} else {
		while (taskReplace->m_outDataBuffer.readReady()) {
			if (!a_dbConnection->executeReplace(a_dbTableName, columnInfor, taskReplace->m_outDataBuffer)) {
				return false;
			}
		}
	}
	_resetTableRowState(EDBTBLRWST_UPDATE);

	CDBDeleteTask* taskDelete = new CDBDeleteTask();
	if (taskDelete == NULL) {
		return false;
	}
	taskPtr = taskDelete;
	taskDelete->m_handle = a_dbConnection->getHandle();
	taskDelete->m_column = columnInfor;
	taskDelete->m_tableName = a_dbTableName;
	if (!serializeTo(taskDelete->m_outDataBuffer, EDBTBLRWST_REMOVE)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取删除序列化数据失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	if (CMysqlConnectionPool::singleton().isValid()) {
		CMysqlConnectionPool::singleton().pushTask(taskPtr);
	} else {
		while (taskDelete->m_outDataBuffer.readReady()) {
			if (!a_dbConnection->executeDelete(a_dbTableName, columnInfor, taskDelete->m_outDataBuffer)) {
				return false;
			}
		}
	}
	_resetTableRowState(EDBTBLRWST_REMOVE);

	return true;
}

bool CDBKeyIndexTable::saveDataToDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_key, const std::string& a_index)
{
	const SDbColumn* columnInfor = m_dbTableHead.getColumnInfor();
	if (columnInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取表头信息失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}

	BSLib::Utility::CThreadTaskPtr taskPtr = NULL;
	CDBReplaceTask* taskReplace = new CDBReplaceTask();
	if (taskReplace == NULL) {
		return false;
	}
	taskPtr = taskReplace;
	taskReplace->m_handle = a_dbConnection->getHandle();
	taskReplace->m_column = columnInfor;
	taskReplace->m_tableName = a_dbTableName;

	if (!serializeTo(a_key, a_index, taskReplace->m_outDataBuffer, EDBTBLRWST_UPDATE)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取更新序列化数据失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	if (CMysqlConnectionPool::singleton().isValid()) {
		CMysqlConnectionPool::singleton().pushTask(taskPtr);
	} else {
		while (taskReplace->m_outDataBuffer.readReady()) {
			if (!a_dbConnection->executeReplace(a_dbTableName, columnInfor, taskReplace->m_outDataBuffer)) {
				return false;
			}
		}
	}
	_resetTableRowState(EDBTBLRWST_UPDATE);

	CDBDeleteTask* taskDelete = new CDBDeleteTask();
	if (taskDelete == NULL) {
		return false;
	}
	taskPtr = taskDelete;
	taskDelete->m_handle = a_dbConnection->getHandle();
	taskDelete->m_column = columnInfor;
	taskDelete->m_tableName = a_dbTableName;
	if (!serializeTo(taskDelete->m_outDataBuffer, EDBTBLRWST_REMOVE)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取删除序列化数据失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	if (CMysqlConnectionPool::singleton().isValid()) {
		CMysqlConnectionPool::singleton().pushTask(taskPtr);
	} else {
		while (taskDelete->m_outDataBuffer.readReady()) {
			if (!a_dbConnection->executeDelete(a_dbTableName, columnInfor, taskDelete->m_outDataBuffer)) {
				return false;
			}
		}
	}
	_resetTableRowState(EDBTBLRWST_REMOVE);

	return true;
}

void CDBKeyIndexTable::traversal(BSLib::Utility::CHashMap<std::string, CDBTableRow*>::CCallback& a_callback)
{
	BSLib::Utility::CHashMap<std::string,  BSLib::Utility::CHashMap<std::string, CDBTableRow*>* >::const_iterator it_tableKey = m_tableRowsHashMap.begin();
	for (; it_tableKey != m_tableRowsHashMap.end(); ++it_tableKey) {
		BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = it_tableKey->second;
		if (indexTableRows == NULL) {
			continue;;
		}
		indexTableRows->traversal(a_callback);
	}
}

void CDBKeyIndexTable::traversal(const std::string& a_key, BSLib::Utility::CHashMap<std::string, CDBTableRow*>::CCallback& a_callback)
{
	BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = NULL;
	m_tableRowsHashMap.getValue(a_key, indexTableRows);
	if (indexTableRows == NULL) {
		return ;
	}
	indexTableRows->traversal(a_callback);
}

bool CDBKeyIndexTable::_serializeTo(BSLib::Utility::CHashMap<std::string, CDBTableRow*>* a_indexTableRows, BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState, bool a_resetState)
{
	std::vector<std::string> removeIndexList;

	BSLib::Utility::CHashMap<std::string, CDBTableRow*>::const_iterator it_tableIndex = a_indexTableRows->begin();
	for (; it_tableIndex != a_indexTableRows->end(); ++it_tableIndex) {
		CDBTableRow* row = it_tableIndex->second;
		if (row == NULL) {
			continue;
		}
		if (a_tableRowState == EDBTBLRWST_NULL) {
			if (row->getRowState() != EDBTBLRWST_REMOVE) {
				if (!row->serializeTo(a_stream)) {
					return false;
				}
			}
			continue;
		} 
		EDBTableRowState rowState = row->getRowState();
		if (a_tableRowState == rowState){
			if (!row->serializeTo(a_stream)) {
				return false;
			}
			if (a_resetState) {
				if (a_tableRowState == EDBTBLRWST_UPDATE) {
					row->setRowState(EDBTBLRWST_NULL);
				} else if (a_tableRowState == EDBTBLRWST_REMOVE) {
					removeIndexList.push_back(it_tableIndex->first);
				}
			}
		}
	}
	for (BSLib::uint32 i=0; i<removeIndexList.size(); ++i) {
		CDBTableRow* row = NULL;
		a_indexTableRows->getValue(removeIndexList[i], row);
		if (row != NULL) {
			BSLIB_SAFE_DELETE(row);
		}
		a_indexTableRows->remove(removeIndexList[i]);
	}
	return true;
}

bool CDBKeyIndexTable::_serializeKeyIndexTo(BSLib::Utility::CHashMap<std::string, CDBTableRow*>* a_indexTableRows, BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState, bool a_resetState)
{
	std::vector<std::string> removeIndexList;

	BSLib::Utility::CHashMap<std::string, CDBTableRow*>::const_iterator it_tableIndex = a_indexTableRows->begin();
	for (; it_tableIndex != a_indexTableRows->end(); ++it_tableIndex) {
		CDBTableRow* row = it_tableIndex->second;
		if (row == NULL) {
			continue;
		}
		if (a_tableRowState == EDBTBLRWST_NULL) {
			if (row->getRowState() != EDBTBLRWST_REMOVE) {
				a_stream << row->getKey();
				a_stream << row->getIndex();
			}
			continue;
		} 
		EDBTableRowState rowState = row->getRowState();
		if (a_tableRowState == rowState){
			a_stream << row->getKey();
			a_stream << row->getIndex();
			if (a_resetState) {
				if (a_tableRowState == EDBTBLRWST_UPDATE) {
					row->setRowState(EDBTBLRWST_NULL);
				} else if (a_tableRowState == EDBTBLRWST_REMOVE){
					removeIndexList.push_back(it_tableIndex->first);
				}
			}
		}
	}
	for (BSLib::uint32 i=0; i<removeIndexList.size(); ++i) {
		CDBTableRow* row = NULL;
		a_indexTableRows->getValue(removeIndexList[i], row);
		if (row != NULL) {
			BSLIB_SAFE_DELETE(row);
		}
		a_indexTableRows->remove(removeIndexList[i]);
	}
	return true;
}


CDBTableRow* CDBKeyIndexTable::_createTableRow(BSLib::Utility::CStream& a_stream)
{
	if (!a_stream.readReady()) {
		return NULL;
	}
	CDBTableRow* tableRow = new CDBTableRow(&m_dbTableHead);
	if (tableRow == NULL) {
		return NULL;
	}
	if (!tableRow->serializeFrom(a_stream)) {
		BSLIB_SAFE_DELETE(tableRow);
		return NULL;
	}
	const std::string& key = tableRow->getKey();
	if (key.empty()) {
		BSLIB_SAFE_DELETE(tableRow);
		return NULL;
	}
	const std::string index = tableRow->getIndex();
	if (index.empty()) {
		BSLIB_SAFE_DELETE(tableRow);
		return NULL;
	}
	return tableRow;
}

bool CDBKeyIndexTable::_addTableRow(CDBTableRow* a_talbeRow)
{
	const std::string& key = a_talbeRow->getKey();
	const std::string& index = a_talbeRow->getIndex();
	BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = NULL;
	m_tableRowsHashMap.getValue(key, indexTableRows);
	if (indexTableRows == NULL) {
		indexTableRows = new BSLib::Utility::CHashMap<std::string, CDBTableRow*>;
		if (indexTableRows == NULL) {
			return false;
		}
		m_tableRowsHashMap.setValue(key, indexTableRows);
	}
	CDBTableRow* oldTableRow = NULL;
	indexTableRows->getValue(index, oldTableRow);
	if (oldTableRow != NULL) {
		BSLIB_SAFE_DELETE(oldTableRow);
		indexTableRows->remove(index);
	}
	indexTableRows->setValue(index, a_talbeRow);
	return true;
}

void CDBKeyIndexTable::_resetTableRowState(EDBTableRowState a_tableRowState)
{
	std::vector<std::string> removeKeyList;

	BSLib::Utility::CHashMap<std::string,  BSLib::Utility::CHashMap<std::string, CDBTableRow*>* >::const_iterator it_tableKey = m_tableRowsHashMap.begin();
	for (; it_tableKey != m_tableRowsHashMap.end(); ++it_tableKey) {
		BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = it_tableKey->second;
		if (indexTableRows == NULL) {
			removeKeyList.push_back(it_tableKey->first);
			continue;
		}
		_resetTableRowState(indexTableRows, a_tableRowState);
		if (indexTableRows->empty()) {
			removeKeyList.push_back(it_tableKey->first);
		}
	}
	for (BSLib::uint32 i=0; i<removeKeyList.size(); ++i) {
		BSLib::Utility::CHashMap<std::string, CDBTableRow*>* indexTableRows = NULL;
		m_tableRowsHashMap.getValue(removeKeyList[i], indexTableRows);
		if (indexTableRows != NULL) {
			BSLIB_SAFE_DELETE(indexTableRows);
		}
		m_tableRowsHashMap.remove(removeKeyList[i]);
	}
	removeKeyList.clear();
}

void CDBKeyIndexTable::_resetTableRowState(BSLib::Utility::CHashMap<std::string, CDBTableRow*>* a_indexTableRows, EDBTableRowState a_tableRowState)
{
	std::vector<std::string> removeIndexList;

	BSLib::Utility::CHashMap<std::string, CDBTableRow*>::const_iterator it_tableIndex = a_indexTableRows->begin();
	for (; it_tableIndex != a_indexTableRows->end(); ++it_tableIndex) {
		CDBTableRow* row = it_tableIndex->second;
		if (row == NULL) {
			continue;
		}
		if (a_tableRowState == EDBTBLRWST_NULL) {
			continue;
		} 
		EDBTableRowState rowState = row->getRowState();
		if (a_tableRowState == rowState){
			if (a_tableRowState == EDBTBLRWST_UPDATE) {
				row->setRowState(EDBTBLRWST_NULL);
			} else {
				removeIndexList.push_back(it_tableIndex->first);
			}
		}
	}
	for (BSLib::uint32 i=0; i<removeIndexList.size(); ++i) {
		CDBTableRow* row = NULL;
		a_indexTableRows->getValue(removeIndexList[i], row);
		if (row != NULL) {
			BSLIB_SAFE_DELETE(row);
		}
		a_indexTableRows->remove(removeIndexList[i]);
	}
}

}//Database

}//BSLib

