//////////////////////////////////////////////////////////////////////
//	created:	2014/07/28
//	filename: 	GSLib\loginSystem\GM\netPlayerGMMgr.h
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_GM_ROLEATTRIBUTEGMMGR_H__
#define __GSLIB_PLAYERSYSTEM_GM_ROLEATTRIBUTEGMMGR_H__

#include <GSLib/playerSystem/GM/roleResource.h>
#include <GSLib/baseDef.h>
namespace GSLib
{

namespace PlayerSystem
{

namespace GM
{

//无效的ID值
#define INVALIDID		-1

// 角色职业
typedef enum
{
    PRO_NULL = 0,
    PRO_ZJIANG = 1,    // Z酱
    PRO_KELEIJIANG,    // 克蕾酱
    PRO_GULANDAISA,    // 古兰戴萨
    PRO_MAX,     
}ProfessionType;

// 角色状态
typedef enum
{
    STATUS_NULL = 0,     // 未知
    STATUS_ACTIVE = 1,     // 激活
    STATUS_INACTIVE = 2,   // 未激活
    STATUS_LOADING = 3,	 // 正在加载数据
}ERoleStatus;

typedef enum
{
    ATTR_VIP_SCORE=1,
    ATTR_ACTIVE_DEGREE=2,
    ATTR_BAG_SIZE=3,
    ATTR_SCENEID=4,
    ATTR_QUALITY=5,               // 角色品级
    ATTR_STARLEVEL=6,             // 角色星级
    ATTR_PVPCOIN=7,
    ATTR_DIAMOND=8,

    ATTR_POP=9,
    ATTR_VITALITY=10,
    ATTR_SKILLPOINT=11,   // 技能点
    ATTR_LEVEL=12,
    ATTR_HP=13,
    ATTR_SP=14,
    ATTR_VIP_LEVEL=15,
    ATTR_TotalUseChargeDiamond=16,
    ATTR_TotalUseBindDiamond=17,
    ATTR_TotalChargeDiamond=18,
    ATTR_CHARGE_DIAMOND=19,           // 充值宝石
    ATTR_BIND_DIAMOND=20,             // 绑定宝石
    ATTR_MAX_VITALITY=21,             // 体力上限

    ATTR_EXP=116,
    ATTR_GOLD=117,
	ATTR_LIGHT_POWER = 118,

}ERoleResID;

struct SRoleResource
{
public:
    SRoleResource();

public:
    bool updateUInt64Value(ERoleResID a_resID,BSLib::uint64 value);
    void setValue(ERoleResID m_attributeID,BSLib::uint32 value);

    bool updateGold(BSLib::uint64 value);
    bool updateExp(BSLib::uint64 value);

    void setGold(BSLib::uint64 a_gold);
    void setExp(BSLib::uint64 a_exp);

	void setLightPower(BSLib::uint32 a_lightPower);

public:
    BSLib::uint32 getValue(ERoleResID m_attributeID) const;

    BSLib::uint64 getExp() const;
    BSLib::uint64 getGold() const;

	BSLib::uint32 getLightPower() const;

private:
    BSLib::uint32 m_bagSize;
    BSLib::uint32 m_quality;
    BSLib::uint32 m_starLevel;
    BSLib::uint32 m_pvpCoin;
    BSLib::uint32 m_chargeDiamond;
    BSLib::uint32 m_bindDiamond;
    BSLib::uint32 m_skillpoint;
    BSLib::uint32 m_pop;
    BSLib::uint32 m_vitality;
    BSLib::uint32 m_level;
    BSLib::uint32 m_hp;
    BSLib::uint32 m_sp;
    
    BSLib::uint32 m_vipLevel;
    BSLib::uint32 m_vipScore;
    BSLib::uint32 m_activeDegree;

    BSLib::uint32 m_totalUseChargeDiamond;
    BSLib::uint32 m_totalUseBindDiamond;
    BSLib::uint32 m_totalChargeDiamond;

    BSLib::uint64 m_exp;
    BSLib::uint64 m_gold;
    BSLib::uint32 m_sceneID;

	BSLib::uint32 m_lightPower;
};

}//GM

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GM_ROLEATTRIBUTEGMMGR_H__