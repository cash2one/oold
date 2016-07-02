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

bool CMailSystemDB::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CMailSystemDB::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CMailSystemDB::_ICommonSystem_startSystem()
{	
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER,
		GSLib::EFUNCTYPE_MAILSYSTEM, EMODULECTYPE_MAIL, EDBTABLEID_ROLE_MAIL_CONFIG_DATA);

	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER,
		GSLib::EFUNCTYPE_MAILSYSTEM, EMODULECTYPE_MAIL, EDBTABLEID_ROLE_MAIL_INPUTBOX_DATA);


	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByGlobal(GSLib::SRVTYPE_GAMESERVER, 
		GSLib::EFUNCTYPE_MAILSYSTEM, EMODULECTYPE_NULL, EDBTABLEID_MAIL_OUTPUT_DATA);


	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByGlobal(GSLib::SRVTYPE_CENTERSERVER, 
		GSLib::EFUNCTYPE_MAILSYSTEM, EMODULECTYPE_NULL, EDBTABLEID_MAIL_OUTPUT_DATA);	

	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_startSystem();
}

void CMailSystemDB::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CMailSystemDB::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

}//DB

}//TaskSystem

}//GSLib

