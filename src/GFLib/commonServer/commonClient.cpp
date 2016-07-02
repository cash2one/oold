#include <BSLib/framework/message/msgDebug.h>
#include <BSLib/utility/thread/threadData.h>
#include <BSLib/framework/message/msgDebug.h>
#include <GFLib/commonServer/commonServer.h>
#include <GFLib/commonServer/tracer.h>
#include <GFLib/commonServer/commonClient.h>
#include <GFLib/commonServer/clientMgr.h>
#include <GFLib/commonServer/message/msgServerLink.h>
#include <GFLib/commonServer/message/msgLocalServer.h>
#include <GFLib/commonServer/message/msgLabel.h>
#include <GFLib/commonServer/serviceMgr.h>

namespace GFLib
{

namespace CommonServer
{

extern BSLib::Utility::CThreadData g_msgQueues;

CCommonClient::CCommonClient(GFLib::SServerID& a_serverID, const std::string& a_serverKey)
: m_isRunning(false)
, m_needReconnect(false)
, m_neetTerminateServer(false)
, m_neetPing(false)
, m_okeyOvertime(6000)
, m_pingCount(0)
{
	IService::_setKey(a_serverKey);
	IService::_setServerID(a_serverID);
	BSLib::Network::CTcpClient::setTcpConnectionMgr(this);
}

CCommonClient::~CCommonClient()
{
	;
}

bool CCommonClient::IService_sendMsg(GFLib::SMessage* msg, BSLib::uint32 msgSize)
{
	if (!m_isRunning) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "发送消息失败[%s][%s]", msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());
		return false;
	}
	if (BSLib::Network::CTcpClient::send(msg, msgSize, true) > 0){
		BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "Client Send MsgID(%d[%s].%d.%d) [%s]", 
			msg->ICommonServer_getServerType(),
			CServerTypeMgr::singleton().getCodeServerType(msg->ICommonServer_getServerType()).c_str(),
			msg->getFunctionType(), 
			msg->getID(),
			BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());
		return true;
	}
	BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "发送消息失败[%s][%s]", msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());
	return false;
}

bool CCommonClient::IService_sendMsg(GFLib::CMessage& msg)
{
	if (!m_isRunning) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "发送消息失败[%s][%s]", msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&msg).c_str());
		return false;
	}
	BSLib::Utility::CStream stream;
	if (!msg.serializeTo(stream)){
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "发送消息失败[%s][%s]", msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&msg).c_str());
		return false;
	}
	if(BSLib::Network::CTcpClient::send(stream, true) > 0) {
		BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "Client Send MsgID(%d[%s].%d.%d) [%s]", 
			msg.ICommonServer_getServerType(),
			CServerTypeMgr::singleton().getCodeServerType(msg.ICommonServer_getServerType()).c_str(),
			msg.getFunctionType(), 
			msg.getID(),
			BSLib::Framework::CMsgDebug::singleton().getPrompt(&msg).c_str());
		return true;
	}
	BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "发送消息失败[%s][%s]", msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&msg).c_str());
	return false;
}

void CCommonClient::IService_close()
{
	terminate();
}

void CCommonClient::start()
{
	m_isRunning = true;
	m_hndThread = BSLib::Utility::CHndThread::createThread(&CCommonClient::_run, this);
	if (!m_hndThread.isValid()) {
		m_isRunning = false;
	}
}

void CCommonClient::join()
{
	m_hndThread.join();
}

bool CCommonClient::isValid()
{
	return m_hndThread.isValid();
}

void CCommonClient::terminate()
{
	m_isRunning = false;
}

void CCommonClient::_initClient()
{
	;
}

void CCommonClient::_notifyServerID()
{
	BSLib::Framework::CMsgExecMgr* msgExecMgr = _getMsgExecMgr();
	if (msgExecMgr != NULL) {
		GFLIB_ADDMSG_OBJEXEC_OBJAFTER(msgExecMgr, MsgIDServerLinkXS2XXResServerID, &CCommonClient::_onMsgServerLinkXS2XXResServerID, &CCommonClient::_afterMsgHandlerCommonClient, this);
	}

	ICommonServer* server = ICommonServer::getCommonServer();
	if (server != NULL) {
		GFLib::SMsgServerLinkXX2XSReqServerID reqServerType;
		reqServerType.m_serverID = server->getServerID();
		reqServerType.setKeyName(server->getServerKey());
		CCommonClient::IService_sendMsg(&reqServerType, sizeof(GFLib::SMsgServerLinkXX2XSReqServerID));
	}
}

void CCommonClient::_finalClient()
{
	;
}

bool CCommonClient::_INetClient_cbParseMsg(void* msgBuff, BSLib::uint32 msgSize)
{
	BSLib::Utility::CRealTime* realTime = m_timerServer.getRealTime();
	m_okeyOvertime.reset(6000, *realTime);
	m_pingCount = 0;

	GFLib::SMessage* msg = (GFLib::SMessage*)msgBuff;
	return IService::_parseMsg(msg, msgSize);
}

void CCommonClient::_INetClient_cbTerminate()
{
	BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "Client %s(%d.%d.%d) Key[%s] Terminate",
		GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(IService::getServerID().ICommonServer_getServerType()).c_str(),
		IService::getServerID().getZoneID(),
		IService::getServerID().ICommonServer_getServerType(),
		IService::getServerID().getServerNumber(),
		IService::getKey().c_str());

	m_isRunning = false;
}

int CCommonClient::_run(void* a_para)
{
	BSLib::Framework::CMsgExecMgr* msgExecMgr = _getMsgExecMgr();
	msgExecMgr->clear();

	bool serverExist = !ICommonServer::getCommonServer()->isTerminate();

	while (serverExist) {
		m_isRunning = true;

		_initClientMsg();

		if (!_connectServer()) {
			BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "Client %s(%d.%d.%d) Key[%s] Thread Over",
				GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(IService::getServerID().ICommonServer_getServerType()).c_str(),
				IService::getServerID().getZoneID(),
				IService::getServerID().ICommonServer_getServerType(),
				IService::getServerID().getServerNumber(),
				IService::getKey().c_str());

			serverExist = !ICommonServer::getCommonServer()->isTerminate();

			continue;
		}

		_initClient();
		_notifyServerID();

		serverExist = !ICommonServer::getCommonServer()->isTerminate();
		while (m_isRunning && serverExist) {
			m_timerServer.update();
			BSLib::Network::CTcpConnectionMgr::INetConnectionMgr_epoll(15);

			serverExist = !ICommonServer::getCommonServer()->isTerminate();

			BSLib::Utility::CRealTime* realTime = m_timerServer.getRealTime();
			if (m_neetPing && serverExist && m_okeyOvertime(*realTime)) {
				m_pingCount ++;
				if (m_pingCount > 3) {
					break;
				}
				GFLib::SMsgServerLinkXS2XXReqPing reqPing;
				CCommonClient::IService_sendMsg(&reqPing, sizeof(GFLib::SMsgServerLinkXS2XXReqPing));
			}
		}
		_finalClient();

		if (CServiceMgr::singleton().delService(getServerID())) {
			ICommonServer* commonServer = ICommonServer::getCommonServer();
			if (commonServer != NULL) {
				SMsgServerLocalLC2LCNtfServerLeave serverLeave;
				serverLeave.m_leaveServerID = IService::getServerID();
				serverLeave.setServerKey(IService::getKey());
				commonServer->sendMsg(&serverLeave, sizeof(serverLeave));

				if (m_neetTerminateServer) {
					commonServer->terminate();
				}
			}
		}

		BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "Client %s(%d.%d.%d) Key[%s] Thread Over",
			GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(IService::getServerID().ICommonServer_getServerType()).c_str(),
			IService::getServerID().getZoneID(),
			IService::getServerID().ICommonServer_getServerType(),
			IService::getServerID().getServerNumber(),
			IService::getKey().c_str());

		BSLib::Network::CTcpClient::INetClient_close();
		BSLib::Network::CTcpConnectionMgr::_checkDelConn();
		BSLib::Network::CTcpConnectionMgr::_clearAllConnection();

		//BSLib::Utility::CThread::msleep(1000);

		if (!m_needReconnect) {
			break;
		}
	}

	CClientMgr::singleton().delCommonClient(IService::getServerID());
	//后面不可以任何操作,对象可能已经释放
	return 0;
}

bool CCommonClient::_connectServer()
{
	bool serverExist = !ICommonServer::getCommonServer()->isTerminate();

	BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "链接服务器[%s:%d] %s(%d.%d.%d) Key[%s] ......", 
		m_connectIP.c_str(), 
		m_connectPort,
		GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(IService::getServerID().ICommonServer_getServerType()).c_str(),
		IService::getServerID().getZoneID(),
		IService::getServerID().ICommonServer_getServerType(),
		IService::getServerID().getServerNumber(),
		IService::getKey().c_str());

	bool isConnect = false;
	while(m_isRunning && serverExist){
		if (BSLib::Network::CTcpClient::INetClient_connect(m_connectIP.c_str(), m_connectPort)) {
			BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "链接服务器[%s:%d] %s(%d.%d.%d) Key[%s] 成功", 
				m_connectIP.c_str(), 
				m_connectPort,
				GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(IService::getServerID().ICommonServer_getServerType()).c_str(),
				IService::getServerID().getZoneID(),
				IService::getServerID().ICommonServer_getServerType(),
				IService::getServerID().getServerNumber(),
				IService::getKey().c_str());

			isConnect = true;
			break;
		}

		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "链接服务器[%s:%d] %s(%d.%d.%d) Key[%s] ......", 
			m_connectIP.c_str(), 
			m_connectPort,
			GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(IService::getServerID().ICommonServer_getServerType()).c_str(),
			IService::getServerID().getZoneID(),
			IService::getServerID().ICommonServer_getServerType(),
			IService::getServerID().getServerNumber(),
			IService::getKey().c_str());

		serverExist = !ICommonServer::getCommonServer()->isTerminate();
	}
	if (isConnect) {
		BSLib::Network::CTcpConnectionMgr::_checkAddConn();
	}

	return isConnect;
}

void CCommonClient::_initClientMsg()
{
	BSLib::Framework::CMsgExecMgr* msgExecMgr = _getMsgExecMgr();

	GFLIB_ADDMSG_OBJEXEC(msgExecMgr, MsgIDServerLinkXS2XXReqPing, &CCommonClient::_onMsgServerLinkXS2XXReqPing, this);
	GFLIB_ADDMSG_OBJEXEC(msgExecMgr, MsgIDServerLinkXX2XSResPing, &CCommonClient::_onMsgServerLinkXX2XSResPing, this);
}

void CCommonClient::_onMsgServerLinkXS2XXReqPing(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg)
{
	GFLib::SMsgServerLinkXX2XSResPing resPing;
	CCommonClient::IService_sendMsg(&resPing, sizeof(GFLib::SMsgServerLinkXX2XSResPing));
}

void CCommonClient::_onMsgServerLinkXX2XSResPing(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg)
{
	;
}

void CCommonClient::_onMsgServerLinkXS2XXResServerID(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg)
{
	GFLib::SMsgServerLinkXS2XXResServerID* resServerType = (GFLib::SMsgServerLinkXS2XXResServerID*)msg;

	if (resServerType->m_serverID == 0) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "Client %s(%d.%d.%d) Key[%s] ServerID不一致",
			GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(IService::getServerID().ICommonServer_getServerType()).c_str(),
			IService::getServerID().getZoneID(),
			IService::getServerID().ICommonServer_getServerType(),
			IService::getServerID().getServerNumber(),
			IService::getKey().c_str());

		terminate();
		return ;
	}
	
	if (resServerType->m_serverID != IService::getServerID()) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "Client %s(%d.%d.%d) Key[%s] ServerID不一致",
			GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(IService::getServerID().ICommonServer_getServerType()).c_str(),
			IService::getServerID().getZoneID(),
			IService::getServerID().ICommonServer_getServerType(),
			IService::getServerID().getServerNumber(),
			IService::getKey().c_str());

		terminate();
		return ;
	}
	if (IService::getKey() != resServerType->m_keyName) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "Client %s(%d.%d.%d) Key[%s] ServerKey不一致",
			GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(IService::getServerID().ICommonServer_getServerType()).c_str(),
			IService::getServerID().getZoneID(),
			IService::getServerID().ICommonServer_getServerType(),
			IService::getServerID().getServerNumber(),
			IService::getKey().c_str());
		terminate();
		return ;
	}

	CCommonClientPtr clientPtr = CClientMgr::singleton().getCommonClient(resServerType->m_serverID);
	IServicePtr servicePtr = (IServicePtr)clientPtr;
	if (servicePtr == NULL) {
		return ;
	}
	CServiceMgr::singleton().addService(servicePtr);

	SMsgServerLocalLC2LCNtfServerEnter serverEnter;
	serverEnter.m_enterServerID = IService::getServerID();
	serverEnter.setServerKey(IService::getKey());
	ICommonServer::getCommonServer()->sendMsg(&serverEnter, sizeof(serverEnter));

	BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "Client %s(%d.%d.%d) Key[%s] OK",
		GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(IService::getServerID().ICommonServer_getServerType()).c_str(),
		IService::getServerID().getZoneID(),
		IService::getServerID().ICommonServer_getServerType(),
		IService::getServerID().getServerNumber(),
		IService::getKey().c_str());
}

void CCommonClient::_afterMsgHandlerCommonClient(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg)
{
	msgExecMgr->delMsgExecPtr(msg->getType(), msg->getID());
}

}//CommonServer

}//GFLib



