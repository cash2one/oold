//////////////////////////////////////////////////////////////////////
//	created:	2015/03/05
//	filename: 	GSLib\petSystem\GM\hotSpring.h
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PETSYSTEM_GM_TALKQUESTION_H__
#define __GSLIB_PETSYSTEM_GM_TALKQUESTION_H__

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
class CTalkQuestion
{
public:
    CTalkQuestion(std::string& question);
    CTalkQuestion();
    ~CTalkQuestion();

    bool SerializeFrom(BSLib::Utility::CStream& stream);
    bool SerializeTo(BSLib::Utility::CStream& stream) const;
    bool addTalkItem(CTalkItem& a_item);
    bool init(const std::string& a_question);

    BSLib::uint32 getFriendlyValue() const;
    const std::vector<ItemSystem::GM::CPrizeItem>& getItemArray() const;

private:
    std::vector<CTalkItem> m_questionArray;
    std::vector<ItemSystem::GM::CPrizeItem> m_itemArray;
};

}//GM

}//PetSystem

}//GSLib
#endif// __GSLIB_PETSYSTEM_GM_TALKQUESTION_H__
