//////////////////////////////////////////////////////////////////////
//	created:	2014/08/29
//	filename: 	src\GSLib\playerSystem\GM\roleBagModule.cpp
//	author:	    zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/playerSystem/GM/bagItem.h>
#include <GSLib/itemSystem/GM/itemGMMgr.h>
namespace GSLib
{

namespace PlayerSystem
{	

namespace GM
{

CItemTPIDList::CItemTPIDList(SItemInstanceID a_itemInstanceID,BagIndex a_index,BSLib::uint32 a_count,GSLib::ItemSystem::GM::EItemType a_type)
: m_totalCount(a_count)
, m_itemInstanceID(a_itemInstanceID)
, m_type(a_type)
{
    m_bagIndexMap.clear();
    m_bagIndexMap.insert(std::pair<BagIndex, BSLib::uint32>(a_index,a_count));
}

CItemTPIDList::~CItemTPIDList()
{
    ;
}

void CItemTPIDList::final()
{
    m_bagIndexMap.clear();
}

bool CItemTPIDList::setIndexItemCount(BagIndex a_index,BSLib::uint32 a_count)
{
    const BSLib::uint32 oldCount = _getCount(a_index);
    const BSLib::uint32 totalCount = getTotalCount();
    if(totalCount < oldCount){
        return false;
    }

    if(!_setIndexItemCount(a_index,a_count)){
        return false;
    }
    const BSLib::uint32 itemCount =  totalCount - oldCount + a_count;
    _setTotalCount(itemCount);
    return true;
}

bool CItemTPIDList::removeItemCount(BSLib::uint32 a_count,std::vector<BSLib::uint32>& a_notifyIndexArray,std::vector<BSLib::uint32>& a_notifyCountArray)
{
    a_notifyIndexArray.clear();
    a_notifyCountArray.clear();
    BSLib::uint32 rmCount = a_count;
    if(m_bagIndexMap.size() <=0){
        return false;
    }
    // 记录数据
    std::map<BagIndex,BSLib::uint32>::iterator it = m_bagIndexMap.begin();
    for (; it != m_bagIndexMap.end(); ++it) {
        BSLib::uint32 curItemCount = it->second;
        const BagIndex index = it->first;
        if (curItemCount == 0) {
            BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[removeItemCount][EMPTY_SLOT][index=%d][curItemCount=%d]",index,curItemCount);
            continue;
        }
        if(curItemCount >= rmCount){
            curItemCount  = curItemCount - rmCount;
            a_notifyIndexArray.push_back(index);
            a_notifyCountArray.push_back(curItemCount);
            break; 
        }
        else{
            const BSLib::uint32 count = 0;
            a_notifyIndexArray.push_back(index);
            a_notifyCountArray.push_back(count);
            rmCount = rmCount - curItemCount;
        }
    }
    // 修改数据
    for(BSLib::uint32 i=0;i< a_notifyCountArray.size(); ++i){
        const BSLib::uint32 index = a_notifyIndexArray[i];
        const BSLib::uint32 count = a_notifyCountArray[i];
        setIndexItemCount(index,count);
    }
    return true;
}

BSLib::uint32 CItemTPIDList::getItemCount(BagIndex a_index) const
{
    std::map<BSLib::uint32,BSLib::uint32>::const_iterator it = m_bagIndexMap.find(a_index);
    if(it == m_bagIndexMap.end()){
        return 0;
    }
    return it->second;
}

BSLib::uint32 CItemTPIDList::getTotalCount()const
{
    return m_totalCount;
}

bool CItemTPIDList::serializeTo(BSLib::uint32& a_itemCount,BSLib::Utility::CStream& stream) const
{
    BSLib::uint32 curCount = 0;
    std::map<BagIndex,BSLib::uint32>::const_iterator it = m_bagIndexMap.begin();
    for (; it != m_bagIndexMap.end(); ++it) {
        BSLib::uint32 count = it->second;
        if (count == 0) {
            continue;
        }
        curCount++;
        BagIndex index = it->first;
        stream << index;
        stream << count;
        BSLib::uint32 tpid = m_itemInstanceID.getItemTPID();
        stream << tpid;
        BSLib::uint32 type = (BSLib::uint32)m_type; 
        stream << type;
        BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[BAGDATA][CItemTPIDList::serializeTo][index=%d][a_itemTPID=%d][a_count=%d][type=%d]",index,tpid,count,type);
    }

    a_itemCount += curCount;

    return true;
}

bool CItemTPIDList::getItem(BagIndex a_index,DB::SRoleBagItemData& a_bagItemData) const
{
    a_bagItemData.m_index = a_index;
    a_bagItemData.m_itemCount = getItemCount(a_index);
    a_bagItemData.m_itemTPID = m_itemInstanceID.getItemTPID();
    a_bagItemData.m_itemType = m_type;

    return true;
}

bool CItemTPIDList::getItemByIndex(BagIndex a_index,SBagItem& a_bagItem) const
{
    a_bagItem.m_index = a_index;
    a_bagItem.m_count = getItemCount(a_index);
    a_bagItem.m_tpid = m_itemInstanceID.getItemTPID();
    a_bagItem.m_instanceID = m_itemInstanceID.getInstanceID();
    a_bagItem.m_type = m_type;
    return true; 
}

BagIndex CItemTPIDList::getFirstNotFullIndex() const
{
    BagIndex index = INVALID_BAG_POSITION_INDEX;
    const ItemTPID tpid = m_itemInstanceID.getItemTPID();
    const BSLib::uint32 maxStackCount = ItemSystem::GM::CItemGMMgr::singleton().getStackCount(tpid); 
    std::map<BagIndex,BSLib::uint32>::const_iterator it = m_bagIndexMap.begin();
    for (; it != m_bagIndexMap.end(); ++it) {
        BSLib::uint32 itemCurCount = it->second;
        if (itemCurCount < maxStackCount) {
            index = it->first;
            BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[BAGDATA][获取没达上限[%d]个背包索引位置[a_Index=%d]",maxStackCount,index);
            return index;
        }
    }
    return index; 
}

BSLib::uint32 CItemTPIDList::_getCount(BagIndex a_index) const
{
    std::map<BagIndex, BSLib::uint32>::const_iterator it =  m_bagIndexMap.find(a_index);
    if( it == m_bagIndexMap.end()){
        return 0;
    }

    return it->second;
}

bool CItemTPIDList::_setIndexItemCount(BagIndex a_index,BSLib::uint32 a_count)
{
    std::map<BSLib::uint32, BSLib::uint32>::iterator it =  m_bagIndexMap.find(a_index);
    if( it == m_bagIndexMap.end()){
        if(a_count == 0){
            return true;
        }
        m_bagIndexMap.insert(std::pair<BSLib::uint32, BSLib::uint32>(a_index,a_count));
        return true;
    }
    if(a_count == 0){
        m_bagIndexMap.erase(it);
        return true;
    }
    it->second = a_count;
    return true;
}

void CItemTPIDList::_setTotalCount(BSLib::uint32 a_count)
{
    m_totalCount = a_count;
}

}//GM

}//PlayerSystem

}//GSLib