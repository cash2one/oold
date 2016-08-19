#ifndef __BSLIB_NETWORK_EPOLL_H__
#define __BSLIB_NETWORK_EPOLL_H__

#ifndef WIN32

#include <sys/epoll.h>

#endif

#include <BSLib/network/baseDef.h>

namespace BSLib
{

namespace Network
{

class CEPoll
{
public:
	CEPoll() : m_epollHnd(-1), m_epollEventMax(0), m_epollEvents(NULL)
	{
		;
	}

	~CEPoll()
	{
		if(m_epollHnd != -1) {
			::INetConnection_close(m_epollHnd);
			m_epollHnd = -1;
		}
		if (m_epollEvents != NULL) {
			BSLIB_SAFE_DELETE_ARRAY(m_epollEvents);
			m_epollEventMax = 0;
		}
	}

public:
	bool isOpen() const
	{
		return m_epollHnd != -1;
	}

	void INetConnection_close()
	{
		::INetConnection_close(m_epollHnd);
		m_epollHnd = -1;
	}

	bool create(int maxEvents = 0)
	{
		m_epollEvents = new epoll_event[maxEvents];
		if (m_epollEvents == NULL) {
			return false;
		}
		m_epollHnd = ::epoll_create(maxEvents);
		if (m_epollHnd == -1) {
			BSLIB_SAFE_DELETE_ARRAY(m_epollEvents);
			return false;
		}
		m_epollEventMax = maxEvents;
		return true;
	}

	bool addEpollEvent(SOCKET sock, uint32 events, void* data)
	{
		if (m_epollHnd == -1) {
			return false;
		}
		if (sock == INVALID_SOCKET) {
			return false;
		}
		epoll_event addEvent;
		addEvent.events = events;
		addEvent.data.ptr = data;

		if (::epoll_ctl(m_epollHnd, EPOLL_CTL_ADD, sock, &addEvent) < 0) {
			return false;
		}
		return true;
	}

	bool delEpollEvent(SOCKET sock)
	{
		if (m_epollHnd == -1) {
			return false;
		}

		if (m_epollHnd == -1) {
			return false;
		}
		if (sock == INVALID_SOCKET) {
			return false;
		}
		epoll_event addEvent;
		addEvent.events = 0;
		addEvent.data.ptr = NULL;

		if (::epoll_ctl(m_epollHnd, EPOLL_CTL_DEL, sock, &addEvent) < 0) {
			return false;
		}
		return true;
	}

	bool modEpollEvent(SOCKET sock, uint32 events, void* data)
	{
		if (m_epollHnd == -1) {
			return false;
		}

		if (m_epollHnd == -1) {
			return false;
		}
		if (sock == INVALID_SOCKET) {
			return false;
		}
		epoll_event addEvent;
		addEvent.events = events;
		addEvent.data.ptr = data;

		if (::epoll_ctl(m_epollHnd, EPOLL_CTL_MOD, sock, &addEvent) < 0) {
			return false;
		}
		return true;
	}


	int wait(uint32 milliseconds)
	{
		if (m_epollHnd == -1) {
			return -1;
		}
		int countEvents = ::epoll_wait(m_epollHnd, m_epollEvents, m_epollEventMax, milliseconds);
		if (countEvents < 0) {
			if (errno == EINTR) {
				return 0;
			}
			return -1;
		}
		return countEvents;
	}

	epoll_event* getEpollEvent(int eventsPos)
	{
		if (m_epollEvents == NULL) {
			return NULL;
		}
		if (eventsPos < 0 || eventsPos >= m_epollEventMax) {
			return NULL;
		}
		return &m_epollEvents[eventsPos];
	}

private:
	int m_epollHnd;
	int m_epollEventMax;
	epoll_event* m_epollEvents;
};

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_EPOLL_H__

