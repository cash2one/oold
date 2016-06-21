#include "GSLib/petSystem/GM/talkQuestion.h"
#include <GSLib/tracer.h>

namespace GSLib
{

namespace PetSystem
{	

namespace GM
{

CTalkQuestion::CTalkQuestion()
{
}

CTalkQuestion::CTalkQuestion(std::string& question)
{
    init(question);
}

CTalkQuestion::~CTalkQuestion()
{
}

bool CTalkQuestion::SerializeFrom(BSLib::Utility::CStream& stream)
{
    return true;
}

bool CTalkQuestion::SerializeTo(BSLib::Utility::CStream& stream) const
{
    BSLib::uint32 count = (BSLib::uint32)m_questionArray.size();
    stream << count;
    for(BSLib::uint32 i=0; i<count; ++i){
        CTalkItem item = m_questionArray[i];
        item.SerializeTo(stream);
    }
    return true;
}

bool CTalkQuestion::addTalkItem(CTalkItem& a_item)
{
    m_questionArray.push_back(a_item);
    return true;
}

bool CTalkQuestion::init(const std::string& a_question)
{
    BSLib::Utility::CStringA strQuestion(a_question);
    std::vector<std::string> vecStr;
    std::string separator(";");
    strQuestion.split(vecStr, separator);
    m_itemArray.clear();
    for(BSLib::uint32 i=0;i<vecStr.size();++i){
        std::string subQuestion = vecStr[i];
        CTalkItem item(subQuestion);
        addTalkItem(item);
    }
    return true;
}
BSLib::uint32 CTalkQuestion::getFriendlyValue()const 
{
    BSLib::uint32 data = 0;
    for(BSLib::uint32 i=0;i<m_questionArray.size();++i){
        CTalkItem item = m_questionArray[i];
        data += item.getFriendlyValue();
    }
    return data;
}

const std::vector<ItemSystem::GM::CPrizeItem>& CTalkQuestion::getItemArray() const
{ 
    return m_itemArray;
}
}//GM

}//PlayerSystem

}//GSLib

