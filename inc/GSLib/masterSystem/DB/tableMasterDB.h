
#ifndef __GSLIB_MASTERSYSTEM_DB_TABLEMASTERDB_H__
#define __GSLIB_MASTERSYSTEM_DB_TABLEMASTERDB_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/dbTableID.h>

namespace GSLib
{

namespace MasterSystem
{

namespace DB
{

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif


const BSLib::Database::SDbColumn g_commandDataColumn[] = {
	{ "Id",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		},
	{ "Request",		BSLib::Database::EDT_STRING,						0,	BSLib::Database::EDF_NULL		},
	{ "Reply",			BSLib::Database::EDT_STRING,						0,	BSLib::Database::EDF_NULL		},
	{ "ReadFlag",		BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},
	{ "ReturnFlag",		BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},
	//{ "Time",			BSLib::Database::EDT_BLOB,							0,	BSLib::Database::EDF_NULL		},
	{ "",				BSLib::Database::EDT_NULL,							0,	BSLib::Database::EDF_NULL		}
};


struct Commandst
{	
	Commandst()
		:m_id(0)
		,m_readFlag(0)
		,m_returnFlag(0)
	{
	}

	Commandst(const Commandst& other)
	{
		this->m_id = other.m_id;
		this->m_request = other.m_request;
		this->m_reply = other.m_reply;
		this->m_readFlag = other.m_readFlag;
		this->m_returnFlag = other.m_returnFlag;
	}

	bool serializeTo(BSLib::Utility::CStream& a_stream){
		a_stream << m_id;
		a_stream << m_request;
		a_stream << m_reply;
		a_stream << m_readFlag;
		a_stream << m_returnFlag;
		return true;
	}


	bool serializeFrom(BSLib::Utility::CStream& a_stream){
		a_stream >> m_id;
		a_stream >> m_request;
		a_stream >> m_reply;
		a_stream >> m_readFlag;
		a_stream >> m_returnFlag;
		return true;
	}

	BSLib::uint32	m_id;
	std::string		m_request;
	std::string		m_reply;
	BSLib::uint32	m_readFlag;
	BSLib::uint32	m_returnFlag;
};


#ifdef WIN32
#pragma pack (pop) 
#else
#pragma pack ()
#endif


}//DB

}

}//GSLib

#endif
