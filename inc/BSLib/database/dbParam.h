//////////////////////////////////////////////////////////////////////
//	created:	2012/09/04
//	filename:	BSLib\dateBSLib\dbParam.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_DATEBSLIB_DBPARAM__
#define __BSLIB_DATEBSLIB_DBPARAM__

#include <string>
#include <BSLib/database/baseDef.h>

namespace BSLib
{

namespace Database
{

enum EDbParamType
{
	EDT_NULL = 0,
	EDT_INT8,
	EDT_UINT8,
	EDT_INT16,
	EDT_UINT16,
	EDT_INT32,
	EDT_UINT32,
	EDT_INT64,
	EDT_UINT64,
	EDT_FLOAT,
	EDT_DOUBLE,
	EDT_STRING,	//变长字符串
	EDT_VARCHAR,//固定长字符串
	EDT_BLOB,	//变长二进制
	EDT_BIN,	//固定长二进制
};

enum EDbParamFlag
{
	EDF_NULL = 0,
	EDF_KEY = 1,
	EDF_INDEX = 2,

	EDF_INCREMENT = 8,
};

struct SDbColumn
{
	std::string m_name;
	EDbParamType m_type;
	BSLib::uint32 m_size;
	EDbParamFlag m_flag;
};

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_DBPARAM__

