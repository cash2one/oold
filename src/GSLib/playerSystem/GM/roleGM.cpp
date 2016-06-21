#include <stdarg.h>
#include <GSLib/dbSystem/GM/dbSystemGM.h>
#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/tracer.h>
#include "roleConfigGMMgr.h"
#include <GSLib/playerSystem/GM/playerSystemGM.h>
#include <GSLib/equipSystem/GM/roleEquipModule.h>
#include <GSLib/skillSystem/GM/roleSkillModule.h>
#include <GSLib/petSystem/GM/petModule.h>
#include <GSLib/prizeSystem/GM/rolePrizeModule.h>
#include <GSLib/achieveSystem/GM/achieveModule.h>
#include <GSLib/taskSystem/GM/roleTaskModule.h>
#include <BSLib/utility/convert.h>
#include <GSLib/itemSystem/GM/itemAttributeGM.h>
#include <GSLib/equipSystem/GM/roleEquipGM.h>
#include <GSLib/equipSystem/GM/roleEquipModule.h>
#include <GSLib/chatSystem/GM/roleChatModule.h>
#include <GSLib/sceneSystem/GM/roleSceneModule.h>


namespace GSLib
{

namespace PlayerSystem
{	

namespace GM
{

CRoleGM::CRoleGM(const GSLib::SRoleKey& a_roleKey, CPlayerGM* a_playerGM,RoleID a_roleID)
: m_playerGM(a_playerGM)
, m_roleKey(a_roleKey) 
, m_roleID(a_roleID)
, m_roleTPID(0)
, m_combat(0)
,m_historyCombatPower(0)
, m_roleStatus(STATUS_NULL)
, m_invalidFlag(0)
{
	m_playerModuleList.resize(EMODULECTYPE_MAX, NULL);
    m_lastQuitTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
    m_loginTime = m_lastQuitTime;
    m_vipGiftRefreshTime = _getVipGiftRefreshTime();
}

CRoleGM::CRoleGM(const GSLib::SRoleKey& a_roleKey, CPlayerGM* a_playerGM,RoleID a_roleID,BSLib::uint32 a_roleTPID,const std::string& a_roldName)
: m_playerGM(a_playerGM)
, m_roleKey(a_roleKey)
, m_roleID(a_roleID)
, m_roleTPID(a_roleTPID)
, m_combat(0)
, m_historyCombatPower(0)
, m_roleStatus(STATUS_NULL)
, m_invalidFlag(0)
{
	m_playerModuleList.resize(EMODULECTYPE_MAX, NULL);
    _setRoleName(a_roldName);
    m_lastQuitTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
    m_loginTime = m_lastQuitTime;
    m_vipGiftRefreshTime = _getVipGiftRefreshTime();
}

CRoleGM::~CRoleGM()
{
}

void CRoleGM::preInit(bool isFirst)
{
	_initRoleData(isFirst);
	_preInitModule(isFirst);
    if(isFirst){
        //_initRoleSkillByConfig();
    }
}

void CRoleGM::postInit(bool isFirst)
{
	_postInitModule(isFirst);
}

void CRoleGM::initToClient()
{
	_initToClient();
}

void CRoleGM::final()
{
	_finalModule();
}

void CRoleGM::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	_initModuleMsg(a_msgExecMgr); 
}

void CRoleGM::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	_freeModuleMsg(a_msgExecMgr);
}

void CRoleGM::updateDataToDB(bool a_first)
{
	_updateRoleDataToDB(a_first);
    _updateVipGiftDataToDB(a_first);
	_updateModuleDataToDB();
}

void CRoleGM::outputGameLog(const std::string& a_gameLable, const char* a_format, ...)
{
	std::string strFormat;

	va_list args;
	va_start(args, a_format);

	BSLib::Utility::stringFormat(strFormat, a_format, args);

	va_end(args);

    std::string roleName = "";
#if defined(WIN32)
    BSLib::Utility::CConvert::utf8ToGB2312(roleName,m_roleName);
#else
    roleName = m_roleName;
#endif

	BSLib::Utility::CDateTime now = BSLib::Utility::CDateTime::getCurrentTime();
	BSLIB_LOG_INFOR(ETT_GSLIB_GAME, "[%s][f_time=%s][f_acc_id=%lld][f_char_id=%d]%s", 
		a_gameLable.c_str(), 
		now.toString().c_str(),
		m_roleKey.getAccountID(), 
		m_roleKey.getIndex(),
		strFormat.c_str());
}

std::string CRoleGM::getRoleLogString() const
{
    std::string roleName = "";
#if defined(WIN32)
    BSLib::Utility::CConvert::utf8ToGB2312(roleName,m_roleName);
#else
    roleName = m_roleName;
#endif

    BSLib::Utility::CStringA log;
    log.format("%s[RoleName=%s]", m_roleKey.toLogString().c_str(),roleName.c_str());
    return log;
}

void CRoleGM::_updateRoleDataToDB(bool a_first)
{
    DB::SRoleData roleData;
    if(a_first){
        m_createTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
        m_lastQuitTime = m_createTime;
        m_loginTime = m_createTime;
        m_lastLoginTime = m_createTime;
        m_lastQuitTime = m_createTime;
    }
    getRoleDBData(roleData);

    if (!updateTableData(EDBTABLEID_ROLE_DATA, &roleData, sizeof(DB::SRoleData))) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新角色信息失败，[AccountID=%lld][ZoneID=%d][a_roleName=%s][a_roleType=%d]",
            getAccountID(), getZoneID(),getName().c_str(),roleData.m_roleTPID);
    }
}

void CRoleGM::_updateVipGiftDataToDB(bool a_first)
{
    _refreshVipGift(); 
    DB::SRoleVipGiftData vipData;
    vipData.m_zoneID = getZoneID();
    vipData.m_accountID = getAccountID();
    vipData.m_roleIndex = getRoleIndex();
    vipData.m_vipGiftRefreshTime = _getPreVipGiftRefreshTime();
   
    std::map<BSLib::uint32, SVipLevelGift*>::iterator it = m_vipLevelGiftMap.begin();
    for (; it != m_vipLevelGiftMap.end(); ++it) {
        SVipLevelGift* data =  it->second;
        if (data == NULL) {
            continue;
        }
        DB::SVipGift vipGift;
        vipGift.m_vipLevel = data->m_vipLevel;
        vipGift.m_giftStatus = data->m_giftStatus;
        vipData.m_vipGiftList.push_back(vipGift);
    }
    
    BSLib::Utility::CStream a_stream;
    a_stream.reset();
    vipData.serializeTo(a_stream);
    if (!updateTableData("","",EDBTABLEID_ROLE_VIPGIFT_DATA,a_stream,true)){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新Vip礼包数据失败");
    }
}

bool CRoleGM::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	return _cbSelectKeyTableData(a_keyTable, a_tableID, a_moduleType, a_sessionID);
}

bool CRoleGM::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	return _cbSelectKeyIndexTableData(a_keyTable, a_tableID, a_moduleType, a_sessionID);
}

bool CRoleGM::cbSelectGlobalMultiTableData(EModuleType a_srcModuleType,BSLib::uint32 a_sessionID,void* a_ptr,BSLib::uint32 a_state,std::vector<GSLib::DBSystem::SSelectTablesResult>& a_ackSelectTablesResultArray,std::vector<GSLib::DBSystem::CKeyTablePtr>& a_keyTablePtrArray,std::vector<GSLib::DBSystem::CKeyIndexTablePtr>& a_keyIndexTablePtrArray)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "GSLIB_SESSIONID_GET_ROLE_ALL_DATA:cbSelectGlobalMultiTableData");
    return _cbSelectGlobalMultiTableData(a_srcModuleType,a_sessionID,a_ptr,a_state,a_ackSelectTablesResultArray,a_keyTablePtrArray,a_keyIndexTablePtrArray);
}
void CRoleGM::selectRoleData(const SRoleKey& a_roleKey,BSLib::uint32 a_sessionID,EModuleType a_srcModuleType ,void* a_ptr)
{
    const SRoleKey& srcRoleKey = getRoleKey();
    std::vector<GSLib::DBSystem::SReqTablesData> selectDataArray;
    selectDataArray.clear();
    GSLib::DBSystem::SReqTablesData req;
    req.m_funcType = GFLib::EFUNCTYPE_NULL;
    req.m_tableID = GSLib::EDBTABLEID_ROLE_DATA;
    req.m_moduleType = EMODULECTYPE_NULL;
    req.m_tableKey = a_roleKey.getDBAccountKey();
    req.m_tableIndex = a_roleKey.getDBIndex();
    req.m_strWhere = "";
    req.m_roleKey = a_roleKey;
    selectDataArray.push_back(req);

    req.clear();
    req.m_funcType = GFLib::EFUNCTYPE_NULL;
    req.m_tableID = GSLib::EDBTABLEID_ROLE_SKILL_DATA;
    req.m_moduleType = EMODULECTYPE_SKILL;
    req.m_tableKey = a_roleKey.getDBKey();
    req.m_tableIndex = "";
    req.m_strWhere = "";
    req.m_roleKey = a_roleKey;
    selectDataArray.push_back(req);

    if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().selectGlobalMultiTableData(srcRoleKey,a_srcModuleType,a_sessionID,a_ptr,selectDataArray)) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "selectRoleData[selectDataArray.size()=%d]", selectDataArray.size());
        return;
    }
}


void CRoleGM::initRoleDataFromDB(const DB::SRoleData& a_roleData)
{
	m_roleTPID = a_roleData.m_roleTPID;
    m_roleID = a_roleData.m_roleID;
    m_combat = a_roleData.m_combat;
	m_historyCombatPower = a_roleData.m_historyMaxCombatPower;

    _setRoleName(a_roleData.m_roleName);
	_setExp(a_roleData.m_roleEXP);
	_setGold(a_roleData.m_gold);
	_setResource(ATTR_LIGHT_POWER, a_roleData.m_lightPower);

    _setResource(ATTR_SCENEID,a_roleData.m_sceneID);
    _setResource(ATTR_LEVEL,a_roleData.m_roleLevel);
	_setResource(ATTR_PVPCOIN,a_roleData.m_PVPCoin);
	_setResource(ATTR_CHARGE_DIAMOND,a_roleData.m_chargeDiamond);
	_setResource(ATTR_BIND_DIAMOND,a_roleData.m_bindDiamond);
	_setResource(ATTR_SKILLPOINT,a_roleData.m_skillPoint);

	_setResource(ATTR_POP,a_roleData.m_rolePOP);
	_setResource(ATTR_VITALITY,a_roleData.m_vitality);
	_setResource(ATTR_QUALITY,a_roleData.m_quality);
	_setResource(ATTR_STARLEVEL,a_roleData.m_starLevel);

    _setResource(ATTR_BAG_SIZE,a_roleData.m_bagCount);
    _setResource(ATTR_VIP_SCORE,a_roleData.m_vipScore);

    _setResource(ATTR_VIP_LEVEL,a_roleData.m_vipLevel);
    _setResource(ATTR_ACTIVE_DEGREE,a_roleData.m_activeDegree);
    _setResource(ATTR_TotalChargeDiamond,a_roleData.m_totalChargeDiamond);
    _setResource(ATTR_TotalUseChargeDiamond,a_roleData.m_totalUseChargeDiamond);
    _setResource(ATTR_TotalUseBindDiamond,a_roleData.m_totalUseBindDiamond);


    updateBaseBattleAttr();
    // 战斗属性
    m_totalBattleAttr.m_atk= a_roleData.m_atk; 
    m_totalBattleAttr.m_def= a_roleData.m_def;
    m_totalBattleAttr.m_atkCrift = a_roleData.m_atkCrift;
    m_totalBattleAttr.m_defCrift = a_roleData.m_defCrift;
    m_totalBattleAttr.m_hitRate = a_roleData.m_hitRate;
    m_totalBattleAttr.m_missRate = a_roleData.m_missRate;
    m_totalBattleAttr.m_maxHP = a_roleData.m_maxHP;

    m_createTime = a_roleData.m_createTime;
    m_lastLoginTime = a_roleData.m_lastLoginTime;
    m_lastQuitTime = a_roleData.m_lastQuitTime;
	m_roleLastSkillUpdateTime.setTime((time_t)a_roleData.m_lastSkillUpdateTime);
    m_roleLastVitalityUpdateTime.setTime((time_t)a_roleData.m_lastVitalityUpdateTime);
	
}

bool CRoleGM::getRoleData(BSLib::Utility::CStream& a_stream)
{
	a_stream.reset();
    a_stream << getAccountID();
 	a_stream << getZoneID();
	a_stream << getRoleIndex();

    a_stream << getName();
	a_stream << getTPID();
	a_stream << getRoleID();

    a_stream << getLevel();
	a_stream << getExp();
	a_stream << getGold();
	a_stream << getLightPower();
	a_stream << getQuality();
	a_stream << getStarLevel();
	a_stream << getPVPCoin();
	a_stream << getTotalDiamond();
	a_stream << getSkillPoint();
    
	a_stream << getPOP();
	a_stream << getVitality();
	a_stream << getHP();
	a_stream << getSP();

    a_stream << getSceneID();
    a_stream << getVipLevel();
    a_stream << getVipScore();
    a_stream << getActiveDegree();
    
	m_totalBattleAttr.serializeTo(a_stream);
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "序列化角色数据getRoleData:%s",m_totalBattleAttr.toLogString().c_str());
    a_stream << getCombat();
	a_stream << getHistoryMaxCombat();
    EquipSystem::GM::CRoleEquipModule* equipModule =  (EquipSystem::GM::CRoleEquipModule*)getPlayerModuleGM(EMODULECTYPE_EQUIP);
    if (equipModule == NULL) {
        return false;
    }

    equipModule->getEquipIDList(a_stream);
    return true;

}

bool CRoleGM::getRoleDBData(DB::SRoleData& a_roleData) const
{
    std::string roleName = getName();
    BSLibSprintf(a_roleData.m_roleName,sizeof(char)*(GSLIB_TEXT_MAX_ROLE_NAME + 1),"%s",roleName.c_str());

    a_roleData.m_zoneID    = getZoneID();
    a_roleData.m_accountID = getAccountID();
    a_roleData.m_roleTPID  = getTPID();
    a_roleData.m_roleID    = getRoleID();
    a_roleData.m_roleIndex = getRoleIndex();

    a_roleData.m_roleEXP   = getExp();
    a_roleData.m_gold      = getGold();
    a_roleData.m_starLevel = getStarLevel();
    a_roleData.m_quality   = getQuality();

    a_roleData.m_vitality  = getVitality();
    a_roleData.m_roleLevel = getLevel();

    a_roleData.m_skillPoint = getSkillPoint();
    a_roleData.m_rolePOP    = getPOP();
    a_roleData.m_PVPCoin    = getPVPCoin();
    
    a_roleData.m_bagCount    = getBagSize();
    a_roleData.m_invalidFlag = m_invalidFlag;
    a_roleData.m_combat      = getCombat();
	a_roleData.m_historyMaxCombatPower = getHistoryMaxCombat();

    a_roleData.m_vipLevel = getVipLevel();
    a_roleData.m_vipScore = getVipScore();
    a_roleData.m_activeDegree = getActiveDegree();
    
    a_roleData.m_bindDiamond = getBindDiamond();
    a_roleData.m_chargeDiamond = getChargeDiamond();
    a_roleData.m_totalChargeDiamond = getTotalChargeDiamond();
    a_roleData.m_totalUseBindDiamond = getTotalUseBindDiamond();
    a_roleData.m_totalUseChargeDiamond = getTotalUseChargeDiamond();

	a_roleData.m_lightPower = getLightPower();

    a_roleData.m_atk= getRoleTotalBattleAttr(ATTR_ATK);
    a_roleData.m_def = getRoleTotalBattleAttr(ATTR_DEF);
    a_roleData.m_atkCrift = getRoleTotalBattleAttr(ATTR_ATK_CRIFT);
    a_roleData.m_defCrift = getRoleTotalBattleAttr(ATTR_DEF_CRIFT);
    a_roleData.m_hitRate = getRoleTotalBattleAttr(ATTR_HIT_RATE);
    a_roleData.m_missRate = getRoleTotalBattleAttr(ATTR_MISS_RATE);
    a_roleData.m_maxHP = getRoleTotalBattleAttr(ATTR_MAXHP);

    a_roleData.m_bagCount = getBagSize();

    a_roleData.m_createTime          = m_createTime;
    a_roleData.m_lastQuitTime        = m_lastQuitTime;
    a_roleData.m_lastLoginTime       = m_loginTime;
    a_roleData.m_lastSkillUpdateTime = m_roleLastSkillUpdateTime.getSeconds();
    a_roleData.m_lastVitalityUpdateTime = m_roleLastVitalityUpdateTime.getSeconds();
    return true;
}


void CRoleGM::getRoleBaseInfo(BSLib::Utility::CStream& a_stream)
{
    getRoleData(a_stream);
}

CRoleModuleGM* CRoleGM::getPlayerModuleGM(EModuleType a_moduleType)
{
	if (a_moduleType >= (EModuleType)m_playerModuleList.size()) {
		return NULL;
	}
	return m_playerModuleList[a_moduleType];
}


CRoleBagModuleGM* CRoleGM::getRoleBag() 
{
	if (m_playerModuleList.size() < EMODULECTYPE_MAX) {
		return NULL;
	}
	return (CRoleBagModuleGM*)m_playerModuleList[EMODULECTYPE_BAG];
}

EquipSystem::GM::CRoleEquipModule * CRoleGM::getEquipModule() const
{
	if (m_playerModuleList.size() > EMODULECTYPE_MAX) {
		return NULL;
	}
	return (EquipSystem::GM::CRoleEquipModule*)m_playerModuleList[EMODULECTYPE_EQUIP];
}

ChatSystem::GM::CRoleChatModule * CRoleGM::getChatModule() const
{
	if (m_playerModuleList.size() > EMODULECTYPE_MAX) {
		return NULL;
	}
	return (ChatSystem::GM::CRoleChatModule*)m_playerModuleList[EMODULECTYPE_CHAT];
}

FriendSystem::GM::CRoleFriendModule * CRoleGM::getFriendModule() const
{
	if (m_playerModuleList.size() > EMODULECTYPE_MAX) {
		return NULL;
	}
	return (FriendSystem::GM::CRoleFriendModule*)m_playerModuleList[EMODULETYPE_FRIEND];
}

SceneSystem::GM::CRoleSceneModule * CRoleGM::getSceneModule() const
{
	if (m_playerModuleList.size() > EMODULECTYPE_MAX) {
		return NULL;
	}
	return (SceneSystem::GM::CRoleSceneModule*)m_playerModuleList[EMODULECTYPE_SCENE];
}

PrizeSystem::GM::CRolePrizeModule * CRoleGM::getPrizeModule() const
{
	if (m_playerModuleList.size() > EMODULECTYPE_MAX) {
		return NULL;
	}
	return (PrizeSystem::GM::CRolePrizeModule*)m_playerModuleList[EMODULECTYPE_PRIZE];
}

bool CRoleGM::sendMsgToClient(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
    LoginSystem::GM::CNetPlayerGM *player = getPlayerGM();
    if(player != NULL){
        return player->sendMsgToClient(a_msg,a_msgSize);
    }
	return false; 
}

bool CRoleGM::sendMsgToClient(GFLib::CMessage& a_msg)
{
    LoginSystem::GM::CNetPlayerGM *player = getPlayerGM();
    if(player != NULL){
        return player->sendMsgToClient(a_msg);
    }
    return false; 
}

bool CRoleGM::sendMsgToGateServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
    LoginSystem::GM::CNetPlayerGM *player = getPlayerGM();
    if(player != NULL){
        return player->sendMsgToGateServer(a_msg, a_msgSize);
    }
    return false; 
}

bool CRoleGM::sendMsgToGateServer(GFLib::CMessage& a_msg)
{
    LoginSystem::GM::CNetPlayerGM *player = getPlayerGM();
    if(player != NULL){
        return player->sendMsgToGateServer(a_msg);
    }
    return false; 
}

bool CRoleGM::sendMsgToDataServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
    LoginSystem::GM::CNetPlayerGM *player = getPlayerGM();
    if(player != NULL){
        return player->sendMsgToDataServer( a_msg, a_msgSize);
    }
    return false; 
}

bool CRoleGM::sendMsgToDataServer(GFLib::CMessage& a_msg)
{
    LoginSystem::GM::CNetPlayerGM *player = getPlayerGM();
    if(player != NULL){
        return player->sendMsgToDataServer(a_msg);
    }
    return false;
}

bool CRoleGM::sendMsgToCenterServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
    LoginSystem::GM::CNetPlayerGM *player = getPlayerGM();
    if(player != NULL){
        return player->sendMsgToCenterServer(a_msg, a_msgSize);
    }
    return false;
}

bool CRoleGM::sendMsgToCenterServer(GFLib::CMessage& a_msg)
{
    LoginSystem::GM::CNetPlayerGM *player = getPlayerGM();
    if(player != NULL){
        return player->sendMsgToCenterServer(a_msg);
    }
    return false;
}

bool CRoleGM::updateTableData(EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave)
{
	if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().updateTableData("", "", "", a_tableID, a_stream, a_needSave)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新表[TableID=%d]失败%s", a_tableID, getRoleKey().toLogString().c_str());
		return false;
	}
	return true;
}

bool CRoleGM::updateTableData(EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize, bool a_needSave)
{
	if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().updateTableData("", "", "", a_tableID, a_data, a_dataSize, a_needSave)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新表[TableID=%d]失败%s", a_tableID, getRoleKey().toLogString().c_str());
		return false;
	}
	return true;
}

bool CRoleGM::updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave)
{
	const SRoleKey& roleKey = getRoleKey();
	std::string tableKey = roleKey.getDBKey();
	if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().updateTableData(tableKey, a_tableIndex, a_name, a_tableID, a_stream, a_needSave)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新表[TableID=%d]失败%s", a_tableID, roleKey.toLogString().c_str());
		return false;
	}
	return true;
}

bool CRoleGM::updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize, bool a_needSave)
{
	const SRoleKey& roleKey = getRoleKey();
	std::string tableKey = roleKey.getDBKey();
	if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().updateTableData(tableKey, a_tableIndex, a_name, a_tableID, a_data, a_dataSize, a_needSave)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新表[TableID=%d]失败%s", a_tableID, roleKey.toLogString().c_str());
		return false;
	}
	return true;
}

bool CRoleGM::notifySaveAllTableDataToDB()
{
	return notifySaveTableDataToDB(EDBTABLEID_NULL);
}

bool CRoleGM::notifySaveTableDataToDB(EDBTableID a_tableID)
{
	CPlayerGM* playerGM = getPlayerGM();
	if (playerGM == NULL) {
		return false;
	}
	//return GSLib::DBSystem::GM::CDBSystemGM::singleton().saveTableData(playerGM->getAccountID(), getRoleIndex(), a_tableID);
	return true;
}

void CRoleGM::updateBaseBattleAttr()
{
    BSLib::int32 level = (BSLib::int32)getLevel();
	BSLib::uint32 roleTPID = getTPID();
    BSLib::uint32 baseAttr = level * level + level + 38;
	switch (roleTPID) 
	{
	case 1:
		{
			m_battleAttr.m_atk = BSLib::uint32(-0.23 * level * level + 59 * level + 442);
			m_battleAttr.m_def = BSLib::uint32(-0.21 * level * level + 53 * level + 438);
			m_battleAttr.m_maxHP = BSLib::uint32(-2.3 * level * level + 600 * level + 5000);
			m_battleAttr.m_hitRate = BSLib::uint32(0.6 * level * level + 7 * level + 90);
			m_battleAttr.m_missRate = BSLib::uint32(0.7 * level * level + 8 * level + 100);
			m_battleAttr.m_atkCrift = BSLib::uint32(0.5 * level * level + 6 * level + 80);
			m_battleAttr.m_defCrift = BSLib::uint32(0.6 * level * level + 7 * level + 90);
		}
		break;
	case 2:
		{
			m_battleAttr.m_atk = BSLib::uint32(-0.23 * level * level + 59 * level + 462);
			m_battleAttr.m_def = BSLib::uint32(-0.21 * level * level + 53 * level + 418);
			m_battleAttr.m_maxHP = BSLib::uint32(-2.3 * level * level + 600 * level + 4800);
			m_battleAttr.m_hitRate = BSLib::uint32(0.5 * level * level + 6 * level + 80);
			m_battleAttr.m_missRate = BSLib::uint32(0.6 * level * level + 7 * level + 90);
			m_battleAttr.m_atkCrift = BSLib::uint32(0.6 * level * level + 7 * level + 90);
			m_battleAttr.m_defCrift = BSLib::uint32(0.7 * level * level + 8 * level + 100);
		}
		break;
	case 3:
		{
			m_battleAttr.m_atk = BSLib::uint32(-0.23 * level * level + 59 * level + 482);
			m_battleAttr.m_def = BSLib::uint32(-0.21 * level * level + 53 * level + 398);
			m_battleAttr.m_maxHP = BSLib::uint32(-2.3 * level * level + 600 * level + 5200);
			m_battleAttr.m_hitRate = BSLib::uint32(0.4 * level * level + 5 * level + 70);
			m_battleAttr.m_missRate = BSLib::uint32(0.5 * level * level + 6 * level + 80);
			m_battleAttr.m_atkCrift = BSLib::uint32(0.4 * level * level + 5 * level + 70);
			m_battleAttr.m_defCrift = BSLib::uint32(0.5 * level * level + 6 * level + 80);
		}
		break;
	default:
		break;
	}

}

bool CRoleGM::updateTotalBattleAttr(bool a_notify)
{
    EquipSystem::GM::CRoleEquipModule* equipModule =  (EquipSystem::GM::CRoleEquipModule*)getPlayerModuleGM(EMODULECTYPE_EQUIP);
    if (equipModule == NULL) {
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "装备模块未初始完成，不更新角色属性");
        return false;
    }

    PetSystem::GM::CPetModule* petModule =  (PetSystem::GM::CPetModule*)getPlayerModuleGM(EMODULECTYPE_PET);
    if (petModule == NULL) {
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "伙伴模块未初始完成，不更新角色属性");
        return false;
    }
   
    m_totalBattleAttr.cleanAttr();

    const SBattleAttribute roleBattleAttr = getRoleBattleAttr();
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "角色基础战斗属性值[battleAttribute=%s]",roleBattleAttr.toLogString().c_str());
    m_totalBattleAttr.addAttr(roleBattleAttr);

    const SBattleAttribute& equipTotalBattleAttr = equipModule->getTotalBattleAttr();
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "装备对角色战斗属性影响总值[battleAttribute=%s]",equipTotalBattleAttr.toLogString().c_str());
    m_totalBattleAttr.addAttr(equipTotalBattleAttr);

    const SBattleAttribute& petTotalBattleAttr = petModule->getTotalBattleAttr();
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "伙伴对角色战斗属性影响总值[battleAttribute=%s]",petTotalBattleAttr.toLogString().c_str());
    m_totalBattleAttr.addAttr(petTotalBattleAttr);

    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "角色最终战斗属性[battleAttribute=%s]",m_totalBattleAttr.toLogString().c_str());
    updateCombat();

    if(!a_notify){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "不通知客户端");
        return true;
    }

    _notifyUpdateRoleDataToCenter();
    _notifyRoleBattleAttributeToClient();
    
    return true;
}

// 系统暂定 
void CRoleGM::updateCombat()
{
    // 战斗力公式 i.	战斗力=攻击力*2 + 防御力 + 生命值/5 + 命中/5 + 闪避/2 + 暴击/2 + 抗暴/5 
	float combat = (float)(m_totalBattleAttr.m_atk * 2 
		+ m_totalBattleAttr.m_def + (m_totalBattleAttr.m_atkCrift / 2) + (m_totalBattleAttr.m_defCrift / 5) + (m_totalBattleAttr.m_hitRate / 5) + (m_totalBattleAttr.m_missRate / 2)
		+ (m_totalBattleAttr.m_maxHP / 5 ) );

	// + 总技能学习等级之和 * 5
	SkillSystem::GM::CRoleSkillModule* skillModule = (SkillSystem::GM::CRoleSkillModule*)getPlayerModuleGM(EMODULECTYPE_SKILL);
	if(skillModule != NULL){
		combat += skillModule->getTotalSkillLevelSum() * 5 + skillModule->getLearnedSkillCount() * 50;
	}
	
	m_combat = (BSLib::uint32)combat;
	if (m_combat > m_historyCombatPower) {
		m_historyCombatPower = m_combat;
	}
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "角色战斗力[m_combat=%d]",m_combat);
    BSLib::Utility::CStream stream;
    stream.reset();
    const GSLib::SRoleKey roleKey = getRoleKey();
    roleKey.serializeTo(stream);
    stream << m_combat;
    GFLib::CommonServer::CEventMgr::singleton().sendEvent(EEVENTID_ACHIEVE_COMBAT,stream);
}

const std::string CRoleGM::getName() const 
{
	return m_roleName;
}

BSLib::uint64  CRoleGM::getRoleID() const
{
    return m_roleID;
}

BSLib::uint32  CRoleGM::getTPID() const
{
	return m_roleTPID;
}

BSLib::uint32  CRoleGM::getLevel() const
{ 
	return m_roleResource.getValue(ATTR_LEVEL);
}

BSLib::uint32 CRoleGM::getSceneID() const
{
	return m_roleResource.getValue(ATTR_SCENEID);
}

BSLib::uint64  CRoleGM::getExp() const 
{ 
	return m_roleResource.getExp();
}

BSLib::uint64  CRoleGM::getGold() const 
{ 
    return m_roleResource.getGold();
}

BSLib::uint32  CRoleGM::getStarLevel() const 
{ 
    return m_roleResource.getValue(ATTR_STARLEVEL);
}

BSLib::uint32  CRoleGM::getQuality() const 
{ 
    return m_roleResource.getValue(ATTR_QUALITY);
}

BSLib::uint32  CRoleGM::getPVPCoin() const 
{ 
	return m_roleResource.getValue(ATTR_PVPCOIN);
}

BSLib::uint32 CRoleGM::getVitality() const 
{
	return m_roleResource.getValue(ATTR_VITALITY);
}


BSLib::uint32 CRoleGM::getMaxVitality() const
{
    const BSLib::uint32 level = getLevel();
    BSLib::uint32 maxVitality =  200 + (level * 2 + 5) / 10;
    return maxVitality;
}

BSLib::uint32  CRoleGM::getPOP() const 
{ 
	return m_roleResource.getValue(ATTR_POP);
}

BSLib::uint32  CRoleGM::getTotalDiamond() const 
{ 
    BSLib::uint32 totalDiamond = getChargeDiamond() + getBindDiamond();
    return totalDiamond;
}

BSLib::uint32  CRoleGM::getChargeDiamond() const 
{ 
	return m_roleResource.getValue(ATTR_CHARGE_DIAMOND);
}

BSLib::uint32  CRoleGM::getBindDiamond() const 
{ 
	return m_roleResource.getValue(ATTR_BIND_DIAMOND);
}

BSLib::uint32  CRoleGM::getHP() const 
{ 
    return m_roleResource.getValue(ATTR_HP);
}

BSLib::uint32  CRoleGM::getSP() const 
{ 
    return m_roleResource.getValue(ATTR_SP);
}

BSLib::uint32  CRoleGM::getSkillPoint() const 
{ 
	return m_roleResource.getValue(ATTR_SKILLPOINT);
}

BSLib::uint32  CRoleGM::getSkillPointUpdateTime()
{
	BSLib::Utility::CDateTime leftTime = BSLib::Utility::CDateTime::getCurrentTime() - m_roleLastSkillUpdateTime;
	time_t passTime = leftTime.getSeconds();
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "过去时间[passTime=%llds]",passTime);
	BSLib::uint32 time = 0;
	if(passTime >= TIME_ROLE_SKILL_UPDATE){
		
		BSLib::uint32 addTime = (BSLib::uint32)((passTime>(TIME_ROLE_SKILL_UPDATE*20))?(TIME_ROLE_SKILL_UPDATE*20):passTime);
		BSLib::uint32 addSkillPoint = addTime/TIME_ROLE_SKILL_UPDATE;
		
		modifyRoleResource(ATTR_SKILLPOINT,addSkillPoint,"RECOVERY_UPDATE",false);
        m_roleLastSkillUpdateTime = m_roleLastSkillUpdateTime + (time_t)(addSkillPoint*TIME_ROLE_SKILL_UPDATE);
		time = TIME_ROLE_SKILL_UPDATE -(passTime%TIME_ROLE_SKILL_UPDATE);
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "过去时间[passTime=%d][addTime=%d][addSkillPoint=%d][time=%d]",passTime,addTime,addSkillPoint,time);
	}
	else{
		time = TIME_ROLE_SKILL_UPDATE-(BSLib::uint32)(passTime%TIME_ROLE_SKILL_UPDATE);
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "过去时间[passTime=%d][time=%d]",passTime,time);
	}
	return time;
}


BSLib::uint32  CRoleGM::getVitalityUpdateTime()
{
    BSLib::Utility::CDateTime leftTime = BSLib::Utility::CDateTime::getCurrentTime() - m_roleLastVitalityUpdateTime;
    time_t passTime = leftTime.getSeconds();
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "过去时间[passTime=%llds]",passTime);
    BSLib::uint32 time = 0;
    if(passTime >= TIME_ROLE_VITALITY_UPDATE){

        BSLib::uint32 addTimes = (BSLib::uint32)(passTime/TIME_ROLE_VITALITY_UPDATE);
        BSLib::uint32 addVitality = addTimes*1;
        const BSLib::uint32 curVitality = getVitality();
        const BSLib::uint32 maxVitality = getMaxVitality();
        if(curVitality < maxVitality){
            const BSLib::uint32 newVitality = curVitality + addVitality;
            if(newVitality > maxVitality){
                addVitality = maxVitality - curVitality;
            }
            modifyRoleResource(ATTR_VITALITY,addVitality,"RECOVERY_UPDATE",false);
        }
        
        m_roleLastVitalityUpdateTime = m_roleLastVitalityUpdateTime + (time_t)(addTimes*TIME_ROLE_VITALITY_UPDATE);
        time = TIME_ROLE_VITALITY_UPDATE -(passTime%TIME_ROLE_VITALITY_UPDATE);
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "过去时间[passTime=%d][addTime=%d][addVitality=%d][time=%d]",passTime,addTimes,addVitality,time);
    }
    else{
        time = TIME_ROLE_VITALITY_UPDATE-(BSLib::uint32)(passTime%TIME_ROLE_VITALITY_UPDATE);
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "过去时间[passTime=%d][time=%d]",passTime,time);
    }
    return time;
}

BSLib::uint32 CRoleGM::getVipLevel() const
{
    return m_roleResource.getValue(ATTR_VIP_LEVEL);
}

BSLib::uint32 CRoleGM::getVipScore() const
{
    return m_roleResource.getValue(ATTR_VIP_SCORE);
}

BSLib::uint32 CRoleGM::getActiveDegree() const
{
    return m_roleResource.getValue(ATTR_ACTIVE_DEGREE);
}
    
BSLib::uint32 CRoleGM::getTotalUseChargeDiamond()const
{
    return m_roleResource.getValue(ATTR_TotalUseChargeDiamond);
}

BSLib::uint32 CRoleGM::getTotalUseBindDiamond()const
{
    return m_roleResource.getValue(ATTR_TotalUseBindDiamond);
}

BSLib::uint32 CRoleGM::getTotalChargeDiamond()const
{
    return m_roleResource.getValue(ATTR_TotalChargeDiamond);
}
    
BSLib::uint32 CRoleGM::getResValue(ERoleResID a_resID) const
{
    return m_roleResource.getValue(a_resID);
}

BSLib::uint32 CRoleGM::getLightPower() const
{
	return m_roleResource.getValue(ATTR_LIGHT_POWER);
}

BSLib::uint32 CRoleGM::getBattleAttr(EAttrID a_attrID) const
{
   return m_battleAttr.getValue(a_attrID);
}
BSLib::uint32 CRoleGM::getRoleTotalBattleAttr(EAttrID a_attrID) const
{
    return m_totalBattleAttr.getValue(a_attrID);
}
const SBattleAttribute& CRoleGM::getRoleBattleAttr() const
{
    return m_battleAttr;
}
const SBattleAttribute& CRoleGM::getRoleTotalBattleAttr() const
{
    return m_totalBattleAttr;
}


// 系统暂定
// 战斗力公式=物理攻击*1.0 
//+物理防御*0.5
//+技能攻击*1.0
//+技能防御*0.5
//+暴击*1.0
//+暴击抗性*0.3
//+暴击伤害*0.5
//+伤害减免*0.5
//+命中*0.2
//+闪避*0.3
//+MAXHP*0.1
//+MAXSP*1 
//+热血*1.0  
BSLib::uint32  CRoleGM::getCombat() const
{
    return m_combat;
}

BSLib::uint32 CRoleGM::getHistoryMaxCombat() const
{
	return m_historyCombatPower;
}

BSLib::uint32  CRoleGM::getBagSize() const
{
    return m_roleResource.getValue(ATTR_BAG_SIZE);
}

void CRoleGM::setRoleStatus(ERoleStatus a_roleStatus)
{ 
	if(a_roleStatus == m_roleStatus){
		return;
	}
	_setRoleStatus(STATUS_ACTIVE);
}


bool CRoleGM::isableModifyResource(ERoleResID a_resID,BSLib::int32 a_addValue) const
{
	BSLib::uint32 value = getResValue(a_resID);
	BSLib::int32 newValue = value + a_addValue;
	if(newValue < 0){
		return false;
	}
    return true;
}

bool CRoleGM::isableModifyGold(BSLib::int64 a_addValue) const
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "isableModifyGold[a_addValue=%lld]",a_addValue);
	BSLib::uint64 value = getGold();
	BSLib::int64 newValue = value + a_addValue;

	if(newValue < 0){
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "isableModifyGold[a_addValue=%lld]",a_addValue);
		return false;
	}
    return true;
}

bool CRoleGM::isableModifyExp(BSLib::int64 a_addValue) const
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "isableModifyExp[a_addValue=%lld]",a_addValue);
	BSLib::uint64 value = getExp();
	BSLib::int64 newValue = value + a_addValue;

	if(newValue < 0){
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "isableModifyExp[a_addValue=%lld]",a_addValue);
		return false;
	}
    return true;
}

bool CRoleGM::modifyRoleResource(ERoleResID a_resID,BSLib::int32 a_addValue,std::string a_reason,bool a_notify)
{	
	using namespace GSLib::ItemSystem::GM;
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "modifyRoleResource[a_attrID=%d][a_addValue=%ld][a_reason=%s][a_notify=%d]",a_resID,a_addValue,a_reason.c_str(),a_notify);
	const BSLib::uint32 oldValue = getResValue(a_resID);
	BSLib::int32 newValue = oldValue + a_addValue;

	BSLib::int32  delta = a_addValue > 0 ? a_addValue : (-a_addValue);

	if(newValue < 0){
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "modifyRoleResource error[a_resID=%d][a_addValue=%ld][a_reason=%s][a_notify=%d][newValue=%ld",a_resID,a_addValue,a_reason.c_str(),a_notify,newValue);
		return false;
	}

	switch(a_resID)
	{
    case ATTR_LEVEL:
        {
           _setResource(a_resID,newValue);
		   outputGameLog("t_player_level","[f_level=%d]", newValue);
        }
        break;
    case ATTR_VITALITY:
        {
           _setResource(a_resID,newValue);
		   outputGameLog("t_resource","[f_type=%d][f_resource_id=%u][f_count=%u][][f_source=%s][ModifyVitality]", a_addValue > 0 ? 1 : -1, EITEM_TP_VIR_VITALITY, delta, a_reason.c_str());
        }
        break;
    case ATTR_DIAMOND:
        {
            _setResource(a_resID,newValue);
			outputGameLog("t_resource","[f_type=%d][f_resource_id=%u][f_count=%u][][f_source=%s][ModifyDiamond]", a_addValue > 0 ? 1 : -1, EITEM_TP_VIR_DIAMOND, delta, a_reason.c_str());
        }
        break;
	case ATTR_CHARGE_DIAMOND:
		{
			_setResource(a_resID,newValue);
            outputGameLog("t_resource","[f_type=%d][f_resource_id=%u][f_count=%u][][f_source=%s][ModifyDiamond]", a_addValue > 0 ? 1 : -1, EITEM_TP_VIR_DIAMOND, delta, a_reason.c_str());
            if(a_notify){
                return _notifyUpdateRoleResource(ATTR_DIAMOND);
            }
            return true;
		}
		break;
	case ATTR_BIND_DIAMOND:
		{
			_setResource(a_resID,newValue);
            outputGameLog("t_resource","[f_type=%d][f_resource_id=%u][f_count=%u][][f_source=%s][ModifyDiamond]", a_addValue > 0 ? 1 : -1, EITEM_TP_VIR_DIAMOND, delta, a_reason.c_str());
            if(a_notify){
                return _notifyUpdateRoleResource(ATTR_DIAMOND);
            }
            return true;
		}
		break;
	case ATTR_SKILLPOINT:
		{
			newValue = (newValue>20)?20:newValue;
            //outputGameLog("ModifySkillPoint","[Type=%s][OldValue=%d][ModifyValue=%d][NewValue=%d]",a_reason.c_str(),oldValue,a_addValue,newValue);
			_setResource(a_resID,newValue);
		}
		break;
     case ATTR_BAG_SIZE:
        {
            _setResource(a_resID,newValue);
			outputGameLog("t_resource","[f_type=%d][f_resource_id=%u][f_count=%u][][f_source=%s][ModifyBagSize]", a_addValue > 0 ? 1 : -1, EITEM_TP_VIR_BAGEXPAND, delta, a_reason.c_str());
            if(a_notify){
                _notifyBagSizeToClient();
            }
            return true;
        }
        break;
     case ATTR_VIP_SCORE:
        {
         	_setResource(a_resID,newValue);
			outputGameLog("t_resource","[f_type=%d][f_resource_id=%u][f_count=%u][][f_source=%s][ModifyVipScore]", a_addValue > 0 ? 1 : -1, EITEM_TP_VIR_VIPSCORE, delta, a_reason.c_str());
            _checkRoleVipLevelUpgrade(a_notify);
        }
        break;
	case ATTR_ACTIVE_DEGREE:
        {
           	_setResource(a_resID,newValue);
			outputGameLog("t_resource","[f_type=%d][f_resource_id=%u][f_count=%u][][f_source=%s][ModifyActiveDegree]", a_addValue > 0 ? 1 : -1, EITEM_TP_VIR_ACTIVE_DEGREE, delta, a_reason.c_str());
            modifyRoleResource(ATTR_VIP_SCORE,a_addValue,a_reason,a_notify);
            
        }
        break;
    case ATTR_VIP_LEVEL:
        {
            _setResource(a_resID,newValue);
           // outputGameLog("ModifyVipLevel","[Type=%s][OldValue=%d][ModifyValue=%d][NewValue=%d]",a_reason.c_str(),oldValue,a_addValue,newValue);
            BSLib::Utility::CStream stream;
            stream.reset();
            const GSLib::SRoleKey roleKey = getRoleKey();
            roleKey.serializeTo(stream);
            BSLib::uint32 subID =  SUB_ACHIEVE_VIPLEVEL; 
            BSLib::uint32 level = getVipLevel(); 
            stream << subID;
            stream << level;
            GFLib::CommonServer::CEventMgr::singleton().sendEvent(EEVENTID_ACHIEVE_CHARGEPAY,stream);
        }
        break;
       
	default:
		{
			_setResource(a_resID,newValue);
            //outputGameLog("ModifyResByID","[Type=%s][OldValue=%d][ModifyValue=%d][NewValue=%d][ID=%d]",a_reason.c_str(),oldValue,a_addValue,newValue,a_resID);
		}
		break;
	}

    _updateRoleDataToDB(false);
    if(a_notify){
        return _notifyUpdateRoleResource(a_resID);
    }
    return true;
}

bool CRoleGM::modifyGold(BSLib::int64 a_addValue,std::string a_reason,bool a_notify)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "modifyGold[a_addValue=%lld][a_reason=%s][a_notify=%d]",a_addValue,a_reason.c_str(),a_notify);
    BSLib::uint64 curGold = getGold();
    if(a_addValue < 0){
        BSLib::uint64 rmGold = BSLib::uint64(0-a_addValue);
        if(rmGold > curGold){
            BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "modifyGold error,[rmGold=%lld][a_reason=%s][a_notify=%d][curGold=%lld",rmGold,a_reason.c_str(),a_notify,curGold);
            return false;
        }
    }

	_updateGold(a_addValue,a_reason); 
	if(a_notify){
        return _notifyUpdateRoleUInt64Resource(ATTR_GOLD);
	}

	return true;
}

bool CRoleGM::modifyExp(BSLib::int64 a_addValue,std::string a_reason,bool a_notify)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "modifyExp[a_addValue=%lld][a_reason=%s][a_notify=%d]",a_addValue,a_reason.c_str(),a_notify);
	const BSLib::uint64 oldValue = getExp();
	const BSLib::int64 newValue = oldValue + a_addValue;

	if(newValue < 0){
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "modifyExp error,[a_addValue=%lld][a_reason=%s][a_notify=%d][newValue=%lld",a_addValue,a_reason.c_str(),a_notify,newValue);
		return false;
	}
	m_roleResource.updateExp(newValue);
    _checkUpgrade(a_notify);
	
	using namespace GSLib::ItemSystem::GM;
	BSLib::int64  delta = a_addValue > 0 ? a_addValue : (-a_addValue);
	outputGameLog("t_resource","[f_type=%d][f_resource_id=%u][f_count=%lld][][f_source=%s][ModifyExp]", a_addValue > 0 ? 1 : -1, EITEM_TP_VIR_EXP, delta, a_reason.c_str());

    _updateRoleDataToDB(false);

	if(a_notify){
        return _notifyUpdateRoleUInt64Resource(ATTR_EXP);
	}

	return true;
}

bool CRoleGM::addDiamond(BSLib::uint32 a_value,std::string a_reason,bool a_notify)
{
	return _modifyDiamond((BSLib::int32)a_value, a_reason, a_notify);
}

bool CRoleGM::delDiamond(BSLib::uint32 a_value,std::string a_reason,bool a_notify)
{
	return _modifyDiamond((BSLib::int32)a_value * (-1), a_reason, a_notify);
}

bool CRoleGM::_modifyDiamond(BSLib::int32 a_addValue,std::string a_reason,bool a_notify)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "modifyDiamond[a_addValue=%d][a_reason=%s][a_notify=%d]",a_addValue,a_reason.c_str(),a_notify);
    BSLib::uint32 curValue = getTotalDiamond();
	BSLib::int64 newValue = (BSLib::int32)curValue + a_addValue;
	BSLib::uint32 value = 0;

    if(newValue < 0){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "modifyDiamond error,[a_addValue=%d][a_reason=%s][a_notify=%d][newValue=%d",a_addValue,a_reason.c_str(),a_notify,newValue);
        return false;
	} else if (newValue > BSLIB_INT32_MAX) {
		value = BSLIB_INT32_MAX;
        BSLIB_LOG_INFOR(ETT_GSLIB_PLAYERSYSTEM, "modifyDiamond error,[a_addValue=%d][a_reason=%s][a_notify=%d][curValue=%u][newValue=%u",
			a_addValue,a_reason.c_str(),a_notify, curValue, newValue);
	} else {
		value = (BSLib::uint32)newValue;
	}
    m_roleResource.setValue(ATTR_DIAMOND,value);

    if(a_notify){
        return _notifyUpdateRoleResource(ATTR_DIAMOND);
    }
    return true;
}

bool CRoleGM::chargeVipScore(BSLib::uint32 a_vipScore)
{
//     CPlayerGM* player = getPlayerGM();
//     if(player == NULL){
//         return false;
//     }
//     if(!player->chargeVipScore(a_vipScore)){
//         return false;
//     }
 	BSLib::uint32 total = m_roleResource.getValue(ATTR_VIP_SCORE);
// 	total += a_vipScore;
/*	_setResource(ATTR_VIP_SCORE, total);*/
	modifyRoleResource(ATTR_VIP_SCORE, a_vipScore, "activity", true);
   /* _checkRoleVipLevelUpgrade(true);*/
    return true;
}
bool CRoleGM::addUpgradeVipLevelGift(BSLib::uint32 a_oldVipLevel,BSLib::uint32 a_vipLevel)
{
    for(BSLib::uint32 i = a_oldVipLevel; i <= a_vipLevel; ++i){
        if(i == 0){
            continue;
        }
        addVipGift(i,0);
    }
    _updateVipGiftDataToDB(false);
    return true;
}

bool CRoleGM::addVipGift(BSLib::uint32 a_vipLevel,BSLib::uint32 a_giftStatus)
{
   SVipLevelGift *vipLevelGift = new SVipLevelGift();
   vipLevelGift->m_vipLevel = a_vipLevel;
   vipLevelGift->m_giftStatus = a_giftStatus;
   m_vipLevelGiftMap.insert(std::make_pair(a_vipLevel,vipLevelGift));
   return true;
}

bool CRoleGM::updateVipGift(BSLib::uint32 a_vipLevel,BSLib::uint32 a_status)
{
   std::map<BSLib::uint32, SVipLevelGift*>::iterator it =  m_vipLevelGiftMap.find(a_vipLevel);
   if(it == m_vipLevelGiftMap.end()){
       return false;
   }
   SVipLevelGift* gift = it->second;
   gift->m_giftStatus = a_status;
   _updateVipGiftDataToDB(false);
   return true;
}

bool CRoleGM::eraseVipGift(BSLib::uint32 a_vipLevel)
{
    std::map<BSLib::uint32, SVipLevelGift*>::iterator it =  m_vipLevelGiftMap.find(a_vipLevel);
    if(it == m_vipLevelGiftMap.end()){
        return false;
    }
     SVipLevelGift* gift = it->second;
     if(gift != NULL){
         BSLIB_SAFE_DELETE(gift);
         m_vipLevelGiftMap.erase(it);
     }
    return true;
}

void CRoleGM::removeAllVipLevelGift()
{
    std::map<BSLib::uint32, SVipLevelGift*>::iterator it = m_vipLevelGiftMap.begin();
    for (; it != m_vipLevelGiftMap.end(); ++it) {
        SVipLevelGift* data =  it->second;
        if (data == NULL) {
            continue;
        }
        BSLIB_SAFE_DELETE(data);
    }
    m_vipLevelGiftMap.clear();
}

bool CRoleGM::getCurrentVipGiftLevel(BSLib::uint32& a_vipLevel) const
{
    std::map<BSLib::uint32, SVipLevelGift*>::const_iterator it = m_vipLevelGiftMap.begin();
    for (; it != m_vipLevelGiftMap.end(); ++it) {
        SVipLevelGift* data =  it->second;
        if (data == NULL) {
            continue;
        }
        if(data->m_giftStatus == 0){
            a_vipLevel = data->m_vipLevel;
            return true;
        }
    }
    return false;
}


bool CRoleGM::getVipGift(BSLib::uint32 a_level)
{
    std::string a_vipGift;
    bool bVipGift = CRoleConfigGMMgr::singleton().getVipGift(a_level,a_vipGift);
    if(!bVipGift){
        return false;
    }
    
    PrizeSystem::GM::CRolePrizeModule *prizeModue = (PrizeSystem::GM::CRolePrizeModule *)getPlayerModuleGM(EMODULECTYPE_PRIZE);
    if (prizeModue == NULL) {
        return false;
    }
    return prizeModue->prizeRequest(a_vipGift,true,"vipGift");
}

bool CRoleGM::addLightPower(BSLib::uint32 a_value,std::string a_reason,bool a_notify)
{
	modifyRoleResource(ATTR_LIGHT_POWER, (BSLib::int32)a_value, a_reason, a_notify);
	return true;
}

bool CRoleGM::delLightPower(BSLib::uint32 a_value,std::string a_reason,bool a_notify)
{
	modifyRoleResource(ATTR_LIGHT_POWER, (BSLib::int32)a_value * (-1), a_reason, a_notify);
	return true;
}

BSLib::uint32 CRoleGM::getMaxPurchaseGoldTimes() const
{
	BSLib::uint32 vipLevel = getVipLevel();
	switch (vipLevel) {
		case 0 : return 1; break;
		case 1 : return 3; break;
		case 2 : return 5; break;
		case 3 : return 7; break;
		case 4 : return 12; break;
		case 5 : return 15; break;
		case 6 : return 18; break;
		case 7 : return 25; break;
		case 8 : return 26; break;
		case 9 : return 28; break;
		case 10 : return 30; break;
		default:return 30;
	}
}

BSLib::uint32 CRoleGM::getPurchaseGoldNeedDiamond(BSLib::uint32 a_times) const
{
	return (BSLib::uint32)(0.5 * a_times * a_times + 4);
}

BSLib::uint32 CRoleGM::getPurchasedGoldCount(BSLib::uint32 a_times) const
{
	return 50 * (getLevel() + a_times) * (getLevel() + a_times) + 8000;
}

void _cbSelectRoleTableData(BSLib::uint32 a_sessionID, EModuleType a_moduleType, GSLib::EDBTableID a_tableID, BSLib::Utility::CStream& a_stream)
{
	;
}

bool CRoleGM::_checkUpgrade(bool a_notify)
{
    BSLib::uint64 exp = getExp();
    BSLib::uint32 oldLevel = getLevel();
    //BSLib::uint32 newlevel = oldLevel;
    BSLib::uint32 upgradeCounts = 0;
    BSLib::uint64 leftExp = 0;
    CRoleConfigGMMgr::singleton().getUpgradeLevels(oldLevel,exp,upgradeCounts,leftExp); 
    if(upgradeCounts <= 0){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_checkUpgrade[oldLevel=%d][exp=%lld]",oldLevel,exp);
        return false;
    }
    m_roleResource.updateExp(leftExp);
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_checkUpgrade[oldLevel=%d][upgradeCounts=%d][leftExp=%lld]",oldLevel,upgradeCounts,leftExp);
    if(!modifyRoleResource(ATTR_LEVEL,upgradeCounts,"UPGRADE",a_notify)){
        return false;
    }

    updateTotalBattleAttr(true);
    
    TaskSystem::GM::CRoleTaskModule* taskModule = (TaskSystem::GM::CRoleTaskModule*)getPlayerModuleGM(EMODULECTYPE_TASK);
    if(taskModule == NULL){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CRoleTaskModule模块获取失败,updateMainTask未调用",oldLevel,exp);
        return true;
    }
    BSLib::uint32 lv = getLevel();
    taskModule->updateMainTask(lv);
    return true;
}

bool CRoleGM::_checkRoleVipLevelUpgrade(bool a_notify)
{
    CPlayerGM* player = getPlayerGM();
    if(player == NULL){
        return false;
    }
    BSLib::uint32 vipScore = getVipScore() + player->getVipScore();
    BSLib::uint32 oldLevel = getVipLevel();
    BSLib::uint32 newLevel = oldLevel;
    bool bUpgrade = CRoleConfigGMMgr::singleton().getUpgradeVipLevel(oldLevel,vipScore,newLevel); 
    if(!bUpgrade){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_checkUpgrade[oldLevel=%d][newLevel=%d]",oldLevel,newLevel);
        return false;
    }
    if(newLevel <= oldLevel){
        return false;
    }
   
    _refreshVipGift();
    BSLib::uint32 addLevel = newLevel - oldLevel;
    addUpgradeVipLevelGift(oldLevel,newLevel);
    return modifyRoleResource(ATTR_VIP_LEVEL,addLevel,"VIP_UPGRADE",a_notify);
}

void CRoleGM::_initRoleData(bool isFirst)
{
	if(isFirst){
		_initRoleResourceByConfig();
        _initRoleAttrByConfig();
	}
}

bool CRoleGM::_initRoleResourceByConfig()
{
    const SRoleInitConfig& config = CRoleConfigGMMgr::singleton().getRoleInitConfig();
    _setResource(ATTR_LEVEL,config.m_roleLevel);	
    _setResource(ATTR_VITALITY,config.m_roleVitality);	
    
    _setResource(ATTR_CHARGE_DIAMOND,0); 
    _setResource(ATTR_BIND_DIAMOND,config.m_roleDiamond);	
    _setResource(ATTR_PVPCOIN,config.m_rolePVPCoin);	
    _setResource(ATTR_SKILLPOINT,config.m_roleSkillPoint);	
    _setResource(ATTR_POP,config.m_rolePOP);
    _setResource(ATTR_BAG_SIZE,EBAGPOSITION_MAX_COUNT);

    _setResource(ATTR_VIP_LEVEL,0);
    _setResource(ATTR_ACTIVE_DEGREE,0);
    _setResource(ATTR_TotalChargeDiamond,0);
    _setResource(ATTR_TotalUseChargeDiamond,0);
    _setResource(ATTR_TotalUseBindDiamond,0);

    _setGold(config.m_roleGold);	
    _setExp(config.m_roleExp);	

    _checkRoleVipLevelUpgrade(false);
    return true;
}

bool CRoleGM::_initRoleAttrByConfig()
{
    m_roleLastSkillUpdateTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
    m_roleLastVitalityUpdateTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();

    return true;
}

bool CRoleGM::_initRoleSkillByConfig()
{
    SSkillInitConfig* skillData = CRoleConfigGMMgr::singleton().getSkillInitConfig(getTPID());
    if(skillData == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "getSkillInitConfig() 失败");
        return false;
    }

    SkillSystem::GM::CRoleSkillModule* skillModule = (SkillSystem::GM::CRoleSkillModule*)getPlayerModuleGM(EMODULECTYPE_SKILL);
    if(skillModule == NULL){
        return false;
    }
    std::map<SkillTPID, SkillLevel> skillList =skillData->m_skillList;

    BSLib::Utility::CStream stream;
    stream.reset();
    const GSLib::SRoleKey roleKey = getRoleKey();
    roleKey.serializeTo(stream);
    stream << skillList.size();

    std::map<SkillTPID, SkillLevel>::iterator it = skillList.begin();
    for (; it != skillList.end(); ++it) {
        SkillTPID skillTPID = it->first;
        SkillLevel skillLevel =  it->second;
        skillModule->initSkill(skillTPID,skillLevel);
        stream << skillLevel; 
    }
    GFLib::CommonServer::CEventMgr::singleton().sendEvent(EEVENTID_ACHIEVE_SKILL,stream);

    return true;
}

void CRoleGM::_deleteRoleDataToDB()
{
    m_invalidFlag = 1;
    DB::SRoleData roleData;
    getRoleDBData(roleData);

    if (!updateTableData(EDBTABLEID_ROLE_DATA, &roleData, sizeof(DB::SRoleData))) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新角色信息失败，[AccountID=%lld][ZoneID=%d][a_roleName=%s][a_roleType=%d]",
            getAccountID(), getZoneID(),getName().c_str(),roleData.m_roleTPID);
    }
}

void CRoleGM::onRoleActive()
{
    m_loginTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
	_onRoleActive();
}

void CRoleGM::onRoleInactive()
{
    m_lastQuitTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
	_onRoleInactive();
}

void CRoleGM::onRoleDelete()
{
    _deleteRoleDataToDB();
    _onRoleDelete();
}

void CRoleGM::_onRoleActive()
{
	std::vector<CRoleModuleGM*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleGM* module = m_playerModuleList[i_module];
		if (module != NULL) {
			BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_cbModuleRoleOnline[i_module=%d]", i_module);
			module->onRoleActive();
		}
	}
}

void CRoleGM::_onRoleInactive()
{
	std::vector<CRoleModuleGM*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleGM* module = m_playerModuleList[i_module];
		if (module != NULL) {
			BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "cbModuleRoleInactive[i_module=%d]", i_module);
			module->onRoleInactive();
		}
	}
}

void CRoleGM::_preInitModule(bool isFirst)
{
	std::vector<CRoleModuleGM*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleGM* module = m_playerModuleList[i_module];
		if (module != NULL) {
			continue;
		}
		module = CRoleModuleGMMgr::singleton().createRoleModule(this, (EModuleType)i_module);
		if (module == NULL) {
			continue;
		}
		m_playerModuleList[i_module] = module;
		module->preInit(isFirst);
	}

}

void CRoleGM::_postInitModule(bool isFirst)
{
	std::vector<CRoleModuleGM*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleGM* module = m_playerModuleList[i_module];
		if (module == NULL) {
			continue;
		}
		module->postInit(isFirst);
	}
}

void CRoleGM::_initToClient()
{
	std::vector<CRoleModuleGM*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleGM* module = m_playerModuleList[i_module];
		if (module != NULL) {
			BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_initToClient[i_module=%d]", i_module);
			module->initToClient();
		}
	}
}

void CRoleGM::_finalModule()
{
	std::vector<CRoleModuleGM*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleGM* module = m_playerModuleList[i_module];
		if (module != NULL) {
			module->final();
			BSLIB_SAFE_DELETE(module);
		}
	}
	m_playerModuleList.clear();
}

void CRoleGM::_initModuleMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	std::vector<CRoleModuleGM*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleGM* module = m_playerModuleList[i_module];
		if (module != NULL) {
			module->initMsg(a_msgExecMgr);
		}
	} 
}

void CRoleGM::_freeModuleMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	std::vector<CRoleModuleGM*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleGM* module = m_playerModuleList[i_module];
		if (module != NULL) {
			module->freeMsg(a_msgExecMgr);
		}
	} 
}

void CRoleGM::_onRoleDelete()
{
    std::vector<CRoleModuleGM*>::size_type i_module = 0;
    for (; i_module < m_playerModuleList.size(); ++i_module) {
        CRoleModuleGM* module = m_playerModuleList[i_module];
        if (module != NULL) {
            module->onRoleDelete();
        }
    }

    i_module = 0;
    for (; i_module < m_playerModuleList.size(); ++i_module) {
        CRoleModuleGM* module = m_playerModuleList[i_module];
        if (module != NULL) {
            BSLIB_SAFE_DELETE(module);
        }
    }
}

void CRoleGM::_updateModuleDataToDB()
{
	std::vector<CRoleModuleGM*>::size_type i_module = 0;
	for (; i_module < m_playerModuleList.size(); ++i_module) {
		CRoleModuleGM* module = m_playerModuleList[i_module];
		if (module != NULL) {
			module->updateDataToDB();
		}
	}
}


bool CRoleGM::_cbGetRoleTableData(const GSLib::SRoleKey& a_roleKey,GSLib::DBSystem::ETableKeyType a_TableKeyType,GSLib::DBSystem::CKeyIndexTablePtr& a_keyIndexTable, GSLib::DBSystem::CKeyTablePtr& a_keyTable,EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID,BSLib::Utility::CStream& a_stream)
{
    if(a_TableKeyType != GSLib::DBSystem::ETABLEKEYTYPE_KEY_INDEX){
        return false;
    }
    BSLib::Database::CDBTableRow* tableRow = a_keyIndexTable->getRow(a_roleKey.getDBAccountKey(),a_roleKey.getDBIndex());
    if (tableRow == NULL) {
        return false;
    }

    if (tableRow != NULL) {
        if (!tableRow->serializeTo(a_stream)) {
            return false; 
        }
        return true; 
    }
    
    return false;
}

bool CRoleGM::_cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
    if(EDBTABLEID_ROLE_VIPGIFT_DATA == a_tableID){
        DB::SRoleVipGiftData roleVipGiftData;
        BSLib::Database::CDBTableRow* tableRow = a_keyTable->getRow(getRoleDBKey());
        if (tableRow != NULL) {
            BSLib::Utility::CStream stream;
            if (!tableRow->serializeTo(stream)) {
               return false; 
            }
            DB::SRoleVipGiftData roleVipGiftData;
            roleVipGiftData.serializeFrom(stream);
            return _cbInitRoleVipGiftData(roleVipGiftData);
        }
        return true;
    }

	CRoleModuleGM* module = getPlayerModuleGM(a_moduleType);
	if (module == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "模块不存在[ModuleType=%d]", a_moduleType);
		return false;
	}
	return module->cbSelectKeyTableData(a_keyTable, a_tableID, a_sessionID);
}

bool CRoleGM::_cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable,EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	CRoleModuleGM* module = getPlayerModuleGM(a_moduleType);
	if (module == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "模块不存在[ModuleType=%d]", a_moduleType);
		return false;
	}
	return module->cbSelectKeyIndexTableData(a_keyTable, a_tableID, a_sessionID);
}

bool CRoleGM::_cbSelectGlobalMultiTableData(EModuleType a_srcModuleType,BSLib::uint32 a_sessionID,void* a_ptr,BSLib::uint32 a_state,std::vector<GSLib::DBSystem::SSelectTablesResult>& a_ackSelectTablesResultArray,std::vector<GSLib::DBSystem::CKeyTablePtr>& a_keyTablePtrArray,std::vector<GSLib::DBSystem::CKeyIndexTablePtr>& a_keyIndexTablePtrArray)
{
    CRoleAllData roleAllData;
    
    GSLib::SRoleKey a_roleKey;
    for(BSLib::uint32 i=0;i<a_ackSelectTablesResultArray.size();++i){
        GSLib::DBSystem::SSelectTablesResult result = a_ackSelectTablesResultArray[i];
        GSLib::DBSystem::CKeyTablePtr keyTable = a_keyTablePtrArray[i];
        GSLib::DBSystem::CKeyIndexTablePtr keyIndexTable = a_keyIndexTablePtrArray[i];
        if(result.m_status == GSLib::DBSystem::EDBOPTION_FAIL){
            _cbSelectMultiTableData(false,a_sessionID,a_srcModuleType,a_ptr,roleAllData);
            return false;
        }
        BSLib::Utility::CStream stream;
        stream.reset();
        if(!_cbSelectGetTableData(result.m_roleKey,result.m_tableKeyType,keyIndexTable,keyTable,result.m_tableID,result.m_moduleType,a_sessionID,stream)){
            BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "模块不存在[ModuleType=%d]", result.m_moduleType);
        }
        if(result.m_tableID == EDBTABLEID_ROLE_DATA){
            DB::SRoleData roleData;
            if(!stream.readReady()){
               continue; 
            }
            
            try {
                stream.read((char*)&roleData,sizeof(DB::SRoleData));
            } catch (...) {
                BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "DB::SRoleData序列化数据失败");
                _cbSelectMultiTableData(false,a_sessionID,a_srcModuleType,a_ptr,roleAllData);
                return false;
            }
            roleAllData.roleData = roleData;
        }
        else if(result.m_tableID == EDBTABLEID_ROLE_SKILL_DATA){
            if(!stream.readReady()){
                continue; 
            }
            if(!roleAllData.roleSkillData.serializeFrom(stream)){
                BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "DB::CRoleSkillData序列化数据失败");
                _cbSelectMultiTableData(false,a_sessionID,a_srcModuleType,a_ptr,roleAllData);
                return false;
            }
        }
    }

    return _cbSelectMultiTableData(true,a_sessionID,a_srcModuleType,a_ptr,roleAllData);
}

bool CRoleGM::_cbSelectMultiTableData(bool a_success,BSLib::uint32 a_sessionID,EModuleType a_srcModuleType,void* a_ptr,CRoleAllData& a_roleAllData)
{
    CRoleModuleGM* module = getPlayerModuleGM(a_srcModuleType);
    if (module == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "模块不存在[ModuleType=%d]", a_srcModuleType);
        return false;
    }
    return module->cbSelectMultiTableData(a_success,a_sessionID,a_ptr,a_roleAllData);
}

bool CRoleGM::_cbSelectGetTableData(const GSLib::SRoleKey& a_roleKey,GSLib::DBSystem::ETableKeyType a_TableKeyType,GSLib::DBSystem::CKeyIndexTablePtr& a_keyIndexTable, GSLib::DBSystem::CKeyTablePtr& a_keyTable,EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID,BSLib::Utility::CStream& a_stream)
{
    if (a_tableID == EDBTABLEID_ROLE_DATA){
       return _cbGetRoleTableData(a_roleKey,a_TableKeyType,a_keyIndexTable,a_keyTable,a_tableID,a_moduleType,a_sessionID,a_stream);
    }
    CRoleModuleGM* module = getPlayerModuleGM(a_moduleType);
    if (module == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "模块不存在[ModuleType=%d]", a_moduleType);
        return false;
    }
    return module->cbSelectGetTableData(a_roleKey,a_TableKeyType,a_keyIndexTable,a_keyTable, a_tableID, a_sessionID,a_stream);
}

void CRoleGM::_setRoleName(const std::string& a_roleName)
{
	m_roleName = a_roleName;
}

void CRoleGM::_setGold(const BSLib::uint64 value)
{
	m_roleResource.setGold(value);
}

void CRoleGM::_setExp(const BSLib::uint64 value)
{
	m_roleResource.setExp(value);
}

void CRoleGM::_setResource(ERoleResID a_resID,const BSLib::uint32 value)
{
	m_roleResource.setValue(a_resID,value);
    if(a_resID == ATTR_LEVEL){
        updateBaseBattleAttr();
        BSLib::Utility::CStream stream;
        stream.reset();
        const GSLib::SRoleKey roleKey = getRoleKey();
        roleKey.serializeTo(stream);
        BSLib::uint32 level = getLevel();
        stream << level;
        GFLib::CommonServer::CEventMgr::singleton().sendEvent(EEVENTID_ACHIEVE_ROLELEVEL,stream);
    }
    
}

bool CRoleGM::_updateGold(BSLib::int64 a_addValue,std::string a_reason)
{
	BSLib::uint64 oldGold  = getGold();
	BSLib::int64 newGold = oldGold;
	newGold += a_addValue;

	if(newGold < 0){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新角色金币信息异常，[oldGold=%lld][newGold=%lld][a_addValue=%lld][EChangeGoldReason=%s]",oldGold,newGold,a_addValue,a_reason.c_str());
		return false;
	}

    BSLib::uint64 newValue = (BSLib::uint64)newGold;
	m_roleResource.updateGold(newValue);
	BSLib::int64  delta = a_addValue > 0 ? a_addValue : (-a_addValue);
	using namespace GSLib::ItemSystem::GM;
	outputGameLog("t_resource","[f_type=%d][f_resource_id=%u][f_count=%lld][][f_source=%s][ModifyGold]", a_addValue > 0 ? 1 : -1, EITEM_TP_VIR_GOLD, delta, a_reason.c_str());

	return true;
}

void CRoleGM::_setRoleStatus(ERoleStatus a_roleStatus)
{
	m_roleStatus = a_roleStatus;
}

bool CRoleGM::_cbInitRoleVipGiftData(const DB::SRoleVipGiftData& a_giftData)
{
    m_vipGiftRefreshTime = a_giftData.m_vipGiftRefreshTime;

    removeAllVipLevelGift();
    if(_refreshVipGift()){
        return true;
    }

    std::vector<DB::SVipGift>::size_type i_vipGift = 0;
    for (; i_vipGift < a_giftData.m_vipGiftList.size(); ++i_vipGift) {
        DB::SVipGift gift = a_giftData.m_vipGiftList[i_vipGift];
        addVipGift(gift.m_vipLevel,gift.m_giftStatus);
    }
    return true;
}

// 周日为：0
BSLib::int32 CRoleGM::_getWeekday(const BSLib::Utility::CDateTime& a_curTime) const
{
    BSLib::uint32 year = a_curTime.getYear();
    BSLib::uint32 month = a_curTime.getMonth();
    BSLib::uint32 day = a_curTime.getDay();
    BSLib::int32 iWeek = 0;
    BSLib::uint32 y = 0, c = 0, m = 0, d = 0;

    if ( month == 1 || month == 2 ) {
        c = ( year - 1 ) / 100;
        y = ( year - 1 ) % 100;
        m = month + 12;
        d = day;
    }
    else {
        c = year / 100;
        y = year % 100;
        m = month;
        d = day;
    }

    iWeek = y + y / 4 + c / 4 - 2 * c + 26 * ( m + 1 ) / 10 + d - 1;    //蔡勒公式
    iWeek = iWeek >= 0 ? ( iWeek % 7 ) : ( iWeek % 7 + 7 );    //iWeek为负时取模

    return iWeek;
}

BSLib::uint64 CRoleGM::_getVipGiftRefreshTime() const
{
    BSLib::Utility::CDateTime curTime = BSLib::Utility::CDateTime::getCurrentTime();
    BSLib::Utility::CDateTime preTime = BSLib::Utility::CDateTime::CDateTime(curTime.getYear(),curTime.getMonth(),curTime.getDay(),0,0,0);
    BSLib::uint64 newTime = preTime.getSeconds();
    BSLib::int32 week = _getWeekday(curTime);
    newTime += (7-week)*24*3600;
    return newTime; 
}

bool CRoleGM::_refreshVipGiftTime()
{
    BSLib::uint64 newRefreshVipGiftTime = _getVipGiftRefreshTime();
    BSLib::uint64 preRefreshVipGiftTime = _getPreVipGiftRefreshTime();
    if(preRefreshVipGiftTime < newRefreshVipGiftTime){
        m_vipGiftRefreshTime = newRefreshVipGiftTime;
        return true;
    }
    return false;
}

bool CRoleGM::_refreshVipGift()
{
    if(_refreshVipGiftTime()){
        BSLib::uint32 vipLevel = getVipLevel();
        addVipGift(vipLevel,0);
        return true;
    }
    return false;
}

bool CRoleGM::_notifyUpdateRoleResource(ERoleResID a_resID)
{
     CMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute ack;
     ack.m_reason = EUPDATEATTRIBUTE_REASON_NORMAL;
     ack.m_resID = a_resID;
     ack.m_value = getResValue(a_resID);
     BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[NTF][_notifyUpdateRoleResource][m_resID =%d][m_reason=%ld][m_value=%ld]",ack.m_resID,ack.m_reason,ack.m_value);
     return sendMsgToClient(ack);
}

bool CRoleGM::_notifyUpdateRoleUInt64Resource(ERoleResID a_resID)
{
    switch(a_resID)
    {
    case ATTR_GOLD:
        {
            CMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute ack;
            ack.m_reason = EUPDATEATTRIBUTE_REASON_NORMAL;
            ack.m_resID = ATTR_GOLD;
            ack.m_value = getGold();
            BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[NTF][modifyGold][m_reason=%d][m_resID=%ld][m_value=%lld]",ack.m_reason,ack.m_resID,ack.m_value);
            return sendMsgToClient(ack);
        }
        break;
    case ATTR_EXP:
        {
            CMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute ack;
            ack.m_reason = EUPDATEATTRIBUTE_REASON_NORMAL;
            ack.m_resID = ATTR_EXP;
            ack.m_value = getExp();
            BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[NTF][modifyExp][m_reason=%d][m_resID=%ld][m_value=%lld]",ack.m_reason,ack.m_resID,ack.m_value);
            return sendMsgToClient(ack);
        }
        break;
    default:
        {
           ;
        }
        break;
    }

    BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[NTF][_notifyUpdateRoleUInt64Resource][a_resID=%d]",a_resID);
    return false;
}


bool CRoleGM::_notifyBagSizeToClient()
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[NTF][_notifyBagSizeToClient][bagSize=%d]",getBagSize());
    CMsgPlayerSystemGM2GCNtfExpandBagSize ack;
    ack.m_bagSize = getBagSize();
    return sendMsgToClient(ack);
}


bool CRoleGM::_notifyRoleBattleAttributeToClient()
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[NTF][_notifyRoleBattleAttributeToClient]%s",m_totalBattleAttr.toLogString().c_str());
    CMsgPlayerSystemGM2GCNtfRoleBattleAttribute ntf;
    ntf.m_battleAttribute = m_totalBattleAttr;
    ntf.m_combat = getCombat();
	ntf.m_historyMaxCombatPower = getHistoryMaxCombat();
    return sendMsgToClient(ntf);
}

bool CRoleGM::_notifyUpdateRoleDataToCenter()
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[NTF][_notifyUpdateRoleDataToCenter]");
    CMsgPlayerSystemGM2CNNtfUpdateRoleData reqUpdateRoleData2CN;
    DB::SRoleData roleData;
    getRoleDBData(roleData);
    reqUpdateRoleData2CN.m_stream.push((BSLib::int8*)&roleData, sizeof(DB::SRoleData));
    if (!sendMsgToCenterServer(reqUpdateRoleData2CN)){
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "创建角色发送消息到[CN]失败");
        return false;
    }
    return true;
}

}//GM

}//PlayerSystem

}//GSLib

