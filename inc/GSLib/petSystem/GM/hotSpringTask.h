//////////////////////////////////////////////////////////////////////
//	created:	2015/03/05
//	filename: 	GSLib\petSystem\GM\hotSpring.h
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PETSYSTEM_GM_HOTSPRINGTASK_H__
#define __GSLIB_PETSYSTEM_GM_HOTSPRINGTASK_H__

#include <GFLib/commonServer/commonSystem.h>
#include <BSLib/utility/table.h>
#include "GSLib/petSystem/baseDef.h"
#include <GSLib/petSystem/GM/talkAnswer.h>
#include <GSLib/petSystem/GM/talkQuestion.h>
namespace GSLib
{

namespace PetSystem
{

namespace GM
{

class CHotSpringTask
{
public:
    CHotSpringTask();
    ~CHotSpringTask();
public:
    bool isInRange(BSLib::uint32 a_curLevel,BSLib::uint32 a_curFriendlyValue) const;
    BSLib::uint32 getTaskID() const;
    PetTPID getPetTPID() const;
    EHotSpringTaskStatus getType() const;
    EHotSpringTaskType getHotSpringTaskSubType() const;
    BSLib::uint32 getMinFriendlyLevel() const;
    BSLib::uint32 getMinFriendlyValue() const;

    BSLib::uint32 getAnswerFriendlyValue(BSLib::uint32 a_answerID) const;
    BSLib::uint32 getEndFriendlyValue(BSLib::uint32 a_endID) const;

    BSLib::uint32 getItemTPID() const;
    BSLib::uint32 getWeight() const;

    void setPetTPID(PetTPID a_petTPID){m_petTPID = a_petTPID;}
    void setTaskType(EHotSpringTaskType a_taskType){m_taskType = a_taskType;}
    void setItemID(BSLib::uint32 a_itemID){m_itemID = a_itemID;}
    void setFriendlyA(BSLib::uint32 a_friendlyA){m_friendlyA = a_friendlyA;}
    void setFriendlyB(BSLib::uint32 a_friendlyB){m_friendlyB = a_friendlyB;}


    bool SerializeFrom(BSLib::Utility::CStream& stream);
    bool SerializeTo(BSLib::Utility::CStream& stream) const;
    bool getTaskEndData(BSLib::uint32 a_answerID,BSLib::Utility::CStream& stream) const;
    bool loadData(BSLib::Utility::CTableRow& a_tableRow);

    bool init(PetTPID a_petTPID,BSLib::uint32 a_itemID,EHotSpringTaskType a_taskType,const std::string&a_question, const std::string& a_answer,ETaskUser a_taskUser);
private:
    bool _init(const std::string&a_question, const std::string& a_answer, const std::string& a_end);
private:
    BSLib::uint32 m_taskID;
    BSLib::uint32 m_petTPID;
    EHotSpringTaskType m_taskType;
    EHotSpringTaskStatus m_type;
    BSLib::uint32 m_minFriendlyLevel;
    BSLib::uint32 m_maxFriendlyLevel;
    BSLib::uint32 m_minFriendlyValue;
    BSLib::uint32 m_maxFriendlyValue;
    BSLib::uint32 m_friendlyA;
    BSLib::uint32 m_friendlyB;
    BSLib::uint32 m_itemID;
    BSLib::uint32 m_weight;
    CTalkQuestion m_talkQuestion;
    std::vector<CTalkAnswer> m_answerArray;
    std::vector<CTalkAnswer> m_endArray;
};

}//GM

}//PetSystem

}//GSLib
#endif// __GSLIB_PETSYSTEM_GM_HOTSPRINGTASK_H__
