//////////////////////////////////////////////////////////////////////
//	created:	2014/09/26
//	filename: 	src\GSLib\petSystem\DB\tablePetDB.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/petSystem/DB/tablePetDB.h>
#include <GSLib/tracer.h>
#include <GSLib/petSystem/baseDef.h>
namespace GSLib
{

namespace PetSystem
{

namespace DB
{

CPetDBData::CPetDBData()
{
    m_petID = 0;
    m_petTPID = 0;
    m_friendlyLevel = 1;
    m_friendlyValue = 0;
    m_maxFriendlyValue = 0;
    m_petStatus = 0;
    m_hotSpringTaskMaxTime = 0;
    m_hotSpringTaskPassTime = 0;
    m_lastMainTaskID = 0;
    m_curTaskID = 0;
    m_hotSpringType = 0;
    m_hotSpringTaskStatus = 0;
    m_hotSpringTaskType = 0;
    m_lastEnterTime = 0;
    m_lastQuitGameTime = 0;
}

CPetDBData::~CPetDBData()
{
}

bool CPetDBData::serializeTo(BSLib::Utility::CStream& stream) const
{
    stream << m_petID;
    stream << m_petTPID;
    stream << m_friendlyLevel;
    stream << m_friendlyValue;
    stream << m_maxFriendlyValue;
    stream << m_petStatus;
    stream << m_hotSpringTaskMaxTime;
    stream << m_hotSpringTaskPassTime;
    stream << m_lastMainTaskID;
    stream << m_curTaskID;
    stream << m_hotSpringType;
    stream << m_hotSpringTaskStatus;
    stream << m_hotSpringTaskType;
    stream << m_lastEnterTime;
    stream << m_lastQuitGameTime;
    m_battleAttr.serializeTo(stream);

    return true;
}

bool CPetDBData::serializeFrom(BSLib::Utility::CStream& stream)
{
    stream >> m_petID;
    stream >> m_petTPID;
    stream >> m_friendlyLevel;
    stream >> m_friendlyValue;
    stream >> m_maxFriendlyValue;
    stream >> m_petStatus;
    stream >> m_hotSpringTaskMaxTime;
    stream >> m_hotSpringTaskPassTime;
    stream >> m_lastMainTaskID;
    stream >> m_curTaskID;
    stream >> m_hotSpringType;
    stream >> m_hotSpringTaskStatus;
    stream >> m_hotSpringTaskType;
    stream >> m_lastEnterTime;
    stream >> m_lastQuitGameTime;
    m_battleAttr.serializeFrom(stream);

    return true;
}

CRolePetData::CRolePetData()
{
   m_hotSpringLevel = 0;
}

CRolePetData::~CRolePetData()
{

}

bool CRolePetData::_serializeTo(BSLib::Utility::CStream& stream) const 
{
    stream << m_hotSpringLevel;
    BSLib::uint32 buffSize = m_petList.size() * sizeof(CPetDBData);
    stream << buffSize; 
    for (BSLib::uint32 i=0; i<m_petList.size(); ++i) {
        m_petList[i].serializeTo(stream);
    }
	return true;
}

bool CRolePetData::_serializeFrom(BSLib::Utility::CStream& stream) 
{
    stream >> m_hotSpringLevel;
    BSLib::uint32 buffSize = 0;
    stream >> buffSize;
    if (buffSize <= 0) {
        return true;
    }
    if (buffSize > stream.readSize()) {
        return false;
    }
    BSLib::uint32 petCount = buffSize / sizeof(CPetDBData);
    for (BSLib::uint32 i=0; i<petCount; ++i) {
        CPetDBData pet;
        pet.serializeFrom(stream);
        m_petList.push_back(pet);
    }

    return true;
}

}//DB

}//PetSystem

}//GSLib
