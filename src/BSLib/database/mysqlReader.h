//////////////////////////////////////////////////////////////////////
//	created:	2012/09/06
//	filename:	src\BSLib\dateBSLib\mysqlReader.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_DATEBSLIB_MYSQLREADER__
#define __BSLIB_DATEBSLIB_MYSQLREADER__

#include <BSLib/utility/hashMap.h>
#include <BSLib/database/dbReader.h>
#include <mysql.h>

namespace BSLib
{

namespace Database
{

class CMysqlReader : public CDbReader
{
public:
	CMysqlReader(MYSQL_RES* mysqlRes);
	virtual ~CMysqlReader();

	virtual uint64 getRowCount() const;
	virtual int getColumnCount() const;

	virtual bool nextRow();
	virtual void close();

	virtual BSLib::uint64 getValueSize(int columnIndex) const;
	virtual BSLib::uint64 getValueSize(const std::string& columnLable) const;

	virtual bool getValue(int columnIndex, int8& data) const;
	virtual bool getValue(int columnIndex, uint8& data) const;
	virtual bool getValue(int columnIndex, int16& data) const;
	virtual bool getValue(int columnIndex, uint16& data) const;
	virtual bool getValue(int columnIndex, int32& data) const;
	virtual bool getValue(int columnIndex, uint32& data) const;
	virtual bool getValue(int columnIndex, int64& data) const;
	virtual bool getValue(int columnIndex, uint64& data) const;

	virtual bool getValue(int columnIndex, float& data) const;
	virtual bool getValue(int columnIndex, double& data) const;
	virtual bool getValue(int columnIndex, std::string& data) const;
	virtual bool getValue(int columnIndex, char* data, uint32 dataSize) const;

	virtual bool getValue(int columnIndex, BSLib::Utility::CStream& stream) const;

	virtual bool getValue(const std::string& columnLable, int8& data) const;
	virtual bool getValue(const std::string& columnLable, uint8& data) const;
	virtual bool getValue(const std::string& columnLable, int16& data) const;
	virtual bool getValue(const std::string& columnLable, uint16& data) const;
	virtual bool getValue(const std::string& columnLable, int32& data) const;
	virtual bool getValue(const std::string& columnLable, uint32& data) const;
	virtual bool getValue(const std::string& columnLable, int64& data) const;
	virtual bool getValue(const std::string& columnLable, uint64& data) const;

	virtual bool getValue(const std::string& columnLable, float& data) const;
	virtual bool getValue(const std::string& columnLable, double& data) const;
	virtual bool getValue(const std::string& columnLable, std::string& data) const;
	virtual bool getValue(const std::string& columnLable, char* data, uint32 dataSize) const;

	virtual bool getValue(const std::string& columnLable, BSLib::Utility::CStream& stream) const;

private:
	MYSQL_RES* m_mysqlRes;
	MYSQL_ROW m_currentRow;
	unsigned long* m_lengths;
	BSLib::Utility::CHashMap<const char*, int> m_lableHashMap;
};
typedef BSLib::Utility::CPointer<CDbReader> CDbReaderPtr;

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_MYSQLREADER__

