#ifndef __BSLIB_DATEBSLIB_DBMGR__
#define __BSLIB_DATEBSLIB_DBMGR__

#include <BSLib/utility/singleton.h>
#include <BSLib/database/baseDef.h>

namespace BSLib
{

namespace Database
{

class CDBMgr
{
public:
	CDBMgr();
	~CDBMgr();

	BSLIB_SINGLETON_DECLARE(CDBMgr);

public:
	bool init(BSLib::int32 a_threadPoolCount = -1);
	void final();
};

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_DBMGR__
