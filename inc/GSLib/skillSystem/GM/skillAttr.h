//////////////////////////////////////////////////////////////////////
//	created:	2014/09/12
//	filename: 	GSLib\skillSystem\GM\skillAttr.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef		__GSLIB_SKILLSYSTEM_GM_SKILLATTR_H__
#define		__GSLIB_SKILLSYSTEM_GM_SKILLATTR_H__

#include <GSLib/baseDef.h>
#include <string>

namespace GSLib
{

namespace SkillSystem
{

namespace GM
{
class CSkillLevel;

class CSkillAttr
{
public:
	CSkillAttr();
	~CSkillAttr();
public:
	void setTPID(GSLib::SkillTPID a_skillTPID);
	GSLib::SkillTPID getTPID()const;

	void setSkillName(std::string a_skillName);
	std::string getSkillName()const;

	void setRoleTPID(BSLib::uint32 a_roleTPID);
	BSLib::uint32 getRoleTPID() const;

	BSLib::uint32 getRequiredGold(BSLib::uint32 a_requireLeve, BSLib::uint32 a_skillLevel) const;
public:
	GSLib::SkillTPID m_skillID;
	BSLib::uint32 m_roleTPID;
	BSLib::uint32 m_maxSkillLevel;
	BSLib::uint32 m_skillLearnRequiredLevel;
};
}//GM

}//SKillSystem

}//GSLib








#endif	//__SKILLATTR_H__

