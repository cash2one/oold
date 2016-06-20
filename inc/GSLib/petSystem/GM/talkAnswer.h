//////////////////////////////////////////////////////////////////////
//	created:	2015/03/05
//	filename: 	GSLib\petSystem\GM\hotSpring.h
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PETSYSTEM_GM_TALKANSWER_H__
#define __GSLIB_PETSYSTEM_GM_TALKANSWER_H__

#include <GFLib/commonServer/commonSystem.h>
#include "GSLib//petSystem/baseDef.h"
#include <GSLib/petSystem/GM/talkItem.h>
#include <GSLib/itemSystem/GM/itemAttributeGM.h>
namespace GSLib
{

namespace PetSystem
{

namespace GM
{

class CTalkEnd
{
public:
    CTalkEnd();
    ~CTalkEnd();

    BSLib::uint32 getEndID();
    std::string getEnd();
    
    void setEndID(BSLib::uint32 a_endID){m_endID = a_endID;}
    void setEnd(std::string a_end){m_end = a_end;}

    bool SerializeFrom(BSLib::Utility::CStream& stream);
    bool SerializeTo(BSLib::Utility::CStream& stream) const;

    bool init(BSLib::uint32 a_endID,std::string& a_end);

    BSLib::uint32 getFriendlyValue();

    std::vector<ItemSystem::GM::CPrizeItem>& getItemList(){ return m_itemArray;}

private:
    BSLib::uint32 m_endID;
    std::string m_end;
    std::vector<CTalkItem> m_endSubList;
    std::vector<ItemSystem::GM::CPrizeItem> m_itemArray;
};


class CTalkAnswer
{
public:
    CTalkAnswer();
    ~CTalkAnswer();

    BSLib::uint32 getAnswerID();
    std::string getAnswer();

    void setAnswerID(BSLib::uint32 a_answerID){m_answerID = a_answerID;}
    void setAnswer(std::string a_answer){m_answer = a_answer;}

    bool SerializeFrom(BSLib::Utility::CStream& stream);
    bool SerializeTo(BSLib::Utility::CStream& stream) const;

    bool init(BSLib::uint32 a_answerID,std::string& a_answer);

    BSLib::uint32 getFriendlyValue() const;

    const std::vector<ItemSystem::GM::CPrizeItem>& getItemList() const{ return m_itemArray;}

private:
    BSLib::uint32 m_answerID;
    std::string m_answer;
    std::vector<CTalkItem> m_answerSubList;
    std::vector<ItemSystem::GM::CPrizeItem> m_itemArray;
};

}//GM

}//PetSystem

}//GSLib
#endif// __GSLIB_PETSYSTEM_GM_TALKANSWER_H__
