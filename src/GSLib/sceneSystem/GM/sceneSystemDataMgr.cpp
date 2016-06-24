#include <GSLib/sceneSystem/GM/sceneSystemDataMgr.h>
#include <GSLib/sceneSystem/GM/reviveItem.h>
#include <BSLib/utility/string.h>
#include <BSLib/utility/file/dirInfo.h>
#include <BSLib/utility/table.h>
#include <BSLib/utility/tracer.h>
#include <GSLib/tracer.h>
#include <BSLib/utility/convert.h>
#include <GSLib/sceneSystem/GM/dropItemEntry.h>
#include <GSLib/sceneSystem/GM/dropItem.h>
#include <GSLib/sceneSystem/GM/arenaPrize.h>
#include <GSLib/sceneSystem/GM/sceneSystemData.h>
#include <GSLib/sceneSystem/GM/sceneAttr.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CSceneSystemDataMgr)

CSceneSystemDataMgr::CSceneSystemDataMgr()
:m_arenaChallengeSucPrize(NULL)
,m_arenaChallengeFailPrize(NULL)
{
	m_arenaAttr = new CSceneAttr(ESCENE_TYPE_ARENA);
	m_arenaAttr->m_sceneTPID = 1;
	m_arenaAttr->m_maxPlayers = 1;
}

bool CSceneSystemDataMgr::loadConfig(const std::string &a_configPath)
{
	BSLib::Utility::CStringA filePath(a_configPath);
	filePath += "\\scene";
	BSLib::Utility::CDirInfo::standardization(filePath);

	if (!_loadReviveItems(filePath)) {
		return false;
	}

	if (!_loadItemDropTable(filePath)) {
		return false;
	}

	if (!_loadArenaData(filePath)) {
		return false;
	}

	if (!_loadStageUnit(filePath)) {
		return false;
	}

	if (!_loadStageAttr(filePath)) {
		return false;
	}

	if (!_loadInstanceData(filePath)) {
		return false;
	}

	if (!_loadInstanceStarPrizeData(filePath)) {
		return false;
	}

	if (!_loadCityAttr(filePath)) {
		return false;
	}

	if (!_loadStageTemplate(filePath)) {
		return false;
	}

	return true;
}

CSceneSystemDataMgr::~CSceneSystemDataMgr()
{
	for (BSLib::Utility::CHashMap<BSLib::uint32, CReviveItem*>::iterator itr = m_hashReviveItems.begin(); itr != m_hashReviveItems.end(); ++itr) {
		if (itr->second != NULL) {
			delete itr->second, itr->second = NULL;
		}
	}

	for (BSLib::Utility::CHashMap<BSLib::uint32, CDropTableEntry*>::iterator itr = m_hashDropItemTable.begin(); itr != m_hashDropItemTable.end(); ++itr) {
		if (itr->second != NULL) {
			delete itr->second, itr->second = NULL;
		}
	}

	for (BSLib::Utility::CHashMap<BSLib::uint32, CArenaPrize*>::iterator itr = m_hashDailyRankPrize.begin(); itr != m_hashDailyRankPrize.end(); ++itr) {
		if (itr->second != NULL) {
			delete itr->second, itr->second = NULL;
		}
	}

	for (BSLib::Utility::CHashMap<BSLib::uint32, CStageUnitAttr*>::iterator itr = m_hashStageUnit.begin(); itr != m_hashStageUnit.end(); ++itr) {
		if (itr->second != NULL) {
			delete itr->second, itr->second = NULL;
		}
	}

	for (BSLib::Utility::CHashMap<BSLib::uint32, CStageTemplate*>::iterator itr = m_hashTemplateStage.begin(); itr != m_hashTemplateStage.end(); ++itr) {
		if (itr->second != NULL) {
			delete itr->second, itr->second = NULL;
		}
	}

	delete m_arenaChallengeSucPrize, m_arenaChallengeSucPrize = NULL;
	delete m_arenaChallengeFailPrize, m_arenaChallengeFailPrize = NULL;
	delete m_arenaAttr , m_arenaAttr = NULL;

	m_hashReviveItems.clear();
	m_hashDropItemTable.clear();
	m_hashDailyRankPrize.clear();
	m_hashStageUnit.clear();
	m_hashTemplateStage.clear();
}

const CSceneAttr* CSceneSystemDataMgr::getSceneAttr(ESceneType a_sceneType, BSLib::uint32 a_sceneTPID) const
{
	switch(a_sceneType)
	{
	case ESCENE_TYPE_CITY:
		{
			BSLib::Utility::CHashMap<BSLib::uint32, CSceneAttr*>::const_iterator itr = m_hashScene.find(a_sceneTPID);
			if (itr != m_hashScene.end()) {
				return itr->second;
			}
		}
		break;
	case ESCENE_TYPE_CONTINUOUS_STAGE:
	case ESCENE_TYPE_STAGE:
	case ESCENE_TYPE_RANDOM_STAGE:
	case ESCENE_TYPE_RANDOM_GOLD_STAGE:
	case ESCENE_TYPE_RANDOM_EXP_STAGE:
		{
			BSLib::Utility::CHashMap<BSLib::uint32, CStageAttr*>::const_iterator itr = m_hashStage.find(a_sceneTPID);
			if (itr != m_hashStage.end()) {
				if (itr->second->getSceneType() == a_sceneType) {
					return itr->second;
				}
			}
		}
		break;
	case ESCENE_TYPE_ARENA:
		{
			return m_arenaAttr;
		}
		break;
	default:
		{
			;
		}
	}
	return NULL;
}

void CSceneSystemDataMgr::addReviveItem(CReviveItem *a_reviveItem)
{
	if (a_reviveItem != NULL) {
		if (m_hashReviveItems.find(a_reviveItem->getReviveTimes()) == m_hashReviveItems.end()) {
			m_hashReviveItems.setValue(a_reviveItem->getReviveTimes(), a_reviveItem);
		}
	}
}

const CReviveItem *CSceneSystemDataMgr::getReviveItem(BSLib::uint32 a_reviveTimes)
{
	BSLib::Utility::CHashMap<BSLib::uint32, CReviveItem*>::iterator itr = m_hashReviveItems.find(a_reviveTimes);		
	if (itr != m_hashReviveItems.end()) {
		if (itr->second != NULL) {
			return itr->second;
		}
	}

	return NULL;
}

void CSceneSystemDataMgr::addDropItemTableEntry(CDropTableEntry *a_dropItemEntry)
{
	if (a_dropItemEntry != NULL) {
		if (m_hashDropItemTable.find(a_dropItemEntry->m_ID) == m_hashDropItemTable.end()) {
			m_hashDropItemTable.setValue(a_dropItemEntry->m_ID, a_dropItemEntry);
		}
	}
}

const CDropTableEntry *CSceneSystemDataMgr::getDropItemEntry(BSLib::uint32 a_ID) const
{
	BSLib::Utility::CHashMap<BSLib::uint32, CDropTableEntry*>::const_iterator itr = m_hashDropItemTable.find(a_ID);
	if (itr != m_hashDropItemTable.end()) {
		return itr->second;
	}
	return NULL;
}


const CDropItem* CSceneSystemDataMgr::getRandomDropItem(BSLib::uint32 a_ID) const
{
	BSLib::Utility::CHashMap<BSLib::uint32, CDropTableEntry*>::const_iterator itr = m_hashDropItemTable.find(a_ID);
	if (itr != m_hashDropItemTable.end()) {
		if (itr->second != NULL) {
			return itr->second->getRandomItem();
		}
	}

	return NULL;
}

void CSceneSystemDataMgr::addDailyRankPrize(BSLib::uint32 a_endRank, CArenaPrize *a_prize)
{
	if (a_endRank != 0 && a_prize != NULL) {
		m_hashDailyRankPrize.setValue(a_endRank, a_prize);
	}
}

const CArenaPrize* CSceneSystemDataMgr::getDailyRankPrize(BSLib::uint32 a_rank) const
{
	const CArenaPrize *prize = NULL;
	BSLib::uint32 last = -1;
	for (BSLib::Utility::CHashMap<BSLib::uint32, CArenaPrize*>::const_iterator itr = m_hashDailyRankPrize.begin(); itr != m_hashDailyRankPrize.end(); ++itr) {
		if (a_rank <= itr->first && last > itr->first) {
			last = itr->first;
			prize = itr->second;
		}
	}

	return prize;
}

void CSceneSystemDataMgr::addHistoryHighestRankPrize(BSLib::uint32 a_endRank, CArenaPrize* a_prize)
{
	if (a_endRank != 0 && a_prize != NULL) {
		m_hashHistoryHighestRankPrize.setValue(a_endRank, a_prize);
	}
}

const CArenaPrize* CSceneSystemDataMgr::getHistoryHighestRankPrize(BSLib::uint32 a_rank, CArenaPrize* a_prize)
{
	const CArenaPrize *prize = NULL;
	BSLib::uint32 last = -1;
	for (BSLib::Utility::CHashMap<BSLib::uint32, CArenaPrize*>::const_iterator itr = m_hashHistoryHighestRankPrize.begin(); itr != m_hashHistoryHighestRankPrize.end(); ++itr) {
		if (a_rank <= itr->first && last > itr->first) {
			last = itr->first;
			prize = itr->second;
		}
	}

	return prize;
}

void CSceneSystemDataMgr::setArenaChallengeSucPrize(CArenaPrize *a_prize)
{
	if (a_prize != NULL) {
		m_arenaChallengeSucPrize = a_prize;	
	}
}

const CArenaPrize* CSceneSystemDataMgr::getArenaChallengeSucPrize() const
{
	return m_arenaChallengeSucPrize;
}

void CSceneSystemDataMgr::setArenaChallengeFailPrize(CArenaPrize *a_prize)
{
	if (a_prize != NULL) {
		m_arenaChallengeFailPrize = a_prize;
	}
}

const CArenaPrize* CSceneSystemDataMgr::getArenaChallengeFailPrize() const
{
	return m_arenaChallengeFailPrize;
}

const CInstanceAttr * CSceneSystemDataMgr::getInstanceAttr(BSLib::uint32 a_instanceTPID) const
{
	BSLib::Utility::CHashMap<BSLib::uint32, CInstanceAttr*>::const_iterator itr = m_hashInstance[0].find(a_instanceTPID);
	if (itr != m_hashInstance[0].end()) {
		return itr->second;
	}
	return NULL;
}

const CStageAttr * CSceneSystemDataMgr::getStageAttr(BSLib::uint32 a_stageTPID) const
{
	BSLib::Utility::CHashMap<BSLib::uint32, CStageAttr*>::const_iterator itr = m_hashStage.find(a_stageTPID);
	if (itr != m_hashStage.end()) {
		return itr->second;
	}
	return NULL;
}

const CStageAttr *CSceneSystemDataMgr::getContinuousStageAttr(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_stageIndex)
{
	BSLib::Utility::CHashMap<BSLib::uint32, CInstanceAttr*>::const_iterator itr = m_hashInstance[EINSTANCE_TYPE_CONTINUOUS_STAGE].find(a_instanceTPID);	
	if (itr != m_hashInstance[EINSTANCE_TYPE_CONTINUOUS_STAGE].end()) {
		CInstanceAttr *instanceAttr = itr->second;
		if (instanceAttr != NULL) {
			if (a_stageIndex < instanceAttr->m_vecStage.size()) {
				return instanceAttr->m_vecStage[a_stageIndex];
			}
		}
	}
	return NULL;
}

const CStageAttr* CSceneSystemDataMgr::getStageAttr(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_stageIndex) const
{
	BSLib::Utility::CHashMap<BSLib::uint32, CInstanceAttr*>::const_iterator itr = m_hashInstance[0].find(a_instanceTPID);	
	if (itr != m_hashInstance[0].end()) {
		CInstanceAttr *instanceAttr = itr->second;
		if (instanceAttr != NULL) {
			if (a_stageIndex < instanceAttr->m_vecStage.size()) {
				return instanceAttr->m_vecStage[a_stageIndex];
			}
		}
	}
	return NULL;
}

const CInstanceStarPrizeAttr* CSceneSystemDataMgr::getInstanceStarPrizeAttr(BSLib::uint32 a_instanceTPID) const
{
	BSLib::Utility::CHashMap<BSLib::uint32, CInstanceStarPrizeAttr*>::const_iterator itr = m_hashInstanceStarPrize.find(a_instanceTPID);	
	if (itr != m_hashInstanceStarPrize.end()) {
		return itr->second;
	}
	return NULL;
}

bool CSceneSystemDataMgr::_loadCityAttr(const std::string & a_path)
{
	BSLib::Utility::CStringA fileName = a_path + "\\t_city_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);
	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载主城场景失败[%s]", fileName.c_str());
		return false;
	}
	try {
		BSLib::Utility::CTable &table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			CSceneAttr *sceneAttr = new CSceneAttr(ESCENE_TYPE_CITY);
			table[i]["f_id"] >> sceneAttr->m_sceneTPID ;
			table[i]["f_max_roles"] >> sceneAttr->m_maxPlayers;
			BSLib::Utility::CStringA strInstance;
			table[i]["f_instance"] >> strInstance;
			std::vector<BSLib::Utility::CStringA> vecIntance;
			strInstance.split(vecIntance, '|');
			for (std::vector<BSLib::Utility::CStringA>::iterator itr = vecIntance.begin(); itr != vecIntance.end(); ++itr) {
				BSLib::uint32 instanceTPID = 0;
				(*itr) >> instanceTPID;
				sceneAttr->m_instances.insert(instanceTPID);
			}
			m_hashScene.setValue(sceneAttr->m_sceneTPID, sceneAttr);
		}
	} catch (...) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载主城场景失败[%s]", fileName.c_str());
		return false;		
	}
	return true;
}

bool CSceneSystemDataMgr::_loadReviveItems(const std::string &a_path)
{
	BSLib::Utility::CStringA fileName = a_path + "\\reviveConfig.xml";

	BSLib::Utility::CTableSheet tableSheet;
	BSLib::Utility::CDirInfo::standardization(fileName);
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载场复活物品置失败[%s]", fileName.c_str());
		return false;
	}
	try {
		BSLib::Utility::CTable &table = tableSheet["revive"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			BSLib::uint32 reviveCount = 0;
			BSLib::uint32 constDiamonds = 0;

			table[i]["f_revive_count"] >> reviveCount;
			table[i]["f_cost_diamond"] >> constDiamonds;

			CReviveItem *reviveItem = new CReviveItem;
			reviveItem->setReviveTimes(reviveCount);
			reviveItem->setConstDiamond(constDiamonds);

			CSceneSystemDataMgr::singleton().addReviveItem(reviveItem);
		}
	} catch (...) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载场复活物品置失败[%s]", fileName.c_str());
		return false;		
	}
	return true;
}

bool CSceneSystemDataMgr::_loadItemDropTable(const std::string &a_path)
{
	BSLib::Utility::CStringA fileName = a_path + "\\t_drop_item_table_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载物品掉落表置失败[%s]", fileName.c_str());
		return false;
	}

	try {
		BSLib::Utility::CTable &table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			BSLib::uint32 dropID = 0;
			BSLib::uint32 itemID = 0;
			//BSLib::uint32 itemType = 0;
			BSLib::uint32 itemCount = 0;
			BSLib::uint32 probability = 0;

			const BSLib::int32 ITEMS_CONT = 5;
			table[i]["f_drop_id"] >> dropID;

			CDropTableEntry *dropEntry = new CDropTableEntry;
			dropEntry->m_ID = dropID;
			for (BSLib::int32 j = 0; j < ITEMS_CONT; ++j) {
				std::string strItemID = "f_prize_item_id_" + BSLib::Utility::CConvert::toStringA(j + 1);
				std::string strCount = "f_prize_item_count_" + BSLib::Utility::CConvert::toStringA(j + 1);
				std::string strProbability = "f_probability_" + BSLib::Utility::CConvert::toStringA(j + 1);

				table[i][strItemID] >> itemID;
				table[i][strCount] >> itemCount;
				table[i][strProbability] >> probability;

				CDropItem *dropItem = new CDropItem;
				dropItem->m_itemTPID = itemID;

				dropItem->m_itemCount = itemCount;
				dropItem->m_weight = probability;
				
				dropEntry->addDropItem(dropItem);
			}

			CSceneSystemDataMgr::singleton().addDropItemTableEntry(dropEntry);
		}
	} catch (...) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载物品掉落表置失败[%s]", fileName.c_str());
		return false;		
	}

	return true;
}

bool CSceneSystemDataMgr::_loadArenaData(const std::string &a_path)
{
	std::string fileName = a_path + "\\arena";

	if (!_loadArenaDailyRankPrize(fileName)) {
		return false;
	}

	if (!_loadArenaHistoryHighestRankPrize(fileName)) {
		return false;
	}

	if (!_loadArenaChallengePrize(fileName)) {
		return false;
	}

	//if (!_loadArenaConfig(fileName)) {
	//	return false;
	//}

	return true;
}

//bool CSceneSystemDataMgr::_loadMonsterInstanceConfig(const std::string & a_path)
//{
//	std::string fileName = a_path + "\\t_monster_instance_config.xml";
//	BSLib::Utility::CTableSheet tableSheet;
//	if (!tableSheet.loadXmlFile(fileName)) {
//		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载怪物实例数据数据失败[%s]", fileName.c_str());
//		return false;
//	}
//	try {
//		BSLib::Utility::CTable & table = tableSheet["item"];
//		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
//			CMonsterInstance *monsterInstance = new CMonsterInstance;
//			table[i]["f_id"] >> monsterInstance->m_instanceID;
//			table[i]["f_type"] >> monsterInstance->m_type;
//			table[i]["f_role"] >> monsterInstance->m_entityID;
//			m_hashMonsterInstance.setValue(monsterInstance->m_instanceID, monsterInstance);
//		}
//	} catch (...) {
//		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载怪物实例数据数据失败[%s]", fileName.c_str());
//		return false;
//	}
//
//	return true;
//}

bool CSceneSystemDataMgr::_loadStageUnit(const std::string &a_path)
{
	std::string fileName = a_path + "\\t_stage_unit_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载关卡单元数据失败[%s]", fileName.c_str());
		return false;
	}
	try {
		BSLib::Utility::CTable & table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			CStageUnitAttr *stageUnit = new CStageUnitAttr;
			table[i]["f_id"] >> stageUnit->m_id;
			table[i]["f_type"] >> stageUnit->m_type;
			const BSLib::int32 MAX_BATCH_COUNT = 5;
			for (BSLib::int32 j = 0; j < MAX_BATCH_COUNT; ++j) {
				CMonsterAttrBatch batchAttr;
				BSLib::Utility::CStringA strMonsters;
				BSLib::int32 groupIndex = j + 1;
				BSLib::Utility::CStringA strIndex = "f_group_" + BSLib::Utility::CConvert::toStringA(groupIndex);
				table[i][strIndex] >> strMonsters;
				if (strMonsters.size() > 0) {
					std::vector<BSLib::Utility::CStringA> vecMonsters;
					strMonsters.split(vecMonsters, "|");
					if (strMonsters.size() > 0) {
						for (std::vector<BSLib::Utility::CStringA>::size_type index = 0; index < vecMonsters.size(); ++index) {
							std::vector<BSLib::Utility::CStringA> vecDetail;
							const BSLib::uint32 MAX_GROUP_ATTR_COUNT = 6;
							vecMonsters[index].split(vecDetail, ",");
							if (vecDetail.size() > MAX_GROUP_ATTR_COUNT - 1) {
								CDropMonsterAttr dropMonsterAttr;
								BSLib::uint32 monsterID = BSLib::Utility::CConvert::toUint32(vecDetail[1]);
								BSLib::uint32 monsterType = BSLib::Utility::CConvert::toUint32(vecDetail[6]);
								dropMonsterAttr.m_ID = monsterID;
								dropMonsterAttr.m_dropType = (EMonsterDropType)monsterType;
								if (monsterType == 3) {
									stageUnit->m_bossID = monsterID;
								}
								batchAttr.addMonsterAttr(dropMonsterAttr);
							}
						}
					}
				}
				if (batchAttr.size() > 0) {
					stageUnit->addMonsterBatchAttr(batchAttr);
				}
			}
			BSLib::Utility::CStringA strBossBatch;
			table[i]["f_group_boss"] >> strBossBatch;
			std::vector<BSLib::Utility::CStringA> vecBoss;
			strBossBatch.split(vecBoss, "|");
			CMonsterAttrBatch batchAttr;
			for (std::vector<BSLib::Utility::CStringA>::size_type index = 0; index < vecBoss.size(); ++index) {
				std::vector<BSLib::Utility::CStringA> vecDetail;
				vecBoss[index].split(vecDetail, ",");
				if (vecDetail.size() > 0) {
					CDropMonsterAttr dropMonsterAttr;
					dropMonsterAttr.m_ID = BSLib::Utility::CConvert::toUint32(vecDetail[1]);
					dropMonsterAttr.m_dropType = (EMonsterDropType)BSLib::Utility::CConvert::toUint32(vecDetail[6]);
					if (dropMonsterAttr.m_dropType == Boss) {
						stageUnit->m_bossID = dropMonsterAttr.m_ID;
					}
					batchAttr.addMonsterAttr(dropMonsterAttr);
				}
			}
			BSLib::Utility::CStringA strRandomElite;
			table[i]["f_random_elite"] >> strRandomElite;
			std::vector<BSLib::Utility::CStringA> vecRandomElite;
			strRandomElite.split(vecRandomElite, ",");
			if (!vecRandomElite.empty()) {
				stageUnit->m_randomElite.m_ID = BSLib::Utility::CConvert::toUint32(vecRandomElite[1]);
				stageUnit->m_randomElite.m_dropType = Elite;
				stageUnit->m_randomElite.m_weight = BSLib::Utility::CConvert::toUint32(vecRandomElite[7]);
				stageUnit->m_randomElite.m_totalWeight = 100;
			}

			if (batchAttr.size() > 0) {
				stageUnit->m_vecMonsterAttrBatch.push_back(batchAttr);
			}
			if (stageUnit->size() > 0) {
				m_hashStageUnit.setValue(stageUnit->m_id, stageUnit);
			}
		}
	} catch (...) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载关卡单元数据失败[%s]", fileName.c_str());
		return false;
	}

	return true;
}

bool CSceneSystemDataMgr::_loadStageAttr(const std::string &a_path)
{
	std::string fileName = a_path + "\\t_stage_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载副本关卡数据失败[%s]", fileName.c_str());
		return false;
	}
	try {
		BSLib::Utility::CTable & table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			CStageAttr *stageAttr = new CStageAttr(ESCENE_TYPE_NONE);
			stageAttr->m_maxPlayers = 1;
			table[i]["f_name"] >> stageAttr->m_name;
			table[i]["f_id"] >> stageAttr->m_sceneTPID;
			table[i]["f_cost_vitality"] >> stageAttr->m_costVitality;
			table[i]["f_daily_enter_count"] >> stageAttr->m_dailyEnterCount;
			table[i]["f_enter_level"] >> stageAttr->m_enterLevel;
			table[i]["f_prize_exp"] >> stageAttr->m_prizeExp;
			table[i]["f_prize_gold"] >> stageAttr->m_prizeGold;
			table[i]["f_drop_item_id_star_1"] >>stageAttr->m_dropItemIDStar1;
			table[i]["f_drop_item_id_star_2"] >>stageAttr->m_dropItemIDStar2;
			table[i]["f_drop_item_id_star_3"] >>stageAttr->m_dropItemIDStar3;
			table[i]["f_revive_count"] >>stageAttr->m_reviveCount;
			table[i]["f_skill_id"] >>stageAttr->m_autoGetSkillTPID;
			table[i]["f_difficulty"] >>stageAttr->m_difficulty;
			table[i]["f_boss_id"] >> stageAttr->m_bossID;
			table[i]["f_pre_stage"] >> stageAttr->m_preStage;
			std::vector<BSLib::Utility::CStringA> vecUnits;
			BSLib::Utility::CStringA strUnits;
			table[i]["f_stage_unit"] >> strUnits;
			strUnits.split(vecUnits, "|");
			for (std::vector<BSLib::Utility::CStringA>::size_type index = 0; index < vecUnits.size(); ++index) {
				BSLib::uint32 uintID = 0;
				vecUnits[index] >> uintID;
				stageAttr->m_vecUnits.push_back(uintID);
				BSLib::Utility::CHashMap<BSLib::uint32, CStageUnitAttr*>::iterator itr = m_hashStageUnit.find(uintID);
				if (itr != m_hashStageUnit.end()){
					CStageUnitAttr *stageUnit = itr->second;
					if (stageUnit != NULL) {
						stageAttr->m_hashStageUnits.setValue(stageUnit->m_id, stageUnit);
						if (stageUnit->m_bossID > 0) {
							stageAttr->m_bossID = stageUnit->m_bossID;
						}
					}
				}
			}
			std::vector<BSLib::Utility::CStringA> vecStagePrize;
			BSLib::Utility::CStringA strStagePrize;
			table[i]["f_stage_award"] >> strStagePrize;
			strStagePrize.split(vecStagePrize, "|");
			for (std::vector<BSLib::Utility::CStringA>::size_type index = 0; index < vecStagePrize.size(); ++index) {
				BSLib::Utility::CStringA strPrize;
				std::vector<BSLib::Utility::CStringA> vecItem;
				vecStagePrize[index].split(vecItem, ",");
				BSLib::uint32 itemID = BSLib::Utility::CConvert::toUint32(vecItem[0]);
				BSLib::uint32 count = BSLib::Utility::CConvert::toUint32(vecItem[1]);
				CDropItem dropItem;				
				dropItem.m_itemTPID = itemID;
				dropItem.m_itemCount = count;
				dropItem.m_weight = 10000;
				dropItem.m_totalWeight = 10000;
				stageAttr->m_stagePrizeAttr.m_vecStagePrize.push_back(dropItem);
			}

			std::vector<BSLib::Utility::CStringA> vecRandomDrop;
			BSLib::Utility::CStringA strRandomDrop;
			table[i]["f_random_drop"] >> strRandomDrop;
			strRandomDrop.split(vecRandomDrop, "|");
			for (std::vector<BSLib::Utility::CStringA>::size_type index = 0; index < vecRandomDrop.size(); ++index) {
				std::vector<BSLib::Utility::CStringA> vecItem;
				vecRandomDrop[index].split(vecItem, ",");
				if (vecItem.size() >= 2) {
					BSLib::uint32 itemID = BSLib::Utility::CConvert::toUint32(vecItem[0]);
					BSLib::uint32 weight = BSLib::Utility::CConvert::toUint32(vecItem[1]);
					CDropItem dropItem;				
					dropItem.m_itemTPID = itemID;
					dropItem.m_itemCount = 1;
					dropItem.m_weight = weight;
					dropItem.m_totalWeight = 10000;
					stageAttr->m_stagePrizeAttr.m_vecRandomDrops.push_back(dropItem);
				} else {
					BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载副本关卡数据失败[%s], 奖励物品填写错误, stage_id[%d]", fileName.c_str(), stageAttr->m_sceneTPID);
					return false;
				}

			}

			std::vector<BSLib::Utility::CStringA> vecCertainlyDrop;
			BSLib::Utility::CStringA strCertainlyDrop;
			table[i]["f_normal_drop"] >> strCertainlyDrop;
			strCertainlyDrop.split(vecCertainlyDrop, "|");
			for (std::vector<BSLib::Utility::CStringA>::size_type index = 0; index < vecCertainlyDrop.size(); ++index) {
				std::vector<BSLib::Utility::CStringA> vecItem;
				vecCertainlyDrop[index].split(vecItem, ",");
				BSLib::uint32 itemID = BSLib::Utility::CConvert::toUint32(vecItem[0]);
				BSLib::uint32 weight = BSLib::Utility::CConvert::toUint32(vecItem[1]);
				CDropItem dropItem;				
				dropItem.m_itemTPID = itemID;
				dropItem.m_itemCount = 1;
				dropItem.m_weight = weight;
				dropItem.m_totalWeight = 10000;
				stageAttr->m_stagePrizeAttr.m_vecCertainlyDrops.push_back(dropItem);
			}

			std::vector<BSLib::Utility::CStringA> vecBossDrop;
			BSLib::Utility::CStringA strBossDrop;
			table[i]["f_boss_drop"] >> strBossDrop;
			strBossDrop.split(vecBossDrop, "|");
			for (std::vector<BSLib::Utility::CStringA>::size_type index = 0; index < vecBossDrop.size(); ++index) {
				std::vector<BSLib::Utility::CStringA> vecItem;
				vecBossDrop[index].split(vecItem, ",");
				BSLib::uint32 itemID = BSLib::Utility::CConvert::toUint32(vecItem[0]);
				BSLib::uint32 weight = BSLib::Utility::CConvert::toUint32(vecItem[1]);
				CDropItem dropItem;				
				dropItem.m_itemTPID = itemID;
				dropItem.m_itemCount = 1;
				dropItem.m_weight = weight;
				dropItem.m_totalWeight = 10000;
				stageAttr->m_stagePrizeAttr.m_vecBossDrops.push_back(dropItem);
			}

			std::vector<BSLib::Utility::CStringA> vecRandomEliteDrop;
			BSLib::Utility::CStringA strEliteDrop;
			table[i]["f_random_elite_drop"] >> strEliteDrop;
			strEliteDrop.split(vecRandomEliteDrop, "|");
			for (std::vector<BSLib::Utility::CStringA>::size_type index = 0; index < vecRandomEliteDrop.size(); ++index) {
				std::vector<BSLib::Utility::CStringA> vecItem;
				vecRandomEliteDrop[index].split(vecItem, ",");
				BSLib::uint32 itemID = BSLib::Utility::CConvert::toUint32(vecItem[0]);
				BSLib::uint32 weight = BSLib::Utility::CConvert::toUint32(vecItem[1]);
				CDropItem dropItem;				
				dropItem.m_itemTPID = itemID;
				dropItem.m_itemCount = 1;
				dropItem.m_weight = weight;
				dropItem.m_totalWeight = 10000;
				stageAttr->m_stagePrizeAttr.m_vecEliteDrops.push_back(dropItem);
			}

			_addStageData(stageAttr);
		}
	}
	catch (...) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载副本关卡数据失败[%s]", fileName.c_str());
		return false;
	}

	return true;	
}

bool CSceneSystemDataMgr::_loadInstanceData(const std::string &a_path)
{
	std::string fileName = a_path + "\\t_instance_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载副本数据失败[%s]", fileName.c_str());
		return false;
	}
	try {
		BSLib::Utility::CTable & table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			CInstanceAttr *instanceAttr = new CInstanceAttr;
			table[i]["f_id"] >> instanceAttr->m_TPID;
			BSLib::uint32 temp = 0;
			table[i]["f_type"] >> temp;
			instanceAttr->m_instanceType = (EInstanceType)temp;
			if (instanceAttr->m_instanceType <= EINSTANCE_TYPE_NONE || instanceAttr->m_instanceType >= EINSTANCE_TYPE_MAX) {
				BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载副本数据失败[%s],副本[%d]类型错误！", fileName.c_str(), instanceAttr->m_TPID);
				return false;
			}
			table[i]["f_unlock_instance"] >> instanceAttr->m_unlockInstanceTPID;
			table[i]["f_city"] >> instanceAttr->m_city;
			BSLib::Utility::CStringA strStage;
			table[i]["f_stage"] >> strStage;
			std::vector<BSLib::Utility::CStringA> vecStage;
			strStage.split(vecStage, '|');
			BSLib::int8 stageIndex = 0;
			for (std::vector<BSLib::Utility::CStringA>::size_type index = 0; index < vecStage.size(); ++index) {
				BSLib::uint32 stageID = 0;
				vecStage[index] >> stageID;
				BSLib::Utility::CHashMap<BSLib::uint32, CStageAttr*>::iterator itr = m_hashStage.find(stageID);
				if (itr != m_hashStage.end()) {
					CStageAttr *stageAttr = itr->second;
					if (stageAttr != NULL) {
						if (stageAttr->m_instanceType != EINSTANCE_TYPE_NONE) {
							BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载副本数据失败[%s],副本[%d]的关卡[%d]赋值给多个副本！", fileName.c_str(), instanceAttr->m_TPID, stageID);
							return false;
						}
						//TODO 加个限制，没有才加入
						stageAttr->m_instanceTPID = instanceAttr->m_TPID;
						if (instanceAttr->m_instanceType == EINSTANCE_TYPE_STORY || instanceAttr->m_instanceType == EINSTANCE_TYPE_ADVANCE ) {
							stageAttr->m_sceneType = ESCENE_TYPE_STAGE;
						} else if (instanceAttr->m_instanceType == EINSTANCE_TYPE_CONTINUOUS_STAGE) {
							stageAttr->m_sceneType = ESCENE_TYPE_CONTINUOUS_STAGE;
						} else if (instanceAttr->m_instanceType == EINSTANCE_TYPE_RANDOM_STAGE) {
							stageAttr->m_sceneType = ESCENE_TYPE_RANDOM_STAGE;
						} else if (instanceAttr->m_instanceType == EINSTANCE_TYPE_RANDOM_GOLD_STAGE) {
							stageAttr->m_sceneType = ESCENE_TYPE_RANDOM_GOLD_STAGE;
						} else if (instanceAttr->m_instanceType == EINSTANCE_TYPE_RANDOM_EXP_STAGE) {
							stageAttr->m_sceneType = ESCENE_TYPE_RANDOM_EXP_STAGE;
						}
						stageAttr->m_instanceType = instanceAttr->m_instanceType;
						stageAttr->m_stageIndex = stageIndex++;
						instanceAttr->m_vecStage.push_back(stageAttr);
					}
				} else {
					BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载副本数据失败[%s],副本[%d]的关卡[%d]不存在！", fileName.c_str(), instanceAttr->m_TPID, stageID);
					return false;
				}
			}
			m_hashInstance[0].setValue(instanceAttr->m_TPID, instanceAttr);
			m_hashInstance[instanceAttr->getType()].setValue(instanceAttr->m_TPID, instanceAttr);
		}
	}
	catch (...) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载副本数据失败[%s]", fileName.c_str());
		return false;
	}

	return true;	
}

bool CSceneSystemDataMgr::_loadInstanceStarPrizeData(const std::string & a_path)
{
	BSLib::Utility::CStringA fileName = a_path + "\\t_instance_star_prize_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载副本星级奖励失败[%s]", fileName.c_str());
		return false;
	}
	try {
		const BSLib::int32 ITEMS_CONT = 5;
		BSLib::Utility::CTable &table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			BSLib::uint32 instanceTPID = 0;
			BSLib::uint16 star = 0;
			table[i]["f_instance_id"] >> instanceTPID;
			table[i]["f_star"] >> star;
			std::vector<ItemSystem::GM::CPrizeItem> vecPrizeItem;
			for (BSLib::int32 j = 0; j < ITEMS_CONT; ++j) {
				std::string strItemID = "f_prize_item_id_" + BSLib::Utility::CConvert::toStringA(j + 1);
				std::string strCount = "f_prize_item_count_" + BSLib::Utility::CConvert::toStringA(j + 1);
				ItemSystem::GM::CPrizeItem prizeItem;
				table[i][strItemID] >> prizeItem.m_itemTPID;
				table[i][strCount] >> prizeItem.m_itemCount;
				vecPrizeItem.push_back(prizeItem);
			}
			_addInstanceStarPrize(instanceTPID, star, vecPrizeItem);
		}
	} catch (...) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载副本星级奖励失败[%s]", fileName.c_str());
		return false;		
	}
	return true;
}

bool CSceneSystemDataMgr::_loadArenaDailyRankPrize(const std::string &a_path)
{
	BSLib::Utility::CStringA fileName = a_path + "\\t_arena_daily_rank_prize_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载竞技场每日排名奖励失败[%s]", fileName.c_str());
		return false;
	}

	try {
		BSLib::Utility::CTable &table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			BSLib::uint32 rank = 0;
			BSLib::uint64 gold = 0;
			BSLib::uint32 diamond = 0;
			BSLib::uint32 pvpCoin = 0;

			table[i]["f_end_rank"] >> rank;
			table[i]["f_gold"] >> gold;
			table[i]["f_diamond"] >> diamond;
			table[i]["f_pvp_coin"] >> pvpCoin;

			CArenaPrize *prize = new CArenaPrize;
			prize->m_gold = gold;
			prize->m_diamond = diamond;
			prize->m_pvpCoin = pvpCoin;

			addDailyRankPrize(rank, prize);
		}
	} catch (...) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载竞技场每日排名奖励失败[%s]", fileName.c_str());
		return false;		
	}

	return true;
}

bool CSceneSystemDataMgr::_loadArenaHistoryHighestRankPrize(const std::string &a_path)
{
	BSLib::Utility::CStringA fileName = a_path + "\\t_arena_history_highest_rank_prize_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载竞技场最高排名奖励奖励失败[%s]", fileName.c_str());
		return false;
	}

	try {
		BSLib::Utility::CTable &table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			BSLib::uint32 rank = 0;
			BSLib::uint64 gold = 0;
			BSLib::uint32 diamond = 0;
			BSLib::uint32 pvpCoin = 0;

			table[i]["f_end_rank"] >> rank;
			table[i]["f_gold"] >> gold;
			table[i]["f_diamond"] >> diamond;
			table[i]["f_pvp_coin"] >> pvpCoin;

			CArenaPrize *prize = new CArenaPrize;
			prize->m_gold = gold;
			prize->m_diamond = diamond;
			prize->m_pvpCoin = pvpCoin;

			addHistoryHighestRankPrize(rank, prize);
		}
	} catch (...) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载竞技场最高排名奖励奖励失败[%s]", fileName.c_str());
		return false;		
	}

	return true;
}

bool CSceneSystemDataMgr::_loadArenaChallengePrize(const std::string &a_path)
{
	BSLib::Utility::CStringA fileName = a_path + "\\t_arena_challenge_prize_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载竞技场排名挑战奖励失败[%s]", fileName.c_str());
		return false;
	}

	try {
		BSLib::Utility::CTable &table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			BSLib::uint32 type = 0;
			BSLib::uint64 gold = 0;
			BSLib::uint32 diamond = 0;
			BSLib::uint32 pvpCoin = 0;

			table[i]["f_type"] >> type;
			table[i]["f_gold"] >> gold;
			table[i]["f_diamond"] >> diamond;
			table[i]["f_pvp_coin"] >> pvpCoin;

			if (type == 0) {
				m_arenaChallengeFailPrize = new CArenaPrize;
				m_arenaChallengeFailPrize->m_gold = gold;
				m_arenaChallengeFailPrize->m_diamond = diamond;
				m_arenaChallengeFailPrize->m_pvpCoin = pvpCoin;
			} else if (type == 1) {
				m_arenaChallengeSucPrize = new CArenaPrize;
				m_arenaChallengeSucPrize->m_gold = gold;
				m_arenaChallengeSucPrize->m_diamond = diamond;
				m_arenaChallengeSucPrize->m_pvpCoin = pvpCoin;
			}
		}
	} catch (...) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载竞技场排名挑战奖励失败[%s]", fileName.c_str());
		return false;		
	}

	return true;
}

//bool CSceneSystemDataMgr::_loadArenaConfig(const std::string &a_path)
//{
//	BSLib::Utility::CStringA fileName = a_path + "\\t_arena_general_config.xml";
//
//	BSLib::Utility::CTableSheet tableSheet;
//	if (!tableSheet.loadXmlFile(fileName)) {
//		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载竞技场配置失败[%s]", fileName.c_str());
//		return false;
//	}
//
//	try {
//		BSLib::Utility::CTable &table = tableSheet["config"];
//		table[0]["f_max_role_hp_extend_times"] >> m_maxRoleHPExtendTimes;				
//	} catch (...) {
//		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载竞技场配置失败[%s]", fileName.c_str());
//		return false;		
//	}
//
//	return true;
//}

bool CSceneSystemDataMgr::_loadStageTemplate(const std::string &a_path)
{
	BSLib::Utility::CStringA fileName = a_path + "\\t_stage_templet_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载随机关卡配置失败[%s]", fileName.c_str());
		return false;
	}

	try {
		BSLib::Utility::CTable &table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			CStageTemplate *stageTemplate = new CStageTemplate();
			table[i]["f_difficulty"] >> stageTemplate->m_difficulty;
			table[i]["f_stage_unit_count"] >> stageTemplate->m_stageUnitCount;
			table[i]["f_group_count"] >> stageTemplate->m_unitBatchCount;

			BSLib::Utility::CStringA strMonsterCount;
			table[i]["f_group_enemy_count"] >> strMonsterCount;
			std::vector<BSLib::Utility::CStringA> vecMonsterCount;
			strMonsterCount.split(vecMonsterCount, ",");
			if (vecMonsterCount.size() > 1) {
				stageTemplate->m_minStageUnitBatchCount = BSLib::Utility::CConvert::toUint32(vecMonsterCount[0]);
				stageTemplate->m_maxStageUnitBatchCount = BSLib::Utility::CConvert::toUint32(vecMonsterCount[1]);
			} else {
				BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载随机关卡配置失败[%s],难度[%d]每批次敌人填写格式有误", fileName.c_str(), stageTemplate->m_difficulty);
			}
			
			_addTemplateStage(stageTemplate);
		}			
	} catch (...) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载随机关卡配置失败[%s]", fileName.c_str());
		return false;		
	}

	return true;
}

void CSceneSystemDataMgr::_addStageData(CStageAttr * stageAttr)
{
	if (stageAttr != NULL) {
		if (m_hashStage.find(stageAttr->m_sceneTPID) == m_hashStage.end()) {
			m_hashStage.setValue(stageAttr->m_sceneTPID, stageAttr);
		}
	}
}

void CSceneSystemDataMgr::_addInstanceStarPrize(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_star, std::vector<ItemSystem::GM::CPrizeItem> &a_vecPrizeItem)
{
	BSLib::Utility::CHashMap<BSLib::uint32, CInstanceStarPrizeAttr*>::iterator itr = m_hashInstanceStarPrize.find(a_instanceTPID);	
	if (itr != m_hashInstanceStarPrize.end()) {
		CInstanceStarPrizeAttr *instancePrize = itr->second;
		if (instancePrize != NULL) {
			BSLib::Utility::CHashMap< BSLib::uint16, std::vector<ItemSystem::GM::CPrizeItem> >::iterator jtr = instancePrize->m_hashStarPrize.find(a_star);
			if (jtr == instancePrize->m_hashStarPrize.end()) {
				instancePrize->m_hashStarPrize.setValue(a_star, a_vecPrizeItem);
			} else {
				BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "重复添加副本星级奖励 副本[%d] 星级[%d]", a_instanceTPID, a_star);
			}
		} else {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "_addInstanceStarPrize失败" );
		}
	} else {
		CInstanceStarPrizeAttr *instancePrize = new CInstanceStarPrizeAttr;
		instancePrize->m_instanceTPID = a_instanceTPID;
		instancePrize->m_hashStarPrize.setValue(a_star, a_vecPrizeItem);
		m_hashInstanceStarPrize.setValue(a_instanceTPID, instancePrize);
	}
}

const CSceneAttr* CSceneSystemDataMgr::getArenaSceneAttr() const
{
	return m_arenaAttr;
}


const CStageTemplate * CSceneSystemDataMgr::getStageTemplate(BSLib::uint32 a_difficulty) const
{
	BSLib::Utility::CHashMap<BSLib::uint32, CStageTemplate*>::const_iterator itr = m_hashTemplateStage.find(a_difficulty);
	if (itr != m_hashTemplateStage.end()) {
		return itr->second;
	}

	return NULL;
}

void CSceneSystemDataMgr::_addTemplateStage(CStageTemplate * a_stageTemplate)
{
	if (a_stageTemplate != NULL) {
		if (m_hashTemplateStage.find(a_stageTemplate->m_difficulty) == m_hashTemplateStage.end()) {
			m_hashTemplateStage.setValue(a_stageTemplate->m_difficulty, a_stageTemplate);
		}
	}
}




}//GM

}//SceneSystem

}//GSLib





