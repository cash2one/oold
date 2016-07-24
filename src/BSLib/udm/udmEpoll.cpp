#include "udmEpoll.h"
#include "udmMgr.h"
#include "udmSocket.h"
#include "udpThreadMgr.h"

namespace BSLib
{

namespace UDM
{

CUdmEpoll::CUdmEpoll(int eid)
: m_isValid(false)
{
	;
}

CUdmEpoll::~CUdmEpoll()
{
	;
}

int CUdmEpoll::epollCreate()
{
	m_isValid = true;
	m_selfEvents.clear();
	m_waitUdmSockets.clear();
	return BSLIB_UDM_OK;
}

int CUdmEpoll::epollAddSock(const UDMSOCKET udmSocket, int udmEpollEvent, void* tempData)
{
	SUdmSocketInfo* udmSocketInfo = CUdmMgr::singleton().getUdmSocketInfo(udmSocket);
	if (udmSocketInfo == NULL){
		return BSLIB_UDM_ERROR;
	}
	SUdmEpollInfo* udmEpollInfo = udmSocketInfo->m_udmEpollInfo;
	if (udmEpollInfo == NULL) {
		udmEpollInfo = new SUdmEpollInfo();
		if (udmEpollInfo == NULL) {
			return BSLIB_UDM_ERROR;
		}
		udmEpollInfo->m_epollTempData = tempData;
		udmEpollInfo->m_epollEventType = 0;
		udmSocketInfo->m_udmEpollInfo = udmEpollInfo;
	} else {
		if (tempData != NULL) {
			udmEpollInfo->m_epollTempData = tempData;
		}
	}
	if (udmSocketInfo->m_udpThreadID != -1) {
		if (createEpollEventQueue(udmSocketInfo) == BSLIB_UDM_ERROR) {
			return BSLIB_UDM_ERROR;
		}
	}
	if (udmEpollEvent & UDM_EPOLL_WRITE) {
		if (udmSocketInfo->m_udmStatus == UDM_STATE_OPEN) {
			udmEpollInfo->m_canWrite = true;
		}
	}
	if (udmEpollEvent & UDM_EPOLL_READ) {
		CUdmSocket* udmSocket = udmSocketInfo->m_udmSocketPtr;
		if (udmSocket != NULL && udmSocket->canRead()) {
			udmEpollInfo->m_canRead = true;
		}
	}
	if (udmEpollEvent & UDM_EPOLL_ERROR) {
		if ((udmSocketInfo->m_udmStatus == UDM_STATE_BROKEN)) {
			udmEpollInfo->m_isBreak = true;
		}
	}
	udmEpollInfo->m_epollEventType |= udmEpollEvent;
	if (udmEpollInfo->m_isBreak == false && udmEpollInfo->m_canRead == false && udmEpollInfo->m_canWrite == false) {
		return BSLIB_UDM_OK;
	}
	m_mutex.lock();
	m_selfEvents.push(udmSocketInfo);
	m_mutex.unlock();
	return BSLIB_UDM_OK;
}

int CUdmEpoll::epollDelSock(const UDMSOCKET udmSocket, int udmEpollEvent)
{
	SUdmSocketInfo* udmSocketInfo = CUdmMgr::singleton().getUdmSocketInfo(udmSocket);
	if (udmSocketInfo == NULL){
		return BSLIB_UDM_ERROR;
	}
	SUdmEpollInfo* udmEpollInfo = udmSocketInfo->m_udmEpollInfo;
	if (udmEpollInfo == NULL) {
		return BSLIB_UDM_OK;
	}
	udmEpollInfo->m_epollEventType &= ~udmEpollEvent;
	if (udmEpollEvent & UDM_EPOLL_WRITE) {
		udmEpollInfo->m_canWrite = false;
	}
	if (udmEpollEvent & UDM_EPOLL_READ) {
		udmEpollInfo->m_canRead = false;
	}
	if (udmEpollEvent & UDM_EPOLL_ERROR) {
		udmEpollInfo->m_isBreak = false;
	}
	return BSLIB_UDM_OK;
}

int CUdmEpoll::epollWait(SEpollEvent* epollList, int epollListCount, int msTimeOut)
{
	if (epollListCount <= 0 || !m_isValid){
		return 0;
	}
	int epollCount = _epollWait(epollList,  epollListCount);
	if (epollCount > 0) {
		return epollCount;
	}
	if (m_epollEvent.wait(msTimeOut) < 0){
		return 0;
	}
	return _epollWait(epollList,  epollListCount);
}

int CUdmEpoll::epollRelease()
{
	m_isValid = true;
	return BSLIB_UDM_OK;
}

int CUdmEpoll::_epollWait(SEpollEvent* epollList, int epollListCount)
{
	int epoll_i = 0;

	m_mutex.lock();

	SUdmSocketInfo* epollEvent = NULL;
	m_selfEvents.pop(epollEvent);

	while(epollEvent != NULL) {
		SUdmEpollInfo* udmEpollInfo = epollEvent->m_udmEpollInfo;
		if (udmEpollInfo != NULL) {
			epollList[epoll_i].m_udmEpollEvent = 0;
			if (udmEpollInfo->m_isBreak) {
				epollList[epoll_i].m_udmEpollEvent |= UDM_EPOLL_ERROR;
				//udmEpollInfo->m_isBreak = false;
			}
			if (udmEpollInfo->m_canRead) {
				epollList[epoll_i].m_udmEpollEvent |= UDM_EPOLL_READ;
				udmEpollInfo->m_canRead = false;
			}
			if (udmEpollInfo->m_canWrite) {
				epollList[epoll_i].m_udmEpollEvent |= UDM_EPOLL_WRITE;
				udmEpollInfo->m_canWrite = false;
			}
			if (epollList[epoll_i].m_udmEpollEvent != 0) {
				epollList[epoll_i].m_udmSocket = epollEvent->m_udmID;
				epollList[epoll_i].m_tempData = udmEpollInfo->m_epollTempData;
				++epoll_i;
				if (epoll_i >= epollListCount){
					m_mutex.unlock();
					return epoll_i;
				}
			}	
		}
		epollEvent = NULL;
		m_selfEvents.pop(epollEvent);
	}

	BSLib::Utility::CHashMap<int, BSLib::Utility::CPtrQueue<SUdmSocketInfo*>*>::iterator it = m_waitUdmSockets.begin();
	for (; it != m_waitUdmSockets.end(); ++it){
		BSLib::Utility::CPtrQueue<SUdmSocketInfo*>* ptrQueue = it->second;
		if (ptrQueue == NULL){
			continue;
		}
		SUdmSocketInfo* epollEvent = NULL;
		ptrQueue->pop(epollEvent);
		while(epollEvent != NULL) {
			SUdmEpollInfo* udmEpollInfo = epollEvent->m_udmEpollInfo;
			if (udmEpollInfo != NULL) {
				epollList[epoll_i].m_udmEpollEvent = 0;
				if (udmEpollInfo->m_isBreak) {
					epollList[epoll_i].m_udmEpollEvent |= UDM_EPOLL_ERROR;
					//udmEpollInfo->m_isBreak = false;
				}
				if (udmEpollInfo->m_canRead) {
					epollList[epoll_i].m_udmEpollEvent |= UDM_EPOLL_READ;
					udmEpollInfo->m_canRead = false;
				}
				if (udmEpollInfo->m_canWrite) {
					epollList[epoll_i].m_udmEpollEvent |= UDM_EPOLL_WRITE;
					udmEpollInfo->m_canWrite = false;
				}
				if (epollList[epoll_i].m_udmEpollEvent != 0) {
					epollList[epoll_i].m_udmSocket = epollEvent->m_udmID;
					epollList[epoll_i].m_tempData = udmEpollInfo->m_epollTempData;
					++epoll_i;
					if (epoll_i >= epollListCount){
						m_mutex.unlock();
						return epoll_i;
					}
				}	
			}
			epollEvent = NULL;
			ptrQueue->pop(epollEvent);
		}
	}
	m_mutex.unlock();
	return epoll_i;
}

int CUdmEpoll::createEpollEventQueue(SUdmSocketInfo* udmSocketInfo)
{
	SUdmEpollInfo* udmEpollInfo = udmSocketInfo->m_udmEpollInfo;
	if (udmEpollInfo == NULL) {
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfo->m_udpThreadID == -1) {
		return BSLIB_UDM_ERROR;
	}
	
	BSLib::Utility::CPtrQueue<SUdmSocketInfo*>* udmEpollEventQueue = NULL;
	m_mutex.lock();
	BSLib::Utility::CHashMap<int, BSLib::Utility::CPtrQueue<SUdmSocketInfo*>*>::iterator it = m_waitUdmSockets.find(udmSocketInfo->m_udpThreadID);
	if (it == m_waitUdmSockets.end()) {
		udmEpollEventQueue = new BSLib::Utility::CPtrQueue<SUdmSocketInfo*>();
		if (udmEpollEventQueue == NULL) {
			m_mutex.unlock();
			return BSLIB_UDM_ERROR;
		}
		m_waitUdmSockets.setValue(udmSocketInfo->m_udpThreadID, udmEpollEventQueue);
	} else {
		udmEpollEventQueue = it->second;
		if (udmEpollEventQueue == NULL) {
			m_mutex.unlock();
			return BSLIB_UDM_ERROR;
		}
	}
	m_mutex.unlock();
	udmEpollInfo->m_epollEventQueue = udmEpollEventQueue;
	udmEpollInfo->m_epollEvent = &m_epollEvent;

	return BSLIB_UDM_OK;
}

}//UDM

}//BSLib



