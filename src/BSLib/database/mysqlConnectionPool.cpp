#include <BSLib/utility/thread/mutex.h>
#include "mysqlConnectionPool.h"
#include "dbThreadTask.h"
#include "mysqlThreadData.h"

namespace BSLib
{

namespace Database
{

//////////////////////////////////////////////////////////////////////////
BSLIB_SINGLETON_DEFINE(CMysqlConnectionPool);

CMysqlConnectionPool::CMysqlConnectionPool()
: m_isValid(false)
, m_currentID(0)
{
	;
}

CMysqlConnectionPool::~CMysqlConnectionPool()
{
	;
}

bool CMysqlConnectionPool::init(BSLib::int32 a_threadPoolCount)
{
	if (m_isValid) {
		return false;
	}
	int32 count = a_threadPoolCount;
	if (count < 0) {
		count = BSLib::Utility::CThread::getNumberOfProcessors();
		count += 2;
	} else if (count == 0) {
		m_isValid = false;
		return true;
	}
	m_threadPool.init(count, &CMysqlConnectionPool::_createTheadData, this);
	m_isValid = true;
	return true;
}

void CMysqlConnectionPool::final()
{
	if (m_isValid) {
		m_threadPool.final();
	}
	m_isValid = false;

	BSLib::Utility::CHashMap<std::string, SUrlInfoItem*>::iterator it = m_urlInfoByKey.begin();
	for (; it != m_urlInfoByKey.end(); ++it) {
		SUrlInfoItem* item = it->second;
		if (item != NULL) {
			BSLIB_SAFE_DELETE(item);
		}		
	}
	m_urlInfoByKey.clear();
	m_urlInfoByHandle.clear();
}

HDbConnection CMysqlConnectionPool::allocateHandle(SUrlInfo& a_urlInfor)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);

	BSLib::Utility::CStringA key;
	key.format("%s:%d:%s:%s",a_urlInfor.m_host.c_str(), a_urlInfor.m_hostPort, a_urlInfor.m_user.c_str(), a_urlInfor.m_dbname.c_str());

	SUrlInfoItem* item = NULL;
	m_urlInfoByKey.getValue(key, item);
	if (item !=  NULL) {
		return item->m_handle;
	}
	item = new SUrlInfoItem;
	if (item == NULL) {
		return INVALID_HDBCONNECTION;
	}
	item->m_key = key;
	item->m_urlInfo = a_urlInfor;
	item->m_handle = m_currentID;
	m_urlInfoByHandle.setValue(item->m_handle, item);
	
	++m_currentID;

	return item->m_handle;
}

SUrlInfoItem* CMysqlConnectionPool::getUrlInfo(HDbConnection a_handle)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);

	SUrlInfoItem* item = NULL;
	m_urlInfoByHandle.getValue(a_handle, item);
	return item;
}

bool CMysqlConnectionPool::executeUpdate(HDbConnection a_handle, const std::string& a_tableName, const std::string& a_where, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer)
{
	BSLib::Utility::CThreadTaskPtr taskPtr = NULL;
	CDBUpdateTask* task = new CDBUpdateTask();
	if (task == NULL) {
		return false;
	}
	task->m_handle = a_handle;
	task->m_tableName = a_tableName;
	task->m_where = a_where;
	task->m_column = a_column;
	if (a_outDataBuffer.readReady()) {
		a_outDataBuffer.copyTo(task->m_outDataBuffer);
		a_outDataBuffer.reset();
	}
	taskPtr = task;

	return pushTask(taskPtr);
}

bool CMysqlConnectionPool::executeReplace(HDbConnection a_handle, const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer)
{
	BSLib::Utility::CThreadTaskPtr taskPtr = NULL;
	CDBReplaceTask* task = new CDBReplaceTask();
	if (task == NULL) {
		return false;
	}
	task->m_handle = a_handle;
	task->m_tableName = a_tableName;
	task->m_column = a_column;
	if (a_outDataBuffer.readReady()) {
		a_outDataBuffer.copyTo(task->m_outDataBuffer);
		a_outDataBuffer.reset();
	}
	taskPtr = task;

	return pushTask(taskPtr);
}

bool CMysqlConnectionPool::executeInsert(HDbConnection a_handle, const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer)
{
	BSLib::Utility::CThreadTaskPtr taskPtr = NULL;
	CDBInsertTask* task = new CDBInsertTask();
	if (task == NULL) {
		return false;
	}
	task->m_handle = a_handle;
	task->m_tableName = a_tableName;
	task->m_column = a_column;
	if (a_outDataBuffer.readReady()) {
		a_outDataBuffer.copyTo(task->m_outDataBuffer);
		a_outDataBuffer.reset();
	}
	taskPtr = task;

	return pushTask(taskPtr);
}

bool CMysqlConnectionPool::executeDelete(HDbConnection a_handle, const std::string& a_tableName, const std::string& a_where)
{
	BSLib::Utility::CThreadTaskPtr taskPtr = NULL;
	CDBDeleteTask* task = new CDBDeleteTask();
	if (task == NULL) {
		return false;
	}
	task->m_handle = a_handle;
	task->m_tableName = a_tableName;
	task->m_column = NULL;
	task->m_where = a_where;
	taskPtr = task;

	return pushTask(taskPtr);
}

bool CMysqlConnectionPool::executeDelete(HDbConnection a_handle, const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer)
{
	BSLib::Utility::CThreadTaskPtr taskPtr = NULL;
	CDBDeleteTask* task = new CDBDeleteTask();
	if (task == NULL) {
		return false;
	}
	task->m_handle = a_handle;
	task->m_tableName = a_tableName;
	task->m_column = a_column;
	if (a_outDataBuffer.readReady()) {
		a_outDataBuffer.copyTo(task->m_outDataBuffer);
		a_outDataBuffer.reset();
	}
	taskPtr = task;

	return pushTask(taskPtr);
}


bool CMysqlConnectionPool::pushTask(BSLib::Utility::CThreadTaskPtr& a_task)
{
	if (!m_isValid) {
		return false;
	}
	return m_threadPool.pushTask(a_task);
}

void CMysqlConnectionPool::_createTheadData(BSLib::Utility::CThreadPoolDataPtr& a_threadDataPtr)
{
	CMysqlThreadData* threadData = new CMysqlThreadData();
	a_threadDataPtr = (BSLib::Utility::CThreadPoolData*)threadData;
}

}//Database

}//BSLib
