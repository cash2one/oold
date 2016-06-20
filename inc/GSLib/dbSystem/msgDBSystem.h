//////////////////////////////////////////////////////////////////////
//	created:	2014/07/22
//	filename: 	GSLib\dbSystem\msgDBSystem.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_DBSYSTEM_MSGDBSYSTEM_H__
#define __GSLIB_DBSYSTEM_MSGDBSYSTEM_H__

#include <GSLib/dbSystem/LG/msgDBSystemLG.h>
#include <GSLib/dbSystem/DB/msgDBSystemDB.h>
#include <GSLib/dbSystem/CN/msgDBSystemCN.h>
#include <GSLib/dbSystem/GM/msgDBSystemGM.h>
#include <GSLib/dbSystem/GT/msgDBSystemGT.h>
#include <GSLib/dbSystem/msgDBSystemGC.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace DBSystem
{

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDDBSystemDB2XSAckSelectTableData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANYSERVER, EFUNCTYPE_DBSYSTEM, EMSGNUMID_DBSYSTEM_DB2XS_ACK_SELECT_TABLE_DATA);
class CMsgLoginSystemDB2XSAckSelectTableData: public GFLib::CMessage
{
public:
	CMsgLoginSystemDB2XSAckSelectTableData() : GFLib::CMessage(MsgIDDBSystemDB2XSAckSelectTableData)
	{
		m_tableID = EDBTABLEID_NULL;
		m_state = 0;
		m_moduleType = EMODULECTYPE_NULL;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_roleKey;
		stream << m_tableID;
		stream << m_funcType;
		stream << m_moduleType;
		stream << m_sessionID;
		stream << m_state;
		if (m_state != 0) {
			return true;
		}
		stream << m_stream;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_roleKey;
		stream >> m_tableID;
		stream >> m_funcType;
		stream >> m_moduleType;
		stream >> m_sessionID;
		stream >> m_state;
		if (m_state != 0) {
			return true;
		}
		stream >> m_stream;
		return true;
	}

public:
	GSLib::SRoleKey m_roleKey;
	EDBTableID m_tableID;
	BSLib::uint16 m_funcType;
	EModuleType m_moduleType;
	BSLib::uint32 m_sessionID;
	BSLib::uint32 m_state;
	BSLib::Utility::CStream m_stream;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDDBSystemDB2XSAckSelectGlobalTableData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANYSERVER, EFUNCTYPE_DBSYSTEM, EMSGNUMID_DBSYSTEM_DB2XS_ACK_SELECT_GLOBAL_TABLE_DATA);
class CMsgLoginSystemDB2XSAckSelectGlobalTableData: public GFLib::CMessage
{
public:
    CMsgLoginSystemDB2XSAckSelectGlobalTableData() : GFLib::CMessage(MsgIDDBSystemDB2XSAckSelectGlobalTableData)
    {
        m_tableID = EDBTABLEID_NULL;
        m_state = 0;
        m_moduleType = EMODULECTYPE_NULL;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_srcRoleKey;
        stream << m_roleKey;
        stream << m_tableID;
        stream << m_funcType;
        stream << m_moduleType;
        stream << m_sessionID;
        stream << m_state;
        if (m_state != 0) {
            return true;
        }
        stream << m_stream;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_srcRoleKey;
        stream >> m_roleKey;
        stream >> m_tableID;
        stream >> m_funcType;
        stream >> m_moduleType;
        stream >> m_sessionID;
        stream >> m_state;
        if (m_state != 0) {
            return true;
        }
        stream >> m_stream;
        return true;
    }

public:
    GSLib::SRoleKey m_srcRoleKey;
    GSLib::SRoleKey m_roleKey;
    EDBTableID m_tableID;
    BSLib::uint16 m_funcType;
    EModuleType m_moduleType;
    BSLib::uint32 m_sessionID;
    BSLib::uint32 m_state;
    BSLib::Utility::CStream m_stream;
};


struct SAckTablesData;
//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDDBSystemDB2XSAckSelectGlobalMultiTableData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANYSERVER, EFUNCTYPE_DBSYSTEM, EMSGNUMID_DBSYSTEM_DB2XS_ACK_SELECT_GLOBAL_MULTI_TABLE_DATA);
class CMsgLoginSystemDB2XSAckSelectGlobalMultiTableData: public GFLib::CMessage
{
public:
    CMsgLoginSystemDB2XSAckSelectGlobalMultiTableData() : GFLib::CMessage(MsgIDDBSystemDB2XSAckSelectGlobalMultiTableData)
    {
        m_state = 0;
        m_tableCount = 0;
        m_srcModuleType = EMODULECTYPE_NULL;
        m_ptr = NULL;
        m_sessionID = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_srcRoleKey;
        stream << m_srcModuleType;
        stream << m_sessionID;
        stream << m_state;
        stream.write((char*)&m_ptr,sizeof(void*));
        stream << m_tableCount;

        if (m_state != 0) {
            return true;
        }
        stream << m_stream;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_srcRoleKey;
        stream >> m_srcModuleType;
        stream >> m_sessionID;
        stream >> m_state;
        stream.read((char*)&m_ptr,sizeof(void*));
        if (m_state != 0) {
            return true;
        }
        stream >> m_tableCount;
        stream >> m_stream;
        return true;
    }

public:
    GSLib::SRoleKey m_srcRoleKey;
    EModuleType m_srcModuleType;
    BSLib::uint32 m_sessionID;
    void*  m_ptr;
    BSLib::uint32 m_state;
    BSLib::uint32 m_tableCount;
    BSLib::Utility::CStream m_stream;
};

}//DBSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_MSGDBSYSTEM_H__
