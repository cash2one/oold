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
	EADDITEM_SUCCESS,                      // ��ӳɹ�
	EADDITEM_INVALID_ITEM,                 // ��Ч����Ʒ
    EADDITEM_BAG_NOTENOUGH_POSITION,       // ��������
	EADDITEM_FAIL,                         // ����������
};

enum EUseResult
{
	EUSEITEM_SUCCESS,        // ��ӳɹ�
	EUSEITEM_INVALID_ITEM,   // ��Ч����Ʒ
	EUSEITEM_NOTENOUGH_ITEM, // ��������
	EUSEITEM_USELIMIT_ITEM,  // ����ʹ����Ʒ
	EUSEITEM_BAG_FULL,       // ������չ�ռ�����
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

    BSLib::uint32 m_index;                          // ��Ʒλ��
    BSLib::uint32 m_tpid;                           // ��ƷTPID
    BSLib::uint32 m_count;                          // ��Ʒ��Ŀ
    GSLib::ItemSystem::GM::EItemType m_type;        // ��Ʒ����
    BSLib::uint32 m_instanceID;                     // ��Ʒʵ��IDװ��ʹ��

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

