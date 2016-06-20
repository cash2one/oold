//////////////////////////////////////////////////////////////////////
//	created:	2015/03/02
//	filename: 	GSLib\sceneSystem\sceneSystemDefine.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SCENESYSTEM_SCENESYSTEMDEFINE_H__
#define __GSLIB_SCENESYSTEM_SCENESYSTEMDEFINE_H__

#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace SceneSystem
{
	const BSLib::uint32 MAX_CHALLENGEE_COUNT = 5;
	const BSLib::uint32 MAX_ARENA_CHALLENGEES_RANK = 400;
	enum EArenaAction
	{
		EARENA_ACTION_NONE = 0,
		EARENA_ACTION_GET_ARENA_DATA,	
		EARENA_ACTION_GET_ARENA_CHALLENGABLE_CHALLENGEES,
		EARENA_ACTION_GET_ARENA_CHALLENGEE_DATA,
		EARENA_ACTION_UPDATE_RECORD_TO_CHALLENGEE,
		EARENA_ACTION_FINISH_ARENA_CHALLENGE,
	};

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_MSGNUMIDSCENESYSTEM_H__
