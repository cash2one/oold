//////////////////////////////////////////////////////////////////////
//	created:	2014/07/29
//	filename: 	src\GSLib\playerSystem\CN\CRoleBaseInfoCN.cpp
//	author:	    zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/tracer.h>
#include <GSLib/playerSystem/CN/roleBaseInfoCN.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace CN
{



CRoleBaseInfoCN::CRoleBaseInfoCN(GSLib::RoleID a_roleID,const std::string& a_roldName,const GSLib::SRoleKey& a_roleKey)
:m_roleKey(a_roleKey)
{
    m_roleData.m_roleID = a_roleID; 
    BSLibSprintf(m_roleData.m_roleName,sizeof(char)*(GSLIB_TEXT_MAX_ROLE_NAME + 1),"%s",a_roldName.c_str());
}

CRoleBaseInfoCN::CRoleBaseInfoCN()
{
}

CRoleBaseInfoCN::~CRoleBaseInfoCN()
{
	;
}

void CRoleBaseInfoCN::init(const DB::SRoleData& a_roleData)
{
    memcpy(&m_roleData, (void*)&a_roleData, sizeof(a_roleData));
}

void CRoleBaseInfoCN::update(const DB::SRoleData& a_roleData)
{
    memcpy(&m_roleData, (void*)&a_roleData, sizeof(a_roleData));
}

bool CRoleBaseInfoCN::serializeTo(BSLib::Utility::CStream& a_stream) const 
{
    a_stream.reset();
    a_stream << m_roleData.m_accountID;
    a_stream << m_roleData.m_zoneID;
    a_stream << m_roleData.m_roleIndex;
    
    std::string roleName = m_roleData.m_roleName;
    a_stream << roleName;
    a_stream << m_roleData.m_roleTPID;
    a_stream << m_roleData.m_roleID;
    a_stream << m_roleData.m_roleLevel;

    a_stream << m_roleData.m_roleEXP;
    a_stream << m_roleData.m_gold;
	a_stream << m_roleData.m_lightPower;
    a_stream << m_roleData.m_quality;
    a_stream << m_roleData.m_starLevel;
    a_stream << m_roleData.m_PVPCoin;
    a_stream << m_roleData.m_chargeDiamond;
    a_stream << m_roleData.m_bindDiamond;
    a_stream << m_roleData.m_skillPoint;

    a_stream << m_roleData.m_rolePOP;
    a_stream << m_roleData.m_vitality;
    

    a_stream << m_roleData.m_sceneID;

    a_stream << m_roleData.m_vipLevel; 
    a_stream << m_roleData.m_vipScore;
    a_stream << m_roleData.m_activeDegree;

    // 战斗属性
    a_stream << m_roleData.m_atk;
    a_stream << m_roleData.m_def;

    a_stream << m_roleData.m_atkCrift;
    a_stream << m_roleData.m_defCrift;

    a_stream << m_roleData.m_hitRate;
    a_stream << m_roleData.m_missRate;
    a_stream << m_roleData.m_maxHP;
    // 战斗力
    a_stream << m_roleData.m_combat;
	a_stream << m_roleData.m_historyMaxCombatPower;

    return true;
}

bool CRoleBaseInfoCN::serializeFrom(BSLib::Utility::CStream& stream)
{	
    stream >> m_roleKey;
    return true;
}

void CRoleBaseInfoCN::getBattleAttr(SBattleAttribute& a_battleAttr)
{
     a_battleAttr.m_atk = m_roleData.m_atk;
     a_battleAttr.m_def= m_roleData.m_def;
     a_battleAttr.m_atkCrift = m_roleData.m_atkCrift;

     a_battleAttr.m_defCrift = m_roleData.m_defCrift;
     a_battleAttr.m_hitRate = m_roleData.m_hitRate;

     a_battleAttr.m_missRate = m_roleData.m_missRate;
     a_battleAttr.m_maxHP = m_roleData.m_maxHP;
}


}//CN

}//PlayerSystem

}//GSLib
