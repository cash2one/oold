#ifndef __BSLIB_NETWOEK_UDPCONNECTION_H__
#define __BSLIB_NETWOEK_UDPCONNECTION_H__

#include <BSLib/network/netConnection.h>

namespace BSLib
{

namespace Network
{

class BSLIB_NETWORK_API CUdpConnection : public CNetConnection
{
public:
	CUdpConnection(int sock = -1, CEncrypt* ptrEncrypt = NULL, CCompress* ptrCompress = NULL);
	virtual ~CUdpConnection();

	virtual bool sendToNetFromBuff();
	virtual bool isEmptyOfSendBuff();

	virtual bool connect(CSockAddr& addrServer, int connMax = 0);
	virtual bool connect(CSockAddr& addrLocal, CSockAddr& addrServer, int connMax = 0);

	virtual void close();

	virtual int getSockect() { return m_udmSock; }
	virtual ENetType getSockectType() { return NETT_UDP; }
	virtual bool isValid();

protected:
	virtual int _send(const void* dataBuff, int buffSize);
	virtual int _recv(void* dataBuff, int buffSize);
	virtual void _postSend();

	virtual int _writeToBuff(const void* data, unsigned int len, unsigned int sign);
	virtual int _sendToNet(const void* data, unsigned int len, unsigned int sign);
	int _sendBlock(const void* dataBuff, int buffSize);

private:
	void _setConnectionAddr(int sock);

private:
	int m_udmSock;
	bool m_isValid;
	Utility::CBufferInt8 m_sendBuff;
	Utility::CMutex m_sendMutex;
	std::list<int> m_sendSizes;
};

}//Network

}//BSLib

#endif//__BSLIB_NETWOEK_UDPCONNECTION_H__


