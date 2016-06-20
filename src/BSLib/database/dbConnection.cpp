//////////////////////////////////////////////////////////////////////
//	created:	2012/09/06
//	filename:	src\BSLib\dateBSLib\dbConnection.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/database/dbConnection.h>
#include "mysqlConnection.h"

namespace BSLib
{

namespace Database
{

SUrlInfo::SUrlInfo()
{
	m_hostPort = 0;
	m_supportTransactions = false;
}

SUrlInfo::SUrlInfo(const SUrlInfo& a_other)
{
	m_user = a_other.m_user;
	m_password = a_other.m_password;
	m_host = a_other.m_host;
	m_hostPort = a_other.m_hostPort;
	m_dbname = a_other.m_dbname;
	m_supportTransactions = a_other.m_supportTransactions;
}

EDbType SUrlInfo::parseSQLURL(const std::string& a_sqlURL)
{
	const char* connString = a_sqlURL.c_str();

	if (0 == strncmp(connString, "mysql://", strlen("mysql://"))) {
		if (parseMySQLURL(connString, (uint32)strlen("mysql://"))) {
			return EDBTYPE_MYSQL;
		}
	}
	return EDBTYPE_ERROR;
}

//mysql://user:pad@host:port/dbname
bool SUrlInfo::parseMySQLURL(const std::string& a_sqlURL, BSLib::uint32 a_parsePosition)
{
	std::string strPort;
	BSLib::uint32 state = 0;
	for (BSLib::uint32 i = a_parsePosition; i < a_sqlURL.size(); ++i) {
		switch (state) {
		case 0:
			{
				if (a_sqlURL[i] == ':') {
					++state;
				} else {
					m_user.push_back(a_sqlURL[i]);
				}
			}
			break;
		case 1:
			{
				if (a_sqlURL[i] == '@') {
					++state;
				} else {
					m_password.push_back(a_sqlURL[i]);
				}
			}
			break;
		case 2:
			{
				if (a_sqlURL[i] == ':') {
					++state;
				} else {
					m_host.push_back(a_sqlURL[i]);
				}
			}
			break;
		case 3:
			{
				if (a_sqlURL[i] == '/') {
					++state;
				} else {
					strPort.push_back(a_sqlURL[i]);
				}
			}
			break;
		case 4:
			{
				m_dbname.push_back(a_sqlURL[i]);
			}
			break;
		default:
			break;
		}
	}
	m_hostPort = 3306;
	if (!strPort.empty()) {
		m_hostPort = atoi(strPort.c_str());
	} 
	return true;
}

SUrlInfo& SUrlInfo::operator =(const SUrlInfo& a_other)
{
	m_user = a_other.m_user;
	m_password = a_other.m_password;
	m_host = a_other.m_host;
	m_hostPort = a_other.m_hostPort;
	m_dbname = a_other.m_dbname;
	m_supportTransactions = a_other.m_supportTransactions;

	return *this;
}

//////////////////////////////////////////////////////////////////////////

CDbConnection::CDbConnection()
: m_connection(NULL)
{
	;
}

CDbConnection::~CDbConnection()
{
	close();
}

bool CDbConnection::connect(const std::string& a_sqlurl, bool a_supportTransactions)
{
	if (m_connection != NULL) {
		return false;
	}
	SUrlInfo urlInfor;
	if (urlInfor.parseSQLURL(a_sqlurl) == EDBTYPE_MYSQL) {
		if (m_connection == NULL) {
			m_connection = new CMysqlConnection();
			if (m_connection == NULL) {
				return false;
			}
		}
		urlInfor.m_supportTransactions = a_supportTransactions;
		if (!m_connection->connect(urlInfor)) {
			BSLIB_SAFE_DELETE(m_connection);
			return false;
		}
	}
	return true;
}

bool CDbConnection::executeQuery(const std::string& a_sql)
{
	if (m_connection == NULL) {
		return false;
	}
	return m_connection->executeQuery(a_sql);
}

bool CDbConnection::executeQuery(const std::string& a_sql, CDbReaderPtr& a_readerPtr)
{
	if (m_connection == NULL) {
		return false;
	}
	return m_connection->executeQuery(a_sql, a_readerPtr);
}

bool CDbConnection::executeSelect(const std::string& a_tableName, const std::string& a_where, const std::string& a_order, const SDbColumn* a_column, CDbReaderPtr& a_readerPtr, BSLib::int32 a_limit, BSLib::int32 a_limitFrom)
{
	if (m_connection == NULL) {
		return false;
	}
	return m_connection->executeSelect(a_tableName, a_where, a_order, a_column, a_readerPtr, a_limit, a_limitFrom);
}

int CDbConnection::executeSelect(const std::string& a_tableName, const std::string& a_where, const std::string& a_order, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer, BSLib::int32 a_limit, BSLib::int32 a_limitFrom)
{
	if (m_connection == NULL) {
		return false;
	}
	return m_connection->executeSelect(a_tableName, a_where, a_order, a_column, a_outDataBuffer, a_limit, a_limitFrom);
}

bool CDbConnection::executeUpdate(const std::string& a_tableName, const std::string& a_where, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer)
{
	if (m_connection == NULL) {
		return false;
	}
	return m_connection->executeUpdate(a_tableName, a_where, a_column, a_outDataBuffer);
}

bool CDbConnection::executeReplace(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer)
{
	if (m_connection == NULL) {
		return false;
	}
	return m_connection->executeReplace(a_tableName, a_column, a_outDataBuffer);
}

bool CDbConnection::executeInsert(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer, BSLib::uint64* a_autoIncrement)
{
	if (m_connection == NULL) {
		return false;
	}
	return m_connection->executeInsert(a_tableName, a_column, a_outDataBuffer, a_autoIncrement);
}

bool CDbConnection::executeDelete(const std::string& a_tableName, const std::string& a_where)
{
	if (m_connection == NULL) {
		return false;
	}
	return m_connection->executeDelete(a_tableName, a_where);
}

bool CDbConnection::executeDelete(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer)
{
	if (m_connection == NULL) {
		return false;
	}
	return m_connection->executeDelete(a_tableName, a_column, a_outDataBuffer);
}

bool CDbConnection::escapeString(const std::string& a_src, std::string& a_dest)
{
	if (m_connection == NULL) {
		return false;
	}
	return m_connection->escapeString(a_src, a_dest);
}

bool CDbConnection::escapeString(const char* a_src, uint32 a_srcSize, std::string& a_dest)
{
	if (m_connection == NULL) {
		return false;
	}
	return m_connection->escapeString(a_src, a_srcSize, a_dest);
}

bool CDbConnection::commit()
{
	if (m_connection == NULL) {
		return false;
	}
	return m_connection->commit();
}

bool CDbConnection::rollback()
{
	if (m_connection == NULL) {
		return false;
	}
	return m_connection->rollback();
}

bool CDbConnection::setTransactions(bool a_supportTransactions)
{
	if (m_connection == NULL) {
		return false;
	}
	return m_connection->setTransactions(a_supportTransactions);
}

void CDbConnection::close()
{
	if (m_connection == NULL) {
		return ;
	}
	m_connection->close();
	BSLIB_SAFE_DELETE(m_connection);
}

HDbConnection CDbConnection::getHandle()
{
	if (m_connection == NULL) {
		return INVALID_HDBCONNECTION;
	}
	return m_connection->getHandle();
}

}//Database

}//BSLib

