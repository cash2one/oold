#ifndef __BSLIB_UDM_UDPTHREAD_H__
#define __BSLIB_UDM_UDPTHREAD_H__

#include <BSLib/utility/thread/event.h>
#include <BSLib/utility/ptrQueue.h>
#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/thread/thread.h>
#include <BSLib/utility/dateTime.h>
#include "udmSocketInfo.h"
#include "udpCtrlMsg.h"
#include "udmClient.h"
#include "udmStub.h"
#include "udmAcceptor.h"

#define BSLIB_UDM_UDP_GROUP 20

namespace BSLib
{

namespace UDM
{
#ifdef WIN32

	class CSocketEvent;

#else

	class CEPoll;

#endif

class CUdpThread : public BSLib::Utility::CThread
{
public:
	CUdpThread(int udpThreadID);
	~CUdpThread();

	bool compareLocalAddr(const struct sockaddr* name, int namelen);
	bool socket();
	bool socket(const struct sockaddr* name, int namelen);
	int sendTo(SUdpCtrlMsg* msg, int msgLen, const struct sockaddr* peerName, int peerNameLen);

	void getAcceptInfor(BSLib::Utility::CEvent*& e, BSLib::Utility::CPtrQueue<CUdmSocket*>*& acceptList);
	void setAcceptor(bool beginNow) { m_beginAccept = beginNow; }
	
	void getLocalAddr(sockaddr* name, int* namelen);
	bool isRunning() { return m_isRunning; }
	void terminate() { m_isRunning = false; }

	void addUdmAcceptor(CUdmAcceptor* udmAcceptor);
	void addUdmClient(CUdmClient* udmClient);
	bool addUdmStub(CUdmStub* udmStub);

private:
	virtual void _run();
	void _tickUdpPeer(int group);
	bool _recv(SOCKET tcpSocket);
	CUdmSocket* _getUdpSocket(sockaddr* peerSockAddr);
	CUdmSocket* _createUdpSocket(sockaddr* peerSockAddr);
	void _addUdpSocket(CUdmSocket* udmSocket);
	void _delUdpSocket(CUdmSocket* udmSocket);
	bool _socket(const struct sockaddr* name, int namelen);
	void _checkUdmClient();

private:
	SYSSOCKET m_sysSocket;
	sockaddr_in m_localAddr;

#ifdef WIN32

	CSocketEvent* m_socketEvent;

#else

	CEPoll* m_epoll;

#endif

	bool m_isRunning;

	BSLib::Utility::CHashMap<uint64, CUdmSocket*> m_udpPeerBySockAddr;
	std::list<CUdmSocket*> m_groups[BSLIB_UDM_UDP_GROUP];

 	BSLib::Utility::CPtrQueue<CUdmSocket*> m_acceptList;
 	BSLib::Utility::CEvent m_acceptEvent;
	bool m_beginAccept;
	CUdmSocket* m_acceptor;

	int m_udpThreadID;

	std::vector<CUdmSocket*> m_addUdmClientList;
	BSLib::Utility::CMutex m_mutex;

	BSLib::Utility::CRealTime m_realTime;

};

}//UDM

}//BSLib

#endif//__BSLIB_UDM_UDPTHREAD_H__


