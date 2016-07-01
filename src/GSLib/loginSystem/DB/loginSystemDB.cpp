#include <GFLib/commonServer/message/msgLabel.h>
#include <GFLib/commonServer/accountMgr.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/tracer.h>
#include <GSLib/loginSystem/DB/loginSystemDB.h>
#include <GSLib/loginSystem/msgLoginSystem.h>
#include <GSLib/loginSystem/DB/netPlayerDBMgr.h>
#include "DB/accountLoginDBInforMgr.h"

namespace GSLib
{

namespace LoginSystem
{

namespace DB
{

BSLIB_SINGLETON_DEFINE(CLoginSystemDB);

CLoginSystemDB::CLoginSystemDB()
{
	;
}

CLoginSystemDB::~CLoginSystemDB()
{
	;
}

bool CLoginSystemDB::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CLoginSystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CLoginSystemDB::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CLoginSystemDB::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	//创建Player
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2DBReqCreatePlayer, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2DBReqCreatePlayer>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2DBReqCreatePlayer, &CLoginSystemDB::_onMsgLoginSystemCN2DBReqCreatePlayer, this);

	//初始化
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2DBReqInitPlayer, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2DBReqInitPlayer>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2DBReqInitPlayer, &CLoginSystemDB::_onMsgLoginSystemCN2DBReqInitPlayer, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGM2DBAckInitPlayer, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGM2DBAckInitPlayer>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGM2DBAckInitPlayer, &CLoginSystemDB::_onMsgLoginSystemGM2DBAckInitPlayer, this);

	//离线协议
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2DBReqAccountOffline, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2DBReqAccountOffline>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2DBReqAccountOffline, &CLoginSystemDB::_onMsgLoginSystemCN2DBReqAccountOffline, this);

	//上线协议
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2DBReqAccountOnline, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2DBReqAccountOnline>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2DBReqAccountOnline, &CLoginSystemDB::_onMsgLoginSystemCN2DBReqAccountOnline, this);

	//退出协议
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGT2DBNtfAccountFinal, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGT2DBNtfAccountFinal>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGT2DBNtfAccountFinal, &CLoginSystemDB::_onMsgLoginSystemGT2DBNtfAccountFinal, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemGM2DBNtfAccountFinal, &BSLib::Framework::CreateCMessage<CMsgLoginSystemGM2DBNtfAccountFinal>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemGM2DBNtfAccountFinal, &CLoginSystemDB::_onMsgLoginSystemGM2DBNtfAccountFinal, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2DBReqAccountFinal, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2DBReqAccountFinal>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2DBReqAccountFinal, &CLoginSystemDB::_onMsgLoginSystemCN2DBReqAccountFinal, this);

	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}

bool CLoginSystemDB::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CLoginSystemDB::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CLoginSystemDB::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	if (a_serverID.ICommonServer_getServerType() == SRVTYPE_GATESERVER) {
		CAccountLoginDBInforMgr::singleton().gateServerLeave(a_serverID);
		return ;
	} else if (a_serverID.ICommonServer_getServerType() == SRVTYPE_GAMESERVER){
		CAccountLoginDBInforMgr::singleton().gameServerLeave(a_serverID);
		return ;
	} else if (a_serverID.ICommonServer_getServerType() == SRVTYPE_CENTERSERVER){
		CAccountLoginDBInforMgr::singleton().centerServerLeave(a_serverID);
		return ;
	}
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerLeave(a_serverID, a_key);
}

void CLoginSystemDB::_onMsgLoginSystemCN2DBReqCreatePlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgLoginSystemCN2DBReqCreatePlayer* reqCreatePlayer = (CMsgLoginSystemCN2DBReqCreatePlayer*)a_msg;
	if (CAccountLoginDBInforMgr::singleton().checkCN2DBReqCreatePlayer(msgLabel->m_serverIDFrom, *reqCreatePlayer)) {
		return;
	}
	CMsgLoginSystemDB2CNAckCreatePlayer ackCreatePlayer;
	ackCreatePlayer.m_accountKey = reqCreatePlayer->m_accountKey;
	ackCreatePlayer.m_centerSession = reqCreatePlayer->m_centerSessionID;
	ackCreatePlayer.m_state = ELOGINRESULT_SERVER_ERROR;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrom, ackCreatePlayer);
}

void CLoginSystemDB::_onMsgLoginSystemCN2DBReqInitPlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgLoginSystemCN2DBReqInitPlayer* reqInitPlayer = (CMsgLoginSystemCN2DBReqInitPlayer*)a_msg;
	if (CAccountLoginDBInforMgr::singleton().checkCN2DBReqInitPlayer(*reqInitPlayer)) {
		return;
	}
	CMsgLoginSystemDB2CNAckInitPlayer ackInitPlayer;
	ackInitPlayer.m_accountKey = reqInitPlayer->m_accountKey;
	ackInitPlayer.m_centerSessionID = reqInitPlayer->m_centerSessionID;
	ackInitPlayer.m_state = ELOGINRESULT_SERVER_ERROR;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrom, ackInitPlayer);
}

void CLoginSystemDB::_onMsgLoginSystemGM2DBAckInitPlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGM2DBAckInitPlayer* ackInitPlayer = (CMsgLoginSystemGM2DBAckInitPlayer*)a_msg;

	CAccountLoginDBInforMgr::singleton().checkGM2DBAckInitPlayer(*ackInitPlayer);
}

void CLoginSystemDB::_onMsgLoginSystemCN2DBReqAccountOffline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgLoginSystemCN2DBReqAccountOffline* reqAccountOffline = (CMsgLoginSystemCN2DBReqAccountOffline*)a_msg;
	if (CAccountLoginDBInforMgr::singleton().checkCN2DBReqAccountOffline(reqAccountOffline->m_centerSessionID, reqAccountOffline->m_accountKey)) {
		return;
	}
	CMsgLoginSystemDB2CNAckAccountOffline ackAccountOffline;
	ackAccountOffline.m_accountKey = reqAccountOffline->m_accountKey;
	ackAccountOffline.m_centerSessionID = reqAccountOffline->m_centerSessionID;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrom, ackAccountOffline);
}

void CLoginSystemDB::_onMsgLoginSystemCN2DBReqAccountOnline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgLoginSystemCN2DBReqAccountOnline* reqAccountOnline = (CMsgLoginSystemCN2DBReqAccountOnline*)a_msg;
	if (CAccountLoginDBInforMgr::singleton().checkCN2DBReqAccountOnline(reqAccountOnline->m_centerSessionID, reqAccountOnline->m_accountKey)) {
		return;
	}
	CMsgLoginSystemDB2CNAckAccountOnline ackAccountOnline;
	ackAccountOnline.m_accountKey = reqAccountOnline->m_accountKey;
	ackAccountOnline.m_centerSessionID = reqAccountOnline->m_centerSessionID;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrom, ackAccountOnline);
}

void CLoginSystemDB::_onMsgLoginSystemGT2DBNtfAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGT2DBNtfAccountFinal* reqAccountFinal = (CMsgLoginSystemGT2DBNtfAccountFinal*)a_msg;

	CAccountLoginDBInforMgr::singleton().checkGT2DBNtfAccountFinal(reqAccountFinal->m_centerSessionID, reqAccountFinal->m_accountKey);
}

void CLoginSystemDB::_onMsgLoginSystemGM2DBNtfAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemGM2DBNtfAccountFinal* reqAccountFinal = (CMsgLoginSystemGM2DBNtfAccountFinal*)a_msg;

	CAccountLoginDBInforMgr::singleton().checkGM2DBNtfAccountFinal(reqAccountFinal->m_centerSessionID, reqAccountFinal->m_accountKey);
}

void CLoginSystemDB::_onMsgLoginSystemCN2DBReqAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgLoginSystemCN2DBReqAccountFinal* reqAccountFinal = (CMsgLoginSystemCN2DBReqAccountFinal*)a_msg;
	if (CAccountLoginDBInforMgr::singleton().checkCN2DBReqAccountFinal(reqAccountFinal->m_centerSessionID, reqAccountFinal->m_accountKey)) {
		return;
	}
	CMsgLoginSystemDB2CNAckAccountFinal ackAccountFinal;
	ackAccountFinal.m_accountKey = reqAccountFinal->m_accountKey;
	ackAccountFinal.m_centerSessionID = reqAccountFinal->m_centerSessionID;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrom, ackAccountFinal);
}

}//DB

}//LoginSystem

}//GSLib

