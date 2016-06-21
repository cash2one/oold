#ifndef __GSLIB_EQUIPSYSTEM_GM_MSGEQUIPSYSTEMGM_H__
#define __GSLIB_EQUIPSYSTEM_GM_MSGEQUIPSYSTEMGM_H__


#include <GSLib/equipSystem/msgNumIDEquipSystem.h>
namespace GSLib
{

namespace EquipSystem
{

//////////////////////////////////////////////////////////////////////

const BSLib::uint32 MsgIDEquipSystemGC2GMReqChangeEquipStatus = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_CHANGE_EQUIPSTATUS);
class CMsgEquipSystemGC2GMReqChangeEquipStatus: public GFLib::CMessage
{
public:
    CMsgEquipSystemGC2GMReqChangeEquipStatus() : GFLib::CMessage(MsgIDEquipSystemGC2GMReqChangeEquipStatus)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_equipID;
        stream << m_itemIndex;
        stream << m_status;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_equipID;
        stream >> m_itemIndex;
        stream >> m_status;
        return true;
    }

public:
    BSLib::uint32 m_equipID;
    BSLib::uint32 m_itemIndex;
    BSLib::uint32 m_status;
};

const BSLib::uint32 MsgIDEquipSystemGC2GMReqResetAttr = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_RESETATTR);
class CMsgEquipSystemGC2GMReqResetAttr: public GFLib::CMessage
{
public:
	CMsgEquipSystemGC2GMReqResetAttr() : GFLib::CMessage(MsgIDEquipSystemGC2GMReqResetAttr)
	{
        m_equipID = 0;
        m_itemTPID = 0;
		m_itemEquipID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_equipID;
        BSLib::uint32 resetEquipType = (BSLib::uint32)m_resetEquipType;
        stream << resetEquipType;
        BSLib::uint32 lockIndexCount = m_lockAttrIndexArray.size();
		stream << lockIndexCount;
        std::vector<BSLib::uint32>::const_iterator it = m_lockAttrIndexArray.begin();
        for(;it != m_lockAttrIndexArray.end(); ++it){
            BSLib::uint32 index = *it;
            stream << index;
        }
		stream << m_itemEquipID;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_equipID;
        BSLib::uint32 resetEquipType = 0;
		stream >> resetEquipType;
        m_resetEquipType = (EResetEquipType)resetEquipType;
        BSLib::uint32 lockIndexCount = 0;
		stream >> lockIndexCount;
        for(BSLib::uint32 i=0;i<lockIndexCount; ++i){
            BSLib::uint32 index = 0;
            stream >> index;
            m_lockAttrIndexArray.push_back(index);
        }

		stream >> m_itemEquipID;
		return true;
	}

public:
    BSLib::uint32 m_equipID;
	BSLib::uint32 m_itemTPID;
    EResetEquipType m_resetEquipType;
    std::vector<BSLib::uint32> m_lockAttrIndexArray;
	BSLib::uint32 m_itemEquipID;
};

const BSLib::uint32 MsgIDEquipSystemGC2GMReqEquipData = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_EQUIP_DATA);
class CMsgEquipSystemGC2GMReqEquipData: public GFLib::CMessage
{
public:
    CMsgEquipSystemGC2GMReqEquipData() : GFLib::CMessage(MsgIDEquipSystemGC2GMReqEquipData)
    {
        m_type = REQ_EQUIP_ALL;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_type;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_type;
        return true;
    }
public:
    EReqEquipType m_type;
};


const BSLib::uint32 MsgIDEquipSystemGC2GMReqInitRoleEquipData = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_GET_ROLEEQUIP);
class CMsgEquipSystemGC2GMReqGetEquipItem: public GFLib::CMessage
{
public:
	CMsgEquipSystemGC2GMReqGetEquipItem() : GFLib::CMessage(MsgIDEquipSystemGC2GMReqInitRoleEquipData)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_reqType;
        stream << m_reqID;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_reqType;
        stream >> m_reqID;
        return true;
    }

public:
    BSLib::uint32 m_reqType;
    BSLib::uint32 m_reqID;
};

const BSLib::uint32 MsgIDEquipSystemGC2GMReqCondition = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_CONDITION);
class CMsgEquipSystemGC2GMReqCondition: public GFLib::CMessage
{
public:
    CMsgEquipSystemGC2GMReqCondition() : GFLib::CMessage(MsgIDEquipSystemGC2GMReqCondition)
    {
    }
protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_equipID;
        stream << m_operation;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_equipID;
        stream >> m_operation;
        return true;
    }

public:
    BSLib::uint32 m_equipID;
    BSLib::uint32 m_operation;
};

const BSLib::uint32 MsgIDEquipSystemGC2GMReqSaveOperation = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_SAVEOPERATION);
class CMsgEquipSystemGC2GMReqSaveOperation: public GFLib::CMessage
{
public:
    CMsgEquipSystemGC2GMReqSaveOperation() : GFLib::CMessage(MsgIDEquipSystemGC2GMReqSaveOperation)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_equipID;
        stream << m_opType;
        stream << m_opResult;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_equipID;
        stream >> m_opType;
        stream >> m_opResult;
        return true;
    }

public:
    BSLib::uint32 m_equipID;
    BSLib::uint32 m_opType;
    BSLib::uint32 m_opResult;
};

const BSLib::uint32 MsgIDEquipSystemGC2GMReqUpgradeLevel = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_UPGRADE_LEVEL);
class CMsgEquipSystemGC2GMReqUpgradeLevel: public GFLib::CMessage
{
public:
	CMsgEquipSystemGC2GMReqUpgradeLevel() : GFLib::CMessage(MsgIDEquipSystemGC2GMReqUpgradeLevel)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_equipID;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_equipID;
		return true;
	}

public:
	BSLib::uint32 m_equipID;
};


const BSLib::uint32 MsgIDEquipSystemGC2GMReqNextAddLevelEquip = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_NEXT_ADDLEVEL_EQUIPSTATUS);
class CMsgEquipSystemGC2GMReqNextAddLevelEquip: public GFLib::CMessage
{
public:
    CMsgEquipSystemGC2GMReqNextAddLevelEquip() : GFLib::CMessage(MsgIDEquipSystemGC2GMReqNextAddLevelEquip)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_equipID;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_equipID;
        return true;
    }

public:
    BSLib::uint32 m_equipID;
};

const BSLib::uint32 MsgIDEquipSystemGC2GMReqDisassemblyEquip = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_DISASSEMBLY_EQUIP);
class CMsgEquipSystemGC2GMReqDisassemblyEquip: public GFLib::CMessage
{
public:
    CMsgEquipSystemGC2GMReqDisassemblyEquip() : GFLib::CMessage(MsgIDEquipSystemGC2GMReqDisassemblyEquip)
    {
        m_equipIDArray.clear();
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        BSLib::uint32 count = 0;
        stream >> count;
        for(BSLib::uint32 i=0;i<count;++i){
            BSLib::uint32 equipID = 0;
            stream >> equipID;
            m_equipIDArray.push_back(equipID);
        }
        return true;
    }

public:
    std::vector<BSLib::uint32> m_equipIDArray;
};


const BSLib::uint32 MsgIDEquipSystemGC2GMReqGetDisassemblyEquipResult = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_GET_DISASSEMBLY_EQUIP_RESULT);
class CMsgEquipSystemGC2GMReqGetDisassemblyEquipResult: public GFLib::CMessage
{
public:
    CMsgEquipSystemGC2GMReqGetDisassemblyEquipResult() : GFLib::CMessage(MsgIDEquipSystemGC2GMReqGetDisassemblyEquipResult)
    {
        m_equipIDArray.clear();
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        BSLib::uint32 count = 0;
        stream >> count;
        for(BSLib::uint32 i=0;i<count;++i){
            BSLib::uint32 equipID = 0;
            stream >> equipID;
            m_equipIDArray.push_back(equipID);
        }
        return true;
    }

public:
    std::vector<BSLib::uint32> m_equipIDArray;
};

const BSLib::uint32 MsgIDEquipSystemGC2GMReqUpgradeQuality = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_UPGRADE_QUALITY);
class CMsgEquipSystemGC2GMReqUpgradeQuality: public GFLib::CMessage
{
public:
	CMsgEquipSystemGC2GMReqUpgradeQuality() : GFLib::CMessage(MsgIDEquipSystemGC2GMReqUpgradeQuality)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_equipID;
		stream << m_itemTPID;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_equipID;
		stream >> m_itemTPID;
		return true;
	}

public:
   BSLib::uint32 m_equipID;
	BSLib::uint32 m_itemTPID;
};


const BSLib::uint32 MsgIDEquipSystemGC2GMReqGemCombine = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_GEM_COMBINE);
class CMsgEquipSystemGC2GMReqGemCombine: public GFLib::CMessage
{
public:
	CMsgEquipSystemGC2GMReqGemCombine() : GFLib::CMessage(MsgIDEquipSystemGC2GMReqGemCombine)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_gemTPID;
        stream >> m_type;
        
		return true;
	}

public:
   BSLib::uint32 m_gemTPID;
   BSLib::uint32 m_type;
};



const BSLib::uint32 MsgIDEquipSystemGC2GMReqChangeGemStatus = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_CHANGE_GEM_STATUS);
class CMsgEquipSystemGC2GMReqChangeGemStatus: public GFLib::CMessage
{
public:
    CMsgEquipSystemGC2GMReqChangeGemStatus() : GFLib::CMessage(MsgIDEquipSystemGC2GMReqChangeGemStatus)
    {
        m_equipID = 0;
        m_gemSlot = 0;
        m_operation = 0;
        m_gemTPID = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_equipID;
        stream << m_gemSlot;
        stream << m_operation;
        stream << m_gemTPID;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_equipID;
        stream >> m_gemSlot;
        stream >> m_operation;
        stream >> m_gemTPID;
        return true;
    }

public:
    BSLib::uint32 m_equipID;
    BSLib::uint32 m_gemSlot;
    BSLib::uint32 m_operation;
    BSLib::uint32 m_gemTPID;
};




}//EquipSystem

}//GSLib

#endif//__GSLIB_EQUIPSYSTEM_GM_MSGEQUIPSYSTEMGM_H__

