#ifndef __BSLIB_UTILITY_THREAD_MSGQUEUETHD_H__
#define __BSLIB_UTILITY_THREAD_MSGQUEUETHD_H__

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

#if defined(WIN32)

#define BSLIB_UTILITY_HNDTHDMSGQUEUE_INVALID NULL
typedef	DWORD	HndThdMsgQueue;

#elif defined(_LINUX)

#define BSLIB_UTILITY_HNDTHDMSGQUEUE_INVALID (-1)
typedef int	HndThdMsgQueue;

#endif

class BSLIB_UTILITY_API CThdMsgQueue
{
public:
	static bool create(HndThdMsgQueue& queHandle);
	static void remove(HndThdMsgQueue queHandle);

	//同步获取消息
	// 0< 异常
	// >0 收到消息
	static int recv(HndThdMsgQueue queHandle, uint32* para1, uint16* para2, void** para3);
	// =0 没有收到消息
	static int recvAsync(HndThdMsgQueue queHandle, uint32* para1, uint16* para2, void** para3);
	
	//异步发送消息
	static bool send(HndThdMsgQueue queHandle, uint32 para1, uint16 para2, void* para3);
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_THREAD_MSGQUEUETHD_H__

