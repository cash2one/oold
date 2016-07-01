#include <GSLib/tracer.h>
#include <GSLib/serverType.h>
#include <GSLib/loginSystem/SP/loginSystemSP.h>
#include <GFLib/commonServer/stubMgr.h>
#include <GSLib/tracer.h>
#include <GFLib/commonServer/serviceMgr.h>
#include "SP/accountTokenInforMgr.h"
#include <GSLib/loginSystem/msgLoginSystemAC.h>


namespace GSLib
{

namespace LoginSystem
{

namespace SP
{

BSLIB_SINGLETON_DEFINE(CLoginSystemSP);

CLoginSystemSP::CLoginSystemSP()
{
	m_authCodeServerID = GFLib::INVALID_SERVERID;
}

CLoginSystemSP::~CLoginSystemSP()
{
	;
}

bool CLoginSystemSP::_init()
{
	return GFLib::CommonServer::CCommonSystem::_init();
}

void CLoginSystemSP::_final()
{
	GFLib::CommonServer::CCommonSystem::_final();
}

bool CLoginSystemSP::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return GFLib::CommonServer::CCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CLoginSystemSP::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemLG2SPReqRegisterToken, &BSLib::Framework::CreateCMessage<CMsgLoginSystemLG2SPReqRegisterToken>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemLG2SPReqRegisterToken, &CLoginSystemSP::_onMsgLoginSystemLG2SPReqRegisterToken, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemLG2SPReqCheckToken, &BSLib::Framework::CreateCMessage<CMsgLoginSystemLG2SPReqCheckToken>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemLG2SPReqCheckToken, &CLoginSystemSP::_onMsgLoginSystemLG2SPReqCheckToken, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemAC2SPAckCheckToken, &BSLib::Framework::CreateCMessage<CMsgLoginSystemAC2SPAckCheckToken>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemAC2SPAckCheckToken, &CLoginSystemSP::_onMsgLoginSystemAC2SPAckCheckToken, this);

	return GFLib::CommonServer::CCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}

bool CLoginSystemSP::_startSystem()
{
	return GFLib::CommonServer::CCommonSystem::_startSystem();
}

void CLoginSystemSP::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::ServerType serverType = a_serverID.ICommonServer_getServerType();
	switch (serverType)
	{
	case SRVTYPE_AUTHCODESERVER:
		m_authCodeServerID = a_serverID;
		break;
	} 
}

void CLoginSystemSP::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::ServerType serverType = a_serverID.ICommonServer_getServerType();
	switch (serverType)
	{
	case SRVTYPE_AUTHCODESERVER:
		m_authCodeServerID = GFLib::INVALID_SERVERID;
		break;
	}
}

void CLoginSystemSP::_onMsgLoginSystemLG2SPReqRegisterToken(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* netLable = (GFLib::SNetMsgLabel*)a_msgLabel; 
	CMsgLoginSystemLG2SPReqRegisterToken* reqRegisterToken = (CMsgLoginSystemLG2SPReqRegisterToken*)a_msg;
	SAccountTokenInfor tokenInfor;
	tokenInfor.m_token = reqRegisterToken->m_token;
	tokenInfor.m_accountKey = reqRegisterToken->m_accountKey;
	tokenInfor.m_accountName = reqRegisterToken->m_accountName;

	CMsgLoginSystemSP2LGAckRegisterToken ackRegisterToken;
	ackRegisterToken.m_loginSession = reqRegisterToken->m_loginSession;
	ackRegisterToken.m_accountKey = reqRegisterToken->m_accountKey;
	ackRegisterToken.m_state = ELOGINRESULT_SERVER_ERROR;
    ackRegisterToken.m_token = reqRegisterToken->m_token;

	if (CAccountTokenInforMgr::singleton().registerAccountTokenInfor(tokenInfor)) {
		ackRegisterToken.m_state = ELOGINRESULT_SUCCESS;
	}
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(netLable->m_serverIDSender, ackRegisterToken);
}

void CLoginSystemSP::_onMsgLoginSystemLG2SPReqCheckToken(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* netLable = (GFLib::SNetMsgLabel*)a_msgLabel; 
	CMsgLoginSystemLG2SPReqCheckToken* reqCheckToken = (CMsgLoginSystemLG2SPReqCheckToken*)a_msg;

	SAccountTokenInfor tokenInfor;
	tokenInfor.m_token = reqCheckToken->m_token;
	tokenInfor.m_accountKey = reqCheckToken->m_accountKey;
	tokenInfor.m_accountName = reqCheckToken->m_accountName;

	CMsgLoginSystemSP2LGAckCheckToken ackCheckToken;
	ackCheckToken.m_loginSession = reqCheckToken->m_loginSession;
	ackCheckToken.m_accountKey = reqCheckToken->m_accountKey;

	if (CAccountTokenInforMgr::singleton().checkAccountTokenInfor(tokenInfor)) {
		ackCheckToken.m_state = ELOGINRESULT_SUCCESS;
		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(netLable->m_serverIDSender, ackCheckToken);
		return ;
	}
	
	CMsgLoginSystemSP2ACReqCheckToken reqCheckTokenSP;
	reqCheckTokenSP.m_token = tokenInfor.m_token;
	reqCheckTokenSP.m_accountKey = tokenInfor.m_accountKey;
	reqCheckTokenSP.m_accountName = tokenInfor.m_accountName;
	reqCheckTokenSP.m_serverID = netLable->m_serverIDSender;
	reqCheckTokenSP.m_sessionID =  reqCheckToken->m_loginSession;
	if (m_authCodeServerID == GFLib::INVALID_SERVERID) {
		ackCheckToken.m_state = ELOGINRESULT_TOKEN_ERROR;
		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(netLable->m_serverIDSender, ackCheckToken);
		return;
	}
	if (!GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_authCodeServerID, reqCheckTokenSP)){
		ackCheckToken.m_state = ELOGINRESULT_TOKEN_ERROR;
		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(netLable->m_serverIDSender, ackCheckToken);
	}
}

void CLoginSystemSP::_onMsgLoginSystemAC2SPAckCheckToken(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemAC2SPAckCheckToken* ackCheckToken = (CMsgLoginSystemAC2SPAckCheckToken*)a_msg;
	
	CMsgLoginSystemSP2LGAckCheckToken ackCheckTokenLG;
	ackCheckTokenLG.m_loginSession = ackCheckToken->m_sessionID;
	ackCheckTokenLG.m_accountKey = ackCheckToken->m_accountKey;

	if (ackCheckToken->m_result == 0) {
		ackCheckTokenLG.m_state = ELOGINRESULT_TOKEN_ERROR;
		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(ackCheckToken->m_serverID, ackCheckTokenLG);
		return;
	}
	SAccountTokenInfor tokenInfor;
	tokenInfor.m_token = ackCheckToken->m_token;
	tokenInfor.m_accountKey = ackCheckToken->m_accountKey;
	tokenInfor.m_accountName = ackCheckToken->m_accountName;
	if (CAccountTokenInforMgr::singleton().registerAccountTokenInfor(tokenInfor)) {
		ackCheckTokenLG.m_state = ELOGINRESULT_SUCCESS;
		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(ackCheckToken->m_serverID, ackCheckTokenLG);
		return ;
	}
	ackCheckTokenLG.m_state = ELOGINRESULT_TOKEN_ERROR;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(ackCheckToken->m_serverID, ackCheckTokenLG);
}

}//LG

}//LoginSystem

}//GSLib

