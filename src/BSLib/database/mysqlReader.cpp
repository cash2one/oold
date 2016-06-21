#include <BSLib/utility/convert.h>
#include "mysqlReader.h"

namespace BSLib
{

namespace Database
{

CMysqlReader::CMysqlReader(MYSQL_RES* mysqlRes)
: m_mysqlRes(mysqlRes)
, m_currentRow(NULL)
{
	if (mysqlRes != NULL){
		for (uint32 i=0; i<mysqlRes->field_count; ++i)	{
			m_lableHashMap.setValue(mysqlRes->fields[i].name, i);
		}
	}
	;
}

CMysqlReader::~CMysqlReader()
{
	close();
}

uint64 CMysqlReader::getRowCount() const
{
	if (m_mysqlRes == NULL) {
		return 0;
	}
	return m_mysqlRes->row_count;
}

int CMysqlReader::getColumnCount() const
{
	if (m_mysqlRes == NULL) {
		return 0;
	}
	return m_mysqlRes->field_count;
}

bool CMysqlReader::nextRow()
{
	if (m_mysqlRes == NULL) {
		return false;
	}
	m_currentRow = mysql_fetch_row(m_mysqlRes);
	if (m_currentRow == NULL) {
		return false;
	}
	m_lengths = mysql_fetch_lengths(m_mysqlRes);
	if (m_lengths == NULL) {
		m_currentRow = NULL;
		return false;
	}
	return true;
}

void CMysqlReader::close()
{
	if (m_mysqlRes != NULL) {
		mysql_free_result(m_mysqlRes);
		m_mysqlRes = NULL;
		m_currentRow = NULL;
		m_lableHashMap.clear();
	}
}

BSLib::uint64 CMysqlReader::getValueSize(int columnIndex) const
{
	return m_lengths[columnIndex];
}

BSLib::uint64 CMysqlReader::getValueSize(const std::string& columnLable) const
{
	int columnIndex = 0;
	if (!m_lableHashMap.getValue(columnLable.c_str(), columnIndex)) {
		return 0;
	}
	return m_lengths[columnIndex];
}

bool CMysqlReader::getValue(int columnIndex, int8& data) const
{
	if (m_currentRow == NULL) {
		return false;
	}
	data = (int8)BSLib::Utility::CConvert::toInt32(m_currentRow[columnIndex]);
	return true;
}

bool CMysqlReader::getValue(int columnIndex, uint8& data) const
{
	if (m_currentRow == NULL) {
		return false;
	}
	data = (uint8)BSLib::Utility::CConvert::toUint32(m_currentRow[columnIndex]);
	return true;
}

bool CMysqlReader::getValue(int columnIndex, int16& data) const
{
	if (m_currentRow == NULL) {
		return false;
	}
	data = (int16)BSLib::Utility::CConvert::toInt32(m_currentRow[columnIndex]);
	return true;
}

bool CMysqlReader::getValue(int columnIndex, uint16& data) const
{
	if (m_currentRow == NULL) {
		return false;
	}
	data = (uint16)BSLib::Utility::CConvert::toUint32(m_currentRow[columnIndex]);
	return true;
}

bool CMysqlReader::getValue(int columnIndex, int32& data) const
{
	if (m_currentRow == NULL) {
		return false;
	}
	data = (int32)BSLib::Utility::CConvert::toInt32(m_currentRow[columnIndex]);
	return true;
}

bool CMysqlReader::getValue(int columnIndex, uint32& data) const
{
	if (m_currentRow == NULL) {
		return false;
	}
	data = (uint32)BSLib::Utility::CConvert::toUint32(m_currentRow[columnIndex]);
	return true;
}

bool CMysqlReader::getValue(int columnIndex, int64& data) const
{
	if (m_currentRow == NULL) {
		return false;
	}
	data = (int64)BSLib::Utility::CConvert::toInt64(m_currentRow[columnIndex]);
	return true;
}

bool CMysqlReader::getValue(int columnIndex, uint64& data) const
{
	if (m_currentRow == NULL) {
		return false;
	}
	data = (uint64)BSLib::Utility::CConvert::toUint64(m_currentRow[columnIndex]);
	return true;
}

bool CMysqlReader::getValue(int columnIndex, float& data) const
{
	if (m_currentRow == NULL) {
		return false;
	}
	data = (float)BSLib::Utility::CConvert::toFloat(m_currentRow[columnIndex]);
	return true;
}

bool CMysqlReader::getValue(int columnIndex, double& data) const
{
	if (m_currentRow == NULL) {
		return false;
	}
	data = (double)BSLib::Utility::CConvert::toDouble(m_currentRow[columnIndex]);
	return true;
}

bool CMysqlReader::getValue(int columnIndex, std::string& data) const
{
	if (m_currentRow == NULL) {
		return false;
	}
	data = m_currentRow[columnIndex];
	return true;
}

bool CMysqlReader::getValue(int columnIndex, char* data, uint32 dataSize) const
{
	if (m_currentRow == NULL) {
		return false;
	}
	if (m_lengths[columnIndex] >= dataSize) {
		memcpy(data, m_currentRow[columnIndex], dataSize);
	} else if (m_lengths[columnIndex] > 0) {
		memcpy(data, m_currentRow[columnIndex], m_lengths[columnIndex]);
	}
	return true;
}

bool CMysqlReader::getValue(int columnIndex, BSLib::Utility::CStream& stream) const
{
	if (m_currentRow == NULL || m_lengths == NULL) {
		return false;
	}
	return stream.push(m_currentRow[columnIndex], m_lengths[columnIndex]);
}

bool CMysqlReader::getValue(const std::string& columnLable, int8& data) const
{
	int columnIndex = 0;
	if (!m_lableHashMap.getValue(columnLable.c_str(), columnIndex)) {
		return false;
	}
	return getValue(columnIndex, data);
}

bool CMysqlReader::getValue(const std::string& columnLable, uint8& data) const
{
	int columnIndex = 0;
	if (!m_lableHashMap.getValue(columnLable.c_str(), columnIndex)) {
		return false;
	}
	return getValue(columnIndex, data);
}

bool CMysqlReader::getValue(const std::string& columnLable, int16& data) const
{
	int columnIndex = 0;
	if (!m_lableHashMap.getValue(columnLable.c_str(), columnIndex)) {
		return false;
	}
	return getValue(columnIndex, data);
}

bool CMysqlReader::getValue(const std::string& columnLable, uint16& data) const
{
	int columnIndex = 0;
	if (!m_lableHashMap.getValue(columnLable.c_str(), columnIndex)) {
		return false;
	}
	return getValue(columnIndex, data);
}

bool CMysqlReader::getValue(const std::string& columnLable, int32& data) const
{
	int columnIndex = 0;
	if (!m_lableHashMap.getValue(columnLable.c_str(), columnIndex)) {
		return false;
	}
	return getValue(columnIndex, data);
}

bool CMysqlReader::getValue(const std::string& columnLable, uint32& data) const
{
	int columnIndex = 0;
	if (!m_lableHashMap.getValue(columnLable.c_str(), columnIndex)) {
		return false;
	}
	return getValue(columnIndex, data);
}

bool CMysqlReader::getValue(const std::string& columnLable, int64& data) const
{
	int columnIndex = 0;
	if (!m_lableHashMap.getValue(columnLable.c_str(), columnIndex)) {
		return false;
	}
	return getValue(columnIndex, data);
}

bool CMysqlReader::getValue(const std::string& columnLable, uint64& data) const
{
	int columnIndex = 0;
	if (!m_lableHashMap.getValue(columnLable.c_str(), columnIndex)) {
		return false;
	}
	return getValue(columnIndex, data);
}

bool CMysqlReader::getValue(const std::string& columnLable, float& data) const
{
	int columnIndex = 0;
	if (!m_lableHashMap.getValue(columnLable.c_str(), columnIndex)) {
		return false;
	}
	return getValue(columnIndex, data);
}

bool CMysqlReader::getValue(const std::string& columnLable, double& data) const
{
	int columnIndex = 0;
	if (!m_lableHashMap.getValue(columnLable.c_str(), columnIndex)) {
		return false;
	}
	return getValue(columnIndex, data);
}

bool CMysqlReader::getValue(const std::string& columnLable, std::string& data) const
{
	int columnIndex = 0;
	if (!m_lableHashMap.getValue(columnLable.c_str(), columnIndex)) {
		return false;
	}
	return getValue(columnIndex, data);
}

bool CMysqlReader::getValue(const std::string& columnLable, char* data, uint32 dataSize) const
{
	int columnIndex = 0;
	if (!m_lableHashMap.getValue(columnLable.c_str(), columnIndex)) {
		return false;
	}
	return getValue(columnIndex, data, dataSize);
}

bool CMysqlReader::getValue(const std::string& columnLable, BSLib::Utility::CStream& stream) const
{
	int columnIndex = 0;
	if (!m_lableHashMap.getValue(columnLable.c_str(), columnIndex)) {
		return false;
	}
	return getValue(columnIndex, stream);
}

}//Database

}//BSLib



