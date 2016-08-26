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

	/// @brief ���ӷ�����
	/// @return	bool ���ӳɹ�����true
	/// @param	addrLocal �󶨱���IP�Ͷ˿�
	/// @param	addrServer ���ӷ�������IP�Ͷ˿�
	/// @param	connMax �������ʧ�ܣ��ظ����ӵĴ�����Ĭ��0����������ֱ�����ӳɹ�
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


    // override tcp send ��Ҫ��д�Ľӿ�
	virtual int _INetConnection_send2Buff(const void* data, unsigned int len, unsigned int sign) override;
	virtual int _INetConnection_send2Net(const void* data, unsigned int len, unsigned int sign) override;

	int _sendBlock(const void* dataBuff, int buffSize);


    // split packet, �� _writeToBuff,  _sendToNet ���
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

