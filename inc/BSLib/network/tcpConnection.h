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

	virtual bool INetConnection_sendBuff2Net() override;
	virtual bool INetConnection_sendBuffIsEmpty() override;

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
    virtual void INetConnection_getNetConnectionInfo(SNetConnectionBytesInfo& a_connectionInfo) override;
protected:
	virtual int _INetConnection_os_send(const void* dataBuff, int buffSize) override;
	virtual int _INetConnection_os_recv(void* dataBuff, int buffSize) override;
	virtual void _INetConnection_postSend() override;


    // override tcp send 需要改写的接口
	virtual int _INetConnection_send2Buff(const void* data, unsigned int len, unsigned int sign) override;
	virtual int _INetConnection_send2Net(const void* data, unsigned int len, unsigned int sign) override;

	int _sendBlock(const void* dataBuff, int buffSize);


    // split packet, 跟 _writeToBuff,  _sendToNet 相关
    virtual int _writeToBuff(const void* data, unsigned int len, unsigned int sign, Utility::CBufferInt8& sendBuff);

private:
	void _setConnectionAddr(int sock);

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

