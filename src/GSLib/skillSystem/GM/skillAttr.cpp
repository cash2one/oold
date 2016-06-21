#include <GSLib/skillSystem/GM/skillAttr.h>
#include <GSLib/skillSystem/GM/skillLevel.h>

namespace GSLib
{

namespace SkillSystem
{

namespace GM
{
CSkillAttr::CSkillAttr()
:m_skillID(0)
,m_roleTPID(0)
,m_maxSkillLevel(0)
,m_skillLearnRequiredLevel(0)
{
}

CSkillAttr::~CSkillAttr()
{
}

void CSkillAttr::setTPID(GSLib::SkillTPID a_skillTPID)
{
	m_skillID = a_skillTPID;
}

GSLib::SkillTPID CSkillAttr::getTPID()const
{
	return m_skillID;
}


void CSkillAttr::setRoleTPID(BSLib::uint32 a_roleTPID)
{
	m_roleTPID = a_roleTPID;
}

BSLib::uint32 CSkillAttr::getRoleTPID() const
{
	return m_roleTPID;
}

BSLib::uint32 CSkillAttr::getRequiredGold(BSLib::uint32 a_requireLeve, BSLib::uint32 a_getSkillLevel) const
{
	//(技能学习等级+强化目标等级*5)^2*10
	return (a_requireLeve + a_getSkillLevel * 5) * (a_requireLeve + a_getSkillLevel * 5) * 10;
}

}//GM

}//SKillSystem

}//GSLib





