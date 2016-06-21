#include <GSLib/tracer.h>
#include <GSLib/chatSystem/msgChatSystem.h>
#include <GSLib/chatSystem/CN/chatSystemCN.h>
#include <GSLib/chatSystem/chatSystemError.h>
#include <GSLib/playerSystem/CN/playerCNMgr.h>
#include <GSLib/playerSystem/CN/roleBaseInfoCN.h>
#include <GSLib/playerSystem/CN/roleBaseInfoCNMgr.h>

namespace GSLib
{

namespace ChatSystem
{	

namespace CN
{
BSLIB_SINGLETON_DEFINE(CChatSystemCN);

CChatSystemCN::CChatSystemCN()
{
	;
}

CChatSystemCN::~CChatSystemCN()
{
	;
}

bool CChatSystemCN::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CChatSystemCN::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CChatSystemCN::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CChatSystemCN::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDChatSystemGM2CNReqPrivateChat, &BSLib::Framework::CreateCMessage<CMsgChatSystemGM2CNReqPrivateChat>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDChatSystemGM2CNReqPrivateChat, &CChatSystemCN::_onMsgChatSystemGM2CNReqPrivateChat, this);

	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CChatSystemCN::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CChatSystemCN::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CChatSystemCN::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

void CChatSystemCN::_onMsgChatSystemGM2CNReqPrivateChat(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}

	GFLib::SNetMsgLabel* netMsgLable = (GFLib::SNetMsgLabel*)a_msgLabel;
	PlayerSystem::CN::CPlayerCN *sender = PlayerSystem::CN::CPlayerCNMgr::singleton().getPlayerCN(netMsgLable->m_acountKey);
	if (sender == NULL || !sender->isOnline()) {
		return;
	}
	PlayerSystem::CN::CRoleCN *sendRole = sender->getCurRole();
	if (sendRole == NULL || !sendRole->isActive()) {
		return;
	}

	CMsgChatSystemGM2CNReqPrivateChat *msgReq = (CMsgChatSystemGM2CNReqPrivateChat *)a_msg;
	PlayerSystem::CN::CPlayerCN *receiver = PlayerSystem::CN::CPlayerCNMgr::singleton().getPlayerCN(msgReq->m_receiverKey.getAccountKey());
	PlayerSystem::CN::CRoleCN *receiveRole = PlayerSystem::CN::CPlayerCNMgr::singleton().getRoleCN(msgReq->m_receiverKey);
	if (receiver == NULL || !receiver->isOnline() || receiveRole == NULL || !receiveRole->isActive()) {
		CMsgChatSystemGM2GCAckChat msgAck;
		msgAck.m_result = CHAT_RESULT_NOT_ONLINE;
		sender->sendMsgToClient(msgAck);
	} else {
		CMsgChatSystemGM2GCAckChat2All msgAck2All;
		msgAck2All.m_senderKey = sendRole->getRoleKey();
		msgAck2All.m_channel = CHAT_CHANNEL_PRIVATE;
		msgAck2All.m_receiverKey = msgReq->m_receiverKey;
		msgAck2All.m_senderName = sendRole->getName();
		msgAck2All.m_content = msgReq->m_content;
		msgAck2All.m_hasEquip = msgReq->m_hasEquip;
		msgAck2All.m_equipStream = msgReq->m_equipStream;
		PlayerSystem::CN::CRoleBaseInfoCN *roleBaseInfo = PlayerSystem::CN::CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleName(sendRole->getName());
		if (roleBaseInfo != NULL) {
			msgAck2All.m_VIPLevel = roleBaseInfo->getVipLevel();
		}
		sender->sendMsgToClient(msgAck2All);
		receiver->sendMsgToClient(msgAck2All);
	}

}

}//CN

}//ChatSystem

}//GSLib

