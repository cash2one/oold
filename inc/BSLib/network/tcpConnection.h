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
	CTcpConnection(SOCKET sock = INVALID_SOCKET, IEncrypt* ptrEncrypt = NULL, ICompress* ptrCompress = NULL);
	virtual ~CTcpConnection();

	virtual bool INetConnection_sendToNetFromBuff() override;
	virtual bool INetConnection_isEmptyOfSendBuff() override;

	/// @brief ���ӷ�����
	/// @return	bool ���ӳɹ�����true
	/// @param	addrLocal �󶨱���IP�Ͷ˿�
	/// @param	addrServer ���ӷ�������IP�Ͷ˿�
	/// @param	connMax �������ʧ�ܣ��ظ����ӵĴ�����Ĭ��0����������ֱ�����ӳɹ�
	virtual bool INetConnection_connect(CSockAddr& addrServer, int connMax = 0);
	virtual bool INetConnection_connect(CSockAddr& addrLocal, CSockAddr& addrServer, int connMax = 0);

	virtual void INetConnection_close();

	virtual int INetConnection_getSockect() { return (int)m_tcpSock; }
	virtual ENetType INetConnection_getSockectType() { return NETT_TCP; }
	virtual bool INetConnection_isValid();

protected:
	virtual int _INetConnection_send(const void* dataBuff, int buffSize);
	virtual int _INetConnection_recv(void* dataBuff, int buffSize);
	virtual void _INetConnection_postSend();

	virtual BSLib::uint64 _INetConnection_getSendBytes();
	virtual BSLib::uint64 _INetConnection_getRecvBytes();

	virtual int _INetConnection_writeToBuff(const void* data, unsigned int len, unsigned int sign);
	virtual int _INetConnection_sendToNet(const void* data, unsigned int len, unsigned int sign);
	int _sendBlock(const void* dataBuff, int buffSize);


private:
	void _setConnectionAddr(int sock);
	int _INetConnection_writeToBuff(const void* data, unsigned int len, unsigned int sign, Utility::CBufferInt8& sendBuff);

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

