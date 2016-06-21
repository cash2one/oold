/*#ifndef __GSLIB_DBSYSTEM_DB_TABLEDATA_H__
#define __GSLIB_DBSYSTEM_DB_TABLEDATA_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/dbTableID.h>

namespace GSLib
{

namespace DBSystem
{

namespace DB
{

class CTableDataCell
{
public:
	virtual bool serializeTo(BSLib::Utility::CStream& stream) const = 0;
	virtual bool serializeFrom(BSLib::Utility::CStream& stream) = 0;
	virtual void* getValue() const = 0;
	virtual BSLib::uint32 getValueSize() const = 0;
};

template<class T>
class CTableDataCellNumber : public CTableDataCell
{
public:
	CTableDataCellNumber() : m_data(0) {}

	virtual bool serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_data;
		return true;
	}

	virtual bool serializeFrom(BSLib::Utility::CStream& stream)
	{
		try {
			stream >> m_data;
			return true;
		} catch (...) {
			return false;
		} 
	}

	virtual void* getValue() const
	{
		return (char*)&m_data;
	}

	virtual BSLib::uint32 getValueSize() const
	{
		return sizeof(m_data);
	}
	
private:
	T m_data;
};

class CTableDataCellVarBin : public CTableDataCell
{
public:
	CTableDataCellVarBin() : m_size(0)
	{
		m_buffer.resize(4);
	}
	virtual bool serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_size;
		if (m_size <= 0) {
			return true;
		}
		stream.write(&m_buffer[0], m_size);
		return true;
	}

	virtual bool serializeFrom(BSLib::Utility::CStream& stream)
	{
		try {
			BSLib::uint32 size;
			stream >> size;
			if (size > m_size) {
				if (m_buffer.size() < size) {
					m_buffer.resize(size, 0);
				}
				stream.read(&m_buffer[0], size);
				m_size = size;
			} else {
				if (size > 0) {
					if (m_buffer.size() < size) {
						m_buffer.resize(size, 0);
					}
					stream.read(&m_buffer[0], size);
				}
				m_size = size;
			}
			return true;
		} catch (...) {
			return false;
		} 
	}

	virtual void* getValue() const
	{
		if (m_buffer.size() == NULL) {
			return NULL;
		}
		return (char*)&m_buffer[0];
	}

	virtual BSLib::uint32 getValueSize() const
	{
		return m_buffer.size();
	}

private:
	BSLib::uint32 m_size;
	std::vector<BSLib::int8> m_buffer;
};

class CTableDataCellFixBin : public CTableDataCell
{
public:
	CTableDataCellFixBin(BSLib::uint32 a_size)
		: m_size(a_size)
	{
		m_buffer.resize(a_size, 0);
	}
	virtual bool serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream.write(&m_buffer[0], m_size);
		return true;
	}

	virtual bool serializeFrom(BSLib::Utility::CStream& stream)
	{
		try {
			stream.read(&m_buffer[0], m_size);
			return true;
		} catch (...) {
			return false;
		} 
	}

	virtual void* getValue() const
	{
		return (char*)&m_buffer[0];
	}

	virtual BSLib::uint32 getValueSize() const
	{
		return m_size;
	}

private:
	BSLib::uint32 m_size;
	std::vector<BSLib::int8> m_buffer;
};


class CTableRow
{
public:
	void close();

	virtual bool serializeTo(BSLib::Utility::CStream& a_stream) const;
	virtual bool serializeFrom(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn* a_dbTableColumn);
	virtual bool updateTableRowData(BSLib::int32 a_tableColumnIndex, BSLib::Utility::CStream& a_stream);

private:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const = 0;
	virtual bool _serializeFrom(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn*& a_dbTableColumn) = 0;
	virtual bool _updateTableRowData(BSLib::int32& a_tableColumnIndex, BSLib::Utility::CStream& a_stream) = 0;

	std::vector<CTableDataCell*> m_dataList;
};

class CTableData
{
public:
	CTableData(EDBTableID a_tableID);
	virtual ~CTableData();

	virtual void close() = 0;
	virtual bool serializeTo(GSLib::RoleIndex a_roleIndex, BSLib::Utility::CStream& a_stream) const = 0;
	virtual bool serializeFrom(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn* a_dbTableColumn) = 0;
	virtual bool updateTableData(GSLib::RoleIndex a_roleIndex, BSLib::int32 a_tableColumnIndex, BSLib::Utility::CStream& a_stream) = 0;
	virtual bool saveTableData(GSLib::RoleIndex a_roleIndex) const = 0;

	bool updateTableData(GSLib::RoleIndex a_roleIndex, BSLib::Utility::CStream& a_stream)
	{
		return updateTableData(a_roleIndex, -1, a_stream);
	}

	EDBTableID getTableID() const { return m_tableID; }
	bool getModuleType(EModuleType& a_moduleType) const;

	bool loadDataFromDB(GFLib::AccountID a_accountID, GFLib::ZoneID a_zoneID);

protected:
	bool _loadDataFromDB(const std::string& a_tableWhere);

private:
	virtual bool _initTableRow(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn* a_dbTableColumn) = 0;

private:
	EDBTableID m_tableID;
};

//////////////////////////////////////////////////////////////////////////

class CRoleTableRow : public CTableRow
{
public:
	CRoleTableRow() : m_accountID(0), m_zoneID(0), m_roleIndex(INVALID_ROLEINDEX) {}
	GFLib::AccountID getAccountID() { return m_accountID; }
	GFLib::ZoneID getZoneID() { return m_zoneID; }
	GSLib::RoleIndex getRoleIndex() { return m_roleIndex; }

private:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn*& a_dbTableColumn);
	virtual bool _updateTableRowData(BSLib::int32& a_tableColumnIndex, BSLib::Utility::CStream& a_stream);

private:
	GFLib::AccountID m_accountID;
	GFLib::ZoneID m_zoneID;
	GSLib::RoleIndex m_roleIndex;
};

class CRoleTableData : public CTableData
{
public:
	CRoleTableData(EDBTableID a_tableID);
	virtual ~CRoleTableData();

	virtual void close();
	virtual bool serializeTo(GSLib::RoleIndex a_roleIndex, BSLib::Utility::CStream& a_stream) const;
	virtual bool serializeFrom(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn* a_dbTableColumn);
	virtual bool updateTableData(GSLib::RoleIndex a_roleIndex, BSLib::int32 a_tableColumnIndex, BSLib::Utility::CStream& a_stream);
	virtual bool saveTableData(GSLib::RoleIndex a_roleIndex) const;

	const BSLib::Utility::CHashMap<GSLib::RoleIndex, CRoleTableRow*>& getRoleTableRows() { return m_roleTableRowHashMap; }

private:
	bool _initTableRow(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn* a_dbTableColumn);

	BSLib::Utility::CHashMap<GSLib::RoleIndex, CRoleTableRow*> m_roleTableRowHashMap;
};

//////////////////////////////////////////////////////////////////////////

class CPlayerTableRow : public CTableRow
{
public:
	CPlayerTableRow() : m_accountID(0), m_zoneID(0) {}

	GFLib::AccountID getAccountID() { return m_accountID; }
	GFLib::ZoneID getZoneID() { return m_zoneID; }

private:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn*& a_dbTableColumn);
	virtual bool _updateTableRowData(BSLib::int32& a_tableColumnIndex, BSLib::Utility::CStream& a_stream);

private:
	GFLib::AccountID m_accountID;
	GFLib::ZoneID m_zoneID;
};

class CPlayerTableData : public CTableData
{
public:
	CPlayerTableData(EDBTableID a_tableID);

	virtual void close();
	virtual bool serializeTo(GSLib::RoleIndex a_roleIndex, BSLib::Utility::CStream& a_stream) const;
	virtual bool serializeFrom(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn* a_dbTableColumn);
	virtual bool updateTableData(GSLib::RoleIndex a_roleIndex, BSLib::int32 a_tableColumnIndex, BSLib::Utility::CStream& a_stream);
	virtual bool saveTableData(GSLib::RoleIndex a_roleIndex) const;

private:
	bool _initTableRow(BSLib::Utility::CStream& a_stream, const BSLib::Database::SDbColumn* a_dbTableColumn);

private:
	CPlayerTableRow* m_playerTableRow;
};

}//DB

}//DBSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_DB_TABLEDATA_H__
*/
