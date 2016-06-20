//////////////////////////////////////////////////////////////////////
//	created:	2014/09/26
//	filename: 	src\GSLib\itemSystem\DB\itemSystemDB.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
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

bool CItemSystemDB::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CItemSystemDB::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}

bool CItemSystemDB::_startSystem()
{
	//GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByPlayer(GSLib::SRVTYPE_GAMESERVER, GSLib::EFUNCTYPE_ITEMSYSTEM, EMODULECTYPE_ITEM, EDBTABLEID_ROLE_ITEM_DATA);
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CItemSystemDB::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CItemSystemDB::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

}//LG

}//ItemSystem

}//GSLib
