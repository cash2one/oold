//////////////////////////////////////////////////////////////////////
//	created:	2012/08/20
//	filename:	BSLib\udm\udm.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UDM_UDM_H__
#define __BSLIB_UDM_UDM_H__

#include <BSLib/udm/baseDef.h>

namespace BSLib
{

namespace UDM
{

BSLIB_UDM_API UDMSOCKET socket();
BSLIB_UDM_API int bind(UDMSOCKET udmSocket, const struct sockaddr* name, int namelen);
BSLIB_UDM_API int bind(UDMSOCKET udmSocket, UDMSOCKET existUdmSocket);
BSLIB_UDM_API int listen(UDMSOCKET udmSocket);
BSLIB_UDM_API UDMSOCKET accept(UDMSOCKET udmSocket, struct sockaddr* addr, int* addrlen);
BSLIB_UDM_API int connect(UDMSOCKET udmSocket, const struct sockaddr* name, int namelen);
BSLIB_UDM_API int close(UDMSOCKET udmSocket);

BSLIB_UDM_API int getpeername(UDMSOCKET udmSocket, struct sockaddr* name, int* namelen);
BSLIB_UDM_API int getsockname(UDMSOCKET udmSocket, struct sockaddr* name, int* namelen);

BSLIB_UDM_API EUdmStatus getsockstate(UDMSOCKET udmSocket);

BSLIB_UDM_API int getlasterror();

//可靠传输
//BSLIB_UDM_API int send(UDMSOCKET rudp, const char* buf, int len);
//BSLIB_UDM_API int recv(UDMSOCKET rudp, char* buf, int len);

//不可靠传输
BSLIB_UDM_API int sendto(UDMSOCKET udmSocket, const char* buf, int len);
BSLIB_UDM_API int recvfrom(UDMSOCKET udmSocket, char* buf, int len);

//epoll
BSLIB_UDM_API int epollCreate();
BSLIB_UDM_API int epollAddSock(const int eid, const UDMSOCKET udmSocket, int udmEpollType, void* tempData);
BSLIB_UDM_API int epollDelSock(const int eid, const UDMSOCKET udmSocket, int udmEpollType);
BSLIB_UDM_API int epollWait(const int eid, SEpollEvent* epollList, int epollListCount, int msTimeOut);
BSLIB_UDM_API int epollRelease(const int eid);

}//UDM

}//BSLib

#endif//__BSLIB_UDM_UDM_H__
