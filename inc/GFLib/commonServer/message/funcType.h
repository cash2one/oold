//////////////////////////////////////////////////////////////////////
//	created:	2012/08/05
//	filename: 	GFLib\commonServer\message\funcType.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GFLIB_COMMONSERVER_MESSAGE_FUNCTYPE_H__
#define __GFLIB_COMMONSERVER_MESSAGE_FUNCTYPE_H__

#include <GFLib/commonServer/baseDef.h>

namespace GFLib
{

enum EFuncType
{
	EFUNCTYPE_NULL = 0,
	EFUNCTYPE_SERVER_LINK,
	EFUNCTYPE_SYSTEM_CHANNEL,
	EFUNCTYPE_SERVER_LOCAL,

	EFUNCTYPE_GFLIB_EXTEND = 8,
};

}//GFLib

#endif//__GFLIB_COMMONSERVER_MESSAGE_FUNCTYPE_H__


