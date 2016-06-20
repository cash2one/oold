//////////////////////////////////////////////////////////////////////
//	created:	2012/08/20
//	filename:	src\BSLib\udm\udmEpollMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UDM_UDMEPOLLMGR_H__
#define __BSLIB_UDM_UDMEPOLLMGR_H__

#include <BSLib/utility/thread/mutex.h>
#include <BSLib/utility/singleton.h>
#include "udmEpoll.h"

#define BSLIB_UDM_EPOLL_MAX BSLIB_UINT8_MAX

namespace BSLib
{

namespace UDM
{

class CUdmEpollMgr
{
public:
	CUdmEpollMgr();
	virtual ~CUdmEpollMgr();

	BSLIB_SINGLETON_DECLARE(CUdmEpollMgr);

	int epollCreate();
	int epollAddSock(const int eid, const UDMSOCKET udmSocket, int udmEpollEvent, void* tempData);
	int epollDelSock(const int eid, const UDMSOCKET udmSocket, int udmEpollEvent);
	int epollWait(const int eid, SEpollEvent* epollList, int epollListCount, int msTimeOut);
	int epollRelease(const int eid);

private:
	CUdmEpoll* m_udmEpolls[BSLIB_UDM_EPOLL_MAX];
	int m_udmEpollPos;
	BSLib::Utility::CMutex m_mutex;
};

}//UDM

}//BSLib

#endif//__BSLIB_UDM_UDMEPOLLMGR_H__



