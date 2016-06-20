//////////////////////////////////////////////////////////////////////
//	created:	2014/08/03
//	filename:	GSLib\playerSystem\GM\playerGMMgr.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////

#ifndef __GSLIB_PLAYERSYSTEM_GM_PLAYERGMMGR_H__
#define __GSLIB_PLAYERSYSTEM_GM_PLAYERGMMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/uniqueID.h>
#include <BSLib/utility/memory/objectMgr.h>
#include <GFLib/commonServer/commonSystem.h>

#include <GSLib/playerSystem/GM/playerGM.h>

#include <GSLib/loginSystem/GM/netPlayerGMMgr.h>
#include <GSLib/loginSystem/GM/netPlayerGM.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace GM
{

BSLIB_UTILITY_OBJECTMGR_KEY2(CObjectPlayerGMMgr, AccountKey, EntityID);

class CPlayerGMMgr:public GSLib::LoginSystem::GM::CNetPlayerGMMgr, BSLib::Utility::CUniqueIDMgr<GSLib::EntityID>
{
public:
	CPlayerGMMgr();
	virtual ~CPlayerGMMgr();

	BSLIB_SINGLETON_DECLARE(CPlayerGMMgr);

	bool init();
	void final();

protected:
	virtual bool checkUniqueID(GSLib::EntityID a_id);

public:
	LoginSystem::GM::CNetPlayerGM* createNetPlayerGM(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName);
	LoginSystem::GM::CNetPlayerGM* getNetPlayerGM(const GFLib::SAccountKey& a_accountKey);
	void removeNetPlayerGM(const GFLib::SAccountKey& a_accountKey);

public:
    CPlayerGM* getPlayerGM(const GFLib::SAccountKey& a_accountKey);
	void getAllRoleGM(std::list<CRoleGM*> &a_listRoles);
	void getActiveRolesGM(std::list<CRoleGM*>&a_listRoles);
	CRoleGM* getCurRoleGM(const GFLib::SAccountKey& a_accountKey);

	CRoleGM* getRoleGM(const GSLib::SRoleKey& a_roleKey);
	CRoleGM* getRoleGM(GFLib::AccountID a_accountID,GFLib::ZoneID a_zoneID,GSLib::RoleIndex a_roleIndex);
    CRoleGM* getRoleGMByRoleName(GFLib::AccountID a_accountID,GFLib::ZoneID a_zoneID,std::string a_roleName);

public:
	void removeAllPlayer();
    void update(BSLib::uint64 a_delayMilliseconds);
private:
	 CObjectPlayerGMMgr<GFLib::SAccountKey, GSLib::EntityID, CPlayerGM> m_playerGMMgr;
	 BSLib::Utility::CUniqueID<GSLib::EntityID> m_uniqueID;
};
}//GM

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GM_PLAYERGMMGR_H__
