#include <GSLib/skillSystem/GM/skill.h>


namespace GSLib
{

namespace SkillSystem
{

namespace GM
{

CSkill::CSkill(SkillTPID skillID, SkillLevel skillLevel)
:m_skillTPID(skillID)
,m_skillLevel(skillLevel)
{

}

CSkill::~CSkill()
{

}

void CSkill::SerializeTo(BSLib::Utility::CStream &stream) const
{
	stream << m_skillTPID;	
	stream << m_skillLevel;
}

SkillTPID CSkill::getSkillTPID() const
{
	return m_skillTPID;
}

void CSkill::setSkillTPID(SkillTPID a_skillTPID)
{
	m_skillTPID = a_skillTPID;
}

SkillLevel CSkill::getSkillLevel() const
{
	return m_skillLevel;
}

void CSkill::setSkillLevel(SkillLevel skillLevel)
{
	m_skillLevel = skillLevel;
}



}//GM
}//SKillSystem
}//GSLib







