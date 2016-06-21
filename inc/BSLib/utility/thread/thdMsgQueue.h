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

	//ͬ����ȡ��Ϣ
	// 0< �쳣
	// >0 �յ���Ϣ
	static int recv(HndThdMsgQueue queHandle, uint32* para1, uint16* para2, void** para3);
	// =0 û���յ���Ϣ
	static int recvAsync(HndThdMsgQueue queHandle, uint32* para1, uint16* para2, void** para3);
	
	//�첽������Ϣ
	static bool send(HndThdMsgQueue queHandle, uint32 para1, uint16 para2, void* para3);
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_THREAD_MSGQUEUETHD_H__

