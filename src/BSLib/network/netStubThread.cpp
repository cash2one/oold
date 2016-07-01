#include <BSLib/utility/tracer.h>
#include <BSLib/network/netConnection.h>
#include <BSLib/network/netServer.h>
#include "netStubThread.h"

namespace BSLib
{

namespace Network
{

CNetStubThread::CNetStubThread(INetServer* netServer)
: m_isRunning(false)
, m_oneSecTimer(1000)
, m_threeSecTimer(3000)
, m_netServer(netServer)
, m_recvBytesCount(0)
, m_sendBytesCount(0)
, m_recvBytesPerSMax(0)
, m_sendBytesPerSMax(0)
{
	;
}

CNetStubThread::~CNetStubThread()
{
	;
}

void CNetStubThread::start()
{
	m_isRunning = true;
	BSLib::Utility::CThread::start();
}

void CNetStubThread::getFlowInfo(SNetFlowInfo& a_infor, BSLib::Utility::CRealTime& a_realTimer)
{
	a_infor.m_recvBytesCount = m_recvBytesCount;
	a_infor.m_sendBytesCount = m_sendBytesCount;
	a_infor.m_recvBytesPerStubMax = m_recvBytesPerSMax;
	a_infor.m_sendBytesPerStubMax = m_sendBytesPerSMax;
}

void CNetStubThread::terminate()
{
	m_isRunning = false;
}

bool CNetStubThread::addStub(CNetStubPtr& stubPtr)
{
	return m_netStubQueue.push(stubPtr);
}

void CNetStubThread::_run()
{
	_enterRun();
	while (m_isRunning) {
		m_timerServer.update();
		_newTask();
		if (m_oneSecTimer(*m_timerServer.getRealTime())){
			_verifyStub();
			_okayStub();
			_recyclePeer();		
		}
		if (m_threeSecTimer(*m_timerServer.getRealTime())){
			_updateNetBytesInfor(*m_timerServer.getRealTime());
			_deletePeer();
		}
		_wait();
	}
	m_isRunning = false;

	for (std::list<CNetStubCbPtr>::iterator it_verify = m_verifyList.begin(); it_verify != m_verifyList.end(); ++it_verify){
		CNetStubCbPtr netStubCbPtr = *it_verify;
		if (netStubCbPtr == NULL) {
			continue;
		}
		while (!netStubCbPtr->isEmptyOfSendBuff()){
			if (!netStubCbPtr->sendToNetFromBuff()) {
				break;
			}
		}
		netStubCbPtr->setState(ESS_DELELE);
		_delStubToNetConnectionMgr(netStubCbPtr->getNetStub());
		netStubCbPtr->terminate();
		netStubCbPtr->getNetStub()->getNetConnectionPtr()->close();
		m_netServer->getNetStubMgr()->delStub(netStubCbPtr->getNetStub());
		netStubCbPtr->finalStub();
	}
	m_verifyList.clear();

	for (std::list<CNetStubCbPtr>::iterator it_okay = m_okayList.begin(); it_okay != m_okayList.end(); ++it_okay){
		CNetStubCbPtr netStubCbPtr = *it_okay;
		if (netStubCbPtr == NULL) {
			continue;
		}
		while (!netStubCbPtr->isEmptyOfSendBuff()){
			if (!netStubCbPtr->sendToNetFromBuff()) {
				break;
			}
		}
		netStubCbPtr->setState(ESS_DELELE);
		_delStubToNetConnectionMgr(netStubCbPtr->getNetStub());
		netStubCbPtr->terminate();
		netStubCbPtr->getNetStub()->getNetConnectionPtr()->close();
		m_netServer->getNetStubMgr()->delStub(netStubCbPtr->getNetStub());
		netStubCbPtr->finalStub();
	}
	m_okayList.clear();

	for (std::list<CNetStubCbPtr>::iterator it_recycle = m_recycleList.begin(); it_recycle != m_recycleList.end(); ++it_recycle){
		CNetStubCbPtr netStubCbPtr = *it_recycle;
		if (netStubCbPtr == NULL){
			continue;
		}
		while (!netStubCbPtr->isEmptyOfSendBuff()){
			if (!netStubCbPtr->sendToNetFromBuff()) {
				break;
			}
		}
		netStubCbPtr->setState(ESS_DELELE);
		_delStubToNetConnectionMgr(netStubCbPtr->getNetStub());
		netStubCbPtr->terminate();
		netStubCbPtr->getNetStub()->getNetConnectionPtr()->close();
		m_netServer->getNetStubMgr()->delStub(netStubCbPtr->getNetStub());
	}
	m_recycleList.clear();

	for (std::list<CNetStubCbPtr>::iterator it_delete = m_deleteList.begin(); it_delete != m_deleteList.end(); ++it_delete){
		CNetStubCbPtr netStubCbPtr = *it_delete;
		if (netStubCbPtr == NULL) {
			continue;
		}
		netStubCbPtr->finalStub();
	}
	m_deleteList.clear();

	_leaveRun();
}

void CNetStubThread::_newTask()
{
	CNetStubPtr stubPtr = NULL;
	m_netStubQueue.pop(stubPtr);
	while (stubPtr != NULL){
		CNetStubCbPtr netStubCbPtr = new CNetStubCb(stubPtr);
		if (netStubCbPtr == NULL) {
			m_netStubQueue.pop(stubPtr);
			continue;
		}
		CNetConnectionCallbackPtr netConnectionCb = netStubCbPtr;
		if (netConnectionCb == NULL) {
			m_netStubQueue.pop(stubPtr);
			continue;
		}
		netStubCbPtr->setRealTimer(m_timerServer.getRealTime());
		netStubCbPtr->setTimerServer(&m_timerServer);
		stubPtr->setState(ESS_VERIFY);

		if (!_addStubToNetConnectionMgr(stubPtr, netConnectionCb)) {
			m_netStubQueue.pop(stubPtr);
			continue;
		}
		netStubCbPtr->initStub();
		netStubCbPtr->recvMsg();
		CNetConnectionPtr netConnection = stubPtr->getNetConnectionPtr();
		if (netConnection != NULL) {
			netConnection->sendToNetFromBuff();;
		}
		m_verifyList.push_back(netStubCbPtr);

		stubPtr = NULL;
		m_netStubQueue.pop(stubPtr);
	}
}

void CNetStubThread::_verifyStub()
{
	if (m_verifyList.empty()){
		return ;
	}
	for (std::list<CNetStubCbPtr>::iterator it = m_verifyList.begin(); it != m_verifyList.end();){
		CNetStubCbPtr netStubCbPtr = *it;
		if (netStubCbPtr == NULL) {
			it = m_verifyList.erase(it);
			continue;
		}
		EStubState state = netStubCbPtr->getState();
		switch (state){
			case ESS_OKAY:
				it = m_verifyList.erase(it);
				m_okayList.push_back(netStubCbPtr);
				break;
			case ESS_VERIFY:
				if (!netStubCbPtr->checkVerifyOvertime(*m_timerServer.getRealTime())){
					++it;
					break;
				}
				BSLIB_LOG_TRACE(BSLib::ETT_BSLIB_NETWORK, "Stub[%d]verify timeout --> recycle", netStubCbPtr->getNetStub()->getStubID());
			default:
				it = m_verifyList.erase(it);
				netStubCbPtr->setState(ESS_RECYCLE);
				m_recycleList.push_back(netStubCbPtr);
				BSLIB_LOG_TRACE(BSLib::ETT_BSLIB_NETWORK, "Stub[%d][%d]verify --> recycle", state, netStubCbPtr->getNetStub()->getStubID());
		}
	}
}

void CNetStubThread::_okayStub()
{
	if (m_okayList.empty()){
		return ;
	}
	for (std::list<CNetStubCbPtr>::iterator it = m_okayList.begin(); it != m_okayList.end();){
		CNetStubCbPtr netStubCbPtr = *it;
		if (netStubCbPtr == NULL) {
			it = m_verifyList.erase(it);
			continue;
		}
		EStubState state = netStubCbPtr->getState();
		switch (state){
			case ESS_OKAY: 
				if (!netStubCbPtr->checkOkeyOvertime(*m_timerServer.getRealTime())){
					++it;
					break;
				}
				BSLIB_LOG_TRACE(BSLib::ETT_BSLIB_NETWORK, "Stub[%d]okay timeout --> recycle", netStubCbPtr->getNetStub()->getStubID());
			case ESS_VERIFY:
			default:
				it = m_okayList.erase(it);
				netStubCbPtr->setState(ESS_RECYCLE);
				m_recycleList.push_back(netStubCbPtr);
				BSLIB_LOG_TRACE(BSLib::ETT_BSLIB_NETWORK, "Stub[%d][%d]okay --> recycle", state, netStubCbPtr->getNetStub()->getStubID());
		}
	}
}

void CNetStubThread::_recyclePeer()
{
	if (m_recycleList.empty()){
		return ;
	}
	for (std::list<CNetStubCbPtr>::iterator it = m_recycleList.begin(); it != m_recycleList.end();){
		CNetStubCbPtr netStubCbPtr = *it;
		if (netStubCbPtr == NULL) {
			it = m_recycleList.erase(it);
		}

		netStubCbPtr->recvMsg();

		if (!netStubCbPtr->isEmptyOfSendBuff()) {
			if (netStubCbPtr->sendToNetFromBuff()){
				continue;
			}
		}
		netStubCbPtr->setState(ESS_DELELE);
		_delStubToNetConnectionMgr(netStubCbPtr->getNetStub());
		netStubCbPtr->terminate();
		netStubCbPtr->getNetStub()->getNetConnectionPtr()->close();

		it = m_recycleList.erase(it);
		m_deleteList.push_back(netStubCbPtr);
	}
}

void CNetStubThread::_deletePeer()
{
	if (m_deleteList.empty()){
		return ;
	}
	for (std::list<CNetStubCbPtr>::iterator it = m_deleteList.begin(); it != m_deleteList.end();){
		CNetStubCbPtr netStubCbPtr = *it;
		if (netStubCbPtr == NULL) {
			it = m_verifyList.erase(it);
			continue;
		}
		if (!netStubCbPtr->checkDeleteOvertime(*m_timerServer.getRealTime())){
			++it;
			continue;
		}
		netStubCbPtr->finalStub();
		m_netServer->getNetStubMgr()->delStub(netStubCbPtr->getNetStub());
		it = m_deleteList.erase(it);
	}
}

void CNetStubThread::_updateNetBytesInfor(BSLib::Utility::CRealTime& a_realTimer)
{
	m_recvBytesCount = 0;
	m_sendBytesCount = 0;
	m_recvBytesPerSMax = 0;
	m_sendBytesPerSMax = 0;

	std::list<CNetStubCbPtr>::iterator it_delete = m_deleteList.begin();
	for (; it_delete != m_deleteList.end(); ++it_delete) {
		CNetStubCbPtr netStubCbPtr = *it_delete;
		if (netStubCbPtr == NULL) {
			continue;
		}
		SNetStubNetInfor netStubNetInfor;
		netStubCbPtr->getNetInfo(a_realTimer, netStubNetInfor);

		m_recvBytesCount += netStubNetInfor.m_recvBytesCount ;
		m_sendBytesCount += netStubNetInfor.m_sendBytesCount ;

		if (m_recvBytesPerSMax < netStubNetInfor.m_recvBytesPerMax) {
			m_recvBytesPerSMax = netStubNetInfor.m_recvBytesPerMax;
		}
		if (m_sendBytesPerSMax < netStubNetInfor.m_sendBytesPerMax) {
			m_sendBytesPerSMax = netStubNetInfor.m_sendBytesPerMax;
		}
	}
	std::list<CNetStubCbPtr>::iterator it_recycle = m_recycleList.begin();
	for (; it_recycle != m_recycleList.end(); ++it_recycle) {
		CNetStubCbPtr netStubCbPtr = *it_recycle;
		if (netStubCbPtr == NULL) {
			continue;
		}
		SNetStubNetInfor netStubNetInfor;
		netStubCbPtr->getNetInfo(a_realTimer, netStubNetInfor);

		m_recvBytesCount += netStubNetInfor.m_recvBytesCount ;
		m_sendBytesCount += netStubNetInfor.m_sendBytesCount ;

		if (m_recvBytesPerSMax < netStubNetInfor.m_recvBytesPerMax) {
			m_recvBytesPerSMax = netStubNetInfor.m_recvBytesPerMax;
		}
		if (m_sendBytesPerSMax < netStubNetInfor.m_sendBytesPerMax) {
			m_sendBytesPerSMax = netStubNetInfor.m_sendBytesPerMax;
		}
	}
	std::list<CNetStubCbPtr>::iterator it_verify =  m_verifyList.begin();
	for (; it_verify != m_verifyList.end(); ++it_verify) {
		CNetStubCbPtr netStubCbPtr = *it_verify;
		if (netStubCbPtr == NULL) {
			continue;
		}
		SNetStubNetInfor netStubNetInfor;
		netStubCbPtr->getNetInfo(a_realTimer, netStubNetInfor);

		m_recvBytesCount += netStubNetInfor.m_recvBytesCount ;
		m_sendBytesCount += netStubNetInfor.m_sendBytesCount ;

		if (m_recvBytesPerSMax < netStubNetInfor.m_recvBytesPerMax) {
			m_recvBytesPerSMax = netStubNetInfor.m_recvBytesPerMax;
		}
		if (m_sendBytesPerSMax < netStubNetInfor.m_sendBytesPerMax) {
			m_sendBytesPerSMax = netStubNetInfor.m_sendBytesPerMax;
		}
	}
	std::list<CNetStubCbPtr>::iterator it_sync =  m_syncList.begin();
	for (; it_sync != m_syncList.end(); ++it_sync) {
		CNetStubCbPtr netStubCbPtr = *it_sync;
		if (netStubCbPtr == NULL) {
			continue;
		}
		SNetStubNetInfor netStubNetInfor;
		netStubCbPtr->getNetInfo(a_realTimer, netStubNetInfor);

		m_recvBytesCount += netStubNetInfor.m_recvBytesCount ;
		m_sendBytesCount += netStubNetInfor.m_sendBytesCount ;

		if (m_recvBytesPerSMax < netStubNetInfor.m_recvBytesPerMax) {
			m_recvBytesPerSMax = netStubNetInfor.m_recvBytesPerMax;
		}
		if (m_sendBytesPerSMax < netStubNetInfor.m_sendBytesPerMax) {
			m_sendBytesPerSMax = netStubNetInfor.m_sendBytesPerMax;
		}
	}
	std::list<CNetStubCbPtr>::iterator it_okay =  m_okayList.begin();
	for (; it_okay != m_okayList.end(); ++it_okay) {
		CNetStubCbPtr netStubCbPtr = *it_okay;
		if (netStubCbPtr == NULL) {
			continue;
		}
		SNetStubNetInfor netStubNetInfor;
		netStubCbPtr->getNetInfo(a_realTimer, netStubNetInfor);

		m_recvBytesCount += netStubNetInfor.m_recvBytesCount ;
		m_sendBytesCount += netStubNetInfor.m_sendBytesCount ;

		if (m_recvBytesPerSMax < netStubNetInfor.m_recvBytesPerMax) {
			m_recvBytesPerSMax = netStubNetInfor.m_recvBytesPerMax;
		}
		if (m_sendBytesPerSMax < netStubNetInfor.m_sendBytesPerMax) {
			m_sendBytesPerSMax = netStubNetInfor.m_sendBytesPerMax;
		}
	}
}

}//Network

}//BSLib


