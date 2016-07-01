#include <GSLib/chatSystem/GM/roleChatModule.h>
#include <GSLib/chatSystem/msgChatSystem.h>
#include <GSLib/playerSystem/GM/playerGMMgr.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/commonServer.h>
#include <GFLib/commonServer/message/msgLocalServer.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/sceneSystem/GM/scene.h>
#include <GSLib/chatSystem/GM/chatMgr.h>
#include <GSLib/playerSystem/GM/roleBagModuleGM.h>
#include <GSLib/itemSystem/GM/itemAttributeGM.h>
#include <GSLib/sceneSystem/GM/roleSceneModule.h>
#include <BSLib/utility/dateTime.h>
#include <GSLib/chatSystem/GM/chatSystemGM.h>
#include <GSLib/equipSystem/GM/roleEquipGM.h>
#include <GSLib/equipSystem/GM/roleEquipModule.h>
#include <GSLib/playerSystem/GM/roleBagModuleGM.h>
#include <GSLib/friendSystem/GM/roleFriendModule.h>

namespace GSLib
{

namespace ChatSystem
{

namespace GM
{

CRoleChatModule::CRoleChatModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType)
:GSLib::PlayerSystem::GM::CRoleModuleGM(a_roleGM, a_moduleType)
,m_lastTalkTime(0)
{
	;
}

CRoleChatModule::~CRoleChatModule()
{
	;
}

void CRoleChatModule::preInit(bool isFirst)
{
	;
}

void CRoleChatModule::postInit(bool isFirst)
{
	;
}

void CRoleChatModule::initToClient()
{
	CMsgChatSystemGM2GCAckInitChatData msgInit(CChatMgr::singleton().getWorldContent(), CChatMgr::singleton().getAnnounceContent());
	sendMsgToClient(msgInit);
}

void CRoleChatModule::final()
{
	;
}

void CRoleChatModule::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDChatSystemGC2GMReqChat, &BSLib::Framework::CreateCMessage<CMsgChatSystemGC2GMReqChat>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDChatSystemGC2GMReqChat, &CRoleChatModule::_onMsgChatSystemGC2GMReqChat, this);
}

void CRoleChatModule::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(MsgIDChatSystemGC2GMReqChat);
}

void CRoleChatModule::updateDataToDB()
{
	;
}

bool CRoleChatModule::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	return true;
}

bool CRoleChatModule::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	return true;
}

void CRoleChatModule::sendAnnounce(const std::string& senderName, const std::string& a_content)
{
	CMsgChatSystemGM2GCAckChat2All msgAck2All;
	msgAck2All.m_senderName = senderName;
	msgAck2All.m_channel = CHAT_CHANNEL_ANNOUNCE;
	msgAck2All.m_content = a_content;
	getRoleGM()->getPlayerGM()->broadcastMsgToClient(msgAck2All);
}

void CRoleChatModule::sendAnnounce(const CChatContent & a_content)
{
	CMsgChatSystemGM2GCAckChat2All msgAck2All;
	msgAck2All.m_senderName = a_content.m_senderName;
	msgAck2All.m_channel = CHAT_CHANNEL_ANNOUNCE;
	msgAck2All.m_content = a_content.m_content;
	msgAck2All.m_hasEquip = a_content.m_hasEquip;
	msgAck2All.m_equipStream = a_content.m_equipStream;
	getRoleGM()->getPlayerGM()->broadcastMsgToClient(msgAck2All);
}

EChatResult CRoleChatModule::_canPrivateChat(const GSLib::SRoleKey& a_receiverKey) /*const*/
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL || getRoleGM()->getFriendModule()== NULL) {
		return CHAT_RESULT_FAIL;
	}

	if (getRoleGM()->getPlayerGM()->getAccountKey() == a_receiverKey.getAccountKey()) {
		return CHAT_RESULT_CAN_NOT_TALK_TO_SELF;
	}

	if (!getRoleGM()->getFriendModule()->isMyFriend(a_receiverKey)) {
		return CHAT_RESULT_NOT_FRIEND;
	}

	return CHAT_RESULT_SUCCESS;
}

EChatResult CRoleChatModule::_canWorldChat() /*const*/
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		return CHAT_RESULT_FAIL;
	}

	GSLib::PlayerSystem::GM::CRoleBagModuleGM *bagModule = getRoleGM()->getRoleBag();
	if (bagModule == NULL) {
		return CHAT_RESULT_FAIL;
	}

	//if (bagModule->getItemCount(C_ITEM_ID_SPEAKER) <= 0) {
	//	return CHAT_RESULT_NOT_ENOUGH_ITEM;
	//}
	if (BSLib::Utility::CDateTime::getCurrentTime().getSeconds() < (time_t)m_lastTalkTime + C_ROLE_TALK_INTERVAL) {
		return CHAT_RESULT_TALK_TOO_FREQUENTLY;
	}

	return CHAT_RESULT_SUCCESS;
}

EChatResult CRoleChatModule::_canCityChat() /*const*/
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		return CHAT_RESULT_FAIL;
	}

	GSLib::SceneSystem::GM::CRoleSceneModule *sceneModule = (GSLib::SceneSystem::GM::CRoleSceneModule *)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_SCENE);
	if (sceneModule == NULL) {
		return CHAT_RESULT_FAIL;
	}
	GSLib::SceneSystem::GM::CScene *scene = sceneModule->getScene();
	if (scene == NULL) {
		return CHAT_RESULT_FAIL;
	}

	if (scene->getSceneType() != GSLib::SceneSystem::GM::ESCENE_TYPE_CITY) {
		return CHAT_RESULT_NOT_IN_MAIN_CITY;
	}

	if (BSLib::Utility::CDateTime::getCurrentTime().getSeconds() < (time_t)m_lastTalkTime + C_ROLE_TALK_INTERVAL) {
		return CHAT_RESULT_TALK_TOO_FREQUENTLY;
	}

	return CHAT_RESULT_SUCCESS;
}

EChatResult CRoleChatModule::_canAnnounceChat() /*const*/
{
	return CHAT_RESULT_SUCCESS;	
}

EChatResult CRoleChatModule::_canChat(EChatChanel a_channel, const GSLib::SRoleKey &a_receiverKey)
{
	switch(a_channel)
	{
	case CHAT_CHANNEL_PRIVATE:
		{
			return _canPrivateChat(a_receiverKey);
		}
		break;
	case CHAT_CHANNEL_WORLD:
		{
			return _canWorldChat();
		}
		break;
	case CHAT_CHANNEL_CITY:
		{
			return _canCityChat();
		}
		break;
	case CHAT_CHANNEL_ANNOUNCE: // for test
		{
			return _canAnnounceChat();
		}
		break;
	default:
		;
	}

	return CHAT_RESULT_SUCCESS;
}

void CRoleChatModule::_privateChat(const CMsgChatSystemGC2GMReqChat &a_chatMsg)
{
	EChatResult result = _canChat(CHAT_CHANNEL_PRIVATE, a_chatMsg.m_receiverKey);

	PlayerSystem::GM::CRoleGM *sender = getRoleGM();
	PlayerSystem::GM::CPlayerGM* receiver = PlayerSystem::GM::CPlayerGMMgr::singleton().getPlayerGM(a_chatMsg.m_receiverKey.getAccountKey());
	if (receiver != NULL) {
		CMsgChatSystemGM2GCAckChat msgAck;
		if (receiver->isOnline()) {
			CMsgChatSystemGM2GCAckChat2All msgAckToAll;
			msgAckToAll.m_senderKey = sender->getRoleKey();
			msgAckToAll.m_senderName = getRoleGM()->getName();
			msgAckToAll.m_VIPLevel = getRoleGM()->getVipLevel();
			msgAckToAll.m_channel = CHAT_CHANNEL_PRIVATE;
			msgAckToAll.m_receiverKey = a_chatMsg.m_receiverKey;
			msgAckToAll.m_content = a_chatMsg.m_content;
			msgAckToAll.m_hasEquip = getEquipStream(a_chatMsg.m_equipID, msgAckToAll.m_equipStream);
			sender->sendMsgToClient(msgAckToAll);
			receiver->sendMsgToClient(msgAckToAll);
		} else {
			result = CHAT_RESULT_NOT_ONLINE;
		}
		msgAck.m_result = result;
		sendMsgToClient(msgAck);
	} else {
		CMsgChatSystemGM2CNReqPrivateChat msgReqCN;
		msgReqCN.m_receiverKey = a_chatMsg.m_receiverKey;
		msgReqCN.m_content = a_chatMsg.m_content;
		msgReqCN.m_hasEquip = getEquipStream(a_chatMsg.m_equipID, msgReqCN.m_equipStream);
		sendMsgToCenterServer(msgReqCN);
	}
}

void CRoleChatModule::_worldChat(const CMsgChatSystemGC2GMReqChat &a_chatMsg)
{
	//GSLib::PlayerSystem::GM::CRoleBagModuleGM *bagModule = getRoleGM()->getRoleBag();
	//if (bagModule == NULL) {
	//	return;
	//}
	
	m_lastTalkTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
	//bagModule->modifyItemCount(C_ITEM_ID_SPEAKER, (GSLib::ItemSystem::GM::EItemType)C_ITEM_TYPE_SPEAKER, -1, "worldChat", true);

	CMsgChatSystemGM2GCAckChat2All msgAck;
	msgAck.m_senderKey = getRoleGM()->getRoleKey();
	msgAck.m_senderName = getRoleGM()->getName();
	msgAck.m_VIPLevel = getRoleGM()->getVipLevel();
	msgAck.m_channel = CHAT_CHANNEL_WORLD;
	msgAck.m_content = a_chatMsg.m_content;
	msgAck.m_hasEquip = getEquipStream(a_chatMsg.m_equipID, msgAck.m_equipStream);
	getRoleGM()->getPlayerGM()->broadcastMsgToClient(msgAck);

	m_lastTalkTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();

	CChatContent content;
	content.m_roleKey = getRoleGM()->getRoleKey();
	content.m_senderName = getRoleGM()->getName();
	content.m_VIPLevel = getRoleGM()->getVipLevel();
	content.m_channel = CHAT_CHANNEL_WORLD;
	content.m_content = a_chatMsg.m_content;
	content.m_hasEquip = getEquipStream(a_chatMsg.m_equipID, content.m_equipStream);
	CChatMgr::singleton().addWorldContent(content);
}

void CRoleChatModule::_cityChat(const CMsgChatSystemGC2GMReqChat &a_chatMsg)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		return;
	}

	SceneSystem::GM::CRoleSceneModule *sceneModule = (SceneSystem::GM::CRoleSceneModule *)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_SCENE);
	if (sceneModule == NULL) {
		return;
	}
	SceneSystem::GM::CScene *scene = sceneModule->getScene();
	if (scene != NULL) {
		CMsgChatSystemGM2GCAckChat2All msgAck;
		msgAck.m_senderKey = getRoleGM()->getRoleKey();
		msgAck.m_senderName = getRoleGM()->getName();
		msgAck.m_VIPLevel = getRoleGM()->getVipLevel();
		msgAck.m_channel = CHAT_CHANNEL_CITY;
		msgAck.m_content = a_chatMsg.m_content;
		msgAck.m_hasEquip = getEquipStream(a_chatMsg.m_equipID, msgAck.m_equipStream);
		scene->sendToAllRoles(msgAck); 
		m_lastTalkTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
	}
}

void CRoleChatModule::_announceChat(const std::string &a_content)
{
	std::string senderName("system");
	sendAnnounce(senderName, a_content);
		
	CChatContent content;
	content.m_senderName = senderName;
	content.m_channel = CHAT_CHANNEL_ANNOUNCE;
	content.m_content = a_content;
	CChatMgr::singleton().addAnnounceContent(content);
}

void CRoleChatModule::_onMsgChatSystemGC2GMReqChat(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}

	CMsgChatSystemGC2GMReqChat *msgReq = (CMsgChatSystemGC2GMReqChat *)a_msg;
	if (CChatSystemGM::singleton().enableGMChatCommand()) {
		if (msgReq->m_content.size() > 0 && msgReq->m_content[0] == '\\') {
			GFLib::CommonServer::ICommonServer* server = GFLib::CommonServer::ICommonServer::getCommonServer();
			if (server == NULL) {
				return ;
			}
			BSLib::Utility::CCmdExecMgr* cmdExecMgr = server->getCmdExecMgr();
			if (cmdExecMgr == NULL) {
				return ;
			}
			cmdExecMgr->parseCommand(&msgReq->m_content[1], this->getRoleGM());
			return ;
		}
	}

	EChatResult result = _canChat(msgReq->m_channel, msgReq->m_receiverKey);
	CMsgChatSystemGM2GCAckChat msgAck;
	msgAck.m_result = result;
	sendMsgToClient(msgAck);
	if (result != CHAT_RESULT_SUCCESS) {
		return;
	}



	switch(msgReq->m_channel)
	{
	case CHAT_CHANNEL_PRIVATE:
		{
			_privateChat(*msgReq);
		}
		break;
	case CHAT_CHANNEL_WORLD:
		{
			_worldChat(*msgReq);
		}
		break;
	case CHAT_CHANNEL_CITY:
		{
			_cityChat(*msgReq);
		}
		break;
	case CHAT_CHANNEL_ANNOUNCE:
		{
			_announceChat(msgReq->m_content); // for test
		}
		break;
	default:
		;
	}

}

bool CRoleChatModule::getEquipStream(const CChatEquipID & a_chatEquipID, BSLib::Utility::CStream & a_stream) const
{
	if (getRoleGM() != NULL) {
		EquipSystem::GM::CRoleEquipModule *equipRole = getRoleGM()->getEquipModule();
		if (equipRole != NULL) {
			EquipSystem::GM::CRoleEquipGM *equip = NULL;
			if (a_chatEquipID.m_bagIndex != CChatEquipID::invalid_index) {
				if (getRoleGM()->getRoleBag() != NULL) {
					PlayerSystem::GM::SBagItem item;
					getRoleGM()->getRoleBag()->getItemByIndex(a_chatEquipID.m_bagIndex, item);
					equip =  equipRole->getEquip(item.m_instanceID);
				}
			} else if (a_chatEquipID.m_equipID != CChatEquipID::invalid_index) {
				equip = equipRole->getEquip(a_chatEquipID.m_equipID);	
			}
			if (equip != NULL) {
				equip->serializeTo(a_stream);
				return true;
			}
		}
	}
	return false;
}


}//GM

}//ChatSystem

}//GSLib
