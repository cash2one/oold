#include <BSLib/utility/thread/threadData.h>
#include <GFLib/commonServer/commonServer.h>
#include <GFLib/commonServer/serverTypeMgr.h>
#include <GFLib/commonServer/service.h>
#include <GFLib/commonServer/tracer.h>
#include <GFLib/commonServer/message/funcType.h>
#include <GFLib/commonServer/message/msgServerLink.h>
#include <GFLib/commonServer/stub.h>
#include <GFLib/commonServer/accountMgr.h>

namespace GFLib
{

namespace CommonServer
{

bool IService::_parseMsg(GFLib::SMessage* msg, BSLib::uint32 msgSize)
{
	BSLib::uint8 msgServerType = msg->getServerType();
	BSLib::uint8 msgFunType = msg->getFunctionType();
	BSLib::uint16 msgID = msg->getID();

	CCommonServer* commonServer = CCommonServer::getCommonServer();
	BSLib::uint8 localServerType = (BSLib::uint8)commonServer->getServerType();
	ServerID localServerID = commonServer->getServerID().getServerID();

	GFLib::SNetMsgLabel msgLable;
	msgLable.m_serverIDFrom = m_serverID;
	msgLable.m_serverIDSender = m_serverID;
	msgLable.m_stubIDsender = _getStubID();
	msgLable.m_serverIDTo = localServerID;
	msgLable.m_msgSize = msgSize;

	BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "Recv MsgID(%d[%s].%d.%d) [%s]", 
		msgServerType,
		CServerTypeMgr::singleton().getCodeServerType(msgServerType).c_str(),
		msgFunType, 
		msgID,
		BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());

	if (!(msgServerType == (BSLib::uint8)SRVTYPE_ANY || msgServerType == (BSLib::uint8)SRVTYPE_ANYSERVER || msgServerType == localServerType)) {
		//非本地消息
		if (_executeTransfer(msg, msgSize)) {
			return true;
		}
		return false;
	}
	//本地消息
	//转发消息
	if (msgFunType == EFUNCTYPE_SERVER_LINK && msgID == EMSGNUMID_SERVERLINK_XX2XX_NTF_TRANSFER) {
		SMsgServerLinkXX2XXNtfTransfer* ntTransfer = (SMsgServerLinkXX2XXNtfTransfer*)msg;
		GFLib::SMessage* subMsg = (GFLib::SMessage*)ntTransfer->m_msg;
		BSLib::uint32 msgSizeSubMsg = ntTransfer->m_msgSize;
		
		BSLib::uint8 subMsgServerType = subMsg->getServerType();
		BSLib::uint8 subMsgFunType = subMsg->getFunctionType();
		BSLib::uint16 subMsgID = subMsg->getID();
		
		msgLable.m_msgSize = msgSizeSubMsg;
		msgLable.m_serverIDFrom = ntTransfer->m_serverIDFrom;
		msgLable.m_serverIDSender = m_serverID;
		msgLable.m_serverIDTo = ntTransfer->m_serverIDTo;
		msgLable.m_acountKey = ntTransfer->m_accountKey;

		BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "RecvSubMsg MsgID(%d[%s].%d.%d) [%s]", 
			subMsgServerType,
			CServerTypeMgr::singleton().getCodeServerType(subMsgServerType).c_str(),
			subMsgFunType, 
			subMsgID,
			BSLib::Framework::CMsgDebug::singleton().getPrompt(subMsg).c_str());

		if (ntTransfer->m_serverIDTo == INVALID_SERVERID) {
			if (subMsgServerType == (BSLib::uint8)SRVTYPE_ANY || subMsgServerType == (BSLib::uint8)SRVTYPE_ANYSERVER || subMsgServerType == localServerType) {
				if (_executeMessage(&msgLable, subMsg)) {
					return true;
				}
				return false;
			}
			if (_executeTransfer(msg, msgSize)) {
				return true;
			}
			return false;
		} else if (ntTransfer->m_serverIDTo == localServerID) {
			if (_executeMessage(&msgLable, subMsg)) {
				return true;
			}
			return false;
		}
		if (_executeTransfer(msg, msgSize)) {
			return true;
		}
		return false;
	}
	if (_executeMessage(&msgLable, msg)) {
		return true;
	}
	return false;
}

bool IService::_transferMsg(GFLib::SMessage* msg, BSLib::uint32 msgSize)
{
	if (msg->getUniqueID() != MsgIDServerLinkXX2XXNtfTransfer) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "丢弃消息[%s][%s],不是转发消息", msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());
		return false;
	}
	SMsgServerLinkXX2XXNtfTransfer* ntTransfer = (SMsgServerLinkXX2XXNtfTransfer*)msg;
	GFLib::SMessage* subMsg = (GFLib::SMessage*)ntTransfer->m_msg;
	//GFLib::ServerType subMsgServerType = (GFLib::ServerType)subMsg->getServerType();

	CAccountPtr accountPtr = CAccountMgr::singleton().getAccount(ntTransfer->m_accountKey);
	if (accountPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "丢弃消息[%s][%s],AccountID不存在", subMsg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(subMsg).c_str());
		return m_serverID.isValid();
	}
	if (!accountPtr->_transferMsg(subMsg->getServerType(), msg, msgSize)) {
		//BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "丢弃消息[%s][%s]", subMsg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(subMsg).c_str());
		return m_serverID.isValid();
	}
	return true;
}


bool IService::_executeMessage(GFLib::SNetMsgLabel* lable, GFLib::SMessage* msg)
{
	BSLib::Framework::CMessage* cmsg = BSLib::Framework::CMsgFactory::singleton().createCMessage(msg->getUniqueID());
	if (cmsg != NULL) {
		cmsg->serializeFrom(msg, lable->m_msgSize);
		if (m_msgExecMgr.executeMessage(lable, cmsg)) {
			BSLIB_SAFE_DELETE(cmsg);
			return true;
		}
		BSLIB_SAFE_DELETE(cmsg);
	} else {
		if (m_msgExecMgr.executeMessage(lable, msg)) {
			return true;
		}
	}

// 	if (!_canTransfer()) {
// 		msg->toString();
// 		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "丢弃消息[%s][%s]", msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());
// 		return false;
// 	}
	//发送给本地消息队列处理
	CCommonServer* commonServer = CCommonServer::getCommonServer();
	if (!commonServer->sendMsg(msg, lable->m_msgSize, lable, lable->getLabelSize())) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "丢弃消息[%s][%s],转发消息队列失败", msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());
		return false;
	}
	BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "发送消息[%s][%s]到MainThread消息队列", msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());
	return true;
}

bool IService::_executeTransfer(GFLib::SMessage* msg, BSLib::uint32 msgSize)
{
	//转发
	if (!_canTransfer()) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "丢弃消息[%s][%s],转发受限制", msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());
		return m_serverID.isValid();
	}
	if (_transferMsg(msg, msgSize)) {
		//BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "转发消息[%s][%s]成功", msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());
		return true;
	}
	//BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "转发消息[%s][%s]失败", msg->toString().c_str(), BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str());
	return m_serverID.isValid();
}

}//CommonServer

}//GFLib




