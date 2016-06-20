//////////////////////////////////////////////////////////////////////
//	created:	2015/04/06
//	filename:	src\BSLib\database\mysqlThreadData.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_DATEBSLIB_MYSQLTHREADDATA_H__
#define __BSLIB_DATEBSLIB_MYSQLTHREADDATA_H__

#include <BSLib/utility/pointer.h>
#include <BSLib/utility/thread/threadPool.h>
#include <BSLib/utility/hashMap.h>
#include <BSLib/database/baseDef.h>
#include "connection.h"

namespace BSLib
{

namespace Database
{

//////////////////////////////////////////////////////////////////////////
class CMysqlThreadData : public BSLib::Utility::CThreadPoolData
{
public:
	CMysqlThreadData();
	virtual ~CMysqlThreadData();

public:
	virtual void init();
	virtual void final();

	IConnection* getDbConnection(HDbConnection a_handle);

private:
	BSLib::Utility::CHashMap<HDbConnection, IConnection*> m_dbConnections;
};

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_MYSQLTHREADDATA_H__