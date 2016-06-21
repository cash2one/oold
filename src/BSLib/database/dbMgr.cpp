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
