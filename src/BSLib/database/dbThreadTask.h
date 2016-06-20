//////////////////////////////////////////////////////////////////////
//	created:	2015/04/06
//	filename:	src\BSLib\database\dbThreadTask.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_DATEBSLIB_DBTHREADTASK_H__
#define __BSLIB_DATEBSLIB_DBTHREADTASK_H__

#include <BSLib/utility/pointer.h>
#include <BSLib/utility/thread/threadPool.h>
#include <BSLib/utility/stream.h>
#include <BSLib/database/baseDef.h>
#include <BSLib/database/dbParam.h>

namespace BSLib
{

namespace Database
{

enum ETaskType
{
	DBTASK_NULL = 1,
	DBTASK_UPDATE = 1,
	DBTASK_INSERT = 2,
	DBTASK_REPLACE = 3,
	DBTASK_DELETE = 4,
};

class CDBThreadTask : public BSLib::Utility::CThreadTask
{
public:
	CDBThreadTask() : m_handle(INVALID_HDBCONNECTION), m_column(NULL) {}
	virtual ~CDBThreadTask(){}

	virtual ETaskType getType() = 0;

public:
	HDbConnection m_handle;
	std::string m_tableName;
	std::string m_where;
	const SDbColumn* m_column;
	BSLib::Utility::CStream m_outDataBuffer;
};

class CDBUpdateTask : public CDBThreadTask
{
public:
	CDBUpdateTask(){}
	virtual ~CDBUpdateTask(){}

	virtual ETaskType getType(){ return DBTASK_UPDATE; }

	virtual void executeTask(BSLib::Utility::CThreadPoolDataPtr& a_threadDataPtr);
};


class CDBInsertTask : public CDBThreadTask
{
public:
	CDBInsertTask(){}
	virtual ~CDBInsertTask(){}

	virtual ETaskType getType(){ return DBTASK_INSERT; }

	virtual void executeTask(BSLib::Utility::CThreadPoolDataPtr& a_threadDataPtr);
};

class CDBReplaceTask : public CDBThreadTask
{
public:
	CDBReplaceTask(){}
	virtual ~CDBReplaceTask(){}

	virtual ETaskType getType(){ return DBTASK_REPLACE; }

	virtual void executeTask(BSLib::Utility::CThreadPoolDataPtr& a_threadDataPtr);
};

class CDBDeleteTask : public CDBThreadTask
{
public:
	CDBDeleteTask(){}
	virtual ~CDBDeleteTask(){}

	virtual ETaskType getType(){ return DBTASK_DELETE; }

	virtual void executeTask(BSLib::Utility::CThreadPoolDataPtr& a_threadDataPtr);
};


}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_DBTHREADTASK_H__