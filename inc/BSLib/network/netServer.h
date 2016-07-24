#ifndef __BSLIB_NETWORK_NETSERVER_H__
#define __BSLIB_NETWORK_NETSERVER_H__

#include <BSLib/utility/thread/thread.h>
#include <BSLib/network/netAcceptor.h>
#include <BSLib/network/netStubMgr.h>

namespace BSLib
{

namespace Network
{

class CNetStubPool;

struct SNetStubsInfo
{
	BSLib::uint32 m_connectTotal;	//链接总次数
	BSLib::uint32 m_stubCount;		//链接数
	BSLib::uint32 m_stubVerifyCount;//正在验证的链接数
	BSLib::uint32 m_stubOkayCount;	//验证成功的链接数

	SNetStubsInfo()
	{
		m_connectTotal = 0;
		m_stubCount = 0;
		m_stubVerifyCount = 0;
		m_stubOkayCount = 0;
	}
};

struct SNetFlowInfo
{
	BSLib::uint64 m_recvBytesCount;		//总接受字节数量
	BSLib::uint64 m_sendBytesCount;		//总发送字节数量	
	BSLib::uint32 m_recvBytesPerMax;	//最大每秒接受字节数量
	BSLib::uint32 m_sendBytesPerMax;	//最大每秒发送字节数量

	BSLib::uint32 m_recvBytesPerStubMax;	//最大每秒接受字节数量
	BSLib::uint32 m_sendBytesPerStubMax;	//最大每秒发送字节数量

	SNetFlowInfo()
	{
		m_recvBytesCount = 0;
		m_sendBytesCount = 0;
		m_recvBytesPerMax = 0;
		m_sendBytesPerMax = 0;
		m_recvBytesPerStubMax = 0;
		m_sendBytesPerStubMax = 0;
	}
};

struct SNetInfo
{
	SNetStubsInfo m_tcpStubsInfo;
	SNetFlowInfo m_tcpFlowInfo;
};

class  BSLIB_NETWORK_API INetServer
{
public:
	INetServer();
	virtual ~INetServer();

	CNetStubMgr* getNetStubMgr() { return m_netStubMgr; }

	void getNetInfo(SNetInfo& a_netInfo, BSLib::Utility::CRealTime& realTimer);

protected:
	bool _addTcpAccpetor(CSockAddr& acceptorAddr, void* tempData = NULL);
	bool _addTcpAccpetor(const std::string& acceptorIP, uint16 acceptPort, void* tempData = NULL);
	bool _addUdpAccpetor(CSockAddr& acceptorAddr, void* tempData = NULL);
	bool _addUdpAccpetor(const std::string& acceptorIP, uint16 acceptPort, void* tempData = NULL);
	
	/// @param	uint32 maxStub 最多容纳NetStub数量
	/// @param	uint32 minThread 最少启动线程数量
	/// @param	uint32 maxStubPerThd 每个线程最多容纳NetStub数量
	bool _setTcpStubPool(uint32 maxStub, uint32 minThread, uint32 maxStubPerThd);
	bool _setUdpStubPool(uint32 maxStub, uint32 minThread, uint32 maxStubPerThd);

	virtual bool _INetServer_init();
	virtual int _INetServer_final();

	virtual CNetStubMgr* _INetServer_cbNetStubMgr() = 0;
	virtual CNetStubPtr _INetServer_cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData) = 0;
	virtual CNetStubPtr _INetServer_cbNewUdpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData) = 0;

private:	
	bool _newTcpConnect(int sock, BSLib::Network::CSockAddr& addrLocal, BSLib::Network::CSockAddr& addrPeer, void* tempData);
	bool _newUdpConnect(int sock, BSLib::Network::CSockAddr& addrLocal, BSLib::Network::CSockAddr& addrPeer, void* tempData);
	int _tcpAcceptorThread(void* para);
	int _udpAcceptorThread(void* para);

private:
	CNetStubMgr* m_netStubMgr;

	BSLib::Network::INetAcceptor* m_tcpAcceptor;
	BSLib::Utility::CHndThread m_tcpAcceptorThread;

	BSLib::Network::INetAcceptor* m_udpAcceptor;
	BSLib::Utility::CHndThread m_udpAcceptorThread;

	BSLib::Network::CNetAcceptorCallbackPtr m_acceptorCbPtr;
	bool m_tcpAcceptorRunning;
	bool m_udpAcceptorRunning;
	CNetStubPool* m_tcpStubPool;
	CNetStubPool* m_udpStubPool;
	BSLib::Utility::CAtomic m_tcpCollectCount;

	friend class CTcpAcceptorCb;
	friend class CUdpAcceptorCb;
};

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_NETSERVER_H__

