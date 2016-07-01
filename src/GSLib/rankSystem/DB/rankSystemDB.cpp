#include <GSLib/rankSystem/DB/rankSystemDB.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GSLib/rankSystem/DB/tableRankDB.h>


namespace GSLib
{

namespace RankSystem
{	

namespace DB
{

BSLIB_SINGLETON_DEFINE(CRankSystemDB);

CRankSystemDB::CRankSystemDB()
{
	;
}

CRankSystemDB::~CRankSystemDB()
{
	;
}

bool CRankSystemDB::_init()
{	
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CRankSystemDB::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CRankSystemDB::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CRankSystemDB::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}

bool CRankSystemDB::_startSystem()
{	
	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByGlobal(GSLib::SRVTYPE_CENTERSERVER, 
		GSLib::EFUNCTYPE_RANKSYSTEM, EMODULECTYPE_NULL, EDBTABLEID_RANK_DATA);	

	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_GAMESERVER, 
		GSLib::EFUNCTYPE_RANKSYSTEM, EMODULECTYPE_RANK, EDBTABLEID_ROLE_RANK_DATA);	

	GSLib::DBSystem::DB::CDBSystemDB::singleton().setInitTableByRole(GSLib::SRVTYPE_CENTERSERVER, 
		GSLib::EFUNCTYPE_RANKSYSTEM, EMODULECTYPE_RANK, EDBTABLEID_ROLE_RANK_CN_DATA);	

	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CRankSystemDB::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CRankSystemDB::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerLeave(a_serverID, a_key);
}

}//DB

}

}//GSLib
