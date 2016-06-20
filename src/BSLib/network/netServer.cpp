//////////////////////////////////////////////////////////////////////
//	created:	2012/09/12
//	filename:	src\BSLib\network\netServer.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/tracer.h>
#include <BSLib/network/tcpAcceptor.h>
#include <BSLib/network/udpAcceptor.h>
#include <BSLib/network/netServer.h>
#include <BSLib/network/tcpConnection.h>
#include <BSLib/network/udpConnection.h>
#include <BSLib/network/netStubMgr.h>
#include "netStubPool.h"

#define BSLIB_NETWORK_ACCEPTOR_WAIT_TIMEOUT 10

namespace BSLib
{

namespace Network
{

//////////////////////////////////////////////////////////////////////////
	
class CTcpAcceptorCb: public BSLib::Network::CNetAcceptorCallback
{
public:
	CTcpAcceptorCb(CNetServer* netServer) : m_netServer(netServer){}
	virtual ~CTcpAcceptorCb(){}

	virtual bool newConnect(int sock, BSLib::Network::CSockAddr& addrLocal, BSLib::Network::CSockAddr& addrPeer, void* tempData)
	{
		if (m_netServer != NULL){
			return m_netServer->_newTcpConnect(sock, addrLocal, addrPeer, tempData);
		}
		return false;
	}

private:
	CNetServer* m_netServer;
};

class CUdpAcceptorCb: public BSLib::Network::CNetAcceptorCallback
{
public:
	CUdpAcceptorCb(CNetServer* netServer) : m_netServer(netServer){}
	virtual ~CUdpAcceptorCb(){}

	virtual bool newConnect(int sock, BSLib::Network::CSockAddr& addrLocal, BSLib::Network::CSockAddr& addrPeer, void* tempData)
	{
		if (m_netServer != NULL){
			return m_netServer->_newUdpConnect(sock, addrLocal, addrPeer, tempData);
		}
		return false;
	}

private:
	CNetServer* m_netServer;
};

//////////////////////////////////////////////////////////////////////////

CNetServer::CNetServer()
: m_netStubMgr(NULL)
, m_tcpAcceptor(NULL)
, m_udpAcceptor(NULL)
, m_acceptorCbPtr(NULL)
, m_tcpAcceptorRunning(false)
, m_udpAcceptorRunning(false)
, m_tcpStubPool(NULL)
, m_udpStubPool(NULL)
{
	;
}

CNetServer::~CNetServer()
{
	;
}

void  CNetServer::getNetInfor(SNetInfor& a_netInfor, BSLib::Utility::CRealTime& realTimer)
{
	if (m_tcpStubPool != NULL) {
		m_tcpStubPool->getStubsInfor(a_netInfor.m_tcpStubsInfor);
		m_tcpStubPool->getFlowInfor(a_netInfor.m_tcpFlowInfor, realTimer);
	}	
	a_netInfor.m_tcpStubsInfor.m_connectTotal = m_tcpCollectCount.getValue();
}

bool CNetServer::_addTcpAccpetor(CSockAddr& acceptorAddr, void* tempData)
{
	if (m_acceptorCbPtr == NULL) {
		m_acceptorCbPtr = new CTcpAcceptorCb(this);
		if (m_acceptorCbPtr == NULL) {
			BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "new CTcpAcceptorCb == NULL");
			return false;
		}
	}
	if (m_tcpAcceptor == NULL) {
		m_tcpAcceptor = new BSLib::Network::CTcpAcceptor();
		if (m_tcpAcceptor == NULL) {
			BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "new CTcpAcceptor == NULL");
			return false;
		}
	}
	if (!m_tcpAcceptor->addAcceptor(acceptorAddr, m_acceptorCbPtr, tempData)) {
		BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "addAcceptor error");
		return false;
	}
	return true;
}

bool CNetServer::_addTcpAccpetor(const std::string& acceptorIP, uint16 acceptPort, void* tempData)
{
	BSLib::Network::CSockAddr tcpSockAddr(acceptorIP.c_str(), acceptPort);

	return _addTcpAccpetor(tcpSockAddr, tempData);
}

bool CNetServer::_addUdpAccpetor(CSockAddr& acceptorAddr, void* tempData)
{
	if (m_acceptorCbPtr == NULL) {
		m_acceptorCbPtr = new CUdpAcceptorCb(this);
		if (m_acceptorCbPtr == NULL) {
			BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "new CUdpAcceptorCb == NULL");
			return false;
		}
	}
	if (m_udpAcceptor == NULL) {
		m_udpAcceptor = new BSLib::Network::CUdpAcceptor();
		if (m_udpAcceptor == NULL) {
			BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "new CUdpAcceptor == NULL");
			return false;
		}
	}
	if (!m_udpAcceptor->addAcceptor(acceptorAddr, m_acceptorCbPtr, tempData)) {
		BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "addAcceptor error");
		return false;
	}
	return true;
}

bool CNetServer::_addUdpAccpetor(const std::string& acceptorIP, uint16 acceptPort, void* tempData)
{
	BSLib::Network::CSockAddr udpSockAddr(acceptorIP.c_str(), acceptPort);

	return _addUdpAccpetor(udpSockAddr, tempData);
}

bool CNetServer::_setTcpStubPool(uint32 maxStub, uint32 minThread, uint32 maxStubPerThd)
{ 
	if (m_tcpStubPool == NULL) {
		m_tcpStubPool = new CNetStubPool(this, NETT_TCP);
		if (m_tcpStubPool == NULL) {
			return false;
		}
	}
	return m_tcpStubPool->init(maxStub, maxStubPerThd, minThread);
}

bool CNetServer::_setUdpStubPool(uint32 maxStub, uint32 minThread, uint32 maxStubPerThd) 
{
	if (m_udpStubPool == NULL) {
		m_udpStubPool = new CNetStubPool(this, NETT_UDP);
		if (m_udpStubPool == NULL) {
			return false;
		}
	}
	return m_udpStubPool->init(maxStub, maxStubPerThd, minThread); 
}

bool CNetServer::_init()
{
	if (m_netStubMgr == NULL) {
		m_netStubMgr = _cbNetStubMgr();
		if (m_netStubMgr == NULL) {
			BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "NetStubMgr == NULL");
			return false;
		}
	}
	
	if (m_tcpAcceptor != NULL) {
		m_tcpAcceptorRunning = true;
		m_tcpAcceptorThread = BSLib::Utility::CHndThread::createThread(&CNetServer::_tcpAcceptorThread, this);
	}
	if (m_udpAcceptor != NULL) {
		m_udpAcceptorRunning = true;
		m_udpAcceptorThread = BSLib::Utility::CHndThread::createThread(&CNetServer::_udpAcceptorThread, this);
	}
	return true;
}

int CNetServer::_final()
{
	if (m_tcpAcceptor != NULL) {
		if (m_tcpAcceptorThread.isValid()) {
			m_tcpAcceptorRunning = false;
			m_tcpAcceptorThread.join();
		}
		BSLIB_SAFE_DELETE(m_tcpAcceptor);
	}
	if (m_udpAcceptor != NULL) {
		if (m_udpAcceptorThread.isValid()) {
			m_udpAcceptorRunning = false;
			m_udpAcceptorThread.join();
		}
		BSLIB_SAFE_DELETE(m_udpAcceptor);
	}
	if (m_tcpStubPool != NULL) {
		m_tcpStubPool->final();
		BSLIB_SAFE_DELETE(m_tcpStubPool);
	}
	if (m_udpStubPool != NULL) {
		m_udpStubPool->final();
		BSLIB_SAFE_DELETE(m_udpStubPool);
	}
	if (m_netStubMgr != NULL) {
		m_netStubMgr->clear();
	}
	return 0;
}

bool CNetServer::_newTcpConnect(int sock, BSLib::Network::CSockAddr& addrLocal, BSLib::Network::CSockAddr& addrPeer, void* tempData)
{
	BSLIB_LOG_INFOR(BSLib::ETT_BSLIB_NETWORK, "TCP[%d][%s:%d]<--[%s:%d] connect", sock, addrLocal.getIP().c_str(), addrLocal.getPort(), addrPeer.getIP().c_str(), addrPeer.getPort());
	m_tcpCollectCount.increment();

	BSLib::Network::CNetConnectionPtr tcpNetConnPtr = new BSLib::Network::CTcpConnection(sock);
	if (tcpNetConnPtr == NULL){
		BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "new CTcpConnection == NULL");
		return false;
	}
	if (m_tcpStubPool == NULL) {
		BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "tcpStubPool == NULL");
		return false;
	}
	BSLib::Network::CNetStubPtr tcpStub = _cbNewTcpStub(tcpNetConnPtr, tempData);
	if (tcpStub == NULL){
		BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "create TcpStub error");
		return false;
	}
	if (!m_tcpStubPool->addStub(tcpStub)) {
		BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "TcpStub add to tcpStubPool error");
		return false;
	}
	if (m_netStubMgr != NULL){
		m_netStubMgr->addStub(tcpStub);
	}
	return true;
}

bool CNetServer::_newUdpConnect(int sock, BSLib::Network::CSockAddr& addrLocal, BSLib::Network::CSockAddr& addrPeer, void* tempData)
{
	BSLIB_LOG_INFOR(BSLib::ETT_BSLIB_NETWORK, "UDP[%d][%s:%d]<--[%s:%d] connect", sock, addrLocal.getIP().c_str(), addrLocal.getPort(), addrPeer.getIP().c_str(), addrPeer.getPort());

	BSLib::Network::CNetConnectionPtr udpNetConnPtr = new BSLib::Network::CUdpConnection(sock);
	if (udpNetConnPtr == NULL){
		BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "new CUdpConnection == NULL");
		return false;
	}
	if (m_udpStubPool == NULL) {
		BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "udpStubPool == NULL");
		return false;
	}
	BSLib::Network::CNetStubPtr udpStub = _cbNewUdpStub(udpNetConnPtr, tempData);
	if (udpStub == NULL){
		BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "create UdpStub error");
		return false;
	}
	if (!m_udpStubPool->addStub(udpStub)) {
		BSLIB_LOG_ERROR(BSLib::ETT_BSLIB_NETWORK, "udpStub add to udpStubPool error");
		return false;
	}
	if (m_netStubMgr != NULL){
		m_netStubMgr->addStub(udpStub);
	}
	return true;
}

int CNetServer::_tcpAcceptorThread(void* para)
{
	while (m_tcpAcceptorRunning) {
		m_tcpAcceptor->waitSocket(15);
	}
	m_tcpAcceptorRunning = false;
	return 0;
}

int CNetServer::_udpAcceptorThread(void* para)
{
	while (m_udpAcceptorRunning) {
		m_udpAcceptor->waitSocket(15);
	}
	m_udpAcceptorRunning = false;
	return 0;
}

}//Network

}//BSLib


