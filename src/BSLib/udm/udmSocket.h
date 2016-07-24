#ifndef __BSLIB_UDM_UDMSOCKET_H__
#define __BSLIB_UDM_UDMSOCKET_H__

#include <BSLib/utility/dateTime.h>
#include <BSLib/utility/stream.h>
#include "udmSocketInfo.h"
#include "udpCtrlMsg.h"

#define BSLIB_UDM_UDP_BUFF_MAX  (64*1024)
#define BSLIB_UDM_PING_MAX 3
#define BSLIB_UDM_PING_TIME 3000

namespace BSLib
{

namespace UDM
{

class CUdmSocket
{
public:
	CUdmSocket(SUdmSocketInfo* udmSocketInfo);
	virtual ~CUdmSocket();

	virtual EUdmSocketType getUdmSocketType() = 0;

	virtual int listen() { return 0; }
	virtual UDMSOCKET accept(struct sockaddr* addr, int* addrlen) { return INVALID_UDMSOCK; }
	virtual int connect(const struct sockaddr* name, int namelen) { return BSLIB_UDM_ERROR; }
	virtual int close() { return BSLIB_UDM_ERROR; }
	virtual int send(const char* buff, int len);
	virtual int recv(char* buff, int len);
	virtual int sendTo(const char* buff, int len);
	virtual int recvFrom(char* buff, int len);

	int getPeerName(struct sockaddr* name, int* namelen);
	int setPeerName(const struct sockaddr* name, int namelen);
	int getSockName(struct sockaddr* name, int* namelen);
	
	virtual bool parseCtrlMsg(SUdpCtrlMsg* msg, int msgSize, BSLib::Utility::CRealTime& realTime);
	virtual bool parseDataMsg(SUdpCtrlMsg* msg, int msgSize, BSLib::Utility::CRealTime& realTime);
	virtual void tickMsg(BSLib::Utility::CRealTime& realTime);

	UDMSOCKET getUdmSocket() { return m_udmSocketInfo->m_udmID; }
	EUdmStatus getState() { return m_udmSocketInfo->m_udmStatus; }
	SUdmSocketInfo* getUdmSocketInfo() { return m_udmSocketInfo; }
	bool canRead();

	void notifyRead();
	void notifyBreak();

protected:
	bool _sendMsg(SUdpCtrlMsg* msg, int msgSize);
	

private:
	SUdmSocketInfo* m_udmSocketInfo;
	sockaddr_in m_peerAddr;

	BSLib::Utility::CStream m_readStream;
	BSLib::Utility::CMutex m_readMutex;

	int m_deleteCount;

// 	SEpollEvent* m_epollEvent;
// 	SEpollEvent m_epollEvent;
};

}//UDM

}//BSLib

#endif//__BSLIB_UDM_UDMSOCKET_H__



