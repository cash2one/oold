#ifndef __BSLIB_DATEBSLIB_BASEDEF__
#define __BSLIB_DATEBSLIB_BASEDEF__

#include <BSLib/utility/baseDef.h>

#ifdef BSLIB_DATABSLIB_EXPORTS
#define BSLIB_DATABSLIB_API _declspec(dllexport)
#elif defined(BSLIB_DATABSLIB_IMPORTS)
#define BSLIB_DATABSLIB_API _declspec(dllimport)
#else
#define BSLIB_DATABSLIB_API
#endif

namespace BSLib
{

namespace Database
{

typedef BSLib::int32 HDbConnection;
const HDbConnection INVALID_HDBCONNECTION = -1;

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_BASEDEF__


