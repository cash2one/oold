//////////////////////////////////////////////////////////////////////
//	created:	2012/08/20
//	filename:	src\BSLib\udm\udpThreadMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UDM_UDPTHREADMGR_H__
#define __BSLIB_UDM_UDPTHREADMGR_H__

#include <BSLib/utility/thread/mutex.h>
#include <BSLib/utility/singleton.h>
#include "udpThread.h"

namespace BSLib
{

namespace UDM
{

#define BSLIB_NETWORK_UDPTHREAD_MAX 128

class CUdpThreadMgr
{
public:
	CUdpThreadMgr();
	~CUdpThreadMgr();

	BSLIB_SINGLETON_DECLARE(CUdpThreadMgr);

	int getUdpThreadID(const struct sockaddr* name, int namelen);
	bool bind(int& udpThreadID, const struct sockaddr* name, int namelen);
	bool bind(int& udpThreadID);

	CUdpThread* getUdpThread(int udpThreadID);

	void clearAll();

private:
	CUdpThread* m_udpThreads[BSLIB_NETWORK_UDPTHREAD_MAX];
	int m_udpThreadCount;
	BSLib::Utility::CMutex m_mutex;
};

}//UDM

}//BSLib

#endif//__BSLIB_UDM_UDPTHREADMGR_H__


