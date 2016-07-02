#ifndef __BSLIB_NETWOEK_TCPCONNECTIONMGR_H__
#define __BSLIB_NETWOEK_TCPCONNECTIONMGR_H__

#include <BSLib/network/netConnectionMgr.h>
#include <BSLib/network/tcpConnection.h>

namespace BSLib
{

namespace Network
{

class CTcpEpoll;

class BSLIB_NETWORK_API CTcpConnectionMgr 
    : public INetConnectionMgr
{
public:
	CTcpConnectionMgr();
	virtual ~CTcpConnectionMgr();
	
	virtual bool INetConnectionMgr_postSend(int tcpSocket);

protected:
	virtual bool _INetConnectionMgr_addConnToPoll(CConnectItemPtr& connItemPtr);
	virtual void _INetConnectionMgr_delConnFromPoll(CConnectItemPtr& connItemPtr);
	virtual bool _INetConnectionMgr_epoll(int msSec);

	bool _readScoket(SOCKET& tcpSocket, void* data);
	bool _writeScoket(SOCKET& tcpSocket, void* data);
	void _terminateScoket(SOCKET& tcpSocket, void* data);

private:
	CTcpEpoll* m_tcpEpoll;
};

}//Network

}//BSLib

#endif//__BSLIB_NETWOEK_TCPCONNECTIONMGR_H__

