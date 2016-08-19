#include <BSLib/network/netClient.h>

namespace BSLib
{

namespace Network
{

//////////////////////////////////////////////////////////////////////////
class CNetClientCb : public BSLib::Network::CNetConnectionCallback
{
public:
	CNetClientCb(INetClient* netClient) : m_netClient(netClient)
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
			if (!m_netClient->_INetClient_cbParseMsg((void*)m_stream.readPtr(), m_stream.readSize())) {
				m_stream.reset();
				return false;
			}
			m_stream.reset();
		}
		return false;
	}

	virtual void terminate(BSLib::Network::CNetConnectionPtr& connection)
	{
		m_netClient->INetClient_close();
		m_netClient->_INetClient_cbTerminate();
	}

private:
	INetClient* m_netClient;
	BSLib::Utility::CStream m_stream;
};

//////////////////////////////////////////////////////////////////////////
// CNetClient
//////////////////////////////////////////////////////////////////////////
INetClient::INetClient()
: m_netConnectionPtr(NULL)
{
	;
}

INetClient::~INetClient()
{
	m_netConnectionPtr = NULL;
}

void INetClient::INetClient_close()
{
	if (m_netConnectionPtr != NULL){
		m_netConnectionPtr->INetConnection_close();
	}
}

int INetClient::send(BSLib::Utility::CStream& stream, bool useBuff)
{
	if (m_netConnectionPtr == NULL){
		return -1;
	}
	if (!m_netConnectionPtr->INetConnection_isValid()) {
		return -1;
	}
	return m_netConnectionPtr->send(stream, useBuff);
}

int INetClient::send(const void* msgBuff, unsigned int buffSize, bool useBuff)
{
	if (m_netConnectionPtr == NULL){
		return -1;
	}
	if (!m_netConnectionPtr->INetConnection_isValid()) {
		return -1;
	}
	return m_netConnectionPtr->send(msgBuff, buffSize, useBuff);
}

int INetClient::recv(BSLib::Utility::CStream& stream)
{
	if (m_netConnectionPtr == NULL){
		return -1;
	}
	return m_netConnectionPtr->recv(stream);
}

int INetClient::recvBlock(BSLib::Utility::CStream& stream)
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

bool CTcpClient::INetClient_connect(const char* serverIP, uint16 serverPort)
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
	if (m_netConnectionPtr->INetConnection_isValid()){
		return false;
	}
	if (m_tcpClientCb == NULL) {
		m_tcpClientCb = new CNetClientCb(this);
		if (m_tcpClientCb == NULL) {
			return false;
		}
	}
	BSLib::Network::CSockAddr sockServer(serverIP, serverPort);
	if (!m_netConnectionPtr->INetConnection_connect(sockServer, 3)){
		return false;
	}
	if (!m_tcpConnectionMgr->INetConnectionMgr_addConnection(m_netConnectionPtr, m_tcpClientCb)) {
		return false;
	}
	return true;
}

void CTcpClient::INetClient_close()
{
	if (m_netConnectionPtr == NULL || m_tcpConnectionMgr == NULL) {
		return ;
	}
	if (!m_netConnectionPtr->INetConnection_isValid()) {
		return ;
	}
	m_tcpConnectionMgr->INetConnectionMgr_delConnection(m_netConnectionPtr->INetConnection_getSockect());
	INetClient::INetClient_close();
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

bool CUdpClient::INetClient_connect(const char* serverIP, uint16 serverPort)
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
	if (m_netConnectionPtr->INetConnection_isValid()){
		return false;
	}
	if (m_udpClientCb == NULL) {
		m_udpClientCb = new CNetClientCb(this);
		if (m_udpClientCb == NULL) {
			return false;
		}
	}
	BSLib::Network::CSockAddr sockServer(serverIP, serverPort);
	if (!m_netConnectionPtr->INetConnection_connect(sockServer, 3)){
		return false;
	}
	if (!m_udpConnectionMgr->INetConnectionMgr_addConnection(m_netConnectionPtr, m_udpClientCb)) {
		return false;
	}
	return true;
}


bool CUdpClient::INetConnection_connect(CSockAddr& addrLocal, CSockAddr& addrServer)
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
	if (m_netConnectionPtr->INetConnection_isValid()){
		return false;
	}
	if (m_udpClientCb == NULL) {
		m_udpClientCb = new CNetClientCb(this);
		if (m_udpClientCb == NULL) {
			return false;
		}
	}
	if (!m_netConnectionPtr->INetConnection_connect(addrLocal, addrServer, 3)){
		return false;
	}
	if (!m_udpConnectionMgr->INetConnectionMgr_addConnection(m_netConnectionPtr, m_udpClientCb)) {
		return false;
	}
	return true;
}

void CUdpClient::INetClient_close()
{
	if (m_netConnectionPtr == NULL || m_udpConnectionMgr == NULL) {
		return ;
	}
	if (!m_netConnectionPtr->INetConnection_isValid()) {
		return ;
	}
	m_udpConnectionMgr->INetConnectionMgr_delConnection(m_netConnectionPtr->INetConnection_getSockect());
	INetClient::INetClient_close();
}

}//Network

}//BSLib


