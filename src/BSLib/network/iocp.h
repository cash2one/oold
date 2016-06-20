//////////////////////////////////////////////////////////////////////
//	created:	2012/07/24
//	filename:	src\BSLib\network\iocp.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_NETWORK_IOCP_H__
#define __BSLIB_NETWORK_IOCP_H__

#include <BSLib/network/baseDef.h>

namespace BSLib
{

namespace Network
{

struct SEpollEvent;

class CIOCP
{
public:
	CIOCP(int maxConcurrency = -1) : m_iocp(NULL)
	{
		if( maxConcurrency != -1 ){
			create(maxConcurrency);
		}
	}

	~CIOCP()
	{
		if( m_iocp != NULL ) {
			::CloseHandle(m_iocp);
		}
	}

public:
	bool isOpen() const
	{
		return m_iocp != NULL;
	}

	bool close()
	{
		BOOL res = ::CloseHandle(m_iocp);
		m_iocp = NULL;
		return res == TRUE;
	}

	bool create(int maxConcurrency = 0)
	{
		m_iocp = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, maxConcurrency);
		return m_iocp != NULL;
	}

	bool associateSocket(SOCKET sock, ULONG_PTR compKey)
	{
		if (m_iocp == NULL) {
			return false;
		}
		return (::CreateIoCompletionPort((HANDLE)sock, m_iocp, compKey, 0) == m_iocp);
	}

	bool postStatus(ULONG_PTR compKey, DWORD numBytes = 0, SEpollEvent* tcpEvent = NULL)
	{
		if (m_iocp == NULL) {
			return false;
		}

		return ::PostQueuedCompletionStatus(m_iocp, numBytes, compKey, (OVERLAPPED*)tcpEvent) == TRUE;
	}

	bool getStatus(ULONG_PTR *compKey, PDWORD numBytes, SEpollEvent** tcpEvent, DWORD milliseconds = INFINITE)
	{
		if (m_iocp == NULL) {
			return false;
		}
		return TRUE == ::GetQueuedCompletionStatus(m_iocp, numBytes, compKey, (OVERLAPPED**)tcpEvent, milliseconds);
	}

	HANDLE getHandle() const
	{
		return m_iocp;
	}

private:
	HANDLE m_iocp;
};

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_IOCP_H__

