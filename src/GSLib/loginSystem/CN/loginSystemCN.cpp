#include <GSLib/tracer.h>
#include <GSLib/loginSystem/CN/loginSystemCN.h>
#include "CN/gateInforMgr.h"
#include "CN/gameInforMgr.h"
#include "CN/accountLoginCNInforMgr.h"

#define TIMEOUT_MAX_ACCOUNT_OFFLINE_CN (15 * 60 * 1000)

namespace GSLib
{

namespace LoginSystem
{	

namespace CN
{

BSLIB_SINGLETON_DEFINE(CLoginSystemCN);

CLoginSystemCN::CLoginSystemCN()
{
	;
}

CLoginSystemCN::~CLoginSystemCN()
{
	;
}

BSLib::Utility::TimerHandle CLoginSystemCN::addTimeoutAccountOnline(BSLib::uint32& a_sessionID)
{
	BSLib::Utility::CTimerServer* timerServer = GSLib::DBSystem::CDBCommonSystem::_getTimerServer();
	if (timerServer == NULL) {
		return BSLib::Utility::INVALID_TIMER;
	}
	BSLib::Utility::TimerHandle timeHandle = timerServer->addTimer(&CLoginSystemCN::_cbTimerAccountOfflineTimeout, this, a_sessionID, 0, TIMEOUT_MAX_ACCOUNT_OFFLINE_CN, TIMEOUT_MAX_ACCOUNT_OFFLINE_CN);
	return timeHandle;
}

void CLoginSystemCN::delTimeoutAccountOnline(BSLib::Utility::TimerHandle& a_timeHandle)
{
	BSLib::Utility::CTimerServer* timerServer = GSLib::DBSystem::CDBCommonSystem::_getTimerServer();
	if (timerServer == NULL) {
		return ;
	}
	timerServer->delTimer(a_timeHandle);
}

bool CLoginSystemCN::_init()
{
	CGateInforMgr::singleton().init();
	CGameInforMgr::singleton().init();

	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CLoginSystemCN::_final()
{
	CGateInforMgr::singleton().final();
	CGameInforMgr::singleton().final();

	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CLoginSystemCN::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CLoginSystemCN::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemLG2CNReqAccountLogin, &BSLib::Framework::CreateCMessage<CMsgLoginSystemLG2CNReqAccountLogin>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemLG2CNReqAccountLogin, &CLoginSystemCN::_onMsgLoginSystemLG2CNReqAccountLogin, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGT2CNAckAccountLogin, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGT2CNAckAccountLogin>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGT2CNAckAccountLogin, &CLoginSystemCN::_onMsgLoginSystemGT2CNAckAccountLogin, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGT2CNReqAccountLogin, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGT2CNReqAccountLogin>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGT2CNReqAccountLogin, &CLoginSystemCN::_onMsgLoginSystemGT2CNReqAccountLogin, this);

	//创建Player
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGM2CNAckCreatePlayer, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGM2CNAckCreatePlayer>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGM2CNAckCreatePlayer, &CLoginSystemCN::_onMsgLoginSystemGM2CNAckCreatePlayer, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGT2CNAckCreatePlayer, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGT2CNAckCreatePlayer>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGT2CNAckCreatePlayer, &CLoginSystemCN::_onMsgLoginSystemGT2CNAckCreatePlayer, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemDB2CNAckCreatePlayer, &BSLib::Framework::CreateCMessage<CMsgLoginSystemDB2CNAckCreatePlayer>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemDB2CNAckCreatePlayer, &CLoginSystemCN::_onMsgLoginSystemDB2CNAckCreatePlayer, this);

	//初始化
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGM2CNNtfInitPlayer, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGM2CNNtfInitPlayer>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGM2CNNtfInitPlayer, &CLoginSystemCN::_onMsgLoginSystemGM2CNNtfInitPlayer, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGT2CNAckInitPlayer, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGT2CNAckInitPlayer>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGT2CNAckInitPlayer, &CLoginSystemCN::_onMsgLoginSystemGT2CNAckInitPlayer, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemDB2CNAckInitPlayer, &BSLib::Framework::CreateCMessage<CMsgLoginSystemDB2CNAckInitPlayer>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemDB2CNAckInitPlayer, &CLoginSystemCN::_onMsgLoginSystemDB2CNAckInitPlayer, this);

	//////////////////////////////////////////////////////////////////////////
	//离线协议
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGT2CNReqAccountBreak, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGT2CNReqAccountBreak>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGT2CNReqAccountBreak, &CLoginSystemCN::_onMsgLoginSystemGT2CNReqAccountBreak, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGT2CNAckAccountOffline, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGT2CNAckAccountOffline>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGT2CNAckAccountOffline, &CLoginSystemCN::_onMsgLoginSystemGT2CNAckAccountOffline, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGM2CNAckAccountOffline, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGM2CNAckAccountOffline>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGM2CNAckAccountOffline, &CLoginSystemCN::_onMsgLoginSystemGM2CNAckAccountOffline, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemDB2CNAckAccountOffline, &BSLib::Framework::CreateCMessage<CMsgLoginSystemDB2CNAckAccountOffline>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemDB2CNAckAccountOffline, &CLoginSystemCN::_onMsgLoginSystemDB2CNAckAccountOffline, this);

	//上线协议
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGT2CNAckAccountOnline, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGT2CNAckAccountOnline>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGT2CNAckAccountOnline, &CLoginSystemCN::_onMsgLoginSystemGT2CNAckAccountOnline, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGM2CNAckAccountOnline, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGM2CNAckAccountOnline>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGM2CNAckAccountOnline, &CLoginSystemCN::_onMsgLoginSystemGM2CNAckAccountOnline, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemDB2CNAckAccountOnline, &BSLib::Framework::CreateCMessage<CMsgLoginSystemDB2CNAckAccountOnline>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemDB2CNAckAccountOnline, &CLoginSystemCN::_onMsgLoginSystemDB2CNAckAccountOnline, this);

	//退出协议
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGT2CNNtfAccountQuit, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGT2CNNtfAccountQuit>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGT2CNNtfAccountQuit, &CLoginSystemCN::_onMsgLoginSystemGT2CNNtfAccountQuit, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGM2CNNtfAccountQuit, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGM2CNNtfAccountQuit>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGM2CNNtfAccountQuit, &CLoginSystemCN::_onMsgLoginSystemGM2CNNtfAccountQuit, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemDB2CNNtfAccountQuit, &BSLib::Framework::CreateCMessage<CMsgLoginSystemDB2CNNtfAccountQuit>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemDB2CNNtfAccountQuit, &CLoginSystemCN::_onMsgLoginSystemDB2CNNtfAccountQuit, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGT2CNAckAccountFinal, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGT2CNAckAccountFinal>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGT2CNAckAccountFinal, &CLoginSystemCN::_onMsgLoginSystemGT2CNAckAccountFinal, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGM2CNAckAccountFinal, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGM2CNAckAccountFinal>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGM2CNAckAccountFinal, &CLoginSystemCN::_onMsgLoginSystemGM2CNAckAccountFinal, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemDB2CNAckAccountFinal, &BSLib::Framework::CreateCMessage<CMsgLoginSystemDB2CNAckAccountFinal>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemDB2CNAckAccountFinal, &CLoginSystemCN::_onMsgLoginSystemDB2CNAckAccountFinal, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGT2CNNtfAccountTimeout, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGT2CNNtfAccountTimeout>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGT2CNNtfAccountTimeout, &CLoginSystemCN::_onMsgLoginSystemGT2CNNtfAccountTimeout, this);

	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CLoginSystemCN::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CLoginSystemCN::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	if (a_serverID.getServerType() == SRVTYPE_GATESERVER) {
		CGateInforMgr::singleton().gateServerEnter(a_serverID);
		return ;
	}else if (a_serverID.getServerType() == SRVTYPE_GAMESERVER){
		CGameInforMgr::singleton().gameServerEnter(a_serverID);
		return ;
	} else if (a_serverID.getServerType() == SRVTYPE_DATASERVER){
		CAccountLoginCNInforMgr::singleton().setDataServerID(a_serverID);
		return ;
	}
	
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CLoginSystemCN::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	if (a_serverID.getServerType() == SRVTYPE_GATESERVER) {
		CAccountLoginCNInforMgr::singleton().gateServerLeave(a_serverID);
		CGateInforMgr::singleton().gateServerLeave(a_serverID);
		return ;
	} else if (a_serverID.getServerType() == SRVTYPE_GAMESERVER){
		CAccountLoginCNInforMgr::singleton().gameServerLeave(a_serverID);
		CGameInforMgr::singleton().gameServerLeave(a_serverID);
		return ;
	} else if (a_serverID.getServerType() == SRVTYPE_DATASERVER){
		CAccountLoginCNInforMgr::singleton().dataServerLeave(a_serverID);
		CAccountLoginCNInforMgr::singleton().setDataServerID(GFLib::INVALID_SERVERID);
		return ;
	}
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

void CLoginSystemCN::_onMsgLoginSystemLG2CNReqAccountLogin(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* netMsgLable = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgLoginSystemLG2CNReqAccountLogin* reqAccountLogin = (CMsgLoginSystemLG2CNReqAccountLogin*)a_msg;

	CMsgLoginSystemCN2LGAckAccountLogin ackAccountLogin;
	ackAccountLogin.m_loginSession = reqAccountLogin->m_loginSession;
	GFLib::SServerID gateServerID;
	BSLib::uint32 sessionID = 0; 
	EAccountStateCN state = CAccountLoginCNInforMgr::singleton().checkLG2CNReqAccountLogin(reqAccountLogin->m_accountKey, gateServerID);
	switch (state) {
	case EACCNTSTT_CN_NULL:// 账号不存在,创建账号
		{
			if (!CGateInforMgr::singleton().increaseAccountToGateServer(gateServerID)) {
				ackAccountLogin.m_state = ELOGINRESULT_ZONEID_STOP;
				GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(netMsgLable->m_serverIDFrome, ackAccountLogin);
				BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取网关失败[AccountName=%s]", reqAccountLogin->m_accountName.c_str());
				return;
			}
			CGateInforMgr::singleton().increaseWaitAccountFromGateServer(gateServerID);

			if (!CAccountLoginCNInforMgr::singleton().registerLG2CNReqAccountLogin(sessionID, netMsgLable->m_serverIDFrome, gateServerID, *reqAccountLogin, EACCNTSTT_CN_WAIT_GATE)) {
				ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
				GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(netMsgLable->m_serverIDFrome, ackAccountLogin);
				CGateInforMgr::singleton().decreaseWaitAccountFromGateServer(gateServerID);
				BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "保存登陆信息失败[AccountName=%s]", reqAccountLogin->m_accountName.c_str());
				return;
			}

			BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "注册网关[AccountName=%s][GateServerID=%s]", reqAccountLogin->m_accountName.c_str(), gateServerID.toString().c_str());
		}
		break;
	case EACCNTSTT_CN_ACCOUNT_FINAL:	//锁定账号，账号正在退出
	case EACCNTSTT_CN_PLAYER_OFFLINE_BREAK://锁定账号，账号正在离线
		{
			ackAccountLogin.m_state = ELOGINRESULT_ACCOUNT_EXIT;
			GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(netMsgLable->m_serverIDFrome, ackAccountLogin);
			BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "账号正在退出[AccountName=%s]", reqAccountLogin->m_accountName.c_str());
			return;
		}
		break;

	case EACCNTSTT_CN_WAIT_CLIENT:// 等待账号登陆
		{
			BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "踢下原登陆账号[AccountName=%s]", reqAccountLogin->m_accountName.c_str());

			if (!CAccountLoginCNInforMgr::singleton().registerLG2CNReqAccountLogin(sessionID, netMsgLable->m_serverIDFrome, gateServerID, *reqAccountLogin, EACCNTSTT_CN_WAIT_GATE)) {
				ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
				GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(netMsgLable->m_serverIDFrome, ackAccountLogin);
				//CGateInforMgr::singleton().decreaseWaitAccountFromGateServer(gateServerID);
				BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "保存登陆信息失败[AccountName=%s]", reqAccountLogin->m_accountName.c_str());
				return;
			}

			BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "注册网关[AccountName=%s][GateServerID=%s]", reqAccountLogin->m_accountName.c_str(), gateServerID.toString().c_str());
		}
		break;
	case EACCNTSTT_CN_OK:// 账号在线
		{
			BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "要求踢下在线账号[AccountName=%s]", reqAccountLogin->m_accountName.c_str());

			if (!CAccountLoginCNInforMgr::singleton().registerLG2CNReqAccountLogin(sessionID, netMsgLable->m_serverIDFrome, gateServerID, *reqAccountLogin, EACCNTSTT_CN_KICK_ACCOUNT)) {
				ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
				GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(netMsgLable->m_serverIDFrome, ackAccountLogin);
				//CGateInforMgr::singleton().decreaseWaitAccountFromGateServer(gateServerID);
				BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "保存登陆信息失败[AccountName=%s]", reqAccountLogin->m_accountName.c_str());
				return;
			}

			BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "玩家上线操作[AccountName=%s][GateServerID=%s]", reqAccountLogin->m_accountName.c_str(), gateServerID.toString().c_str());
		}
		break;

	case EACCNTSTT_CN_OFFLINE_WAIT_CLIENT:// 账号离线，等待账号上线
		{
			BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "踢下原登陆账号[AccountName=%s]", reqAccountLogin->m_accountName.c_str());

			if (!CAccountLoginCNInforMgr::singleton().registerLG2CNReqAccountLogin(sessionID, netMsgLable->m_serverIDFrome, gateServerID, *reqAccountLogin, EACCNTSTT_CN_OFFLINE_WAIT_GATE)) {
				ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
				GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(netMsgLable->m_serverIDFrome, ackAccountLogin);
				//CGateInforMgr::singleton().decreaseWaitAccountFromGateServer(gateServerID);
				BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "保存登陆信息失败[AccountName=%s]", reqAccountLogin->m_accountName.c_str());
				return;
			}

			BSLIB_LOG_INFOR(ETT_GSLIB_LOGINSYSTEM, "玩家上线操作[AccountName=%s][GateServerID=%s]", reqAccountLogin->m_accountName.c_str(), gateServerID.toString().c_str());
		}
		break;
	case EACCNTSTT_CN_WAIT_GATE:	//锁定账号，账号正在等待Gate回应
	case EACCNTSTT_CN_PLAYER_INIT:	//锁定账号，账号正在初始化
	case EACCNTSTT_CN_KICK_ACCOUNT: //锁定账号，账号正在踢人下线
	case EACCNTSTT_CN_PLAYER_OFFLINE_KICK:	//锁定账号，账号正在踢人下线
	case EACCNTSTT_CN_PLAYER_ONLINE:		//锁定账号，账号正在上线
	case EACCNTSTT_CN_OFFLINE_WAIT_GATE:	//锁定账号，账号正在等待Gate回应
	default:
		{
			ackAccountLogin.m_state = ELOGINRESULT_ACCOUNT_LOGIN;
			GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(netMsgLable->m_serverIDFrome, ackAccountLogin);
			BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "账号正在登陆[AccountName=%s]", reqAccountLogin->m_accountName.c_str());
			return;
		}
		break;
	}
}

void CLoginSystemCN::_onMsgLoginSystemGT2CNAckAccountLogin(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGT2CNAckAccountLogin* ackAccountLogin = (CMsgLoginSystemGT2CNAckAccountLogin*)a_msg;
	CAccountLoginCNInforMgr::singleton().checkGT2CNAckAccountLogin(*ackAccountLogin);
}

void CLoginSystemCN::_onMsgLoginSystemGT2CNReqAccountLogin(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* netMsgLable = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgLoginSystemGT2CNReqAccountLogin* reqAccountLogin = (CMsgLoginSystemGT2CNReqAccountLogin*)a_msg;

	CMsgLoginSystemCN2GTAckAccountLogin ackAccountLogin;
	ackAccountLogin.m_accountKey = reqAccountLogin->m_accountKey;
	ackAccountLogin.m_gateSession = reqAccountLogin->m_gateSessionID;

	if (CAccountLoginCNInforMgr::singleton().checkGT2CNReqAccountLogin(*reqAccountLogin, ackAccountLogin)) {
		return ;
	}

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(netMsgLable->m_serverIDFrome, ackAccountLogin);
}

void CLoginSystemCN::_onMsgLoginSystemGM2CNAckCreatePlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGM2CNAckCreatePlayer* ackCreatePlayer = (CMsgLoginSystemGM2CNAckCreatePlayer*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkGM2CNAckCreatePlayer(ackCreatePlayer->m_centerSession, ackCreatePlayer->m_accountKey, ackCreatePlayer->m_state);
}

void CLoginSystemCN::_onMsgLoginSystemGT2CNAckCreatePlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGT2CNAckCreatePlayer* ackCreatePlayer = (CMsgLoginSystemGT2CNAckCreatePlayer*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkGT2CNAckCreatePlayer(ackCreatePlayer->m_centerSessionID, ackCreatePlayer->m_accountKey, ackCreatePlayer->m_state);
}

void CLoginSystemCN::_onMsgLoginSystemDB2CNAckCreatePlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemDB2CNAckCreatePlayer* ackCreatePlayer = (CMsgLoginSystemDB2CNAckCreatePlayer*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkDB2CNAckCreatePlayer(ackCreatePlayer->m_centerSession, ackCreatePlayer->m_accountKey, ackCreatePlayer->m_state);
}

void CLoginSystemCN::_onMsgLoginSystemGM2CNNtfInitPlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGM2CNNtfInitPlayer* ntfInitPlayer = (CMsgLoginSystemGM2CNNtfInitPlayer*)a_msg;
	
	CAccountLoginCNInforMgr::singleton().checkGM2CNNtfInitPlayer(ntfInitPlayer->m_centerSessionID, ntfInitPlayer->m_accountKey, ntfInitPlayer->m_state);
}

void CLoginSystemCN::_onMsgLoginSystemGT2CNAckInitPlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGT2CNAckInitPlayer* ackInitPlayer = (CMsgLoginSystemGT2CNAckInitPlayer*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkGT2CNAckInitPlayer(ackInitPlayer->m_centerSession, ackInitPlayer->m_accountKey, ackInitPlayer->m_state);
}

void CLoginSystemCN::_onMsgLoginSystemDB2CNAckInitPlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemDB2CNAckInitPlayer* ackInitPlayer = (CMsgLoginSystemDB2CNAckInitPlayer*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkDB2CNAckInitPlayer(ackInitPlayer->m_centerSessionID, ackInitPlayer->m_accountKey, ackInitPlayer->m_state);
}

void CLoginSystemCN::_onMsgLoginSystemGT2CNReqAccountBreak(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGT2CNReqAccountBreak* reqAccountBreak = (CMsgLoginSystemGT2CNReqAccountBreak*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkGT2CNReqAccountBreak(reqAccountBreak->m_centerSessionID, reqAccountBreak->m_accountKey);
}

void CLoginSystemCN::_onMsgLoginSystemGT2CNAckAccountOffline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGT2CNAckAccountOffline* ackAccountOffline = (CMsgLoginSystemGT2CNAckAccountOffline*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkGT2CNAckAccountOffline(ackAccountOffline->m_centerSessionID, ackAccountOffline->m_accountKey);
}

void CLoginSystemCN::_onMsgLoginSystemGM2CNAckAccountOffline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGM2CNAckAccountOffline* ackAccountOffline = (CMsgLoginSystemGM2CNAckAccountOffline*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkGM2CNAckAccountOffline(ackAccountOffline->m_centerSessionID, ackAccountOffline->m_accountKey);
}

void CLoginSystemCN::_onMsgLoginSystemDB2CNAckAccountOffline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemDB2CNAckAccountOffline* ackAccountOffline = (CMsgLoginSystemDB2CNAckAccountOffline*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkDB2CNAckAccountOffline(ackAccountOffline->m_centerSessionID, ackAccountOffline->m_accountKey);
}

void CLoginSystemCN::_onMsgLoginSystemGT2CNAckAccountOnline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGT2CNAckAccountOnline* ackAccountOffline = (CMsgLoginSystemGT2CNAckAccountOnline*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkGT2CNAckAccountOnline(ackAccountOffline->m_centerSessionID, ackAccountOffline->m_accountKey);
}

void CLoginSystemCN::_onMsgLoginSystemGM2CNAckAccountOnline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGM2CNAckAccountOnline* ackAccountOffline = (CMsgLoginSystemGM2CNAckAccountOnline*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkGM2CNAckAccountOnline(ackAccountOffline->m_centerSessionID, ackAccountOffline->m_accountKey);
}

void CLoginSystemCN::_onMsgLoginSystemDB2CNAckAccountOnline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemDB2CNAckAccountOnline* ackAccountOffline = (CMsgLoginSystemDB2CNAckAccountOnline*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkDB2CNAckAccountOnline(ackAccountOffline->m_centerSessionID, ackAccountOffline->m_accountKey);
}

void CLoginSystemCN::_onMsgLoginSystemGT2CNNtfAccountQuit(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGT2CNNtfAccountQuit* ntfAccountQuit = (CMsgLoginSystemGT2CNNtfAccountQuit*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkNtfAccountQuit(ntfAccountQuit->m_accountKey);
}

void CLoginSystemCN::_onMsgLoginSystemGM2CNNtfAccountQuit(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGM2CNNtfAccountQuit* ntfAccountQuit = (CMsgLoginSystemGM2CNNtfAccountQuit*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkNtfAccountQuit(ntfAccountQuit->m_accountKey);
}

void CLoginSystemCN::_onMsgLoginSystemDB2CNNtfAccountQuit(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemDB2CNNtfAccountQuit* ntfAccountQuit = (CMsgLoginSystemDB2CNNtfAccountQuit*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkNtfAccountQuit(ntfAccountQuit->m_accountKey);
}

void CLoginSystemCN::_onMsgLoginSystemGT2CNAckAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGT2CNAckAccountFinal* ackAccountFinal = (CMsgLoginSystemGT2CNAckAccountFinal*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkGT2CNAckAccountFinal(ackAccountFinal->m_centerSessionID, ackAccountFinal->m_accountKey);
}

void CLoginSystemCN::_onMsgLoginSystemGM2CNAckAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGM2CNAckAccountFinal* ackAccountFinal = (CMsgLoginSystemGM2CNAckAccountFinal*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkGM2CNAckAccountFinal(ackAccountFinal->m_centerSessionID, ackAccountFinal->m_accountKey);
}

void CLoginSystemCN::_onMsgLoginSystemDB2CNAckAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemDB2CNAckAccountFinal* ackAccountFinal = (CMsgLoginSystemDB2CNAckAccountFinal*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkDB2CNAckAccountFinal(ackAccountFinal->m_centerSessionID, ackAccountFinal->m_accountKey);
}

void CLoginSystemCN::_onMsgLoginSystemGT2CNNtfAccountTimeout(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGT2CNNtfAccountTimeout* ntfAccountTimeout = (CMsgLoginSystemGT2CNNtfAccountTimeout*)a_msg;

	CAccountLoginCNInforMgr::singleton().checkGT2CNNtfAccountTimeout(ntfAccountTimeout->m_centerSessionID, ntfAccountTimeout->m_accountKey);
}

// bool CLoginSystemCN::_cbTimerAccountLogin(BSLib::uint64 a_para1, void* a_para2)
// {
// 	BSLib::uint32 sesssionID = (BSLib::uint32)a_para1;
// 
// 	CAccountLoginCNInforMgr::singleton().timeoutAccountLoginInfor(sesssionID);
// 
// 	return false;
// }

bool CLoginSystemCN::_cbTimerAccountOfflineTimeout(BSLib::uint64 a_para1, void* a_para2)
{
	BSLib::uint32 sesssionID = (BSLib::uint32)a_para1;

	CAccountLoginCNInforMgr::singleton().timeoutAccountOffline(sesssionID);

	return false;
}

}//CN

}//LoginSystem

}//GSLib

