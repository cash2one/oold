#ifndef __GSLIB_PLAYERSYSTEM_GM_BAGITEM_H__
#define __GSLIB_PLAYERSYSTEM_GM_BAGITEM_H__
#include <GSLib/tracer.h>
#include <BSLib/utility/baseDef.h>
#include <GSLib/itemSystem/GM/itemAttributeGM.h>
#include <GSLib/playerSystem/baseDef.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
//#include <GSLib/playerSystem/GM/roleGM.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace GM
{

#define EBAGPOSITION_MAX_COUNT 200

enum EAddResult
{
	EADDITEM_SUCCESS,                      // 添加成功
	EADDITEM_INVALID_ITEM,                 // 无效的物品
    EADDITEM_BAG_NOTENOUGH_POSITION,       // 背包已满
	EADDITEM_FAIL,                         // 服务器错误
};

enum EUseResult
{
	EUSEITEM_SUCCESS,        // 添加成功
	EUSEITEM_INVALID_ITEM,   // 无效的物品
	EUSEITEM_NOTENOUGH_ITEM, // 数量不足
	EUSEITEM_USELIMIT_ITEM,  // 不可使用物品
	EUSEITEM_BAG_FULL,       // 背包扩展空间已满
	EUSEITEM_FAIL,
};

struct SDesItem{
    BSLib::uint32 m_index;
    BSLib::uint32 m_tpid;
    BSLib::uint32 m_count;
    GSLib::ItemSystem::GM::EItemType m_type;
};

struct SBagItem
{
    SBagItem()
    {
        m_index = 0;
        m_tpid = 0;
        m_type = GSLib::ItemSystem::GM::EITEM_TP_IVALID;
        m_count = 0;
        m_instanceID = 0;
    }
    bool serializeTo(BSLib::Utility::CStream& a_stream) const
    {
        a_stream << m_index;
        a_stream << m_count;
        a_stream << m_tpid;
        BSLib::uint32 type = (BSLib::uint32)m_type; 
        a_stream << type;
        a_stream << m_instanceID;
        return true;
    }

    BSLib::uint32 m_index;                          // 物品位置
    BSLib::uint32 m_tpid;                           // 物品TPID
    BSLib::uint32 m_count;                          // 物品数目
    GSLib::ItemSystem::GM::EItemType m_type;        // 物品类型
    BSLib::uint32 m_instanceID;                     // 物品实例ID装备使用

};

class CItemTPIDList
{
public:
    CItemTPIDList(SItemInstanceID a_itemInstanceID,BagIndex a_index,BSLib::uint32 a_count,GSLib::ItemSystem::GM::EItemType a_type);
    virtual ~CItemTPIDList();
    void final();
public:
    bool setIndexItemCount(BagIndex a_index,BSLib::uint32 a_count);
    bool removeItemCount(BSLib::uint32 a_count,std::vector<BSLib::uint32>& a_notifyIndexArray,std::vector<BSLib::uint32>& a_notifyCountArray);

public:
    bool serializeTo(BSLib::uint32& a_itemCount,BSLib::Utility::CStream& stream) const;
    bool getItem(BagIndex a_index,DB::SRoleBagItemData& a_bagItemData) const;
    bool getItemByIndex(BagIndex a_index,SBagItem& a_bagItem) const;
    BagIndex getFirstNotFullIndex() const;

    BSLib::uint32 getItemCount(BagIndex a_index) const;
    BSLib::uint32 getTotalCount() const;
    
private:
    bool _setIndexItemCount(BagIndex a_index,BSLib::uint32 a_count);
    void _setTotalCount(BSLib::uint32 a_count);

    BSLib::uint32 _getCount(BagIndex a_index) const;

private:
    std::map<BagIndex,BSLib::uint32> m_bagIndexMap;
    BSLib::uint32 m_totalCount;
    SItemInstanceID m_itemInstanceID;
public:
    GSLib::ItemSystem::GM::EItemType m_type;
};

}//GM

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GM_BAGITEM_H__

