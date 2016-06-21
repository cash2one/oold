#ifndef __GSLIB_PETSYSTEM_GM_PETUNLOCKITEM_H__
#define __GSLIB_PETSYSTEM_GM_PETUNLOCKITEM_H__
#include <BSLib/utility/table.h>
#include <BSLib/utility/stream.h>
#include <GSLib/petSystem/baseDef.h>
namespace GSLib
{

namespace PetSystem
{

namespace GM
{

struct SPetUnlockItem
{
    PetID m_petID;
    PetTPID m_petTPID;
    EPetUnlockStatus m_petUnlockStatus;
    bool serializeFrom(BSLib::Utility::CStream& stream);
    bool serializeTo(BSLib::Utility::CStream& stream) const;
};

class CPetUnlockData
{
public:
    CPetUnlockData();
    ~CPetUnlockData();

    bool serializeFrom(BSLib::Utility::CStream& stream);
    bool serializeTo(BSLib::Utility::CStream& stream) const;
    void addItem(SPetUnlockItem& a_item);
    const std::vector<SPetUnlockItem>& getItemArray() const;
private:
    std::vector<SPetUnlockItem> m_itemArray;
};

}//GM
}//petSystem
}//GSLib
#endif// __GSLIB_PETSYSTEM_GM_PETUNLOCKITEM_H__

