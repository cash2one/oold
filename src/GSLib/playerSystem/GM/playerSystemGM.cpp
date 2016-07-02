#include <BSLib/framework/message/msgExecMgr.h>
#include <GSLib/tracer.h>
#include <GSLib/playerSystem/GM/playerSystemGM.h>
#include <GSLib/equipSystem/GM/equipSystemGM.h>
#include <GSLib/achieveSystem/GM/achieveModule.h>
#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include <GSLib/playerSystem/GM/roleBagModuleGM.h>
#include "roleConfigGMMgr.h"
#include <BSLib/utility/eventMgr.h>
#include <GSLib/masterSystem/GM/masterSystemGM.h>
namespace GSLib
{

namespace PlayerSystem
{	

namespace GM
{

BSLIB_SINGLETON_DEFINE(CPlayerSystemGM);

CPlayerSystemGM::CPlayerSystemGM()
{
	;
}

CPlayerSystemGM::~CPlayerSystemGM()
{
	;
}

bool CPlayerSystemGM::_init()
{
	CRoleModuleGMMgr::singleton().addCreateRoleModuleFun(EMODULECTYPE_BAG, createRoleModuleFun<CRoleBagModuleGM>);
	
	CPlayerGMMgr::singleton().init();
    _initEvent();
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CPlayerSystemGM::_final()
{
    CRoleConfigGMMgr::singleton().final();
	CPlayerGMMgr::singleton().final();
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CPlayerSystemGM::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	if (!CRoleConfigGMMgr::singleton().loadGameConfig(a_configPath)){
		return false;
	}
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CPlayerSystemGM::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{

	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_EQUIPSYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_ITEMSYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_SKILLPSYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_NPCSYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_PRIZESYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_TASKSYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_CHATSYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_MAILSYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_RANKSYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_SHOPSYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
    GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_FRIENDSYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
    GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_ACTIVITYSYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
    GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_ACHIEVESYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);
	 GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_GAMESERVER, EFUNCTYPE_MASTERSYSTEM), &PlayerSystem::GM::CPlayerSystemGM::_onMsgPlayerSystem, this);

	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CPlayerSystemGM::_initCommand(BSLib::Utility::CCmdExecMgr* a_cmdExecMgr)
{
	a_cmdExecMgr->addCmdExecPtr("AddGold",       &CPlayerSystemGM::_onCmdAddGold, this);
    a_cmdExecMgr->addCmdExecPtr("AddDiamond",    &CPlayerSystemGM::_onCmdAddDiamond, this);
    a_cmdExecMgr->addCmdExecPtr("AddExp",        &CPlayerSystemGM::_onCmdAddExp, this);
	a_cmdExecMgr->addCmdExecPtr("AddItem",       &CPlayerSystemGM::_onCmdAddItem, this);  
    a_cmdExecMgr->addCmdExecPtr("UpdateLevel",   &CPlayerSystemGM::_onCmdUpdateLevel, this);  
    a_cmdExecMgr->addCmdExecPtr("SetVIPLevel",   &CPlayerSystemGM::_onCmdSetVIPLevel, this);  

	return GSLib::DBSystem::CDBCommonSystem::_initCommand(a_cmdExecMgr);
}

bool CPlayerSystemGM::_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CPlayerSystemGM::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CPlayerSystemGM::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

bool CPlayerSystemGM::_cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	CPlayerGM* player = CPlayerGMMgr::singleton().getPlayerGM(a_roleKey.getAccountKey());
	if (player != NULL) {
		if (player->cbSelectKeyTableData(a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID)) {
			return true;
		}
	}
	BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "丢弃查询数据 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);
	return false;
}

bool CPlayerSystemGM::_cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	CPlayerGM* player = CPlayerGMMgr::singleton().getPlayerGM(a_roleKey.getAccountKey());
	if (player != NULL) {
		if (player->cbSelectKeyIndexTableData(a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID)) {
			return true;
		}
	}
	BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "丢弃查询数据 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);
	return false;
}

void CPlayerSystemGM::update(BSLib::uint64 a_delayMilliseconds)
{
    CPlayerGMMgr::singleton().update(a_delayMilliseconds);
};

void CPlayerSystemGM::_onMsgPlayerSystem(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* netMsgLable = (GFLib::SNetMsgLabel*)a_msgLabel;
	GFLib::SMessage* msg = (GFLib::SMessage*)a_msg;

	LoginSystem::GM::CNetPlayerGMMgr* netPlayerGMMgr = GSLib::LoginSystem::GM::CNetPlayerGMMgr::getSingleton();
	if (netPlayerGMMgr == NULL) {
		return;
	}
	LoginSystem::GM::CNetPlayerGM* player = netPlayerGMMgr->getNetPlayerGM(netMsgLable->m_acountKey);
	if (player != NULL) {
		if (player->executeMessage(a_msgLabel, a_msg)) {
			return ;
		}
	}
 
	BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "丢弃消息 MsgID(%d[%s].%d.%d) [%s] [%s]", 
		msg->ICommonServer_getServerType(),
		GFLib::CommonServer::CServerTypeMgr::singleton().getCodeServerType(msg->ICommonServer_getServerType()).c_str(),
		msg->getFunctionType(), 
		msg->getID(),
		BSLib::Framework::CMsgDebug::singleton().getPrompt(msg).c_str(),netMsgLable->m_acountKey.toLogString().c_str());
}

bool CPlayerSystemGM::_cbSelectGlobalKeyTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
    CPlayerGM* player = CPlayerGMMgr::singleton().getPlayerGM(a_srcRoleKey.getAccountKey());
    if (player != NULL) {
        if (player->cbSelectGlobalKeyTableData(a_srcRoleKey,a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID)) {
            return true;
        }
    }
	
	switch(a_moduleType)
	{
	case GSLib::EMODULECTYPE_MASTER:
		GSLib::MasterSystem::GM::CMasterSystemGM::singleton()._cbSelectGlobalKeyTableData(a_srcRoleKey, a_roleKey,
			a_keyTable, a_tableID, a_moduleType, a_sessionID);

		return true;
	default:
		;
	}

    BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "丢弃查询数据 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);
    return false;
}

bool CPlayerSystemGM::_cbSelectGlobalKeyIndexTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
    CPlayerGM* player = CPlayerGMMgr::singleton().getPlayerGM(a_srcRoleKey.getAccountKey());
    if (player != NULL) {
        if (player->cbSelectGlobalKeyIndexTableData(a_srcRoleKey,a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID)) {
            return true;
        }
    }

	switch(a_moduleType)
	{
	case GSLib::EMODULECTYPE_MASTER:
		GSLib::MasterSystem::GM::CMasterSystemGM::singleton()._cbSelectGlobalKeyIndexTableData(a_srcRoleKey, a_roleKey, 
			a_keyTable, a_tableID, a_moduleType, a_sessionID);	
		return true;
	default:
		;
	}

    BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "丢弃查询数据 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);
    return false;
}

bool CPlayerSystemGM::_cbSelectGlobalMultiTableData(const GSLib::SRoleKey& a_srcRoleKey,EModuleType a_srcModuleType, BSLib::uint32 a_sessionID,void* a_ptr,BSLib::uint32 a_state,std::vector<GSLib::DBSystem::SSelectTablesResult>& a_ackSelectTablesResultArray,std::vector<GSLib::DBSystem::CKeyTablePtr>& a_keyTablePtrArray,std::vector<GSLib::DBSystem::CKeyIndexTablePtr>& a_keyIndexTablePtrArray)
{
    CPlayerGM* player = CPlayerGMMgr::singleton().getPlayerGM(a_srcRoleKey.getAccountKey());
    if (player != NULL) {
        if (player->cbSelectGlobalMultiTableData(a_srcRoleKey,a_srcModuleType,a_sessionID,a_ptr, a_state, a_ackSelectTablesResultArray, a_keyTablePtrArray, a_keyIndexTablePtrArray)) {
            return true;
        }
    }
    BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "丢弃多表查询数据 %s[a_sessionID=%d][a_state=%d]", a_srcRoleKey.toLogString().c_str(), a_sessionID,a_state);
    return false;
}

CRoleGM* CPlayerSystemGM::getRoleByCmd(BSLib::Utility::CProperties& a_properties) const
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######getRoleByCmd()#######");
    GFLib::AccountID accountID = 0;
    GSLib::RoleIndex roleIndex = 0;
    std::string strAccountID;
    BSLib::int32 zoneID = 0;
    a_properties.getValueString("accountid", strAccountID);
    if (strAccountID.empty()) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "#######getRoleByCmd()[accountID=%lld][无效accountID]",strAccountID.c_str());
        return NULL;
    }
    accountID = atol(strAccountID.c_str());
    if (accountID <= 0) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "#######getRoleByCmd()[accountID=%lld][无效accountID]",accountID);
        return NULL;
    }

    a_properties.getValueInt32("zoneid", zoneID);
    if (zoneID <= 0) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "#######getRoleByCmd()[zoneID=%d][无效zoneID]",zoneID);
        return NULL;
    }

    std::string strName;
    a_properties.getValueString("name", strName);
    if (!strName.empty()) {
         return CPlayerGMMgr::singleton().getRoleGMByRoleName(accountID,(GFLib::ZoneID)zoneID,strName);
    }

    a_properties.getValueInt32("index", roleIndex);
    if (roleIndex < 0) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "#######getRoleByCmd()[roleIndex=%d][无效roleIndex]",roleIndex);
        return NULL;
    }

    return CPlayerGMMgr::singleton().getRoleGM(accountID,(GFLib::ZoneID)zoneID,roleIndex);
}

int CPlayerSystemGM::_onCmdTest(BSLib::Utility::CProperties& a_properties, void* a_tempPara)
{
	BSLib::int32 count = 0;
	std::string roleName;
	if (a_properties.getValueString("1", roleName)) {
		if (a_properties.getValueInt32("2", count)) {
		} else {
			a_properties.getValueInt32("count", count);
		}
	} else {
		a_properties.getValueString("name", roleName);
		a_properties.getValueInt32("count", count);
	}
	if (roleName.empty()) {
		return 1;
	}
	if (count <= 0) {
		return 1;
	}

	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######AddGold name=%s count=%d", roleName.c_str(), count);
	return 1;
}

int CPlayerSystemGM::_onCmdAddGold(BSLib::Utility::CProperties& a_properties, void* a_tempPara)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######_onCmdAddGold()#######");
    CRoleGM*  role = (CRoleGM*)a_tempPara;
    if(NULL == role){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "#######_onCmdAddGold()[角色不存在或不在线]");
        return 1;
    }

    std::string strValue;
	a_properties.getValueString("1", strValue);
	if (strValue.empty()) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "#######_onCmdAddGold()[gold=%s][无效gold]",strValue.c_str());
		return 1;
	}

    BSLib::int64 value = atol(strValue.c_str());

	role->modifyGold(value,"GM_CMD",true);

	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######AddGold[success] %s gold=%lld", role->getRoleKey().toLogString().c_str(), value);
	return 1;
}

int CPlayerSystemGM::_onCmdAddExp(BSLib::Utility::CProperties& a_properties, void* a_tempPara)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######_onCmdAddExp()#######");
    CRoleGM*  role = (CRoleGM*)a_tempPara;
    if(NULL == role){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "#######_onCmdAddExp()[角色不存在或不在线]");
        return 1;
    }
    std::string strValue;
    a_properties.getValueString("1", strValue);
    if (strValue.empty()) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "#######_onCmdAddExp()[exp=%s][无效exp]",strValue.c_str());
        return 1;
    }
    BSLib::int64 value = atol(strValue.c_str());

    role->modifyExp(value,"GM_CMD",true);

    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######AddExp[success]%s exp=%lld", role->getRoleKey().toLogString().c_str(),value);
    return 1;
}

int CPlayerSystemGM::_onCmdAddDiamond(BSLib::Utility::CProperties& a_properties, void* a_tempPara)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######_onCmdAddDiamond()#######");
    CRoleGM*  role = (CRoleGM*)a_tempPara;
    if(NULL == role){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "#######_onCmdAddDiamond()[角色不存在或不在线]");
        return 1;
    }

    BSLib::int32 value = 0;
    if (a_properties.getValueInt32("1",value)) {
        if (value != 0) {
            role->modifyRoleResource(ATTR_BIND_DIAMOND,value,"GM_CMD",true);
            BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######AddDiamond[diamond] %s", role->getRoleKey().toLogString().c_str());
            return 1;
        }
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######AddDiamond[fail] %s 无效指令被丢弃", role->getRoleKey().toLogString().c_str());
        return 1;
    }

    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######AddDiamond[success]%s exp=%lld", role->getRoleKey().toLogString().c_str(),value);
    return 1;
}

int CPlayerSystemGM::_onCmdAddItem(BSLib::Utility::CProperties& a_properties, void* a_tempPara)
{
	BSLib::int32 itemID = 0;
	BSLib::int32 count = 0;
	BSLib::int32 type = 0;
    CRoleGM*  role = (CRoleGM*)a_tempPara;
    if(NULL == role){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "#######_onCmdAddExp()[角色不存在或不在线]");
        return 1;
    }

	a_properties.getValueInt32("1", itemID);
	if (itemID < 0) {
		return 1;
	}

	a_properties.getValueInt32("2", count);
	if (count < 0) {
		return 1;
	}

	CRoleBagModuleGM* bag = role->getRoleBag();
	if(bag == NULL){
		return 1;
	}

    ItemSystem::GM::CPrizeItem item;
    item.m_itemTPID = itemID;
    item.m_itemCount = count;
    item.m_itemType = ItemSystem::GM::EITEM_TP_IVALID;
    bag->addItem(item,false,true,"GM_CMD");

	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######AddItem%s itemID=%d type=%d count=%d", role->getRoleKey().toLogString().c_str(),itemID,type,count);
	return 1;
}

int CPlayerSystemGM::_onCmdUpdateLevel(BSLib::Utility::CProperties& a_properties, void* a_tempPara)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######_onCmdUpdateLevel()#######");
    CRoleGM*  role = (CRoleGM*)a_tempPara;
    if(NULL == role){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "#######_onCmdUpdateLevel()[角色不存在或不在线]");
        return 1;
    }

    // \UpdateLevel accountid=10000000 zoneid=21 index=121 level=4
    BSLib::int32 a_desLevel = 0;
    if (a_properties.getValueInt32("1",a_desLevel)) {
        if (a_desLevel != 0) {
            BSLib::int64 a_exp = 0;
            a_exp -= role->getExp();
            BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_checkUpgrade[a_desLevel=%d][a_exp=%lld]",a_desLevel,a_exp);
            role->modifyExp(a_exp,"GM_CMD",true);
            BSLib::int32 upgradeLevel = a_desLevel - role->getLevel();
            role->modifyRoleResource(ATTR_LEVEL,upgradeLevel,"GM_CMD",true);
            BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######UpdateLevel %s", role->getRoleKey().toLogString().c_str());
            return 1;
        }
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######UpdateLevel[fail] %s 无效指令被丢弃", role->getRoleKey().toLogString().c_str());
        return 1;
    }

    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######UpdateLevel[success]%s level=%d", role->getRoleKey().toLogString().c_str(),a_desLevel);
    return 1;
}

int CPlayerSystemGM::_onCmdSetVIPLevel(BSLib::Utility::CProperties& a_properties, void* a_tempPara)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######_onCmdSetVIPLevel()#######");
	CRoleGM*  role = (CRoleGM*)a_tempPara;
	if(NULL == role){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "#######_onCmdSetVIPLevel()[角色不存在或不在线]");
		return 1;
	}

	// \UpdateLevel accountid=10000000 zoneid=21 index=121 level=4
	BSLib::int32 a_desLevel = 0;
	if (a_properties.getValueInt32("1",a_desLevel)) {
		if (a_desLevel >= 0) {
			BSLib::int32 addLevel = a_desLevel - (BSLib::int32)role->getVipLevel();
			role->modifyRoleResource(ATTR_VIP_LEVEL,addLevel,"VIP_UPGRADE",true);
			return 1;
		}
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######UpdateLevel[fail] %s 无效指令被丢弃", role->getRoleKey().toLogString().c_str());
		return 1;
	}

	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######UpdateLevel[success]%s level=%d", role->getRoleKey().toLogString().c_str(),a_desLevel);
	return 1;	
}

bool CPlayerSystemGM::_initEvent()
{
    for(BSLib::uint32 i = EEVENTID_ACHIEVE_ROLELEVEL;i<= EEVENTID_ACHIEVE_MAXID; ++i){
         BSLib::Utility::EventID eventID = i;
         //GFLib::CommonServer::CEventMgr::singleton().registerEvent(eventID,&CPlayerSystemGM::_onEventAchieveUpdate,this);
    }
    return true;
}

void CPlayerSystemGM::_onEventAchieveUpdate(BSLib::Utility::EventID& a_eventID, BSLib::Utility::CStream& a_stream)
{
    GSLib::SRoleKey roleKey;
    roleKey.serializeFrom(a_stream);
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "#######_onEventAchieveUpdate()#######[a_eventID=%d] %s",a_eventID,roleKey.toLogString().c_str());
    CRoleGM* role = CPlayerGMMgr::singleton().getRoleGM(roleKey);
    if (role == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[_onEventAchieveUpdate][a_eventID=%d] %s[角色不存在]",a_eventID,roleKey.toLogString().c_str());
        return;
    }

    GSLib::AchieveSystem::GM::CAchieveModule *roleAchieveModule = (GSLib::AchieveSystem::GM::CAchieveModule *)role->getPlayerModuleGM(EMODULECTYPE_ACHIEVE);
    if (roleAchieveModule == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[_onEventAchieveUpdate][a_eventID=%d] %s[角色成就模块获取失败]",a_eventID,roleKey.toLogString().c_str());
       return;
    }
    roleAchieveModule->onEventAchieveUpdate(a_eventID,a_stream);
}

}//GM

}//PlayerSystem

}//GSLib

