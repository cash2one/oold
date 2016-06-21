#ifndef __GSLIB_DBSYSTEM_GM_DBTABLEGM_H__
#define __GSLIB_DBSYSTEM_GM_DBTABLEGM_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/dbTableID.h>
//#include <GSLib/dbSystem/dbTableID.h>

namespace GSLib
{

namespace DBSystem
{

namespace GM
{

const BSLib::Database::SDbColumn g_playerDataColumn[] = {
	{ "AccountID",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64)		},
	{ "ZoneID",				BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16)		},
	{ "CurrentRoleIndex",	BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "VIPLevel",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "",					BSLib::Database::EDT_NULL,		0							}
};

const BSLib::Database::SDbColumn g_roleDataColumn[] = {
	{ "AccountID",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64)		},
	{ "ZoneID",				BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16)		},
	{ "RoleIndex",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RoleName",			BSLib::Database::EDT_VARCHAR,	GSLIB_TEXT_MAX_ROLE_NAME + 1},
	{ "RoleType",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RoleEXP",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64)		},
	{ "RoleStr",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RoleCon",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RoleInt",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RoleDex",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RolePhyAttack",		BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RolePhyDefence",		BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RoleMagAttack",		BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RoleCritRate",		BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RoleCritDefence",	BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RoleCritDamage",		BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RoleMissRate",		BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RoleMaxHP",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RoleMaxMP",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RoleGrade",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "RoleStarLevel",		BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "PVEPower",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "Gold",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint32)		},
	{ "Diamond",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "SceneID",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32)		},
	{ "",					BSLib::Database::EDT_NULL,		0							}
};

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif



struct SPlayerData
{
	SPlayerData()
	{
		m_accountID = 0;
		m_zoneID = 0;
		m_currentRoleIndex = 0;
		m_vipLevel = 0;
	}

	GFLib::AccountID m_accountID;
	GFLib::ZoneID m_zoneID;
	BSLib::uint32 m_currentRoleIndex;
	BSLib::uint32 m_vipLevel;
};

struct SRoleData
{
	SRoleData()
	{
		m_accountID = 0;
		m_zoneID = 0;
		m_roleIndex = 0;
		m_roleName[0] = 0;
		m_roleType = 0;
		m_roleEXP = 0;
		m_roleStr = 0;
		m_roleCon = 0;
		m_roleInt = 0;
		m_roleDex = 0;
		m_rolePhyAttack = 0;
		m_rolePhyDefence = 0;
		m_roleMagAttack = 0;
		m_roleCritRate = 0;
		m_roleCritDefence = 0;
		m_roleCritDamage = 0;
		m_roleMissRate = 0;
		m_roleMaxHP = 0;
		m_roleMaxMP = 0;
		m_roleGrade = 0;
		m_roleStarLevel = 0;
		m_pvePower = 0;
		m_gold = 0;
		m_diamond = 0;
		m_sceneID = 0;
	}
	GFLib::AccountID m_accountID;
	GFLib::ZoneID m_zoneID;
	BSLib::uint32 m_roleIndex;
	char m_roleName[GSLIB_TEXT_MAX_ROLE_NAME + 1];
	BSLib::uint32 m_roleType;
	BSLib::uint64 m_roleEXP;
	BSLib::uint32 m_roleStr;
	BSLib::uint32 m_roleCon;
	BSLib::uint32 m_roleInt;
	BSLib::uint32 m_roleDex;
	BSLib::uint32 m_rolePhyAttack;
	BSLib::uint32 m_rolePhyDefence;
	BSLib::uint32 m_roleMagAttack;
	BSLib::uint32 m_roleCritRate;
	BSLib::uint32 m_roleCritDefence;
	BSLib::uint32 m_roleCritDamage;
	BSLib::uint32 m_roleMissRate;
	BSLib::uint32 m_roleMaxHP;
	BSLib::uint32 m_roleMaxMP;
	BSLib::uint32 m_roleGrade;
	BSLib::uint32 m_roleStarLevel;
	BSLib::uint32 m_pvePower;
	BSLib::uint64 m_gold;
	BSLib::uint32 m_diamond;
	BSLib::uint32 m_sceneID;
};


struct SRoleModuleBase
{
	SRoleModuleBase()
	{
		m_accountID = 0;
		m_zoneID = 0;
		m_roleIndex = 0;
	}

	GFLib::AccountID m_accountID;
	GFLib::ZoneID m_zoneID;
	BSLib::uint32 m_roleIndex;
};

#ifdef WIN32
#pragma pack (pop) 
#else
#pragma pack ()
#endif

}//GM

}//DBSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_GM_DBTABLEGM_H__

