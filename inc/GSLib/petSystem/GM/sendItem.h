#ifndef __GSLIB_PETSYSTEM_GM_SENDITEM_H__
#define __GSLIB_PETSYSTEM_GM_SENDITEM_H__

#include <GFLib/commonServer/commonSystem.h>
#include "GSLib//petSystem/baseDef.h"
#include <GSLib/itemSystem/GM/itemAttributeGM.h>
#include <GSLib/petSystem/GM/sendItem.h>
namespace GSLib
{

namespace PetSystem
{

namespace GM
{
class CSendItem
{
public:
    CSendItem();
    ~CSendItem();

    bool serializeFrom(BSLib::Utility::CStream& stream);
    bool serializeTo(BSLib::Utility::CStream& stream) const;
    void addItem(ItemSystem::GM::CPrizeItem a_item);
    const std::vector<ItemSystem::GM::CPrizeItem>& getItemArray() const;

   
private:
    std::vector<ItemSystem::GM::CPrizeItem> m_itemArray;
};

}//GM

}//PetSystem

}//GSLib
#endif// __GSLIB_PETSYSTEM_GM_SENDITEM_H__

