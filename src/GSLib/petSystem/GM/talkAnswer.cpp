//////////////////////////////////////////////////////////////////////
//	created:	2014/07/29
//	filename: 	src\GSLib\petSystem\GM\hotSpringTask.cpp
//	author:	    zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include "GSLib/petSystem/GM/talkAnswer.h"
#include <GSLib/tracer.h>
#include <GSLib/petSystem/GM/talkItem.h>
namespace GSLib
{

namespace PetSystem
{	

namespace GM
{

CTalkEnd::CTalkEnd()
{
    m_endID=0;
    m_end="";
    m_endSubList.clear();
}

CTalkEnd::~CTalkEnd()
{
}

BSLib::uint32 CTalkEnd::getEndID()
{
    return m_endID;
}

std::string CTalkEnd::getEnd()
{
    return m_end;
}

bool CTalkEnd::SerializeFrom(BSLib::Utility::CStream& stream)
{
    stream >> m_endID;
    stream >> m_end;
    BSLib::uint32 endCount = 0;
    stream >> endCount;
    for (BSLib::uint32 i = 0; i < endCount; ++i)
    {
        CTalkItem item;
        item.SerializeFrom(stream);
        m_endSubList.push_back(item);
    }
    return true;
}

bool CTalkEnd::SerializeTo(BSLib::Utility::CStream& stream) const
{
    stream << m_endID;
    stream << m_end;
    BSLib::uint32 endCount = m_endSubList.size();
    stream << endCount;
    for (BSLib::uint32 i = 0; i < endCount; ++i)
    {
        CTalkItem item = m_endSubList[i];
        item.SerializeTo(stream);
    }
    return true;
}

bool CTalkEnd::init(BSLib::uint32 a_endID,std::string& a_end)
{
    m_endID = a_endID;
    BSLib::Utility::CStringA strAnswer(a_end);
    std::vector<std::string> vecStr;
    std::string separator(":");
    strAnswer.split(vecStr, separator);
    if(vecStr.size() != 2){
        BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "[LOADCONFIG_ERROR][CTalkEnd a_end=%s]", a_end.c_str());
        return false;
    }
    m_end = vecStr[0];
    std::string subAnswer = vecStr[1];

    BSLib::Utility::CStringA strSubAnswer(subAnswer);
    std::vector<std::string> vecSubStr;
    std::string subSeparator(";");
    strSubAnswer.split(vecSubStr, subSeparator);
    m_itemArray.clear();
    for(BSLib::uint32 i=0;i<vecSubStr.size();++i){
        std::string subAnswerItem = vecSubStr[i];
        CTalkItem item(subAnswerItem);
        m_endSubList.push_back(item);
    }
    return true;
}

BSLib::uint32 CTalkEnd::getFriendlyValue()
{
    BSLib::uint32 data = 0;
    for(BSLib::uint32 i=0;i<m_endSubList.size();++i){
        CTalkItem item = m_endSubList[i];
        data += item.getFriendlyValue();
    }
    return data;
}

CTalkAnswer::CTalkAnswer()
{
    m_answerID=0;
    m_answer="";
    m_answerSubList.clear();
}

CTalkAnswer::~CTalkAnswer()
{
}

BSLib::uint32 CTalkAnswer::getAnswerID()
{
    return m_answerID;
}

std::string CTalkAnswer::getAnswer()
{
    return m_answer;
}

bool CTalkAnswer::SerializeFrom(BSLib::Utility::CStream& stream)
{
    stream >> m_answerID;
    stream >> m_answer;
    BSLib::uint32 answerCount = 0;
    stream >> answerCount;
    for (BSLib::uint32 i = 0; i < answerCount; ++i)
    {
        CTalkItem item;
        item.SerializeFrom(stream);
        m_answerSubList.push_back(item);
    }
    return true;
}

bool CTalkAnswer::SerializeTo(BSLib::Utility::CStream& stream) const
{
    stream << m_answerID;
    stream << m_answer;
    BSLib::uint32 answerCount = m_answerSubList.size();
    stream << answerCount;
    for (BSLib::uint32 i = 0; i < answerCount; ++i)
    {
        CTalkItem item = m_answerSubList[i];
        item.SerializeTo(stream);
    }
    return true;
}

bool CTalkAnswer::init(BSLib::uint32 a_answerID,std::string& a_answer)
{
    m_answerID = a_answerID;
    BSLib::Utility::CStringA strAnswer(a_answer);
    std::vector<std::string> vecStr;
    std::string separator(":");
    strAnswer.split(vecStr, separator);
    BSLib::uint32 count = vecStr.size();
    if(count != 2){
        BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "[LOADCONFIG_ERROR][CTalkAnswer a_answer=%s][count=%d]", a_answer.c_str(),count);
        return false;
    }
    m_answer = vecStr[0];
    std::string subAnswer = vecStr[1];

    BSLib::Utility::CStringA strSubAnswer(subAnswer);
    std::vector<std::string> vecSubStr;
    std::string subSeparator(";");
    strSubAnswer.split(vecSubStr, subSeparator);
    m_itemArray.clear();
    for(BSLib::uint32 i=0;i<vecSubStr.size();++i){
        std::string subAnswerItem = vecSubStr[i];
        CTalkItem item(subAnswerItem);
        m_answerSubList.push_back(item);
    }
    return true;
}

BSLib::uint32 CTalkAnswer::getFriendlyValue() const
{
    BSLib::uint32 data = 0;
    for(BSLib::uint32 i=0;i<m_answerSubList.size();++i){
        CTalkItem item = m_answerSubList[i];
        data += item.getFriendlyValue();
    }
    return data;
}

}//GM

}//PlayerSystem

}//GSLib
