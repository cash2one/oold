#ifndef __GSLIB_ITEMSYSTEM_DB_TABLETASKDB_H__
#define __GSLIB_ITEMSYSTEM_DB_TABLETASKDB_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/dbTableID.h>
#include <GSLib/taskSystem/GM/taskSystemDefine.h>

namespace GSLib
{

namespace TaskSystem
{

namespace DB
{

const BSLib::Database::SDbColumn g_roleDailyTaskColumn[] = 
{
	{"AccountID",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_KEY },
	{"ZoneID",								BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_KEY },
	{"RoleIndex",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_KEY },
	{"TaskTPID",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_INDEX},
	{"AcceptTime",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_NULL},
	{"Count",								BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_NULL},
	{"State",								BSLib::Database::EDT_UINT8, sizeof(BSLib::uint8), BSLib::Database::EDF_NULL},
	{ "",									BSLib::Database::EDT_NULL,		0,BSLib::Database::EDF_NULL	}
};

const BSLib::Database::SDbColumn g_roleMainTaskColumn[] = 
{
	{"AccountID",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_KEY },
	{"ZoneID",								BSLib::Database::EDT_UINT16, sizeof(BSLib::uint16), BSLib::Database::EDF_KEY },
	{"RoleIndex",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_KEY },
	{"CurTaskTPID",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"CurCount",							BSLib::Database::EDT_UINT32, sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"AcceptTime",							BSLib::Database::EDT_INT64, sizeof(BSLib::uint64), BSLib::Database::EDF_NULL},
	{"State",								BSLib::Database::EDT_UINT8, sizeof(BSLib::uint8), BSLib::Database::EDF_NULL},
	{ "",									BSLib::Database::EDT_NULL,		0,BSLib::Database::EDF_NULL	}
};

const BSLib::Database::SDbColumn g_rolePetTaskColumn[] = 
{
	{"AccountID",		BSLib::Database::EDT_INT64,		sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY },
	{"ZoneID",			BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY },
	{"RoleIndex",		BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY },
	{"TaskIndex",		BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_INDEX },
	{"TaskTPID",		BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL},
	{"Color",			BSLib::Database::EDT_UINT8,		sizeof(BSLib::uint8),	BSLib::Database::EDF_NULL},
	{"AcceptTime",		BSLib::Database::EDT_INT64,		sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL},
	{"Count",			BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_NULL},
	{"State",			BSLib::Database::EDT_UINT8,		sizeof(BSLib::uint8),	BSLib::Database::EDF_NULL},
	{ "",				BSLib::Database::EDT_NULL,		0,BSLib::Database::EDF_NULL	}
};

//任务相关更新数据
const BSLib::Database::SDbColumn g_roleTaskSystemDataColumn[] = 
{
	{"AccountID",							BSLib::Database::EDT_INT64,		sizeof(BSLib::uint64), BSLib::Database::EDF_KEY },
	{"ZoneID",								BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16), BSLib::Database::EDF_KEY },
	{"RoleIndex",							BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32), BSLib::Database::EDF_KEY },
	{"taskCompletedCount",					BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32), BSLib::Database::EDF_NULL },
	{"DailyRereshNewTaskCount",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32), BSLib::Database::EDF_NULL},
	{"LastUpdateTime",						BSLib::Database::EDT_INT32,		sizeof(BSLib::int32), BSLib::Database::EDF_NULL},
	{ "",									BSLib::Database::EDT_NULL,0,	BSLib::Database::EDF_NULL		}
};


class CRoleDailyTaskDataDB : public GSLib::PlayerSystem::DB::CRoleKey
{
public:
	CRoleDailyTaskDataDB();
	~CRoleDailyTaskDataDB();
public:
	std::string getDBKey() const;
	std::string getIndexKey() const;
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool  _serializeFrom(BSLib::Utility::CStream& stream);
public:
	BSLib::uint32 m_taskTPID;
	BSLib::uint64 m_acceptTime;
	BSLib::uint16 m_count;
	GM::ETaskState m_state;
};

class CRoleMainTaskDataDB : public GSLib::PlayerSystem::DB::CRoleKey
{
public:
	CRoleMainTaskDataDB();
	~CRoleMainTaskDataDB();
public:
	std::string getDBKey() const;
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BSLib::Utility::CStream& stream);
public:
	BSLib::uint32 m_curTaskTPID;
	BSLib::uint32 m_curCount;
	BSLib::uint64 m_acceptTime;
	GM::ETaskState m_state;
};

class CRolePetTaskDataDB : public GSLib::PlayerSystem::DB::CRoleKey
{
public:
	CRolePetTaskDataDB();
	~CRolePetTaskDataDB();
public:
	std::string getDBKey() const;
	std::string getIndexKey() const;
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool  _serializeFrom(BSLib::Utility::CStream& stream);
public:
	BSLib::uint32 m_taskIndex;
	BSLib::uint32 m_taskTPID;
	GM::EPetTaskColor m_taskColor;
	BSLib::uint64 m_acceptTime;
	BSLib::uint16 m_count;
	GM::ETaskState m_state;
};

//////////////////////////////////////////////////////////////////////////////////
class CRoleTaskSystemData : public GSLib::PlayerSystem::DB::CRoleKey
{
public:
	CRoleTaskSystemData();
	~CRoleTaskSystemData();
public:
	std::string getKey() const;
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BSLib::Utility::CStream& stream);
public:
	BSLib::uint32 m_taskCompletedCount;
	BSLib::uint32 m_dailyRefreshNewTaskCount;
	BSLib::int32 m_lastUpdateTime;
};



}//DB

}//ItemSystem

}//GSLib

#endif//__GSLIB_ITEMSYSTEM_DB_TABLETASKDB_H__

