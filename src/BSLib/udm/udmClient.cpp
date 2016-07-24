#include "udmClient.h"
#include "udpThreadMgr.h"

#define BSLIB_UDM_CONNECT_TIMEOUT 3000

namespace BSLib
{

namespace UDM
{

CUdmClient::CUdmClient(SUdmSocketInfo* udmSocketInfo)
: CUdmSocket(udmSocketInfo)
, m_isWaiting(false)
, m_pingTimeout(1000)
, m_pingCount(0)
{
	;
}

CUdmClient::~CUdmClient()
{
	;
}

int CUdmClient::connect(const struct sockaddr* name, int namelen)
{
	SUdmSocketInfo* udpSocketInfo = CUdmSocket::getUdmSocketInfo();
	CUdpThread* udpThread = CUdpThreadMgr::singleton().getUdpThread(udpSocketInfo->m_udpThreadID);
	if (udpThread == NULL){
		return BSLIB_UDM_ERROR;
	}
	
	CUdmSocket::setPeerName(name, namelen);
	udpThread->addUdmClient(this);
	
	EUdmStatus udmStatus = udpSocketInfo->m_udmStatus;
	udpSocketInfo->m_udmStatus = UDM_STATE_CONNECTING;

	m_isWaiting = true;

	SMsgPc2PsReqConnect reqConnectMsg;
	if (udpThread->sendTo(&reqConnectMsg, sizeof(reqConnectMsg), name, namelen) == BSLIB_UDM_ERROR) {
		udpSocketInfo->m_udmStatus = udmStatus;
		return BSLIB_UDM_ERROR;
	}

	if (!udpThread->isRunning()) {
		udpThread->start();
	}

	m_connectEvent.wait(BSLIB_UDM_CONNECT_TIMEOUT);

	m_isWaiting = false;

	if (CUdmSocket::getUdmSocketInfo()->m_udmStatus != UDM_STATE_OPEN) {
		udpSocketInfo->m_udmStatus = udmStatus;
		m_connectEvent.reset();
		return BSLIB_UDM_ERROR;
	}
	return BSLIB_UDM_OK;
}

int CUdmClient::close()
{ 
	SUdmSocketInfo* udpSocketInfo = CUdmSocket::getUdmSocketInfo();
	switch(udpSocketInfo->m_udmStatus)
	{
	case UDM_STATE_INIT:
	case UDM_STATE_BIND:
	case UDM_STATE_BROKEN:
		{
			udpSocketInfo->m_udmStatus = UDM_STATE_NONEXIST;
			break;
		}
	case UDM_STATE_CONNECTING:
	case UDM_STATE_CONNECTED:
	case UDM_STATE_OPEN:
		{
			udpSocketInfo->m_udmStatus = UDM_STATE_CLOSING;
			SMsgPc2PsReqClose reqCloseMsg;
			CUdmSocket::_sendMsg(&reqCloseMsg, sizeof(reqCloseMsg));
			break;
		}
	default:
		{
			break;
		}
	}
	return BSLIB_UDM_OK;
}

bool CUdmClient::parseCtrlMsg(SUdpCtrlMsg* msg, int msgSize, BSLib::Utility::CRealTime& realTime)
{
	int msgID = msg->getMsgID();
	switch (msgID)
	{
	case  EMID_PC2PS_REQ_CONNECT:
		{
			SMsgPs2PcResConnect resConnectMsg;
			CUdmSocket::_sendMsg(&resConnectMsg, sizeof(resConnectMsg));
			break;
		}
	case  EMID_PS2PC_RES_CONNECT:
		{
			SMsgPc2PsNtfConnect ntfConnectMsg;
			CUdmSocket::_sendMsg(&ntfConnectMsg, sizeof(ntfConnectMsg));
			
			SUdmSocketInfo* udpSocketInfo = CUdmSocket::getUdmSocketInfo();
			if (udpSocketInfo->m_udmStatus == UDM_STATE_CONNECTING) {
				if (m_isWaiting) {
					udpSocketInfo->m_udmStatus = UDM_STATE_OPEN;
					m_connectEvent.set();

					m_pingTimeout.reset(BSLIB_UDM_PING_TIME, realTime);
					m_pingCount = 0;
				}
			}
			break;
		}
	case EMID_PC2PS_NTF_CONNECT:
		{
			break;
		}
	case EMID_PS2PC_REQ_PING:
		{
			SUdmSocketInfo* udpSocketInfo = CUdmSocket::getUdmSocketInfo();
			if (udpSocketInfo->m_udmStatus == UDM_STATE_OPEN) {
				SMsgPc2PsResPing resPing;
				CUdmSocket::_sendMsg(&resPing, sizeof(resPing));
			}
			break;
		}
	case EMID_PC2PS_REQ_PING:
		{
			SMsgPs2PcResPing resPing;
			CUdmSocket::_sendMsg(&resPing, sizeof(resPing));
			break;
		}
	case EMID_PS2PC_RES_PING:
		{
			m_pingTimeout.reset(BSLIB_UDM_PING_TIME, realTime);
			m_pingCount = 0;
			break;
		}
	case EMID_PC2PS_REQ_CLOSE:
		{
			SMsgPs2PcResClose resCloseMsg;
			CUdmSocket::_sendMsg(&resCloseMsg, sizeof(resCloseMsg));
			break;
		}
	case EMID_PS2PC_NTF_CLOSE:
		{
			SMsgPc2PsReqClose reqCloseMsg;
			CUdmSocket::_sendMsg(&reqCloseMsg, sizeof(reqCloseMsg));

			SUdmSocketInfo* udpSocketInfo = CUdmSocket::getUdmSocketInfo();
			if (udpSocketInfo->m_udmStatus == UDM_STATE_CONNECTING || 
				udpSocketInfo->m_udmStatus == UDM_STATE_CONNECTED ||
				udpSocketInfo->m_udmStatus == UDM_STATE_OPEN) {
					udpSocketInfo->m_udmStatus = UDM_STATE_CLOSING;
					CUdmSocket::notifyBreak();
			}
			
			break;
		}
	case EMID_PS2PC_RES_CLOSE:
		{
			SMsgPc2PsNtfClose ntfCloseMsg;
			CUdmSocket::_sendMsg(&ntfCloseMsg, sizeof(ntfCloseMsg));

			SUdmSocketInfo* udpSocketInfo = CUdmSocket::getUdmSocketInfo();
			if (udpSocketInfo->m_udmStatus == UDM_STATE_CLOSING) {
				udpSocketInfo->m_udmStatus = UDM_STATE_NONEXIST;
			}
			break;
		}
	case EMID_PC2PS_NTF_CLOSE:
		{
			break;
		}
	default:
		{
			;
		}
	}
	return true;
}

bool CUdmClient::parseDataMsg(SUdpCtrlMsg* msg, int msgSize, BSLib::Utility::CRealTime& realTime)
{
	SUdmSocketInfo* udpSocketInfo = CUdmSocket::getUdmSocketInfo();
	if (udpSocketInfo->m_udmStatus == UDM_STATE_OPEN) {
		m_pingTimeout.reset(BSLIB_UDM_PING_TIME, realTime);
		m_pingCount = 0;
	}
	return CUdmSocket::parseDataMsg(msg, msgSize, realTime);
}

void CUdmClient::tickMsg(BSLib::Utility::CRealTime& realTime)
{
	SUdmSocketInfo* udpSocketInfo = CUdmSocket::getUdmSocketInfo();
	if (udpSocketInfo->m_udmStatus == UDM_STATE_CONNECTING) {
		SMsgPc2PsReqConnect reqConnectMsg;
		CUdmSocket::_sendMsg(&reqConnectMsg, sizeof(reqConnectMsg));
	}
	if (udpSocketInfo->m_udmStatus == UDM_STATE_CLOSING) {
		SMsgPc2PsReqClose reqCloseMsg;
		CUdmSocket::_sendMsg(&reqCloseMsg, sizeof(reqCloseMsg));
	}
	if (udpSocketInfo->m_udmStatus == UDM_STATE_OPEN) {
		if (m_pingTimeout(realTime)) {
			if (m_pingCount > BSLIB_UDM_PING_MAX) {
				udpSocketInfo->m_udmStatus = UDM_STATE_BROKEN;
				CUdmSocket::notifyBreak();
				return ;
			}
			SMsgPc2PsReqPing reqPing;
			CUdmSocket::_sendMsg(&reqPing, sizeof(reqPing));
			++m_pingCount;
			m_pingTimeout.reset(1000, realTime);
		}
	}
	CUdmSocket::tickMsg(realTime);
}

}//UDM

}//BSLib




