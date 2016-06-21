#ifndef __GSLIB_PLAYERSYSTEM_CN_CPLAYERCNMGR_H__
#define __GSLIB_PLAYERSYSTEM_CN_CPLAYERCNMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/uniqueID.h>
#include <BSLib/utility/memory/objectMgr.h>
#include <GFLib/commonServer/commonSystem.h>
#include "GSLib/playerSystem/CN/playerCN.h"
#include "GSLib/loginSystem/CN/netPlayerCNMgr.h"
#include "GSLib/loginSystem/CN/netPlayerCN.h"

namespace GSLib
{

namespace PlayerSystem
{

namespace CN
{
BSLIB_UTILITY_OBJECTMGR_KEY2(CObjectPlayerCNMgr, AccountKey, EntityID);
class CPlayerCNMgr : public GSLib::LoginSystem::CN::CNetPlayerCNMgr, BSLib::Utility::CUniqueIDMgr<GSLib::EntityID>
{
public:

	CPlayerCNMgr();
	virtual ~CPlayerCNMgr();

	BSLIB_SINGLETON_DECLARE(CPlayerCNMgr);

	bool init();
	void final();
protected:
	virtual bool checkUniqueID(GSLib::EntityID a_id);
public:
	virtual GSLib::LoginSystem::CN::CNetPlayerCN* createNetPlayerCN(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName);
	virtual GSLib::LoginSystem::CN::CNetPlayerCN* getNetPlayerCN(const GFLib::SAccountKey& a_accountKey);
	virtual void removeNetPlayerCN(const GFLib::SAccountKey& a_accountKey);

public:
	CPlayerCN* getPlayerCN(const GFLib::SAccountKey& a_accountKey);
	CRoleCN* getCurRoleCN(const GFLib::SAccountKey& a_accountKey);

	void getAllRoleCN(std::list<CRoleCN*> &a_listRoles);
	void getActiveRolesCN(std::list<CRoleCN*>&a_listRoles);
	CRoleCN* getRoleCN(const GSLib::SRoleKey& a_roleKey);
	CRoleCN* getRoleCN(GFLib::AccountID a_accountID,GFLib::ZoneID a_zoneID,GSLib::RoleIndex a_roleIndex);

public:
	void removeAllPlayer();

private:
	CObjectPlayerCNMgr<GFLib::SAccountKey, GSLib::EntityID, CPlayerCN> m_playerCNMgr;
	BSLib::Utility::CUniqueID<GSLib::EntityID> m_uniqueID;
};

}//CN

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_CN_CPLAYERCNMGR_H__

