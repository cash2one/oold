//////////////////////////////////////////////////////////////////////
//	created:	2014/07/28
//	filename: 	GSLib\loginSystem\GM\netPlayerGM.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/loginSystem/GM/netPlayerGM.h>
#include <GSLib/tracer.h>
#include "GM/accountLoginGMInforMgr.h"

namespace GSLib
{

namespace LoginSystem
{

namespace GM
{


CNetPlayerGM::CNetPlayerGM(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName)
: CNetPlayer(a_accountKey, a_accountName)
, m_accountPtr(NULL)
{
	;
}


CNetPlayerGM::~CNetPlayerGM()
{
	;
}

bool CNetPlayerGM::sendMsgToClient(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
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

bool CNetPlayerGM::sendMsgToClient(GFLib::CMessage& a_msg)
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

bool CNetPlayerGM::sendMsgToGateServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
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

bool CNetPlayerGM::sendMsgToGateServer(GFLib::CMessage& a_msg)
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

bool CNetPlayerGM::sendMsgToDataServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
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

bool CNetPlayerGM::sendMsgToDataServer(GFLib::CMessage& a_msg)
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

bool CNetPlayerGM::sendMsgToCenterServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
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

bool CNetPlayerGM::sendMsgToCenterServer(GFLib::CMessage& a_msg)
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

void CNetPlayerGM::_cbInitPlayer()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerGM::_cbInitPlayer[Account=%s]", getAccountName().c_str());
	_finishInitPlayer(ELOGINRESULT_SUCCESS);
}

void CNetPlayerGM::_cbFinalPlayer()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerGM::_cbFinalPlayer[Account=%s]", getAccountName().c_str());
}

void CNetPlayerGM::_cbPlayerOnline()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerGM::_cbPlayerOnline[Account=%s]", getAccountName().c_str());
}

void CNetPlayerGM::_cbPlayerOffline()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerGM::_cbPlayerOffline[Account=%s]", getAccountName().c_str());
}

void CNetPlayerGM::_quit()
{
	CMsgLoginSystemGM2CNNtfAccountQuit ackAccountQuit;
	ackAccountQuit.m_accountKey = getAccountKey();
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_centerServerID, ackAccountQuit);
}

void CNetPlayerGM::_finishInitPlayer(ELoginResult a_result)
{
	GFLib::SAccountKey accountKey = getAccountKey();
	CAccountLoginGMInforMgr::singleton().finishInitPlayer(accountKey, a_result);
}

bool CNetPlayerGM::_transferMsg(const GFLib::ServerType& a_serverType, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "转发消息失败[%s][%s]", a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
	return false;
}

}//GM

}//LoginSystem

}//GSLib

