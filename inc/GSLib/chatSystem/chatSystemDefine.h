#ifndef __GSLIB_CHATSYSTEM_CHATSYSTEMDEFINE_H__
#define __GSLIB_CHATSYSTEM_CHATSYSTEMDEFINE_H__

#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace ChatSystem
{
	const BSLib::int32	C_MAX_WORLD_CHAT_BUFFERD_CONTENT_COUNT = 20;
	const BSLib::int32	C_MAX_ANNOUNCE_CHAT_BUFFERD_CONTENT_COUNT = 5;
	const BSLib::uint32	C_ITEM_ID_SPEAKER = 100210005;
	const BSLib::uint32	C_ITEM_TYPE_SPEAKER = 0;
	const BSLib::uint32 C_ROLE_TALK_INTERVAL = 3;

enum EChatChanel
{
	CHAT_CHANNEL_PRIVATE,					//私聊频道
	CHAT_CHANNEL_WORLD,					//世界频道
	CHAT_CHANNEL_CITY,						//主城频道
	CHAT_CHANNEL_ANNOUNCE,				//主城频道
};


}//ChatSystem

}//GSLib

#endif//__GSLIB_CHATSYSTEM_MSGNUMIDCHATSYSTEM_H__

