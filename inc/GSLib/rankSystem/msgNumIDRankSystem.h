//////////////////////////////////////////////////////////////////////
//	created:	2014/10/23
//	filename: 	GSLib\rankSystem\msgNumIDRankSystem.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_RANKSYSTEM_MSGNUMIDRANKSYSTEM_H__
#define __GSLIB_RANKSYSTEM_MSGNUMIDRANKSYSTEM_H__

#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace RankSystem
{

enum EMsgNumIDRankSystem
{
	EMSGNUMID_RANKSYSTEM_GC2CN_REQ_GET_RANK_LIST = 3,
	EMSGNUMID_RANKSYSTEM_CN2GC_ACK_GET_RANK_LIST,
	EMSGNUMID_RANKSYSTEM_GM2CN_NTF_UPDATE,
	EMSGNUMID_RANKSYSTEM_CN2GM_NTF_PLACE,
	EMSGNUMID_RANKSYSTEM_GM2CN_NTF_INIT_FINISH,
};

}//RankSystem

}//GSLib

#endif//__GSLIB_RANKSYSTEM_MSGNUMIDRANKSYSTEM_H__
