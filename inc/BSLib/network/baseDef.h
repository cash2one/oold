#ifndef __BSLIB_NETWORK_BASEDEF_H__
#define __BSLIB_NETWORK_BASEDEF_H__

#ifndef _WIN32

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
typedef int SOCKET;

void closesocket(SOCKET sock);

#endif

#include <BSLib/utility/baseDef.h>

#ifdef BSLIB_NETWORK_EXPORTS
	#define BSLIB_NETWORK_API _declspec(dllexport)
#elif defined(BSLIB_NETWORK_IMPORTS)
	#define BSLIB_NETWORK_API _declspec(dllimport)
#else
	#define BSLIB_NETWORK_API
#endif

namespace BSLib
{

namespace Network
{

enum ENetType
{
	NETT_NULL = 0,
	NETT_TCP,
	NETT_UDP,
	NETT_MAX,
};

}//Network

}//BSLib

#endif //__BSLIB_NETWORK_BASEDEF_H__




