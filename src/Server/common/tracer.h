//////////////////////////////////////////////////////////////////////
//	created:	2014/07/09
//	filename:	src\Server\common\tracer.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////


#ifndef __SERVER_COMMON_TRACER_H__
#define __SERVER_COMMON_TRACER_H__

#include <GSLib/tracer.h>

namespace Server
{

enum EServerTraceType
{
	ETT_SERVER_COMMON = GSLib::ETT_GSLIB_EXTEND,
};

}//Server

#endif//__SERVER_COMMON_TRACER_H__



