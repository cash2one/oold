#ifndef __GSLIB_PETSYSTEM_GM_TALKITEM_H__
#define __GSLIB_PETSYSTEM_GM_TALKITEM_H__

#include <GFLib/commonServer/commonSystem.h>
#include "GSLib//petSystem/baseDef.h"
namespace GSLib
{

namespace PetSystem
{

namespace GM
{

class CTalkItem
{
public:
    CTalkItem(std::string& a_item);
    CTalkItem();
    ~CTalkItem();

    BSLib::int32 getSoundID();
    BSLib::uint32 getFriendlyValue();
    BSLib::uint32 getCounts();
    BSLib::uint32 getUserID();
    EUserType getUserType();
    std::string getContent();

    void setSoundID(BSLib::int32 a_soundID){m_soundID = a_soundID;}
    void setFriendly(BSLib::uint32 a_friendly){m_friendly = a_friendly;}
    void setUserType(EUserType a_userType){m_userType = a_userType;}
    void setContent(std::string a_content){m_content = a_content;}


    bool SerializeFrom(BSLib::Utility::CStream& stream);
    bool SerializeTo(BSLib::Utility::CStream& stream) const;

    bool initTalkItem(std::string& a_item);
private:
    BSLib::uint32 m_friendly;// 老板娘物品ID,角色亲密度
    BSLib::uint32 m_count;//// 老板娘物品个数
    BSLib::int32 m_soundID;
    BSLib::uint32 m_userID;
    EUserType m_userType;
    std::string m_content;
};

}//GM

}//PetSystem

}//GSLib
#endif// __GSLIB_PETSYSTEM_GM_TALKITEM_H__

