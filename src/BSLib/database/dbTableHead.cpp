//////////////////////////////////////////////////////////////////////
//	created:	2014/10/23
//	filename: 	src\BSLib\database\dbTableHead.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/database/dbTableHead.h>

namespace BSLib
{

namespace Database
{

CDBTableHead::CDBTableHead(const SDbColumn* a_dbColumn)
: m_dbColumn(a_dbColumn)
, m_columnCount(0)
, m_isAutoIncrement(false)
, m_autoIncrementValue(0)
{
	if (a_dbColumn == NULL) {
		return ;
	}
	m_columnCount = 0;
	for (BSLib::int32 i=0; !a_dbColumn[i].m_name.empty(); ++i) {
		m_namesHashMap.setValue(a_dbColumn[i].m_name, i);
		++m_columnCount;
		if (a_dbColumn->m_flag & EDF_INCREMENT) {
			m_isAutoIncrement = true;
		}
	}
}

std::string CDBTableHead::getName(BSLib::int32 a_nameNumber)
{
	if (a_nameNumber < 0 || a_nameNumber >= m_columnCount) {
		return "";
	}
	return m_dbColumn[a_nameNumber].m_name;
}

BSLib::int32 CDBTableHead::getNameNumber(const std::string& a_name)
{
	BSLib::int32 nameNumber = -1;
	m_namesHashMap.getValue(a_name, nameNumber);
	return nameNumber;
}

EDbParamType CDBTableHead::getType(BSLib::int32 a_nameNumber)
{
	if (a_nameNumber < 0 || a_nameNumber >= m_columnCount) {
		return EDT_NULL;
	}
	return m_dbColumn[a_nameNumber].m_type;
}

EDbParamType CDBTableHead::getType(const std::string& a_name)
{
	BSLib::int32 nameNumber = -1;
	m_namesHashMap.getValue(a_name, nameNumber);
	return getType(nameNumber);
}

BSLib::uint32 CDBTableHead::getSize(BSLib::int32 a_nameNumber)
{
	if (a_nameNumber < 0 || a_nameNumber >= m_columnCount) {
		return 0;
	}
	return m_dbColumn[a_nameNumber].m_size;
}

BSLib::uint32 CDBTableHead::getSize(const std::string& a_name)
{
	BSLib::int32 nameNumber = -1;
	m_namesHashMap.getValue(a_name, nameNumber);
	return getSize(nameNumber);
}

bool CDBTableHead::isKey(BSLib::int32 a_nameNumber)
{
	if (a_nameNumber < 0 || a_nameNumber >= m_columnCount) {
		return false;
	}
	return (m_dbColumn[a_nameNumber].m_flag & EDF_KEY) != 0;
}

bool CDBTableHead::isKey(const std::string& a_name)
{
	BSLib::int32 nameNumber = -1;
	m_namesHashMap.getValue(a_name, nameNumber);
	return isKey(nameNumber);
}

bool CDBTableHead::isIndex(BSLib::int32 a_nameNumber)
{
	if (a_nameNumber < 0 || a_nameNumber >= m_columnCount) {
		return false;
	}
	return (m_dbColumn[a_nameNumber].m_flag & EDF_INDEX) != 0;
}

bool CDBTableHead::isIndex(const std::string& a_name)
{
	BSLib::int32 nameNumber = -1;
	m_namesHashMap.getValue(a_name, nameNumber);
	return isIndex(nameNumber);
}

bool CDBTableHead::isAutoIncrement()
{
	return m_isAutoIncrement;
}

BSLib::uint32 CDBTableHead::getAutoIncrementValue()
{
	return m_autoIncrementValue;
}

BSLib::uint32 CDBTableHead::addAutoIncrementValue(BSLib::uint32 a_data)
{
	m_autoIncrementValue += a_data;
	return m_autoIncrementValue;
}

void CDBTableHead::setAutoIncrementValue(BSLib::uint32 a_value)
{
	m_autoIncrementValue = a_value;
}

BSLib::int32 CDBTableHead::getColumnCount()
{
	return m_columnCount;
}

bool CDBTableHead::getAutoIncrement(CDbConnection* a_dbConnection, const std::string& a_tableName)
{
	BSLib::Utility::CStringA strSql = "select auto_increment from information_schema.tables where table_schema = database() and table_name=\'";
	strSql += a_tableName;
	strSql += "\'";
	CDbReaderPtr readerPtr = NULL;
	a_dbConnection->executeQuery(strSql, readerPtr);
	if (readerPtr == NULL) {
		return false;
	}
	if (!readerPtr->nextRow()) {
		return false;
	}
	BSLib::uint32 autoIncrement = 0;
	if (!readerPtr->getValue(0, autoIncrement)) {
		return false;
	}
	m_autoIncrementValue = autoIncrement;
	return true;
}

bool CDBTableHead::getKeyStrWhere(CDbConnection* a_dbConnection, const std::string& a_key, BSLib::Utility::CStringA& a_strWhere)
{
	BSLib::Utility::CStream stream;
	stream.write(a_key.c_str(), (BSLib::uint32)a_key.size());
	return _getStrWhere(a_dbConnection, EDF_KEY, stream, a_strWhere);
}

bool CDBTableHead::getIndexStrWhere(CDbConnection* a_dbConnection, const std::string& a_index, BSLib::Utility::CStringA& a_strWhere)
{
	BSLib::Utility::CStream stream;
	stream.write(a_index.c_str(), (BSLib::uint32)a_index.size());
	return _getStrWhere(a_dbConnection, EDF_INDEX, stream, a_strWhere);
}

bool CDBTableHead::_getStrWhere(CDbConnection* a_dbConnection, EDbParamFlag a_paraFlag, BSLib::Utility::CStream& a_stream, BSLib::Utility::CStringA& a_strWhere)
{
	if (m_dbColumn == NULL) {
		return false;
	}
	bool first = true;
	const SDbColumn*column = m_dbColumn;
	while (!column->m_name.empty()) {
		if (column->m_flag != a_paraFlag) {
			++column;
			continue;
		}
		if (!a_stream.readReady()) {
			return true;
		}
		if (!first){
			a_strWhere += " AND ";
		} else {
			first = false;
		}
		a_strWhere += column->m_name;
		a_strWhere += "=";

		switch(column->m_type)
		{
		case EDT_INT8:
			{
				BSLib::int8 data;
				try {
					a_stream >> data;
				} catch (...) {
					a_strWhere.clear();
					return false;
				} 
				a_strWhere << data;
			}
			break;
		case EDT_UINT8:
			{
				BSLib::uint8 data;
				try {
					a_stream >> data;
				} catch (...) {
					a_strWhere.clear();
					return false;
				} 
				a_strWhere << data;
			}
			break;
		case EDT_INT16:
			{
				BSLib::int16 data;
				try {
					a_stream >> data;
				} catch (...) {
					a_strWhere.clear();
					return false;
				} 
				a_strWhere << data;
			}
			break;
		case EDT_UINT16:
			{
				BSLib::uint16 data;
				try {
					a_stream >> data;
				} catch (...) {
					a_strWhere.clear();
					return false;
				} 
				a_strWhere << data;
			}
			break;
		case EDT_INT32:
			{
				BSLib::int32 data;
				try {
					a_stream >> data;
				} catch (...) {
					a_strWhere.clear();
					return false;
				} 
				a_strWhere << data;
			}
			break;
		case EDT_UINT32:
			{
				BSLib::uint32 data;
				try {
					a_stream >> data;
				} catch (...) {
					a_strWhere.clear();
					return false;
				} 
				a_strWhere << data;
			}
			break;
		case EDT_INT64:
			{
				BSLib::int64 data;
				try {
					a_stream >> data;
				} catch (...) {
					a_strWhere.clear();
					return false;
				} 
				a_strWhere << data;
			}
			break;
		case EDT_UINT64:
			{
				BSLib::uint64 data;
				try {
					a_stream >> data;
				} catch (...) {
					a_strWhere.clear();
					return false;
				} 
				a_strWhere << data;
			}
			break;
		case EDT_FLOAT:
			{
				float data;
				try {
					a_stream >> data;
				} catch (...) {
					a_strWhere.clear();
					return false;
				} 
				a_strWhere << data;
			}
			break;
		case EDT_DOUBLE:
			{
				double data;
				try {
					a_stream >> data;
				} catch (...) {
					a_strWhere.clear();
					return false;
				} 
				a_strWhere << data;
			}
			break;
		case EDT_STRING:
			{
				std::string data;
				std::string temp;
				try {
					a_stream >> data;
				} catch (...) {
					a_strWhere.clear();
					return false;
				} 
				if (!a_dbConnection->escapeString(data, temp)) {
					a_strWhere.clear();
					return false;
				}
				a_strWhere <<  "\'" << temp << "\'";
			}
			break;
		case EDT_VARCHAR:
			{
				if (a_stream.readSize() < column->m_size) {
					a_strWhere.clear();
					return false;
				}
				std::string data = a_stream.readPtr();
				if (data.size() >= column->m_size) {
					data.resize(column->m_size - 1);
				}
				std::string temp;
				if (!a_dbConnection->escapeString(data, temp)) {
					a_strWhere.clear();
					return false;
				}
				a_strWhere <<  "\'" << temp << "\'";

				a_stream.readFlip(column->m_size);
			}
			break;
		case EDT_BLOB:
			{
				uint32 dataSize = 0;
				try {
					a_stream >> dataSize;
				} catch (...) {
					a_strWhere.clear();
					return false;
				}
				if (a_stream.readSize() < dataSize) {
					a_strWhere.clear();
					return false;
				}
				std::string temp;
				if (!a_dbConnection->escapeString(a_stream.readPtr(), dataSize, temp)) {
					a_strWhere.clear();
					return false;
				}
				a_strWhere <<  "\'" << temp << "\'";

				a_stream.readFlip(dataSize);
			}
			break;
		case EDT_BIN:
			{
				if (a_stream.readSize() < column->m_size) {
					a_strWhere.clear();
					return false;
				}
				std::string temp;
				if (!a_dbConnection->escapeString(a_stream.readPtr(), column->m_size, temp)) {
					a_strWhere.clear();
					return false;
				}
				a_strWhere <<  "\'" << temp << "\'";

				a_stream.readFlip(column->m_size);
			}
			break;
		default:
			{
				a_strWhere.clear();
				return false;
			}
		}
		++column;
	}
	return true;
}

}//Database

}//BSLib
