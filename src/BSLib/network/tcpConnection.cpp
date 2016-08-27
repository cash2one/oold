#ifdef WIN32

#include <WinSock2.h>

#else

#include <fcntl.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include "epoll.h"

#endif

#include <BSLib/utility/tracer.h>
#include <BSLib/utility/thread/thread.h>
#include <BSLib/network/tcpConnectionMgr.h>
#include <BSLib/network/tcpConnection.h>

#include "netinit.h"

namespace BSLib
{

namespace Network
{
const int g_tcpBufferSize = 256*1024;

CTcpConnection::CTcpConnection(SOCKET sock, IEncrypt* ptrEncrypt, ICompress* ptrCompress, ICodec* ptrCodec)
: INetConnection(ptrEncrypt, ptrCompress, ptrCodec)
, m_tcpSock(INVALID_SOCKET) 
, m_isValid(false)
, m_recvBytes(0)
, m_sendBytes(0)
{
#ifdef WIN32

	CNetInit::singleton();

#endif

	if (sock != INVALID_SOCKET){
		_setConnectionAddr((int)sock);
		m_isValid = true;
	}
}

CTcpConnection::~CTcpConnection()
{
	//;INetConnection_close();
}

bool CTcpConnection::INetConnection_sendBuff2Net()
{
	Utility::CMutexFun mutexFun(&m_sendMutex);

	while(m_sendBuff.readSize()){
		int len = _INetConnection_os_send(m_sendBuff.readPtr(), m_sendBuff.readSize());
		if (len < 0){
			return false;
		}
		if (len == 0){
			_INetConnection_postSend();
			return true;
		}
		m_sendBuff.readFlip(len);
	}
	return true;
}

bool CTcpConnection::INetConnection_sendBuffIsEmpty()
{
	return !m_sendBuff.readReady();
}

bool CTcpConnection::INetConnection_connect(CSockAddr& addrServer, int connMax)
{
	if (m_isValid){
		return false;
	}

	sockaddr_in* pAddrListen = (sockaddr_in*)addrServer;
#ifdef WIN32
	SOCKET sock = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);  
#else
	SOCKET sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#endif
	if (sock == INVALID_SOCKET) {
		return false;
	}
	
	int count = 0;
	while (SOCKET_ERROR == ::connect(sock, (sockaddr*)pAddrListen, sizeof(sockaddr_in))) {
		++count;
		if (connMax != 0 && count >= connMax) {
			::closesocket(sock);
			sock = INVALID_SOCKET;
			return false;
		}
		BSLib::Utility::CThread::msleep(1000);
	}

	uint32 reuserAddr = 1;
	::setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuserAddr , sizeof(uint32));

	::setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&g_tcpBufferSize, sizeof(g_tcpBufferSize));
	::setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&g_tcpBufferSize, sizeof(g_tcpBufferSize));

	uint32 nodelay = 1;
	::setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&nodelay , sizeof(nodelay));
	::setsockopt(sock, SOL_SOCKET, TCP_NODELAY, (char*)&nodelay , sizeof(nodelay));

#ifdef WIN32

	unsigned long flag=1;
	ioctlsocket(sock, FIONBIO, &flag);

#else

	int flag = ::fcntl(sock, F_GETFL, 0);
	flag |= O_NONBLOCK;
	::fcntl(sock, F_SETFL, flag);

#endif

	_setConnectionAddr((int)sock);
	_clearRecvBuff();
	return true;
}

bool CTcpConnection::INetConnection_connect(CSockAddr& addrLocal, CSockAddr& addrServer, int connMax)
{
	if (m_isValid){
		return false;
	}

	sockaddr_in* pAddrListen = (sockaddr_in*)addrServer;
#ifdef WIN32
	SOCKET sock = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);  
#else
	SOCKET sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#endif

	if (sock == INVALID_SOCKET) {
		return false;
	}

	if (SOCKET_ERROR == ::bind(sock, (sockaddr*)addrLocal, sizeof(sockaddr_in))) {
		::closesocket(sock);
		return false;
	}

	int count = 0;
	while (SOCKET_ERROR == ::connect(sock, (sockaddr*)pAddrListen, sizeof(sockaddr_in))) {
		++count;
		if (connMax != 0 && count >= connMax) {
			::closesocket(sock);
			sock = INVALID_SOCKET;
			return false;
		}
		Utility::CThread::msleep(1000);
	}

	uint32 reuserAddr = 1;
	::setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuserAddr , sizeof(uint32));

	::setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&g_tcpBufferSize, sizeof(g_tcpBufferSize));
	::setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&g_tcpBufferSize, sizeof(g_tcpBufferSize));

	uint32 nodelay = 1;
	::setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&nodelay , sizeof(nodelay));
	::setsockopt(sock, SOL_SOCKET, TCP_NODELAY, (char*)&nodelay , sizeof(nodelay));

#ifdef WIN32

	unsigned long flag=1;
	ioctlsocket(sock, FIONBIO, &flag);

#else

	int flag = ::fcntl(sock, F_GETFL, 0);
	flag |= O_NONBLOCK;
	::fcntl(sock, F_SETFL, flag);

#endif

	_setConnectionAddr((int)sock);
	_clearRecvBuff();
	return true;
}

void CTcpConnection::INetConnection_getNetConnectionInfo(SNetConnectionBytesInfo& a_connectionInfo)
{
    a_connectionInfo.m_recvBytes = m_recvBytes;
    a_connectionInfo.m_sendBytes = m_sendBytes;
}

void CTcpConnection::INetConnection_close()
{
	if (!m_isValid){
		return ;
	}
	::closesocket(m_tcpSock);
	m_isValid = false;
	INetConnection::INetConnection_close();
}

bool CTcpConnection::INetConnection_isValid()
{
	return m_isValid;
}


int CTcpConnection::_INetConnection_os_send(const void* dataBuff, int buffSize)
{
#ifdef WIN32

	int len = ::send(m_tcpSock, (char*)dataBuff, buffSize, 0);

	if (len == SOCKET_ERROR) {
		int error = WSAGetLastError();
		if (error == WSAEWOULDBLOCK || error == ERROR_IO_PENDING || error == WSAENOBUFS) {
			return 0;
		}
		return -1;
	}

#else

	int len = ::send(m_tcpSock, (char*)dataBuff, buffSize, MSG_DONTWAIT);

	if (len == SOCKET_ERROR){
		if (errno == EAGAIN || errno == EWOULDBLOCK || errno == ENOBUFS) {
			return 0;
		}
		return -1;
	}

#endif

// 	BSLIB_LOG_TRACE(ETT_BSLIB_NETWORK, "TCP send [%d][%s:%d]---[%d]--->[%s:%d]",
// 		m_tcpSock,
// 		getLocalAddr().getIP().c_str(),
// 		getLocalAddr().getPort(),
// 		len,
// 		getPeerAddr().getIP().c_str(),
// 		getPeerAddr().getPort());

	m_sendBytes += len;

	return len;
}

int CTcpConnection::_INetConnection_os_recv(void* dataBuff, int buffSize)
{
#ifdef WIN32

	int len = ::recv(m_tcpSock, (char*)dataBuff, buffSize, 0);
	if (len == 0){
		return -1;
	}

	if (len < 0) {
		int error = WSAGetLastError();
		if (error == 0 || error == WSAEWOULDBLOCK || error == ERROR_IO_PENDING) {
			return 0;
		}
		return -1;
	}

#else

	int len = ::recv(m_tcpSock, (char*)dataBuff, buffSize, MSG_DONTWAIT);
	if (len == 0){
		return -1;
	}
	if (len < 0){
		if (errno == EAGAIN || errno == EWOULDBLOCK) {
			return 0;
		}
		return -1;
	}

#endif

// 	BSLIB_LOG_TRACE(ETT_BSLIB_NETWORK, "TCP recv [%d][%s:%d]<---[%d]---[%s:%d]",
// 		m_tcpSock,
// 		getLocalAddr().getIP().c_str(),
// 		getLocalAddr().getPort(),
// 		len,
// 		getPeerAddr().getIP().c_str(),
// 		getPeerAddr().getPort());

	m_recvBytes += len;

	return len;
}

void CTcpConnection::_INetConnection_postSend() 
{
	INetConnectionMgr* netConnMgr = getNetConnectionMgr();
	if (netConnMgr != NULL){
		netConnMgr->INetConnectionMgr_postSend((int)m_tcpSock);
	}
}

int CTcpConnection::_INetConnection_send2Buff(const void* data, unsigned int len)
{
	m_sendMutex.lock();

	if (_writeToBuff(data, len, m_sendBuff) < 0) {
		m_sendMutex.unlock();
		return -1;
	}
	m_sendMutex.unlock();
	
	_INetConnection_postSend();

	return len;
}

int CTcpConnection::_INetConnection_send2Net(const void* data, unsigned int len)
{
	Utility::CBufferInt8 buffer;
	
	if (_writeToBuff(data, len, buffer) < 0) {
		m_sendMutex.unlock();
		return -1;
	}

	Utility::CMutexFun mutexFun(&m_sendMutex);

	if (_sendBlock(buffer.readPtr(), buffer.readSize()) < 0){
		return -1;
	}
	return len;
}

int CTcpConnection::_sendBlock(const void* dataBuff, int buffSize)
{
	const char* sendData = (const char*)dataBuff;
	int dataLen = buffSize;
	int offset = 0;

	do {
		int sendSize = _INetConnection_os_send(&sendData[offset], dataLen - offset);
		if (sendSize < 0){
			return -1;
		}
		if (sendSize == 0) {
			_waitForSend();
			continue;
		}
		offset += sendSize;
	} while (offset < dataLen);

	return buffSize;
}

void CTcpConnection::_setConnectionAddr(int sock)
{
	if (sock != INVALID_SOCKET){
		CSockAddr peerAddr;
		CSockAddr localAddr;
		int len = sizeof(sockaddr_in);

#ifdef WIN32

		if (::getpeername(sock, (sockaddr*)peerAddr, &len) != SOCKET_ERROR) {
			peerAddr.setIP();
			_setPeerAddr(peerAddr);
		}
		if (::getsockname(sock, (sockaddr*)localAddr, &len) != SOCKET_ERROR) {
			localAddr.setIP();
			_setLocalAddr(localAddr);
		}

#else

		if (::getpeername(sock, (sockaddr*)peerAddr, (socklen_t*)&len) != SOCKET_ERROR) {
			peerAddr.setIP();
			_setPeerAddr(peerAddr);
		}
		if (::getsockname(sock, (sockaddr*)localAddr, (socklen_t*)&len) != SOCKET_ERROR) {
			localAddr.setIP();
			_setLocalAddr(localAddr);
		}

#endif
		
		m_tcpSock = sock;
		m_isValid = true;
	}
}

int CTcpConnection::_writeToBuff(const void* data, unsigned int len, Utility::CBufferInt8& sendBuff)
{
    unsigned int dataSize = len;
    char* dataBuff = (char*)data;
    
    if (!sendBuff.push((char*)data, dataSize))
    {
        return -1;
    }

    return len;

	/*
    unsigned int dataSize = len;
    char* dataBuff = (char*)data;
    unsigned int dataPos = 0;

    while (dataSize > 0)
    {
    unsigned int cmdFlag = sign;
    unsigned int cmdLen = 0;
    if (dataSize > GNET_PACKET_LEN)
    {
    cmdFlag |= GNET_PACKET_NEXT;    // ªπ”–
    cmdLen = GNET_PACKET_LEN;
    }
    else
    {
    cmdLen = dataSize;
    }

    cmdFlag = (cmdFlag & GNET_PACKET_SIGN)  // ¡Ù FF, ∆‰”‡ clear
    | cmdLen;

    // push flag first
    if (!sendBuff.push((char*)&cmdFlag, sizeof(cmdFlag)))
    {
    return -1;
    }

    // push data
    if (!sendBuff.push((char*)&dataBuff[dataPos], cmdLen))
    {
    return -1;
    }

    dataSize -= cmdLen;
    dataPos += cmdLen;
    }

    return len;
    */
}

}//Network

}//BSLib


