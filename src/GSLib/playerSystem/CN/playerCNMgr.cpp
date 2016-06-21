#include <GSLib/playerSystem/CN/playerCNMgr.h>
#include "GSLib/playerSystem/CN/playerCN.h"
#include <GSLib/tracer.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace CN
{

BSLIB_SINGLETON_DEFINE(CPlayerCNMgr);

CPlayerCNMgr::CPlayerCNMgr()
{
	m_uniqueID.setUniqueIDMgr(this);
}

CPlayerCNMgr::~CPlayerCNMgr()
{
	;
}
bool CPlayerCNMgr::init()
{
	return true;
}

void CPlayerCNMgr::final()
{
	removeAllPlayer();
}

bool  CPlayerCNMgr::checkUniqueID(GSLib::EntityID a_id)
{
	return m_playerCNMgr.getObjectByEntityID(a_id) != NULL;
}

GSLib::LoginSystem::CN::CNetPlayerCN* CPlayerCNMgr::createNetPlayerCN(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "createNetPlayerCN%s[a_accountName=%s]", a_accountKey.toLogString().c_str(), a_accountName.c_str());

	EntityID entitiyID = m_uniqueID.allocateID();

	if (!m_uniqueID.isValidID(entitiyID)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "createNetPlayerCN%s[a_accountName=%s] 失败！ !m_uniqueID.isValidID [playerEntitiyID=%lld]", a_accountKey.toLogString().c_str(), a_accountName.c_str(), entitiyID);
		return NULL; 
	}
	CPlayerCN* pPlayer = m_playerCNMgr.allcateObject(a_accountKey, entitiyID, entitiyID, a_accountKey, a_accountName);
	if (pPlayer == NULL){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "createNetPlayerCN%s[a_accountName=%s] 失败！", a_accountKey.toLogString().c_str(), a_accountName.c_str());
		return NULL;
	}
	return pPlayer;
}

GSLib::LoginSystem::CN::CNetPlayerCN* CPlayerCNMgr::getNetPlayerCN(const GFLib::SAccountKey& a_accountKey)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getNetPlayerCN%s", a_accountKey.toLogString().c_str());
	return (LoginSystem::CN::CNetPlayerCN*)m_playerCNMgr.getObjectByAccountKey(a_accountKey);
}

void CPlayerCNMgr::removeNetPlayerCN(const GFLib::SAccountKey& a_accountKey)
{
	m_playerCNMgr.destroyByAccountKey(a_accountKey);
}

CPlayerCN* CPlayerCNMgr::getPlayerCN(const GFLib::SAccountKey& a_accountKey)
{
	return m_playerCNMgr.getObjectByAccountKey(a_accountKey);
}

void CPlayerCNMgr::getActiveRolesCN(std::list<CRoleCN*>&a_listRoles)
{
	class Callback : public CObjectPlayerCNMgr<GFLib::SAccountKey, GSLib::EntityID, CPlayerCN>::CCallback
	{
	public:
		Callback(std::list<CRoleCN *> & a_listRoleGM)
			:m_listRoleCN(a_listRoleGM)
		{
		}
		virtual bool exec(CPlayerCN * a_player)
		{
			if ( a_player != NULL ) {
				CRoleCN * role = a_player->getCurRole();
				if ((role != NULL)&& (role->isActive())){
					m_listRoleCN.push_back(a_player->getCurRole());
				}
			}
			return true;
		}
	private:
		std::list<CRoleCN * > & m_listRoleCN;
	};

	Callback callBack(a_listRoles);
	m_playerCNMgr.traversal(callBack);
}

CRoleCN* CPlayerCNMgr::getCurRoleCN(const GFLib::SAccountKey& a_accountKey)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getRoleCN%s", a_accountKey.toLogString().c_str());
	CPlayerCN* player = m_playerCNMgr.getObjectByAccountKey(a_accountKey);
	if (player == NULL){
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getCurRoleCN 玩家不在线%s", a_accountKey.toLogString().c_str());
		return NULL;
	}
	return player->getCurRole();
}

CRoleCN* CPlayerCNMgr::getRoleCN(const GSLib::SRoleKey& a_roleKey)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getRoleCN%s", a_roleKey.toLogString().c_str());
	const GFLib::SAccountKey& accountKey = a_roleKey.getAccountKey();
	CPlayerCN* player = m_playerCNMgr.getObjectByAccountKey(accountKey);
	if (player == NULL){
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getRoleCN 玩家不在线%s", accountKey.toLogString().c_str());
		return NULL;
	}
	return player->getRole(a_roleKey.getIndex());
}

CRoleCN* CPlayerCNMgr::getRoleCN(GFLib::AccountID a_accountID,GFLib::ZoneID a_zoneID,GSLib::RoleIndex a_roleIndex)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getRoleCN=%lld", a_accountID);
	GSLib::SRoleKey roleKey;
	roleKey.setAccountID(a_accountID);
	roleKey.setZoneID(a_zoneID);
	roleKey.setIndex(a_roleIndex);
	return getRoleCN(roleKey);
}

void CPlayerCNMgr::removeAllPlayer()
{
	m_playerCNMgr.destroyAll();
}

}//CN

}//PlayerSystem

}//GSLib

