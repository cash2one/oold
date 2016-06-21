#include <GSLib/sceneSystem/DB/tableSceneDB.h>
#include <GSLib/tracer.h>

namespace GSLib
{

namespace SceneSystem
{

namespace DB
{

CRoleArenaDataDB::CRoleArenaDataDB()
:m_arenaTicketCount(0)
,m_dailyTicketHasPurchasedCount(0)
,m_lastChallengeTime(0)
,m_lastResetTime(0)
{

}

CRoleArenaDataDB::~CRoleArenaDataDB()
{

}

std::string CRoleArenaDataDB::getKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
	return key;
}

bool CRoleArenaDataDB::_serializeTo(BSLib::Utility::CStream& stream) const 
{
	stream << m_arenaTicketCount;
	stream << m_dailyTicketHasPurchasedCount;
	stream << m_dailyCoolDownCount;
	stream << m_lastChallengeTime;
	stream << m_lastResetTime;
	return true;
}

bool CRoleArenaDataDB::_serializeFrom(BSLib::Utility::CStream& stream)
{
	stream >> m_arenaTicketCount;
	stream >> m_dailyTicketHasPurchasedCount;
	stream >> m_dailyCoolDownCount;
	stream >> m_lastChallengeTime;
	stream >> m_lastResetTime;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////
CArenaChallgengeRecordDB::CArenaChallgengeRecordDB()
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
,m_isRevenged(false)
{

}

CArenaChallgengeRecordDB::~CArenaChallgengeRecordDB()
{

}

std::string CArenaChallgengeRecordDB::getDBKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
	return key;
}

std::string CArenaChallgengeRecordDB::getIndexKey() const
{
	std::string indexKey;
	indexKey.append((char*)&m_recordID, sizeof(m_recordID));
	return indexKey;
}

bool CArenaChallgengeRecordDB::_serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_recordID;
	stream << m_isActive;
	stream << m_isWin;
	stream << m_challengeTime;
	stream << m_newRank;
	stream << m_changedRank;
	stream << m_challengeeAccountID;
	stream << m_challengeeZoneID;
	stream << m_challengeeRoleIndex;
	stream << m_challengeeTPID;
	stream << m_challengeeName;
	stream << m_isRevenged;
	return true;
}

bool CArenaChallgengeRecordDB::_serializeFrom(BSLib::Utility::CStream& stream) 
{
	stream >> m_recordID;
	stream >> m_isActive;
	stream >> m_isWin;
	stream >> m_challengeTime;
	stream >> m_newRank;
	stream >> m_changedRank;
	stream >> m_challengeeAccountID;
	stream >> m_challengeeZoneID;
	stream >> m_challengeeRoleIndex;
	stream >> m_challengeeTPID;
	stream >> m_challengeeName;
	stream >> m_isRevenged;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
CRoleStageSystemData::CRoleStageSystemData()
:m_dailyGetHelpCount(0)
,m_greedLandEnterCountRemaining(0)
,m_lastGreedLandUpdateTime(0)
,m_lastUpdateTime(0)
{

}

CRoleStageSystemData::~CRoleStageSystemData()
{

}

std::string CRoleStageSystemData::getKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
	return key;
}

bool CRoleStageSystemData::_serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_dailyGetHelpCount;
	stream << m_greedLandEnterCountRemaining;
	stream << m_lastGreedLandUpdateTime;
	stream << m_lastUpdateTime;
	return true;
}

bool CRoleStageSystemData::_serializeFrom(BSLib::Utility::CStream& stream)
{
	stream >> m_dailyGetHelpCount;
	stream >> m_greedLandEnterCountRemaining;
	stream >> m_lastGreedLandUpdateTime;
	stream >> m_lastUpdateTime;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
CRoleStoryInstanceProgressDB::CRoleStoryInstanceProgressDB()
:m_instanceID(0)
,m_stageIndex(0)
{

}

CRoleStoryInstanceProgressDB::~CRoleStoryInstanceProgressDB()
{

}

std::string CRoleStoryInstanceProgressDB::getKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
	return key;
}

bool CRoleStoryInstanceProgressDB::_serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_instanceID;
	stream << m_stageIndex;
	return true;
}

bool CRoleStoryInstanceProgressDB::_serializeFrom(BSLib::Utility::CStream& stream)
{
	stream >> m_instanceID;
	stream >> m_stageIndex;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
CRoleInstancePrizeDB::CRoleInstancePrizeDB()
:m_instanceID(0)
,m_star(0)
{

}

CRoleInstancePrizeDB::~CRoleInstancePrizeDB()
{

}

std::string CRoleInstancePrizeDB::getDBKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
	return key;
}

std::string CRoleInstancePrizeDB::getIndexKey() const
{
	std::string indexKey;
	indexKey.append((char*)&m_instanceID, sizeof(m_instanceID));
	return indexKey;
}

bool CRoleInstancePrizeDB::_serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_instanceID;
	stream << m_star;
	return true;
}

bool CRoleInstancePrizeDB::_serializeFrom(BSLib::Utility::CStream& stream)
{
	stream >> m_instanceID;
	stream >> m_star;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
CFinishStageDataDB::CFinishStageDataDB()
:m_instanceID(0)
,m_stageIndex(0)
,m_star(0)
,m_dailyEnteredTimes(0)
,m_lastResetTime(0)
,m_dailyRestoreCount(0)
{

}

CFinishStageDataDB::~CFinishStageDataDB()
{

}

std::string CFinishStageDataDB::getDBKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
	return key;
}

std::string CFinishStageDataDB::getIndexKey() const
{
	std::string indexKey;
	indexKey.append((char*)&m_instanceID, sizeof(m_instanceID));
	indexKey.append((char*)&m_stageIndex, sizeof(m_stageIndex));
	return indexKey;
}

bool CFinishStageDataDB::_serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_instanceID;
	stream << m_stageIndex;
	stream << m_star;
	stream << m_dailyEnteredTimes;
	stream << m_lastResetTime;
	stream << m_dailyRestoreCount;
	return true;
}

bool CFinishStageDataDB::_serializeFrom(BSLib::Utility::CStream& stream)
{
	stream >> m_instanceID;
	stream >> m_stageIndex;
	stream >> m_star;	
	stream >> m_dailyEnteredTimes;
	stream >> m_lastResetTime;
	stream >> m_dailyRestoreCount;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
CRoleConInstanceBriefDataDB::CRoleConInstanceBriefDataDB()
:m_dailyActivateInstanceCount(0)
,m_dailyFreeRollFastClearStageCount(0)
,m_lastResetTime(0)
{

}

CRoleConInstanceBriefDataDB::~CRoleConInstanceBriefDataDB()
{

}

std::string CRoleConInstanceBriefDataDB::getDBKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
	return key;
}

bool CRoleConInstanceBriefDataDB::_serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_dailyActivateInstanceCount;
	stream << m_dailyFreeRollFastClearStageCount;
	stream << m_lastResetTime;
	return true;
}

bool CRoleConInstanceBriefDataDB::_serializeFrom(BSLib::Utility::CStream& stream)
{
	stream >> m_dailyActivateInstanceCount;
	stream >> m_dailyFreeRollFastClearStageCount;
	stream >> m_lastResetTime;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
CContinuousStageResultDataDB::CContinuousStageResultDataDB()
:m_instanceTPID(0)
,m_stageIndex(0)
,m_score(0)
{

}

CContinuousStageResultDataDB::~CContinuousStageResultDataDB()
{

}

std::string CContinuousStageResultDataDB::getDBKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
	return key;
}

std::string CContinuousStageResultDataDB::getIndexKey() const
{
	std::string key;
	key.append((char*)&m_instanceTPID, sizeof(m_instanceTPID));
	key.append((char*)&m_stageIndex, sizeof(m_stageIndex));
	return key;
}

bool CContinuousStageResultDataDB::_serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_instanceTPID;
	stream << m_stageIndex;
	stream << m_score;
	return true;
}

bool CContinuousStageResultDataDB::_serializeFrom(BSLib::Utility::CStream& stream)
{
	stream >> m_instanceTPID;
	stream >> m_stageIndex;
	stream >> m_score;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
CRoleConInstanceProgressDB::CRoleConInstanceProgressDB()
:m_instanceTPID(0)
,m_isActivated(false)
,m_curDayStageIndex(0)
,m_maxClearStageIndex(0)
{

}

CRoleConInstanceProgressDB::~CRoleConInstanceProgressDB()
{

}

std::string CRoleConInstanceProgressDB::getDBKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
	return key;
}

std::string CRoleConInstanceProgressDB::getIndexKey() const
{
	std::string key;
	key.append((char*)&m_instanceTPID, sizeof(m_instanceTPID));
	return key;
}

bool CRoleConInstanceProgressDB::_serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_instanceTPID;
	stream << m_isActivated;
	stream << m_curDayStageIndex;
	stream << m_maxClearStageIndex;
	return true;
}

bool CRoleConInstanceProgressDB::_serializeFrom(BSLib::Utility::CStream& stream)
{
	stream >> m_instanceTPID;
	stream >> m_isActivated;
	stream >> m_curDayStageIndex;
	stream >> m_maxClearStageIndex;
	return true;
}



}//DB

}//SkillSystem

}//GSLib
