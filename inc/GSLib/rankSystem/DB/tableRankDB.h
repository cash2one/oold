
#ifndef __GSLIB_RANKSYSTEM_DB_TABLERANKDB_H__
#define __GSLIB_RANKSYSTEM_DB_TABLERANKDB_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/dbTableID.h>

namespace GSLib
{

namespace RankSystem
{

namespace DB
{

const BSLib::Database::SDbColumn g_RankPendingQueueDataColumn[] =
{
	{ "AccountID",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY		},//0
	{ "ZoneID",					BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		},//1
	{ "RoleIndex",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		},//2
	{ "Exact",					BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "Approximate"	,			BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "RefreshTime",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},
	{ "",						BSLib::Database::EDT_NULL,		0,						BSLib::Database::EDF_NULL		}
};	


const BSLib::Database::SDbColumn g_roleRankDataColumn[] =
{
	{ "AccountID",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY		},//0
	{ "ZoneID",					BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		},//1
	{ "RoleIndex",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		},//2
	{ "Power",					BSLib::Database::EDT_INT32,		sizeof(BSLib::int32),	BSLib::Database::EDF_NULL		},
	{ "",						BSLib::Database::EDT_NULL,		0,						BSLib::Database::EDF_NULL		}
};

const BSLib::Database::SDbColumn g_roleRankCNDataColumn[] =
{
	{ "AccountID",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY		},//0
	{ "ZoneID",					BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		},//1
	{ "RoleIndex",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		},//2
	{ "Infinite",				BSLib::Database::EDT_INT32,		sizeof(BSLib::int32),	BSLib::Database::EDF_NULL		},
	{ "InfiniteRefreshTime",	BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},
	{ "",						BSLib::Database::EDT_NULL,		0,						BSLib::Database::EDF_NULL		}
};	


}//DB

}

}//GSLib

#endif
