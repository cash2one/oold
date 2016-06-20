//////////////////////////////////////////////////////////////////////
//	created:	2014/11/14
//	filename: 	GSLib\uniqueIDType.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_UNIQUEIDTYPE_H__
#define __GSLIB_UNIQUEIDTYPE_H__

#include <GFLib/commonServer/uniqueIDMgr.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

enum EUniqueIDType
{
	EUNIQUEIDTYPE_NULL = 0,
	EUNIQUEIDTYPE_MAILID = 1,
    EUNIQUEIDTYPE_ROLEID = 2,
};

}//GSLib

#endif//__GSLIB_UNIQUEIDTYPE_H__