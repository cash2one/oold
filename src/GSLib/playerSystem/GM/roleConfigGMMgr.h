
#ifndef __GSLIB_PLAYERSYSTEM_GM_GEMGMMGR_H__
#define __GSLIB_PLAYERSYSTEM_GM_GEMGMMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/memory/objectMgr.h>
#include <GFLib/commonServer/commonSystem.h>
#include "roleDataGM.h"
#include <GSLib/playerSystem/GM/roleBagModuleGM.h>
namespace GSLib
{

namespace PlayerSystem
{

namespace GM
{

struct SRoleInitConfig{
	BSLib::uint32 m_roleLevel;
	BSLib::uint32 m_roleDiamond;
	BSLib::uint32 m_rolePVPCoin;
	BSLib::uint32 m_roleVitality;
	BSLib::uint32 m_rolePOP;
	BSLib::uint32 m_roleSkillPoint;
	BSLib::uint64 m_roleGold;
	BSLib::uint64 m_roleExp;
	
	SRoleInitConfig(){
		m_roleLevel = 1;
		m_roleDiamond = 0;
		m_rolePVPCoin = 0;
		m_roleVitality = 0;
		m_roleSkillPoint = 0;
		m_rolePOP = 0;
		m_roleGold=0;
		m_roleExp=0;
	}
};

class CRoleConfigGMMgr
{
public:
	CRoleConfigGMMgr();
	virtual ~CRoleConfigGMMgr();

    BSLIB_SINGLETON_DECLARE(CRoleConfigGMMgr);
	void init();
	void final();
	bool loadGameConfig(const std::string& a_configPath);

public:
    bool getVipScore(BSLib::uint32 a_level,BSLib::uint32& a_vipScore) const;
    bool getVipGift(BSLib::uint32 a_level,std::string& a_vipGift) const;
    SVipConfig* getVipConfig(BSLib::uint32 a_level) const;

    bool getUpgradeExp(BSLib::uint32 a_level,BSLib::uint64& a_exp) const;
    bool getUpgradeVipLevel(BSLib::uint32 a_oldVipLevel,BSLib::uint32 a_vipScore,BSLib::uint32& a_vipLevel) const;
    bool getUpgradeLevels(BSLib::uint32 a_level,BSLib::uint64 a_exp,BSLib::uint32& a_upgradeCount,BSLib::uint64& a_leftExp) const;

public:
	const SRoleInitConfig& getRoleInitConfig() const;
	BSLib::Utility::CHashMap<BSLib::uint32, SBagInitConfig*> getBagInitConfig() const;
    SSkillInitConfig* getSkillInitConfig(BSLib::uint32 a_roleTPID) const;

private:
    bool _loadVipConfig(const std::string& a_configPath);
	bool _loadRoleInitConfig(const std::string& a_configPath);
	bool _loadBagInitConfig(const std::string& a_configPath);
    bool _loadSkillInitConfig(const std::string& a_configPath);

    void _removeVipConfig();
    void _removeBagInitConfig();
    void _removeSkillInitConfig();

private:
	SRoleInitConfig m_roleInitConfig;
	std::map<BSLib::uint32, BSLib::uint64> m_roleLevelExpMap;
    std::map<BSLib::uint32, SVipConfig*> m_roleVipMap;
	BSLib::Utility::CHashMap<BSLib::uint32, SBagInitConfig*> m_bagInitConfigHashMap;
    BSLib::Utility::CHashMap<BSLib::uint32, SSkillInitConfig*> m_skillInitConfigHashMap;
};

}//GM

}//EquipSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GM_GEMGMMGR_H__

