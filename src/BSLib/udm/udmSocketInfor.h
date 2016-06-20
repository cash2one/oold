//////////////////////////////////////////////////////////////////////
//	created:	2012/08/20
//	filename:	src\BSLib\udm\udmSocketInfor.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
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
struct SUdmSocketInfor;

struct SUdmEpollInfor
{
	int m_epollEventType;
	bool m_canWrite;
	bool m_canRead;
	bool m_isBreak;
	void* m_epollTempData;
	BSLib::Utility::CEvent* m_epollEvent;
	BSLib::Utility::CPtrQueue<SUdmSocketInfor*>* m_epollEventQueue;

	SUdmEpollInfor() : m_epollEventType(0), m_canWrite(false), m_canRead(false), m_isBreak(false), m_epollTempData(NULL), m_epollEvent(NULL), m_epollEventQueue(NULL){}
};

struct SUdmSocketInfor
{
	UDMSOCKET m_udmID;
	EUdmStatus m_udmStatus;
	int m_udpThreadID;
	CUdmSocket* m_udmSocketPtr;
	SUdmEpollInfor* m_udmEpollInfor;

	SUdmSocketInfor() : m_udmID(INVALID_UDMSOCK), m_udmStatus(UDM_STATE_NULL), m_udpThreadID(-1), m_udmSocketPtr(NULL), m_udmEpollInfor(NULL){}
	~SUdmSocketInfor(){}
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

