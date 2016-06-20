//////////////////////////////////////////////////////////////////////
//	created:	2014/09/12
//	filename: 	GSLib\skillSystem\GM\skillLevel.cpp
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/skillSystem/GM/skillLevel.h>

namespace GSLib
{

namespace SkillSystem
{

namespace GM
{

CSkillLevel::CSkillLevel()
:m_skillLevel(0)
,m_requireRoleLevel(0)
,m_requireGold(0)
,m_requirePVPCoin(0)
,m_requireDiamond(0)
,m_requireSkillPoint(0)
{
}

CSkillLevel::~CSkillLevel()
{
}

BSLib::uint16 CSkillLevel::getRequireRoleLevel() const
{
	return m_requireRoleLevel;
}

BSLib::uint64 CSkillLevel::getRequireGold() const
{
	return m_requireGold;
}

BSLib::uint32 CSkillLevel::getRequirePVPCoin() const
{
	return m_requirePVPCoin;
}

BSLib::uint32 CSkillLevel::getRequireDiamond() const
{
	return m_requireDiamond;
}

BSLib::uint32 CSkillLevel::getRequireSkillPoint() const
{
	return m_requireSkillPoint;
}

}//GM

}//SKillSystem

}//GSLib






