#include "GSLib/petSystem/GM/finishPetTaskData.h"
#include <GSLib/tracer.h>

namespace GSLib
{

namespace PetSystem
{	

namespace GM
{

CFinishPetTaskData::CFinishPetTaskData()
{
    m_petID = 0;
    m_answerID = 0;
}

CFinishPetTaskData::~CFinishPetTaskData()
{
}


PetID CFinishPetTaskData::getPetID() const
{
    return m_petID;
}

BSLib::uint32 CFinishPetTaskData::getAnswerID() const
{
    return m_answerID;
}
bool CFinishPetTaskData::serializeFrom(BSLib::Utility::CStream& stream)
{
    stream >> m_petID;
    stream >> m_answerID;
    m_sendItem.serializeFrom(stream);
    return true;
}

bool CFinishPetTaskData::serializeTo(BSLib::Utility::CStream& stream) const
{
    stream << m_petID;
    stream << m_answerID;
    m_sendItem.serializeTo(stream);
    return true;
}


CFinishBossTaskData::CFinishBossTaskData()
{
    m_taskID = 0;
    m_answerID = 0;
}

CFinishBossTaskData::~CFinishBossTaskData()
{
}

BSLib::uint32 CFinishBossTaskData::getID() const
{
    return m_taskID;
}

BSLib::uint32 CFinishBossTaskData::getAnswerID() const
{
    return m_answerID;
}

const CSendItem& CFinishBossTaskData::getSendItem() const
{
    return m_sendItem;
}

bool CFinishBossTaskData::serializeFrom(BSLib::Utility::CStream& stream)
{
    stream >> m_taskID;
    stream >> m_answerID;
    m_sendItem.serializeFrom(stream);
    return true;
}

bool CFinishBossTaskData::serializeTo(BSLib::Utility::CStream& stream) const
{
    stream << m_taskID;
    stream << m_answerID;
    m_sendItem.serializeTo(stream);
    return true;
}

}//GM

}//PlayerSystem

}//GSLib

