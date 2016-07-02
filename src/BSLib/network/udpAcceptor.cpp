#include <BSLib/udm/udm.h>
#include <BSLib/network/udpAcceptor.h>

namespace BSLib
{

namespace Network
{

CUdpAcceptor::CUdpAcceptor()
: m_udmEpollID(-1)
{
	m_udmEpollID = BSLib::UDM::epollCreate();
}

CUdpAcceptor::~CUdpAcceptor()
{
	if (m_udmEpollID != -1) {
		BSLib::UDM::epollRelease(m_udmEpollID);
		m_udmEpollID = -1;
	}
}

bool CUdpAcceptor::waitSocket(int msSec)
{
	BSLib::UDM::SEpollEvent epollEvent[256];
	int udmCount = BSLib::UDM::epollWait(m_udmEpollID, epollEvent, 256, msSec);
	if (udmCount == 0) {
		return true;
	} else if (udmCount < 0) {
		return false;
	}
	for (int i=0; i<udmCount; ++i){
		if (epollEvent[i].m_udmEpollEvent & BSLib::UDM::UDM_EPOLL_READ) {
			if(epollEvent[i].m_udmSocket != INVALID_UDMSOCK){
				if(!_newScoket(epollEvent[i].m_udmSocket)){
					_terminateScoket(epollEvent[i].m_udmSocket);
				}
			}
		}
		if (epollEvent[i].m_udmEpollEvent & BSLib::UDM::UDM_EPOLL_ERROR) {
			if(epollEvent[i].m_udmSocket != INVALID_UDMSOCK){
				_terminateScoket(epollEvent[i].m_udmSocket);
			}
		}
	}
	return true;
}

bool CUdpAcceptor::_INetAcceptor_addAcceptor(SAcceptorItemPtr& item)
{
	sockaddr_in* addrListen = (sockaddr_in*)item->m_addrAcceptor;
	UDMSOCKET sock = BSLib::UDM::socket();
	if (sock == INVALID_UDMSOCK){
		return false;
	}

	if (BSLib::UDM::bind(sock, (sockaddr*)addrListen, sizeof(sockaddr_in)) == BSLIB_UDM_ERROR) {
		BSLib::UDM::close(sock);
		return false;
	}
	if (BSLib::UDM::listen(sock) == BSLIB_UDM_ERROR) {
		BSLib::UDM::close(sock);
		return false;
	}

	BSLib::UDM::epollAddSock(m_udmEpollID, sock, BSLib::UDM::UDM_EPOLL_READ | BSLib::UDM::UDM_EPOLL_ERROR, NULL);
	item->m_sockID = sock;
	m_udmHashMap.setValue(sock, item);
	return true;
}

bool CUdpAcceptor::_INetAcceptor_delAcceptor(SAcceptorItemPtr& item)
{
	if (m_udmEpollID != -1) {
		BSLib::UDM::epollDelSock((int)m_udmEpollID, (int)item->m_sockID, BSLib::UDM::UDM_EPOLL_READ | BSLib::UDM::UDM_EPOLL_ERROR);
	}
	BSLib::UDM::close((int)item->m_sockID);
	item->m_sockID = INVALID_SOCKET;
	m_udmHashMap.remove((int)item->m_sockID);
	return true;
}

bool CUdpAcceptor::_newScoket(int udpSocket)
{
	SAcceptorItemPtr acceptor = NULL;
	if (!m_udmHashMap.getValue(udpSocket, acceptor)) {
		return false;
	}
	if (acceptor == NULL || acceptor->m_cbNewConnection == NULL){
		return false;
	}
	CSockAddr sockPeerAddr;
	int sockAddrLen = sizeof(sockaddr);
	UDMSOCKET sockPeer = BSLib::UDM::accept(udpSocket, (sockaddr*)sockPeerAddr, &sockAddrLen);
	if (sockPeer == INVALID_UDMSOCK){
		return true;
	}
	sockPeerAddr.setIP();

	if (!acceptor->m_cbNewConnection->newConnect(sockPeer, acceptor->m_addrAcceptor, sockPeerAddr, acceptor->m_tempData)){
		BSLib::UDM::close(sockPeer);
	}
	return true;
}

void CUdpAcceptor::_terminateScoket(int udpSocket)
{
	SAcceptorItemPtr acceptor = NULL;
	if (!m_udmHashMap.getValue(udpSocket, acceptor)) {
		return ;
	}
	if (acceptor == NULL){
		return ;
	}
	_INetAcceptor_delAcceptor(acceptor);
}

}//Network

}//BSLib


