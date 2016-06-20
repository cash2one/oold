//////////////////////////////////////////////////////////////////////
//	created:	2015/04/02
//	filename: 	src\BSLib\database\dbMgr.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/database/dbMgr.h>
#include "mysqlConnectionPool.h"

namespace BSLib
{

namespace Database
{

BSLIB_SINGLETON_DEFINE(CDBMgr);

CDBMgr::CDBMgr()
{
	;
}

CDBMgr::~CDBMgr()
{
	;
}

bool CDBMgr::init(BSLib::int32 a_threadPoolCount)
{
	if (!CMysqlConnectionPool::singleton().init(a_threadPoolCount)) {
		return false;
	}
	return true;
}

void CDBMgr::final()
{
	CMysqlConnectionPool::singleton().final();
}

}//Database

}//BSLib