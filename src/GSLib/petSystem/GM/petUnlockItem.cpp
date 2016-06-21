#include <GSLib/petSystem/GM/petUnlockItem.h>
namespace GSLib
{

namespace PetSystem
{

namespace GM
{

bool SPetUnlockItem::serializeFrom(BSLib::Utility::CStream& stream)
{
    stream >> m_petID;
    stream >> m_petTPID;
    stream >> m_petUnlockStatus;
    return true;
}

bool SPetUnlockItem::serializeTo(BSLib::Utility::CStream& stream) const
{
    stream << m_petID;
    stream << m_petTPID;
    stream << m_petUnlockStatus;
   
    return true;
}

CPetUnlockData::CPetUnlockData()
{
    m_itemArray.clear();
}

CPetUnlockData::~CPetUnlockData()
{
    m_itemArray.clear();
}

bool CPetUnlockData::serializeFrom(BSLib::Utility::CStream& stream)
{
    BSLib::uint32 count = 0;
    stream >> count;
    for (BSLib::uint32 i = 0; i < count; ++i)
    {
        SPetUnlockItem item;
        item.serializeFrom(stream);
        m_itemArray.push_back(item);
    }
    return true;
}

bool CPetUnlockData::serializeTo(BSLib::Utility::CStream& stream) const
{
    BSLib::uint32 count = m_itemArray.size();
    stream << count;
    for (BSLib::uint32 i = 0; i < count; ++i){
        const SPetUnlockItem& item  = m_itemArray[i];
        item.serializeTo(stream);
    }

    return true;
}

void CPetUnlockData::addItem(SPetUnlockItem& a_item)
{
    m_itemArray.push_back(a_item);
}

const std::vector<SPetUnlockItem>& CPetUnlockData::getItemArray() const
{
    return m_itemArray;
}

}//GM

}//petSystem

}//GSLib

