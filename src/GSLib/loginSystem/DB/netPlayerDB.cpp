#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/loginSystem/DB/netPlayerDB.h>
#include <GSLib/tracer.h>
#include "DB/accountLoginDBInforMgr.h"

namespace GSLib
{

namespace LoginSystem
{

namespace DB
{


CNetPlayerDB::CNetPlayerDB(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName)
: CNetPlayer(a_accountKey, a_accountName)
, m_accountPtr(NULL)
{
	;
}

CNetPlayerDB::~CNetPlayerDB()
{
	;
}

bool CNetPlayerDB::sendMsgToClient(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
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

bool CNetPlayerDB::sendMsgToClient(GFLib::CMessage& a_msg)
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

bool CNetPlayerDB::sendMsgToGateServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
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

bool CNetPlayerDB::sendMsgToGateServer(GFLib::CMessage& a_msg)
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

bool CNetPlayerDB::sendMsgToCenterServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	if (!m_centerServerID.isValid()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
		return false;
	}
	if (m_accountPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
		return false;
	}
	return m_accountPtr->sendMsgToServer(m_centerServerID, a_msg, a_msgSize);
}

bool CNetPlayerDB::sendMsgToCenterServer(GFLib::CMessage& a_msg)
{
	if (!m_centerServerID.isValid()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&a_msg).c_str());
		return false;
	}
	if (m_accountPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&a_msg).c_str());
		return false;
	}
	return m_accountPtr->sendMsgToServer(m_centerServerID, a_msg);
}

bool CNetPlayerDB::sendMsgToGameServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
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

bool CNetPlayerDB::sendMsgToGameServer(GFLib::CMessage& a_msg)
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

void CNetPlayerDB::_cbInitPlayer()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerDB::_cbInitPlayer[Account=%s]", getAccountName().c_str());

	_finishInitPlayer(ELOGINRESULT_SUCCESS);
}

void CNetPlayerDB::_cbFinalPlayer()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerDB::_cbFinalPlayer[Account=%s]", getAccountName().c_str());
}

void CNetPlayerDB::_cbPlayerOnline()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerDB::_cbPlayerOnline[Account=%s]", getAccountName().c_str());
}

void CNetPlayerDB::_cbPlayerOffline()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerDB::_cbPlayerOffline[Account=%s]", getAccountName().c_str());
}

void CNetPlayerDB::_quit()
{
	GFLib::SAccountKey accountKey = getAccountKey();
	CAccountLoginDBInforMgr::singleton().checkNtfAccountQuit(accountKey);
}

void CNetPlayerDB::_finishInitPlayer(ELoginResult a_result)
{
	GFLib::SAccountKey accountKey = getAccountKey();
	CAccountLoginDBInforMgr::singleton().finishInitPlayer(accountKey, a_result);
}

bool CNetPlayerDB::_transferMsg(const GFLib::ServerType& a_serverType, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "转发消息失败[%s][%s]", a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
	return false;
}

}//DB

}//LoginSystem

}//GSLib


