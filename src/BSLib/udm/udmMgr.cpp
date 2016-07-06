#include <BSLib/utility/thread/threadData.h>
#include "udmMgr.h"
#include "udmError.h"
#include "udpThreadMgr.h"
#include "udmClient.h"
#include "udmAcceptor.h"

namespace BSLib
{

namespace UDM
{

BSLib::Utility::CThreadData g_errorData;

BSLIB_SINGLETON_DEFINE(CUdmMgr);

CUdmMgr::CUdmMgr()
: m_currtUdmSocketInforPos(0)
{
	_startUp();
	for (int i=0; i<BSLIB_UDM_SOCKET_MAX; ++i){
		m_udpSocketInfor[i] = NULL;
	}
}

CUdmMgr::~CUdmMgr()
{
	for (int i=0; i<BSLIB_UDM_SOCKET_MAX; ++i){
		if (m_udpSocketInfor[i] != NULL) {
			if (m_udpSocketInfor[i]->m_udmEpollInfo != NULL) {
				BSLIB_SAFE_DELETE(m_udpSocketInfor[i]->m_udmEpollInfo);
			}
			if (m_udpSocketInfor[i]->m_udmSocketPtr != NULL) {
				BSLIB_SAFE_DELETE(m_udpSocketInfor[i]->m_udmSocketPtr);
			}
			BSLIB_SAFE_DELETE(m_udpSocketInfor[i]);
		}
	}
	_cleanUp();
	
}

UDMSOCKET CUdmMgr::udmSocket()
{
	SUdmSocketInfo* udmSocketInfor = NULL;

	m_mutex.lock();
	for (int i=0; i<BSLIB_UDM_SOCKET_MAX; ++i){
		if (m_udpSocketInfor[m_currtUdmSocketInforPos] == NULL) {
			udmSocketInfor = new SUdmSocketInfo();
			if (udmSocketInfor == NULL) {
				m_mutex.unlock();
				setlasterror(UDM_ERROR_OUT_OF_MEMORY);
				return INVALID_UDMSOCK;
			}
			udmSocketInfor->m_udmID = m_currtUdmSocketInforPos + 1;
			udmSocketInfor->m_udmStatus = UDM_STATE_INIT;
			udmSocketInfor->m_udpThreadID = -1;
			udmSocketInfor->m_udmSocketPtr = NULL;
			m_udpSocketInfor[m_currtUdmSocketInforPos] = udmSocketInfor;

			m_currtUdmSocketInforPos = (m_currtUdmSocketInforPos + 1) % BSLIB_UDM_SOCKET_MAX;
			break;
		} else if (m_udpSocketInfor[m_currtUdmSocketInforPos]->m_udmStatus == UDM_STATE_NULL) {
			udmSocketInfor = m_udpSocketInfor[m_currtUdmSocketInforPos];
			udmSocketInfor->m_udmID = m_currtUdmSocketInforPos + 1;
			udmSocketInfor->m_udmStatus = UDM_STATE_INIT;
			udmSocketInfor->m_udpThreadID = -1;
			udmSocketInfor->m_udmSocketPtr = NULL;

			m_currtUdmSocketInforPos = (m_currtUdmSocketInforPos + 1) % BSLIB_UDM_SOCKET_MAX;
			break;
		}

		m_currtUdmSocketInforPos = (m_currtUdmSocketInforPos + 1) % BSLIB_UDM_SOCKET_MAX;
	}
	m_mutex.unlock();

	if (udmSocketInfor == NULL) {
		setlasterror(UDM_ERROR_OUT_OF_UDMSOCKID);
		return INVALID_UDMSOCK;
	}
	return udmSocketInfor->m_udmID;
}

UDMSOCKET CUdmMgr::udmSocket(SUdmSocketInfo* udmSocketInfor)
{
	m_mutex.lock();
	for (int i=0; i<BSLIB_UDM_SOCKET_MAX; ++i){
		if (m_udpSocketInfor[m_currtUdmSocketInforPos] == NULL) {
			udmSocketInfor->m_udmID = m_currtUdmSocketInforPos + 1;
			m_udpSocketInfor[m_currtUdmSocketInforPos] = udmSocketInfor;
			m_currtUdmSocketInforPos = (m_currtUdmSocketInforPos + 1) % BSLIB_UDM_SOCKET_MAX;
			break;
		} else if (m_udpSocketInfor[m_currtUdmSocketInforPos]->m_udmStatus == UDM_STATE_NULL) {
			BSLIB_SAFE_DELETE(m_udpSocketInfor[m_currtUdmSocketInforPos]);

			udmSocketInfor->m_udmID = m_currtUdmSocketInforPos + 1;
			m_udpSocketInfor[m_currtUdmSocketInforPos] = udmSocketInfor;
			m_currtUdmSocketInforPos = (m_currtUdmSocketInforPos + 1) % BSLIB_UDM_SOCKET_MAX;
			break;
		}
		m_currtUdmSocketInforPos = (m_currtUdmSocketInforPos + 1) % BSLIB_UDM_SOCKET_MAX;
	}
	m_mutex.unlock();

	return udmSocketInfor->m_udmID;
}

int CUdmMgr::bind(UDMSOCKET udmID, const struct sockaddr* name, int namelen)
{
	if (udmID <= 0 || udmID > BSLIB_UDM_SOCKET_MAX) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKID);
		return BSLIB_UDM_ERROR;
	}
	int udmPos = udmID - 1;
	SUdmSocketInfo* udmSocketInfor = m_udpSocketInfor[udmPos];
	if (udmSocketInfor == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCK);
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfor->m_udmStatus != UDM_STATE_INIT) {
		setlasterror(UDM_ERROR_INVALID_STATE);
		return BSLIB_UDM_ERROR;
	}
	int udpThreadID = CUdpThreadMgr::singleton().getUdpThreadID(name, namelen);
	if (udpThreadID == -1) {
		if (!CUdpThreadMgr::singleton().bind(udpThreadID, name, namelen)) {
			setlasterror(UDM_ERROR_BIND_UDPADDR);
			return BSLIB_UDM_ERROR;
		}
	}
	udmSocketInfor->m_udpThreadID = udpThreadID;
	udmSocketInfor->m_udmStatus = UDM_STATE_BIND;
	return BSLIB_UDM_OK;
}

int CUdmMgr::bind(UDMSOCKET udmID, UDMSOCKET existUdmId)
{
	if (udmID <= 0 || udmID > BSLIB_UDM_SOCKET_MAX) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKID);
		return BSLIB_UDM_ERROR;
	}
	int udmPos = udmID - 1;
	SUdmSocketInfo* udmSocketInfor = m_udpSocketInfor[udmPos];
	if (udmSocketInfor == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCK);
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfor->m_udmStatus != UDM_STATE_INIT) {
		setlasterror(UDM_ERROR_INVALID_STATE);
		return BSLIB_UDM_ERROR;
	}

	if (existUdmId <= 0 || existUdmId > BSLIB_UDM_SOCKET_MAX) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKID);
		return BSLIB_UDM_ERROR;
	}
	int existUdmPos = existUdmId - 1;
	SUdmSocketInfo* existUdmSocketInfor = m_udpSocketInfor[existUdmPos];
	if (existUdmSocketInfor == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCK);
		return BSLIB_UDM_ERROR;
	}
	if (existUdmSocketInfor->m_udpThreadID == -1) {
		setlasterror(UDM_ERROR_BIND_UDPADDR);
		return BSLIB_UDM_ERROR;
	}
	udmSocketInfor->m_udpThreadID = existUdmSocketInfor->m_udpThreadID;
	udmSocketInfor->m_udmStatus = UDM_STATE_BIND;
	return BSLIB_UDM_OK;
}

int CUdmMgr::listen(UDMSOCKET udmID)
{
	if (udmID <= 0 || udmID > BSLIB_UDM_SOCKET_MAX) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKID);
		return BSLIB_UDM_ERROR;
	}
	int udmPos = udmID - 1;
	SUdmSocketInfo* udmSocketInfor = m_udpSocketInfor[udmPos];
	if (udmSocketInfor == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCK);
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfor->m_udmStatus != UDM_STATE_BIND) {
		setlasterror(UDM_ERROR_INVALID_STATE);
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfor->m_udpThreadID == -1) {
		setlasterror(UDM_ERROR_BIND_UDPADDR);
		return BSLIB_UDM_ERROR;
	}
	CUdmSocket* udmSocket = udmSocketInfor->m_udmSocketPtr;
	CUdmAcceptor* udmAcceptor = NULL;
	if (udmSocket == NULL){
		udmAcceptor = new CUdmAcceptor(udmSocketInfor);
		if (udmAcceptor == NULL){
			setlasterror(UDM_ERROR_OUT_OF_MEMORY);
			return BSLIB_UDM_ERROR;
		}
		udmSocketInfor->m_udmSocketPtr = udmAcceptor;
	} else {
		if (udmSocket->getUdmSocketType() != UDM_SOCKTYPE_ACCEPTOR) {
			setlasterror(UDM_ERROR_BIND_UDPADDR);
			return BSLIB_UDM_ERROR;
		}
		udmAcceptor = (CUdmAcceptor*)udmSocket;
	}
	return udmAcceptor->listen();
}

UDMSOCKET CUdmMgr::accept(UDMSOCKET udmID, struct sockaddr* addr, int* addrlen)
{
	if (udmID <= 0 || udmID > BSLIB_UDM_SOCKET_MAX) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKID);
		return BSLIB_UDM_ERROR;
	}
	int udmPos = udmID - 1;
	SUdmSocketInfo* udmSocketInfor = m_udpSocketInfor[udmPos];
	if (udmSocketInfor == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCK);
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfor->m_udmStatus != UDM_STATE_LISTEN) {
		setlasterror(UDM_ERROR_INVALID_STATE);
		return BSLIB_UDM_ERROR;
	}
	CUdmSocket* udmSocket = udmSocketInfor->m_udmSocketPtr;
	if (udmSocket == NULL){
		setlasterror(UDM_ERROR_INVALID_UDMSOCKOBJ);
		return BSLIB_UDM_ERROR;
	}
	return udmSocket->accept(addr, addrlen);
}

int CUdmMgr::connect(UDMSOCKET udmID, const struct sockaddr* name, int namelen)
{
	if (udmID <= 0 || udmID > BSLIB_UDM_SOCKET_MAX) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKID);
		return BSLIB_UDM_ERROR;
	}
	int udmPos = udmID - 1;
	SUdmSocketInfo* udmSocketInfor = m_udpSocketInfor[udmPos];
	if (udmSocketInfor == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCK);
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfor->m_udmStatus == UDM_STATE_INIT) {
		int udpThreadID = -1;
		if (!CUdpThreadMgr::singleton().bind(udpThreadID)) {
			setlasterror(UDM_ERROR_BIND_UDPADDR);
			return BSLIB_UDM_ERROR;
		}
		udmSocketInfor->m_udpThreadID = udpThreadID;
		udmSocketInfor->m_udmStatus = UDM_STATE_BIND;
	} else if (udmSocketInfor->m_udmStatus != UDM_STATE_BIND) {
		setlasterror(UDM_ERROR_INVALID_STATE);
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfor->m_udpThreadID == -1) {
		setlasterror(UDM_ERROR_BIND_UDPADDR);
		return BSLIB_UDM_ERROR;
	}
	CUdmSocket* udmClient = udmSocketInfor->m_udmSocketPtr;
	if (udmClient == NULL) {
		udmClient = new CUdmClient(udmSocketInfor);
		if (udmClient == NULL){
			setlasterror(UDM_ERROR_OUT_OF_MEMORY);
			return BSLIB_UDM_ERROR;
		}
		udmSocketInfor->m_udmSocketPtr = udmClient;
	}
	return udmClient->connect(name, namelen);
}

int CUdmMgr::close(UDMSOCKET udmID)
{
	if (udmID <= 0 || udmID > BSLIB_UDM_SOCKET_MAX) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKID);
		return BSLIB_UDM_ERROR;
	}
	int udmPos = udmID - 1;
	SUdmSocketInfo* udmSocketInfor = m_udpSocketInfor[udmPos];
	if (udmSocketInfor == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCK);
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfor->m_udmStatus == UDM_STATE_NULL ||
		udmSocketInfor->m_udmStatus == UDM_STATE_NONEXIST ||
		udmSocketInfor->m_udmStatus == UDM_STATE_DELETE1 ||
		udmSocketInfor->m_udmStatus == UDM_STATE_DELETE2) {
			setlasterror(UDM_ERROR_INVALID_UDMSOCK);
			return BSLIB_UDM_ERROR;
	}
	CUdmSocket* udmSocket = udmSocketInfor->m_udmSocketPtr;
	if (udmSocket == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKOBJ);
		return BSLIB_UDM_ERROR;
	}
	return udmSocket->close();
}

int CUdmMgr::getPeerName(UDMSOCKET udmID, struct sockaddr* name, int* namelen)
{
	if (udmID <= 0 || udmID > BSLIB_UDM_SOCKET_MAX) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKID);
		return BSLIB_UDM_ERROR;
	}
	int udmPos = udmID - 1;
	SUdmSocketInfo* udmSocketInfor = m_udpSocketInfor[udmPos];
	if (udmSocketInfor == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCK);
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfor->m_udmStatus == UDM_STATE_NULL ||
		udmSocketInfor->m_udmStatus == UDM_STATE_NONEXIST ||
		udmSocketInfor->m_udmStatus == UDM_STATE_DELETE1 ||
		udmSocketInfor->m_udmStatus == UDM_STATE_DELETE2) {
			setlasterror(UDM_ERROR_INVALID_UDMSOCK);
			return BSLIB_UDM_ERROR;
	}
	CUdmSocket* udmSocket = udmSocketInfor->m_udmSocketPtr;
	if (udmSocket == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKOBJ);
		return BSLIB_UDM_ERROR;
	}
	return udmSocket->getPeerName(name, namelen);
}

int CUdmMgr::getSockName(UDMSOCKET udmID, struct sockaddr* name, int* namelen)
{
	if (udmID <= 0 || udmID > BSLIB_UDM_SOCKET_MAX) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKID);
		return BSLIB_UDM_ERROR;
	}
	int udmPos = udmID - 1;
	SUdmSocketInfo* udmSocketInfor = m_udpSocketInfor[udmPos];
	if (udmSocketInfor == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCK);
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfor->m_udmStatus == UDM_STATE_NULL ||
		udmSocketInfor->m_udmStatus == UDM_STATE_NONEXIST ||
		udmSocketInfor->m_udmStatus == UDM_STATE_DELETE1 ||
		udmSocketInfor->m_udmStatus == UDM_STATE_DELETE2) {
			setlasterror(UDM_ERROR_INVALID_UDMSOCK);
			return BSLIB_UDM_ERROR;
	}
	CUdmSocket* udmSocket = udmSocketInfor->m_udmSocketPtr;
	if (udmSocket == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKOBJ);
		return BSLIB_UDM_ERROR;
	}
	return udmSocket->getSockName(name, namelen);
}

EUdmStatus CUdmMgr::getSockState(UDMSOCKET udmID)
{
	if (udmID <= 0 || udmID > BSLIB_UDM_SOCKET_MAX) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKID);
		return UDM_STATE_NONEXIST;
	}
	int udmPos = udmID - 1;
	SUdmSocketInfo* udmSocketInfor = m_udpSocketInfor[udmPos];
	if (udmSocketInfor == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCK);
		return UDM_STATE_NONEXIST;
	}
	if (udmSocketInfor->m_udmStatus == UDM_STATE_NULL ||
		udmSocketInfor->m_udmStatus == UDM_STATE_NONEXIST ||
		udmSocketInfor->m_udmStatus == UDM_STATE_DELETE1 ||
		udmSocketInfor->m_udmStatus == UDM_STATE_DELETE2) {
			setlasterror(UDM_ERROR_INVALID_UDMSOCK);
			return UDM_STATE_NONEXIST;
	}
	return udmSocketInfor->m_udmStatus;
}

int CUdmMgr::getLastError()
{
	return (long int)g_errorData.get();
}

void CUdmMgr::setlasterror(int error)
{
	g_errorData.set((void*)error);
}

int CUdmMgr::send(UDMSOCKET udmID, const char* buf, int len)
{
	if (udmID <= 0 || udmID > BSLIB_UDM_SOCKET_MAX) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKID);
		return BSLIB_UDM_ERROR;
	}
	int udmPos = udmID - 1;
	SUdmSocketInfo* udmSocketInfor = m_udpSocketInfor[udmPos];
	if (udmSocketInfor == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCK);
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfor->m_udmStatus != UDM_STATE_OPEN) {
		setlasterror(UDM_ERROR_INVALID_STATE);
		return BSLIB_UDM_ERROR;
	}
	CUdmSocket* udmSocket = udmSocketInfor->m_udmSocketPtr;
	if (udmSocket == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKOBJ);
		return BSLIB_UDM_ERROR;
	}
	return udmSocket->send(buf, len);
}

int CUdmMgr::recv(UDMSOCKET udmID, char* buf, int len)
{
	if (udmID <= 0 || udmID > BSLIB_UDM_SOCKET_MAX) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKID);
		return BSLIB_UDM_ERROR;
	}
	int udmPos = udmID - 1;
	SUdmSocketInfo* udmSocketInfor = m_udpSocketInfor[udmPos];
	if (udmSocketInfor == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCK);
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfor->m_udmStatus == UDM_STATE_NULL ||
		udmSocketInfor->m_udmStatus == UDM_STATE_NONEXIST ||
		udmSocketInfor->m_udmStatus == UDM_STATE_DELETE1 ||
		udmSocketInfor->m_udmStatus == UDM_STATE_DELETE2) {
			setlasterror(UDM_ERROR_INVALID_UDMSOCK);
			return BSLIB_UDM_ERROR;
	}
	CUdmSocket* udmSocket = udmSocketInfor->m_udmSocketPtr;
	if (udmSocket == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKOBJ);
		return BSLIB_UDM_ERROR;
	}
	return udmSocket->recv(buf, len);
}

int CUdmMgr::sendTo(UDMSOCKET udmID, const char* buf, int len)
{
	if (udmID <= 0 || udmID > BSLIB_UDM_SOCKET_MAX) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKID);
		return BSLIB_UDM_ERROR;
	}
	int udmPos = udmID - 1;
	SUdmSocketInfo* udmSocketInfor = m_udpSocketInfor[udmPos];
	if (udmSocketInfor == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCK);
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfor->m_udmStatus != UDM_STATE_OPEN) {
		setlasterror(UDM_ERROR_INVALID_STATE);
		return BSLIB_UDM_ERROR;
	}
	CUdmSocket* udmSocket = udmSocketInfor->m_udmSocketPtr;
	if (udmSocket == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKOBJ);
		return BSLIB_UDM_ERROR;
	}
	return udmSocket->sendTo(buf, len);
}

int CUdmMgr::recvFrom(UDMSOCKET udmID, char* buf, int len)
{
	if (udmID <= 0 || udmID > BSLIB_UDM_SOCKET_MAX) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKID);
		return BSLIB_UDM_ERROR;
	}
	int udmPos = udmID - 1;
	SUdmSocketInfo* udmSocketInfor = m_udpSocketInfor[udmPos];
	if (udmSocketInfor == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCK);
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfor->m_udmStatus == UDM_STATE_NULL ||
		udmSocketInfor->m_udmStatus == UDM_STATE_NONEXIST ||
		udmSocketInfor->m_udmStatus == UDM_STATE_DELETE1 ||
		udmSocketInfor->m_udmStatus == UDM_STATE_DELETE2) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCK);
		return BSLIB_UDM_ERROR;
	}
	CUdmSocket* udmSocket = udmSocketInfor->m_udmSocketPtr;
	if (udmSocket == NULL) {
		setlasterror(UDM_ERROR_INVALID_UDMSOCKOBJ);
		return BSLIB_UDM_ERROR;
	}
	int recvLen = udmSocket->recvFrom(buf, len);
	if (recvLen == BSLIB_UDM_ERROR) {
		setlasterror(UDM_ERROR_INVALID_STATE);
		return BSLIB_UDM_ERROR;
	}
	return recvLen;
}

SUdmSocketInfo* CUdmMgr::getUdmSocketInfor(UDMSOCKET udmID)
{
	if (udmID <= 0 || udmID > BSLIB_UDM_SOCKET_MAX) {
		return NULL;
	}
	int udmPos = udmID - 1;
	return m_udpSocketInfor[udmPos];
}

void CUdmMgr::_startUp()
{
#ifdef WIN32

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,0), &wsaData);

#endif
}

void CUdmMgr::_cleanUp()
{
#ifdef WIN32

	WSACleanup();

#endif
}

}//UDM

}//BSLib



