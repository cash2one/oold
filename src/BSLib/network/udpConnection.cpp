#include "netinit.h"
#include <BSLib/udm/udm.h>
#include <BSLib/utility/thread/thread.h>
#include <BSLib/network/udpConnection.h>
#include <BSLib/network/udpConnectionMgr.h>

#define BSLIB_NETWORK_PACKET_SIZE_MAX 512

namespace BSLib
{

namespace Network
{

CUdpConnection::CUdpConnection(int sock, IEncrypt* ptrEncrypt, ICompress* ptrCompress, ICodec* ptrCodec)
: INetConnection(ptrEncrypt, ptrCompress, ptrCodec)
, m_udmSock(-1) 
, m_isValid(false)
{
	if (sock != INVALID_SOCKET){
		_setConnectionAddr(sock);
	}
}

CUdpConnection::~CUdpConnection()
{
	if (m_udmSock != -1) {
		//BSLib::UDM::INetConnection_close(m_udmSock);
		m_isValid = false;
	}
}

bool CUdpConnection::INetConnection_sendToNetFromBuff()
{
	Utility::CMutexFun mutexFun(&m_sendMutex);

	int sendSize = 0;
	std::list<int>::iterator it_size = m_sendSizes.begin();
	for (; it_size != m_sendSizes.end();){
		if (sendSize + *it_size < BSLIB_NETWORK_PACKET_SIZE_MAX)	{
			sendSize += *it_size;
			it_size = m_sendSizes.erase(it_size);
			continue;
		}
		if (sendSize == 0){
			_INetConnection_send(m_sendBuff.readPtr(), *it_size);
			m_sendBuff.readFlip(*it_size);
			it_size = m_sendSizes.erase(it_size);
			continue;
		}
		_INetConnection_send(m_sendBuff.readPtr(), sendSize);
		m_sendBuff.readFlip(sendSize);
		
		sendSize = *it_size;
		it_size = m_sendSizes.erase(it_size);
	}
	if (sendSize > 0){
		_INetConnection_send(m_sendBuff.readPtr(), sendSize);
		m_sendBuff.readFlip(sendSize);
	}
	return true;
}

bool CUdpConnection::INetConnection_isEmptyOfSendBuff()
{
	return !m_sendBuff.readReady();
}

bool CUdpConnection::INetConnection_connect(CSockAddr& addrServer, int connMax)
{
	if (m_isValid){
		return false;
	}
	int count = 0;
	UDMSOCKET sock = BSLib::UDM::socket();
	if (sock == INVALID_UDMSOCK) {
		return false;
	}
	while (BSLib::UDM::connect(sock, (sockaddr*)addrServer, sizeof(sockaddr_in)) == BSLIB_UDM_ERROR) {
		++count;
		if (connMax != 0 && count >= connMax) {
			BSLib::UDM::close(sock);
			sock = (int)INVALID_SOCKET;
			return false;
		}
		BSLib::Utility::CThread::msleep(1000);
	}
	_setConnectionAddr(sock);
	_clearBuff();
	return true;
}

bool CUdpConnection::INetConnection_connect(CSockAddr& addrLocal, CSockAddr& addrServer, int connMax)
{
	if (m_isValid){
		return false;
	}
	int count = 0;
	UDMSOCKET sock = BSLib::UDM::socket();
	if (sock == INVALID_UDMSOCK) {
		return false;
	}

	if (BSLib::UDM::bind(sock, (sockaddr*)addrLocal, sizeof(sockaddr_in)) == BSLIB_UDM_ERROR) {
		BSLib::UDM::close(sock);
		return false;
	}

	while (BSLib::UDM::connect(sock, (sockaddr*)addrServer, sizeof(sockaddr_in)) == BSLIB_UDM_ERROR) {
		++count;
		if (connMax != 0 && count >= connMax) {
			BSLib::UDM::close(sock);
			sock = (int)INVALID_SOCKET;
			return false;
		}
		BSLib::Utility::CThread::msleep(1000);
	}
	_setConnectionAddr(sock);
	_clearBuff();
	return true;
}

void CUdpConnection::INetConnection_close()
{
	if (!m_isValid){
		return ;
	}
	BSLib::UDM::close(m_udmSock);
	m_isValid = false;
	INetConnection::INetConnection_close();
}

bool CUdpConnection::INetConnection_isValid()
{
	BSLib::UDM::EUdmStatus state = BSLib::UDM::getsockstate(m_udmSock);
	if (state >= BSLib::UDM::UDM_STATE_BROKEN) {
		m_isValid = false;
	}
	return m_isValid;
}

int CUdpConnection::_INetConnection_send(const void* dataBuff, int buffSize)
{
	int len = BSLib::UDM::sendto(m_udmSock, (char*)dataBuff, buffSize);
	if (len == BSLIB_UDM_ERROR) {
		return -1;
	}
	return len;
}

int CUdpConnection::_INetConnection_recv(void* dataBuff, int buffSize)
{
	int len = BSLib::UDM::recvfrom(m_udmSock, (char*)dataBuff, buffSize);
	if (len == BSLIB_UDM_ERROR) {
		return -1;
	}
	return len;
}

void CUdpConnection::_INetConnection_postSend()
{
	INetConnectionMgr* netConnMgr = getNetConnectionMgr();
	if (netConnMgr != NULL){
		netConnMgr->INetConnectionMgr_postSend(m_udmSock);
	}
}

int CUdpConnection::_INetConnection_writeToBuff(const void* data, unsigned int len, unsigned int sign)
{
	if (len > GNET_PACKET_LEN) {
		return -1;
	}
	unsigned int cmdFlag = (sign & GNET_PACKET_SIGN) | len;

	m_sendMutex.lock();
	if (!m_sendBuff.push((char*)&cmdFlag, sizeof(cmdFlag))){
		m_sendMutex.unlock();
		return -1;
	}
	if (!m_sendBuff.push((char*)data, len)){
		m_sendMutex.unlock();
		return -1;
	}
	int sendSize = sizeof(cmdFlag) + len;
	m_sendSizes.push_back(sendSize);

	m_sendMutex.unlock();

	_INetConnection_postSend();
	return len;
}

int CUdpConnection::_INetConnection_sendToNet(const void* data, unsigned int len, unsigned int sign)
{
	if (len > GNET_PACKET_LEN) {
		return -1;
	}
	unsigned int cmdFlag = (sign & GNET_PACKET_SIGN) | len;

	Utility::CMutexFun mutexFun(&m_sendMutex);

	if (_sendBlock(&cmdFlag, sizeof(cmdFlag)) < 0){
		return -1;
	}
	if (_sendBlock(data, len) < 0){
		return -1;
	}
	return len;
}

int CUdpConnection::_sendBlock(const void* dataBuff, int buffSize)
{
	const char* sendData = (const char*)dataBuff;
	int dataLen = buffSize;
	int offset = 0;

	do {
		int sendSize = _INetConnection_send(&sendData[offset], dataLen - offset);
		if (sendSize < 0){
			return -1;
		}
		if (sendSize == 0) {
			_INetConnection_waitForSend();
			continue;
		}
		offset += sendSize;
	} while (offset < dataLen);

	return buffSize;
}

void CUdpConnection::_setConnectionAddr(int sock)
{
	if (sock != INVALID_UDMSOCK){
		CSockAddr peerAddr;
		CSockAddr localAddr;
		int len = sizeof(sockaddr_in);

		if (BSLib::UDM::getpeername(sock, (sockaddr*)peerAddr, &len) != BSLIB_UDM_ERROR) {
			peerAddr.setIP();
			_setPeerAddr(peerAddr);
		}
		if (BSLib::UDM::getsockname(sock, (sockaddr*)localAddr, &len) != BSLIB_UDM_ERROR) {
			localAddr.setIP();
			_setLocalAddr(localAddr);
		}
		m_udmSock = sock;
		m_isValid = true;
	}
}

}//Network

}//BSLib



