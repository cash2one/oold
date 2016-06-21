#include "udmStub.h"
#include "udpThreadMgr.h"

namespace BSLib
{

namespace UDM
{

CUdmStub::CUdmStub(SUdmSocketInfor* udmSocketInfor, BSLib::Utility::CRealTime& realTime)
: CUdmSocket(udmSocketInfor)
, m_pingTimeout(1000, realTime)
, m_pingCount(0)
{
	;
}

CUdmStub::~CUdmStub()
{
	;
}

int CUdmStub::close()
{
	SUdmSocketInfor* udpSocketInfor = CUdmSocket::getUdmSocketInfor();
	switch(udpSocketInfor->m_udmStatus)
	{
	case UDM_STATE_INIT:
	case UDM_STATE_BROKEN:
		{
			udpSocketInfor->m_udmStatus = UDM_STATE_NONEXIST;
			break;
		}
	case UDM_STATE_CONNECTING:
	case UDM_STATE_CONNECTED:
	case UDM_STATE_OPEN:
		{
			udpSocketInfor->m_udmStatus = UDM_STATE_CLOSING;
			SMsgPs2PcNtfClose ntfCloseMsg;
			CUdmSocket::_sendMsg(&ntfCloseMsg, sizeof(ntfCloseMsg));
			break;
		}
	default:
		{
			break;
		}
	}
	return BSLIB_UDM_OK;
}

bool CUdmStub::parseCtrlMsg(SUdpCtrlMsg* msg, int msgSize, BSLib::Utility::CRealTime& realTime)
{
	int msgID = msg->getMsgID();
	switch (msgID)
	{
	case  EMID_PC2PS_REQ_CONNECT:
		{
			SUdmSocketInfor* udpSocketInfor = CUdmSocket::getUdmSocketInfor();
			if (udpSocketInfor->m_udmStatus == UDM_STATE_CONNECTED || udpSocketInfor->m_udmStatus == UDM_STATE_INIT) {
				SMsgPs2PcResConnect resConnectMsg;
				CUdmSocket::_sendMsg(&resConnectMsg, sizeof(resConnectMsg));
				udpSocketInfor->m_udmStatus = UDM_STATE_CONNECTED;
			}
			break;
		} 
	case EMID_PC2PS_NTF_CONNECT:
		{
			SUdmSocketInfor* udpSocketInfor = CUdmSocket::getUdmSocketInfor();
			if (udpSocketInfor->m_udmStatus == UDM_STATE_CONNECTED) {
				udpSocketInfor->m_udmStatus = UDM_STATE_OPEN;
				CUdpThread* udpThread = CUdpThreadMgr::singleton().getUdpThread(udpSocketInfor->m_udpThreadID);
				if (udpThread != NULL){
					udpThread->addUdmStub(this);
				}
				m_pingTimeout.reset(BSLIB_UDM_PING_TIME, realTime);
				m_pingCount = 0;
			}
			break;
		}
	case EMID_PC2PS_RES_PING:
		{
			m_pingTimeout.reset(BSLIB_UDM_PING_TIME, realTime);
			m_pingCount = 0;
			break;
		}
	case EMID_PC2PS_REQ_PING:
		{
			SUdmSocketInfor* udpSocketInfor = CUdmSocket::getUdmSocketInfor();
			if (udpSocketInfor->m_udmStatus == UDM_STATE_OPEN) {
				SMsgPs2PcResPing resPing;
				CUdmSocket::_sendMsg(&resPing, sizeof(resPing));
			}
			break;
		}
	case EMID_PC2PS_REQ_CLOSE:
		{
			SMsgPs2PcResClose resCloseMsg;
			CUdmSocket::_sendMsg(&resCloseMsg, sizeof(resCloseMsg));

			SUdmSocketInfor* udpSocketInfor = CUdmSocket::getUdmSocketInfor();
			if (udpSocketInfor->m_udmStatus == UDM_STATE_CONNECTING || 
				udpSocketInfor->m_udmStatus == UDM_STATE_CONNECTED ||
				udpSocketInfor->m_udmStatus == UDM_STATE_OPEN ||
				udpSocketInfor->m_udmStatus == UDM_STATE_CLOSING) {
				udpSocketInfor->m_udmStatus = UDM_STATE_CLOSED;
				CUdmSocket::notifyBreak();
			}
			break;
		}
	case EMID_PC2PS_NTF_CLOSE:
		{
			SUdmSocketInfor* udpSocketInfor = CUdmSocket::getUdmSocketInfor();
			if (udpSocketInfor->m_udmStatus == UDM_STATE_CLOSED) {
				udpSocketInfor->m_udmStatus = UDM_STATE_NONEXIST;
			}
			break;
		}
	default:
		{
			;
		}
	}
	return true;
}

bool CUdmStub::parseDataMsg(SUdpCtrlMsg* msg, int msgSize, BSLib::Utility::CRealTime& realTime)
{
	SUdmSocketInfor* udpSocketInfor = CUdmSocket::getUdmSocketInfor();
	if (udpSocketInfor->m_udmStatus == UDM_STATE_OPEN) {
		m_pingTimeout.reset(BSLIB_UDM_PING_TIME, realTime);
		m_pingCount = 0;
	}
	return CUdmSocket::parseDataMsg(msg, msgSize, realTime);
}

void CUdmStub::tickMsg(BSLib::Utility::CRealTime& realTime)
{
	SUdmSocketInfor* udpSocketInfor = CUdmSocket::getUdmSocketInfor();
	if (udpSocketInfor->m_udmStatus == UDM_STATE_CONNECTED) {
		SMsgPs2PcResConnect resConnectMsg;
		CUdmSocket::_sendMsg(&resConnectMsg, sizeof(resConnectMsg));
	}
	if (udpSocketInfor->m_udmStatus == UDM_STATE_OPEN) {
		if (m_pingTimeout(realTime)) {
			if (m_pingCount > BSLIB_UDM_PING_MAX) {
				udpSocketInfor->m_udmStatus = UDM_STATE_BROKEN;
				CUdmSocket::notifyBreak();
				return ;
			}
			SMsgPs2PcReqPing reqPing;
			CUdmSocket::_sendMsg(&reqPing, sizeof(reqPing));
			++m_pingCount;
			m_pingTimeout.reset(1000, realTime);
		}
	}
	if (udpSocketInfor->m_udmStatus == UDM_STATE_CLOSING) {
		SMsgPs2PcNtfClose ntfCloseMsg;
		CUdmSocket::_sendMsg(&ntfCloseMsg, sizeof(ntfCloseMsg));
	}
	if (udpSocketInfor->m_udmStatus == UDM_STATE_CLOSED) {
		SMsgPs2PcResClose resCloseMsg;
		CUdmSocket::_sendMsg(&resCloseMsg, sizeof(resCloseMsg));
	}
	CUdmSocket::tickMsg(realTime);
}

}//UDM

}//BSLib


