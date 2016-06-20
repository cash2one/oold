//////////////////////////////////////////////////////////////////////
//	created:	2014/07/19
//	filename:	src\GSLib\loginSystem\GM\loginSystemGM.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/accountMgr.h>
#include <GSLib/tracer.h>
#include <GSLib/loginSystem/GM/loginSystemGM.h>
#include <GSLib/loginSystem/msgLoginSystem.h>
#include <GSLib/loginSystem/GM/netPlayerGMMgr.h>
#include "GM/accountLoginGMInforMgr.h"

namespace GSLib
{

namespace LoginSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CLoginSystemGM);

CLoginSystemGM::CLoginSystemGM()
{
	;
}

CLoginSystemGM::~CLoginSystemGM()
{
	;
}

bool CLoginSystemGM::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CLoginSystemGM::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CLoginSystemGM::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CLoginSystemGM::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	//创建Player
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2GMReqCreatePlayer, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2GMReqCreatePlayer>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2GMReqCreatePlayer, &CLoginSystemGM::_onMsgLoginSystemCN2GMReqCreatePlayer, this);

	//初始化
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemDB2GMReqInitPlayer, &BSLib::Framework::CreateCMessage<CMsgLoginSystemDB2GMReqInitPlayer>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemDB2GMReqInitPlayer, &CLoginSystemGM::_onMsgLoginSystemDB2GMReqInitPlayer, this);

	//初始化客户端
//	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGT2GMNtfPlayerInforToClient, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGT2GMNtfPlayerInforToClient>);
//	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGT2GMNtfPlayerInforToClient, &CLoginSystemGM::_onMsgLoginSystemGT2GMNtfPlayerInforToClient, this);

	//离线协议
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2GMReqAccountOffline, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2GMReqAccountOffline>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2GMReqAccountOffline, &CLoginSystemGM::_onMsgLoginSystemCN2GMReqAccountOffline, this);

	//上线协议
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2GMReqAccountOnline, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2GMReqAccountOnline>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2GMReqAccountOnline, &CLoginSystemGM::_onMsgLoginSystemCN2GMReqAccountOnline, this);

	//退出协议
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2GMReqAccountFinal, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2GMReqAccountFinal>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2GMReqAccountFinal, &CLoginSystemGM::_onMsgLoginSystemCN2GMReqAccountFinal, this);

	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CLoginSystemGM::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CLoginSystemGM::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CLoginSystemGM::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	if (a_serverID.getServerType() == SRVTYPE_GATESERVER) {
		CAccountLoginGMInforMgr::singleton().dataServerLeave(a_serverID);
		return ;
	} else if (a_serverID.getServerType() == SRVTYPE_GAMESERVER){
		CAccountLoginGMInforMgr::singleton().gateServerLeave(a_serverID);
		return ;
	} else if (a_serverID.getServerType() == SRVTYPE_CENTERSERVER){
		CAccountLoginGMInforMgr::singleton().centerServerLeave(a_serverID);
		return ;
	}
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

void CLoginSystemGM::_onMsgLoginSystemCN2GMReqCreatePlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgLoginSystemCN2GMReqCreatePlayer* reqCreatePlayer = (CMsgLoginSystemCN2GMReqCreatePlayer*)a_msg;
	if (CAccountLoginGMInforMgr::singleton().checkCN2GMReqCreatePlayer(msgLabel->m_serverIDFrome, *reqCreatePlayer)){
		return;
	}
	CMsgLoginSystemGM2CNAckCreatePlayer ackCreatePlayer;
	ackCreatePlayer.m_accountKey = reqCreatePlayer->m_accountKey;
	ackCreatePlayer.m_centerSession = reqCreatePlayer->m_centerSessionID;
	ackCreatePlayer.m_state = ELOGINRESULT_SERVER_ERROR;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrome, ackCreatePlayer);
}

void CLoginSystemGM::_onMsgLoginSystemDB2GMReqInitPlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgLoginSystemDB2GMReqInitPlayer* reqInitPlayer = (CMsgLoginSystemDB2GMReqInitPlayer*)a_msg;
	if (CAccountLoginGMInforMgr::singleton().checkDB2GMReqInitPlayer(*reqInitPlayer)) {
		return;
	}
	CMsgLoginSystemGM2DBAckInitPlayer ackInitPlayerDB;
	ackInitPlayerDB.m_accountKey = reqInitPlayer->m_accountKey;
	ackInitPlayerDB.m_centerSessionID = reqInitPlayer->m_centerSessionID;
	ackInitPlayerDB.m_state = ELOGINRESULT_SERVER_ERROR;

	CMsgLoginSystemGM2CNNtfInitPlayer ntfInitPlayerCN;
	ntfInitPlayerCN.m_accountKey = reqInitPlayer->m_accountKey;
	ntfInitPlayerCN.m_centerSessionID = reqInitPlayer->m_centerSessionID;
	ntfInitPlayerCN.m_state = ELOGINRESULT_SERVER_ERROR;

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrome, ackInitPlayerDB);
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(reqInitPlayer->m_centerServerID, ntfInitPlayerCN);
}

void CLoginSystemGM::_onMsgLoginSystemCN2GMReqAccountOffline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgLoginSystemCN2GMReqAccountOffline* reqAccountOffline = (CMsgLoginSystemCN2GMReqAccountOffline*)a_msg;
	if (CAccountLoginGMInforMgr::singleton().checkCN2GMReqAccountOffline(reqAccountOffline->m_centerSessionID, reqAccountOffline->m_accountKey)) {
		return ;
	}
	CMsgLoginSystemGM2CNAckAccountOffline ackAccountOffline;
	ackAccountOffline.m_centerSessionID = reqAccountOffline->m_centerSessionID;
	ackAccountOffline.m_accountKey = reqAccountOffline->m_accountKey;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrome, ackAccountOffline);
}

void CLoginSystemGM::_onMsgLoginSystemCN2GMReqAccountOnline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgLoginSystemCN2GMReqAccountOnline* reqAccountOnline = (CMsgLoginSystemCN2GMReqAccountOnline*)a_msg;
	if (CAccountLoginGMInforMgr::singleton().checkCN2GMReqAccountOnline(reqAccountOnline->m_centerSessionID, reqAccountOnline->m_accountKey)){
		return;
	}
    
    CMsgLoginSystemGM2CNAckAccountOnline ackAccountOnline;
	ackAccountOnline.m_centerSessionID = reqAccountOnline->m_centerSessionID;
	ackAccountOnline.m_accountKey = reqAccountOnline->m_accountKey;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrome, ackAccountOnline);
}

void CLoginSystemGM::_onMsgLoginSystemCN2GMReqAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgLoginSystemCN2GMReqAccountFinal* reqAccountFinal = (CMsgLoginSystemCN2GMReqAccountFinal*)a_msg;
	if (CAccountLoginGMInforMgr::singleton().checkCN2GMReqAccountFinal(reqAccountFinal->m_centerSessionID, reqAccountFinal->m_accountKey)) {
		return;
	}
	CMsgLoginSystemGM2CNAckAccountFinal ackAccountFinalCN;
	ackAccountFinalCN.m_centerSessionID = reqAccountFinal->m_centerSessionID;
	ackAccountFinalCN.m_accountKey = reqAccountFinal->m_accountKey;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrome, ackAccountFinalCN);

	CMsgLoginSystemGM2DBNtfAccountFinal ntfAccountFinalDB;
	ntfAccountFinalDB.m_centerSessionID = reqAccountFinal->m_centerSessionID;
	ntfAccountFinalDB.m_accountKey = reqAccountFinal->m_accountKey;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(reqAccountFinal->m_dataServerID, ntfAccountFinalDB);
}

}//GM

}//LoginSystem

}//GSLib
