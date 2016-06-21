#ifdef WIN32

#include <WinSock2.h>
#include <mswsock.h>
#include "iocp.h"

#else

#include <sys/epoll.h>
#include "epoll.h"

#endif//WIN32

#include <BSLib/utility/tracer.h>
#include "tcpEpoll.h"

#define BSLIB_NETWORK_EPOLL_MAX 256

namespace BSLib
{

namespace Network
{

#ifdef WIN32

	enum EIOCPOpType
	{
		EIOCP_OP_ERROR = 0,
		EIOCP_OP_READ,
		EIOCP_OP_WRITE,
		EIOCP_OP_ACCEPT,
		EIOCP_OP_MAX,
	};

	struct SEpollEvent
	{
		OVERLAPPED m_ol;
		WSABUF m_buffer;
		char m_dataBuffer[DATA_LENGTH];
		int m_dataLength;
		EIOCPOpType m_type;
		SOCKET m_client; 

		SEpollEvent(EIOCPOpType type)
		{
			clear();
			m_type = type;
		}

		void clear()
		{
			m_type = EIOCP_OP_ERROR;
			m_dataLength = 0;
			m_client = INVALID_SOCKET;
			memset(&m_ol, 0, sizeof(OVERLAPPED));
			memset(&m_buffer, 0, sizeof(WSABUF));
			memset(&m_dataBuffer, 0, sizeof(m_dataBuffer));
		}
	};

#endif

CTcpEpoll::CTcpEpoll()
#ifdef WIN32

: m_iocp(NULL)
, m_readEvent(NULL)
, m_writeEvent(NULL)
, m_acceptScoket(NULL)

#else

: m_epoll(NULL)

#endif
, m_readScoket(NULL)
, m_writeScoket(NULL)
, m_terminateScoket(NULL)
{
}

CTcpEpoll::~CTcpEpoll()
{
	releaseEpoll();

	if (m_readScoket != NULL) {
		BSLIB_SAFE_DELETE(m_readScoket);
	}

	if (m_writeScoket != NULL) {
		BSLIB_SAFE_DELETE(m_writeScoket);
	}

	if (m_terminateScoket != NULL) {
		BSLIB_SAFE_DELETE(m_terminateScoket);
	}
#ifdef WIN32
	if (m_acceptScoket != NULL) {
		BSLIB_SAFE_DELETE(m_acceptScoket);
	}
	if (m_readEvent != NULL) {
		BSLIB_SAFE_DELETE(m_readEvent);
	}
	if (m_writeEvent != NULL) {
		BSLIB_SAFE_DELETE(m_writeEvent);
	}
#endif
}

bool CTcpEpoll::createEpoll()
{
#ifdef WIN32

	if (m_iocp != NULL){
		return false;
	}
	m_iocp = new CIOCP(1);
	if (m_iocp == NULL)	{
		return false;
	}
	if (m_readEvent == NULL) {
		m_readEvent = new SEpollEvent(EIOCP_OP_READ);
		if (m_readEvent == NULL) {
			return false;
		}
	}

	if (m_writeEvent == NULL) {
		m_writeEvent = new SEpollEvent(EIOCP_OP_WRITE);
		if (m_writeEvent == NULL) {
			return false;
		}
	}

#else

	if (m_epoll != NULL) {
		return false;
	}
	m_epoll = new CEPoll();
	if (m_epoll == NULL) {
		return false;
	}
	if (!m_epoll->create(BSLIB_NETWORK_EPOLL_MAX)) {
		BSLIB_SAFE_DELETE(m_epoll);
		return false;
	}

#endif
	return true;
}

void CTcpEpoll::releaseEpoll()
{
#ifdef WIN32

	if (m_iocp != NULL){
		m_iocp->close();
		BSLIB_SAFE_DELETE(m_iocp);
	}
	
#else

	if (m_epoll != NULL) {
		m_epoll->close();
		BSLIB_SAFE_DELETE(m_epoll);
	}

#endif

	m_socketEvents.clear();
}

bool CTcpEpoll::addTcpToEpoll(const SOCKET& tcpSocket, void* data)
{
#ifdef WIN32
	if (m_iocp == NULL){
		return false;
	}

	if (tcpSocket == INVALID_SOCKET) {
		return false;
	}

	if (m_socketEvents.find(tcpSocket) != m_socketEvents.end()) {
		return false;
	}

	if (!m_iocp->associateSocket(tcpSocket, tcpSocket)) {
		return false;
	}

	m_socketEvents.setValue(tcpSocket, data);

	return true;

#else

	if (m_epoll == NULL){
		return false;
	}

	if (tcpSocket == INVALID_SOCKET) {
		return false;
	}

	if (m_socketEvents.find(tcpSocket) != m_socketEvents.end()) {
		return false;
	}
	
	m_socketEvents.setValue(tcpSocket, data);
	
	if (!m_epoll->addEpollEvent(tcpSocket, EPOLLIN | EPOLLPRI | EPOLLERR| EPOLLET, (void*)tcpSocket)) {
		m_socketEvents.remove(tcpSocket);
		return false;
	}

	return true;

#endif
}

bool CTcpEpoll::delTcpFromEpoll(const SOCKET& tcpSocket)
{
#ifdef WIN32
	
	if (m_iocp == NULL){
		return false;
	}
	if (tcpSocket == INVALID_SOCKET) {
		return false;
	}

	m_socketEvents.remove(tcpSocket);
	return true;

#else

	if (m_epoll == NULL){
		return false;
	}

	if (tcpSocket == INVALID_SOCKET) {
		return false;
	}

	if (m_socketEvents.find(tcpSocket) != m_socketEvents.end()) {
		m_epoll->delEpollEvent(tcpSocket);
		m_socketEvents.remove(tcpSocket);
	}
	return true;

#endif
}

bool CTcpEpoll::epoll(int msSec)
{
#ifdef WIN32

	if (m_iocp == NULL) {
		return false;
	}
	SOCKET compKey = 0;
	DWORD numBytes = 0;
	SEpollEvent* epollEvent = NULL;

	bool result = m_iocp->getStatus((ULONG_PTR*)&compKey, &numBytes, &epollEvent, msSec);
	if (compKey == INVALID_SOCKET){
		return false;
	}
	if (!result) {
		if (GetLastError() == WAIT_TIMEOUT) {
			return true;
		}
		BSLib::Utility::CHashMap<SOCKET, void*>::iterator it = m_socketEvents.find(compKey);
		if (it == m_socketEvents.end()) {
			return true;
		}
		void* socketData = it->second;

		(*m_terminateScoket)(compKey, socketData);
		m_socketEvents.remove(compKey);

		return true;
	}
	BSLib::Utility::CHashMap<SOCKET, void*>::iterator it = m_socketEvents.find(compKey);
	if (it == m_socketEvents.end()) {
		return true;
	}

	void* socketData = it->second;

	if (epollEvent == NULL) {
		(*m_terminateScoket)(compKey, socketData);
		m_socketEvents.remove(compKey);
		return true;
	}
	//BSLIB_LOG_TRACE(ETT_BSLIB_NETWORK, "epoll socket[%d] type[%d]", compKey, epollEvent->m_type);
	switch(epollEvent->m_type)
	{
	case EIOCP_OP_READ:
		{
			//BSLIB_LOG_TRACE(ETT_BSLIB_NETWORK, "epoll socket[%d] read", compKey);
			if (m_readScoket != NULL) {
				if (!(*m_readScoket)(compKey, socketData)){
					if (m_terminateScoket != NULL) {
						(*m_terminateScoket)(compKey, socketData);
					}
					m_socketEvents.remove(compKey);
					break;
				}
				if(!notifyRecv(compKey, epollEvent)){
					if (m_terminateScoket != NULL) {
						(*m_terminateScoket)(compKey, socketData);
					}
					m_socketEvents.remove(compKey);
					break;
				}
			}
		}
		break;
	case EIOCP_OP_WRITE:
		{
			//BSLIB_LOG_TRACE(ETT_BSLIB_NETWORK, "epoll socket[%d] write", compKey);
			if (m_writeScoket != NULL) {
				if (!(*m_writeScoket)(compKey, socketData)){
					if (m_terminateScoket != NULL) {
						(*m_terminateScoket)(compKey, socketData);
					}
					m_socketEvents.remove(compKey);
					break;
				}
			}
		}
		break;
	case EIOCP_OP_ACCEPT:
		{
			//BSLIB_LOG_TRACE(ETT_BSLIB_NETWORK, "epoll socket[%d] accept", compKey);
			if (!epollAccept(compKey, epollEvent, socketData)) {
				if (m_terminateScoket != NULL) {
					(*m_terminateScoket)(compKey, socketData);
				}
				m_socketEvents.remove(compKey);
				break;
			}
			if(!notifyAccept(compKey, epollEvent)){
				if (m_terminateScoket != NULL) {
					(*m_terminateScoket)(compKey, socketData);
				}
				m_socketEvents.remove(compKey);
				break;
			}
		}
		break;
	default:
		{
			BSLIB_LOG_ERROR(ETT_BSLIB_NETWORK, "epoll socket[%d] type[%d]", compKey, epollEvent->m_type);
// 			if (m_terminateScoket != NULL) {
// 				(*m_terminateScoket)(compKey, socketData);
// 			}
// 			m_socketEvents.remove(compKey);
		}
		
	}

	return true;

#else

	if (m_epoll == NULL) {
		return false;
	}
	int count = m_epoll->wait(msSec);
	if (count < 0) {
		return false;
	}
	epoll_event* et = NULL;
	for (int i=0; i<count; ++i){
		et = m_epoll->getEpollEvent(i);
		if (et == NULL) {
			return false;
		}
		SOCKET tcpSocket = (long int)et->data.ptr;
		if(tcpSocket == INVALID_SOCKET){
			return false;
		}
		BSLib::Utility::CHashMap<SOCKET, void*>::iterator it = m_socketEvents.find(tcpSocket);
		if (it == m_socketEvents.end()) {
			m_epoll->delEpollEvent(tcpSocket);
			m_socketEvents.remove(tcpSocket);
			return true;
		}
		void* socketData = it->second;

		if (et->events & (EPOLLIN | EPOLLPRI)) {
			if (!(*m_readScoket)(tcpSocket, socketData)){
				(*m_terminateScoket)(tcpSocket, socketData);
				m_epoll->delEpollEvent(tcpSocket);
				m_socketEvents.remove(tcpSocket);
				break;
			}
		} else if (et->events & EPOLLOUT) {
			if (!m_epoll->modEpollEvent(tcpSocket, EPOLLIN | EPOLLPRI | EPOLLERR| EPOLLET, (void*)tcpSocket)) {
				(*m_terminateScoket)(tcpSocket, socketData);
				m_epoll->delEpollEvent(tcpSocket);
				m_socketEvents.remove(tcpSocket);
				break;
			}
			if (!(*m_writeScoket)(tcpSocket, socketData)){
				(*m_terminateScoket)(tcpSocket, socketData);
				m_epoll->delEpollEvent(tcpSocket);
				m_socketEvents.remove(tcpSocket);
				break;
			}
		} else {
			(*m_terminateScoket)(tcpSocket, socketData);
			m_epoll->delEpollEvent(tcpSocket);
			m_socketEvents.remove(tcpSocket);
		}
	}
	return true;

#endif
}

bool CTcpEpoll::postRecv(const SOCKET& tcpSocket)
{
#ifdef _WIN32
	if (!m_iocp->postStatus(tcpSocket, sizeof(SEpollEvent), m_readEvent)){
		return false;
	}
#endif
	return true;
}

bool CTcpEpoll::notifyRecv(const SOCKET& tcpSocket, void* a_para)
{
#ifdef _WIN32

	if (tcpSocket == INVALID_SOCKET) {
		return false;
	}

	DWORD flag = 0;
	int recvLen = 0;

	int recvRes = ::WSARecv(tcpSocket,  &m_readEvent->m_buffer, 1, (LPDWORD)&recvLen, &flag, (OVERLAPPED*)m_readEvent, NULL);
	if (recvRes < 0){
		int error = WSAGetLastError();
		if (!(error == WSAEWOULDBLOCK || error == WSAENOBUFS || error == ERROR_IO_PENDING)) {
			return false;
		}
	}
	return true;

#else

	return false;

#endif
}

bool CTcpEpoll::notifySend(const SOCKET& tcpSocket)
{
#ifdef _WIN32

	if (m_iocp == NULL) {
		return false;
	}

	return m_iocp->postStatus(tcpSocket, sizeof(SEpollEvent), m_writeEvent);

#else

	if (m_epoll == NULL) {
		return false;
	}
	return m_epoll->modEpollEvent(tcpSocket, EPOLLOUT | EPOLLERR| EPOLLET, (void*)tcpSocket);

#endif
}

void CTcpEpoll::setReadSocketFun(BSLib::Utility::CFunction<bool, SOCKET&, void*>& fun)
{
	if (m_readScoket != NULL) {
		BSLIB_SAFE_DELETE(m_readScoket);
	}
	m_readScoket = fun.clone();
}

void CTcpEpoll::setWriteSocketFun(BSLib::Utility::CFunction<bool, SOCKET&, void*>& fun)
{
	if (m_writeScoket != NULL) {
		BSLIB_SAFE_DELETE(m_writeScoket);
	}
	m_writeScoket = fun.clone();
}

void CTcpEpoll::setTerminateSocketFun(BSLib::Utility::CFunction<void, SOCKET&, void*>& fun)
{
	if (m_terminateScoket != NULL) {
		BSLIB_SAFE_DELETE(m_terminateScoket);
	}
	m_terminateScoket = fun.clone();
}

#ifdef _WIN32

bool CTcpEpoll::epollAccept(SOCKET& tcpSocket, void* a_para1, void* a_para2)
{
	SEpollEvent* epollEvent = (SEpollEvent*)a_para1;

	if(setsockopt(epollEvent->m_client, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, ( char* )&(tcpSocket), sizeof(tcpSocket) ) == SOCKET_ERROR) {
		return false;
	}

	if (!(*m_acceptScoket)(tcpSocket, epollEvent->m_client, a_para2)){
		return false;
	}
	return true;
}

bool CTcpEpoll::notifyAccept(const SOCKET& tcpSocket, void* a_para)
{
	LPFN_ACCEPTEX acceptExFun = NULL;     //AcceptExº¯ÊýÖ¸Õë
	GUID guidAcceptEx = WSAID_ACCEPTEX;
	DWORD dwBytes = 0;

	if(WSAIoctl(tcpSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidAcceptEx, sizeof(guidAcceptEx), &acceptExFun, sizeof(acceptExFun), &dwBytes, NULL,NULL) != 0){
		return false;
	}

	SEpollEvent* epollEvent = (SEpollEvent*)a_para;
	if (epollEvent == NULL) {
		epollEvent = (SEpollEvent*)GlobalAlloc(GPTR,sizeof(SEpollEvent));
		if (epollEvent == NULL) {
			return false;
		}
		epollEvent->clear();
	}
	epollEvent->m_type = EIOCP_OP_ACCEPT;
	epollEvent->m_client = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,0,0,WSA_FLAG_OVERLAPPED);
	if (epollEvent->m_client == INVALID_SOCKET) {
		return false;
	}
	epollEvent->m_dataLength = 0;
	dwBytes = 0;

	BOOL rc = acceptExFun(tcpSocket, epollEvent->m_client, epollEvent->m_dataBuffer, 0, sizeof(SOCKADDR_IN)+16, sizeof(SOCKADDR_IN)+16, &dwBytes, &(epollEvent->m_ol));
	if (rc == FALSE) {
		int error = WSAGetLastError();
		if (!(error == WSAEWOULDBLOCK || error == WSAENOBUFS || error == ERROR_IO_PENDING)) {
			return false;
		}
	}
	return true;
}

void CTcpEpoll::setAcceptSocketFun(BSLib::Utility::CFunction<bool, SOCKET&, SOCKET&, void*>& fun)
{
	if (m_acceptScoket != NULL) {
		BSLIB_SAFE_DELETE(m_acceptScoket);
	}
	m_acceptScoket = fun.clone();
}

#endif

}//Network

}//BSLib

