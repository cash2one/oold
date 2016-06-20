//////////////////////////////////////////////////////////////////////
//	created:	2014/07/29
//	filename: 	src\GSLib\playerSystem\GM\roleResource.cpp
//	author:	    zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/playerSystem/GM/roleResource.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace GM
{

SRoleResource::SRoleResource()
:m_gold(0)
,m_exp(0)
,m_bagSize(0)
,m_quality(0)
,m_starLevel(0)
,m_pvpCoin(0)
,m_chargeDiamond(0)
,m_bindDiamond(0)
,m_skillpoint(0)
,m_pop(0)
,m_vitality(0)
,m_sceneID(0)
,m_level(0)
,m_hp(0)
,m_sp(0)
,m_vipScore(0)
,m_vipLevel(0)
,m_activeDegree(0)
,m_totalChargeDiamond(0)
,m_totalUseChargeDiamond(0)
,m_totalUseBindDiamond(0)
,m_lightPower(0)
{

}

bool  SRoleResource::updateGold(BSLib::uint64 value)
{
	setGold(value);
	return  true;
}

bool  SRoleResource::updateExp(BSLib::uint64 value)
{
	setExp(value);
	return  true;
}

void SRoleResource::setGold(BSLib::uint64 a_gold)
{
	m_gold = a_gold;
}

void SRoleResource::setExp(BSLib::uint64 a_exp)
{
	m_exp = a_exp;
}

void SRoleResource::setLightPower(BSLib::uint32 a_lightPower)
{
	m_lightPower = a_lightPower;
}

BSLib::uint32 SRoleResource::getValue(ERoleResID a_resID) const
{
    switch(a_resID)
    {
    case ATTR_BAG_SIZE:              return m_bagSize;
    case ATTR_SCENEID:               return m_sceneID;
    case ATTR_QUALITY:               return m_quality;
    case ATTR_STARLEVEL:             return m_starLevel;
    case ATTR_PVPCOIN:               return m_pvpCoin;

    case ATTR_DIAMOND:               return m_bindDiamond + m_activeDegree;
    case ATTR_POP:                   return m_pop;
    case ATTR_VITALITY:              return m_vitality;
    case ATTR_SKILLPOINT:            return m_skillpoint;

    case ATTR_LEVEL:                 return m_level;
    case ATTR_HP:                    return m_hp;
    case ATTR_SP:                    return m_sp;

    case ATTR_VIP_SCORE:             return m_vipScore;
    case ATTR_VIP_LEVEL:             return m_vipLevel;
    case ATTR_ACTIVE_DEGREE:         return m_activeDegree;

    case ATTR_CHARGE_DIAMOND:        return m_chargeDiamond;
    case ATTR_BIND_DIAMOND:          return m_bindDiamond;

    case ATTR_TotalUseChargeDiamond: return m_totalUseChargeDiamond;
    case ATTR_TotalUseBindDiamond:   return m_totalUseBindDiamond;
    case ATTR_TotalChargeDiamond:    return m_totalChargeDiamond;
	case ATTR_LIGHT_POWER:			 return m_lightPower;

    default:                     return 0;
    }
}

void SRoleResource::setValue(ERoleResID a_resID,BSLib::uint32 a_value)
{
    switch(a_resID)
    {
    case ATTR_BAG_SIZE:              m_bagSize        = a_value; break;
    case ATTR_SCENEID:               m_sceneID        = a_value; break;
    case ATTR_QUALITY:               m_quality        = a_value; break;
    case ATTR_STARLEVEL:             m_starLevel      = a_value; break;
    case ATTR_PVPCOIN:               m_pvpCoin        = a_value; break;

    case ATTR_POP:                   m_pop            = a_value; break;
    case ATTR_VITALITY:              m_vitality       = a_value; break;
    case ATTR_SKILLPOINT:            m_skillpoint     = a_value; break;

    case ATTR_LEVEL:                 m_level          = a_value; break;
    case ATTR_HP:                    m_hp             = a_value; break;
    case ATTR_SP:                    m_sp             = a_value; break;

    case ATTR_VIP_SCORE:             m_vipScore       = a_value; break;
    case ATTR_VIP_LEVEL:             m_vipLevel       = a_value; break;
    case ATTR_ACTIVE_DEGREE:         m_activeDegree   = a_value; break;

    case ATTR_CHARGE_DIAMOND:        m_chargeDiamond  = a_value; break;
    case ATTR_BIND_DIAMOND:          m_bindDiamond    = a_value; break;
	case ATTR_LIGHT_POWER:			 m_lightPower     = a_value; break;

    case ATTR_TotalUseChargeDiamond: m_totalUseChargeDiamond = a_value; break;
    case ATTR_TotalUseBindDiamond:   m_totalUseBindDiamond = a_value; break;
    case ATTR_TotalChargeDiamond:    m_totalChargeDiamond = a_value; break;
    case ATTR_DIAMOND:      
        {
            BSLib::uint32 totalDiamond = getValue(ATTR_DIAMOND);
            if(totalDiamond < a_value){
                BSLib::uint32 add = a_value - totalDiamond;
                BSLib::uint32 newDiamond = getValue(ATTR_BIND_DIAMOND) + add;
                setValue(ATTR_BIND_DIAMOND,newDiamond);
            }
            else if(totalDiamond > a_value){
                BSLib::uint32 change = totalDiamond - a_value;
                BSLib::uint32 bindDiamond = getValue(ATTR_BIND_DIAMOND);
                if(bindDiamond >= change){
                    BSLib::uint32 newBindDiamond = bindDiamond - change;
                    setValue(ATTR_BIND_DIAMOND,newBindDiamond);
                }
                else{
                    BSLib::uint32 bindDiamond = getValue(ATTR_BIND_DIAMOND);
                    setValue(ATTR_BIND_DIAMOND,0);
                    BSLib::uint32 newChargeDiamond = getValue(ATTR_CHARGE_DIAMOND) - change + bindDiamond; 
                    setValue(ATTR_CHARGE_DIAMOND,newChargeDiamond);
                }
            }
            else{
                ;
            }
        }
        break;

    default:;break;
    }
}

BSLib::uint64 SRoleResource::getGold() const
{
	return m_gold;
}

BSLib::uint64 SRoleResource::getExp() const
{
	return m_exp;
}

BSLib::uint32 SRoleResource::getLightPower() const
{
	return m_lightPower;
}

}//GM

}//PlayerSystem

}//GSLib
