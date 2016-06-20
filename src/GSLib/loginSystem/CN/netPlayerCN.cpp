//////////////////////////////////////////////////////////////////////
//	created:	2014/07/28
//	filename: 	GSLib\loginSystem\CN\netPlayerCN.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/loginSystem/CN/netPlayerCN.h>
#include <GSLib/tracer.h>
#include "CN/accountLoginCNInforMgr.h"

namespace GSLib
{

namespace LoginSystem
{

namespace CN
{

CNetPlayerCN::CNetPlayerCN(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName)
: CNetPlayer(a_accountKey, a_accountName)
, m_accountPtr(NULL)
{
	;
}

CNetPlayerCN::~CNetPlayerCN()
{
	;
}

bool CNetPlayerCN::sendMsgToClient(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	if (!m_gateServerID.isValid()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
		return false;
	}
	if (m_accountPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
		return false;
	}
	return m_accountPtr->sendMsgToClient(m_gateServerID, a_msg, a_msgSize);
}

bool CNetPlayerCN::sendMsgToClient(GFLib::CMessage& a_msg)
{
	if (!m_gateServerID.isValid()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&a_msg).c_str());
		return false;
	}
	if (m_accountPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&a_msg).c_str());
		return false;
	}
	return m_accountPtr->sendMsgToClient(m_gateServerID, a_msg);
}

bool CNetPlayerCN::sendMsgToGateServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	if (!m_gateServerID.isValid()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
		return false;
	}
	if (m_accountPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
		return false;
	}
	return m_accountPtr->sendMsgToServer(m_gateServerID, a_msg, a_msgSize);
}

bool CNetPlayerCN::sendMsgToGateServer(GFLib::CMessage& a_msg)
{
	if (!m_gateServerID.isValid()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&a_msg).c_str());
		return false;
	}
	if (m_accountPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&a_msg).c_str());
		return false;
	}
	return m_accountPtr->sendMsgToServer(m_gateServerID, a_msg);
}

bool CNetPlayerCN::sendMsgToDataServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	if (!m_dataServerID.isValid()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
		return false;
	}
	if (m_accountPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
		return false;
	}
	return m_accountPtr->sendMsgToServer(m_dataServerID, a_msg, a_msgSize);
}

bool CNetPlayerCN::sendMsgToDataServer(GFLib::CMessage& a_msg)
{
	if (!m_dataServerID.isValid()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&a_msg).c_str());
		return false;
	}
	if (m_accountPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&a_msg).c_str());
		return false;
	}
	return m_accountPtr->sendMsgToServer(m_dataServerID, a_msg);
}

bool CNetPlayerCN::sendMsgToGameServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	if (!m_gameServerID.isValid()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
		return false;
	}
	if (m_accountPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
		return false;
	}
	return m_accountPtr->sendMsgToServer(m_gameServerID, a_msg, a_msgSize);
}

bool CNetPlayerCN::sendMsgToGameServer(GFLib::CMessage& a_msg)
{
	if (!m_gameServerID.isValid()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&a_msg).c_str());
		return false;
	}
	if (m_accountPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&a_msg).c_str());
		return false;
	}
	return m_accountPtr->sendMsgToServer(m_gameServerID, a_msg);
}

void CNetPlayerCN::_cbInitPlayer()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerCN::_cbInitPlayer[Account=%s]", getAccountName().c_str());

	_finishInitPlayer(ELOGINRESULT_SUCCESS);
}

void CNetPlayerCN::_cbFinalPlayer()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerCN::_cbFinalPlayer[Account=%s]", getAccountName().c_str());
}

void CNetPlayerCN::_cbPlayerOnline()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerCN::_cbPlayerOnline[Account=%s]", getAccountName().c_str());
}

void CNetPlayerCN::_cbPlayerOffline()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerCN::_cbPlayerOffline[Account=%s]", getAccountName().c_str());
}

void CNetPlayerCN::_quit()
{
	GFLib::SAccountKey accountKey = getAccountKey();
	CAccountLoginCNInforMgr::singleton().checkNtfAccountQuit(accountKey);
}

void CNetPlayerCN::_finishInitPlayer(ELoginResult a_result)
{
	GFLib::SAccountKey accountKey = getAccountKey();
	CAccountLoginCNInforMgr::singleton().checkCNInitPlayer(accountKey, a_result);
}

bool CNetPlayerCN::_transferMsg(const GFLib::ServerType& a_serverType, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "转发消息失败[%s][%s]", a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
	return false;
}

}//CN

}//LoginSystem

}//GSLib

