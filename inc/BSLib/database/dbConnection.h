#ifndef __BSLIB_DATEBSLIB_DBCONNECTION__
#define __BSLIB_DATEBSLIB_DBCONNECTION__

#include <BSLib/database/dbReader.h>
#include <BSLib/database/dbParam.h>

namespace BSLib
{

namespace Database
{

class IConnection;

class BSLIB_DATABSLIB_API CDbConnection
{
public:
	CDbConnection();
	~CDbConnection();

	///////////////////////////////////////////////////////////////////////////
	// Method:    connect
	// Qualifier: 连接数据库
	// Returns:   bool 连接成功返回true，否则返回false
	// Parameter: const std::string & a_sqlurl 数据库连接的URL，比如MySQL数据库 mysql://user:pwd@host:port/dbname
	// Parameter: bool a_supportTransactions 此连接是否支持事务
	///////////////////////////////////////////////////////////////////////////
	bool connect(const std::string& a_sqlurl, bool a_supportTransactions);
	
	///////////////////////////////////////////////////////////////////////////
	// Method:    executeQuery
	// Qualifier: 执行一个SQL语句
	// Returns:   bool 成功返回true，失败返回false
	// Parameter: const std::string & a_sql SQL语句
	///////////////////////////////////////////////////////////////////////////
	bool executeQuery(const std::string& a_sql);

	///////////////////////////////////////////////////////////////////////////
	// Method:    executeQuery
	// Qualifier: 执行一个SQL语句，并有结果返回
	// Returns:   bool 成功返回true，失败返回false
	// Parameter: const std::string & a_sql SQL语句
	// Parameter: CDbReaderPtr & a_readerPtr 结果返回
	///////////////////////////////////////////////////////////////////////////
	bool executeQuery(const std::string& a_sql, CDbReaderPtr& a_readerPtr);

	///////////////////////////////////////////////////////////////////////////
	// Method:    executeSelect
	// Qualifier: 执行SELECT SQL
	// Returns:   bool 成功返回true，失败返回false
	// Parameter: const std::string & a_tableName SQL操作的表名
	// Parameter: const std::string & a_where SQL的where表达式，没有用是为空
	// Parameter: const std::string & a_order SQL的order表达式，没有用是为空
	// Parameter: const SDbColumn * a_column 要操作的数据库字段描述数组，以{"",0,0}为最后一个数组元素表示结束
	// Parameter: CDbReaderPtr& a_readerPtr 结果返回
	// Parameter: BSLib::int32 a_limit 返回结果记录集的最大条目数量
	// Parameter: BSLib::int32 a_limitFrom 返回开始位置
	///////////////////////////////////////////////////////////////////////////
	bool executeSelect(const std::string& a_tableName, const std::string& a_where, const std::string& a_order, const SDbColumn* a_column, CDbReaderPtr& a_readerPtr, BSLib::int32 a_limit = -1, BSLib::int32 a_limitFrom = 0);
	int  executeSelect(const std::string& a_tableName, const std::string& a_where, const std::string& a_order, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer, BSLib::int32 a_limit = -1, BSLib::int32 a_limitFrom = 0);

	///////////////////////////////////////////////////////////////////////////
	// Method:    executeUpdate
	// Qualifier: 执行UPDATE SQL
	// Returns:   bool
	// Parameter: const std::string & a_tableName SQL操作的表名
	// Parameter: const std::string & a_where SQL的where表达式，没有用是为空
	// Parameter: const SDbColumn * a_column 要操作的数据库字段描述数组，以{"",0,0}为最后一个数组元素表示结束
	// Parameter: BSLib::Utility::CStream & a_outDataBuffer 按照a_column的描述方式反序列化数据保存到DB
	///////////////////////////////////////////////////////////////////////////
	bool executeUpdate(const std::string& a_tableName, const std::string& a_where, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer);
	bool executeReplace(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer);

	///////////////////////////////////////////////////////////////////////////
	// Method:    executeInsert
	// Qualifier:
	// Returns:   bool
	// Parameter: const std::string & a_tableName
	// Parameter: const SDbColumn * a_column
	// Parameter: BSLib::Utility::CStream & a_outDataBuffer
	// Parameter: BSLib::uint32 * a_autoIncrement
	///////////////////////////////////////////////////////////////////////////
	bool executeInsert(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer, BSLib::uint64* a_autoIncrement = NULL);
	
	///////////////////////////////////////////////////////////////////////////
	// Method:    executeDelete
	// Qualifier: 执行DELETE SQL
	// Returns:   bool 成功返回true，失败返回false
	// Parameter: const std::string & a_tableNameS QL操作的表名
	// Parameter: const std::string & a_where SQL的where表达式，没有用是为空
	///////////////////////////////////////////////////////////////////////////
	bool executeDelete(const std::string& a_tableName, const std::string& a_where);
	bool executeDelete(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer);

	// Method:    escapeString
	// Qualifier: 转换字符串为有效的MYSQL字符串
	// Returns:   bool  成功返回true，失败返回false
	// Parameter: const connHandleID handleID
	// Parameter: const std::string & a_src 源字符串
	// Parameter: std::string & a_dest 转换后的字符串
	///////////////////////////////////////////////////////////////////////////
	bool escapeString(const std::string& a_src, std::string& a_dest);
	bool escapeString(const char* a_src, uint32 a_srcSize, std::string& a_dest);

	///////////////////////////////////////////////////////////////////////////
	// Method:    commit
	// Qualifier: 事务提交
	// Returns:   bool 成功返回true，失败返回false
	///////////////////////////////////////////////////////////////////////////
	bool commit();

	// Method:    rollback
	// Qualifier: 事务回滚
	// Returns:   bool 成功返回true，失败返回false
	///////////////////////////////////////////////////////////////////////////
	bool rollback();

	///////////////////////////////////////////////////////////////////////////
	// Method:    setTransactions
	// Qualifier: 设置此连接是否支持事务
	// Returns:   bool 成功返回true，失败返回false
	// Parameter: bool a_supportTransactions 是否支持事务
	///////////////////////////////////////////////////////////////////////////
	bool setTransactions(bool a_supportTransactions);

	///////////////////////////////////////////////////////////////////////////
	// Method:    close
	// Qualifier: 关闭连接
	// Returns:   void
	///////////////////////////////////////////////////////////////////////////
	void close();

	///////////////////////////////////////////////////////////////////////////
	// Method:    getHandle
	// Qualifier: 获取链接句柄。链接的数据库相同，可能会得到相同的句柄
	// Returns:   HDbConnection
	///////////////////////////////////////////////////////////////////////////
	HDbConnection getHandle();

private:
	IConnection* m_connection;
};

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_DBCONNECTION__



