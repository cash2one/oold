#include <BSLib/utility/tracer.h>
#include <BSLib/utility/thread/thread.h>
#include <BSLib/network/netStub.h>

#define BSLIB_NETWORK_VERIFY_TIMEOUT 6000
#define BSLIB_NETWORK_OKEY_TIMEOUT 6000
#define BSLIB_NETWORK_DELETE_TIMEOUT 10000
#define BSLIB_NETWORK_ERROR_PING_MAX 6

namespace BSLib
{

namespace Network
{

uint32 CNetStub::m_verifyTimeout = BSLIB_NETWORK_VERIFY_TIMEOUT;
uint32 CNetStub::m_okeyTimeout = BSLIB_NETWORK_OKEY_TIMEOUT;
uint32 CNetStub::m_errorPingMax = BSLIB_NETWORK_ERROR_PING_MAX;

CNetStub::CNetStub(CNetConnectionPtr& netConnection)
: m_stubID(INVALID_STUBID)
, m_stubState(ESS_NULL)
, m_netConnectionPtr(netConnection)
, m_verifyOvertime(m_verifyTimeout)
, m_okeyOvertime(m_okeyTimeout)
, m_deleteOvertime(BSLIB_NETWORK_DELETE_TIMEOUT)
, m_realTime(NULL)
, m_errorNotifyPingCount(0)
, m_timerServer(NULL)
, m_needPing(true)
{
	;
}

CNetStub::~CNetStub()
{
	BSLIB_LOG_DEBUG(BSLib::ETT_BSLIB_NETWORK, "free BSLib::Network::CNetStub");
	if (m_netConnectionPtr == NULL){
		return ;
	}
	m_netConnectionPtr->close();
	m_netConnectionPtr = NULL;
}

void CNetStub::setState(EStubState state)
{
	if (m_stubState >= state) {
		return ;
	}
	m_stubState = state;
	switch (m_stubState){
		case ESS_VERIFY:
			if (NULL != m_realTime){
				m_verifyOvertime.reset(m_verifyTimeout, *m_realTime);
			}
			break;
		case ESS_OKAY:
			if (NULL != m_realTime){
				m_okeyOvertime.reset(m_okeyTimeout, *m_realTime);
			}
			break;
		case ESS_DELELE:
			if (NULL != m_realTime){
				m_deleteOvertime.reset(BSLIB_NETWORK_DELETE_TIMEOUT, *m_realTime);
			}
			break;
		case ESS_RECYCLE:
		default:
			break;
	}
}

void CNetStub::gotoNextState() 
{ 
	setState((EStubState)((m_stubState + 1) % ESS_MAX));
}

int CNetStub::send(BSLib::Utility::CStream& stream)
{
	if (m_stubState == ESS_VERIFY || m_stubState == ESS_OKAY){
		if (m_netConnectionPtr != NULL && m_netConnectionPtr->isValid()) {
			return m_netConnectionPtr->send(stream, true);
		}
	}
	return -1;
}

int CNetStub::send(const void* msgBuff, unsigned int buffSize)
{
	if (m_stubState == ESS_VERIFY || m_stubState == ESS_OKAY){
		if (m_netConnectionPtr != NULL && m_netConnectionPtr->isValid()) {
			return m_netConnectionPtr->send(msgBuff, buffSize, true);
		}
	}
	return -1;
}

void CNetStub::setOkeyStateTimeoutMAX(uint32 okeyTimeoutMAX, uint32 pingTime) 
{ 
	m_errorPingMax = (uint32)(okeyTimeoutMAX / pingTime);
	if (m_errorPingMax <= 0){
		m_errorPingMax = 1;
	}
	m_okeyTimeout = pingTime;
}


bool CNetStub::_checkVerifyOvertime(BSLib::Utility::CRealTime& realTimer)
{
	return m_verifyOvertime(realTimer);
}

bool CNetStub::_checkOkeyOvertime(BSLib::Utility::CRealTime& realTimer)
{
	if (!m_needPing) {
		return false;
	}
	if (m_okeyOvertime(realTimer)){
		if (m_errorNotifyPingCount >= m_errorPingMax){
			return true;
		}
		_cbNotifyPing();
		m_okeyOvertime.next(realTimer);
		++m_errorNotifyPingCount;
	}
	return false;
}

bool CNetStub::_checkDeleteOvertime(BSLib::Utility::CRealTime& realTimer)
{
	return m_deleteOvertime(realTimer);
}

void CNetStub::_resetOkeyTick()
{
	m_okeyOvertime.next(*m_realTime);
	m_errorNotifyPingCount = 0;
}

void CNetStub::_setTimerServer(BSLib::Utility::CTimerServer* a_timerServer)
{
	m_timerServer = a_timerServer;
}


}//Network

}//BSLib



