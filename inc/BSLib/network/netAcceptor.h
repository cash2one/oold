#ifndef __BSLIB_NETWORK_NETACCEPTOR_H__
#define __BSLIB_NETWORK_NETACCEPTOR_H__

#include <vector>
#include <BSLib/utility/pointer.h>
#include <BSLib/network/sockAddr.h>

namespace BSLib
{

namespace Network
{

class BSLIB_NETWORK_API CNetAcceptorCallback
{
public:
	virtual ~CNetAcceptorCallback(){}
	virtual bool newConnect(int sock, CSockAddr& addrLocal, CSockAddr& addrPeer, void* tempData) = 0;
};
typedef BSLib::Utility::CPointer<CNetAcceptorCallback> CNetAcceptorCallbackPtr;

class BSLIB_NETWORK_API INetAcceptor
{
public:
	struct SAcceptorItem
	{
		CSockAddr m_addrAcceptor;
		CNetAcceptorCallbackPtr m_cbNewConnection;
		SOCKET m_sockID;
		void* m_tempData;
		
		SAcceptorItem() :m_cbNewConnection(NULL), m_sockID(INVALID_SOCKET), m_tempData(NULL) {}
	};
	typedef Utility::CPointer<SAcceptorItem> SAcceptorItemPtr;

public:
	virtual ~INetAcceptor() {}
	bool addAcceptor(CSockAddr& addrAcceptor, CNetAcceptorCallbackPtr& cbNewConnection, void* tempData);
	bool delAcceptor(CSockAddr& addrAcceptor);

	virtual bool waitSocket(int msSec) = 0;

protected:
	virtual bool _INetAcceptor_addAcceptor(SAcceptorItemPtr& item) = 0;
	virtual bool _INetAcceptor_delAcceptor(SAcceptorItemPtr& item) = 0;

protected:
	std::vector<SAcceptorItemPtr> m_accepteorList;

};

typedef BSLib::Utility::CPointer<INetAcceptor> INetAcceptorsPtr;

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_NETACCEPTOR_H__

