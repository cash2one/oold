//////////////////////////////////////////////////////////////////////
//	created:	2014/07/19
//	filename:	GSLib\tracer.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////

#ifndef __GSLIB_TRACER_H__
#define __GSLIB_TRACER_H__

#include <GFLib/commonServer/tracer.h>

namespace GSLib
{

enum ESystemTraceType
{
	ETT_GSLIB_LOGINSYSTEM = GFLib::ETT_GFLIB_EXTEND,
	ETT_GSLIB_DBSYSTEM,
	ETT_GSLIB_PLAYERSYSTEM,
	ETT_GSLIB_SCENESYSTEM,
	ETT_GSLIB_EQUIPSYSTEM,
	ETT_GSLIB_ITEMSYSTEM,
	ETT_GSLIB_SKILLPSYSTEM,
	ETT_GSLIB_NPCSYSTEM,
	ETT_GSLIB_PETSYSTEM,
	ETT_GSLIB_PRIZESYSTEM,
	ETT_GSLIB_TASKSYSTEM,
	ETT_GSLIB_CHATSYSTEM,
	ETT_GSLIB_MAILSYSTEM,
	ETT_GSLIB_RANKSYSTEM,
	ETT_GSLIB_SHOPSYSTEM,
	ETT_GSLIB_FRIENDSYSTEM,
	ETT_GSLIB_ACTIVITYSYSTEM,
    ETT_GSLIB_ACHIEVESYSTEM,
	ETT_GSLIB_MASTERSYSTEM,

	ETT_GSLIB_GAME,//”Œœ∑¬ﬂº≠»’÷æ

	ETT_GSLIB_EXTEND = 128,
};

}//GFLib

#endif//__GSLIB_TRACER_H__