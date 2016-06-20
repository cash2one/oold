//////////////////////////////////////////////////////////////////////
//	created:	2014/11/20
//	filename: 	BSLib\math\baseDef.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_MATH_BASEDEF_H__
#define __BSLIB_MATH_BASEDEF_H__

#include <math.h>
#include <BSLib/utility/baseDef.h>

#ifdef BSLIB_MATH_EXPORTS
#define BSLIB_MATH_API _declspec(dllexport)
#elif defined(BSLIB_MATH_IMPORTS)
#define BSLIB_MATH_API _declspec(dllimport)
#else
#define BSLIB_MATH_API
#endif

#define GMH_EPSILON     (0.00001f)

namespace BSLib
{

namespace Math
{

typedef float Scalar;

}//Math

}//BSLib

#endif//__BSLIB_MATH_BASEDEF_H__