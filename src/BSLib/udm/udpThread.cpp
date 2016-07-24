#ifdef WIN32

#include "sockEvent.hpp"

#else

#include <fcntl.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include "epoll.h"

#endif

#include "udpThread.h"
#include "udmStub.h"
//#include <BSLib/utility/tracer.h>

#define BSLIB_UDM_UDP_WAIT_TIME  10
#define	BSLIB_UDM_EPOLL_MAX 1

namespace BSLib
{

namespace UDM
{

const int g_udpBufferSize = 256*1024;

#ifdef WIN32

CUdpThread::CUdpThread(int udpThreadID)
: m_sysSocket(INVALID_SOCKET)
, m_socketEvent(NULL)
, m_isRunning(false)
, m_beginAccept(false)
, m_acceptor(NULL)
, m_udpThreadID(udpThreadID)
{
	memset(&m_localAddr, 0, sizeof(sockaddr_in));
	m_socketEvent = new CSocketEvent();
}

#else

CUdpThread::CUdpThread(int udpThreadID)
: m_sysSocket(INVALID_SOCKET)
, m_epoll(NULL)
, m_isRunning(false)
, m_beginAccept(false)
, m_acceptor(NULL)
, m_udpThreadID(udpThreadID)
{
	m_epoll = new CEPoll();
	if (m_epoll != NULL) {
		m_epoll->create(BSLIB_UDM_EPOLL_MAX);
	}
}

#endif	


CUdpThread::~CUdpThread()
{
#ifdef WIN32
	if (m_socketEvent != NULL) {
		BSLIB_SAFE_DELETE(m_socketEvent);
	}
#endif
}

bool CUdpThread::compareLocalAddr(const struct sockaddr* name, int namelen)
{
	sockaddr_in* localAddr = (sockaddr_in*)name;
	if (sizeof(sockaddr_in) != namelen) {
		return false;
	}
	if (localAddr->sin_port != m_localAddr.sin_port) {
		return false;
	}
	if (localAddr->sin_addr.s_addr != m_localAddr.sin_addr.s_addr) {
		return false;
	}
	return true;
}

bool CUdpThread::socket()
{
	return _socket(NULL, 0);
}

int CUdpThread::sendTo(SUdpCtrlMsg* msg, int msgLen, const struct sockaddr* peerName, int peerNameLen)
{
	if (m_sysSocket == INVALID_SOCKET) {
		return false;
	}

#ifdef WIN32
	
	int sendLen = ::sendto(m_sysSocket, (const char*)msg, msgLen, 0, peerName, peerNameLen);

#else

	int sendLen = ::sendto(m_sysSocket, (const char*)msg, msgLen, MSG_DONTWAIT, peerName, peerNameLen);

#endif

	if (sendLen == msgLen) {
		//sockaddr_in* peerSockAddPtr = (sockaddr_in*)peerName;
		//printf("msg[%d]-----[%d]----->[%s:%d]\n", msg->getMsgID(), msgLen, inet_ntoa(peerSockAddPtr->sin_addr), ntohs(peerSockAddPtr->sin_port));
		return sendLen;
	}
	return UDM_EPOLL_ERROR;
}

void CUdpThread::getAcceptInfo(BSLib::Utility::CEvent*& e, BSLib::Utility::CPtrQueue<CUdmSocket*>*& acceptList)
{
	e = &m_acceptEvent;
	acceptList = &m_acceptList;
}

void CUdpThread::getLocalAddr(sockaddr* name, int* namelen) 
{
	if (m_sysSocket == INVALID_SOCKET) {
		return;
	}
	*namelen = (int)sizeof(sockaddr_in);

#ifdef WIN32

	::getsockname(m_sysSocket, (sockaddr*)&m_localAddr, namelen);

#else

	::getsockname(m_sysSocket, (sockaddr*)&m_localAddr, (socklen_t*)namelen);

#endif
	
	*name = *((sockaddr*)&m_localAddr);  
}

bool CUdpThread::socket(const struct sockaddr* name, int namelen)
{
	return _socket(name, namelen);
}

void CUdpThread::addUdmAcceptor(CUdmAcceptor* udmAcceptor)
{
	m_acceptor = udmAcceptor;

	m_mutex.lock();
	m_addUdmClientList.push_back(udmAcceptor);
	m_mutex.unlock();
}

void CUdpThread::addUdmClient(CUdmClient* udmClient)
{
	m_mutex.lock();
	m_addUdmClientList.push_back(udmClient);
	m_mutex.unlock();
}

bool CUdpThread::addUdmStub(CUdmStub* udmStub)
{
	if (!m_beginAccept) {
		if (!m_acceptList.empty()) {
			m_acceptList.clear();
		}
		return false;
	}
	
	m_acceptList.push(udmStub);
	m_acceptEvent.set();
	
	if (m_acceptor != NULL) {
		m_acceptor->notifyRead();
	}

	return true;
}

void CUdpThread::_run()
{
	BSLib::Utility::CDelayTimer delayTimer(25, m_realTime);
	int group = 0;

	m_realTime.now();
	delayTimer.reset(50, m_realTime);

	m_isRunning = true;
	while (m_isRunning){
#ifdef WIN32
		SYSSOCKET sysSocket = INVALID_SOCKET;
		long e = 0;
		if (!m_socketEvent->waitSocket(sysSocket, e, BSLIB_UDM_UDP_WAIT_TIME)) {
			m_realTime.now();
			_checkUdmClient();
			if (delayTimer(m_realTime)){
				_tickUdpPeer(group);
				group = (group + 1) % BSLIB_UDM_UDP_GROUP;
			}
			continue;
		}
		m_realTime.now();
		_checkUdmClient();
		if(sysSocket == INVALID_SOCKET){
			continue;
		}
		if (!(e & FD_READ)) {
			continue;
		}
		if (!_recv(sysSocket)) {
			continue;
		}
		if (delayTimer(m_realTime)){
			_tickUdpPeer(group);
			group = (group + 1) % BSLIB_UDM_UDP_GROUP;
		}

#else

		int count = m_epoll->wait(BSLIB_UDM_UDP_WAIT_TIME);
		if (count < 0) {
			break;
		}

		m_realTime.now();
		_checkUdmClient();

		epoll_event* et = NULL;
		for (int i=0; i<count; ++i){
			et = m_epoll->getEpollEvent(i);
			if (et == NULL) {
				continue;
			}
			SOCKET tcpSocket = (long int)et->data.ptr;
			if(tcpSocket == INVALID_SOCKET){
				continue;
			}
			if (!_recv(tcpSocket)) {
				continue;
			}
		}
		if (delayTimer(m_realTime)){
			_tickUdpPeer(group);
			group = (group + 1) % BSLIB_UDM_UDP_GROUP;
		}

#endif	
	}
	m_isRunning = false;
}

void CUdpThread::_tickUdpPeer(int group)
{
	std::list<CUdmSocket*>::iterator it = m_groups[group].begin();
	for (; it != m_groups[group].end();){
		CUdmSocket* udmSocket = *it;
		if (udmSocket != NULL) {
			SUdmSocketInfo* udmSocketInfo = udmSocket->getUdmSocketInfo();
			if (udmSocketInfo->m_udmStatus == UDM_STATE_NONEXIST) {
				_delUdpSocket(udmSocket);
				udmSocketInfo->m_udmStatus = UDM_STATE_DELETE1;
			}
			if (udmSocketInfo->m_udmStatus == UDM_STATE_DELETE2){	
				it = m_groups[group].erase(it);
				udmSocketInfo->m_udmSocketPtr = NULL;
				udmSocketInfo->m_udmStatus = UDM_STATE_NULL;
				if (udmSocketInfo->m_udmID == INVALID_SOCKET) {
					BSLIB_SAFE_DELETE(udmSocketInfo);
				}
				BSLIB_SAFE_DELETE(udmSocket);
				continue;
			}
			udmSocket->tickMsg(m_realTime);
		}
		++it;
	}
}

bool CUdpThread::_recv(SYSSOCKET sysSocket)
{
	sockaddr peerSockAddr;
	char buff[BSLIB_UDM_UDP_BUFF_MAX];
	int recvLen = 0;

	do {
#ifdef WIN32

		int addrLen = sizeof(sockaddr);
		recvLen = ::recvfrom(sysSocket, buff, BSLIB_UDM_UDP_BUFF_MAX, 0, &peerSockAddr, &addrLen);
		if (recvLen == SOCKET_ERROR) {
			int error = ::WSAGetLastError();
			if (error == WSAEWOULDBLOCK || error == ERROR_IO_PENDING || error == WSAENOBUFS) {
				return true;
			}
			return false;
		}

#else

		socklen_t addrLen = sizeof(sockaddr);
		recvLen = ::recvfrom(sysSocket, buff, BSLIB_UDM_UDP_BUFF_MAX, MSG_DONTWAIT, &peerSockAddr, &addrLen);
		if (recvLen == SOCKET_ERROR) {
			if (errno == EAGAIN || errno == EWOULDBLOCK || errno == ENOBUFS) {
				return true;
			}
			return false;
		}

#endif
		
		if (recvLen == 0) {
			return false;
		}

		//sockaddr_in* peerSockAddPtr = (sockaddr_in*)&peerSockAddr;
		//BSLIB_LOG_DEBUG(BSLib::ETT_BSLIB_P2PSERVER, "<--------[%s:%d][%d]", inet_ntoa(peerSockAddPtr->sin_addr), ntohs(peerSockAddPtr->sin_port), recvLen);

		SUdpCtrlMsg* msg = (SUdpCtrlMsg*)buff;
		if (msg->isCtrlMsg()) {
			CUdmSocket* udpPeer = _getUdpSocket(&peerSockAddr);
			if (udpPeer == NULL) {
				if (msg->getMsgID() != EMID_PC2PS_REQ_CONNECT){
					continue;
				}
				udpPeer = _createUdpSocket(&peerSockAddr);
				if (udpPeer == NULL) {
					continue;
				}
			}
			udpPeer->parseCtrlMsg(msg, recvLen, m_realTime);
			continue;
		}
		if (msg->isDataMsg()) {
			CUdmSocket* udpPeer = _getUdpSocket(&peerSockAddr);
			if (udpPeer != NULL) {
				udpPeer->parseDataMsg(msg, recvLen, m_realTime);
			}
		}
	} while (recvLen > 0);
	return true;
}

CUdmSocket* CUdpThread::_getUdpSocket(sockaddr* peerSockAddr)
{
	uint64 key = 0;
	CUdmSocket* udpPeer = NULL;
	sockaddr_in* ptrAddr = (sockaddr_in*)peerSockAddr;

 	key = BSLIB_HI_SHIFT((uint64)ptrAddr->sin_addr.s_addr, 32) + ptrAddr->sin_port;
	if (!m_udpPeerBySockAddr.getValue(key, udpPeer)) {
		return NULL;
	}
	return udpPeer;
}

CUdmSocket* CUdpThread::_createUdpSocket(sockaddr* peerSockAddr)
{
	if (!m_beginAccept){
		return NULL;
	}
	SUdmSocketInfo* udmSocketInfo = new SUdmSocketInfo();
	if (udmSocketInfo == NULL)	{
		return NULL;
	}
	udmSocketInfo->m_udmID = INVALID_UDMSOCK;
	udmSocketInfo->m_udmStatus = UDM_STATE_INIT;
	udmSocketInfo->m_udpThreadID = m_udpThreadID;
	CUdmStub* udmStub = new CUdmStub(udmSocketInfo, m_realTime);
	if (udmStub == NULL){
		BSLIB_SAFE_DELETE(udmSocketInfo);
		return NULL;
	}
	udmStub->setPeerName(peerSockAddr, sizeof(sockaddr));
	udmSocketInfo->m_udmSocketPtr = udmStub;

	_addUdpSocket(udmStub);

	return udmStub;
}

void CUdpThread::_addUdpSocket(CUdmSocket* udmSocket)
{
	uint64 key = 0;
	sockaddr_in peerAddr;
	int addrLen = sizeof(sockaddr_in);
	udmSocket->getPeerName((sockaddr*)&peerAddr, &addrLen);

	key = BSLIB_HI_SHIFT((uint64)peerAddr.sin_addr.s_addr, 32) + peerAddr.sin_port;
	if (m_udpPeerBySockAddr.find(key) != m_udpPeerBySockAddr.end()) {
		return;
	}
	m_udpPeerBySockAddr.setValue(key, udmSocket);

	int minCount = (int)m_groups[0].size();
	int pos = 0;
	for (int i=1; i<BSLIB_UDM_UDP_GROUP; ++i) {
		int tmpCount = (int)m_groups[i].size();
		if (tmpCount < minCount){
			pos = i;
			minCount = tmpCount; 
		}
	}
	m_groups[pos].push_back(udmSocket);
}

void CUdpThread::_delUdpSocket(CUdmSocket* udmSocket)
{
	uint64 key = 0;
	sockaddr_in peerAddr;
	int len = sizeof(sockaddr_in);
	udmSocket->getPeerName((sockaddr*)&peerAddr, &len);

	key = BSLIB_HI_SHIFT((uint64)peerAddr.sin_addr.s_addr, 32) + peerAddr.sin_port;
	m_udpPeerBySockAddr.remove(key);
}

bool CUdpThread::_socket(const struct sockaddr* name, int namelen)
{
#ifdef WIN32

	SOCKET udpSocket = ::WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);  

#else

	SOCKET udpSocket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

#endif
	if (udpSocket == INVALID_SOCKET) {
		return false;
	}

	if (name != NULL) {
		if (SOCKET_ERROR == ::bind(udpSocket, name, namelen)) {
			
#ifdef WIN32

			::closesocket(udpSocket); 

#else

			::shutdown(udpSocket, SHUT_RDWR);
			::close(udpSocket);

#endif

			return false;
		}
	}

	uint32 reuserAddr = 1;
	setsockopt(udpSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuserAddr , sizeof(uint32));

	::setsockopt(udpSocket, SOL_SOCKET, SO_RCVBUF, (char*)&g_udpBufferSize, sizeof(g_udpBufferSize));
	::setsockopt(udpSocket, SOL_SOCKET, SO_SNDBUF, (char*)&g_udpBufferSize, sizeof(g_udpBufferSize));

	//uint32 nodelay = 1;
	//::setsockopt(udpSocket, SOL_SOCKET, TCP_NODELAY, (char*)&nodelay, sizeof(nodelay));

#ifdef WIN32

	unsigned long flag=1;
	ioctlsocket(udpSocket, FIONBIO, &flag);

	m_sysSocket = udpSocket;
	if (name != NULL) {
		m_localAddr = *(sockaddr_in*)name;
	}
	m_socketEvent->addSocket(m_sysSocket, FD_READ);

#else

	int flag = ::fcntl(udpSocket, F_GETFL, 0);
#if defined(O_NONBLOCK)
	flag |= O_NONBLOCK;
#elif defined(O_NDELAY)
	flag |= O_NDELAY;
#elif defined(O_FNDELAY)
	flag |= O_FNDELAY;
#endif
	::fcntl(udpSocket, F_SETFL, flag);

	m_sysSocket = udpSocket;
	if (name != NULL) {
		m_localAddr = *(sockaddr_in*)name;
	}
	m_epoll->addEpollEvent(m_sysSocket, EPOLLIN | EPOLLET, (void*)m_sysSocket);

#endif
	
	return true;
}

void CUdpThread::_checkUdmClient()
{
	if (m_addUdmClientList.size()) {
		m_mutex.lock();

		for (uint32 i=0; i<m_addUdmClientList.size(); ++i){
			CUdmSocket* udmClient = m_addUdmClientList[i];
			if (udmClient == NULL){
				continue;
			}
			_addUdpSocket(udmClient);
		}
		m_addUdmClientList.clear();

		m_mutex.unlock();
	}
}

}//UDM

}//BSLib


