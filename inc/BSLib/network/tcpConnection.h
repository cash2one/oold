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

	virtual bool INetConnection_sendToNetFromBuff();
	virtual bool INetConnection_isEmptyOfSendBuff();

	/// @brief ���ӷ�����
	/// @return	bool ���ӳɹ�����true
	/// @param	addrLocal �󶨱���IP�Ͷ˿�
	/// @param	addrServer ���ӷ�������IP�Ͷ˿�
	/// @param	connMax �������ʧ�ܣ��ظ����ӵĴ�����Ĭ��0����������ֱ�����ӳɹ�
	virtual bool connect(CSockAddr& addrServer, int connMax = 0);
	virtual bool connect(CSockAddr& addrLocal, CSockAddr& addrServer, int connMax = 0);

	virtual void close();

	virtual int getSockect() { return (int)m_tcpSock; }
	virtual ENetType getSockectType() { return NETT_TCP; }
	virtual bool isValid();

protected:
	virtual int _send(const void* dataBuff, int buffSize);
	virtual int _recv(void* dataBuff, int buffSize);
	virtual void _postSend();

	virtual BSLib::uint64 _getSendBytes();
	virtual BSLib::uint64 _getRecvBytes();

	virtual int _writeToBuff(const void* data, unsigned int len, unsigned int sign);
	virtual int _sendToNet(const void* data, unsigned int len, unsigned int sign);
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

