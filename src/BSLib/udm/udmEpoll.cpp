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
	SUdmSocketInfor* udmSocketInfor = CUdmMgr::singleton().getUdmSocketInfor(udmSocket);
	if (udmSocketInfor == NULL){
		return BSLIB_UDM_ERROR;
	}
	SUdmEpollInfor* udmEpollInfor = udmSocketInfor->m_udmEpollInfor;
	if (udmEpollInfor == NULL) {
		udmEpollInfor = new SUdmEpollInfor();
		if (udmEpollInfor == NULL) {
			return BSLIB_UDM_ERROR;
		}
		udmEpollInfor->m_epollTempData = tempData;
		udmEpollInfor->m_epollEventType = 0;
		udmSocketInfor->m_udmEpollInfor = udmEpollInfor;
	} else {
		if (tempData != NULL) {
			udmEpollInfor->m_epollTempData = tempData;
		}
	}
	if (udmSocketInfor->m_udpThreadID != -1) {
		if (createEpollEventQueue(udmSocketInfor) == BSLIB_UDM_ERROR) {
			return BSLIB_UDM_ERROR;
		}
	}
	if (udmEpollEvent & UDM_EPOLL_WRITE) {
		if (udmSocketInfor->m_udmStatus == UDM_STATE_OPEN) {
			udmEpollInfor->m_canWrite = true;
		}
	}
	if (udmEpollEvent & UDM_EPOLL_READ) {
		CUdmSocket* udmSocket = udmSocketInfor->m_udmSocketPtr;
		if (udmSocket != NULL && udmSocket->canRead()) {
			udmEpollInfor->m_canRead = true;
		}
	}
	if (udmEpollEvent & UDM_EPOLL_ERROR) {
		if ((udmSocketInfor->m_udmStatus == UDM_STATE_BROKEN)) {
			udmEpollInfor->m_isBreak = true;
		}
	}
	udmEpollInfor->m_epollEventType |= udmEpollEvent;
	if (udmEpollInfor->m_isBreak == false && udmEpollInfor->m_canRead == false && udmEpollInfor->m_canWrite == false) {
		return BSLIB_UDM_OK;
	}
	m_mutex.lock();
	m_selfEvents.push(udmSocketInfor);
	m_mutex.unlock();
	return BSLIB_UDM_OK;
}

int CUdmEpoll::epollDelSock(const UDMSOCKET udmSocket, int udmEpollEvent)
{
	SUdmSocketInfor* udmSocketInfor = CUdmMgr::singleton().getUdmSocketInfor(udmSocket);
	if (udmSocketInfor == NULL){
		return BSLIB_UDM_ERROR;
	}
	SUdmEpollInfor* udmEpollInfor = udmSocketInfor->m_udmEpollInfor;
	if (udmEpollInfor == NULL) {
		return BSLIB_UDM_OK;
	}
	udmEpollInfor->m_epollEventType &= ~udmEpollEvent;
	if (udmEpollEvent & UDM_EPOLL_WRITE) {
		udmEpollInfor->m_canWrite = false;
	}
	if (udmEpollEvent & UDM_EPOLL_READ) {
		udmEpollInfor->m_canRead = false;
	}
	if (udmEpollEvent & UDM_EPOLL_ERROR) {
		udmEpollInfor->m_isBreak = false;
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

	SUdmSocketInfor* epollEvent = NULL;
	m_selfEvents.pop(epollEvent);

	while(epollEvent != NULL) {
		SUdmEpollInfor* udmEpollInfor = epollEvent->m_udmEpollInfor;
		if (udmEpollInfor != NULL) {
			epollList[epoll_i].m_udmEpollEvent = 0;
			if (udmEpollInfor->m_isBreak) {
				epollList[epoll_i].m_udmEpollEvent |= UDM_EPOLL_ERROR;
				//udmEpollInfor->m_isBreak = false;
			}
			if (udmEpollInfor->m_canRead) {
				epollList[epoll_i].m_udmEpollEvent |= UDM_EPOLL_READ;
				udmEpollInfor->m_canRead = false;
			}
			if (udmEpollInfor->m_canWrite) {
				epollList[epoll_i].m_udmEpollEvent |= UDM_EPOLL_WRITE;
				udmEpollInfor->m_canWrite = false;
			}
			if (epollList[epoll_i].m_udmEpollEvent != 0) {
				epollList[epoll_i].m_udmSocket = epollEvent->m_udmID;
				epollList[epoll_i].m_tempData = udmEpollInfor->m_epollTempData;
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

	BSLib::Utility::CHashMap<int, BSLib::Utility::CPtrQueue<SUdmSocketInfor*>*>::iterator it = m_waitUdmSockets.begin();
	for (; it != m_waitUdmSockets.end(); ++it){
		BSLib::Utility::CPtrQueue<SUdmSocketInfor*>* ptrQueue = it->second;
		if (ptrQueue == NULL){
			continue;
		}
		SUdmSocketInfor* epollEvent = NULL;
		ptrQueue->pop(epollEvent);
		while(epollEvent != NULL) {
			SUdmEpollInfor* udmEpollInfor = epollEvent->m_udmEpollInfor;
			if (udmEpollInfor != NULL) {
				epollList[epoll_i].m_udmEpollEvent = 0;
				if (udmEpollInfor->m_isBreak) {
					epollList[epoll_i].m_udmEpollEvent |= UDM_EPOLL_ERROR;
					//udmEpollInfor->m_isBreak = false;
				}
				if (udmEpollInfor->m_canRead) {
					epollList[epoll_i].m_udmEpollEvent |= UDM_EPOLL_READ;
					udmEpollInfor->m_canRead = false;
				}
				if (udmEpollInfor->m_canWrite) {
					epollList[epoll_i].m_udmEpollEvent |= UDM_EPOLL_WRITE;
					udmEpollInfor->m_canWrite = false;
				}
				if (epollList[epoll_i].m_udmEpollEvent != 0) {
					epollList[epoll_i].m_udmSocket = epollEvent->m_udmID;
					epollList[epoll_i].m_tempData = udmEpollInfor->m_epollTempData;
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

int CUdmEpoll::createEpollEventQueue(SUdmSocketInfor* udmSocketInfor)
{
	SUdmEpollInfor* udmEpollInfor = udmSocketInfor->m_udmEpollInfor;
	if (udmEpollInfor == NULL) {
		return BSLIB_UDM_ERROR;
	}
	if (udmSocketInfor->m_udpThreadID == -1) {
		return BSLIB_UDM_ERROR;
	}
	
	BSLib::Utility::CPtrQueue<SUdmSocketInfor*>* udmEpollEventQueue = NULL;
	m_mutex.lock();
	BSLib::Utility::CHashMap<int, BSLib::Utility::CPtrQueue<SUdmSocketInfor*>*>::iterator it = m_waitUdmSockets.find(udmSocketInfor->m_udpThreadID);
	if (it == m_waitUdmSockets.end()) {
		udmEpollEventQueue = new BSLib::Utility::CPtrQueue<SUdmSocketInfor*>();
		if (udmEpollEventQueue == NULL) {
			m_mutex.unlock();
			return BSLIB_UDM_ERROR;
		}
		m_waitUdmSockets.setValue(udmSocketInfor->m_udpThreadID, udmEpollEventQueue);
	} else {
		udmEpollEventQueue = it->second;
		if (udmEpollEventQueue == NULL) {
			m_mutex.unlock();
			return BSLIB_UDM_ERROR;
		}
	}
	m_mutex.unlock();
	udmEpollInfor->m_epollEventQueue = udmEpollEventQueue;
	udmEpollInfor->m_epollEvent = &m_epollEvent;

	return BSLIB_UDM_OK;
}

}//UDM

}//BSLib



