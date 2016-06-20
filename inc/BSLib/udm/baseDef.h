//////////////////////////////////////////////////////////////////////
//	created:	2012/08/20
//	filename:	BSLib\udm\baseDef.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UDM_BASEDEF_H__
#define __BSLIB_UDM_BASEDEF_H__

#include <BSLib/utility/baseDef.h>

#ifndef _WIN32

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
typedef int SOCKET;

#endif

#ifdef BSLIB_UDM_EXPORTS
	#define BSLIB_UDM_API _declspec(dllexport)
#elif defined(BSLIB_UDM_IMPORTS)
	#define BSLIB_UDM_API _declspec(dllimport)
#else
	#define BSLIB_UDM_API
#endif

#ifdef WIN32
	#ifndef __MINGW__
		typedef SOCKET SYSSOCKET;
	#else
		typedef int SYSSOCKET;
	#endif
#else
	typedef int SYSSOCKET;
#endif

#define INVALID_UDMSOCK (-1)
#define BSLIB_UDM_ERROR (-1)
#define BSLIB_UDM_OK 0

typedef int UDMSOCKET;

namespace BSLib
{

namespace UDM
{

enum EUdmStatus 
{
	UDM_STATE_NULL = 0,
	UDM_STATE_INIT, 
	UDM_STATE_BIND, 
	UDM_STATE_LISTEN, 
	UDM_STATE_CONNECTING, 
	UDM_STATE_CONNECTED,
	UDM_STATE_OPEN,
	UDM_STATE_BROKEN,
	UDM_STATE_CLOSING, 
	UDM_STATE_CLOSED,
	UDM_STATE_NONEXIST,
	UDM_STATE_DELETE1,
	UDM_STATE_DELETE2,
};

enum EUdmEpollEventType 
{
	UDM_EPOLL_ERROR = 1,
	UDM_EPOLL_READ = 2,
	UDM_EPOLL_WRITE = 4,
};

struct SEpollEvent
{
	UDMSOCKET m_udmSocket;
	int m_udmEpollEvent;
	void* m_tempData;
};

}//UDM

}//BSLib

#endif//__BSLIB_UDM_BASEDEF_H__
