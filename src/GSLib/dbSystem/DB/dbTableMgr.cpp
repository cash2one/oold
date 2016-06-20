//////////////////////////////////////////////////////////////////////
//	created:	2014/08/30
//	filename: 	src\GSLib\dbSystem\DB\dbTableMgr.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/tracer.h>
#include <GSLib/dbSystem/GM/dbTableGM.h>
#include "DB/dbTableMgr.h"

namespace GSLib
{

namespace DBSystem
{

namespace DB
{

BSLIB_SINGLETON_DEFINE(CDBTableMgr);

CDBTableMgr::CDBTableMgr()
{
	;
}

CDBTableMgr::~CDBTableMgr()
{
	;
}

bool CDBTableMgr::init()
{
	const std::string& serverName = GFLib::CommonServer::CCommonServer::getCommonServer()->getServerTypeName();
	const std::string localMysqlDB = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "LocalMySQLDB");
	if (localMysqlDB.empty()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "获取本地数据库参数失败");
		return false;
	}
	if (!m_dbConnectionLocal.connect(localMysqlDB, false)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "连接数据库失败");
		return false;
	}

	const std::string globalMysqlDB = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "GlobalMySQLDB");
	if (globalMysqlDB.empty()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "获取全局数据库参数失败");
		return false;
	}
	if (!m_dbConnectionGlobal.connect(globalMysqlDB, false)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "连接数据库失败");
		return false;
	}
	_initDBTableInfor();

	return true;
}

void CDBTableMgr::final()
{
	_closeDBTableInfor();

	m_dbConnectionLocal.close();
	m_dbConnectionGlobal.close();
}

bool CDBTableMgr::selectTableData(GFLib::AccountID a_accountID, GFLib::ZoneID a_zoneID, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream)
{
	SDBTableInfor* dbTableInfor = NULL;
	m_dbTableInforHashMap.getValue(a_tableID, dbTableInfor);
	if (dbTableInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "TableID不存在[TableID=%d]", a_tableID);
		return false;
	}
	BSLib::Utility::CStringA sqlWhere;
	sqlWhere.format("AccountID=%lld AND ZoneID=%d", a_accountID, a_zoneID);

	BSLib::Utility::CStream stream;
	int res = m_dbConnectionLocal.executeSelect(dbTableInfor->m_dbTableName, sqlWhere, "", dbTableInfor->m_dbTableColumn, a_stream);
	if (res < 0) {
		return false;
	}
	return true;
}

bool CDBTableMgr::updateTableData(EDBTableID a_tableID, BSLib::Utility::CStream& a_stream)
{
	SDBTableInfor* dbTableInfor = NULL;
	m_dbTableInforHashMap.getValue(a_tableID, dbTableInfor);
	if (dbTableInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "TableID不存在[TableID=%d]", a_tableID);
		return false;
	}

	int res = m_dbConnectionLocal.executeReplace(dbTableInfor->m_dbTableName, dbTableInfor->m_dbTableColumn, a_stream);
	if (res < 0) {
		return false;
	}
	return true;
}

void CDBTableMgr::_initDBTableInfor()
{
	m_dbTableInforHashMap.setValue(EDBTABLEID_PLAYER_DATA, new SDBTableInfor("PlayerData", GSLib::DBSystem::GM::g_playerDataColumn));
	m_dbTableInforHashMap.setValue(EDBTABLEID_ROLE_DATA, new SDBTableInfor("RoleData", GSLib::DBSystem::GM::g_roleDataColumn));
}

void CDBTableMgr::_closeDBTableInfor()
{
	BSLib::Utility::CHashMap<EDBTableID, SDBTableInfor*>::iterator it = m_dbTableInforHashMap.begin();
	for (; it != m_dbTableInforHashMap.end(); ++it) {
		SDBTableInfor*& tableInfor = it->second;
		if (tableInfor != NULL) {
			BSLIB_SAFE_DELETE(tableInfor);
		}
	}
	m_dbTableInforHashMap.clear();
}

}//DB

}//LoginSystem

}//GSLib
