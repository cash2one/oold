#ifndef __GSLIB_PLAYERSYSTEM_CN_ROLEBASEINFOCN_H__
#define __GSLIB_PLAYERSYSTEM_CN_ROLEBASEINFOCN_H__
#include <GSLib/baseDef.h>
#include <BSLib/utility/memory/objectMgr.h>
#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/playerSystem/CN/roleModuleCN.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace CN
{

class CRoleBaseInfoCN
{
public:
	CRoleBaseInfoCN(GSLib::RoleID a_roleID,const std::string& a_roldName,const GSLib::SRoleKey& a_roleKey);
    CRoleBaseInfoCN();
	virtual ~CRoleBaseInfoCN();

    void init(const GSLib::PlayerSystem::DB::SRoleData& a_roleData);
    void update(const GSLib::PlayerSystem::DB::SRoleData& a_roleData);

public:
    bool serializeTo(BSLib::Utility::CStream& a_stream) const;
    bool serializeFrom(BSLib::Utility::CStream& stream);

public:
	const GSLib::SRoleKey& getRoleKey() const { return m_roleKey; }
    RoleID getRoleID() const { return m_roleData.m_roleID; }
	
    BSLib::uint32 getRoleTPID() const {return m_roleData.m_roleTPID;}
    BSLib::uint32 getRoleLevel() const {return m_roleData.m_roleLevel;}

    std::string getRoleName() const { return m_roleData.m_roleName;}

    BSLib::uint32 getVipLevel() const { return m_roleData.m_vipLevel;}
    BSLib::uint32 getVipScore() const { return m_roleData.m_vipScore;}

    BSLib::uint64 getRoleExp() const {return m_roleData.m_roleEXP;}
    BSLib::uint64 getGold() const {return m_roleData.m_gold;}
    BSLib::uint32 getVitality() const {return m_roleData.m_vitality;}
    BSLib::uint32 getChargeDiamond() const {return m_roleData.m_chargeDiamond;}
    BSLib::uint32 getBindDiamond() const {return m_roleData.m_bindDiamond;}

    BSLib::uint32 getPVPCoin() const {return m_roleData.m_PVPCoin;}
    BSLib::uint32 getRolePOP() const {return m_roleData.m_rolePOP;}
    BSLib::uint32 getCombat() const {return m_roleData.m_combat;}
    BSLib::uint64 getCreateTime() const {return m_roleData.m_createTime;}

    void getBattleAttr(SBattleAttribute& a_battleAttr);

private:
	GSLib::SRoleKey m_roleKey;
    DB::SRoleData m_roleData;
    
};

}//CN

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_CN_ROLEBASEINFOCN_H__

