//////////////////////////////////////////////////////////////////////
//	created:	2014/08/20
//	filename:	GSLib\inc\baseDef.h
//	author:		zhangping
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_ITEMSYSTEM_BASEDEF_H__
#define __GSLIB_ITEMSYSTEM_BASEDEF_H__

typedef BSLib::uint32 ItemTPID;                          // 物品TPID 配置表中的物品ID
typedef BSLib::uint32 InstanceID;                        // 内存中的实例ID,目前仅装备需要实例ID
typedef BSLib::uint32 BagIndex;                          // 背包格子索引

#define  INVALID_ITEMINDEX  -1                           // 无效索引
#define  INVALID_BAG_POSITION_INDEX   65535              // 无效格子索引


struct SItemInstanceID
{
public:
    SItemInstanceID()
        : m_itemTPID(0), m_instanceID(0) {} 
    SItemInstanceID(ItemTPID a_itemTPID, InstanceID a_instanceID)
        : m_itemTPID(a_itemTPID), m_instanceID(a_instanceID){} 
    ItemTPID getItemTPID() const { return m_itemTPID; }
    InstanceID getInstanceID() const { return m_instanceID; }

    void setItemTPID(ItemTPID a_itemTPID)	{ m_itemTPID = a_itemTPID; }
    void setInstanceID(InstanceID a_instanceID) { m_instanceID = a_instanceID; }

    SItemInstanceID& operator =(const SItemInstanceID& a_entityID)
    {
        m_itemTPID = a_entityID.m_itemTPID;
        m_instanceID = a_entityID.m_instanceID;
        return *this;
    }

    bool operator < (const SItemInstanceID& a_entityID) const
    {
        if( m_itemTPID < a_entityID.m_itemTPID){
            return true;
        }	
        else if((m_itemTPID == a_entityID.m_itemTPID) && (m_instanceID < a_entityID.m_instanceID)){
            return true;
        }	
        return false;
    }

    bool operator ==(const SItemInstanceID& a_entityID) const 
    {
        return (m_itemTPID == a_entityID.m_itemTPID) && (m_instanceID == a_entityID.m_instanceID);
    }

    bool operator !=(const SItemInstanceID& a_entityID) const
    {
        return (m_itemTPID != a_entityID.m_itemTPID) || (m_instanceID != a_entityID.m_instanceID);
    }

    bool isEmpty() const
    {
         return (m_itemTPID == 0) && (m_instanceID == 0);
    }

    std::string toLogString() const 
    {
        BSLib::Utility::CStringA log;
        log.format("[m_itemTPID=%d][m_instanceID=%d]", m_itemTPID, m_instanceID);
        return log;
    }
private:
   ItemTPID m_itemTPID;
   InstanceID m_instanceID;
};

#endif//__GSLIB_ITEMSYSTEM_BASEDEF_H__