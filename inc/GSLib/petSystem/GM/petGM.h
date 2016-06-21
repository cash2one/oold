#ifndef __GSLIB_PETSYSTEM_GM_PETGM_H__
#define __GSLIB_PETSYSTEM_GM_PETGM_H__

#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/petSystem/baseDef.h>
#include <GSLib/petSystem/DB/tablePetDB.h>
#include <GSLib/petSystem/GM/hotSpringTask.h>
namespace GSLib
{

namespace PetSystem
{

namespace GM
{

class CPetModule;

class CPetGM
{
public:
	CPetGM(DB::CPetDBData& a_petData,CPetModule* a_petModule);
	~CPetGM();

public:
	void init(bool a_first = false);
    void final();
public:
    bool addFriendlyValue(BSLib::uint32 a_friendly);
    bool addPassTime(BSLib::uint32 a_passTime);
    bool cleanHotSpringTaskPassTime();

public:
    bool finishPetTask(BSLib::uint32 a_answerID);
    bool endPetTask(EPetHotSprintEnd a_endStatus,BSLib::Utility::CStream& a_stream);
    bool getPetTaskDetail(EHotSpringTaskType a_type,BSLib::Utility::CStream& a_stream);

    void finishCurMainTask();
    CHotSpringTask* activePetTask();
    CHotSpringTask* randomDailyPetTask() const;
    CHotSpringTask* getCurMainTask() const;
    CHotSpringTask* getCurRandomTask() const;
    CHotSpringTask* getRandomTask() const;

public:
    bool sitDown();
    bool standUp();
    bool enterPool(EHotSpringType a_hotSpringType);
    bool quitPool(bool bFast);
public:
    bool serializeToClient(BSLib::Utility::CStream& stream) const;
    bool getBaseInfor(BSLib::Utility::CStream& stream) const;
    const DB::CPetDBData& getPetDBData() const;

public:
	PetTPID getTPID() const;
	PetID getPetID() const;

	EPetStatus getStatus() const;
    EHotSpringTaskStatus getHotSprintTaskStatus() const;
    EHotSpringType getHotSpringType() const;
    BSLib::uint32 getFriendlyLevel() const;
    BSLib::uint32 getFriendlyValue() const;
    BSLib::uint32 getCurTaskID() const;
    BSLib::uint32 getLastMainTaskID() const;

    BSLib::uint32 getBattleAttr(EAttrID a_attrID) const;
    bool getBattleAttr(SBattleAttribute& a_petBattleAttre) const;

    BSLib::uint32 getLeftTime() const;

    BSLib::uint32 getAddPassTime() const;
    BSLib::uint32 getHotSpringTaskMaxTime() const;
    BSLib::uint32 getHotSpringTaskPassTime() const;
    BSLib::uint32 getFastFinishNeedDiamond() const;

public:
    void setPetID(PetID a_petID);
    void setStatus(EPetStatus a_petStatus);
    void setCurTaskID(BSLib::uint32 a_taskID);
    void setLastMainTaskID(BSLib::uint32 a_curMainTaskID);
    void setHotSpringTaskStatus(EHotSpringTaskStatus a_hotSpringTaskStatus);
    void setHotSpringTaskType(EHotSpringTaskType a_hotSpringTaskType);
    void setHotSpringTaskMaxTime(BSLib::uint32 a_hotSpringTaskMaxTime);
    void setHotSpringType(EHotSpringType a_hotSpringType);
    
    
	void setBattleAttribute(EAttrID a_attrID,BSLib::uint32 value);

    void updateBattleAttr(bool a_notify);
    void updateFriendlyLevel();

private:
    DB::CPetDBData m_petData;
    SBattleAttribute m_petTotalBattleAttr;
    CPetModule* m_petModule;
};

}//GM

}//PetSystem

}//GSLib

#endif//__GSLIB_PETSYSTEM_GM_PETGM_H__

