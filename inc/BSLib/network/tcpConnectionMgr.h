#ifndef __BSLIB_NETWOEK_TCPCONNECTIONMGR_H__
#define __BSLIB_NETWOEK_TCPCONNECTIONMGR_H__

#include <BSLib/network/netConnectionMgr.h>
#include <BSLib/network/tcpConnection.h>

namespace BSLib
{

namespace Network
{

class CTcpEpoll;

class BSLIB_NETWORK_API CTcpConnectionMgr : public CNetConnectionMgr
{
public:
	CTcpConnectionMgr();
	virtual ~CTcpConnectionMgr();
	
	virtual bool postSend(int tcpSocket);

protected:
	virtual bool _addConnToPoll(CConnectItemPtr& connItemPtr);
	virtual void _delConnFromPoll(CConnectItemPtr& connItemPtr);
	virtual bool _epoll(int msSec);

	virtual bool _readScoket(SOCKET& tcpSocket, void* data);
	virtual bool _writeScoket(SOCKET& tcpSocket, void* data);
	virtual void _terminateScoket(SOCKET& tcpSocket, void* data);

private:
	CTcpEpoll* m_tcpEpoll;
};

}//Network

}//BSLib

#endif//__BSLIB_NETWOEK_TCPCONNECTIONMGR_H__

