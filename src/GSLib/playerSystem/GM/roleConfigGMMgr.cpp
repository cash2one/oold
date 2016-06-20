//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	src\GSLib\equipSystem\GM\equipGMMgr.cpp
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////

#include <GSLib/equipSystem/msgEquipSystemGC.h>
#include <GSLib/equipSystem/msgEquipSystem.h>
#include <GSLib/tracer.h>
#include <BSLib/utility/file/dirInfo.h>
#include <BSLib/utility/table.h>
#include "roleConfigGMMgr.h"
#include <GSLib/playerSystem/GM/roleBagModuleGM.h>
namespace GSLib
{

namespace PlayerSystem
{	

namespace GM
{

BSLIB_SINGLETON_DEFINE(CRoleConfigGMMgr);

CRoleConfigGMMgr::CRoleConfigGMMgr()
{

}

CRoleConfigGMMgr::~CRoleConfigGMMgr()
{
}

void CRoleConfigGMMgr::init()
{
	;
}

void CRoleConfigGMMgr::final()
{
    _removeVipConfig();
    _removeBagInitConfig();
    _removeSkillInitConfig();
}

bool CRoleConfigGMMgr::loadGameConfig(const std::string& a_configPath)
{
    if (!_loadVipConfig(a_configPath)){
        return false;
    }

	if (!_loadRoleInitConfig(a_configPath)){
		return false;
	}

	if (!_loadBagInitConfig(a_configPath)){
		return false;
	}

    if (!_loadSkillInitConfig(a_configPath)){
        return false;
    }

	return true;
}

bool CRoleConfigGMMgr::getUpgradeExp(BSLib::uint32 a_level,BSLib::uint64& a_exp) const
{
    if((a_level < 1)||(a_level>=100)){
        return false;
    }
    if((a_level >= 1)&&(a_level <= 30)){
        a_exp = 61 * a_level * a_level - 153 * a_level + 192;
		a_exp = (a_exp + 5) / 10 * 10 ; //十位数四舍五入
    } else {
        a_exp = 1750 * a_level * a_level - 102500 * a_level + 1550000;
		a_exp = (a_exp + 50) / 100 * 100; //百位数四舍五入
    }
    return true;
}

bool CRoleConfigGMMgr::getVipScore(BSLib::uint32 a_level,BSLib::uint32& a_vipScore) const
{
    std::map<BSLib::uint32, SVipConfig*>::const_iterator it = m_roleVipMap.find(a_level);
    if( it == m_roleVipMap.end()){
        return false;
    }

    SVipConfig* config = it ->second;
    if(config == NULL){
        return false;
    }
    a_vipScore = config->m_score;
    return true;
}

bool CRoleConfigGMMgr::getVipGift(BSLib::uint32 a_level,std::string& a_vipGift) const
{
    std::map<BSLib::uint32, SVipConfig*>::const_iterator it = m_roleVipMap.find(a_level);
    if( it == m_roleVipMap.end()){
        return false;
    }

    SVipConfig* config = it ->second;
    if(config == NULL){
        return false;
    }
    a_vipGift = config->m_vip_gift;
    return true;
}

SVipConfig* CRoleConfigGMMgr::getVipConfig(BSLib::uint32 a_level) const
{
    std::map<BSLib::uint32, SVipConfig*>::const_iterator it = m_roleVipMap.find(a_level);
    if( it == m_roleVipMap.end()){
        return NULL;
    }

   return it ->second;
}


bool CRoleConfigGMMgr::getUpgradeVipLevel(BSLib::uint32 a_oldVipLevel,BSLib::uint32 a_vipScore,BSLib::uint32& a_vipLevel) const
{
    BSLib::uint32 VipLevel = a_oldVipLevel + 1; 
    std::map<BSLib::uint32, SVipConfig*>::const_iterator it = m_roleVipMap.find(VipLevel);
    if( it == m_roleVipMap.end()){
        return false;
    }
    BSLib::uint32 score = 0;
    for(;it != m_roleVipMap.end();it++){
         SVipConfig* config = it ->second;
        score = config->m_score;
        if(a_vipScore < score){
            break;
        }
        a_vipLevel = it->first;
    }
    if(a_vipLevel <= a_oldVipLevel){
        return false;
    }

    return true;
}

bool CRoleConfigGMMgr::getUpgradeLevels(BSLib::uint32 a_level,BSLib::uint64 a_exp,BSLib::uint32& a_upgradeCount,BSLib::uint64& a_leftExp) const
{
    a_upgradeCount = 0;
    a_leftExp = a_exp;
    BSLib::uint64 needExp = 0; 
    for(BSLib::uint32 level = a_level;a_leftExp >= needExp;level++){
        if(!getUpgradeExp(level,needExp)){
            return false;
        }
        if(a_leftExp < needExp){
            return false;
        }
        a_upgradeCount++;
        a_leftExp -= needExp; 
    }
    
    return true;
}


const SRoleInitConfig& CRoleConfigGMMgr::getRoleInitConfig() const
{
	return m_roleInitConfig;
}

BSLib::Utility::CHashMap<BSLib::uint32, SBagInitConfig*> CRoleConfigGMMgr::getBagInitConfig() const
{
	return m_bagInitConfigHashMap;
}

SSkillInitConfig* CRoleConfigGMMgr::getSkillInitConfig(BSLib::uint32 a_roleTPID) const
{
    SSkillInitConfig* skillData = NULL;
    m_skillInitConfigHashMap.getValue(a_roleTPID,skillData);
    return skillData;
}

bool CRoleConfigGMMgr::_loadVipConfig(const std::string& a_configPath)
{
    BSLib::Utility::CStringA configPath = a_configPath;
    configPath += "\\player\\";

    std::string fileName = configPath + "t_role_vip_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

    BSLib::Utility::CStringA path(fileName);

    BSLib::Utility::CTableSheet tableSheet;
    if (!tableSheet.loadXmlFile(path)) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[LOADCONFIG_ERROR]loadXmlFile[%s]", path.c_str());
        return false;
    }
    try {
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "加载物品使用配置[%s]", path.c_str());
        BSLib::Utility::CTable& table = tableSheet["item"];
        for (BSLib::uint32 i=0; i < table.getRowCount(); ++i) {
            SVipConfig* config = new SVipConfig();
            config->loadData(table[i]);
            m_roleVipMap.insert(std::pair<BSLib::uint32, SVipConfig*>(config->m_level,config));
        }
    } catch (...){
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[LOADCONFIG_ERROR][Exception][%s]", path.c_str());
        return false;
    }
    return true;
}

bool CRoleConfigGMMgr::_loadRoleInitConfig(const std::string& a_configPath)
{
	BSLib::Utility::CStringA configPath = a_configPath;
	configPath += "\\roleInit\\";

	std::string fileName = configPath + "t_role_init_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

	BSLib::Utility::CStringA path(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(path)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[LOADCONFIG_ERROR]loadXmlFile[%s]", path.c_str());
		return false;
	}
	try {
		BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "加载角色初始配置[%s]", path.c_str());
		BSLib::Utility::CTable& table = tableSheet["item"];
		if (table.getRowCount()<=0){
			return false;
		}
		table[0]["f_role_diamond"] >> m_roleInitConfig.m_roleDiamond;
		table[0]["f_role_exp"] >> m_roleInitConfig.m_roleExp;
		table[0]["f_role_gold"] >> m_roleInitConfig.m_roleGold;
		table[0]["f_role_level"] >> m_roleInitConfig.m_roleLevel;
		table[0]["f_role_pop"] >> m_roleInitConfig.m_rolePOP;
		table[0]["f_role_vitality"] >> m_roleInitConfig.m_roleVitality;
		table[0]["f_role_pvpcoin"] >> m_roleInitConfig.m_rolePVPCoin;
		table[0]["f_role_skillpoint"] >> m_roleInitConfig.m_roleSkillPoint;

	} catch (...){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[LOADCONFIG_ERROR][Exception][%s]", path.c_str());
		return false;
	}
	return true;
}

bool CRoleConfigGMMgr::_loadBagInitConfig(const std::string& a_configPath)
{
	BSLib::Utility::CStringA configPath = a_configPath;
	configPath += "\\roleInit\\";

	std::string fileName = configPath + "t_bag_init_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

	BSLib::Utility::CStringA path(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(path)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[LOADCONFIG_ERROR]loadXmlFile[%s]", path.c_str());
		return false;
	}
	try {
		BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "加载角色背包数据配置[%s]", path.c_str());
		BSLib::Utility::CTable& table = tableSheet["item"];
		for (BSLib::uint32 i=0; i < table.getRowCount(); ++i) {
			SBagInitConfig *bagItem = new SBagInitConfig();
			if(bagItem == NULL){
				BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[LOADCONFIG_ERROR][bagItem == NULL]");
				return false;
			}
			bagItem->loadData(table[i]);
			m_bagInitConfigHashMap.setValue(i,bagItem);
		}
	} catch (...){
		BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[LOADCONFIG_ERROR][Exception][%s]", path.c_str());
		return false;
	}
	return true;
}

bool CRoleConfigGMMgr::_loadSkillInitConfig(const std::string& a_configPath)
{
    BSLib::Utility::CStringA configPath = a_configPath;
    configPath += "\\roleInit\\";

	std::string fileName = configPath + "t_skill_init_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

    BSLib::Utility::CStringA path(fileName);

    BSLib::Utility::CTableSheet tableSheet;
    if (!tableSheet.loadXmlFile(path)) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[LOADCONFIG_ERROR]loadXmlFile[%s]", path.c_str());
        return false;
    }
    try {
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "加载角色背包数据配置[%s]", path.c_str());
        BSLib::Utility::CTable& table = tableSheet["item"];
        for (BSLib::uint32 i=0; i < table.getRowCount(); ++i) {
            BSLib::uint32 roleTPID = 0;
            table[i]["f_profession"] >> roleTPID;
            SSkillInitConfig *skillItem = NULL;
            m_skillInitConfigHashMap.getValue(roleTPID,skillItem);
            if(NULL == skillItem){
                skillItem = new SSkillInitConfig();
                skillItem->m_roleTPID = roleTPID;
                m_skillInitConfigHashMap.setValue(roleTPID,skillItem);
            }
        
            if(skillItem == NULL){
                BSLIB_LOG_ERROR(ETT_GSLIB_PLAYERSYSTEM, "[LOADCONFIG_ERROR][skillItem == NULL]");
                return false;
            }
            SkillTPID skillTPID = 0;
            SkillLevel skillLevel = 0;
            table[i]["f_skill_id"] >> skillTPID;
            table[i]["f_skill_level"] >> skillLevel;
            skillItem->addSkill(skillTPID,skillLevel);
        }
    } catch (...){
        BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "[LOADCONFIG_ERROR][Exception][%s]", path.c_str());
        return false;
    }
    return true;
}

void CRoleConfigGMMgr::_removeVipConfig()
{
    std::map<BSLib::uint32, SVipConfig*>::iterator it = m_roleVipMap.begin();
    for (; it != m_roleVipMap.end(); ++it) {
        SVipConfig* data =  it->second;
        if (data == NULL) {
            continue;
        }
        BSLIB_SAFE_DELETE(data);
    }
    m_roleVipMap.clear();
}

void CRoleConfigGMMgr::_removeBagInitConfig()
{
    BSLib::Utility::CHashMap<BSLib::uint32, SBagInitConfig*>::iterator it = m_bagInitConfigHashMap.begin();
    for (; it != m_bagInitConfigHashMap.end(); ++it) {
        SBagInitConfig* data =  it->second;
        if (data == NULL) {
            continue;
        }
        BSLIB_SAFE_DELETE(data);
    }
    m_bagInitConfigHashMap.clear();
}

void CRoleConfigGMMgr::_removeSkillInitConfig()
{
    BSLib::Utility::CHashMap<BSLib::uint32, SSkillInitConfig*>::iterator it = m_skillInitConfigHashMap.begin();
    for (; it != m_skillInitConfigHashMap.end(); ++it) {
        SSkillInitConfig* data =  it->second;
        if (data == NULL) {
            continue;
        }
        data->clear();
        BSLIB_SAFE_DELETE(data);
    }
    m_bagInitConfigHashMap.clear();
}

}//GM

}//EquipSystem

}//GSLib
