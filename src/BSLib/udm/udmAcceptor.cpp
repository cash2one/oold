//////////////////////////////////////////////////////////////////////
//	created:	2012/08/20
//	filename:	src\BSLib\udm\udmAcceptor.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include "udmAcceptor.h"
#include "udpThreadMgr.h"
#include "udmMgr.h"

namespace BSLib
{

namespace UDM
{

CUdmAcceptor::CUdmAcceptor(SUdmSocketInfor* udmSocketInfor)
: CUdmSocket(udmSocketInfor)
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
	SUdmSocketInfor* udmSocketInfor = CUdmSocket::getUdmSocketInfor();
	CUdpThread* udpThread = CUdpThreadMgr::singleton().getUdpThread(udmSocketInfor->m_udpThreadID);
	if (udpThread == NULL){
		return BSLIB_UDM_ERROR;
	}
	
	udpThread->getAcceptInfor(m_acceptEvent, m_acceptList);
	udpThread->addUdmAcceptor(this);
	udpThread->setAcceptor(true);

	if (udpThread->isRunning()) {
		if (udmSocketInfor->m_udmStatus == UDM_STATE_BIND) {
			udmSocketInfor->m_udmStatus = UDM_STATE_LISTEN;
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
	udmSocketInfor->m_udmStatus = UDM_STATE_LISTEN;
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
	if (CUdmMgr::singleton().udmSocket(udmSocket->getUdmSocketInfor()) == INVALID_UDMSOCK) {
		return INVALID_UDMSOCK;
	}
	udmSocket->getPeerName(addr, addrlen);
	return 	udmSocket->getUdmSocket();
}

int CUdmAcceptor::close()
{
	SUdmSocketInfor* udmSocketInfor = CUdmSocket::getUdmSocketInfor();
	CUdpThread* udpThread = CUdpThreadMgr::singleton().getUdpThread(udmSocketInfor->m_udpThreadID);
	if (udpThread == NULL){
		return BSLIB_UDM_ERROR;
	}
	udpThread->setAcceptor(false);
	m_acceptList = NULL;
	m_acceptEvent = NULL;
	
	udmSocketInfor->m_udmStatus = UDM_STATE_NONEXIST;
	return BSLIB_UDM_OK;
}

}//UDM

}//BSLib



