//////////////////////////////////////////////////////////////////////
//	created:	2012/09/04
//	filename:	BSLib\dateBSLib\dbReader.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_DATEBSLIB_DBREADER__
#define __BSLIB_DATEBSLIB_DBREADER__

#include <string>
#include <BSLib/utility/stream.h>
#include <BSLib/utility/pointer.h>
#include <BSLib/database/baseDef.h>

namespace BSLib
{

namespace Database
{

class BSLIB_DATABSLIB_API CDbReader
{
public:
	CDbReader(){}
	virtual ~CDbReader(){}

	virtual uint64 getRowCount() const = 0;
	virtual int getColumnCount() const = 0;

	virtual bool nextRow() = 0;
	virtual void close() = 0;

	virtual BSLib::uint64 getValueSize(int columnIndex) const = 0;
	virtual BSLib::uint64 getValueSize(const std::string& columnLable) const = 0;

	virtual bool getValue(int columnIndex, int8& data) const = 0;
	virtual bool getValue(int columnIndex, uint8& data) const = 0;
	virtual bool getValue(int columnIndex, int16& data) const = 0;
	virtual bool getValue(int columnIndex, uint16& data) const = 0;
	virtual bool getValue(int columnIndex, int32& data) const = 0;
	virtual bool getValue(int columnIndex, uint32& data) const = 0;
	virtual bool getValue(int columnIndex, int64& data) const = 0;
	virtual bool getValue(int columnIndex, uint64& data) const = 0;

	virtual bool getValue(int columnIndex, float& data) const = 0;
	virtual bool getValue(int columnIndex, double& data) const = 0;
	virtual bool getValue(int columnIndex, std::string& data) const = 0;
	virtual bool getValue(int columnIndex, char* data, uint32 dataSize) const = 0;

	virtual bool getValue(int columnIndex, BSLib::Utility::CStream& stream) const = 0;

	virtual bool getValue(const std::string& columnLable, int8& data) const = 0;
	virtual bool getValue(const std::string& columnLable, uint8& data) const = 0;
	virtual bool getValue(const std::string& columnLable, int16& data) const = 0;
	virtual bool getValue(const std::string& columnLable, uint16& data) const = 0;
	virtual bool getValue(const std::string& columnLable, int32& data) const = 0;
	virtual bool getValue(const std::string& columnLable, uint32& data) const = 0;
	virtual bool getValue(const std::string& columnLable, int64& data) const = 0;
	virtual bool getValue(const std::string& columnLable, uint64& data) const = 0;

	virtual bool getValue(const std::string& columnLable, float& data) const = 0;
	virtual bool getValue(const std::string& columnLable, double& data) const = 0;
	virtual bool getValue(const std::string& columnLable, std::string& data) const = 0;
	virtual bool getValue(const std::string& columnLable, char* data, uint32 dataSize) const = 0;

	virtual bool getValue(const std::string& columnLable, BSLib::Utility::CStream& stream) const = 0;
};
typedef BSLib::Utility::CPointer<CDbReader> CDbReaderPtr;

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_DBREADER__


