#include <GSLib/tracer.h>
#include "DB/playerDBMgr.h"

namespace GSLib
{

namespace DBSystem
{	

namespace DB
{

BSLIB_SINGLETON_DEFINE(CPlayerDBMgr);

CPlayerDBMgr::CPlayerDBMgr()
{
	;
}

CPlayerDBMgr::~CPlayerDBMgr()
{
	;
}

bool CPlayerDBMgr::init()
{
	return true;
}

void CPlayerDBMgr::final()
{
	BSLib::Utility::CHashMap<GFLib::SAccountKey, CPlayerDB*>::iterator it = m_accountHashMap.begin();
	for (; it != m_accountHashMap.end(); ++it) {
		CPlayerDB* playerDB = it->second;
		if (playerDB == NULL) {
			continue;
		}
		playerDB->final();

		BSLIB_SAFE_DELETE(playerDB);
	}
}

GSLib::LoginSystem::DB::CNetPlayerDB* CPlayerDBMgr::createNetPlayerDB(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName)
{
	if (m_accountHashMap.find(a_accountKey) != m_accountHashMap.end()) {
		return NULL;
	}
	CPlayerDB* playerDB = new CPlayerDB(a_accountKey, a_accountName);
	if (playerDB == NULL) {
		return NULL;
	}
	m_accountHashMap.setValue(a_accountKey, playerDB);
	return playerDB;
}

GSLib::LoginSystem::DB::CNetPlayerDB* CPlayerDBMgr::getNetPlayerDB(const GFLib::SAccountKey& a_accountKey)
{
	CPlayerDB* playerDB = NULL;
	m_accountHashMap.getValue(a_accountKey, playerDB);
	return playerDB;
}

CPlayerDB* CPlayerDBMgr::getPlayerDB(const GFLib::SAccountKey& a_accountKey)
{
	CPlayerDB* playerDB = NULL;
	m_accountHashMap.getValue(a_accountKey, playerDB);
	return playerDB;
}

void CPlayerDBMgr::removeNetPlayerDB(const GFLib::SAccountKey& a_accountKey)
{
	CPlayerDB* playerDB = NULL;
	if (!m_accountHashMap.getValue(a_accountKey, playerDB)) {
		return;
	}
	if (playerDB != NULL) {
		BSLIB_SAFE_DELETE(playerDB);
	}
	m_accountHashMap.remove(a_accountKey);
}

}//DB

}//DBSystem

}//GSLib

