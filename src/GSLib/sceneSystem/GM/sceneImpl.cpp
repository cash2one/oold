#include <GSLib/sceneSystem/GM/sceneImpl.h>
#include <GSLib/sceneSystem/GM/roleSceneModule.h>
#include <GSLib/sceneSystem/GM/sceneSystemDataMgr.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <BSLib/utility/random.h>
#include <GSLib/taskSystem/GM/roleTaskModule.h>
#include <GSLib/sceneSystem/msgSceneSystemGC.h>
#include <BSLib/utility/dateTime.h>
#include <GSLib/itemSystem/GM/itemGMMgr.h>
#include <GSLib/prizeSystem/GM/rolePrizeModule.h>
#include <GSLib/equipSystem/GM/roleEquipModule.h>
#include <GSLib/rankSystem/GM/roleRankModule.h>

namespace GSLib
{

namespace SceneSystem
{	

namespace GM
{

/////////////////////////////////////////////////////////////////////////////////////////////
CSceneCity::CSceneCity(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr)
:CScene(a_sceneType, a_sceneAttr)
{

}

CSceneCity::~CSceneCity()
{

}

EEnterSceneResult CSceneCity::canEnterScene(CRoleSceneModule * a_sceneRole)
{
	if (a_sceneRole == NULL || a_sceneRole->getRoleGM() == NULL) {
		return EENTER_SCENE_RESULT_SYSTEM_ERROR;
	}
	if (m_setSceneRole.find(a_sceneRole->getRoleGM()->getRoleKey()) != m_setSceneRole.end()) {
		return EENTER_SCENE_RESULT_ALREADY_IN_SCENE;
	}
	if (a_sceneRole->getRoleGM()->getLevel() < m_sceneAttr->getEnterLevel() ) {
		return EENTER_SCENE_RESULT_NOT_ENOUGH_ROLE_LEVEL;
	}
	return EENTER_SCENE_RESULT_SUCCESS;
}

void CSceneCity::_enterScene(CRoleSceneModule * a_sceneRole)
{
}

void CSceneCity::_exitScene(CRoleSceneModule * a_sceneRole)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////
CSceneStage::CSceneStage(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr)
:CScene(a_sceneType, a_sceneAttr)
{

}

CSceneStage::~CSceneStage()
{

}

EEnterSceneResult CSceneStage::canEnterScene(CRoleSceneModule * a_sceneRole)
{
	if (a_sceneRole == NULL) {
		return EENTER_STAGE_RESULT_FAIL;
	}
	const CStageAttr *stageAttr = static_cast<const CStageAttr*>(m_sceneAttr);
	if (stageAttr == NULL) {
		return EENTER_STAGE_RESULT_FAIL;
	}
	if (stageAttr->getSceneType() != ESCENE_TYPE_STAGE) {
		return EENTER_STAGE_RESULT_ERROR_INSTANCE;
	}
	if (a_sceneRole->m_curScene != NULL) {
		if (a_sceneRole->m_curScene->getSceneType() != ESCENE_TYPE_CITY) {
			return EENTER_SCENE_RESULT_ALREADY_IN_OTHER_INSTANCE;
		}
	}
	if (a_sceneRole->getRoleGM() == NULL) {
		return EENTER_STAGE_RESULT_FAIL;
	}
	if (a_sceneRole->getRoleGM()->getLevel() < m_sceneAttr->getEnterLevel() ) {
		return EENTER_STAGE_RESULT_NOT_ENOUGH_ROLE_LEVEL;
	}
	if (a_sceneRole->getRoleGM()->getVitality() < stageAttr->m_costVitality) {
		return EENTER_STAGE_RESULT_NOT_ENOUGH_VATALITY;
	}
	const CInstanceAttr * instanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(stageAttr->getInstanceTPID());
	if (instanceAttr == NULL) {
		return EENTER_STAGE_RESULT_NOT_SUCH_INSTANCE ;
	}
	if (stageAttr->getStageIndex() >= (BSLib::uint32)instanceAttr->stageSize() || instanceAttr->m_vecStage[stageAttr->getStageIndex()] == NULL) {
		return EENTER_STAGE_RESULT_NO_SUCH_STAGE_INDEX ;
	}

	if (stageAttr->getMaxDailyEnterTimes() != 0) {
		const CFinishStage *finishStage = a_sceneRole->m_roleInstanceData.getStage(stageAttr->getSceneTPID());
		if (finishStage != NULL && finishStage->getDailyEnteredTimes() >= stageAttr->getMaxDailyEnterTimes()) {
			return EENTER_STAGE_RESULT_REACH_DAILY_ENTER_TIMES_LIMIT;
		}
	}

	CRoleInstanceData & roleInstanceData = a_sceneRole->getRoleInstanceData();
	if (instanceAttr->getInstanceType() == EINSTANCE_TYPE_STORY) {
		if (stageAttr->getInstanceTPID() * C_MAX_STAGES_PER_INSTANCE + stageAttr->getStageIndex()  > 
			roleInstanceData.getProgressInstanceTPID() * C_MAX_STAGES_PER_INSTANCE + roleInstanceData.getProgressStageIndex()) {
				return EENTER_STAGE_RESULT_STAGE_NOT_OPEN;
		}
	} else if (instanceAttr->getInstanceType() == EINSTANCE_TYPE_ADVANCE) {
		const CFinishStage * unlockStage = a_sceneRole->m_roleInstanceData.getStage(stageAttr->m_preStage);
		if (unlockStage == NULL || !unlockStage->isValid()) {
			return EENTER_STAGE_RESULT_STAGE_NOT_OPEN;
		}
		if (unlockStage->m_star < C_STAGE_LEVEL_REQUIRE_STAR) {
			return EENTER_STAGE_RESULT_NOT_ENOUGH_STAR;	
		}
	} 
	return EENTER_SCENE_RESULT_SUCCESS;
}

void CSceneStage::reportStageResult(CRoleSceneModule & a_sceneRole, const CStageReportResult & a_reportResult)
{
	ESendStageResultReportResult result = a_sceneRole._canReportStageResult();
	if (result != ESEND_STAGE_RESULT_REPORT_RESULT_SUCCESS) {
		CMsgSceneSystemGM2GCAckStageResultReport msgAck;
		msgAck.m_result = result;
		a_sceneRole.sendMsgToClient(msgAck);
		//exitScene();
		return;
	}
	if (!a_reportResult.m_isWin) {
		CMsgSceneSystemGM2GCAckStageResultReport msgAck;
		msgAck.m_result = ESEND_STAGE_RESULT_REPORT_RESULT_SUCCESS;
		a_sceneRole.sendMsgToClient(msgAck);
		a_sceneRole.exitScene();
		return;
	}
	BSLib::uint32 curInstanceTPID = a_sceneRole.m_roleInstanceData.getCurInstanceTPID();
	BSLib::uint16 curStageIndex = a_sceneRole.m_roleInstanceData.getCurStageIndex();
	const CInstanceAttr *instanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(curInstanceTPID);
	CStageAttr *stageAttr = instanceAttr->m_vecStage[curStageIndex];
	CFinishStage finishStage;
	a_sceneRole.m_roleInstanceData.reportStageResult(curInstanceTPID, curStageIndex, a_reportResult.m_star, finishStage);
	a_sceneRole._updateRoleFinishStageDataTable(finishStage);

	CRoleStage curRoleStage = a_sceneRole.m_roleInstanceData.getCurStage();
	a_sceneRole._nextStoryStage(curRoleStage);
	BSLib::uint32 progressInstanceTPID = a_sceneRole.m_roleInstanceData.getProgressInstanceTPID();
	BSLib::uint16 progressStageIndex = a_sceneRole.m_roleInstanceData.getProgressStageIndex();
	if (instanceAttr->getType() == EINSTANCE_TYPE_STORY) {
		if (curRoleStage.m_instanceTPID * C_MAX_STAGES_PER_INSTANCE + curRoleStage.m_stageIndex > 
			progressInstanceTPID * C_MAX_STAGES_PER_INSTANCE + progressStageIndex) {
				a_sceneRole.m_roleInstanceData.setStoryInstanceProgress(curRoleStage.m_instanceTPID, curRoleStage.m_stageIndex);
				a_sceneRole._updateStoryInstanceProgressTable(a_sceneRole.m_roleInstanceData.getProgressData());
		}
	}
	a_sceneRole._updateInstanceAchieve(curInstanceTPID, stageAttr->getStageIndex());
	BSLib::int32 costVitality = (BSLib::int32)stageAttr->m_costVitality;
	a_sceneRole.getRoleGM()->modifyRoleResource(PlayerSystem::GM::ATTR_VITALITY, -costVitality, "");
	//exitScene();

	if (a_sceneRole.m_curScene != NULL) {
		a_sceneRole.m_curScene->getStageMonsterPrize().setValid(true);
		a_sceneRole.m_curScene->updateRandomMonsterPrize(a_reportResult.m_clearedRandomMonster);
	}
	if (stageAttr->getInstanceType() == EINSTANCE_TYPE_ADVANCE) {
		RankSystem::GM::CRoleRankModule *rankRole = (RankSystem::GM::CRoleRankModule *)a_sceneRole.getRoleGM()->getPlayerModuleGM(EMODULECTYPE_RANK);
		if (rankRole != NULL) {
			rankRole->update(stageAttr->getSceneTPID(), a_reportResult.m_useTime);
		}
	}

	CMsgSceneSystemGM2GCAckStageResultReport msgAck;
	msgAck.m_result = ESEND_STAGE_RESULT_REPORT_RESULT_SUCCESS;
	a_sceneRole.sendMsgToClient(msgAck);
}

void CSceneStage::clearStage(CRoleSceneModule& a_sceneRole, bool isBreakDownItem)
{
	const CStageAttr * stageAttr = static_cast<const CStageAttr *>(m_sceneAttr);
	CMsgSceneSystemGM2GCAckClearStage msgAck;
	msgAck.m_result = ECLEAR_STAGE_RESULT_SUCCESS;

	if (stageAttr != NULL) {
		BSLib::uint32 count = 0;
		const CStagePrizeAttr* stagePrizeAttr = NULL; 
		for (BSLib::Utility::CHashMap<BSLib::uint32, CStageUnitAttr*>::const_iterator stage = stageAttr->m_hashStageUnits.begin(); stage != stageAttr->m_hashStageUnits.end(); ++stage) {
			CStageUnitAttr *unitAttr = stage->second;
			if (unitAttr != NULL) {
				_genMonster(m_stageMonster, *unitAttr, stageAttr->m_stagePrizeAttr, count);
			}
		}
		genStagePrize();
		PlayerSystem::GM::CRoleBagModuleGM *bagModule = a_sceneRole.getRoleGM()->getRoleBag();
		if (bagModule == NULL) {
			return;
		}
		CFinishStage *finishStage = a_sceneRole.m_roleInstanceData.getStage(stageAttr->m_instanceTPID, stageAttr->m_stageIndex);
		if (finishStage == NULL) {
			return;
		}
		++finishStage->m_dailyEnteredTimes;
		a_sceneRole._updateRoleFinishStageDataTable(*finishStage);
		a_sceneRole.getRoleGM()->modifyRoleResource(PlayerSystem::GM::ATTR_VITALITY, (BSLib::int32)stageAttr->getCostVitality() * (-1), "ClearStage");

		std::vector<ItemSystem::GM::CPrizeItem> vecItem;
		std::vector<ItemSystem::GM::CPrizeItem> vecBreakItem;
		PrizeSystem::GM::CRolePrizeModule *prizeModue = (PrizeSystem::GM::CRolePrizeModule *)a_sceneRole.getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PRIZE);
		if (prizeModue != NULL || a_sceneRole.getRoleGM()->getEquipModule() != NULL) {
			for (std::vector<CMonster>::const_iterator monster = m_stagePrize.m_vecDropMonster.begin(); monster != m_stagePrize.m_vecDropMonster.end(); ++monster) {
				if (!monster->m_vecDropItem.empty()) {
					for (std::vector<ItemSystem::GM::CPrizeItem>::const_iterator item = monster->m_vecDropItem.begin(); item != monster->m_vecDropItem.end(); ++item) {
						ItemSystem::GM::CPrizeItem prizeItem;
						prizeItem.m_itemTPID = item->m_itemTPID;
						prizeItem.m_itemCount = 1;
						ItemSystem::GM::CItemDataGM *itemAttr = ItemSystem::GM::CItemGMMgr::singleton().getItem(item->m_itemTPID);
						if (itemAttr != NULL) {
							if (isBreakDownItem && itemAttr->getQualityID() < QUALITY_BLUE) {
								//sellEquip是分解装备的接口不是卖装备:(
								a_sceneRole.getRoleGM()->getEquipModule()->sellEquip(prizeItem.m_itemTPID);	
								vecBreakItem.push_back(prizeItem);
								if (monster->m_type == Elite) {
									msgAck.m_stagePrize.m_elitePrizeItem.push_back(prizeItem);
								}
							} else {
								vecItem.push_back(prizeItem);
								if (monster->m_type == Elite) {
									msgAck.m_stagePrize.m_elitePrizeItem.push_back(prizeItem);
								} 
							}
						}
					}
				}
			}
			if (!vecItem.empty()) {
				prizeModue->prizeRequest(vecItem, toMailString("系统信息"), toMailString("副本掉落道具(背包满)"), toMailString("恭喜您!扫荡副本，获得了丰厚的奖励，奖励如下："), "InstancePrize");//todo
				a_sceneRole.announceItem(m_sceneAttr->getName() ,vecItem);
			}
		}
		const CStageAttr * stageAttr = static_cast<const CStageAttr *>(m_sceneAttr);
		if (stageAttr != NULL) {
			for (std::vector<CDropItem>::const_iterator itr =  stageAttr->m_stagePrizeAttr.m_vecStagePrize.begin(); itr != stageAttr->m_stagePrizeAttr.m_vecStagePrize.end(); ++itr) {
				ItemSystem::GM::CPrizeItem item;
				item.m_itemTPID = itr->m_itemTPID;
				item.m_itemCount = itr->m_itemCount;
				bagModule->addItem(item, true);	
				ItemSystem::GM::EItemType type = ItemSystem::GM::CItemGMMgr::singleton().getType(item.m_itemTPID);
				if (type == ItemSystem::GM::EITEM_TP_VIR_GOLD) {
					msgAck.m_stagePrize.m_gold = item.m_itemCount;			
				} else if (type == ItemSystem::GM::EITEM_TP_VIR_EXP) {
					msgAck.m_stagePrize.m_exp = item.m_itemCount;
				}
			}
		}
		msgAck.m_stagePrize.m_vecPrizeItem.insert(msgAck.m_stagePrize.m_vecPrizeItem.end(), vecItem.begin(), vecItem.end());
		msgAck.m_stagePrize.m_vecPrizeItem.insert(msgAck.m_stagePrize.m_vecPrizeItem.end(), vecBreakItem.begin(), vecBreakItem.end());
	}
	a_sceneRole.sendMsgToClient(msgAck);
}

void CSceneStage::_enterScene(CRoleSceneModule * a_sceneRole)
{
	const CStageAttr *stageAttr = static_cast<const CStageAttr*>(m_sceneAttr);
	if (stageAttr != NULL) {
		a_sceneRole->m_roleInstanceData.setCurStage(stageAttr->getInstanceTPID(), stageAttr->getStageIndex());
		genMonster(a_sceneRole);
		genStagePrize();
	}
}

void CSceneStage::_exitScene(CRoleSceneModule * a_sceneRole)
{
	if (a_sceneRole != NULL) {
		a_sceneRole->m_roleInstanceData.exitScene();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
CSceneArena::CSceneArena(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr)
:CScene(a_sceneType, a_sceneAttr)
{

}

CSceneArena::~CSceneArena()
{

}

EEnterSceneResult CSceneArena::canEnterScene(CRoleSceneModule * a_sceneRole)
{
	if (a_sceneRole == NULL) {
		return EENTER_ARENA_RESULT_FAIL;
	}
	if (a_sceneRole->m_curScene != NULL) {
		if (a_sceneRole->m_curScene->getSceneType() != ESCENE_TYPE_CITY) {
			return EENTER_ARENA_RESULT_ALREADY_IN_OTHER_INSTANCE;
		}
	}
	if (a_sceneRole->getRoleGM()->getLevel() < m_sceneAttr->getEnterLevel() ) {
		return EENTER_ARENA_RESULT_NOT_ENOUGH_ROLE_LEVEL;
	}
	if (!a_sceneRole->m_arenaData.hasDailyChallengeCount()) {
		return EENTER_ARENA_RESULT_CHALLENGEE_NO_DAILY_CHALLENGE_COUNT;
	}
	if (a_sceneRole->m_arenaData.m_challengeInfo.m_type == ECHALLENGE_TYPE_RANKING_ROLE) {
		if (a_sceneRole->m_arenaData.m_vecChallengees.empty() 
			|| a_sceneRole->m_arenaData.m_challengeInfo.m_param > (BSLib::int32)(a_sceneRole->m_arenaData.m_vecChallengees.size() - 1)) {
				return EENTER_ARENA_RESULT_CHALLENGEE_NOT_EXIST;
		}
	} else if (a_sceneRole->m_arenaData.m_challengeInfo.m_type == ECHALLENGE_TYPE_REVENGE) {
		const SceneSystem::CArenaChallengeRecord * record = a_sceneRole->m_arenaData.getChallengeRecord(a_sceneRole->m_arenaData.m_challengeInfo.m_param);
		if (record == NULL) {
			return EENTER_ARENA_RESULT_NOT_SUCH_RECORD;
		}
		//策划说任何时候无限次复仇
		//if (record->m_isRevenged) {
		//	return EENTER_ARENA_RESULT_HAS_REVENGED;
		//}
		if (record->m_isActive) {
			return EENTER_ARENA_RESULT_IS_ACTIVE_RECORD;
		}
	}
	if (a_sceneRole->m_arenaData.getLastChallengeTime() + C_CHALLENGE_COOL_DWON_INTERVAL > 
		BSLib::Utility::CDateTime::getCurrentTime().getSeconds()) {
		if (!a_sceneRole->m_arenaData.m_challengeInfo.m_useDiamond) {
			return EENTER_ARENA_RESULT_IN_COLD_DOWN;
		} else {
			if (a_sceneRole->getRoleGM()->getTotalDiamond() < a_sceneRole->m_arenaData.getArenaCoolDownCost()) {
				return EENTER_ARENA_RESULT_NOT_ENOUGH_DIAMOND;
			}
		}
	}

	return EENTER_SCENE_RESULT_SUCCESS;
}

void CSceneArena::_enterScene(CRoleSceneModule * a_sceneRole)
{
}

void CSceneArena::_exitScene(CRoleSceneModule * a_sceneRole)
{
	a_sceneRole->m_arenaData.exitScene();
}

/////////////////////////////////////////////////////////////////////////////////////////////
CSceneContinuousStage::CSceneContinuousStage(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr)
:CScene(a_sceneType, a_sceneAttr)
{

}

CSceneContinuousStage::~CSceneContinuousStage()
{

}

GSLib::SceneSystem::GM::EEnterSceneResult CSceneContinuousStage::canEnterScene(CRoleSceneModule * a_sceneRole)
{
	if (a_sceneRole == NULL) {
		return EENTER_CON_STAGE_RESULT_FAIL;
	}
	const CStageAttr *stageAttr = static_cast<const CStageAttr*>(m_sceneAttr);
	if (stageAttr == NULL) {
		return EENTER_CON_STAGE_RESULT_FAIL;
	}
	if (a_sceneRole->m_curScene != NULL) {
		if (a_sceneRole->m_curScene->getSceneType() != ESCENE_TYPE_CITY) {
			return EENTER_SCENE_RESULT_ALREADY_IN_OTHER_INSTANCE;
		}
	}
	if (a_sceneRole->getRoleGM() == NULL) {
		return EENTER_CON_STAGE_RESULT_NOT_ENOUGH_ROLE_LEVEL;
	}
	if (a_sceneRole->getRoleGM()->getLevel() < m_sceneAttr->getEnterLevel() ) {
		return EENTER_CON_STAGE_RESULT_NOT_ENOUGH_ROLE_LEVEL;
	}
	const CInstanceAttr * instanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(stageAttr->m_instanceTPID);
	if (instanceAttr == NULL) {
		return EENTER_CON_STAGE_DATA_ERROR ;
	}
	if (stageAttr->getStageIndex() >= (BSLib::uint32)instanceAttr->stageSize() || instanceAttr->m_vecStage[stageAttr->getStageIndex()] == NULL) {
		return EENTER_CON_STAGE_RESULT_NO_SUCH_STAGE_INDEX ;
	}
	const CConInstanceProgressData *conInstanceProgressData = a_sceneRole->m_roleContinuousStageData.getConInstanceProgressData(instanceAttr->m_TPID);
	if (conInstanceProgressData == NULL || !conInstanceProgressData->isActivated()) {
		CRoleContinuousStageData & roleConStageData = a_sceneRole->getRoleConStageData();
		if (roleConStageData.getDailyActivateInstanceCount() <= 0) {
			return EENTER_CON_STAGE_RESULT_NOT_ENOUGH_ACTIVATE_COUNT;
		}
	}
	if (conInstanceProgressData == NULL) {
		if (stageAttr->m_stageIndex != 0) {
			return EENTER_CON_STAGE_RESULT_ERROR_NEXT_STAGE_INDEX;
		}
	} else {
		if (stageAttr->m_stageIndex != conInstanceProgressData->m_curDayStageIndex) {
			return EENTER_CON_STAGE_RESULT_ERROR_NEXT_STAGE_INDEX;
		}
	}
	return EENTER_SCENE_RESULT_SUCCESS;
}

void CSceneContinuousStage::_enterScene(CRoleSceneModule * a_sceneRole)
{
	const CStageAttr *stageAttr = static_cast<const CStageAttr*>(m_sceneAttr);
	if (stageAttr != NULL) {
		const CInstanceAttr *instanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(stageAttr->getInstanceTPID());
		if (instanceAttr != NULL) {
			BSLib::Utility::CHashMap<BSLib::uint32, CConInstanceProgressData>::iterator itr = a_sceneRole->m_roleContinuousStageData.m_hashConInstanceData.find(stageAttr->m_instanceTPID);	
			if (itr == a_sceneRole->m_roleContinuousStageData.m_hashConInstanceData.end()) {
				if (a_sceneRole->m_roleContinuousStageData.m_roleConInstanceBriefData.m_dailyActivateInstanceCount > 0) {
					--a_sceneRole->m_roleContinuousStageData.m_roleConInstanceBriefData.m_dailyActivateInstanceCount;	
					a_sceneRole->_updateRoleConInstanceData(a_sceneRole->m_roleContinuousStageData.m_roleConInstanceBriefData);
				}
				CConInstanceProgressData conInstanceProgress;
				conInstanceProgress.m_isActivated = true;
				conInstanceProgress.m_instanceTPID = stageAttr->getInstanceTPID();
				conInstanceProgress.m_curDayStageIndex = 0;
				conInstanceProgress.m_maxClearStageIndex = 0;
				conInstanceProgress.m_instanceAttr = instanceAttr;
				a_sceneRole->m_roleContinuousStageData.addConInstanceProgressData(conInstanceProgress);
				a_sceneRole->_updateRoleContinuousInstanceProgressData(conInstanceProgress);
			} else {
				CConInstanceProgressData & conInstanceProgress = itr->second;
				if (!conInstanceProgress.m_isActivated) {
					if (a_sceneRole->m_roleContinuousStageData.m_roleConInstanceBriefData.m_dailyActivateInstanceCount > 0) {
						--a_sceneRole->m_roleContinuousStageData.m_roleConInstanceBriefData.m_dailyActivateInstanceCount;	
						conInstanceProgress.m_isActivated = true;
						a_sceneRole->_updateRoleConInstanceData(a_sceneRole->m_roleContinuousStageData.m_roleConInstanceBriefData);
						a_sceneRole->_updateRoleContinuousInstanceProgressData(conInstanceProgress);
					}
				}
			}
			a_sceneRole->m_roleContinuousStageData.setCurEnteredStage(stageAttr->m_instanceTPID, stageAttr->m_stageIndex);
		}
	}
}

void CSceneContinuousStage::_exitScene(CRoleSceneModule * a_sceneRole)
{
	a_sceneRole->m_roleContinuousStageData.exitScene();
}

/////////////////////////////////////////////////////////////////////////////////////////////
CSceneRandomStage::CSceneRandomStage(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr)
:CScene(a_sceneType, a_sceneAttr)
{

}

CSceneRandomStage::~CSceneRandomStage()
{

}

GSLib::SceneSystem::GM::EEnterSceneResult CSceneRandomStage::canEnterScene(CRoleSceneModule * a_sceneRole)
{
	if (a_sceneRole == NULL || a_sceneRole->getRoleGM() == NULL) {
		return EENTER_RANDOM_STAGE_FAIL;
	}
	if (a_sceneRole->getRoleGM()->getLevel() < m_sceneAttr->getEnterLevel() ) {
		return EENTER_RANDOM_STAGE_RESULT_NOT_ENOUGH_ROLE_LEVEL;
	}
	const CStageAttr *stageAttr = static_cast<const CStageAttr*>(m_sceneAttr);
	if (stageAttr == NULL) {
		return EENTER_RANDOM_STAGE_FAIL;
	}
	if (a_sceneRole->m_curScene != NULL) {
		if (a_sceneRole->m_curScene->getSceneType() != ESCENE_TYPE_CITY) {
			return EENTER_RANDOM_STAGE_RESULT_ALREADY_IN_OTHER_INSTANCE;
		}
	}
	if (a_sceneRole->getRoleGM() == NULL) {
		return EENTER_RANDOM_STAGE_FAIL;
	}

	return EENTER_SCENE_RESULT_SUCCESS;
}

void CSceneRandomStage::reportStageResult(CRoleSceneModule & a_sceneRole, const CStageReportResult & a_result)
{
	if (!a_result.m_isWin) {
		CMsgSceneSystemGM2GCAckStageResultReport msgAck;
		msgAck.m_result = ESEND_STAGE_RESULT_REPORT_RESULT_SUCCESS;
		a_sceneRole.sendMsgToClient(msgAck);
		a_sceneRole.exitScene();
		return;
	}
	ESendStageResultReportResult result = ESEND_STAGE_RESULT_REPORT_RESULT_SUCCESS;
	if (a_sceneRole.m_curScene == NULL || a_sceneRole.m_curScene->getSceneType() != ESCENE_TYPE_RANDOM_STAGE) {
		result = ESEND_STAGE_RESULT_REPORT_NOT_IN_STAGE;
	}
	if (a_sceneRole.m_curScene->getStageMonsterPrize().isValid()) {
		result = ESEND_STAGE_RESULT_REPORT_HAS_REPROT_RESULT;
	}

	if (result == ESEND_STAGE_RESULT_REPORT_RESULT_SUCCESS) {
		a_sceneRole.m_curScene->getStageMonsterPrize().setValid(true);
	}
	CMsgSceneSystemGM2GCAckStageResultReport msgAck;
	msgAck.m_result = result;
	a_sceneRole.sendMsgToClient(msgAck);
}

void CSceneRandomStage::_enterScene(CRoleSceneModule * a_sceneRole)
{
	const CStageAttr *stageAttr = static_cast<const CStageAttr*>(m_sceneAttr);
	if (stageAttr != NULL) {
		genMonster(a_sceneRole);
		genStagePrize();
	}	
}

void CSceneRandomStage::_exitScene(CRoleSceneModule * a_sceneRole)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////
CSceneGoldLandStage::CSceneGoldLandStage(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr)
:CScene(a_sceneType, a_sceneAttr)
{

}

CSceneGoldLandStage::~CSceneGoldLandStage()
{

}

EEnterSceneResult CSceneGoldLandStage::canEnterScene(CRoleSceneModule * a_sceneRole)
{
	if (a_sceneRole == NULL || a_sceneRole->getRoleGM() == NULL) {
		return EEnter_GREED_LAND_STAGE_FAIL;
	}
	if (a_sceneRole->getRoleGM()->getLevel() < m_sceneAttr->getEnterLevel() ) {
		return EENTER_SCENE_RESULT_NOT_ENOUGH_ROLE_LEVEL;
	}
	const CStageAttr *stageAttr = static_cast<const CStageAttr*>(m_sceneAttr);
	if (stageAttr == NULL) {
		return EEnter_GREED_LAND_STAGE_FAIL;
	}
	if (a_sceneRole->m_curScene != NULL) {
		if (a_sceneRole->m_curScene->getSceneType() != ESCENE_TYPE_CITY) {
			return EENTER_SCENE_RESULT_ALREADY_IN_OTHER_INSTANCE;
		}
	}

	if (a_sceneRole->m_roleInstanceData.m_roleStageSystemData.getGreedLandEntrances() <= 0) {
		return EEnter_GREED_LAND_STAGE_NO_ENTRANCE_TICKET;
	}
	if (stageAttr->getStageIndex() > 0) {
		CFinishStage * stageData = a_sceneRole->m_roleInstanceData.getStage(stageAttr->getInstanceTPID(), stageAttr->getStageIndex() - 1);
		if (stageData == NULL) {
			return EEnter_GREED_LAND_STAGE_FAIL;
		}
		if (!stageData->isValid()) {
			return EEnter_GREED_LAND_STAGE_NOT_OPEN;
		}
	}
	return EENTER_SCENE_RESULT_SUCCESS;
}

void CSceneGoldLandStage::reportStageResult(CRoleSceneModule & a_sceneRole, const CStageReportResult & a_reportResult)
{
	const CStageAttr *stageAttr = static_cast<const CStageAttr*>(m_sceneAttr);
	if (stageAttr == NULL) {
		return;
	}
	if (!a_reportResult.m_isWin) {
		CMsgSceneSystemGM2GCAckStageResultReport msgAck;
		msgAck.m_result = ESEND_STAGE_RESULT_REPORT_RESULT_SUCCESS;
		a_sceneRole.sendMsgToClient(msgAck);
		a_sceneRole.exitScene();
		return;
	}
	CFinishStage finsStageData;
	a_sceneRole.m_roleInstanceData.reportStageResult(stageAttr->getInstanceTPID(), stageAttr->getStageIndex(), 0, finsStageData);
	a_sceneRole._updateRoleFinishStageDataTable(finsStageData);

	a_sceneRole._updateInstanceAchieve(stageAttr->getInstanceTPID(), stageAttr->getStageIndex());
	BSLib::int32 costVitality = (BSLib::int32)stageAttr->m_costVitality;
	a_sceneRole.getRoleGM()->modifyRoleResource(PlayerSystem::GM::ATTR_VITALITY, -costVitality, "");
	if (a_sceneRole.m_curScene != NULL) {
		a_sceneRole.m_curScene->getStageMonsterPrize().setValid(true);
		a_sceneRole.m_curScene->updateRandomMonsterPrize(a_reportResult.m_clearedRandomMonster);
	}
	if (a_sceneRole.m_roleInstanceData.m_roleStageSystemData.m_greedLandTickets > 0) {
		--a_sceneRole.m_roleInstanceData.m_roleStageSystemData.m_greedLandTickets;
		if (a_sceneRole.m_roleInstanceData.getGreedLandTicketsCount() == C_MAX_GREED_LAND_ENTRANCE_TICKETS - 1) {
			a_sceneRole.m_roleInstanceData.setLastGreedLandTicktsUpdateTime((BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds());
		}
	}
	a_sceneRole._updateRoleStageSystemData(a_sceneRole.m_roleInstanceData.m_roleStageSystemData);
	CMsgSceneSystemGM2GCAckStageResultReport msgAck;
	msgAck.m_result = ESEND_STAGE_RESULT_REPORT_RESULT_SUCCESS;
	a_sceneRole.sendMsgToClient(msgAck);
}

void CSceneGoldLandStage::_enterScene(CRoleSceneModule * a_sceneRole)
{
	const CStageAttr *stageAttr = static_cast<const CStageAttr*>(m_sceneAttr);
	if (stageAttr != NULL) {
		genMonster(a_sceneRole);
		genStagePrize();
	}	
}

void CSceneGoldLandStage::_exitScene(CRoleSceneModule * a_sceneRole)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////
CSceneExpLandStage::CSceneExpLandStage(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr)
:CScene(a_sceneType, a_sceneAttr)
{

}

CSceneExpLandStage::~CSceneExpLandStage()
{

}

EEnterSceneResult CSceneExpLandStage::canEnterScene(CRoleSceneModule * a_sceneRole)
{
	if (a_sceneRole == NULL || a_sceneRole->getRoleGM() == NULL) {
		return EEnter_GREED_LAND_STAGE_FAIL;
	}
	if (a_sceneRole->getRoleGM()->getLevel() < m_sceneAttr->getEnterLevel() ) {
		return EENTER_SCENE_RESULT_NOT_ENOUGH_ROLE_LEVEL;
	}
	const CStageAttr *stageAttr = static_cast<const CStageAttr*>(m_sceneAttr);
	if (stageAttr == NULL) {
		return EEnter_GREED_LAND_STAGE_FAIL;
	}
	if (a_sceneRole->m_curScene != NULL) {
		if (a_sceneRole->m_curScene->getSceneType() != ESCENE_TYPE_CITY) {
			return EENTER_SCENE_RESULT_ALREADY_IN_OTHER_INSTANCE;
		}
	}

	if (a_sceneRole->m_roleInstanceData.m_roleStageSystemData.getGreedLandEntrances() <= 0) {
		return EEnter_GREED_LAND_STAGE_NO_ENTRANCE_TICKET;
	}
	if (stageAttr->getStageIndex() > 0) {
		CFinishStage * stageData = a_sceneRole->m_roleInstanceData.getStage(stageAttr->getInstanceTPID(), stageAttr->getStageIndex() - 1);
		if (stageData == NULL) {
			return EEnter_GREED_LAND_STAGE_FAIL;
		}
		if (!stageData->isValid()) {
			return EEnter_GREED_LAND_STAGE_NOT_OPEN;
		}
	}
	return EENTER_SCENE_RESULT_SUCCESS;
}

void CSceneExpLandStage::reportStageResult(CRoleSceneModule & a_sceneRole, const CStageReportResult & a_reportResult)
{
	const CStageAttr *stageAttr = static_cast<const CStageAttr*>(m_sceneAttr);
	if (stageAttr == NULL) {
		return;
	}
	if (!a_reportResult.m_isWin) {
		CMsgSceneSystemGM2GCAckStageResultReport msgAck;
		msgAck.m_result = ESEND_STAGE_RESULT_REPORT_RESULT_SUCCESS;
		a_sceneRole.sendMsgToClient(msgAck);
		a_sceneRole.exitScene();
		return;
	}
	CFinishStage finsStageData;
	a_sceneRole.m_roleInstanceData.reportStageResult(stageAttr->getInstanceTPID(), stageAttr->getStageIndex(), 0, finsStageData);
	a_sceneRole._updateRoleFinishStageDataTable(finsStageData);

	a_sceneRole._updateInstanceAchieve(stageAttr->getInstanceTPID(), stageAttr->getStageIndex());
	BSLib::int32 costVitality = (BSLib::int32)stageAttr->m_costVitality;
	a_sceneRole.getRoleGM()->modifyRoleResource(PlayerSystem::GM::ATTR_VITALITY, -costVitality, "");
	if (a_sceneRole.m_curScene != NULL) {
		a_sceneRole.m_curScene->getStageMonsterPrize().setValid(true);
		a_sceneRole.m_curScene->updateRandomMonsterPrize(a_reportResult.m_clearedRandomMonster);
	}
	if (a_sceneRole.m_roleInstanceData.m_roleStageSystemData.m_greedLandTickets > 0) {
		--a_sceneRole.m_roleInstanceData.m_roleStageSystemData.m_greedLandTickets;
		if (a_sceneRole.m_roleInstanceData.getGreedLandTicketsCount() == C_MAX_GREED_LAND_ENTRANCE_TICKETS - 1) {
			a_sceneRole.m_roleInstanceData.setLastGreedLandTicktsUpdateTime((BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds());
		}
	}
	a_sceneRole._updateRoleStageSystemData(a_sceneRole.m_roleInstanceData.m_roleStageSystemData);
	CMsgSceneSystemGM2GCAckStageResultReport msgAck;
	msgAck.m_result = ESEND_STAGE_RESULT_REPORT_RESULT_SUCCESS;
	a_sceneRole.sendMsgToClient(msgAck);
}

void CSceneExpLandStage::_enterScene(CRoleSceneModule * a_sceneRole)
{
	const CStageAttr *stageAttr = static_cast<const CStageAttr*>(m_sceneAttr);
	if (stageAttr != NULL) {
		genMonster(a_sceneRole);
		genStagePrize();
	}
}

void CSceneExpLandStage::_exitScene(CRoleSceneModule * a_sceneRole)
{

}








}//GM

}//SceneSystem

}//GSLib

