#include <BSLib/utility/tracer.h>
#include "mysqlConnection.h"
#include "mysqlReader.h"
#include "mysqlConnectionPool.h"

namespace BSLib
{

namespace Database
{

CMysqlConnection::CMysqlConnection()
: m_handle(INVALID_HDBCONNECTION)
{
	;
}

CMysqlConnection::~CMysqlConnection()
{
	close();
}

bool CMysqlConnection::connect(const SUrlInfo& a_sqlurl)
{
	m_urlInfor = a_sqlurl;
	if (mysql_init(&m_mysql) == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "初始化MySQL失败");
		return false;
	}
	if (mysql_real_connect(&m_mysql,
							m_urlInfor.m_host.c_str(),
							m_urlInfor.m_user.c_str(),
							m_urlInfor.m_password.c_str(),
							m_urlInfor.m_dbname.c_str(),
							m_urlInfor.m_hostPort,
							NULL, CLIENT_COMPRESS | CLIENT_MULTI_STATEMENTS | CLIENT_INTERACTIVE) == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "连接MySQL失败[%s]", mysql_error(&m_mysql));
		return false;
	}

	executeQuery("SET NAMES UTF8");
	
	if (!setTransactions(m_urlInfor.m_supportTransactions)) {
		mysql_close(&m_mysql);
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "连接MySQL是否支持事务失败[%s]", mysql_error(&m_mysql));
		return false;
	}

	m_handle = CMysqlConnectionPool::singleton().allocateHandle(m_urlInfor);

	return true;
}

bool CMysqlConnection::executeQuery(const std::string& command)
{
	if (!_checkConnect()) {
		BSLIB_LOG_FATAL(ETT_BSLIB_DATABASE, "连接MySQL断开");
		return false;
	}

	BSLIB_LOG_DEBUG(ETT_BSLIB_DATABASE, "[SQL=%s]", command.c_str());

	int res = mysql_real_query(&m_mysql, command.c_str(), (unsigned long)command.length());
	if (res != 0) {
		printf("%s\n", mysql_error(&m_mysql));
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "执行[%s]失败[%s]", command.c_str(), mysql_error(&m_mysql));
		return false;
	}
	return true;
}

bool CMysqlConnection::executeQuery(const std::string& command, CDbReaderPtr& dbReaderPtr)
{
	if (!_checkConnect()) {
		BSLIB_LOG_FATAL(ETT_BSLIB_DATABASE, "连接MySQL断开");
		return false;
	}
	
	BSLIB_LOG_DEBUG(ETT_BSLIB_DATABASE, "[SQL=%s]", command.c_str());

	int res = mysql_real_query(&m_mysql, command.c_str(), (unsigned long)command.length());
	if (res != 0) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "执行[%s]失败[%s]", command.c_str(), mysql_error(&m_mysql));
		return false;
	}
	MYSQL_RES* mysqlRes = mysql_store_result(&m_mysql);
	if (mysqlRes == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "获取结果失败[%s]", command.c_str(), mysql_error(&m_mysql));
		return false;
	}
	if (mysql_num_rows(mysqlRes) < 0) {
		mysql_free_result(mysqlRes);
		return false;
	}
	CMysqlReader* mysqlReader = new CMysqlReader(mysqlRes);
	if (mysqlReader == NULL) {
		mysql_free_result(mysqlRes);
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "分配内存失败");
		return false;
	}
	dbReaderPtr = mysqlReader;
	return true;
}

bool CMysqlConnection::executeSelect(const std::string& a_tableName, const std::string& a_where, const std::string& a_order, const SDbColumn* a_column, CDbReaderPtr& a_readerPtr, BSLib::int32 a_limit, BSLib::int32 a_limitFrom)
{
	if (a_column == NULL) {
		return false;
	}
	std::string sqlCommand = "SELECT ";
	bool first = true;
	const SDbColumn* column = a_column;
	while (!column->m_name.empty()) {
		if (!first){
			sqlCommand += ", ";
		} else {
			first = false;
		}
		sqlCommand += column->m_name;
		++column;
	}

	if (!a_tableName.empty()) {
		sqlCommand += " FROM ";
		sqlCommand += a_tableName;
	}

	if (!a_where.empty()) {
		sqlCommand += " WHERE ";
		sqlCommand += a_where;
	}

	if (!a_order.empty()) {
		sqlCommand += " ORDER BY ";
		sqlCommand += a_order;
	}

	if (a_limitFrom > 0 && a_limit > 0) {
		BSLib::Utility::CStringA strLimit;
		strLimit.format("%d , %d", a_limitFrom, a_limit);
		sqlCommand += " LIMIT ";
		sqlCommand += strLimit;
	} else if (a_limit > 0) {
		BSLib::Utility::CStringA strLimit;
		strLimit.format("%d", a_limit);
		sqlCommand += " LIMIT ";
		sqlCommand += strLimit;
	}
	sqlCommand += ";";
	return executeQuery(sqlCommand, a_readerPtr);
}

int CMysqlConnection::executeSelect(const std::string& a_tableName, const std::string& a_where, const std::string& a_order, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer, BSLib::int32 a_limit, BSLib::int32 a_limitFrom)
{
	CDbReaderPtr a_readerPtr = NULL; 
	if (!executeSelect(a_tableName, a_where, a_order, a_column, a_readerPtr, a_limit, a_limitFrom)) {
		return -1;
	}
	if (a_readerPtr == NULL) {
		return -1;
	}
	int rowCount = 0;
	while (a_readerPtr->nextRow()) {
		const SDbColumn* column = a_column;
		int index = 0;
		while (!column->m_name.empty()) {
			switch(column->m_type)
			{
			case EDT_INT8:
				{
					BSLib::int8 data;
					if (!a_readerPtr->getValue(index, data)){
						a_outDataBuffer.reset();
						return -1;
					}
					a_outDataBuffer << data;
				}
				break;
			case EDT_UINT8:
				{
					BSLib::uint8 data;
					if (!a_readerPtr->getValue(index, data)){
						a_outDataBuffer.reset();
						return -1;
					}
					a_outDataBuffer << data;
				}
				break;
			case EDT_INT16:
				{
					BSLib::int16 data;
					if (!a_readerPtr->getValue(index, data)){
						a_outDataBuffer.reset();
						return -1;
					}
					a_outDataBuffer << data;
				}
				break;
			case EDT_UINT16:
				{
					BSLib::uint16 data;
					if (!a_readerPtr->getValue(index, data)){
						a_outDataBuffer.reset();
						return -1;
					}
					a_outDataBuffer << data;
				}
				break;
			case EDT_INT32:
				{
					BSLib::int32 data;
					if (!a_readerPtr->getValue(index, data)){
						a_outDataBuffer.reset();
						return -1;
					}
					a_outDataBuffer << data;
				}
				break;
			case EDT_UINT32:
				{
					BSLib::uint32 data;
					if (!a_readerPtr->getValue(index, data)){
						a_outDataBuffer.reset();
						return -1;
					}
					a_outDataBuffer << data;
				}
				break;
			case EDT_INT64:
				{
					BSLib::int64 data;
					if (!a_readerPtr->getValue(index, data)){
						a_outDataBuffer.reset();
						return -1;
					}
					a_outDataBuffer << data;
				}
				break;
			case EDT_UINT64:
				{
					BSLib::uint64 data;
					if (!a_readerPtr->getValue(index, data)){
						a_outDataBuffer.reset();
						return -1;
					}
					a_outDataBuffer << data;
				}
				break;
			case EDT_FLOAT:
				{
					float data;
					if (!a_readerPtr->getValue(index, data)){
						a_outDataBuffer.reset();
						return -1;
					}
					a_outDataBuffer << data;
				}
				break;
			case EDT_DOUBLE:
				{
					double data;
					if (!a_readerPtr->getValue(index, data)){
						a_outDataBuffer.reset();
						return -1;
					}
					a_outDataBuffer << data;
				}
				break;
			case EDT_STRING:
				{
					std::string data;
					if (!a_readerPtr->getValue(index, data)){
						a_outDataBuffer.reset();
						return -1;
					}
					a_outDataBuffer << data;
				}
				break;
			case EDT_VARCHAR:
				{
					if (!a_outDataBuffer.writeReserve(column->m_size)) {
						a_outDataBuffer.reset();
						return -1;
					}
					memset(a_outDataBuffer.writePtr(), 0, column->m_size);
					if (!a_readerPtr->getValue(index, a_outDataBuffer.writePtr(), column->m_size-1)) {
						a_outDataBuffer.reset();
						return -1;
					}
					a_outDataBuffer.writeFlip(column->m_size);
				}
				break;
			case EDT_BLOB:
				{
					BSLib::uint32 valueSize = (BSLib::uint32)a_readerPtr->getValueSize(index);
					a_outDataBuffer << valueSize;
					if (valueSize > 0) {
						a_readerPtr->getValue(index, a_outDataBuffer);
					}
				}
				break;
			case EDT_BIN:
				{
					if (!a_outDataBuffer.writeReserve(column->m_size)) {
						a_outDataBuffer.reset();
						return -1;
					}
					memset(a_outDataBuffer.writePtr(), 0, column->m_size);
					if (!a_readerPtr->getValue(index, a_outDataBuffer.writePtr(), column->m_size)) {
						a_outDataBuffer.reset();
						return -1;
					}
					a_outDataBuffer.writeFlip(column->m_size);
				}
				break;
			default:
				{
					return -1;
				}
			}
			++column;
			++index;
		}
		++rowCount;
	}
	return rowCount;
}

bool CMysqlConnection::executeUpdate(const std::string& a_tableName, const std::string& a_where, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer)
{
	BSLib::Utility::CStringA sqlCommand;
	while (a_outDataBuffer.readReady()) {
		BSLib::Utility::CStringA tempCommand;
		if (!_executeUpdate(tempCommand, a_tableName, a_where, a_column, a_outDataBuffer)) {
			return false;
		}
		sqlCommand += tempCommand;
		if (sqlCommand.size() > 1 * 1024 * 1024) {
			if(!executeQuery(sqlCommand)){
				return false;
			}
			sqlCommand.clear();
		}
	}
	if (!sqlCommand.empty()) {
		if(!executeQuery(sqlCommand)){
			return false;
		}
	}
	return true;
}

bool CMysqlConnection::executeReplace(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer)
{
	BSLib::Utility::CStringA command = "REPLACE INTO ";
	command += a_tableName;
	command += " ( ";

	bool first = true;
	const SDbColumn* column = a_column;
	while (!column->m_name.empty()) {
		if (!first){
			command += ", ";
		} else {
			first = false;
		}
		command += column->m_name;
		++column;
	}
	command += " ) VALUES ";

	BSLib::Utility::CStringA sqlCommand = command;
	BSLib::Utility::CStringA rowData;
	first = true;

	while (a_outDataBuffer.readReady()) {
		if (!_executeReplace(rowData, a_column, a_outDataBuffer)) {
			return false;
		}
		if (!first){
			sqlCommand += ", ";
		} else {
			first = false;
		}
		sqlCommand += rowData;
		rowData.clear();
		if (sqlCommand.size() > 1 * 1024 * 1024) {
			sqlCommand += ";";
			if(!executeQuery(sqlCommand)){
				return false;
			}
			sqlCommand.clear();
			sqlCommand = command;
			first = true;
		}
	}
	if (!first) {
		sqlCommand += ";";

		if(!executeQuery(sqlCommand)){
			return false;
		}
	}

	return true;
}

bool CMysqlConnection::executeInsert(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer, BSLib::uint64* a_autoIncrement)
{
	BSLib::Utility::CStringA command = "INSERT INTO ";
	command += a_tableName;
	command += " ( ";

	bool first = true;
	const SDbColumn* column = a_column;
	while (!column->m_name.empty()) {
		if (!first){
			command += ", ";
		} else {
			first = false;
		}
		command += column->m_name;
		++column;
	}
	command += " ) VALUES ";

	BSLib::Utility::CStringA rowData;
	BSLib::Utility::CStringA sqlCommand = command;
	first = true;
	
	while (a_outDataBuffer.readReady()) {
		
		if (!_executeReplace(rowData, a_column, a_outDataBuffer)) {
			return false;
		}
		if (!first){
			sqlCommand += ", ";
		} else {
			first = false;
		}
		sqlCommand += rowData;
		rowData.clear();
		if (sqlCommand.size() > 1 * 1024 * 1024) {
			sqlCommand += ";";
			if(!executeQuery(sqlCommand)){
				return false;
			}
			sqlCommand.clear();
			sqlCommand = command;
			first = true;
		}
	}
	if (!first) {
		sqlCommand += ";";

		if(!executeQuery(sqlCommand)){
			return false;
		}
	}
	
	if (a_autoIncrement == NULL) {
		return true;
	}
	*a_autoIncrement = (BSLib::uint64)mysql_insert_id(&m_mysql);
	return true;
};

bool CMysqlConnection::executeDelete(const std::string& a_tableName, const std::string& a_where)
{
	std::string sqlCommand = "DELETE FROM ";
	sqlCommand += a_tableName;
	if (!a_where.empty()) {
		sqlCommand += " WHERE ";
		sqlCommand += a_where;
	}
	sqlCommand += ";";
	return executeQuery(sqlCommand);
}

bool CMysqlConnection::executeDelete(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer)
{
	BSLib::Utility::CStringA sqlCommand;
	while (a_outDataBuffer.readReady()){
		if (!_executeDelete(sqlCommand, a_tableName, a_column, a_outDataBuffer)) {
			return false;
		}
		if (sqlCommand.size()  > 1 * 1024 * 1024) {
			if (!executeQuery(sqlCommand)) {
				return false;
			}
			sqlCommand.clear();
		}
	}
	if (sqlCommand.empty()) {
		return true;
	}
	return executeQuery(sqlCommand);
}

bool CMysqlConnection::escapeString(const std::string& a_src, std::string& a_dest)
{
	return escapeString(a_src.c_str(), (uint32)a_src.length(), a_dest);
}

bool CMysqlConnection::escapeString(const char* a_src, uint32 a_srcSize, std::string& a_dest)
{
	if (!_checkConnect()) {
		BSLIB_LOG_FATAL(ETT_BSLIB_DATABASE, "连接MySQL断开");
		return false;
	}
	if (a_srcSize <= 0) {
		return true;
	}
	int len = 2 * a_srcSize + 1;
	char* buff = new char[len];

	memset(buff, 0, len);
	mysql_real_escape_string(&m_mysql, buff, a_src, a_srcSize);
	a_dest = buff;

	delete [] buff;

	return true;
}

bool CMysqlConnection::commit()
{
	if (mysql_commit(&m_mysql) == 0) {
		return true;
	}
	BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "commit失败[%s]", mysql_error(&m_mysql));
	return false;
}

bool CMysqlConnection::rollback()
{
	if (mysql_rollback(&m_mysql) == 0) {
		return true;
	}
	BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "rollback失败[%s]", mysql_error(&m_mysql));
	return false;
}

bool CMysqlConnection::setTransactions(bool a_supportTransactions)
{
	if (a_supportTransactions){
		if (mysql_autocommit(&m_mysql, 0) == 0) {
			return true;
		}
		BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "set autocommit失败[%s]", mysql_error(&m_mysql));
		return false;
	}
	if (mysql_autocommit(&m_mysql, 1) == 0) {
		return true;
	}
	BSLIB_LOG_ERROR(ETT_BSLIB_DATABASE, "set autocommit失败[%s]", mysql_error(&m_mysql));
	return false;
}

void CMysqlConnection::close()
{
	mysql_close(&m_mysql);
}

bool CMysqlConnection::_checkConnect()
{
	if (mysql_ping(&m_mysql) != 0) {
		close();
		BSLIB_LOG_INFO(ETT_BSLIB_DATABASE, "重新连接MySQL");
		if (!connect(m_urlInfor)){
			BSLIB_LOG_FATAL(ETT_BSLIB_DATABASE, "重新连接MySQL失败");
			return false;
		}
	}
	return true;
}

bool CMysqlConnection::_executeReplace(BSLib::Utility::CStringA& a_sqlCommand, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer)
{
	a_sqlCommand = "(";
	const SDbColumn* column = a_column;
	bool first = true;
	while (!column->m_name.empty()) {
		if (!first){
			a_sqlCommand += ", ";
		} else {
			first = false;
		}
		switch(column->m_type)
		{
		case EDT_INT8:
			{
				BSLib::int8 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_UINT8:
			{
				BSLib::uint8 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_INT16:
			{
				BSLib::int16 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_UINT16:
			{
				BSLib::uint16 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_INT32:
			{
				BSLib::int32 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_UINT32:
			{
				BSLib::uint32 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_INT64:
			{
				BSLib::int64 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_UINT64:
			{
				BSLib::uint64 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_FLOAT:
			{
				float data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_DOUBLE:
			{
				double data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_STRING:
			{
				std::string data;
				std::string temp;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				if (!escapeString(data, temp)) {
					return false;
				}
				a_sqlCommand <<  "\'" << temp << "\'";
			}
			break;
		case EDT_VARCHAR:
			{
				if (a_outDataBuffer.readSize() < column->m_size) {
					return false;
				}
				std::string data = a_outDataBuffer.readPtr();
				if (data.size() >= column->m_size) {
					data.resize(column->m_size - 1);
				}
				std::string temp;
				if (!escapeString(data, temp)) {
					return false;
				}
				a_sqlCommand <<  "\'" << temp << "\'";

				a_outDataBuffer.readFlip(column->m_size);
			}
			break;
		case EDT_BLOB:
			{
				uint32 dataSize = 0;
				try {
					a_outDataBuffer >> dataSize;
				} catch (...) {
					return false;
				}
				if (a_outDataBuffer.readSize() < dataSize) {
					return false;
				}
				std::string temp;
				if (!escapeString(a_outDataBuffer.readPtr(), dataSize, temp)) {
					return false;
				}
				a_sqlCommand <<  "\'" << temp << "\'";

				a_outDataBuffer.readFlip(dataSize);
			}
			break;
		case EDT_BIN:
			{
				if (a_outDataBuffer.readSize() < column->m_size) {
					return false;
				}
				std::string temp;
				if (!escapeString(a_outDataBuffer.readPtr(), column->m_size, temp)) {
					return false;
				}
				a_sqlCommand <<  "\'" << temp << "\'";

				a_outDataBuffer.readFlip(column->m_size);
			}
			break;
		default:
			{
				return false;
			}
		}
		++column;
	}
	a_sqlCommand << ")";
	return true;
}

bool CMysqlConnection::_executeUpdate(BSLib::Utility::CStringA& a_sqlCommand, const std::string& a_tableName, const std::string& a_where, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer)
{
	a_sqlCommand = "UPDATE ";
	a_sqlCommand += a_tableName;
	a_sqlCommand += " SET ";

	bool first = true;
	const SDbColumn* column = a_column;
	while (!column->m_name.empty()) {
		if (!first){
			a_sqlCommand += ", ";
		} else {
			first = false;
		}
		a_sqlCommand << column->m_name;
		a_sqlCommand << " = ";
		switch(column->m_type)
		{
		case EDT_INT8:
			{
				BSLib::int8 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_UINT8:
			{
				BSLib::uint8 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_INT16:
			{
				BSLib::int16 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_UINT16:
			{
				BSLib::uint16 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_INT32:
			{
				BSLib::int32 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_UINT32:
			{
				BSLib::uint32 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_INT64:
			{
				BSLib::int64 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_UINT64:
			{
				BSLib::uint64 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_FLOAT:
			{
				float data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_DOUBLE:
			{
				double data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				a_sqlCommand << data;
			}
			break;
		case EDT_STRING:
			{
				std::string data;
				std::string temp;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				if (!escapeString(data, temp)) {
					return false;
				}
				a_sqlCommand <<  "\'" << temp << "\'";
			}
			break;
		case EDT_VARCHAR:
			{
				if (a_outDataBuffer.readSize() < column->m_size) {
					return false;
				}
				std::string data = a_outDataBuffer.readPtr();
				if (data.size() >= column->m_size) {
					data.resize(column->m_size - 1);
				}
				std::string temp;
				if (!escapeString(data, temp)) {
					return false;
				}
				a_sqlCommand <<  "\'" << temp << "\'";

				a_outDataBuffer.readFlip(column->m_size);
			}
			break;
		case EDT_BLOB:
			{
				uint32 dataSize = 0;
				try {
					a_outDataBuffer >> dataSize;
				} catch (...) {
					return false;
				}
				if (a_outDataBuffer.readSize() < dataSize) {
					return false;
				}
				std::string temp;
				if (!escapeString(a_outDataBuffer.readPtr(), dataSize, temp)) {
					return false;
				}
				a_sqlCommand <<  "\'" << temp << "\'";

				a_outDataBuffer.readFlip(dataSize);
			}
			break;
		case EDT_BIN:
			{
				if (a_outDataBuffer.readSize() < column->m_size) {
					return false;
				}
				std::string temp;
				if (!escapeString(a_outDataBuffer.readPtr(), column->m_size, temp)) {
					return false;
				}
				a_sqlCommand <<  "\'" << temp << "\'";

				a_outDataBuffer.readFlip(column->m_size);
			}
			break;
		default:
			{
				return false;
			}
		}
		++column;
	}
	if (!a_where.empty()){
		a_sqlCommand << " WHERE ";
		a_sqlCommand << a_where;
	}
	a_sqlCommand += ";";
	return true;
}

bool CMysqlConnection::_executeDelete(BSLib::Utility::CStringA& a_sqlCommand, const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer)
{
	std::string sqlCommand = "DELETE FROM ";
	sqlCommand += a_tableName;

	BSLib::Utility::CStringA sqlWhere;
	bool first = true;
	const SDbColumn*column = a_column;
	while (!column->m_name.empty()) {
		if (column->m_flag != EDF_NULL){
			if (!first){
				sqlWhere += " AND ";
			} else {
				first = false;
			}

			sqlWhere += column->m_name;
			sqlWhere += "=";
		}
		
		switch(column->m_type)
		{
		case EDT_INT8:
			{
				BSLib::int8 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				if (column->m_flag != EDF_NULL){
					sqlWhere << data;
				}
			}
			break;
		case EDT_UINT8:
			{
				BSLib::uint8 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				if (column->m_flag != EDF_NULL){
					sqlWhere << data;
				}
			}
			break;
		case EDT_INT16:
			{
				BSLib::int16 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				if (column->m_flag != EDF_NULL){
					sqlWhere << data;
				}
			}
			break;
		case EDT_UINT16:
			{
				BSLib::uint16 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				if (column->m_flag != EDF_NULL){
					sqlWhere << data;
				}
			}
			break;
		case EDT_INT32:
			{
				BSLib::int32 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				if (column->m_flag != EDF_NULL){
					sqlWhere << data;
				}
			}
			break;
		case EDT_UINT32:
			{
				BSLib::uint32 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				if (column->m_flag != EDF_NULL){
					sqlWhere << data;
				}
			}
			break;
		case EDT_INT64:
			{
				BSLib::int64 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				if (column->m_flag != EDF_NULL){
					sqlWhere << data;
				}
			}
			break;
		case EDT_UINT64:
			{
				BSLib::uint64 data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				if (column->m_flag != EDF_NULL){
					sqlWhere << data;
				}
			}
			break;
		case EDT_FLOAT:
			{
				float data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				if (column->m_flag != EDF_NULL){
					sqlWhere << "\'" << data<< "\'";
				}
			}
			break;
		case EDT_DOUBLE:
			{
				double data;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				if (column->m_flag != EDF_NULL){
					sqlWhere << "\'" << data<< "\'";
				}
			}
			break;
		case EDT_STRING:
			{
				std::string data;
				std::string temp;
				try {
					a_outDataBuffer >> data;
				} catch (...) {
					return false;
				} 
				if (!escapeString(data, temp)) {
					return false;
				}
				if (column->m_flag != EDF_NULL){
					sqlWhere <<  "\'" << temp << "\'";
				}
			}
			break;
		case EDT_VARCHAR:
			{
				if (a_outDataBuffer.readSize() < column->m_size) {
					return false;
				}
				std::string data = a_outDataBuffer.readPtr();
				if (data.size() >= column->m_size) {
					data.resize(column->m_size - 1);
				}
				std::string temp;
				if (!escapeString(data, temp)) {
					return false;
				}
				if (column->m_flag != EDF_NULL){
					sqlWhere <<  "\'" << temp << "\'";
				}

				a_outDataBuffer.readFlip(column->m_size);
			}
			break;
		case EDT_BLOB:
			{
				uint32 dataSize = 0;
				try {
					a_outDataBuffer >> dataSize;
				} catch (...) {
					return false;
				}
				if (a_outDataBuffer.readSize() < dataSize) {
					return false;
				}
				std::string temp;
				if (!escapeString(a_outDataBuffer.readPtr(), dataSize, temp)) {
					return false;
				}
				if (column->m_flag != EDF_NULL){
					sqlWhere <<  "\'" << temp << "\'";
				}

				a_outDataBuffer.readFlip(dataSize);
			}
			break;
		case EDT_BIN:
			{
				if (a_outDataBuffer.readSize() < column->m_size) {
					return false;
				}
				std::string temp;
				if (!escapeString(a_outDataBuffer.readPtr(), column->m_size, temp)) {
					return false;
				}
				if (column->m_flag != EDF_NULL){
					sqlWhere <<  "\'" << temp << "\'";
				}

				a_outDataBuffer.readFlip(column->m_size);
			}
			break;
		default:
			{
				return false;
			}
		}
		++column;
	}
	
	a_sqlCommand += sqlCommand;
	if (!sqlWhere.empty()) {
		a_sqlCommand += " WHERE ";
		a_sqlCommand += sqlWhere;
	} 
	a_sqlCommand += ";";
	return true;
}

}//Database

}//BSLib


