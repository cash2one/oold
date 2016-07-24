#include <BSLib/utility/tracer.h>
#include "netStubPool.h"
#include "tcpStubThread.h"
#include "udpStubThread.h"

namespace BSLib
{

namespace Network
{

CNetStubPool::CNetStubPool(INetServer* netServer, ENetType netType)
: m_netServer(netServer)
, m_netType(netType)
, m_maxStub(0)
, m_countPerThd(0)
, m_countThread(0)
, m_recvBytesCount(0)
, m_sendBytesCount(0)
, m_seconds(0)
{
	;
}

CNetStubPool::~CNetStubPool()
{
	;
}

bool CNetStubPool::init(const uint32 maxStub, uint32 countPerThd, const uint32 minThread)
{
	m_maxStub = maxStub;
	m_countPerThd = countPerThd;
	m_countThread = minThread;
	m_maxStub = maxStub;

	if (m_countPerThd == 0){
		return false;
	}
	m_maxThread = (m_maxStub + m_countPerThd - 1) / m_countPerThd;
	if (m_maxThread < m_countThread){
		m_maxThread = m_countThread;
	}
	for (uint32 i=0; i<m_countThread; ++i){
		BSLib::Utility::CThreadPtr stubThread = NULL;
		if (m_netType == NETT_TCP) {
			stubThread = new CTcpStubThread(m_netServer);
			if (stubThread == NULL){
				return false;
			}
		} else if (m_netType == NETT_UDP) {
			stubThread = new CUdpStubThread(m_netServer);
			if (stubThread == NULL){
				return false;
			}
		}
		if (stubThread == NULL) {
			return false;
		}
		stubThread->start();
		if (!m_threadArray.addThread(stubThread)) {
			stubThread->cancel();
			return false;
		}
	}
	return true;
}

void CNetStubPool::final()
{
	for (uint32 i=0;  i<m_threadArray.getSize(); ++i){
		BSLib::Utility::CThreadPtr& netThreadPtr = m_threadArray[i];
		CNetStubThread* netStubThread = (CNetStubThread*)netThreadPtr;
		if (netStubThread != NULL) {
			netStubThread->terminate();
		}
	}
	m_threadArray.joinAll();
}

uint32 CNetStubPool::getStubCount()
{
	uint32 count = 0;
	for (uint32 i=0;  i<m_threadArray.getSize(); ++i){
		BSLib::Utility::CThreadPtr& netThreadPtr = m_threadArray[i];
		CNetStubThread* netStubThread = (CNetStubThread*)netThreadPtr;
		if (netStubThread != NULL) {
			count += netStubThread->getStubCount();
		}
	}
	return count;
}

void CNetStubPool::getStubsInfo(SNetStubsInfo& a_Info)
{
	a_Info.m_stubCount = 0;
	a_Info.m_stubOkayCount = 0;
	a_Info.m_stubVerifyCount = 0;
	for (uint32 i=0;  i<m_threadArray.getSize(); ++i){
		BSLib::Utility::CThreadPtr& netThreadPtr = m_threadArray[i];
		CNetStubThread* netStubThread = (CNetStubThread*)netThreadPtr;
		if (netStubThread != NULL) {
			a_Info.m_stubCount += netStubThread->getStubCount();
			a_Info.m_stubOkayCount += netStubThread->getOkayStubCount();
			a_Info.m_stubVerifyCount += netStubThread->getVerifyStubCount();
		}
	}
}

void CNetStubPool::getFlowInfo(SNetFlowInfo& a_Info, BSLib::Utility::CRealTime& realTimer)
{
	a_Info.m_recvBytesCount = 0;
	a_Info.m_sendBytesCount = 0;
	a_Info.m_recvBytesPerMax = 0;
	a_Info.m_sendBytesPerMax = 0;
	a_Info.m_recvBytesPerStubMax = 0;
	a_Info.m_sendBytesPerStubMax = 0;

	for (uint32 i=0;  i<m_threadArray.getSize(); ++i){
		BSLib::Utility::CThreadPtr& netThreadPtr = m_threadArray[i];
		CNetStubThread* netStubThread = (CNetStubThread*)netThreadPtr;
		if (netStubThread != NULL) {
			SNetFlowInfo Info;
			netStubThread->getFlowInfo(Info, realTimer);
			a_Info.m_recvBytesCount += Info.m_recvBytesCount;
			a_Info.m_sendBytesCount += Info.m_sendBytesCount;
			if (a_Info.m_recvBytesPerStubMax < Info.m_recvBytesPerStubMax) {
				a_Info.m_recvBytesPerStubMax = Info.m_recvBytesPerStubMax;
			}
			if (a_Info.m_sendBytesPerStubMax < Info.m_sendBytesPerStubMax) {
				a_Info.m_sendBytesPerStubMax = Info.m_sendBytesPerStubMax;
			}
		}
	}
	BSLib::int64 seconds = realTimer.seconds();
	if (m_seconds <= 0) {
		m_seconds = seconds;
		m_recvBytesCount = a_Info.m_recvBytesCount;
		m_sendBytesCount = a_Info.m_sendBytesCount;
		return ;
	}
	if (m_seconds == seconds) {
		a_Info.m_recvBytesPerMax = (uint32)(a_Info.m_recvBytesCount - m_recvBytesCount);
		a_Info.m_sendBytesPerMax = (uint32)(a_Info.m_sendBytesCount - m_sendBytesCount);
		return ;
	}
	m_seconds = seconds;
	a_Info.m_recvBytesPerMax = (uint32)(a_Info.m_recvBytesCount - m_recvBytesCount);
	a_Info.m_sendBytesPerMax = (uint32)(a_Info.m_sendBytesCount - m_sendBytesCount);
	m_recvBytesCount = a_Info.m_recvBytesCount;
	m_sendBytesCount = a_Info.m_sendBytesCount;
}


bool CNetStubPool::addStub(CNetStubPtr& stubPtr)
{
	uint32 count = getStubCount();
	if (count > m_maxStub) {
		BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "count[%d]maxCount[%d]", count, m_maxStub);
		return false;
	}
	if (_addStub(stubPtr)) {
		return true;
	}
	if (m_countThread < m_maxThread) {
		BSLib::Utility::CThreadPtr stubThread = NULL;
		if (m_netType == NETT_TCP) {
			stubThread = new CTcpStubThread(m_netServer);
			if (stubThread == NULL){
				return false;
			}
		} else if (m_netType == NETT_UDP) {
			stubThread = new CUdpStubThread(m_netServer);
			if (stubThread == NULL){
				return false;
			}
		}
		if (stubThread == NULL) {
			return false;
		}
		if (!m_threadArray.addThread(stubThread)) {
			return false;
		}
		stubThread->start();
		m_countThread++;
		if (!_addStub(stubPtr)) {
			stubThread->cancel();
			return false;
		}
		return true;
	}
	BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "add thread error");
	return false;
}


bool CNetStubPool::_addStub(CNetStubPtr& stubPtr)
{
	uint32 minCount = m_maxStub;
	CNetStubThread* stubThread = NULL;
	for (uint32 i=0;  i<m_threadArray.getSize(); ++i){
		BSLib::Utility::CThreadPtr& netThreadPtr = m_threadArray[i];
		CNetStubThread* tmpThread = (CNetStubThread*)netThreadPtr;
		if (tmpThread == NULL) {
			continue;
		}
		uint32 stubCount = tmpThread->getStubCount();
		if (minCount > stubCount) {
			minCount = stubCount;
			stubThread = tmpThread;
		}
	}
	if (stubThread == NULL) {
		return false;
	}
	return stubThread->addStub(stubPtr);
}

}//Network

}//BSLib


