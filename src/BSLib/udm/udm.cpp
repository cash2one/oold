#include <BSLib/udm/udm.h>
#include "udmMgr.h"
#include "udmEpollMgr.h"

namespace BSLib
{

namespace UDM
{

UDMSOCKET socket()
{
	return CUdmMgr::singleton().udmSocket();
}

int bind(UDMSOCKET udmSocket, const struct sockaddr* name, int namelen)
{
	return CUdmMgr::singleton().bind(udmSocket, name, namelen);
}

int bind(UDMSOCKET udmSocket, UDMSOCKET existUdmSocket)
{
	return CUdmMgr::singleton().bind(udmSocket, existUdmSocket);
}

int listen(UDMSOCKET udmSocket)
{
	return CUdmMgr::singleton().listen(udmSocket);
}

UDMSOCKET accept(UDMSOCKET udmSocket, struct sockaddr* addr, int* addrlen)
{
	return CUdmMgr::singleton().accept(udmSocket, addr, addrlen);
}

int connect(UDMSOCKET udmSocket, const struct sockaddr* name, int namelen)
{
	return CUdmMgr::singleton().connect(udmSocket, name, namelen);
}

int close(UDMSOCKET udmSocket)
{
	return CUdmMgr::singleton().close(udmSocket);
}

int getpeername(UDMSOCKET udmSocket, struct sockaddr* name, int* namelen)
{
	return CUdmMgr::singleton().getPeerName(udmSocket, name, namelen);
}

int getsockname(UDMSOCKET udmSocket, struct sockaddr* name, int* namelen)
{
	return CUdmMgr::singleton().getSockName(udmSocket, name, namelen);
}

EUdmStatus getsockstate(UDMSOCKET udmSocket)
{
	return CUdmMgr::singleton().getSockState(udmSocket);
}

int getlasterror()
{
	return CUdmMgr::singleton().getLastError();
}

//可靠传输
int send(UDMSOCKET udmSocket, const char* buf, int len)
{
	return CUdmMgr::singleton().send(udmSocket, buf, len);
}

int recv(UDMSOCKET udmSocket, char* buf, int len)
{
	return CUdmMgr::singleton().recv(udmSocket, buf, len);
}
//不可靠传输
int sendto(UDMSOCKET udmSocket, const char* buf, int len)
{
	return CUdmMgr::singleton().sendTo(udmSocket, buf, len);
}

int recvfrom(UDMSOCKET udmSocket, char* buf, int len)
{
	return CUdmMgr::singleton().recvFrom(udmSocket, buf, len);
}

//epoll
int epollCreate()
{
	return CUdmEpollMgr::singleton().epollCreate();
}

int epollAddSock(const int eid, const UDMSOCKET udmSocket, int udmEpollType, void* tempData)
{
	return CUdmEpollMgr::singleton().epollAddSock(eid, udmSocket, udmEpollType, tempData);
}

int epollDelSock(const int eid, const UDMSOCKET udmSocket, int udmEpollType)
{
	return CUdmEpollMgr::singleton().epollDelSock(eid, udmSocket, udmEpollType);
}

int epollWait(const int eid, SEpollEvent* epollList, int epollListCount, int msTimeOut)
{
	return CUdmEpollMgr::singleton().epollWait(eid, epollList, epollListCount, msTimeOut);
}

int epollRelease(const int eid)
{
	return CUdmEpollMgr::singleton().epollRelease(eid);
}

}//UDM

}//BSLib


