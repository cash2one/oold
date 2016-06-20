//////////////////////////////////////////////////////////////////////
//	created:	2014/07/27
//	filename: 	src\GSLib\petSystem\GM\petData.cpp
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/tracer.h>
#include <GSLib/petSystem/GM/petData.h>

namespace GSLib
{

namespace PetSystem
{	

namespace GM
{

CPetData::CPetData()
{
    memset(&m_petData,0,sizeof(DB::CPetDBData));
    m_skillList.clear();
}

CPetData::~CPetData()
{
    m_skillList.clear();
}

bool CPetData::serializeTo(BSLib::Utility::CStream& stream) const
{
    m_petData.serializeTo(stream);
    BSLib::uint32 m_skillCount = m_skillList.size();
    stream << m_skillCount;
    std::list<SPetSkillItem*>::const_iterator it = m_skillList.begin();
    for (it = m_skillList.begin(); it != m_skillList.end(); ++it){
        SPetSkillItem* skill = *it;
        if(skill == NULL) return false;
        stream << skill->m_skillID;
        stream << skill->m_skillLevel;
    }

    return true;
}

}//GM

}//PetSystem

}//GSLib
