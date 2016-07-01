#include <GFLib/commonServer/accountMgr.h>
#include <GSLib/loginSystem/msgLoginSystem.h>
#include <GSLib/loginSystem/GT/loginSystemGT.h>
#include "gateStub.h"

CGateStub::CGateStub(BSLib::Network::CNetConnectionPtr& netConnection)
: GFLib::CommonServer::IStub(netConnection)
, m_gateKey(0)
, m_gateSession(0)
, m_isValidAccountID(false)
{
	;
}

void CGateStub::INetStub_finalStub()
{
	;
}

void CGateStub::IStub_initStubMsg(BSLib::Framework::CMsgExecMgr* msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(GSLib::LoginSystem::MsgIDLoginSystemGC2GTReqAccountLogin, &BSLib::Framework::CreateCMessage<GSLib::LoginSystem::CMsgLoginSystemGC2GTReqAccountLogin>);
	GFLIB_ADDMSG_OBJEXEC_OBJAFTER(msgExecMgr, GSLib::LoginSystem::MsgIDLoginSystemGC2GTReqAccountLogin, &CGateStub::_onMsgLoginSystemGC2GTReqAccountLogin, &CGateStub::_afterMsgHandlerGameStub, this);
}

void CGateStub::INetStub_cbTerminate()
{
	if (m_isValidAccountID) {
		GSLib::LoginSystem::GT::CLoginSystemGT::singleton().terminateAccountLogin(m_accountKey, m_gateKey, m_gateSession, getStubID());
		m_isValidAccountID = false;
	}
}

bool CGateStub::_transferMsg(GFLib::SMessage* msg, BSLib::uint32 a_msgSize)
{
	if (!m_isValidAccountID) {
		return false;
	}

	GFLib::CommonServer::CAccountPtr accountPtr = GFLib::CommonServer::CAccountMgr::singleton().getAccount(m_accountKey);
	if (accountPtr == NULL) {
		return false;
	}
	GFLib::ServerType msgType = msg->ICommonServer_getServerType();
	switch(msgType)
	{
	case GSLib::SRVTYPE_DATASERVER:
		{
			if (!m_dbServerID.isValid()) {
				return false;
			}
			return accountPtr->sendMsgToServer(m_dbServerID, msg, a_msgSize);
		}
		break;
	case GSLib::SRVTYPE_CENTERSERVER:
		{
			if (!m_dbServerID.isValid()) {
				return false;
			}
			return accountPtr->sendMsgToServer(m_centerServerID, msg, a_msgSize);
		}
		break;
	case GSLib::SRVTYPE_GAMESERVER:
		{
			if (!m_dbServerID.isValid()) {
				return false;
			}
			return accountPtr->sendMsgToServer(m_gameServerID, msg, a_msgSize);
		}
		break;
	default:
		{
			;
		}
	}
	return false;
}

void CGateStub::_cbVerifyAccountLogin(GFLib::SServerID& a_gameServerID, GFLib::SServerID& a_dbServerID, GFLib::SServerID& a_centerServerID)
{
	m_centerServerID = a_centerServerID;
	m_dbServerID = a_dbServerID;
	m_gameServerID = a_gameServerID;
}

void CGateStub::_onMsgLoginSystemGC2GTReqAccountLogin(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GSLib::LoginSystem::CMsgLoginSystemGC2GTReqAccountLogin* reqAccountLogin = (GSLib::LoginSystem::CMsgLoginSystemGC2GTReqAccountLogin*)a_msg;

	BSLib::Network::CNetConnectionPtr netConnectionPtr = getNetConnectionPtr();
	if (netConnectionPtr == NULL) {
		return ;
	}
	m_accountKey = reqAccountLogin->m_accountKey;
	m_gateKey = reqAccountLogin->m_gateKey;
	m_gateSession = reqAccountLogin->m_gateSession;
	
	std::string gateLoginIP = netConnectionPtr->getPeerAddr().getIP();

	GFLib::CommonServer::IStub::setState(BSLib::Network::ESS_OKAY);
	
	GSLib::LoginSystem::CMsgLoginSystemGT2GCAckAccountLogin ackAccountLogin;
	if (!GSLib::LoginSystem::GT::CLoginSystemGT::singleton().verifyAccountLogin(getStubID(), gateLoginIP, *reqAccountLogin, ackAccountLogin,this)) {
		GFLib::CommonServer::IStub::IService_sendMsg(ackAccountLogin);
		GFLib::CommonServer::IStub::setState(BSLib::Network::ESS_RECYCLE);
		return ;
	}
	m_isValidAccountID = true;
}

void CGateStub::_afterMsgHandlerGameStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg)
{
	msgExecMgr->delMsgExecPtr(msg->getType(), msg->getID());
}

