#ifndef __GSLIB_MAILSYSTEM_DB_TABLEMAILDB_H__
#define __GSLIB_MAILSYSTEM_DB_TABLEMAILDB_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/dbTableID.h>

namespace GSLib
{

namespace MailSystem
{

namespace DB
{

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

	
enum EDBColumnIndexMailOutputData
{
	EDBCOLUMN_MailOUTPUTDATA_AccountID = 0,
	EDBCOLUMN_MailOUTPUTDATA_ZoneID,
	EDBCOLUMN_MailOUTPUTDATA_RoleIndex,
	EDBCOLUMN_MailOUTPUTDATA_MailID,
	EDBCOLUMN_MailOUTPUTDATA_MailType,
	EDBCOLUMN_MailOUTPUTDATA_SystemMail,
	EDBCOLUMN_MailOUTPUTDATA_IsRead,
	EDBCOLUMN_MailOUTPUTDATA_IsGet,
	EDBCOLUMN_MailOUTPUTDATA_TimeStamp,
	EDBCOLUMN_MailOUTPUTDATA_Title,
	EDBCOLUMN_MailOUTPUTDATA_Content,
	EDBCOLUMN_MailOUTPUTDATA_Sender,
	EDBCOLUMN_MailOUTPUTDATA_Types,
	EDBCOLUMN_MailOUTPUTDATA_Ids,
	EDBCOLUMN_MailOUTPUTDATA_Nums,
};

#define		MAIL_TITLE_LEN		255
#define		MAIL_CONTENT_LEN	3000
#define		MAIL_SENDER_LEN		255

const BSLib::Database::SDbColumn g_mailOutputDataColumn[] = {
	{ "AccountID",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY		}, //0
	{ "ZoneID",				BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		}, //1
	{ "RoleIndex",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		}, //2
	{ "MailID",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_INDEX		}, //3
	{ "MailType",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},
	{ "SystemMail",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},
	{ "IsRead",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},
	{ "IsGet",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},
	{ "TimeStamp",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},
	{ "Title",				BSLib::Database::EDT_STRING,	0,						BSLib::Database::EDF_NULL		},
	{ "Content",			BSLib::Database::EDT_STRING,	0,						BSLib::Database::EDF_NULL		},
	{ "Sender",				BSLib::Database::EDT_STRING,	0,						BSLib::Database::EDF_NULL		},
	{ "Types",				BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "Ids",				BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "Nums",				BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "",					BSLib::Database::EDT_NULL,		0,						BSLib::Database::EDF_NULL		}
};


enum EDBColumnIndexRoleMailInputData
{
	EDBCOLUMN_ROLEMAILINPUTDATA_AccountID = 0,
	EDBCOLUMN_ROLEMAILINPUTDATA_ZoneID,
	EDBCOLUMN_ROLEMAILINPUTDATA_RoleIndex,
	EDBCOLUMN_ROLEMAILINPUTDATA_MailID,
	EDBCOLUMN_ROLEMAILINPUTDATA_MailType,
	EDBCOLUMN_ROLEMAILINPUTDATA_SystemMail,
	EDBCOLUMN_ROLEMAILINPUTDATA_IsRead,
	EDBCOLUMN_ROLEMAILINPUTDATA_IsGet,
	EDBCOLUMN_ROLEMAILINPUTDATA_TimeStamp,
	EDBCOLUMN_ROLEMAILINPUTDATA_Title,
	EDBCOLUMN_ROLEMAILINPUTDATA_Content,
	EDBCOLUMN_ROLEMAILINPUTDATA_Sender,
	EDBCOLUMN_ROLEMAILINPUTDATA_Types,
	EDBCOLUMN_ROLEMAILINPUTDATA_Ids,
	EDBCOLUMN_ROLEMAILINPUTDATA_Nums,
};


const BSLib::Database::SDbColumn g_roleMailInputDataColumn[] = {
	{ "AccountID",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY		},//0
	{ "ZoneID",				BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		},//1
	{ "RoleIndex",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		},//2
	{ "MailID",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_INDEX		},//3
	{ "MailType",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},
	{ "SystemMail",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},
	{ "IsRead",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},
	{ "IsGet",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},
	{ "TimeStamp",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},
	{ "Title",				BSLib::Database::EDT_STRING,	0,						BSLib::Database::EDF_NULL		},
	{ "Content",			BSLib::Database::EDT_STRING,	0,						BSLib::Database::EDF_NULL		},
	{ "Sender",				BSLib::Database::EDT_STRING,	0,						BSLib::Database::EDF_NULL		},
	{ "Types",				BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "Ids",				BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "Nums",				BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "",					BSLib::Database::EDT_NULL,		0,						BSLib::Database::EDF_NULL		}
};


enum EDBColumnIndexRoleMailConfigData
{
	EDBCOLUMN_ROLEMAILCONFIGDATA_AccountID = 0,
	EDBCOLUMN_ROLEMAILCONFIGDATA_ZoneID,
	EDBCOLUMN_ROLEMAILCONFIGDATA_RoleIndex,
	EDBCOLUMN_ROLEMAILCONFIGDATA_LASTESTSYSTEMMAILID,
	EDBCOLUMN_ROLEMAILCONFIGDATA_LASTESTSELFMAILID,
};

const BSLib::Database::SDbColumn g_roleMailConfigDataColumn[] = {
	{ "AccountID",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY		},//0
	{ "ZoneID",					BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		},//1
	{ "RoleIndex",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		},//2
	{ "LastestSystemMailID",	BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},
	{ "LastestSelfMailID",		BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},
	{ "",						BSLib::Database::EDT_NULL,		0,						BSLib::Database::EDF_NULL		}
};


struct SRoleMailConfigData
{
	SRoleMailConfigData()
	{
		m_accountID = 0;
		m_zoneID = 0;
		m_roleIndex = 0;
		m_lastestSystemMailID = 0;
		m_lastestSelfMailID = 0;
	}
	
	bool serializeTo(BSLib::Utility::CStream& a_stream){
		a_stream << m_accountID;
		a_stream << m_zoneID;
		a_stream << m_roleIndex;
		a_stream << m_lastestSystemMailID;
		a_stream << m_lastestSelfMailID;
		return true;
	}


	bool serializeFrom(BSLib::Utility::CStream& a_stream){
		a_stream >> m_accountID;
		a_stream >> m_zoneID;
		a_stream >> m_roleIndex;
		a_stream >> m_lastestSystemMailID;
		a_stream >> m_lastestSelfMailID;
		return true;
	}

	std::string getDBKey() const
	{
		std::string key;
		key.append((char*)&m_accountID, sizeof(m_accountID));
		key.append((char*)&m_zoneID, sizeof(m_zoneID));
		key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
		return key;
	}


	GFLib::AccountID m_accountID;
	GFLib::ZoneID m_zoneID;
	BSLib::uint32 m_roleIndex;
	BSLib::uint64 m_lastestSystemMailID;
	BSLib::uint64 m_lastestSelfMailID;	
};


#ifdef WIN32
#pragma pack (pop) 
#else
#pragma pack ()
#endif


}//DB

}//MailSystem

}//GSLib

#endif//__GSLIB_MAILSYSTEM_DB_TABLEMAILDB_H__

