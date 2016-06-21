#include "dbThreadTask.h"
#include "mysqlThreadData.h"

namespace BSLib
{

namespace Database
{

//////////////////////////////////////////////////////////////////////////
void CDBUpdateTask::executeTask(BSLib::Utility::CThreadPoolDataPtr& a_threadDataPtr)
{
	CMysqlThreadData* threadData = (CMysqlThreadData*)a_threadDataPtr;
	if (threadData == NULL) {
		return ;
	}
	IConnection* connection = threadData->getDbConnection(m_handle);
	if (connection == NULL) {
		return ;
	}
	connection->executeUpdate(m_tableName, m_where, m_column, m_outDataBuffer);
}

//////////////////////////////////////////////////////////////////////////
void CDBInsertTask::executeTask(BSLib::Utility::CThreadPoolDataPtr& a_threadDataPtr)
{
	CMysqlThreadData* threadData = (CMysqlThreadData*)a_threadDataPtr;
	if (threadData == NULL) {
		return ;
	}
	IConnection* connection = threadData->getDbConnection(m_handle);
	if (connection == NULL) {
		return ;
	}
	connection->executeInsert(m_tableName, m_column, m_outDataBuffer, NULL);
}

//////////////////////////////////////////////////////////////////////////
void CDBReplaceTask::executeTask(BSLib::Utility::CThreadPoolDataPtr& a_threadDataPtr)
{
	CMysqlThreadData* threadData = (CMysqlThreadData*)a_threadDataPtr;
	if (threadData == NULL) {
		return ;
	}
	IConnection* connection = threadData->getDbConnection(m_handle);
	if (connection == NULL) {
		return ;
	}
	connection->executeReplace(m_tableName, m_column, m_outDataBuffer);
}

//////////////////////////////////////////////////////////////////////////
void CDBDeleteTask::executeTask(BSLib::Utility::CThreadPoolDataPtr& a_threadDataPtr)
{
	CMysqlThreadData* threadData = (CMysqlThreadData*)a_threadDataPtr;
	if (threadData == NULL) {
		return ;
	}
	IConnection* connection = threadData->getDbConnection(m_handle);
	if (connection == NULL) {
		return ;
	}
	if (m_outDataBuffer.readReady()) {
		connection->executeDelete(m_tableName, m_column, m_outDataBuffer);
		return ;
	}
	connection->executeDelete(m_tableName, m_where);
}

}//Database

}//BSLib
