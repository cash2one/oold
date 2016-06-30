#ifndef __BSLIB_NETWOEK_UDPCONNECTIONMGR_H__
#define __BSLIB_NETWOEK_UDPCONNECTIONMGR_H__

#include <BSLib/network/netConnectionMgr.h>
#include <BSLib/network/udpConnection.h>

namespace BSLib
{

namespace Network
{

class BSLIB_NETWORK_API CUdpConnectionMgr : public INetConnectionMgr
{
public:
	CUdpConnectionMgr();
	virtual ~CUdpConnectionMgr();

	virtual bool postSend(int udpSocket);

protected:
	virtual bool _addConnToPoll(CConnectItemPtr& connItemPtr);
	virtual void _delConnFromPoll(CConnectItemPtr& connItemPtr);
	virtual bool _epoll(int msSec);

	virtual bool _readScoket(int& udmSocket, void* data);
	virtual bool _writeScoket(int& udmSocket, void* data);
	virtual void _terminateScoket(int& udmSocket, void* data);

private:
	int m_udmEpollID;
};

}//Network

}//BSLib

#endif//__BSLIB_NETWOEK_UDPCONNECTIONMGR_H__

