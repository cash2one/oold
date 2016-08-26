#include <BSLib/network/tcpConnection.h>
#include <BSLib/network/tcpConnectionMgr.h>
#include "netinit.h"
#include "tcpEpoll.h"

namespace BSLib
{

namespace Network
{

CTcpConnectionMgr::CTcpConnectionMgr()
: m_tcpEpoll(NULL)
{
#ifdef WIN32
	CNetInit::singleton();
#endif

	m_tcpEpoll = new CTcpEpoll();
	if (m_tcpEpoll != NULL) {
		if (m_tcpEpoll->createEpoll()) {
			BSLib::Utility::CFunctionObject<bool, CTcpConnectionMgr, SOCKET&, void*> readSocketFun(&CTcpConnectionMgr::_readScoket, this);
			m_tcpEpoll->setReadSocketFun(readSocketFun);

			BSLib::Utility::CFunctionObject<bool, CTcpConnectionMgr, SOCKET&, void*> writeSocketFun(&CTcpConnectionMgr::_writeScoket, this);
			m_tcpEpoll->setWriteSocketFun(writeSocketFun);

			BSLib::Utility::CFunctionObject<void, CTcpConnectionMgr, SOCKET&, void*> terminateSocketFun(&CTcpConnectionMgr::_terminateScoket, this);
			m_tcpEpoll->setTerminateSocketFun(terminateSocketFun);
		}
	}
}

CTcpConnectionMgr::~CTcpConnectionMgr()
{
	if (m_tcpEpoll != NULL) {
		m_tcpEpoll->releaseEpoll();
		BSLIB_SAFE_DELETE(m_tcpEpoll);
	}
}

bool CTcpConnectionMgr::INetConnectionMgr_postSend(int tcpSocket)
{
	if (m_tcpEpoll == NULL) {
		return false;
	}
	return m_tcpEpoll->notifySend(tcpSocket);
}

bool CTcpConnectionMgr::_INetConnectionMgr_addConnToPoll(CConnectItemPtr& connItemPtr)
{
	if (m_tcpEpoll == NULL) {
		return false;
	}

	CConnectItem* item = (CConnectItem*) connItemPtr;
	if (item == NULL || item->m_connect == NULL) {
		return false;
	}
	if (!item->m_connect->INetConnection_isValid()){
		return false;
	}
	SOCKET socket = item->m_connect->INetConnection_getSockect();
	if (item->m_connect->INetConnection_getSockectType() != NETT_TCP){
		return false;
	}

	if (!m_tcpEpoll->addTcpToEpoll(socket, item)) {
		return false;
	}
	if (!m_tcpEpoll->postRecv(socket)) {
		m_tcpEpoll->delTcpFromEpoll(socket);
		return false;
	}
// 	if (!m_tcpEpoll->notifyRecv(socket, NULL)) {
// 		m_tcpEpoll->delTcpFromEpoll(socket);
// 		return false;
// 	}
	return true;
}

void CTcpConnectionMgr::_INetConnectionMgr_delConnFromPoll(CConnectItemPtr& connItemPtr)
{
	if (m_tcpEpoll == NULL) {
		return ;
	}
	CConnectItem* item = (CConnectItem*) connItemPtr;
	if (item == NULL || item->m_connect == NULL) {
		return ;
	}
	m_tcpEpoll->delTcpFromEpoll(item->m_connect->INetConnection_getSockect());
}

bool CTcpConnectionMgr::_INetConnectionMgr_epoll(int msSec)
{
	if (m_tcpEpoll == NULL) {
		return false;
	}
	return m_tcpEpoll->epoll(msSec);
}

bool CTcpConnectionMgr::_readScoket(SOCKET& tcpSocket, void* data)
{
	CConnectItem* item = (CConnectItem*)data;
	if (item == NULL){
		return false;
	}
	if (item->m_connect == NULL || item->m_callback == NULL){
		return false;
	}
	if (!item->m_connect->INetConnection_isValid()){
		return false;
	}
	if (!item->m_connect->recvNet2Buff()){
		return false;
	}
	return item->m_callback->recvMsg(item->m_connect);
}

bool CTcpConnectionMgr::_writeScoket(SOCKET& tcpSocket, void* data)
{
	CConnectItem* item = (CConnectItem*)data;
	if (item == NULL){
		return false;
	}
	if (item->m_connect == NULL || item->m_callback == NULL){
		return false;
	}
	if (!item->m_connect->INetConnection_isValid()){
		return false;
	}
	return item->m_connect->INetConnection_sendBuff2Net();
}

void CTcpConnectionMgr::_terminateScoket(SOCKET& tcpSocket, void* data)
{
	CConnectItem* item = (CConnectItem*)data;
	if (item == NULL){
		return ;
	}
	if (item->m_connect == NULL || item->m_callback == NULL){
		return ;
	}
	if (item->m_connect->INetConnection_isValid()){
		item->m_connect->INetConnection_close();
		item->m_callback->terminate(item->m_connect);
	}

	INetConnectionMgr::_delConnection((int)tcpSocket);
}

}//Network

}//BSLib

