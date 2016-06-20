//////////////////////////////////////////////////////////////////////
//	created:	2014/10/27
//	filename: 	GSLib\sceneSystem\GM\arenaData.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef		__GSLIB_SCENESYSTEM_GM_ROLEARENADATA_H__
#define		__GSLIB_SCENESYSTEM_GM_ROLEARENADATA_H__

#include <list>
#include <BSLib/utility/baseDef.h>
#include <GSLib/baseDef.h>
#include <GSLib/sceneSystem/GM/sceneSystemData.h>

namespace GSLib
{

namespace SceneSystem
{
	class CArenaChallengeRecord;
	class CArenaChallengeeData;
namespace GM
{

	class CRoleSceneModule;
class CRoleArenaData
{
public:
	CRoleArenaData();
	~CRoleArenaData();
public:
	void setSceneRole(CRoleSceneModule *a_sceneRole);

	bool isValid() const;

	void serializeTo(BSLib::Utility::CStream& stream) const;

	void addChallengeRecord(const SceneSystem::CArenaChallengeRecord & a_record);

	void setCombatRole(BSLib::uint32 a_combatRole);
	BSLib::int32 getCombatRole() const;

	void setLastChallengeTime(BSLib::int32 a_lastChallengeTime);
	BSLib::int32 getLastChallengeTime() const;

	void setDailyChallengeTimes(BSLib::uint16 a_dailyChallengeTimes);
	BSLib::uint16 getDailyChallengeTimes() const;

	bool hasDailyChallengeCount() const;

	CArenaChallengeeData *getChanllengee(BSLib::uint32 a_index);

	BSLib::int32 getAvailableTicketPurchaseCount () const;

	BSLib::uint32 getArenaTicketPrice() const;

	BSLib::int32 getTryChallengeRoleIndex() const;

	SceneSystem::CArenaChallengeRecord * getChallengeRecord(BSLib::uint64 a_recordID);

	void setArenaTicketCount(BSLib::uint32 a_ticketCount);

	BSLib::uint32 getArenaTicketCount() const;

	BSLib::uint32 getDailyCoolDownCount() const;

	BSLib::uint32 getArenaCoolDownCost() const;

	void reset();

	void exitScene();
public:
	CRoleSceneModule *m_sceneRole;
	BSLib::uint32 m_rank;
	BSLib::int32 m_combatRole;
	BSLib::int32 m_tryChallengeRoleIndex;
	CChallengeInfo m_challengeInfo;
	BSLib::uint32 m_arenaTicketCount;
	BSLib::uint32 m_dailyTicketPurchasedCount;
	BSLib::uint32 m_dailyCoolDownCount;
	BSLib::int32 m_lastChallengeTime;
	BSLib::int32 m_lastResetTime;
	std::map<BSLib::uint64, SceneSystem::CArenaChallengeRecord> m_mapChallengeRecords;
	std::vector<CArenaChallengeeData> m_vecChallengees;
};

}//GM
}//SceneSystem

}//GSLib






#endif










