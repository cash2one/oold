#include "udmEpollMgr.h"

namespace BSLib
{

namespace UDM
{

BSLIB_SINGLETON_DEFINE(CUdmEpollMgr);

CUdmEpollMgr::CUdmEpollMgr()
: m_udmEpollPos(0)
{
	for (int i=0; i<BSLIB_UDM_EPOLL_MAX; ++i){
		m_udmEpolls[i] = NULL;
	}
}

CUdmEpollMgr::~CUdmEpollMgr()
{
	for (int i=0; i<BSLIB_UDM_EPOLL_MAX; ++i){
		if (m_udmEpolls[i] != NULL) {
			BSLIB_SAFE_DELETE(m_udmEpolls[i]);
		}
	}
}

int CUdmEpollMgr::epollCreate()
{
	m_mutex.lock();
	int epollID = BSLIB_UDM_ERROR;
	for (int i=0; i<BSLIB_UDM_EPOLL_MAX; ++i){
		if (m_udmEpolls[m_udmEpollPos] == NULL) {
			CUdmEpoll* edmEpoll = new CUdmEpoll(m_udmEpollPos);
			if (edmEpoll == NULL) {
				m_mutex.unlock();
				return epollID;
			}
			m_udmEpolls[m_udmEpollPos] = edmEpoll;
			m_udmEpolls[m_udmEpollPos]->epollCreate();
			m_udmEpollPos = m_udmEpollPos + 1;
			epollID = m_udmEpollPos;
			m_mutex.unlock();
			return epollID;
		}
		if (!m_udmEpolls[m_udmEpollPos]->isValid()) {
			m_udmEpolls[m_udmEpollPos]->epollCreate();
			m_udmEpollPos = m_udmEpollPos + 1;
			epollID = m_udmEpollPos;
			m_mutex.unlock();
			return epollID;
		}
		m_udmEpollPos = (m_udmEpollPos + 1) % BSLIB_UDM_EPOLL_MAX;
	}
	return epollID;
}

int CUdmEpollMgr::epollAddSock(const int eid, const UDMSOCKET udmSocket, int udmEpollEvent, void* tempData)
{
	if (eid < 0 || eid >= BSLIB_UDM_EPOLL_MAX) {
		return BSLIB_UDM_ERROR;
	}
	int epollPos = eid - 1;
	if (m_udmEpolls[epollPos] == NULL) {
		return BSLIB_UDM_ERROR;
	}
	return m_udmEpolls[epollPos]->epollAddSock(udmSocket, udmEpollEvent, tempData);
}

int CUdmEpollMgr::epollDelSock(const int eid, const UDMSOCKET udmSocket, int udmEpollEvent)
{
	if (eid < 0 || eid >= BSLIB_UDM_EPOLL_MAX) {
		return BSLIB_UDM_ERROR;
	}
	int epollPos = eid - 1;
	if (m_udmEpolls[epollPos] == NULL) {
		return BSLIB_UDM_ERROR;
	}
	return m_udmEpolls[epollPos]->epollDelSock(udmSocket, udmEpollEvent);
}

int CUdmEpollMgr::epollWait(const int eid, SEpollEvent* epollList, int epollListCount, int msTimeOut)
{
	if (eid < 0 || eid >= BSLIB_UDM_EPOLL_MAX) {
		return BSLIB_UDM_ERROR;
	}
	int epollPos = eid - 1;
	if (m_udmEpolls[epollPos] == NULL) {
		return BSLIB_UDM_ERROR;
	}
	return m_udmEpolls[epollPos]->epollWait(epollList, epollListCount, msTimeOut);
}

int CUdmEpollMgr::epollRelease(const int eid)
{
	if (eid < 0 || eid >= BSLIB_UDM_EPOLL_MAX) {
		return BSLIB_UDM_ERROR;
	}
	int epollPos = eid - 1;
	if (m_udmEpolls[epollPos] == NULL) {
		return BSLIB_UDM_ERROR;
	}
	return m_udmEpolls[epollPos]->epollRelease();
}

}//UDM

}//BSLib


