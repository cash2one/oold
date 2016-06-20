//////////////////////////////////////////////////////////////////////
//	created:	2012/09/16
//	filename:	src\BSLib\network\netClient.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/network/netClient.h>

namespace BSLib
{

namespace Network
{

//////////////////////////////////////////////////////////////////////////
class CNetClientCb : public BSLib::Network::CNetConnectionCallback
{
public:
	CNetClientCb(CNetClient* netClient) : m_netClient(netClient)
	{
		;
	}
	virtual bool recvMsg(BSLib::Network::CNetConnectionPtr& connection)
	{
		int recvSize = 0;
		while ((recvSize = connection->recv(m_stream)) >= 0 ) {
			if (recvSize == 0){
				return true;
			}
			if (!m_netClient->_cbParseMsg((void*)m_stream.readPtr(), m_stream.readSize())) {
				m_stream.reset();
				return false;
			}
			m_stream.reset();
		}
		return false;
	}

	virtual void terminate(BSLib::Network::CNetConnectionPtr& connection)
	{
		m_netClient->close();
		m_netClient->_cbTerminate();
	}

private:
	CNetClient* m_netClient;
	BSLib::Utility::CStream m_stream;
};

//////////////////////////////////////////////////////////////////////////
// CNetClient
//////////////////////////////////////////////////////////////////////////
CNetClient::CNetClient()
: m_netConnectionPtr(NULL)
{
	;
}

CNetClient::~CNetClient()
{
	m_netConnectionPtr = NULL;
}

void CNetClient::close()
{
	if (m_netConnectionPtr != NULL){
		m_netConnectionPtr->close();
	}
}

int CNetClient::send(BSLib::Utility::CStream& stream, bool useBuff)
{
	if (m_netConnectionPtr == NULL){
		return -1;
	}
	if (!m_netConnectionPtr->isValid()) {
		return -1;
	}
	return m_netConnectionPtr->send(stream, useBuff);
}

int CNetClient::send(const void* msgBuff, unsigned int buffSize, bool useBuff)
{
	if (m_netConnectionPtr == NULL){
		return -1;
	}
	if (!m_netConnectionPtr->isValid()) {
		return -1;
	}
	return m_netConnectionPtr->send(msgBuff, buffSize, useBuff);
}

int CNetClient::recv(BSLib::Utility::CStream& stream)
{
	if (m_netConnectionPtr == NULL){
		return -1;
	}
	return m_netConnectionPtr->recv(stream);
}

int CNetClient::recvBlock(BSLib::Utility::CStream& stream)
{
	if (m_netConnectionPtr == NULL){
		return -1;
	}
	return m_netConnectionPtr->recvBlock(stream);
}


//////////////////////////////////////////////////////////////////////////
// CTcpClient
//////////////////////////////////////////////////////////////////////////
CTcpClient::CTcpClient()
: m_tcpConnectionMgr(NULL)
{
	;
}

CTcpClient::~CTcpClient()
{
	m_tcpClientCb = NULL;
}

bool CTcpClient::connect(const char* serverIP, uint16 serverPort)
{
	if (m_tcpConnectionMgr == NULL) {
		return false;
	}
	if (m_netConnectionPtr == NULL){
		m_netConnectionPtr = new BSLib::Network::CTcpConnection();
		if (m_netConnectionPtr == NULL){
			return false;
		}
	}
	if (m_netConnectionPtr->isValid()){
		return false;
	}
	if (m_tcpClientCb == NULL) {
		m_tcpClientCb = new CNetClientCb(this);
		if (m_tcpClientCb == NULL) {
			return false;
		}
	}
	BSLib::Network::CSockAddr sockServer(serverIP, serverPort);
	if (!m_netConnectionPtr->connect(sockServer, 3)){
		return false;
	}
	if (!m_tcpConnectionMgr->addConnection(m_netConnectionPtr, m_tcpClientCb)) {
		return false;
	}
	return true;
}

void CTcpClient::close()
{
	if (m_netConnectionPtr == NULL || m_tcpConnectionMgr == NULL) {
		return ;
	}
	if (!m_netConnectionPtr->isValid()) {
		return ;
	}
	m_tcpConnectionMgr->delConnection(m_netConnectionPtr->getSockect());
	CNetClient::close();
}

//////////////////////////////////////////////////////////////////////////
// CUdpClient
//////////////////////////////////////////////////////////////////////////
CUdpClient::CUdpClient()
: m_udpConnectionMgr(NULL)
{
	;
}

CUdpClient::~CUdpClient()
{
	m_udpClientCb = NULL;
}

bool CUdpClient::connect(const char* serverIP, uint16 serverPort)
{
	if (m_udpConnectionMgr == NULL) {
		return false;
	}
	if (m_netConnectionPtr == NULL){
		m_netConnectionPtr = new BSLib::Network::CUdpConnection();
		if (m_netConnectionPtr == NULL){
			return false;
		}
	}
	if (m_netConnectionPtr->isValid()){
		return false;
	}
	if (m_udpClientCb == NULL) {
		m_udpClientCb = new CNetClientCb(this);
		if (m_udpClientCb == NULL) {
			return false;
		}
	}
	BSLib::Network::CSockAddr sockServer(serverIP, serverPort);
	if (!m_netConnectionPtr->connect(sockServer, 3)){
		return false;
	}
	if (!m_udpConnectionMgr->addConnection(m_netConnectionPtr, m_udpClientCb)) {
		return false;
	}
	return true;
}


bool CUdpClient::connect(CSockAddr& addrLocal, CSockAddr& addrServer)
{
	if (m_udpConnectionMgr == NULL) {
		return false;
	}
	if (m_netConnectionPtr == NULL){
		m_netConnectionPtr = new BSLib::Network::CUdpConnection();
		if (m_netConnectionPtr == NULL){
			return false;
		}
	}
	if (m_netConnectionPtr->isValid()){
		return false;
	}
	if (m_udpClientCb == NULL) {
		m_udpClientCb = new CNetClientCb(this);
		if (m_udpClientCb == NULL) {
			return false;
		}
	}
	if (!m_netConnectionPtr->connect(addrLocal, addrServer, 3)){
		return false;
	}
	if (!m_udpConnectionMgr->addConnection(m_netConnectionPtr, m_udpClientCb)) {
		return false;
	}
	return true;
}

void CUdpClient::close()
{
	if (m_netConnectionPtr == NULL || m_udpConnectionMgr == NULL) {
		return ;
	}
	if (!m_netConnectionPtr->isValid()) {
		return ;
	}
	m_udpConnectionMgr->delConnection(m_netConnectionPtr->getSockect());
	CNetClient::close();
}

}//Network

}//BSLib

