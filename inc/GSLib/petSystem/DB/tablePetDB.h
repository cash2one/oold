//////////////////////////////////////////////////////////////////////
//	created:	2014/09/26
//	filename: 	GSLib\petSystem\DB\tablePetDB.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PETSYSTEM_DB_TABLEEQUIPDB_H__
#define __GSLIB_PETSYSTEM_DB_TABLEEQUIPDB_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/dbTableID.h>

namespace GSLib
{

namespace PetSystem
{

namespace DB
{

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

enum EDBColumnIndexPetData
{
    EDBCOLUMN_PETDATA_ACCOUNTID = 0,
    EDBCOLUMN_PETDATA_ZoneID,
    EDBCOLUMN_PETDATA_RoleIndex,
    EDBCOLUMN_PETDATA_HotSpringLevel,
    EDBCOLUMN_PETDATA_PetList,
};

const BSLib::Database::SDbColumn g_petDataColumn[] = {
    { "AccountID",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY		},//0
    { "ZoneID",					BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		},//1
    { "RoleIndex",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		},//2
    { "HotSpringLevel",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},//3
    { "PetList",			    BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},//6
    { "",						BSLib::Database::EDT_NULL,		0,						BSLib::Database::EDF_NULL		}
};

class CPetDBData
{
public:
    CPetDBData();
    ~CPetDBData();

    bool serializeTo(BSLib::Utility::CStream& stream) const;
    bool serializeFrom(BSLib::Utility::CStream& stream);
public:
    BSLib::uint32 m_petID;
    BSLib::uint32 m_petTPID;
    BSLib::uint32 m_friendlyLevel;
    BSLib::uint32 m_friendlyValue;
    BSLib::uint32 m_maxFriendlyValue;
    BSLib::uint32 m_petStatus;
    BSLib::uint32 m_hotSpringTaskMaxTime;
    BSLib::uint32 m_hotSpringTaskPassTime;
    BSLib::uint32 m_hotSpringType;
    BSLib::uint32 m_hotSpringTaskStatus;
    BSLib::uint32 m_hotSpringTaskType;
    BSLib::uint32 m_lastMainTaskID;
    BSLib::uint32 m_curTaskID;
    BSLib::uint64 m_lastEnterTime;       // 上次进入温泉时间
    BSLib::uint64 m_lastQuitGameTime;    // 上次离开游戏时间
    SBattleAttribute m_battleAttr;       // 初始属性固定不变
};

#ifdef WIN32
#pragma pack (pop) 
#else
#pragma pack ()
#endif


class CRolePetData :public GSLib::PlayerSystem::DB::CRoleKey
{
public:
    CRolePetData();
    ~CRolePetData();
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
    virtual bool _serializeFrom(BSLib::Utility::CStream& stream);
public:
    BSLib::uint32 m_hotSpringLevel;
	std::vector<CPetDBData> m_petList;
};

}//DB

}//PetSystem



}//GSLib

#endif//__GSLIB_PETSYSTEM_DB_TABLEEQUIPDB_H__
