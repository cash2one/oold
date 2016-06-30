#include <BSLib/framework/message/msgDebug.h>
#include <GFLib/commonServer/stubMgr.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/accountMgr.h>
#include <GFLib/commonServer/serverTypeMgr.h>
#include <GSLib/tracer.h>
#include <GSLib/loginSystem/GT/netPlayerGTMgr.h>
#include "GT/accountLoginGTInforMgr.h"
#include <GSLib/tracer.h>

namespace GSLib
{

namespace LoginSystem
{

namespace GT
{

CAccountLoginGTInforMgr::CAccountLoginGTInforMgr()
{
	m_sessionAllocator.setUniqueIDMgr(this);
}

CAccountLoginGTInforMgr::~CAccountLoginGTInforMgr()
{
	;
}

BSLIB_SINGLETON_DEFINE(CAccountLoginGTInforMgr);

int CAccountLoginGTInforMgr::registerCN2GTReqAccountLogin(BSLib::uint32& a_sessionID, GFLib::SServerID& a_centerServerID, CMsgLoginSystemCN2GTReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemGT2CNAckAccountLogin& a_ackAccountLogin)
{
	GFLib::SServerID gameServerID;
	GFLib::SServerID dataServerID;
	//EAccountStateGT state = EACCNTSTT_GT_NULL;
	int res = 1;
	SAccountLoginGTInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_reqAccountLogin.m_accountKey);
	if (infor != NULL) {
		if (infor->m_stubID != GFLib::INVALID_STUBID) {
			GFLib::CommonServer::CStubPtr stubPtr = GFLib::CommonServer::CStubMgr::singleton().getCommonStubByStubID(infor->m_stubID);
			if (stubPtr != NULL) {
				//在线玩家被踢下线
				stubPtr->setState(BSLib::Network::ESS_RECYCLE);
			}
		}
		gameServerID = infor->m_gameServerID;
		dataServerID = infor->m_dataServerID;
		//state = infor->m_state;

		m_accountInforMgr.destroyByAccountKey(a_reqAccountLogin.m_accountKey);
		infor = NULL;
		res = 0;
	}
	a_sessionID = m_sessionAllocator.allocateID();
	if (a_sessionID == m_sessionAllocator.invalidID()) {
		a_ackAccountLogin.m_centerSession = a_reqAccountLogin.m_centerSession;
		a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
		return -1;
	}
	infor = m_accountInforMgr.allcateObject(a_sessionID, a_reqAccountLogin.m_accountKey);
	if (infor == NULL) {
		a_ackAccountLogin.m_centerSession = a_reqAccountLogin.m_centerSession;
		a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
		return -1;
	}
	infor->m_gtSessionID = a_sessionID;
	infor->m_accountKey = a_reqAccountLogin.m_accountKey;
	infor->m_accountName = a_reqAccountLogin.m_accountName;
	infor->m_gateKey = 0;
	infor->m_channelID = a_reqAccountLogin.m_channelID;
	infor->m_accountLoginIP = a_reqAccountLogin.m_accountLoginIP;
	infor->m_accountKey = a_reqAccountLogin.m_accountKey;
	infor->m_centerServerID = a_centerServerID;
	
	infor->m_dataServerID = dataServerID;
	infor->m_gameServerID = gameServerID;
	infor->m_stubID = GFLib::INVALID_STUBID;
	infor->m_centerSessionID = a_reqAccountLogin.m_centerSession;
	infor->m_cbverifyAccountLogin = NULL;


	a_ackAccountLogin.m_centerSession = a_reqAccountLogin.m_centerSession;
	a_ackAccountLogin.m_state = ELOGINRESULT_SUCCESS;
	a_ackAccountLogin.m_gateKey = infor->m_gateKey;
	a_ackAccountLogin.m_gateSession = a_sessionID;
	a_ackAccountLogin.m_accountKey = a_reqAccountLogin.m_accountKey;

// 	if (state == EACCNTSTT_GT_OK || state == EACCNTSTT_GT_OFFLINE_WAIT_CLIENT || state == EACCNTSTT_GT_OFFLINE_WAIT_CENTER || state == EACCNTSTT_GT_BREAK_WAIT_CENTER) {
// 		infor->m_state = EACCNTSTT_GT_OFFLINE_WAIT_CLIENT;
// 		return 0;
// 	}
	infor->m_state = EACCNTSTT_GT_WAIT_CLIENT;
	return res;
}

bool CAccountLoginGTInforMgr::verifyAccountLogin(GFLib::StubID a_stubID, std::string& a_gateLoginIP, CMsgLoginSystemGC2GTReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemGT2GCAckAccountLogin& a_ackAccountLogin, CVerifyAccountLoginCallBack* a_cbverifyAccountLogin)
{
	SAccountLoginGTInfor* infor = m_accountInforMgr.getObjectByGTSessionID(a_reqAccountLogin.m_gateSession);
	if (infor == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "Session可能超时, 账号不存在");
		a_ackAccountLogin.m_state = ELOGINRESULT_LOGIN_TIMEOUT;
		return false;
	}
    BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "[GT_DEBUG][Account=%s][infor->m_state=%d]", infor->m_accountName.c_str(),infor->m_state);
	if (infor->m_accountKey != a_reqAccountLogin.m_accountKey){
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "AccountID不一致[Account=%s]", infor->m_accountName.c_str());
		a_ackAccountLogin.m_state = ELOGINRESULT_LOGIN_CHECK_ERROR;
		return false;
	}
	if (infor->m_gateKey != a_reqAccountLogin.m_gateKey){
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "Key不一致[Account=%s]", infor->m_accountName.c_str());
		a_ackAccountLogin.m_state = ELOGINRESULT_LOGIN_CHECK_ERROR;
		return false;
	}
	if (infor->m_channelID != a_reqAccountLogin.m_channelID){
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "ChannelID不一致[Account=%s]",infor->m_accountName.c_str());
		a_ackAccountLogin.m_state = ELOGINRESULT_LOGIN_CHECK_ERROR;
		return false;
	}
	
// 	if (infor->m_accountLoginIP != a_gateLoginIP) {
// 		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "IP不一致[Account=%s]", infor->m_accountName.c_str());
// 		a_ackAccountLogin.m_state = ELOGINRESULT_LOGIN_CHECK_ERROR;
// 		return false;
// 	}

     if((infor->m_stubID != a_stubID)&&(infor->m_stubID != GFLib::INVALID_STUBID)){
         if ((infor->m_state == EACCNTSTT_GT_OK)||(infor->m_state == EACCNTSTT_GT_WAIT_CLIENT)){
             // 掉线重连，替换旧的连接
             BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "[GT_DEBUG_OK][Account=%s][infor->m_state=%d][infor->m_stubID=%d][a_stubID=%d][掉线重连，替换旧的连接]", infor->m_accountName.c_str(),infor->m_state,infor->m_stubID,a_stubID);
             GFLib::CommonServer::CStubPtr stubPtr = GFLib::CommonServer::CStubMgr::singleton().getCommonStubByStubID(infor->m_stubID);
             if (stubPtr != NULL) {
                  stubPtr->setState(BSLib::Network::ESS_RECYCLE);
             }
             infor->m_stubID = a_stubID;
             GFLib::CommonServer::CStubPtr newStubPtr = GFLib::CommonServer::CStubMgr::singleton().getCommonStubByStubID(a_stubID);
             if (newStubPtr != NULL) {
                 a_ackAccountLogin.m_state = ELOGINRESULT_SUCCESS;
                 newStubPtr->IService_sendMsg(a_ackAccountLogin);
                 return true;
             }
         }
     }
	
	if (infor->m_state != EACCNTSTT_GT_WAIT_CLIENT) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "登陆状态不一致[Account=%s]", infor->m_accountName.c_str());
		a_ackAccountLogin.m_state = ELOGINRESULT_ACCOUNT_EXIT;
		return false;
	}
	if (infor->m_stubID != GFLib::INVALID_STUBID) {
		GFLib::CommonServer::CStubPtr stubPtr = GFLib::CommonServer::CStubMgr::singleton().getCommonStubByStubID(infor->m_stubID);
		if (stubPtr != NULL) {
			stubPtr->setState(BSLib::Network::ESS_RECYCLE);
		}
	}
    BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "[GT_DEBUG_OK][Account=%s][infor->m_state=%d]", infor->m_accountName.c_str(),infor->m_state);

	CMsgLoginSystemGT2CNReqAccountLogin reqAccountLogin2CN;
	reqAccountLogin2CN.m_gateSessionID = infor->m_gtSessionID;
	reqAccountLogin2CN.m_centerSessionID = infor->m_centerSessionID;
	reqAccountLogin2CN.m_accountKey = a_reqAccountLogin.m_accountKey;

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_centerServerID, reqAccountLogin2CN);

	infor->m_state = EACCNTSTT_GT_WAIT_CENTER;
	
	infor->m_stubID = a_stubID;
	infor->m_cbverifyAccountLogin = a_cbverifyAccountLogin;

	return true;
}

void CAccountLoginGTInforMgr::timeroutAccountLogin(BSLib::uint32& a_sessionID)
{
	SAccountLoginGTInfor* infor = m_accountInforMgr.getObjectByGTSessionID(a_sessionID);
	if (infor == NULL) {
		return ;
	}
	if (infor->m_state != EACCNTSTT_GT_WAIT_CLIENT) {
		return ;
	}
	if (infor->m_gameServerID.isValid() && infor->m_dataServerID.isValid()) {
		return ;
	}
	CMsgLoginSystemGT2CNNtfAccountTimeout ntfAccountTimeout;
	ntfAccountTimeout.m_centerSessionID = infor->m_centerSessionID;
	ntfAccountTimeout.m_accountKey = infor->m_accountKey;

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_centerServerID, ntfAccountTimeout);

	m_accountInforMgr.destroyByGTSessionID(a_sessionID);
}

void CAccountLoginGTInforMgr::terminateAccountLoginInfor(GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_gateKey, BSLib::uint32 a_gateSession, GFLib::StubID a_stubID)
{
	SAccountLoginGTInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		return ;
	}
	if (infor->m_gateKey != a_gateKey || infor->m_gtSessionID != a_gateSession || infor->m_stubID != a_stubID) {
		return ;
	}
	_terminateAccount(infor);
}

void CAccountLoginGTInforMgr::checCN2GTAckAccountLogin(CMsgLoginSystemCN2GTAckAccountLogin& a_ackAccountLogin)
{
	SAccountLoginGTInfor* infor = m_accountInforMgr.getObjectByGTSessionID(a_ackAccountLogin.m_gateSession);
	if (infor == NULL) {
		return ;
	}
	if (infor->m_accountKey != a_ackAccountLogin.m_accountKey) {
		return ;
	}
	if (infor->m_state != EACCNTSTT_GT_WAIT_CENTER) {
		return ;
	}
	GSLib::LoginSystem::CMsgLoginSystemGT2GCAckAccountLogin ackAccountLoginGT;
	if (a_ackAccountLogin.m_state != ELOGINRESULT_SUCCESS) {
		if (infor->m_stubID != GFLib::INVALID_STUBID) {
			GFLib::CommonServer::CStubPtr stubPtr = GFLib::CommonServer::CStubMgr::singleton().getCommonStubByStubID(infor->m_stubID);
			if (stubPtr != NULL) {
				ackAccountLoginGT.m_state = a_ackAccountLogin.m_state;
				stubPtr->IService_sendMsg(ackAccountLoginGT);
				stubPtr->setState(BSLib::Network::ESS_RECYCLE);
				m_accountInforMgr.destroyByGTSessionID(a_ackAccountLogin.m_gateSession);
			}
		}
		m_accountInforMgr.destroyByGTSessionID(a_ackAccountLogin.m_gateSession);
		return ;
	}
	if (infor->m_stubID == GFLib::INVALID_STUBID) {
		infor->m_state = EACCNTSTT_GT_OK;
		_terminateAccount(infor);
		return ;
	}
	GFLib::CommonServer::CStubPtr stubPtr = GFLib::CommonServer::CStubMgr::singleton().getCommonStubByStubID(infor->m_stubID);
	if (stubPtr == NULL) {
		infor->m_state = EACCNTSTT_GT_OK;
		_terminateAccount(infor);
		return ;
	}
	ackAccountLoginGT.m_state = a_ackAccountLogin.m_state;
	if (infor->m_cbverifyAccountLogin != NULL) {
		infor->m_cbverifyAccountLogin->_cbVerifyAccountLogin(infor->m_gameServerID, infor->m_dataServerID, infor->m_centerServerID);
	}
	infor->m_state = EACCNTSTT_GT_OK;
	stubPtr->IService_sendMsg(ackAccountLoginGT);
	BSLIB_LOG_INFO(GSLib::ETT_GSLIB_LOGINSYSTEM, "[AccountLogin][AccountName=%s][AccountID=%lld][ZoneID=%d]", 
		infor->m_accountName.c_str(), infor->getAccountKey().getAccountID(), infor->m_accountKey.getZoneID());

}

bool CAccountLoginGTInforMgr::checCN2GTReqCreatePlayer(CMsgLoginSystemCN2GTReqCreatePlayer& a_reqCreatePlayer)
{
	CMsgLoginSystemGT2CNAckCreatePlayer ackCreatePlayer;
	ackCreatePlayer.m_accountKey = a_reqCreatePlayer.m_accountKey;
	ackCreatePlayer.m_centerSessionID = a_reqCreatePlayer.m_centerSessionID;

	SAccountLoginGTInfor* infor = m_accountInforMgr.getObjectByGTSessionID(a_reqCreatePlayer.m_gateSessionID);
	if (infor == NULL) {
		return false;
	}
	if (infor->m_accountKey != a_reqCreatePlayer.m_accountKey) {
		return false;
	}
	if (infor->m_centerSessionID != a_reqCreatePlayer.m_centerSessionID) {
		return false;
	}
	if (infor->m_state != EACCNTSTT_GT_WAIT_CENTER) {
		return false;
	}
	CNetPlayerGTMgr* netPlayerGTMgr = CNetPlayerGTMgr::getSingleton();
	if (netPlayerGTMgr == NULL) {
		return false;
	}
	CNetPlayerGT* playerGT = netPlayerGTMgr->createNetPlayerGT(infor->m_accountKey, infor->m_accountName);
	if (playerGT == NULL) {
		return false;
	}
	GFLib::CommonServer::CAccountPtr accountPtr = new GFLib::CommonServer::CAccount(infor->m_accountKey);
	if (accountPtr == NULL) {
		return false;
	}
	infor->m_gameServerID = GFLib::SServerID(a_reqCreatePlayer.m_gameServerID);
	infor->m_dataServerID = GFLib::SServerID(a_reqCreatePlayer.m_dataServerID);

	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "创建账号%s[AccountName=%s]", infor->m_accountKey.toLogString().c_str(), infor->m_accountName.c_str());

	playerGT->_setDataServerID(infor->m_dataServerID);
	playerGT->_setGameServerID(infor->m_gameServerID);
	playerGT->_setCenterServerID(infor->m_centerServerID);
	playerGT->_setClientStubID(infor->m_stubID);

	playerGT->_setAccountPtr(accountPtr);
	accountPtr->setTransferMsgCB(playerGT);
	
	GFLib::CommonServer::CAccountMgr::singleton().addAccount(accountPtr);

	ackCreatePlayer.m_state = ELOGINRESULT_SUCCESS;

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_centerServerID, ackCreatePlayer);
	return true;
}

bool CAccountLoginGTInforMgr::checCN2GTReqInitPlayer(CMsgLoginSystemCN2GTReqInitPlayer& a_reqInitPlayer)
{
	SAccountLoginGTInfor* infor = m_accountInforMgr.getObjectByGTSessionID(a_reqInitPlayer.m_gateSessionID);
	if (infor == NULL) {
		return false;
	}
	if (infor->m_accountKey != a_reqInitPlayer.m_accountKey) {
		return false;
	}
	CNetPlayerGTMgr* netPlayerGTMgr = CNetPlayerGTMgr::getSingleton();
	if (netPlayerGTMgr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGTMgr失败");
		return false;
	}
	CNetPlayerGT* playerGT = netPlayerGTMgr->getNetPlayerGT(a_reqInitPlayer.m_accountKey);
	if (playerGT == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGT失败%s", a_reqInitPlayer.m_accountKey.toLogString().c_str());
		return false;
	}
	infor->m_isInit = true;
	playerGT->_cbInitPlayer();
	return true;
}

void CAccountLoginGTInforMgr::checCN2GTAckAccountBreak(BSLib::uint32 a_gateSessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginGTInfor* infor = m_accountInforMgr.getObjectByGTSessionID(a_gateSessionID);
	if (infor == NULL) {
		return ;
	}
	if (infor->m_accountKey != a_accountKey) {
		return ;
	}
	if (infor->m_state != EACCNTSTT_GT_OFFINE) {
		return ;
	}
	infor->m_state = EACCNTSTT_GT_WAIT_CLIENT;
}

bool CAccountLoginGTInforMgr::checCN2GTReqAccountOffline(BSLib::uint32 a_gateSessionID, GFLib::SAccountKey& a_accountKey)
{
	CMsgLoginSystemGT2CNAckAccountOffline ackAccountOffline; 
	ackAccountOffline.m_accountKey = a_accountKey;

	SAccountLoginGTInfor* infor = m_accountInforMgr.getObjectByGTSessionID(a_gateSessionID);
	if (infor == NULL) {
		return false;
	}
	if (infor->m_accountKey != a_accountKey) {
		return false;
	}
	ackAccountOffline.m_centerSessionID = infor->m_centerSessionID;

	CNetPlayerGTMgr* netPlayerGTMgr = CNetPlayerGTMgr::getSingleton();
	if (netPlayerGTMgr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGTMgr失败");
		return false;
	}
	CNetPlayerGT* playerGT = netPlayerGTMgr->getNetPlayerGT(a_accountKey);
	if (playerGT == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGT失败%s", a_accountKey.toLogString().c_str());
		return false;
	}
	playerGT->_cbPlayerOffline();

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_centerServerID, ackAccountOffline);
	return true;
}

bool CAccountLoginGTInforMgr::checCN2GTReqAccountOnline(BSLib::uint32 a_gateSessionID, GFLib::SAccountKey& a_accountKey)
{
	CMsgLoginSystemGT2CNAckAccountOnline ackAccountOnline; 
	ackAccountOnline.m_accountKey = a_accountKey;

	SAccountLoginGTInfor* infor = m_accountInforMgr.getObjectByGTSessionID(a_gateSessionID);
	if (infor == NULL) {
		return false;
	}
	if (infor->m_accountKey != a_accountKey) {
		return false;
	}
	ackAccountOnline.m_centerSessionID = infor->m_centerSessionID;

	CNetPlayerGTMgr* netPlayerGTMgr = CNetPlayerGTMgr::getSingleton();
	if (netPlayerGTMgr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGTMgr失败");
		return false;
	}
	CNetPlayerGT* playerGT = netPlayerGTMgr->getNetPlayerGT(a_accountKey);
	if (playerGT == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGT失败%s", a_accountKey.toLogString().c_str());
		return false;
	}
	playerGT->_setClientStubID(infor->m_stubID);

	playerGT->_cbPlayerOnline();

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_centerServerID, ackAccountOnline);
	return true;
}

bool CAccountLoginGTInforMgr::checCN2GTReqAccountFinal(BSLib::uint32 a_gateSessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginGTInfor* infor = m_accountInforMgr.getObjectByGTSessionID(a_gateSessionID);
	if (infor == NULL) {
		return false;
	}
	if (infor->m_accountKey != a_accountKey) {
		return false;
	}	
	_finishFinal(infor);
	return true;
}

void CAccountLoginGTInforMgr::finishInitPlayer(GFLib::SAccountKey& a_accountKey, ELoginResult a_result)
{
	SAccountLoginGTInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		return ;
	}

	CMsgLoginSystemGT2CNAckInitPlayer ackInitPlayer;
	ackInitPlayer.m_accountKey = infor->m_accountKey;
	ackInitPlayer.m_centerSession = infor->m_centerSessionID;
	ackInitPlayer.m_state = a_result;

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_centerServerID, ackInitPlayer);
}


void CAccountLoginGTInforMgr::dataServerLeave(const GFLib::SServerID& a_dataServerID)
{
	class CTraversalAccountCB : public CObjectAccountLoginGTInfor<BSLib::uint32, GFLib::SAccountKey, SAccountLoginGTInfor>::CCallback
	{
	public:
		CTraversalAccountCB(const GFLib::SServerID& a_dataServerID) : m_dataServerID(a_dataServerID)
		{
			;
		}

		virtual bool exec(SAccountLoginGTInfor* _value)
		{
			if (_value->m_dataServerID != m_dataServerID) {
				return true;
			}
			m_gateAcountArray.push_back(_value);
			return true;
		}

		GFLib::SServerID m_dataServerID;
		std::vector<SAccountLoginGTInfor*> m_gateAcountArray;
	};

	CTraversalAccountCB cb(a_dataServerID);

	m_accountInforMgr.traversal(cb);

	for (BSLib::uint32 i=0; i<cb.m_gateAcountArray.size(); ++i) {
		_finishFinal(cb.m_gateAcountArray[i], false, false);
	}
}

void CAccountLoginGTInforMgr::gameServerLeave(const GFLib::SServerID& a_gameServerID)
{
	;
}

void CAccountLoginGTInforMgr::centerServerLeave(const GFLib::SServerID& a_centerServerID)
{
	class CTraversalAccountCB : public CObjectAccountLoginGTInfor<BSLib::uint32, GFLib::SAccountKey, SAccountLoginGTInfor>::CCallback
	{
	public:
		CTraversalAccountCB(const GFLib::SServerID& a_centerServerID) : m_centerServerID(a_centerServerID)
		{
			;
		}

		virtual bool exec(SAccountLoginGTInfor* _value)
		{
			if (_value->m_centerServerID != m_centerServerID) {
				return true;
			}
			m_gateAcountArray.push_back(_value);
			return true;
		}

		GFLib::SServerID m_centerServerID;
		std::vector<SAccountLoginGTInfor*> m_gateAcountArray;
	};

	CTraversalAccountCB cb(a_centerServerID);

	m_accountInforMgr.traversal(cb);

	for (BSLib::uint32 i=0; i<cb.m_gateAcountArray.size(); ++i) {
		_finishFinal(cb.m_gateAcountArray[i], true, false);
	}
}

void CAccountLoginGTInforMgr::broadcastMsg(CMsgLoginSystemXS2GTNtfBroadcastMsg* a_ntfBroadcastMsg)
{
	class CTraversalAccountCB : public CObjectAccountLoginGTInfor<BSLib::uint32, GFLib::SAccountKey, SAccountLoginGTInfor>::CCallback
	{
	public:
		CTraversalAccountCB(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize) : m_msg(a_msg), m_msgSize(a_msgSize)
		{
			;
		}

		virtual bool exec(SAccountLoginGTInfor* _value)
		{
			if (_value->m_stubID == GFLib::INVALID_STUBID) {
				return true;
			}
			GFLib::CommonServer::CStubPtr stubPtr = GFLib::CommonServer::CStubMgr::singleton().getCommonStubByStubID(_value->m_stubID);
			if (stubPtr == NULL) {
				return true;
			}
			stubPtr->IService_sendMsg(m_msg, m_msgSize);
			return true;
		}

		GFLib::SMessage* m_msg;
		BSLib::uint32 m_msgSize;
	};

	if (a_ntfBroadcastMsg->m_subMsg.readSize() <= 0) {
		return;
	}

	GFLib::SMessage* msg = (GFLib::SMessage*)a_ntfBroadcastMsg->m_subMsg.readPtr();
	BSLib::uint32 msgSize = a_ntfBroadcastMsg->m_subMsg.readSize();

	BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "Broadcast MsgID(%d[%s].%d.%d) [%s]", 
		msg->getServerType(),
		GFLib::CommonServer::CServerTypeMgr::singleton().getCodeServerType(msg->getServerType()).c_str(),
		msg->getFunctionType(), 
		msg->getID(),
		BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());

	CTraversalAccountCB cb(msg, msgSize);
	m_accountInforMgr.traversal(cb);
}

void CAccountLoginGTInforMgr::checkNtfAccountQuit(GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginGTInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		return ;
	}

	CMsgLoginSystemGT2CNNtfAccountQuit ntfAccountQuit;
	ntfAccountQuit.m_accountKey = infor->m_accountKey;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_centerServerID, ntfAccountQuit);
}

bool CAccountLoginGTInforMgr::checkUniqueID(BSLib::uint32 a_id)
{
	return m_accountInforMgr.getObjectByGTSessionID(a_id) != NULL;
}

void CAccountLoginGTInforMgr::_terminateAccount(SAccountLoginGTInfor* a_infor)
{
	a_infor->m_stubID = GFLib::INVALID_STUBID;
	a_infor->m_cbverifyAccountLogin = NULL;

	if (a_infor->m_state == EACCNTSTT_GT_OK) {
		a_infor->m_state = EACCNTSTT_GT_OFFINE;

		CMsgLoginSystemGT2CNReqAccountBreak ntfAccountTimeout;
		ntfAccountTimeout.m_centerSessionID = a_infor->m_centerSessionID;
		ntfAccountTimeout.m_accountKey = a_infor->m_accountKey;

		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_centerServerID, ntfAccountTimeout);
	}
}

void CAccountLoginGTInforMgr::_finishFinal(SAccountLoginGTInfor* a_infor, bool a_needNotifyDB, bool a_needNotyfyCN)
{
	CNetPlayerGTMgr* netPlayerGTMgr = CNetPlayerGTMgr::getSingleton();
	if (netPlayerGTMgr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGTMgr失败");
		return ;
	}
	CNetPlayerGT* playerGT = netPlayerGTMgr->getNetPlayerGT(a_infor->m_accountKey);
	if (playerGT == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGT失败%s", a_infor->m_accountKey.toLogString().c_str());
		return ;
	}

	if (a_infor->m_isInit) {
		playerGT->_cbFinalPlayer();
	}

	if (a_needNotifyDB) {
		CMsgLoginSystemGT2DBNtfAccountFinal ackAccountFinalDB; 
		ackAccountFinalDB.m_accountKey = a_infor->m_accountKey;
		ackAccountFinalDB.m_centerSessionID = a_infor->m_centerSessionID;
		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_dataServerID, ackAccountFinalDB);
	}
	if (a_needNotyfyCN) {
		CMsgLoginSystemGT2CNAckAccountFinal ackAccountFinalCN; 
		ackAccountFinalCN.m_accountKey = a_infor->m_accountKey;
		ackAccountFinalCN.m_centerSessionID = a_infor->m_centerSessionID;
		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_centerServerID, ackAccountFinalCN);
	}

	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "释放账号%s[AccountName=%s]", a_infor->m_accountKey.toLogString().c_str(), a_infor->m_accountName.c_str());
	
	GFLib::CommonServer::CAccountMgr::singleton().delAccount(a_infor->m_accountKey);
	netPlayerGTMgr->removeNetPlayerGT(a_infor->m_accountKey);
	m_accountInforMgr.destroyByAccountKey(a_infor->m_accountKey);
}


}//GT

}//LoginSystem

}//GSLib

