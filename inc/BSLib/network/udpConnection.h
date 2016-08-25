#ifndef __BSLIB_NETWOEK_UDPCONNECTION_H__
#define __BSLIB_NETWOEK_UDPCONNECTION_H__

#include <BSLib/network/netConnection.h>
#include "BSLib/network/codec.hpp"

namespace BSLib
{

namespace Network
{

class BSLIB_NETWORK_API CUdpConnection 
    : public INetConnection
{
public:
	CUdpConnection(int sock = -1, IEncrypt* ptrEncrypt = NULL, ICompress* ptrCompress = NULL,ICodec* ptrCodec = NULL);
	virtual ~CUdpConnection();

	virtual bool INetConnection_sendToNetFromBuff() override;
	virtual bool INetConnection_isEmptyOfSendBuff() override;

	virtual bool INetConnection_connect(CSockAddr& addrServer, int connMax = 0) override;
	virtual bool INetConnection_connect(CSockAddr& addrLocal, CSockAddr& addrServer, int connMax = 0) override;

	virtual void INetConnection_close() override;

	virtual int INetConnection_getSockect()  override { return m_udmSock; }
	virtual ENetType INetConnection_getSockectType() override  { return NETT_UDP; }
	virtual bool INetConnection_isValid()  override;

protected:
	virtual int _INetConnection_send(const void* dataBuff, int buffSize)  override;
	virtual int _INetConnection_recv(void* dataBuff, int buffSize)  override;
	virtual void _INetConnection_postSend()  override;

	virtual int _INetConnection_writeToBuff(const void* data, unsigned int len, unsigned int sign)  override;
	virtual int _INetConnection_sendToNet(const void* data, unsigned int len, unsigned int sign)  override;
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


