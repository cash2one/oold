#include <GSLib/playerSystem/CN/roleBaseInfoCNMgr.h>
#include "GSLib/playerSystem/CN/roleBaseInfoCN.h"
#include <GSLib/tracer.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace CN
{

BSLIB_SINGLETON_DEFINE(CRoleBaseInfoCNMgr);

CRoleBaseInfoCNMgr::CRoleBaseInfoCNMgr()
{
	m_uniqueID.setUniqueIDMgr(this);
}

CRoleBaseInfoCNMgr::~CRoleBaseInfoCNMgr()
{
	;
}
bool CRoleBaseInfoCNMgr::init()
{
	return true;
}

void CRoleBaseInfoCNMgr::final()
{
	removeAllPlayer();
}

bool  CRoleBaseInfoCNMgr::checkUniqueID(GSLib::RoleID a_id)
{
	return m_roleBaseInfoCNMgr.getObjectByRoleID(a_id) != NULL;
}

GSLib::RoleID CRoleBaseInfoCNMgr::getNewRoleID()
{
    return m_uniqueID.allocateID();
}

CRoleBaseInfoCN* CRoleBaseInfoCNMgr::createRoleBaseInfoCN(const DB::SRoleData& a_roleData)
{
    if(NULL != getRoleBaseInfoCNByRoleID(a_roleData.m_roleID)){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "createRoleBaseInfoCN[a_roleID=%d] 添加数据失败,roleID重复！", a_roleData.m_roleID);
       return NULL;
    }
    GSLib::SRoleKey roleKey;
    roleKey.setAccountID(a_roleData.m_accountID);
    roleKey.setZoneID(a_roleData.m_zoneID);
    roleKey.setIndex(a_roleData.m_roleIndex);

    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "createRoleBaseInfoCN[a_roleID=%d]", a_roleData.m_roleID);
    CRoleBaseInfoCN* roleBaseInfo = m_roleBaseInfoCNMgr.allcateObject(a_roleData.m_roleID,a_roleData.m_roleName,roleKey.getDBKey(), a_roleData.m_roleID, a_roleData.m_roleName,roleKey);
    if (roleBaseInfo == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "createRoleBaseInfoCN[a_roleID=%d] 失败！", a_roleData.m_roleID);
        return NULL;
    }
    roleBaseInfo->init(a_roleData);
    return roleBaseInfo;
}

CRoleBaseInfoCN* CRoleBaseInfoCNMgr::updateRoleBaseInfoCN(const DB::SRoleData& a_roleData)
{
    CRoleBaseInfoCN* roleBaseInfo = getRoleBaseInfoCNByRoleID(a_roleData.m_roleID);
    if(NULL == roleBaseInfo){
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "createRoleBaseInfoCN[m_roleName=%s][a_roleID=%d] 更新角色数据不存在,添加数据！", a_roleData.m_roleName, a_roleData.m_roleID);
        return createRoleBaseInfoCN(a_roleData);
    }
    roleBaseInfo->update(a_roleData);
    return roleBaseInfo;
}


void CRoleBaseInfoCNMgr::removeRoleBaseInfoCNRoleID(GSLib::RoleID a_roleID)
{
	m_roleBaseInfoCNMgr.getObjectByRoleID(a_roleID);
}

CRoleBaseInfoCN* CRoleBaseInfoCNMgr::getRoleBaseInfoCNByRoleName(const std::string& a_roleName)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getRoleBaseInfoCN%s", a_roleName.c_str());
	return m_roleBaseInfoCNMgr.getObjectByRoleName(a_roleName);
}

CRoleBaseInfoCN* CRoleBaseInfoCNMgr::getRoleBaseInfoCNByRoleKey(const std::string& a_roleKey)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getRoleBaseInfoCN%s", a_roleKey.c_str());
    return m_roleBaseInfoCNMgr.getObjectByRoleKey(a_roleKey);
}

CRoleBaseInfoCN* CRoleBaseInfoCNMgr::getRoleBaseInfoCNByRoleID(GSLib::RoleID a_roleID)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "getRoleBaseInfoCN%d", a_roleID);
    return m_roleBaseInfoCNMgr.getObjectByRoleID(a_roleID);
}

void CRoleBaseInfoCNMgr::removeAllPlayer()
{
	m_roleBaseInfoCNMgr.destroyAll();
}

}//CN

}//PlayerSystem

}//GSLib

