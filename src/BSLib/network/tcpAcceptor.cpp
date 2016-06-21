#ifdef WIN32

#include "sockEvent.hpp"
#include "netinit.h"

#else

#include <fcntl.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include "epoll.h"

#endif

#include "tcpEpoll.h"
#include <BSLib/network/tcpAcceptor.h>
#include <BSLib/utility/tracer.h>

namespace BSLib
{

namespace Network
{

int g_tcpBufferSize = 16*1024;
#define BSLIB_NETWORK_EPOLL_MAX 256


#ifdef WIN32

CTcpAcceptor::CTcpAcceptor()
: m_tcpEpoll(NULL)
{
	CNetInit::singleton();
	m_tcpEpoll = new CTcpEpoll();
	if (m_tcpEpoll != NULL) {
		if (m_tcpEpoll->createEpoll()) {
			BSLib::Utility::CFunctionObject<bool, CTcpAcceptor, SOCKET&, SOCKET&, void*> acceptSockeFun(&CTcpAcceptor::_acceptScoket, this);
			m_tcpEpoll->setAcceptSocketFun(acceptSockeFun);

			BSLib::Utility::CFunctionObject<void, CTcpAcceptor, SOCKET&, void*> terminateSocketFun(&CTcpAcceptor::_terminateScoket, this);
			m_tcpEpoll->setTerminateSocketFun(terminateSocketFun);
		}
	}
}

CTcpAcceptor::~CTcpAcceptor()
{
	if (m_tcpEpoll){
		BSLIB_SAFE_DELETE(m_tcpEpoll);
	}
}

bool CTcpAcceptor::waitSocket(int msSec)
{
	if (m_tcpEpoll == NULL) {
		return false;
	}
	return m_tcpEpoll->epoll(msSec);
}

bool CTcpAcceptor::_addAcceptor(CNetAcceptor::SAcceptorItemPtr& item)
{
	sockaddr_in* addrListen = (sockaddr_in*)item->m_addrAcceptor;
	SOCKET sock = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);  

	if (sock == INVALID_SOCKET){
		return 0;
	}

	if (::bind(sock, (sockaddr*)addrListen, sizeof(sockaddr_in)) < 0) {
		::closesocket(sock);
		return false;
	}
	if (::listen(sock, 4096) < 0) {
		::closesocket(sock);
		return false;
	}

	unsigned long flag=1;
	ioctlsocket(sock, FIONBIO, &flag);

	item->m_sockID = sock;
	m_tcpHashMap.setValue(sock, item);

	if (!m_tcpEpoll->addTcpToEpoll(sock, this)) {
		m_tcpHashMap.remove(sock);
		return false;
	}
	m_tcpEpoll->notifyAccept(sock, NULL);

	return true;
}

bool CTcpAcceptor::_delAcceptor(CNetAcceptor::SAcceptorItemPtr& item)
{
	::closesocket(item->m_sockID);
	item->m_sockID = INVALID_SOCKET;
	m_tcpHashMap.remove(item->m_sockID);
	return true;
}

bool CTcpAcceptor::_acceptScoket(SOCKET& a_tcpServerSocket, SOCKET& a_tcpPeerSocket, void* a_data)
{
	SAcceptorItemPtr& acceptor = m_tcpHashMap.getValue(a_tcpServerSocket); 
	if (acceptor == NULL || acceptor->m_cbNewConnection == NULL){
		BSLIB_LOG_ERROR(ETT_BSLIB_NETWORK, "AcceptScoket[%d]", a_tcpPeerSocket);
		return false;
	}
	CSockAddr sockPeerAddr;
	int sockAddrLen = sizeof(sockaddr);
	if (0 != getpeername(a_tcpPeerSocket, (sockaddr*)sockPeerAddr, &sockAddrLen)){
		BSLIB_LOG_ERROR(ETT_BSLIB_NETWORK, "getpeername[%d]", a_tcpPeerSocket);
		return false;
	}
	sockPeerAddr.setIP();

	uint32 reuserAddr = 1;
	::setsockopt(a_tcpPeerSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuserAddr , sizeof(uint32));

	::setsockopt(a_tcpPeerSocket, SOL_SOCKET, SO_RCVBUF, (char*)&g_tcpBufferSize, sizeof(g_tcpBufferSize));
	::setsockopt(a_tcpPeerSocket, SOL_SOCKET, SO_SNDBUF, (char*)&g_tcpBufferSize, sizeof(g_tcpBufferSize));

// 	uint32 nodelay = 1;
// 	::setsockopt(a_tcpPeerSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&nodelay , sizeof(nodelay));
// 	::setsockopt(a_tcpPeerSocket, SOL_SOCKET, TCP_NODELAY, (char*)&nodelay , sizeof(nodelay));
// 
// 	unsigned long flag=1;
// 	ioctlsocket(a_tcpPeerSocket, FIONBIO, &flag);

	if (!acceptor->m_cbNewConnection->newConnect((int)a_tcpPeerSocket, acceptor->m_addrAcceptor, sockPeerAddr, acceptor->m_tempData)){
		BSLIB_LOG_ERROR(ETT_BSLIB_NETWORK, "new connect[%d][%s:%d] error", a_tcpPeerSocket, sockPeerAddr.getIP().c_str(), sockPeerAddr.getPort());
		return false;
	}
	return true;
}

void CTcpAcceptor::_terminateScoket(SOCKET& tcpSocket, void* data)
{
	BSLIB_LOG_ERROR(ETT_BSLIB_NETWORK, "TerminateScoket[%d]", tcpSocket);

	SAcceptorItemPtr& acceptor = m_tcpHashMap.getValue(tcpSocket); 
	if (acceptor == NULL){
		return ;
	}
	_delAcceptor(acceptor);
}

#else//WIN32

CTcpAcceptor::CTcpAcceptor()
: m_epoll(NULL)
{
	m_epoll = new CEPoll();
	if (m_epoll != NULL) {
		m_epoll->create(BSLIB_NETWORK_EPOLL_MAX);
	}
}

CTcpAcceptor::~CTcpAcceptor()
{
	if (m_epoll != NULL) {
		m_epoll->close();
		BSLIB_SAFE_DELETE(m_epoll);
	}
}

bool CTcpAcceptor::waitSocket(int msSec)
{
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
		if(!_newScoket(tcpSocket)){
			_terminateScoket(tcpSocket);
		}
	}
	return true;
}

bool CTcpAcceptor::_addAcceptor(CNetAcceptor::SAcceptorItemPtr& item)
{
	sockaddr_in* addrListen = (sockaddr_in*)item->m_addrAcceptor;
	SOCKET sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock == INVALID_SOCKET){
		return 0;
	}

	if (::bind(sock, (sockaddr*)addrListen, sizeof(sockaddr_in)) < 0) {
		::closesocket(sock);
		return false;
	}
	if (::listen(sock, 24) < 0) {
		::closesocket(sock);
		return false;
	}
	
	int flag = ::fcntl(sock, F_GETFL, 0);
	flag |= O_NONBLOCK;
	::fcntl(sock, F_SETFL, flag);

	item->m_sockID = sock;
	m_tcpHashMap.setValue(sock, item);

	if (!m_epoll->addEpollEvent(sock, EPOLLIN | EPOLLET, (void*)sock)) {
		m_tcpHashMap.remove(sock);
		return false;
	}

	return true;
}

bool CTcpAcceptor::_delAcceptor(CNetAcceptor::SAcceptorItemPtr& item)
{
	if (m_epoll != NULL) {
		m_epoll->delEpollEvent(item->m_sockID);
	}
	::closesocket(item->m_sockID);
	item->m_sockID = INVALID_SOCKET;
	m_tcpHashMap.remove(item->m_sockID);
	return true;
}



bool CTcpAcceptor::_newScoket(SOCKET tcpSocket)
{
	SAcceptorItemPtr& acceptor = m_tcpHashMap.getValue(tcpSocket); 
	if (acceptor == NULL || acceptor->m_cbNewConnection == NULL){
		return false;
	}
	CSockAddr sockPeerAddr;
	SOCKET sockPeer = INVALID_SOCKET;
	int sockAddrLen = sizeof(sockaddr);
	do {
		sockPeer = ::accept(tcpSocket, (sockaddr*)sockPeerAddr, (socklen_t*)&sockAddrLen);
		if (sockPeer == INVALID_SOCKET){
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				return true;
			}
			return false;
		}
		sockPeerAddr.setIP();

		uint32 reuserAddr = 1;
		::setsockopt(sockPeer, SOL_SOCKET, SO_REUSEADDR, (char*)&reuserAddr , sizeof(uint32));

		::setsockopt(sockPeer, SOL_SOCKET, SO_RCVBUF, (char*)&g_tcpBufferSize, sizeof(g_tcpBufferSize));
		::setsockopt(sockPeer, SOL_SOCKET, SO_SNDBUF, (char*)&g_tcpBufferSize, sizeof(g_tcpBufferSize));

// 		uint32 nodelay = 1;
// 		::setsockopt(sockPeer, IPPROTO_TCP, TCP_NODELAY, (char*)&nodelay , sizeof(nodelay));
// 		::setsockopt(sockPeer, SOL_SOCKET, TCP_NODELAY, (char*)&nodelay , sizeof(nodelay));

		int flag = ::fcntl(sockPeer, F_GETFL, 0);
		flag |= O_NONBLOCK;
		::fcntl(sockPeer, F_SETFL, flag);

		if (!acceptor->m_cbNewConnection->newConnect(sockPeer, acceptor->m_addrAcceptor, sockPeerAddr, acceptor->m_tempData)){
			::closesocket(sockPeer);
		}
	} while (true);
	
	return true;
}

void CTcpAcceptor::_terminateScoket(SOCKET tcpSocket)
{
	SAcceptorItemPtr& acceptor = m_tcpHashMap.getValue(tcpSocket); 
	if (acceptor == NULL){
		return ;
	}
	_delAcceptor(acceptor);
}

#endif//WIN32



}//Network

}//BSLib


