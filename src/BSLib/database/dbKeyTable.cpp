//////////////////////////////////////////////////////////////////////
//	created:	2014/10/24
//	filename: 	src\BSLib\database\dbKeyTable.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/tracer.h>
#include <BSLib/database/dbKeyTable.h>
#include "mysqlConnectionPool.h"
#include "dbThreadTask.h"

namespace BSLib
{

namespace Database
{


CDBKeyTable::CDBKeyTable(const SDbColumn* a_dbColumn)
: m_dbTableHead(a_dbColumn)
{
	;
}

CDBKeyTable::~CDBKeyTable()
{
	clear();
}

//导入导出数据
bool CDBKeyTable::serializeTo(BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState, bool a_resetState) 
{
	std::vector<std::string> removeList;

	BSLib::Utility::CHashMap<std::string, CDBTableRow*>::const_iterator it = m_tableRowsHashMap.begin();
	for (; it != m_tableRowsHashMap.end(); ++it) {
		CDBTableRow* row = it->second;
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
				} else if(a_tableRowState == EDBTBLRWST_REMOVE) {
					removeList.push_back(it->first);
				}
			}
		}
	}
	for (BSLib::uint32 i=0; i<removeList.size(); ++i) {
		CDBTableRow* row = NULL;
		m_tableRowsHashMap.getValue(removeList[i], row);
		if (row != NULL) {
			BSLIB_SAFE_DELETE(row);
		}
		m_tableRowsHashMap.remove(removeList[i]);
	}
	removeList.clear();
	return true;
}

bool CDBKeyTable::serializeTo(const std::string& a_key, BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState, bool a_resetState)
{
	if (a_key.empty()) {
		return serializeTo(a_stream, a_tableRowState, a_resetState);
	}
	CDBTableRow* row = getRow(a_key);
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
	if (a_tableRowState != rowState){
		return true;
	}
	if (!row->serializeTo(a_stream)) {
		return false;
	}
	if (a_resetState) {
		if (a_tableRowState == EDBTBLRWST_UPDATE) {
			row->setRowState(EDBTBLRWST_NULL);
		} else if(a_tableRowState == EDBTBLRWST_REMOVE){
			BSLIB_SAFE_DELETE(row);
			m_tableRowsHashMap.remove(a_key);
		}
	}
	return true;
}

bool CDBKeyTable::serializeFrom(BSLib::Utility::CStream& a_stream)
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

bool CDBKeyTable::serializeKeyTo(BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState, bool a_resetState)
{
	std::vector<std::string> removeList;

	BSLib::Utility::CHashMap<std::string, CDBTableRow*>::const_iterator it = m_tableRowsHashMap.begin();
	for (; it != m_tableRowsHashMap.end(); ++it) {
		CDBTableRow* row = it->second;
		if (row == NULL) {
			continue;
		}
		if (a_tableRowState == EDBTBLRWST_NULL) {
			if (row->getRowState() != EDBTBLRWST_REMOVE) {
				a_stream << row->getKey();
			}
			continue;
		} 
		EDBTableRowState rowState = row->getRowState();
		if (a_tableRowState == rowState){
			a_stream << row->getKey();
			if (a_resetState) {
				if (a_tableRowState == EDBTBLRWST_REMOVE) {
					row->setRowState(EDBTBLRWST_NULL);
				} else {
					removeList.push_back(it->first);
				}
			}
		}
	}
	for (BSLib::uint32 i=0; i<removeList.size(); ++i) {
		CDBTableRow* row = NULL;
		m_tableRowsHashMap.getValue(removeList[i], row);
		if (row != NULL) {
			BSLIB_SAFE_DELETE(row);
		}
		m_tableRowsHashMap.remove(removeList[i]);
	}
	removeList.clear();
	return true;
}

bool CDBKeyTable::update(const std::string& a_key, const std::string& a_itemName, void* a_buffer, BSLib::uint32 a_buffSize)
{
	BSLib::Utility::CStream stream;
	stream.write((char*)a_buffer, a_buffSize);
	return update(a_key, a_itemName, stream);
}

//更新或添加数据
bool CDBKeyTable::update(const std::string& a_key, const std::string& a_itemName, BSLib::Utility::CStream& a_stream)
{
	if (a_itemName.empty()) {
		return update(a_key, a_stream);
	}
	CDBTableRow* tableRow = NULL;
	m_tableRowsHashMap.getValue(a_key, tableRow);
	if (tableRow == NULL) {
		return false;
	}
	if (m_dbTableHead.isKey(a_itemName)) {
		return false;
	}
	return tableRow->update(a_itemName, a_stream);
}

bool CDBKeyTable::update(const std::string& a_key, BSLib::int32 a_itemNumber, void* a_buffer, BSLib::uint32 a_buffSize)
{
	BSLib::Utility::CStream stream;
	stream.write((char*)a_buffer, a_buffSize);
	return update(a_key, a_itemNumber, stream);
}

bool CDBKeyTable::update(const std::string& a_key, BSLib::int32 a_itemNumber, BSLib::Utility::CStream& a_stream)
{
	if (a_itemNumber < 0) {
		return update(a_key, a_stream);
	}
	CDBTableRow* tableRow = NULL;
	m_tableRowsHashMap.getValue(a_key, tableRow);
	if (tableRow == NULL) {
		return false;
	}
	if (m_dbTableHead.isKey(a_itemNumber)) {
		return false;
	}
	return tableRow->update(a_itemNumber, a_stream);
}

bool CDBKeyTable::update(const std::string& a_key, void* a_buffer, BSLib::uint32 a_buffSize)
{
	BSLib::Utility::CStream stream;
	stream.write((char*)a_buffer, a_buffSize);
	return update(a_key, stream);
}

bool CDBKeyTable::update(const std::string& a_key, BSLib::Utility::CStream& a_stream)
{
	if (!a_stream.readReady()) {
		return false;
	}
	if (a_key.empty()) {
		return update(a_stream);
	}
	CDBTableRow* tableRow = NULL;
	m_tableRowsHashMap.getValue(a_key, tableRow);
	if (tableRow == NULL) {
		tableRow =_createTableRow(a_stream);
		if (tableRow == NULL) {
			return false;
		}
		if (tableRow->getKey() != a_key) {
			BSLIB_SAFE_DELETE(tableRow);
			return false;
		}
		tableRow->setRowState(EDBTBLRWST_UPDATE);
		if (!_addTableRow(tableRow)) {
			BSLIB_SAFE_DELETE(tableRow);
			return false;
		}
		return true;
	}
	return tableRow->update(a_stream);
}

bool CDBKeyTable::update(BSLib::Utility::CStream& a_stream)
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

//删除本行数据
void CDBKeyTable::remove(const std::string& a_key)
{
	if (a_key.empty()) {
		removeAll();
	}
	CDBTableRow* tableRow = NULL;
	m_tableRowsHashMap.getValue(a_key, tableRow);
	if (tableRow == NULL) {
		return ;
	}
	tableRow->remove();
}

void CDBKeyTable::removeAll()
{
	BSLib::Utility::CHashMap<std::string, CDBTableRow*>::iterator it = m_tableRowsHashMap.begin();
	for (; it != m_tableRowsHashMap.end(); ++it) {
		CDBTableRow* row = it->second;
		if (row != NULL) {
			row->remove();
		}
	}
}

void CDBKeyTable::clear(const std::string& a_key)
{
	if (a_key.empty()) {
		clear();
		return;
	}
	CDBTableRow* tableRow = NULL;
	m_tableRowsHashMap.getValue(a_key, tableRow);
	if (tableRow != NULL) {
		BSLIB_SAFE_DELETE(tableRow);
	}
	m_tableRowsHashMap.remove(a_key);
}

void CDBKeyTable::clear()
{
	BSLib::Utility::CHashMap<std::string, CDBTableRow*>::iterator it = m_tableRowsHashMap.begin();
	for (; it != m_tableRowsHashMap.end(); ++it) {
		CDBTableRow* row = it->second;
		if (row != NULL) {
			//row->clear();
			BSLIB_SAFE_DELETE(row);
			continue;
		}
	}
	m_tableRowsHashMap.clear();
}

CDBTableRow* CDBKeyTable::getRow(const std::string& a_key)
{
	CDBTableRow* tableRow = NULL;
	m_tableRowsHashMap.getValue(a_key, tableRow);
	return tableRow;
}

//获取失败，则抛出异常
CDBTableRow& CDBKeyTable::operator [](const std::string& a_key)
{
	CDBTableRow* tableRow = NULL;
	m_tableRowsHashMap.getValue(a_key, tableRow);
	if (tableRow == NULL) {
		tableRow = new CDBTableRow(&m_dbTableHead);
		if (tableRow == NULL) {
			throw BSLib::Utility::CException("null");
		}
		if (!tableRow->create(a_key, "")) {
			BSLIB_SAFE_DELETE(tableRow);
			throw BSLib::Utility::CException("null");
		}
		m_tableRowsHashMap.setValue(a_key, tableRow);
	}
	return *tableRow;
}

//从DB加载数据
bool CDBKeyTable::loadDataFromDBByWhere(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_sqlWhere)
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

bool CDBKeyTable::loadDataFromDBByWhere(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_key, const std::string& a_strWhere)
{
    BSLib::Utility::CStringA sqlWhere;
    if (a_key.empty()) { 
        if (a_strWhere.empty()) {
            return loadDataFromDB(a_dbConnection, a_dbTableName);
        }
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

    if (!a_strWhere.empty()) {
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

bool CDBKeyTable::loadDataFromDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName)
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

bool CDBKeyTable::loadDataFromDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_key)
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
bool CDBKeyTable::saveDataToDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName)
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

bool CDBKeyTable::saveDataToDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_key)
{
	const SDbColumn* columnInfor = m_dbTableHead.getColumnInfor();
	if (columnInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取表头信息失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	BSLib::Utility::CStream stream;
	if (!serializeTo(a_key, stream, EDBTBLRWST_UPDATE)) {
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
bool CDBKeyTable::saveDataToDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName)
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
		if (taskReplace->m_outDataBuffer.readReady()) {
			CMysqlConnectionPool::singleton().pushTask(taskPtr);
		}
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
		if (taskDelete->m_outDataBuffer.readReady()) {
			CMysqlConnectionPool::singleton().pushTask(taskPtr);
		}
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

bool CDBKeyTable::saveDataToDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_key)
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

	if (!serializeTo(a_key, taskReplace->m_outDataBuffer, EDBTBLRWST_UPDATE)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取更新序列化数据失败[TableName=%s]", a_dbTableName.c_str());
		return false;
	}
	if (CMysqlConnectionPool::singleton().isValid()) {
		if (taskReplace->m_outDataBuffer.readReady()) {
			CMysqlConnectionPool::singleton().pushTask(taskPtr);
		}
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
		if (taskDelete->m_outDataBuffer.readReady()) {
			CMysqlConnectionPool::singleton().pushTask(taskPtr);
		}
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
CDBTableRow* CDBKeyTable::_createTableRow(BSLib::Utility::CStream& a_stream)
{
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
	return tableRow;
}

bool CDBKeyTable::_addTableRow(CDBTableRow* a_talbeRow)
{
	const std::string& key = a_talbeRow->getKey();
	CDBTableRow* oldTableRow = NULL;
	m_tableRowsHashMap.getValue(key, oldTableRow);
	if (oldTableRow != NULL) {
		BSLIB_SAFE_DELETE(oldTableRow);
		m_tableRowsHashMap.remove(key);
	}
	m_tableRowsHashMap.setValue(key, a_talbeRow);
	return true;
}

void CDBKeyTable::_resetTableRowState(EDBTableRowState a_tableRowState)
{
	std::vector<std::string> removeList;

	BSLib::Utility::CHashMap<std::string, CDBTableRow*>::const_iterator it = m_tableRowsHashMap.begin();
	for (; it != m_tableRowsHashMap.end(); ++it) {
		CDBTableRow* row = it->second;
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
				removeList.push_back(it->first);
			}
		}
	}
	for (BSLib::uint32 i=0; i<removeList.size(); ++i) {
		CDBTableRow* row = NULL;
		m_tableRowsHashMap.getValue(removeList[i], row);
		if (row != NULL) {
			BSLIB_SAFE_DELETE(row);
		}
		m_tableRowsHashMap.remove(removeList[i]);
	}
	removeList.clear();
}

}//Database

}//BSLib
