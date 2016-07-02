#include <GSLib/friendSystem/DB/friendSystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/friendSystem/DB/tableFriendDB.h>


namespace GSLib
{

namespace FriendSystem
{	

namespace DB
{

BSLIB_SINGLETON_DEFINE(CFriendSystemDB);

CFriendSystemDB::CFriendSystemDB()
{
	;
}

CFriendSystemDB::~CFriendSystemDB()
{
	;
}

bool CFriendSystemDB::_init()
{	
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CFriendSystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CFriendSystemDB::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CFriendSystemDB::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CFriendSystemDB::_startSystem()
{	
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_CENTERSERVER,
		GSLib::EFUNCTYPE_FRIENDSYSTEM, EMODULETYPE_FRIEND, EDBTABLEID_ROLE_FRIEND_DATA);

	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER,
		GSLib::EFUNCTYPE_FRIENDSYSTEM, EMODULETYPE_FRIEND, EDBTABLEID_ROLE_FRIEND_DATA);

	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByGlobal(GSLib::SRVTYPE_CENTERSERVER,
		GSLib::EFUNCTYPE_FRIENDSYSTEM, EMODULECTYPE_NULL, EDBTABLEID_FRIEND_PENDING_QUEUE_DATA);


	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CFriendSystemDB::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CFriendSystemDB::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

}//DB

}

}//GSLib
