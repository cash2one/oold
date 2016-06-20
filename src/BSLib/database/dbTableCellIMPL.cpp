//////////////////////////////////////////////////////////////////////
//	created:	2014/10/23
//	filename: 	src\BSLib\database\dbTableCellIMPL.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include "dbTableCellIMPL.h"

namespace BSLib
{

namespace Database
{


CDBTableCellFixBin::CDBTableCellFixBin(CDBTableRow* a_dbTableRow, BSLib::uint32 a_size)
: CDBTableCell(a_dbTableRow), m_size(a_size) 
{
	m_buffer.resize(a_size+1, 0);
}

CDBTableCellFixBin::~CDBTableCellFixBin()
{
	;
}

//导入导出数据接口
bool CDBTableCellFixBin::serializeTo(BSLib::Utility::CStream& stream) const
{ 
	stream.write(&m_buffer[0], m_size);
	return true;
}

bool CDBTableCellFixBin::serializeFrom(BSLib::Utility::CStream& stream)
{ 
	try {
		stream.read(&m_buffer[0], m_size);
		return true;
	} catch (...) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "序列化数据失败");
		return false;
	} 
} 

void CDBTableCellFixBin::setVarcharValue(const std::string& a_value)
{
	memset(&m_buffer[0], 0, m_size);

	if (m_size <= a_value.size()) {
		memcpy(&m_buffer[0], a_value.c_str(), m_size);
	} else {
		memcpy(&m_buffer[0], a_value.c_str(), a_value.size());
	}
}

void CDBTableCellFixBin::setBinValue(void* a_value, BSLib::uint32 a_valueSize) 
{
	memset(&m_buffer[0], 0, m_size);

	if (m_size <= a_valueSize) {
		memcpy(&m_buffer[0], a_value, m_size);
	} else {
		memcpy(&m_buffer[0], a_value, a_valueSize);
	} 
}

CDBTableCellVarBin::CDBTableCellVarBin(CDBTableRow* a_dbTableRow)
: CDBTableCell(a_dbTableRow), m_size(0) 
{
	;
}

CDBTableCellVarBin::~CDBTableCellVarBin()
{
	;
}

	//导入导出数据接口
bool CDBTableCellVarBin::serializeTo(BSLib::Utility::CStream& stream) const
{ 
	stream << m_size;
	if (m_size <= 0) {
		return true;
	}
	stream.write(&m_buffer[0], m_size);
	return true;
}

bool CDBTableCellVarBin::serializeFrom(BSLib::Utility::CStream& stream)
{ 
	try {
		BSLib::uint32 bufferSize =  (BSLib::uint32)m_buffer.size();
		BSLib::uint32 size = 0;
		stream >> size;
		if (size > bufferSize) {
			m_buffer.resize(size, 0);
			stream.read(&m_buffer[0], size);
			m_size = size;
		} else {
			if (size == 0) {
				m_size = 0;
			} else {
				stream.read(&m_buffer[0], size);
				m_size = size;
			}
		}
		return true;
	} catch (...) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "序列化数据失败");
		return false;
	}
} 

void CDBTableCellVarBin::setStringValue(const std::string& a_value)
{ 
	BSLib::uint32 bufferSize =  (BSLib::uint32)m_buffer.size();
	BSLib::uint32 size = (BSLib::uint32)a_value.size();
	if (size > bufferSize) {
		m_buffer.resize(size, 0);
		memcpy(&m_buffer[0], a_value.c_str(), size);
		m_size = size;
	} else {
		if (size == 0) {
			m_size = 0;
		} else {
			memcpy(&m_buffer[0], a_value.c_str(), size);
			m_size = size;
		}
	}
}

void CDBTableCellVarBin::setBlobValue(void* a_value, BSLib::uint32 a_valueSize)
{
	BSLib::uint32 bufferSize =  (BSLib::uint32)m_buffer.size();
	BSLib::uint32 size = a_valueSize;
	if (size > bufferSize) {
		m_buffer.resize(size, 0);
		memcpy(&m_buffer[0], a_value, size);
		m_size = size;
	} else {
		if (size == 0) {
			m_size = 0;
		} else {
			memcpy(&m_buffer[0], a_value, size);
			m_size = size;
		}
	}
}

}//Database

}//BSLib
