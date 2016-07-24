#ifndef __BSLIB_UDM_UDMEPOLL_H__
#define __BSLIB_UDM_UDMEPOLL_H__

#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/ptrQueue.h>
#include <BSLib/utility/thread/event.h>
#include <BSLib/utility/thread/mutex.h>
#include "udmSocketInfo.h"

namespace BSLib
{

namespace UDM
{

class CUdmEpoll
{
public:
	CUdmEpoll(int eid);
	virtual ~CUdmEpoll();

	bool isValid() { return m_isValid; }
	int epollCreate();
	int epollAddSock(const UDMSOCKET udmSocket, int udmEpollEvent, void* tempData);
	int epollDelSock(const UDMSOCKET udmSocket, int udmEpollEvent);
	int epollWait(SEpollEvent* epollList, int epollListCount, int msTimeOut);
	int epollRelease();
	int createEpollEventQueue(SUdmSocketInfo* udmSocketInfo);

private:
	int _epollWait(SEpollEvent* epollList, int epollListCount);

private:
	bool m_isValid;
	BSLib::Utility::CEvent m_epollEvent;
	BSLib::Utility::CHashMap<int, BSLib::Utility::CPtrQueue<SUdmSocketInfo*>*> m_waitUdmSockets;

	BSLib::Utility::CPtrQueue<SUdmSocketInfo*> m_selfEvents;
	BSLib::Utility::CMutex m_mutex;
};

}//UDM

}//BSLib

#endif//__BSLIB_UDM_UDMEPOLL_H__




