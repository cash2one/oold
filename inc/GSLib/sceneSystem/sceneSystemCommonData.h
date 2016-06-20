//////////////////////////////////////////////////////////////////////
//	created:	2015/03/6
//	filename: 	GSLib\sceneSystem\GM\arenaChallengeeData.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef		__GSLIB_SCENESYSTEM_SCENESYSTEMCOMMONDATA_H__
#define		__GSLIB_SCENESYSTEM_SCENESYSTEMCOMMONDATA_H__

#include <BSLib/utility/baseDef.h>
#include <GSLib/baseDef.h>
#include <GFLib/commonServer/baseDef.h>
#include <BSLib/utility/hashMap.h>
#include <GSLib/skillSystem/GM/skill.h>
#include <GSLib/skillSystem/GM/skillDefine.h>

namespace BSLib
{
	namespace Utility
	{
		class CStream;
	};
};

namespace GSLib
{
namespace SceneSystem
{

//////////////////////////////////////////////////////////////////////////
class CArenaChallengeeData
{
public:
	CArenaChallengeeData();
	~CArenaChallengeeData();
public:
	void	serializeFrom(BSLib::Utility::CStream& stream);
	void 	serializeTo(BSLib::Utility::CStream& stream) const;
public:
	BSLib::uint16 m_zoneID;
	GFLib::AccountID m_accountID;
	BSLib::uint32 m_roleIndex;
	std::string m_roleName;
	BSLib::uint32 m_roleTPID;
	BSLib::uint32 m_level;
	BSLib::uint32 m_rank;
	BSLib::uint32 m_combatPower;
};

//////////////////////////////////////////////////////////////////////////
class CArenaChallengeRecord
{
public:
	CArenaChallengeRecord();
	~CArenaChallengeRecord();
public:
	void serializeTo(BSLib::Utility::CStream& stream) const;
	void serializeFrom(BSLib::Utility::CStream& stream);
public:
	BSLib::uint64 m_recordID;
	bool m_isActive;
	bool m_isWin;
	BSLib::int32 m_challengeTime;
	BSLib::uint32 m_newRank;
	BSLib::int32 m_changedRank;
	BSLib::uint16 m_challengeeZoneID;
	GFLib::AccountID m_challengeeAccountID;
	BSLib::uint32 m_challengeeRoleIndex;
	BSLib::uint32 m_challengeeTPID;
	std::string m_challengeeName;
	bool m_isRevenged;
};

//////////////////////////////////////////////////////////////////////////
class CBattleRoleData
{
public:
	CBattleRoleData();
	~CBattleRoleData();
public:
	void 	serializeTo(BSLib::Utility::CStream&  a_stream) const;
public:
	BSLib::uint16 m_zoneID;
	GFLib::AccountID m_accountID;
	BSLib::uint32 m_roleIndex;
	BSLib::uint32 m_roleTPID;
	std::string m_roleName;
	BSLib::uint32 m_level;
	BSLib::uint32 m_combatPower;
	SBattleAttribute m_battleAttr;
	BSLib::Utility::CHashMap<SkillTPID, GSLib::SkillSystem::GM::CSkill>	m_skills;
	SkillTPID m_skillButtons[SkillSystem::GM::SKILL_BOTTON_COUNT];
};




}//SceneSystem

}//GSLib






#endif



















