//////////////////////////////////////////////////////////////////////
//	created:	2014/09/26
//	filename: 	src\GSLib\skillSystem\DB\tableSkillDB.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/achieveSystem/DB/tableAchieveDB.h>
#include <GSLib/tracer.h>

namespace GSLib
{

namespace AchieveSystem 
{

namespace DB
{

bool CAchieveData::serializeTo(BSLib::Utility::CStream& stream) const 
{
    stream << m_accountID;
    stream << m_zoneID;
    stream << m_roleIndex;
    BSLib::uint32 buffSize = m_achieveList.size() * sizeof(SAchieveItem);
    stream << buffSize; 
    for (BSLib::uint32 i=0; i<m_achieveList.size(); ++i) {
        m_achieveList[i].serializeTo(stream);
    }
    return true;
}

bool CAchieveData::serializeFrom(BSLib::Utility::CStream& stream) 
{
    stream >> m_accountID;
    stream >> m_zoneID;
    stream >> m_roleIndex;
    BSLib::uint32 buffSize = 0;
    stream >> buffSize;
    if (buffSize <= 0) {
        return true;
    }
    if (buffSize > stream.readSize()) {
        return false;
    }
    BSLib::uint32 count = buffSize / sizeof(SAchieveItem);
    for (BSLib::uint32 i=0; i<count; ++i) {
        SAchieveItem item;
        item.serializeFrom(stream);
        m_achieveList.push_back(item);
    }
    return true;
}

}//DB

}//SkillSystem

}//GSLib