#ifndef __GSLIB_PETSYSTEM_GM_FINISHHOTSPRINGTASKDATA_H__
#define __GSLIB_PETSYSTEM_GM_FINISHHOTSPRINGTASKDATA_H__

#include <GFLib/commonServer/commonSystem.h>
#include "GSLib//petSystem/baseDef.h"
#include <GSLib/petSystem/GM/sendItem.h>
namespace GSLib
{

namespace PetSystem
{

namespace GM
{
class CFinishPetTaskData
{
public:
    CFinishPetTaskData();
    ~CFinishPetTaskData();

    PetID getPetID() const;
    BSLib::uint32 getAnswerID() const;
    const CSendItem& getSendItem() const{return m_sendItem;}
    bool serializeFrom(BSLib::Utility::CStream& stream);
    bool serializeTo(BSLib::Utility::CStream& stream) const;

private:
    BSLib::uint32 m_petID;
    BSLib::uint32 m_answerID;
    CSendItem m_sendItem;
};

class CFinishBossTaskData
{
public:
    CFinishBossTaskData();
    ~CFinishBossTaskData();

    BSLib::uint32 getID() const;
    BSLib::uint32 getAnswerID() const;
    const CSendItem& getSendItem() const;
    bool serializeFrom(BSLib::Utility::CStream& stream);
    bool serializeTo(BSLib::Utility::CStream& stream) const;

private:
    BSLib::uint32 m_taskID;
    BSLib::uint32 m_answerID;
    CSendItem m_sendItem;
};

}//GM

}//PetSystem

}//GSLib
#endif// __GSLIB_PETSYSTEM_GM_FINISHHOTSPRINGTASKDATA_H__

