#ifndef __GFLIB_COMMONSERVER_COMMONCLIENT_H__
#define __GFLIB_COMMONSERVER_COMMONCLIENT_H__

#include <BSLib/utility/pointer.h>
#include <BSLib/utility/thread/thread.h>
#include <BSLib/utility/timerServer.h>
#include <BSLib/network/netClient.h>
#include <BSLib/framework/message/msgExecMgr.h>
#include <GFLib/commonServer/service.h>

namespace GFLib
{

namespace CommonServer
{

class GFLIB_COMMONSERVER_API CCommonClient 
    :public IService,
    public BSLib::Network::CTcpClient,
    public BSLib::Network::CTcpConnectionMgr
{
public:
	CCommonClient(GFLib::SServerID& a_serverID, const std::string& a_serverKey);
	virtual ~CCommonClient();

	virtual bool IService_sendMsg(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	virtual bool IService_sendMsg(GFLib::CMessage& msg);
	virtual void IService_close();

	void start();
	void join();
	bool isValid();

	void terminate();

	void setNeedReconnect(bool a_reconnect) { m_needReconnect = a_reconnect; }
	void setNeedTerminateServer(bool a_terminateServer) { m_neetTerminateServer = a_terminateServer; }
	void setNeedPing(bool a_needPing) { m_neetPing = a_needPing; }

	void setServerIPAndPort(const std::string& connectIP, int connectPort) { m_connectIP = connectIP; m_connectPort = connectPort; }

protected:
	void _initClient();	
	void _notifyServerID();
	void _finalClient();

	virtual bool _INetClient_cbParseMsg(void* msgBuff, BSLib::uint32 msgSize);
	virtual void _INetClient_cbTerminate();
	
	virtual GFLib::StubID _IService_getStubID() { return INVALID_STUBID; }

	int _run(void* a_para);

	BSLib::Utility::CTimerServer* _getTimerServer() { return &m_timerServer; }

private:
	bool _connectServer();
	void _initClientMsg();

	void _onMsgServerLinkXS2XXReqPing(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg);
	void _onMsgServerLinkXX2XSResPing(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg);

	void _onMsgServerLinkXS2XXResServerID(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg);
	void _afterMsgHandlerCommonClient(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg);


private:
	bool m_isRunning;
	std::string m_connectIP;
	int m_connectPort;
	BSLib::Utility::CTimerServer m_timerServer;
	BSLib::Utility::CHndThread m_hndThread;
	bool m_needReconnect;
	bool m_neetTerminateServer;
	bool m_neetPing;

	BSLib::Utility::CDelayTimer m_okeyOvertime;
	BSLib::uint32 m_pingCount;
};
typedef BSLib::Utility::CPointer<CCommonClient> CCommonClientPtr;

}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_COMMONCLIENT_H__


