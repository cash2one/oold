#include <GFLib/commonServer/stubMgr.h>
#include <GSLib/tracer.h>
#include <GSLib/loginSystem/msgLoginSystem.h>
#include "LG/accountLoginLGInforMgr.h"
#include "LG/zoneInforMgr.h"


namespace GSLib
{

namespace LoginSystem
{

namespace LG
{

CAccountLoginLGInforMgr::CAccountLoginLGInforMgr()
{
	m_sessionAllocator.setUniqueIDMgr(this);
}

CAccountLoginLGInforMgr::~CAccountLoginLGInforMgr()
{
	;
}

BSLIB_SINGLETON_DEFINE(CAccountLoginLGInforMgr);

bool CAccountLoginLGInforMgr::registerAccountLoginInfor(SAccountLoginLGInfor& a_accountInfor)
{
	a_accountInfor.m_sessionID = m_sessionAllocator.allocateID();
	if (a_accountInfor.m_sessionID == m_sessionAllocator.invalidID()) {
		return false;
	}
	SAccountLoginLGInfor* infor = m_accountInforMgr.allcateObject(a_accountInfor.m_sessionID, a_accountInfor.m_stubID);
	infor->m_sessionID = a_accountInfor.m_sessionID;
	infor->m_stubID = a_accountInfor.m_stubID;
	infor->m_accountName = a_accountInfor.m_accountName;
	infor->m_accountKey = a_accountInfor.m_accountKey;
	infor->m_channelID = a_accountInfor.m_channelID;
	infor->m_accountLoginIP = a_accountInfor.m_accountLoginIP;

	return true;
}

bool CAccountLoginLGInforMgr::checkUniqueID(BSLib::uint32 a_id)
{
	return m_accountInforMgr.getObjectByLGSessionID(a_id) != NULL;
}

bool CAccountLoginLGInforMgr::isValidAccountLogin(GFLib::StubID& a_stubID)
{
	return m_accountInforMgr.getObjectByStubID(a_stubID) != NULL;
}

void CAccountLoginLGInforMgr::removeAccountLoginInfor(GFLib::StubID& a_stubID)
{
	m_accountInforMgr.destroyByStubID(a_stubID);
}

void CAccountLoginLGInforMgr::checkCN2LGAckAccountLogin(CMsgLoginSystemCN2LGAckAccountLogin& a_ackAccountLogin)
{
	SAccountLoginLGInfor* infor = m_accountInforMgr.getObjectByLGSessionID(a_ackAccountLogin.m_loginSession);
	if (infor == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "SessionID无效%s[SessionID=%d]", a_ackAccountLogin.m_accountKey.toLogString().c_str(), a_ackAccountLogin.m_loginSession);
		return ;
	}
	GFLib::StubID stubID = infor->m_stubID;
	GFLib::CommonServer::CStubPtr stubPtr = GFLib::CommonServer::CStubMgr::singleton().getCommonStubByStubID(stubID);
	if (stubPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "StubID无效[AccountName=%s][StubID=%d]", infor->m_accountName.c_str(), stubID);
		m_accountInforMgr.destroyByLGSessionID(a_ackAccountLogin.m_loginSession);
		return;
	}

	BSLIB_LOG_INFO(ETT_GSLIB_LOGINSYSTEM, "游戏区请求结束[AccountName=%s][SessionID=%d][State=%d]",
		infor->m_accountName.c_str(),
		a_ackAccountLogin.m_loginSession,
		a_ackAccountLogin.m_state);

	CMsgLoginSystemLG2GCAckAccountLogin ackAccountLogin2GC;
	ackAccountLogin2GC.m_state = a_ackAccountLogin.m_state;
	if (ackAccountLogin2GC.m_state <= ELOGINRESULT_SUCCESS) {
		ackAccountLogin2GC.m_gateServerIP = a_ackAccountLogin.m_gateServerIP;
		ackAccountLogin2GC.m_gateServerPort = a_ackAccountLogin.m_gateServerPort;
		ackAccountLogin2GC.m_gateKey = a_ackAccountLogin.m_gateKey;
		ackAccountLogin2GC.m_gateSession = a_ackAccountLogin.m_gateSession;
		ackAccountLogin2GC.m_accountKey = a_ackAccountLogin.m_accountKey;
	}
	stubPtr->IService_sendMsg(ackAccountLogin2GC);
	stubPtr->setState(BSLib::Network::ESS_RECYCLE);

	m_accountInforMgr.destroyByLGSessionID(a_ackAccountLogin.m_loginSession);
}

void CAccountLoginLGInforMgr::checkSP2LGAckRegisterToken(CMsgLoginSystemSP2LGAckRegisterToken& a_ackRegisterToken)
{
	SAccountLoginLGInfor* infor = m_accountInforMgr.getObjectByLGSessionID(a_ackRegisterToken.m_loginSession);
	if (infor == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "SessionID无效%s[SessionID=%d]",
			a_ackRegisterToken.m_accountKey.toLogString().c_str(),
			a_ackRegisterToken.m_loginSession);
		return ;
	}
	GFLib::StubID stubID = infor->m_stubID;
	GFLib::CommonServer::CStubPtr stubPtr = GFLib::CommonServer::CStubMgr::singleton().getCommonStubByStubID(stubID);
	if (stubPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "StubID无效[AccountName=%s][StubID=%d]", infor->m_accountName.c_str(), stubID);
		m_accountInforMgr.destroyByLGSessionID(a_ackRegisterToken.m_loginSession);
		return;
	}

	BSLIB_LOG_INFO(ETT_GSLIB_LOGINSYSTEM, "Super请求结束[AccountName=%s][SessionID=%d][State=%d][m_token=%s][AccountID=%lld]",
		infor->m_accountName.c_str(),
		a_ackRegisterToken.m_loginSession,
		a_ackRegisterToken.m_state,
        a_ackRegisterToken.m_token.c_str(),
        infor->m_accountKey.getAccountID());

    CMsgLoginSystemLG2GCAckGetAccountToken ackGetToken;
    ackGetToken.m_state = EGETACCOUNTTAKEN_SUCCESS;
    ackGetToken.m_accountToken = a_ackRegisterToken.m_token;
    ackGetToken.m_accountID = infor->m_accountKey.getAccountID();
    stubPtr->IService_sendMsg(ackGetToken);
    stubPtr->setState(BSLib::Network::ESS_RECYCLE);
}

void CAccountLoginLGInforMgr::checkSP2LGAckCheckToken(CMsgLoginSystemSP2LGAckCheckToken& a_ackCheckToken)
{
    SAccountLoginLGInfor* infor = m_accountInforMgr.getObjectByLGSessionID(a_ackCheckToken.m_loginSession);
    if (infor == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "SessionID无效%s[SessionID=%d]",
            a_ackCheckToken.m_accountKey.toLogString().c_str(),
            a_ackCheckToken.m_loginSession);
        return ;
    }
    GFLib::StubID stubID = infor->m_stubID;
    GFLib::CommonServer::CStubPtr stubPtr = GFLib::CommonServer::CStubMgr::singleton().getCommonStubByStubID(stubID);
    if (stubPtr == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "CMsgLoginSystemSP2LGAckCheckToken ERROR[AccountName=%s][StubID=%d]", infor->m_accountName.c_str(), stubID);
        m_accountInforMgr.destroyByLGSessionID(a_ackCheckToken.m_loginSession);
        return;
    }

    GSLib::LoginSystem::CMsgLoginSystemLG2GCAckAccountLogin ackAccountLogin;
    if(a_ackCheckToken.m_state != ELOGINRESULT_SUCCESS){
        ackAccountLogin.m_state = a_ackCheckToken.m_state;

        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "verifyTokenAccountLogin获取游戏区失败[ZoneID=%d][m_state=%d]", 
            a_ackCheckToken.m_accountKey.getZoneID(),a_ackCheckToken.m_state);

        stubPtr->IService_sendMsg(ackAccountLogin);
        stubPtr->setState(BSLib::Network::ESS_RECYCLE);

        m_accountInforMgr.destroyByLGSessionID(a_ackCheckToken.m_loginSession);  
        return;
    }

    GFLib::SServerID centerServerID;
    if (!CZoneInforMgr::singleton().verifyZone(a_ackCheckToken.m_accountKey.getZoneID(), ackAccountLogin, centerServerID)) {
        ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;

       BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "verifyTokenAccountLogin获取游戏区失败[ZoneID=%d][m_state=%d]", 
            a_ackCheckToken.m_accountKey.getZoneID(),a_ackCheckToken.m_state);

        stubPtr->IService_sendMsg(ackAccountLogin);
        stubPtr->setState(BSLib::Network::ESS_RECYCLE);
        m_accountInforMgr.destroyByLGSessionID(a_ackCheckToken.m_loginSession);     
        return ;
    }

	CMsgLoginSystemLG2CNReqAccountLogin reqAccountLogin2CN;
	reqAccountLogin2CN.m_accountName = infor->m_accountName;
	reqAccountLogin2CN.m_loginSession = infor->m_sessionID;
	reqAccountLogin2CN.m_channelID = infor->m_channelID;
	reqAccountLogin2CN.m_accountLoginIP = infor->m_accountLoginIP;
	reqAccountLogin2CN.m_accountKey = infor->m_accountKey;
	if (!GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(centerServerID, reqAccountLogin2CN)){
		ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;

		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "发送消息失败[CenterServer=%s][Account=%s]",
			centerServerID.toString().c_str(),
			infor->m_accountName.c_str());
		stubPtr->IService_sendMsg(ackAccountLogin);
		stubPtr->setState(BSLib::Network::ESS_RECYCLE);
		m_accountInforMgr.destroyByLGSessionID(a_ackCheckToken.m_loginSession);
		return ;
	}

	BSLIB_LOG_INFO(ETT_GSLIB_LOGINSYSTEM, "进入游戏区请求[AccountName=%s][zoneID=%d][SessionID=%d]",
		infor->m_accountName.c_str(),
		infor->m_accountKey.getZoneID(),
		infor->m_sessionID);;
}

}//LG

}//LoginSystem

}//GSLib

