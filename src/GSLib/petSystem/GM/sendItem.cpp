#include <GSLib/petSystem/GM/sendItem.h>
#include <GSLib/tracer.h>

namespace GSLib
{

namespace PetSystem
{	

namespace GM
{

CSendItem::CSendItem()
{
    m_itemArray.clear();
}

CSendItem::~CSendItem()
{
    m_itemArray.clear();
}

bool CSendItem::serializeFrom(BSLib::Utility::CStream& stream)
{
    BSLib::uint32 count = 0;
    stream >> count;
    for (BSLib::uint32 i = 0; i < count; ++i)
    {
        ItemSystem::GM::CPrizeItem item;
        item.serializeFrom(stream);
        m_itemArray.push_back(item);
    }
    return true;
}

bool CSendItem::serializeTo(BSLib::Utility::CStream& stream) const
{
    BSLib::uint32 count = m_itemArray.size();
    stream << count;
    for (BSLib::uint32 i = 0; i < count; ++i)
    {
        ItemSystem::GM::CPrizeItem item  = m_itemArray[i];
        item.serializeTo(stream);
    }
   
    return true;
}

void CSendItem::addItem(ItemSystem::GM::CPrizeItem a_item)
{
    m_itemArray.push_back(a_item);
}

const std::vector<ItemSystem::GM::CPrizeItem>& CSendItem::getItemArray() const
{
   return m_itemArray;
}

}//GM

}//PlayerSystem

}//GSLib

