#include "GSLib/itemSystem/GM/itemAttributeGM.h"
#include <GSLib/tracer.h>
#include "GSLib/itemSystem/GM/itemGMMgr.h"
namespace GSLib
{

namespace ItemSystem
{	

namespace GM
{

CPrizeItem::CPrizeItem(ItemTPID a_TPID, GSLib::ItemSystem::GM::EItemType a_itemType, BSLib::uint32 a_itemCount)
:m_itemTPID(a_TPID)
,m_itemType(a_itemType)
,m_itemCount(a_itemCount)
{
}

CPrizeItem::~CPrizeItem()
{
}

bool CPrizeItem::init(const std::string& a_strItem, const std::string& a_separator)
{
    BSLib::Utility::CStringA strItem(a_strItem);
    std::vector<std::string> vecStr;
    strItem.split(vecStr, a_separator);
    if(vecStr.size() != 2){
        return false;
    }
    m_itemTPID = (BSLib::uint32)atoi(vecStr[0].c_str());
    m_itemCount = (BSLib::uint32)atoi(vecStr[1].c_str());
    m_itemType = EITEM_TP_IVALID;
    //m_itemType = CItemGMMgr::singleton().getType(m_itemTPID);
    return true;
}

void CPrizeItem::serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_itemTPID;
	stream << (BSLib::uint32)m_itemType;
	stream << m_itemCount;
}

void CPrizeItem::serializeFrom(BSLib::Utility::CStream& stream)
{
    stream >> m_itemTPID;
    BSLib::uint32 itemType = 0;
    stream >> itemType;
    m_itemType = (GSLib::ItemSystem::GM::EItemType)itemType;
    stream >> m_itemCount;
}
}//GM

}//PlayerSystem

}//GSLib

