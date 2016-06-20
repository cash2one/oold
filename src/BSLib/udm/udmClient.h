//////////////////////////////////////////////////////////////////////
//	created:	2012/08/20
//	filename:	src\BSLib\udm\udmClient.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UDM_UDMCLIENT_H__
#define __BSLIB_UDM_UDMCLIENT_H__

#include <BSLib/utility/thread/event.h>
#include "udmSocket.h"

namespace BSLib
{

namespace UDM
{

class CUdmClient : public CUdmSocket
{
public:
	CUdmClient(SUdmSocketInfor* udmSocketInfor);
	virtual ~CUdmClient();

	virtual EUdmSocketType getUdmSocketType() { return UDM_SOCKTYPE_CLIENT; }
	virtual int connect(const struct sockaddr* name, int namelen);
	virtual int close();

	virtual bool parseCtrlMsg(SUdpCtrlMsg* msg, int msgSize, BSLib::Utility::CRealTime& realTime);
	virtual bool parseDataMsg(SUdpCtrlMsg* msg, int msgSize, BSLib::Utility::CRealTime& realTime);
	virtual void tickMsg(BSLib::Utility::CRealTime& realTime);

private:
	BSLib::Utility::CEvent m_connectEvent;
	bool m_isWaiting;

	BSLib::Utility::CDelayTimer m_pingTimeout;
	int m_pingCount;
};

}//UDM

}//BSLib

#endif//__BSLIB_UDM_UDMCLIENT_H__


