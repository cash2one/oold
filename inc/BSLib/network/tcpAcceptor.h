//////////////////////////////////////////////////////////////////////
//	created:	2012/07/31
//	filename: 	BSLib\network\tcpAcceptors.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_NETWORK_TCPACCEPTOR_H__
#define __BSLIB_NETWORK_TCPACCEPTOR_H__

#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/thread/thread.h>
#include <BSLib/network/netAcceptor.h>

namespace BSLib
{

namespace Network
{

#ifdef WIN32

	class CTcpEpoll;

#else

	class CEPoll;

#endif

class CTcpAcceptor : public CNetAcceptor
{
public:
	CTcpAcceptor();
	virtual ~CTcpAcceptor();

	virtual bool waitSocket(int msSec);

protected:
	virtual bool _addAcceptor(CNetAcceptor::SAcceptorItemPtr& item);
	virtual bool _delAcceptor(CNetAcceptor::SAcceptorItemPtr& item);

#ifdef WIN32
	bool _acceptScoket(SOCKET& a_tcpServerSocket, SOCKET& a_tcpPeerSocket, void* a_data);
	void _terminateScoket(SOCKET& tcpSocket, void* data);

#else
	bool _newScoket(SOCKET tcpSocket);
	void _terminateScoket(SOCKET tcpSocket);
#endif


private:
	BSLib::Utility::CHashMap<SOCKET, CNetAcceptor::SAcceptorItemPtr> m_tcpHashMap;

#ifdef WIN32

	CTcpEpoll* m_tcpEpoll;

#else

	CEPoll* m_epoll;

#endif
};

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_TCPACCEPTOR_H__
