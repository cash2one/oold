//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	src\GSLib\petSystem\GM\petGMMgr.cpp
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <math.h>
#include <GSLib/petSystem/msgPetSystemGC.h>
#include <GSLib/petSystem/msgPetSystem.h>
#include <GSLib/tracer.h>
#include <BSLib/utility/file/dirInfo.h>
#include <BSLib/utility/table.h>
#include "petConfigGMMgr.h"
#include <BSLib/utility/random.h>
#include <GSLib/itemSystem/GM/itemGMMgr.h>

namespace GSLib
{

namespace PetSystem
{	

namespace GM
{

BSLIB_SINGLETON_DEFINE(CPetConfigGMMgr);

CPetConfigGMMgr::CPetConfigGMMgr()
{
}

CPetConfigGMMgr::~CPetConfigGMMgr()
{
}

void CPetConfigGMMgr::init()
{
	;
}

void CPetConfigGMMgr::final()
{
	_removeHotSpringTaskConfig();
}

bool CPetConfigGMMgr::loadGameConfig(const std::string& a_configPath)
{
    if (!_loadHotSpringTaskConfig(a_configPath)){
        return false;
    }

	return true;
}

BSLib::uint32 CPetConfigGMMgr::getPetMaxLevel(ItemTPID a_tpid) const
{
   return ItemSystem::GM::CItemGMMgr::singleton().getPetMaxLevel(a_tpid);
}

BSLib::uint32 CPetConfigGMMgr::getUpgradeNeedFriendlyValue(ItemTPID a_tpid,BSLib::uint32 a_level) const
{
    EQualityID quality = ItemSystem::GM::CItemGMMgr::singleton().getQualityID(a_tpid);
    switch (quality)
    {
    case QUALITY_WHITE:    { return (a_level+1)*70;   } break;
    case QUALITY_GREEN:    { return (a_level+1)*70;   } break;
    case QUALITY_BLUE:     { return (a_level+1)*70;   } break;
    case QUALITY_PURPLE:   { return (a_level+1)*70;  } break;
    case QUALITY_ORANGE:   { return (a_level+1)*70;  } break;
    default:               { return 0; } break;
    }
    return 0;
}

bool CPetConfigGMMgr::getPetAttr(ItemTPID a_tpid,BSLib::uint32 a_level,SBattleAttribute& a_battleAttr) const
{
    ItemSystem::GM::EMainType type = ItemSystem::GM::CItemGMMgr::singleton().getMainType(a_tpid);
    if(type != ItemSystem::GM::EMAIN_TP_PET){
        return false;
    }

    SBattleAttribute baseAttrs;
    SBattleAttribute upgradeAttrs;
    
    if(!ItemSystem::GM::CItemGMMgr::singleton().getPetBaseAttrs(a_tpid,baseAttrs)){
        return false;
    }
    if(!ItemSystem::GM::CItemGMMgr::singleton().getPetUpgradeAttrs(a_tpid,upgradeAttrs)){
        return false;
    }
    if(a_level < 0){
        return false;
    }
    const BSLib::uint32 addLevel = a_level - 1;
    for(BSLib::uint32 i=0;i<MAX_ATTR_INDEX;++i){
        EAttrID attrID = (EAttrID)i;
        BSLib::uint32 baseAttrValue = baseAttrs.getValue(attrID);
        BSLib::uint32 upgradeAttrValue = upgradeAttrs.getValue(attrID);
        BSLib::uint32 newAttr = baseAttrValue + upgradeAttrValue*addLevel;
        a_battleAttr.setValue(attrID,newAttr);
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[getPetAttr][a_tpid=%d][伙伴初始属性值][%s]",a_tpid,a_battleAttr.toLogString().c_str());
    return true;
}

bool CPetConfigGMMgr::getUpgradeAttr(ItemTPID a_tpid,SBattleAttribute& a_upgradeAttrs) const
{
    ItemSystem::GM::EMainType type = ItemSystem::GM::CItemGMMgr::singleton().getMainType(a_tpid);
    if(type != ItemSystem::GM::EMAIN_TP_PET){
        return false;
    }

    if(!ItemSystem::GM::CItemGMMgr::singleton().getPetUpgradeAttrs(a_tpid,a_upgradeAttrs)){
        return false;
    }
    return true;
}

BSLib::uint32 CPetConfigGMMgr::getPetLevel(ItemTPID a_tpid,BSLib::uint32 a_level,BSLib::uint32 a_curFriendlyValue,BSLib::uint32& a_leftFriendlyValue) const
{
    BSLib::uint32 newLevel = a_level;
    BSLib::uint32 curFriendlyValue = a_curFriendlyValue;
    BSLib::uint32 needFriendlyValue = getUpgradeNeedFriendlyValue(a_tpid,a_level);
    BSLib::uint32 maxLevel = getPetMaxLevel(a_tpid);
    for(;((newLevel<maxLevel)&&(needFriendlyValue <= curFriendlyValue));){
        newLevel += 1;
        curFriendlyValue -= needFriendlyValue;
        needFriendlyValue = getUpgradeNeedFriendlyValue(a_tpid,newLevel);
    }
    a_leftFriendlyValue = curFriendlyValue;
    return newLevel;
}

BSLib::uint32 CPetConfigGMMgr::getFastFinishNeedDiamond(EHotSpringType a_hotSpringType) const
{
    switch(a_hotSpringType){
        case EFiveMiniteHotSpring: { return 5; }
        case EFourHoursHotSpring:  { return 30; }
        case EEightHoursHotSpring: { return 100; }
        default:{;} break;
    }
    return 0;
}

BSLib::uint32 CPetConfigGMMgr::getAddFriendlyValueByHotSpringType(EHotSpringType a_hotSpringType) const
{
    switch(a_hotSpringType){
        case EFiveMiniteHotSpring: { return 10;  }
        case EFourHoursHotSpring:  { return 100; }
        case EEightHoursHotSpring: { return 500; }
        default:                   { return 0;   }
    }
    return 0;
}

BSLib::uint32 CPetConfigGMMgr::getHotSpringMaxLevel() const
{
    return 5;
}

BSLib::uint32 CPetConfigGMMgr::getHotSpringSize(BSLib::uint32 a_level) const
{
    BSLib::uint32 size = a_level + 1;
    return size;
}

BSLib::uint32 CPetConfigGMMgr::getExpandHotSpringNeedDiamond(BSLib::uint32 a_level) const
{
    BSLib::uint32 needDiamond = a_level*a_level*100;
    return needDiamond;
}

BSLib::uint32 CPetConfigGMMgr::getHotSpringMaxSize() const
{
    BSLib::uint32 maxLevel = getHotSpringMaxLevel();
    return getHotSpringSize(maxLevel);
}

BSLib::uint32 CPetConfigGMMgr::randomHotSpringTaskTime() const
{
	//hot spring time
    BSLib::uint32 leftTime = BSLib::Utility::CRandom::randomBetween(30*60, 60*60);
    return leftTime;
}

CHotSpringTask* CPetConfigGMMgr::getHotSpringTask(BSLib::uint32 a_taskID) const
{
    CHotSpringTask* task = NULL;
    m_hotSpringTaskHashMap.getValue(a_taskID,task);
    return task;
}

CHotSpringTask* CPetConfigGMMgr::randomDailyPetTask(PetTPID a_petTPID,BSLib::uint32 a_fLevel,BSLib::uint32 a_friendlyValue,EHotSpringTaskType a_taskType) const
{
     CPetTPIDTask* petTPIDTask = _getDialyHotSpringTask(a_petTPID);
     if(petTPIDTask == NULL){
         return NULL;
     }
     std::vector<BSLib::uint32>& taskIDs = petTPIDTask->m_taskIDArray;
     std::vector<CHotSpringTask*> desTasks; 
     for(BSLib::uint32 i=0;i< taskIDs.size(); ++i){
         BSLib::uint32 taskID = taskIDs[i];
         CHotSpringTask*task = getHotSpringTask(taskID);
         if(task == NULL){
            continue; 
         }
         if(task->isInRange(a_fLevel,a_friendlyValue)){
             if(a_taskType != task->getHotSpringTaskSubType()){
                 continue;
             }
             desTasks.push_back(task);
         }
     }
     return _getRandomPetTask(desTasks);
}

CHotSpringTask* CPetConfigGMMgr::randomPetTask(PetTPID a_petTPID,BSLib::uint32 a_fLevel,BSLib::uint32 a_friendlyValue) const
{
    CPetTPIDTask* petTPIDTask = _getRandomHotSpringTask(a_petTPID);
    if(petTPIDTask == NULL){
        return NULL;
    }
    std::vector<BSLib::uint32>& taskIDs = petTPIDTask->m_taskIDArray;
    std::vector<CHotSpringTask*> desTasks; 
    for(BSLib::uint32 i=0;i< taskIDs.size(); ++i){
        BSLib::uint32 taskID = taskIDs[i];
        CHotSpringTask*task = getHotSpringTask(taskID);
        if(task == NULL){
            continue; 
        }
        if(task->isInRange(a_fLevel,a_friendlyValue)){
            desTasks.push_back(task);
        }
    }
    return _getRandomPetTask(desTasks);
}

CHotSpringTask* CPetConfigGMMgr::getMainPetTask(PetTPID a_petTPID,BSLib::uint32 a_fLevel,BSLib::uint32 a_friendlyValue,BSLib::uint32 a_lastTaskID) const
{
    CPetTPIDTask* petTPIDTask = _getMainHotSpringTask(a_petTPID);
    if(petTPIDTask == NULL){
        return NULL;
    }
    BSLib::uint32 taskID = 0;
    std::vector<BSLib::uint32>& taskIDs = petTPIDTask->m_taskIDArray;
    std::map<BSLib::uint32,CHotSpringTask*> desTasks; 
    for(BSLib::uint32 i=0;i< taskIDs.size(); ++i){
        BSLib::uint32 taskID = taskIDs[i];
        CHotSpringTask*task = getHotSpringTask(taskID);
        if(task == NULL){
            continue; 
        }
        if(task->isInRange(a_fLevel,a_friendlyValue)){
            desTasks.insert(std::make_pair(task->getTaskID(),task));
        }
    }
    return _getNextMainTask(desTasks,a_lastTaskID);
}

CPetTPIDTask* CPetConfigGMMgr::_getDialyHotSpringTask(PetTPID a_petTPID) const
{
    CPetTPIDTask* task = NULL;
    m_petDailyTaskHashMap.getValue(a_petTPID,task);
    return task;
}

CPetTPIDTask* CPetConfigGMMgr::_getMainHotSpringTask(PetTPID a_petTPID) const
{
    CPetTPIDTask* task = NULL;
    m_petMainTaskHashMap.getValue(a_petTPID,task);
    return task;
}

CPetTPIDTask* CPetConfigGMMgr::_getRandomHotSpringTask(PetTPID a_petTPID) const
{
    CPetTPIDTask* task = NULL;
    m_petRandomTaskHashMap.getValue(a_petTPID,task);
    return task;
}

void CPetConfigGMMgr::_removeHotSpringTaskConfig()
{
    BSLib::Utility::CHashMap<BSLib::uint32, CHotSpringTask*>::iterator it = m_hotSpringTaskHashMap.begin();
    for (; it != m_hotSpringTaskHashMap.end(); ++it) {
        CHotSpringTask* task = it->second;
        if (task == NULL) {
            continue;
        }
        BSLIB_SAFE_DELETE(task);
    }
    m_hotSpringTaskHashMap.clear();

    BSLib::Utility::CHashMap<PetTPID, CPetTPIDTask*>::iterator dailyTaskIt = m_petDailyTaskHashMap.begin();
    for (; dailyTaskIt!= m_petDailyTaskHashMap.end(); ++dailyTaskIt) {
        CPetTPIDTask* task = dailyTaskIt->second;
        if (task == NULL) {
            continue;
        }
        BSLIB_SAFE_DELETE(task);
    }
    m_petDailyTaskHashMap.clear();

    BSLib::Utility::CHashMap<PetTPID, CPetTPIDTask*>::iterator mainTaskIt = m_petMainTaskHashMap.begin();
    for (; mainTaskIt!= m_petMainTaskHashMap.end(); ++mainTaskIt) {
        CPetTPIDTask* task = mainTaskIt->second;
        if (task == NULL) {
            continue;
        }
        BSLIB_SAFE_DELETE(task);
    }
    m_petMainTaskHashMap.clear();

    BSLib::Utility::CHashMap<PetTPID, CPetTPIDTask*>::iterator ramdomTaskIt = m_petRandomTaskHashMap.begin();
    for (; ramdomTaskIt!= m_petRandomTaskHashMap.end(); ++ramdomTaskIt) {
        CPetTPIDTask* task = ramdomTaskIt->second;
        if (task == NULL) {
            continue;
        }
        BSLIB_SAFE_DELETE(task);
    }
    m_petRandomTaskHashMap.clear();

}


CHotSpringTask* CPetConfigGMMgr::_getRandomPetTask(std::vector<CHotSpringTask*>& a_tasks) const
{
    std::vector<BSLib::uint32> maxWeightArrays;
    std::vector<CHotSpringTask*> tasks;
    BSLib::uint32 weight = 0;
    for(BSLib::uint32 i=0;i< a_tasks.size(); ++i){
        CHotSpringTask*task = a_tasks[i];
        if(task == NULL){
            continue; 
        }
        weight += task->getWeight();
        maxWeightArrays.push_back(weight);
        tasks.push_back(task);
    }

    BSLib::uint32 Q = BSLib::Utility::CRandom::randomBetween(0,weight);
    BSLIB_LOG_DEBUG(ETT_GSLIB_PETSYSTEM, "[Q=%d]",Q);
    BSLib::uint32 area = 0;
    BSLib::uint32 findIndex = 0;
    for(findIndex=0;findIndex<maxWeightArrays.size(); ++findIndex){
        if(Q < maxWeightArrays[findIndex]){
            area = findIndex;
            break;
        }
    }
    if(findIndex == tasks.size()){
        return NULL;
    }
    CHotSpringTask* desTask = tasks[area]; 

    return desTask;
}


CHotSpringTask* CPetConfigGMMgr::_getNextMainTask(std::map<BSLib::uint32,CHotSpringTask*>& a_tasks,BSLib::uint32 a_lastTaskID) const
{
    if(a_lastTaskID == 0){
        if(a_tasks.size() == 0){
            return NULL;
        }
        std::map<BSLib::uint32,CHotSpringTask*>::const_iterator it = a_tasks.begin();
        for(;it != a_tasks.end();++it){
            CHotSpringTask* task = it->second;
            return task;
        }
    }
    std::map<BSLib::uint32,CHotSpringTask*>::const_iterator it = a_tasks.find(a_lastTaskID);
    for(;it != a_tasks.end();++it){
        if(it->first == a_lastTaskID){
            continue;
        }
        CHotSpringTask* task = it->second;
        return task;
    }
    return NULL;
}

BSLib::uint64 CPetConfigGMMgr::_makeUInt64Key(BSLib::uint32 a_left,BSLib::uint32 a_right) const
{
	BSLib::uint64 left = (((BSLib::uint64)a_right) << (32)) & 0XFFFFFFFF00000000;
	BSLib::uint64 right = ((BSLib::uint64)a_left) & 0X00000000FFFFFFFF;
	BSLib::uint64 key = (left)|(right);
	return key;
}

bool CPetConfigGMMgr::_loadHotSpringTaskConfig(const std::string& a_configPath)
{
    BSLib::Utility::CStringA configPath = a_configPath;
    configPath += "\\pet\\";

    std::string fileName = configPath + "t_hotspring_task_config.xml";
    BSLib::Utility::CDirInfo::standardization(fileName);

    BSLib::Utility::CStringA path(fileName);

    BSLib::Utility::CTableSheet tableSheet;
    if (!tableSheet.loadXmlFile(path)) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "[LOADCONFIG_ERROR]loadXmlFile[%s]", path.c_str());
        return false;
    }
    try {
        BSLIB_LOG_DEBUG(ETT_GSLIB_PETSYSTEM, "加载僚姬数据配置[%s]", path.c_str());
        BSLib::Utility::CTable& table = tableSheet["item"];
        for (BSLib::uint32 i=0; i < table.getRowCount(); ++i) {
            CHotSpringTask * task = new CHotSpringTask();
            if(task == NULL){
                BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "[LOADCONFIG_ERROR][CHotSpringTask == NULL]");
                return false;
            }
            if(!task->loadData(table[i])){
                BSLIB_SAFE_DELETE(task);
                return false;
            }

            if ((task->getType() == EHotSpringTaskNormal) &&(task->getHotSpringTaskSubType() != EHotSpringTaskTypeTalk)){
                BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "[无效的日常任务配置][taskID=%d]",task->getTaskID());
                continue;
            }
            if(!_addHotSpringTask(task)){
                BSLIB_SAFE_DELETE(task);
                return false;
            }
        }
        if(table.getRowCount() != m_hotSpringTaskHashMap.size()){
            BSLIB_LOG_ERROR(ETT_GSLIB_ITEMSYSTEM, "配置错误,未加载完全[RowCount=%d][size=%d][%s]",table.getRowCount(),m_hotSpringTaskHashMap.size(), path.c_str());
            return false;
        }
    } catch (...){
        BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "[LOADCONFIG_ERROR][Exception][%s]", path.c_str());
        return false;
    }

    return true;
}

bool CPetConfigGMMgr::_addHotSpringTask(CHotSpringTask* a_task)
{
    CHotSpringTask *task = a_task;
    if(task == NULL){
        return false;
    }
    BSLib::uint32 taskID = task->getTaskID();
    BSLib::Utility::CHashMap<BSLib::uint32, CHotSpringTask*>::iterator it= m_hotSpringTaskHashMap.find(taskID);
    if(it != m_hotSpringTaskHashMap.end()){
        BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "[LOADCONFIG_ERROR][重复配置][taskID=%d]",task->getTaskID());
        return false;
    }
    m_hotSpringTaskHashMap.setValue(taskID,task);
    EHotSpringTaskStatus type = task->getType();
    switch(type){
        case EHotSpringInvalidTask:
            {
            }
            break;
        case EHotSpringTaskNormal:
            {
                BSLib::uint32 petTPID = task->getPetTPID();
                CPetTPIDTask *item =_getDialyHotSpringTask(petTPID);        
                if(item == NULL){
                    CPetTPIDTask *newTask = new CPetTPIDTask();
                    newTask->addTask(taskID);
                    m_petDailyTaskHashMap.setValue(petTPID,newTask);
                    return true;
                }
                item->addTask(taskID);
            }
            break;
        case EHotSpringMainTask:
            {
                BSLib::uint32 petTPID = task->getPetTPID();
                CPetTPIDTask *item =_getMainHotSpringTask(petTPID);        
                if(item == NULL){
                    CPetTPIDTask *newTask = new CPetTPIDTask();
                    newTask->addTask(taskID);
                    m_petMainTaskHashMap.setValue(petTPID,newTask);
                    return true;
                }
                item->addTask(taskID);
            }
            break;
        case EHotSpringRandomTask:
            {
                BSLib::uint32 petTPID = task->getPetTPID();
                CPetTPIDTask *item =_getRandomHotSpringTask(petTPID);        
                if(item == NULL){
                    CPetTPIDTask *newTask = new CPetTPIDTask();
                    newTask->addTask(taskID);
                    m_petRandomTaskHashMap.setValue(petTPID,newTask);
                    return true;
                }
                item->addTask(taskID);
            }
        default:{ ; } break;
    }
    return true;
}

}//GM

}//PetSystem

}//GSLib
