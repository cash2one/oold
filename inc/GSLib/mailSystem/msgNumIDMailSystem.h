//////////////////////////////////////////////////////////////////////
//	created:	2014/10/09
//	filename: 	GSLib\mailSystem\msgNumIDMailSystem.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_MAILSYSTEM_MSGNUMIDMAILSYSTEM_H__
#define __GSLIB_MAILSYSTEM_MSGNUMIDMAILSYSTEM_H__

#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace MailSystem
{

	enum EMsgNumIDMailSystem
	{
		EMSGID_MAILSYSTEM_GM2GC_NTF_PUSH_MAIL	= 3,
		EMSGID_MAILSYSTEM_GC2GM_REQ_GET_ATTACH,
		EMSGID_MAILSYSTEM_GM2GC_ACK_GET_ATTACH,
		EMSGID_MAILSYSTEM_GC2GM_REQ_OPERATE_MAIL,
		EMSGID_MAILSYSTEM_GM2GC_ACK_OPERATE_MAIL,

		// 内部
		EMSGID_MAILSYSTEM_GM2CN_REQ_UNRECEIVED_MAIL,
		EMSGID_MAILSYSTEM_CN2GM_ACK_UNRECEIVED_MAIL,
		EMSGID_MAILSYSTEM_GM2CN_NTF_DEL_MAIL,
		EMSGID_MAILSYSTEM_CN2GM_NTF_NEW_SYSTEM_MAIL,
		EMSGID_MAILSYSTEM_CM2GM_NTF_NEW_ROLE_MAIL,
	};


	enum EMailSystemResult
	{
		EMAILSYSTEM_RESUlT_SUCCESS = 0,
		EMAILSYSTEM_RESUlT_FAIL = 1,
	};

	enum EMailSystemOPType
	{
		EMAILSYSTEM_OP_READ = 1,
		EMAILSYSTEM_OP_DEL,
		EMAILSYSTEM_OP_REQ	// 请求全体邮件,复用消息之用
	};

	enum EMailSystemUpdateType
	{
		EMAILSYSTEM_UPDATE_TOTAL = 1,
		EMAILSYSTEM_UPDATE_DELTA
	};


}//MailSystem

}//GSLib

#endif//__GSLIB_MAILSYSTEM_MSGNUMIDMAILSYSTEM_H__
