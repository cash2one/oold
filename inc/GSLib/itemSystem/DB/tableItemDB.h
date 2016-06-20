//////////////////////////////////////////////////////////////////////
//	created:	2014/09/26
//	filename: 	GSLib\itemSystem\DB\tableItemDB.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_ITEMSYSTEM_DB_TABLEITEMDB_H__
#define __GSLIB_ITEMSYSTEM_DB_TABLEITEMDB_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/dbTableID.h>

namespace GSLib
{

namespace ItemSystem
{

namespace DB
{

enum EDBColumnIndexSkillData
{
	EDBCOLUMN_ITEMDATA_AccountID = 0,
	EDBCOLUMN_ITEMDATA_ZoneID,
	EDBCOLUMN_ITEMDATA_RoleIndex,
};

const BSLib::Database::SDbColumn g_roleItemDataColumn[] = {
	{ "AccountID",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY 		},//0
	{ "ZoneID",				BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		},//1
	{ "RoleIndex",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		},//2
	{ "",					BSLib::Database::EDT_NULL,		0,						BSLib::Database::EDF_NULL		}
};

class CRoleItemData : public GSLib::PlayerSystem::DB::CRoleKey
{
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BSLib::Utility::CStream& stream);

public:
	//std::vector<SkillID> m_skillList;
};

}//DB

}//ItemSystem

}//GSLib

#endif//__GSLIB_ITEMSYSTEM_DB_TABLEITEMDB_H__
