#ifndef __GSLIB_SKILLSYSTEM_MSGSKILLSYSTEMGC_H__
#define __GSLIB_SKILLSYSTEM_MSGSKILLSYSTEMGC_H__

#include <GSLib/skillSystem/msgNumIDSkillSystem.h>
#include <GSLib/skillSystem/GM/skillError.h>
#include <GSLib/skillSystem/GM/skill.h>
#include <GSLib/skillSystem/GM/skillDefine.h>

namespace GSLib
{

namespace SkillSystem
{
const BSLib::uint32 MsgIDSkillSystemGM2GCAckLearnSkill = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SKILLPSYSTEM, EMSGNUMID_SKILLSYSTEM_GM2GC_ACK_LEARN_SKILL);
class CMsgSkillSystemGM2GCAckLearnSkill: public GFLib::CMessage
{
public:
	CMsgSkillSystemGM2GCAckLearnSkill() 
	 :GFLib::CMessage(MsgIDSkillSystemGM2GCAckLearnSkill)
	 ,m_result(SkillSystem::GM::LEARN_SKILL_ERROR_FAIL)
	 ,m_skillTPID(0)
	{
		;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_result;
		stream << m_skillTPID;
		return true;
	}
public:
	BSLib::int8 m_result;
	GSLib::SkillTPID m_skillTPID;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCAckUpgradeSkill = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SKILLPSYSTEM, EMSGNUMID_SKILLSYSTEM_GM2GC_ACK_UPGRADE_SKILL);
class CMsgSkillSystemGM2GCAckUpgradeSkill: public GFLib::CMessage
{
public:
	CMsgSkillSystemGM2GCAckUpgradeSkill()
	:GFLib::CMessage(MsgIDPlayerSystemGM2GCAckUpgradeSkill)
	,m_result(SkillSystem::GM::UPGRADE_SKILL_ERROR_FAIL)
	,m_skillTPID(0)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_result;
		stream << m_skillTPID;
		return true;
	}
public:
	BSLib::int8 m_result;
	GSLib::SkillTPID m_skillTPID;
};

const BSLib::uint32 MsgIDSkillSystemGM2GCAckInitRoleSkillData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SKILLPSYSTEM, EMSGNUMID_SKILLSYSTEM_GM2GC_ACK_INIT_ROLE_SKILLDATA);
class CMsgSkillSystemGM2GCAckInitRoleSkillData: public GFLib::CMessage
{
public:
	CMsgSkillSystemGM2GCAckInitRoleSkillData() : GFLib::CMessage(MsgIDSkillSystemGM2GCAckInitRoleSkillData)
	{
		memset(m_skillButtons, 0, sizeof(m_skillButtons));
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::uint16)m_skills.size();
		if (m_skills.size() > 0) {
			for (BSLib::Utility::CHashMap<SkillTPID, GSLib::SkillSystem::GM::CSkill*>::const_iterator itr = m_skills.begin(); itr != m_skills.end(); ++itr) {
				if (itr->second != NULL) {
					itr->second->SerializeTo(stream);
				}
			}
		}
		for (BSLib::int32 i = 0; i < GM::SKILL_BOTTON_COUNT; ++i) {
			stream << m_skillButtons[i];
		}

		return true;
	}

public:
	BSLib::Utility::CHashMap<SkillTPID, GSLib::SkillSystem::GM::CSkill*>	m_skills;
	SkillTPID m_skillButtons[GM::SKILL_BOTTON_COUNT];
};

const BSLib::uint32 MsgIDSkillSystemGM2GCAckSetSkillButton = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SKILLPSYSTEM, EMSGNUMID_SKILLSYSTEM_GC2GM_ACK_SET_SKILL_BUTTON);
class CMsgSkillSystemGM2GCAckSetSkillButton: public GFLib::CMessage
{
public:
	CMsgSkillSystemGM2GCAckSetSkillButton() 
		:GFLib::CMessage(MsgIDSkillSystemGM2GCAckSetSkillButton)
		,m_result(SkillSystem::GM::SET_SKILL_BUTTON_FAIL)
	{
		memset(m_skillButtons, 0, sizeof(m_skillButtons));
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_result;
		if (m_result == GM::SET_SKILL_BUTTON_SUCCESS) {
			for (BSLib::int32 i = 0; i < GM::SKILL_BOTTON_COUNT; ++i) {
				stream << m_skillButtons[i];
			}
		}

		return true;
	}
public:
	BSLib::int8 m_result;
	SkillTPID m_skillButtons[GM::SKILL_BOTTON_COUNT];
};

}//SkillSystem

}//GSLib

#endif//__GSLIB_SKILLSYSTEM_MSGSKILLSYSTEMGC_H__

