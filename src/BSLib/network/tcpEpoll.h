#ifndef __BSLIB_NETWORK_TCPEPOLL_H__
#define __BSLIB_NETWORK_TCPEPOLL_H__

#ifdef WIN32

//#include <WinSock2.h>


#define DATA_LENGTH 256

#endif//WIN32

#include <BSLib/utility/hashMap.h>
#include <BSLib/network/baseDef.h>

namespace BSLib
{

namespace Network
{

#ifdef WIN32
	
	class CIOCP;
	struct SEpollEvent;

#else

	class CEPoll;

#endif

class BSLIB_NETWORK_API CTcpEpoll
{
public:
	CTcpEpoll();
	virtual ~CTcpEpoll();

	bool createEpoll();
	void releaseEpoll();

	bool addTcpToEpoll(const SOCKET& tcpSocket, void* data);
	bool delTcpFromEpoll(const SOCKET& tcpSocket);
	
	bool epoll(int msSec);

	bool postRecv(const SOCKET& tcpSocket);
	bool notifyRecv(const SOCKET& tcpSocket, void* a_para);
	bool notifySend(const SOCKET& tcpSocket);

	void setReadSocketFun(BSLib::Utility::CFunction<bool, SOCKET&, void*>& fun);
	void setWriteSocketFun(BSLib::Utility::CFunction<bool, SOCKET&, void*>& fun);
	void setTerminateSocketFun(BSLib::Utility::CFunction<void, SOCKET&, void*>& fun);

#ifdef WIN32
public:	
	bool epollAccept(SOCKET& tcpSocket, void* a_para1, void* a_para2);
	bool notifyAccept(const SOCKET& tcpSocket, void* a_para);
	void setAcceptSocketFun(BSLib::Utility::CFunction<bool, SOCKET&, SOCKET&, void*>& fun);

#endif


private:
#ifdef WIN32

	CIOCP* m_iocp;
	SEpollEvent* m_readEvent;
	SEpollEvent* m_writeEvent;
	BSLib::Utility::CFunction<bool, SOCKET&, SOCKET&, void*>* m_acceptScoket;

#else

	CEPoll* m_epoll;

#endif

	BSLib::Utility::CHashMap<SOCKET, void*> m_socketEvents;
	BSLib::Utility::CFunction<bool, SOCKET&, void*>* m_readScoket;
	BSLib::Utility::CFunction<bool, SOCKET&, void*>* m_writeScoket;
	BSLib::Utility::CFunction<void, SOCKET&, void*>* m_terminateScoket;
};

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_TCPEPOLL_H__

