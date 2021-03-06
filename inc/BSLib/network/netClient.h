#ifndef __BSLIB_NETWORK_NETCLIENT_H__
#define __BSLIB_NETWORK_NETCLIENT_H__

#include <BSLib/utility/pointer.h>
#include <BSLib/utility/stream.h>
#include <BSLib/network/tcpConnectionMgr.h>
#include <BSLib/network/udpConnectionMgr.h>

namespace BSLib
{

namespace Network
{

class CNetClientCb;

class  BSLIB_NETWORK_API INetClient
{
public:
	INetClient();
	virtual ~INetClient();

	virtual bool INetClient_connect(const char* serverIP, uint16 serverPort) = 0;
	virtual void INetClient_close();

	CNetConnectionPtr getNetConnection() { return m_netConnectionPtr; }

	int send(BSLib::Utility::CStream& stream, bool useBuff = true);
	int send(const void* msgBuff, unsigned int buffSize, bool useBuff = true);
	int recv(BSLib::Utility::CStream& stream);
	int recvBlock(BSLib::Utility::CStream& stream);

protected:
	virtual bool _INetClient_cbParseMsg(void* msgBuff, uint32 msgSize) = 0;
	virtual void _INetClient_cbTerminate() = 0;

protected:
	CNetConnectionPtr m_netConnectionPtr;

	friend class CNetClientCb;
};
typedef BSLib::Utility::CPointer<INetClient> CNetClientPtr;


class BSLIB_NETWORK_API CTcpClient 
    : public INetClient
{
public:
	CTcpClient();
	virtual ~CTcpClient();

	void setTcpConnectionMgr(CTcpConnectionMgr* tcpConnectionMgr) { m_tcpConnectionMgr = tcpConnectionMgr; }

	virtual bool INetClient_connect(const char* serverIP, uint16 serverPort);
	virtual void INetClient_close();

private:
	BSLib::Network::CTcpConnectionMgr* m_tcpConnectionMgr;
	BSLib::Network::INetConnectionCallbackPtr m_tcpClientCb;

};
typedef BSLib::Utility::CPointer<CTcpClient> CTcpClientPtr;


class BSLIB_NETWORK_API CUdpClient 
    : public INetClient
{
public:
	CUdpClient();
	virtual ~CUdpClient();

	void setUdpConnectionMgr(BSLib::Network::CUdpConnectionMgr* udpConnectionMgr) { m_udpConnectionMgr = udpConnectionMgr; }

	virtual bool INetClient_connect(const char* serverIP, uint16 serverPort) override;
	virtual void INetClient_close() override;

	bool INetConnection_connect(CSockAddr& addrLocal, CSockAddr& addrServer);

private:
	BSLib::Network::CUdpConnectionMgr* m_udpConnectionMgr;
	BSLib::Network::INetConnectionCallbackPtr m_udpClientCb;

};
typedef BSLib::Utility::CPointer<CUdpClient> CUdpClientPtr;

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_NETCLIENT_H__


