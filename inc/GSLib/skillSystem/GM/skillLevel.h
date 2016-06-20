//////////////////////////////////////////////////////////////////////
//	created:	2014/09/12
//	filename: 	GSLib\skillSystem\GM\skillLevel.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////

#ifndef		__GSLIB_SKILLSYSTEM_GM_SKILLLEVEL_H__
#define		__GSLIB_SKILLSYSTEM_GM_SKILLLEVEL_H__

#include <BSLib/utility/baseDef.h>
#include <BSLib/utility/hashMap.h>
#include <GSLib/playerSystem/GM/roleBagModuleGM.h>

namespace GSLib
{

namespace SkillSystem
{

namespace GM
{

class CSkillLevel
{
public:	
	CSkillLevel();
	~CSkillLevel();
public:
	BSLib::uint16 getRequireRoleLevel() const;
	BSLib::uint64 getRequireGold() const;
	BSLib::uint32 getRequirePVPCoin() const;
	BSLib::uint32 getRequireDiamond() const;
	BSLib::uint32 getRequireSkillPoint() const;
public:
	BSLib::uint16 m_skillLevel;
	BSLib::uint16 m_requireRoleLevel;
	BSLib::uint64 m_requireGold;
	BSLib::uint32 m_requirePVPCoin;
	BSLib::uint32 m_requireDiamond;
	BSLib::uint32 m_requireSkillPoint;
};
}//GM

}//SKillSystem

}//GSLib

#endif//__SKILLLEVEL_H__












