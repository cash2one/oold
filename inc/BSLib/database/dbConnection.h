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
	// Qualifier: �������ݿ�
	// Returns:   bool ���ӳɹ�����true�����򷵻�false
	// Parameter: const std::string & a_sqlurl ���ݿ����ӵ�URL������MySQL���ݿ� mysql://user:pwd@host:port/dbname
	// Parameter: bool a_supportTransactions �������Ƿ�֧������
	///////////////////////////////////////////////////////////////////////////
	bool connect(const std::string& a_sqlurl, bool a_supportTransactions);
	
	///////////////////////////////////////////////////////////////////////////
	// Method:    executeQuery
	// Qualifier: ִ��һ��SQL���
	// Returns:   bool �ɹ�����true��ʧ�ܷ���false
	// Parameter: const std::string & a_sql SQL���
	///////////////////////////////////////////////////////////////////////////
	bool executeQuery(const std::string& a_sql);

	///////////////////////////////////////////////////////////////////////////
	// Method:    executeQuery
	// Qualifier: ִ��һ��SQL��䣬���н������
	// Returns:   bool �ɹ�����true��ʧ�ܷ���false
	// Parameter: const std::string & a_sql SQL���
	// Parameter: CDbReaderPtr & a_readerPtr �������
	///////////////////////////////////////////////////////////////////////////
	bool executeQuery(const std::string& a_sql, CDbReaderPtr& a_readerPtr);

	///////////////////////////////////////////////////////////////////////////
	// Method:    executeSelect
	// Qualifier: ִ��SELECT SQL
	// Returns:   bool �ɹ�����true��ʧ�ܷ���false
	// Parameter: const std::string & a_tableName SQL�����ı���
	// Parameter: const std::string & a_where SQL��where���ʽ��û������Ϊ��
	// Parameter: const std::string & a_order SQL��order���ʽ��û������Ϊ��
	// Parameter: const SDbColumn * a_column Ҫ���������ݿ��ֶ��������飬��{"",0,0}Ϊ���һ������Ԫ�ر�ʾ����
	// Parameter: CDbReaderPtr& a_readerPtr �������
	// Parameter: BSLib::int32 a_limit ���ؽ����¼���������Ŀ����
	// Parameter: BSLib::int32 a_limitFrom ���ؿ�ʼλ��
	///////////////////////////////////////////////////////////////////////////
	bool executeSelect(const std::string& a_tableName, const std::string& a_where, const std::string& a_order, const SDbColumn* a_column, CDbReaderPtr& a_readerPtr, BSLib::int32 a_limit = -1, BSLib::int32 a_limitFrom = 0);
	int  executeSelect(const std::string& a_tableName, const std::string& a_where, const std::string& a_order, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer, BSLib::int32 a_limit = -1, BSLib::int32 a_limitFrom = 0);

	///////////////////////////////////////////////////////////////////////////
	// Method:    executeUpdate
	// Qualifier: ִ��UPDATE SQL
	// Returns:   bool
	// Parameter: const std::string & a_tableName SQL�����ı���
	// Parameter: const std::string & a_where SQL��where���ʽ��û������Ϊ��
	// Parameter: const SDbColumn * a_column Ҫ���������ݿ��ֶ��������飬��{"",0,0}Ϊ���һ������Ԫ�ر�ʾ����
	// Parameter: BSLib::Utility::CStream & a_outDataBuffer ����a_column��������ʽ�����л����ݱ��浽DB
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
	// Qualifier: ִ��DELETE SQL
	// Returns:   bool �ɹ�����true��ʧ�ܷ���false
	// Parameter: const std::string & a_tableNameS QL�����ı���
	// Parameter: const std::string & a_where SQL��where���ʽ��û������Ϊ��
	///////////////////////////////////////////////////////////////////////////
	bool executeDelete(const std::string& a_tableName, const std::string& a_where);
	bool executeDelete(const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer);

	// Method:    escapeString
	// Qualifier: ת���ַ���Ϊ��Ч��MYSQL�ַ���
	// Returns:   bool  �ɹ�����true��ʧ�ܷ���false
	// Parameter: const connHandleID handleID
	// Parameter: const std::string & a_src Դ�ַ���
	// Parameter: std::string & a_dest ת������ַ���
	///////////////////////////////////////////////////////////////////////////
	bool escapeString(const std::string& a_src, std::string& a_dest);
	bool escapeString(const char* a_src, uint32 a_srcSize, std::string& a_dest);

	///////////////////////////////////////////////////////////////////////////
	// Method:    commit
	// Qualifier: �����ύ
	// Returns:   bool �ɹ�����true��ʧ�ܷ���false
	///////////////////////////////////////////////////////////////////////////
	bool commit();

	// Method:    rollback
	// Qualifier: ����ع�
	// Returns:   bool �ɹ�����true��ʧ�ܷ���false
	///////////////////////////////////////////////////////////////////////////
	bool rollback();

	///////////////////////////////////////////////////////////////////////////
	// Method:    setTransactions
	// Qualifier: ���ô������Ƿ�֧������
	// Returns:   bool �ɹ�����true��ʧ�ܷ���false
	// Parameter: bool a_supportTransactions �Ƿ�֧������
	///////////////////////////////////////////////////////////////////////////
	bool setTransactions(bool a_supportTransactions);

	///////////////////////////////////////////////////////////////////////////
	// Method:    close
	// Qualifier: �ر�����
	// Returns:   void
	///////////////////////////////////////////////////////////////////////////
	void close();

	///////////////////////////////////////////////////////////////////////////
	// Method:    getHandle
	// Qualifier: ��ȡ���Ӿ�������ӵ����ݿ���ͬ�����ܻ�õ���ͬ�ľ��
	// Returns:   HDbConnection
	///////////////////////////////////////////////////////////////////////////
	HDbConnection getHandle();

private:
	IConnection* m_connection;
};

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_DBCONNECTION__



