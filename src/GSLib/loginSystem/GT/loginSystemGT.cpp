//////////////////////////////////////////////////////////////////////
//	created:	2014/07/19
//	filename:	src\GSLib\loginSystem\GT\loginSystemGT.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/tracer.h>
#include <GSLib/loginSystem/GT/loginSystemGT.h>
#include "GT/accountLoginGTInforMgr.h"

#define TIMEOUT_MAX_ACCOUNT_LOGIN_GT (60 * 1000)

namespace GSLib
{

namespace LoginSystem
{

namespace GT
{

BSLIB_SINGLETON_DEFINE(CLoginSystemGT);

CLoginSystemGT::CLoginSystemGT()
{
	;
}

CLoginSystemGT::~CLoginSystemGT()
{
	;
}

bool CLoginSystemGT::verifyAccountLogin(GFLib::StubID a_stubID, std::string& a_gateLoginIP, CMsgLoginSystemGC2GTReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemGT2GCAckAccountLogin& a_ackAccountLogin, CVerifyAccountLoginCallBack* a_cbverifyAccountLogin)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	if (!CAccountLoginGTInforMgr::singleton().verifyAccountLogin(a_stubID, a_gateLoginIP, a_reqAccountLogin, a_ackAccountLogin, a_cbverifyAccountLogin)) {
		return false;
	}
	return true;
}

void CLoginSystemGT::terminateAccountLogin(GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_gateKey, BSLib::uint32 a_gateSession, GFLib::StubID a_stubID)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	CAccountLoginGTInforMgr::singleton().terminateAccountLoginInfor(a_accountKey, a_gateKey, a_gateSession, a_stubID);
}

bool CLoginSystemGT::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CLoginSystemGT::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CLoginSystemGT::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CLoginSystemGT::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	//登陆注册
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2GTReqAccountLogin, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2GTReqAccountLogin>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2GTReqAccountLogin, &CLoginSystemGT::_onMsgLoginSystemCN2GTReqAccountLogin, this);

	//登陆验证回应
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2GTAckAccountLogin, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2GTAckAccountLogin>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2GTAckAccountLogin, &CLoginSystemGT::_onMsgLoginSystemCN2GTAckAccountLogin, this);

	//创建Player
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2GTReqCreatePlayer, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2GTReqCreatePlayer>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2GTReqCreatePlayer, &CLoginSystemGT::_onMsgLoginSystemCN2GTReqCreatePlayer, this);

	//初始化
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2GTReqInitPlayer, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2GTReqInitPlayer>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2GTReqInitPlayer, &CLoginSystemGT::_onMsgLoginSystemCN2GTReqInitPlayer, this);

	//离线协议
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2GTAckAccountBreak, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2GTAckAccountBreak>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2GTAckAccountBreak, &CLoginSystemGT::_onMsgLoginSystemCN2GTAckAccountBreak, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2GTReqAccountOffline, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2GTReqAccountOffline>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2GTReqAccountOffline, &CLoginSystemGT::_onMsgLoginSystemCN2GTReqAccountOffline, this);

	//上线协议
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2GTReqAccountOnline, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2GTReqAccountOnline>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2GTReqAccountOnline, &CLoginSystemGT::_onMsgLoginSystemCN2GTReqAccountOnline, this);

	//退出协议
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2GTReqAccountFinal, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2GTReqAccountFinal>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2GTReqAccountFinal, &CLoginSystemGT::_onMsgLoginSystemCN2GTReqAccountFinal, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemXS2GTNtfBroadcastMsg, &BSLib::Framework::CreateCMessage<CMsgLoginSystemXS2GTNtfBroadcastMsg>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemXS2GTNtfBroadcastMsg, &CLoginSystemGT::_onMsgLoginSystemXS2GTNtfBroadcastMsg, this);

	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CLoginSystemGT::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CLoginSystemGT::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CLoginSystemGT::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	
	if (a_serverID.getServerType() == SRVTYPE_GATESERVER) {
		CAccountLoginGTInforMgr::singleton().dataServerLeave(a_serverID);
		return ;
	} else if (a_serverID.getServerType() == SRVTYPE_GAMESERVER){
		CAccountLoginGTInforMgr::singleton().gameServerLeave(a_serverID);
		return ;
	} else if (a_serverID.getServerType() == SRVTYPE_CENTERSERVER){
		CAccountLoginGTInforMgr::singleton().centerServerLeave(a_serverID);
		return ;
	}
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

void CLoginSystemGT::_onMsgLoginSystemCN2GTReqAccountLogin(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);

	GFLib::SNetMsgLabel* netMsgLable = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgLoginSystemCN2GTReqAccountLogin* reqAccountLogin = (CMsgLoginSystemCN2GTReqAccountLogin*)a_msg;

	CMsgLoginSystemGT2CNAckAccountLogin ackAccountLogin;
	BSLib::uint32 sessionID = 0;
	int res = CAccountLoginGTInforMgr::singleton().registerCN2GTReqAccountLogin(sessionID, netMsgLable->m_serverIDFrome, *reqAccountLogin, ackAccountLogin);

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(netMsgLable->m_serverIDFrome, ackAccountLogin);

	if (res > 0) {
		BSLib::Utility::CTimerServer* timerServer = GSLib::DBSystem::CDBCommonSystem::_getTimerServer();
		if (timerServer == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取TimerServer失败");
			CAccountLoginGTInforMgr::singleton().timeroutAccountLogin(sessionID);
			return;
		}
		BSLib::Utility::TimerHandle timeHandle = timerServer->addTimer(&CLoginSystemGT::_cbTimerAccountLogin, this, sessionID, NULL, TIMEOUT_MAX_ACCOUNT_LOGIN_GT, TIMEOUT_MAX_ACCOUNT_LOGIN_GT, 1);
		if (timeHandle == BSLib::Utility::INVALID_TIMER) {
			BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取TimerHandle失败");
			CAccountLoginGTInforMgr::singleton().timeroutAccountLogin(sessionID);
			return;
		}
	}
}

void CLoginSystemGT::_onMsgLoginSystemCN2GTAckAccountLogin(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	CMsgLoginSystemCN2GTAckAccountLogin* ackAccountLogin = (CMsgLoginSystemCN2GTAckAccountLogin*)a_msg;

	CAccountLoginGTInforMgr::singleton().checCN2GTAckAccountLogin(*ackAccountLogin);
}

void CLoginSystemGT::_onMsgLoginSystemCN2GTReqCreatePlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;
	
	CMsgLoginSystemCN2GTReqCreatePlayer* reqCreatePlayer = (CMsgLoginSystemCN2GTReqCreatePlayer*)a_msg;

	if (CAccountLoginGTInforMgr::singleton().checCN2GTReqCreatePlayer(*reqCreatePlayer)) {
		return ;
	}
	CMsgLoginSystemGT2CNAckCreatePlayer ackCreatePlayer;
	ackCreatePlayer.m_accountKey = reqCreatePlayer->m_accountKey;
	ackCreatePlayer.m_centerSessionID = reqCreatePlayer->m_centerSessionID;
	ackCreatePlayer.m_state = ELOGINRESULT_SERVER_ERROR;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrome, ackCreatePlayer);
}

void CLoginSystemGT::_onMsgLoginSystemCN2GTReqInitPlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;

	CMsgLoginSystemCN2GTReqInitPlayer* reqInitPlayer = (CMsgLoginSystemCN2GTReqInitPlayer*)a_msg;

	if (CAccountLoginGTInforMgr::singleton().checCN2GTReqInitPlayer(*reqInitPlayer)) {
		return ;
	}
	CMsgLoginSystemGT2CNAckInitPlayer ackInitPlayer;
	ackInitPlayer.m_accountKey = reqInitPlayer->m_accountKey;
	ackInitPlayer.m_centerSession = reqInitPlayer->m_centerSessionID;
	ackInitPlayer.m_state = ELOGINRESULT_SERVER_ERROR;

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrome, ackInitPlayer);
}

void CLoginSystemGT::_onMsgLoginSystemCN2GTAckAccountBreak(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	CMsgLoginSystemCN2GTAckAccountBreak* ackAccountBreak = (CMsgLoginSystemCN2GTAckAccountBreak*)a_msg;

	CAccountLoginGTInforMgr::singleton().checCN2GTAckAccountBreak(ackAccountBreak->m_gateSessionID, ackAccountBreak->m_accountKey);
}

void CLoginSystemGT::_onMsgLoginSystemCN2GTReqAccountOffline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;

	CMsgLoginSystemCN2GTReqAccountOffline* reqAccountOffline = (CMsgLoginSystemCN2GTReqAccountOffline*)a_msg;

	if (CAccountLoginGTInforMgr::singleton().checCN2GTReqAccountOffline(reqAccountOffline->m_gateSessionID, reqAccountOffline->m_accountKey)) {
		return ;
	}
	CMsgLoginSystemGT2CNAckAccountOffline ackAccountOffline; 
	ackAccountOffline.m_accountKey = reqAccountOffline->m_accountKey;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrome, ackAccountOffline);
	return ;
}

void CLoginSystemGT::_onMsgLoginSystemCN2GTReqAccountOnline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;

	CMsgLoginSystemCN2GTReqAccountOnline* reqAccountOnline = (CMsgLoginSystemCN2GTReqAccountOnline*)a_msg;

	if (CAccountLoginGTInforMgr::singleton().checCN2GTReqAccountOnline(reqAccountOnline->m_gateSessionID, reqAccountOnline->m_accountKey)){
		return ;
	}
	CMsgLoginSystemGT2CNAckAccountOnline ackAccountOnline; 
	ackAccountOnline.m_accountKey = reqAccountOnline->m_accountKey;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrome, ackAccountOnline);
}

void CLoginSystemGT::_onMsgLoginSystemCN2GTReqAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;

	CMsgLoginSystemCN2GTReqAccountFinal* reqAccountFinal = (CMsgLoginSystemCN2GTReqAccountFinal*)a_msg;

	if (CAccountLoginGTInforMgr::singleton().checCN2GTReqAccountFinal(reqAccountFinal->m_gateSessionID, reqAccountFinal->m_accountKey)) {
		return ;
	}
	CMsgLoginSystemGT2CNAckAccountFinal ackAccountFinalCN; 
	ackAccountFinalCN.m_accountKey = reqAccountFinal->m_accountKey;
	ackAccountFinalCN.m_centerSessionID = reqAccountFinal->m_centerSessionID;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrome, ackAccountFinalCN);

	CMsgLoginSystemGT2DBNtfAccountFinal ntfAccountFinalDB; 
	ntfAccountFinalDB.m_accountKey = reqAccountFinal->m_accountKey;
	ntfAccountFinalDB.m_centerSessionID = reqAccountFinal->m_centerSessionID;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(reqAccountFinal->m_dataServerID, ntfAccountFinalDB);
}

void CLoginSystemGT::_onMsgLoginSystemXS2GTNtfBroadcastMsg(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	CMsgLoginSystemXS2GTNtfBroadcastMsg* ntfBroadcastMsg = (CMsgLoginSystemXS2GTNtfBroadcastMsg*)a_msg;

	CAccountLoginGTInforMgr::singleton().broadcastMsg(ntfBroadcastMsg);
}


bool CLoginSystemGT::_cbTimerAccountLogin(BSLib::uint64 a_para1, void* a_para2)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);

	BSLib::uint32 sesssionID = (BSLib::uint32)a_para1;

	CAccountLoginGTInforMgr::singleton().timeroutAccountLogin(sesssionID);

	return false;
}

}//GT

}//LoginSystem

}//GSLib
