#ifndef __GSLIB_ACHIEVESYSTEM_DB_TABLEITEMDB_H__
#define __GSLIB_ACHIEVESYSTEM_DB_TABLEITEMDB_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/dbTableID.h>
#include <GSLib/achieveSystem/baseDef.h>

namespace GSLib
{

namespace AchieveSystem
{
namespace DB
{
#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

enum EDBColumnIndexPetSkillData
{
    EDBCOLUMN_ACHIEVEDATA_AccountID = 0,
    EDBCOLUMN_ACHIEVEDATA_ZoneID,
    EDBCOLUMN_ACHIEVEDATA_RoleIndex,
    EDBCOLUMN_ACHIEVEDATA_AchieveList,
};

const BSLib::Database::SDbColumn g_roleAchieveDataColumn[] = {
    { "AccountID",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY		},//0
    { "ZoneID",				BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		},//1
    { "RoleIndex",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		},//2
    { "AchieveList",		BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},//4
    { "",					BSLib::Database::EDT_NULL,		0,						BSLib::Database::EDF_NULL		}
};

struct SAchieveItem
{
    AchieveID m_achieveID;
    BSLib::uint32 m_achieveSubType;
    EAchieveStatus m_achieveStatus;
    BSLib::uint32 m_achieveProgress;

    SAchieveItem()
    {
        m_achieveID = 0;
        m_achieveSubType = 0;
        m_achieveStatus = ACHIEVE_STATUS_DOING;
        m_achieveProgress = 0;
    }

    bool serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_achieveID;
        stream << m_achieveSubType;
        stream << m_achieveStatus;
        stream << m_achieveProgress;

        return true;
    }
    bool serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_achieveID;
        stream >> m_achieveSubType;
        stream >> m_achieveStatus;
        stream >> m_achieveProgress;

        return true;
    }
};
#ifdef WIN32
#pragma pack (pop) 
#else
#pragma pack ()
#endif


class CAchieveData :public GSLib::PlayerSystem::DB::STalbeRoleKey
{
public:
    bool serializeTo(BSLib::Utility::CStream& stream) const;
    bool serializeFrom(BSLib::Utility::CStream& stream);
public:
    std::vector<SAchieveItem> m_achieveList;
};

}//DB

}//AchieveSystem

}//GSLib

#endif//__GSLIB_ACHIEVESYSTEM_DB_TABLEITEMDB_H__

