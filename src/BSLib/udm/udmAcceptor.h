#ifndef __BSLIB_UDM_UDMACCEPTOR_H__
#define __BSLIB_UDM_UDMACCEPTOR_H__

#include <BSLib/utility/ptrQueue.h>
#include <BSLib/utility/thread/event.h>
#include "udmSocket.h"

namespace BSLib
{

namespace UDM
{

class CUdmAcceptor : public CUdmSocket
{
public:
	CUdmAcceptor(SUdmSocketInfo* udmSocketInfo);
	virtual ~CUdmAcceptor();

	virtual EUdmSocketType getUdmSocketType() { return UDM_SOCKTYPE_ACCEPTOR; }

	virtual int listen();
	virtual UDMSOCKET accept(struct sockaddr* addr, int* addrlen);
	virtual int close();

private:
	BSLib::Utility::CPtrQueue<CUdmSocket*>* m_acceptList;
	BSLib::Utility::CEvent* m_acceptEvent;
};

}//UDM

}//BSLib

#endif//__BSLIB_UDM_UDMACCEPTOR_H__



