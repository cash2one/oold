#include <BSLib/framework/sysConfig.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/tracer.h>
#include <GSLib/dbSystem/LG/dbSystemLG.h>

namespace GSLib
{

namespace DBSystem
{

namespace LG
{

BSLIB_SINGLETON_DEFINE(CDBSystemLG);

CDBSystemLG::CDBSystemLG()
{
	;
}

CDBSystemLG::~CDBSystemLG()
{
	;
}

bool CDBSystemLG::updateActivationCodeData(SActivationCodeData& a_dbData)
{     
    std::string sqlWhere = "Code = ";
    sqlWhere += "\'";
    sqlWhere += a_dbData.m_code;
    sqlWhere += "\'";

    BSLib::Utility::CStream stream;
    stream.reset();
    stream.write((const char*)&a_dbData,sizeof(a_dbData));
    return  m_dbConnection.executeUpdate("ActivationCode", sqlWhere, g_ActivationCodeDataColumn, stream);
}

int CDBSystemLG::selectActivationCodeData(std::string a_activationCode, SActivationCodeData& a_dbData)
{
    //BSLib::Utility::CStringA key = a_key;
    //accountName.toLower();

    std::string dbActivationCode;
    if (!m_dbConnection.escapeString(a_activationCode, dbActivationCode)) {
        return -1;
    }

    std::string sqlWhere = "Code = ";
    sqlWhere += "\'";
    sqlWhere += dbActivationCode;
    sqlWhere += "\'";

    BSLib::Utility::CStream stream;
    int res = m_dbConnection.executeSelect("ActivationCode", sqlWhere, "", g_ActivationCodeDataColumn, stream);
    if (res <= 0) {
        return res;
    }
    if (stream.readSize() < sizeof(a_dbData)) {
        return -1;
    }
    stream.read((char*)&a_dbData, sizeof(a_dbData));
    return 1;
}

int CDBSystemLG::selectAccountData(const std::string a_accountName, SAccountData& a_accountData)
{
	BSLib::Utility::CStringA accountName = a_accountName;
	//accountName.toLower();

	std::string dbAccountName;
	if (!m_dbConnection.escapeString(accountName, dbAccountName)) {
		return -1;
	}

	std::string sqlWhere = "AccountName = \'";
	sqlWhere += dbAccountName;
	sqlWhere += "\'";

	BSLib::Utility::CStream stream;
	int res = m_dbConnection.executeSelect("AccountData", sqlWhere, "", g_accountDataColumn, stream);
	if (res <= 0) {
		return res;
	}
	if (stream.readSize() < sizeof(a_accountData)) {
		return -1;
	}
	stream.read((char*)&a_accountData, sizeof(a_accountData));
	return 1;
}

int CDBSystemLG::selectFastLoginAccountData(const std::string a_uniqueID, const std::string a_uniqueKey,const BSLib::uint32 a_bindFlag,SAccountData& a_accountData)
{
	BSLib::Utility::CStringA uniqueID = a_uniqueID;
	//uniqueID.toLower();

	std::string dbUniqueID;
	if (!m_dbConnection.escapeString(uniqueID, dbUniqueID)) {
		return -1;
	}

	BSLib::Utility::CStringA uniqueKey = a_uniqueKey;
	//uniqueKey.toLower();

	std::string dbUniqueKey;
	if (!m_dbConnection.escapeString(uniqueKey, dbUniqueKey)) {
		return -1;
	}

	BSLib::Utility::CStringA bindFlag = a_bindFlag;
    std::string dbBindFlag;
	if (!m_dbConnection.escapeString(bindFlag, dbBindFlag)) {
		return -1;
	}

	std::string sqlWhere = "UniqueID = \'";
	sqlWhere += dbUniqueID;
	sqlWhere += "\'";
	sqlWhere += " and UniqueKey = \'";
	sqlWhere += dbUniqueKey;
	sqlWhere += "\'";
	sqlWhere += " and BindFlag = ";
	sqlWhere += dbBindFlag;
	BSLib::Utility::CStream stream;
	int res = m_dbConnection.executeSelect("AccountData", sqlWhere, "", g_accountDataColumn, stream);
	if (res <= 0) {
		return res;
	}
	if (stream.readSize() < sizeof(a_accountData)) {
		return -1;
	}
	stream.read((char*)&a_accountData, sizeof(a_accountData));
	return 1;
}

bool CDBSystemLG::insertAccountData(BSLib::Utility::CStream& a_stream, BSLib::uint64* a_autoIncrement)
{
	return m_dbConnection.executeInsert("AccountData", g_accountDataInsertColumn, a_stream,a_autoIncrement);
}

bool CDBSystemLG::_init()
{
	const std::string& serverName = GFLib::CommonServer::CCommonServer::getCommonServer()->getServerTypeName();
	const std::string mysqlDB = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "MySQLDB");
	if (mysqlDB.empty()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "获取数据库参数失败");
		return false;
	}
	if (!m_dbConnection.connect(mysqlDB, false)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "连接数据库失败");
		return false;
	}

	return GFLib::CommonServer::CCommonSystem::_init();
}

void CDBSystemLG::_final()
{
	m_dbConnection.close();

	GFLib::CommonServer::CCommonSystem::_final();
}

bool CDBSystemLG::_loadGameConfig(const std::string& a_configPath)
{
	return GFLib::CommonServer::CCommonSystem::_loadGameConfig(a_configPath);
}

bool CDBSystemLG::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GFLib::CommonServer::CCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CDBSystemLG::_startSystem()
{
	return GFLib::CommonServer::CCommonSystem::_startSystem();
}

void CDBSystemLG::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	return GFLib::CommonServer::CCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CDBSystemLG::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	return GFLib::CommonServer::CCommonSystem::_cbServerLeave(a_serverID, a_key);
}

}//LG

}//DBSystem

}//GSLib

