#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/accountMgr.h>
#include <GSLib/tracer.h>
#include "CN/accountLoginCNInforMgr.h"
#include <GSLib/loginSystem/CN/netPlayerCNMgr.h>
#include <GSLib/loginSystem/CN/loginSystemCN.h>

#define GSLIB_LOGINSYSTEM_STATE_CN 0x01
#define GSLIB_LOGINSYSTEM_STATE_GT 0x02
#define GSLIB_LOGINSYSTEM_STATE_GM 0x04
#define GSLIB_LOGINSYSTEM_STATE_DB 0x08

#define GSLIB_LOGINSYSTEM_ERROR_STATE_CN 0x10
#define GSLIB_LOGINSYSTEM_ERROR_STATE_GT 0x20
#define GSLIB_LOGINSYSTEM_ERROR_STATE_GM 0x40
#define GSLIB_LOGINSYSTEM_ERROR_STATE_DB 0x80

#define GSLIB_LOGINSYSTEM_STATE_XX 0x0F
#define GSLIB_LOGINSYSTEM_ERROR_STATE_XX 0xF0

namespace GSLib
{

namespace LoginSystem
{

namespace CN
{

CAccountLoginCNInforMgr::CAccountLoginCNInforMgr()
{
	m_sessionAllocator.setUniqueIDMgr(this);
}

CAccountLoginCNInforMgr::~CAccountLoginCNInforMgr()
{
	;
}

BSLIB_SINGLETON_DEFINE(CAccountLoginCNInforMgr);

EAccountStateCN CAccountLoginCNInforMgr::checkLG2CNReqAccountLogin(GFLib::SAccountKey& a_accountKey, GFLib::SServerID& a_gateServerID)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		return EACCNTSTT_CN_NULL;
	}
	a_gateServerID = infor->m_gateServerID;
	return infor->getAccountState();
}

bool CAccountLoginCNInforMgr::registerLG2CNReqAccountLogin(BSLib::uint32& a_sessionID, GFLib::SServerID& a_loginServerID, GFLib::SServerID& a_gateServerID, CMsgLoginSystemLG2CNReqAccountLogin& a_reqAccountLogin, EAccountStateCN a_state)
{
	GFLib::SServerID gameServerID;
	EAccountStateCN state = EACCNTSTT_CN_NULL;
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_reqAccountLogin.m_accountKey);
	if (infor != NULL) {
		gameServerID = infor->m_gameServerID;
		state = infor->getAccountState();
		m_accountInforMgr.destroyByAccountKey(a_reqAccountLogin.m_accountKey);
		infor = NULL;
	}
	a_sessionID = m_sessionAllocator.allocateID();
	if (a_sessionID == m_sessionAllocator.invalidID()) {
		return false;
	}
	infor = m_accountInforMgr.allcateObject(a_sessionID, a_reqAccountLogin.m_accountKey);
	if (infor == NULL) {
		return false;
	}
	infor->m_cnSessionID = a_sessionID;
	infor->m_accountKey = a_reqAccountLogin.m_accountKey;
	infor->setAccountState(a_state);
	infor->m_gateServerID = a_gateServerID;
	infor->m_gameServerID = gameServerID;
	infor->m_loginServerID = a_loginServerID;
	infor->m_accountName = a_reqAccountLogin.m_accountName;
	infor->m_loginSession = a_reqAccountLogin.m_loginSession;
	infor->m_gateKey = 0;
	infor->m_gateSession = 0;

	CMsgLoginSystemCN2GTReqAccountLogin reqAccountLogin2GT;
	reqAccountLogin2GT.m_centerSession = a_sessionID;
	reqAccountLogin2GT.m_channelID = a_reqAccountLogin.m_channelID;
	reqAccountLogin2GT.m_accountName = a_reqAccountLogin.m_accountName;
	reqAccountLogin2GT.m_accountLoginIP = a_reqAccountLogin.m_accountLoginIP;
	reqAccountLogin2GT.m_accountKey = a_reqAccountLogin.m_accountKey;
	if (!GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_gateServerID, reqAccountLogin2GT)) {
		infor->setAccountState(state);
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "发送信息失败 %s[AccountName=%s]", a_reqAccountLogin.toString().c_str(), a_reqAccountLogin.m_accountName.c_str());
		return false;
	}

	BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "通知Gate注册玩家 %s[AccountName=%s]", a_reqAccountLogin.toString().c_str(), a_reqAccountLogin.m_accountName.c_str());

	return true;
}

void CAccountLoginCNInforMgr::checkGT2CNAckAccountLogin(CMsgLoginSystemGT2CNAckAccountLogin& a_ackAccountLogin)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_ackAccountLogin.m_centerSession);
	if (infor == NULL) {
		return;
	}
	if (infor->m_accountKey != a_ackAccountLogin.m_accountKey) {
		return;
	}
	
	infor->m_gateKey = a_ackAccountLogin.m_gateKey;
	infor->m_gateSession = a_ackAccountLogin.m_gateSession;

	CMsgLoginSystemCN2LGAckAccountLogin ackAccountLogin;
	ackAccountLogin.m_state = a_ackAccountLogin.m_state;
	ackAccountLogin.m_loginSession = infor->m_loginSession;

	EAccountStateCN state = infor->getAccountState();
	if (state == EACCNTSTT_CN_WAIT_GATE) {
		if (a_ackAccountLogin.m_state != ELOGINRESULT_SUCCESS) {
			BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "Gate反馈 %s[AccountName=%s][%d][%d]", infor->m_accountKey.toLogString().c_str(), infor->m_accountName.c_str(), infor->getAccountState(), a_ackAccountLogin.m_state);

			GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_loginServerID, ackAccountLogin);
			CGateInforMgr::singleton().decreaseWaitAccountFromGateServer(infor->m_gateServerID);
			m_accountInforMgr.destroyByCNSessionID(a_ackAccountLogin.m_centerSession);
			return ;
		}
		infor->setAccountState(EACCNTSTT_CN_WAIT_CLIENT);

	} else if (state == EACCNTSTT_CN_OFFLINE_WAIT_GATE) {
		if (a_ackAccountLogin.m_state != ELOGINRESULT_SUCCESS) {
			BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "Gate反馈 %s[AccountName=%s][%d][%d]", infor->m_accountKey.toLogString().c_str(), infor->m_accountName.c_str(), infor->getAccountState(), a_ackAccountLogin.m_state);

			GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_loginServerID, ackAccountLogin);
			infor->setAccountState(EACCNTSTT_CN_OFFLINE_WAIT_CLIENT);
			return ;
		}
		infor->setAccountState(EACCNTSTT_CN_OFFLINE_WAIT_CLIENT);
	} else if (state == EACCNTSTT_CN_KICK_ACCOUNT) {
		BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "Gate要求下线 %s[AccountName=%s][%d][%d]", infor->m_accountKey.toLogString().c_str(), infor->m_accountName.c_str(), infor->getAccountState(), a_ackAccountLogin.m_state);

		infor->setAccountState(EACCNTSTT_CN_PLAYER_OFFLINE_KICK);
		_notifyOffline(infor);
		return;
	}

	BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "Gate反馈 %s[AccountName=%s][%d][%d]", infor->m_accountKey.toLogString().c_str(), infor->m_accountName.c_str(), infor->getAccountState(), a_ackAccountLogin.m_state);

	BSLib::Network::CSockAddr&  connectAddr = CGateInforMgr::singleton().getGateConnectAddr(infor->m_gateServerID);

	ackAccountLogin.m_gateServerIP = connectAddr.getIP();
	ackAccountLogin.m_gateServerPort = connectAddr.getPort();
	ackAccountLogin.m_gateKey = a_ackAccountLogin.m_gateKey;
	ackAccountLogin.m_gateSession = a_ackAccountLogin.m_gateSession;
	ackAccountLogin. m_accountKey = a_ackAccountLogin.m_accountKey;

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_loginServerID, ackAccountLogin);
}

void CAccountLoginCNInforMgr::removeCN2LGAckAccountLogin(BSLib::uint32& a_sessionID, ELoginResult a_loginResult)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	CMsgLoginSystemCN2LGAckAccountLogin ackAccountLogin;
	ackAccountLogin.m_loginSession = infor->m_loginSession;
	ackAccountLogin.m_state = a_loginResult;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_loginServerID, ackAccountLogin);

	//CGateInforMgr::singleton().decreaseWaitAccountFromGateServer(infor->m_gateServerID);

	m_accountInforMgr.destroyByCNSessionID(a_sessionID);
}

void CAccountLoginCNInforMgr::timeoutAccountLoginInfor(BSLib::uint32& a_sessionID)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->getAccountState() != EACCNTSTT_CN_WAIT_CLIENT) {
		return;
	}
	BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "登陆超时[SessionID=%d]%s[Account=%s]", a_sessionID, infor->m_accountKey.toLogString().c_str(), infor->m_accountName.c_str());

	CGateInforMgr::singleton().decreaseWaitAccountFromGateServer(infor->m_gateServerID);
	m_accountInforMgr.destroyByCNSessionID(a_sessionID);	
}

void CAccountLoginCNInforMgr::timeoutAccountOffline(BSLib::uint32& a_sessionID)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->getAccountState() != EACCNTSTT_CN_OFFLINE_WAIT_CLIENT) {
		return;
	}
	BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "离线超时[SessionID=%d]%s[Account=%s]", a_sessionID, infor->m_accountKey.toLogString().c_str(), infor->m_accountName.c_str());

	infor->setAccountState(EACCNTSTT_CN_ACCOUNT_FINAL);
	_notifyFinal(infor);

	//CGateInforMgr::singleton().decreaseWaitAccountFromGateServer(infor->m_gateServerID);
	//m_accountInforMgr.destroyByCNSessionID(a_sessionID);
}

bool CAccountLoginCNInforMgr::checkGT2CNReqAccountLogin(CMsgLoginSystemGT2CNReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemCN2GTAckAccountLogin& a_ackAccountLogin)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_reqAccountLogin.m_accountKey);
	
	if (infor == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "登陆超时 %s", a_reqAccountLogin.m_accountKey.toLogString().c_str());
		a_ackAccountLogin.m_state = ELOGINRESULT_LOGIN_TIMEOUT;
		return false;
	}
	if (a_reqAccountLogin.m_gateSessionID != infor->m_gateSession) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "登陆超时,SessionID不一致 %s", a_reqAccountLogin.m_accountKey.toLogString().c_str());
		a_ackAccountLogin.m_state = ELOGINRESULT_LOGIN_TIMEOUT;
		return false;
	}
	EAccountStateCN state = infor->getAccountState();
	if (state == EACCNTSTT_CN_OFFLINE_WAIT_CLIENT) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "玩家上线 %s[AccountName=%s][%d]", infor->m_accountKey.toLogString().c_str(), infor->m_accountName.c_str(), state);
		//通知所有Server玩家上线;
		_notifyOnline(infor);
		return true;
	}
	if (state != EACCNTSTT_CN_WAIT_CLIENT) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "玩家上线异常 %s[AccountName=%s][%d]", infor->m_accountKey.toLogString().c_str(), infor->m_accountName.c_str(), state);
		a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
		return false;
	}

	if (!m_dataServerID.isValid()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "Gate不存在 %s[AccountName=%s][%d]", infor->m_accountKey.toLogString().c_str(), infor->m_accountName.c_str(), state);
		a_ackAccountLogin.m_state = ELOGINRESULT_ZONEID_STOP;
		CGateInforMgr::singleton().decreaseWaitAccountFromGateServer(infor->m_gateServerID);
		m_accountInforMgr.destroyByAccountKey(a_reqAccountLogin.m_accountKey);
		return false;
	}
	GFLib::SServerID gameServerID;
	if (!CGameInforMgr::singleton().increaseAccountToGameServer(gameServerID)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "分配Gate失败 %s[AccountName=%s][%d]", infor->m_accountKey.toLogString().c_str(), infor->m_accountName.c_str(), state);

		a_ackAccountLogin.m_state = ELOGINRESULT_ZONEID_STOP;

		CGateInforMgr::singleton().decreaseWaitAccountFromGateServer(infor->m_gateServerID);
		m_accountInforMgr.destroyByAccountKey(a_reqAccountLogin.m_accountKey);
		return false;
	}
	infor->m_gameServerID = gameServerID;
	infor->setAccountState(EACCNTSTT_CN_PLAYER_INIT);

	BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "准备初始化玩家 %s[AccountName=%s]", infor->m_accountKey.toLogString().c_str(), infor->m_accountName.c_str());

	if (!_notifyCreatePlayer(infor)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "创建Player失败 %s[AccountName=%s][%d]", infor->m_accountKey.toLogString().c_str(), infor->m_accountName.c_str(), state);

		a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;

		CGateInforMgr::singleton().decreaseWaitAccountFromGateServer(infor->m_gateServerID);
		m_accountInforMgr.destroyByAccountKey(a_reqAccountLogin.m_accountKey);
		return false;
	}
	CGateInforMgr::singleton().decreaseWaitAccountFromGateServer(infor->m_gateServerID);
	CGateInforMgr::singleton().increaseOnlineAccountFromGateServer(infor->m_gateServerID);
	
	return true;
}

void CAccountLoginCNInforMgr::gateServerLeave(const GFLib::SServerID& a_gateServerID)
{
	class CTraversalAccountCB : public CObjectAccountLoginCNInforMgr<BSLib::uint32, GFLib::SAccountKey, SAccountLoginCNInfor>::CCallback
	{
	public:
		CTraversalAccountCB(const GFLib::SServerID& a_gateServerID) : m_gateServerID(a_gateServerID)
		{
			;
		}

		virtual bool exec(SAccountLoginCNInfor* _value)
		{
			if (_value->m_gateServerID != m_gateServerID) {
				return true;
			}
			_value->m_stateFinal |= GSLIB_LOGINSYSTEM_STATE_GT;
			m_gateAcountArray.push_back(_value);
			return true;
		}

		GFLib::SServerID m_gateServerID;
		std::vector<SAccountLoginCNInfor*> m_gateAcountArray;
	};

	CTraversalAccountCB cb(a_gateServerID);

	m_accountInforMgr.traversal(cb);

	for (BSLib::uint32 i=0; i<cb.m_gateAcountArray.size(); ++i) {
		_notifyExit(cb.m_gateAcountArray[i]);
	}
}

void CAccountLoginCNInforMgr::gameServerLeave(const GFLib::SServerID& a_gameServerID)
{
	class CTraversalAccountCB : public CObjectAccountLoginCNInforMgr<BSLib::uint32, GFLib::SAccountKey, SAccountLoginCNInfor>::CCallback
	{
	public:
		CTraversalAccountCB(const GFLib::SServerID& a_gameServerID) : m_gameServerID(a_gameServerID)
		{
			;
		}

		virtual bool exec(SAccountLoginCNInfor* _value)
		{
			if (_value->m_gameServerID != m_gameServerID) {
				return true;
			}
			_value->m_stateFinal |= GSLIB_LOGINSYSTEM_STATE_GM;
			m_gateAcountArray.push_back(_value);
			return true;
		}

		GFLib::SServerID m_gameServerID;
		std::vector<SAccountLoginCNInfor*> m_gateAcountArray;
	};

	CTraversalAccountCB cb(a_gameServerID);

	m_accountInforMgr.traversal(cb);

	for (BSLib::uint32 i=0; i<cb.m_gateAcountArray.size(); ++i) {
		_notifyExit(cb.m_gateAcountArray[i]);
	}
}

void CAccountLoginCNInforMgr::dataServerLeave(const GFLib::SServerID& a_dataServerID)
{
	class CTraversalAccountCB : public CObjectAccountLoginCNInforMgr<BSLib::uint32, GFLib::SAccountKey, SAccountLoginCNInfor>::CCallback
	{
	public:
		virtual bool exec(SAccountLoginCNInfor* _value)
		{
			_value->m_stateFinal |= GSLIB_LOGINSYSTEM_STATE_XX;
			m_gateAcountArray.push_back(_value);
			return true;
		}

		std::vector<SAccountLoginCNInfor*> m_gateAcountArray;
	};

	CTraversalAccountCB cb;

	m_accountInforMgr.traversal(cb);

	for (BSLib::uint32 i=0; i<cb.m_gateAcountArray.size(); ++i) {
		_notifyExit(cb.m_gateAcountArray[i]);
	}
}

void CAccountLoginCNInforMgr::checkGM2CNAckCreatePlayer(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_state)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->getAccountState() != EACCNTSTT_CN_PLAYER_INIT) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}
	infor->m_stateCreatePlayerGM = 1;
	if (a_state != ELOGINRESULT_SUCCESS) {
		infor->m_stateCreatePlayerGM = 2;
		_notifyExitByCreate(infor);
		return;
	}
	if (infor->m_stateCreatePlayerDB == 2 || infor->m_stateCreatePlayerGM == 2 || infor->m_stateCreatePlayerGT == 2) {
		_notifyExitByCreate(infor);
		return;
	}
	if (infor->m_stateCreatePlayerDB == 1 && infor->m_stateCreatePlayerGM == 1 && infor->m_stateCreatePlayerGT == 1) {
		_notifyInitPlayer(infor);
	}
}

void CAccountLoginCNInforMgr::checkGT2CNAckCreatePlayer(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_state)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->getAccountState() != EACCNTSTT_CN_PLAYER_INIT) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}
	infor->m_stateCreatePlayerGT = 1;
	if (a_state != ELOGINRESULT_SUCCESS) {
		infor->m_stateCreatePlayerGT = 2;
		_notifyExitByCreate(infor);
		return;
	}
	if (infor->m_stateCreatePlayerDB == 2 || infor->m_stateCreatePlayerGM == 2 || infor->m_stateCreatePlayerGT == 2) {
		_notifyExitByCreate(infor);
		return;
	}
	if (infor->m_stateCreatePlayerDB == 1 && infor->m_stateCreatePlayerGM == 1 && infor->m_stateCreatePlayerGT == 1) {
		_notifyInitPlayer(infor);
	}
}

void CAccountLoginCNInforMgr::checkDB2CNAckCreatePlayer(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_state)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->getAccountState() != EACCNTSTT_CN_PLAYER_INIT) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}
	infor->m_stateCreatePlayerDB= 1;
	if (a_state != ELOGINRESULT_SUCCESS) {
		infor->m_stateCreatePlayerDB= 2;
		_notifyExitByCreate(infor);
		return;
	}
	if (infor->m_stateCreatePlayerDB == 2 || infor->m_stateCreatePlayerGM == 2 || infor->m_stateCreatePlayerGT == 2) {
		_notifyExitByCreate(infor);
		return;
	}
	if (infor->m_stateCreatePlayerDB == 1 && infor->m_stateCreatePlayerGM == 1 && infor->m_stateCreatePlayerGT == 1) {
		_notifyInitPlayer(infor);
	}
}

void CAccountLoginCNInforMgr::checkGM2CNNtfInitPlayer(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_state)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->getAccountState() != EACCNTSTT_CN_PLAYER_INIT) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}
	
	if (a_state != ELOGINRESULT_SUCCESS) {
		infor->m_stateInitPlayer |= GSLIB_LOGINSYSTEM_ERROR_STATE_GM;
		_notifyExitByInit(infor);
		return;
	}
	if (!_initPlayer(infor)) {
		infor->m_stateInitPlayer |= GSLIB_LOGINSYSTEM_ERROR_STATE_GM;
		_notifyExitByInit(infor);
		return;
	}
	infor->m_stateInitPlayer |= GSLIB_LOGINSYSTEM_STATE_GM;
	
	CMsgLoginSystemCN2GTReqInitPlayer reqInitPlayer2GT;
	reqInitPlayer2GT.m_centerSessionID = infor->m_cnSessionID;
	reqInitPlayer2GT.m_accountKey = infor->m_accountKey;
	reqInitPlayer2GT.m_gateSessionID = infor->m_gateSession;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_gateServerID, reqInitPlayer2GT);
}

void CAccountLoginCNInforMgr::checkGT2CNAckInitPlayer(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_state)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->getAccountState() != EACCNTSTT_CN_PLAYER_INIT) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}
	if (a_state != ELOGINRESULT_SUCCESS) {
		infor->m_stateInitPlayer |= GSLIB_LOGINSYSTEM_ERROR_STATE_GT;
		_notifyExitByInit(infor);
		return;
	}
	infor->m_stateInitPlayer |= GSLIB_LOGINSYSTEM_STATE_GT;
	if (infor->m_stateInitPlayer == GSLIB_LOGINSYSTEM_STATE_XX) {
		_finishInitPlayer(infor);
	}
}

void CAccountLoginCNInforMgr::checkDB2CNAckInitPlayer(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_state)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->getAccountState() != EACCNTSTT_CN_PLAYER_INIT) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}
	if (a_state != ELOGINRESULT_SUCCESS) {
		infor->m_stateInitPlayer |= GSLIB_LOGINSYSTEM_ERROR_STATE_DB;
		_notifyExitByInit(infor);
		return;
	}
	infor->m_stateInitPlayer |= GSLIB_LOGINSYSTEM_STATE_DB;
	if (infor->m_stateInitPlayer == GSLIB_LOGINSYSTEM_STATE_XX) {
		_finishInitPlayer(infor);
	}
}

void CAccountLoginCNInforMgr::checkGT2CNReqAccountBreak(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}

	if (infor->getAccountState() != EACCNTSTT_CN_OK) {
		return;
	}
	infor->setAccountState(EACCNTSTT_CN_PLAYER_OFFLINE_BREAK);
	_notifyOffline(infor);
}

void CAccountLoginCNInforMgr::checkGT2CNAckAccountOffline(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}

	EAccountStateCN state = infor->getAccountState();
	if (!(state == EACCNTSTT_CN_PLAYER_OFFLINE_BREAK || state == EACCNTSTT_CN_PLAYER_OFFLINE_KICK)) {
		return;
	}
	infor->m_stateOffline |= GSLIB_LOGINSYSTEM_STATE_GT;

	if (infor->m_stateOffline == GSLIB_LOGINSYSTEM_STATE_XX) {
		_finishOffline(infor);
	}
}

void CAccountLoginCNInforMgr::checkGM2CNAckAccountOffline(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}

	EAccountStateCN state = infor->getAccountState();
	if (!(state == EACCNTSTT_CN_PLAYER_OFFLINE_BREAK || state == EACCNTSTT_CN_PLAYER_OFFLINE_KICK)) {
		return;
	}
	infor->m_stateOffline |= GSLIB_LOGINSYSTEM_STATE_GM;

	if (infor->m_stateOffline == GSLIB_LOGINSYSTEM_STATE_XX) {
		_finishOffline(infor);
	}
}

void CAccountLoginCNInforMgr::checkDB2CNAckAccountOffline(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}

	EAccountStateCN state = infor->getAccountState();
	if (!(state == EACCNTSTT_CN_PLAYER_OFFLINE_BREAK || state == EACCNTSTT_CN_PLAYER_OFFLINE_KICK)) {
		return;
	}
	infor->m_stateOffline |= GSLIB_LOGINSYSTEM_STATE_DB;

	if (infor->m_stateOffline == GSLIB_LOGINSYSTEM_STATE_XX) {
		_finishOffline(infor);
	}
}

void CAccountLoginCNInforMgr::checkGT2CNAckAccountOnline(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}

	if (infor->getAccountState() != EACCNTSTT_CN_PLAYER_ONLINE) {
		return;
	}
	infor->m_stateOnline |= GSLIB_LOGINSYSTEM_STATE_GT;

	CMsgLoginSystemCN2GMReqAccountOnline reqAccountOnlineGM;
	reqAccountOnlineGM.m_accountKey = infor->m_accountKey;
	reqAccountOnlineGM.m_centerSessionID = infor->m_cnSessionID;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_gameServerID, reqAccountOnlineGM);

	CMsgLoginSystemCN2DBReqAccountOnline reqAccountOnlineDB;
	reqAccountOnlineDB.m_accountKey = infor->m_accountKey;
	reqAccountOnlineDB.m_centerSessionID = infor->m_cnSessionID;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_dataServerID, reqAccountOnlineDB);

// 	if (infor->m_stateOnline == GSLIB_LOGINSYSTEM_STATE_XX) {
// 		_finishOnline(infor);
// 	}
}

void CAccountLoginCNInforMgr::checkGM2CNAckAccountOnline(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}

	if (infor->getAccountState() != EACCNTSTT_CN_PLAYER_ONLINE) {
		return;
	}
	infor->m_stateOnline |= GSLIB_LOGINSYSTEM_STATE_GM;

	if (infor->m_stateOnline == GSLIB_LOGINSYSTEM_STATE_XX) {
		_finishOnline(infor);
	}
}

void CAccountLoginCNInforMgr::checkDB2CNAckAccountOnline(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}

	if (infor->getAccountState() != EACCNTSTT_CN_PLAYER_ONLINE) {
		return;
	}
	infor->m_stateOnline |= GSLIB_LOGINSYSTEM_STATE_DB;

	if (infor->m_stateOnline == GSLIB_LOGINSYSTEM_STATE_XX) {
		_finishOnline(infor);
	}
}

void CAccountLoginCNInforMgr::checkNtfAccountQuit(GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		return;
	}
	EAccountStateCN state = infor->getAccountState();
	if (!(state == EACCNTSTT_CN_OK || state == EACCNTSTT_CN_OFFLINE_WAIT_CLIENT)) {
		return;
	}
	infor->setAccountState(EACCNTSTT_CN_ACCOUNT_FINAL);
	_notifyFinal(infor);
}

void CAccountLoginCNInforMgr::checkGT2CNAckAccountFinal(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}

	if (infor->getAccountState() != EACCNTSTT_CN_ACCOUNT_FINAL) {
		return;
	}
	infor->m_stateFinal |= GSLIB_LOGINSYSTEM_STATE_GT;

	if (infor->m_stateFinal == GSLIB_LOGINSYSTEM_STATE_XX) {
		_finishFinal(infor);
	}
}

void CAccountLoginCNInforMgr::checkGM2CNAckAccountFinal(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}

	if (infor->getAccountState() != EACCNTSTT_CN_ACCOUNT_FINAL) {
		return;
	}
	infor->m_stateFinal |= GSLIB_LOGINSYSTEM_STATE_GM;

	if (infor->m_stateFinal == GSLIB_LOGINSYSTEM_STATE_XX) {
		_finishFinal(infor);
	}
}

void CAccountLoginCNInforMgr::checkDB2CNAckAccountFinal(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}

	if (infor->getAccountState() != EACCNTSTT_CN_ACCOUNT_FINAL) {
		return;
	}
	infor->m_stateFinal |= GSLIB_LOGINSYSTEM_STATE_DB;

	if (infor->m_stateFinal == GSLIB_LOGINSYSTEM_STATE_XX) {
		_finishFinal(infor);
	}
}

void CAccountLoginCNInforMgr::checkGT2CNNtfAccountTimeout(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByCNSessionID(a_sessionID);
	if (infor == NULL) {
		return;
	}
	if (infor->m_accountKey != a_accountKey) {
		return;
	}

	if (infor->getAccountState() != EACCNTSTT_CN_WAIT_CLIENT) {
		return;
	}
	m_accountInforMgr.destroyByCNSessionID(a_sessionID);
}

void CAccountLoginCNInforMgr::checkCNInitPlayer(GFLib::SAccountKey& a_accountKey, ELoginResult a_state)
{
	SAccountLoginCNInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		return;
	}
	if (infor->getAccountState() != EACCNTSTT_CN_PLAYER_INIT) {
		return;
	}
	if (a_state != ELOGINRESULT_SUCCESS) {
		return;
	}
	infor->m_stateInitPlayer |= GSLIB_LOGINSYSTEM_STATE_CN;

	if (infor->m_stateInitPlayer == GSLIB_LOGINSYSTEM_STATE_XX) {
		_finishInitPlayer(infor);
	}
}

bool CAccountLoginCNInforMgr::checkUniqueID(BSLib::uint32 a_id)
{
	return m_accountInforMgr.getObjectByCNSessionID(a_id) != NULL;
}

bool CAccountLoginCNInforMgr::_notifyCreatePlayer(SAccountLoginCNInfor* a_infor)
{
	if (!_createPlayer(a_infor)) {
		return false;
	}

	a_infor->m_stateCreatePlayerDB = 0;
	a_infor->m_stateCreatePlayerGM = 0;
	a_infor->m_stateCreatePlayerGT = 0;

	CMsgLoginSystemCN2DBReqCreatePlayer reqCreatePlayer2DB;
	reqCreatePlayer2DB.m_centerSessionID = a_infor->m_cnSessionID;
	reqCreatePlayer2DB.m_gateServerID = a_infor->m_gateServerID.getServerID();
	reqCreatePlayer2DB.m_gameServerID = a_infor->m_gameServerID.getServerID();
	reqCreatePlayer2DB.m_accountKey = a_infor->m_accountKey;
	reqCreatePlayer2DB.m_accountName = a_infor->m_accountName;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_dataServerID, reqCreatePlayer2DB);

	CMsgLoginSystemCN2GMReqCreatePlayer reqCreatePlayer2GM;
	reqCreatePlayer2GM.m_centerSessionID = a_infor->m_cnSessionID;
	reqCreatePlayer2GM.m_gateServerID = a_infor->m_gateServerID.getServerID();
	reqCreatePlayer2GM.m_dataServerID = m_dataServerID.getServerID();
	reqCreatePlayer2GM.m_accountKey = a_infor->m_accountKey;
	reqCreatePlayer2GM.m_accountName = a_infor->m_accountName;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_gameServerID, reqCreatePlayer2GM);

	CMsgLoginSystemCN2GTReqCreatePlayer reqCreatePlayer2GT;
	reqCreatePlayer2GT.m_centerSessionID = a_infor->m_cnSessionID;
	reqCreatePlayer2GT.m_gameServerID = a_infor->m_gameServerID.getServerID();
	reqCreatePlayer2GT.m_dataServerID = m_dataServerID.getServerID();
	reqCreatePlayer2GT.m_accountKey = a_infor->m_accountKey;
	reqCreatePlayer2GT.m_gateSessionID = a_infor->m_gateSession;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_gateServerID, reqCreatePlayer2GT);

	return  true;
}

void CAccountLoginCNInforMgr::_notifyInitPlayer(SAccountLoginCNInfor* a_infor)
{
	a_infor->m_stateInitPlayer = 0;

	CMsgLoginSystemCN2DBReqInitPlayer reqInitPlayer2DB;
	reqInitPlayer2DB.m_centerSessionID = a_infor->m_cnSessionID;
	reqInitPlayer2DB.m_accountKey = a_infor->m_accountKey;
	if (!GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_dataServerID, reqInitPlayer2DB)) {
		_notifyExitByCreate(a_infor);
		return ;
	}
}

bool CAccountLoginCNInforMgr::_createPlayer(SAccountLoginCNInfor* a_infor)
{
	CNetPlayerCNMgr* netPlayerCNMgr = CNetPlayerCNMgr::getSingleton();
	if (netPlayerCNMgr == NULL) {
		return false;
	}
	CNetPlayerCN* playerCN = netPlayerCNMgr->createNetPlayerCN(a_infor->m_accountKey, a_infor->m_accountName);
	if (playerCN == NULL) {
		return false;
	}
	GFLib::CommonServer::CAccountPtr accountPtr = new GFLib::CommonServer::CAccount(a_infor->m_accountKey);
	if (accountPtr == NULL) {
		return false;
	}

	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "创建账号%s[AccountName=%s]", a_infor->m_accountKey.toLogString().c_str(), a_infor->m_accountName.c_str());

	playerCN->_setDataServerID(m_dataServerID);
	playerCN->_setGameServerID(a_infor->m_gameServerID);
	playerCN->_setGateServerID(a_infor->m_gateServerID);
	playerCN->_setAccountPtr(accountPtr);
	accountPtr->setTransferMsgCB(playerCN);
	GFLib::CommonServer::CAccountMgr::singleton().addAccount(accountPtr);

	return true;
}

bool CAccountLoginCNInforMgr::_initPlayer(SAccountLoginCNInfor* a_infor)
{
	CNetPlayerCNMgr* netPlayerCNMgr = CNetPlayerCNMgr::getSingleton();
	if (netPlayerCNMgr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerCNMgr失败[Account=%s]", a_infor->m_accountName.c_str());
		return false;
	}
	CNetPlayerCN* playerCN = netPlayerCNMgr->getNetPlayerCN(a_infor->m_accountKey);
	if (playerCN == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerCN失败[Account=%s]", a_infor->m_accountName.c_str());
		return false;
	}
	a_infor->m_isInit = true;

	playerCN->_initMsg();
	playerCN->_cbInitPlayer();
	
	return true;
}

void CAccountLoginCNInforMgr::_finishInitPlayer(SAccountLoginCNInfor* a_infor)
{
	a_infor->setAccountState(EACCNTSTT_CN_OK);

	CMsgLoginSystemCN2GTAckAccountLogin ackAccountLogin;
	ackAccountLogin.m_state = ELOGINRESULT_SUCCESS;
	ackAccountLogin.m_gateSession = a_infor->m_gateSession;
	ackAccountLogin.m_accountKey = a_infor->m_accountKey;

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_gateServerID, ackAccountLogin);
}

void CAccountLoginCNInforMgr::_notifyExitByCreate(SAccountLoginCNInfor* a_infor)
{
	if (a_infor->m_stateCreatePlayerDB == 0 || a_infor->m_stateCreatePlayerGM == 0 || a_infor->m_stateCreatePlayerGT == 0) {
		return;
	}
	BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "异常_notifyExitByCreate[Account=%s]", a_infor->m_accountName.c_str());

	CMsgLoginSystemCN2GTAckAccountLogin ackAccountLogin;
	ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
	ackAccountLogin.m_gateSession = a_infor->m_gateSession;
	ackAccountLogin.m_accountKey = a_infor->m_accountKey;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_gateServerID, ackAccountLogin);

	//a_infor->m_stateFinal = 0;
	
	_notifyExit(a_infor);
}

void CAccountLoginCNInforMgr::_notifyExitByInit(SAccountLoginCNInfor* a_infor)
{
	BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "异常_notifyExitByInit[Account=%s]", a_infor->m_accountName.c_str());

	CMsgLoginSystemCN2GTAckAccountLogin ackAccountLogin;
	ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
	ackAccountLogin.m_gateSession = a_infor->m_gateSession;
	ackAccountLogin.m_accountKey = a_infor->m_accountKey;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_gateServerID, ackAccountLogin);

	a_infor->m_stateFinal = 0X0F;

	if ((a_infor->m_stateInitPlayer & GSLIB_LOGINSYSTEM_STATE_DB) || (a_infor->m_stateInitPlayer & GSLIB_LOGINSYSTEM_ERROR_STATE_DB)) {
		if (a_infor->m_stateInitPlayer & GSLIB_LOGINSYSTEM_STATE_DB) {
			a_infor->m_stateFinal &= (~(GSLIB_LOGINSYSTEM_STATE_DB | GSLIB_LOGINSYSTEM_STATE_GM));
		} else {
			a_infor->m_stateFinal &= (~GSLIB_LOGINSYSTEM_STATE_DB);
		}
	}
	if ((a_infor->m_stateInitPlayer & GSLIB_LOGINSYSTEM_STATE_GT) || (a_infor->m_stateInitPlayer & GSLIB_LOGINSYSTEM_ERROR_STATE_GT)) {
		a_infor->m_stateFinal &= (~GSLIB_LOGINSYSTEM_STATE_GT);
	}
	if ((a_infor->m_stateInitPlayer & GSLIB_LOGINSYSTEM_STATE_CN) || (a_infor->m_stateInitPlayer & GSLIB_LOGINSYSTEM_ERROR_STATE_CN)) {
		a_infor->m_stateFinal &= (~GSLIB_LOGINSYSTEM_STATE_CN);
	}
	if ((a_infor->m_stateInitPlayer & GSLIB_LOGINSYSTEM_STATE_GM) || (a_infor->m_stateInitPlayer & GSLIB_LOGINSYSTEM_ERROR_STATE_GM)) {
		a_infor->m_stateFinal &= (~GSLIB_LOGINSYSTEM_STATE_GM);
	}

	_notifyExit(a_infor);	

}

void CAccountLoginCNInforMgr::_notifyOffline(SAccountLoginCNInfor* a_infor)
{
	CNetPlayerCNMgr* netPlayerCNMgr = CNetPlayerCNMgr::getSingleton();
	if (netPlayerCNMgr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerCNMgr失败[Account=%s]", a_infor->m_accountName.c_str());
		return ;
	}
	CNetPlayerCN* playerCN = netPlayerCNMgr->getNetPlayerCN(a_infor->m_accountKey);
	if (playerCN == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerCN失败[Account=%s]", a_infor->m_accountName.c_str());
		return ;
	}
	a_infor->m_stateOffline = GSLIB_LOGINSYSTEM_STATE_CN;

	playerCN->_cbPlayerOffline();

	CMsgLoginSystemCN2GTReqAccountOffline reqAccountOfflineGT;
	reqAccountOfflineGT.m_accountKey = a_infor->m_accountKey;
	reqAccountOfflineGT.m_gateSessionID = a_infor->m_gateSession;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_gateServerID, reqAccountOfflineGT);

	CMsgLoginSystemCN2GMReqAccountOffline reqAccountOfflineGM;
	reqAccountOfflineGM.m_accountKey = a_infor->m_accountKey;
	reqAccountOfflineGM.m_centerSessionID = a_infor->m_cnSessionID;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_gameServerID, reqAccountOfflineGM);

	CMsgLoginSystemCN2DBReqAccountOffline reqAccountOfflineDB;
	reqAccountOfflineDB.m_accountKey = a_infor->m_accountKey;
	reqAccountOfflineDB.m_centerSessionID = a_infor->m_cnSessionID;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_dataServerID, reqAccountOfflineDB);
}

void CAccountLoginCNInforMgr::_finishOffline(SAccountLoginCNInfor* a_infor)
{
	if (a_infor->getAccountState() == EACCNTSTT_CN_PLAYER_OFFLINE_BREAK) {
		a_infor->setAccountState(EACCNTSTT_CN_OFFLINE_WAIT_CLIENT);

		CMsgLoginSystemCN2GTAckAccountBreak ackAccountBreak;
		ackAccountBreak.m_gateSessionID = a_infor->m_gateSession;
		ackAccountBreak.m_accountKey = a_infor->m_accountKey;
		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_gateServerID, ackAccountBreak);

		if (a_infor->m_timeHandleOffline != BSLib::Utility::INVALID_TIMER) {
			LoginSystem::CN::CLoginSystemCN::singleton().delTimeoutAccountOnline(a_infor->m_timeHandleOffline);
		}
		
		BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "离线设置退出触发器器[SessionID=%d]%s[Account=%s]", a_infor->m_cnSessionID, a_infor->m_accountKey.toLogString().c_str(), a_infor->m_accountName.c_str());

		a_infor->m_timeHandleOffline = LoginSystem::CN::CLoginSystemCN::singleton().addTimeoutAccountOnline(a_infor->m_cnSessionID);
		return ;
	}
	if (a_infor->getAccountState() == EACCNTSTT_CN_PLAYER_OFFLINE_KICK) {
		a_infor->setAccountState(EACCNTSTT_CN_OFFLINE_WAIT_CLIENT);

		BSLib::Network::CSockAddr&  connectAddr = CGateInforMgr::singleton().getGateConnectAddr(a_infor->m_gateServerID);

		CMsgLoginSystemCN2LGAckAccountLogin ackAccountLogin;
		ackAccountLogin.m_loginSession = a_infor->m_loginSession;
		ackAccountLogin.m_state = ELOGINRESULT_SUCCESS;
		ackAccountLogin.m_gateServerIP = connectAddr.getIP();
		ackAccountLogin.m_gateServerPort = connectAddr.getPort();
		ackAccountLogin.m_gateKey = a_infor->m_gateKey;
		ackAccountLogin.m_gateSession = a_infor->m_gateSession;
		ackAccountLogin. m_accountKey = a_infor->m_accountKey;

		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_loginServerID, ackAccountLogin);

//		if (a_infor->m_timeHandleOffline != BSLib::Utility::INVALID_TIMER) {
//			LoginSystem::CN::CLoginSystemCN::singleton().delTimeoutAccountOnline(a_infor->m_timeHandleOffline);
//		}
//		a_infor->m_timeHandleOffline = LoginSystem::CN::CLoginSystemCN::singleton().addTimeoutAccountOnline(a_infor->m_cnSessionID);

		return ;
	}
	BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "异常_finishOffline[Account=%s]", a_infor->m_accountName.c_str());
}

void CAccountLoginCNInforMgr::_notifyOnline(SAccountLoginCNInfor* a_infor)
{
	CNetPlayerCNMgr* netPlayerCNMgr = CNetPlayerCNMgr::getSingleton();
	if (netPlayerCNMgr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerCNMgr失败[Account=%s]", a_infor->m_accountName.c_str());
		return ;
	}
	CNetPlayerCN* playerCN = netPlayerCNMgr->getNetPlayerCN(a_infor->m_accountKey);
	if (playerCN == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerCN失败[Account=%s]", a_infor->m_accountName.c_str());
		return ;
	}
	a_infor->m_stateOnline = GSLIB_LOGINSYSTEM_STATE_CN;
	a_infor->setAccountState(EACCNTSTT_CN_PLAYER_ONLINE);


	if (a_infor->m_timeHandleOffline != BSLib::Utility::INVALID_TIMER) {
		BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "上线，清除触发器器[SessionID=%d]%s[Account=%s]", a_infor->m_cnSessionID, a_infor->m_accountKey.toLogString().c_str(), a_infor->m_accountName.c_str());

		LoginSystem::CN::CLoginSystemCN::singleton().delTimeoutAccountOnline(a_infor->m_timeHandleOffline);
		a_infor->m_timeHandleOffline =  BSLib::Utility::INVALID_TIMER;
	}

	playerCN->_cbPlayerOnline();

	CMsgLoginSystemCN2GTReqAccountOnline reqAccountOnlineGT;
	reqAccountOnlineGT.m_accountKey = a_infor->m_accountKey;
	reqAccountOnlineGT.m_gateSessionID = a_infor->m_gateSession;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_gateServerID, reqAccountOnlineGT);
}

void CAccountLoginCNInforMgr::_finishOnline(SAccountLoginCNInfor* a_infor)
{
	if (a_infor->getAccountState() != EACCNTSTT_CN_PLAYER_ONLINE) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "异常_finishOnline[Account=%s]", a_infor->m_accountName.c_str());
		return ;
	}
	a_infor->setAccountState(EACCNTSTT_CN_OK);

	CMsgLoginSystemCN2GTAckAccountLogin ackAccountLogin;
	ackAccountLogin.m_state = ELOGINRESULT_SUCCESS;
	ackAccountLogin.m_gateSession = a_infor->m_gateSession;
	ackAccountLogin.m_accountKey = a_infor->m_accountKey;

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_gateServerID, ackAccountLogin);
}

void CAccountLoginCNInforMgr::_notifyFinal(SAccountLoginCNInfor* a_infor)
{
	CNetPlayerCNMgr* netPlayerCNMgr = CNetPlayerCNMgr::getSingleton();
	if (netPlayerCNMgr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerCNMgr失败[Account=%s]", a_infor->m_accountName.c_str());
		return ;
	}
	CNetPlayerCN* playerCN = netPlayerCNMgr->getNetPlayerCN(a_infor->m_accountKey);
	if (playerCN == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerCN失败[Account=%s]", a_infor->m_accountName.c_str());
		return ;
	}
	a_infor->m_stateFinal = GSLIB_LOGINSYSTEM_STATE_CN;

	playerCN->_cbFinalPlayer();

	CMsgLoginSystemCN2GTReqAccountFinal reqAccountFinalGT;
	reqAccountFinalGT.m_centerSessionID = a_infor->m_cnSessionID;
	reqAccountFinalGT.m_accountKey = a_infor->m_accountKey;
	reqAccountFinalGT.m_gateSessionID = a_infor->m_gateSession;
	reqAccountFinalGT.m_dataServerID = m_dataServerID.getServerID();
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_gateServerID, reqAccountFinalGT);

	CMsgLoginSystemCN2GMReqAccountFinal reqAccountFinalGM;
	reqAccountFinalGM.m_accountKey = a_infor->m_accountKey;
	reqAccountFinalGM.m_centerSessionID = a_infor->m_cnSessionID;
	reqAccountFinalGM.m_dataServerID = m_dataServerID.getServerID();
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_gameServerID, reqAccountFinalGM);

	CMsgLoginSystemCN2DBReqAccountFinal reqAccountFinalDB;
	reqAccountFinalDB.m_accountKey = a_infor->m_accountKey;
	reqAccountFinalDB.m_centerSessionID = a_infor->m_cnSessionID;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_dataServerID, reqAccountFinalDB);
}

void CAccountLoginCNInforMgr::_finishFinal(SAccountLoginCNInfor* a_infor)
{
	if (a_infor->getAccountState() != EACCNTSTT_CN_ACCOUNT_FINAL) {
		GFLib::CommonServer::CAccountMgr::singleton().delAccount(a_infor->m_accountKey);
		m_accountInforMgr.destroyByAccountKey(a_infor->m_accountKey);
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "异常_finishOnline[Account=%s]", a_infor->m_accountName.c_str());
		return ;
	}
	CNetPlayerCNMgr* netPlayerCNMgr = CNetPlayerCNMgr::getSingleton();
	if (netPlayerCNMgr == NULL) {
		GFLib::CommonServer::CAccountMgr::singleton().delAccount(a_infor->m_accountKey);
		m_accountInforMgr.destroyByAccountKey(a_infor->m_accountKey);
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerCNMgr失败[Account=%s]", a_infor->m_accountName.c_str());
		return ;
	}

	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "释放账号%s[AccountName=%s]", a_infor->m_accountKey.toLogString().c_str(), a_infor->m_accountName.c_str());

	CGateInforMgr::singleton().decreaseOnlineAccountFromGateServer(a_infor->m_gateServerID);

	netPlayerCNMgr->removeNetPlayerCN(a_infor->m_accountKey);
	GFLib::CommonServer::CAccountMgr::singleton().delAccount(a_infor->m_accountKey);
	m_accountInforMgr.destroyByAccountKey(a_infor->m_accountKey);
}

void CAccountLoginCNInforMgr::_notifyExit(SAccountLoginCNInfor* a_infor)
{
	if (a_infor->getAccountState() == EACCNTSTT_CN_ACCOUNT_FINAL) {
		if (a_infor->m_stateFinal == GSLIB_LOGINSYSTEM_STATE_XX) {
			_finishFinal(a_infor);
		}
		return;
	}

	a_infor->setAccountState(EACCNTSTT_CN_ACCOUNT_FINAL);

	if ((a_infor->m_stateFinal & GSLIB_LOGINSYSTEM_STATE_CN) == 0) {
		CNetPlayerCNMgr* netPlayerCNMgr = CNetPlayerCNMgr::getSingleton();
		if (netPlayerCNMgr == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerCNMgr失败[Account=%s]", a_infor->m_accountName.c_str());
			return ;
		}
		CNetPlayerCN* playerCN = netPlayerCNMgr->getNetPlayerCN(a_infor->m_accountKey);
		if (playerCN == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerCN失败[Account=%s]", a_infor->m_accountName.c_str());
			return ;
		}
		a_infor->m_stateFinal |= GSLIB_LOGINSYSTEM_STATE_CN;

		if (a_infor->m_isInit) {
			playerCN->_cbFinalPlayer();
		}
	}

	if ((a_infor->m_stateFinal & GSLIB_LOGINSYSTEM_STATE_GT) == 0) {
		CMsgLoginSystemCN2GTReqAccountFinal reqAccountFinalGT;
		reqAccountFinalGT.m_centerSessionID = a_infor->m_cnSessionID;
		reqAccountFinalGT.m_accountKey = a_infor->m_accountKey;
		reqAccountFinalGT.m_gateSessionID = a_infor->m_gateSession;
		reqAccountFinalGT.m_dataServerID = m_dataServerID.getServerID();
		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_gateServerID, reqAccountFinalGT);
	}
	
	if ((a_infor->m_stateFinal & GSLIB_LOGINSYSTEM_STATE_GM) == 0) {
		CMsgLoginSystemCN2GMReqAccountFinal reqAccountFinalGM;
		reqAccountFinalGM.m_accountKey = a_infor->m_accountKey;
		reqAccountFinalGM.m_centerSessionID = a_infor->m_cnSessionID;
		reqAccountFinalGM.m_dataServerID = m_dataServerID.getServerID();
		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_gameServerID, reqAccountFinalGM);
	}
	
	if ((a_infor->m_stateFinal & GSLIB_LOGINSYSTEM_STATE_DB) == 0) {
		CMsgLoginSystemCN2DBReqAccountFinal reqAccountFinalDB;
		reqAccountFinalDB.m_accountKey = a_infor->m_accountKey;
		reqAccountFinalDB.m_centerSessionID = a_infor->m_cnSessionID;
		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_dataServerID, reqAccountFinalDB);
	}

	if (a_infor->m_stateFinal == GSLIB_LOGINSYSTEM_STATE_XX) {
		_finishFinal(a_infor);
	}
}

}//CN

}//LoginSystem

}//GSLib

