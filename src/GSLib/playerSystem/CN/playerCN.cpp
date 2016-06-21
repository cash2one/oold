#include <GSLib/tracer.h>
#include <GSLib/playerSystem/msgPlayerSystem.h>
#include <GSLib/playerSystem/CN/playerSystemCN.h>
#include <GSLib/playerSystem/CN/playerCN.h>
#include <GSLib/playerSystem/CN/playerCNMgr.h>
#include <GSLib/playerSystem/CN/roleBaseInfoCNMgr.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace CN
{


CPlayerCN::CPlayerCN(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName)
: LoginSystem::CN::CNetPlayerCN(a_accountKey, a_accountName),m_playerID(0),m_curRoleIndex(INVALID_ROLEINDEX),m_playerStatus(ESTATUS_NULL)
{
}

CPlayerCN::CPlayerCN(EntityID a_entityID, const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName)
:LoginSystem::CN::CNetPlayerCN(a_accountKey,a_accountName),m_playerID(0),m_curRoleIndex(INVALID_ROLEINDEX),m_playerStatus(ESTATUS_NULL)
{

}

CPlayerCN::~CPlayerCN()
{
	;
}

bool CPlayerCN::init()
{
	return true;
}

void CPlayerCN::final()
{
	
}

void CPlayerCN::_cbInitPlayer()
{
	LoginSystem::CN::CNetPlayerCN::_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SUCCESS);
}

void CPlayerCN::_cbFinalPlayer()
{
     BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CPlayerCN::_cbFinalPlayer");
}

void CPlayerCN::_cbPlayerOnline()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CPlayerCN::_cbPlayerOnline");
    _setPlayerStatus(ESTATUS_ONLINE);
}

void CPlayerCN::_cbPlayerOffline()
{   
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CPlayerCN::_cbPlayerOffline");
    CRoleCN* role = getCurRole();
    if (role != NULL) {
        role->setRoleStatus(STATUS_INACTIVE);
        role->onRoleInactive();
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[RoleIndex=%d]下线",role->getRoleIndex());
    }
    _setPlayerStatus(ESTATUS_OFFLINE);
}

void CPlayerCN::_cbInitMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGM2CNReqCreateRole, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGM2CNReqCreateRole>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGM2CNReqCreateRole, &CPlayerCN::_OnMsgPlayerSystemGM2CNReqCreateRole, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGM2CNReqInitPlayerData, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGM2CNReqInitPlayerData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGM2CNReqInitPlayerData, &CPlayerCN::_OnMsgPlayerSystemGM2CNReqInitPlayerData, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGM2CNReqSelectRole, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGM2CNReqSelectRole>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGM2CNReqSelectRole, &CPlayerCN::_OnMsgPlayerSystemGM2CNReqInitSelectRole, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGM2CNReqRoleQuit, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGM2CNReqRoleQuit>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGM2CNReqRoleQuit, &CPlayerCN::_OnMsgPlayerSystemGM2CNReqRoleQuit, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGM2CNReqGetRoleData, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGM2CNReqGetRoleData>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGM2CNReqGetRoleData, &CPlayerCN::_OnMsgPlayerSystemGM2CNReqGetRoleData, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPlayerSystemGM2CNNtfUpdateRoleData, &BSLib::Framework::CreateCMessage<CMsgPlayerSystemGM2CNNtfUpdateRoleData>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPlayerSystemGM2CNNtfUpdateRoleData, &CPlayerCN::_OnMsgPlayerSystemGM2CNNtfUpdateRoleData, this);

	LoginSystem::CN::CNetPlayerCN::_cbInitMsg(a_msgExecMgr);
}

void CPlayerCN::_OnMsgPlayerSystemGM2CNReqCreateRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	//GFLib::SNetMsgLabel* netMsgLable = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgPlayerSystemGM2CNReqCreateRole* req = (CMsgPlayerSystemGM2CNReqCreateRole*)a_msg;
	//RoleIndex roleIndex = INVALID_ROLEINDEX;
    DB::SRoleData roleData;
    req->m_stream.read((char*)&roleData,sizeof(DB::SRoleData));
    std::string roleName = roleData.m_roleName;
	if (roleName.empty()){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_createRole error:roleName.empty()");
		return ;
	}
	if (!_createRole(roleData.m_roleName, roleData.m_roleTPID,roleData.m_roleIndex)) {
       BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_createRole error");
       return;
	}
    CRoleBaseInfoCN* roleBaseInfo = CRoleBaseInfoCNMgr::singleton().createRoleBaseInfoCN(roleData);
    if(roleBaseInfo == NULL){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "createRoleBaseInfoCN error");
        return;
    }
}

void CPlayerCN::_OnMsgPlayerSystemGM2CNReqInitPlayerData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_OnMsgPlayerSystemGM2CNReqInitPlayerData AccountKey=%s", getAccountKey().toLogString().c_str());
	//GFLib::SNetMsgLabel* netMsgLable = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgPlayerSystemGM2CNReqInitPlayerData* reqGM = (CMsgPlayerSystemGM2CNReqInitPlayerData*)a_msg;
	BSLib::uint32 roleCount = reqGM->m_roleCount;
	GFLib::SAccountKey accountKey = getAccountKey();
	BSLib::Utility::CStream stream = reqGM->m_stream;
    _setPlayerStatus(ESTATUS_ONLINE);
	_setVipLevel(reqGM->m_vipLevel);
	for(BSLib::uint32 i=0;i<roleCount;i++){
		
		RoleIndex roleIndex = INVALID_ROLEINDEX;
		std::string roleName = "";
		BSLib::uint32 roleTPID = 0;
		BSLib::uint32 roleLevel = 0;
		BSLib::uint32 roleCombat = 0;

		stream >> roleIndex;
		stream >> roleTPID;
		stream >> roleLevel;
		stream >> roleName;
		stream >> roleCombat;

		GSLib::SRoleKey roleKey;
		roleKey.setRoleKey(accountKey.getAccountID(), accountKey.getZoneID(), roleIndex);
		CRoleCN*  role = getRole(roleIndex);
		if (role == NULL) {
			role = new CRoleCN(roleKey, this,roleTPID,roleName);
			if(role == NULL){
                BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "初始化RoleCN失败%s", roleKey.toLogString().c_str());
				return;
			}
		}
		// 初始化角色
		role->setLevel(roleLevel);
		role->setCombat(roleCombat);
		// 模块初始化
		role->preInit();

		m_roleHashMap.setValue(roleIndex, role);
        role->setRoleStatus(STATUS_LOADING);
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "开始初始化RoleGM%s", roleKey.toLogString().c_str());

        std::string tableKey = roleKey.getDBKey();
        if (!GSLib::PlayerSystem::CN::CPlayerSystemCN::singleton().selectTableData(roleKey, tableKey, "", GSLib::EDBTABLEID_COMMAND_INIT_ROLE)) {
            BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "初始化RoleCN失败%s", roleKey.toLogString().c_str());
            return;
        }
	}

	GSLib::SRoleKey roleKeyEnd(getAccountKey(), GSLib::INVALID_ROLEINDEX);
	std::string tableKeyEnd = getAccountKey().getDBKey();
	if (!GSLib::PlayerSystem::CN::CPlayerSystemCN::singleton().selectTableData(roleKeyEnd, tableKeyEnd, "", GSLib::EDBTABLEID_COMMAND_INIT_ROLE_END)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "初始化所有的Role失败[AccountID=%lld][ZoneID=%d]", getAccountID(), getZoneID());
	}
}

void CPlayerCN::_OnMsgPlayerSystemGM2CNReqInitSelectRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	//GFLib::SNetMsgLabel* netMsgLable = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgPlayerSystemGM2CNReqSelectRole* reqGM = (CMsgPlayerSystemGM2CNReqSelectRole*)a_msg;
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "选角色[req->m_roleIndex=%d]", reqGM->m_roleIndex);
	CMsgPlayerSystemCN2GMAckSelectRole ackCN;
	if(!setCurRoleIndex(reqGM->m_roleIndex)){
		ackCN.m_state = 0;
	}
	else{
        ackCN.m_state = 1;
	}
	sendMsgToGameServer(ackCN);
}

void CPlayerCN::_OnMsgPlayerSystemGM2CNReqRoleQuit(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	//GFLib::SNetMsgLabel* netMsgLable = (GFLib::SNetMsgLabel*)a_msgLabel;
	CMsgPlayerSystemGM2CNReqRoleQuit* reqGM = (CMsgPlayerSystemGM2CNReqRoleQuit*)a_msg;
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "选角色[req->m_roleIndex=%d]", reqGM->m_roleIndex);
	CMsgPlayerSystemCN2GMAckRoleQuit ackCN;
	if(getCurRoleIndex() != (int)reqGM->m_roleIndex){
		ackCN.m_state = 0;
	}
	else{
		CRoleCN * role = getCurRole();
		if(role == NULL){
			ackCN.m_state = 0;
		}
		else{
			BSLib::Framework::CMsgExecMgr* msgExecMgr = _getMsgExecMgr();
			role->freeMsg(msgExecMgr);
			role->setRoleStatus(STATUS_INACTIVE);
			role->onRoleInactive();
			_setCurRoleIndex(INVALID_ROLEINDEX);
			ackCN.m_state = 1;
		}
	}
	sendMsgToGameServer(ackCN);
}

void CPlayerCN::_OnMsgPlayerSystemGM2CNReqGetRoleData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    //GFLib::SNetMsgLabel* netMsgLable = (GFLib::SNetMsgLabel*)a_msgLabel;
    CMsgPlayerSystemGM2CNReqGetRoleData* reqGM = (CMsgPlayerSystemGM2CNReqGetRoleData*)a_msg;
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "选角色 req:%s", reqGM->m_roleKey.toLogString().c_str());

    CMsgPlayerSystemCN2GMAckGetRoleData ackCN;
    CRoleBaseInfoCN* roleBaseInfo = CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleKey(reqGM->m_roleKey.getDBKey());
    if(roleBaseInfo == NULL){
        ackCN.m_state = EGETROLEDATA_RESULT_FAIL;
        sendMsgToGameServer(ackCN);
        return;
    }

    roleBaseInfo->serializeTo(ackCN.m_stream);
    ackCN.m_state = EGETROLEDATA_RESULT_SUCCESS;
    sendMsgToGameServer(ackCN);
}


void CPlayerCN::_OnMsgPlayerSystemGM2CNNtfUpdateRoleData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    //GFLib::SNetMsgLabel* netMsgLable = (GFLib::SNetMsgLabel*)a_msgLabel;
    CMsgPlayerSystemGM2CNNtfUpdateRoleData* req = (CMsgPlayerSystemGM2CNNtfUpdateRoleData*)a_msg;
    DB::SRoleData roleData;
    req->m_stream.read((char*)&roleData,sizeof(DB::SRoleData));
    CRoleBaseInfoCNMgr::singleton().updateRoleBaseInfoCN(roleData);
}

bool  CPlayerCN::_createRole(const std::string& a_roleName,BSLib::int32 a_roleTPID,RoleIndex a_roleIndex)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "创建角色_createRole[name=%s][aTPID=%d][index=%d]", a_roleName.c_str(),a_roleTPID,a_roleIndex);
	if(getCurRoleIndex() == a_roleIndex){
		return true;
	}
	
	SRoleKey roleKey;
	roleKey.setRoleKey(getAccountKey(), a_roleIndex);
	CRoleCN* role = new CRoleCN(roleKey, this,a_roleTPID,a_roleName);
	if (role == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "new 内存失败");
		return false;
	}

	m_roleHashMap.setValue(a_roleIndex, role);
	role->preInit(true);

    std::string tableKey = roleKey.getDBKey();
    if (!GSLib::PlayerSystem::CN::CPlayerSystemCN::singleton().selectTableData(roleKey, tableKey, "", GSLib::EDBTABLEID_COMMAND_INIT_ROLE,EMODULECTYPE_NULL,GSLIB_SESSIONID_CREATE_ROLE_FINISH)) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "更新RoleCN失败%s", roleKey.toLogString().c_str());
        return false;
    }

	role->setRoleStatus(STATUS_LOADING);
	return true;
}

bool CPlayerCN::setCurRoleIndex(RoleIndex a_curRoleIndex)
{
	if(getCurRoleIndex() == a_curRoleIndex){
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "当前角色重新激活[%d]", a_curRoleIndex);
		CRoleCN* roleCur = getCurRole();
		if (roleCur == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "获取当前角色失败");
			return false;
		}
		roleCur->setRoleStatus(STATUS_ACTIVE);
		roleCur->onRoleActive();
        roleCur->initToClient();
		return true;
	}

	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "setCurRoleIndex 角色索引[%d]切换到[%d]",_getCurRoleIndex(), a_curRoleIndex);

	BSLib::Framework::CMsgExecMgr* msgExecMgr = _getMsgExecMgr();
	CRoleCN* roleOld = getCurRole();
	if (roleOld != NULL) {	
		if(roleOld->isActive()){
			roleOld->freeMsg(msgExecMgr);
			roleOld->setRoleStatus(STATUS_INACTIVE);
			roleOld->onRoleInactive();
		}
	}

	_setCurRoleIndex(a_curRoleIndex);
	CRoleCN* roleCur = getCurRole();
	if (roleCur == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "获取当前角色失败");
		return false;
	}
	roleCur->initMsg(msgExecMgr);
	roleCur->setRoleStatus(STATUS_ACTIVE);
	roleCur->onRoleActive();
    roleCur->initToClient();

	return true;
}

bool CPlayerCN::cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "查询数据返回 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);

	if (a_moduleType == EMODULECTYPE_NULL) {
		return _cbSelectKeyTableData(a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID);
	}
	CRoleCN* roleCN = getRole(a_roleKey.getIndex());
	if (roleCN == NULL) {
		return false;
	}

	return roleCN->cbSelectKeyTableData(a_keyTable, a_tableID, a_moduleType, a_sessionID);
}

bool CPlayerCN::cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "查询数据返回 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);

	if (a_moduleType == EMODULECTYPE_NULL) {
		return _cbSelectKeyIndexTableData(a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID);
	}
	CRoleCN* roleCN = getRole(a_roleKey.getIndex());
	if (roleCN == NULL) {
		return false;
	}
	return roleCN->cbSelectKeyIndexTableData(a_keyTable, a_tableID, a_moduleType, a_sessionID);
}


EntityID CPlayerCN::getEntityID() const
{
	return 0;
}
CRoleCN * CPlayerCN::getCurRole()
{
	CRoleCN * role = NULL;
	m_roleHashMap.getValue(_getCurRoleIndex(), role);
	return role;
}

CRoleCN*  CPlayerCN::getRole(RoleIndex a_roleIndex)
{
	CRoleCN * role = NULL;
	m_roleHashMap.getValue(a_roleIndex, role);
	return role;
}

bool CPlayerCN::isOnline()const
{
	if(m_playerStatus == ESTATUS_ONLINE){
		return true;
	}
	return false;
}

bool CPlayerCN::_cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable,  EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
    switch (a_tableID)
    {
    case EDBTABLEID_PLAYER_DATA:
        {
            return true;
        }
        break;
    case EDBTABLEID_COMMAND_INIT_PLAYER_FINSH:
        {
            return true;
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

bool CPlayerCN::_cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable,  EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	return true;
}


bool CPlayerCN::_cbTableInitRoleFinish(const GSLib::SRoleKey& a_roleKey,BSLib::uint32 a_sessionID)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "初始化完成RoleCN%s", a_roleKey.toLogString().c_str());
    // 创建角色处理

    CRoleCN *currentLoadingRole = getRole(a_roleKey.getIndex());
    if(NULL != currentLoadingRole){
        bool firstInit = (a_sessionID == GSLIB_SESSIONID_CREATE_ROLE_FINISH)?true:false;
        currentLoadingRole->postInit(firstInit);
    }

    if(a_sessionID == GSLIB_SESSIONID_CREATE_ROLE_FINISH){
         CMsgPlayerSystemCN2GMAckCreateRole ackCN;
        CRoleCN * role = getRole(a_roleKey.getIndex());
        if(role == NULL){
             ackCN.m_state = 0;
             ackCN.m_roleIndex = INVALID_ROLEINDEX;
             sendMsgToGameServer(ackCN);
            return false;
        }

        ackCN.m_state = 1;
        ackCN.m_roleIndex = a_roleKey.getIndex();
        sendMsgToGameServer(ackCN);
        return true;
    }

    BSLib::Utility::CHashMap<RoleIndex, CRoleCN*>::iterator it = m_roleHashMap.begin();
    for (; it != m_roleHashMap.end(); ++it) {
        CRoleCN* roleCN = it->second;
        if (roleCN == NULL) {
            continue;
        }
        if (roleCN->getRoleKey() == a_roleKey) {
            if (m_curRoleIndex == a_roleKey.getIndex()) {
                roleCN->setRoleStatus(STATUS_ACTIVE);
            } else {
                roleCN->setRoleStatus(STATUS_INACTIVE);
            }
            break;
        }
    }

    return true;
}

bool CPlayerCN::_cbTableInitRoleEnd()
{
	CMsgPlayerSystemCN2GMAckInitPlayerData ackGM;
	ackGM.m_state = 1;
	return sendMsgToGameServer(ackGM);
}

}//CN

}//PlayerSystem

}//GSLib

