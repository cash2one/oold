
#include <GSLib/loginSystem/msgLoginSystem.h>
#include <GSLib/loginSystem/LG/loginSystemLG.h>
#include "loginStub.h"
#include "loginServer.h"
#include "common/tracer.h"

#define TIMEOUT_MAX_ACCOUNT_LOGIN (30 * 1000)

CLoginStub::CLoginStub(BSLib::Network::CNetConnectionPtr& netConnection)
: GFLib::CommonServer::CStub(netConnection)
, m_timeHandleAccountLogin(BSLib::Utility::INVALID_TIMER)
{
	;
}

void CLoginStub::INetStub_finalStub()
{
	;
}

void CLoginStub::INetStub_initStubMsg(BSLib::Framework::CMsgExecMgr* msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(GSLib::LoginSystem::MsgIDLoginSystemGC2LGReqAccountLogin, &BSLib::Framework::CreateCMessage<GSLib::LoginSystem::CMsgLoginSystemGC2LGReqAccountLogin>);
	GFLIB_ADDMSG_OBJEXEC_OBJAFTER(msgExecMgr, GSLib::LoginSystem::MsgIDLoginSystemGC2LGReqAccountLogin, &CLoginStub::_onMsgLoginSystemGC2LGReqAccountLogin, &CLoginStub::_afterMsgHandlerLoginStub, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(GSLib::LoginSystem::MsgIDLoginSystemGC2LGReqRegisterAccount, &BSLib::Framework::CreateCMessage<GSLib::LoginSystem::CMsgLoginSystemGC2LGReqRegisterAccount>);
	GFLIB_ADDMSG_OBJEXEC_OBJAFTER(msgExecMgr, GSLib::LoginSystem::MsgIDLoginSystemGC2LGReqRegisterAccount, &CLoginStub::_onMsgLoginSystemGC2LGReqRegisterAccount, &CLoginStub::_afterMsgHandlerRegisterStub, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(GSLib::LoginSystem::MsgIDLoginSystemGC2LGReqGetAccountToken, &BSLib::Framework::CreateCMessage<GSLib::LoginSystem::CMsgLoginSystemGC2LGReqGetAccountToken>);
    GFLIB_ADDMSG_OBJEXEC_OBJAFTER(msgExecMgr, GSLib::LoginSystem::MsgIDLoginSystemGC2LGReqGetAccountToken, &CLoginStub::_onMsgLoginSystemGC2LGReqGetAccountToken, &CLoginStub::_afterMsgHandlerGetAccountTokenStub, this);
}

void CLoginStub::INetStub_cbTerminate()
{
	if (m_timeHandleAccountLogin != BSLib::Utility::INVALID_TIMER) {
		BSLib::Utility::CTimerServer* timerServer = GFLib::CommonServer::CStub::_getTimerServer();
		if (timerServer == NULL) {
			return;
		}
		timerServer->delTimer(m_timeHandleAccountLogin);
		m_timeHandleAccountLogin = BSLib::Utility::INVALID_TIMER;
		
		GSLib::LoginSystem::LG::CLoginSystemLG::singleton().removeAccountLogin(getStubID());
	}
	
}

void CLoginStub::_onMsgLoginSystemGC2LGReqAccountLogin(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
{
	GSLib::LoginSystem::CMsgLoginSystemGC2LGReqAccountLogin* reqAccountLogin = (GSLib::LoginSystem::CMsgLoginSystemGC2LGReqAccountLogin*)msg;
	
	BSLIB_LOG_INFO(Server::ETT_SERVER_COMMON, "请求登陆[AccountName=%s][Zone=%d][Channel=%d]"
		, reqAccountLogin->m_accountName.c_str()
		, reqAccountLogin->m_zoneID
		, reqAccountLogin->m_channelID);

	BSLib::Network::CNetConnectionPtr netConnectionPtr = getNetConnectionPtr();
	if (netConnectionPtr == NULL) {
		return ;
	}
	std::string accountLoginIP = netConnectionPtr->getPeerAddr().getIP();

	m_accountName = reqAccountLogin->m_accountName;
	m_zoneID = reqAccountLogin->m_zoneID;

	
	GSLib::LoginSystem::CMsgLoginSystemLG2GCAckAccountLogin ackAccountLogin;
	if (!GSLib::LoginSystem::LG::CLoginSystemLG::singleton().verifyAccountLogin(getStubID(), accountLoginIP, *reqAccountLogin, ackAccountLogin)){
		GFLib::CommonServer::CStub::IService_sendMsg(ackAccountLogin);
		return ;
	}

	BSLib::Utility::CTimerServer* timerServer = GFLib::CommonServer::CStub::_getTimerServer();
	if (timerServer == NULL) {
		GSLib::LoginSystem::LG::CLoginSystemLG::singleton().removeAccountLogin(getStubID());
		_notifyAccountLoginResult(GSLib::LoginSystem::ELOGINRESULT_SERVER_ERROR);

		BSLIB_LOG_ERROR(Server::ETT_SERVER_COMMON, "获取定时器失败[AccountName=%s][Zone=%d]"
			, m_accountName.c_str()
			, m_zoneID);

		return;
	}

	m_timeHandleAccountLogin = timerServer->addTimer(&CLoginStub::_cbTimerAccountLogin, this, 0, NULL, TIMEOUT_MAX_ACCOUNT_LOGIN, TIMEOUT_MAX_ACCOUNT_LOGIN, 1);
	if (m_timeHandleAccountLogin == BSLib::Utility::INVALID_TIMER) {
		GSLib::LoginSystem::LG::CLoginSystemLG::singleton().removeAccountLogin(getStubID());
		_notifyAccountLoginResult(GSLib::LoginSystem::ELOGINRESULT_SERVER_ERROR);

		BSLIB_LOG_ERROR(Server::ETT_SERVER_COMMON, "获取定时器失败[AccountName=%s][Zone=%d]"
			, m_accountName.c_str()
			, m_zoneID);

		return;
	}

	GFLib::CommonServer::CStub::setState(BSLib::Network::ESS_OKAY);
}

void CLoginStub::_onMsgLoginSystemGC2LGReqRegisterAccount(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
{
	GSLib::LoginSystem::CMsgLoginSystemGC2LGReqRegisterAccount* reqAccountLogin = (GSLib::LoginSystem::CMsgLoginSystemGC2LGReqRegisterAccount*)msg;

	BSLIB_LOG_INFO(Server::ETT_SERVER_COMMON, "请求注册[AccountName=%s][Channel=%d]"
		, reqAccountLogin->m_accountName.c_str()
		, reqAccountLogin->m_channelID);

	BSLib::Network::CNetConnectionPtr netConnectionPtr = getNetConnectionPtr();
	if (netConnectionPtr == NULL) {
		return ;
	}
	std::string accountLoginIP = netConnectionPtr->getPeerAddr().getIP();

	GSLib::LoginSystem::CMsgLoginSystemLG2GCAckRegisterAccount ackAccountLogin;
	GSLib::LoginSystem::LG::CLoginSystemLG::singleton().registerAccount(getStubID(), accountLoginIP, *reqAccountLogin, ackAccountLogin);
	GFLib::CommonServer::CStub::IService_sendMsg(ackAccountLogin);
	return;
}


void CLoginStub::_onMsgLoginSystemGC2LGReqGetAccountToken(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
{
    GSLib::LoginSystem::CMsgLoginSystemGC2LGReqGetAccountToken* reqAccountLogin = (GSLib::LoginSystem::CMsgLoginSystemGC2LGReqGetAccountToken*)msg;

    BSLIB_LOG_INFO(Server::ETT_SERVER_COMMON, "请求登陆[AccountName=%s][Channel=%d]"
        , reqAccountLogin->m_accountName.c_str()
        , reqAccountLogin->m_channelID);

    BSLib::Network::CNetConnectionPtr netConnectionPtr = getNetConnectionPtr();
    if (netConnectionPtr == NULL) {
        return ;
    }
    std::string accountLoginIP = netConnectionPtr->getPeerAddr().getIP();
    m_accountName = reqAccountLogin->m_accountName;

    GSLib::LoginSystem::CMsgLoginSystemLG2GCAckGetAccountToken ackAccountLogin;
    if (!GSLib::LoginSystem::LG::CLoginSystemLG::singleton().verifyGetAccountToken(getStubID(), accountLoginIP, *reqAccountLogin, ackAccountLogin)){
        GFLib::CommonServer::CStub::IService_sendMsg(ackAccountLogin);
        return ;
    }
}

void CLoginStub::_afterMsgHandlerLoginStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg)
{
	msgExecMgr->delMsgExecPtr(msg->getType(), msg->getID());
}

void CLoginStub::_afterMsgHandlerRegisterStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg)
{
	msgExecMgr->delMsgExecPtr(msg->getType(), msg->getID());
}

void CLoginStub::_afterMsgHandlerGetAccountTokenStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg)
{
    msgExecMgr->delMsgExecPtr(msg->getType(), msg->getID());
}


bool CLoginStub::_cbTimerAccountLogin(BSLib::uint64, void* a_para)
{
	if (GSLib::LoginSystem::LG::CLoginSystemLG::singleton().isValidAccountLogin(getStubID())) {
		GSLib::LoginSystem::LG::CLoginSystemLG::singleton().removeAccountLogin(getStubID());
		_notifyAccountLoginResult(GSLib::LoginSystem::ELOGINRESULT_SERVER_ERROR);

		BSLIB_LOG_ERROR(Server::ETT_SERVER_COMMON, "账号请求超时[AccountName=%s][Zone=%d]"
			, m_accountName.c_str()
			, m_zoneID);

	}
	m_timeHandleAccountLogin = BSLib::Utility::INVALID_TIMER;
	GFLib::CommonServer::CStub::setState(BSLib::Network::ESS_RECYCLE);
	return false;
}

void CLoginStub::_notifyAccountLoginResult(GSLib::LoginSystem::ELoginResult result)
{
	GSLib::LoginSystem::CMsgLoginSystemLG2GCAckAccountLogin ackAccountLogin;
	ackAccountLogin.m_state = result;
	GFLib::CommonServer::CStub::IService_sendMsg(ackAccountLogin);
}


void CLoginStub::_notifyGetAccountTokenResult(GSLib::LoginSystem::EGetAccountTokenResult result)
{
    GSLib::LoginSystem::CMsgLoginSystemLG2GCAckGetAccountToken ackAccountLogin;
    ackAccountLogin.m_state = result;
    GFLib::CommonServer::CStub::IService_sendMsg(ackAccountLogin);
}


