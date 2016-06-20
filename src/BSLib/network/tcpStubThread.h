//////////////////////////////////////////////////////////////////////
//	created:	2012/09/15
//	filename:	src\BSLib\network\tcpStubThread.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
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
	CTcpStubThread(CNetServer* netServer);
	virtual ~CTcpStubThread();

protected:
	virtual bool _addStubToNetConnectionMgr(CNetStubPtr& stubPtr, CNetConnectionCallbackPtr& netConnectionCb);
	virtual bool _delStubToNetConnectionMgr(CNetStubPtr& stubPtr);
	virtual void _wait();
	virtual void _enterRun();
	virtual void _leaveRun();

};

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_TCPSTUBTHREAD_H__