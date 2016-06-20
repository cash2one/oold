//////////////////////////////////////////////////////////////////////
//	created:	2012/07/28
//	filename:	src\BSLib\network\sockEvent.hpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_NETWORK_SOCKEVENT_H__
#define __BSLIB_NETWORK_SOCKEVENT_H__

#ifdef WIN32

#include <WinSock2.h>

#include <vector>
#include <BSLib/utility/thread/mutex.h>

#define WSAEVENT_MAX 64

namespace BSLib
{

namespace Network
{

class CSocketEvent
{
private:
	struct SSocketEventItem
	{
		SOCKET m_sock;
		long m_event;
	};

public:
	CSocketEvent()
	{
		m_eventCount = 0;
		for (int i=0; i<WSAEVENT_MAX; ++i){
			m_sockList[i] = INVALID_SOCKET;
			m_wsaEventHandle[i] = NULL;
		}
	}

	~CSocketEvent()
	{
		for (int i=0; i<WSAEVENT_MAX; ++i){
			if (m_wsaEventHandle[i] != NULL) {
				::WSACloseEvent(m_wsaEventHandle[i]);
				m_wsaEventHandle[i] = NULL;
			}
		}
	}

	bool addSocket(SOCKET sock, long e)
	{
		SSocketEventItem item;
		item.m_sock = sock;
		item.m_event = e;

		m_mutex.lock();
		m_addList.push_back(item);
		m_mutex.unlock();
		return true;
	}

	bool delSocket(SOCKET sock)
	{
		m_mutex.lock();
		m_delList.push_back(sock);
		m_mutex.unlock();
		return true;
	}

	bool waitSocket(SOCKET& sock, long& e, int timeout)
	{
		if (m_addList.size() > 0){
			_addEvent();
		}

		if (m_delList.size() > 0) {
			_delEvent();
		}

		if (m_eventCount == 0) {
			::Sleep(timeout);
			return false;
		}

		DWORD res = WSAWaitForMultipleEvents(m_eventCount, m_wsaEventHandle, FALSE, timeout, FALSE);
		switch(res)
		{
			case  WSA_WAIT_TIMEOUT:
			{
				break;
			} 
			case WSA_WAIT_FAILED:
			{
				break;
			} 
			default:
			{
				int pos = res - WSA_WAIT_EVENT_0;
				if (pos >= 0 && pos < WSAEVENT_MAX){
					if (m_sockList[pos] != INVALID_SOCKET && m_wsaEventHandle[pos] != NULL){
						sock = m_sockList[pos];

						WSANETWORKEVENTS wsaEvent;
						::WSAEnumNetworkEvents(sock, m_wsaEventHandle[pos], &wsaEvent);

						e = wsaEvent.lNetworkEvents;

						::WSAResetEvent(m_wsaEventHandle[pos]);
						return true;
					}
				}
				break;
			}
		}
		return false;
	}

protected:
	void _addEvent()
	{
		m_mutex.lock();
		for (uint32 i=0; i<m_addList.size(); ++i) {
			int j=0;
			for (; j<m_eventCount; ++j) {
				if (m_sockList[j] == m_addList[i].m_sock){
					break;
				}
			}
			if (j < m_eventCount) {
				continue;
			}

			WSAEVENT wsaEvent = WSACreateEvent();
			if (wsaEvent == NULL){
				continue;
			}
			if (WSAEventSelect(m_addList[i].m_sock, wsaEvent, m_addList[i].m_event) == SOCKET_ERROR) {
				::WSACloseEvent(wsaEvent);
				continue;
			}
			m_sockList[m_eventCount] = m_addList[i].m_sock;
			m_wsaEventHandle[m_eventCount] = wsaEvent;
			m_eventCount++;
		}
		m_addList.clear();
		m_mutex.unlock();
	}
	void _delEvent()
	{
		m_mutex.lock();
		for (uint32 i=0; i<m_delList.size(); ++i) {
			int j=0;
			for (; j<m_eventCount; ++j) {
				if (m_sockList[j] == m_delList[i]){
					break;
				}
			}
			if (j >= m_eventCount) {
				continue;
			}
			::WSACloseEvent(m_wsaEventHandle[j]);

			for (; j<m_eventCount-1; ++j) {
				m_wsaEventHandle[j] = m_wsaEventHandle[j+1];
				m_sockList[j] = m_sockList[j+1];
			}
			m_eventCount--;
			m_sockList[m_eventCount] = INVALID_SOCKET;
			m_wsaEventHandle[m_eventCount] = NULL;
		}
		m_delList.clear();
		m_mutex.unlock();
	}

private:
	SOCKET m_sockList[WSAEVENT_MAX];
	WSAEVENT m_wsaEventHandle[WSAEVENT_MAX];
	long m_event[WSAEVENT_MAX];
	int m_eventCount;
	BSLib::Utility::CMutex m_mutex;
	std::vector<SSocketEventItem> m_addList;
	std::vector<SOCKET> m_delList;
};

}//Network

}//BSLib

#endif//WIN32

#endif//__BSLIB_NETWORK_SOCKEVENT_H__
