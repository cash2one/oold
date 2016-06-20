//////////////////////////////////////////////////////////////////////
//	created:	2012/09/10
//	filename: 	GFLib\managerServer\tracer.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GFLIB_MANAGERSERVER_TRACER_H__
#define __GFLIB_MANAGERSERVER_TRACER_H__

#include <GFLib/commonServer/tracer.h>

namespace GFLib
{

enum EManagerTraceType
{
	ETT_GFLIB_MANAGER = GFLib::ETT_GFLIB_COMMON_EXTEND,
	ETT_GFLIB_MANAGER_EXTEND,
};

}//GFLib

#endif//__GFLIB_MANAGERSERVER_TRACER_H__



