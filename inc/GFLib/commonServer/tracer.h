//////////////////////////////////////////////////////////////////////
//	created:	2012/09/10
//	filename: 	GFLib\commonServer\tracer.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GFLIB_COMMONSERVER_TRACER_H__
#define __GFLIB_COMMONSERVER_TRACER_H__

#include <GFLib/commonServer/baseDef.h>
#include <BSLib/utility/tracer.h>

namespace GFLib
{

enum ECommonTraceType
{
	ETT_GFLIB_COMMON = BSLib::ETT_BSLIB_EXTEND,
	ETT_GFLIB_EXTEND = 64,
};

}//GFLib

#endif//__GFLIB_COMMONSERVER_TRACER_H__



