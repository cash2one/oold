#include <GFLib/commonServer/stubMgr.h>
#include <GSLib/tracer.h>
#include <GSLib/loginSystem/msgLoginSystem.h>
#include <GSLib/tracer.h>
#include "SP/accountTokenInforMgr.h"


namespace GSLib
{

namespace LoginSystem
{

namespace SP
{
BSLIB_SINGLETON_DEFINE(CAccountTokenInforMgr);

CAccountTokenInforMgr::CAccountTokenInforMgr()
{
	;
}

CAccountTokenInforMgr::~CAccountTokenInforMgr()
{
	;
}

bool CAccountTokenInforMgr::registerAccountTokenInfor(SAccountTokenInfor& a_accountInfor)
{
	SAccountTokenInfor* tokenInfor = NULL;
	m_accountInforMgr.getValue(a_accountInfor.m_accountKey.getAccountID(), tokenInfor);
	if (tokenInfor == NULL) {
		tokenInfor = new SAccountTokenInfor;
		if (tokenInfor == NULL) {
			return false;
		}
		tokenInfor->m_accountKey = a_accountInfor.m_accountKey;
		tokenInfor->m_accountName = a_accountInfor.m_accountName;
		tokenInfor->m_token = a_accountInfor.m_token;
		m_accountInforMgr.setValue(a_accountInfor.m_accountKey.getAccountID(), tokenInfor);

		BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "注册账号Token[Token=%s][AccountName=%s][AccountKey=%s]",
			a_accountInfor.m_token.c_str(),
			a_accountInfor.m_accountName.c_str(),
			a_accountInfor.m_accountKey.toLogString().c_str());

		return true;
	}
	tokenInfor->m_accountKey = a_accountInfor.m_accountKey;
	tokenInfor->m_accountName = a_accountInfor.m_accountName;
	tokenInfor->m_token = a_accountInfor.m_token;

	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "注册账号Token[Token=%s][AccountName=%s][AccountKey=%s]",
		a_accountInfor.m_token.c_str(),
		a_accountInfor.m_accountName.c_str(),
		a_accountInfor.m_accountKey.toLogString().c_str());

	return true;
}

// bool CAccountTokenInforMgr::checkAccountTokenInfor(SAccountTokenInfor& a_accountInfor, )
// {
//     SAccountTokenInfor* tokenInfor = NULL;
//     m_accountInforMgr.getValue(a_accountInfor.m_token, tokenInfor);
//     if (tokenInfor == NULL) {
//         BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "Token无效[Token=%s][AccountName=%s]%s",
//             a_accountInfor.m_token.c_str(),
//             a_accountInfor.m_accountName.c_str(),
//             a_accountInfor.m_accountKey.toLogString().c_str());
//         return false;
//     }
// 
// 
//     if (tokenInfor->m_accountKey != a_accountInfor.m_accountKey) {
// 		if(tokenInfor->m_accountKey.getAccountID() == a_accountInfor.m_accountKey.getAccountID()){
// 			tokenInfor->m_accountKey.setZoneID(a_accountInfor.m_accountKey.getZoneID());
// 			BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "验证账号OK [Token=%s][AccountName=%s][AccountKey=%s]",
// 				a_accountInfor.m_token.c_str(),
// 				a_accountInfor.m_accountName.c_str(),
// 				a_accountInfor.m_accountKey.toLogString().c_str());
// 			return true;
// 		}
// 		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "AccountKey不一致[Token=%s][AccountName=%s][AccountKey=%s]",
// 			a_accountInfor.m_token.c_str(),
// 			a_accountInfor.m_accountName.c_str(),
// 			a_accountInfor.m_accountKey.toLogString().c_str());
// 		return false;
//     }
// 
//     BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "验证账号Token[Token=%s][AccountName=%s]%s",
//         a_accountInfor.m_token.c_str(),
//         a_accountInfor.m_accountName.c_str(),
//         a_accountInfor.m_accountKey.toLogString().c_str());
// 
// 	return true;
// }

bool CAccountTokenInforMgr::checkAccountTokenInfor(SAccountTokenInfor& a_accountInfor)
{
    SAccountTokenInfor* tokenInfor = NULL;
    m_accountInforMgr.getValue(a_accountInfor.m_accountKey.getAccountID(), tokenInfor);
    if (tokenInfor == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "Token无效[Token=%s][AccountName=%s]%s",
            a_accountInfor.m_token.c_str(),
            a_accountInfor.m_accountName.c_str(),
            a_accountInfor.m_accountKey.toLogString().c_str());
        return false;
    }


    if (tokenInfor->m_accountKey != a_accountInfor.m_accountKey) {
        
        if(tokenInfor->m_accountKey.getAccountID() == a_accountInfor.m_accountKey.getAccountID()){
            tokenInfor->m_accountKey.setZoneID(a_accountInfor.m_accountKey.getZoneID());
            BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "验证账号OK [Token=%s][AccountName=%s][AccountKey=%s]",
                a_accountInfor.m_token.c_str(),
                a_accountInfor.m_accountName.c_str(),
                a_accountInfor.m_accountKey.toLogString().c_str());
            return true;
        }
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "AccountKey不一致[Token=%s][AccountName=%s][AccountKey=%s]",
            a_accountInfor.m_token.c_str(),
            a_accountInfor.m_accountName.c_str(),
            a_accountInfor.m_accountKey.toLogString().c_str());
        return false;
    }

    BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "验证账号Token OK [Token=%s][AccountName=%s][AccountKey=%s]",
        a_accountInfor.m_token.c_str(),
        a_accountInfor.m_accountName.c_str(),
        a_accountInfor.m_accountKey.toLogString().c_str());

    return true;
}

}//SP

}//LoginSystem

}//GSLib

