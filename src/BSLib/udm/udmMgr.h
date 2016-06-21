#ifndef __BSLIB_UDM_UDMMGR_H__
#define __BSLIB_UDM_UDMMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/thread/mutex.h>
#include "udmSocketInfor.h"

#define BSLIB_UDM_SOCKET_MAX BSLIB_UINT16_MAX

namespace BSLib
{

namespace UDM
{

class CUdmMgr
{
public:
	CUdmMgr();
	virtual ~CUdmMgr();

	BSLIB_SINGLETON_DECLARE(CUdmMgr);

	UDMSOCKET udmSocket();
	UDMSOCKET udmSocket(SUdmSocketInfor* udmSocketInfor);

	int bind(UDMSOCKET udmID, const struct sockaddr* name, int namelen);
	int bind(UDMSOCKET udmID, UDMSOCKET existUdmId);
	int listen(UDMSOCKET udmID);
	UDMSOCKET accept(UDMSOCKET udmID, struct sockaddr* addr, int* addrlen);
	int connect(UDMSOCKET udmID, const struct sockaddr* name, int namelen);
	int close(UDMSOCKET udmID);

	int getPeerName(UDMSOCKET udmID, struct sockaddr* name, int* namelen);
	int getSockName(UDMSOCKET udmID, struct sockaddr* name, int* namelen);
	EUdmStatus getSockState(UDMSOCKET udmID);
	
	int getLastError();
	void setlasterror(int error);

	int send(UDMSOCKET udmID, const char* buf, int len);
	int recv(UDMSOCKET udmID, char* buf, int len);

	int sendTo(UDMSOCKET udmID, const char* buf, int len);
	int recvFrom(UDMSOCKET udmID, char* buf, int len);

	SUdmSocketInfor* getUdmSocketInfor(UDMSOCKET udmID);

private:
	void _startUp();
	void _cleanUp();

private:
	SUdmSocketInfor* m_udpSocketInfor[BSLIB_UDM_SOCKET_MAX];
	int m_currtUdmSocketInforPos;
	BSLib::Utility::CMutex m_mutex;
};

}//UDM

}//BSLib

#endif//__BSLIB_UDM_UDMMGR_H__



