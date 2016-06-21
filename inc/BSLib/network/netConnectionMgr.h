#ifndef __BSLIB_NETWOEK_NETCONNECTIONMGR_H__
#define __BSLIB_NETWOEK_NETCONNECTIONMGR_H__

#include <queue>
#include <BSLib/utility/thread/mutex.h>
#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/thread/thread.h>
#include <BSLib/network/netConnection.h>

namespace BSLib
{

namespace Network
{

class BSLIB_NETWORK_API CNetConnectionMgr
{
protected:
	class CConnectItem
	{
	public:
		CNetConnectionPtr m_connect;
		CNetConnectionCallbackPtr m_callback;
	};
	typedef BSLib::Utility::CPointer<CConnectItem> CConnectItemPtr;

public:
	CNetConnectionMgr();
	virtual ~CNetConnectionMgr();

	//支持多线程添加
	virtual bool addConnection(CNetConnectionPtr& connection, CNetConnectionCallbackPtr& netConnectionCb);
	//支持多线程删除
	virtual bool delConnection(int sock);

	//轮询方式调用
	//执行连接的recv和send
	virtual bool epoll(int msSec);

	//通知socket发送
	virtual bool postSend(int tcpSocket) = 0;
	
	uint32 getConnectionCount() { return m_connSize + m_addConnSize - m_delConnSize; }
	
	//必须与epoll在同一个线程
	void updateConn();

protected:
	void _checkAddConn();
	void _checkDelConn();

	bool _addConnection(CConnectItemPtr& connItemPtr);
	void _delConnection(int sock);

	void _clearAllConnection();
	
	CConnectItemPtr _getConnectionItem(int sock);

	virtual bool _addConnToPoll(CConnectItemPtr& connItemPtr) = 0;
	virtual void _delConnFromPoll(CConnectItemPtr& connItemPtr) = 0;
	virtual bool _epoll(int msSec) = 0;

private:
	BSLib::Utility::CHashMap<int, CConnectItemPtr> m_connHashMap;

	std::queue<CConnectItemPtr> m_addConnList;
	uint32 m_addConnSize;
	
	std::queue<int> m_delConnList;
	uint32 m_delConnSize;

	BSLib::Utility::CMutex m_mutex;

	uint32 m_connSize;
};

}//Network

}//BSLib

#endif//__BSLIB_NETWOEK_NETCONNECTIONMGR_H__

