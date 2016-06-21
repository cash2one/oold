#include <stdio.h>
#include "netinit.h"

#ifdef WIN32

namespace BSLib
{

namespace  Network
{

BSLIB_SINGLETON_DEFINE(CNetInit);

CNetInit::CNetInit()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,0), &wsaData);
}

CNetInit::~CNetInit()
{
	WSACleanup();
}

}//Network

}//BSLib

#endif//WIN32


