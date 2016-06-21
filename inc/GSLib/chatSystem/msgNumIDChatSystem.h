#ifndef __GSLIB_CHATSYSTEM_MSGNUMIDCHATSYSTEM_H__
#define __GSLIB_CHATSYSTEM_MSGNUMIDCHATSYSTEM_H__

#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace ChatSystem
{

enum EMsgNumIDTestSystem
{
	EMSGNUMID_CHATSYSTEM_GC2GM_REQ_CHAT = 1,
	EMSGNUMID_CHATSYSTEM_GC2GM_ACK_CHAT= 2,
	EMSGNUMID_CHATSYSTEM_GC2GM_ACK_CHAT2ALL = 3,
	EMSGNUMID_CHATSYSTEM_GC2GM_ACK_INIT_CHAT_DATA = 4,

	// between servers
	EMSGNUMID_CHATSYSTEM_GM2CN_REQ_PRIVATE_CHAT = 99,
};

}//ChatSystem

}//GSLib

#endif//__GSLIB_CHATSYSTEM_MSGNUMIDCHATSYSTEM_H__

