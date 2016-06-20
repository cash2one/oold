//////////////////////////////////////////////////////////////////////
//	created:	2014/08/05
//	filename: 	GSLib\dbSystem\LG\dbTableLG.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_DBSYSTEM_LG_DBTABLELG_H__
#define __GSLIB_DBSYSTEM_LG_DBTABLELG_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace DBSystem
{

namespace LG
{

const BSLib::Database::SDbColumn g_accountDataColumn[] = {
	{ "AccountID",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),					BSLib::Database::EDF_KEY},
	{ "AccountName",		BSLib::Database::EDT_VARCHAR,	GSLIB_TEXT_MAX_ACCOUNT_NAME + 1,		BSLib::Database::EDF_NULL},
	{ "AccountPassword",	BSLib::Database::EDT_VARCHAR,	GSLIB_TEXT_MAX_ACCOUNT_PASSWORD + 1,	BSLib::Database::EDF_NULL},
	{ "UniqueID",	        BSLib::Database::EDT_VARCHAR,	GSLIB_TEXT_MAX_ACCOUNT_UNIQUEID + 1,	BSLib::Database::EDF_NULL},
	{ "UniqueKey",	        BSLib::Database::EDT_VARCHAR,	GSLIB_TEXT_MAX_ACCOUNT_UNIQUEKEY+ 1,	BSLib::Database::EDF_NULL},
	{ "Channel",	        BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),					BSLib::Database::EDF_NULL},
	{ "Platform",	        BSLib::Database::EDT_VARCHAR,	GSLIB_TEXT_MAX_PLATFORM + 1,			BSLib::Database::EDF_NULL},
	{ "BindFlag",	        BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),					BSLib::Database::EDF_NULL},
	{ "RegisterTime",       BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),					BSLib::Database::EDF_NULL},
	{ "Forbidden",	        BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),					BSLib::Database::EDF_NULL},
	{ "ActivationCode",	    BSLib::Database::EDT_VARCHAR,	256,			                        BSLib::Database::EDF_NULL},
	{ "",					BSLib::Database::EDT_NULL,		0,										BSLib::Database::EDF_NULL}
};

const BSLib::Database::SDbColumn g_accountDataInsertColumn[] = {
	{ "AccountName",		BSLib::Database::EDT_VARCHAR,	GSLIB_TEXT_MAX_ACCOUNT_NAME + 1	},
	{ "AccountPassword",	BSLib::Database::EDT_VARCHAR,	GSLIB_TEXT_MAX_ACCOUNT_PASSWORD + 1	},
	{ "UniqueID",	        BSLib::Database::EDT_VARCHAR,	GSLIB_TEXT_MAX_ACCOUNT_UNIQUEID + 1	},
	{ "UniqueKey",	        BSLib::Database::EDT_VARCHAR,	GSLIB_TEXT_MAX_ACCOUNT_UNIQUEKEY+ 1	},
	{ "Channel",	        BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)	},
	{ "Platform",	        BSLib::Database::EDT_VARCHAR,	GSLIB_TEXT_MAX_PLATFORM + 1	},
	{ "BindFlag",	        BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)	},
    { "RegisterTime",       BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64)},
	{ "Forbidden",	        BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)	},
    { "ActivationCode",	    BSLib::Database::EDT_VARCHAR,	256,		            },
	{ "",					BSLib::Database::EDT_NULL,		0							}
};


const BSLib::Database::SDbColumn g_ActivationCodeDataColumn[] = {
    { "ID",	        BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),					BSLib::Database::EDF_KEY},
    { "Code",	    BSLib::Database::EDT_VARCHAR,	256,			                        BSLib::Database::EDF_NULL},
    { "Used",	    BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),					BSLib::Database::EDF_NULL},
    { "",		    BSLib::Database::EDT_NULL,		0,										BSLib::Database::EDF_NULL}
};


#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

struct SAccountData
{	
	SAccountData():m_forbidden(0){}
	GFLib::AccountID m_accountID;
	char m_accountName[GSLIB_TEXT_MAX_ACCOUNT_NAME + 1];
	char m_accountPassword[GSLIB_TEXT_MAX_ACCOUNT_PASSWORD + 1];
	char m_uniqueID[GSLIB_TEXT_MAX_ACCOUNT_UNIQUEID + 1];
	char m_uniqueKey[GSLIB_TEXT_MAX_ACCOUNT_UNIQUEKEY + 1];
	BSLib::uint32 m_channelID;
	char m_platform[GSLIB_TEXT_MAX_PLATFORM + 1];
	BSLib::uint32 m_bindFlag;
  BSLib::uint64 m_registerTime;
	BSLib::uint32 m_forbidden;
  char m_activationCode[256];
};

struct SAccountInsertData
{	
	SAccountInsertData():m_forbidden(0){}
	char m_accountName[GSLIB_TEXT_MAX_ACCOUNT_NAME + 1];
	char m_accountPassword[GSLIB_TEXT_MAX_ACCOUNT_PASSWORD + 1];
	char m_uniqueID[GSLIB_TEXT_MAX_ACCOUNT_UNIQUEID + 1];
	char m_uniqueKey[GSLIB_TEXT_MAX_ACCOUNT_UNIQUEKEY + 1];
	BSLib::uint32 m_channelID;
	char m_platform[GSLIB_TEXT_MAX_PLATFORM + 1];
	BSLib::uint32 m_bindFlag;
  BSLib::uint64 m_registerTime;
	BSLib::uint32 m_forbidden;
  char m_activationCode[256];
};

struct SActivationCodeData
{    
    BSLib::uint32 m_id;
    char m_code[256];
    BSLib::uint32 m_used;
};

#ifdef WIN32
#pragma pack (pop) 
#else
#pragma pack ()
#endif

}//LG

}//DBSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_LG_DBTABLELG_H__
