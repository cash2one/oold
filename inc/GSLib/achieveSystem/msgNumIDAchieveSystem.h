//////////////////////////////////////////////////////////////////////
//	created:	2014/09/09
//	filename: 	GSLib\ACHIEVESYSTEM\msgNumIDAchieveSystem.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_ACHIEVESYSTEM_MSGNUMIDACHIEVESYSTEM_H__
#define __GSLIB_ACHIEVESYSTEM_MSGNUMIDACHIEVESYSTEM_H__

#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace AchieveSystem
{
    enum EMsgNumIDAchieveSystem
    {
        EMSGNUMID_ACHIEVESYSTEM_GC2GM_REQ_GET_ACHIEVE_LIST = 1,
        EMSGNUMID_ACHIEVESYSTEM_GM2GC_ACK_GET_ACHIEVE_LIST = 2,
        EMSGNUMID_ACHIEVESYSTEM_GC2GM_REQ_GET_ACHIEVE_PRIZE = 3,     
        EMSGNUMID_ACHIEVESYSTEM_GM2GC_ACK_GET_ACHIEVE_PRIZE = 4,
        EMSGNUMID_ACHIEVESYSTEM_GC2GM_REQ_SAVE_ACHIEVE_DATA = 5,     
        EMSGNUMID_ACHIEVESYSTEM_GM2GC_ACK_SAVE_ACHIEVE_DATA = 6,
        EMSGNUMID_ACHIEVESYSTEM_GM2GC_NTF_ACHIEVE_FINISHED = 7,
    };

    enum EGetAchieveListResult
    {
        EGETACHIEVELIST_RESULT_SUCCESS = 0,
        EGETACHIEVELIST_RESULT_FAIL = 1,
    };

    enum EGetAchievePrizeResult
    {
        EGETACHIEVEPRIZE_RESULT_SUCCESS = 0,
        EGETACHIEVEPRIZE_RESULT_FAIL = 1,
    };

    enum ESaveAchieveDataResult
    {
        ESAVEACHIEVEDATA_RESULT_SUCCESS = 0,
        ESAVEACHIEVEDATA_RESULT_FAIL = 1,
    };

}//AchieveSystem

}//GSLib

#endif//__GSLIB_ACHIEVESYSTEM_MSGNUMIDACHIEVESYSTEM_H__
