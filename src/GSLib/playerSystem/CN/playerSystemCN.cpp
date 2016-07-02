#include <GSLib/playerSystem/CN/playerSystemCN.h>
#include <GSLib/playerSystem/CN/playerCNMgr.h>
#include <GSLib/playerSystem/CN/roleModuleCNMgr.h>
#include <GSLib/playerSystem/CN/roleBagModuleCN.h>
#include <GSLib/playerSystem/CN/roleBaseInfoCNMgr.h>
#include <GSLib/tracer.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace CN
{

BSLIB_SINGLETON_DEFINE(CPlayerSystemCN);

CPlayerSystemCN::CPlayerSystemCN()
{
	m_roleTablePtr = NULL;
}

CPlayerSystemCN::~CPlayerSystemCN()
{
	;
}

bool CPlayerSystemCN::_init()
{
	CRoleModuleCNMgr::singleton().addCreateRoleModuleFun(EMODULECTYPE_BAG, createRoleModuleFun<CRoleBagModuleCN>);
	CPlayerCNMgr::singleton().init();

	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CPlayerSystemCN::_final()
{
	CPlayerCNMgr::singleton().init();
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CPlayerSystemCN::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CPlayerSystemCN::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_CENTERSERVER, EFUNCTYPE_PLAYERSYSTEM), &PlayerSystem::CN::CPlayerSystemCN::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_CENTERSERVER, EFUNCTYPE_EQUIPSYSTEM), &PlayerSystem::CN::CPlayerSystemCN::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_CENTERSERVER, EFUNCTYPE_ITEMSYSTEM), &PlayerSystem::CN::CPlayerSystemCN::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_CENTERSERVER, EFUNCTYPE_SKILLPSYSTEM), &PlayerSystem::CN::CPlayerSystemCN::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_CENTERSERVER, EFUNCTYPE_NPCSYSTEM), &PlayerSystem::CN::CPlayerSystemCN::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_CENTERSERVER, EFUNCTYPE_PETSYSTEM), &PlayerSystem::CN::CPlayerSystemCN::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_CENTERSERVER, EFUNCTYPE_PRIZESYSTEM), &PlayerSystem::CN::CPlayerSystemCN::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_CENTERSERVER, EFUNCTYPE_TASKSYSTEM), &PlayerSystem::CN::CPlayerSystemCN::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_CENTERSERVER, EFUNCTYPE_CHATSYSTEM), &PlayerSystem::CN::CPlayerSystemCN::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_CENTERSERVER, EFUNCTYPE_MAILSYSTEM), &PlayerSystem::CN::CPlayerSystemCN::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_CENTERSERVER, EFUNCTYPE_SCENESYSTEM), &PlayerSystem::CN::CPlayerSystemCN::_onMsgPlayerSystem, this);
	GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_CENTERSERVER, EFUNCTYPE_RANKSYSTEM), &PlayerSystem::CN::CPlayerSystemCN::_onMsgPlayerSystem, this);
    GFLIB_ADDMSGTYPE_OBJEXEC(a_msgExecMgr, GFLIB_MSG_TYPE(SRVTYPE_CENTERSERVER, EFUNCTYPE_FRIENDSYSTEM), &PlayerSystem::CN::CPlayerSystemCN::_onMsgPlayerSystem, this);

	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CPlayerSystemCN::_ICommonSystem_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_startSystem();
}

void CPlayerSystemCN::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CPlayerSystemCN::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

void CPlayerSystemCN::_onMsgPlayerSystem(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* netMsgLable = (GFLib::SNetMsgLabel*)a_msgLabel;
	GFLib::SMessage* msg = (GFLib::SMessage*)a_msg;

	LoginSystem::CN::CNetPlayerCNMgr* netPlayerCNMgr = GSLib::LoginSystem::CN::CNetPlayerCNMgr::getSingleton();
	if (netPlayerCNMgr == NULL) {
		return;
	}
	LoginSystem::CN::CNetPlayerCN* player = netPlayerCNMgr->getNetPlayerCN(netMsgLable->m_acountKey);
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

bool CPlayerSystemCN::_cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
    // 全局数据
    if(a_sessionID == GSLIB_SESSIONID_INIT_GLOBALDATA){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_cbSelectKeyTableData加载全局数据%s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);
    }

	CPlayerCN* player = CPlayerCNMgr::singleton().getPlayerCN(a_roleKey.getAccountKey());
	if (player != NULL) {
		if (player->cbSelectKeyTableData(a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID)) {
			return true;
		}
	}
	BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "丢弃查询数据 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);

	return false;
}

bool CPlayerSystemCN::_cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
    if(a_sessionID == GSLIB_SESSIONID_INIT_GLOBALDATA){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "_cbSelectKeyIndexTableData加载全局数据%s[TableID=%d]", a_roleKey.toLogString().c_str(),a_tableID);
        if(EDBTABLEID_ROLE_DATA == a_tableID){
            a_keyTable->traversal(*this);
            m_roleTablePtr = a_keyTable;
            return true;
        }  
    }

	CPlayerCN* player = CPlayerCNMgr::singleton().getPlayerCN(a_roleKey.getAccountKey());
	if (player != NULL) {
		if (player->cbSelectKeyIndexTableData(a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID)) {
			return true;
		}
	}
	BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "丢弃查询数据 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);

	return false;
}

bool CPlayerSystemCN::exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "查询角色数据[a_key=%d]", a_key.c_str());
    DB::SRoleData roleData;
    if (!a_value->serializeTo(&roleData, sizeof(roleData))) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "查询角色数据[a_key=%d]", a_key.c_str());
        return false;
    }
    CRoleBaseInfoCNMgr::singleton().createRoleBaseInfoCN(roleData);

    return true;
}

}//CN

}//PlayerSystem

}//GSLib

