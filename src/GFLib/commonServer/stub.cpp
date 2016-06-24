#include <BSLib/framework/message/msgDebug.h>
#include <GFLib/commonServer/message/msgServerLink.h>
#include <GFLib/commonServer/message/msgLocalServer.h>
#include <GFLib/commonServer/commonServer.h>
#include <GFLib/commonServer/stub.h>
#include <GFLib/commonServer/tracer.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/stubMgr.h>

namespace GFLib
{

namespace CommonServer
{

CStub::CStub(BSLib::Network::CNetConnectionPtr& netConnection)
: BSLib::Network::CNetStub(netConnection)
{
	;
}

CStub::~CStub()
{
	;
}

bool CStub::sendMsg(GFLib::SMessage* msg, BSLib::uint32 msgSize)
{
	if (BSLib::Network::CNetStub::send(msg, msgSize) > 0){		
		BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "Stub[%d] Send MsgID(%d[%s].%d.%d) [%s]",
			this->getStubID(),
			msg->getServerType(),
			CServerTypeMgr::singleton().getCodeServerType(msg->getServerType()).c_str(),
			msg->getFunctionType(), 
			msg->getID(),
			BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());
		return true;
	}

	BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "Stub[%d]发送消息失败[%s][%s]", this->getStubID(), msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());
	return false;
}

bool CStub::sendMsg(GFLib::CMessage& msg)
{
	BSLib::Utility::CStream stream;
	if (!msg.serializeTo(stream)){
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "Stub[%d]发送消息失败[%s][%s]", this->getStubID(), msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&msg).c_str());
		return false;
	}
	if (BSLib::Network::CNetStub::send(stream) > 0){
		BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "Stub[%d] Send MsgID(%d[%s].%d.%d) [%s]", 
			this->getStubID(), 
			msg.getServerType(),
			CServerTypeMgr::singleton().getCodeServerType(msg.getServerType()).c_str(),
			msg.getFunctionType(), 
			msg.getID(),
			BSLib::Framework::CMsgDebug::singleton().getPrompt(&msg).c_str());
		return true;
	}
	BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "Stub[%d]发送消息失败[%s][%s]", this->getStubID(), msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&msg).c_str());
	return false;
}

void CStub::close()
{
	BSLib::Network::CNetStub::setState(BSLib::Network::ESS_RECYCLE);
}

void CStub::_initStub()
{
	BSLib::Framework::CMsgExecMgr* msgExecMgr = CService::_getMsgExecMgr();

	GFLIB_ADDMSG_OBJEXEC(msgExecMgr, MsgIDServerLinkXS2XXReqPing, &CStub::_onMsgServerLinkXS2XXReqPing,this);
	GFLIB_ADDMSG_OBJEXEC(msgExecMgr, MsgIDServerLinkXX2XSResPing, &CStub::_onMsgServerLinkXX2XSResPing,this);

	_initStubMsg(msgExecMgr);
}

void CStub::_finalStub()
{
	;
}

void CStub::_initStubMsg(BSLib::Framework::CMsgExecMgr* msgExecMgr)
{
	GFLIB_ADDMSG_OBJEXEC_OBJAFTER(msgExecMgr, MsgIDServerLinkXX2XSReqServerID, &CStub::_onMsgServerLinkXX2XSReqServerType, &CStub::_afterMsgHandlerStub, this);
}

void CStub::_cbNotifyPing()
{
	SMsgServerLinkXS2XXReqPing reqPing;
	BSLib::Network::CNetStub::send(&reqPing, sizeof(reqPing));
}

bool CStub::_cbParseMsg(void* msgBuff, BSLib::uint32 msgSize)
{
	GFLib::SMessage* msg = (GFLib::SMessage*)msgBuff;

	return CService::_parseMsg(msg, msgSize);
}

void CStub::_cbTerminate()
{
	if (CServiceMgr::singleton().delService(CService::getServerID())) {
		CCommonServer* commonServer = CCommonServer::getCommonServer();
		if (commonServer == NULL) {
			return ;
		}
		SMsgServerLocalLC2LCNtfServerLeave serverLeave;
		serverLeave.m_leaveServerID = CService::getServerID();
		serverLeave.setServerKey(CService::getKey());

		commonServer->sendMsg(&serverLeave, sizeof(serverLeave));
	}

	BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "Stub[%d] %s(%d.%d.%d) Key[%s] Terminate",
		this->getStubID(),
		GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(CService::getServerID().getServerType()).c_str(),
		CService::getServerID().getZoneID(),
		CService::getServerID().getServerType(),
		CService::getServerID().getServerNumber(),
		CService::getKey().c_str());
}

bool CStub::_canTransfer() 
{ 
	BSLib::Network::EStubState stubState = BSLib::Network::CNetStub::getState();
	return stubState == BSLib::Network::ESS_OKAY || stubState == BSLib::Network::ESS_RECYCLE;
}

GFLib::StubID CStub::_getStubID()
{
	return BSLib::Network::CNetStub::getStubID();
}

void CStub::_onMsgServerLinkXS2XXReqPing(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
{
	GFLib::SMsgServerLinkXX2XSResPing resPing;
	BSLib::Network::CNetStub::send(&resPing, sizeof(GFLib::SMsgServerLinkXX2XSResPing));
}

void CStub::_onMsgServerLinkXX2XSResPing(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
{
	BSLib::Network::CNetStub::_resetOkeyTick();
}

void CStub::_onMsgServerLinkXX2XSReqServerType(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
{
	GFLib::SMsgServerLinkXX2XSReqServerID* reqServerType = (GFLib::SMsgServerLinkXX2XSReqServerID*)msg;

	if (reqServerType->m_serverID == 0) {
		return;
	}
	CService::_setServerID(reqServerType->m_serverID.getServerID());
	CService::_setKey(reqServerType->m_key);

	CCommonServer* server = CCommonServer::getCommonServer();
	GFLib::SMsgServerLinkXS2XXResServerID resServerType;
	resServerType.m_serverID = server->getServerID();
	resServerType.setKey(server->getServerKey());

	if (!sendMsg(&resServerType, sizeof(GFLib::SMsgServerLinkXS2XXResServerID))) {
		return ;
	}
	
	CStubPtr stubPtr = CStubMgr::singleton().getCommonStubByStubID(getStubID());
	CServicePtr servicePtr = (CServicePtr)stubPtr;
	if (servicePtr == NULL) {
		return;
	}

	if (!CServiceMgr::singleton().addService(servicePtr)) {
		BSLib::Network::CNetStub::setState(BSLib::Network::ESS_RECYCLE);
		return;
	}

	BSLib::Network::CNetStub::setState(BSLib::Network::ESS_OKAY);
	
	SMsgServerLocalLC2LCNtfServerEnter serverEnter;
	serverEnter.m_enterServerID = CService::getServerID();
	serverEnter.setServerKey(CService::getKey());
	CCommonServer::getCommonServer()->sendMsg(&serverEnter, sizeof(serverEnter));

	BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "Stub[%d] %s(%d.%d.%d) Key[%s] OK",
		this->getStubID(),
		GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(CService::getServerID().getServerType()).c_str(),
		CService::getServerID().getZoneID(),
		CService::getServerID().getServerType(),
		CService::getServerID().getServerNumber(),
		CService::getKey().c_str());
}

void CStub::_afterMsgHandlerStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg)
{
	msgExecMgr->delMsgExecPtr(msg->getType(), msg->getID());
}

}//CommonServer

}//GFLib



