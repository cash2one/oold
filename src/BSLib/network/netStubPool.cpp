//////////////////////////////////////////////////////////////////////
//	created:	2012/09/15
//	filename:	src\BSLib\network\netStubPool.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/tracer.h>
#include "netStubPool.h"
#include "tcpStubThread.h"
#include "udpStubThread.h"

namespace BSLib
{

namespace Network
{

CNetStubPool::CNetStubPool(CNetServer* netServer, ENetType netType)
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

void CNetStubPool::getStubsInfor(SNetStubsInfor& a_infor)
{
	a_infor.m_stubCount = 0;
	a_infor.m_stubOkayCount = 0;
	a_infor.m_stubVerifyCount = 0;
	for (uint32 i=0;  i<m_threadArray.getSize(); ++i){
		BSLib::Utility::CThreadPtr& netThreadPtr = m_threadArray[i];
		CNetStubThread* netStubThread = (CNetStubThread*)netThreadPtr;
		if (netStubThread != NULL) {
			a_infor.m_stubCount += netStubThread->getStubCount();
			a_infor.m_stubOkayCount += netStubThread->getOkayStubCount();
			a_infor.m_stubVerifyCount += netStubThread->getVerifyStubCount();
		}
	}
}

void CNetStubPool::getFlowInfor(SNetFlowInfor& a_infor, BSLib::Utility::CRealTime& realTimer)
{
	a_infor.m_recvBytesCount = 0;
	a_infor.m_sendBytesCount = 0;
	a_infor.m_recvBytesPerMax = 0;
	a_infor.m_sendBytesPerMax = 0;
	a_infor.m_recvBytesPerStubMax = 0;
	a_infor.m_sendBytesPerStubMax = 0;

	for (uint32 i=0;  i<m_threadArray.getSize(); ++i){
		BSLib::Utility::CThreadPtr& netThreadPtr = m_threadArray[i];
		CNetStubThread* netStubThread = (CNetStubThread*)netThreadPtr;
		if (netStubThread != NULL) {
			SNetFlowInfor infor;
			netStubThread->getFlowInfor(infor, realTimer);
			a_infor.m_recvBytesCount += infor.m_recvBytesCount;
			a_infor.m_sendBytesCount += infor.m_sendBytesCount;
			if (a_infor.m_recvBytesPerStubMax < infor.m_recvBytesPerStubMax) {
				a_infor.m_recvBytesPerStubMax = infor.m_recvBytesPerStubMax;
			}
			if (a_infor.m_sendBytesPerStubMax < infor.m_sendBytesPerStubMax) {
				a_infor.m_sendBytesPerStubMax = infor.m_sendBytesPerStubMax;
			}
		}
	}
	BSLib::int64 seconds = realTimer.seconds();
	if (m_seconds <= 0) {
		m_seconds = seconds;
		m_recvBytesCount = a_infor.m_recvBytesCount;
		m_sendBytesCount = a_infor.m_sendBytesCount;
		return ;
	}
	if (m_seconds == seconds) {
		a_infor.m_recvBytesPerMax = (uint32)(a_infor.m_recvBytesCount - m_recvBytesCount);
		a_infor.m_sendBytesPerMax = (uint32)(a_infor.m_sendBytesCount - m_sendBytesCount);
		return ;
	}
	m_seconds = seconds;
	a_infor.m_recvBytesPerMax = (uint32)(a_infor.m_recvBytesCount - m_recvBytesCount);
	a_infor.m_sendBytesPerMax = (uint32)(a_infor.m_sendBytesCount - m_sendBytesCount);
	m_recvBytesCount = a_infor.m_recvBytesCount;
	m_sendBytesCount = a_infor.m_sendBytesCount;
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

// void CNetStubPool::getBytesStubInfor(SNetStubsCollectInfor& a_netCollectInfor)
// {
// // 	*a_recvBytesCount = 0;
// // 	*a_sendBytesCount = 0;
// // 	*a_recvBytesPerSMax = 0;
// // 	*a_sendBytesPerSMax = 0;
// 
// 	for (uint32 i=0;  i<m_threadArray.getSize(); ++i){
// 		BSLib::Utility::CThreadPtr& netThreadPtr = m_threadArray[i];
// 		CNetStubThread* netStubThread = (CNetStubThread*)netThreadPtr;
// 		if (netStubThread != NULL) {
// 			BSLib::uint64 recvBytesCount = 0;
// 			BSLib::uint64 sendBytesCount = 0;
// 			BSLib::uint32 recvBytesPerSMax = 0;
// 			BSLib::uint32 sendBytesPerSMax = 0;
// 
// 			netStubThread->getBytesStubInfor(&recvBytesCount, &sendBytesCount, &recvBytesPerSMax, &sendBytesPerSMax);
// 
// // 			*a_recvBytesCount += recvBytesCount;
// // 			*a_sendBytesCount += sendBytesCount;
// // 			if (*a_recvBytesPerSMax < recvBytesPerSMax) {
// // 				*a_recvBytesPerSMax = recvBytesPerSMax;
// // 			}
// // 			if (*a_sendBytesPerSMax < sendBytesPerSMax) {
// // 				*a_sendBytesPerSMax = sendBytesPerSMax;
// // 			}
// 		}
// 	}
// }


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

