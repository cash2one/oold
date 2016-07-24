#include "udmAcceptor.h"
#include "udpThreadMgr.h"
#include "udmMgr.h"

namespace BSLib
{

namespace UDM
{

CUdmAcceptor::CUdmAcceptor(SUdmSocketInfo* udmSocketInfo)
: CUdmSocket(udmSocketInfo)
, m_acceptEvent(NULL)
{
	;
}

CUdmAcceptor::~CUdmAcceptor()
{
	;
}

int CUdmAcceptor::listen()
{
	SUdmSocketInfo* udmSocketInfo = CUdmSocket::getUdmSocketInfo();
	CUdpThread* udpThread = CUdpThreadMgr::singleton().getUdpThread(udmSocketInfo->m_udpThreadID);
	if (udpThread == NULL){
		return BSLIB_UDM_ERROR;
	}
	
	udpThread->getAcceptInfo(m_acceptEvent, m_acceptList);
	udpThread->addUdmAcceptor(this);
	udpThread->setAcceptor(true);

	if (udpThread->isRunning()) {
		if (udmSocketInfo->m_udmStatus == UDM_STATE_BIND) {
			udmSocketInfo->m_udmStatus = UDM_STATE_LISTEN;
			return BSLIB_UDM_OK;
		}
		return BSLIB_UDM_ERROR;
	}
	udpThread->start();
	if (!udpThread->isValid()) {
		m_acceptList = NULL;
		m_acceptEvent = NULL;
		udpThread->setAcceptor(false);
		return BSLIB_UDM_ERROR;
	}
	udmSocketInfo->m_udmStatus = UDM_STATE_LISTEN;
	return BSLIB_UDM_OK;
}

UDMSOCKET CUdmAcceptor::accept(struct sockaddr* addr, int* addrlen)
{
	if (m_acceptList == NULL){
		return INVALID_UDMSOCK;
	}
	if (m_acceptList->empty()) {
		m_acceptEvent->wait();
		if (m_acceptList->empty()){
			return INVALID_UDMSOCK;
		}
	}
	CUdmSocket* udmSocket = NULL;
	m_acceptList->pop(udmSocket);
	if (udmSocket == NULL) {
		return INVALID_UDMSOCK;
	}
	if (CUdmMgr::singleton().udmSocket(udmSocket->getUdmSocketInfo()) == INVALID_UDMSOCK) {
		return INVALID_UDMSOCK;
	}
	udmSocket->getPeerName(addr, addrlen);
	return 	udmSocket->getUdmSocket();
}

int CUdmAcceptor::close()
{
	SUdmSocketInfo* udmSocketInfo = CUdmSocket::getUdmSocketInfo();
	CUdpThread* udpThread = CUdpThreadMgr::singleton().getUdpThread(udmSocketInfo->m_udpThreadID);
	if (udpThread == NULL){
		return BSLIB_UDM_ERROR;
	}
	udpThread->setAcceptor(false);
	m_acceptList = NULL;
	m_acceptEvent = NULL;
	
	udmSocketInfo->m_udmStatus = UDM_STATE_NONEXIST;
	return BSLIB_UDM_OK;
}

}//UDM

}//BSLib




