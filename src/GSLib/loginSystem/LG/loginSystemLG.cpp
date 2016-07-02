#include <BSLib/utility/uuid.h>
#include <GSLib/tracer.h>
#include <GSLib/serverType.h>
#include <GSLib/loginSystem/LG/loginSystemLG.h>
#include <GFLib/commonServer/stubMgr.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/tracer.h>
#include <GSLib/dbSystem/LG/dbSystemLG.h>
#include "LG/zoneInforMgr.h"
#include "LG/accountLoginLGInforMgr.h"

namespace GSLib
{

namespace LoginSystem
{

namespace LG
{

BSLIB_SINGLETON_DEFINE(CLoginSystemLG);

CLoginSystemLG::CLoginSystemLG()
:m_codeFilterMode(0)
{
	;
}

CLoginSystemLG::~CLoginSystemLG()
{
	;
}

bool CLoginSystemLG::verifyAccountLogin(GFLib::StubID a_stubID, std::string& accountLoginIP, CMsgLoginSystemGC2LGReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemLG2GCAckAccountLogin& a_ackAccountLogin)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);

	GSLib::LoginSystem::ELoginType loginType = (GSLib::LoginSystem::ELoginType)a_reqAccountLogin.m_loginType;
	if(loginType == GSLib::LoginSystem::ELOGINTYPE_NORMAL_LOGIN){
		return _verifyNormalAccountLogin(a_stubID,accountLoginIP,a_reqAccountLogin,a_ackAccountLogin);
	}
	else if(loginType == GSLib::LoginSystem::ELOGINTYPE_FAST_LOGIN){
		if(!_verifyFastAccountLogin(a_stubID,accountLoginIP,a_reqAccountLogin,a_ackAccountLogin)){
			if(_fastRegisterAccount(a_reqAccountLogin)){
				return _verifyFastAccountLogin(a_stubID,accountLoginIP,a_reqAccountLogin,a_ackAccountLogin);
			}
		}
		else{
			return true;
		}
	}
    else if(loginType == GSLib::LoginSystem::ELOGINTYPE_TOKEN_LOGIN){
       return _verifyTokenAccountLogin(a_stubID,accountLoginIP,a_reqAccountLogin,a_ackAccountLogin);
    }

	return false;
}

bool CLoginSystemLG::registerAccount(GFLib::StubID a_stubID, std::string& accountLoginIP, CMsgLoginSystemGC2LGReqRegisterAccount& a_reqRegisterAccount, CMsgLoginSystemLG2GCAckRegisterAccount& a_ackRegisterAccount)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);

	GSLib::LoginSystem::ERegisterType registerType = (GSLib::LoginSystem::ERegisterType)a_reqRegisterAccount.m_registerType;

	GSLib::DBSystem::LG::SAccountData accountData;
	if(registerType == GSLib::LoginSystem::EREGEITERTYPE_NORMAL_REGISTER){
		BSLIB_LOG_INFO(ETT_GSLIB_LOGINSYSTEM, "普通注册[AccountName=%s]", a_reqRegisterAccount.m_accountName.c_str());
		if(a_reqRegisterAccount.m_accountName.length() < 6){
			a_ackRegisterAccount.m_state = EREGISTERRESULT_ACCOUNT_INVALID;
			return false;
		}
		if(a_reqRegisterAccount.m_accountPwd.length() < 6){
			a_ackRegisterAccount.m_state = EREGISTERRESULT_ACCOUNT_INVALID;
			return false;
		}

		GSLib::DBSystem::LG::SAccountData accountData;
		int res = GSLib::DBSystem::LG::CDBSystemLG::singleton().selectAccountData(a_reqRegisterAccount.m_accountName, accountData);
		if (res < 0) {
			BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "查询账号失败[AccountName=%s]", a_reqRegisterAccount.m_accountName.c_str());
			a_ackRegisterAccount.m_state = ELOGINRESULT_SERVER_ERROR;
			return false;
		} else if (res > 0) {
			BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "账号已经存在[AccountName=%s]", a_reqRegisterAccount.m_accountName.c_str());
			a_ackRegisterAccount.m_state = EREGISTERRESULT_ACCOUNT_EXIST;
			return false;
		}
		
		GSLib::DBSystem::LG::SActivationCodeData actData;
        if(m_codeFilterMode)
        {
            if(a_reqRegisterAccount.m_activationCode.empty())
            {   
                BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "需要激活码[AccountName=%s]", a_reqRegisterAccount.m_accountName.c_str());
                a_ackRegisterAccount.m_state = EREGISTERRESULT_ACTIVATION_CODE_INVALID;
                return false;
            }
            res = GSLib::DBSystem::LG::CDBSystemLG::singleton().selectActivationCodeData(a_reqRegisterAccount.m_activationCode, actData);
            if( res <= 0)
            {
                BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "查询激活码失败[ActivationCode=%s]", a_reqRegisterAccount.m_activationCode.c_str());
                a_ackRegisterAccount.m_state = EREGISTERRESULT_ACTIVATION_CODE_INVALID;
                return false;
            }
           
            if( actData.m_used)
            {
                BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "激活码已使用[ActivationCode=%s]", a_reqRegisterAccount.m_activationCode.c_str());
                a_ackRegisterAccount.m_state = EREGISTERRESULT_ACTIVATION_CODE_INVALID;
                return false;
            }

            actData.m_used = 1;
        }

		BSLib::uint64 accountID = 0;
		if (!_registerNormalAccountToDB(a_reqRegisterAccount.m_accountName, a_reqRegisterAccount.m_accountPwd, a_reqRegisterAccount.m_channelID, a_reqRegisterAccount.m_platform, a_reqRegisterAccount.m_activationCode, accountID)) {
			a_ackRegisterAccount.m_state = EREGISTERRESULT_ACCOUNT_EXIST;
			return false;
		}
		a_ackRegisterAccount.m_state = ELOGINRESULT_SUCCESS;
		if(m_codeFilterMode)
		{
			GSLib::DBSystem::LG::CDBSystemLG::singleton().updateActivationCodeData(actData);
		}

		// 记录日志
		BSLib::Utility::CDateTime now = BSLib::Utility::CDateTime::getCurrentTime();
		BSLIB_LOG_INFO(ETT_GSLIB_GAME, "[t_register][f_time=%s][f_acc_id=%lld][f_acc_type=%u]", 
			now.toString().c_str(),
			accountID,
			a_reqRegisterAccount.m_channelID);

// 		GSLib::DBSystem::LG::SAccountInsertData data;
// 		BSLibSprintf(data.m_accountName,sizeof(char)*(GSLIB_TEXT_MAX_ACCOUNT_NAME + 1),"%s",a_reqRegisterAccount.m_accountName.c_str());
// 		BSLibSprintf(data.m_accountPassword,sizeof(char)*(GSLIB_TEXT_MAX_ACCOUNT_PASSWORD + 1),"%s",a_reqRegisterAccount.m_accountPwd.c_str());
// 		memset(data.m_uniqueID,0,sizeof(data.m_uniqueID));
// 		memset(data.m_uniqueKey,0,sizeof(data.m_uniqueKey));
//         memset(data.m_activationCode,0,sizeof(data.m_activationCode));
// 		BSLibSprintf(data.m_platform,sizeof(char)*(GSLIB_TEXT_MAX_PLATFORM + 1),"%s",a_reqRegisterAccount.m_platform.c_str());
// 		data.m_channelID = a_reqRegisterAccount.m_channelID;
// 		data.m_bindFlag = 0;
// 		data.m_registerTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
//         if(m_codeFilterMode)
//         {
//            BSLibSprintf(data.m_activationCode,sizeof(char)*(256),"%s",a_reqRegisterAccount.m_activationCode.c_str());
//         }
// 
// 		BSLib::Utility::CStream stream;
// 		stream.reset();
// 		stream.write((const char*)&data,sizeof(data));
// 
// 		if(!GSLib::DBSystem::LG::CDBSystemLG::singleton().insertAccountData(stream,NULL)){
// 			a_ackRegisterAccount.m_state = EREGISTERRESULT_ACCOUNT_EXIST;
// 			return false;
// 		}
// 		a_ackRegisterAccount.m_state = ELOGINRESULT_SUCCESS;
// 		if(m_codeFilterMode)
// 		{
// 			GSLib::DBSystem::LG::CDBSystemLG::singleton().updateActivationCodeData(actData);
// 		}
// 
// 		// 记录日志
// 		{	
// 			GSLib::DBSystem::LG::SAccountData  saData;
// 			int res = GSLib::DBSystem::LG::CDBSystemLG::singleton().selectAccountData(a_reqRegisterAccount.m_accountName, saData);	
// 			if( res > 0)
// 			{
// 				BSLib::Utility::CDateTime now = BSLib::Utility::CDateTime::getCurrentTime();
// 				BSLIB_LOG_INFO(ETT_GSLIB_GAME, "[t_register][f_time=%s][f_acc_id=%lld][f_acc_type=%u]", 
// 					now.toString().c_str(),
// 					saData.m_accountID,
// 					saData.m_channelID);
// 			}
// 		}
	} else if(registerType == GSLib::LoginSystem::EREGEITERTYPE_FAST_REGISTER){
		BSLIB_LOG_INFO(ETT_GSLIB_LOGINSYSTEM, "快速注册[m_uniqueID=%s][m_uniqueKey=%s]", a_reqRegisterAccount.m_uniqueID.c_str(), a_reqRegisterAccount.m_uniqueKey.c_str());
		const BSLib::uint32 bindFlag = 0;
		int res = GSLib::DBSystem::LG::CDBSystemLG::singleton().selectFastLoginAccountData(a_reqRegisterAccount.m_uniqueID,a_reqRegisterAccount.m_uniqueKey,bindFlag, accountData);

		if (res < 0) {
			BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "查询账号失败[m_uniqueID=%s][m_uniqueKey=%s]", a_reqRegisterAccount.m_uniqueID.c_str(), a_reqRegisterAccount.m_uniqueKey.c_str());
			a_ackRegisterAccount.m_state = EREGISTERRESULT_ACCOUNT_INVALID;
			return false;
		} else if (res > 0) {
			BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "账号已经存在[m_uniqueID=%s][m_uniqueKey=%s]", a_reqRegisterAccount.m_uniqueID.c_str(), a_reqRegisterAccount.m_uniqueKey.c_str());
			a_ackRegisterAccount.m_state = EREGISTERRESULT_ACCOUNT_EXIST;
			return false;
		}

		BSLib::uint64 accountID = 0;
		if (!_registerFastAccountToDB(a_reqRegisterAccount.m_uniqueID, a_reqRegisterAccount.m_uniqueKey, a_reqRegisterAccount.m_channelID, a_reqRegisterAccount.m_platform, accountID)) {
			a_ackRegisterAccount.m_state = EREGISTERRESULT_ACCOUNT_EXIST;
			return false;
		}
		a_ackRegisterAccount.m_state = ELOGINRESULT_SUCCESS;
		return true;

// 		GSLib::DBSystem::LG::SAccountInsertData data;
// 		memset(data.m_accountName,0,sizeof(data.m_accountName));
// 		memset(data.m_accountPassword,0,sizeof(data.m_accountPassword));
// 		BSLibSprintf(data.m_uniqueID,sizeof(char)*(GSLIB_TEXT_MAX_ACCOUNT_UNIQUEID + 1),"%s",a_reqRegisterAccount.m_uniqueID.c_str());
// 		BSLibSprintf(data.m_uniqueKey,sizeof(char)*(GSLIB_TEXT_MAX_ACCOUNT_UNIQUEKEY + 1),"%s",a_reqRegisterAccount.m_uniqueKey.c_str());
// 		BSLibSprintf(data.m_platform,sizeof(char)*(GSLIB_TEXT_MAX_PLATFORM + 1),"%s",a_reqRegisterAccount.m_platform.c_str());
// 		data.m_channelID = a_reqRegisterAccount.m_channelID;
// 		data.m_bindFlag = bindFlag;
// 		data.m_registerTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
// 
// 		BSLib::Utility::CStream stream;
// 		stream.reset();
// 		stream.write((const char*)&data,sizeof(data));
// 
// 		if(!GSLib::DBSystem::LG::CDBSystemLG::singleton().insertAccountData(stream,NULL)){
// 			a_ackRegisterAccount.m_state = EREGISTERRESULT_ACCOUNT_EXIST;
// 			return false;
// 		}
// 
// 		a_ackRegisterAccount.m_state = ELOGINRESULT_SUCCESS;
// 		return true;
	} else if(registerType == GSLib::LoginSystem::EREGEITERTYPE_BIND_MACHINE){
		BSLIB_LOG_INFO(ETT_GSLIB_LOGINSYSTEM, "账号绑定[AccountName=%s][m_uniqueID=%s][m_uniqueKey=%s]", a_reqRegisterAccount.m_accountName.c_str(), a_reqRegisterAccount.m_uniqueID.c_str(), a_reqRegisterAccount.m_uniqueKey.c_str());
	}

	return true;
}

bool CLoginSystemLG::verifyGetAccountToken(GFLib::StubID a_stubID, std::string& accountLoginIP, CMsgLoginSystemGC2LGReqGetAccountToken& a_reqAccountLogin, CMsgLoginSystemLG2GCAckGetAccountToken& a_ackAccountLogin)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);

	GSLib::LoginSystem::EGetTokenType loginType = (GSLib::LoginSystem::EGetTokenType)a_reqAccountLogin.m_loginType;
	if(loginType == GSLib::LoginSystem::EGETTAKENTYPE_NORMAL_LOGIN){
		return _verifyNormalGetAccountToken(a_stubID,accountLoginIP,a_reqAccountLogin,a_ackAccountLogin);
	}
	else if(loginType == GSLib::LoginSystem::EGETTAKENTYPE_FAST_LOGIN){
		if(!_verifyFastGetAccountToken(a_stubID,accountLoginIP,a_reqAccountLogin,a_ackAccountLogin)){
			if(_fastRegisterAccount(a_reqAccountLogin)){
				return _verifyFastGetAccountToken(a_stubID,accountLoginIP,a_reqAccountLogin,a_ackAccountLogin);
			}
			return false;
		}
		else{
			return true;
		}
	}

	return false;
}

bool CLoginSystemLG::isValidAccountLogin(GFLib::StubID a_stubID)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);

	return CAccountLoginLGInforMgr::singleton().isValidAccountLogin(a_stubID);
}

void CLoginSystemLG::removeAccountLogin(GFLib::StubID a_stubID)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);

	CAccountLoginLGInforMgr::singleton().removeAccountLoginInfor(a_stubID);
}

bool CLoginSystemLG::_verifyNormalAccountLogin(GFLib::StubID a_stubID, std::string& accountLoginIP, CMsgLoginSystemGC2LGReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemLG2GCAckAccountLogin& a_ackAccountLogin)
{
	//BSLib::Utility::CMutexFun fun(&m_mutex);

	if (m_superServerID == GFLib::INVALID_SERVERID){
		a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyNormalAccountLogin][Super服务器没有启动]");
		return false;
	}
	GFLib::SServerID centerServerID;
	if (!CZoneInforMgr::singleton().verifyZone(a_reqAccountLogin.m_zoneID, a_ackAccountLogin, centerServerID)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyNormalAccountLogin][获取游戏区失败][AccountName=%s][ZoneID=%d][m_state=%d]", a_reqAccountLogin.m_accountName.c_str(), a_reqAccountLogin.m_zoneID,a_ackAccountLogin.m_state);
		return false;
	}

	GSLib::DBSystem::LG::SAccountData accountData;
	int res = GSLib::DBSystem::LG::CDBSystemLG::singleton().selectAccountData(a_reqAccountLogin.m_accountName, accountData);
	if (res < 0) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyNormalAccountLogin][查询账号失败][AccountName=%s]", a_reqAccountLogin.m_accountName.c_str());
		a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
		return false;
	} else if (res == 0) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyNormalAccountLogin][账号不存在][AccountName=%s]", a_reqAccountLogin.m_accountName.c_str());
		a_ackAccountLogin.m_state = ELOGINRESULT_ACCOUNT_NOTEXIST;
		return false;
	}
	if (a_reqAccountLogin.m_accountPwd.empty()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyNormalAccountLogin][验证密码不合法][AccountName=%s]", a_reqAccountLogin.m_accountName.c_str());
		a_ackAccountLogin.m_state = ELOGINRESULT_PASSWORD_ERROR;
		return false;
	}
	if (a_reqAccountLogin.m_accountPwd != accountData.m_accountPassword) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyNormalAccountLogin][验证密码不合法][AccountName=%s]", a_reqAccountLogin.m_accountName.c_str());
		a_ackAccountLogin.m_state = ELOGINRESULT_PASSWORD_ERROR;
		return false;
	}

	SAccountLoginLGInfor accountInfor;
	accountInfor.m_stubID = a_stubID;
	accountInfor.m_sessionID = 0;
	accountInfor.m_accountName = a_reqAccountLogin.m_accountName;
	accountInfor.m_channelID = a_reqAccountLogin.m_channelID;
	accountInfor.m_accountLoginIP = accountLoginIP;
	accountInfor.m_accountKey.setKey(accountData.m_accountID, a_reqAccountLogin.m_zoneID);
	if (!CAccountLoginLGInforMgr::singleton().registerAccountLoginInfor(accountInfor)) {
		a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "保存登陆信息失败[AccountName=%s]", a_reqAccountLogin.m_accountName.c_str());
		return false;
	}

// 	BSLib::Utility::CUUID uuidToken;
// 	BSLib::Utility::CUUID::generate(uuidToken);
// 
// 	CMsgLoginSystemLG2SPReqRegisterToken reqRegisterTocken2SP;
// 	reqRegisterTocken2SP.m_loginSession = accountInfor.m_sessionID;
// 	reqRegisterTocken2SP.m_accountKey = accountInfor.m_accountKey;
// 	reqRegisterTocken2SP.m_accountName = a_reqAccountLogin.m_accountName;
// 	reqRegisterTocken2SP.m_token = uuidToken.unparse();
// 	if (!GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_superServerID, reqRegisterTocken2SP)){
// 		a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
// 		CAccountLoginLGInforMgr::singleton().removeAccountLoginInfor(a_stubID);
// 		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "发送消息失败[SuperServer=%s][Account=%s]", reqRegisterTocken2SP.toString().c_str(), a_reqAccountLogin.m_accountName.c_str());
// 		return false;
// 	}
// 
// 	BSLIB_LOG_INFO(ETT_GSLIB_LOGINSYSTEM, "进入Super请求[AccountName=%s][zoneID=%d][SessionID=%d]",
// 		a_reqAccountLogin.m_accountName.c_str(),
// 		a_reqAccountLogin.m_zoneID,
// 		accountInfor.m_sessionID);

	CMsgLoginSystemLG2CNReqAccountLogin reqAccountLogin2CN;
	reqAccountLogin2CN.m_accountName = accountInfor.m_accountName;
	reqAccountLogin2CN.m_loginSession = accountInfor.m_sessionID;
	reqAccountLogin2CN.m_channelID = accountInfor.m_channelID;
	reqAccountLogin2CN.m_accountLoginIP = accountInfor.m_accountLoginIP;
	reqAccountLogin2CN.m_accountKey = accountInfor.m_accountKey;
	if (!GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(centerServerID, reqAccountLogin2CN)){
		a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
		return false;
	}

    BSLIB_LOG_INFO(ETT_GSLIB_LOGINSYSTEM, "进入CMsgLoginSystemLG2CNReqAccountLogin请求[AccountName=%s][zoneID=%d][SessionID=%d]",
        a_reqAccountLogin.m_accountName.c_str(),
        a_reqAccountLogin.m_zoneID,
        accountInfor.m_sessionID);

	return true;
}

bool CLoginSystemLG::_verifyTokenAccountLogin(GFLib::StubID a_stubID, std::string& accountLoginIP, CMsgLoginSystemGC2LGReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemLG2GCAckAccountLogin& a_ackAccountLogin)
{
    //BSLib::Utility::CMutexFun fun(&m_mutex);

    if (m_superServerID == GFLib::INVALID_SERVERID){
        a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "Super服务器没有启动");
        return false;
    }
    GFLib::SServerID centerServerID;
    if (!CZoneInforMgr::singleton().verifyZone(a_reqAccountLogin.m_zoneID, a_ackAccountLogin, centerServerID)) {
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "verifyTokenAccountLogin获取游戏区失败[AccountName=%s][ZoneID=%d][m_state=%d]", a_reqAccountLogin.m_accountName.c_str(), a_reqAccountLogin.m_zoneID,a_ackAccountLogin.m_state);
        return false;
    }
	//获取账号accountID
	BSLib::uint64 accountID = a_reqAccountLogin.m_accountID;
	if (!a_reqAccountLogin.m_accountName.empty()) {
		GSLib::DBSystem::LG::SAccountData accountData;
		int res = GSLib::DBSystem::LG::CDBSystemLG::singleton().selectAccountData(a_reqAccountLogin.m_accountName, accountData);
		if (res < 0) {
			BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "查询账号失败[AccountName=%s]", a_reqAccountLogin.m_accountName.c_str());
			return false;
		} else if(res == 0){
			if (!_registerNormalAccountToDB(a_reqAccountLogin.m_accountName, "", a_reqAccountLogin.m_channelID, a_reqAccountLogin.m_platform, "", accountID)) {
				BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "verifyTokenAccountLogin注册账号ID失败[AccountName=%s][ZoneID=%d][m_state=%d]", a_reqAccountLogin.m_accountName.c_str(), a_reqAccountLogin.m_zoneID,a_ackAccountLogin.m_state);
				return false;
			}
		} else if (res > 0) {
			BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "账号已经存在[AccountName=%s]", a_reqAccountLogin.m_accountName.c_str());
			accountID = accountData.m_accountID;
		}
	}
	
    SAccountLoginLGInfor accountInfor;
    accountInfor.m_stubID = a_stubID;
    accountInfor.m_sessionID = 0;
    accountInfor.m_accountName = a_reqAccountLogin.m_accountName;
    accountInfor.m_channelID = a_reqAccountLogin.m_channelID;
    accountInfor.m_accountLoginIP = accountLoginIP;
    accountInfor.m_accountKey.setKey(accountID, a_reqAccountLogin.m_zoneID);
    if (!CAccountLoginLGInforMgr::singleton().registerAccountLoginInfor(accountInfor)) {
        a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "保存登陆信息失败[AccountName=%s]", a_reqAccountLogin.m_accountName.c_str());
        return false;
    }

    CMsgLoginSystemLG2SPReqCheckToken reqCheckTokenTocken2SP;
    reqCheckTokenTocken2SP.m_loginSession = accountInfor.m_sessionID;
    reqCheckTokenTocken2SP.m_accountKey.setKey(accountID, a_reqAccountLogin.m_zoneID);
    reqCheckTokenTocken2SP.m_accountName = a_reqAccountLogin.m_accountName;
    reqCheckTokenTocken2SP.m_token = a_reqAccountLogin.m_token;
    if (!GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_superServerID, reqCheckTokenTocken2SP)){
        a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
        CAccountLoginLGInforMgr::singleton().removeAccountLoginInfor(a_stubID);
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "发送消息失败[Account=%s]", a_reqAccountLogin.m_uniqueID.c_str());
        return false;
    }

    BSLIB_LOG_INFO(ETT_GSLIB_LOGINSYSTEM, "进入Super请求[AccountName=%s][zoneID=%d][SessionID=%d]",
        a_reqAccountLogin.m_accountName.c_str(),
        a_reqAccountLogin.m_zoneID,
        accountInfor.m_sessionID);

    return true;
}

bool CLoginSystemLG::_verifyFastAccountLogin(GFLib::StubID a_stubID, std::string& accountLoginIP, CMsgLoginSystemGC2LGReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemLG2GCAckAccountLogin& a_ackAccountLogin)
{
	//BSLib::Utility::CMutexFun fun(&m_mutex);

	if (m_superServerID == GFLib::INVALID_SERVERID){
		a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "Super服务器没有启动");
		return false;
	}

	GFLib::SServerID centerServerID;
	if (!CZoneInforMgr::singleton().verifyZone(a_reqAccountLogin.m_zoneID, a_ackAccountLogin, centerServerID)) {
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyFastAccountLogin]n获取游戏区失败[AccountName=%s][ZoneID=%d][m_state=%d]", a_reqAccountLogin.m_accountName.c_str(), a_reqAccountLogin.m_zoneID,a_ackAccountLogin.m_state);
		return false;
	}

	GSLib::DBSystem::LG::SAccountData accountData;
	const BSLib::uint32 bindFlag = 0;
	int res = GSLib::DBSystem::LG::CDBSystemLG::singleton().selectFastLoginAccountData(a_reqAccountLogin.m_uniqueID,a_reqAccountLogin.m_uniqueKey,bindFlag, accountData);
	if (res < 0) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyFastAccountLogin]查询账号失败[AccountName=%s]", a_reqAccountLogin.m_uniqueID.c_str());
		a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
		return false;
	} if (res == 0) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyFastAccountLogin]账号不存在[AccountName=%s]", a_reqAccountLogin.m_uniqueID.c_str());
		a_ackAccountLogin.m_state = ELOGINRESULT_ACCOUNT_NOTEXIST;
		return false;
	}

	SAccountLoginLGInfor accountInfor;
	accountInfor.m_stubID = a_stubID;
	accountInfor.m_sessionID = 0;
	accountInfor.m_accountName = a_reqAccountLogin.m_uniqueID;
	accountInfor.m_channelID = a_reqAccountLogin.m_channelID;
	accountInfor.m_accountLoginIP = accountLoginIP;
	accountInfor.m_accountKey.setKey(accountData.m_accountID, a_reqAccountLogin.m_zoneID);
	if (!CAccountLoginLGInforMgr::singleton().registerAccountLoginInfor(accountInfor)) {
		a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "保存登陆信息失败[AccountName=%s]", a_reqAccountLogin.m_uniqueID.c_str());
		return false;
	}
	
// 	BSLib::Utility::CUUID uuidToken;
// 	BSLib::Utility::CUUID::generate(uuidToken);
// 
// 	CMsgLoginSystemLG2SPReqRegisterToken reqRegisterTocken2SP;
// 	reqRegisterTocken2SP.m_loginSession = accountInfor.m_sessionID;
// 	reqRegisterTocken2SP.m_accountKey = accountInfor.m_accountKey;
// 	reqRegisterTocken2SP.m_accountName = a_reqAccountLogin.m_uniqueID;
// 	reqRegisterTocken2SP.m_token = uuidToken.unparse();
// 	if (!GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_superServerID, reqRegisterTocken2SP)){
// 		a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
// 		CAccountLoginLGInforMgr::singleton().removeAccountLoginInfor(a_stubID);
// 		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "发送消息失败[SuperServer=%s][Account=%s]", reqRegisterTocken2SP.toString().c_str(), a_reqAccountLogin.m_uniqueID.c_str());
// 		return false;
// 	}
// 
// 	BSLIB_LOG_INFO(ETT_GSLIB_LOGINSYSTEM, "进入Super请求[AccountName=%s][zoneID=%d][SessionID=%d]",
// 		a_reqAccountLogin.m_uniqueID.c_str(),
// 		a_reqAccountLogin.m_zoneID,
// 		accountInfor.m_sessionID);
    CMsgLoginSystemLG2CNReqAccountLogin reqAccountLogin2CN;
    reqAccountLogin2CN.m_accountName = accountInfor.m_accountName;
    reqAccountLogin2CN.m_loginSession = accountInfor.m_sessionID;
    reqAccountLogin2CN.m_channelID = accountInfor.m_channelID;
    reqAccountLogin2CN.m_accountLoginIP = accountInfor.m_accountLoginIP;
    reqAccountLogin2CN.m_accountKey = accountInfor.m_accountKey;
    if (!GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(centerServerID, reqAccountLogin2CN)){
        a_ackAccountLogin.m_state = ELOGINRESULT_SERVER_ERROR;
        return false;
    }

    BSLIB_LOG_INFO(ETT_GSLIB_LOGINSYSTEM, "进入CMsgLoginSystemLG2CNReqAccountLogin请求[AccountName=%s][zoneID=%d][SessionID=%d]",
        a_reqAccountLogin.m_accountName.c_str(),
        a_reqAccountLogin.m_zoneID,
        accountInfor.m_sessionID);

	return true;
}

bool CLoginSystemLG::_fastRegisterAccount(CMsgLoginSystemGC2LGReqAccountLogin& a_reqAccountLogin)
{
    //BSLib::Utility::CMutexFun fun(&m_mutex);

    GSLib::LoginSystem::ELoginType loginType = (GSLib::LoginSystem::ELoginType)a_reqAccountLogin.m_loginType;

    GSLib::DBSystem::LG::SAccountData accountData;
    if(loginType == GSLib::LoginSystem::ELOGINTYPE_FAST_LOGIN){
        BSLIB_LOG_INFO(ETT_GSLIB_LOGINSYSTEM, "快速注册[m_uniqueID=%s][m_uniqueKey=%s]", a_reqAccountLogin.m_uniqueID.c_str(), a_reqAccountLogin.m_uniqueKey.c_str());
        //return registerFastAccountLogin(a_stubID,accountLoginIP,a_reqRegisterAccount,a_ackRegisterAccount);
        const BSLib::uint32 bindFlag = 0;
        int res = GSLib::DBSystem::LG::CDBSystemLG::singleton().selectFastLoginAccountData(a_reqAccountLogin.m_uniqueID,a_reqAccountLogin.m_uniqueKey,bindFlag, accountData);
        if (res < 0) {
            BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "查询账号失败[m_uniqueID=%s][m_uniqueKey=%s]", a_reqAccountLogin.m_uniqueID.c_str(), a_reqAccountLogin.m_uniqueKey.c_str());
            return false;
        } if (res > 0) {
            BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "账号已经存在[m_uniqueID=%s][m_uniqueKey=%s]", a_reqAccountLogin.m_uniqueID.c_str(), a_reqAccountLogin.m_uniqueKey.c_str());
            return false;
        }

		BSLib::uint64 accountID = 0;
		if (!_registerFastAccountToDB(a_reqAccountLogin.m_uniqueID, a_reqAccountLogin.m_uniqueKey, a_reqAccountLogin.m_channelID, a_reqAccountLogin.m_platform, accountID)) {
			return false;
		}
		return true;

//         GSLib::DBSystem::LG::SAccountInsertData data;
//         //BSLibSprintf(data.m_accountName,sizeof(char)*(GSLIB_TEXT_MAX_ACCOUNT_NAME + 1),"%s",a_reqRegisterAccount.m_accountName.c_str());
//         //BSLibSprintf(data.m_accountPassword,sizeof(char)*(GSLIB_TEXT_MAX_ACCOUNT_PASSWORD + 1),"%s",a_reqRegisterAccount.m_accountPwd.c_str());
//         memset(data.m_accountName,0,sizeof(data.m_accountName));
//         memset(data.m_accountPassword,0,sizeof(data.m_accountPassword));
//         BSLibSprintf(data.m_uniqueID,sizeof(char)*(GSLIB_TEXT_MAX_ACCOUNT_UNIQUEID + 1),"%s",a_reqAccountLogin.m_uniqueID.c_str());
//         BSLibSprintf(data.m_uniqueKey,sizeof(char)*(GSLIB_TEXT_MAX_ACCOUNT_UNIQUEKEY + 1),"%s",a_reqAccountLogin.m_uniqueKey.c_str());
//         BSLibSprintf(data.m_platform,sizeof(char)*(GSLIB_TEXT_MAX_PLATFORM + 1),"%s",a_reqAccountLogin.m_platform.c_str());
//         data.m_channelID = a_reqAccountLogin.m_channelID;
//         data.m_bindFlag = bindFlag;
//         data.m_registerTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
// 
//         BSLib::Utility::CStream stream;
//         stream.reset();
//         stream.write((const char*)&data,sizeof(data));
// 
//         if(!GSLib::DBSystem::LG::CDBSystemLG::singleton().insertAccountData(stream,NULL)){
//             return false;
//         }
// 
//         return true;
    }

    return false;
}

bool CLoginSystemLG::_fastRegisterAccount(CMsgLoginSystemGC2LGReqGetAccountToken& a_reqAccountLogin)
{
	//BSLib::Utility::CMutexFun fun(&m_mutex);

	GSLib::LoginSystem::ELoginType loginType = (GSLib::LoginSystem::ELoginType)a_reqAccountLogin.m_loginType;

	GSLib::DBSystem::LG::SAccountData accountData;
	if(loginType == GSLib::LoginSystem::ELOGINTYPE_FAST_LOGIN){
		BSLIB_LOG_INFO(ETT_GSLIB_LOGINSYSTEM, "快速注册[m_uniqueID=%s][m_uniqueKey=%s]", a_reqAccountLogin.m_uniqueID.c_str(), a_reqAccountLogin.m_uniqueKey.c_str());
		const BSLib::uint32 bindFlag = 0;
		int res = GSLib::DBSystem::LG::CDBSystemLG::singleton().selectFastLoginAccountData(a_reqAccountLogin.m_uniqueID,a_reqAccountLogin.m_uniqueKey,bindFlag, accountData);

		if (res < 0) {
			BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "查询账号失败[m_uniqueID=%s][m_uniqueKey=%s]", a_reqAccountLogin.m_uniqueID.c_str(), a_reqAccountLogin.m_uniqueKey.c_str());
			return false;
		} if (res > 0) {
			BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "账号已经存在[m_uniqueID=%s][m_uniqueKey=%s]", a_reqAccountLogin.m_uniqueID.c_str(), a_reqAccountLogin.m_uniqueKey.c_str());
			return false;
		}

		BSLib::uint64 accountID = 0;
		if (!_registerFastAccountToDB(a_reqAccountLogin.m_uniqueID, a_reqAccountLogin.m_uniqueKey, a_reqAccountLogin.m_channelID, a_reqAccountLogin.m_platform, accountID)) {
			return false;
		}
		return true;

// 		GSLib::DBSystem::LG::SAccountInsertData data;
// 		memset(data.m_accountName,0,sizeof(data.m_accountName));
// 		memset(data.m_accountPassword,0,sizeof(data.m_accountPassword));
// 		BSLibSprintf(data.m_uniqueID,sizeof(char)*(GSLIB_TEXT_MAX_ACCOUNT_UNIQUEID + 1),"%s",a_reqAccountLogin.m_uniqueID.c_str());
// 		BSLibSprintf(data.m_uniqueKey,sizeof(char)*(GSLIB_TEXT_MAX_ACCOUNT_UNIQUEKEY + 1),"%s",a_reqAccountLogin.m_uniqueKey.c_str());
// 		BSLibSprintf(data.m_platform,sizeof(char)*(GSLIB_TEXT_MAX_PLATFORM + 1),"%s",a_reqAccountLogin.m_platform.c_str());
// 		data.m_channelID = a_reqAccountLogin.m_channelID;
// 		data.m_bindFlag = bindFlag;
//         data.m_registerTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
// 
// 		BSLib::Utility::CStream stream;
// 		stream.reset();
// 		stream.write((const char*)&data,sizeof(data));
// 
// 		if(!GSLib::DBSystem::LG::CDBSystemLG::singleton().insertAccountData(stream,NULL)){
// 			return false;
// 		}
// 
// 		return true;
	}

	return false;
}




bool CLoginSystemLG::_verifyNormalGetAccountToken(GFLib::StubID a_stubID, std::string& accountLoginIP, CMsgLoginSystemGC2LGReqGetAccountToken& a_reqAccountLogin, CMsgLoginSystemLG2GCAckGetAccountToken& a_ackAccountLogin)
{
    //BSLib::Utility::CMutexFun fun(&m_mutex);

    if (m_superServerID == GFLib::INVALID_SERVERID){
        a_ackAccountLogin.m_state = EGETACCOUNTTAKEN_SERVER_ERROR;
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyNormalGetAccountToken]Super服务器没有启动");
        return false;
    }

    GSLib::DBSystem::LG::SAccountData accountData;
    int res = GSLib::DBSystem::LG::CDBSystemLG::singleton().selectAccountData(a_reqAccountLogin.m_accountName, accountData);
    if (res < 0) {
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyNormalGetAccountToken]查询账号失败[AccountName=%s]", a_reqAccountLogin.m_accountName.c_str());
        a_ackAccountLogin.m_state = EGETACCOUNTTAKEN_SERVER_ERROR;
        return false;
    } if (res == 0) {
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyNormalGetAccountToken]账号不存在[AccountName=%s]", a_reqAccountLogin.m_accountName.c_str());
        a_ackAccountLogin.m_state = ELOGINRESULT_ACCOUNT_NOTEXIST;
        return false;
    }
    if (accountData.m_accountPassword != a_reqAccountLogin.m_accountPwd) {
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyNormalGetAccountToken]验证密码不合法[AccountName=%s]", a_reqAccountLogin.m_accountName.c_str());
        a_ackAccountLogin.m_state = EGETACCOUNTTAKEN_PASSWORD_ERROR;
        return false;
    }

    SAccountLoginLGInfor accountInfor;
    accountInfor.m_stubID = a_stubID;
    accountInfor.m_sessionID = 0;
    accountInfor.m_accountName = a_reqAccountLogin.m_accountName;
    accountInfor.m_channelID = a_reqAccountLogin.m_channelID;
    accountInfor.m_accountLoginIP = accountLoginIP;
    accountInfor.m_accountKey.setKey(accountData.m_accountID, 0);
    if (!CAccountLoginLGInforMgr::singleton().registerAccountLoginInfor(accountInfor)) {
        a_ackAccountLogin.m_state = EGETACCOUNTTAKEN_SERVER_ERROR;
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "保存登陆信息失败[AccountName=%s]", a_reqAccountLogin.m_accountName.c_str());
        return false;
    }

    BSLib::Utility::CUUID uuidToken;
    BSLib::Utility::CUUID::generate(uuidToken);

    CMsgLoginSystemLG2SPReqRegisterToken reqRegisterTocken2SP;
    reqRegisterTocken2SP.m_loginSession = accountInfor.m_sessionID;
    reqRegisterTocken2SP.m_accountKey = accountInfor.m_accountKey;
    reqRegisterTocken2SP.m_accountName = a_reqAccountLogin.m_accountName;
    reqRegisterTocken2SP.m_token = uuidToken.unparse();
    if (!GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_superServerID, reqRegisterTocken2SP)){
        a_ackAccountLogin.m_state = EGETACCOUNTTAKEN_SERVER_ERROR;
        CAccountLoginLGInforMgr::singleton().removeAccountLoginInfor(a_stubID);
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "发送消息失败[SuperServer=%s][Account=%s]", reqRegisterTocken2SP.toString().c_str(), a_reqAccountLogin.m_accountName.c_str());
        return false;
    }

    BSLIB_LOG_INFO(ETT_GSLIB_LOGINSYSTEM, "进入Super请求[AccountName=%s][SessionID=%d]",
        a_reqAccountLogin.m_accountName.c_str(),
        accountInfor.m_sessionID);

    return true;
}

bool CLoginSystemLG::_verifyFastGetAccountToken(GFLib::StubID a_stubID, std::string& accountLoginIP, CMsgLoginSystemGC2LGReqGetAccountToken& a_reqAccountLogin, CMsgLoginSystemLG2GCAckGetAccountToken& a_ackAccountLogin)
{
    //BSLib::Utility::CMutexFun fun(&m_mutex);

    if (m_superServerID == GFLib::INVALID_SERVERID){
        a_ackAccountLogin.m_state = EGETACCOUNTTAKEN_SERVER_ERROR;
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyFastGetAccountToken]Super服务器没有启动");
        return false;
    }

    GSLib::DBSystem::LG::SAccountData accountData;
    const BSLib::uint32 bindFlag = 0;
    int res = GSLib::DBSystem::LG::CDBSystemLG::singleton().selectFastLoginAccountData(a_reqAccountLogin.m_uniqueID,a_reqAccountLogin.m_uniqueKey,bindFlag, accountData);
    if (res < 0) {
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyFastGetAccountToken]查询账号失败[m_uniqueID=%s]", a_reqAccountLogin.m_uniqueID.c_str());
        a_ackAccountLogin.m_state = EGETACCOUNTTAKEN_SERVER_ERROR;
        return false;
    } if (res == 0) {
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "[verifyFastGetAccountToken]账号不存在[m_uniqueID=%s]", a_reqAccountLogin.m_uniqueID.c_str());
        a_ackAccountLogin.m_state = EGETACCOUNTTAKEN_ACCOUNT_NOTEXIST;
        return false;
    }

    SAccountLoginLGInfor accountInfor;
    accountInfor.m_stubID = a_stubID;
    accountInfor.m_sessionID = 0;
    accountInfor.m_accountName = a_reqAccountLogin.m_uniqueID;
    accountInfor.m_channelID = a_reqAccountLogin.m_channelID;
    accountInfor.m_accountLoginIP = accountLoginIP;
    accountInfor.m_accountKey.setKey(accountData.m_accountID, 0);
    if (!CAccountLoginLGInforMgr::singleton().registerAccountLoginInfor(accountInfor)) {
        a_ackAccountLogin.m_state = EGETACCOUNTTAKEN_SERVER_ERROR;
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "保存登陆信息失败[AccountName=%s]", a_reqAccountLogin.m_uniqueID.c_str());
        return false;
    }

    BSLib::Utility::CUUID uuidToken;
    BSLib::Utility::CUUID::generate(uuidToken);

    CMsgLoginSystemLG2SPReqRegisterToken reqRegisterTocken2SP;
    reqRegisterTocken2SP.m_loginSession = accountInfor.m_sessionID;
    reqRegisterTocken2SP.m_accountKey = accountInfor.m_accountKey;
    reqRegisterTocken2SP.m_accountName = a_reqAccountLogin.m_uniqueID;
    reqRegisterTocken2SP.m_token = uuidToken.unparse();
    if (!GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_superServerID, reqRegisterTocken2SP)){
        a_ackAccountLogin.m_state = EGETACCOUNTTAKEN_SERVER_ERROR;
        CAccountLoginLGInforMgr::singleton().removeAccountLoginInfor(a_stubID);
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "发送消息失败[SuperServer=%s][Account=%s]", reqRegisterTocken2SP.toString().c_str(), a_reqAccountLogin.m_uniqueID.c_str());
        return false;
    }

    BSLIB_LOG_INFO(ETT_GSLIB_LOGINSYSTEM, "进入Super请求[AccountName=%s][SessionID=%d]",
        a_reqAccountLogin.m_uniqueID.c_str(),
        accountInfor.m_sessionID);

    return true;
}

bool CLoginSystemLG::_init()
{
	CZoneInforMgr::singleton().init();
	return GFLib::CommonServer::ICommonSystem::_init();
}

void CLoginSystemLG::_final()
{
	CZoneInforMgr::singleton().final();
	GFLib::CommonServer::ICommonSystem::_final();
}

bool CLoginSystemLG::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{   
    GFLib::CommonServer::ICommonServer* srv = GFLib::CommonServer::ICommonServer::getCommonServer();
    std::string srvName = srv->getServerTypeName();
    m_codeFilterMode = BSLib::Framework::CSysConfig::singleton().getValueInt(srvName, "ActivationCodeMode");

	return GFLib::CommonServer::ICommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CLoginSystemLG::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemCN2LGAckAccountLogin, &BSLib::Framework::CreateCMessage<CMsgLoginSystemCN2LGAckAccountLogin>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemCN2LGAckAccountLogin, &CLoginSystemLG::_onMsgLoginSystemCN2LGAckAccountLogin, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemSP2LGAckRegisterToken, &BSLib::Framework::CreateCMessage<CMsgLoginSystemSP2LGAckRegisterToken>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemSP2LGAckRegisterToken, &CLoginSystemLG::_onMsgLoginSystemSP2LGAckRegisterToken, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDLoginSystemSP2LGAckCheckToken, &BSLib::Framework::CreateCMessage<CMsgLoginSystemSP2LGAckCheckToken>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDLoginSystemSP2LGAckCheckToken, &CLoginSystemLG::_onMsgLoginSystemSP2LGAckCheckToken, this);

	return GFLib::CommonServer::ICommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CLoginSystemLG::_startSystem()
{
	return GFLib::CommonServer::ICommonSystem::_startSystem();
}

void CLoginSystemLG::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::ServerType serverType = a_serverID.ICommonServer_getServerType();
	switch (serverType)
	{
	case SRVTYPE_CENTERSERVER:
		CZoneInforMgr::singleton().centerServerEnter(a_serverID);
		break;
	case SRVTYPE_SUPERSERVER:
		m_superServerID = a_serverID;
		break;
	} 
}

void CLoginSystemLG::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::ServerType serverType = a_serverID.ICommonServer_getServerType();
	switch (serverType)
	{
	case SRVTYPE_CENTERSERVER:
		CZoneInforMgr::singleton().centerServerLeave(a_serverID);
		break;
	case SRVTYPE_SUPERSERVER:
		m_superServerID = GFLib::INVALID_SERVERID;
		break;
	} 
}

void CLoginSystemLG::_onMsgLoginSystemCN2LGAckAccountLogin(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);

	CMsgLoginSystemCN2LGAckAccountLogin* ackAccountLogin = (CMsgLoginSystemCN2LGAckAccountLogin*)msg;
	
	CAccountLoginLGInforMgr::singleton().checkCN2LGAckAccountLogin(*ackAccountLogin);
}

void CLoginSystemLG::_onMsgLoginSystemSP2LGAckRegisterToken(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	
	CMsgLoginSystemSP2LGAckRegisterToken* reqRegisterToken = (CMsgLoginSystemSP2LGAckRegisterToken*)msg;

	CAccountLoginLGInforMgr::singleton().checkSP2LGAckRegisterToken(*reqRegisterToken);
}

void CLoginSystemLG::_onMsgLoginSystemSP2LGAckCheckToken(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);

	CMsgLoginSystemSP2LGAckCheckToken* reqCheckToken = (CMsgLoginSystemSP2LGAckCheckToken*)msg;

	CAccountLoginLGInforMgr::singleton().checkSP2LGAckCheckToken(*reqCheckToken);
}

bool CLoginSystemLG::_registerNormalAccountToDB(const std::string& a_accountName, const std::string& a_accountPwd, BSLib::uint32 a_channelID, const std::string& a_platform, const std::string& a_activationCode, BSLib::uint64& a_accountID)
{
	GSLib::DBSystem::LG::SAccountInsertData data;
	memset(&data, 0, sizeof(data));
	
	BSLibSprintf(data.m_accountName, sizeof(data.m_accountName), "%s", a_accountName.c_str());
	BSLibSprintf(data.m_accountPassword, sizeof(data.m_accountPassword),"%s", a_accountPwd.c_str());
	BSLibSprintf(data.m_platform, sizeof(data.m_platform), "%s", a_platform.c_str());
	if(m_codeFilterMode)
	{
		BSLibSprintf(data.m_activationCode, sizeof(data.m_activationCode),"%s", a_activationCode.c_str());
	}
	data.m_channelID = a_channelID;
	data.m_registerTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();

	BSLib::Utility::CStream stream;
	stream.reset();
	stream.write((const char*)&data,sizeof(data));

	if(!GSLib::DBSystem::LG::CDBSystemLG::singleton().insertAccountData(stream, &a_accountID)){
		return false;
	}
	return true;
}

bool CLoginSystemLG::_registerFastAccountToDB(const std::string& a_uniqueID, const std::string& a_uniqueKey, BSLib::uint32 a_channelID, const std::string& a_platform, BSLib::uint64& a_accountID)
{
	GSLib::DBSystem::LG::SAccountInsertData data;
	memset(&data, 0, sizeof(data));

	BSLibSprintf(data.m_uniqueID, sizeof(data.m_uniqueID), "%s", a_uniqueID.c_str());
	BSLibSprintf(data.m_uniqueKey, sizeof(data.m_uniqueKey),"%s", a_uniqueKey.c_str());
	BSLibSprintf(data.m_platform, sizeof(data.m_platform), "%s", a_platform.c_str());

	data.m_channelID = a_channelID;
	data.m_registerTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();

	BSLib::Utility::CStream stream;
	stream.reset();
	stream.write((const char*)&data,sizeof(data));

	if(!GSLib::DBSystem::LG::CDBSystemLG::singleton().insertAccountData(stream, &a_accountID)){
		return false;
	}
	return true;
}


}//LG

}//LoginSystem

}//GSLib

