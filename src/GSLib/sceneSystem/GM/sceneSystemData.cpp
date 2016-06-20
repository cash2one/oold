//////////////////////////////////////////////////////////////////////
//	created:	2014/12/19
//	filename: 	GSLib\sceneSystem\GM\sceneSystemData.cpp
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <BSLib/utility/stream.h>
#include <GSLib/sceneSystem/GM/sceneSystemData.h>
#include <GSLib/sceneSystem/GM/sceneSystemDataMgr.h>
#include <GSLib/sceneSystem/GM/scene.h>
#include <GSLib/sceneSystem/GM/sceneAttr.h>
#include <BSLib/utility/random.h>
#include <GSLib/sceneSystem/GM/sceneSystemGM.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

//////////////////////////////////////////////////////////////////////////////////////////////////
CRoleStoryInstanceProgress::CRoleStoryInstanceProgress()
:m_instanceTPID(1)
,m_stageIndex(0)
{

}

CRoleStoryInstanceProgress::~CRoleStoryInstanceProgress()
{

}
//////////////////////////////////////////////////////////////////////////////////
CRoleInstanceStarPrize::CRoleInstanceStarPrize()
:m_instanceTPID(0)
,m_star(0)
{

}

CRoleInstanceStarPrize::~CRoleInstanceStarPrize()
{

}

//////////////////////////////////////////////////////////////////////////////////
CStagePrizeAttr::CStagePrizeAttr()
{

}

CStagePrizeAttr::~CStagePrizeAttr()
{

}

void CStagePrizeAttr::append(const CStagePrizeAttr &rhs)
{
	m_vecStagePrize.insert(m_vecStagePrize.end(), rhs.m_vecStagePrize.begin(), rhs.m_vecStagePrize.end());
	m_vecRandomDrops.insert(m_vecRandomDrops.end(), rhs.m_vecRandomDrops.begin(), rhs.m_vecRandomDrops.end());
	m_vecBossDrops.insert(m_vecBossDrops.end(), rhs.m_vecBossDrops.begin(), rhs.m_vecBossDrops.end()); 
	m_vecCertainlyDrops.insert(m_vecCertainlyDrops.end(), rhs.m_vecCertainlyDrops.begin(), rhs.m_vecCertainlyDrops.end());
	m_vecEliteDrops.insert(m_vecEliteDrops.end(), rhs.m_vecEliteDrops.begin(), rhs.m_vecEliteDrops.end());
}

//////////////////////////////////////////////////////////////////////////////////
CDropMonsterAttr::CDropMonsterAttr()
:m_ID(0)
,m_dropType(None)
,m_weight(100)
,m_totalWeight(100)
{

}

CDropMonsterAttr::~CDropMonsterAttr()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////
CStageTemplate::CStageTemplate()
:m_difficulty(0)
,m_stageUnitCount(0)
,m_unitBatchCount(0)
,m_minStageUnitBatchCount(0)
,m_maxStageUnitBatchCount(0)
{

}

CStageTemplate::~CStageTemplate()
{

}

//////////////////////////////////////////////////////////////////////////////////
CMonsterAttrBatch::CMonsterAttrBatch()
{

}

void CMonsterAttrBatch::addMonsterAttr(const CDropMonsterAttr & a_monsterAttr)
{
	m_vecMonsterAttr.push_back(a_monsterAttr);	
}

CMonsterAttrBatch::~CMonsterAttrBatch()
{

}

std::vector<CDropMonsterAttr>::size_type CMonsterAttrBatch::size() const
{
	return m_vecMonsterAttr.size();
}

//////////////////////////////////////////////////////////////////////////////////
CMonsterBatch::CMonsterBatch()
:m_batchIndex(-1)
{

}

CMonsterBatch::~CMonsterBatch()
{

}

void CMonsterBatch::addMonster(const CMonster & a_monster)
{
	m_vecMonster.push_back(a_monster);
}

BSLib::uint32 CMonsterBatch::size() const
{
	return m_vecMonster.size();
}

void CMonsterBatch::serializeTo(BSLib::Utility::CStream & stream) const
{
	stream << m_batchIndex;
	BSLib::uint16 count = (BSLib::uint16)m_vecMonster.size();
	stream << count;
	for (BSLib::uint16 i = 0; i < count; ++i) {
		m_vecMonster[i].serializeTo(stream);
	}
}

//////////////////////////////////////////////////////////////////////////////////
CStageUnitMonster::CStageUnitMonster()
{

}

CStageUnitMonster::~CStageUnitMonster()
{

}

void CStageUnitMonster::addMonsterBatch(const CMonsterBatch & a_monsterBatch)
{
	m_batchMonster.push_back(a_monsterBatch);		
}

void CStageUnitMonster::serializeTo(BSLib::Utility::CStream & stream) const
{
	BSLib::uint16 count = (BSLib::uint16)m_batchMonster.size();
	stream << count;
	for (BSLib::uint16 i = 0; i < count; ++i) {
		m_batchMonster[i].serializeTo(stream);
	}
	stream << m_randomElite.isValid();
	if (m_randomElite.isValid()) {
		m_randomElite.serializeTo(stream);
	}
}

//////////////////////////////////////////////////////////////////////////////////
CStageMonster::CStageMonster()
:m_isValid(false)
{

}

CStageMonster::~CStageMonster()
{

}

void CStageMonster::addStageUnit(const CStageUnitMonster & a_stageUnitMonster)
{
	m_vecMonster.push_back(a_stageUnitMonster);
}

void CStageMonster::clear()
{
	m_vecMonster.clear();
	m_vecDropMonster.clear();	
	m_vecDropMonster.clear();
	m_isValid = false;
}

void CStageMonster::serializeTo(BSLib::Utility::CStream & stream) const
{
	BSLib::uint16 count = (BSLib::uint16)m_vecMonster.size();
	stream << count;
	for (BSLib::uint16 i = 0; i < count; ++i) {
		m_vecMonster[i].serializeTo(stream);
	}
}

void CStageMonster::addDropMonster(const CMonster & a_dropMonster)
{
	m_vecDropMonster.push_back(a_dropMonster);
}

void CStageMonster::setValid(bool a_value)
{
	m_isValid = a_value;
}

bool CStageMonster::isValid() const
{
	return m_isValid;
}

//////////////////////////////////////////////////////////////////////////////////
CStageUnitAttr::CStageUnitAttr()
:m_id(0)
,m_type(0)
,m_bossID(0)
{
}

CStageUnitAttr::~CStageUnitAttr()
{
}

void CStageUnitAttr::addMonsterBatchAttr(const CMonsterAttrBatch &a_monsterAttrBatch)
{
	m_vecMonsterAttrBatch.push_back(a_monsterAttrBatch);
}

std::vector<CMonsterAttrBatch>::size_type CStageUnitAttr::size() const
{
	return m_vecMonsterAttrBatch.size();
}

//////////////////////////////////////////////////////////////////////////////////
CStageAttr::CStageAttr(ESceneType a_sceneType)
:CSceneAttr(a_sceneType)
,m_instanceType(EINSTANCE_TYPE_NONE)
,m_difficulty(0)
,m_costVitality(0)
,m_dailyEnterCount(0)
,m_prizeExp(0)
,m_prizeGold(0)
,m_dropItemIDStar1(0)
,m_dropItemIDStar2(0)
,m_dropItemIDStar3(0)
,m_reviveCount(0)
,m_autoGetSkillTPID(0)
,m_instanceTPID(0)
,m_stageIndex(0)
,m_preStage(0)
,m_bossID(0)
{
	m_hashStageUnits.clear();
	m_vecUnits.clear();
}

CStageAttr::~CStageAttr()
{
}

BSLib::uint32 CStageAttr::getInstanceTPID() const
{
	return m_instanceTPID;
}

BSLib::uint16 CStageAttr::getStageIndex() const
{
	return m_stageIndex;
}

BSLib::uint32 CStageAttr::getPreStage() const
{
	return m_preStage;
}

BSLib::uint32 CStageAttr::getDropItem(BSLib::int8 a_star) const
{
	BSLib::uint32 dropItemTable = 0;
	if (a_star == 1) {
		dropItemTable = m_dropItemIDStar1;
	} else if (a_star == 2) {
		dropItemTable = m_dropItemIDStar2;
	} else if(a_star == 3) {
		dropItemTable = m_dropItemIDStar3;
	}
	return dropItemTable;
}

BSLib::uint32 CStageAttr::getExp() const
{
	return m_prizeExp;
}

BSLib::uint32 CStageAttr::getGold() const
{
	return m_prizeGold;
}

BSLib::uint16 CStageAttr::getMaxDailyEnterTimes() const
{
	return m_dailyEnterCount;
}

BSLib::uint32 CStageAttr::getBossID() const
{
	return m_bossID;
}

GSLib::SceneSystem::GM::EInstanceType CStageAttr::getInstanceType() const
{
	return m_instanceType;
}

BSLib::uint32 CStageAttr::getCostVitality() const
{
	return m_costVitality;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CMonster::CMonster()
:m_type(None)
,m_index(0)
,m_monsterAttr(NULL)
{

}

CMonster::~CMonster()
{

}

bool CMonster::isValid() const
{
	return m_index > 0;
}

void CMonster::serializeTo(BSLib::Utility::CStream & stream) const
{
	stream << m_index;
	BSLib::uint16 type = (BSLib::uint16)m_type;
	stream << type;
	BSLib::uint16 count = (BSLib::uint16)m_vecDropItem.size();
	stream << count;
	for (BSLib::uint16 i = 0; i < count; ++i) {
		m_vecDropItem[i].serializeTo(stream);
	}
}

//////////////////////////////////////////////////////////////////////////////////
CInstanceAttr::CInstanceAttr()
:m_TPID(0)
,m_instanceType(EINSTANCE_TYPE_NONE)
,m_unlockInstanceTPID(0)
,m_city(0)
{
}

CInstanceAttr::~CInstanceAttr()
{

}

EInstanceType CInstanceAttr::getInstanceType() const
{
	return m_instanceType;
}

BSLib::uint16 CInstanceAttr::stageSize() const
{
	return (BSLib::uint16)m_vecStage.size();
}

EInstanceType CInstanceAttr::getType() const
{
	return m_instanceType;
}

const CStageAttr *CInstanceAttr::getStageAttr(BSLib::uint16 a_stageIndex)
{
	if (a_stageIndex < (BSLib::uint16)m_vecStage.size()) {
		return m_vecStage[a_stageIndex];
	}
	return NULL;
}

BSLib::uint32 CInstanceAttr::getUnlockInstanceTPID() const
{
	return m_unlockInstanceTPID;
}

////////////////////////////////////////////////////////////////////////////////////////////
CFinishStage::CFinishStage()
:m_instanceID(0)
,m_stageIndex(0)
,m_star(0)
,m_dailyEnteredTimes(0)
,m_lastResetTime(0)
,m_dailyRestoreCount(0)
{

}

CFinishStage::~CFinishStage()
{

}

bool CFinishStage::operator==(const CFinishStage& stageData) const
{
	return stageData.m_stageIndex == m_stageIndex;
}

void CFinishStage::serializeTo(BSLib::Utility::CStream &stream) const
{
	stream << m_stageIndex;	
	stream << m_star;
	stream << m_dailyEnteredTimes;
	stream << m_dailyRestoreCount;
	stream << getNextRestoreStageRequireDiamond();
}

bool CFinishStage::isValid() const
{
	return m_instanceID > 0;
}

BSLib::int8 CFinishStage::getStar() const
{
	return m_star;
}

BSLib::uint16 CFinishStage::getDailyEnteredTimes() const
{
	return m_dailyEnteredTimes;
}

BSLib::int32 CFinishStage::getLastResetTime() const
{
	return m_lastResetTime;
}

BSLib::uint32 CFinishStage::getNextRestoreStageRequireDiamond() const
{
	return (m_dailyRestoreCount + 3) * (m_dailyRestoreCount + 3) - 6;
}

BSLib::uint32 CFinishStage::getDailyRestoreCount() const
{
	return m_dailyRestoreCount;
}

////////////////////////////////////////////////////////////////////////////////////////////
CFinishInstanceData::CFinishInstanceData(const CInstanceAttr *a_instanceAttr)
{
	if (a_instanceAttr != NULL) {
		m_instanceAttr = a_instanceAttr;
		if (a_instanceAttr->stageSize() > 0) {
			m_vecFinishStage.assign(a_instanceAttr->stageSize(), CFinishStage());
		}
	}
}

CFinishInstanceData::~CFinishInstanceData()
{

}

const CInstanceAttr *CFinishInstanceData::getInstanceAttr() const
{
	return m_instanceAttr;
}

std::vector<CFinishStage>& CFinishInstanceData::getFinishStage() 
{
	return m_vecFinishStage;
}

void CFinishInstanceData::setStage(BSLib::uint16 a_index, CFinishStage & a_finishStageData)
{
	if (a_index < (BSLib::uint16)m_vecFinishStage.size()) {
		m_vecFinishStage[a_index] = a_finishStageData;
	}
}

bool CFinishInstanceData::hasFinished() const
{
	for (std::vector<CFinishStage>::const_iterator itr = m_vecFinishStage.begin(); itr != m_vecFinishStage.end(); ++itr) {
		if (!itr->isValid()) {
			return false;
		}
	}
	return true;
}

BSLib::int8 CFinishInstanceData::getStars() const
{
	BSLib::int8 count = 0;
	for (std::vector<CFinishStage>::const_iterator itr = m_vecFinishStage.begin(); itr != m_vecFinishStage.end(); ++itr) {
		count += itr->getStar();
	}
	return count;
}

CFinishStage * CFinishInstanceData::getStage(BSLib::uint16 a_stageIndex)
{
	if (a_stageIndex < m_vecFinishStage.size()) {
		return &m_vecFinishStage[a_stageIndex];
	}
	return NULL;
}

const std::vector<CFinishStage> & CFinishInstanceData::getStages() const
{
	return m_vecFinishStage;
}


////////////////////////////////////////////////////////////////////////////////////////////////
CRoleStage::CRoleStage()
:m_instanceTPID(0)
,m_stageIndex(0)
{

}

CRoleStage::~CRoleStage()
{

}

bool CRoleStage::isInStage() const
{
	return m_instanceTPID > 0;
}

void CRoleStage::clear()
{
	m_instanceTPID = 0;
	m_stageIndex = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////
CRoleStageSystemData::CRoleStageSystemData()
:m_dailyGetHelperCount(0)
,m_greedLandTickets(0)
,m_lastGreedLandUpdateTime(0)
,m_lastUpdateTime(0)
{

}

CRoleStageSystemData::~CRoleStageSystemData()
{

}

void CRoleStageSystemData::reset()
{
	m_dailyGetHelperCount = 0;	
	m_lastUpdateTime = (BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
}

BSLib::uint32 CRoleStageSystemData::getGreedLandEntrances() const
{
	return m_greedLandTickets;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CStagePrize::CStagePrize()
:m_exp(0)
,m_gold(0)
{

}

CStagePrize::~CStagePrize()
{

}

void CStagePrize::serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_exp;
	stream << m_gold;
	BSLib::uint16 count = m_vecPrizeItem.size();
	stream << count;
	for (std::vector<GSLib::ItemSystem::GM::CPrizeItem>::const_iterator itr = m_vecPrizeItem.begin(); itr != m_vecPrizeItem.end(); ++itr) {
		itr->serializeTo(stream);
	}
	count = m_elitePrizeItem.size();
	stream << count;
	for (std::vector<GSLib::ItemSystem::GM::CPrizeItem>::const_iterator itr = m_elitePrizeItem.begin(); itr != m_elitePrizeItem.end(); ++itr) {
		itr->serializeTo(stream);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
CInstanceStarPrizeAttr::CInstanceStarPrizeAttr()
:m_instanceTPID(0)
{

}

CInstanceStarPrizeAttr::~CInstanceStarPrizeAttr()
{

}

void CInstanceStarPrizeAttr::getStarLevelPrize(BSLib::uint16 a_star, std::vector<ItemSystem::GM::CPrizeItem> &vecInstancePrize) const
{
	BSLib::Utility::CHashMap< BSLib::uint16, std::vector<ItemSystem::GM::CPrizeItem> >::const_iterator itr = m_hashStarPrize.find(a_star);
	if (itr != m_hashStarPrize.end()) {
		vecInstancePrize = itr->second;
	}
}

BSLib::uint16 CInstanceStarPrizeAttr::getNextStarLevel(BSLib::uint16 a_curStar) const
{
	BSLib::uint16 nextStarLevel = -1;
	for (BSLib::Utility::CHashMap< BSLib::uint16, std::vector<ItemSystem::GM::CPrizeItem> >::const_iterator itr = m_hashStarPrize.begin(); itr != m_hashStarPrize.end(); ++itr) {
		BSLib::uint16 star = itr->first;
		if (star > a_curStar && nextStarLevel > star) {
			nextStarLevel = star;
		}
	}
	nextStarLevel = nextStarLevel == (BSLib::uint16)-1 ? 0 : nextStarLevel;
	return nextStarLevel;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CSceneRoleInfo::CSceneRoleInfo()
:m_roleTPID(0)
,m_roleName("")
,m_level(0)
,m_VIPLevel(0)
,m_combatPower(0)
,m_fashionTPID(0)
{

}

CSceneRoleInfo::~CSceneRoleInfo()
{

}

void CSceneRoleInfo::serializeTo(BSLib::Utility::CStream & a_stream) const
{
	m_roleKey.serializeTo(a_stream);
	a_stream << m_roleTPID;
	a_stream << m_roleName;
	a_stream << m_level;
	a_stream << m_VIPLevel;
	a_stream << m_fashionTPID;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
CRoleInstanceData::CRoleInstanceData()
:m_tryEnterStageAttr(NULL)
{

}

CRoleInstanceData::~CRoleInstanceData()
{

}

void CRoleInstanceData::setCurStage(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_stageIndex)
{
	m_curStage.m_instanceTPID = a_instanceTPID;
	m_curStage.m_stageIndex = a_stageIndex;
}

CRoleStage& CRoleInstanceData::getCurStage()
{
	return m_curStage;
}

BSLib::uint32 CRoleInstanceData::getCurInstanceTPID() const
{
	return m_curStage.m_instanceTPID;
}

BSLib::uint16 CRoleInstanceData::getCurStageIndex() const
{
	return m_curStage.m_stageIndex;
}

bool CRoleInstanceData::isInStage() const
{
	return m_curStage.isInStage();
}

void CRoleInstanceData::exitScene()
{
	m_curStage.clear();
}

void CRoleInstanceData::setStoryInstanceProgress(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_stageIndex)
{
	m_roleStoryInstanceProgress.m_instanceTPID = a_instanceTPID;
	m_roleStoryInstanceProgress.m_stageIndex = a_stageIndex;
}

void CRoleInstanceData::setStoryInstanceProgress(const CRoleStoryInstanceProgress &a_storyInstanceProgress)
{
	m_roleStoryInstanceProgress = a_storyInstanceProgress;
}

BSLib::Utility::CHashMap<BSLib::uint32, CRoleInstanceStarPrize> & CRoleInstanceData::getRoleInstancPrizeMap()
{
	return m_hashRoleInstancePrize;
}

const CRoleStoryInstanceProgress & CRoleInstanceData::getProgressData() const
{
	return m_roleStoryInstanceProgress;
}

BSLib::uint32 CRoleInstanceData::getProgressInstanceTPID() const
{
	return m_roleStoryInstanceProgress.m_instanceTPID;
}

BSLib::uint16 CRoleInstanceData::getProgressStageIndex() const
{
	return m_roleStoryInstanceProgress.m_stageIndex;
}

CFinishInstanceData * CRoleInstanceData::getFinishInstanceData(BSLib::uint32 a_instanceTPID)
{
	BSLib::Utility::CHashMap<BSLib::uint32, CFinishInstanceData >::iterator itr = m_hashFinishInstanceData.find(a_instanceTPID);
	if (itr != m_hashFinishInstanceData.end()) {
		return &(itr->second);
	}

	return NULL;
}

CFinishStage *CRoleInstanceData::getStage(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_stageIndex)
{
	BSLib::Utility::CHashMap<BSLib::uint32, CFinishInstanceData >::iterator itr = m_hashFinishInstanceData.find(a_instanceTPID);
	if (itr != m_hashFinishInstanceData.end()) {
		return itr->second.getStage(a_stageIndex);
	}
	return NULL;
}

CFinishStage *CRoleInstanceData::getStage(BSLib::uint32 a_stageTPID)
{
	const CStageAttr * stageAttr = CSceneSystemDataMgr::singleton().getStageAttr(a_stageTPID);	
	if (stageAttr != NULL) {
		return getStage(stageAttr->getInstanceTPID(), stageAttr->getStageIndex());	
	}

	return NULL;
}

bool CRoleInstanceData::hasFinishInstance(BSLib::uint32 a_instanceTPID) const
{
	BSLib::Utility::CHashMap<BSLib::uint32, CFinishInstanceData >::const_iterator itr = m_hashFinishInstanceData.find(a_instanceTPID);	
	if (itr != m_hashFinishInstanceData.end()) {
		return itr->second.hasFinished();
	}
	return false;
}

void CRoleInstanceData::reportStageResult(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_stageIndex, BSLib::int8 a_star, CFinishStage & a_finsStageData)
{
	const CInstanceAttr * instanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(a_instanceTPID);
	if (instanceAttr != NULL) {
		BSLib::Utility::CHashMap< BSLib::uint32, CFinishInstanceData >::iterator itr = m_hashFinishInstanceData.find(a_instanceTPID);
		if (itr != m_hashFinishInstanceData.end()) { //existed
			std::vector<CFinishStage> &vecFinishStage = itr->second.getFinishStage();
			CFinishStage &finishStage = vecFinishStage[a_stageIndex];
			finishStage.m_instanceID = a_instanceTPID;
			finishStage.m_stageIndex  = a_stageIndex;
			++finishStage.m_dailyEnteredTimes;
			if (finishStage.m_lastResetTime == 0) {
				finishStage.m_lastResetTime = CSceneSystemGM::singleton().getLastInstanceStageResetTime();
			}
			finishStage.m_star = a_star > finishStage.m_star ? a_star : finishStage.m_star;
			a_finsStageData = finishStage;
		} else { //not exists
			CFinishInstanceData roleInstance(instanceAttr);
			std::vector<CFinishStage> &vecFinishStage = roleInstance.getFinishStage();
			CFinishStage &finishStage = vecFinishStage[a_stageIndex];
			finishStage.m_instanceID = a_instanceTPID;
			finishStage.m_stageIndex = a_stageIndex;
			finishStage.m_star = a_star;
			finishStage.m_dailyEnteredTimes = 1;
			finishStage.m_lastResetTime = CSceneSystemGM::singleton().getLastInstanceStageResetTime();
			a_finsStageData = finishStage;
			m_hashFinishInstanceData.setValue(a_instanceTPID, roleInstance);
		}	
	}
}

void CRoleInstanceData::addStageData(CFinishStage & a_finishStageData)
{
	const CStageAttr *stageAttr = CSceneSystemDataMgr::singleton().getStageAttr(a_finishStageData.m_instanceID, a_finishStageData.m_stageIndex);
	const CInstanceAttr *instanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(stageAttr->m_instanceTPID);
	if (stageAttr != NULL && instanceAttr != NULL) {
		BSLib::Utility::CHashMap<BSLib::uint32, CFinishInstanceData>::iterator itr = m_hashFinishInstanceData.find(stageAttr->m_instanceTPID);
		if (itr == m_hashFinishInstanceData.end()) {
			CFinishInstanceData instance(instanceAttr);
			instance.setStage(stageAttr->m_stageIndex, a_finishStageData);
			m_hashFinishInstanceData.setValue(instanceAttr->m_TPID, instance);
		} else {
			itr->second.setStage(stageAttr->m_stageIndex, a_finishStageData);
			std::vector<CFinishStage> &vecFinishData = itr->second.getFinishStage();
			vecFinishData[stageAttr->m_stageIndex] = a_finishStageData;
		}
	}
}

void CRoleInstanceData::addInstancePrizeData(CRoleInstanceStarPrize & a_instancePrize)
{
	BSLib::Utility::CHashMap<BSLib::uint32, CRoleInstanceStarPrize>::iterator itr = m_hashRoleInstancePrize.find(a_instancePrize.m_instanceTPID);
	if (itr == m_hashRoleInstancePrize.end()) {
		m_hashRoleInstancePrize.setValue(a_instancePrize.m_instanceTPID, a_instancePrize);
	} 
}

BSLib::uint16 CRoleInstanceData::getCurrentInstancePrizeStar(BSLib::uint32 a_instanceTPID) const
{
	BSLib::Utility::CHashMap<BSLib::uint32, CRoleInstanceStarPrize>::const_iterator itr = m_hashRoleInstancePrize.find(a_instanceTPID);
	if (itr != m_hashRoleInstancePrize.end()) {
		return itr->second.m_star;
	} 
	return 0;
}

BSLib::uint16 CRoleInstanceData::getNextInstancePrizeStar(BSLib::uint32 a_instanceTPID) const
{
	const CInstanceStarPrizeAttr *instanceStarPrizeAttr = CSceneSystemDataMgr::singleton().getInstanceStarPrizeAttr(a_instanceTPID);
	if (instanceStarPrizeAttr != NULL) {
		BSLib::uint16 curPrizeStar = getCurrentInstancePrizeStar(a_instanceTPID);
		return instanceStarPrizeAttr->getNextStarLevel(curPrizeStar);
	}
	return 0;
}

CRoleInstanceStarPrize * CRoleInstanceData::getInstanceStarPrize(BSLib::uint32 a_instanceTPID)
{
	BSLib::Utility::CHashMap<BSLib::uint32, CRoleInstanceStarPrize>::iterator itr = m_hashRoleInstancePrize.find(a_instanceTPID);
	if (itr != m_hashRoleInstancePrize.end()) {
		return &(itr->second);
	} 
	return NULL;
}

BSLib::int32 CRoleInstanceData::getLastStageGetHelpUpdateTime() const
{
	return m_roleStageSystemData.m_lastUpdateTime;
}

void CRoleInstanceData::onRoleStageGetHelpReset()
{
	m_roleStageSystemData.reset();
}

BSLib::uint32 CRoleInstanceData::getLastGreedLandTicketsUpdateTime() const
{
	return m_roleStageSystemData.m_lastGreedLandUpdateTime;
}

void CRoleInstanceData::setLastGreedLandTicktsUpdateTime(BSLib::int32 a_updateTime)
{
	m_roleStageSystemData.m_lastGreedLandUpdateTime = a_updateTime;
}

BSLib::uint32 CRoleInstanceData::getGreedLandTicketsCount() const
{
	return m_roleStageSystemData.m_greedLandTickets;
}

void CRoleInstanceData::setGreedLandTicketsCount(BSLib::uint32 a_count)
{
	m_roleStageSystemData.m_greedLandTickets = a_count;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CRoleConInstanceBriefData::CRoleConInstanceBriefData()
:m_dailyActivateInstanceCount(DAILY_ACTIVATE_INSTANCE_COUNT)
,m_dailyFreeRollFastClearStageCount(DAILY_FREE_ROLL_FAST_CLEAR_STAGE_COUNT)
,m_lastResetTime(0)
,m_curEnteredInstanceTPID(0)
,m_curEnteredStageIndex(0)
{

}

CRoleConInstanceBriefData::~CRoleConInstanceBriefData()
{

}

void CRoleConInstanceBriefData::onReset()
{
	m_dailyActivateInstanceCount = DAILY_ACTIVATE_INSTANCE_COUNT;
	m_dailyFreeRollFastClearStageCount = DAILY_FREE_ROLL_FAST_CLEAR_STAGE_COUNT;
	m_lastResetTime = (BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
}

void CRoleConInstanceBriefData::exitScene()
{
	m_curEnteredInstanceTPID = 0;
	m_curEnteredStageIndex = 0;
}

BSLib::uint32 CRoleConInstanceBriefData::getDailyFreeRollFastClearStageCount() const
{
	return m_dailyFreeRollFastClearStageCount;
}

void CRoleConInstanceBriefData::setDailyFreeRollFastClearStageCount(BSLib::uint32 a_count)
{
	m_dailyFreeRollFastClearStageCount = a_count;
}

void CRoleConInstanceBriefData::setDailyActivateInstanceCount(BSLib::uint32 a_count)
{
	m_dailyActivateInstanceCount = a_count;
}

BSLib::uint32 CRoleConInstanceBriefData::getDailyActivateInstanceCount() const
{
	return m_dailyActivateInstanceCount;
}


////////////////////////////////////////////////////////////////////////////////////////////////
CContinuousStageResultData::CContinuousStageResultData()
:m_instanceTPID(0)
,m_stageIndex(0)
,m_score(0)
{

}

CContinuousStageResultData::~CContinuousStageResultData()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////
CConInstanceProgressData::CConInstanceProgressData()
:m_isActivated(false)
,m_curDayStageIndex(0)
,m_maxClearStageIndex(0)
,m_instanceAttr(NULL)
{
	m_vecStageResult.assign(MAX_CONTINUOUS_STAGE_COUNT, CContinuousStageResultData());	
}

CConInstanceProgressData::~CConInstanceProgressData()
{

}

void CConInstanceProgressData::onReset()
{
	m_isActivated = false;
	m_curDayStageIndex = 0;
}

BSLib::uint32 CConInstanceProgressData::stageSize() const
{
	return (BSLib::uint32)m_vecStageResult.size();
}

void CConInstanceProgressData::addStageResult(CContinuousStageResultData & a_stageResult)
{
	if (a_stageResult.m_stageIndex < m_vecStageResult.size()) {
		m_vecStageResult[a_stageResult.m_stageIndex] = a_stageResult;
	}
}

bool CConInstanceProgressData::isActivated() const
{
	return m_isActivated;
}

void CConInstanceProgressData::setCurDayStageIndex(BSLib::uint32 a_curDayStageIndex)
{
	m_curDayStageIndex = a_curDayStageIndex;	
}

BSLib::uint32 CConInstanceProgressData::getCurDayStageIndex() const
{
	return m_curDayStageIndex;
}

BSLib::uint32 CConInstanceProgressData::getMaxClearStageIndex() const
{
	return m_maxClearStageIndex;
}

BSLib::uint32 CConInstanceProgressData::getInstanceStageSize() const
{
	if (m_instanceAttr != NULL) {
		return m_instanceAttr->stageSize();
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CRoleContinuousStageData::CRoleContinuousStageData()
{
}

CRoleContinuousStageData::~CRoleContinuousStageData()
{

}

void CRoleContinuousStageData::onDailyRest()
{
	m_roleConInstanceBriefData.onReset();
	for (BSLib::Utility::CHashMap<BSLib::uint32, CConInstanceProgressData>::iterator itr = m_hashConInstanceData.begin(); itr != m_hashConInstanceData.end(); ++itr) {
		itr->second.onReset();
	}
}

void CRoleContinuousStageData::exitScene()
{
	m_roleConInstanceBriefData.exitScene();
}

BSLib::int32 CRoleContinuousStageData::getLastResetTime() const
{
	return m_roleConInstanceBriefData.m_lastResetTime;
}

BSLib::uint32 CRoleContinuousStageData::getCurEnteredConInstanceTPID() const
{
	return m_roleConInstanceBriefData.m_curEnteredInstanceTPID;
}

BSLib::uint32 CRoleContinuousStageData::getCurEnteredConStageIndex() const
{
	return m_roleConInstanceBriefData.m_curEnteredStageIndex;
}

void CRoleContinuousStageData::setCurEnteredStage(BSLib::uint32 a_instanceTPID, BSLib::uint32 a_stageIndex)
{
	m_roleConInstanceBriefData.m_curEnteredInstanceTPID = a_instanceTPID;
	m_roleConInstanceBriefData.m_curEnteredStageIndex = a_stageIndex;
}

CConInstanceProgressData * CRoleContinuousStageData::getConInstanceProgressData(BSLib::uint32 a_instanceTPID)
{
	BSLib::Utility::CHashMap<BSLib::uint32, CConInstanceProgressData>::iterator itr = m_hashConInstanceData.find(a_instanceTPID);
	if (itr != m_hashConInstanceData.end()) {
		return &(itr->second);
	}
	return NULL;
}

CConInstanceProgressData * CRoleContinuousStageData::getCurConInstanceProgressData()
{
	return getConInstanceProgressData(m_roleConInstanceBriefData.m_curEnteredInstanceTPID);
}

void CRoleContinuousStageData::addConInstanceProgressData(const CConInstanceProgressData & a_conInstanceProgressData)
{
	BSLib::Utility::CHashMap<BSLib::uint32, CConInstanceProgressData>::iterator itr = m_hashConInstanceData.find(a_conInstanceProgressData.m_instanceTPID);
	if (itr != m_hashConInstanceData.end()) {
		//CConInstanceProgressData &conInstanceData = itr->second;
		//conInstanceData.m_isActivated = a_conInstanceProgressData.m_isActivated;
		//conInstanceData.m_curDayStageIndex = a_conInstanceProgressData.m_curDayStageIndex;
		//conInstanceData.m_maxClearStageIndex = a_conInstanceProgressData.m_maxClearStageIndex;
	} else {
		m_hashConInstanceData.setValue(a_conInstanceProgressData.m_instanceTPID, a_conInstanceProgressData);
	}
}
void CRoleContinuousStageData::addConStageResult(CContinuousStageResultData & a_conStageResult, const CInstanceAttr *a_instanceAttr)
{
	BSLib::Utility::CHashMap<BSLib::uint32, CConInstanceProgressData>::iterator itr = m_hashConInstanceData.find(a_conStageResult.m_instanceTPID);
	if (itr != m_hashConInstanceData.end()) {
		itr->second.addStageResult(a_conStageResult);
	} else {
		CConInstanceProgressData instanceProgressData;
		instanceProgressData.m_instanceTPID = a_conStageResult.m_instanceTPID;
		instanceProgressData.m_instanceAttr = a_instanceAttr;
		instanceProgressData.addStageResult(a_conStageResult);
		m_hashConInstanceData.setValue(a_conStageResult.m_instanceTPID, instanceProgressData);
	}
}

void CRoleContinuousStageData::setDailyActivateInstanceCount(BSLib::uint32 a_count)
{
	m_roleConInstanceBriefData.setDailyActivateInstanceCount(a_count);
}

BSLib::uint32 CRoleContinuousStageData::getDailyActivateInstanceCount() const
{
	return m_roleConInstanceBriefData.getDailyActivateInstanceCount();
}

const CRoleConInstanceBriefData & CRoleContinuousStageData::getRoleConInstanceBriefData() const
{
	return m_roleConInstanceBriefData;	 
}

void CRoleContinuousStageData::reportConStageResult(BSLib::uint32 a_score, CContinuousStageResultData & a_conStageResult, CConInstanceProgressData & a_conInstanceProgress)
{
	if (m_roleConInstanceBriefData.m_curEnteredInstanceTPID > 0) {
		BSLib::Utility::CHashMap<BSLib::uint32, CConInstanceProgressData>::iterator itr = m_hashConInstanceData.find(m_roleConInstanceBriefData.m_curEnteredInstanceTPID);
		if (itr != m_hashConInstanceData.end()) {
			CConInstanceProgressData & conInstanceProgressData = itr->second;
			if (conInstanceProgressData.m_instanceAttr != NULL) {
				BSLib::uint32 nextStageIndex = conInstanceProgressData.m_curDayStageIndex + 1;
				conInstanceProgressData.m_curDayStageIndex = nextStageIndex < conInstanceProgressData.m_instanceAttr->stageSize() ? nextStageIndex : conInstanceProgressData.m_instanceAttr->stageSize();
				conInstanceProgressData.m_maxClearStageIndex = 
					conInstanceProgressData.m_curDayStageIndex > conInstanceProgressData.m_maxClearStageIndex ? conInstanceProgressData.m_curDayStageIndex :conInstanceProgressData.m_maxClearStageIndex;
				CContinuousStageResultData &conStageResult = conInstanceProgressData.m_vecStageResult[conInstanceProgressData.m_curDayStageIndex];
				conStageResult.m_instanceTPID = m_roleConInstanceBriefData.m_curEnteredInstanceTPID;
				conStageResult.m_stageIndex = m_roleConInstanceBriefData.m_curEnteredStageIndex;
				conStageResult.m_score = a_score > conStageResult.m_score ? a_score : conStageResult.m_score;
				a_conStageResult = conStageResult;
				a_conInstanceProgress = conInstanceProgressData;
			}
		}
	}
}

BSLib::uint32 CRoleContinuousStageData::getDailyFreeRollFastClearStageCount() const
{
	return m_roleConInstanceBriefData.getDailyFreeRollFastClearStageCount();
}

void CRoleContinuousStageData::setDailyFreeRollFastClearStageCount(BSLib::uint32 a_count)
{
	m_roleConInstanceBriefData.setDailyFreeRollFastClearStageCount(a_count);
}

const BSLib::Utility::CHashMap<BSLib::uint32, CConInstanceProgressData> & CRoleContinuousStageData::getConInstanceDataMap() const
{
	return m_hashConInstanceData;		 
}

BSLib::uint32 CRoleContinuousStageData::getConStageScore(BSLib::uint32 a_instanceTPID, BSLib::uint32 a_stageIndex) const
{
	BSLib::Utility::CHashMap<BSLib::uint32, CConInstanceProgressData>::const_iterator itr = m_hashConInstanceData.find(a_instanceTPID);
	if (itr != m_hashConInstanceData.end()) {
		const CConInstanceProgressData & progressData = itr->second;
		if (a_stageIndex < progressData.getInstanceStageSize()) {
			return progressData.m_vecStageResult[a_stageIndex].m_score;
		}
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CGreedLandInfo::CGreedLandInfo()
:m_curTickets(0)
,m_maxTicketsCount(0)
,m_nextUpdateTimeRemaining(0)
{

}

CGreedLandInfo::~CGreedLandInfo()
{

}

void CGreedLandInfo::serializeTo(BSLib::Utility::CStream & a_stream) const
{
	a_stream << m_curTickets;
	a_stream << m_maxTicketsCount;
	a_stream << m_nextUpdateTimeRemaining;
}

///////////////////////////////////////////////////////////////////////////////////
CStageReportResult::CStageReportResult()
:m_isWin(false)
,m_star(0)
,m_useTime(0)
,m_score(0)
{

}

CStageReportResult::~CStageReportResult()
{

}

CChallengeInfo::CChallengeInfo()
:m_type(ECHALLENGE_TYPE_RANKING_ROLE)
,m_param(0)
,m_useDiamond(false)
{

}

CChallengeInfo::~CChallengeInfo()
{

}

void CChallengeInfo::serializeFrom(BSLib::Utility::CStream & a_stream)
{
	BSLib::int8 type;
	a_stream >> type;
	m_type = (EChallengeType)type;
	a_stream >> m_param;
	a_stream >> m_useDiamond;
}

void CChallengeInfo::reset()
{
	m_type = ECHALLENGE_TYPE_RANKING_ROLE;
	m_param = 0;
	m_useDiamond = false;
}












}//GM

}//SceneSystem



}//GSLib
