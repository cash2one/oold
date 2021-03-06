#ifndef __BSLIB_UDM_UDMSOCKETINFOR_H__
#define __BSLIB_UDM_UDMSOCKETINFOR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/ptrQueue.h>
#include <BSLib/utility/thread/event.h>
#include <BSLib/udm/baseDef.h>

namespace BSLib
{

namespace UDM
{

class CUdmSocket;
struct SUdmSocketInfo;

struct SUdmEpollInfo
{
	int m_epollEventType;
	bool m_canWrite;
	bool m_canRead;
	bool m_isBreak;
	void* m_epollTempData;
	BSLib::Utility::CEvent* m_epollEvent;
	BSLib::Utility::CPtrQueue<SUdmSocketInfo*>* m_epollEventQueue;

	SUdmEpollInfo() : m_epollEventType(0), m_canWrite(false), m_canRead(false), m_isBreak(false), m_epollTempData(NULL), m_epollEvent(NULL), m_epollEventQueue(NULL){}
};

struct SUdmSocketInfo
{
	UDMSOCKET m_udmID;
	EUdmStatus m_udmStatus;
	int m_udpThreadID;
	CUdmSocket* m_udmSocketPtr;
	SUdmEpollInfo* m_udmEpollInfo;

	SUdmSocketInfo() : m_udmID(INVALID_UDMSOCK), m_udmStatus(UDM_STATE_NULL), m_udpThreadID(-1), m_udmSocketPtr(NULL), m_udmEpollInfo(NULL){}
	~SUdmSocketInfo(){}
};

enum EUdmSocketType
{
	UDM_SOCKTYPE_CLIENT,
	UDM_SOCKTYPE_STUB,
	UDM_SOCKTYPE_ACCEPTOR,
};

}//UDM

}//BSLib

#endif//__BSLIB_UDM_UDMSOCKETINFOR_H__


