//////////////////////////////////////////////////////////////////////
//	created:	2014/12/5
//	filename: 	msgNumIDActivitySystem.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_ACTIVITYSYSTEM_MSGNUMIDACTIVITYSYSTEM_H__
#define __GSLIB_ACTIVITYSYSTEM_MSGNUMIDACTIVITYSYSTEM_H__

#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace ActivitySystem
{

enum EMsgNumIDActivitySystem
{
	EMSGNUMID_ACTIVITYSYSTEM_GC2GM_REQ_GET_ATTENDENCE_DATA = 1,
	EMSGNUMID_ACTIVITYSYSTEM_GM2GC_ACK_GET_ATTENDENCE_DATA = 2,

	EMSGNUMID_ACTIVITYSYSTEM_GC2GM_REQ_SGIN_IN = 3,
	EMSGNUMID_ACTIVITYSYSTEM_GM2GC_ACK_SIGN_IN = 4,

	EMSGNUMID_ACTIVITYSYSTEM_GC2GM_REQ_DRAW_CARD = 5,
	EMSGNUMID_ACTIVITYSYSTEM_GM2GC_ACK_DRAW_CARD = 6,

	EMSGNUMID_ACTIVITYSYSTEM_GC2GM_REQ_GET_DRAW_CARD_INFO = 7,
	EMSGNUMID_ACTIVITYSYSTEM_GM2GC_ACK_GET_DRAW_CARD_INFO = 8,
};




}

}//GSLib

#endif
