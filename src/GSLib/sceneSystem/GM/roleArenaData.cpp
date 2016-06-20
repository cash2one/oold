#include <GSLib/sceneSystem/GM/roleArenaData.h>
#include <GSLib/sceneSystem/sceneSystemCommonData.h>
#include <GSLib/sceneSystem/GM/sceneDefine.h>
#include <BSLib/utility/dateTime.h>
#include <GSLib/sceneSystem/GM/roleSceneModule.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

CRoleArenaData::CRoleArenaData()
:m_sceneRole(NULL)
,m_rank(10001)
,m_combatRole(-1)
,m_tryChallengeRoleIndex(-1)
,m_arenaTicketCount(C_DAILY_ARENA_CHALLENGE_TIMES)
,m_dailyTicketPurchasedCount(0)
,m_lastChallengeTime(0)
,m_lastResetTime(0)
{
}

CRoleArenaData::~CRoleArenaData()
{
	m_mapChallengeRecords.clear();
	m_vecChallengees.clear();
}

void CRoleArenaData::setSceneRole(CRoleSceneModule *a_sceneRole)
{
	m_sceneRole = a_sceneRole;
}

bool CRoleArenaData::isValid() const
{
	return m_sceneRole != NULL;
}

void CRoleArenaData::serializeTo(BSLib::Utility::CStream& stream) const
{
	if (!isValid()) {
		return;
	}
	stream << m_rank;
	stream << m_arenaTicketCount;
	stream << m_dailyTicketPurchasedCount;
	BSLib::uint32 maxDailyPurchasedArenaTicketCount = m_sceneRole->getMaxPurchaseArenaTicketCount();
	BSLib::uint32 remaindPurchasedCount = maxDailyPurchasedArenaTicketCount > m_dailyTicketPurchasedCount ? maxDailyPurchasedArenaTicketCount - m_dailyTicketPurchasedCount : 0;
	stream << remaindPurchasedCount;
	int interval = 0;
	if (m_lastChallengeTime > 0) {
		interval = (BSLib::int32)(C_CHALLENGE_COOL_DWON_INTERVAL - (BSLib::Utility::CDateTime::getCurrentTime().getSeconds() - m_lastChallengeTime));
	}
	interval = interval > 0 ? interval : 0;
	stream << interval;
	stream << getArenaCoolDownCost();

	BSLib::uint32 recordSize = (BSLib::uint32)m_mapChallengeRecords.size();
	recordSize = recordSize > C_MAX_CHALLENGE_RECORD_COUNT ? C_MAX_CHALLENGE_RECORD_COUNT : recordSize;
	stream << (BSLib::uint16)recordSize;
	BSLib::uint32 count = 0;
	for (std::map<BSLib::uint64 ,CArenaChallengeRecord>::const_iterator itr = m_mapChallengeRecords.begin(); itr != m_mapChallengeRecords.end(); ++itr) {
		itr->second.serializeTo(stream);
		if (++count > recordSize) {
			break;
		}
	}

	stream << (BSLib::uint16)m_vecChallengees.size();
	for (std::vector<CArenaChallengeeData>::const_iterator itr = m_vecChallengees.begin(); itr != m_vecChallengees.end(); ++itr) {
		itr->serializeTo(stream);
	}
}

void CRoleArenaData::addChallengeRecord(const SceneSystem::CArenaChallengeRecord & a_record)
{
	m_mapChallengeRecords.insert(std::make_pair(a_record.m_recordID, a_record));
}

void CRoleArenaData::setCombatRole(BSLib::uint32 a_combatRole)
{
	m_combatRole = a_combatRole;
}

BSLib::int32 CRoleArenaData::getCombatRole() const
{
	return m_combatRole;
}

void CRoleArenaData::setLastChallengeTime(BSLib::int32 a_lastChallengeTime)
{
	if (m_lastChallengeTime < a_lastChallengeTime) {
		m_lastChallengeTime = a_lastChallengeTime;
	}
}

BSLib::int32 CRoleArenaData::getLastChallengeTime() const
{
	return m_lastChallengeTime;
}

void CRoleArenaData::setDailyChallengeTimes(BSLib::uint16 a_dailyChallengeTimes)
{
	m_arenaTicketCount = a_dailyChallengeTimes;
}

BSLib::uint16 CRoleArenaData::getDailyChallengeTimes() const
{
	return m_arenaTicketCount;
}

bool CRoleArenaData::hasDailyChallengeCount() const
{
	return m_arenaTicketCount > 0;
}

CArenaChallengeeData * CRoleArenaData::getChanllengee(BSLib::uint32 a_index)
{
	if (a_index < m_vecChallengees.size()) {
		return &m_vecChallengees[a_index];
	}

	return NULL;
}

BSLib::int32 CRoleArenaData::getAvailableTicketPurchaseCount () const
{
	BSLib::int32 count = C_MAX_DAILY_ARENA_TICKET_PURCHASE_COUNT - m_dailyTicketPurchasedCount;
	return count < 0 ? 0 : count;
}

BSLib::uint32 CRoleArenaData::getArenaTicketPrice() const
{
	return 50 + m_dailyTicketPurchasedCount * 100;
}

BSLib::int32 CRoleArenaData::getTryChallengeRoleIndex() const
{
	return m_tryChallengeRoleIndex;;
}

void CRoleArenaData::setArenaTicketCount(BSLib::uint32 a_ticketCount)
{
	m_arenaTicketCount = a_ticketCount;	
}

BSLib::uint32 CRoleArenaData::getArenaTicketCount() const
{
	return m_arenaTicketCount;
}

BSLib::uint32 CRoleArenaData::getArenaCoolDownCost() const
{
	return 10 + m_dailyCoolDownCount * 5;
}

void CRoleArenaData::reset()
{
	m_dailyTicketPurchasedCount = 0;
	m_dailyCoolDownCount = 0;
	m_lastResetTime = (BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
	m_arenaTicketCount = C_DAILY_ARENA_CHALLENGE_TIMES;
}

void CRoleArenaData::exitScene()
{
	m_combatRole = -1;
	m_vecChallengees.clear();
	m_challengeInfo.reset();
	m_tryChallengeRoleIndex = -1;
}

SceneSystem::CArenaChallengeRecord * CRoleArenaData::getChallengeRecord(BSLib::uint64 a_recordID) 
{
	std::map<BSLib::uint64, SceneSystem::CArenaChallengeRecord>::iterator itr =
		m_mapChallengeRecords.find(a_recordID);
	if (itr != m_mapChallengeRecords.end()) {
		return &itr->second;
	}
	return NULL;
}










}//GM

}//SceneSystem

}//GSLib











