//////////////////////////////////////////////////////////////////////
//	created:	2015/08/25
//	filename: 	src\GSLib\dbSystem\DB\chargeTableDBMgr.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/tracer.h>
#include "DB/chargeTableDBMgr.h"

namespace GSLib
{

namespace DBSystem
{

namespace DB
{

BSLIB_SINGLETON_DEFINE(CChargeTableDBMgr);

CChargeTableDBMgr::CChargeTableDBMgr()
{
	;
}

CChargeTableDBMgr::~CChargeTableDBMgr()
{
	;
}

bool CChargeTableDBMgr::init()
{
	const std::string& serverName = GFLib::CommonServer::CCommonServer::getCommonServer()->getServerTypeName();
	std::string chargeMysqlDB = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "ChargeMySQLDB");
	if (chargeMysqlDB.empty()) {
		chargeMysqlDB = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "LocalMySQLDB");
	}
	
	if (chargeMysqlDB.empty()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "获取本地数据库参数失败");
		return false;
	}
	if (!m_dbConnectionLocal.connect(chargeMysqlDB, false)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "连接数据库失败");
		return false;
	}
	return true;
}

void CChargeTableDBMgr::final()
{
	;
}

bool CChargeTableDBMgr::getRoleChargeList(const SRoleKey& a_roleKey, std::vector<SChargeList>& a_chargeList)
{
 	BSLib::Utility::CStringA sqlSelect;
	sqlSelect.format("select ChargeID, Type, Money from RoleCharge where AccountID='%lld' and ZoneID='%d' and RoleIndex='%d' and GetTime='0';",
		a_roleKey.getAccountKey().getAccountID(),
		a_roleKey.getAccountKey().getZoneID(),
		a_roleKey.getIndex());

	BSLib::Database::CDbReaderPtr readerPtr = NULL;
 	if (!m_dbConnectionLocal.executeQuery(sqlSelect, readerPtr)) {
		return true;
	}
	if (readerPtr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从数据库获取%s充值数据失败", a_roleKey.toLogString().c_str());
		return false;
	}
	SChargeList chargeList;
	while (readerPtr->nextRow()) {
		BSLib::int64 chargeID =0 ;
		int type = 0;
		int money = 0;
		if (!readerPtr->getValue(0, chargeID)){
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从数据库获取%s充值数据失败", a_roleKey.toLogString().c_str());
			return false;
		}
		if (!readerPtr->getValue(1, type)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从数据库获取%s充值数据失败", a_roleKey.toLogString().c_str());
			return false;
		}
		if (!readerPtr->getValue(2, money)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从数据库获取%s充值数据失败", a_roleKey.toLogString().c_str());
			return false;
		}
		chargeList.m_chargeID = chargeID;
		chargeList.m_type = type;
		chargeList.m_money = money;
		a_chargeList.push_back(chargeList);

		BSLIB_LOG_INFOR(ETT_GSLIB_DBSYSTEM, "[charge_read]%s[chargeid=%lld][type=%d][money=%d]", a_roleKey.toLogString().c_str(), chargeID, type, money);
	}

	BSLib::Utility::CDateTime dataTime = BSLib::Utility::CDateTime::getCurrentTime();
	BSLib::uint64 seconds = dataTime.getSeconds();

	BSLib::Utility::CStringA sqlInsert;
	sqlInsert.format("update RoleCharge set GetTime='%lld' where AccountID='%lld' and ZoneID='%d' and RoleIndex='%d'",
		seconds,
		a_roleKey.getAccountKey().getAccountID(),
		a_roleKey.getAccountKey().getZoneID(),
		a_roleKey.getIndex());
	for (int i=0; i<(int)a_chargeList.size(); ++i) {
		BSLib::Utility::CStringA sql = sqlInsert;
		if (!m_dbConnectionLocal.executeQuery(sql)) {
			return false;
		}
		BSLIB_LOG_INFOR(ETT_GSLIB_DBSYSTEM, "[charge_read_set]%s[chargeid=%lld][type=%d][money=%d]", a_roleKey.toLogString().c_str(), a_chargeList[i].m_chargeID, a_chargeList[i].m_type, a_chargeList[i].m_money);
	}

	return true;
}


}//DB

}//DBSystem

}//GSLib