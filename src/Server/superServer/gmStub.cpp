//////////////////////////////////////////////////////////////////////
//	created:	2014/12/10
//	filename: 	src\Server\superServer\superStub.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/loginSystem/msgLoginSystem.h>
#include <GSLib/loginSystem/LG/loginSystemLG.h>
#include "gmStub.h"
#include "superServer.h"
#include "common/tracer.h"
#include <GSLib/masterSystem/gm.proto.h>

#define TIMEOUT_MAX_ACCOUNT_LOGIN (30 * 1000)

CGMStub::CGMStub(BSLib::Network::CNetConnectionPtr& netConnection)
: GFLib::CommonServer::CStub(netConnection)
, m_timeHandleAccountLogin(BSLib::Utility::INVALID_TIMER)
{
	;
}

void CGMStub::_finalStub()
{
	;
}

void CGMStub::_initStubMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
// 	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(GSLib::LoginSystem::MsgIDLoginSystemGC2LGReqAccountLogin, &BSLib::Framework::CreateCMessage<GSLib::LoginSystem::CMsgLoginSystemGC2LGReqAccountLogin>);
// 	GFLIB_ADDMSG_OBJEXEC_OBJAFTER(msgExecMgr, GSLib::LoginSystem::MsgIDLoginSystemGC2LGReqAccountLogin, &CLoginStub::_onMsgLoginSystemGC2LGReqAccountLogin, &CLoginStub::_afterMsgHandlerLoginStub, this);
// 
// 	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(GSLib::LoginSystem::MsgIDLoginSystemGC2LGReqRegisterAccount, &BSLib::Framework::CreateCMessage<GSLib::LoginSystem::CMsgLoginSystemGC2LGReqRegisterAccount>);
// 	GFLIB_ADDMSG_OBJEXEC_OBJAFTER(msgExecMgr, GSLib::LoginSystem::MsgIDLoginSystemGC2LGReqRegisterAccount, &CLoginStub::_onMsgLoginSystemGC2LGReqRegisterAccount, &CLoginStub::_afterMsgHandlerRegisterStub, this);
	
	using namespace GSLib::MasterSystem;
	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqLogin, CGMStub);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqOnlineZone, CGMStub);
}

void CGMStub::_cbTerminate()
{
// 	if (m_timeHandleAccountLogin != BSLib::Utility::INVALID_TIMER) {
// 		BSLib::Utility::CTimerServer* timerServer = GFLib::CommonServer::CStub::_getTimerServer();
// 		if (timerServer == NULL) {
// 			return;
// 		}
// 		timerServer->delTimer(m_timeHandleAccountLogin);
// 		m_timeHandleAccountLogin = BSLib::Utility::INVALID_TIMER;
// 		
// 		GSLib::LoginSystem::LG::CLoginSystemLG::singleton().removeAccountLogin(getStubID());
// 	}
	
}

// void CGMStub::_onMsgLoginSystemGC2LGReqAccountLogin(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
// {
// 	GSLib::LoginSystem::CMsgLoginSystemGC2LGReqAccountLogin* reqAccountLogin = (GSLib::LoginSystem::CMsgLoginSystemGC2LGReqAccountLogin*)msg;
// 	
// 	BSLIB_LOG_INFOR(Server::ETT_SERVER_COMMON, "�����½[AccountName=%s][Zone=%d][Channel=%d]"
// 		, reqAccountLogin->m_accountName.c_str()
// 		, reqAccountLogin->m_zoneID
// 		, reqAccountLogin->m_channelID);
// 
// 	BSLib::Network::CNetConnectionPtr netConnectionPtr = getNetConnectionPtr();
// 	if (netConnectionPtr == NULL) {
// 		return ;
// 	}
// 	std::string accountLoginIP = netConnectionPtr->getPeerAddr().getIP();
// 
// 	m_accountName = reqAccountLogin->m_accountName;
// 	m_zoneID = reqAccountLogin->m_zoneID;
// 
// 	
// 	GSLib::LoginSystem::CMsgLoginSystemLG2GCAckAccountLogin ackAccountLogin;
// 	if (!GSLib::LoginSystem::LG::CLoginSystemLG::singleton().verifyAccountLogin(getStubID(), accountLoginIP, *reqAccountLogin, ackAccountLogin)){
// 		GFLib::CommonServer::CStub::sendMsg(ackAccountLogin);
// 		return ;
// 	}
// 
// 	BSLib::Utility::CTimerServer* timerServer = GFLib::CommonServer::CStub::_getTimerServer();
// 	if (timerServer == NULL) {
// 		GSLib::LoginSystem::LG::CLoginSystemLG::singleton().removeAccountLogin(getStubID());
// 		_notifyAccountLoginResult(GSLib::LoginSystem::ELOGINRESULT_SERVER_ERROR);
// 
// 		BSLIB_LOG_ERROR(Server::ETT_SERVER_COMMON, "��ȡ��ʱ��ʧ��[AccountName=%s][Zone=%d]"
// 			, m_accountName.c_str()
// 			, m_zoneID);
// 
// 		return;
// 	}
// 
// 	m_timeHandleAccountLogin = timerServer->addTimer(&CLoginStub::_cbTimerAccountLogin, this, 0, NULL, TIMEOUT_MAX_ACCOUNT_LOGIN, TIMEOUT_MAX_ACCOUNT_LOGIN, 1);
// 	if (m_timeHandleAccountLogin == BSLib::Utility::INVALID_TIMER) {
// 		GSLib::LoginSystem::LG::CLoginSystemLG::singleton().removeAccountLogin(getStubID());
// 		_notifyAccountLoginResult(GSLib::LoginSystem::ELOGINRESULT_SERVER_ERROR);
// 
// 		BSLIB_LOG_ERROR(Server::ETT_SERVER_COMMON, "��ȡ��ʱ��ʧ��[AccountName=%s][Zone=%d]"
// 			, m_accountName.c_str()
// 			, m_zoneID);
// 
// 		return;
// 	}
// 
// 	GFLib::CommonServer::CStub::setState(BSLib::Network::ESS_OKAY);
// }
// 
// void CGMStub::_onMsgLoginSystemGC2LGReqRegisterAccount(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
// {
// 	GSLib::LoginSystem::CMsgLoginSystemGC2LGReqRegisterAccount* reqAccountLogin = (GSLib::LoginSystem::CMsgLoginSystemGC2LGReqRegisterAccount*)msg;
// 
// 	BSLIB_LOG_INFOR(Server::ETT_SERVER_COMMON, "����ע��[AccountName=%s][Zone=%d][Channel=%d]"
// 		, reqAccountLogin->m_accountName.c_str()
// 		, reqAccountLogin->m_zoneID
// 		, reqAccountLogin->m_channelID);
// 
// 	BSLib::Network::CNetConnectionPtr netConnectionPtr = getNetConnectionPtr();
// 	if (netConnectionPtr == NULL) {
// 		return ;
// 	}
// 	std::string accountLoginIP = netConnectionPtr->getPeerAddr().getIP();
// 
// 	GSLib::LoginSystem::CMsgLoginSystemLG2GCAckRegisterAccount ackAccountLogin;
// 	GSLib::LoginSystem::LG::CLoginSystemLG::singleton().registerAccount(getStubID(), accountLoginIP, *reqAccountLogin, ackAccountLogin);
// 	GFLib::CommonServer::CStub::sendMsg(ackAccountLogin);
// 	return;
// }
// 
// void CGMStub::_afterMsgHandlerLoginStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg)
// {
// 	msgExecMgr->delMsgExecPtr(msg->getType(), msg->getID());
// }
// 
// void CGMStub::_afterMsgHandlerRegisterStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg)
// {
// 	msgExecMgr->delMsgExecPtr(msg->getType(), msg->getID());
// }
// 
// bool CGMStub::_cbTimerAccountLogin(BSLib::uint64, void* a_para)
// {
// 	if (GSLib::LoginSystem::LG::CLoginSystemLG::singleton().isValidAccountLogin(getStubID())) {
// 		GSLib::LoginSystem::LG::CLoginSystemLG::singleton().removeAccountLogin(getStubID());
// 		_notifyAccountLoginResult(GSLib::LoginSystem::ELOGINRESULT_SERVER_ERROR);
// 
// 		BSLIB_LOG_ERROR(Server::ETT_SERVER_COMMON, "�˺�����ʱ[AccountName=%s][Zone=%d]"
// 			, m_accountName.c_str()
// 			, m_zoneID);
// 
// 	}
// 	m_timeHandleAccountLogin = BSLib::Utility::INVALID_TIMER;
// 	GFLib::CommonServer::CStub::setState(BSLib::Network::ESS_RECYCLE);
// 	return false;
// }
// 
// void CGMStub::_notifyAccountLoginResult(GSLib::LoginSystem::ELoginResult result)
// {
// 	GSLib::LoginSystem::CMsgLoginSystemLG2GCAckAccountLogin ackAccountLogin;
// 	ackAccountLogin.m_state = result;
// 	GFLib::CommonServer::CStub::sendMsg(ackAccountLogin);
// }

void CGMStub::_onCMsgMasterSystemXX2XSReqLogin(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
{	
	GSLib::MasterSystem::CMsgMasterSystemXS2XXAckLogin ack;
	sendMsg(ack);
	
	GFLib::CommonServer::CStub::setState(BSLib::Network::ESS_OKAY);
}

void CGMStub::_onCMsgMasterSystemXX2XSReqOnlineZone(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
{	
	GSLib::MasterSystem::CMsgMasterSystemXS2XXAckOnlineZone ack;
	std::map<std::string, GFLib::SServerID>::iterator it = CSuperServer::singleton().m_cnServers.begin();
	for(; it != CSuperServer::singleton().m_cnServers.end(); ++it)
	{
		ack.keys.push_back(it->first);
	}
	sendMsg(ack);
}

