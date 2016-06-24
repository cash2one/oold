#include <GSLib/tracer.h>

#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/playerSystem/GM/playerGMMgr.h>
#include <GSLib/playerSystem/GM/playerSystemGM.h>
#include <GSLib/sceneSystem/GM/sceneGMMgr.h>
#include <GFLib/commonServer/eventMgr.h>
#include <GFLib/commonServer/uniqueIDMgr.h>
#include <GSLib/uniqueIDType.h>
#include <GSLib/petSystem/GM/petModule.h>
#include <GSLib/prizeSystem/GM/rolePrizeModule.h>
#include <GSLib/itemSystem/GM/itemGMMgr.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace GM
{

CPlayerGM::CPlayerGM(EntityID a_entityID, const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName)
: LoginSystem::GM::CNetPlayerGM(a_accountKey,a_accountName)
, m_playerStatus(ESTATUS_NULL)
, m_entityID(a_entityID)
, m_curRoleIndex(INVALID_ROLEINDEX)
, m_vipScore(0)
, m_newRoleTPID(0)
{
    memset(&m_roleNameData, 0, sizeof(DB::SRoleNameData));
}

CPlayerGM::~CPlayerGM()
{
	_removeAllRole();
}

bool CPlayerGM::setCurRoleIndex(RoleIndex a_curRoleIndex)
{
	if(isInvalidRoleIndex(a_curRoleIndex)){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "角色ID无效[%d]", a_curRoleIndex);
		return false;
	}

	if(getCurRoleIndex() == a_curRoleIndex){
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "当前角色重新激活[%d]", a_curRoleIndex);
		CRoleGM* curRole = getCurRole();
		if (curRole == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "获取当前角色失败");
			return false;
		}
		curRole->setRoleStatus(STATUS_ACTIVE);
		curRole->onRoleActive();
		return true;
	}

	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "setCurRoleIndex 角色索引[%d]切换到[%d]",_getCurRoleIndex(), a_curRoleIndex);
	BSLib::Framework::CMsgExecMgr* msgExecMgr = _getMsgExecMgr();
	CRoleGM* roleOld = getCurRole();
	if (roleOld != NULL) {
		roleOld->updateDataToDB();
		roleOld->freeMsg(msgExecMgr);
		if(roleOld->isActive()){
			roleOld->setRoleStatus(STATUS_INACTIVE);
			roleOld->onRoleInactive();
		}	
	}
	_setCurRoleIndex(a_curRoleIndex);
	CRoleGM* curRoleGM = getCurRole();
	if (curRoleGM == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "获取当前角色失败");
		return false;
	}
	
	if (!curRoleGM->isLoading()) {
		curRoleGM->initMsg(msgExecMgr);
		curRoleGM->setRoleStatus(STATUS_ACTIVE);
		curRoleGM->onRoleActive();
	}
	
	return true;
}

bool CPlayerGM::chargeVipScore(BSLib::uint32 a_vipScore)
{
    BSLib::uint32 vipScore = getVipScore();
    vipScore += a_vipScore;
    _setVipScore(vipScore);
    CMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore ack;
    ack.m_vipScore = getVipScore();
    sendMsgToClient(ack);
    return true;
}

CRoleGM * CPlayerGM::getCurRole()
{
	return getRole(_getCurRoleIndex());
}

CRoleGM*  CPlayerGM::getRole(RoleIndex a_roleIndex)
{
	CRoleGM * role = NULL;
	m_roleHashMap.getValue(a_roleIndex, role);
	return role;
}

CRoleGM*  CPlayerGM::getRoleByName(std::string a_roleName)
{
    BSLib::Utility::CHashMap<RoleIndex, CRoleGM*>::const_iterator it = m_roleHashMap.begin();
    for (; it != m_roleHashMap.end(); ++it) {
        CRoleGM* roleGM = it->second;
        if (roleGM == NULL) {
            continue;
        }
        if (roleGM->getName() == a_roleName) {
            return roleGM;
        }
    }
    return NULL;
}

bool CPlayerGM::isOnline()const
{
	if(m_playerStatus == ESTATUS_ONLINE){
		return true;
	}
	return false;
}

void CPlayerGM::_cbInitMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqPlayerData, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqPlayerData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqPlayerData, &CPlayerGM::_onMsgPlayerSystemGC2GMReqInitPlayerData, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqCreateRole, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqCreateRole>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqCreateRole, &CPlayerGM::_onMsgPlayerSystemGC2GMReqCreateRole, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqSelectRole, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqSelectRole>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqSelectRole, &CPlayerGM::_onMsgPlayerSystemGC2GMReqSelectRole, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqUpdateSkillPoint, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqUpdateSkillPoint>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqUpdateSkillPoint, &CPlayerGM::_onMsgPlayerSystemGC2GMReqUpdateSkillPoint, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqRoleQuit, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqRoleQuit>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqRoleQuit, &CPlayerGM::_onMsgPlayerSystemGC2GMReqRoleQuit, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqDeleteRole, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqDeleteRole>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqDeleteRole, &CPlayerGM::_onMsgPlayerSystemGC2GMReqDeleteRole, this);


    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqGetRoleData, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqRoleGetRoleData>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqGetRoleData, &CPlayerGM::_onMsgPlayerSystemGC2GMReqGetRoleData, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqGetVipLevelGift, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqGetVipLevelGift>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqGetVipLevelGift, &CPlayerGM::_onMsgPlayerSystemGC2GMReqGetVipLevelGift, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqVipLevelGiftStatus, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqVipLevelGiftStatus>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqVipLevelGiftStatus, &CPlayerGM::_onMsgPlayerSystemGC2GMReqVipLevelGiftStatus, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemCN2GMAckSelectRole, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemCN2GMAckSelectRole>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemCN2GMAckSelectRole, &CPlayerGM::_onMsgPlayerSystemCN2GMAckSelectRole, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemCN2GMAckInitPlayerData, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemCN2GMAckInitPlayerData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemCN2GMAckInitPlayerData, &CPlayerGM::_onMsgPlayerSystemCN2GMAckInitPlayerData, this);


	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemCN2GMAckRoleQuit, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemCN2GMAckRoleQuit>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemCN2GMAckRoleQuit, &CPlayerGM::_onMsgPlayerSystemCN2GMAckRoleQuit, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemCN2GMAckCreateRole, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemCN2GMAckCreateRole>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemCN2GMAckCreateRole, &CPlayerGM::_onMsgPlayerSystemCN2GMAckCreateRole, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemCN2GMAckGetRoleData, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemCN2GMAckGetRoleData>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemCN2GMAckGetRoleData, &CPlayerGM::_onMsgPlayerSystemCN2GMAckGetRoleData, this);
	

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqGetVitality, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqGetVitality>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqGetVitality, &CPlayerGM::_onMsgPlayerSystemGC2GMReqGetVitality, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqBuyVitality, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqBuyVitality>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqBuyVitality, &CPlayerGM::_onMsgPlayerSystemGC2GMReqBuyVitality, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqBuyVitalityDiamond, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqBuyVitalityDiamond>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqBuyVitalityDiamond, &CPlayerGM::_onMsgPlayerSystemGC2GMReqBuyVitalityDiamond, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqPurchaseGold, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqPurchaseGold>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqPurchaseGold, &CPlayerGM::_onMsgPlayerSystemGC2GMReqPurchaseGold, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGC2GMReqGetPurchaseGoldInfo, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGC2GMReqGetPurchaseGoldInfo>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGC2GMReqGetPurchaseGoldInfo, &CPlayerGM::_onMsgPlayerSystemGC2GMReqGetPurchaseGoldInfo, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemDB2GMNtfChargeList, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemDB2GMNtfChargeList>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemDB2GMNtfChargeList, &CPlayerGM::_onMsgPlayerSystemDB2CMNtfChargeList, this);

	LoginSystem::GM::CNetPlayerGM::_cbInitMsg(a_msgExecMgr);
}

void CPlayerGM::_cbInitPlayer()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "初始化PlayerGM_cbInitPlayer");
	GSLib::SRoleKey roleKey(getAccountKey(), GSLib::INVALID_ROLEINDEX);
	std::string tableKey = getAccountKey().getDBKey();
	if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().selectTableData(roleKey, tableKey, "", GSLib::EDBTABLEID_COMMAND_INIT_PLAYER)) {
		LoginSystem::GM::CNetPlayerGM::_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SERVER_ERROR);
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "初始化PlayerGM失败[AccountID=%lld][ZoneID=%d]", getAccountID(), getZoneID());
		return ;
	}
}

void CPlayerGM::_cbFinalPlayer()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CPlayerGM::_cbFinalPlayer");
	_removeAllRole();
}

void CPlayerGM::_cbPlayerOnline()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CPlayerGM::_cbPlayerOnline");
    _setPlayerStatus(ESTATUS_ONLINE);
}

void CPlayerGM::_cbPlayerOffline()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CPlayerGM::_cbPlayerOffline");
	CRoleGM* role = getCurRole();
	if (role != NULL) {
		role->updateDataToDB();
		role->setRoleStatus(STATUS_INACTIVE);
		role->onRoleInactive();
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[RoleIndex=%d]下线",role->getRoleIndex());
	}

	_setPlayerStatus(ESTATUS_OFFLINE);
}

EntityID CPlayerGM::getEntityID() const
{
	return GSLib::LoginSystem::GM::CNetPlayerGM::getAccountID();
}

EntityTPID CPlayerGM::getTPID() const
{
	return 0;
}

std::string CPlayerGM::getName() const
{
	return GSLib::LoginSystem::GM::CNetPlayerGM::getAccountName();
}

void CPlayerGM::updateDataToDB()
{
    DB::SPlayerData playerData;
    playerData.m_zoneID =  getZoneID();
    playerData.m_accountID = getAccountID();
    playerData.m_currentRoleIndex = getCurRoleIndex();
    playerData.m_maxRoleIndex = _getMaxRoleIndex();
    playerData.m_vipScore = _getVipScore();

    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "更新玩家信息，[AccountID=%lld][ZoneID=%d][m_vipLevel=%d][m_maxRoleIndex=%d]",
        getAccountID(), getZoneID(),getVipScore(),_getMaxRoleIndex());
    if (!updateTableData("","",EDBTABLEID_PLAYER_DATA, &playerData, sizeof(DB::SPlayerData),true)) {
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "更新玩家信息失败，[AccountID=%lld][ZoneID=%d][m_vipLevel=%d][m_maxRoleIndex=%d]",
            getAccountID(), getZoneID(),getVipScore(),_getMaxRoleIndex());
    }
}

bool CPlayerGM::updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave)
{
	const GFLib::SAccountKey& accountKey = getAccountKey();
	std::string tableKey = accountKey.getDBKey();
	if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().updateTableData(tableKey, a_tableIndex, a_name, a_tableID, a_stream, a_needSave)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新表[TableID=%d]失败%s", a_tableID, accountKey.toLogString().c_str());
		return false;
	}
	return true;
}

bool CPlayerGM::updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize, bool a_needSave)
{
	const GFLib::SAccountKey& accountKey = getAccountKey();
	std::string tableKey = accountKey.getDBKey();
	if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().updateTableData(tableKey, a_tableIndex, a_name, a_tableID, a_data, a_dataSize, a_needSave)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新表[TableID=%d]失败%s", a_tableID, accountKey.toLogString().c_str());
		return false;
	}
	return true;
}

void CPlayerGM::_onMsgPlayerSystemGC2GMReqInitPlayerData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "step1:收到玩家登陆请求CPlayerGM::_onMsgPlayerSystemGC2GMReqInitPlayerData");
    CMsgPlayerSystemGM2CNReqInitPlayerData req;
    req.m_accountKey = getAccountKey();
    req.m_roleCount = getRoleCount();
    req.m_vipLevel = getVipScore();
    req.m_stream.reset();
    BSLib::Utility::CHashMap<RoleIndex, GSLib::PlayerSystem::GM::CRoleGM*> ::iterator its;
    for (its = m_roleHashMap.begin(); its != m_roleHashMap.end(); ++its){
        GSLib::PlayerSystem::GM::CRoleGM *role = its->second;
        if(role != NULL){
            req.m_stream << role->getRoleIndex();
            req.m_stream << role->getTPID();
            req.m_stream << role->getLevel();
            req.m_stream << role->getName();
            req.m_stream << role->getCombat();
        }
    }
    sendMsgToCenterServer(req);
}

void CPlayerGM::_onMsgPlayerSystemGC2GMReqCreateRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgPlayerSystemGC2GMReqCreateRole* req = (CMsgPlayerSystemGC2GMReqCreateRole*)a_msg;
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemGC2GMReqCreateRole 收到[m_roleName=%s][roleType=%d]", req->m_roleName.c_str(),req->m_roleType);
    BSLib::uint32 roleCount = getRoleCount();
    if (roleCount >= ROLE_MAX_COUNT){
        _cbCreateRoleResult(ECREATEROLE_RESULT_COUNT_LIMIT);
        return;
    }
    if(req->m_roleName.length() > 64){
       _cbCreateRoleResult(ECREATEROLE_RESULT_INVALID_ROLENAME);
       return;
    }
    if((req->m_roleType >= PRO_MAX)||(req->m_roleType <= PRO_NULL)){
        _cbCreateRoleResult(ECREATEROLE_RESULT_INVALID_PROTYPE);
        return;
    }
    
    m_roleNameData.m_roleID = 0;
    m_newRoleTPID = req->m_roleType;
    memset(&m_roleNameData.m_roleName, 0, sizeof(char)*(GSLIB_TEXT_MAX_ROLE_NAME + 1));
    strcpy((char*)&m_roleNameData.m_roleName, req->m_roleName.c_str());   

    GSLib::SRoleKey srcRoleKey(getAccountKey(), GSLib::INVALID_ROLEINDEX);
    std::string tableKey;
    tableKey.append((char*)&m_roleNameData.m_roleName, sizeof(char)*(GSLIB_TEXT_MAX_ROLE_NAME + 1));
    if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().selectGlobalTableData(srcRoleKey,GSLib::SRoleKey(0, 0, GSLib::INVALID_ROLEINDEX), tableKey ,"", GSLib::EDBTABLEID_ROLE_NAME_DATA,EMODULECTYPE_NULL,GSLIB_SESSIONID_CHECK_ROLENAME,GFLib::EFUNCTYPE_NULL)) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "创建角色失败[AccountID=%lld][ZoneID=%d]", getAccountID(), getZoneID());
        _cbCreateRoleResult(ECREATEROLE_RESULT_FAIL);
        return;
    }
}

void CPlayerGM::_onMsgPlayerSystemGC2GMReqSelectRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgPlayerSystemGC2GMReqSelectRole* reqGC = (CMsgPlayerSystemGC2GMReqSelectRole*)a_msg;
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemGC2GMReqSelectRole 收到[req->m_roleIndex=%d]", reqGC->m_roleIndex);
	CMsgPlayerSystemGM2GCAckSelectRole ackGC;
	ackGC.m_retCode = ESELECTROLE_RESULT_FAIL;

	if(isInvalidRoleIndex(reqGC->m_roleIndex)){
		sendMsgToClient(ackGC);
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemGC2GMReqSelectRole 返回 选择角色失败,无效请求[req->m_roleIndex=%d]", reqGC->m_roleIndex);
		return;
	}
	if (!setCurRoleIndex(reqGC->m_roleIndex)) {
		sendMsgToClient(ackGC);
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemGC2GMReqSelectRole 返回 选择角色失败,切换角色失败[req->m_roleIndex=%d]", reqGC->m_roleIndex);
		return;
	}

	CRoleGM* role = getCurRole();
	if (role == NULL){
		sendMsgToClient(ackGC);
	   return;
	}

    CMsgPlayerSystemGM2GCNtfInitRoleData ntfInitRole;
    ntfInitRole.m_retCode = EINITROLEDATA_RESULT_SUCCESS;
    ntfInitRole.m_roleIndex = _getCurRoleIndex();
    ntfInitRole.m_sceneTpID = _getSceneTypeID();
    role->updateTotalBattleAttr(false);
    role->getRoleData(ntfInitRole.m_stream);
    sendMsgToClient(ntfInitRole);

	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemGC2GMReqSelectRole 向中心服务器同步当前角色[req->m_roleIndex=%d]", reqGC->m_roleIndex);
	CMsgPlayerSystemGM2CNReqSelectRole reqCN;
	reqCN.m_roleIndex = reqGC->m_roleIndex;
	sendMsgToCenterServer(reqCN);
}



void CPlayerGM::_onMsgPlayerSystemGC2GMReqDeleteRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPlayerSystemGC2GMReqDeleteRole* reqGC = (CMsgPlayerSystemGC2GMReqDeleteRole*)a_msg;
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemGC2GMReqDeleteRole 收到[req->m_roleIndex=%d]", reqGC->m_roleIndex);
    CMsgPlayerSystemGM2GCAckDeleteRole ackGC;
    ackGC.m_retCode = EDELETEROLE_RESULT_FAIL;
    if(!_deleteRole(reqGC->m_roleIndex,ackGC)){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemGC2GMReqDeleteRole 删除的角色失败[req->m_roleIndex=%d]", reqGC->m_roleIndex);
    }
    sendMsgToClient(ackGC);  
}

void CPlayerGM::_onMsgPlayerSystemGC2GMReqGetRoleData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPlayerSystemGC2GMReqRoleGetRoleData* reqGC = (CMsgPlayerSystemGC2GMReqRoleGetRoleData*)a_msg;
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemGC2GMReqGetRoleData 收到[req->rolekey %s", reqGC->m_roleKey.toLogString().c_str());
    CRoleGM * role = CPlayerGMMgr::singleton().getRoleGM(reqGC->m_roleKey);
    if(role != NULL){
        CMsgPlayerSystemGM2GCAckGetRoleData ackGC;
        ackGC.m_retCode = EROLEQUIT_RESULT_SUCCESS;
        role->getRoleBaseInfo(ackGC.m_stream);
        sendMsgToClient(ackGC);
      return;
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemGC2GMReqGetRoleData 从CN拉取 %s详细信息", reqGC->m_roleKey.toLogString().c_str());
    CMsgPlayerSystemGM2CNReqGetRoleData reqCN;
    reqCN.m_roleKey = reqGC->m_roleKey;
    sendMsgToCenterServer(reqCN); 
}

void CPlayerGM::_onMsgPlayerSystemGC2GMReqGetVipLevelGift(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPlayerSystemGC2GMReqGetVipLevelGift* reqGC = (CMsgPlayerSystemGC2GMReqGetVipLevelGift*)a_msg;
    CMsgPlayerSystemGM2GCAckGetVipLevelGift ackGC;
    CRoleGM* role = getCurRole();
    if (role == NULL){
        ackGC.m_retCode = EGETVIPLEVELGIFT_RESULT_FAIL;
        sendMsgToClient(ackGC);
        return;
    }

    BSLib::uint32 vipLevel = 0;
    if(!role->getCurrentVipGiftLevel(vipLevel)){
        ackGC.m_vipLevel = reqGC->m_vipLevel;
        ackGC.m_retCode = EGETVIPLEVELGIFT_RESULT_FAIL;
        sendMsgToClient(ackGC);
        return;
    }
    BSLib::uint32 currentVipLevel = vipLevel;
    if(!role->getVipGift(currentVipLevel)){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "发奖失败 [getCurRoleIndex()=%d]", getCurRoleIndex());
        ackGC.m_vipLevel = reqGC->m_vipLevel;
        ackGC.m_retCode = EGETVIPLEVELGIFT_RESULT_FAIL;
        sendMsgToClient(ackGC);
        return;
    }
    role->updateVipGift(vipLevel,1);
    if(!role->getCurrentVipGiftLevel(vipLevel)){
        ackGC.m_retCode = EGETVIPLEVELGIFT_RESULT_SUCCESS;
        ackGC.m_vipLevel = currentVipLevel;
        ackGC.m_nextVipLevel = -1;
        sendMsgToClient(ackGC);
        return;
    }
    ackGC.m_retCode = EGETVIPLEVELGIFT_RESULT_SUCCESS;
    ackGC.m_vipLevel = currentVipLevel;
    ackGC.m_nextVipLevel = vipLevel;
    sendMsgToClient(ackGC);
}

void CPlayerGM::_onMsgPlayerSystemGC2GMReqVipLevelGiftStatus(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPlayerSystemGC2GMReqVipLevelGiftStatus* reqGC = (CMsgPlayerSystemGC2GMReqVipLevelGiftStatus*)a_msg;
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemGC2GMReqVipLevelGiftStatus收到[req->m_vipLevel = %d", reqGC->m_vipLevel);
    CMsgPlayerSystemGM2GCAckVipLevelGiftStatus ackGC;

    CRoleGM* role = getCurRole();
    if (role == NULL){
        ackGC.m_retCode = EVIPLEVEL_GIFT_STATUS_RESULT_FAIL;
        ackGC.m_getStatus = EGETVIPGIFT_STATUS_NO;
        sendMsgToClient(ackGC);
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemGC2GMReqVipLevelGiftStatus获取当前角色失败[getCurRoleIndex()=%d]", getCurRoleIndex());
        return;
    }
    
    BSLib::uint32 vipLevel = 0;
    if(!role->getCurrentVipGiftLevel(vipLevel)){
        ackGC.m_retCode = EVIPLEVEL_GIFT_STATUS_RESULT_SUCCESS;
        ackGC.m_getStatus = EGETVIPGIFT_STATUS_NO;
       sendMsgToClient(ackGC);
       return;
    }
    ackGC.m_vipLevel = vipLevel;
    ackGC.m_retCode = EVIPLEVEL_GIFT_STATUS_RESULT_SUCCESS;
    ackGC.m_getStatus = EGETVIPGIFT_STATUS_YES;
    sendMsgToClient(ackGC);
}

void CPlayerGM::_onMsgPlayerSystemCN2GMAckSelectRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgPlayerSystemCN2GMAckSelectRole* ackCN = (CMsgPlayerSystemCN2GMAckSelectRole*)a_msg;
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemCN2GMAckSelectRole 收到中心服务器同步结果[ackCN.m_state=%d]", ackCN->m_state);
	CMsgPlayerSystemGM2GCAckSelectRole ackGC;
	if(ackCN->m_state == 0){
        ackGC.m_retCode = ESELECTROLE_RESULT_FAIL;
		sendMsgToClient(ackGC);
		return;
	}

	CRoleGM* role = getCurRole();
	if (role == NULL){
		ackGC.m_retCode = ESELECTROLE_RESULT_FAIL;
		sendMsgToClient(ackGC);
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "选角失败[getCurRoleIndex()=%d]", getCurRoleIndex());
		return;
	}

	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "选角成功[getCurRoleIndex()=%d][initToClientBegin]开始初始化角色数据...", getCurRoleIndex());
    role->initToClient();
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[getCurRoleIndex()=%d][initToClientEnd]初始化角色数据完成", getCurRoleIndex());
    ackGC.m_retCode = ESELECTROLE_RESULT_SUCCESS;
	sendMsgToClient(ackGC);
	BSLIB_LOG_INFO(GSLib::ETT_GSLIB_PLAYERSYSTEM, "[SelectRole][AccountName=%s][AccountID=%lld][ZoneID=%d][RoleIndex=%d]", 
		getAccountName().c_str(), getAccountID(), getZoneID(), m_curRoleIndex);

	{
		BSLib::Utility::CDateTime now = BSLib::Utility::CDateTime::getCurrentTime();
		BSLIB_LOG_INFO(ETT_GSLIB_GAME, "[t_login][f_time=%s][f_acc_id=%lld][f_char_id=%d]", 
			now.toString().c_str(),
			getAccountID(), 
			m_curRoleIndex);
	}
}

void CPlayerGM::_onMsgPlayerSystemCN2GMAckInitPlayerData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgPlayerSystemCN2GMAckInitPlayerData* ackCN = (CMsgPlayerSystemCN2GMAckInitPlayerData*)a_msg;
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemCN2GMAckInitPlayerData 收到中心服务器同步结果[ackCN.m_state=%d]", ackCN->m_state);
	CMsgPlayerSystemGM2GCAckPlayerData ackPlayerData;
	if(ackCN->m_state == 0){
		ackPlayerData.m_retCode = EINITPLAYERDATA_RESULT_FAIL;
		sendMsgToClient(ackPlayerData);
		return;
	}

    _setPlayerStatus(ESTATUS_ONLINE);
	ackPlayerData.m_retCode = EINITPLAYERDATA_RESULT_SUCCESS;
	ackPlayerData.m_roleCount = getRoleCount();
	ackPlayerData.m_accountName = getAccountName();
	ackPlayerData.m_vipLevel = getVipScore();
	_getRoleList(ackPlayerData.m_stream);
	sendMsgToClient(ackPlayerData);
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "初始化角色列表[AccountID=%lld][ZoneID=%d][m_roleCount=%d]", getAccountID(), getZoneID(),getRoleCount());
}

void CPlayerGM::_onMsgPlayerSystemCN2GMAckRoleQuit(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgPlayerSystemCN2GMAckRoleQuit* ackCN = (CMsgPlayerSystemCN2GMAckRoleQuit*)a_msg;
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemCN2GMAckRoleQuit 收到中心服务器同步结果[ackCN.m_state=%d]", ackCN->m_state);
	CMsgPlayerSystemGM2GCAckRoleQuit ackGC;
	if(ackCN->m_state == 0){
		ackGC.m_retCode = EROLEQUIT_RESULT_FAIL;
        sendMsgToClient(ackGC);
		return;
	}	
	ackGC.m_retCode = EROLEQUIT_RESULT_SUCCESS;
	sendMsgToClient(ackGC);
}

void CPlayerGM::_onMsgPlayerSystemCN2GMAckCreateRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPlayerSystemCN2GMAckCreateRole* ackCN = (CMsgPlayerSystemCN2GMAckCreateRole*)a_msg;
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemCN2GMAckCreateRole 收到中心服务器同步结果[ackCN.m_state=%d]", ackCN->m_state);
    if(ackCN->m_state == 0){
        _cbCreateRoleResult(ECREATEROLE_RESULT_FAIL);
        return;
    }

    CRoleGM* role = getRole(ackCN->m_roleIndex);
    if (role == NULL){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_onMsgPlayerSystemCN2GMAckCreateRole 返回 创建选择角色失败,获取角色失败[ackCN->m_roleIndex=%d]", ackCN->m_roleIndex);
        _cbCreateRoleResult(ECREATEROLE_RESULT_FAIL);
        return;
    }

    _cbCreateRoleResult(ECREATEROLE_RESULT_SUCCESS,role);
}

void CPlayerGM::_onMsgPlayerSystemCN2GMAckGetRoleData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPlayerSystemCN2GMAckGetRoleData* ackCN = (CMsgPlayerSystemCN2GMAckGetRoleData*)a_msg;
    CMsgPlayerSystemGM2GCAckGetRoleData ackGC;
    if(ackCN->m_state == EGETROLEDATA_RESULT_FAIL){
        ackGC.m_retCode = EGETROLEDATA_RESULT_FAIL;
        sendMsgToClient(ackGC);
        return;
    }	

    ackGC.m_retCode = EROLEQUIT_RESULT_SUCCESS;
    ackGC.m_stream = ackCN->m_stream;
    sendMsgToClient(ackGC);
}

void CPlayerGM::_onMsgPlayerSystemGC2GMReqUpdateSkillPoint(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgPlayerSystemGM2GCAckUpdateSkillPoint ack;

	CRoleGM *role = getCurRole();
	if(role==NULL){
		ack.m_retCode = EUPDATESKILLPOINT_RESULT_FAIL;
        sendMsgToClient(ack);
        return;
	}

    ack.m_updateTime = role->getSkillPointUpdateTime();
    ack.m_skillPoint = role->getSkillPoint();
    ack.m_retCode = EUPDATESKILLPOINT_RESULT_SUCCESS;
    sendMsgToClient(ack);
}

void CPlayerGM::_onMsgPlayerSystemGC2GMReqRoleQuit(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgPlayerSystemGC2GMReqRoleQuit* req = (CMsgPlayerSystemGC2GMReqRoleQuit*)a_msg;
	CMsgPlayerSystemGM2GCAckRoleQuit ack;
	if(_getCurRoleIndex() != (BSLib::int32)req->m_roleIndex){
		ack.m_retCode = EROLEQUIT_RESULT_FAIL;
		sendMsgToClient(ack);
		return;
	}

	CRoleGM *role = getCurRole();
	if(role == NULL){
		ack.m_retCode = EROLEQUIT_RESULT_FAIL;
		sendMsgToClient(ack);
		return;
	}

	role->setRoleStatus(STATUS_INACTIVE);
	role->onRoleInactive();
	CMsgPlayerSystemGM2CNReqRoleQuit reqGM;
	reqGM.m_roleIndex = req->m_roleIndex;
	sendMsgToCenterServer(reqGM);
}

void CPlayerGM::_onMsgPlayerSystemGC2GMReqGetVitality(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPlayerSystemGM2GCAckGetVitality ack;
    CRoleGM *role = getCurRole();
    if(role==NULL){
        ack.m_retCode = EGETVITALITY_RESULT_FAIL;
        sendMsgToClient(ack);
        return;
    }
    ack.m_updateTime = role->getVitalityUpdateTime();
    ack.m_vitality = role->getVitality();
    ack.m_retCode = EGETVITALITY_RESULT_SUCCESS;
    sendMsgToClient(ack);
}

void CPlayerGM::_onMsgPlayerSystemGC2GMReqBuyVitality(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPlayerSystemGM2GCAckBuyVitality ack;

    CRoleGM *role = getCurRole();
    if(role==NULL){
        ack.m_retCode = EBUYVITALITY_RESULT_FAIL;
        sendMsgToClient(ack);
        return;
    }

    PrizeSystem::GM::CRolePrizeModule *prizeModue = (PrizeSystem::GM::CRolePrizeModule *)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
    if (prizeModue == NULL) {
        ack.m_retCode = EBUYVITALITY_RESULT_FAIL;
        sendMsgToClient(ack);
        return;

    }
    const BSLib::uint32 prizeID = 2; // 体力配置奖励ID
    const BSLib::uint32 curBuyTimes = prizeModue->prizeNum(prizeID);
    using namespace ItemSystem::GM;
    const BSLib::uint32 vipLevel = role->getVipLevel();
    const BSLib::uint32 totalBuyTimes = CItemGMMgr::singleton().getBuyVitalityMaxTimes(vipLevel);
    if(curBuyTimes >= totalBuyTimes){
        ack.m_retCode = EBUYVITALITY_RESULT_BUYTIMES_LIMIT;
        sendMsgToClient(ack);
        return;
    }
    const BSLib::uint32 newBuyTimes = curBuyTimes + 1;
    const BSLib::uint32 needDiamond = CItemGMMgr::singleton().getBuyVitalityNeedDiamond(newBuyTimes);
    const BSLib::uint32 curDiamond = role->getTotalDiamond();
    if(needDiamond > curDiamond){
       ack.m_retCode = EBUYVITALITY_RESULT_DIAMOND_LIMIT;       
       sendMsgToClient(ack);
       return;
    }
    std::string sender = toMailString("系统信息");
    std::string title = toMailString("购买体力");
    std::string content = toMailString("体力已满，购买体力以邮件发送");
    prizeModue->prizeRequest(prizeID,sender,title,content,"BUY_VITALITY");
    BSLib::int32 addValue = 0 - (BSLib::int32)needDiamond;
    role->modifyRoleResource(ATTR_DIAMOND,addValue,"BUY_VITALITY",true);
    
    ack.m_vitality = role->getVitality();
    ack.m_retCode = EBUYVITALITY_RESULT_SUCCESS;
    sendMsgToClient(ack);
}

void CPlayerGM::_onMsgPlayerSystemGC2GMReqBuyVitalityDiamond(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPlayerSystemGM2GCAckBuyVitalityDiamond ack;

    CRoleGM *role = getCurRole();
    if(role==NULL){
        ack.m_retCode = EGETNEEDDIAMOND_RESULT_FAIL;
        sendMsgToClient(ack);
        return;
    }

    PrizeSystem::GM::CRolePrizeModule *prizeModue = (PrizeSystem::GM::CRolePrizeModule *)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
    if (prizeModue == NULL) {
        ack.m_retCode = EGETNEEDDIAMOND_RESULT_FAIL;
        sendMsgToClient(ack);
        return;
    }
    const BSLib::uint32 prizeID = 2; // 体力配置奖励ID
    const BSLib::uint32 curBuyTimes = prizeModue->prizeNum(prizeID);
   
    using namespace ItemSystem::GM;
    const BSLib::uint32 vipLevel = role->getVipLevel();
    const BSLib::uint32 totalBuyTimes = CItemGMMgr::singleton().getBuyVitalityMaxTimes(vipLevel);
    ack.m_curBuyCount = curBuyTimes;
    ack.m_maxBuyCount = totalBuyTimes;
    const BSLib::uint32 newBuyTimes = curBuyTimes + 1;
    ack.m_diamond = CItemGMMgr::singleton().getBuyVitalityNeedDiamond(newBuyTimes);
    ack.m_retCode = EGETNEEDDIAMOND_RESULT_SUCCESS;
    sendMsgToClient(ack);
}

void CPlayerGM::_onMsgPlayerSystemGC2GMReqPurchaseGold(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgPlayerSystemGM2GCAckPurchaseGold msgAck;

	CRoleGM *role = getCurRole();
	if(role==NULL){
		msgAck.m_result = EPURCHASE_GOLD_RESULT_FAIL;
		sendMsgToClient(msgAck);
		return;
	}

	PrizeSystem::GM::CRolePrizeModule *prizeModue = (PrizeSystem::GM::CRolePrizeModule *)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
	if (prizeModue == NULL) {
		msgAck.m_result = EPURCHASE_GOLD_RESULT_FAIL;
		sendMsgToClient(msgAck);
		return;

	}
	const BSLib::uint32 prizeID = 3; 
	const BSLib::uint32 curPurchaseTimes = prizeModue->prizeNum(prizeID);
	const BSLib::uint32 totalPurchaseTimes = role->getMaxPurchaseGoldTimes();
	if(curPurchaseTimes >= totalPurchaseTimes){
		msgAck.m_result = EPURCHASE_GOLD_RESULT_LIMIT_TIMES;
		sendMsgToClient(msgAck);
		return;
	}
	const BSLib::uint32 newPurchaseTimes = curPurchaseTimes + 1;
	const BSLib::uint32 needDiamond = role->getPurchaseGoldNeedDiamond(newPurchaseTimes);
	const BSLib::uint32 curDiamond = role->getTotalDiamond();
	if(needDiamond > curDiamond){
		msgAck.m_result = EPURCHASE_GOLD_RESULT_NOT_ENOUGH_DIAMOND;       
		sendMsgToClient(msgAck);
		return;
	}
	std::string sender = toMailString("系统信息");
	std::string title = toMailString("购买钻石");
	std::string content = toMailString("金币已满，购买体力以邮件发送");

	const BSLib::uint32 goldTPID = 101;
	std::vector<ItemSystem::GM::CPrizeItem>items;
	ItemSystem::GM::CPrizeItem item;
	item.m_itemTPID = goldTPID;
	item.m_itemCount = role->getPurchasedGoldCount(newPurchaseTimes);
	items.push_back(item);

	prizeModue->prizeRequest(prizeID, items, sender,title,content,"PURCHASE_GOLD");
	role->delDiamond(needDiamond, "PURCHASE_GOLD", true);

	msgAck.m_result = EPURCHASE_GOLD_RESULT_SUCCESS;
	msgAck.m_remainTimes = role->getMaxPurchaseGoldTimes() > prizeModue->prizeNum(prizeID) ? role->getMaxPurchaseGoldTimes() - prizeModue->prizeNum(prizeID) : 0;
	msgAck.m_maxTimes = role->getMaxPurchaseGoldTimes();
	sendMsgToClient(msgAck);
}

void CPlayerGM::_onMsgPlayerSystemGC2GMReqGetPurchaseGoldInfo(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo msgAck;
	msgAck.m_result = EGET_PURCHASE_GOLD_INFO_RESULT_SUCCESS;

	CRoleGM *role = getCurRole();
	if(role == NULL){
		msgAck.m_result = EGET_PURCHASE_GOLD_INFO_RESULT_FAIL;
		sendMsgToClient(msgAck);
		return;
	}

	PrizeSystem::GM::CRolePrizeModule *prizeModue = (PrizeSystem::GM::CRolePrizeModule *)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
	if (prizeModue == NULL) {
		msgAck.m_result = EGET_PURCHASE_GOLD_INFO_RESULT_FAIL;
		sendMsgToClient(msgAck);
		return;

	}

	BSLib::uint32 prizeID = 3;
	msgAck.m_remainTimes = role->getMaxPurchaseGoldTimes() > prizeModue->prizeNum(prizeID) ? role->getMaxPurchaseGoldTimes() - prizeModue->prizeNum(prizeID) : 0;
	msgAck.m_maxTimes = role->getMaxPurchaseGoldTimes();
	sendMsgToClient(msgAck);
}

void CPlayerGM::_onMsgPlayerSystemDB2CMNtfChargeList(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgPlayerSystemDB2GMNtfChargeList* msgChargeList = (CMsgPlayerSystemDB2GMNtfChargeList*)a_msg;

	CRoleGM * role = getRole(msgChargeList->m_roleKey.getIndex());
	if(role == NULL){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "角色不存在%s", msgChargeList->m_roleKey.toLogString().c_str());
		return ;
	}
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "收到充值列表%s", msgChargeList->m_roleKey.toLogString().c_str());
	
	PrizeSystem::GM::CRolePrizeModule * prize = role->getPrizeModule();
	for (int i=0; i<(int)msgChargeList->m_chargeList.size(); ++i) {
		BSLIB_LOG_INFO(ETT_GSLIB_DBSYSTEM, "[charge_read_ok]%s[chargeid=%lld][type=%d][money=%d]",  msgChargeList->m_roleKey.toLogString().c_str(), msgChargeList->m_chargeList[i].m_chargeID, msgChargeList->m_chargeList[i].m_type, msgChargeList->m_chargeList[i].m_money);
		prize->chargeUpdate(msgChargeList->m_chargeList[i].m_chargeID, msgChargeList->m_chargeList[i].m_type, msgChargeList->m_chargeList[i].m_money);
		role->chargeVipScore(msgChargeList->m_chargeList[i].m_money); // vip 积分
		BSLib::uint32 vipScore = role->getVipScore();
		BSLIB_LOG_INFO(ETT_GSLIB_DBSYSTEM, "[total vip score=%d]",  vipScore);
	}
}

bool CPlayerGM::_deleteRole(RoleIndex a_roleIndex,CMsgPlayerSystemGM2GCAckDeleteRole& a_ack)
{
    if(!_deleteRole(a_roleIndex)){
        a_ack.m_retCode = EDELETEROLE_RESULT_FAIL;
        return false;
    }
    a_ack.m_retCode = EDELETEROLE_RESULT_SUCCESS;
    a_ack.m_roleIndex = a_roleIndex;
    
    return true;
}

bool CPlayerGM::_deleteRole(RoleIndex a_roleIndex)
{
    CRoleGM * role = getRole(a_roleIndex);
    if(role == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "_deleteRole删除的角色不存在[req->m_roleIndex=%d]", a_roleIndex);
        return false;
    }

    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "删除角色onRoleDelete[AccountID=%lld][ZoneID=%d][Index=%d]",role->getAccountID(),role->getZoneID(),role->getRoleIndex());
    BSLib::Framework::CMsgExecMgr* msgExecMgr = _getMsgExecMgr();
    role->freeMsg(msgExecMgr);
    role->onRoleDelete();
    
    m_roleHashMap.remove(a_roleIndex);
    BSLIB_SAFE_DELETE(role);
    return true;
}

bool CPlayerGM::cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "查询数据返回 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);
	if (a_moduleType == EMODULECTYPE_NULL) {
		return _cbSelectKeyTableData(a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID);
	}
	CRoleGM* roleGM = getRole(a_roleKey.getIndex());
	if (roleGM == NULL) {
		return false;
	}
	return roleGM->cbSelectKeyTableData(a_keyTable, a_tableID, a_moduleType, a_sessionID);
}

bool CPlayerGM::cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "查询数据返回 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);
	if (a_moduleType == EMODULECTYPE_NULL) {
		return _cbSelectKeyIndexTableData(a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID);
	}
	CRoleGM* roleGM = getRole(a_roleKey.getIndex());
	if (roleGM == NULL) {
		return false;
	}
	return roleGM->cbSelectKeyIndexTableData(a_keyTable, a_tableID, a_moduleType, a_sessionID);
}

bool CPlayerGM::cbSelectGlobalKeyTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "查询数据返回 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);
    if(a_tableID == EDBTABLEID_ROLE_NAME_DATA){
        return _cbSelectGlobalRoleNameKeyTableData(a_keyTable,a_sessionID);
    }

    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "cbSelectGlobalKeyTableData 查询数据返回 %s[TableID=%d] 被丢弃", a_roleKey.toLogString().c_str(), a_tableID);
    return true;
}

bool CPlayerGM::cbSelectGlobalKeyIndexTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "查询数据返回 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);
    if (a_moduleType == EMODULECTYPE_NULL) {
        return _cbSelectKeyIndexTableData(a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID);
    }
    CRoleGM* roleGM = getRole(a_roleKey.getIndex());
    if (roleGM == NULL) {
        return false;
    }
    return roleGM->cbSelectKeyIndexTableData(a_keyTable, a_tableID, a_moduleType, a_sessionID);
}

bool CPlayerGM::cbSelectGlobalMultiTableData(const GSLib::SRoleKey& a_srcRoleKey, EModuleType a_srcModuleType, BSLib::uint32 a_sessionID,void* a_ptr,BSLib::uint32 a_state,std::vector<GSLib::DBSystem::SSelectTablesResult>& a_ackSelectTablesResultArray,std::vector<GSLib::DBSystem::CKeyTablePtr>& a_keyTablePtrArray,std::vector<GSLib::DBSystem::CKeyIndexTablePtr>& a_keyIndexTablePtrArray)
{
    CRoleGM* roleGM = getRole(a_srcRoleKey.getIndex());
    if (roleGM == NULL) {
        return false;
    }
    return roleGM->cbSelectGlobalMultiTableData(a_srcModuleType,a_sessionID,a_ptr, a_state, a_ackSelectTablesResultArray, a_keyTablePtrArray,a_keyIndexTablePtrArray);
}

bool CPlayerGM::_cbKeyTableInitPlayerData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, BSLib::uint32 a_sessionID)
{
	DB::SPlayerData playerDataInit;
	BSLib::Database::CDBTableRow* tableRow = a_keyTable->getRow(a_roleKey.getAccountKey().getDBKey());
	if (tableRow == NULL) {
		playerDataInit.m_accountID = getAccountID();
		playerDataInit.m_zoneID = getZoneID();
		playerDataInit.m_currentRoleIndex = GSLib::INVALID_ROLEINDEX;
        playerDataInit.m_maxRoleIndex = GSLib::INVALID_ROLEINDEX;
        playerDataInit.m_vipScore = _getVipScore();
		if( !a_keyTable->update(a_roleKey.getAccountKey().getDBKey(), &playerDataInit, sizeof(playerDataInit))) {
			LoginSystem::GM::CNetPlayerGM::_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SERVER_ERROR);
			BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "初始化PlayerGM失败%s", getAccountKey().toLogString().c_str());
			return false;
		}
		if (!a_keyTable->saveDataToDBServer(true)) {
			LoginSystem::GM::CNetPlayerGM::_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SERVER_ERROR);
			BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "初始化PlayerGM失败%s", getAccountKey().toLogString().c_str());
			return false;
		}
	}
    else {
		if (!tableRow->serializeTo(&playerDataInit, sizeof(playerDataInit))) {
			LoginSystem::GM::CNetPlayerGM::_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SERVER_ERROR);
			BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "初始化PlayerGM失败%s", getAccountKey().toLogString().c_str());
			return false;
		}
	}
	_setVipScore(playerDataInit.m_vipScore);
    _setMaxRoleIndex(playerDataInit.m_maxRoleIndex);

	return true;
}

bool CPlayerGM::_cbKeyIndexTableInitRoleData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, BSLib::uint32 a_sessionID)
{
	const BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>* tables = a_keyTable->getRows(a_roleKey.getAccountKey().getDBKey());
	if (tables == NULL) {
		return true;
	}
	BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::const_iterator it = tables->begin();
	for (; it != tables->end(); ++it) {
		BSLib::Database::CDBTableRow* row = it->second;
		if (row == NULL) {
			continue;
		}
		DB::SRoleData roleData;
		if (!row->serializeTo(&roleData, sizeof(roleData))) {
			continue;
		}
		GSLib::SRoleKey roleKey;
		roleKey.setRoleKey(roleData.m_accountID, roleData.m_zoneID, roleData.m_roleIndex);
		CRoleGM*  newRole = new CRoleGM(roleKey, this,roleData.m_roleID);
		if (newRole == NULL) {
			LoginSystem::GM::CNetPlayerGM::_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SERVER_ERROR);
			BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "初始化RoleGM失败%s", roleKey.toLogString().c_str());
			return false;
		}
        // todo:临时GM屏蔽删除角色，需要进一步优化
        if(roleData.m_invalidFlag == 1){
            continue;
        }

		newRole->initRoleDataFromDB(roleData);
		newRole->preInit();
		newRole->setRoleStatus(STATUS_LOADING);
		_addRole(newRole);

		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "请求查询角色模块数据%s", roleKey.toLogString().c_str());
		std::string tableKey = roleKey.getDBKey();
        if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().selectTableData(roleKey, tableKey, "", GSLib::EDBTABLEID_COMMAND_INIT_ROLE)) {
			LoginSystem::GM::CNetPlayerGM::_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SERVER_ERROR);
			BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "初始化RoleGM失败%s", roleKey.toLogString().c_str());
			return false;
		}
	}

	GSLib::SRoleKey roleKeyEnd(getAccountKey(), GSLib::INVALID_ROLEINDEX);
	std::string tableKeyEnd = getAccountKey().getDBKey();
	if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().selectTableData(roleKeyEnd, tableKeyEnd, "", GSLib::EDBTABLEID_COMMAND_INIT_ROLE_END)) {
		LoginSystem::GM::CNetPlayerGM::_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SERVER_ERROR);
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "初始化所有的Role失败[AccountID=%lld][ZoneID=%d]", getAccountID(), getZoneID());
		return false;
	}
	return true;
}

bool CPlayerGM::_cbSelectGlobalRoleNameKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, BSLib::uint32 a_sessionID)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_cbSelectGlobalRoleNameKeyTableData查询数据返回[a_sessionID=%d]", a_sessionID);
    switch(a_sessionID)
    {
    case GSLIB_SESSIONID_CHECK_ROLENAME:
        {
            _createRole(a_keyTable);
            break;
        }
    case GSLIB_SESSIONID_GET_ROLEID:
        {
            break;
        }
    default:
        {
            break;
        }
    }

    return true;
}


bool CPlayerGM::_cbTableInitPlayerFinish(const GSLib::SRoleKey& a_roleKey)
{
	if (m_roleHashMap.empty()) {
		LoginSystem::GM::CNetPlayerGM::_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SUCCESS);
	}
	return true;
}

bool CPlayerGM::_cbTableInitRoleFinish(const GSLib::SRoleKey& a_roleKey,BSLib::uint32 a_sessionID)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "初始化完成RoleGM%s", a_roleKey.toLogString().c_str());

	CRoleGM *currentLoadingRole = getRole(a_roleKey.getIndex());
	if(NULL != currentLoadingRole){
        bool firstInit = (a_sessionID == GSLIB_SESSIONID_CREATE_ROLE_FINISH)?true:false;
        currentLoadingRole->postInit(firstInit);
	}

	if(a_sessionID == GSLIB_SESSIONID_CREATE_ROLE_FINISH){
		CRoleGM * role = getRole(a_roleKey.getIndex());
		if(role == NULL){
            _cbCreateRoleResult(ECREATEROLE_RESULT_FAIL);
			return false;
		}
		role->updateDataToDB(true);
        _sendMsgCreateRoleToCenterServer(*role);

		return true;
	}

	BSLib::Utility::CHashMap<RoleIndex, CRoleGM*>::iterator it = m_roleHashMap.begin();
	for (; it != m_roleHashMap.end(); ++it) {
		CRoleGM* roleGM = it->second;
		if (roleGM == NULL) {
			continue;
		}
		if (roleGM->getRoleKey() == a_roleKey) {
			if (m_curRoleIndex == a_roleKey.getIndex()) {
				roleGM->setRoleStatus(STATUS_ACTIVE);
			} else {
				roleGM->setRoleStatus(STATUS_INACTIVE);
			}
			break;
		}
	}

    BSLib::Utility::CHashMap<RoleIndex, CRoleGM*>::iterator its = m_roleHashMap.begin();
	for (; its != m_roleHashMap.end(); ++its) {
		CRoleGM* roleGM = its->second;
		if (roleGM == NULL) {
			continue;
		}
		if (roleGM->isLoading()) {
			return true;
		}
	}
	//LoginSystem::GM::CNetPlayerGM::_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SUCCESS);
	return true;
}

bool CPlayerGM::_cbTableInitRoleEnd()
{
	LoginSystem::GM::CNetPlayerGM::_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SUCCESS);
	return true;
}

bool CPlayerGM::_cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable,  EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	switch (a_tableID)
	{
	case EDBTABLEID_PLAYER_DATA:
		{
			return _cbKeyTableInitPlayerData(a_roleKey, a_keyTable, a_sessionID);
		}
		break;
	case EDBTABLEID_COMMAND_INIT_PLAYER_FINSH:
		{
			return _cbTableInitPlayerFinish(a_roleKey);
		}
		break;
	case EDBTABLEID_COMMAND_INIT_ROLE_FINSH:
		{
			return _cbTableInitRoleFinish(a_roleKey,a_sessionID);
		}
		break;
	case EDBTABLEID_COMMAND_INIT_ROLE_END:
		{
			return _cbTableInitRoleEnd();
		}
		break;
	default:
		{
			;
		}
		break;
	}
	return true;
}

bool CPlayerGM::_cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable,  EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	switch (a_tableID)
	{
	case EDBTABLEID_ROLE_DATA:
		{
			return _cbKeyIndexTableInitRoleData(a_roleKey, a_keyTable, a_sessionID);
		}
        break;	
	default:
		{
			;
		}
		break;
	}
	return true;
}

void CPlayerGM::_updateRoleNameDataToDB()
{
    BSLib::Utility::CStream stream;
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "updateRoleNameDataToDB");
    if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().updateTableData("","","",EDBTABLEID_ROLE_NAME_DATA, &m_roleNameData, sizeof(DB::SRoleNameData), false)) {
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "updateRoleNameDataToDB ERROR");
    }
}

bool CPlayerGM::_createRole(GSLib::DBSystem::CKeyTablePtr& a_keyTable)
{
    std::string tableKey;
    tableKey.append((char*)&m_roleNameData.m_roleName, sizeof(char)*(GSLIB_TEXT_MAX_ROLE_NAME + 1));
    BSLib::Database::CDBTableRow* tableRow = a_keyTable->getRow(tableKey);
    if (tableRow != NULL) {
        _cbCreateRoleResult(ECREATEROLE_RESULT_INVALID_ROLENAME);
        return false;
    }
    
    _updateRoleNameDataToDB();

    if (tableKey.empty()){
        _cbCreateRoleResult(ECREATEROLE_RESULT_FAIL);
        return false;
    }

    BSLib::uint64 roleID = GFLib::CommonServer::CUniqueIDMgr::singleton().getInt64ZoneUniqueID(GSLib::EUNIQUEIDTYPE_ROLEID);
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "生成RoleID[RoleID=%lld]", roleID);
    RoleIndex roleIndex;
    if (!_createRole(m_roleNameData.m_roleName, m_newRoleTPID,roleID, roleIndex)) {
        _cbCreateRoleResult(ECREATEROLE_RESULT_FAIL);
        return false;
    }

    return true;
}

bool  CPlayerGM::_createRole(const std::string& a_roleName,BSLib::int32 a_roleTPID,RoleID a_roleID, RoleIndex& a_newRoleIndex)
{
    if(!_getNewRoleIndex(a_newRoleIndex)){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "分配角色ID失败！");
        return false;
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "创建角色分配[a_newRoleIndex=%d]",a_newRoleIndex);
	if(a_newRoleIndex == INVALID_ROLEINDEX){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "无效角色索引");
		return false;
	}
	SRoleKey roleKey;
	roleKey.setRoleKey(getAccountKey(), a_newRoleIndex);
	CRoleGM* role = new CRoleGM(roleKey, this, a_roleID,a_roleTPID, a_roleName);
	if (role == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "new 内存失败");
		return false;
	}

	_addRole(role);
	role->preInit(true);
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "创建角色,请求查询角色模块数据%s", roleKey.toLogString().c_str());
	std::string tableKey = roleKey.getDBKey();
	if (!GSLib::PlayerSystem::GM::CPlayerSystemGM::singleton().selectTableData(roleKey, tableKey, "", GSLib::EDBTABLEID_COMMAND_INIT_ROLE,EMODULECTYPE_NULL,GSLIB_SESSIONID_CREATE_ROLE_FINISH)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "_createRole失败%s", roleKey.toLogString().c_str());
		return false;
	}

    _setMaxRoleIndex(a_newRoleIndex);
    updateDataToDB();

	return true;
}

void CPlayerGM::_cbCreateRoleResult(ECreateRoleResult a_result,CRoleGM* a_role)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_cbCreateRoleResult[a_result=%d]",a_result);
    CMsgPlayerSystemGM2GCAckCreateRole ackCreateRole;
    ackCreateRole.m_retCode = a_result;
    switch(a_result)
    {
    case ECREATEROLE_RESULT_SUCCESS:
        {
            if(NULL == a_role){
                ackCreateRole.m_retCode = ECREATEROLE_RESULT_FAIL;
                sendMsgToClient(ackCreateRole);
                return;
            }
            ackCreateRole.m_roleIndex = a_role->getRoleIndex();
            a_role->updateTotalBattleAttr(false);
            a_role->getRoleData(ackCreateRole.m_stream);
            break;
        }
    case ECREATEROLE_RESULT_FAIL:
        {
            break;
        }
    case ECREATEROLE_RESULT_INVALID_PROTYPE:
        {
            break;
        }
    case ECREATEROLE_RESULT_INVALID_ROLENAME:
        {
            break;
        }
    case ECREATEROLE_RESULT_COUNT_LIMIT:
        {
            break;
        }
    default:
        {
            break;
        } 
    }
    sendMsgToClient(ackCreateRole);
}

bool CPlayerGM::_sendMsgCreateRoleToCenterServer(const CRoleGM& a_role)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CPlayerGM::_sendMsgCreateRoleToCenterServer[roleTPID=%d]",a_role.getTPID());
    CMsgPlayerSystemGM2CNReqCreateRole reqCreateRole2CN;
    reqCreateRole2CN.m_accountKey.setKey(getAccountID(),getZoneID());
    DB::SRoleData roleData;
    a_role.getRoleDBData(roleData);
    reqCreateRole2CN.m_stream.push((BSLib::int8*)&roleData, sizeof(DB::SRoleData));
    if (!sendMsgToCenterServer(reqCreateRole2CN)){
        _cbCreateRoleResult(ECREATEROLE_RESULT_FAIL);
        BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "创建角色发送消息到[CN]失败");
        return false;
    }
    return true;
}

void CPlayerGM::_removeRole(RoleIndex a_RoleIndex)
{
	m_roleHashMap.remove(a_RoleIndex);
}

void CPlayerGM::_removeAllRole()
{
	BSLib::Utility::CHashMap<RoleIndex, CRoleGM*>::iterator it = m_roleHashMap.begin();
	for (; it != m_roleHashMap.end(); ++it) {
		CRoleGM* pRole = it->second;
		if (pRole == NULL) {
			continue;
		}
		pRole->final();
		BSLIB_SAFE_DELETE(pRole);
	}
	m_roleHashMap.clear();
}

bool CPlayerGM::_getNewRoleIndex(RoleIndex& a_newRoleIndex) const
{ 
    if(m_maxRoleIndex >= MAX_ROLE_INDEX){
        return false;
    }
    a_newRoleIndex = m_maxRoleIndex + 1;
    return true;
}

CRoleBagModuleGM * CPlayerGM::getItemPackage()
{
	CRoleGM * role = getCurRole();
	if(role == NULL){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "getItemPackage[_getCurRole()=%d]获取当前角色失败!",getCurRole());
		return NULL;
	}

	return role->getRoleBag();
}

void CPlayerGM::_getRoleList(BSLib::Utility::CStream& a_stream) const
{
	BSLib::Utility::CHashMap<RoleIndex, GSLib::PlayerSystem::GM::CRoleGM*> ::const_iterator it = m_roleHashMap.begin();
	for (; it != m_roleHashMap.end(); ++it){
		GSLib::PlayerSystem::GM::CRoleGM *role = it->second;
		if(role != NULL){
			a_stream << role->getRoleIndex();
			a_stream << role->getTPID();
			a_stream << role->getLevel();
			a_stream << role->getName();
		}
	}
}

bool CPlayerGM::_addRole(CRoleGM* a_role)
{
    RoleIndex roleIndex = a_role->getRoleIndex();
    const BSLib::int32 maxRoleIndex = ROLE_MAX_INDEX;
	if ((roleIndex < 0)||(roleIndex > maxRoleIndex)){
		return false;
	}

	_setRole(roleIndex, a_role);
	return true;
}

bool CPlayerGM::_setRole(RoleIndex a_roleIndex,CRoleGM* a_role)
{
    m_roleHashMap.setValue(a_roleIndex, a_role);
    return true;
}

}//GM

}//PlayerSystem

}//GSLib

