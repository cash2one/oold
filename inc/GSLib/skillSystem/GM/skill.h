#ifndef		__GSLIB_SKILLSYSTEM_GM_SKILL_H__
#define		__GSLIB_SKILLSYSTEM_GM_SKILL_H__

#include <GSLib/baseDef.h>
#include <BSLib/utility/stream.h>

namespace GSLib
{

namespace SkillSystem
{

namespace GM
{

class CSkill
{
public:
	CSkill(SkillTPID skillID = 0, SkillLevel skillLevel = 0);
	~CSkill();
public:
	void SerializeTo(BSLib::Utility::CStream &stream) const;
public:
	SkillTPID getSkillTPID() const;
	void setSkillTPID(SkillTPID a_skillTPID) ;

	SkillLevel getSkillLevel() const;
	void setSkillLevel(SkillLevel skillLevel);
private:
	SkillTPID m_skillTPID;
	SkillLevel m_skillLevel;
};

}//GM

}//SKillSystem

}//GSLib



#endif


