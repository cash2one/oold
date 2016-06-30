#include <BSLib/utility/dateTime.h>
#include <BSLib/network/netConnectionMgr.h>

namespace BSLib
{

namespace Network
{

INetConnectionMgr::INetConnectionMgr()
: m_addConnSize(0)
, m_delConnSize(0)
, m_connSize(0)
{
	;
}

INetConnectionMgr::~INetConnectionMgr()
{
	;
}

bool INetConnectionMgr::INetConnectionMgr_addConnection(CNetConnectionPtr& connection, CNetConnectionCallbackPtr& netConnectionCb)
{
	if (connection == NULL || netConnectionCb == NULL){
		return false;
	}

	CConnectItem* item = new CConnectItem();
	if (item == NULL){
		return false;
	}

	item->m_connect = connection;
	item->m_callback = netConnectionCb;

	m_mutex.lock();
	m_addConnList.push(item);
	m_addConnSize++;
	m_mutex.unlock();
	return true;
}

bool INetConnectionMgr::INetConnectionMgr_delConnection(int sock)
{
	m_mutex.lock();
	m_delConnList.push(sock);
	m_delConnSize++;
	m_mutex.unlock();
	return true;
}

bool INetConnectionMgr::INetConnectionMgr_epoll(int msSec)
{
	updateConn();

	BSLib::Utility::CSurveyTimer timer;
	int64 start = timer.milliseconds();
	while (_epoll(msSec)) {
		if ((timer.milliseconds() - start) >= msSec) {
			updateConn();
			return true;
		}
	}
	updateConn();
	return false;
}

void INetConnectionMgr::updateConn()
{
	if (m_addConnSize){
		_checkAddConn();
	}
	if (m_delConnSize){
		_checkDelConn();
	}
}

void INetConnectionMgr::_checkAddConn()
{
	std::queue<CConnectItemPtr> addConnListTemp;

	m_mutex.lock();
	while (!m_addConnList.empty()) {
		addConnListTemp.push(m_addConnList.front());
		m_addConnList.pop();
	}
	m_addConnSize = 0;
	m_mutex.unlock();

	while (!addConnListTemp.empty()){
		CConnectItemPtr connPtr = addConnListTemp.front();
		if (connPtr == NULL || connPtr->m_connect == NULL){
			addConnListTemp.pop();
			continue;
		}
		_addConnection(connPtr);
		this->postSend(connPtr->m_connect->getSockect());
		addConnListTemp.pop();
	}
	m_connSize = m_connHashMap.size();
}

void INetConnectionMgr::_checkDelConn()
{
	std::queue<int> delConnListTemp;
	
	m_mutex.lock();
	while (!m_delConnList.empty()) {
		delConnListTemp.push(m_delConnList.front());
		m_delConnList.pop();
	}
	m_delConnSize = 0;
	m_mutex.unlock();

	while (!delConnListTemp.empty()){
		int sock = delConnListTemp.front();
		_delConnection(sock);
		delConnListTemp.pop();
	}
	m_connSize = m_connHashMap.size();
}

bool INetConnectionMgr::_addConnection(CConnectItemPtr& connItemPtr)
{
	m_connHashMap.setValue(connItemPtr->m_connect->getSockect(), connItemPtr);
	if (!_addConnToPoll(connItemPtr)){
		m_connHashMap.remove(connItemPtr->m_connect->getSockect());
		return false;
	}
	connItemPtr->m_connect->setNetConnectionMgr(this);
	return true;
}

void INetConnectionMgr::_delConnection(int sock)
{
	CConnectItemPtr item = m_connHashMap.getValue(sock);
	if (item == NULL || item->m_connect == NULL){
		return;
	}
	_delConnFromPoll(item);

	item->m_connect->setNetConnectionMgr(NULL);

	m_connHashMap.remove(sock);
}

INetConnectionMgr::CConnectItemPtr INetConnectionMgr::_getConnectionItem(int sock)
{
	CConnectItemPtr item = NULL;
	m_connHashMap.getValue(sock, item);
	return item;
}

void INetConnectionMgr::_clearAllConnection()
{
	BSLib::Utility::CHashMap<int, CConnectItemPtr>::iterator it = m_connHashMap.begin();
	for (; it != m_connHashMap.end(); ++it)	{
		CConnectItemPtr &item = it->second;
		if (item == NULL || item->m_connect == NULL){
			continue;
		}
		_delConnFromPoll(item);

		item->m_connect->setNetConnectionMgr(NULL);
	}

	m_connHashMap.clear();
}

}//Network

}//BSLib










