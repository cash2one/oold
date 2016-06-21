#ifndef __GSLIB_ACTIVITYSYSTEM_DB_TABLEACTIVITYDB_H__
#define __GSLIB_ACTIVITYSYSTEM_DB_TABLEACTIVITYDB_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/dbTableID.h>

namespace GSLib
{

namespace ActivitySystem
{

namespace DB
{

const BSLib::Database::SDbColumn g_roleAttendenceTableColumn[] = 
{
	{"AccountID",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_KEY },
	{"ZoneID",								BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_KEY },
	{"RoleIndex",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_KEY },
	{"PrizeTableID",						BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"StartTime",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_NULL},
	{"LastSignInTime",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_NULL},
	{"AttendenceCount",				BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_NULL},
	{ "",										BSLib::Database::EDT_NULL, 0, BSLib::Database::EDF_NULL	}
};

const BSLib::Database::SDbColumn g_roleDrawCardData[] = 
{
	{"AccountID",												BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_KEY },
	{"ZoneID",													BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_KEY },
	{"RoleIndex",												BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_KEY },
	{"curFreeGoldDrawCardCount",					BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL },
	{"LastFreeGoldDrawCardCountResetTime",	BSLib::Database::EDT_INT32, sizeof(BSLib::int32), BSLib::Database::EDF_NULL },
	{"LastGoldDrawCardTime",							BSLib::Database::EDT_INT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"LastDiamondDrawCardTime",					BSLib::Database::EDT_INT32, sizeof(BSLib::uint64), BSLib::Database::EDF_NULL},
	{ "",															BSLib::Database::EDT_NULL, 0, BSLib::Database::EDF_NULL}
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CRoleAttendenceDataDB:public GSLib::PlayerSystem::DB::CRoleKey
{
public:
public:
	CRoleAttendenceDataDB();
	~CRoleAttendenceDataDB();
public:
	std::string getDBKey() const;
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const;
	bool _serializeFrom(BSLib::Utility::CStream& stream);
public:
	BSLib::uint32 m_prizeTableID;
	BSLib::uint64 m_startTime;
	BSLib::uint64 m_lastSignInTime;
	BSLib::uint32 m_attendenceCount;
};

////////////////////////////////////////////////////////////////////////////////////////////////
class CRoleDrawCardDataDB:public GSLib::PlayerSystem::DB::CRoleKey
{
public:
public:
	CRoleDrawCardDataDB();
	~CRoleDrawCardDataDB();
public:
	std::string getDBKey() const;
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const;
	bool _serializeFrom(BSLib::Utility::CStream& stream);
public:
	BSLib::uint32 m_curFreeGoldDrawCardCount;
	BSLib::int32 m_lastFreeGoldDrawCardCountResetTime;
	BSLib::int32 m_lastGoldDrawCardTime;
	BSLib::int32 m_lastDiamondDrawCardTime;
};


}//DB

}

}//GSLib

#endif

