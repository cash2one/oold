#include "GSLib/petSystem/GM/talkItem.h"
#include <GSLib/tracer.h>

namespace GSLib
{

namespace PetSystem
{	

namespace GM
{


CTalkItem::CTalkItem()
{
    m_friendly = 0;
    m_count = 0;
    m_soundID = 0;
    m_userType = EUserMe;
    m_userID=0;
    m_content = "";
}

CTalkItem::CTalkItem(std::string& a_item)
{
    initTalkItem(a_item);
}

CTalkItem::~CTalkItem()
{
}

BSLib::int32 CTalkItem::getSoundID()
{
    return m_soundID;
}
BSLib::uint32 CTalkItem::getFriendlyValue()
{
    return m_friendly;
}

BSLib::uint32 CTalkItem::getCounts()
{
    return m_count;
}

BSLib::uint32 CTalkItem::getUserID()
{
    return m_userID;
}

EUserType CTalkItem::getUserType()
{
    return m_userType;
}

std::string CTalkItem::getContent()
{
    return m_content;
}

bool CTalkItem::SerializeFrom(BSLib::Utility::CStream& stream)
{
    BSLib::uint32 userType = 0;
    stream >> userType;
    m_userType = (EUserType)userType;
    stream >> m_soundID;
    stream >> m_content;
    return true;
}

bool CTalkItem::SerializeTo(BSLib::Utility::CStream& stream) const
{
    BSLib::uint32 userType = (BSLib::uint32)m_userType;
    stream << userType;
    stream << m_userID;
    stream << m_soundID;
    stream << m_content;
    return true;
}

bool CTalkItem::initTalkItem(std::string& a_item)
{   
    std::string subQuestion = a_item;
    BSLib::Utility::CStringA strSubQuestion(subQuestion);
    std::vector<std::string> vecSubStr;
    std::string subSP("|");
    strSubQuestion.split(vecSubStr, subSP);
    if (vecSubStr.size() != 4){
          return false;
    }
    if(vecSubStr[0].compare("m")){
        setUserType(EUserYou);
        m_userID = (BSLib::uint32)atoi(vecSubStr[0].c_str());
    }
    else{
        m_userID = 0;
        setUserType(EUserMe);
    }
    BSLib::int32 soundID = (BSLib::int32)atoi(vecSubStr[1].c_str());
    setSoundID(soundID);
    setContent(vecSubStr[2].c_str());
    BSLib::uint32 friendlyValue = 0;
    friendlyValue = (BSLib::uint32)atoi(vecSubStr[3].c_str());
    setFriendly(friendlyValue);
    return true;
}

}//GM

}//PlayerSystem

}//GSLib

