#include "udpStubThread.h"

namespace BSLib
{

namespace Network
{

CUdpStubThread::CUdpStubThread(INetServer* netServer)
: CNetStubThread(netServer)
{
	;
}

CUdpStubThread::~CUdpStubThread()
{
	;
}

bool CUdpStubThread::_addStubToNetConnectionMgr(CNetStubPtr& stubPtr, CNetConnectionCallbackPtr& netConnectionCb)
{
	CUdpConnectionMgr::CConnectItem* item = new CUdpConnectionMgr::CConnectItem();
	if (item == NULL){
		return false;
	}
	item->m_connect = stubPtr->getNetConnectionPtr();
	item->m_callback = netConnectionCb;

	CUdpConnectionMgr::CConnectItemPtr connItemPtr = item;
	return CUdpConnectionMgr::_addConnection(connItemPtr);
}

bool CUdpStubThread::_delStubToNetConnectionMgr(CNetStubPtr& stubPtr)
{
	CNetConnectionPtr netConnect = stubPtr->getNetConnectionPtr();
	if (netConnect == NULL) {
		return false;
	}
	int sock = netConnect->INetConnection_getSockect();
	if (!netConnect->INetConnection_isValid()) {
		return false;
	}
	CUdpConnectionMgr::_delConnection(sock);
	return true;
}

void CUdpStubThread::_wait()
{
	CUdpConnectionMgr::_INetConnectionMgr_epoll(15);
}

void CUdpStubThread::_enterRun()
{
	;
}

void CUdpStubThread::_leaveRun()
{
	CUdpConnectionMgr::_clearAllConnection();
}

}//Network

}//BSLib


