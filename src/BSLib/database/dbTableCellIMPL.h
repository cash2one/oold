#ifndef __BSLIB_DATEBSLIB_DBTABLECELLIMPL__
#define __BSLIB_DATEBSLIB_DBTABLECELLIMPL__

#include <BSLib/utility/tracer.h>
#include <BSLib/database/dbTableCell.h>
#include <BSLib/database/dbTableRow.h>

namespace BSLib
{

namespace Database
{

template<class TYPE>
class CDBTableCellNumber : public CDBTableCell
{
public:
	CDBTableCellNumber(CDBTableRow* a_dbTableRow) : CDBTableCell(a_dbTableRow), m_cellValue(0) {}
	virtual ~CDBTableCellNumber(){}

	//导入导出数据接口
	virtual bool serializeTo(BSLib::Utility::CStream& a_stream) const
	{ 
		a_stream << m_cellValue;
		return true;
	}

	virtual bool serializeFrom(BSLib::Utility::CStream& a_stream)
	{ 
		try {
			a_stream >> m_cellValue;
			return true;
		} catch (...) {
			BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "序列化数据失败");
			return false;
		} 
	} 

	//读取数据
	virtual BSLib::int8 getInt8Value() const { return (BSLib::int8)m_cellValue; }
	virtual BSLib::int16 getInt16Value() const { return (BSLib::int16)m_cellValue; }
	virtual BSLib::int32 getInt32Value() const { return (BSLib::int32)m_cellValue; }
	virtual BSLib::int64 getInt64Value() const { return (BSLib::int64)m_cellValue; }

	virtual BSLib::uint8 getUInt8Value() const { return (BSLib::uint8)m_cellValue; }
	virtual BSLib::uint16 getUInt16Value() const { return (BSLib::uint16)m_cellValue; }
	virtual BSLib::uint32 getUInt32Value() const { return (BSLib::uint32)m_cellValue; }
	virtual BSLib::uint64 getUInt64Value() const { return (BSLib::uint64)m_cellValue; }

	virtual float getFloatValue() const { return (float)m_cellValue; }
	virtual double getDoubleValue() const { return (double)m_cellValue; }

	//virtual std::string getStrValue() { throw std::exception("null", 0); }
	//virtual std::string getVarValue() { throw std::exception("null", 0); }

	//virtual void* getBlobValue() const { throw std::exception("null", 0); }
	//virtual void* getBinValue() const { throw std::exception("null", 0); }

	//设置数据
	virtual void setInt8Value(BSLib::int8 a_value)  
	{
		m_cellValue = (TYPE)a_value; 

		CDBTableRow* dbTableRow = CDBTableCell::_getTableRow();
		if (dbTableRow != NULL) {
			dbTableRow->setRowState(EDBTBLRWST_UPDATE);
		}
	}

	virtual void setInt16Value(BSLib::int16 a_value)  
	{
		m_cellValue = (TYPE)a_value; 

		CDBTableRow* dbTableRow = CDBTableCell::_getTableRow();
		if (dbTableRow != NULL) {
			dbTableRow->setRowState(EDBTBLRWST_UPDATE);
		}
	}

	virtual void setInt32Value(BSLib::int32 a_value)
	{
		m_cellValue = (TYPE)a_value; 

		CDBTableRow* dbTableRow = CDBTableCell::_getTableRow();
		if (dbTableRow != NULL) {
			dbTableRow->setRowState(EDBTBLRWST_UPDATE);
		}
	}

	virtual void setInt64Value(BSLib::int64 a_value)
	{
		m_cellValue = (TYPE)a_value; 

		CDBTableRow* dbTableRow = CDBTableCell::_getTableRow();
		if (dbTableRow != NULL) {
			dbTableRow->setRowState(EDBTBLRWST_UPDATE);
		}
	}

	virtual void setUInt8Value(BSLib::uint8 a_value)
	{
		m_cellValue = (TYPE)a_value; 

		CDBTableRow* dbTableRow = CDBTableCell::_getTableRow();
		if (dbTableRow != NULL) {
			dbTableRow->setRowState(EDBTBLRWST_UPDATE);
		}
	}

	virtual void setUInt16Value(BSLib::uint16 a_value)
	{
		m_cellValue = (TYPE)a_value; 

		CDBTableRow* dbTableRow = CDBTableCell::_getTableRow();
		if (dbTableRow != NULL) {
			dbTableRow->setRowState(EDBTBLRWST_UPDATE);
		}
	}

	virtual void setUInt32Value(BSLib::uint32 a_value)
	{
		m_cellValue = (TYPE)a_value; 

		CDBTableRow* dbTableRow = CDBTableCell::_getTableRow();
		if (dbTableRow != NULL) {
			dbTableRow->setRowState(EDBTBLRWST_UPDATE);
		}
	}

	virtual void setUInt64Value(BSLib::uint64 a_value)
	{
		m_cellValue = (TYPE)a_value; 

		CDBTableRow* dbTableRow = CDBTableCell::_getTableRow();
		if (dbTableRow != NULL) {
			dbTableRow->setRowState(EDBTBLRWST_UPDATE);
		}
	}

	virtual void setFloatValue(float a_value) 
	{
		m_cellValue = (TYPE)a_value; 

		CDBTableRow* dbTableRow = CDBTableCell::_getTableRow();
		if (dbTableRow != NULL) {
			dbTableRow->setRowState(EDBTBLRWST_UPDATE);
		}
	}

	virtual void setDoubleValue(double a_value)
	{
		m_cellValue = (TYPE)a_value; 

		CDBTableRow* dbTableRow = CDBTableCell::_getTableRow();
		if (dbTableRow != NULL) {
			dbTableRow->setRowState(EDBTBLRWST_UPDATE);
		}
	}

	//virtual void setStringValue(const std::string& a_value) { throw std::exception("null", 0); }
	//virtual void setVarcharValue(const std::string& a_value) { throw std::exception("null", 0); }

	//virtual void setBlobValue(void* a_value, BSLib::uint32 a_valueSize) { throw std::exception("null", 0); }
	//virtual void setBinValue(void* a_value, BSLib::uint32 a_valueSize) { throw std::exception("null", 0); }

	virtual BSLib::uint32 getValueSize() const { return sizeof(TYPE); }

private:
	TYPE m_cellValue;
};

class CDBTableCellFixBin : public CDBTableCell
{
public:
	CDBTableCellFixBin(CDBTableRow* a_dbTableRow, BSLib::uint32 a_size);
	virtual ~CDBTableCellFixBin();

	//导入导出数据接口
	virtual bool serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool serializeFrom(BSLib::Utility::CStream& stream);

	//读取数据
// 	virtual BSLib::int8 getInt8Value() const { throw std::exception("null", 0); }
// 	virtual BSLib::int16 getInt16Value() const { throw std::exception("null", 0); }
// 	virtual BSLib::int32 getInt32Value() const { throw std::exception("null", 0); }
// 	virtual BSLib::int64 getInt64Value() const { throw std::exception("null", 0); }
// 
// 	virtual BSLib::uint8 getUInt8Value() const { throw std::exception("null", 0); }
// 	virtual BSLib::uint16 getUInt16Value() const { throw std::exception("null", 0); }
// 	virtual BSLib::uint32 getUInt32Value() const { throw std::exception("null", 0); }
// 	virtual BSLib::uint64 getUInt64Value() const { throw std::exception("null", 0); }
// 
// 	virtual float getFloatValue() { throw std::exception("null", 0); }
// 	virtual double getDoubleValue() { throw std::exception("null", 0); }

	virtual std::string getStrValue() const { return (char*)&m_buffer[0]; }
	virtual std::string getVarValue() const { return (char*)&m_buffer[0]; }

	virtual void* getBlobValue() const { return (char*)&m_buffer[0];; }
	virtual void* getBinValue() const { return (char*)&m_buffer[0]; }

	//设置数据
// 	virtual void setInt8Value(BSLib::int8 a_value) const { throw std::exception("null", 0); }
// 	virtual void setInt16Value(BSLib::int16 a_value) const { throw std::exception("null", 0); }
// 	virtual void setInt32Value(BSLib::int32 a_value) const { throw std::exception("null", 0); }
// 	virtual void setInt64Value(BSLib::int64 a_value) const { throw std::exception("null", 0); }
// 
// 	virtual void setUInt8Value(BSLib::uint8 a_value) const { throw std::exception("null", 0); }
// 	virtual void setUInt16Value(BSLib::uint16 a_value) const { throw std::exception("null", 0); }
// 	virtual void setUInt32Value(BSLib::uint32 a_value) const { throw std::exception("null", 0); }
// 	virtual void setUInt64Value(BSLib::uint64 a_value) const { throw std::exception("null", 0); }
// 
// 	virtual void setFloatValue(float a_value) { throw std::exception("null", 0); }
// 	virtual void setDoubleValue(double a_value) { throw std::exception("null", 0); }

	virtual void setStringValue(const std::string& a_value) {  setVarcharValue(a_value); }
	virtual void setVarcharValue(const std::string& a_value);

	virtual void setBlobValue(void* a_value, BSLib::uint32 a_valueSize) { setBinValue(a_value, a_valueSize); }
	virtual void setBinValue(void* a_value, BSLib::uint32 a_valueSize);

	virtual BSLib::uint32 getValueSize() const { return m_size; }

private:
	BSLib::uint32 m_size;
	std::vector<BSLib::int8> m_buffer;
};

class CDBTableCellVarBin : public CDBTableCell
{
public:
	CDBTableCellVarBin(CDBTableRow* a_dbTableRow);
	virtual ~CDBTableCellVarBin();

	//导入导出数据接口
	virtual bool serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool serializeFrom(BSLib::Utility::CStream& stream);

	//读取数据
	// 	virtual BSLib::int8 getInt8Value() const { throw std::exception("null", 0); }
	// 	virtual BSLib::int16 getInt16Value() const { throw std::exception("null", 0); }
	// 	virtual BSLib::int32 getInt32Value() const { throw std::exception("null", 0); }
	// 	virtual BSLib::int64 getInt64Value() const { throw std::exception("null", 0); }
	// 
	// 	virtual BSLib::uint8 getUInt8Value() const { throw std::exception("null", 0); }
	// 	virtual BSLib::uint16 getUInt16Value() const { throw std::exception("null", 0); }
	// 	virtual BSLib::uint32 getUInt32Value() const { throw std::exception("null", 0); }
	// 	virtual BSLib::uint64 getUInt64Value() const { throw std::exception("null", 0); }
	// 
	// 	virtual float getFloatValue() { throw std::exception("null", 0); }
	// 	virtual double getDoubleValue() { throw std::exception("null", 0); }

	virtual std::string getStrValue() const { return (char*)&m_buffer[0]; }
	virtual std::string getVarValue() const { return (char*)&m_buffer[0]; }

	virtual void* getBlobValue() const { return (char*)&m_buffer[0];; }
	virtual void* getBinValue() const { return (char*)&m_buffer[0]; }

	//设置数据
	// 	virtual void setInt8Value(BSLib::int8 a_value) const { throw std::exception("null", 0); }
	// 	virtual void setInt16Value(BSLib::int16 a_value) const { throw std::exception("null", 0); }
	// 	virtual void setInt32Value(BSLib::int32 a_value) const { throw std::exception("null", 0); }
	// 	virtual void setInt64Value(BSLib::int64 a_value) const { throw std::exception("null", 0); }
	// 
	// 	virtual void setUInt8Value(BSLib::uint8 a_value) const { throw std::exception("null", 0); }
	// 	virtual void setUInt16Value(BSLib::uint16 a_value) const { throw std::exception("null", 0); }
	// 	virtual void setUInt32Value(BSLib::uint32 a_value) const { throw std::exception("null", 0); }
	// 	virtual void setUInt64Value(BSLib::uint64 a_value) const { throw std::exception("null", 0); }
	// 
	// 	virtual void setFloatValue(float a_value) { throw std::exception("null", 0); }
	// 	virtual void setDoubleValue(double a_value) { throw std::exception("null", 0); }

	virtual void setStringValue(const std::string& a_value);
	virtual void setVarcharValue(const std::string& a_value) { setStringValue(a_value); }

	virtual void setBlobValue(void* a_value, BSLib::uint32 a_valueSize);
	virtual void setBinValue(void* a_value, BSLib::uint32 a_valueSize) { setBlobValue(a_value, a_valueSize); }

	virtual BSLib::uint32 getValueSize() const { return m_size; }

private:
	BSLib::uint32 m_size;
	std::vector<BSLib::int8> m_buffer;
};

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_DBTABLECELLIMPL__
