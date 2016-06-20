//////////////////////////////////////////////////////////////////////
//	created:	2012/09/06
//	filename:	src\BSLib\dateBSLib\connection.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_DATEBSLIB_CONNECTION__
#define __BSLIB_DATEBSLIB_CONNECTION__

#include <BSLib/database/dbReader.h>
#include <BSLib/database/dbParam.h>

namespace BSLib
{

namespace Database
{

enum EDbType
{
	EDBTYPE_ERROR = 0,
	EDBTYPE_MYSQL,
};


struct SUrlInfo
{
public:
	std::string m_user;
	std::string m_password;

	std::string m_host;
	BSLib::uint16 m_hostPort;

	std::string m_dbname;

	bool m_supportTransactions;

public:
	SUrlInfo();
	SUrlInfo(const SUrlInfo& a_other);
	EDbType parseSQLURL(const std::string& a_sqlURL);
	bool parseMySQLURL(const std::string& a_sqlURL, BSLib::uint32 a_parsePosition);

	SUrlInfo& operator =(const SUrlInfo& a_other);
};

class IConnection
{
public:
	virtual ~IConnection(){}

	virtual bool connect(const SUrlInfo& a_sqlurl) = 0;

	virtual bool executeQuery(const std::string& a_sql) = 0;
	virtual bool executeQuery(const std::string& a_sql, CDbReaderPtr& a_readerPtr) = 0;
	
	virtual bool executeSelect(const std::string& a_tableName, const std::string& a_where, const std::string& a_order, const SDbColumn* a_column, CDbReaderPtr& a_readerPtr, BSLib::int32 a_limit, BSLib::int32 a_limitFrom) = 0;
	virtual int  executeSelect(const std::string& a_tableName, const std::string& a_where, const std::string& a_order, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer, BSLib::int32 a_limit, BSLib::int32 a_limitFrom) = 0;
	virtual bool executeUpdate(const std::string& a_tableName, const std::string& a_where, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer) = 0;
	virtual bool executeReplace(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer) = 0;
	virtual bool executeInsert(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer, BSLib::uint64* a_autoIncrement) = 0;
	virtual bool executeDelete(const std::string& a_tableName, const std::string& a_where) = 0;
	virtual bool executeDelete(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer) = 0;

	virtual bool escapeString(const std::string& a_src, std::string& a_dest) = 0;
	virtual bool escapeString(const char* a_src, uint32 a_srcSize, std::string& a_dest) = 0;

	virtual bool commit() = 0;

	virtual bool rollback() = 0;

	virtual bool setTransactions(bool a_supportTransactions) = 0;
	virtual void close() = 0;

	virtual HDbConnection getHandle() = 0;
};

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_CONNECTION__

