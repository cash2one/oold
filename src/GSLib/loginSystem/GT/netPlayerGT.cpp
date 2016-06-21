#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/message/msgServerLink.h>
#include <GFLib/commonServer/stubMgr.h>
#include <GSLib/loginSystem/GT/netPlayerGT.h>
#include <GSLib/tracer.h>
#include "GT/accountLoginGTInforMgr.h"

namespace GSLib
{

namespace LoginSystem
{

namespace GT
{


CNetPlayerGT::CNetPlayerGT(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName)
: CNetPlayer(a_accountKey, a_accountName)
, m_stubID(GFLib::INVALID_STUBID)
, m_accountPtr(NULL)
{
	;
}

CNetPlayerGT::~CNetPlayerGT()
{
	;
}

bool CNetPlayerGT::sendMsgToClient(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	if (m_stubID == GFLib::INVALID_STUBID) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
		return false;
	}
	GFLib::CommonServer::CStubPtr stubPtr = GFLib::CommonServer::CStubMgr::singleton().getCommonStubByStubID(m_stubID);
	if (stubPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
		return false;
	}
	return stubPtr->sendMsg(a_msg, a_msgSize);
}

bool CNetPlayerGT::sendMsgToClient(GFLib::CMessage& a_msg)
{
	if (m_stubID == GFLib::INVALID_STUBID) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&a_msg).c_str());
		return false;
	}
	GFLib::CommonServer::CStubPtr stubPtr = GFLib::CommonServer::CStubMgr::singleton().getCommonStubByStubID(m_stubID);
	if (stubPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&a_msg).c_str());
		return false;
	}
	return stubPtr->sendMsg(a_msg);
}

bool CNetPlayerGT::sendMsgToCenterServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
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

bool CNetPlayerGT::sendMsgToCenterServer(GFLib::CMessage& a_msg)
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

bool CNetPlayerGT::sendMsgToDataServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
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

bool CNetPlayerGT::sendMsgToDataServer(GFLib::CMessage& a_msg)
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

bool CNetPlayerGT::sendMsgToGameServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
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

bool CNetPlayerGT::sendMsgToGameServer(GFLib::CMessage& a_msg)
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

// bool CNetPlayerGT::sendMsgToSuperServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
// {
// 	if (!m_centerServerID.isValid()) {
// 		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
// 		return false;
// 	}
// 	if (m_accountPtr == NULL) {
// 		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
// 		return false;
// 	}
// 	return m_accountPtr->sendMsgToServer(m_centerServerID, a_msg, a_msgSize);
// }

// bool CNetPlayerGT::sendMsgToSuperServer(GFLib::CMessage& a_msg)
// {
// 	if (!m_centerServerID.isValid()) {
// 		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&a_msg).c_str());
// 		return false;
// 	}
// 	if (m_accountPtr == NULL) {
// 		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s发送消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg.toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(&a_msg).c_str());
// 		return false;
// 	}
// 	return m_accountPtr->sendMsgToServer(m_centerServerID, a_msg);
// }

bool CNetPlayerGT::broadcastMsgToClient(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	CMsgLoginSystemXS2GTNtfBroadcastMsg ntfBroadcastMsg;
	ntfBroadcastMsg.m_subMsg.write((char*)a_msg, a_msgSize);

	CAccountLoginGTInforMgr::singleton().broadcastMsg(&ntfBroadcastMsg);
	return true;
}

bool CNetPlayerGT::broadcastMsgToClient(GFLib::CMessage& a_msg)
{
	CMsgLoginSystemXS2GTNtfBroadcastMsg ntfBroadcastMsg;
	if (!a_msg.serializeTo(ntfBroadcastMsg.m_subMsg)) {
		return false;
	}
	CAccountLoginGTInforMgr::singleton().broadcastMsg(&ntfBroadcastMsg);
	return true;
}


void CNetPlayerGT::_cbInitPlayer()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerGT::_cbInitPlayer[Account=%s]", getAccountName().c_str());
	_finishInitPlayer(ELOGINRESULT_SUCCESS);
}

void CNetPlayerGT::_cbFinalPlayer()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerGT::_cbFinalPlayer[Account=%s]", getAccountName().c_str());
}

void CNetPlayerGT::_cbPlayerOnline()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerGT::_cbPlayerOnline[Account=%s]", getAccountName().c_str());
}

void CNetPlayerGT::_cbPlayerOffline()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "CNetPlayerGT::_cbPlayerOffline[Account=%s]", getAccountName().c_str());
}

void CNetPlayerGT::_quit()
{
	GFLib::SAccountKey accountKey = getAccountKey();
	CAccountLoginGTInforMgr::singleton().checkNtfAccountQuit(accountKey);
}

void CNetPlayerGT::_finishInitPlayer(ELoginResult a_result)
{
	GFLib::SAccountKey accountKey = getAccountKey();
	CAccountLoginGTInforMgr::singleton().finishInitPlayer(accountKey, a_result);
}

bool CNetPlayerGT::_transferMsg(const GFLib::ServerType& a_serverType, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	switch(a_serverType)
	{
	case GFLib::SRVTYPE_GAMECLIENT:
		{
			GFLib::SMsgServerLinkXX2XXNtfTransfer* ntTransfer = (GFLib::SMsgServerLinkXX2XXNtfTransfer*)a_msg;
			GFLib::SMessage* subMsg = (GFLib::SMessage*)ntTransfer->m_msg;
			BSLib::uint32 msgSizeSubMsg = ntTransfer->m_msgSize;

			return sendMsgToClient(subMsg, msgSizeSubMsg);
		}
		break;
	default:
		{
			;
		}
	}
	BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "%s转发消息失败[%s][%s]", CNetPlayer::getAccountKey().toLogString().c_str(), a_msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
	return false;
}

}//GT

}//LoginSystem

}//GSLib


