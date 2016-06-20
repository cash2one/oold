//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	GSLib\playerSystem\CN\CPlayerCNMgr.h
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_CN_CROLEBASEINFOCNMGR_H__
#define __GSLIB_PLAYERSYSTEM_CN_CROLEBASEINFOCNMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/uniqueID.h>
#include <BSLib/utility/memory/objectMgr.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/playerSystem/CN/roleBaseInfoCN.h>
#include "GSLib/loginSystem/CN/netPlayerCNMgr.h"
#include "GSLib/loginSystem/CN/netPlayerCN.h"

namespace GSLib
{

namespace PlayerSystem
{

namespace CN
{
BSLIB_UTILITY_OBJECTMGR_KEY3(CObjectRoleBaseInfoCNMgr, RoleID,RoleName,RoleKey);
class CRoleBaseInfoCNMgr : BSLib::Utility::CUniqueIDMgr<GSLib::RoleID>
{
public:
	CRoleBaseInfoCNMgr();
	virtual ~CRoleBaseInfoCNMgr();

	BSLIB_SINGLETON_DECLARE(CRoleBaseInfoCNMgr);

	bool init();
	void final();

protected:
	virtual bool checkUniqueID(GSLib::RoleID a_id);

    GSLib::RoleID getNewRoleID();

public:
    CRoleBaseInfoCN* createRoleBaseInfoCN(const DB::SRoleData& a_roleData);
    CRoleBaseInfoCN* updateRoleBaseInfoCN(const DB::SRoleData& a_roleData);

	CRoleBaseInfoCN* getRoleBaseInfoCNByRoleName(const std::string& a_roleName);
    CRoleBaseInfoCN* getRoleBaseInfoCNByRoleKey(const std::string& a_roleKey);
    CRoleBaseInfoCN* getRoleBaseInfoCNByRoleID(GSLib::RoleID a_roleID);

    void removeRoleBaseInfoCNRoleID(GSLib::RoleID a_roleID);
    void removeAllPlayer();

    const CObjectRoleBaseInfoCNMgr<GSLib::RoleID, std::string,std::string, CRoleBaseInfoCN>&  getRoleBaseInfoCNMgr() { return m_roleBaseInfoCNMgr;}
private:
    CObjectRoleBaseInfoCNMgr<GSLib::RoleID, std::string,std::string, CRoleBaseInfoCN> m_roleBaseInfoCNMgr;
	BSLib::Utility::CUniqueID<GSLib::RoleID> m_uniqueID;
};

}//CN

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_CN_CROLEBASEINFOCNMGR_H__
