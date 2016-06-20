//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	GSLib\equipSystem\msgEquipSystemGC.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_EQUIPSYSTEM_MSGEQUIPSYSTEMGC_H__
#define __GSLIB_EQUIPSYSTEM_MSGEQUIPSYSTEMGC_H__

#include <GSLib/equipSystem/msgNumIDEquipSystem.h>

namespace GSLib
{

namespace EquipSystem
{

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDEquipSystemGM2GCAckSaveOperation = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_SAVEOPERATION);
class CMsgEquipSystemGM2GCAckSaveOperation: public GFLib::CMessage
{
public:
    CMsgEquipSystemGM2GCAckSaveOperation() : GFLib::CMessage(MsgIDEquipSystemGM2GCAckSaveOperation)
    {
        m_retCode = ESAVEOPERATION_RESULT_FAIL;
        m_equipID = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_equipID;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::uint32 m_equipID;
};

const BSLib::uint32 MsgIDEquipSystemGM2GCAckChangeEquipStatus= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_CHANGE_EQUIPSTATUS);
class CMsgEquipSystemGM2GCAckChangeEquipStatus: public GFLib::CMessage
{
public:
	CMsgEquipSystemGM2GCAckChangeEquipStatus() : GFLib::CMessage(MsgIDEquipSystemGM2GCAckChangeEquipStatus)
	{
        m_retCode = ECHANGESTATUS_RESULT_FAIL;
        m_equipID = 0;
        m_itemIndex = 0;
        m_status = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
        stream << m_retCode;
        stream << m_equipID;
        stream << m_itemIndex;
        stream << m_status;
		return true;
	}

public:
    BSLib::uint32 m_retCode;
    BSLib::uint32 m_equipID;
    BSLib::uint32 m_itemIndex;
    BSLib::uint32 m_status;
};

const BSLib::uint32 MsgIDEquipSystemGM2GCAckResetAttr = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_RESETATTR);
class CMsgEquipSystemGM2GCAckResetAttr: public GFLib::CMessage
{
public:
    CMsgEquipSystemGM2GCAckResetAttr() : GFLib::CMessage(MsgIDEquipSystemGM2GCAckResetAttr)
    {
        m_retCode = ERESETATTR_RESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDEquipSystemGM2GCAckEquipItem= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_GET_ROLEEQUIP);
class CMsgEquipSystemGM2GCAckGetEquipItem: public GFLib::CMessage
{
public:
	CMsgEquipSystemGM2GCAckGetEquipItem() : GFLib::CMessage(MsgIDEquipSystemGM2GCAckEquipItem)
	{
		m_retCode = EINITEQUIPDATA_RESULT_FAIL;
		m_stream.reset();
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_retCode;
		stream << m_stream;
		return true;
	}

public:
	BSLib::uint32 m_retCode;
	BSLib::Utility::CStream m_stream;
};



const BSLib::uint32 MsgIDEquipSystemGM2GCAckNextAddLevelEquip = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_NEXT_ADDLEVEL_EQUIPSTATUS);
class CMsgEquipSystemGM2GCAckNextAddLevelEquip: public GFLib::CMessage
{
public:
    CMsgEquipSystemGM2GCAckNextAddLevelEquip() : GFLib::CMessage(MsgIDEquipSystemGM2GCAckNextAddLevelEquip)
    {
        m_retCode = EGETEQUIP_RESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDEquipSystemGM2GCAckDisassemblyEquip = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_DISASSEMBLY_EQUIP);
class CMsgEquipSystemGM2GCAckDisassemblyEquip: public GFLib::CMessage
{
public:
    CMsgEquipSystemGM2GCAckDisassemblyEquip() : GFLib::CMessage(MsgIDEquipSystemGM2GCAckDisassemblyEquip)
    {
        m_retCode = EDISASSEMBLYEQUIP_RESULT_FAIL;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        return true;
    }
public:
    BSLib::uint32 m_retCode;
};

const BSLib::uint32 MsgIDEquipSystemGM2GCAckGetDisassemblyEquipResult = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_GET_DISASSEMBLY_EQUIP_RESULT);
class CMsgEquipSystemGM2GCAckGetDisassemblyEquipResult: public GFLib::CMessage
{
public:
    CMsgEquipSystemGM2GCAckGetDisassemblyEquipResult() : GFLib::CMessage(MsgIDEquipSystemGM2GCAckGetDisassemblyEquipResult)
    {
        m_retCode = EGETDISASSEMBLYEQUIP_RESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};


const BSLib::uint32 MsgIDEquipSystemGM2GCAckEquipData= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_EQUIP_DATA);
class CMsgEquipSystemGM2GCAckEquipData: public GFLib::CMessage
{
public:
    CMsgEquipSystemGM2GCAckEquipData() : GFLib::CMessage(MsgIDEquipSystemGM2GCAckEquipData)
    {
        m_retCode = EEQUIPDATA_RESULT_FAIL;
        m_equipCount = 0;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_equipCount;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::uint32 m_equipCount;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDEquipSystemGM2GCAckCondition = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_CONDITION);
class CMsgEquipSystemGM2GCAckCondition: public GFLib::CMessage
{
public:
    CMsgEquipSystemGM2GCAckCondition() : GFLib::CMessage(MsgIDEquipSystemGM2GCAckCondition)
    {
        m_retCode = ECONDITION_RESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};


const BSLib::uint32 MsgIDEquipSystemGM2GCAckUpdateRoleEquipData= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GM2GC_NTF_ROLEEQUIPDATA_UPDATE);
class CMsgEquipSystemGM2GCAckUpdateRoleEquipData: public GFLib::CMessage
{
public:
	CMsgEquipSystemGM2GCAckUpdateRoleEquipData() : GFLib::CMessage(MsgIDEquipSystemGM2GCAckUpdateRoleEquipData)
	{
		m_retCode = EUPDATEEQUIPDATA_RESULT_FAIL;
		m_stream.reset();
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_retCode;
		stream << m_stream;
		return true;
	}

public:
	BSLib::uint32 m_retCode;
	BSLib::Utility::CStream m_stream;
};


const BSLib::uint32 MsgIDEquipSystemGM2GCAckEquipUpgradeLevel= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_UPGRADE_LEVEL);
class CMsgEquipSystemGM2GCAckUpgradeLevel: public GFLib::CMessage
{
public:
	CMsgEquipSystemGM2GCAckUpgradeLevel() : GFLib::CMessage(MsgIDEquipSystemGM2GCAckEquipUpgradeLevel)
	{
		m_retCode = EUPGRADELEVEL_RESULT_FAIL;
		m_stream.reset();
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_retCode;
		stream << m_stream;
		return true;
	}

public:
	BSLib::uint32 m_retCode;
	BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDEquipSystemGM2GCAckUpgradeQuality = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_UPGRADE_QUALITY);
class CMsgEquipSystemGM2GCAckUpgradeQuality: public GFLib::CMessage
{
public:
	CMsgEquipSystemGM2GCAckUpgradeQuality() : GFLib::CMessage(MsgIDEquipSystemGM2GCAckUpgradeQuality)
	{
		m_retCode = EUPGRATEQUALITY_EEQUIPRESUlT_FAIL;
		m_stream.reset();
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_retCode;
		stream << m_stream;
		return true;
	}

public:
	BSLib::uint32 m_retCode;
	BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDEquipSystemGM2GCAckGemCombine = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_GEM_COMBINE);
class CMsgEquipSystemGM2GCAckGemCombine: public GFLib::CMessage
{
public:
	CMsgEquipSystemGM2GCAckGemCombine() : GFLib::CMessage(MsgIDEquipSystemGM2GCAckGemCombine)
	{
		m_retCode = EGEM_COMBINE_RESULT_FAIL;
		m_newGemTPID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_retCode;
		stream << m_newGemTPID;
		return true;
	}

public:
	BSLib::uint32 m_retCode;
	BSLib::uint32 m_newGemTPID;
};


const BSLib::uint32 MsgIDEquipSystemGM2GCAckChangeGemStatus = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_EQUIPSYSTEM, EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_CHANGE_GEM_STATUS);
class CMsgEquipSystemGM2GCAckChangeGemStatus: public GFLib::CMessage
{
public:
    CMsgEquipSystemGM2GCAckChangeGemStatus() : GFLib::CMessage(MsgIDEquipSystemGM2GCAckChangeGemStatus)
    {
        m_retCode = EGEM_UPDATESTATUS_RESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};

}//EquipSystem

}//GSLib

#endif//__GSLIB_EQUIPSYSTEM_MSGEQUIPSYSTEMGC_H__
