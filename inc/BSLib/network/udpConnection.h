#ifndef __BSLIB_NETWOEK_UDPCONNECTION_H__
#define __BSLIB_NETWOEK_UDPCONNECTION_H__

#include <BSLib/network/netConnection.h>

namespace BSLib
{

namespace Network
{

class BSLIB_NETWORK_API CUdpConnection 
    : public INetConnection
{
public:
	CUdpConnection(int sock = -1, IEncrypt* ptrEncrypt = NULL, ICompress* ptrCompress = NULL);
	virtual ~CUdpConnection();

	virtual bool INetConnection_sendToNetFromBuff();
	virtual bool INetConnection_isEmptyOfSendBuff();

	virtual bool INetConnection_connect(CSockAddr& addrServer, int connMax = 0);
	virtual bool INetConnection_connect(CSockAddr& addrLocal, CSockAddr& addrServer, int connMax = 0);

	virtual void INetConnection_close();

	virtual int INetConnection_getSockect() { return m_udmSock; }
	virtual ENetType INetConnection_getSockectType() { return NETT_UDP; }
	virtual bool INetConnection_isValid();

protected:
	virtual int _INetConnection_send(const void* dataBuff, int buffSize);
	virtual int _INetConnection_recv(void* dataBuff, int buffSize);
	virtual void _INetConnection_postSend();

	virtual int _INetConnection_writeToBuff(const void* data, unsigned int len, unsigned int sign);
	virtual int _INetConnection_sendToNet(const void* data, unsigned int len, unsigned int sign);
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


