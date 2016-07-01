#include <GSLib/mailSystem/DB/mailSystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/mailSystem/DB/tableMailDB.h>


namespace GSLib
{

namespace MailSystem
{	

namespace DB
{

BSLIB_SINGLETON_DEFINE(CMailSystemDB);

CMailSystemDB::CMailSystemDB()
{
	;
}

CMailSystemDB::~CMailSystemDB()
{
	;
}

bool CMailSystemDB::_init()
{	
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CMailSystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CMailSystemDB::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CMailSystemDB::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}

bool CMailSystemDB::_startSystem()
{	
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER,
		GSLib::EFUNCTYPE_MAILSYSTEM, EMODULECTYPE_MAIL, EDBTABLEID_ROLE_MAIL_CONFIG_DATA);

	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER,
		GSLib::EFUNCTYPE_MAILSYSTEM, EMODULECTYPE_MAIL, EDBTABLEID_ROLE_MAIL_INPUTBOX_DATA);


	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByGlobal(GSLib::SRVTYPE_GAMESERVER, 
		GSLib::EFUNCTYPE_MAILSYSTEM, EMODULECTYPE_NULL, EDBTABLEID_MAIL_OUTPUT_DATA);


	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByGlobal(GSLib::SRVTYPE_CENTERSERVER, 
		GSLib::EFUNCTYPE_MAILSYSTEM, EMODULECTYPE_NULL, EDBTABLEID_MAIL_OUTPUT_DATA);	

	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CMailSystemDB::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CMailSystemDB::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerLeave(a_serverID, a_key);
}

}//DB

}//TaskSystem

}//GSLib

