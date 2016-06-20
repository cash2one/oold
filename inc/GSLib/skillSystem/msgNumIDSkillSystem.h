//////////////////////////////////////////////////////////////////////
//	created:	2014/09/09
//	filename: 	GSLib\skillSystem\msgNumIDSkillSystem.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SKILLSYSTEM_MSGNUMIDSKILLSYSTEM_H__
#define __GSLIB_SKILLSYSTEM_MSGNUMIDSKILLSYSTEM_H__

#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace SkillSystem
{
enum EMsgNumIDSkillSystem
{
	EMSGNUMID_SKILLSYSTEM_GC2GM_REQ_LEARN_SKILL = 1,
	EMSGNUMID_SKILLSYSTEM_GM2GC_ACK_LEARN_SKILL = 2,

	EMSGNUMID_SKILLSYSTEM_GC2GM_REQ_UPGRADE_SKILL = 3,
	EMSGNUMID_SKILLSYSTEM_GM2GC_ACK_UPGRADE_SKILL = 4,

	EMSGNUMID_SKILLSYSTEM_GM2GC_REQ_INIT_ROLE_SKILLDATA = 5,
	EMSGNUMID_SKILLSYSTEM_GM2GC_ACK_INIT_ROLE_SKILLDATA = 6,

	EMSGNUMID_SKILLSYSTEM_GC2GM_REQ_SET_SKILL_BUTTON = 7,
	EMSGNUMID_SKILLSYSTEM_GC2GM_ACK_SET_SKILL_BUTTON = 8,

};
}//SkillSystem
}//GSLib

#endif//__GSLIB_SKILLSYSTEM_MSGNUMIDSKILLSYSTEM_H__
