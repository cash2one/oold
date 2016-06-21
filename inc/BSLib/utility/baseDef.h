#ifndef __BSLIB_UTILITY_BASEDEF_H__
#define __BSLIB_UTILITY_BASEDEF_H__

#include <BSLib/utility/baseInc.h>

#if defined( WIN32 )

#pragma warning(disable:4251)
#pragma warning(disable:4996)

#endif

namespace BSLib
{

typedef int                int32;
typedef unsigned int       uint32;	      

typedef short              int16;	   
typedef unsigned short     uint16;	      

typedef char               int8;
typedef unsigned char      uint8;

#if defined( WIN32 )
	
	typedef __int64            int64;
	typedef unsigned __int64   uint64;	      

#elif defined(_LINUX)
	
	typedef long long int				int64; 
	typedef unsigned long long int		uint64;

#endif

}// base

#define BSLIB_LO_SHIFT(x, y)   ((x) >> (y))
#define BSLIB_HI_SHIFT(x, y)   ((x) << (y))

#define BSLIB_INT64_C(val)	(val##LL)
#define BSLIB_UINT64_C(val)	(val##ULL)

#ifndef NULL
	#ifdef __cplusplus
		#define NULL    0
	#else
		#define NULL    ((void *)0)
	#endif
#endif

#if defined( WIN32 )

	#define BSLibSprintf sprintf_s

#elif defined(_LINUX)		   

	#define BSLibSprintf snprintf	

#else

   #error "Unknown platform !!"  

#endif

#define BSLIB_INT8_MIN (-0x7f - 1)
#define BSLIB_INT8_MAX (0x7f)
#define BSLIB_UINT8_MIN (0x00)
#define BSLIB_UINT8_MAX (0xff)

#define BSLIB_INT16_MIN (-0x7fff - 1)
#define BSLIB_INT16_MAX (0x7fff)
#define BSLIB_UINT16_MIN (0x0000)
#define BSLIB_UINT16_MAX (0xffff)

#define BSLIB_INT32_MIN (-0x7fffffff - 1)
#define BSLIB_INT32_MAX (0x7fffffff)
#define BSLIB_UINT32_MIN (0x00000000)
#define BSLIB_UINT32_MAX (0xffffffff)

#define BSLIB_INT64_MIN (INT64_C(-0x7fffffffffffffff) - 1)
#define BSLIB_INT64_MAX INT64_C(0x7fffffffffffffff)
#define BSLIB_UINT64_MIN INT64_C(0x0000000000000000)
#define BSLIB_UINT64_MAX INT64_C(0xffffffffffffffff)

#ifndef BSLIB_SAFE_DELETE
	#define BSLIB_SAFE_DELETE(x)     { delete (x); (x) = NULL; }
#endif // BSLIB_SAFE_DELETE

#ifndef BSLIB_SAFE_DELETE_ARRAY
	#define BSLIB_SAFE_DELETE_ARRAY(x)  { delete [] x; x = NULL; }
#endif // BSLIB_SAFE_DELETE_ARRAY  

#define BSLIB_ABS(f) ( f>0 ? f : -f )

#define BSLIB_MAX(f1, f2) ( f1>f2 ? f1 : f2 )

#define BSLIB_MIN(f1, f2) ( f1>f2 ? f2 : f1 )

#ifdef BSLIB_UTILITY_EXPORTS
	#define BSLIB_UTILITY_API _declspec(dllexport)
#elif defined(BSLIB_UTILITY_IMPORTS)
	#define BSLIB_UTILITY_API _declspec(dllimport)
#else
	#define BSLIB_UTILITY_API
#endif

#ifdef _WIN32
	#define BSLIB_DLL_EXPORT extern "C" _declspec(dllexport)
#else
	#define BSLIB_DLL_EXPORT extern "C" 
#endif

#endif //__BSLIB_UTILITY_BASEDEF_H__




