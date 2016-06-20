//////////////////////////////////////////////////////////////////////
//	created:	2012/09/06
//	filename:	src\BSLib\dateBSLib\mysqlConnection.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_DATEBSLIB_MYSQLCONNECTION__
#define __BSLIB_DATEBSLIB_MYSQLCONNECTION__

#include "connection.h"
#include <mysql.h>

#define BSLIB_DATABSLIB_BINDPARA_COUNT_MAX 256
namespace BSLib
{

namespace Database
{

class CMysqlConnection : public IConnection
{
public:
	CMysqlConnection();
	virtual ~CMysqlConnection();

	virtual bool connect(const SUrlInfo& a_sqlurl);

	virtual bool executeQuery(const std::string& command);
	virtual bool executeQuery(const std::string& command, CDbReaderPtr& dbReaderPtr);

	virtual bool executeSelect(const std::string& a_tableName, const std::string& a_where, const std::string& a_order, const SDbColumn* a_column, CDbReaderPtr& a_readerPtr, BSLib::int32 a_limit, BSLib::int32 a_limitFrom);
	virtual int  executeSelect(const std::string& a_tableName, const std::string& a_where, const std::string& a_order, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer, BSLib::int32 a_limit, BSLib::int32 a_limitFrom);
	virtual bool executeUpdate(const std::string& a_tableName, const std::string& a_where, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer);
	
	virtual bool executeReplace(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer);

	virtual bool executeInsert(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer, BSLib::uint64* a_autoIncrement);
	virtual bool executeDelete(const std::string& a_tableName, const std::string& a_where);
	virtual bool executeDelete(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer);

	virtual bool escapeString(const std::string& a_src, std::string& a_dest);
	virtual bool escapeString(const char* a_src, uint32 a_srcSize, std::string& a_dest);

	virtual bool commit();

	virtual bool rollback();

	virtual bool setTransactions(bool a_supportTransactions);

	virtual void close();

	virtual HDbConnection getHandle() { return m_handle; }

private:
	bool _checkConnect();

	bool _executeReplace(BSLib::Utility::CStringA& a_sqlCommand, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer);
	bool _executeUpdate(BSLib::Utility::CStringA& a_sqlCommand, const std::string& a_tableName, const std::string& a_where, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer);
	bool _executeDelete(BSLib::Utility::CStringA& a_sqlCommand, const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer);

private:
	SUrlInfo m_urlInfor;
	MYSQL m_mysql;
	HDbConnection m_handle;

};

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_CONNECTION__

