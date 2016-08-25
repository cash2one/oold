#ifndef __BSLIB_NETWORK_TCPSTUBTHREAD_H__
#define __BSLIB_NETWORK_TCPSTUBTHREAD_H__

#include <BSLib/network/tcpConnectionMgr.h>
#include "netStubThread.h"

namespace BSLib
{

namespace Network
{

class CTcpStubThread : public CNetStubThread, public CTcpConnectionMgr
{
public:
	CTcpStubThread(INetServer* netServer);
	virtual ~CTcpStubThread();

protected:
	virtual bool _addStubToNetConnectionMgr(CNetStubPtr& stubPtr, INetConnectionCallbackPtr& netConnectionCb);
	virtual bool _delStubToNetConnectionMgr(CNetStubPtr& stubPtr);
	virtual void _wait();
	virtual void _enterRun();
	virtual void _leaveRun();

};

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_TCPSTUBTHREAD_H__
