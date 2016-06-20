//////////////////////////////////////////////////////////////////////
//	created:	2012/08/20
//	filename:	src\BSLib\udm\udmStub.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UDM_UDMSTUB_H__
#define __BSLIB_UDM_UDMSTUB_H__

#include "udmSocket.h"

namespace BSLib
{

namespace UDM
{

class CUdmStub : public CUdmSocket
{
public:
	CUdmStub(SUdmSocketInfor* udmSocketInfor, BSLib::Utility::CRealTime& realTime);
	virtual ~CUdmStub();

	virtual EUdmSocketType getUdmSocketType() { return UDM_SOCKTYPE_STUB; }
	virtual int close();
	
	virtual bool parseCtrlMsg(SUdpCtrlMsg* msg, int msgSize, BSLib::Utility::CRealTime& realTime);
	virtual bool parseDataMsg(SUdpCtrlMsg* msg, int msgSize, BSLib::Utility::CRealTime& realTime);
	virtual void tickMsg(BSLib::Utility::CRealTime& realTime);

private:
	sockaddr_in m_peerSocketAddr;
	BSLib::Utility::CDelayTimer m_pingTimeout;
	int m_pingCount;
};

}//UDM

}//BSLib

#endif//__BSLIB_UDM_UDMSTUB_H__



