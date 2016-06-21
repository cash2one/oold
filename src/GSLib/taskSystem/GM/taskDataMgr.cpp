#include <BSLib/utility/file/dirInfo.h>
#include <GSLib/taskSystem/GM/taskDataMgr.h>
#include <BSLib/utility/string.h>
#include <BSLib/utility/table.h>
#include <BSLib/utility/tracer.h>
#include <BSLib/utility/convert.h>
#include <GSLib/itemSystem/GM/itemAttributeGM.h>
#include <GSLib/tracer.h>
#include <BSLib/utility/random.h>

namespace GSLib
{

namespace TaskSystem
{

namespace GM
{

CTaskDataMgr::CTaskDataMgr()
:m_taskSystemResetHour(3)
,m_taskSystemResetMinute(0)
{

}

CTaskDataMgr::~CTaskDataMgr()
{

}

BSLIB_SINGLETON_DEFINE(CTaskDataMgr);	

bool CTaskDataMgr::loadConfig(const std::string & a_path)
{
	_initPetTaskColorAttr();

	if (!_loadDailyTaskData(a_path)) {
		return false;
	}

	if (!_loadDailyTaskConfig(a_path)) {
		return false;
	}

	if (!_loadMainTaskConfig(a_path)) {
		return false;
	}

	if (!_loadPetTaskConfig(a_path)) {
		return false;
	}

	return true;
}

const CDailyTaskAttr * CTaskDataMgr::getDailyTask(BSLib::uint32 a_TPID) const
{
	BSLib::Utility::CHashMap<BSLib::uint32, CDailyTaskAttr*>::const_iterator itr = m_hashDailyTaskData.find(a_TPID);
	if (itr != m_hashDailyTaskData.end()) {
		return itr->second;
	}

	return NULL;
}

const BSLib::Utility::CHashMap<BSLib::uint32, CDailyTaskAttr*> & CTaskDataMgr::getDailyTask() const
{
	return m_hashDailyTaskData;
}

const CMainTaskAttr *CTaskDataMgr::getMainTask(BSLib::uint32 a_TPID) const
{
	std::map<BSLib::uint32, CMainTaskAttr*>::const_iterator itr = m_mapMainTaskData.find(a_TPID);
	if (itr != m_mapMainTaskData.end()) {
		return itr->second;
	}

	return NULL;
}

const CMainTaskAttr* CTaskDataMgr::getFirstMainTask() const
{
	if (m_mapMainTaskData.size() > 0) {
		return m_mapMainTaskData.begin()->second;
	}

	return NULL;
}

const CMainTaskAttr* CTaskDataMgr::getNextMainTask(BSLib::uint32 a_mainTaskTPID) const
{
	std::map<BSLib::uint32, CMainTaskAttr*>::const_iterator cur = m_mapMainTaskData.find(a_mainTaskTPID);
	if (cur != m_mapMainTaskData.end()) {
		++cur;
		if (cur != m_mapMainTaskData.end()) {
			return cur->second;
		}
	}

	return NULL;
}

const CPetTaskAttr* CTaskDataMgr::getPetTaskByTaskID(BSLib::uint32 a_TPID) const
{
	BSLib::Utility::CHashMap<BSLib::uint32, CPetTaskAttr*>::const_iterator itr = m_hashPetAttrByTaskID.find(a_TPID);
	if (itr != m_hashPetAttrByTaskID.end()) {
		return itr->second;
	}

	return NULL;	
}

BSLib::uint32 CTaskDataMgr::getTaskSystemResetHour() const
{
	return m_taskSystemResetHour;
}

BSLib::uint32 CTaskDataMgr::getTaskSystemResetMinte() const
{
	return m_taskSystemResetMinute;
}

BSLib::uint32 CTaskDataMgr::getFirstMainTaskTPID() const
{
	return m_firstMainTaskTPID;
}

CPetTaskAttr* CTaskDataMgr::getRandomPetTask(BSLib::uint32 a_petID, BSLib::uint32 a_roleLevel)
{
	BSLib::Utility::CHashMap< BSLib::uint32, std::vector<CPetTaskAttr *> >::iterator itr 
		= m_hashPetAttrByPetID.find(a_petID);
	if (itr != m_hashPetAttrByPetID.end()) {
		std::vector<CPetTaskAttr *>  &taskList = itr->second;
		std::vector<CPetTaskAttr *>  findTaskList;
		for (std::vector<CPetTaskAttr *>::iterator task = taskList.begin(); task != taskList.end(); ++task) {
			CPetTaskAttr *petTask = *task;
			if (petTask != NULL) {
				if (a_roleLevel >= petTask->m_minRoleLevel &&  a_roleLevel <= petTask->m_maxRoleLevel) {
					findTaskList.push_back(petTask);
					continue;
				} 
			}
		}
		if (!findTaskList.empty()) {
			BSLib::uint32 rollNum = BSLib::Utility::CRandom::randomBetween(0, findTaskList.size() - 1);			
			if (rollNum < taskList.size()) {
				return taskList.at(rollNum);
			}
		}
	}

	return NULL;
}

EPetTaskColor CTaskDataMgr::genRandomPetTaskColor()
{
	BSLib::uint32 weight = 0;
	for (std::vector<CPetTaskColorAttr>::iterator itr = m_petTaskColorList.begin(); 
		itr != m_petTaskColorList.end(); ++itr) {
		weight += itr->m_weight;
	}
	BSLib::uint32 totalWeight = 0;
	BSLib::uint32 rollNum = BSLib::Utility::CRandom::randomBetween(1, weight);
	for (std::vector<CPetTaskColorAttr>::iterator itr = m_petTaskColorList.begin(); 
		itr != m_petTaskColorList.end(); ++itr) {
			totalWeight += itr->m_weight;
			if (rollNum < totalWeight) {
				return itr->m_color;
			}
	}

	return EPET_TASK_COLOR_WHITE;
}

const CPetTaskColorAttr *CTaskDataMgr::getPetTaskColorAttr(EPetTaskColor a_color) const
{
	if (a_color < EPET_TASK_COLOR_WHITE || a_color > EPET_TASK_COLOR_ORANGE) {
		return NULL;
	}
	return &m_petTaskColorList.at(a_color);
}

void CTaskDataMgr::_addDailyTaskData(CDailyTaskAttr * a_task)
{
	if (a_task == NULL || a_task->m_taskTPID == 0 || a_task->m_taskType == EDAILY_TASK_TYPE_NONE) {
		return;
	}

	if (m_hashDailyTaskData.find(a_task->m_taskTPID) != m_hashDailyTaskData.end()) {
		return;
	}

	m_hashDailyTaskData.setValue(a_task->m_taskTPID, a_task);
}

void CTaskDataMgr::_addMainTaskData(CMainTaskAttr * a_task)
{
	if (a_task == NULL || a_task->m_taskTPID == 0 || a_task->m_taskType == EMAIN_TASK_TYPE_NONE) {
		return;
	}

	if (m_mapMainTaskData.find(a_task->m_taskTPID) != m_mapMainTaskData.end()) {
		return;
	}

	m_mapMainTaskData.insert(std::make_pair(a_task->m_taskTPID, a_task));
}

void CTaskDataMgr::_addPetTaskData(CPetTaskAttr *a_task)
{
	if (a_task != NULL) {
		m_hashPetAttrByTaskID.setValue(a_task->m_taskTPID, a_task);

		BSLib::Utility::CHashMap< BSLib::uint32, std::vector<CPetTaskAttr *> >::iterator itr 
			= m_hashPetAttrByPetID.find(a_task->m_petID);
		if (itr != m_hashPetAttrByPetID.end()) {
			std::vector<CPetTaskAttr*> & taskList = itr->second;
			taskList.push_back(a_task);
		} else {
			std::vector<CPetTaskAttr*> taskList;
			taskList.push_back(a_task);
			m_hashPetAttrByPetID.setValue(a_task->m_petID, taskList);
		}
	}
}

bool CTaskDataMgr::_loadDailyTaskData(const std::string &a_path)
{
	const BSLib::uint32 C_MAX_PRIZE_SIZE = 5;
	BSLib::Utility::CStringA fileName = a_path + "\\t_daily_task.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载日常任务数据失败[%s]", fileName.c_str());
		return false;
	}

	try {
		BSLib::Utility::CTable &table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			CDailyTaskAttr *taskAttr = new CDailyTaskAttr;
			BSLib::Utility::CStringA input(table[i]["f_id"]);
			input >> taskAttr->m_taskTPID;
			input = table[i]["f_type"];
			BSLib::uint16 type;
			input >> type;
			input = table[i]["f_task_name"];
			input >> taskAttr->m_taskName;
			input = table[i]["f_para_1"];
			input >> taskAttr->m_para1;
			input = table[i]["f_para_2"];
			input >> taskAttr->m_para2;
			taskAttr->m_taskType = (EDailyTaskType)type;
			input = table[i]["f_target_count"];
			input >> taskAttr->m_targetCount;
			input = table[i]["f_min_level"];
			input >> taskAttr->m_minRequiredRoleLevel;
			input = table[i]["f_max_level"];
			input >> taskAttr->m_maxRequiredRoleLevel;
			input = table[i]["f_icon"];
			input >> taskAttr->m_icon;
			input = table[i]["f_desc"];
			input >> taskAttr->m_taskDescription;
			input = table[i]["f_jump_id"];
			input >> taskAttr->m_jumpID;
			for (BSLib::uint32 j = 0; j < C_MAX_PRIZE_SIZE; ++j) {
				GSLib::ItemSystem::GM::CPrizeItem item;
				input = table[i]["f_prize_id_" + BSLib::Utility::CConvert::toStringA(j + 1)];
				if (!input.empty()) {
					input >> item.m_itemTPID;
					input = table[i]["f_prize_count_" + BSLib::Utility::CConvert::toStringA(j + 1)];
					input >> item.m_itemCount;
					if (item.m_itemTPID > 0) {
						taskAttr->m_vecItems.push_back(item);
					}
				}
			}
			_addDailyTaskData(taskAttr);
		}
	} catch (...) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载日常任务数据失败[%s]", fileName.c_str());
		return false;		
	}

	return true;
}

bool CTaskDataMgr::_loadDailyTaskConfig(const std::string & a_path)
{
	BSLib::Utility::CStringA fileName = a_path + "\\t_task_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载任务配置失败[%s]", fileName.c_str());
		return false;
	}
	try {
		BSLib::Utility::CTable &table = tableSheet["reset"];
		BSLib::Utility::CStringA data = table[0]["f_daily_task_reset_hour"];
		data >> m_taskSystemResetHour;
		data = table[0]["f_daily_task_reset_minute"];
		data >>m_taskSystemResetMinute;

		BSLib::Utility::CTable &firstMainTask = tableSheet["first_main_task"];
		data = firstMainTask[0]["taksTPID"];
		data >> m_firstMainTaskTPID;
	} catch (...) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载任务配置失败[%s]", fileName.c_str());
		return false;		
	}

	return true;
}

bool CTaskDataMgr::_loadMainTaskConfig(const std::string & a_path)
{
	//const BSLib::uint32 C_MAX_PRIZE_SIZE = 5;
	BSLib::Utility::CStringA fileName = a_path + "\\t_main_task.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载主线任务数据失败[%s]", fileName.c_str());
		return false;
	}

	try {
		BSLib::Utility::CTable &table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			CMainTaskAttr *taskAttr = new CMainTaskAttr;
			BSLib::Utility::CStringA input(table[i]["f_id"]);
			table[i]["f_id"] >> taskAttr->m_taskTPID;
			table[i]["f_name"] >> taskAttr->m_taskName;
			BSLib::int8 type;
			table[i]["f_type"] >> type;
			taskAttr->m_taskType = (EMainTaskType)type;
			table[i]["f_desc"] >> taskAttr->m_taskDescription;
			table[i]["f_start_npc"] >> taskAttr->m_startNPC;
			table[i]["f_end_npc"] >> taskAttr->m_endNPC;
			table[i]["f_level_limit"] >> taskAttr->m_levelLimit;

			BSLib::Utility::CStringA NPC;
			table[i]["f_npc"] >> NPC;
			std::vector<BSLib::Utility::CStringA> npcDetailList; 
			NPC.split(npcDetailList, ",");	
			if (npcDetailList.size() % 3 == 0) {
				if (npcDetailList.size() > 0) {
					taskAttr->m_NPC.m_ID = BSLib::Utility::CConvert::toUint32(npcDetailList[0]);
					taskAttr->m_NPC.m_slotID = BSLib::Utility::CConvert::toUint32(npcDetailList[1]);
					taskAttr->m_NPC.m_isSpawned = BSLib::Utility::CConvert::toUint32(npcDetailList[2]) != 0;
				}
			} else {
				BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载主线任务数据失败[%s], [f_monster_drop]字段填写有误", fileName.c_str());
				return false;
			}
			table[i]["f_stage"] >> taskAttr->m_stageID;
			table[i]["f_monster"] >> taskAttr->m_monsterID;
			BSLib::Utility::CStringA monsterDrop;
			std::vector<std::string> dropList;
			table[i]["f_monster_drop"] >> monsterDrop;
			monsterDrop.split(dropList, ",");
			if (dropList.size() >= 3) {
				if (dropList.size() % 3 == 0) {
					SceneSystem::GM::CDropItem dropItem;
					BSLib::uint32 type = BSLib::Utility::CConvert::toUint32(dropList[0]);	
					dropItem.m_itemTPID = BSLib::Utility::CConvert::toUint32(dropList[1]);	
					dropItem.m_weight = BSLib::Utility::CConvert::toUint32(dropList[2]);	
					dropItem.m_itemCount = 1;
					dropItem.m_totalWeight = 10000;
					if (type == SceneSystem::GM::CertainlyDropMonster) {
						taskAttr->m_taskStageDropItem.m_vecCertainlyDrops.push_back(dropItem);
					} else if (type == SceneSystem::GM::RandomDropMonster) {
						taskAttr->m_taskStageDropItem.m_vecRandomDrops.push_back(dropItem);
					} else if (type == SceneSystem::GM::Boss) {
						taskAttr->m_taskStageDropItem.m_vecBossDrops.push_back(dropItem);
					}
					taskAttr->m_dropItemTPID = dropItem.m_itemTPID;
				} else {
					BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载主线任务数据失败[%s], [f_monster_drop]字段填写有误", fileName.c_str());
					return false;
				}
			} 
			table[i]["f_need_count"] >> taskAttr->m_needCount;

			BSLib::Utility::CStringA prizeItem;
			std::vector<BSLib::Utility::CStringA> prizeItemList;
			table[i]["f_award"] >> prizeItem;
			prizeItem.split(prizeItemList, ",");
			for (std::vector<BSLib::Utility::CStringA>::size_type index = 0; index < prizeItemList.size(); ++index) {
				std::vector<BSLib::Utility::CStringA> itemDetailList;
				prizeItemList[index].split(itemDetailList, "*");
				if (itemDetailList.size() == 2) {
					ItemSystem::GM::CPrizeItem item;
					item.m_itemTPID = BSLib::Utility::CConvert::toUint32(itemDetailList[0]);
					item.m_itemCount = BSLib::Utility::CConvert::toUint32(itemDetailList[1]);
					taskAttr->m_vecPrizeItem.push_back(item);
				} else {
					BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载主线任务数据失败[%s], [f_award]字段填写有误", fileName.c_str());
					return false;
				}
			}

			table[i]["f_dialog_start"] >> taskAttr->m_dialogStart;
			table[i]["f_dialog_after_accept"] >> taskAttr->m_dialogAfterAccept;
			table[i]["f_dialog_end"] >> taskAttr->m_dialogEnd;
			table[i]["f_dialog_npc"] >> taskAttr->m_dialogNPC;
			table[i]["f_dialog_before_fight"] >> taskAttr->m_dialogBeforeFight;
			table[i]["f_dialog_after_boss"] >> taskAttr->m_dialogAfterBoss;
			table[i]["f_dialog_after_win"] >> taskAttr->m_dialogAfterWin;

			_addMainTaskData(taskAttr);
		}
	} catch (...) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载主线任务数据失败[%s]", fileName.c_str());
		return false;		
	}

	return true;
}

bool CTaskDataMgr::_loadPetTaskConfig(const std::string & a_path)
{
	BSLib::Utility::CStringA fileName = a_path + "\\t_pet_task_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载伙伴任务任务数据失败[%s]", fileName.c_str());
		return false;
	}
	
	std::vector<ItemSystem::GM::CPrizeItem> m_prizeItemList;
	try {
		BSLib::Utility::CTable &table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			CPetTaskAttr *taskAttr = new CPetTaskAttr;
			BSLib::Utility::CStringA input(table[i]["f_id"]);
			table[i]["f_id"] >> taskAttr->m_taskTPID;
			table[i]["f_name"] >> taskAttr->m_name;
			table[i]["f_des"] >> taskAttr->m_desc;
			table[i]["f_pet_id"] >> taskAttr->m_petID;
			table[i]["f_weight"] >> taskAttr->m_weight;
			BSLib::int8 type;
			table[i]["f_type"] >> type;
			taskAttr->m_type = (EPetTaskType)type;
			table[i]["f_param_1"] >> taskAttr->m_param1;
			table[i]["f_param_2"] >> taskAttr->m_param2;
			table[i]["f_param_3"] >> taskAttr->m_param3;
			table[i]["f_param_4"] >> taskAttr->m_param4;
			table[i]["f_pet_friendly_value"] >> taskAttr->m_petFriendlyValue;

			BSLib::Utility::CStringA levelRequired;
			std::vector<BSLib::Utility::CStringA> levels;
			table[i]["f_role_level_required"] >> levelRequired;
			levelRequired.split(levels, ",");
			if (levels.size() != 2) {
				BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载伙伴任务数据失败[%s], [f_prize]字段填写有误", fileName.c_str());
				return false;
			}
			taskAttr->m_minRoleLevel = BSLib::Utility::CConvert::toUint32(levels[0]);
			taskAttr->m_maxRoleLevel = BSLib::Utility::CConvert::toUint32(levels[1]);

			BSLib::Utility::CStringA prizeItem;
			std::vector<BSLib::Utility::CStringA> prizeItemList;
			table[i]["f_prize"] >> prizeItem;
			prizeItem.split(prizeItemList, ",");
			for (std::vector<BSLib::Utility::CStringA>::size_type index = 0; index < prizeItemList.size(); ++index) {
				std::vector<BSLib::Utility::CStringA> itemDetailList;
				prizeItemList[index].split(itemDetailList, "*");
				if (itemDetailList.size() == 2) {
					ItemSystem::GM::CPrizeItem item;
					item.m_itemTPID = BSLib::Utility::CConvert::toUint32(itemDetailList[0]);
					item.m_itemCount = BSLib::Utility::CConvert::toUint32(itemDetailList[1]);
					taskAttr->m_prizeItemList.push_back(item);
				} else {
					BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载伙伴任务数据失败[%s], [f_prize]字段填写有误", fileName.c_str());
					return false;
				}
			}
			_addPetTaskData(taskAttr);
		}
	} catch (...) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载伙伴任务任务数据失败[%s]", fileName.c_str());
		return false;		
	}

	return true;
}

void CTaskDataMgr::_initPetTaskColorAttr()
{
	CPetTaskColorAttr none(EPET_TASK_COLOR_NONE, 0, 0, 0);
	m_petTaskColorList.push_back(none);
	CPetTaskColorAttr white(EPET_TASK_COLOR_WHITE, 50, 90, 15);
	m_petTaskColorList.push_back(white);
	CPetTaskColorAttr green(EPET_TASK_COLOR_GREEN, 80, 100, 30);
	m_petTaskColorList.push_back(green);
	CPetTaskColorAttr blue(EPET_TASK_COLOR_BLUE, 100, 110, 40);
	m_petTaskColorList.push_back(blue);
	CPetTaskColorAttr purple(EPET_TASK_COLOR_PURPLE, 150, 150, 10);
	m_petTaskColorList.push_back(purple);
	CPetTaskColorAttr orange(EPET_TASK_COLOR_ORANGE, 200, 200, 5);
	m_petTaskColorList.push_back(orange);
}




}//GM

}//TaskSystem

}//GSLib
