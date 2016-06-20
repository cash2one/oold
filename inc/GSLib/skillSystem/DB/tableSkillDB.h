//////////////////////////////////////////////////////////////////////
//	created:	2014/09/26
//	filename: 	GSLib\skillSystem\DB\tableSkillDB.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SKILLSYSTEM_DB_TABLESKILLDB_H__
#define __GSLIB_SKILLSYSTEM_DB_TABLESKILLDB_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/dbTableID.h>
#include <GSLib/skillSystem/GM/skill.h>

namespace GSLib
{

namespace SkillSystem
{

namespace DB
{

const BSLib::Database::SDbColumn g_roleSkillDataColumn[] = {
	{ "AccountID",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY		},//0
	{ "ZoneID",				BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		},//1
	{ "RoleIndex",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		},//2
	{ "SkillList",			BSLib::Database::EDT_BLOB,	0,						BSLib::Database::EDF_NULL		},//3
	{"SkillPos",			BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL},
	{ "",					BSLib::Database::EDT_NULL,		0,						BSLib::Database::EDF_NULL		}
};

class CRoleSkillData : public GSLib::PlayerSystem::DB::CRoleKey
{
protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BSLib::Utility::CStream& stream);
public:
	std::string getDBKey() const;
public:
	std::vector<GM::CSkill> m_vecSkill;
	std::vector<SkillTPID> m_vecSkillPos;
};

}//DB

}//SkillSystem

}//GSLib

#endif//__GSLIB_SKILLSYSTEM_DB_TABLESKILLDB_H__
