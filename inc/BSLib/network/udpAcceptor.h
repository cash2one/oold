#ifndef __BSLIB_NETWORK_UDPACCEPTOR_H__
#define __BSLIB_NETWORK_UDPACCEPTOR_H__

#include <vector>
#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/ptrQueue.h>
#include <BSLib/utility/thread/event.h>
#include <BSLib/network/sockAddr.h>
#include <BSLib/network/netAcceptor.h>

namespace BSLib
{

namespace Network
{

class BSLIB_NETWORK_API CUdpAcceptor 
    : public INetAcceptor
{
public:
	CUdpAcceptor();
	~CUdpAcceptor();

	virtual bool waitSocket(int msSec);

protected:
	virtual bool _INetAcceptor_addAcceptor(SAcceptorItemPtr& item);
	virtual bool _INetAcceptor_delAcceptor(SAcceptorItemPtr& item);

	bool _newScoket(int udmSocket);
	void _terminateScoket(int udmSocket);

private:
	BSLib::Utility::CHashMap<int, INetAcceptor::SAcceptorItemPtr> m_udmHashMap;
	int m_udmEpollID;
};

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_UDPACCEPTOR_H__


