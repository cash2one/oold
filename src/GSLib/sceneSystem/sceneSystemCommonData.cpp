#include <GSLib/sceneSystem/sceneSystemCommonData.h>
#include <BSLib/utility/stream.h>
#include <GSLib/skillSystem/GM/skill.h>

namespace GSLib
{

namespace SceneSystem
{

CArenaChallengeeData::CArenaChallengeeData()
:m_zoneID(0)
,m_accountID(10001)
,m_roleIndex(0)
,m_roleName("")
,m_roleTPID(0)
,m_level(0)
,m_rank(0)
,m_combatPower(0)
{
}

CArenaChallengeeData::~CArenaChallengeeData()
{

}

void CArenaChallengeeData::serializeFrom(BSLib::Utility::CStream& stream)
{

	stream >> m_zoneID;
	stream >> m_accountID;
	stream >> m_roleIndex;
	stream >> m_roleName;
	stream >> m_roleTPID;
	stream >> m_level;
	stream >> m_rank;
	stream >> m_combatPower;
}

void CArenaChallengeeData::serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_zoneID;
	stream << m_accountID;
	stream << m_roleIndex;
	stream << m_roleName;
	stream << m_roleTPID;
	stream << m_level;
	stream << m_rank;
	stream << m_combatPower;
}

///////////////////////////////////////////////////////////////////
CArenaChallengeRecord::CArenaChallengeRecord()
:m_recordID(0)
,m_isActive(false)
,m_isWin(false)
,m_challengeTime(0)
,m_newRank(0)
,m_changedRank(0)
,m_challengeeZoneID(0)
,m_challengeeAccountID(0)
,m_challengeeRoleIndex(0)
,m_challengeeTPID(0)
,m_challengeeName("")
,m_isRevenged(0)
{

}

CArenaChallengeRecord::~CArenaChallengeRecord()
{

}

void CArenaChallengeRecord::serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_recordID;
	stream << m_isActive;
	stream << m_isWin;
	stream << m_challengeTime;
	BSLib::Utility::CDateTime time;
	BSLib::int32 timeElapsed = (BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds() - m_challengeTime; 
	timeElapsed = timeElapsed > 0 ? timeElapsed : 0;
	stream << timeElapsed;
	stream << m_newRank;
	stream << m_changedRank;
	stream << m_challengeeZoneID;
	stream << m_challengeeAccountID;
	stream << m_challengeeRoleIndex;
	stream << m_challengeeTPID;
	stream << m_challengeeName;
	stream << m_isRevenged;
}

void CArenaChallengeRecord::serializeFrom(BSLib::Utility::CStream& stream)
{
	stream >> m_recordID;
	stream >> m_isActive;
	stream >> m_isWin;
	stream >> m_challengeTime;
	BSLib::int32 timeElapsed = 0;
	stream >> timeElapsed;
	stream >> m_newRank;
	stream >> m_changedRank;
	stream >> m_challengeeZoneID;
	stream >> m_challengeeAccountID;
	stream >> m_challengeeRoleIndex;
	stream >> m_challengeeTPID;
	stream >> m_challengeeName;
	stream >> m_isRevenged;
}

//////////////////////////////////////////////////////////////////
CBattleRoleData::CBattleRoleData()
:m_zoneID(0)
,m_accountID(0)
,m_roleIndex(0)
,m_roleTPID(0)
,m_roleName("")
,m_level(0)
,m_combatPower(0)
{
	for (BSLib::int32 i = 0; i < SkillSystem::GM::SKILL_BOTTON_COUNT; ++i) {
		m_skillButtons[i] = 0;
	}
}

CBattleRoleData::~CBattleRoleData()
{

}

void CBattleRoleData::serializeTo(BSLib::Utility::CStream& a_stream) const
{
	a_stream << m_zoneID;
	a_stream << m_accountID;
	a_stream << m_roleIndex;
	a_stream << m_roleTPID;
	a_stream << m_roleName;
	a_stream << m_level;
	a_stream << m_combatPower;
	m_battleAttr.serializeTo(a_stream);
	a_stream << (BSLib::uint16)m_skills.size();
	if (m_skills.size() > 0) {
		for (BSLib::Utility::CHashMap<SkillTPID, GSLib::SkillSystem::GM::CSkill>::const_iterator itr = m_skills.begin(); itr != m_skills.end(); ++itr) {
			itr->second.SerializeTo(a_stream);
		}
	}
	for (BSLib::int32 i = 0; i < SkillSystem::GM::SKILL_BOTTON_COUNT; ++i) {
		a_stream << m_skillButtons[i];
	}

}



}//SceneSystem

}//GSLib











