#ifndef __BSLIB_NETWOEK_TCPCONNECTION_H__
#define __BSLIB_NETWOEK_TCPCONNECTION_H__

#include <BSLib/network/netConnection.h>

namespace BSLib
{

namespace Network
{

class BSLIB_NETWORK_API CTcpConnection 
    : public INetConnection
{
public:
	CTcpConnection(SOCKET sock = INVALID_SOCKET, IEncrypt* ptrEncrypt = NULL, ICompress* ptrCompress = NULL, ICodec* ptrCodec = NULL);
	virtual ~CTcpConnection();

	virtual bool INetConnection_sendToNetFromBuff() override;
	virtual bool INetConnection_isEmptyOfSendBuff() override;

	/// @brief 连接服务器
	/// @return	bool 连接成功返回true
	/// @param	addrLocal 绑定本地IP和端口
	/// @param	addrServer 连接服务器的IP和端口
	/// @param	connMax 如果连接失败，重复连接的次数；默认0，反复连接直到连接成功
	virtual bool INetConnection_connect(CSockAddr& addrServer, int connMax = 0) override;
	virtual bool INetConnection_connect(CSockAddr& addrLocal, CSockAddr& addrServer, int connMax = 0) override;

	virtual void INetConnection_close() override;

	virtual int INetConnection_getSockect() override { return (int)m_tcpSock; }
	virtual ENetType INetConnection_getSockectType() override  { return NETT_TCP; }
	virtual bool INetConnection_isValid() override;

protected:
	virtual int _INetConnection_send(const void* dataBuff, int buffSize) override;
	virtual int _INetConnection_recv(void* dataBuff, int buffSize) override;
	virtual void _INetConnection_postSend() override;

	virtual BSLib::uint64 _INetConnection_getSendBytes() override;
	virtual BSLib::uint64 _INetConnection_getRecvBytes() override;

	virtual int _INetConnection_writeToBuff(const void* data, unsigned int len, unsigned int sign) override;
	virtual int _INetConnection_sendToNet(const void* data, unsigned int len, unsigned int sign) override;
	int _sendBlock(const void* dataBuff, int buffSize);


private:
	void _setConnectionAddr(int sock);
	int _writeToBuff(const void* data, unsigned int len, unsigned int sign, Utility::CBufferInt8& sendBuff);

private:
	SOCKET m_tcpSock;
	bool m_isValid;
	Utility::CBufferInt8 m_sendBuff;
	Utility::CMutex m_sendMutex;

	BSLib::uint64 m_recvBytes;
	BSLib::uint64 m_sendBytes;
};

}//Network

}//BSLib

#endif//__BSLIB_NETWOEK_TCPCONNECTION_H__

