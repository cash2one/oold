//////////////////////////////////////////////////////////////////////
//	created:	2014/08/04
//	filename: 	src\GSLib\loginSystem\netPlayer.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <stdarg.h>
#include <GSLib/loginSystem/netPlayer.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/loginSystem/msgLoginSystem.h>
#include <GSLib/tracer.h>
#include <GSLib/serverType.h>
#include <BSLib/utility/convert.h>

namespace GSLib
{

namespace LoginSystem
{


CNetPlayer::CNetPlayer(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName)
: m_accountKey(a_accountKey)
, m_accountName(a_accountName)
{
	;
}

CNetPlayer::~CNetPlayer()
{
	;
}

bool CNetPlayer::executeMessage(BSLib::Framework::SMsgLabel* a_msgLabel, BSLib::Framework::SMessage* a_msg)
{
	return m_msgExecMgr.executeMessage(a_msgLabel, a_msg);
}

void CNetPlayer::outputGameLog(const std::string& a_gameLable, const char* a_format, ...)
{
	std::string strFormat;

	va_list args;
	va_start(args, a_format);
		
	BSLib::Utility::stringFormat(strFormat, a_format, args);

	va_end(args);

    std::string accountName = "";
#if defined(WIN32)
    BSLib::Utility::CConvert::utf8ToGB2312(accountName,m_accountName);
#else
   accountName = m_accountName;
#endif

	BSLIB_LOG_INFOR(ETT_GSLIB_GAME, "[%s]%s[AccountName=%s]%s", 
		a_gameLable.c_str(), 
		m_accountKey.toLogString().c_str(), 
		accountName.c_str(),
		strFormat.c_str());
}

bool CNetPlayer::broadcastMsgToClient(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	CMsgLoginSystemXS2GTNtfBroadcastMsg ntfBroadcastMsg;
	ntfBroadcastMsg.m_subMsg.write((char*)a_msg, a_msgSize);

	return GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServerType(SRVTYPE_GATESERVER, ntfBroadcastMsg);
}

bool CNetPlayer::broadcastMsgToClient(GFLib::CMessage& a_msg)
{
	CMsgLoginSystemXS2GTNtfBroadcastMsg ntfBroadcastMsg;
	if (!a_msg.serializeTo(ntfBroadcastMsg.m_subMsg)) {
		return false;
	}
	return GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServerType(SRVTYPE_GATESERVER, ntfBroadcastMsg);
}

void CNetPlayer::_cbInitMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayer::_cbInitMsg[Account=%s]", m_accountName.c_str());
}

void CNetPlayer::_initMsg()
{
	_cbInitMsg(&m_msgExecMgr);
}

}//LoginSystem

}//GSLib