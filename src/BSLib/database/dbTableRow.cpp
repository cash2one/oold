#include <BSLib/database/dbTableRow.h>
#include "dbTableCellIMPL.h"

namespace BSLib
{

namespace Database
{

CDBTableRow::CDBTableRow(CDBTableHead* a_dbTableHead)
: m_dbTableHead(a_dbTableHead)
, m_rowState(EDBTBLRWST_NULL)
{
	;
}

CDBTableRow::~CDBTableRow()
{
	clear();
}

bool CDBTableRow::serializeTo(void* a_buffer, BSLib::uint32 a_buffSize) const
{
	BSLib::Utility::CStream stream;
	if (!serializeTo(stream)) {
		return false;
	}
	if (stream.readSize() < 0) {
		return false;
	}
	memcpy(a_buffer, stream.readPtr(), a_buffSize);
	return true;
}

//导入导出数据
bool CDBTableRow::serializeTo(BSLib::Utility::CStream& a_stream) const
{
	if (m_tableCells.size() <= 0) {
		return true;
	}
	for (BSLib::uint32 i=0; i<m_tableCells.size(); ++i) {
		CDBTableCell* tableCell = m_tableCells[i];
		if (tableCell == NULL) {
			BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "serializeTo信息不存在[CellNum=%d]失败", i);
			return false;
		}
		if (!tableCell->serializeTo(a_stream)) {
			if (m_dbTableHead != NULL) {
				std::string name = m_dbTableHead->getName(i);
				BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "serializeTo[CellNum=%d][CellName=%s]失败", i, name.c_str());
			} else {
				BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "serializeTo[CellNum=%d]失败", i);
			}
			return false;
		}
	}
	return true;
}

bool CDBTableRow::serializeFrom(BSLib::Utility::CStream& a_stream)
{
	if (m_tableCells.size() <= 0) {
		if (!_createTalbeRow()) {
			BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "创建TableRow失败");
			return false;
		}
	}
	BSLib::Utility::CStream keyStream;
	BSLib::Utility::CStream indexStream;
	for (BSLib::uint32 i=0; i<m_tableCells.size(); ++i) {
		CDBTableCell* tableCell = m_tableCells[i];
		if (tableCell == NULL) {
			BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "serializeFrom信息不存在[CellNum=%d]失败", i);
			return false;
		}
		if (!tableCell->serializeFrom(a_stream)) {
			if (m_dbTableHead != NULL) {
				std::string name = m_dbTableHead->getName(i);
				BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "serializeFrom[CellNum=%d][CellName=%s]失败", i, name.c_str());
			} else {
				BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "serializeFrom[CellNum=%d]失败", i);
			}
			return false;;
		}
		if (m_dbTableHead->isKey(i)) {
			if (!tableCell->serializeTo(keyStream)) {
				if (m_dbTableHead != NULL) {
					std::string name = m_dbTableHead->getName(i);
					BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取Key[CellNum=%d][CellName=%s]失败", i, name.c_str());
				} else {
					BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取Key[CellNum=%d]失败", i);
				}
				return false;
			}
		} 
		if (m_dbTableHead->isIndex(i)) {
			if (!tableCell->serializeTo(indexStream)) {
				if (m_dbTableHead != NULL) {
					std::string name = m_dbTableHead->getName(i);
					BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取Index[CellNum=%d][CellName=%s]失败", i, name.c_str());
				} else {
					BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取Index[CellNum=%d]失败", i);
				}
				return false;
			}
		}
	}
	if (keyStream.readReady()) {
		m_key.clear();
		m_key.append((char*)keyStream.readPtr(), keyStream.readSize());
	}
	if (indexStream.readReady()) {
		m_index.clear();
		m_index.append((char*)indexStream.readPtr(), indexStream.readSize());
	}
	return true;
}

//更新或添加数据
bool CDBTableRow::update(const std::string& a_itemName, BSLib::Utility::CStream& a_stream)
{
	CDBTableCell* tableCell = getCellValue(a_itemName);
	if (tableCell == NULL) {
		return false;
	}
	if (!tableCell->serializeFrom(a_stream)) {
		return false;
	}
	setRowState(EDBTBLRWST_UPDATE);
	return true;
}

bool CDBTableRow::update(BSLib::int32 a_itemNumber, BSLib::Utility::CStream& a_stream)
{
	CDBTableCell* tableCell = getCellValue(a_itemNumber);
	if (tableCell == NULL) {
		return false;
	}
	if (!tableCell->serializeFrom(a_stream)) {
		return false;
	}
	setRowState(EDBTBLRWST_UPDATE);
	return true;
}

bool CDBTableRow::update(BSLib::Utility::CStream& a_stream)
{
	if (!serializeFrom(a_stream)) {
		return false;
	}
	setRowState(EDBTBLRWST_UPDATE);
	return true;
}

bool CDBTableRow::create(const std::string& a_key, const std::string& a_index)
{
	if (m_tableCells.size() <= 0) {
		if (!_createTalbeRow()) {
			return false;
		}
	}
	BSLib::Utility::CStream keyStream;
	keyStream.write(a_key.c_str(), (BSLib::uint32)a_key.size());

	BSLib::Utility::CStream indexStream;
	indexStream.write(a_index.c_str(), (BSLib::uint32)a_index.size());

	for (BSLib::uint32 i=0; i<m_tableCells.size(); ++i) {
		CDBTableCell* tableCell = m_tableCells[i];
		if (tableCell == NULL) {
			return false;
		}
		if (m_dbTableHead->isKey(i)) {
			if (!tableCell->serializeFrom(keyStream)) {
				return false;
			}
		} 
		if (m_dbTableHead->isIndex(i)) {
			if (!tableCell->serializeFrom(indexStream)) {
				return false;
			}
		}
	}
	m_key = a_key;
	m_index = a_index;
	return true;
}

void CDBTableRow::clear()
{
	for (BSLib::uint32 i=0; i<m_tableCells.size(); ++i) {
		CDBTableCell* tableCell = m_tableCells[i];
		if (tableCell == NULL) {
			continue;
		}
		BSLIB_SAFE_DELETE(tableCell);
	}
	m_tableCells.clear();
}

CDBTableCell* CDBTableRow::getCellValue(const std::string& a_itemName)
{
	if (m_dbTableHead == NULL) {
		return NULL;
	}
	BSLib::int32 itemNumber = m_dbTableHead->getNameNumber(a_itemName);
	return getCellValue(itemNumber);
}

CDBTableCell* CDBTableRow::getCellValue(BSLib::int32 a_itemNumber)
{
	if (a_itemNumber < 0) {
		return NULL;
	}
	if ((BSLib::uint32)a_itemNumber > m_tableCells.size()) {
		return NULL;
	}
	return m_tableCells[a_itemNumber];
}

CDBTableCell& CDBTableRow::operator [](const std::string& a_itemName)
{
	CDBTableCell* tableCell = getCellValue(a_itemName);
	if (tableCell == NULL) {
		throw BSLib::Utility::CException("null");
	}
	return *tableCell;
}

CDBTableCell& CDBTableRow::operator [](BSLib::int32 a_itemNumber)
{
	CDBTableCell* tableCell = getCellValue(a_itemNumber);
	if (tableCell == NULL) {
		throw BSLib::Utility::CException("null");
	}
	return *tableCell;
}

bool CDBTableRow::_createTalbeRow()
{
	if (m_dbTableHead == NULL) {
		return false;
	}
	for (BSLib::int32 i=0; i<m_dbTableHead->getColumnCount(); ++i) {
		CDBTableCell* item = NULL;
		EDbParamType paraType = m_dbTableHead->getType(i);
		
		switch(paraType)
		{
		case BSLib::Database::EDT_INT8:
			item = new CDBTableCellNumber<BSLib::int8>(this);
			break;
		case BSLib::Database::EDT_UINT8:
			item = new CDBTableCellNumber<BSLib::uint8>(this);
			break;
		case BSLib::Database::EDT_INT16:
			item = new CDBTableCellNumber<BSLib::int16>(this);
			break;
		case BSLib::Database::EDT_UINT16:
			item = new CDBTableCellNumber<BSLib::uint16>(this);
			break;
		case BSLib::Database::EDT_INT32:
			item = new CDBTableCellNumber<BSLib::int32>(this);
			break;
		case BSLib::Database::EDT_UINT32:
			item = new CDBTableCellNumber<BSLib::uint32>(this);
			break;
		case BSLib::Database::EDT_INT64:
			item = new CDBTableCellNumber<BSLib::int64>(this);
			break;
		case BSLib::Database::EDT_UINT64:
			item = new CDBTableCellNumber<BSLib::uint64>(this);
			break;
		case BSLib::Database::EDT_FLOAT:
			item = new CDBTableCellNumber<float>(this);
			break;
		case BSLib::Database::EDT_DOUBLE:
			item = new CDBTableCellNumber<double>(this);
			break;
		case BSLib::Database::EDT_STRING:
		case BSLib::Database::EDT_BLOB:
			item = new CDBTableCellVarBin(this);
			break;
		case BSLib::Database::EDT_VARCHAR:
		case BSLib::Database::EDT_BIN:
			item = new CDBTableCellFixBin(this, m_dbTableHead->getSize(i));
			break;
		default:
			item = NULL;
			break;
		}
		if (item == NULL) {
			return false;
		}
		m_tableCells.push_back(item);
	}
	return true;
}

}//Database

}//BSLib

