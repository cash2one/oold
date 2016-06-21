#include <GSLib/tracer.h>
#include <GSLib/petSystem/GM/petGM.h>
#include "petConfigGMMgr.h"
#include <GSLib/petSystem/GM/petModule.h>
#include <GSLib/itemSystem/GM/itemGMMgr.h>

namespace GSLib
{

namespace PetSystem
{	

namespace GM
{

CPetGM::CPetGM(DB::CPetDBData& a_petData,CPetModule* a_petModule)
:m_petData(a_petData)
,m_petModule(a_petModule)
{
}

CPetGM::~CPetGM()
{
}

bool CPetGM::addFriendlyValue(BSLib::uint32 a_friendly)
{
    m_petData.m_friendlyValue += a_friendly;
    updateFriendlyLevel();
    return true;
}

bool CPetGM::addPassTime(BSLib::uint32 a_passTime)
{
    const BSLib::uint32 maxTime = getHotSpringTaskMaxTime();
    if(maxTime > m_petData.m_hotSpringTaskPassTime){
       m_petData.m_hotSpringTaskPassTime += a_passTime;
       return true; 
    } 
    else if(maxTime == m_petData.m_hotSpringTaskPassTime){
       m_petData.m_hotSpringTaskPassTime += a_passTime;
       if(m_petModule == NULL){
           return false;
       }
       return m_petModule->sendMsgToClientToActivePetTask(getPetID());
    }
    else if(maxTime < m_petData.m_hotSpringTaskPassTime){
        if(getHotSprintTaskStatus() == EHotSpringTaskNormal){
            BSLib::uint32 leftTime = CPetConfigGMMgr::singleton().randomHotSpringTaskTime();
            setHotSpringTaskMaxTime(leftTime);
            cleanHotSpringTaskPassTime();
        }
    }
    return true;
}

bool CPetGM::cleanHotSpringTaskPassTime()
{
    m_petData.m_hotSpringTaskPassTime = 0;
    return true;
}

bool CPetGM::finishPetTask(BSLib::uint32 a_answerID)
{
    BSLib::uint32 taskID =getCurTaskID();
    CHotSpringTask* task = CPetConfigGMMgr::singleton().getHotSpringTask(taskID); 
    if(task == NULL){
        return false;
    }
    BSLib::uint32 friendlyValue = task->getAnswerFriendlyValue(a_answerID);
    addFriendlyValue(friendlyValue);

    EHotSpringTaskType type = task->getHotSpringTaskSubType();
    if(type != EHotSpringTaskTypePublishTask){
        if(task->getType() == EHotSpringMainTask){
            setLastMainTaskID(taskID);
        }
        setHotSpringTaskStatus(EHotSpringTaskNormal);
        setHotSpringTaskType(EHotSpringTaskTypeInvalid);
        setCurTaskID(0);
    }
    else if(a_answerID == 1){
        setHotSpringTaskStatus(EHotSpringTaskNormal);
        setHotSpringTaskType(EHotSpringTaskTypeInvalid);
        setCurTaskID(0);
    }
    return true;
}

bool CPetGM::endPetTask(EPetHotSprintEnd a_endStatus,BSLib::Utility::CStream& a_stream)
{
    BSLib::uint32 taskID = getCurTaskID();
    CHotSpringTask* task = CPetConfigGMMgr::singleton().getHotSpringTask(taskID); 
    if(task == NULL){
        return false;
    }
    EHotSpringTaskType type = task->getHotSpringTaskSubType();
    if(type != EHotSpringTaskTypePublishTask){
        return false;
    }
    BSLib::uint32 endID = 0;
    if(a_endStatus == EPetHotSprintEndWin){
        endID = 0;
    }
    else{
        endID = 1;
    }
    BSLib::uint32 friendlyValue = task->getEndFriendlyValue(endID);
    addFriendlyValue(friendlyValue);
    if(!task->getTaskEndData(endID,a_stream)){
        return false;
    }
    if(task->getType() == EHotSpringMainTask){
        setLastMainTaskID(taskID);
    }
    setCurTaskID(0);
    setHotSpringTaskStatus(EHotSpringTaskNormal);
    setHotSpringTaskType(EHotSpringTaskTypeInvalid);

    if(getHotSprintTaskStatus() != EHotSpringTaskNormal){
        BSLib::uint32 leftTime = CPetConfigGMMgr::singleton().randomHotSpringTaskTime();
        setHotSpringTaskMaxTime(leftTime);
        cleanHotSpringTaskPassTime();
    }
    return true;
}

bool CPetGM::getPetTaskDetail(EHotSpringTaskType a_type,BSLib::Utility::CStream& a_stream)
{
    EHotSpringTaskStatus status = getHotSprintTaskStatus();
    CHotSpringTask* task = NULL;
    switch(status){
        case EHotSpringTaskNormal: { task = randomDailyPetTask(); } break;
        case EHotSpringMainTask:   { task = getCurMainTask();     } break;
        case EHotSpringRandomTask: { task = getCurRandomTask();   } break;
        default: { ; }
    }
    if( task == NULL){
        return false;
    }
    if(task != NULL){
        BSLib::uint32 taskID = task->getTaskID();
        setCurTaskID(taskID);
    }

    task->SerializeTo(a_stream);
    return true;
}

void CPetGM::finishCurMainTask()
{
    const CHotSpringTask* task = getCurMainTask();
    if(task != NULL){
        setLastMainTaskID(task->getTaskID());
    }
}

CHotSpringTask* CPetGM::activePetTask()
{
    CHotSpringTask* task = getCurMainTask();
    if(task == NULL){
        task = getRandomTask();
    }
    if(task != NULL){
        EHotSpringTaskType subType = task->getHotSpringTaskSubType();
        EHotSpringTaskStatus status = task->getType();
        setHotSpringTaskType(subType);
        setHotSpringTaskStatus(status); 
		setCurTaskID(task->getTaskID());
    }
    return task;
}

CHotSpringTask* CPetGM::randomDailyPetTask() const
{
    EHotSpringTaskType type = EHotSpringTaskTypeTalk;
    return CPetConfigGMMgr::singleton().randomDailyPetTask(getTPID(),getFriendlyLevel(),getFriendlyValue(),type);
}

CHotSpringTask* CPetGM::getCurMainTask() const
{
    return CPetConfigGMMgr::singleton().getMainPetTask(getTPID(),getFriendlyLevel(),getFriendlyValue(),getLastMainTaskID());
}

CHotSpringTask* CPetGM::getCurRandomTask() const
{
    BSLib::uint32 taskID = getCurTaskID();
    CHotSpringTask* task = CPetConfigGMMgr::singleton().getHotSpringTask(taskID);
    if ((task != NULL) && (EHotSpringTaskNormal == task->getType())){
        task = getRandomTask();
    }
    return task;
}

CHotSpringTask* CPetGM::getRandomTask() const
{
    return CPetConfigGMMgr::singleton().randomPetTask(getTPID(),getFriendlyLevel(),getFriendlyValue());
}

bool CPetGM::sitDown()
{
    setStatus(EPetStatusSit);
    setHotSpringTaskStatus(EHotSpringTaskNormal);
    setHotSpringTaskType(EHotSpringTaskTypeInvalid);
    return true;
}

bool CPetGM::standUp()
{
    setStatus(EPetStatusFree);
    setHotSpringTaskStatus(EHotSpringInvalidTask);
    setHotSpringTaskType(EHotSpringTaskTypeInvalid);
    return true;
}

bool CPetGM::enterPool(EHotSpringType a_hotSpringType)
{
    setStatus(EPetStatusInSpring);
    setHotSpringTaskStatus(EHotSpringTaskNormal);
    setHotSpringTaskType(EHotSpringTaskTypeInvalid);
    BSLib::uint32 leftTime = CPetConfigGMMgr::singleton().randomHotSpringTaskTime();
    setHotSpringTaskMaxTime(leftTime);
    cleanHotSpringTaskPassTime();
    setHotSpringType(a_hotSpringType);
    return true;
}

bool CPetGM::quitPool(bool bFast)
{
    setStatus(EPetStatusFree);
    setHotSpringTaskStatus(EHotSpringInvalidTask);
    setHotSpringTaskType(EHotSpringTaskTypeInvalid);
    setHotSpringType(EInvalidHotSpring);
    EHotSpringType type = (EHotSpringType)getHotSpringType();
    BSLib::uint32 addFriendly = CPetConfigGMMgr::singleton().getAddFriendlyValueByHotSpringType(type);
    addFriendlyValue(addFriendly);
    return true;
}

const DB::CPetDBData& CPetGM::getPetDBData() const
{
    return m_petData;
}

PetTPID CPetGM::getTPID() const
{
    return m_petData.m_petTPID;
}

PetID CPetGM::getPetID() const 
{ 
    return m_petData.m_petID;
}

EPetStatus CPetGM::getStatus() const 
{ 
    return (EPetStatus)m_petData.m_petStatus; 
}

EHotSpringTaskStatus CPetGM::getHotSprintTaskStatus() const
{
    return (EHotSpringTaskStatus)m_petData.m_hotSpringTaskStatus; 
}

EHotSpringType CPetGM::getHotSpringType() const
{
    return (EHotSpringType)m_petData.m_hotSpringType; 
}

BSLib::uint32 CPetGM::getFriendlyLevel() const 
{
    return m_petData.m_friendlyLevel; 
}

BSLib::uint32 CPetGM::getFriendlyValue() const 
{ 
    return m_petData.m_friendlyValue;
}

BSLib::uint32 CPetGM::getCurTaskID() const
{
    return m_petData.m_curTaskID;
}

BSLib::uint32 CPetGM::getLastMainTaskID() const
{
    return m_petData.m_lastMainTaskID;
}

BSLib::uint32 CPetGM::getBattleAttr(EAttrID a_attrID) const
{
    return m_petTotalBattleAttr.getValue(a_attrID);
}

bool CPetGM::getBattleAttr(SBattleAttribute& a_petBattleAttribute) const
{
    memcpy(&a_petBattleAttribute, (void*)&m_petTotalBattleAttr, sizeof(m_petTotalBattleAttr));
    return true;
}

BSLib::uint32 CPetGM::getLeftTime() const
{
    BSLib::uint32 passTime = 0;
    if(m_petData.m_lastEnterTime != 0){
        BSLib::uint64 curTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
        passTime = (BSLib::uint32)(curTime - m_petData.m_lastEnterTime);
    }
    BSLib::uint32 leftTime = 0;
    BSLib::uint32 totalTime = 0;
    switch(m_petData.m_hotSpringType){
        case EFiveMiniteHotSpring: // 根据需求变更改成10分钟
            {
               totalTime = 10*60;
            }
            break;
        case EFourHoursHotSpring:
            {
               totalTime = 4*60*60;
            }
            break;
        case EEightHoursHotSpring:
            {
               totalTime = 8*60*60;
            }
            break;
        default:{;} break;
    }
    if(totalTime <= passTime){
        return 0;
    }
    leftTime = totalTime - passTime;
    return leftTime;
}

BSLib::uint32 CPetGM::getAddPassTime() const
{
    BSLib::uint32 passTime = 0;
    if(m_petData.m_lastQuitGameTime != 0){
        if(getStatus() == EPetStatusFree){
            return 0;
        }
        BSLib::uint64 curTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
        passTime = (BSLib::uint32)(curTime - m_petData.m_lastQuitGameTime);
    }
    return passTime;
}

BSLib::uint32 CPetGM::getHotSpringTaskMaxTime() const
{
    return m_petData.m_hotSpringTaskMaxTime;
}

BSLib::uint32 CPetGM::getHotSpringTaskPassTime() const
{
    return m_petData.m_hotSpringTaskPassTime;
}

BSLib::uint32 CPetGM::getFastFinishNeedDiamond() const
{
    EHotSpringType type = (EHotSpringType)m_petData.m_hotSpringType;
    return CPetConfigGMMgr::singleton().getFastFinishNeedDiamond(type);
}


void CPetGM::setStatus(EPetStatus a_petStatus)
{ 
    m_petData.m_petStatus = a_petStatus;
    m_petData.m_hotSpringTaskPassTime = 0;
    if(a_petStatus == EPetStatusInSpring){
        m_petData.m_lastEnterTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
    }
}

void CPetGM::setCurTaskID(BSLib::uint32 a_taskID)
{
    m_petData.m_curTaskID = a_taskID;
}

void CPetGM::setLastMainTaskID(BSLib::uint32 a_curMainTaskID)
{
    m_petData.m_lastMainTaskID = a_curMainTaskID;
}

void CPetGM::setHotSpringTaskStatus(EHotSpringTaskStatus a_hotSpringTaskStatus)
{
    m_petData.m_hotSpringTaskStatus = a_hotSpringTaskStatus;
}

void CPetGM::setHotSpringTaskType(EHotSpringTaskType a_hotSpringTaskType)
{
    m_petData.m_hotSpringTaskType = a_hotSpringTaskType;
}

void CPetGM::setHotSpringTaskMaxTime(BSLib::uint32 a_hotSpringTaskMaxTime)
{
    m_petData.m_hotSpringTaskMaxTime = a_hotSpringTaskMaxTime;
}

void CPetGM::setHotSpringType(EHotSpringType a_hotSpringType)
{
    m_petData.m_hotSpringType = (BSLib::uint32)a_hotSpringType;
}

void CPetGM::setBattleAttribute(EAttrID a_attrID,BSLib::uint32 a_value)
{
	m_petTotalBattleAttr.setValue(a_attrID,a_value);
}

void CPetGM::updateBattleAttr(bool a_notify)
{
    m_petTotalBattleAttr.cleanAttr();
    m_petTotalBattleAttr.addAttr(m_petData.m_battleAttr);
    BSLIB_LOG_DEBUG(ETT_GSLIB_PETSYSTEM, "updateBattleAttr伙伴属性值[petID=%d]%s",getPetID(),m_petTotalBattleAttr.toLogString().c_str());
    m_petModule->updatePetTotalBattleAttr(a_notify);
}

void CPetGM::updateFriendlyLevel()
{
    if(m_petData.m_friendlyValue < m_petData.m_maxFriendlyValue){
        return;
    }
    BSLib::uint32 curLevel = getFriendlyLevel();
    BSLib::uint32 curFriendlyValue = getFriendlyValue();
    BSLib::uint32 newFriendlyValue = curFriendlyValue;
    BSLib::uint32 newLevel = CPetConfigGMMgr::singleton().getPetLevel(getTPID(),curLevel,curFriendlyValue,newFriendlyValue);
    if(newLevel != curLevel){
        m_petData.m_friendlyLevel = newLevel;
        m_petData.m_friendlyValue = newFriendlyValue;
        m_petData.m_maxFriendlyValue = CPetConfigGMMgr::singleton().getUpgradeNeedFriendlyValue(getTPID(),getFriendlyLevel());
        CPetConfigGMMgr::singleton().getPetAttr(getTPID(),m_petData.m_friendlyLevel,m_petData.m_battleAttr);
        updateBattleAttr(true);
    }
}

void CPetGM::init(bool a_first)
{
    if(a_first){
        CPetConfigGMMgr::singleton().getPetAttr(getTPID(),m_petData.m_friendlyLevel,m_petData.m_battleAttr);
        m_petData.m_maxFriendlyValue = CPetConfigGMMgr::singleton().getUpgradeNeedFriendlyValue(getTPID(),getFriendlyLevel());
    }
    else{
        BSLib::uint32 passTime = m_petData.m_hotSpringTaskPassTime + getAddPassTime();
        if(passTime > m_petData.m_hotSpringTaskMaxTime){
            m_petData.m_hotSpringTaskPassTime = passTime;
            m_petModule->sendMsgToClientToActivePetTask(getTPID(),false);
        }
    }
	updateBattleAttr(false);
}

void CPetGM::final()
{

}

bool CPetGM::serializeToClient(BSLib::Utility::CStream& stream) const
{
    stream << m_petData.m_petID;
    stream << m_petData.m_petTPID;
    stream << m_petData.m_friendlyLevel;
    stream << m_petData.m_friendlyValue;
    stream << m_petData.m_maxFriendlyValue;
    stream << m_petData.m_petStatus;
    stream << m_petData.m_hotSpringType;
    stream << m_petData.m_hotSpringTaskStatus;
    stream << m_petData.m_hotSpringTaskType;
    stream << getLeftTime();
    m_petData.m_battleAttr.serializeTo(stream);
    SBattleAttribute upgradeAttr;
    if(!CPetConfigGMMgr::singleton().getUpgradeAttr(m_petData.m_petTPID,upgradeAttr)){
        return false;
    }
    upgradeAttr.serializeTo(stream);
    return true;
}

bool CPetGM::getBaseInfor(BSLib::Utility::CStream& stream) const
{
    stream << m_petData.m_petID;
    stream << m_petData.m_petTPID;
    stream << m_petData.m_petStatus;
    stream << getLeftTime();
    return true;
}

}//GM

}//PetSystem

}//GSLib

