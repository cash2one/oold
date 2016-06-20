//////////////////////////////////////////////////////////////////////
//	created:	2014/10/23
//	filename: 	BSLib\database\dbTableHead.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_DATEBSLIB_DBTABLEHEAD__
#define __BSLIB_DATEBSLIB_DBTABLEHEAD__

#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/stream.h>
#include <BSLib/database/dbParam.h>
#include <BSLib/database/dbConnection.h>

namespace BSLib
{

namespace Database
{

class CDBTableHead
{
public:
	CDBTableHead(const SDbColumn* a_dbColumn);

	std::string getName(BSLib::int32 a_nameNumber);
	BSLib::int32 getNameNumber(const std::string& a_name);
	
	EDbParamType getType(BSLib::int32 a_nameNumber);
	EDbParamType getType(const std::string& a_name);

	BSLib::uint32 getSize(BSLib::int32 a_nameNumber);
	BSLib::uint32 getSize(const std::string& a_name);

	bool isKey(BSLib::int32 a_nameNumber);
	bool isKey(const std::string& a_name);

	bool isIndex(BSLib::int32 a_nameNumber);
	bool isIndex(const std::string& a_name);

	bool isAutoIncrement();
	BSLib::uint32 getAutoIncrementValue();
	BSLib::uint32 addAutoIncrementValue(BSLib::uint32 a_data = 1);
	void setAutoIncrementValue(BSLib::uint32 a_value);

	BSLib::int32 getColumnCount();

	const SDbColumn* getColumnInfor() { return m_dbColumn; }

	bool getAutoIncrement(CDbConnection* a_dbConnection, const std::string& a_tableName);
	bool getKeyStrWhere(CDbConnection* a_dbConnection, const std::string& a_key, BSLib::Utility::CStringA& a_strWhere);
	bool getIndexStrWhere(CDbConnection* a_dbConnection, const std::string& a_index, BSLib::Utility::CStringA& a_strWhere);

private:
	bool _getStrWhere(CDbConnection* a_dbConnection, EDbParamFlag a_paraFlag, BSLib::Utility::CStream& a_stream, BSLib::Utility::CStringA& a_strWhere);

private:
	const SDbColumn* m_dbColumn;
	BSLib::int32 m_columnCount;
	BSLib::Utility::CHashMap<std::string, BSLib::int32> m_namesHashMap;

	bool m_isAutoIncrement;
	BSLib::uint32 m_autoIncrementValue;
};

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_DBTABLEHEAD__
