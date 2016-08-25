#ifndef __BSLIB_NETWORK_NETSTUBTHREAD_H__
#define __BSLIB_NETWORK_NETSTUBTHREAD_H__

#include <BSLib/utility/ptrQueue.h>
#include <BSLib/utility/dateTime.h>
#include <BSLib/utility/thread/thread.h>
#include <BSLib/utility/timerServer.h>
#include <BSLib/network/netStub.h>
#include <BSLib/network/netServer.h>

namespace BSLib
{

namespace Network
{

struct SNetStubNetInfo
{
	BSLib::uint64 m_recvBytesCount;
	BSLib::uint64 m_sendBytesCount;
	BSLib::uint32 m_recvBytesPerMax;
	BSLib::uint32 m_sendBytesPerMax;

	SNetStubNetInfo()
	{
		m_recvBytesCount = 0;
		m_sendBytesCount = 0;
		m_recvBytesPerMax = 0;
		m_sendBytesPerMax = 0;
	}
};

//////////////////////////////////////////////////////////////////////////
// CNetStubCb
//////////////////////////////////////////////////////////////////////////
class CNetStubCb 
    : public BSLib::Network::INetConnectionCallback
{
public:
	CNetStubCb(CNetStubPtr& stubPtr) : m_stubPtr(stubPtr), m_seconds(0) {}
	virtual ~CNetStubCb()
	{
		m_stubPtr = NULL;
	}

	void recvMsg()
	{
		recvMsg(m_stubPtr->m_netConnectionPtr);
	}

	virtual bool recvMsg(CNetConnectionPtr& connection)
	{
		m_stubPtr->_resetOkeyTick();

		int recvSize = 0;
		while ((recvSize = connection->recv(m_stream)) >= 0 ) {
			if (recvSize == 0){
				return true;
			}
			if (!m_stubPtr->INetStub_cbParseMsg((void*)m_stream.readPtr(), m_stream.readSize())) {
				m_stream.reset();
				return false;
			}
			m_stream.reset();
		}
		return false;
	}

	virtual void terminate()
	{
		m_stubPtr->INetStub_cbTerminate();
	}

	virtual void terminate(CNetConnectionPtr& connection)
	{
		EStubState stubState = m_stubPtr->getState();
		if (stubState == ESS_VERIFY || stubState == ESS_OKAY) {
			m_stubPtr->setState(ESS_RECYCLE);
		}
	}

	void setRealTimer(BSLib::Utility::CRealTime* realTimer)
	{
		m_stubPtr->_setRealTimer(realTimer);
	}

	void setState(EStubState state)
	{
		m_stubPtr->setState(state);
	}

	void setTimerServer(BSLib::Utility::CTimerServer* a_timerServer)
	{
		m_stubPtr->_setTimerServer(a_timerServer);
	}

	EStubState getState()
	{ 
		return m_stubPtr->m_stubState; 
	}

	bool checkVerifyOvertime(BSLib::Utility::CRealTime& realTimer)
	{
		return m_stubPtr->_checkVerifyOvertime(realTimer);
	}

	bool checkOkeyOvertime(BSLib::Utility::CRealTime& realTimer)
	{
		return m_stubPtr->_checkOkeyOvertime(realTimer);
	}

	bool checkDeleteOvertime(BSLib::Utility::CRealTime& realTimer)
	{
		return m_stubPtr->_checkDeleteOvertime(realTimer);
	}

	void getNetInfo(BSLib::Utility::CRealTime& realTimer, SNetStubNetInfo& a_netStubNetInfo)
	{
		CNetConnectionPtr netConnectionPtr = m_stubPtr->getNetConnectionPtr();
		if (netConnectionPtr != NULL) {
			SNetConnectionBytesInfo connectionInfo;
			netConnectionPtr->getNetConnectionInfo(connectionInfo);
			if (m_seconds == 0) {
				m_netConnectBytesInfo = connectionInfo;
				m_seconds = realTimer.seconds();

				a_netStubNetInfo.m_recvBytesCount = m_netConnectBytesInfo.m_recvBytes;
				a_netStubNetInfo.m_sendBytesCount = m_netConnectBytesInfo.m_sendBytes;
				return;
			}
			BSLib::int64 seconds = realTimer.seconds();
			if (m_seconds >= seconds) {
				a_netStubNetInfo.m_recvBytesPerMax = (BSLib::uint32)(connectionInfo.m_recvBytes - m_netConnectBytesInfo.m_recvBytes);
				a_netStubNetInfo.m_sendBytesPerMax = (BSLib::uint32)(connectionInfo.m_sendBytes - m_netConnectBytesInfo.m_sendBytes);

				a_netStubNetInfo.m_recvBytesCount = m_netConnectBytesInfo.m_recvBytes;
				a_netStubNetInfo.m_sendBytesCount = m_netConnectBytesInfo.m_sendBytes;
				return;
			}
			BSLib::int64 t_seconds = seconds - m_seconds;
			a_netStubNetInfo.m_recvBytesPerMax = (BSLib::uint32)((connectionInfo.m_recvBytes - m_netConnectBytesInfo.m_recvBytes)/t_seconds);
			a_netStubNetInfo.m_sendBytesPerMax = (BSLib::uint32)((connectionInfo.m_sendBytes - m_netConnectBytesInfo.m_sendBytes)/t_seconds);

			m_netConnectBytesInfo = connectionInfo;
			m_seconds = seconds;

			a_netStubNetInfo.m_recvBytesCount = m_netConnectBytesInfo.m_recvBytes;
			a_netStubNetInfo.m_sendBytesCount = m_netConnectBytesInfo.m_sendBytes;
		}
	}

	void initStub()
	{
		m_stubPtr->INetStub_initStub();
	}

	void finalStub()
	{
		m_stubPtr->INetStub_finalStub();
	}

	bool INetConnection_sendToNetFromBuff()
	{
		if (m_stubPtr == NULL) {
			return false;
		}
		CNetConnectionPtr connectPtr = m_stubPtr->getNetConnectionPtr();
		if (connectPtr == NULL) {
			return false;
		}
		return connectPtr->INetConnection_sendToNetFromBuff();
	}

	bool INetConnection_isEmptyOfSendBuff()
	{
		if (m_stubPtr == NULL) {
			return true;
		}
		CNetConnectionPtr connectPtr = m_stubPtr->getNetConnectionPtr();
		if (connectPtr == NULL) {
			return true;
		}
		return connectPtr->INetConnection_isEmptyOfSendBuff();
	}

	CNetStubPtr& getNetStub() { return m_stubPtr; }

private:
	CNetStubPtr m_stubPtr;
	BSLib::Utility::CStream m_stream;
	SNetConnectionBytesInfo m_netConnectBytesInfo;
	BSLib::int64 m_seconds;
};
typedef BSLib::Utility::CPointer<CNetStubCb> CNetStubCbPtr;

//////////////////////////////////////////////////////////////////////////
// CNetStubThread
//////////////////////////////////////////////////////////////////////////
class INetServer;

class CNetStubThread 
    : public BSLib::Utility::CThread
{
public:
	CNetStubThread(INetServer* netServer);
	virtual ~CNetStubThread();

	virtual void start();
	virtual uint32 getStubCount() { return (uint32)m_netStubQueue.size() + (uint32)m_verifyList.size() + (uint32)m_okayList.size(); }
	virtual uint32 getVerifyStubCount() { return (uint32)m_verifyList.size(); }
	virtual uint32 getOkayStubCount() { return (uint32)m_okayList.size(); }

	virtual void getFlowInfo(SNetFlowInfo& a_Info, BSLib::Utility::CRealTime& a_realTimer);

	virtual void terminate();

	virtual bool addStub(CNetStubPtr& stubPtr);

protected:
	virtual bool _addStubToNetConnectionMgr(CNetStubPtr& stubPtr, INetConnectionCallbackPtr& netConnectionCb) = 0;
	virtual bool _delStubToNetConnectionMgr(CNetStubPtr& stubPtr) = 0;
	virtual void _wait() = 0;
	virtual void _run();
	virtual void _enterRun() = 0;
	virtual void _leaveRun() = 0;
	void _newTask();
	void _verifyStub();
	void _okayStub();
	void _recyclePeer();
	void _deletePeer();

	void _updateNetBytesInfo(BSLib::Utility::CRealTime& a_realTimer);

private:
	BSLib::Utility::CPtrQueue<CNetStubPtr> m_netStubQueue;
	bool m_isRunning;
	BSLib::Utility::CDelayTimer m_oneSecTimer;
	BSLib::Utility::CDelayTimer m_threeSecTimer;

	std::list<CNetStubCbPtr> m_deleteList;
	std::list<CNetStubCbPtr> m_recycleList;
	std::list<CNetStubCbPtr> m_verifyList;
	std::list<CNetStubCbPtr> m_syncList;
	std::list<CNetStubCbPtr> m_okayList;

	INetServer* m_netServer;
	BSLib::Utility::CTimerServer m_timerServer;

	BSLib::uint64 m_recvBytesCount;
	BSLib::uint64 m_sendBytesCount;
	BSLib::uint32 m_recvBytesPerSMax;
	BSLib::uint32 m_sendBytesPerSMax;
};

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_NETSTUBTHREAD_H__

