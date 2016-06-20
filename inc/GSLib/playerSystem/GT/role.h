//////////////////////////////////////////////////////////////////////
//	created:	2014/07/29
//	filename: 	GSLib\playerSystem\GM\role.h
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_GM_ROLE_H__
#define __GSLIB_PLAYERSYSTEM_GM_ROLE_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace GM
{

class CRole
{
public:
	CRole();
	CRole(BSLib::uint64 a_roleID,std::string a_roldName);
	virtual ~CRole();

public:
	virtual bool _init();
	virtual void _final();
	
public:
	void inline setRoleID(BSLib::uint64 a_RoleID){ m_nRoleId = a_RoleID;}
	void inline setRoleName(std::string a_strRoleName){ m_strRoleName = a_strRoleName;}

	BSLib::uint64 inline getRoleID(){ return m_nRoleId;}
	std::string inline getRoleName(){ return m_strRoleName;}

	//角色基本属性(一级属性)
	enum CHAR_ATTR_LEVEL1
	{
		CATTR_LEVEL1_STR			=0, //力量  1力量=4物理攻击
		CATTR_LEVEL1_CON			=1,	//体质  1体质=100生命值+4物理防御+4技能防御
		CATTR_LEVEL1_INT			=2,	//智力  1智力=4技能攻击
		CATTR_LEVEL1_DEX			=3,	//敏捷  1敏捷=4暴击+4闪避

		CATTR_LEVEL1_NUMBER, //角色基本属性总数
	};



	//角色二级属性
	enum CHAR_ATTR_LEVEL2
	{
		CATTR_LEVEL2_ATTACKRATE_P =0,	//物理攻击
		CATTR_LEVEL2_DEFENCE_P,			//物理防御
		CATTR_LEVEL2_ATTACKRATE_M,		//技能攻击
		CATTR_LEVEL2_DEFENCE_M,			//技能防御

		CATTR_LEVEL2_ATTCAK_CRIT,       //暴击
		CATTR_LEVEL2_DEFENCE_CRIT,      //暴击抗性
		CATTR_LEVEL2_DAMAGE_CRIT,       //暴击伤害

		CATTR_LEVEL2_DAMAGE_REDUCE,     //减免伤害

		CATTR_LEVEL2_HIT,				//命中机率
		CATTR_LEVEL2_MISS,				//闪避机率

		CATTR_LEVEL2_MAXHP,				//HP上限
		CATTR_LEVEL2_MAXMP,				//MP上限
		CATTR_LEVEL2_RESTOREHP,			//HP回复
		CATTR_LEVEL2_RESTOREMP,			//MP回复


		CATTR_LEVEL2_PHOTONFORCE ,		//光子力

		CATTR_LEVEL2_NUMBER,			//二级属性数量

	};
	// 角色属性
public:
    // 一级属性
	
	// 二级属性

private:
	BSLib::uint64 m_nRoleId;
	std::string   m_strRoleName;

};

}//GM

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GM_ROLE_H__
