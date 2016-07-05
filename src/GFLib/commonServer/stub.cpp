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

IStub::IStub(BSLib::Network::CNetConnectionPtr& netConnection)
: BSLib::Network::INetStub(netConnection)
{
	;
}

IStub::~IStub()
{
	;
}

bool IStub::IService_sendMsg(GFLib::SMessage* msg, BSLib::uint32 msgSize)
{
	if (BSLib::Network::INetStub::send(msg, msgSize) > 0){		
		BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "Stub[%d] Send MsgID(%d[%s].%d.%d) [%s]",
			this->getStubID(),
			msg->ICommonServer_getServerType(),
			CServerTypeMgr::singleton().getCodeServerType(msg->ICommonServer_getServerType()).c_str(),
			msg->getFunctionType(), 
			msg->getID(),
			BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());
		return true;
	}

	BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "Stub[%d]发送消息失败[%s][%s]", this->getStubID(), msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());
	return false;
}

bool IStub::IService_sendMsg(GFLib::CMessage& msg)
{
	BSLib::Utility::CStream stream;
	if (!msg.serializeTo(stream)){
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "Stub[%d]发送消息失败[%s][%s]", this->getStubID(), msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&msg).c_str());
		return false;
	}
	if (BSLib::Network::INetStub::send(stream) > 0){
		BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "Stub[%d] Send MsgID(%d[%s].%d.%d) [%s]", 
			this->getStubID(), 
			msg.ICommonServer_getServerType(),
			CServerTypeMgr::singleton().getCodeServerType(msg.ICommonServer_getServerType()).c_str(),
			msg.getFunctionType(), 
			msg.getID(),
			BSLib::Framework::CMsgDebug::singleton().getPrompt(&msg).c_str());
		return true;
	}
	BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "Stub[%d]发送消息失败[%s][%s]", this->getStubID(), msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&msg).c_str());
	return false;
}

void IStub::IService_close()
{
	BSLib::Network::INetStub::setState(BSLib::Network::ESS_RECYCLE);
}

void IStub::INetStub_initStub()
{
	BSLib::Framework::CMsgExecMgr* msgExecMgr = IService::_getMsgExecMgr();

	GFLIB_ADDMSG_OBJEXEC(msgExecMgr, MsgIDServerLinkXS2XXReqPing, &IStub::_onMsgServerLinkXS2XXReqPing,this);
	GFLIB_ADDMSG_OBJEXEC(msgExecMgr, MsgIDServerLinkXX2XSResPing, &IStub::_onMsgServerLinkXX2XSResPing,this);

	IStub_initStubMsg(msgExecMgr);
}

void IStub::INetStub_finalStub()
{
	;
}

void IStub::IStub_initStubMsg(BSLib::Framework::CMsgExecMgr* msgExecMgr)
{
	GFLIB_ADDMSG_OBJEXEC_OBJAFTER(msgExecMgr, MsgIDServerLinkXX2XSReqServerID, &IStub::_onMsgServerLinkXX2XSReqServerType, &IStub::_afterMsgHandlerStub, this);
}

void IStub::INetStub_cbNotifyPing()
{
	SMsgServerLinkXS2XXReqPing reqPing;
	BSLib::Network::INetStub::send(&reqPing, sizeof(reqPing));
}

bool IStub::INetStub_cbParseMsg(void* msgBuff, BSLib::uint32 msgSize)
{
	GFLib::SMessage* msg = (GFLib::SMessage*)msgBuff;

	return IService::_parseMsg(msg, msgSize);
}

void IStub::INetStub_cbTerminate()
{
	if (CServiceMgr::singleton().delService(IService::getServerID())) {
		ICommonServer* commonServer = ICommonServer::getCommonServer();
		if (commonServer == NULL) {
			return ;
		}
		SMsgServerLocalLC2LCNtfServerLeave serverLeave;
		serverLeave.m_leaveServerID = IService::getServerID();
		serverLeave.setServerKey(IService::getKey());

		commonServer->sendMsg(&serverLeave, sizeof(serverLeave));
	}

	BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "Stub[%d] %s(%d.%d.%d) Key[%s] Terminate",
		this->getStubID(),
		GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(IService::getServerID().getServerType()).c_str(),
		IService::getServerID().getZoneID(),
		IService::getServerID().getServerType(),
		IService::getServerID().getServerNumber(),
		IService::getKey().c_str());
}

bool IStub::_IService_canTransfer() 
{ 
	BSLib::Network::EStubState stubState = BSLib::Network::INetStub::getState();
	return stubState == BSLib::Network::ESS_OKAY || stubState == BSLib::Network::ESS_RECYCLE;
}

GFLib::StubID IStub::_IService_getStubID()
{
	return BSLib::Network::INetStub::getStubID();
}

void IStub::_onMsgServerLinkXS2XXReqPing(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
{
	GFLib::SMsgServerLinkXX2XSResPing resPing;
	BSLib::Network::INetStub::send(&resPing, sizeof(GFLib::SMsgServerLinkXX2XSResPing));
}

void IStub::_onMsgServerLinkXX2XSResPing(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
{
	BSLib::Network::INetStub::_resetOkeyTick();
}

void IStub::_onMsgServerLinkXX2XSReqServerType(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
{
	GFLib::SMsgServerLinkXX2XSReqServerID* reqServerType = (GFLib::SMsgServerLinkXX2XSReqServerID*)msg;

	if (reqServerType->m_serverID == 0) {
		return;
	}
	IService::_setServerID(reqServerType->m_serverID.getServerID());
	IService::_setKey(reqServerType->m_key);

	ICommonServer* server = ICommonServer::getCommonServer();
	GFLib::SMsgServerLinkXS2XXResServerID resServerType;
	resServerType.m_serverID = server->getServerID();
	resServerType.setKey(server->getServerKey());

	if (!IService_sendMsg(&resServerType, sizeof(GFLib::SMsgServerLinkXS2XXResServerID))) {
		return ;
	}
	
	CStubPtr stubPtr = CStubMgr::singleton().getCommonStubByStubID(getStubID());
	IServicePtr servicePtr = (IServicePtr)stubPtr;
	if (servicePtr == NULL) {
		return;
	}

	if (!CServiceMgr::singleton().addService(servicePtr)) {
		BSLib::Network::INetStub::setState(BSLib::Network::ESS_RECYCLE);
		return;
	}

	BSLib::Network::INetStub::setState(BSLib::Network::ESS_OKAY);
	
	SMsgServerLocalLC2LCNtfServerEnter serverEnter;
	serverEnter.m_enterServerID = IService::getServerID();
	serverEnter.setServerKey(IService::getKey());
	ICommonServer::getCommonServer()->sendMsg(&serverEnter, sizeof(serverEnter));

	BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "Stub[%d] %s(%d.%d.%d) Key[%s] OK",
		this->getStubID(),
		GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(IService::getServerID().getServerType()).c_str(),
		IService::getServerID().getZoneID(),
		IService::getServerID().getServerType(),
		IService::getServerID().getServerNumber(),
		IService::getKey().c_str());
}

void IStub::_afterMsgHandlerStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg)
{
	msgExecMgr->delMsgExecPtr(msg->getType(), msg->getID());
}

}//CommonServer

}//GFLib



