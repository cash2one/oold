#include <GSLib/playerSystem/GM/playerGMMgr.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/tracer.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace GM
{

BSLIB_SINGLETON_DEFINE(CPlayerGMMgr);

CPlayerGMMgr::CPlayerGMMgr()
{
	m_uniqueID.setUniqueIDMgr(this);
}

CPlayerGMMgr::~CPlayerGMMgr()
{
}

bool CPlayerGMMgr::init()
{	
	return true;
}

void CPlayerGMMgr::final()
{
	removeAllPlayer();
}

bool  CPlayerGMMgr::checkUniqueID(GSLib::EntityID a_id)
{
	return m_playerGMMgr.getObjectByEntityID(a_id) != NULL;
}

LoginSystem::GM::CNetPlayerGM*  CPlayerGMMgr::createNetPlayerGM(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "createNetPlayerGM%s[a_accountName=%s]", a_accountKey.toLogString().c_str(), a_accountName.c_str());

	EntityID entitiyID = m_uniqueID.allocateID();

	if (!m_uniqueID.isValidID(entitiyID)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "createNetPlayerGM%s[a_accountName=%s] 失败！ !m_uniqueID.isValidID [playerEntitiyID=%lld]", a_accountKey.toLogString().c_str(), a_accountName.c_str(), entitiyID);
		return NULL; 
	}
	CPlayerGM* pPlayer = m_playerGMMgr.allcateObject(a_accountKey, entitiyID, entitiyID, a_accountKey, a_accountName);
	if (pPlayer == NULL){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "createNetPlayerGM%s[a_accountName=%s] 失败！", a_accountKey.toLogString().c_str(), a_accountName.c_str());
		return NULL;
	}
    return pPlayer;
}

LoginSystem::GM::CNetPlayerGM* CPlayerGMMgr::getNetPlayerGM(const GFLib::SAccountKey& a_accountKey)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getNetPlayerGM%s", a_accountKey.toLogString().c_str());
	return (LoginSystem::GM::CNetPlayerGM*)m_playerGMMgr.getObjectByAccountKey(a_accountKey);
}

void CPlayerGMMgr::removeNetPlayerGM(const GFLib::SAccountKey& a_accountKey)
{
	m_playerGMMgr.destroyByAccountKey(a_accountKey);
}

void CPlayerGMMgr::removeAllPlayer()
{
	m_playerGMMgr.destroyAll();
}

void CPlayerGMMgr::update(BSLib::uint64 a_delayMilliseconds)
{
}

CPlayerGM* CPlayerGMMgr::getPlayerGM(const GFLib::SAccountKey& a_accountKey)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getPlayerGM%s", a_accountKey.toLogString().c_str());
	return m_playerGMMgr.getObjectByAccountKey(a_accountKey);
}

void CPlayerGMMgr::getAllRoleGM(std::list<CRoleGM*> &a_listRoles)
{
	class Callback : public CObjectPlayerGMMgr<GFLib::SAccountKey, GSLib::EntityID, CPlayerGM>::CCallback
	{
	public:
		Callback(std::list<CRoleGM *> & a_listRoleGM)
			:m_listRoleGM(a_listRoleGM)
		{
		}
		virtual bool exec(CPlayerGM * a_player)
		{
			if ( a_player != NULL ) {
				CRoleGM * role = a_player->getCurRole();
				if (role != NULL){
					m_listRoleGM.push_back(a_player->getCurRole());
				}
			}
			return true;
		}
	private:
		std::list<CRoleGM * > & m_listRoleGM;
	};

	Callback callBack(a_listRoles);
	m_playerGMMgr.traversal(callBack);
}

void CPlayerGMMgr::getActiveRolesGM(std::list<CRoleGM*>&a_listRoles)
{
	class Callback : public CObjectPlayerGMMgr<GFLib::SAccountKey, GSLib::EntityID, CPlayerGM>::CCallback
	{
	public:
		Callback(std::list<CRoleGM *> & a_listRoleGM)
			:m_listRoleGM(a_listRoleGM)
		{
		}
		virtual bool exec(CPlayerGM * a_player)
		{
			if ( a_player != NULL ) {
				CRoleGM * role = a_player->getCurRole();
				if ((role != NULL)&& (role->isActive())){
					m_listRoleGM.push_back(a_player->getCurRole());
				}
			}
			return true;
		}
	private:
		std::list<CRoleGM * > & m_listRoleGM;
	};

	Callback callBack(a_listRoles);
	m_playerGMMgr.traversal(callBack);
}

CRoleGM* CPlayerGMMgr::getCurRoleGM(const GFLib::SAccountKey& a_accountKey)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getRoleGM%s", a_accountKey.toLogString().c_str());
	CPlayerGM* player = m_playerGMMgr.getObjectByAccountKey(a_accountKey);
	if (player == NULL){
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getPlayerGM 玩家不在线%s", a_accountKey.toLogString().c_str());
		return NULL;
	}
	return player->getCurRole();
}

CRoleGM* CPlayerGMMgr::getRoleGM(const GSLib::SRoleKey& a_roleKey)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getRoleGM%s", a_roleKey.toLogString().c_str());
	const GFLib::SAccountKey& accountKey = a_roleKey.getAccountKey();
	CPlayerGM* player = m_playerGMMgr.getObjectByAccountKey(accountKey);
	if (player == NULL){
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getPlayerGM 玩家不在线%s", accountKey.toLogString().c_str());
		return NULL;
	}
	return player->getRole(a_roleKey.getIndex());
}

CRoleGM* CPlayerGMMgr::getRoleGM(GFLib::AccountID a_accountID,GFLib::ZoneID a_zoneID,GSLib::RoleIndex a_roleIndex)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getRoleGM=%lld", a_accountID);
	GSLib::SRoleKey roleKey;
	roleKey.setAccountID(a_accountID);
	roleKey.setZoneID(a_zoneID);
	roleKey.setIndex(a_roleIndex);
    return getRoleGM(roleKey);
}

CRoleGM* CPlayerGMMgr::getRoleGMByRoleName(GFLib::AccountID a_accountID,GFLib::ZoneID a_zoneID,std::string a_roleName)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getRoleGM=%lld", a_accountID);
	GFLib::SAccountKey accountKey;
	accountKey.setAccountID(a_accountID);
	accountKey.setZoneID(a_zoneID);
    CPlayerGM* player = m_playerGMMgr.getObjectByAccountKey(accountKey);
    if (player == NULL){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getRoleGMByRoleName 玩家不在线%s", accountKey.toLogString().c_str());
        return NULL;
    }
    return player->getRoleByName(a_roleName);
}

}//GM

}//PlayerSystem

}//GSLib

