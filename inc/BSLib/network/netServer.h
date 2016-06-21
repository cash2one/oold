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

struct SNetStubsInfor
{
	BSLib::uint32 m_connectTotal;	//�����ܴ���
	BSLib::uint32 m_stubCount;		//������
	BSLib::uint32 m_stubVerifyCount;//������֤��������
	BSLib::uint32 m_stubOkayCount;	//��֤�ɹ���������

	SNetStubsInfor()
	{
		m_connectTotal = 0;
		m_stubCount = 0;
		m_stubVerifyCount = 0;
		m_stubOkayCount = 0;
	}
};

struct SNetFlowInfor
{
	BSLib::uint64 m_recvBytesCount;		//�ܽ����ֽ�����
	BSLib::uint64 m_sendBytesCount;		//�ܷ����ֽ�����	
	BSLib::uint32 m_recvBytesPerMax;	//���ÿ������ֽ�����
	BSLib::uint32 m_sendBytesPerMax;	//���ÿ�뷢���ֽ�����

	BSLib::uint32 m_recvBytesPerStubMax;	//���ÿ������ֽ�����
	BSLib::uint32 m_sendBytesPerStubMax;	//���ÿ�뷢���ֽ�����

	SNetFlowInfor()
	{
		m_recvBytesCount = 0;
		m_sendBytesCount = 0;
		m_recvBytesPerMax = 0;
		m_sendBytesPerMax = 0;
		m_recvBytesPerStubMax = 0;
		m_sendBytesPerStubMax = 0;
	}
};

struct SNetInfor
{
	SNetStubsInfor m_tcpStubsInfor;
	SNetFlowInfor m_tcpFlowInfor;
};

class  BSLIB_NETWORK_API CNetServer
{
public:
	CNetServer();
	virtual ~CNetServer();

	CNetStubMgr* getNetStubMgr() { return m_netStubMgr; }

	void getNetInfor(SNetInfor& a_netInfor, BSLib::Utility::CRealTime& realTimer);

protected:
	bool _addTcpAccpetor(CSockAddr& acceptorAddr, void* tempData = NULL);
	bool _addTcpAccpetor(const std::string& acceptorIP, uint16 acceptPort, void* tempData = NULL);
	bool _addUdpAccpetor(CSockAddr& acceptorAddr, void* tempData = NULL);
	bool _addUdpAccpetor(const std::string& acceptorIP, uint16 acceptPort, void* tempData = NULL);
	
	/// @brief
	/// @return	bool
	/// @param	uint32 maxStub �������NetStub����
	/// @param	uint32 minThread ���������߳�����
	/// @param	uint32 maxStubPerThd ÿ���߳��������NetStub����
	bool _setTcpStubPool(uint32 maxStub, uint32 minThread, uint32 maxStubPerThd);
	bool _setUdpStubPool(uint32 maxStub, uint32 minThread, uint32 maxStubPerThd);

	virtual bool _init();
	virtual int _final();

	virtual CNetStubMgr* _cbNetStubMgr() = 0;
	virtual CNetStubPtr _cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData) = 0;
	virtual CNetStubPtr _cbNewUdpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData) = 0;

private:	
	bool _newTcpConnect(int sock, BSLib::Network::CSockAddr& addrLocal, BSLib::Network::CSockAddr& addrPeer, void* tempData);
	bool _newUdpConnect(int sock, BSLib::Network::CSockAddr& addrLocal, BSLib::Network::CSockAddr& addrPeer, void* tempData);
	int _tcpAcceptorThread(void* para);
	int _udpAcceptorThread(void* para);

private:
	CNetStubMgr* m_netStubMgr;
	BSLib::Network::CNetAcceptor* m_tcpAcceptor;
	BSLib::Utility::CHndThread m_tcpAcceptorThread;
	BSLib::Network::CNetAcceptor* m_udpAcceptor;
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

