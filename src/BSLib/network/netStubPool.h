#ifndef __BSLIB_NETWORK_NETSTUBPOOL_H__
#define __BSLIB_NETWORK_NETSTUBPOOL_H__

#include <BSLib/utility/thread/thread.h>
#include <BSLib/utility/dateTime.h>
#include <BSLib/network/netStub.h>
#include <BSLib/network/netServer.h>
#include <BSLib/network/netServer.h>

namespace BSLib
{

namespace Network
{

class CNetServer;

class CNetStubPool
{
public:
	CNetStubPool(CNetServer* netServer, ENetType netType);
	virtual ~CNetStubPool();

	virtual bool init(const uint32 maxStub, uint32 countPerThd, const uint32 minThread);
	virtual void final();
 	virtual uint32 getStubCount();
	virtual bool addStub(CNetStubPtr& stubPtr);

	void getStubsInfo(SNetStubsInfo& a_infor);
	void getFlowInfo(SNetFlowInfo& a_infor, BSLib::Utility::CRealTime& realTimer);

private:
	virtual bool _addStub(CNetStubPtr& stubPtr);

private:
	CNetServer* m_netServer;
	ENetType m_netType;
	uint32 m_maxStub;
	uint32 m_countPerThd;
	uint32 m_countThread;
	uint32 m_maxThread;
	BSLib::Utility::CThreadArray m_threadArray;

	BSLib::uint64 m_recvBytesCount;
	BSLib::uint64 m_sendBytesCount;
	BSLib::int64 m_seconds;
};

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_NETSTUBPOOL_H__


