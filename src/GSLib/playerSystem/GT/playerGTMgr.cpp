#include <GSLib/playerSystem/GT/playerGTMgr.h>
#include <GSLib/playerSystem/GT/playerGT.h>
#include <GSLib/tracer.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace GT
{

BSLIB_SINGLETON_DEFINE(CPlayerGTMgr);
CPlayerGTMgr::CPlayerGTMgr()
{
	;
}

CPlayerGTMgr::~CPlayerGTMgr()
{
	;
}

bool CPlayerGTMgr::init()
{
	return true;
}

void CPlayerGTMgr::final()
{
	removeAllPlayer();
}

GSLib::LoginSystem::GT::CNetPlayerGT* CPlayerGTMgr::createNetPlayerGT(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "createNetPlayerGT%s[a_accountName=%s]", a_accountKey.toLogString().c_str(), a_accountName.c_str());

	CPlayerGT* pPlayer = NULL;
	pPlayer = new CPlayerGT(a_accountKey,a_accountName);
	if (pPlayer == NULL){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "createNetPlayerGT%s[a_accountName=%s] 失败！", a_accountKey.toLogString().c_str(), a_accountName.c_str());
		return NULL;
	}
	m_accountHashMap.setValue(a_accountKey, pPlayer);

	return pPlayer;
}

GSLib::LoginSystem::GT::CNetPlayerGT* CPlayerGTMgr::getNetPlayerGT(const GFLib::SAccountKey& a_accountKey)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getNetPlayerGT%s", a_accountKey.toLogString().c_str());
	CPlayerGT* pPlayer = NULL;
	m_accountHashMap.getValue(a_accountKey,pPlayer);
	return pPlayer;
}

void CPlayerGTMgr::removeNetPlayerGT(const GFLib::SAccountKey& a_accountKey)
{
	CPlayerGT* pPlayer = NULL;
	if (!m_accountHashMap.getValue(a_accountKey, pPlayer)) {
		return ;
	}
	if (pPlayer != NULL) {
		BSLIB_SAFE_DELETE(pPlayer);
	}

	m_accountHashMap.remove(a_accountKey);
}

CPlayerGT* CPlayerGTMgr::getPlayerGT(const GFLib::SAccountKey& a_accountKey)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getNetPlayerGT%s", a_accountKey.toLogString().c_str());
	CPlayerGT* pPlayer = NULL;
	m_accountHashMap.getValue(a_accountKey,pPlayer);
	return pPlayer;
}

CRoleGT* CPlayerGTMgr::getCurRoleGT(const GFLib::SAccountKey& a_accountKey)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getRoleGT%s", a_accountKey.toLogString().c_str());
	CPlayerGT* player = getPlayerGT(a_accountKey);
	if (player == NULL){
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getCurRoleGT 玩家不在线%s", a_accountKey.toLogString().c_str());
		return NULL;
	}
	return player->getCurRole();
}

void CPlayerGTMgr::removeAllPlayer()
{
	BSLib::Utility::CHashMap<GFLib::SAccountKey, CPlayerGT*>::iterator it = m_accountHashMap.begin();
	for (; it != m_accountHashMap.end(); ++it) {
		CPlayerGT* pPlayer = it->second;
		if (pPlayer == NULL) {
			continue;
		}
		BSLIB_SAFE_DELETE(pPlayer);
	}
	m_accountHashMap.clear();
}

}//GT

}//PlayerSystem

}//GSLib

