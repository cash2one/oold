/*#include <GSLib/tracer.h>
#include "DB/tableDataMgr.h"
#include "DB/tableData.h"

namespace GSLib
{

namespace DBSystem
{

namespace DB
{

void CTableRow::close()
{
	std::vector<CTableDataCell*>::iterator it = m_dataList.begin();
	for (; it != m_dataList.end(); ++it) {
		CTableDataCell* item = *it;
		if (item != NULL) {
			BSLIB_SAFE_DELETE(item);
		}
	}
	m_dataList.clear();
}

bool CTableRow::serializeTo(BSLib::Utility::CStream& a_stream) const
{
	if (!_serializeTo(a_stream)) {
		return false;
	}

	std::vector<CTableDataCell*>::const_iterator it = m_dataList.begin();
	for (; it != m_dataList.end(); ++it) {
		CTableDataCell* item = *it;
		if (item != NULL) {
			if (!item->serializeTo(a_stream)) {
				return false;
			}
		}
	}
	return true;
}

bool CTableRow::serializeFrom(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn* a_dbTableColumn)
{
	if (!_serializeFrom(a_stream, a_dbTableColumn)) {
		return false;
	}
	while (!a_dbTableColumn->m_name.empty()) {
		CTableDataCell* item = NULL;
		switch(a_dbTableColumn->m_type)
		{
		case BSLib::Database::EDT_INT8:
			item = new CTableDataCellNumber<BSLib::int8>;
			break;
		case BSLib::Database::EDT_UINT8:
			item = new CTableDataCellNumber<BSLib::uint8>;
			break;
		case BSLib::Database::EDT_INT16:
			item = new CTableDataCellNumber<BSLib::int16>;
			break;
		case BSLib::Database::EDT_UINT16:
			item = new CTableDataCellNumber<BSLib::uint16>;
			break;
		case BSLib::Database::EDT_INT32:
			item = new CTableDataCellNumber<BSLib::int32>;
			break;
		case BSLib::Database::EDT_UINT32:
			item = new CTableDataCellNumber<BSLib::uint32>;
			break;
		case BSLib::Database::EDT_INT64:
			item = new CTableDataCellNumber<BSLib::int64>;
			break;
		case BSLib::Database::EDT_UINT64:
			item = new CTableDataCellNumber<BSLib::uint64>;
			break;
		case BSLib::Database::EDT_FLOAT:
			item = new CTableDataCellNumber<float>;
			break;
		case BSLib::Database::EDT_DOUBLE:
			item = new CTableDataCellNumber<double>;
			break;
		case BSLib::Database::EDT_STRING:
		case BSLib::Database::EDT_BLOB:
			item = new CTableDataCellVarBin;
			break;
		case BSLib::Database::EDT_VARCHAR:
		case BSLib::Database::EDT_BIN:
			item = new CTableDataCellFixBin(a_dbTableColumn->m_size);
			break;
		default:
			item = NULL;
			break;
		}
		if (item == NULL) {
			return false;
		}
		if (!item->serializeFrom(a_stream)){
			return false;
		}
		++a_dbTableColumn;
		m_dataList.push_back(item);
	}
	return true;
}

bool CTableRow::updateTableRowData(BSLib::int32 a_tableColumnIndex, BSLib::Utility::CStream& a_stream)
{
	if (a_tableColumnIndex == -1) {
		try {
			_updateTableRowData(a_tableColumnIndex, a_stream);
		} catch (...) {
			return false;
		} 
		for (BSLib::uint32 i=0; i<m_dataList.size(); ++i) {
			CTableDataCell* cell = m_dataList[i];
			if (cell == NULL) {
				continue;
			}
			if (!cell->serializeFrom(a_stream)) {
				return false;
			}
		}
		return true;
	}
	try {
		if (_updateTableRowData(a_tableColumnIndex, a_stream)) {
			return true;
		}
	} catch (...) {
		return false;
	} 
	if ((BSLib::uint32)a_tableColumnIndex >= m_dataList.size()) {
		return false;
	}
	CTableDataCell* cell = m_dataList[a_tableColumnIndex];
	if (cell == NULL) {
		return false;
	}
	return cell->serializeFrom(a_stream);
}

//////////////////////////////////////////////////////////////////////////

CTableData::CTableData(EDBTableID a_tableID)
: m_tableID(a_tableID)
{
	;
}

CTableData::~CTableData()
{
	;
}

bool CTableData::loadDataFromDB(GFLib::AccountID a_accountID, GFLib::ZoneID a_zoneID)
{
	BSLib::Utility::CStringA sqlWhere;
	sqlWhere.format("AccountID=\'%lld\' AND ZoneID=\'%d\'", a_accountID, a_zoneID);
	return CTableData::_loadDataFromDB(sqlWhere);
}

bool CTableData::getModuleType(EModuleType& a_moduleType) const
{
	STableDataInfor* tableDataInfor = CTableDataMgr::singleton().getTableDataInfor(m_tableID);
	if (tableDataInfor != NULL) {
		a_moduleType = tableDataInfor->m_moduleType;
		return true;
	}
	return false;
}

bool CTableData::_loadDataFromDB(const std::string& a_tableWhere)
{
	close();

	STableDataInfor* tableDataInfor = CTableDataMgr::singleton().getTableDataInfor(m_tableID);
	if (tableDataInfor == NULL) {
		return false;
	}
	const BSLib::Database::SDbColumn* dbTableColumn = tableDataInfor->m_dbTableColumn;
	if (dbTableColumn == NULL) {
		return false;
	}
	BSLib::Utility::CStream stream;
	if (!CTableDataMgr::singleton().selectLocalTableData(a_tableWhere, m_tableID, stream)) {
		return false;
	}
	return _initTableRow(stream, dbTableColumn);
}

//////////////////////////////////////////////////////////////////////////

bool CRoleTableRow::_serializeTo(BSLib::Utility::CStream& a_stream) const
{
	a_stream << m_accountID;
	a_stream << m_zoneID;
	a_stream << m_roleIndex;
	return true;
}

bool CRoleTableRow::_serializeFrom(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn*& a_dbTableColumn)
{
	try {
		if (a_dbTableColumn->m_name.empty()) {
			return false;
		}
		a_stream >> m_accountID;
		++a_dbTableColumn;

		if (a_dbTableColumn->m_name.empty()) {
			return false;
		}
		a_stream >> m_zoneID;
		++a_dbTableColumn;

		if (a_dbTableColumn->m_name.empty()) {
			return false;
		}
		a_stream >> m_roleIndex;
		++a_dbTableColumn;
	} catch (...) {
		return false;
	}
	return true;
}

bool CRoleTableRow::_updateTableRowData(BSLib::int32& a_tableColumnIndex, BSLib::Utility::CStream& a_stream)
{
	if (a_tableColumnIndex == -1) {
		a_stream >> m_accountID;
		a_stream >> m_zoneID;
		a_stream >> m_roleIndex;
		return true;
	}
	if (a_tableColumnIndex == 0) {
		a_stream >> m_accountID;
		return true;
	} else if (a_tableColumnIndex == 1){
		a_stream >> m_zoneID;
		return true;
	} else if (a_tableColumnIndex == 2){
		a_stream >> m_roleIndex;
		return true;
	} else if (a_tableColumnIndex >= 3) {
		a_tableColumnIndex -= 3;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
CRoleTableData::CRoleTableData(EDBTableID a_tableID)
: CTableData(a_tableID)
{
	;
}

CRoleTableData::~CRoleTableData()
{
	close();
}

void CRoleTableData::close()
{
	BSLib::Utility::CHashMap<GSLib::RoleIndex, CRoleTableRow*>::iterator it = m_roleTableRowHashMap.begin();
	for (; it != m_roleTableRowHashMap.end(); ++it) {
		CRoleTableRow* row = it->second;
		if (row != NULL) {
			BSLIB_SAFE_DELETE(row);
		}
	}
	m_roleTableRowHashMap.clear();
}

bool CRoleTableData::serializeTo(GSLib::RoleIndex a_roleIndex, BSLib::Utility::CStream& a_stream) const
{
	if (a_roleIndex == INVALID_ROLEINDEX) {
		BSLib::Utility::CHashMap<GSLib::RoleIndex, CRoleTableRow*>::const_iterator it = m_roleTableRowHashMap.begin();
		for (; it != m_roleTableRowHashMap.end(); ++it) {
			CRoleTableRow* row = it->second;
			if (row != NULL){
				if (!row->serializeTo(a_stream)){
					return false;
				}
			}
		}
		return true;
	} else {
		CRoleTableRow* row = NULL;
		m_roleTableRowHashMap.getValue(a_roleIndex, row);
		if (row != NULL) {
			if (!row->serializeTo(a_stream)){
				return false;
			}
		}
	}
	return true;
}

bool CRoleTableData::serializeFrom(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn* a_dbTableColumn)
{
	BSLib::Utility::CHashMap<GSLib::RoleIndex, CRoleTableRow*>::iterator it = m_roleTableRowHashMap.begin();
	for (; it != m_roleTableRowHashMap.end(); ++it) {
		CRoleTableRow* row = it->second;
		if (row != NULL) {
			if (!row->serializeFrom(a_stream, a_dbTableColumn)){
				return false;
			}
		}
	}
	return true;
}

bool CRoleTableData::updateTableData(GSLib::RoleIndex a_roleIndex, BSLib::int32 a_tableColumnIndex, BSLib::Utility::CStream& a_stream)
{
	STableDataInfor* tableDataInfor = CTableDataMgr::singleton().getTableDataInfor(getTableID());
	if (tableDataInfor == NULL) {
		return false;
	}
	const BSLib::Database::SDbColumn* dbTableColumn = tableDataInfor->m_dbTableColumn;
	if (dbTableColumn == NULL) {
		return false;
	}
	
	CRoleTableRow* roleRow = NULL;
	m_roleTableRowHashMap.getValue(a_roleIndex, roleRow);
	if (roleRow != NULL) {
		return roleRow->updateTableRowData(a_tableColumnIndex, a_stream);
	}
	if (a_tableColumnIndex != -1) {
		return false;
	}
	roleRow = new CRoleTableRow;
	if (roleRow == NULL) {
		return false;
	}
	if (!roleRow->serializeFrom(a_stream, dbTableColumn)) {
		BSLIB_SAFE_DELETE(roleRow);
		return false;
	}
	if (a_roleIndex != roleRow->getRoleIndex()) {
		BSLIB_SAFE_DELETE(roleRow);
		return false;
	}
	m_roleTableRowHashMap.setValue(roleRow->getRoleIndex(), roleRow);
	return true;
}

bool CRoleTableData::saveTableData(GSLib::RoleIndex a_roleIndex) const
{
	BSLib::Utility::CStream stream;

	if (a_roleIndex == INVALID_ROLEINDEX) {
		BSLib::Utility::CHashMap<GSLib::RoleIndex, CRoleTableRow*>::const_iterator it = m_roleTableRowHashMap.begin();
		for (; it != m_roleTableRowHashMap.end(); ++it) {
			CRoleTableRow* tableRow = it->second;
			if (tableRow == NULL) {
				continue;
			}
			stream.reset();
			if (!tableRow->serializeTo(stream)) {
				BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "序列化数据失败[AccountID=%lld][ZoneID=%d][RoleIndex=%d]TableID=%d]",
					tableRow->getAccountID(),
					tableRow->getZoneID(),
					tableRow->getRoleIndex(),
					getTableID());
				continue;
			}
			if (!CTableDataMgr::singleton().updateLocalTableData(getTableID(), stream)) {
				BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "保存数据失败[AccountID=%lld][ZoneID=%d][RoleIndex=%d]TableID=%d]",
					tableRow->getAccountID(),
					tableRow->getZoneID(),
					tableRow->getRoleIndex(),
					getTableID());
			}
		}
		return true;
	}
	CRoleTableRow* tableRow = NULL;
	m_roleTableRowHashMap.getValue(a_roleIndex, tableRow);
	if (tableRow == NULL) {
		return false;
	}
	stream.reset();
	if (!tableRow->serializeTo(stream)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "序列化数据失败[AccountID=%lld][ZoneID=%d][RoleIndex=%d]TableID=%d]",
			tableRow->getAccountID(),
			tableRow->getZoneID(),
			tableRow->getRoleIndex(),
			getTableID());
		return false;
	}
	if (!CTableDataMgr::singleton().updateLocalTableData(getTableID(), stream)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "保存数据失败[AccountID=%lld][ZoneID=%d][RoleIndex=%d]TableID=%d]",
			tableRow->getAccountID(),
			tableRow->getZoneID(),
			tableRow->getRoleIndex(),
			getTableID());
		return false;
	}
	return true;
}

bool CRoleTableData::_initTableRow(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn* a_dbTableColumn)
{
	close();

	while (a_stream.readSize() > 0) {
		CRoleTableRow* row = new CRoleTableRow;
		if (row == NULL) {
			return false;
		}
		if (!row->serializeFrom(a_stream, a_dbTableColumn)) {
			BSLIB_SAFE_DELETE(row);
			continue;
		}
		if (m_roleTableRowHashMap.find(row->getRoleIndex()) != m_roleTableRowHashMap.end()) {
			BSLIB_SAFE_DELETE(row);
			continue;
		}
		m_roleTableRowHashMap.setValue(row->getRoleIndex(), row);
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////

bool CPlayerTableRow::_serializeTo(BSLib::Utility::CStream& a_stream) const
{
	a_stream << m_accountID;
	a_stream << m_zoneID;
	return true;
}

bool CPlayerTableRow::_serializeFrom(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn*& a_dbTableColumn)
{
	try {
		if (a_dbTableColumn->m_name.empty()) {
			return false;
		}
		a_stream >> m_accountID;
		++a_dbTableColumn;

		if (a_dbTableColumn->m_name.empty()) {
			return false;
		}
		a_stream >> m_zoneID;
		++a_dbTableColumn;
	} catch (...) {
		return false;
	}
	return true;
}

bool CPlayerTableRow::_updateTableRowData(BSLib::int32& a_tableColumnIndex, BSLib::Utility::CStream& a_stream)
{
	if (a_tableColumnIndex == -1) {
		a_stream >> m_accountID;
		a_stream >> m_zoneID;
		return true;
	}
	if (a_tableColumnIndex == 0) {
		a_stream >> m_accountID;
		return true;
	} else if (a_tableColumnIndex == 1){
		a_stream >> m_zoneID;
		return true;
	} else if (a_tableColumnIndex >= 2) {
		a_tableColumnIndex -= 2;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////

CPlayerTableData::CPlayerTableData(EDBTableID a_tableID)
: CTableData(a_tableID)
, m_playerTableRow(NULL)
{
	;
}

void CPlayerTableData::close()
{
	if (m_playerTableRow != NULL) {
		m_playerTableRow->close();
		BSLIB_SAFE_DELETE(m_playerTableRow);
	}
}

bool CPlayerTableData::serializeTo(GSLib::RoleIndex a_roleIndex, BSLib::Utility::CStream& a_stream) const
{
	if (m_playerTableRow == NULL) {
		return false;
	}
	return m_playerTableRow->serializeTo(a_stream);
}

bool CPlayerTableData::serializeFrom(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn* a_dbTableColumn)
{
	if (m_playerTableRow == NULL) {
		return false;
	}
	return serializeFrom(a_stream, a_dbTableColumn);
}

bool CPlayerTableData::updateTableData(GSLib::RoleIndex a_roleIndex, BSLib::int32 a_tableColumnIndex, BSLib::Utility::CStream& a_stream)
{
	STableDataInfor* tableDataInfor = CTableDataMgr::singleton().getTableDataInfor(getTableID());
	if (tableDataInfor == NULL) {
		return false;
	}
	const BSLib::Database::SDbColumn* dbTableColumn = tableDataInfor->m_dbTableColumn;
	if (dbTableColumn == NULL) {
		return false;
	}
	if (m_playerTableRow != NULL) {
		return m_playerTableRow->updateTableRowData(a_tableColumnIndex, a_stream);
	}
	if (a_tableColumnIndex != -1) {
		return false;
	}
	m_playerTableRow = new CPlayerTableRow();
	if (m_playerTableRow == NULL) {
		return false;
	}
	if (!m_playerTableRow->serializeFrom(a_stream, dbTableColumn)) {
		BSLIB_SAFE_DELETE(m_playerTableRow);
		return false;
	}
	return true;
}

bool CPlayerTableData::saveTableData(GSLib::RoleIndex a_roleIndex) const
{
	if (m_playerTableRow == NULL) {
		return false;
	}
	BSLib::Utility::CStream stream;
	if (!m_playerTableRow->serializeTo(stream)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "序列化数据失败[AccountID=%lld][ZoneID=%d]TableID=%d]",
			m_playerTableRow->getAccountID(),
			m_playerTableRow->getZoneID(),
			getTableID());
		return false;
	}
	if (!CTableDataMgr::singleton().updateLocalTableData(getTableID(), stream)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "保存数据失败[AccountID=%lld][ZoneID=%d]TableID=%d]",
			m_playerTableRow->getAccountID(),
			m_playerTableRow->getZoneID(),
			getTableID());
		return false;
	}
	return true;
}

bool CPlayerTableData::_initTableRow(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn* a_dbTableColumn)
{
	close();
	m_playerTableRow = new CPlayerTableRow();
	if (m_playerTableRow == NULL) {
		return false;
	}
	if (!m_playerTableRow->serializeFrom(a_stream, a_dbTableColumn)) {
		BSLIB_SAFE_DELETE(m_playerTableRow);
	}
	return true;
}

}//DB

}//PlayerSystem

}//GSLib
*/
