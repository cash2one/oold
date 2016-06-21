#ifndef __BSLIB_DATEBSLIB_DBTABLECELL__
#define __BSLIB_DATEBSLIB_DBTABLECELL__

#include <BSLib/utility/exception.h>
#include <BSLib/database/dbReader.h>


namespace BSLib
{

namespace Database
{

class CDBTableRow;

class CDBTableCell
{
public:
	CDBTableCell(CDBTableRow* a_dbTableRow) : m_dbTableRow (a_dbTableRow){}
	virtual ~CDBTableCell() {}

	//导入导出数据接口
	virtual bool serializeTo(BSLib::Utility::CStream& stream) const { throw BSLib::Utility::CException("null"); }
	virtual bool serializeFrom(BSLib::Utility::CStream& stream) { throw BSLib::Utility::CException("null"); } 

	//读取数据
	virtual BSLib::int8 getInt8Value() const { throw BSLib::Utility::CException("null"); }
	virtual BSLib::int16 getInt16Value() const { throw BSLib::Utility::CException("null"); }
	virtual BSLib::int32 getInt32Value() const { throw BSLib::Utility::CException("null"); }
	virtual BSLib::int64 getInt64Value() const { throw BSLib::Utility::CException("null"); }

	virtual BSLib::uint8 getUInt8Value() const { throw BSLib::Utility::CException("null"); }
	virtual BSLib::uint16 getUInt16Value() const { throw BSLib::Utility::CException("null"); }
	virtual BSLib::uint32 getUInt32Value() const { throw BSLib::Utility::CException("null"); }
	virtual BSLib::uint64 getUInt64Value() const { throw BSLib::Utility::CException("null"); }

	virtual float getFloatValue() const { throw BSLib::Utility::CException("null"); }
	virtual double getDoubleValue() const { throw BSLib::Utility::CException("null"); }

	virtual std::string getStrValue() const { throw BSLib::Utility::CException("null"); }
	virtual std::string getVarValue() const { throw BSLib::Utility::CException("null"); }

	virtual void* getBlobValue() const { throw BSLib::Utility::CException("null"); }
	virtual void* getBinValue() const { throw BSLib::Utility::CException("null"); }

	//设置数据
	virtual void setInt8Value(BSLib::int8 a_value) { throw BSLib::Utility::CException("null"); }
	virtual void setInt16Value(BSLib::int16 a_value) { throw BSLib::Utility::CException("null"); }
	virtual void setInt32Value(BSLib::int32 a_value) { throw BSLib::Utility::CException("null"); }
	virtual void setInt64Value(BSLib::int64 a_value) { throw BSLib::Utility::CException("null"); }

	virtual void setUInt8Value(BSLib::uint8 a_value) { throw BSLib::Utility::CException("null"); }
	virtual void setUInt16Value(BSLib::uint16 a_value) { throw BSLib::Utility::CException("null"); }
	virtual void setUInt32Value(BSLib::uint32 a_value) { throw BSLib::Utility::CException("null"); }
	virtual void setUInt64Value(BSLib::uint64 a_value) { throw BSLib::Utility::CException("null"); }

	virtual void setFloatValue(float a_value) { throw BSLib::Utility::CException("null"); }
	virtual void setDoubleValue(double a_value) { throw BSLib::Utility::CException("null"); }

	virtual void setStringValue(const std::string& a_value) { throw BSLib::Utility::CException("null"); }
	virtual void setVarcharValue(const std::string& a_value) { throw BSLib::Utility::CException("null"); }

	virtual void setBlobValue(void* a_value, BSLib::uint32 a_valueSize) { throw BSLib::Utility::CException("null"); }
	virtual void setBinValue(void* a_value, BSLib::uint32 a_valueSize) { throw BSLib::Utility::CException("null"); }

	virtual BSLib::uint32 getValueSize() const { throw BSLib::Utility::CException("null"); }

protected:
	CDBTableRow* _getTableRow() { return m_dbTableRow; }

private:
	CDBTableRow* m_dbTableRow;
};

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_DBTABLECELL__
