//////////////////////////////////////////////////////////////////////
//	created:	2012/09/15
//	filename:	src\BSLib\network\udpStubThread.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_NETWORK_UDPSTUBTHREAD_H__
#define __BSLIB_NETWORK_UDPSTUBTHREAD_H__

#include <BSLib/network/udpConnectionMgr.h>
#include "netStubThread.h"

namespace BSLib
{

namespace Network
{

class CUdpStubThread : public CNetStubThread, public CUdpConnectionMgr
{
public:
	CUdpStubThread(CNetServer* netServer);
	virtual ~CUdpStubThread();

protected:
	virtual bool _addStubToNetConnectionMgr(CNetStubPtr& stubPtr, CNetConnectionCallbackPtr& netConnectionCb);
	virtual bool _delStubToNetConnectionMgr(CNetStubPtr& stubPtr);
	virtual void _wait();
	virtual void _enterRun();
	virtual void _leaveRun();
};

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_UDPSTUBTHREAD_H__


