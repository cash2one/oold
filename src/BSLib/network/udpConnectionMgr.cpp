#include <BSLib/udm/udm.h>
#include <BSLib/network/udpConnectionMgr.h>

namespace BSLib
{

namespace Network
{

CUdpConnectionMgr::CUdpConnectionMgr()
: m_udmEpollID(-1)
{
	m_udmEpollID = BSLib::UDM::epollCreate();
}

CUdpConnectionMgr::~CUdpConnectionMgr()
{
	if (m_udmEpollID != -1) {
		BSLib::UDM::epollRelease(m_udmEpollID);
		m_udmEpollID = -1;
	}
}

bool CUdpConnectionMgr::INetConnectionMgr_postSend(int udpSocket)
{
	if (m_udmEpollID == -1) {
		return false;
	}
	return BSLib::UDM::epollAddSock(m_udmEpollID, udpSocket, BSLib::UDM::UDM_EPOLL_WRITE, NULL) == BSLIB_UDM_OK;
}

bool CUdpConnectionMgr::_INetConnectionMgr_addConnToPoll(CConnectItemPtr& connItemPtr)
{
	if (m_udmEpollID == -1) {
		return false;
	}
	CConnectItem* item = (CConnectItem*)connItemPtr;
	if (item == NULL || item->m_connect == NULL) {
		return false;
	}
	if (!item->m_connect->isValid()){
		return false;
	}
	if (item->m_connect->getSockectType() != NETT_UDP){
		return false;
	}
	return BSLib::UDM::epollAddSock(m_udmEpollID, item->m_connect->getSockect(), BSLib::UDM::UDM_EPOLL_READ | BSLib::UDM::UDM_EPOLL_WRITE | BSLib::UDM::UDM_EPOLL_ERROR, NULL) == BSLIB_UDM_OK;
}

void CUdpConnectionMgr::_INetConnectionMgr_delConnFromPoll(CConnectItemPtr& connItemPtr)
{
	if (m_udmEpollID == -1) {
		return ;
	}
	CConnectItem* item = (CConnectItem*) connItemPtr;
	if (item == NULL || item->m_connect == NULL) {
		return ;
	}
	BSLib::UDM::epollDelSock(m_udmEpollID, item->m_connect->getSockect(), BSLib::UDM::UDM_EPOLL_READ | BSLib::UDM::UDM_EPOLL_WRITE | BSLib::UDM::UDM_EPOLL_ERROR);
}

bool CUdpConnectionMgr::_INetConnectionMgr_epoll(int msSec)
{
	if (m_udmEpollID == -1) {
		return false;
	}
	BSLib::UDM::SEpollEvent epollEvent[256];
	int waitCount = BSLib::UDM::epollWait(m_udmEpollID, epollEvent, 256, msSec);
	if (waitCount == 0) {
		return true;
	} else if (waitCount < 0) {
		return false;
	}
	for (int i=0; i<waitCount; ++i)	{
		CConnectItemPtr itemPtr = INetConnectionMgr::_getConnectionItem(epollEvent[i].m_udmSocket);
		if (itemPtr == NULL) {
			continue;
		}
		CConnectItem* item = (CConnectItem*)itemPtr;
		if (item == NULL) {
			INetConnectionMgr::_delConnection(epollEvent[i].m_udmSocket);
			continue;
		}
		if (epollEvent[i].m_udmEpollEvent & BSLib::UDM::UDM_EPOLL_READ) {
			if (!_readScoket(epollEvent[i].m_udmSocket, item)) {
				_terminateScoket(epollEvent[i].m_udmSocket, item);
			}
		} 
		if (epollEvent[i].m_udmEpollEvent & BSLib::UDM::UDM_EPOLL_WRITE) {
			if (!_writeScoket(epollEvent[i].m_udmSocket, item)) {
				_terminateScoket(epollEvent[i].m_udmSocket, item);
			}
		}
		if (epollEvent[i].m_udmEpollEvent & BSLib::UDM::UDM_EPOLL_ERROR) {
			_terminateScoket(epollEvent[i].m_udmSocket, item);
		} 
	}
	return true;
}

bool CUdpConnectionMgr::_readScoket(int& udmSocket, void* data)
{
	CConnectItem* item = (CConnectItem*)data;
	if (item == NULL){
		return false;
	}
	if (item->m_connect == NULL || item->m_callback == NULL){
		return false;
	}
	if (!item->m_connect->isValid()){
		return false;
	}
	if (!item->m_connect->recvToBuffFromNet()){
		return false;
	}
	return item->m_callback->recvMsg(item->m_connect);
}

bool CUdpConnectionMgr::_writeScoket(int& udmSocket, void* data)
{
	CConnectItem* item = (CConnectItem*)data;
	if (item == NULL){
		return false;
	}
	if (item->m_connect == NULL || item->m_callback == NULL){
		return false;
	}
	if (!item->m_connect->isValid()){
		return false;
	}
	return item->m_connect->sendToNetFromBuff();
}

void CUdpConnectionMgr::_terminateScoket(int& udmSocket, void* data)
{
	CConnectItem* item = (CConnectItem*)data;
	if (item == NULL){
		return ;
	}
	if (item->m_connect == NULL || item->m_callback == NULL){
		return ;
	}
	//if (item->m_connect->isValid()){
		item->m_callback->terminate(item->m_connect);
		item->m_connect->close();
	//}

	INetConnectionMgr::_delConnection(udmSocket);
}

}//Network

}//BSLib


