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

//////////////////////////////////////////////////////////////////////////
// CNetClient
//////////////////////////////////////////////////////////////////////////
class  BSLIB_NETWORK_API CNetClient
{
public:
	CNetClient();
	virtual ~CNetClient();

	virtual bool connect(const char* serverIP, uint16 serverPort) = 0;
	virtual void close();

	CNetConnectionPtr getNetConnection() { return m_netConnectionPtr; }

	int send(BSLib::Utility::CStream& stream, bool useBuff = true);
	int send(const void* msgBuff, unsigned int buffSize, bool useBuff = true);
	int recv(BSLib::Utility::CStream& stream);
	int recvBlock(BSLib::Utility::CStream& stream);

protected:
	virtual bool _cbParseMsg(void* msgBuff, uint32 msgSize) = 0;
	virtual void _cbTerminate() = 0;

protected:
	CNetConnectionPtr m_netConnectionPtr;

	friend class CNetClientCb;
};
typedef BSLib::Utility::CPointer<CNetClient> CNetClientPtr;

//////////////////////////////////////////////////////////////////////////
// CTcpClient
//////////////////////////////////////////////////////////////////////////
class BSLIB_NETWORK_API CTcpClient : public CNetClient 
{
public:
	CTcpClient();
	virtual ~CTcpClient();

	void setTcpConnectionMgr(CTcpConnectionMgr* tcpConnectionMgr) { m_tcpConnectionMgr = tcpConnectionMgr; }

	virtual bool connect(const char* serverIP, uint16 serverPort);
	virtual void close();

private:
	BSLib::Network::CTcpConnectionMgr* m_tcpConnectionMgr;
	BSLib::Network::CNetConnectionCallbackPtr m_tcpClientCb;

};
typedef BSLib::Utility::CPointer<CTcpClient> CTcpClientPtr;

//////////////////////////////////////////////////////////////////////////
// CUdpClient
//////////////////////////////////////////////////////////////////////////
class BSLIB_NETWORK_API CUdpClient : public CNetClient 
{
public:
	CUdpClient();
	virtual ~CUdpClient();

	void setUdpConnectionMgr(BSLib::Network::CUdpConnectionMgr* udpConnectionMgr) { m_udpConnectionMgr = udpConnectionMgr; }

	virtual bool connect(const char* serverIP, uint16 serverPort);

	virtual void close();

	bool connect(CSockAddr& addrLocal, CSockAddr& addrServer);

private:
	BSLib::Network::CUdpConnectionMgr* m_udpConnectionMgr;
	BSLib::Network::CNetConnectionCallbackPtr m_udpClientCb;

};
typedef BSLib::Utility::CPointer<CUdpClient> CUdpClientPtr;

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_NETCLIENT_H__


