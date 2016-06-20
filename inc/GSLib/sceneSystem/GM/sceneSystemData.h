//////////////////////////////////////////////////////////////////////
//	created:	2014/12/19
//	filename: 	GSLib\sceneSystem\GM\sceneSystemData.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SCENESYSTEM_GM_SCENESYSTEMDATA_H__
#define __GSLIB_SCENESYSTEM_GM_SCENESYSTEMDATA_H__ 

#include <BSLib/utility/baseDef.h>
#include <BSLib/math/vector3.h>
#include <GSLib/sceneSystem/GM/sceneDefine.h>
#include <BSLib/utility/hashMap.h>
#include <GSLib/itemSystem/GM/itemAttributeGM.h>
#include <BSLib/utility/hashMap.h>
#include <GSLib/sceneSystem/GM/sceneAttr.h>
#include <GSLib/baseDef.h>
#include <GSLib/sceneSystem/GM/dropItem.h>

namespace BSLib
{
	namespace Utility
	{
		class CStream;
	}
}

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class CSceneGM;
class CScene;

////////////////////////////////////////////////////////////////////////////////////////////////
class CRoleStoryInstanceProgress
{
public:
	CRoleStoryInstanceProgress();
	~CRoleStoryInstanceProgress();
public:
	BSLib::uint32 m_instanceTPID;
	BSLib::uint16 m_stageIndex;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CRoleInstanceStarPrize
{
public:
	CRoleInstanceStarPrize();
	~CRoleInstanceStarPrize();
public:
	BSLib::uint32 m_instanceTPID;
	BSLib::uint16 m_star;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CStagePrizeAttr
{
public:
	CStagePrizeAttr();
	~CStagePrizeAttr();
public:
	void append(const CStagePrizeAttr &rhs);
public:
	std::vector<CDropItem> m_vecStagePrize;
	std::vector<CDropItem> m_vecRandomDrops;
	std::vector<CDropItem> m_vecCertainlyDrops;
	std::vector<CDropItem> m_vecBossDrops;
	std::vector<CDropItem> m_vecEliteDrops;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CDropMonsterAttr
{
public:
	CDropMonsterAttr();
	~CDropMonsterAttr();
public:
	BSLib::uint32 m_ID;
	EMonsterDropType m_dropType;
	BSLib::uint32 m_weight;
	BSLib::uint32 m_totalWeight;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CStageTemplate
{
public:
	CStageTemplate();
	~CStageTemplate();
public:
	BSLib::uint32 m_difficulty;
	BSLib::uint32 m_stageUnitCount;
	BSLib::uint32 m_unitBatchCount;
	BSLib::uint32 m_minStageUnitBatchCount;
	BSLib::uint32 m_maxStageUnitBatchCount;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CMonsterAttrBatch
{
public:
	CMonsterAttrBatch();
	~CMonsterAttrBatch();
public:
	void addMonsterAttr(const CDropMonsterAttr & a_monsterAttr);
	std::vector<CDropMonsterAttr>::size_type size() const;
public:
	std::vector<CDropMonsterAttr> m_vecMonsterAttr;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CStageUnitAttr
{
public:
	CStageUnitAttr();
	~CStageUnitAttr();
public:
	void addMonsterBatchAttr(const CMonsterAttrBatch &a_monsterAttrBatch);
	bool isValid() const;
	std::vector<CMonsterAttrBatch>::size_type size() const;
public:
	BSLib::uint32 m_id;
	BSLib::uint32 m_type;
	BSLib::uint32 m_bossID;
	std::vector<CMonsterAttrBatch> m_vecMonsterAttrBatch;
	CDropMonsterAttr m_randomElite;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CStageAttr : public CSceneAttr
{
public:
	CStageAttr(ESceneType a_sceneType);
	~CStageAttr();
public:
	BSLib::uint32 getInstanceTPID() const;
	BSLib::uint16 getStageIndex() const;
	BSLib::uint32 getPreStage() const;
	BSLib::uint32 getDropItem(BSLib::int8 a_star) const;
	BSLib::uint32 getExp() const;
	BSLib::uint32 getGold() const;
	BSLib::uint16 getMaxDailyEnterTimes() const;
	BSLib::uint32 getBossID() const;
	EInstanceType getInstanceType() const;
	BSLib::uint32 getCostVitality() const;
public:
	EInstanceType m_instanceType;
	BSLib::uint32 m_difficulty;
	BSLib::uint32 m_costVitality;
	BSLib::uint32 m_dailyEnterCount;
	BSLib::uint32 m_prizeExp;
	BSLib::uint32 m_prizeGold;
	BSLib::uint32 m_dropItemIDStar1;
	BSLib::uint32 m_dropItemIDStar2;
	BSLib::uint32 m_dropItemIDStar3;
	BSLib::uint32 m_reviveCount;
	BSLib::uint32 m_autoGetSkillTPID;
	BSLib::uint32 m_instanceTPID;
	BSLib::uint16 m_stageIndex;
	BSLib::uint32 m_preStage;
	std::list<BSLib::uint32> m_vecUnits;
	BSLib::uint32 m_bossID;
	BSLib::Utility::CHashMap<BSLib::uint32, CStageUnitAttr*> m_hashStageUnits;
	CStagePrizeAttr m_stagePrizeAttr;
};


////////////////////////////////////////////////////////////////////////////////////////////////
class CMonster
{
public:
	CMonster();
	~CMonster();
public:
	bool isValid() const;
	void serializeTo(BSLib::Utility::CStream & stream) const;
public:
	EMonsterDropType m_type;
	BSLib::uint32 m_index;
	std::vector<ItemSystem::GM::CPrizeItem> m_vecDropItem; 
	const CDropMonsterAttr *m_monsterAttr;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CMonsterBatch
{
public:
	CMonsterBatch();
	~CMonsterBatch();
public:
	void addMonster(const CMonster & a_monster);
	BSLib::uint32 size() const;
	void serializeTo(BSLib::Utility::CStream& stream) const;
public:
	BSLib::int32 m_batchIndex;
	std::vector<CMonster> m_vecMonster;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CStageUnitMonster
{
public:
	CStageUnitMonster();
	~CStageUnitMonster();
public:
	void addMonsterBatch(const CMonsterBatch & a_monsterBatch);
	void serializeTo(BSLib::Utility::CStream & stream) const;
public:
	std::vector<CMonsterBatch> m_batchMonster;
	CMonster m_randomElite;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CStageMonster
{
public:
	CStageMonster();
	~CStageMonster();
public:
	void addStageUnit(const CStageUnitMonster & a_stageUnitMonster);
	void addDropMonster(const CMonster & a_dropMonster);
	void clear();
	void serializeTo(BSLib::Utility::CStream & stream) const;
	void setValid(bool a_value);
	bool isValid() const;
public:
	bool m_isValid;
	std::vector<CStageUnitMonster> m_vecMonster;
	std::vector<CMonster> m_vecDropMonster;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CInstanceAttr
{
public:
	CInstanceAttr();
	~CInstanceAttr();
public:
	EInstanceType getInstanceType() const;
	BSLib::uint16 stageSize() const;
	EInstanceType getType() const;
	const CStageAttr *getStageAttr(BSLib::uint16 a_stageIndex);
	BSLib::uint32 getUnlockInstanceTPID() const;
public:
	BSLib::uint32 m_TPID;
	EInstanceType m_instanceType;	
	BSLib::uint32 m_unlockInstanceTPID;
	std::vector<CStageAttr*> m_vecStage;
	BSLib::uint32 m_city;
};
///////////////////////////////////////////////////////////////////////////////////////////////
class CFinishStage
{
public:
	CFinishStage();
	~CFinishStage();
public:
	bool operator==(const CFinishStage& stageData) const;
public:
	void serializeTo(BSLib::Utility::CStream &stream) const;
	bool isValid() const;
	BSLib::int8 getStar() const;
	BSLib::uint16 getDailyEnteredTimes() const;
	BSLib::int32 getLastResetTime() const;
	BSLib::uint32 getNextRestoreStageRequireDiamond() const;
	BSLib::uint32 getDailyRestoreCount() const;

public:
	BSLib::uint32 m_instanceID;
	BSLib::uint16 m_stageIndex;
	BSLib::int8 m_star;
	BSLib::uint16 m_dailyEnteredTimes;
	BSLib::int32 m_lastResetTime;
	BSLib::uint32 m_dailyRestoreCount;
};
///////////////////////////////////////////////////////////////////////////////////////////
class CFinishInstanceData
{
public:
	CFinishInstanceData(const CInstanceAttr *a_instanceAttr = NULL);
	~CFinishInstanceData();
public:
	const CInstanceAttr *getInstanceAttr() const;
	std::vector<CFinishStage>& getFinishStage() ;	
	void setStage(BSLib::uint16 a_index, CFinishStage & a_finishStageData);
	CFinishStage * getStage(BSLib::uint16 a_stageIndex);
	const std::vector<CFinishStage> & getStages() const;
	bool hasFinished() const;
	BSLib::int8 getStars() const;
public:
	const CInstanceAttr *m_instanceAttr;
	std::vector<CFinishStage> m_vecFinishStage;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CRoleStage
{
public:
	CRoleStage();
	~CRoleStage();
public:
	bool isInStage() const;
	void clear();
public:
	BSLib::uint32 m_instanceTPID;
	BSLib::uint16 m_stageIndex;
};

///////////////////////////////////////////////////////////////////////////////////////////////
class CRoleStageSystemData
{
public:
	CRoleStageSystemData();
	~CRoleStageSystemData();
public:
	BSLib::uint32 getGreedLandEntrances() const;
public:
	void reset();
public:
	BSLib::uint32 m_dailyGetHelperCount;
	BSLib::uint32 m_greedLandTickets;
	BSLib::int32 m_lastGreedLandUpdateTime;
	BSLib::int32 m_lastUpdateTime;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CStagePrize
{
public:
	CStagePrize();
	~CStagePrize();
public:
	void serializeTo(BSLib::Utility::CStream& stream) const;
public:
	BSLib::uint64 m_exp;
	BSLib::uint64 m_gold;
	std::vector<GSLib::ItemSystem::GM::CPrizeItem> m_vecPrizeItem;
	std::vector<GSLib::ItemSystem::GM::CPrizeItem> m_elitePrizeItem;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CInstanceStarPrizeAttr
{
public:
	CInstanceStarPrizeAttr();
	~CInstanceStarPrizeAttr();
public:
	 void getStarLevelPrize(BSLib::uint16 a_star, std::vector<ItemSystem::GM::CPrizeItem> &vecInstancePrize) const;
	BSLib::uint16 getNextStarLevel(BSLib::uint16 a_curStar) const;
public:
	BSLib::uint32 m_instanceTPID;
	BSLib::Utility::CHashMap< BSLib::uint16, std::vector<ItemSystem::GM::CPrizeItem> > m_hashStarPrize;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CSceneRoleInfo
{
public:
	CSceneRoleInfo();
	~CSceneRoleInfo();
public:
	void serializeTo(BSLib::Utility::CStream & a_stream) const;
public:
	GSLib::SRoleKey m_roleKey;
	BSLib::uint32 m_roleTPID;
	std::string m_roleName;
	BSLib::uint32 m_level;
	BSLib::uint32 m_VIPLevel;
	BSLib::uint32 m_combatPower;
	BSLib::uint32 m_fashionTPID;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CRoleInstanceData
{
public:
	CRoleInstanceData();
	~CRoleInstanceData();
public:

	void setCurStage(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_stageIndex);

	CRoleStage& getCurStage();

	BSLib::uint32 getCurInstanceTPID() const;

	BSLib::uint16 getCurStageIndex() const;

	bool isInStage() const;

	void exitScene();

	void setStoryInstanceProgress(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_stageIndex);

	void setStoryInstanceProgress(const CRoleStoryInstanceProgress &a_storyInstanceProgress);

	BSLib::Utility::CHashMap<BSLib::uint32, CRoleInstanceStarPrize> & getRoleInstancPrizeMap();

	const CRoleStoryInstanceProgress & getProgressData() const;

	BSLib::uint32 getProgressInstanceTPID() const;

	BSLib::uint16 getProgressStageIndex() const;

	CFinishInstanceData* getFinishInstanceData(BSLib::uint32 a_instanceTPID);

	CFinishStage *getStage(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_stageIndex);

	CFinishStage *getStage(BSLib::uint32 a_stageTPID);

	bool hasFinishInstance(BSLib::uint32 a_instanceTPID) const;

	void reportStageResult(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_stageIndex, BSLib::int8 a_star, CFinishStage & a_finsStageData);

	void addStageData(CFinishStage & a_finishStageData);

	void addInstancePrizeData(CRoleInstanceStarPrize & a_instancePrize);

	BSLib::uint16 getCurrentInstancePrizeStar(BSLib::uint32 a_instanceTPID) const;

	BSLib::uint16 getNextInstancePrizeStar(BSLib::uint32 a_instanceTPID) const;

	CRoleInstanceStarPrize *getInstanceStarPrize(BSLib::uint32 a_instanceTPID);

	BSLib::int32 getLastStageGetHelpUpdateTime() const;

	void onRoleStageGetHelpReset();

	BSLib::uint32 getLastGreedLandTicketsUpdateTime() const;

	void setLastGreedLandTicktsUpdateTime(BSLib::int32 a_updateTime);

	BSLib::uint32 getGreedLandTicketsCount() const;

	void setGreedLandTicketsCount(BSLib::uint32 a_count);

public:
	CRoleStage m_curStage;	
	const CStageAttr *m_tryEnterStageAttr;//¡Ÿ ±∑Ω∞∏
	CRoleStageSystemData m_roleStageSystemData;
	CRoleStoryInstanceProgress m_roleStoryInstanceProgress;
	BSLib::Utility::CHashMap<BSLib::uint32, CFinishInstanceData > m_hashFinishInstanceData;
	BSLib::Utility::CHashMap<BSLib::uint32, CRoleInstanceStarPrize> m_hashRoleInstancePrize;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CRoleConInstanceBriefData 
{
	enum {DAILY_ACTIVATE_INSTANCE_COUNT = 9999,};
	enum {DAILY_FREE_ROLL_FAST_CLEAR_STAGE_COUNT = 9999,};
public:
	CRoleConInstanceBriefData();
	~CRoleConInstanceBriefData();
public:
	void onReset();
	void exitScene();
	BSLib::uint32 getDailyFreeRollFastClearStageCount() const;
	void setDailyFreeRollFastClearStageCount(BSLib::uint32 a_count);
	void setDailyActivateInstanceCount(BSLib::uint32 a_count);
	BSLib::uint32 getDailyActivateInstanceCount() const;
public:
	BSLib::uint32 m_dailyActivateInstanceCount;
	BSLib::uint32 m_dailyFreeRollFastClearStageCount;
	BSLib::int32 m_lastResetTime;
	BSLib::uint32 m_curEnteredInstanceTPID;
	BSLib::uint32 m_curEnteredStageIndex;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CContinuousStageResultData
{
public:
	CContinuousStageResultData();
	~CContinuousStageResultData();
public:
	BSLib::uint32 m_instanceTPID;
	BSLib::uint32 m_stageIndex;	
	BSLib::uint32 m_score;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CConInstanceProgressData
{
	enum { MAX_CONTINUOUS_STAGE_COUNT = 200, };
public:
	CConInstanceProgressData();
	~CConInstanceProgressData();
public:
	void onReset();
	BSLib::uint32 stageSize() const;
	void addStageResult(CContinuousStageResultData & a_stageResult);
	bool isActivated() const;
	void setCurDayStageIndex(BSLib::uint32 a_curDayStageIndex);
	BSLib::uint32 getCurDayStageIndex() const;
	BSLib::uint32 getMaxClearStageIndex() const;
	BSLib::uint32 getInstanceStageSize() const;
public:
	BSLib::uint32 m_instanceTPID;
	bool m_isActivated;
	BSLib::uint32 m_curDayStageIndex;
	BSLib::uint32 m_maxClearStageIndex;
	std::vector<CContinuousStageResultData> m_vecStageResult;
	const CInstanceAttr *m_instanceAttr;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CRoleContinuousStageData
{
public:
	CRoleContinuousStageData();
	~CRoleContinuousStageData();
public:
	void onDailyRest();

	void exitScene();

	BSLib::int32 getLastResetTime() const;

	BSLib::uint32 getCurEnteredConInstanceTPID() const;
	BSLib::uint32 getCurEnteredConStageIndex() const;

	void setCurEnteredStage(BSLib::uint32 a_instanceTPID, BSLib::uint32 a_stageIndex);

	CConInstanceProgressData * getConInstanceProgressData(BSLib::uint32 a_instanceTPID);	
	CConInstanceProgressData * getCurConInstanceProgressData();

	void addConInstanceProgressData(const CConInstanceProgressData & a_conInstanceProgressData);

	void addConStageResult(CContinuousStageResultData & a_conStageResult, const CInstanceAttr *a_instanceAttr);

	void setDailyActivateInstanceCount(BSLib::uint32 a_count);
	BSLib::uint32 getDailyActivateInstanceCount() const;

	const CRoleConInstanceBriefData & getRoleConInstanceBriefData() const;

	void reportConStageResult(BSLib::uint32 a_score, CContinuousStageResultData & a_conStageResult, CConInstanceProgressData & a_conInstanceProgress);

	BSLib::uint32 getDailyFreeRollFastClearStageCount() const;
	void setDailyFreeRollFastClearStageCount(BSLib::uint32 a_count);

	const BSLib::Utility::CHashMap<BSLib::uint32, CConInstanceProgressData> & getConInstanceDataMap() const;

	BSLib::uint32 getConStageScore(BSLib::uint32 a_instanceTPID, BSLib::uint32 a_stageIndex) const;
public:
	CRoleConInstanceBriefData m_roleConInstanceBriefData;
	BSLib::Utility::CHashMap<BSLib::uint32, CConInstanceProgressData> m_hashConInstanceData;
};

class CGreedLandInfo
{
public:
	CGreedLandInfo();
	~CGreedLandInfo();
public:
	void serializeTo(BSLib::Utility::CStream & a_stream) const;
public:
	BSLib::uint32 m_curTickets;
	BSLib::uint32 m_maxTicketsCount;
	BSLib::uint32 m_nextUpdateTimeRemaining;
};

///////////////////////////////////////////////////////////////////////////////////
class CStageReportResult
{
public:
	CStageReportResult();
	~CStageReportResult();
public:
	bool m_isWin;
	BSLib::uint32 m_star;
	BSLib::int32 m_useTime;
	BSLib::uint32 m_score;
	std::vector<BSLib::uint32> m_clearedRandomMonster;
};


class CChallengeInfo
{
public:
	CChallengeInfo();
	~CChallengeInfo();
public:
	void serializeFrom(BSLib::Utility::CStream & a_stream);
	void reset();
public:
	EChallengeType m_type;
	BSLib::uint64 m_param;
	bool m_useDiamond;
};





}//GM

}//SceneSystem

}//GSLib




#endif
