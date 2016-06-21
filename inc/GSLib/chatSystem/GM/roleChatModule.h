#ifndef __GSLIB_CHATSYSTEM_GM_ROLECHATMODULE_H__
#define __GSLIB_CHATSYSTEM_GM_ROLECHATMODULE_H__

#include <GFLib/commonServer/baseDef.h>
#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <GSLib/chatSystem/chatSystemError.h>
#include <GSLib/chatSystem/chatSystemDefine.h>

namespace GSLib
{

namespace ChatSystem
{

	class CMsgChatSystemGC2GMReqChat;
namespace GM
{
	class CChatEquipID;
	class CChatContent;

class CRoleChatModule : public GSLib::PlayerSystem::GM::CRoleModuleGM
{
public:
	CRoleChatModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CRoleChatModule();

	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void updateDataToDB();
	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
public:
	void sendAnnounce(const std::string& senderName, const std::string& a_content);
	void sendAnnounce(const CChatContent & a_content);
	
private:
	EChatResult _canPrivateChat(const GSLib::SRoleKey& a_receiverKey) /*const*/;
	EChatResult _canWorldChat() /*const*/;
	EChatResult _canCityChat() /*const*/;
	EChatResult _canAnnounceChat() /*const*/;

	EChatResult _canChat(EChatChanel a_channel, const GSLib::SRoleKey& a_receiverKey);

	void _privateChat(const CMsgChatSystemGC2GMReqChat &a_chatMsg);
	void _worldChat(const CMsgChatSystemGC2GMReqChat &a_chatMsg);
	void _cityChat(const CMsgChatSystemGC2GMReqChat &a_chatMsg);
	void _announceChat(const std::string &a_content);
	
	bool getEquipStream(const CChatEquipID & a_chatEquipID, BSLib::Utility::CStream &a_stream) const;
private:
	void _onMsgChatSystemGC2GMReqChat(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
private:
	BSLib::uint64 m_lastTalkTime;
};

}//GM

}//ChatSystem

}//GSLib

#endif//__GSLIB_CHATSYSTEM_GM_ROLECHATMODULE_H__
