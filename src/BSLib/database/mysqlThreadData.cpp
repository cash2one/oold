//////////////////////////////////////////////////////////////////////
//	created:	2015/04/06
//	filename:	src\BSLib\database\mysqlThreadData.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include "mysqlConnectionPool.h"
#include "mysqlConnection.h"
#include "mysqlThreadData.h"

namespace BSLib
{

namespace Database
{

CMysqlThreadData::CMysqlThreadData()
{
	;
}

CMysqlThreadData::~CMysqlThreadData()
{
	;
}

void CMysqlThreadData::init()
{
	;
}

void CMysqlThreadData::final()
{
	BSLib::Utility::CHashMap<HDbConnection, IConnection*>::iterator it = m_dbConnections.begin();
	for (; it != m_dbConnections.end(); ++it) {
		IConnection* connection = it->second;
		if (connection != NULL) {
			connection->close();
			BSLIB_SAFE_DELETE(connection);
		}
	}
	m_dbConnections.clear();
}

IConnection* CMysqlThreadData::getDbConnection(HDbConnection a_handle)
{
	IConnection* connection = NULL;
	m_dbConnections.getValue(a_handle, connection);
	if (connection != NULL) {
		return connection;
	}
	SUrlInfoItem* item = CMysqlConnectionPool::singleton().getUrlInfo(a_handle);
	if (item == NULL) {
		return NULL;
	}
	connection = new CMysqlConnection;
	if (connection == NULL) {
		return NULL;
	}
	if (!connection->connect(item->m_urlInfo)) {
		BSLIB_SAFE_DELETE(connection);
		return NULL;
	}
	m_dbConnections.setValue(a_handle, connection);
	return connection;
}

}//Database

}//BSLib