#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/tracer.h>
#include <GSLib/dbTableDef.hpp>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbSystem/keyTable.h>
#include <GSLib/dbSystem/keyIndexTable.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>

namespace GSLib
{

namespace DBSystem
{

CDBCommonSystem::CDBCommonSystem()
{
	;
}

CDBCommonSystem::~CDBCommonSystem()
{

}

bool CDBCommonSystem::selectTableData(const std::string& a_tableKey, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID, BSLib::uint16 a_funcType, const std::string& a_strWhere)
{
	return selectTableData(GSLib::SRoleKey(0, 0, GSLib::INVALID_ROLEINDEX), a_tableKey, "", a_tableID, a_moduleType, a_sessionID, a_funcType,a_strWhere);
}


bool CDBCommonSystem::selectTableData(const GSLib::SRoleKey& a_roleKey, const std::string& a_tableKey, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID, BSLib::uint16 a_funcType, const std::string& a_strWhere)
{
	return selectTableData(a_roleKey, a_tableKey, "", a_tableID, a_moduleType, a_sessionID, a_funcType,a_strWhere);
}

bool CDBCommonSystem::selectTableData(const GSLib::SRoleKey& a_roleKey, const std::string& a_tableKey, const std::string& a_tableIndex, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID, BSLib::uint16 a_funcType, const std::string& a_strWhere)
{
	GFLib::CommonServer::ICommonServer* server = GFLib::CommonServer::ICommonServer::getCommonServer();
	if (server == NULL) {
		return false;
	}
	if (server->ICommonServer_getServerType() == SRVTYPE_DATASERVER) {
		return GSLib::DBSystem::DB::CDBSystemDB::singleton().selectTableData(a_roleKey, a_tableKey, a_tableIndex, a_tableID, a_moduleType, a_sessionID, a_funcType,a_strWhere);
	}
	if (!m_dataServerID.isValid()) {
		return false;
	}

	GSLib::DBSystem::CMsgLoginSystemXS2DBReqSelectTableData reqSelectTableData;
	reqSelectTableData.m_roleKey = a_roleKey;
	reqSelectTableData.m_key = a_tableKey;
	reqSelectTableData.m_index = a_tableIndex;
	reqSelectTableData.m_tableID = a_tableID;
	reqSelectTableData.m_moduleType = a_moduleType;
	reqSelectTableData.m_sessionID = a_sessionID;
    reqSelectTableData.m_strWhere = a_strWhere;
	if (a_funcType == GFLib::EFUNCTYPE_NULL) {
		reqSelectTableData.m_funcType = ICommonSystem_getFuncType();
	} else {
		reqSelectTableData.m_funcType = a_funcType;
	}
	
	return GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_dataServerID, reqSelectTableData);
}

bool CDBCommonSystem::selectGlobalTableData(const GSLib::SRoleKey& a_srcRoleKey,const GSLib::SRoleKey& a_roleKey, const std::string& a_tableKey, const std::string& a_tableIndex, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID, BSLib::uint16 a_funcType, const std::string& a_strWhere)
{
    GFLib::CommonServer::ICommonServer* server = GFLib::CommonServer::ICommonServer::getCommonServer();
    if (server == NULL) {
        return false;
    }
    if (server->ICommonServer_getServerType() == SRVTYPE_DATASERVER) {
        return GSLib::DBSystem::DB::CDBSystemDB::singleton().selectTableData(a_roleKey, a_tableKey, a_tableIndex, a_tableID, a_moduleType, a_sessionID, a_funcType,a_strWhere);
    }
    if (!m_dataServerID.isValid()) {
        return false;
    }

    GSLib::DBSystem::CMsgLoginSystemXS2DBReqSelectGlobalTableData reqSelectTableData;
    reqSelectTableData.m_roleKey = a_roleKey;
    reqSelectTableData.m_key = a_tableKey;
    reqSelectTableData.m_index = a_tableIndex;
    reqSelectTableData.m_tableID = a_tableID;
    reqSelectTableData.m_moduleType = a_moduleType;
    reqSelectTableData.m_sessionID = a_sessionID;
    reqSelectTableData.m_strWhere = a_strWhere;
    reqSelectTableData.m_srcRoleKey = a_srcRoleKey;
    if (a_funcType == GFLib::EFUNCTYPE_NULL) {
        reqSelectTableData.m_funcType = ICommonSystem_getFuncType();
    } else {
        reqSelectTableData.m_funcType = a_funcType;
    }

    return GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_dataServerID, reqSelectTableData);
}

bool CDBCommonSystem::selectGlobalMultiTableData(const GSLib::SRoleKey& a_srcRoleKey,EModuleType a_srcModuleType,BSLib::uint32 a_sessionID,void* a_ptr,std::vector<SReqTablesData> a_selectDataArray)
{
    GFLib::CommonServer::ICommonServer* server = GFLib::CommonServer::ICommonServer::getCommonServer();
    if (server == NULL) {
        return false;
    }
    if (server->ICommonServer_getServerType() == SRVTYPE_DATASERVER) {
        return GSLib::DBSystem::DB::CDBSystemDB::singleton().selectTableDatas(a_srcRoleKey,a_srcModuleType, a_sessionID, a_ptr,a_selectDataArray);
    }
    if (!m_dataServerID.isValid()) {
        return false;
    }

    GSLib::DBSystem::CMsgLoginSystemXS2DBReqSelectGlobalMultiTableData reqSelectTableData;
    reqSelectTableData.m_sessionID = a_sessionID;
    reqSelectTableData.m_srcModuleType = a_srcModuleType;
    reqSelectTableData.m_srcRoleKey = a_srcRoleKey;
    reqSelectTableData.m_ptr = a_ptr;
    reqSelectTableData.m_tableCount = a_selectDataArray.size();
    std::vector<SReqTablesData>::iterator it = a_selectDataArray.begin();
    
    for(; it != a_selectDataArray.end(); ++it){
        SReqTablesData* req =  &(*it);
        if (req == NULL){
            return false;
        }
        BSLib::Utility::CStream desStream;
        desStream.reset();
        if (req->m_funcType == GFLib::EFUNCTYPE_NULL) {
            req->m_funcType= ICommonSystem_getFuncType();
        }
        req->serializeTo(desStream);
        reqSelectTableData.m_stream << desStream;
    }
    return GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_dataServerID, reqSelectTableData);
}

bool CDBCommonSystem::updateTableData(const std::string& a_key, const std::string& a_index, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave)
{
	return updateTableData(a_key, a_index, a_name, a_tableID, (void*)a_stream.readPtr(), a_stream.readSize(), a_needSave);
}

bool CDBCommonSystem::updateTableData(const std::string& a_tableKey, const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize, bool a_needSave)
{
	GFLib::CommonServer::ICommonServer* server = GFLib::CommonServer::ICommonServer::getCommonServer();
	if (server == NULL) {
		return false;
	}
	if (server->ICommonServer_getServerType() == SRVTYPE_DATASERVER) {
		return GSLib::DBSystem::DB::CDBSystemDB::singleton().updateTableData(a_tableKey, a_tableIndex, a_name, a_tableID, a_data, a_dataSize, a_needSave);
	}

	if (!m_dataServerID.isValid()) {
		return false;
	}

	GSLib::DBSystem::CMsgLoginSystemXS2DBNtfUpdateTableData ntfUpdateTableData;
	ntfUpdateTableData.m_key = a_tableKey;
	ntfUpdateTableData.m_index = a_tableIndex;
	ntfUpdateTableData.m_name = a_name;
	ntfUpdateTableData.m_tableID = a_tableID;
	ntfUpdateTableData.m_neadSave = a_needSave ? 1 : 0;
	ntfUpdateTableData.m_stream.push((BSLib::int8*)a_data, a_dataSize);
	return GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_dataServerID, ntfUpdateTableData);
}

bool CDBCommonSystem::removeTableData(BSLib::Utility::CStream& a_steam, EDBTableID a_tableID, bool a_needSave)
{
	GFLib::CommonServer::ICommonServer* server = GFLib::CommonServer::ICommonServer::getCommonServer();
	if (server == NULL) {
		return false;
	}
	if (server->ICommonServer_getServerType() == SRVTYPE_DATASERVER) {
		return GSLib::DBSystem::DB::CDBSystemDB::singleton().removeTableData(a_steam, a_tableID, a_needSave);
	}

	if (!m_dataServerID.isValid()) {
		return false;
	}
	GSLib::DBSystem::CMsgLoginSystemXS2DBNtfRemoveTableData ntfRemoveTableData;
	ntfRemoveTableData.m_stream.push(a_steam.readPtr(), a_steam.readSize());
	ntfRemoveTableData.m_tableID = a_tableID;
	ntfRemoveTableData.m_neadSave = a_needSave;
	return GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_dataServerID, ntfRemoveTableData);
}

bool CDBCommonSystem::removeTableData(const std::string& a_tableKey, const std::string& a_tableIndex, EDBTableID a_tableID, bool a_needSave)
{
	GFLib::CommonServer::ICommonServer* server = GFLib::CommonServer::ICommonServer::getCommonServer();
	if (server == NULL) {
		return false;
	}
	if (server->ICommonServer_getServerType() == SRVTYPE_DATASERVER) {
		return GSLib::DBSystem::DB::CDBSystemDB::singleton().removeTableData(a_tableKey, a_tableIndex, a_tableID, a_needSave);
	}

	const SDbColumnInfor* dbColumnInfor = getDbColumnInfor(a_tableID);
	if (dbColumnInfor == NULL) {
		return false;
	}
	if (!m_dataServerID.isValid()) {
		return false;
	}
	GSLib::DBSystem::CMsgLoginSystemXS2DBNtfRemoveTableData ntfRemoveTableData;
	ntfRemoveTableData.m_stream << a_tableKey;

	if (dbColumnInfor->m_tableKeyType == ETABLEKEYTYPE_KEY_INDEX) {
		ntfRemoveTableData.m_stream << a_tableIndex;
	}
	ntfRemoveTableData.m_tableID = a_tableID;
	ntfRemoveTableData.m_neadSave = a_needSave;
	return GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_dataServerID, ntfRemoveTableData);
}

bool CDBCommonSystem::saveTableData(const std::string& a_tableKey, const std::string& a_tableIndex, EDBTableID a_tableID)
{
	GFLib::CommonServer::ICommonServer* server = GFLib::CommonServer::ICommonServer::getCommonServer();
	if (server == NULL) {
		return false;
	}
	if (server->ICommonServer_getServerType() == SRVTYPE_DATASERVER) {
		return GSLib::DBSystem::DB::CDBSystemDB::singleton().saveTableData(a_tableKey, a_tableIndex, a_tableID);
	}

	if (!m_dataServerID.isValid()) {
		return false;
	}
	GSLib::DBSystem::CMsgLoginSystemXS2DBNtfSaveTableData ntfSaveTableData;
	ntfSaveTableData.m_key = a_tableKey;
	ntfSaveTableData.m_index = a_tableIndex;
	ntfSaveTableData.m_tableID = a_tableID;
	return GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_dataServerID, ntfSaveTableData);
}


bool CDBCommonSystem::closeTableData(const std::string& a_tableKey, const std::string& a_tableIndex, EDBTableID a_tableID)
{
	GFLib::CommonServer::ICommonServer* server = GFLib::CommonServer::ICommonServer::getCommonServer();
	if (server == NULL) {
		return false;
	}
	if (server->ICommonServer_getServerType() == SRVTYPE_DATASERVER) {
		return GSLib::DBSystem::DB::CDBSystemDB::singleton().closeTableData(a_tableKey, a_tableIndex, a_tableID);
	}

	if (!m_dataServerID.isValid()) {
		return false;
	}
	GSLib::DBSystem::CMsgLoginSystemXS2DBNtfCloseTableData ntfCloseTableData;
	ntfCloseTableData.m_key = a_tableKey;
	ntfCloseTableData.m_index = a_tableIndex;
	ntfCloseTableData.m_tableID = a_tableID;
	return GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_dataServerID, ntfCloseTableData);
}

const SDbColumnInfor* CDBCommonSystem::getDbColumnInfor(EDBTableID a_tableID)
{
	SDbColumnInfor* dbColumnInfor = NULL;
	m_tableColumnHashMap.getValue(a_tableID, dbColumnInfor);
	return dbColumnInfor;
}

bool CDBCommonSystem::addDbColumn(EDBTableID a_tableID, const std::string& a_tableName, const BSLib::Database::SDbColumn* a_dbColumn, EDBConnnectType a_connectType)
{
	if (a_dbColumn == NULL) {
		return false;
	}
	ETableKeyType keyType = _getTableKey(a_dbColumn);
	if (keyType == ETABLEKEYTYPE_NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "table没有定义Key或index[TableID=%d][TableName=%s]", a_tableID, a_tableName.c_str());
		return false;
	}
	SDbColumnInfor* dbColumnInfor = NULL;
	m_tableColumnHashMap.getValue(a_tableID, dbColumnInfor);
	if (dbColumnInfor == NULL) {
		dbColumnInfor = new SDbColumnInfor;
		if (dbColumnInfor == NULL) {
			return false;
		}
		m_tableColumnHashMap.setValue(a_tableID, dbColumnInfor);
	}
	dbColumnInfor->m_tableID = a_tableID;
	dbColumnInfor->m_dbTableName = a_tableName;
	dbColumnInfor->m_dbTableColumn = a_dbColumn;
	dbColumnInfor->m_tableKeyType = keyType;
	dbColumnInfor->m_connectType = a_connectType;
	return true;
}

ETableKeyType CDBCommonSystem::_getTableKey(const BSLib::Database::SDbColumn* a_dbTableColumn)
{
	bool isKey = false;
	bool isIndex = false;
	const BSLib::Database::SDbColumn* dbColumn = a_dbTableColumn;
	while (!dbColumn->m_name.empty()) {
		if (dbColumn->m_flag == BSLib::Database::EDF_KEY) {
			isKey = true;
		} else if (dbColumn->m_flag == BSLib::Database::EDF_INDEX) {
			isIndex = true;
		}
		++dbColumn;
	}
	if (isKey) {
		return isIndex ? ETABLEKEYTYPE_KEY_INDEX : ETABLEKEYTYPE_KEY;
	}
	return ETABLEKEYTYPE_NULL;
}

void CDBCommonSystem::cbSelectTableData(const GSLib::SRoleKey& a_roleKey, EModuleType a_moduleType, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, BSLib::uint32 a_sessionID)
{
	if (a_tableID & EDBTABLEID_COMMAND) {
		CKeyTablePtr keyTablePtr = NULL;
		if (!_cbSelectKeyTableData(a_roleKey, keyTablePtr, a_tableID, a_moduleType, a_sessionID)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select处理失败[TableID=%d]", a_tableID);
			return;
		}
		return ;
	}
	const SDbColumnInfor* columnInfor = getDbColumnInfor(a_tableID);
	if (columnInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,Table信息不存在[TableID=%d]", a_tableID);
		return;
	}
	if (columnInfor->m_tableKeyType == ETABLEKEYTYPE_KEY) {
		CKeyTablePtr keyTablePtr = new CKeyTable(this, columnInfor);
		if (keyTablePtr == NULL) {
			return;
		}
		keyTablePtr->serializeFrom(a_stream);
		if (!_cbSelectKeyTableData(a_roleKey, keyTablePtr, a_tableID, a_moduleType, a_sessionID)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select处理失败[TableID=%d][TableName=%s]", a_tableID, columnInfor->m_dbTableName.c_str());
			return;
		}
	} else if (columnInfor->m_tableKeyType == ETABLEKEYTYPE_KEY_INDEX) {
		CKeyIndexTablePtr keyIndexTablePtr = new CKeyIndexTable(this, columnInfor);
		if (keyIndexTablePtr == NULL) {
			return;
		}
		keyIndexTablePtr->serializeFrom(a_stream);
		if (!_cbSelectKeyIndexTableData(a_roleKey, keyIndexTablePtr, a_tableID, a_moduleType, a_sessionID)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select处理失败[TableID=%d][TableName=%s]", a_tableID, columnInfor->m_dbTableName.c_str());
			return;
		}
	}
}

void CDBCommonSystem::cbSelectGlobalTableData(const GSLib::SRoleKey& a_srcRoleKey,const GSLib::SRoleKey& a_roleKey, EModuleType a_moduleType, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, BSLib::uint32 a_sessionID)
{
    if (a_tableID & EDBTABLEID_COMMAND) {
        CKeyTablePtr keyTablePtr = NULL;
        if (!_cbSelectGlobalKeyTableData(a_srcRoleKey,a_roleKey, keyTablePtr, a_tableID, a_moduleType, a_sessionID)) {
            BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select处理失败[TableID=%d]", a_tableID);
            return;
        }
        return ;
    }
    const SDbColumnInfor* columnInfor = getDbColumnInfor(a_tableID);
    if (columnInfor == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,Table信息不存在[TableID=%d]", a_tableID);
        return;
    }
    if (columnInfor->m_tableKeyType == ETABLEKEYTYPE_KEY) {
        CKeyTablePtr keyTablePtr = new CKeyTable(this, columnInfor);
        if (keyTablePtr == NULL) {
            return;
        }
        keyTablePtr->serializeFrom(a_stream);
        if (!_cbSelectGlobalKeyTableData(a_srcRoleKey,a_roleKey, keyTablePtr, a_tableID, a_moduleType, a_sessionID)) {
            BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select处理失败[TableID=%d][TableName=%s]", a_tableID, columnInfor->m_dbTableName.c_str());
            return;
        }
    } else if (columnInfor->m_tableKeyType == ETABLEKEYTYPE_KEY_INDEX) {
        CKeyIndexTablePtr keyIndexTablePtr = new CKeyIndexTable(this, columnInfor);
        if (keyIndexTablePtr == NULL) {
            return;
        }
        keyIndexTablePtr->serializeFrom(a_stream);
        if (!_cbSelectGlobalKeyIndexTableData(a_srcRoleKey,a_roleKey, keyIndexTablePtr, a_tableID, a_moduleType, a_sessionID)) {
            BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select处理失败[TableID=%d][TableName=%s]", a_tableID, columnInfor->m_dbTableName.c_str());
            return;
        }
    }
}

bool CDBCommonSystem::_getSelectGlobalTableData(EDBTableID a_tableID,BSLib::Utility::CStream& a_stream,ETableKeyType& a_tableKeyType,CKeyTablePtr& a_keyTablePtr,CKeyIndexTablePtr& a_keyIndexTablePtr)
{
    if (a_tableID & EDBTABLEID_COMMAND) {
        a_tableKeyType = ETABLEKEYTYPE_NULL;
        a_keyTablePtr = NULL;
        return true;
    }
    const SDbColumnInfor* columnInfor = getDbColumnInfor(a_tableID);
    if (columnInfor == NULL) {
        a_tableKeyType = ETABLEKEYTYPE_NULL;
        BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,Table信息不存在[TableID=%d]", a_tableID);
        return false;
    }
    a_tableKeyType = columnInfor->m_tableKeyType;
    if (columnInfor->m_tableKeyType == ETABLEKEYTYPE_KEY) {
        CKeyTablePtr keyTablePtr = new CKeyTable(this, columnInfor);
        a_keyTablePtr = keyTablePtr;
        if (keyTablePtr == NULL) {
            return true;
        }
        keyTablePtr->serializeFrom(a_stream);
        return true;
    }
    else if (columnInfor->m_tableKeyType == ETABLEKEYTYPE_KEY_INDEX) {
        CKeyIndexTablePtr keyIndexTablePtr = new CKeyIndexTable(this, columnInfor);
        a_keyIndexTablePtr = keyIndexTablePtr;
        if (keyIndexTablePtr == NULL) {
            return true;
        }
        keyIndexTablePtr->serializeFrom(a_stream);
        return true;
    }
    return true;
}

void CDBCommonSystem::cbSelectGlobalMultiTableData(const GSLib::SRoleKey& a_srcRoleKey,EModuleType a_moduleType, BSLib::uint32 a_sessionID,void* a_ptr,BSLib::uint32 a_state,std::vector<SAckTablesData> a_ackTablesDataArray)
{
    std::vector<SSelectTablesResult> selectTablesResultArray;
    std::vector<CKeyTablePtr> keyTablePtrArray;
    std::vector<CKeyIndexTablePtr> keyIndexTablePtrArray;
    selectTablesResultArray.clear();
    std::vector<SAckTablesData>::iterator it = a_ackTablesDataArray.begin();
    for(;it != a_ackTablesDataArray.end(); ++it){
           SAckTablesData table = *it;
           SSelectTablesResult result;
           CKeyTablePtr keyTablePtr = NULL;
           CKeyIndexTablePtr keyIndexTablePtr = NULL;
           if(!_getSelectGlobalTableData(table.m_tableID,table.m_stream,result.m_tableKeyType,keyTablePtr,keyIndexTablePtr)){
               continue;
           }
           result.m_funcType = table.m_funcType;
           result.m_moduleType = table.m_moduleType;
           result.m_roleKey = table.m_roleKey;
           result.m_tableID = table.m_tableID;
           result.m_status = table.m_status;
           selectTablesResultArray.push_back(result);
           keyTablePtrArray.push_back(keyTablePtr);
           keyIndexTablePtrArray.push_back(keyIndexTablePtr);
    }
    if (!_cbSelectGlobalMultiTableData(a_srcRoleKey,a_moduleType,a_sessionID,a_ptr,a_state,selectTablesResultArray,keyTablePtrArray,keyIndexTablePtrArray)) {
        BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select处理失败[a_sessionID=%d][a_srcRoleKey=%s]", a_sessionID, a_srcRoleKey.toLogString().c_str());
        return;
    }
}

bool CDBCommonSystem::_init()
{
	relateDBTableIDBySDbColumn(*this);

	return GFLib::CommonServer::ICommonSystem::_init();
}

void CDBCommonSystem::_final()
{
	BSLib::Utility::CHashMap<EDBTableID, SDbColumnInfor*>::iterator it = m_tableColumnHashMap.begin();
	for (; it != m_tableColumnHashMap.end(); ++it) {
		SDbColumnInfor* infor = it->second;
		if (infor != NULL) {
			BSLIB_SAFE_DELETE(infor);
		}
	}
	m_tableColumnHashMap.clear();

	return GFLib::CommonServer::ICommonSystem::_final();
}

void CDBCommonSystem::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	if (a_serverID.ICommonServer_getServerType() == SRVTYPE_DATASERVER){
		m_dataServerID = a_serverID;
		return ;
	}
	return GFLib::CommonServer::ICommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CDBCommonSystem::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	if (a_serverID.ICommonServer_getServerType() == SRVTYPE_DATASERVER){
		m_dataServerID = GFLib::INVALID_SERVERID;
		return ;
	}
	return GFLib::CommonServer::ICommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

bool CDBCommonSystem::_cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "丢弃查询数据 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);
	return false;
}

bool CDBCommonSystem::_cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "丢弃查询数据 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);
	return false;
}

bool CDBCommonSystem::_cbSelectGlobalKeyTableData(const GSLib::SRoleKey& a_srcRoleKey,const GSLib::SRoleKey& a_roleKey, CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
    BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "丢弃查询数据 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);
    return false;
}

bool CDBCommonSystem::_cbSelectGlobalKeyIndexTableData(const GSLib::SRoleKey& a_srcRoleKey,const GSLib::SRoleKey& a_roleKey, CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
    BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "丢弃查询数据 %s[TableID=%d]", a_roleKey.toLogString().c_str(), a_tableID);
    return false;
}

bool CDBCommonSystem::_cbSelectGlobalMultiTableData(const GSLib::SRoleKey& a_srcRoleKey,EModuleType a_srcModuleType, BSLib::uint32 a_sessionID,void* a_ptr,BSLib::uint32 a_state,std::vector<SSelectTablesResult>& a_ackSelectTablesResultArray,std::vector<CKeyTablePtr>& a_keyTablePtrArray,std::vector<CKeyIndexTablePtr>& a_keyIndexTablePtrArray)
{
    BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "丢弃多表查询数据 %s[a_sessionID=%d][a_state=%d]", a_srcRoleKey.toLogString().c_str(), a_sessionID,a_state);
    return false;
}

}//DBSystem

}//GSLib


