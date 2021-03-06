#include "tcpStubThread.h"

namespace BSLib
{

namespace Network
{

CTcpStubThread::CTcpStubThread(INetServer* netServer)
: CNetStubThread(netServer)
{
	;
}

CTcpStubThread::~CTcpStubThread()
{
	;
}

bool CTcpStubThread::_addStubToNetConnectionMgr(CNetStubPtr& stubPtr, INetConnectionCallbackPtr& netConnectionCb)
{
	CTcpConnectionMgr::CConnectItem* item = new CTcpConnectionMgr::CConnectItem();
	if (item == NULL){
		return false;
	}
	item->m_connect = stubPtr->getNetConnectionPtr();
	item->m_callback = netConnectionCb;

	CTcpConnectionMgr::CConnectItemPtr connItemPtr = item;
	return CTcpConnectionMgr::_addConnection(connItemPtr);
}

bool CTcpStubThread::_delStubToNetConnectionMgr(CNetStubPtr& stubPtr)
{
	CNetConnectionPtr netConnect = stubPtr->getNetConnectionPtr();
	if (netConnect == NULL) {
		return false;
	}
	int sock = netConnect->INetConnection_getSockect();
	if (!netConnect->INetConnection_isValid()) {
		return false;
	}
	CTcpConnectionMgr::_delConnection(sock);
	return true;
}

void CTcpStubThread::_wait()
{
	CTcpConnectionMgr::_INetConnectionMgr_epoll(15);
}

void CTcpStubThread::_enterRun()
{
	;
}

void CTcpStubThread::_leaveRun()
{
	CTcpConnectionMgr::_clearAllConnection();
}

}//Network

}//BSLib



