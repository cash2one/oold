//////////////////////////////////////////////////////////////////////
//	created:	2014/07/22
//	filename: 	GSLib\dbSystem\DB\msgDBSystemDB.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_DBSYSTEM_DB_MSGDBSYSTEMDB_H__
#define __GSLIB_DBSYSTEM_DB_MSGDBSYSTEMDB_H__

#include <GSLib/dbSystem/msgNumIDDBSystem.h>
#include <GSLib/moduleType.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace DBSystem
{


//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDDBSystemXS2DBReqSelectTableData = GFLIB_MSGID_DEBUG(GSLib::SRVTYPE_DATASERVER, EFUNCTYPE_DBSYSTEM, EMSGNUMID_DBSYSTEM_XS2DB_REQ_SELECT_TABLE_DATA);
class CMsgLoginSystemXS2DBReqSelectTableData: public GFLib::CMessage
{
public:
	CMsgLoginSystemXS2DBReqSelectTableData() : GFLib::CMessage(MsgIDDBSystemXS2DBReqSelectTableData)
	{
		m_tableID = EDBTABLEID_NULL;
		m_moduleType = EMODULECTYPE_NULL;
		m_funcType = 0;
		m_sessionID = 0;
        m_strWhere = "";
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_roleKey;
		stream << m_key;
		stream << m_index;
		stream << m_tableID;
		stream << m_funcType;
		stream << m_moduleType;
		stream << m_sessionID;
        stream << m_strWhere;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_roleKey;
		stream >> m_key;
		stream >> m_index;
		stream >> m_tableID;
		stream >> m_funcType;
		stream >> m_moduleType;
		stream >> m_sessionID;
        stream >> m_strWhere;
		return true;
	}

public:
	GSLib::SRoleKey m_roleKey;
	std::string m_key;
	std::string m_index;
	EDBTableID m_tableID;
	BSLib::uint16 m_funcType;
	EModuleType m_moduleType;
	BSLib::uint32 m_sessionID;
    std::string m_strWhere;
};


const BSLib::uint32 MsgIDDBSystemXS2DBReqSelectGlobalTableData = GFLIB_MSGID_DEBUG(GSLib::SRVTYPE_DATASERVER, EFUNCTYPE_DBSYSTEM, EMSGNUMID_DBSYSTEM_XS2DB_REQ_SELECT_GLOBAL_TABLE_DATA);
class CMsgLoginSystemXS2DBReqSelectGlobalTableData: public GFLib::CMessage
{
public:
    CMsgLoginSystemXS2DBReqSelectGlobalTableData() : GFLib::CMessage(MsgIDDBSystemXS2DBReqSelectGlobalTableData)
    {
        m_tableID = EDBTABLEID_NULL;
        m_moduleType = EMODULECTYPE_NULL;
        m_funcType = 0;
        m_sessionID = 0;
        m_strWhere = "";
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_roleKey;
        stream << m_key;
        stream << m_index;
        stream << m_tableID;
        stream << m_funcType;
        stream << m_moduleType;
        stream << m_sessionID;
        stream << m_strWhere;
        stream << m_srcRoleKey;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_roleKey;
        stream >> m_key;
        stream >> m_index;
        stream >> m_tableID;
        stream >> m_funcType;
        stream >> m_moduleType;
        stream >> m_sessionID;
        stream >> m_strWhere;
        stream >> m_srcRoleKey;
        return true;
    }

public:
    GSLib::SRoleKey m_roleKey;
    std::string m_key;
    std::string m_index;
    EDBTableID m_tableID;
    BSLib::uint16 m_funcType;
    EModuleType m_moduleType;
    BSLib::uint32 m_sessionID;
    std::string m_strWhere;
    GSLib::SRoleKey m_srcRoleKey;
};

const BSLib::uint32 MsgIDDBSystemXS2DBReqSelectGlobalMultiTableData = GFLIB_MSGID_DEBUG(GSLib::SRVTYPE_DATASERVER, EFUNCTYPE_DBSYSTEM, EMSGNUMID_DBSYSTEM_XS2DB_REQ_SELECT_GLOBAL_MULTI_TABLE_DATA);
class CMsgLoginSystemXS2DBReqSelectGlobalMultiTableData: public GFLib::CMessage
{
public:
    CMsgLoginSystemXS2DBReqSelectGlobalMultiTableData() : GFLib::CMessage(MsgIDDBSystemXS2DBReqSelectGlobalMultiTableData)
    {
        m_tableCount = 0;
        m_sessionID = 0;
        m_srcModuleType = EMODULECTYPE_NULL;
        m_ptr = NULL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_srcRoleKey;
        stream << m_srcModuleType;
        stream << m_sessionID;
        stream.write((char*)&m_ptr,sizeof(void*));
        stream << m_tableCount;
        stream << m_stream;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_srcRoleKey;
        stream >> m_srcModuleType;
        stream >> m_sessionID;
        stream.read((char*)&m_ptr,sizeof(void*));
        stream >> m_tableCount;
        stream >> m_stream;
        return true;
    }

public:
    GSLib::SRoleKey m_srcRoleKey;
    EModuleType m_srcModuleType;
    BSLib::uint32 m_sessionID;
    void*  m_ptr;
    BSLib::uint32 m_tableCount;
    BSLib::Utility::CStream m_stream;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDDBSystemXS2DBNtfUpdateTableData = GFLIB_MSGID_DEBUG(GSLib::SRVTYPE_DATASERVER, EFUNCTYPE_DBSYSTEM, EMSGNUMID_DBSYSTEM_XS2DB_NTF_UPDATE_TABLE_DATA);
class CMsgLoginSystemXS2DBNtfUpdateTableData: public GFLib::CMessage
{
public:
	CMsgLoginSystemXS2DBNtfUpdateTableData() : GFLib::CMessage(MsgIDDBSystemXS2DBNtfUpdateTableData)
	{
		m_tableID = EDBTABLEID_NULL;
		m_neadSave = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_key;
		stream << m_index;
		stream << m_name;
		stream << m_tableID;
		stream << m_neadSave;
		stream << m_stream;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_key;
		stream >> m_index;
		stream >> m_name;
		stream >> m_tableID;
		stream >> m_neadSave;
		stream >> m_stream;
		return true;
	}

public:
	std::string m_key;
	std::string m_index;
	std::string m_name;
	EDBTableID m_tableID;
	BSLib::uint8 m_neadSave;
	BSLib::Utility::CStream m_stream;
	
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDDBSystemXS2DBNtfSaveTableData = GFLIB_MSGID_DEBUG(GSLib::SRVTYPE_DATASERVER, EFUNCTYPE_DBSYSTEM, EMSGNUMID_DBSYSTEM_XS2DB_NTF_SAVE_TABLE_DATA);
class CMsgLoginSystemXS2DBNtfSaveTableData: public GFLib::CMessage
{
public:
	CMsgLoginSystemXS2DBNtfSaveTableData() : GFLib::CMessage(MsgIDDBSystemXS2DBNtfSaveTableData)
	{
		m_tableID = EDBTABLEID_NULL;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_key;
		stream << m_index;
		stream << m_tableID;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_key;
		stream >> m_index;
		stream >> m_tableID;
		return true;
	}

public:
	std::string m_key;
	std::string m_index;
	EDBTableID m_tableID;
};

const BSLib::uint32 MsgIDDBSystemXS2DBNtfCloseTableData = GFLIB_MSGID_DEBUG(GSLib::SRVTYPE_DATASERVER, EFUNCTYPE_DBSYSTEM, EMSGNUMID_DBSYSTEM_XS2DB_NTF_CLOSE_TABLE_DATA);
class CMsgLoginSystemXS2DBNtfCloseTableData: public GFLib::CMessage
{
public:
	CMsgLoginSystemXS2DBNtfCloseTableData() : GFLib::CMessage(MsgIDDBSystemXS2DBNtfCloseTableData)
	{
		m_tableID = EDBTABLEID_NULL;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_key;
		stream << m_index;
		stream << m_tableID;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_key;
		stream >> m_index;
		stream >> m_tableID;
		return true;
	}

public:
	std::string m_key;
	std::string m_index;
	EDBTableID m_tableID;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDDBSystemXS2DBNtfRemoveTableData = GFLIB_MSGID_DEBUG(GSLib::SRVTYPE_DATASERVER, EFUNCTYPE_DBSYSTEM, EMSGNUMID_DBSYSTEM_XS2DB_NTF_REMOVE_TABLE_DATA);
class CMsgLoginSystemXS2DBNtfRemoveTableData: public GFLib::CMessage
{
public:
	CMsgLoginSystemXS2DBNtfRemoveTableData() : GFLib::CMessage(MsgIDDBSystemXS2DBNtfRemoveTableData)
	{
		m_tableID = EDBTABLEID_NULL;
		m_neadSave = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_tableID;
		stream << m_neadSave;
		stream << m_stream;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_tableID;
		stream >> m_neadSave;
		stream >> m_stream;
		return true;
	}

public:
	EDBTableID m_tableID;
	BSLib::uint8 m_neadSave;
	BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDDBSystemCH2DBNtfCharge = GFLIB_MSGID_DEBUG(SRVTYPE_DATASERVER, EFUNCTYPE_DBSYSTEM, EMSGNUMID_DBSYSTEM_CH2DB_NTF_CHARGE);
class CMsgDBSystemCH2DBNtfCharge: public GFLib::CMessage
{
public:
	CMsgDBSystemCH2DBNtfCharge() : GFLib::CMessage(MsgIDDBSystemCH2DBNtfCharge)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_roleKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_roleKey;
		return true;
	}

public:
	SRoleKey m_roleKey;
};


}//DBSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_DB_MSGDBSYSTEMDB_H__
