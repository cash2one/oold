#include <GSLib/itemSystem/DB/itemSystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/itemSystem/DB/tableItemDB.h>


namespace GSLib
{

namespace ItemSystem
{	

namespace DB
{

BSLIB_SINGLETON_DEFINE(CItemSystemDB);

CItemSystemDB::CItemSystemDB()
{
	;
}

CItemSystemDB::~CItemSystemDB()
{
	;
}

bool CItemSystemDB::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CItemSystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CItemSystemDB::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CItemSystemDB::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CItemSystemDB::_startSystem()
{
	//GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByPlayer(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_ITEMSYSTEM, EMODULECTYPE_ITEM, EDBTABLEID_ROLE_ITEM_DATA);
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CItemSystemDB::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CItemSystemDB::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

}//LG

}//ItemSystem

}//GSLib

