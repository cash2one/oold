//////////////////////////////////////////////////////////////////////
//	created:	2012/09/15
//	filename:	src\BSLib\network\tcpStubThread.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include "tcpStubThread.h"

namespace BSLib
{

namespace Network
{

CTcpStubThread::CTcpStubThread(CNetServer* netServer)
: CNetStubThread(netServer)
{
	;
}

CTcpStubThread::~CTcpStubThread()
{
	;
}

bool CTcpStubThread::_addStubToNetConnectionMgr(CNetStubPtr& stubPtr, CNetConnectionCallbackPtr& netConnectionCb)
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
	int sock = netConnect->getSockect();
	if (!netConnect->isValid()) {
		return false;
	}
	CTcpConnectionMgr::_delConnection(sock);
	return true;
}

void CTcpStubThread::_wait()
{
	CTcpConnectionMgr::_epoll(15);
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


