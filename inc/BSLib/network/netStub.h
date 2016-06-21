#ifndef __BSLIB_NETWORK_NETSTUB_H__
#define __BSLIB_NETWORK_NETSTUB_H__

#include <BSLib/utility/pointer.h>
#include <BSLib/utility/dateTime.h>
#include <BSLib/utility/timerServer.h>
#include <BSLib/network/netConnection.h>

namespace BSLib
{

namespace Network
{

typedef uint32 StubID;
const StubID INVALID_STUBID = 0;

enum EStubState
{
	ESS_NULL = 0,	//无效状态
	ESS_VERIFY,		//连接验证状态
	ESS_OKAY,		//验证成功，进入正常处理状态
	ESS_RECYCLE,	//连接退出，准备回收
	ESS_DELELE,		//回收,释放资源
	ESS_MAX,
};

class CNetStubCb;

class BSLIB_NETWORK_API CNetStub
{
public:
	CNetStub(CNetConnectionPtr& netConnection);
	virtual ~CNetStub();

	StubID getStubID() { return m_stubID;}
	EStubState getState() { return m_stubState; }

	void setState(EStubState state);
	void gotoNextState();

	CNetConnectionPtr getNetConnectionPtr() { return m_netConnectionPtr; }

	int send(BSLib::Utility::CStream& stream);
	int send(const void* msgBuff, unsigned int buffSize);

	void setNeedPing(bool needPing) { m_needPing = needPing; }

public:
	static void setVerifyStateTimeoutMAX(uint32 verifyTimeoutMAX) { m_verifyTimeout = verifyTimeoutMAX; }
	static void setOkeyStateTimeoutMAX(uint32 okeyTimeoutMAX, uint32 pingTime);

protected:
	virtual void _initStub() = 0;
	virtual void _finalStub() = 0;
	virtual void _cbNotifyPing() = 0;
	virtual bool _cbParseMsg(void* msgBuff, uint32 msgSize) = 0;
	virtual void _cbTerminate() = 0;

	bool _checkVerifyOvertime(BSLib::Utility::CRealTime& realTimer);
	bool _checkOkeyOvertime(BSLib::Utility::CRealTime& realTimer);
	bool _checkDeleteOvertime(BSLib::Utility::CRealTime& realTimer);
	void _setRealTimer(BSLib::Utility::CRealTime* realTimer) { m_realTime = realTimer; }
	void _resetOkeyTick();
	void _setTimerServer(BSLib::Utility::CTimerServer* a_timerServer);
	BSLib::Utility::CTimerServer* _getTimerServer() { return m_timerServer; }

private:
	void _setStubID(StubID& a_stubID) { m_stubID = a_stubID ; }

private:
	StubID m_stubID;
	EStubState m_stubState;
	CNetConnectionPtr m_netConnectionPtr;

	BSLib::Utility::CDelayTimer m_verifyOvertime;
	BSLib::Utility::CDelayTimer m_okeyOvertime;
	BSLib::Utility::CDelayTimer m_deleteOvertime;
	BSLib::Utility::CRealTime* m_realTime;
	uint32 m_errorNotifyPingCount;
	BSLib::Utility::CTimerServer* m_timerServer;
	bool m_needPing;


private:
	static uint32 m_verifyTimeout;
	static uint32 m_okeyTimeout;
	static uint32 m_errorPingMax;

	friend class CNetStubCb;
	friend class CNetStubMgr;
};
typedef BSLib::Utility::CPointer<CNetStub> CNetStubPtr;

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_NETSTUB_H__



