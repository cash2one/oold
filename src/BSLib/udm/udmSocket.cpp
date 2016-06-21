#include "udmSocket.h"
#include "udpThreadMgr.h"

#define BSLIB_UDM_DELETE_TICK_MAX 3
#define BSLIB_UDM_RECV_BUFFSIZE (1024*1024)
namespace BSLib
{

namespace UDM
{

CUdmSocket::CUdmSocket(SUdmSocketInfor* udmSocketInfor)
: m_udmSocketInfor(udmSocketInfor)
, m_deleteCount(0)
{
	;
}

CUdmSocket::~CUdmSocket()
{
	printf("free CUdmSocket\n");
}

int CUdmSocket::getPeerName(struct sockaddr* name, int* namelen)
{
	*name = *(sockaddr*)&m_peerAddr; 
	*namelen = sizeof(sockaddr_in);
	return BSLIB_UDM_OK; 
}

int CUdmSocket::setPeerName(const struct sockaddr* name, int namelen)
{
	m_peerAddr = *(sockaddr_in*)name;
	return BSLIB_UDM_OK;
}

int CUdmSocket::getSockName(struct sockaddr* name, int* namelen)
{
	SUdmSocketInfor* udpSocketInfor = CUdmSocket::getUdmSocketInfor();
	CUdpThread* udpThread = CUdpThreadMgr::singleton().getUdpThread(udpSocketInfor->m_udpThreadID);
	if (udpThread == NULL){
		return BSLIB_UDM_ERROR;
	}
	udpThread->getLocalAddr(name, namelen);
	return BSLIB_UDM_OK;
}

int CUdmSocket::send(const char* buff, int len)
{
	return BSLIB_UDM_ERROR;
}

int CUdmSocket::recv(char* buff, int len)
{
	return BSLIB_UDM_ERROR;
}

int CUdmSocket::sendTo(const char* buff, int len)
{
	char tempBuff[BSLIB_UDM_UDP_BUFF_MAX];
	if (len > (int)(BSLIB_UDM_UDP_BUFF_MAX - sizeof(SUdpDataMsg))) {
		return BSLIB_UDM_ERROR;
	}
	SUdpDataMsg* msg = (SUdpDataMsg*)tempBuff;
	new (static_cast<void*>(msg)) SUdpDataMsg();

	memcpy(msg->m_msg, buff, len);
	msg->m_msgSize = len;

	if (!_sendMsg(msg, msg->getSize())) {
		return BSLIB_UDM_ERROR;
	}
	return len;
}

int CUdmSocket::recvFrom(char* buff, int len)
{
	m_readMutex.lock();
	uint32 size = m_readStream.readSize();
	if (size <= 0) {
		m_readMutex.unlock();
		if (m_udmSocketInfor->m_udmStatus == UDM_STATE_BROKEN) {
			return BSLIB_UDM_ERROR;
		}
		return BSLIB_UDM_OK;
	}
	uint32 recvLen = m_readStream.pop(buff, len);
	m_readMutex.unlock();

	return recvLen;
}

bool CUdmSocket::parseCtrlMsg(SUdpCtrlMsg* msg, int msgSize, BSLib::Utility::CRealTime& realTime)
{
	return false;
}

bool CUdmSocket::parseDataMsg(SUdpCtrlMsg* msg, int msgSize, BSLib::Utility::CRealTime& realTime)
{
	if (msg->getMsgID() == 0){
		SUdpDataMsg* msgData = (SUdpDataMsg*)msg;
		if (msgData->getSize() != msgSize) {
			return false;
		}
		m_readMutex.lock();
		if (m_readStream.writeSize() > BSLIB_UDM_RECV_BUFFSIZE){
			return false;
		}
		m_readStream.push(msgData->m_msg, msgData->m_msgSize);
		m_readMutex.unlock();

		notifyRead();
		return true;
	}

	return false;
}

void CUdmSocket::tickMsg(BSLib::Utility::CRealTime& realTime)
{
	SUdmSocketInfor* udpSocketInfor = CUdmSocket::getUdmSocketInfor();
	if (udpSocketInfor->m_udmStatus == UDM_STATE_DELETE1) {
		if (m_deleteCount > BSLIB_UDM_DELETE_TICK_MAX) {
			udpSocketInfor->m_udmStatus = UDM_STATE_DELETE2;
			return ;
		}
		++m_deleteCount;
	}
}

bool CUdmSocket::canRead()
{
	return m_readStream.readSize() > 0;
}

void CUdmSocket::notifyRead()
{
	SUdmEpollInfor* udmEpollInfor = m_udmSocketInfor->m_udmEpollInfor;
	if (udmEpollInfor == NULL) {
		return ;
	}
	if (udmEpollInfor->m_epollEventType & UDM_EPOLL_READ) {
		if (udmEpollInfor->m_epollEventQueue != NULL && udmEpollInfor->m_epollEvent != NULL) {
			bool canNotify = false;
			if (udmEpollInfor->m_isBreak == false && udmEpollInfor->m_canRead == false && udmEpollInfor->m_canWrite == false) {
				canNotify = true;
			}
			udmEpollInfor->m_canRead = true;
			if (canNotify) {
				udmEpollInfor->m_epollEventQueue->push(m_udmSocketInfor);
				udmEpollInfor->m_epollEvent->set();
			}
		}
	}
}

void CUdmSocket::notifyBreak()
{
	SUdmEpollInfor* udmEpollInfor = m_udmSocketInfor->m_udmEpollInfor;
	if (udmEpollInfor == NULL) {
		return ;
	}
	if (udmEpollInfor->m_epollEventType & UDM_EPOLL_ERROR) {
		if (udmEpollInfor->m_epollEventQueue != NULL && udmEpollInfor->m_epollEvent != NULL) {
			bool canNotify = false;
			if (udmEpollInfor->m_isBreak == false && udmEpollInfor->m_canRead == false && udmEpollInfor->m_canWrite == false) {
				canNotify = true;
			}
			udmEpollInfor->m_isBreak = true;
			if (canNotify) {
				udmEpollInfor->m_epollEventQueue->push(m_udmSocketInfor);
				udmEpollInfor->m_epollEvent->set();
			}
		}
	}
}

bool CUdmSocket::_sendMsg(SUdpCtrlMsg* msg, int msgSize)
{
	SUdmSocketInfor* udpSocketInfor = CUdmSocket::getUdmSocketInfor();
	CUdpThread* udpThread = CUdpThreadMgr::singleton().getUdpThread(udpSocketInfor->m_udpThreadID);
	if (udpThread == NULL){
		return false;
	}
	if (udpThread->sendTo(msg, msgSize, (sockaddr*)&m_peerAddr, sizeof(sockaddr_in)) == BSLIB_UDM_ERROR) {
		return false;
	}
	return true;
}

}//UDM

}//BSLib


