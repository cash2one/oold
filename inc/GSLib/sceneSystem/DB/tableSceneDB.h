//////////////////////////////////////////////////////////////////////
//	created:	2014/11/6
//	filename: 	GSLib\sceneSystem\DB\tableSceneDB.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SCENESYSTEM_DB_TABLESCENEDB_H__
#define __GSLIB_SCENESYSTEM_DB_TABLESCENEDB_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/dbTableID.h>

namespace GSLib
{

namespace SceneSystem
{

namespace DB
{

const BSLib::Database::SDbColumn g_roleArenaDataColumn[] = 
{
	{"AccountID",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64),  BSLib::Database::EDF_KEY },
	{"ZoneID",								BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_KEY },
	{"RoleIndex",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_KEY },
	{"DailyAreanTicketCount",				BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"DailyTicketPurchasedCount",			BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"DailyCoolDownCount",					BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"LastChallengeTime",					BSLib::Database::EDT_INT32, sizeof(BSLib::int32),	BSLib::Database::EDF_NULL},
	{"LastResetTime",						BSLib::Database::EDT_INT32, sizeof(BSLib::int32),	BSLib::Database::EDF_NULL},
	{ "",									BSLib::Database::EDT_NULL,0,						BSLib::Database::EDF_NULL}
};

const BSLib::Database::SDbColumn g_arenaChallengeRecordColumn[] = 
{
	{"AccountID",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_KEY },
	{"ZoneID",								BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_KEY },
	{"RoleIndex",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_KEY },
	{"RecordID",							BSLib::Database::EDT_UINT64, sizeof(BSLib::uint64), BSLib::Database::EDF_INDEX },
	{"IsActive",							BSLib::Database::EDT_UINT8, sizeof(BSLib::uint8), BSLib::Database::EDF_NULL},
	{"IsWin",								BSLib::Database::EDT_UINT8, sizeof(BSLib::uint8), BSLib::Database::EDF_NULL},
	{"ChallengeTime",						BSLib::Database::EDT_INT32, sizeof(BSLib::int32), BSLib::Database::EDF_NULL},
	{"NewRank",								BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"ChangedRank",							BSLib::Database::EDT_INT32, sizeof(BSLib::int32), BSLib::Database::EDF_NULL},
	{"ChallengeeAccountID",					BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_NULL},
	{"ChallengeeZoneID",					BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_NULL},
	{"ChallengeeRoleIndex",					BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"ChallengeeTPID",						BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"ChallengeeName",						BSLib::Database::EDT_STRING, 0, BSLib::Database::EDF_NULL},
	{"IsRevenged",							BSLib::Database::EDT_UINT8, sizeof(BSLib::uint8), BSLib::Database::EDF_NULL},
	{ "",									BSLib::Database::EDT_NULL,		0,BSLib::Database::EDF_NULL	}
};

//副本关卡好友助阵
const BSLib::Database::SDbColumn g_roleStageSystemDataColumn[] = 
{
	{"AccountID",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_KEY },
	{"ZoneID",								BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_KEY },
	{"RoleIndex",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_KEY },
	{"DailyGetHelpCount",					BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"GreedLandEnterCountRemaining",		BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"LastGreedLandUpdateTime",				BSLib::Database::EDT_INT32, sizeof(BSLib::int32), BSLib::Database::EDF_NULL},
	{"LastUpdateTime",						BSLib::Database::EDT_INT32, sizeof(BSLib::int32), BSLib::Database::EDF_NULL},
	{ "",									BSLib::Database::EDT_NULL,0,	BSLib::Database::EDF_NULL		}
};

//剧情副本进度表
const BSLib::Database::SDbColumn g_roleStoryInstanceProgressColumn[] = 
{
	{"AccountID",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_KEY },
	{"ZoneID",								BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_KEY },
	{"RoleIndex",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_KEY },
	{"InstanceID",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"StageIndex",							BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_NULL},
	{ "",									BSLib::Database::EDT_NULL,0,	BSLib::Database::EDF_NULL		}
};

//#创建剧个人关卡数据表
const BSLib::Database::SDbColumn g_roleInstanceStageDataColumn[] = 
{
	{"AccountID",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_KEY },
	{"ZoneID",								BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_KEY },
	{"RoleIndex",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_KEY },
	{"InstanceID",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_INDEX},
	{"StageIndex",							BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_INDEX},
	{"Star",								BSLib::Database::EDT_INT8, sizeof(BSLib::uint8), BSLib::Database::EDF_NULL},
	{"DailyEnteredTimes",					BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_NULL},
	{"LastResetTime",						BSLib::Database::EDT_INT32, sizeof(BSLib::int32), BSLib::Database::EDF_NULL},
	{"DailyRestoreTicketCount",				BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{ "",									BSLib::Database::EDT_NULL,0,	BSLib::Database::EDF_NULL		}
};

//个人副本奖励数据表
const BSLib::Database::SDbColumn g_roleInstancePrizeDataColumn[] = 
{
	{"AccountID",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_KEY },
	{"ZoneID",								BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_KEY },
	{"RoleIndex",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_KEY },
	{"InstanceID",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_INDEX},
	{"Star",								BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_NULL},
	{ "",									BSLib::Database::EDT_NULL,0,	BSLib::Database::EDF_NULL		}
};

//个人连续闯关数据
const BSLib::Database::SDbColumn g_roleContinuousInstanceDataColumn[] = 
{
	{"AccountID",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_KEY },
	{"ZoneID",								BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_KEY },
	{"RoleIndex",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_KEY },
	{"DailyActivateInstanceCount",			BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"DailyFreeRollFastClearStageCount",	BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"LastResetTime",						BSLib::Database::EDT_INT32, sizeof(BSLib::int32), BSLib::Database::EDF_NULL},
	{ "",									BSLib::Database::EDT_NULL,0,	BSLib::Database::EDF_NULL		}
};

//连续闯关进度数据
const BSLib::Database::SDbColumn g_roleContinuousInstanceProgressDataColumn[] = 
{
	{"AccountID",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_KEY },
	{"ZoneID",								BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_KEY },
	{"RoleIndex",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_KEY },
	{"InstanceID",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_INDEX},
	{"IsActivated",							BSLib::Database::EDT_INT8, sizeof(BSLib::int8), BSLib::Database::EDF_NULL},
	{"CurDayStageIndex",					BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"MaxClearStageIndex",					BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{ "",									BSLib::Database::EDT_NULL,0,	BSLib::Database::EDF_NULL		}
};

//连续闯关关卡成绩数据
const BSLib::Database::SDbColumn g_roleContinuousStageResultDataColumn[] = 
{
	{"AccountID",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_KEY },
	{"ZoneID",								BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_KEY },
	{"RoleIndex",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_KEY },
	{"InstanceID",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_INDEX},
	{"StageIndex",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_INDEX},
	{"Score",								BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{ "",									BSLib::Database::EDT_NULL,0,	BSLib::Database::EDF_NULL		}
};

//////////////////////////////////////////////////////////////////////////////////
class CRoleArenaDataDB:public GSLib::PlayerSystem::DB::CRoleKey 
{
public:
	CRoleArenaDataDB();
	~CRoleArenaDataDB();
public:
	std::string getKey() const;
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BSLib::Utility::CStream& stream);
public:
	BSLib::uint32 m_arenaTicketCount;
	BSLib::uint32 m_dailyTicketHasPurchasedCount;
	BSLib::uint32 m_dailyCoolDownCount;
	BSLib::int32 m_lastChallengeTime;
	BSLib::int32 m_lastResetTime;
};

//////////////////////////////////////////////////////////////////////////////////
class CArenaChallgengeRecordDB : public GSLib::PlayerSystem::DB::CRoleKey
{
public:
	CArenaChallgengeRecordDB();
	~CArenaChallgengeRecordDB();
public:
	std::string getDBKey() const;
	std::string getIndexKey() const;
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BSLib::Utility::CStream& stream);
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
//////////////////////////////////////////////////////////////////////////////////
class CRoleStageSystemData : public GSLib::PlayerSystem::DB::CRoleKey
{
public:
	CRoleStageSystemData();
	~CRoleStageSystemData();
public:
	std::string getKey() const;
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BSLib::Utility::CStream& stream);
public:
	BSLib::uint32 m_dailyGetHelpCount;
	BSLib::uint32 m_greedLandEnterCountRemaining;
	BSLib::int32 m_lastGreedLandUpdateTime;
	BSLib::int32 m_lastUpdateTime;
};
//////////////////////////////////////////////////////////////////////////////////
class CRoleStoryInstanceProgressDB : public GSLib::PlayerSystem::DB::CRoleKey
{
public:
	CRoleStoryInstanceProgressDB();
	~CRoleStoryInstanceProgressDB();
public:
	std::string getKey() const;
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BSLib::Utility::CStream& stream);
public:
	BSLib::uint32 m_instanceID;
	BSLib::uint16 m_stageIndex;
};

class CRoleInstancePrizeDB : public GSLib::PlayerSystem::DB::CRoleKey
{
public:
	CRoleInstancePrizeDB();
	~CRoleInstancePrizeDB();
public:
	std::string getDBKey() const;
	std::string getIndexKey() const;
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BSLib::Utility::CStream& stream);
public:
	BSLib::uint32 m_instanceID;
	BSLib::uint16 m_star;
};

//////////////////////////////////////////////////////////////////////////////////
class CFinishStageDataDB : public GSLib::PlayerSystem::DB::CRoleKey
{
public:
	CFinishStageDataDB();
	~CFinishStageDataDB();
public:
	std::string getDBKey() const;
	std::string getIndexKey() const;
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BSLib::Utility::CStream& stream);
public:
	BSLib::uint32 m_instanceID;
	BSLib::uint16 m_stageIndex;
	BSLib::int8 m_star;
	BSLib::uint16 m_dailyEnteredTimes;
	BSLib::int32 m_lastResetTime;
	BSLib::uint32 m_dailyRestoreCount;
};

//////////////////////////////////////////////////////////////////////////////////
class CRoleConInstanceBriefDataDB : public GSLib::PlayerSystem::DB::CRoleKey
{
public:
	CRoleConInstanceBriefDataDB();
	~CRoleConInstanceBriefDataDB();
public:
	std::string getDBKey() const;
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BSLib::Utility::CStream& stream);
public:
	BSLib::uint32 m_dailyActivateInstanceCount;
	BSLib::uint32 m_dailyFreeRollFastClearStageCount;
	BSLib::int32 m_lastResetTime;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CRoleConInstanceProgressDB  : public GSLib::PlayerSystem::DB::CRoleKey
{
public:
	CRoleConInstanceProgressDB();
	~CRoleConInstanceProgressDB();
public:
	std::string getDBKey() const;
	std::string getIndexKey() const;
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BSLib::Utility::CStream& stream);
public:
	BSLib::uint32 m_instanceTPID;
	BSLib::int8 m_isActivated;
	BSLib::uint32 m_curDayStageIndex;
	BSLib::uint32 m_maxClearStageIndex;
};

//////////////////////////////////////////////////////////////////////////////////
class CContinuousStageResultDataDB : public GSLib::PlayerSystem::DB::CRoleKey
{
public:
	CContinuousStageResultDataDB();
	~CContinuousStageResultDataDB();
public:
	std::string getDBKey() const;
	std::string getIndexKey() const;
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BSLib::Utility::CStream& stream);
public:
	BSLib::uint32 m_instanceTPID;
	BSLib::uint32 m_stageIndex;	
	BSLib::uint32 m_score;
};



}//DB

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_DB_TABLESCENEDB_H__
