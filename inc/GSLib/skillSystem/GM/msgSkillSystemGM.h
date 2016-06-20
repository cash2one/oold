//////////////////////////////////////////////////////////////////////
//	created:	2014/09/09
//	filename: 	GSLib\skillSystem\GM\msgSkillSystemGM.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SKILLSYSTEM_MSGSKILLSYSTEMGM_H__
#define __GSLIB_SKILLSYSTEM_MSGSKILLSYSTEMGM_H__

#include <GSLib/skillSystem/msgNumIDSkillSystem.h>

namespace GSLib
{

namespace SkillSystem
{

const BSLib::uint32 MsgIDSkillSystemGC2GMReqLearnSkill = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SKILLPSYSTEM, EMSGNUMID_SKILLSYSTEM_GC2GM_REQ_LEARN_SKILL);
class CMsgSkillSystemGC2GMReqLearnSkill: public GFLib::CMessage
{
public:
	CMsgSkillSystemGC2GMReqLearnSkill()
	:GFLib::CMessage(MsgIDSkillSystemGC2GMReqLearnSkill)
	,m_skillTPID(0)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_skillTPID;
		return true;
	}
public:
	SkillTPID m_skillTPID;
};

const BSLib::uint32 MsgIDSkillSystemGC2GMReqUpgradeSkill = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SKILLPSYSTEM, EMSGNUMID_SKILLSYSTEM_GC2GM_REQ_UPGRADE_SKILL);
class CMsgSkillSystemGC2GMReqUpgradeSkill: public GFLib::CMessage
{
public:
	CMsgSkillSystemGC2GMReqUpgradeSkill()
	:GFLib::CMessage(MsgIDSkillSystemGC2GMReqUpgradeSkill)
	,m_skillTPID(0)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_skillTPID;
		return true;
	}
public:
	SkillTPID m_skillTPID;
};

const BSLib::uint32 MsgIDSkillSystemGC2GMReqInitSkillData = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SKILLPSYSTEM, EMSGNUMID_SKILLSYSTEM_GM2GC_REQ_INIT_ROLE_SKILLDATA);
class CMsgSkillSystemGC2GMReqInitRoleSkillData: public GFLib::CMessage
{
public:
	CMsgSkillSystemGC2GMReqInitRoleSkillData()
	:GFLib::CMessage(MsgIDSkillSystemGC2GMReqInitSkillData)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		return true;
	}
};

const BSLib::uint32 MsgIDSkillSystemGC2GMReqSetSkillButton = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SKILLPSYSTEM, EMSGNUMID_SKILLSYSTEM_GC2GM_REQ_SET_SKILL_BUTTON);
class CMsgSkillSystemGC2GMReqSetSkillButton: public GFLib::CMessage
{
public:
	CMsgSkillSystemGC2GMReqSetSkillButton()
		:GFLib::CMessage(MsgIDSkillSystemGC2GMReqSetSkillButton)
		,m_skillTPID(0)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_skillTPID;
		stream >> m_skillButtonIndex;
		return true;
	}
public:
	SkillTPID m_skillTPID;
	BSLib::uint8 m_skillButtonIndex;
};

}//SkillSystem

}//GSLib

#endif//__GSLIB_SKILLSYSTEM_MSGSKILLSYSTEMGM_H__
