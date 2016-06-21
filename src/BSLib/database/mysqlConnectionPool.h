#ifndef __BSLIB_DATEBSLIB_MYSQLCONNECTIONPOOL__
#define __BSLIB_DATEBSLIB_MYSQLCONNECTIONPOOL__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/pointer.h>
#include <BSLib/utility/thread/threadPool.h>
#include <BSLib/utility/hashMap.h>
#include <BSLib/database/baseDef.h>
#include "connection.h"

namespace BSLib
{

namespace Database
{

struct SUrlInfoItem
{
	std::string m_key;
	HDbConnection m_handle;
	SUrlInfo m_urlInfo;
};

class CMysqlConnectionPool
{
public:
	CMysqlConnectionPool();
	~CMysqlConnectionPool();

	BSLIB_SINGLETON_DECLARE(CMysqlConnectionPool);

public:
	virtual bool init(BSLib::int32 a_threadPoolCount);
	virtual void final();

	HDbConnection allocateHandle(SUrlInfo& a_urlInfor);
	SUrlInfoItem* getUrlInfo(HDbConnection a_handle);

public:
	bool executeUpdate(HDbConnection a_handle, const std::string& a_tableName, const std::string& a_where, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer);

	bool executeReplace(HDbConnection a_handle, const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer);

	bool executeInsert(HDbConnection a_handle, const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer);
	
	bool executeDelete(HDbConnection a_handle, const std::string& a_tableName, const std::string& a_where);
	bool executeDelete(HDbConnection a_handle, const std::string& a_tableName, const SDbColumn* a_column, BSLib::Utility::CStream& a_outDataBuffer);

public:
	bool isValid() { return m_isValid; }
	bool pushTask(BSLib::Utility::CThreadTaskPtr& a_task);

protected:
	
	void _createTheadData(BSLib::Utility::CThreadPoolDataPtr& a_threadDataPtr);

private:
	bool m_isValid;
	BSLib::Utility::CThreadPool m_threadPool;

	BSLib::Utility::CHashMap<std::string, SUrlInfoItem*> m_urlInfoByKey;
	BSLib::Utility::CHashMap<HDbConnection, SUrlInfoItem*> m_urlInfoByHandle;
	BSLib::Utility::CMutex m_mutex;
	BSLib::int32 m_currentID;
};

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_MYSQLCONNECTIONPOOL__
