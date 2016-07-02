#include <GFLib/commonServer/commonServer.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/tracer.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/dbSystem/msgDBSystem.h>
#include <GSLib/playerSystem/GM/msgPlayerSystemGM.h>
#include "DB/tableDataMgr.h"
#include "DB/playerDBMgr.h"
#include "DB/chargeTableDBMgr.h"
#include "DB/playerDB.h"

namespace GSLib
{

namespace DBSystem
{

namespace DB
{

BSLIB_SINGLETON_DEFINE(CDBSystemDB);

CDBSystemDB::CDBSystemDB()
: m_tick1000Handle(BSLib::Utility::INVALID_TIMER)
, m_currentTableID(EDBTABLEID_NULL)
{
	;
}

CDBSystemDB::~CDBSystemDB()
{
	;
}

bool CDBSystemDB::setInitTableByGlobal(GFLib::ServerType a_serverType, BSLib::uint16 a_funcType, EModuleType a_moduleType, EDBTableID a_tableID,const std::string& a_strWhere)
{
	if (a_tableID & EDBTABLEID_COMMAND) {
		return false;
	}
	SInitTableInfo infor;
	infor.m_funcType = a_funcType;
	infor.m_moduleType = a_moduleType;
	infor.m_tableID = a_tableID;
	infor.m_serverType = a_serverType;
    infor.m_strWhere = a_strWhere;

	std::list<SInitTableInfo>::iterator it = m_initTableByGlobal.begin();
	for (; it != m_initTableByGlobal.end(); ++it) {
		if (it->m_tableID <= a_tableID) {
			continue;
		}
		m_initTableByGlobal.insert(it, infor);
		return true;
	}
	m_initTableByGlobal.push_back(infor);
	return true;
}

bool CDBSystemDB::setInitTableByPlayer(GFLib::ServerType a_serverType, BSLib::uint16 a_funcType, EModuleType a_moduleType, EDBTableID a_tableID,const std::string& a_strWhere)
{
	if (a_tableID & EDBTABLEID_COMMAND) {
		return false;
	}
	SInitTableInfo infor;
	infor.m_funcType = a_funcType;
	infor.m_moduleType = a_moduleType;
	infor.m_tableID = a_tableID;
	infor.m_serverType = a_serverType;
    infor.m_strWhere = a_strWhere;

	std::list<SInitTableInfo>::iterator it = m_initTableByPlayer.begin();
	for (; it != m_initTableByPlayer.end(); ++it) {
		if (it->m_tableID <= a_tableID) {
			continue;
		}
		m_initTableByPlayer.insert(it, infor);
		return true;
	}
	m_initTableByPlayer.push_back(infor);
	return true;
}

bool CDBSystemDB::setInitTableByRole(GFLib::ServerType a_serverType, BSLib::uint16 a_funcType, EModuleType a_moduleType, EDBTableID a_tableID,const std::string& a_strWhere)
{
	if (a_tableID & EDBTABLEID_COMMAND) {
		return false;
	}
	SInitTableInfo infor;
	infor.m_funcType = a_funcType;
	infor.m_moduleType = a_moduleType;
	infor.m_tableID = a_tableID;
	infor.m_serverType = a_serverType;
    infor.m_strWhere = a_strWhere;

	std::list<SInitTableInfo>::iterator it = m_initTableByRole.begin();
	for (; it != m_initTableByRole.end(); ++it) {
		if (it->m_tableID <= a_tableID) {
			continue;
		}
		m_initTableByRole.insert(it, infor);
		return true;
	}
	m_initTableByRole.push_back(infor);
	return true;
}

bool CDBSystemDB::loadInitTableByPlayer(const std::string& a_talbeKey, const std::string& a_tableIndex)
{
	std::list<SInitTableInfo>::iterator it = m_initTableByPlayer.begin();
	for (; it != m_initTableByPlayer.end(); ++it) {
		
		BSLIB_LOG_DEBUG(ETT_GSLIB_DBSYSTEM, "加载玩家初始化数据[TableID=%d]", it->m_tableID);

		if (!CTableDataMgr::singleton().loadTableData(a_talbeKey, a_tableIndex, it->m_tableID,it->m_strWhere)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "加载玩家初始化数据失败[TableID=%d]", it->m_tableID);
			return false;
		}
	}
	return true;
}

bool CDBSystemDB::loadInitTableByRole(const std::string& a_sqlWhere)
{
	std::list<SInitTableInfo>::iterator it = m_initTableByRole.begin();
	for (; it != m_initTableByRole.end(); ++it) {
        BSLib::Utility::CStringA sqlWhere = a_sqlWhere;
        if(sqlWhere.empty()){
            if(!it->m_strWhere.empty()){
                sqlWhere += it->m_strWhere;
            }
        }
        else{
            if(!it->m_strWhere.empty()){
                sqlWhere += " AND ";
                sqlWhere += it->m_strWhere;
            }
        }
		BSLIB_LOG_DEBUG(ETT_GSLIB_DBSYSTEM, "加载玩家角色初始化数据[TableID=%d][sqlWhere=%s]", it->m_tableID,sqlWhere.c_str());
        
		if (!CTableDataMgr::singleton().loadTableData(it->m_tableID, sqlWhere)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "加载玩家角色初始化数据失败[TableID=%d][sqlWhere=%s]", it->m_tableID,sqlWhere.c_str());
			return false;
		}
	}
	return true;
}

bool CDBSystemDB::selectTableData(const GSLib::SRoleKey& a_roleKey, const std::string& a_tableKey, const std::string& a_tableIndex, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID, BSLib::uint16 a_funcType, const std::string& a_strWhere)
{
	if (a_tableID & EDBTABLEID_COMMAND) {
		return false;
	}
	BSLib::Utility::CStream stream;
	if (!CTableDataMgr::singleton().selectTableData(a_tableKey, a_tableIndex, a_tableID, stream,a_strWhere)) {
		stream.reset();
	}
	if (a_funcType == GFLib::EFUNCTYPE_NULL || a_funcType == getFuncType()){
		cbSelectTableData(a_roleKey, a_moduleType, a_tableID, stream, a_sessionID);
		return true;
	}
	GFLib::CommonServer::ICommonSystem* commonSystem = GFLib::CommonServer::CCommonSystemMgr::singleton().getSystem(a_funcType);
	if (commonSystem == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,没有找到相应的功能模块[FuncType=%d][TableID=%d]", a_funcType, a_tableID);
		return false;
	}
	if (commonSystem->getFuncType() == a_funcType) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,功能模块不一致[FuncType=%d][TableID=%d]", a_funcType, a_tableID);
		return false;
	}

	GSLib::DBSystem::CDBCommonSystem* dbCommonSystem = dynamic_cast<GSLib::DBSystem::CDBCommonSystem*>(commonSystem);
	if (dbCommonSystem == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,功能模块异常[FuncType=%d][TableID=%d]", a_funcType, a_tableID);
		return false;
	}
	BSLIB_LOG_DEBUG(ETT_GSLIB_DBSYSTEM, "select返回数据[FuncType=%d][TableID=%d]", a_funcType, a_tableID);

	dbCommonSystem->cbSelectTableData(a_roleKey, a_moduleType, a_tableID, stream, a_sessionID);
	return true;
}

bool CDBSystemDB::selectTableDatas(const GSLib::SRoleKey& a_srcRoleKey,EModuleType a_srcModuleType,BSLib::uint32 a_sessionID,void* a_ptr,std::vector<GSLib::DBSystem::SReqTablesData> a_selectDataArray)
{
    BSLib::uint32 state = 0;
    std::vector<GSLib::DBSystem::SReqTablesData>::iterator it = a_selectDataArray.begin();
    BSLib::Utility::CStream stream;
    std::vector<GSLib::DBSystem::SAckTablesData> ackTablesDataArray;
    ackTablesDataArray.clear();
    for(;it != a_selectDataArray.end(); ++it){
        GSLib::DBSystem::SReqTablesData req = *it;
        if (req.m_tableID & EDBTABLEID_COMMAND) {
            return false;
        }
        BSLib::Utility::CStream stream;
        if (!CTableDataMgr::singleton().selectTableData(req.m_tableKey, req.m_tableIndex, req.m_tableID, stream,req.m_strWhere)) {
            state = 1;
            stream.reset();
            break;
        }
        GSLib::DBSystem::SAckTablesData data;
        data.serializeFrom(stream);
        ackTablesDataArray.push_back(data);
    }

    GFLib::CommonServer::ICommonSystem* commonSystem = GFLib::CommonServer::CCommonSystemMgr::singleton().getSystem(GSLib::EFUNCTYPE_PLAYERSYSTEM);
    if (commonSystem == NULL) {
        //BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,没有找到相应的PlayerSystem系统[TableID=%d]", ackSelectData->m_tableID);
        return false;
    }
    if (commonSystem->getFuncType() != GSLib::EFUNCTYPE_PLAYERSYSTEM) {
        BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,功能模块不一致[m_sessionID=%d][m_state=%d]", a_sessionID, state);
        return false;
    }

    GSLib::DBSystem::CDBCommonSystem* dbCommonSystem = dynamic_cast<GSLib::DBSystem::CDBCommonSystem*>(commonSystem);
    if (dbCommonSystem == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,功能模块异常[m_sessionID=%d][m_state=%d]", a_sessionID, state);
        return false;
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_DBSYSTEM, "_onMsgDBSystemDB2XSAckSelectGlobalMultiTableData select返回数据[m_sessionID=%d][m_state=%d]", a_sessionID, state);

    dbCommonSystem->cbSelectGlobalMultiTableData(a_srcRoleKey,a_srcModuleType,a_sessionID,a_ptr,state, ackTablesDataArray);
    return true;
}


bool CDBSystemDB::updateTableData(const std::string& a_key, const std::string& a_index, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave)
{
	if (a_tableID & EDBTABLEID_COMMAND) {
		return false;
	}
	if (!CTableDataMgr::singleton().updateTableData(a_key,a_index, a_name, a_tableID, a_stream)) {
		return false;
	}
	if (a_needSave) {
		return CTableDataMgr::singleton().saveTableData(a_key, a_index, a_tableID);
	}
	return true;
}

bool CDBSystemDB::updateTableData(const std::string& a_key, const std::string& a_index, const std::string& a_name, EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize, bool a_needSave)
{
	if (a_tableID & EDBTABLEID_COMMAND) {
		return false;
	}
	BSLib::Utility::CStream stream;
	stream.push((char*)a_data, a_dataSize);
	if (!CTableDataMgr::singleton().updateTableData(a_key, a_index, a_name, a_tableID, stream)) {
		return false;
	}
	if (a_needSave) {
		return CTableDataMgr::singleton().saveTableData(a_key, a_index, a_tableID);
	}
	return true;
}

bool CDBSystemDB::removeTableData(BSLib::Utility::CStream& a_steam, EDBTableID a_tableID, bool a_needSave)
{
	if (a_tableID & EDBTABLEID_COMMAND) {
		return false;
	}
	const SDbColumnInfor* dbColumnInfor = getDbColumnInfor(a_tableID);
	if (dbColumnInfor == NULL) {
		return false;
	}

	while (!a_steam.readReady()) {
		std::string key;
		std::string index;
		try {
			a_steam >> key;
			if (dbColumnInfor->m_tableKeyType == ETABLEKEYTYPE_KEY_INDEX) {
				a_steam >> index;
			}
		} catch (...) {
			break;
		}
		CTableDataMgr::singleton().removeTableData(key, index, a_tableID);
	}

	if (a_needSave) {
		CTableDataMgr::singleton().saveTableData("", "", a_tableID);
	}
	return true;
}

bool CDBSystemDB::removeTableData(const std::string& a_key, const std::string& a_index, EDBTableID a_tableID, bool a_needSave)
{
	if (a_tableID & EDBTABLEID_COMMAND) {
		return false;
	}
	if (!CTableDataMgr::singleton().removeTableData(a_key,a_index, a_tableID)) {
		return false;
	}
	if (a_needSave) {
		return CTableDataMgr::singleton().saveTableData(a_key, a_index, a_tableID);
	}
	return true;
}

bool CDBSystemDB::saveTableData(const std::string& a_key, const std::string& a_index, EDBTableID a_tableID)
{
	if (a_tableID & EDBTABLEID_COMMAND) {
		return false;
	}
	return CTableDataMgr::singleton().saveTableData(a_key, a_index, a_tableID);
}

void CDBSystemDB::saveAllTableData(const std::string& a_tabkeKey)
{
	return CTableDataMgr::singleton().saveAllTableData(a_tabkeKey, "");
}

bool CDBSystemDB::closeTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, EDBTableID a_tableID)
{
	if (a_tableID & EDBTABLEID_COMMAND) {
		return false;
	}
	CTableDataMgr::singleton().saveTableData(a_tabkeKey, a_tableIndex, a_tableID);

	CTableDataMgr::singleton().closeTableData(a_tabkeKey, a_tableIndex, a_tableID);

	return true;
}

bool CDBSystemDB::_init()
{
	if (!CTableDataMgr::singleton().init()) {
		return false;
	}
	if (!CChargeTableDBMgr::singleton().init()) {
		return false;
	}
	if (!CPlayerDBMgr::singleton().init()) {
		return false;
	}
	return CDBCommonSystem::_init();
}

void CDBSystemDB::_final()
{
	CPlayerDBMgr::singleton().final();
	CChargeTableDBMgr::singleton().final();
	CTableDataMgr::singleton().final();

	CDBCommonSystem::_final();
}

bool CDBSystemDB::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CDBSystemDB::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDDBSystemXS2DBReqSelectTableData, &BSLib::Framework::CreateCMessage<CMsgLoginSystemXS2DBReqSelectTableData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDDBSystemXS2DBReqSelectTableData, &CDBSystemDB::_onMsgDBSystemXS2DBReqSelectTableData, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDDBSystemXS2DBReqSelectGlobalTableData, &BSLib::Framework::CreateCMessage<CMsgLoginSystemXS2DBReqSelectGlobalTableData>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDDBSystemXS2DBReqSelectGlobalTableData, &CDBSystemDB::_onMsgDBSystemXS2DBReqSelectGlobalTableData, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDDBSystemXS2DBReqSelectGlobalMultiTableData, &BSLib::Framework::CreateCMessage<CMsgLoginSystemXS2DBReqSelectGlobalMultiTableData>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDDBSystemXS2DBReqSelectGlobalMultiTableData, &CDBSystemDB::_onMsgDBSystemXS2DBReqSelectGlobalMultiTableData, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDDBSystemXS2DBNtfUpdateTableData, &BSLib::Framework::CreateCMessage<CMsgLoginSystemXS2DBNtfUpdateTableData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDDBSystemXS2DBNtfUpdateTableData, &CDBSystemDB::_onMsgDBSystemXS2DBNtfUpdateTableData, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDDBSystemXS2DBNtfSaveTableData, &BSLib::Framework::CreateCMessage<CMsgLoginSystemXS2DBNtfSaveTableData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDDBSystemXS2DBNtfSaveTableData, &CDBSystemDB::_onMsgDBSystemXS2DBNtfSaveTableData, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDDBSystemXS2DBNtfRemoveTableData, &BSLib::Framework::CreateCMessage<CMsgLoginSystemXS2DBNtfRemoveTableData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDDBSystemXS2DBNtfRemoveTableData, &CDBSystemDB::_onMsgDBSystemXS2DBNtfRemoveTableData, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDDBSystemXS2DBNtfCloseTableData, &BSLib::Framework::CreateCMessage<CMsgLoginSystemXS2DBNtfCloseTableData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDDBSystemXS2DBNtfCloseTableData, &CDBSystemDB::_onMsgDBSystemXS2DBNtfCloseTableData, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDDBSystemCH2DBNtfCharge, &BSLib::Framework::CreateCMessage<CMsgDBSystemCH2DBNtfCharge>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDDBSystemCH2DBNtfCharge, &CDBSystemDB::_onMsgDBSystemCH2DBNtfCharge, this);

	return CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CDBSystemDB::_startSystem()
{
	BSLib::Utility::CTimerServer* timerServer = _getTimerServer();
	if (timerServer == NULL) {
		return false;
	}
	m_tick1000Handle = timerServer->addTimer(&CDBSystemDB::_tick1000, this, 0, NULL, 1000, 30000);
	if (m_tick1000Handle == BSLib::Utility::INVALID_TIMER) {
		return false;
	}

	return CDBCommonSystem::_startSystem();
}

bool CDBSystemDB::_postStartSystem()
{
	if (!_loadInitTableByGlobal()) {
		return false;
	}
// 	if (!_loadInitTableByPlayer()) {
// 		return false;
// 	}
// 	if (!_loadInitTableByRole()) {
// 		return false;
// 	}
	return CDBCommonSystem::_postStartSystem();
}

void CDBSystemDB::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	return CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CDBSystemDB::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	return CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

bool CDBSystemDB::_cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	switch(a_tableID)
	{
	case EDBTABLEID_COMMAND_INIT_SERVER_FINSH:
		BSLIB_LOG_DEBUG(ETT_GSLIB_DBSYSTEM, "DB推送Server数据完成");
		return true;
	default:
		;
	}
	return GSLib::DBSystem::CDBCommonSystem::_cbSelectKeyTableData(a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID);
}

bool CDBSystemDB::_cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	return GSLib::DBSystem::CDBCommonSystem::_cbSelectKeyIndexTableData(a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID);
}

bool CDBSystemDB::_loadInitTableByGlobal()
{
	std::list<SInitTableInfo>::iterator it = m_initTableByGlobal.begin();
	for (; it != m_initTableByGlobal.end(); ++it) {
		
		BSLIB_LOG_INFO(ETT_GSLIB_DBSYSTEM, "加载全局初始化数据[TableID=%d]", it->m_tableID);

		if (!CTableDataMgr::singleton().loadTableData("", "", it->m_tableID,it->m_strWhere)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "加载全局初始化数据失败[TableID=%d]", it->m_tableID);
			return false;
		}
	}
	return true;
}

bool CDBSystemDB::_loadInitTableByPlayer()
{
	std::list<SInitTableInfo>::iterator it = m_initTableByPlayer.begin();
	for (; it != m_initTableByPlayer.end(); ++it) {

		BSLIB_LOG_INFO(ETT_GSLIB_DBSYSTEM, "加载玩家初始化数据[TableID=%d]", it->m_tableID);

		if (!CTableDataMgr::singleton().loadTableData("", "", it->m_tableID,it->m_strWhere)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "加载玩家初始化数据失败[TableID=%d]", it->m_tableID);
			return false;
		}
	}
	return true;
}

bool CDBSystemDB::_loadInitTableByRole()
{
	std::list<SInitTableInfo>::iterator it = m_initTableByRole.begin();
	for (; it != m_initTableByRole.end(); ++it) {

		BSLIB_LOG_INFO(ETT_GSLIB_DBSYSTEM, "加载角色初始化数据[TableID=%d]", it->m_tableID);

		if (!CTableDataMgr::singleton().loadTableData("", "", it->m_tableID, it->m_strWhere)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "加载角色初始化数据失败[TableID=%d]", it->m_tableID);
			return false;
		}
	}
	return true;
}

bool CDBSystemDB::_selectTableCommand(GFLib::SNetMsgLabel* a_msgLabel, CMsgLoginSystemXS2DBReqSelectTableData* a_reqSelectTableData)
{
	CMsgLoginSystemDB2XSAckSelectTableData ackSelectTableData;
	ackSelectTableData.m_roleKey = a_reqSelectTableData->m_roleKey;
	ackSelectTableData.m_moduleType = a_reqSelectTableData->m_moduleType;
	ackSelectTableData.m_funcType = a_reqSelectTableData->m_funcType;
	ackSelectTableData.m_tableID = a_reqSelectTableData->m_tableID;
	ackSelectTableData.m_state = 0;
	ackSelectTableData.m_sessionID = a_reqSelectTableData->m_sessionID;

	switch(a_reqSelectTableData->m_tableID)
	{
	case EDBTABLEID_COMMAND_INIT_PLAYER:
		{
			std::list<SInitTableInfo>::iterator it = m_initTableByPlayer.begin();
			for (; it != m_initTableByPlayer.end(); ++it) {
				SInitTableInfo& infor = *it;
				if (infor.m_serverType == GFLib::SRVTYPE_NULL || infor.m_serverType == a_msgLabel->m_serverIDFrom.ICommonServer_getServerType()) {
					ackSelectTableData.m_tableID = infor.m_tableID;
					if (infor.m_moduleType != EMODULECTYPE_NULL) {
						ackSelectTableData.m_moduleType = infor.m_moduleType;
					}
					if (infor.m_funcType != 0) {
						ackSelectTableData.m_funcType = infor.m_funcType;
					}
					ackSelectTableData.m_stream.reset();
					ackSelectTableData.m_state = 0;
					if (!CTableDataMgr::singleton().selectTableData(a_reqSelectTableData->m_key, a_reqSelectTableData->m_index, infor.m_tableID, ackSelectTableData.m_stream,infor.m_strWhere)) {
						ackSelectTableData.m_state = 1;
					}
					GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_msgLabel->m_serverIDFrom, ackSelectTableData);
				}
			}
			ackSelectTableData.m_moduleType = a_reqSelectTableData->m_moduleType;
			ackSelectTableData.m_funcType = a_reqSelectTableData->m_funcType;
			ackSelectTableData.m_tableID = EDBTABLEID_COMMAND_INIT_PLAYER_FINSH;
			ackSelectTableData.m_state = 0;
			GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_msgLabel->m_serverIDFrom, ackSelectTableData);
			return true;
		}
	case EDBTABLEID_COMMAND_INIT_ROLE:
		{
			std::list<SInitTableInfo>::iterator it = m_initTableByRole.begin();
			for (; it != m_initTableByRole.end(); ++it) {
				SInitTableInfo& infor = *it;
				if (infor.m_serverType == GFLib::SRVTYPE_NULL || infor.m_serverType == a_msgLabel->m_serverIDFrom.ICommonServer_getServerType()) {
					ackSelectTableData.m_tableID = infor.m_tableID;
					if (infor.m_moduleType != EMODULECTYPE_NULL) {
						ackSelectTableData.m_moduleType = infor.m_moduleType;
					}
					if (infor.m_funcType != 0) {
						ackSelectTableData.m_funcType = infor.m_funcType;
					}
					ackSelectTableData.m_stream.reset();
					ackSelectTableData.m_state = 0;
					if (!CTableDataMgr::singleton().selectTableData(a_reqSelectTableData->m_key, a_reqSelectTableData->m_index, infor.m_tableID, ackSelectTableData.m_stream,infor.m_strWhere)) {
						ackSelectTableData.m_state = 1;
					}
					GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_msgLabel->m_serverIDFrom, ackSelectTableData);
				}
			}
			ackSelectTableData.m_moduleType = a_reqSelectTableData->m_moduleType;
			ackSelectTableData.m_funcType = a_reqSelectTableData->m_funcType;
			ackSelectTableData.m_tableID = EDBTABLEID_COMMAND_INIT_ROLE_FINSH;
			ackSelectTableData.m_state = 0;
			GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_msgLabel->m_serverIDFrom, ackSelectTableData);

			GSLib::PlayerSystem::CMsgPlayerSystemDB2GMNtfChargeList msgChargeList;
			msgChargeList.m_roleKey = a_reqSelectTableData->m_roleKey;
			if (CChargeTableDBMgr::singleton().getRoleChargeList(msgChargeList.m_roleKey, msgChargeList.m_chargeList)) {
				GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_msgLabel->m_serverIDFrom, a_reqSelectTableData->m_roleKey.getAccountKey(), msgChargeList);
			}

			return true;
		}
	case EDBTABLEID_COMMAND_INIT_ROLE_END:
		{
			ackSelectTableData.m_moduleType = a_reqSelectTableData->m_moduleType;
			ackSelectTableData.m_funcType = a_reqSelectTableData->m_funcType;
			ackSelectTableData.m_tableID = EDBTABLEID_COMMAND_INIT_ROLE_END;
			ackSelectTableData.m_state = 0;
			GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_msgLabel->m_serverIDFrom, ackSelectTableData);
			return true;
		}
	case EDBTABLEID_COMMAND_INIT_SERVER:
		{
			std::list<SInitTableInfo>::iterator it = m_initTableByGlobal.begin();
			for (; it != m_initTableByGlobal.end(); ++it) {
				SInitTableInfo& infor = *it;
				if (infor.m_serverType == GFLib::SRVTYPE_NULL || infor.m_serverType == a_msgLabel->m_serverIDFrom.ICommonServer_getServerType()) {
					ackSelectTableData.m_tableID = infor.m_tableID;
					if (infor.m_moduleType != EMODULECTYPE_NULL) {
						ackSelectTableData.m_moduleType = infor.m_moduleType;
					}
					if (infor.m_funcType != 0) {
						ackSelectTableData.m_funcType = infor.m_funcType;
					}
					ackSelectTableData.m_stream.reset();
					ackSelectTableData.m_state = 0;
					if (!CTableDataMgr::singleton().selectTableData(a_reqSelectTableData->m_key, a_reqSelectTableData->m_index, infor.m_tableID, ackSelectTableData.m_stream,infor.m_strWhere)) {
						ackSelectTableData.m_state = 1;
					}
					GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_msgLabel->m_serverIDFrom, ackSelectTableData);
				}
			}
			ackSelectTableData.m_moduleType = a_reqSelectTableData->m_moduleType;
			ackSelectTableData.m_funcType = a_reqSelectTableData->m_funcType;
			ackSelectTableData.m_tableID = EDBTABLEID_COMMAND_INIT_SERVER_FINSH;
			ackSelectTableData.m_state = 0;
			GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_msgLabel->m_serverIDFrom, ackSelectTableData);

			return true;
		}
	default:
		;
	}
	return false;
}

bool CDBSystemDB::_tick1000(BSLib::uint64 a_para1, void* a_para2)
{
	if (m_currentTableID >= EDBTABLEID_MAX) {
		m_currentTableID = (EDBTableID )(EDBTABLEID_NULL + 1);
	}
	
	CTableDataMgr::singleton().saveTableData("", "", m_currentTableID);

	m_currentTableID = (EDBTableID)(m_currentTableID + 1);

	return true;
}

void CDBSystemDB::_onMsgDBSystemXS2DBReqSelectTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;

	CMsgLoginSystemXS2DBReqSelectTableData* reqSelectTableData = (CMsgLoginSystemXS2DBReqSelectTableData*)a_msg;
	
	if (reqSelectTableData->m_tableID & EDBTABLEID_COMMAND) {
		_selectTableCommand(msgLabel, reqSelectTableData);
		return ;
	}
	CMsgLoginSystemDB2XSAckSelectTableData ackSelectTableData;
	ackSelectTableData.m_roleKey = reqSelectTableData->m_roleKey;
	ackSelectTableData.m_moduleType = reqSelectTableData->m_moduleType;
	ackSelectTableData.m_funcType = reqSelectTableData->m_funcType;
	ackSelectTableData.m_tableID = reqSelectTableData->m_tableID;
	ackSelectTableData.m_state = 0;
	ackSelectTableData.m_sessionID = reqSelectTableData->m_sessionID;

	if (!CTableDataMgr::singleton().selectTableData(reqSelectTableData->m_key, reqSelectTableData->m_index, reqSelectTableData->m_tableID, ackSelectTableData.m_stream,reqSelectTableData->m_strWhere)) {
		ackSelectTableData.m_state = 1;
	}
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrom, ackSelectTableData);
}

void CDBSystemDB::_onMsgDBSystemXS2DBReqSelectGlobalTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;

    CMsgLoginSystemXS2DBReqSelectGlobalTableData* reqSelectTableData = (CMsgLoginSystemXS2DBReqSelectGlobalTableData*)a_msg;


    CMsgLoginSystemDB2XSAckSelectGlobalTableData ackSelectTableData;
    ackSelectTableData.m_roleKey = reqSelectTableData->m_roleKey;
    ackSelectTableData.m_moduleType = reqSelectTableData->m_moduleType;
    ackSelectTableData.m_funcType = reqSelectTableData->m_funcType;
    ackSelectTableData.m_tableID = reqSelectTableData->m_tableID;
    ackSelectTableData.m_state = 0;
    ackSelectTableData.m_sessionID = reqSelectTableData->m_sessionID;
    ackSelectTableData.m_srcRoleKey = reqSelectTableData->m_srcRoleKey;
    if (reqSelectTableData->m_tableID & EDBTABLEID_COMMAND) {
         ackSelectTableData.m_state = 1;
         GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrom, ackSelectTableData);
         return;
    }

    if (!CTableDataMgr::singleton().selectTableData(reqSelectTableData->m_key, reqSelectTableData->m_index, reqSelectTableData->m_tableID, ackSelectTableData.m_stream,reqSelectTableData->m_strWhere)) {
        ackSelectTableData.m_state = 1;
    }
    GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrom, ackSelectTableData);
}


void CDBSystemDB::_onMsgDBSystemXS2DBReqSelectGlobalMultiTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    GFLib::SNetMsgLabel* msgLabel = (GFLib::SNetMsgLabel*)a_msgLabel;

    CMsgLoginSystemXS2DBReqSelectGlobalMultiTableData* reqSelectTableData = (CMsgLoginSystemXS2DBReqSelectGlobalMultiTableData*)a_msg;

    CMsgLoginSystemDB2XSAckSelectGlobalMultiTableData ackSelectMultiTableData;
    ackSelectMultiTableData.m_state = 0;
    ackSelectMultiTableData.m_sessionID = reqSelectTableData->m_sessionID;
    ackSelectMultiTableData.m_srcRoleKey = reqSelectTableData->m_srcRoleKey;
    ackSelectMultiTableData.m_srcModuleType = reqSelectTableData->m_srcModuleType;
    ackSelectMultiTableData.m_ptr = reqSelectTableData->m_ptr;
    ackSelectMultiTableData.m_tableCount = reqSelectTableData->m_tableCount;

    std::vector<GSLib::DBSystem::SReqTablesData> selectDataArray;
        selectDataArray.clear();
         for(BSLib::uint32 i=0; i<reqSelectTableData->m_tableCount; ++i){
             GSLib::DBSystem::SReqTablesData data;
             data.serializeFrom(reqSelectTableData->m_stream);
             selectDataArray.push_back(data);
         }
         for(BSLib::uint32 i=0; i<selectDataArray.size(); ++i){
             GSLib::DBSystem::SReqTablesData req =  selectDataArray[i];
             BSLib::Utility::CStream desStream;
             GSLib::DBSystem::SAckTablesData data;
             data.m_funcType = req.m_funcType;
             data.m_moduleType = req.m_moduleType;
             data.m_roleKey = req.m_roleKey;
             data.m_tableID = req.m_tableID;
             desStream.reset();
             if (req.m_tableID & EDBTABLEID_COMMAND) {
                 ackSelectMultiTableData.m_state = 1;
                 GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrom, ackSelectMultiTableData);
                 return;
             }
             if (!CTableDataMgr::singleton().selectTableData(req.m_tableKey, req.m_tableIndex, req.m_tableID, desStream,req.m_strWhere)) {
                  data.m_status = EDBOPTION_FAIL;
             }
             else{
                 data.m_status = EDBOPTION_SUCCESS;
             }
             data.m_size = desStream.readSize();
             data.m_stream = desStream;
             data.serializeTo(ackSelectMultiTableData.m_stream);
         }

    GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(msgLabel->m_serverIDFrom, ackSelectMultiTableData);
}

void CDBSystemDB::_onMsgDBSystemXS2DBNtfUpdateTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemXS2DBNtfUpdateTableData* ntfUpdateTableData = (CMsgLoginSystemXS2DBNtfUpdateTableData*)a_msg;


	CTableDataMgr::singleton().updateTableData(ntfUpdateTableData->m_key, ntfUpdateTableData->m_index, ntfUpdateTableData->m_name, ntfUpdateTableData->m_tableID, ntfUpdateTableData->m_stream);

// 	if (ntfUpdateTableData->m_neadSave) {
// 		CTableDataMgr::singleton().saveTableData(ntfUpdateTableData->m_key, ntfUpdateTableData->m_index, ntfUpdateTableData->m_tableID);
// 	}
}

void CDBSystemDB::_onMsgDBSystemXS2DBNtfSaveTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemXS2DBNtfSaveTableData* ntfSaveTableData = (CMsgLoginSystemXS2DBNtfSaveTableData*)a_msg;

	CTableDataMgr::singleton().saveTableData(ntfSaveTableData->m_key, ntfSaveTableData->m_index, ntfSaveTableData->m_tableID);
}

void CDBSystemDB::_onMsgDBSystemXS2DBNtfRemoveTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemXS2DBNtfRemoveTableData* ntfRemoveTableData = (CMsgLoginSystemXS2DBNtfRemoveTableData*)a_msg;

	const SDbColumnInfor* dbColumnInfor = getDbColumnInfor(ntfRemoveTableData->m_tableID);
	if (dbColumnInfor == NULL) {
		return ;
	}

	while (ntfRemoveTableData->m_stream.readReady()) {
		std::string key;
		std::string index;
		try {
			ntfRemoveTableData->m_stream >> key;
			if (dbColumnInfor->m_tableKeyType == ETABLEKEYTYPE_KEY_INDEX) {
				ntfRemoveTableData->m_stream >> index;
			}
		} catch (...) {
			break;
		}
		CTableDataMgr::singleton().removeTableData(key, index, ntfRemoveTableData->m_tableID);
	}
	
// 	if (ntfRemoveTableData->m_neadSave) {
// 		CTableDataMgr::singleton().saveTableData("", "", ntfRemoveTableData->m_tableID);
// 	}
}

void CDBSystemDB::_onMsgDBSystemXS2DBNtfCloseTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemXS2DBNtfCloseTableData* ntfCloseTableData = (CMsgLoginSystemXS2DBNtfCloseTableData*)a_msg;

	CTableDataMgr::singleton().saveTableData(ntfCloseTableData->m_key, ntfCloseTableData->m_index, ntfCloseTableData->m_tableID);
	
	CTableDataMgr::singleton().closeTableData(ntfCloseTableData->m_key, ntfCloseTableData->m_index, ntfCloseTableData->m_tableID);
}

void CDBSystemDB::_onMsgDBSystemCH2DBNtfCharge(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgDBSystemCH2DBNtfCharge* msgNtf = (CMsgDBSystemCH2DBNtfCharge*)a_msg;

	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "充值通知%s", msgNtf->m_roleKey.toLogString().c_str());

	CPlayerDB* playerDB = CPlayerDBMgr::singleton().getPlayerDB(msgNtf->m_roleKey.getAccountKey());
	if (playerDB == NULL) {
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "充值通知%s,不在线", msgNtf->m_roleKey.toLogString().c_str());
		return ;
	}
	GSLib::PlayerSystem::CMsgPlayerSystemDB2GMNtfChargeList msgChargeList;
	msgChargeList.m_roleKey = msgNtf->m_roleKey;
	if (!CChargeTableDBMgr::singleton().getRoleChargeList(msgChargeList.m_roleKey, msgChargeList.m_chargeList)) {
		return ;
	}
	playerDB->sendMsgToGameServer(msgChargeList);

}

}//DB

}//DBSystem

}//GSLib

