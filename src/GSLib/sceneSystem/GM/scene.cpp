//////////////////////////////////////////////////////////////////////
//	created:	2015/1/8
//	filename: 	src\GSLib\sceneSystem\GM\scene.cpp
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/sceneSystem/GM/scene.h>
#include <GSLib/sceneSystem/GM/roleSceneModule.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <BSLib/utility/random.h>
#include <GSLib/prizeSystem/GM/rolePrizeModule.h>
#include <GSLib/taskSystem/GM/roleTaskModule.h>
#include <GSLib/playerSystem/GM/roleBagModuleGM.h>
#include <GSLib/sceneSystem/GM/sceneSystemDataMgr.h>
#include <GSLib/playerSystem/GM/playerGMMgr.h>

namespace GSLib
{

namespace SceneSystem
{	

namespace GM
{

CScene::CScene(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr)
:m_sceneType(a_sceneType)
,m_sceneAttr(a_sceneAttr)
{

}

CScene::~CScene()
{
	m_setSceneRole.clear();
	m_stagePrize.clear();
}

BSLib::uint32 CScene::getScenePlayerCount() const
{
	return (BSLib::uint32)m_setSceneRole.size();
}

ESceneType CScene::getSceneType() const
{
	return m_sceneType;
}

void CScene::setSceneID(BSLib::uint32 a_sceneID)
{
	m_sceneID = a_sceneID;
}

BSLib::uint32 CScene::getSceneID() const
{
	return m_sceneID;
}

BSLib::uint32 CScene::getSceneTPID() const
{
	if (m_sceneAttr != NULL) {
		return m_sceneAttr->getSceneTPID();
	}
	return 0;
}

const CSceneAttr *CScene::getSceneAttr() const
{
	return m_sceneAttr;
}

void CScene::enterScene(CRoleSceneModule * a_sceneRole)
{
	if (a_sceneRole != NULL || a_sceneRole->getRoleGM() != NULL) {
		if (m_setSceneRole.find(a_sceneRole->getRoleGM()->getRoleKey()) == m_setSceneRole.end()) {
			_enterScene(a_sceneRole);
			m_setSceneRole.insert(a_sceneRole->getRoleGM()->getRoleKey());
		}
	}
}

void CScene::exitScene(CRoleSceneModule * a_sceneRole)
{
	if (a_sceneRole != NULL && a_sceneRole->getRoleGM() != NULL) {
		_exitScene(a_sceneRole);
		if (m_stagePrize.isValid()) {
			std::vector<BSLib::uint32> receiveItems;
			determineStagePrizeItem(*a_sceneRole, receiveItems);
			m_stagePrize.setValid(false);
		}
		m_stagePrize.clear();
		m_stageMonster.clear();
		m_setSceneRole.erase(a_sceneRole->getRoleGM()->getRoleKey());
	}
}

void CScene::sendToAllRoles(GFLib::CMessage &message)
{
	for (std::set<SRoleKey>::iterator itr = m_setSceneRole.begin(); itr != m_setSceneRole.end(); ++itr) {
		PlayerSystem::GM::CRoleGM *role = PlayerSystem::GM::CPlayerGMMgr::singleton().getRoleGM(*itr);
		if (role != NULL) {
			role->sendMsgToClient(message);
		}
	}
}

void CScene::genMonster(CRoleSceneModule * a_sceneRole)
{
	const CStageAttr * stageAttr = static_cast<const CStageAttr *>(m_sceneAttr);
	if (stageAttr != NULL && a_sceneRole != NULL) {
		if (stageAttr->m_difficulty > 0) {
			_genRandomStageMonster(a_sceneRole);
		} else {
			BSLib::uint32 count = 0;
			CStagePrizeAttr prize;
			_genStagePrizeAttr(*a_sceneRole, prize);
			for (BSLib::Utility::CHashMap<BSLib::uint32, CStageUnitAttr*>::const_iterator stage = stageAttr->m_hashStageUnits.begin(); stage != stageAttr->m_hashStageUnits.end(); ++stage) {
				CStageUnitAttr *unitAttr = stage->second;
				if (unitAttr != NULL) {
					_genMonster(m_stageMonster, *unitAttr, prize, count);
				}
			}
		}
	}
}

void CScene::reportStageResult(CRoleSceneModule & a_sceneRole, const CStageReportResult & a_result)
{
	
}

void CScene::clearStage(CRoleSceneModule& a_sceneRole, bool isBreakDownItem)
{

}

CStageMonster & CScene::getStageMonsterPrize()
{
	return m_stagePrize;
}

void CScene::updateRandomMonsterPrize(const std::vector<BSLib::uint32> &a_clearedRandomMonster)
{
	std::set<BSLib::uint32> setRandomMonster(a_clearedRandomMonster.begin(), a_clearedRandomMonster.end());
	std::vector<CMonster>::iterator monster = m_stagePrize.m_vecDropMonster.begin();
	while(monster != m_stagePrize.m_vecDropMonster.end()) {	
		if (monster->m_type != RandomDropMonster) {
			++monster;
			continue;
		}
		std::set<BSLib::uint32>::iterator searchMonster = setRandomMonster.find(monster->m_index);
		if (searchMonster == setRandomMonster.end()) {
			monster = m_stagePrize.m_vecDropMonster.erase(monster);
		} else {
			++monster;
		}
	}
}

void CScene::determineStagePrizeItem(CRoleSceneModule& a_sceneRole, const std::vector<BSLib::uint32>& a_receiveItems)
{
	if (a_sceneRole.getRoleGM() == NULL) {
		return;
	}
	if (m_sceneAttr == NULL) {
		return;
	}
	PlayerSystem::GM::CRoleBagModuleGM *bagModule = a_sceneRole.getRoleGM()->getRoleBag();
	if (bagModule == NULL) {
		return;
	}
	std::multiset<BSLib::uint32> setReceiveItem(a_receiveItems.begin(), a_receiveItems.end());
	if (m_stagePrize.isValid()) {
		PrizeSystem::GM::CRolePrizeModule *prizeModue = (PrizeSystem::GM::CRolePrizeModule *)a_sceneRole.getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PRIZE);
		if (prizeModue != NULL) {
			std::vector<ItemSystem::GM::CPrizeItem> vecItem;
			for (std::vector<CMonster>::const_iterator monster = m_stagePrize.m_vecDropMonster.begin(); monster != m_stagePrize.m_vecDropMonster.end(); ++monster) {
				for (std::vector<ItemSystem::GM::CPrizeItem>::const_iterator item = monster->m_vecDropItem.begin(); item != monster->m_vecDropItem.end(); ++item) {
					std::multiset<BSLib::uint32>::iterator object = setReceiveItem.find(item->m_itemTPID);
					if (object != setReceiveItem.end()) { // receive item
						ItemSystem::GM::CPrizeItem prizeItem;
						prizeItem.m_itemTPID = item->m_itemTPID;
						prizeItem.m_itemCount = 1;
						vecItem.push_back(prizeItem);
						setReceiveItem.erase(object);
					} else { // selling item
						bagModule->sellItemNotInBag(item->m_itemTPID, 1);
						BSLIB_LOG_DEBUG(ETT_GSLIB_SCENESYSTEM, "--sell item determine item stageTPID[%d] sold itemid[%d] count[%d]\n", m_sceneAttr->m_sceneTPID, item->m_itemTPID, 1);
					}
				}
			}
			if (!vecItem.empty()) {
				prizeModue->prizeRequest(vecItem, toMailString("系统信息"), toMailString("副本掉落道具(背包满)"), toMailString("恭喜您!通关副本，获得了丰厚的奖励，奖励如下："), "InstancePrize");//todo
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
			}
		}
		m_stagePrize.setValid(false);
	}
}

void CScene::_genMonster(CStageMonster & a_stageMonster, const CStageUnitAttr & a_stageUnitAttr, const CStagePrizeAttr & a_stagePrizeAttr, BSLib::uint32 &a_curIndex)
{
	CStageUnitMonster stageUnit;
	BSLib::uint32 unitIndex = 0;
	for (std::vector<CMonsterAttrBatch>::const_iterator unit = a_stageUnitAttr.m_vecMonsterAttrBatch.begin(); unit != a_stageUnitAttr.m_vecMonsterAttrBatch.end(); ++unit) {
		CMonsterBatch monsterBatch;
		monsterBatch.m_batchIndex = unitIndex++;
		for (std::vector<CDropMonsterAttr>::const_iterator monster = unit->m_vecMonsterAttr.begin(); monster != unit->m_vecMonsterAttr.end(); ++monster) {
			const CDropMonsterAttr monsterAttr = *monster;
			CMonster monsetrInstance;
			_getMonster(monsterAttr, a_stagePrizeAttr, monsetrInstance);
			if (monsetrInstance.m_type != None) {
				monsetrInstance.m_index = a_curIndex++;
				monsterBatch.addMonster(monsetrInstance);
				a_stageMonster.addDropMonster(monsetrInstance);
			}
		}
		if (monsterBatch.size() > 0) {
			stageUnit.addMonsterBatch(monsterBatch);
		}
	}
	//elite
	if (a_stageUnitAttr.m_randomElite.m_dropType == Elite) {
		_getMonster(a_stageUnitAttr.m_randomElite, a_stagePrizeAttr, stageUnit.m_randomElite);
		if (stageUnit.m_randomElite.m_type == Elite) {
			stageUnit.m_randomElite.m_index = a_curIndex++;
			a_stageMonster.addDropMonster(stageUnit.m_randomElite);
		}
	}
	a_stageMonster.addStageUnit(stageUnit);
}

void CScene::_getMonster(const CDropMonsterAttr& a_monsterAttr, const CStagePrizeAttr& a_stagePrizeAttr, CMonster& a_monster)
{
	if (a_monsterAttr.m_dropType == None) {
		return;
	}
	if (a_monsterAttr.m_dropType == RandomDropMonster) {
		BSLib::uint32 rollNum = BSLib::Utility::CRandom::randomBetween(1, 10000);
		BSLib::uint32 curWeight = 0;
		for (std::vector<CDropItem>::const_iterator drop = a_stagePrizeAttr.m_vecRandomDrops.begin(); drop != a_stagePrizeAttr.m_vecRandomDrops.end(); ++drop) {
			curWeight += drop->m_weight;
			if (rollNum <= curWeight) {
				ItemSystem::GM::CPrizeItem prize;
				prize.m_itemTPID = drop->m_itemTPID;
				prize.m_itemCount = drop->m_itemCount;
				a_monster.m_vecDropItem.push_back(prize);
				break;
			} 
		}
	} else if (a_monsterAttr.m_dropType == CertainlyDropMonster) {
		BSLib::uint32 rollNum = BSLib::Utility::CRandom::randomBetween(1, 10000);
		BSLib::uint32 curWeight = 0;
		for (std::vector<CDropItem>::const_iterator drop = a_stagePrizeAttr.m_vecCertainlyDrops.begin(); drop != a_stagePrizeAttr.m_vecCertainlyDrops.end(); ++drop) {
			curWeight += drop->m_weight;
			if (rollNum <= curWeight) {
				ItemSystem::GM::CPrizeItem prize;
				prize.m_itemTPID = drop->m_itemTPID;
				prize.m_itemCount = drop->m_itemCount;
				a_monster.m_vecDropItem.push_back(prize);
				break;
			} 
		}
	} else if (a_monsterAttr.m_dropType == Boss) {
		for (std::vector<CDropItem>::const_iterator drop = a_stagePrizeAttr.m_vecBossDrops.begin(); drop != a_stagePrizeAttr.m_vecBossDrops.end(); ++drop) {
			bool isRollIn = BSLib::Utility::CRandom::selectByOdds(drop->m_weight, drop->m_totalWeight);
			if (isRollIn) {
				ItemSystem::GM::CPrizeItem prize;
				prize.m_itemTPID = drop->m_itemTPID;
				prize.m_itemCount = drop->m_itemCount;
				a_monster.m_vecDropItem.push_back(prize);
			} 
		}
	} else if (a_monsterAttr.m_dropType == Elite) {
		bool isGen = isGen = BSLib::Utility::CRandom::selectByOdds(a_monsterAttr.m_weight, a_monsterAttr.m_totalWeight);;
		if (!isGen) {
			return;
		}
		for (std::vector<CDropItem>::const_iterator drop = a_stagePrizeAttr.m_vecEliteDrops.begin(); drop != a_stagePrizeAttr.m_vecEliteDrops.end(); ++drop) {
			bool isRollIn = BSLib::Utility::CRandom::selectByOdds(drop->m_weight, drop->m_totalWeight);
			if (isRollIn) {
				ItemSystem::GM::CPrizeItem prize;
				prize.m_itemTPID = drop->m_itemTPID;
				prize.m_itemCount = drop->m_itemCount;
				a_monster.m_vecDropItem.push_back(prize);
			} 
		}
	}
	a_monster.m_type = a_monsterAttr.m_dropType;
	a_monster.m_monsterAttr = &a_monsterAttr;
}

void CScene::genStagePrize()
{
	m_stagePrize = m_stageMonster;
}

void CScene::_genStagePrizeAttr(CRoleSceneModule& a_sceneRole, CStagePrizeAttr & a_stagePrize) const
{
	_getPetTaskPrizeAttr(a_sceneRole, a_stagePrize);

	const CStageAttr * stageAttr = static_cast<const CStageAttr *>(m_sceneAttr);
	const CStagePrizeAttr* stagePrizeAttr = NULL; 
	if (stageAttr != NULL) {
		if (a_sceneRole.getRoleGM() != NULL) {
			TaskSystem::GM::CRoleTaskModule *roleTask = (TaskSystem::GM::CRoleTaskModule *)a_sceneRole.getRoleGM()->getPlayerModuleGM(EMODULECTYPE_TASK);
			if (roleTask != NULL) {
				if (roleTask->getMainTaskData().getType() == TaskSystem::GM::EMAIN_TASK_TYPE_ITEM_DROP &&
					roleTask->getMainTaskData().getState() == TaskSystem::GM::ETASKSTATE_ACCEPT) {
					if (roleTask->getMainTaskData().getAttr() != NULL) {
						if (roleTask->getMainTaskData().getAttr()->getStageTPID() == stageAttr->getSceneTPID()) {
							stagePrizeAttr = &(roleTask->getMainTaskData().getAttr()->getStagePrizeAttr());
						} 
					}
				}
			}
		}
		if (stagePrizeAttr != NULL) {
			a_stagePrize.append(*stagePrizeAttr);
		}
		a_stagePrize.append(stageAttr->m_stagePrizeAttr);
	}

}

bool CScene::_getPetTaskPrizeAttr(CRoleSceneModule& a_sceneRole, CStagePrizeAttr & a_stagePrizeAttr) const
{
	TaskSystem::GM::CRoleTaskModule *roleTask = 
		(TaskSystem::GM::CRoleTaskModule *)a_sceneRole.getRoleGM()->getPlayerModuleGM(EMODULECTYPE_TASK);
	if (roleTask == NULL) {
		return NULL;
	}
	const CStageAttr * stageAttr = static_cast<const CStageAttr *>(m_sceneAttr);
	if (stageAttr != NULL) {
		for (BSLib::Utility::CHashMap<BSLib::uint32, TaskSystem::GM::CRolePetTaskData>::iterator itr 
			= roleTask->m_hashPetTask.begin(); itr != roleTask->m_hashPetTask.end(); ++itr) {
				const TaskSystem::GM::CRolePetTaskData &taskData = itr->second;
				const TaskSystem::GM::CPetTaskAttr * taskAttr = taskData.m_taskAttr;
				if (taskAttr != NULL) {
					if (taskData.m_state == TaskSystem::GM::ETASKSTATE_ACCEPT) {
						CDropItem dropItem;
						dropItem.m_itemTPID = taskAttr->m_param2;
						dropItem.m_itemCount = 1;
						dropItem.m_weight = taskAttr->m_param4;
						dropItem.m_totalWeight = 10000;
						if (taskAttr->m_param1 == stageAttr->m_sceneTPID) {
							if (taskAttr->m_type == TaskSystem::GM::EPET_TASK_TYPE_BOSS_DROP) {
								a_stagePrizeAttr.m_vecBossDrops.push_back(dropItem);	
								return true;
							} else if (taskAttr->m_type == TaskSystem::GM::EPET_TASK_TYPE_MONSTER_DROP) {
								a_stagePrizeAttr.m_vecCertainlyDrops.push_back(dropItem);
								return true;
							}
						}
					}
				}
		}
	}

	return false;
}

void CScene::_genRandomStageMonster(CRoleSceneModule * a_sceneRole)
{
	const CStageAttr *stageAttr = static_cast<const CStageAttr *>(m_sceneAttr);
	if (stageAttr != NULL) {
		BSLib::uint32 count = 0;
		CStagePrizeAttr stagePrize;
		_genStagePrizeAttr(*a_sceneRole, stagePrize);
		//if (stagePrize != NULL) {
		const CStageTemplate *stageTemplate = CSceneSystemDataMgr::singleton().getStageTemplate(stageAttr->m_difficulty);	
		if (stageTemplate != NULL) {
			for (BSLib::uint32 unit = 0; unit < stageTemplate->m_stageUnitCount; ++unit) {
				CStageUnitAttr unitAttr;
				for (BSLib::uint32 batch = 0; batch < stageTemplate->m_unitBatchCount; ++batch) {
					CMonsterAttrBatch batchAttr;
					BSLib::uint32 rollMonsterCount = BSLib::Utility::CRandom::randomBetween(stageTemplate->m_minStageUnitBatchCount, stageTemplate->m_maxStageUnitBatchCount);
					for (BSLib::uint32 index = 0; index < rollMonsterCount; ++index) {
						CDropMonsterAttr monsterAttr;
						monsterAttr.m_ID = 0;
						monsterAttr.m_dropType = CertainlyDropMonster;
						batchAttr.addMonsterAttr(monsterAttr);
					}
					if (unit == stageTemplate->m_stageUnitCount - 1) {
						if (batch == stageTemplate->m_unitBatchCount - 1) {
							CDropMonsterAttr boss;
							boss.m_ID = 0;
							boss.m_dropType = Boss;	
							batchAttr.addMonsterAttr(boss);
						}
					}
					unitAttr.m_vecMonsterAttrBatch.push_back(batchAttr);
				}
				_genMonster(m_stageMonster, unitAttr, stagePrize, count);
			}
		}
		//}
	}
}




}//GM

}//SceneSystem

}//GSLib
