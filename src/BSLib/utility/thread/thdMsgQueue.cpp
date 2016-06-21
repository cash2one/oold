#ifndef WIN32

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#endif

#include <string.h>
#include <BSLib/utility/thread/thdMsgQueue.h>

namespace BSLib
{

namespace Utility
{

bool CThdMsgQueue::create(HndThdMsgQueue& queHandle)
{
#if defined(WIN32)

	MSG msg;
	queHandle = ::GetCurrentThreadId(); 
	::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
	return true; 

#elif defined(_LINUX)

	queHandle = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
	if(queHandle < 0){
		return false;
	}
	return true;

#else

#error "Unknown platform !!"

#endif
}

void CThdMsgQueue::remove(HndThdMsgQueue queHandle)
{
#if defined(WIN32)

	;

#elif defined(_LINUX)

	if(queHandle >= 0) {
		msgctl(queHandle, IPC_RMID, 0);
	}

#else

#error "Unknown platform !!"

#endif
}

//同步获取消息
int CThdMsgQueue::recv(HndThdMsgQueue queHandle, uint32* para1, uint16* para2, void** para3)
{
#if defined(WIN32)

	MSG msg;
	BOOL bRet;
	while((bRet = ::GetMessage(&msg, NULL, 0, 0)) != 0) { 
		if (msg.message >= WM_USER && msg.message < WM_APP){
			break;
		}
		::TranslateMessage(&msg); 
		::DispatchMessage(&msg);
	}
	if (bRet == 0){
		return -1;
	}
	if (para1){
		*para1 = (uint32)msg.wParam;
	}
	if (para2){
		*para2 = (uint16)(msg.message - WM_USER);
	}
	if (para3){
		*para3 = (void*)msg.lParam;
	}
	return 1;

#elif defined(_LINUX)

	msgbuf *mb;
	char buf[sizeof(msgbuf) + sizeof(uint32) + sizeof(uint16) + sizeof(void*)] = {0};
	int flag = 0;

	memset(buf, 0, sizeof(buf));
	mb = (msgbuf*)buf;

	flag |= MSG_NOERROR;
	if (msgrcv(queHandle, mb, sizeof(uint32) + sizeof(uint16) + sizeof(void*), 1, flag) == -1){
		return -1;
	}
	if (para1){
		*para1 = *((uint32*)((void*)mb->mtext));
	}
	if(para2){
		*para2 = *((uint16*)(mb->mtext + sizeof(uint32)));
	}
	if(para3){
		*para3 = *((void**)(mb->mtext + sizeof(uint32) + sizeof(uint16)));
	}
	return 1;

#else

#error "Unknown platform !!"

#endif
}

int CThdMsgQueue::recvAsync(HndThdMsgQueue queHandle, uint32* para1, uint16* para2, void** para3)
{
#if defined(WIN32)

	MSG msg;
	BOOL bRet;
	while((bRet = ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) != 0) { 
		if (msg.message >= WM_USER && msg.message < WM_APP){
			break;
		}
		::TranslateMessage(&msg); 
		::DispatchMessage(&msg);
		if (msg.message == WM_QUIT){
			return -1;
		}
	}
	if (bRet == 0){
		return 0;
	}
	if (para1){
		*para1 = (uint32)msg.wParam;
	}
	if (para2){
		*para2 = (uint16)(msg.message - WM_USER);
	}
	if (para3){
		*para3 = (void*)msg.lParam;
	}
	return 1;

#elif defined(_LINUX)

	msgbuf *mb;
	char buf[sizeof(msgbuf) + sizeof(uint32) + sizeof(uint16) + sizeof(void*)] = {0};
	int flag = 0;

	memset(buf, 0, sizeof(buf));
	mb = (msgbuf*)buf;

	flag |= IPC_NOWAIT;
	if (msgrcv(queHandle, mb, sizeof(uint32) + sizeof(uint16) + sizeof(void*), 1, flag) == -1){
		if (errno == ENOMSG) {
			return 0;
		}
		return -1;
	}
	if (para1){
		*para1 = *((uint32*)((void*)mb->mtext));
	}
	if(para2){
		*para2 = *((uint16*)(mb->mtext + sizeof(uint32)));
	}
	if(para3){
		*para3 = *((void**)(mb->mtext + sizeof(uint32) + sizeof(uint16)));
	}
	return 1;

#else

#error "Unknown platform !!"

#endif
}

//异步发送消息
bool CThdMsgQueue::send(HndThdMsgQueue queHandle, uint32 para1, uint16 para2, void* para3)
{
#if defined(WIN32)

	UINT msg = para2 + WM_USER;
	if (msg >= WM_APP) {
		return false;
	}
	if(::PostThreadMessage(queHandle, msg, para1, (LPARAM)para3) == false){
		return false;
	}
	return true;

#elif defined(_LINUX)

	msgbuf *mb;
	char buf[sizeof(msgbuf) + sizeof(uint32) + sizeof(uint16) + sizeof(void*)] = {0};
	int flag = 0;

	mb = (msgbuf*) buf;
	mb->mtype = 1;

	*((uint32*)((void*)mb->mtext)) = para1;
	*((uint16*)(mb->mtext + sizeof(uint32))) = para2;
	*((void**)(mb->mtext + sizeof(uint32) + sizeof(uint16))) = para3;

	flag |= IPC_NOWAIT;
	if (msgsnd(queHandle, mb, sizeof(uint32) + sizeof(uint16) + sizeof(void*), flag) == 0){
		return true;
	}
	// error;
	return false;

#else

#error "Unknown platform !!"

#endif
}

}//Utility

}//BSLib

