#ifndef __GSLIB_EQUIPSYSTEM_DB_TABLEEQUIPDB_H__
#define __GSLIB_EQUIPSYSTEM_DB_TABLEEQUIPDB_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/dbTableID.h>
#include <GSLib/equipSystem/GM/equipAttributeGM.h>

namespace GSLib
{

namespace EquipSystem
{

namespace DB
{

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

enum EDBColumnIndexEquipData
{
	EDBCOLUMN_EQUIPDATA_ACCOUNTID = 0,
	EDBCOLUMN_EQUIPDATA_ZoneID,
	EDBCOLUMN_EQUIPDATA_RoleIndex,
    EDBCOLUMN_EQUIPDATA_EquipIndex,
	EDBCOLUMN_EQUIPDATA_EquipTPID,
	EDBCOLUMN_EQUIPDATA_EquipLevel,
	EDBCOLUMN_EQUIPDATA_EquipAddLevel,
	EDBCOLUMN_EQUIPDATA_EquipQuality,
	EDBCOLUMN_EQUIPDATA_EquipStatus,
	EDBCOLUMN_EQUIPDATA_ResetSum,
    EDBCOLUMN_EQUIPDATA_EquipWhiteGemsCount,
    EDBCOLUMN_EQUIPDATA_EquipGreenGemsCount,
    EDBCOLUMN_EQUIPDATA_EquipBlueGemsCount,
    EDBCOLUMN_EQUIPDATA_EquipPurpleGemsCount,
    EDBCOLUMN_EQUIPDATA_EquipOrangeGemsCount,
	EDBCOLUMN_EQUIPDATA_EquipAttr,
	EDBCOLUMN_EQUIPDATA_EquipAttachAttr,
	EDBCOLUMN_EQUIPDATA_EquipAddAttr,
	EDBCOLUMN_EQUIPDATA_EquipSlotCount,
	EDBCOLUMN_EQUIPDATA_EquipGem1TPID,
	EDBCOLUMN_EQUIPDATA_EquipGem2TPID,
	EDBCOLUMN_EQUIPDATA_EquipGem3TPID,
	EDBCOLUMN_EQUIPDATA_EquipGem4TPID,
};

const BSLib::Database::SDbColumn g_roleEquipDataColumn[] = {
	{ "AccountID",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY		},//0
	{ "ZoneID",					BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		},//1
	{ "RoleIndex",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		},//2
	{ "EquipIndex",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_INDEX		},//2
    { "EquipTPID",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},//3
	{ "EquipLevel",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},//4
	{ "EquipAddLevel",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},//4
	{ "EquipQuality",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},//4
	{ "EquipStatus",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},//4
	{ "ResetSum",			    BSLib::Database::EDT_FLOAT,	    sizeof(float),	        BSLib::Database::EDF_NULL		},//4
	{ "EquipWhiteGemsCount",    BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},//4
	{ "EquipGreenGemsCount",    BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},//4
	{ "EquipBlueGemsCount",     BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},//4
	{ "EquipPurpleGemsCount",   BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},//4
	{ "EquipOrangeGemsCount",   BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},//4
    { "EquipAttr",			    BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},//4
    { "EquipAttachAttr",		BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},//4
    { "EquipAddAttr",		    BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},//4
	{ "SlotCount",			    BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},//5
	{ "EquipGem1TPID",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},//5
	{ "EquipGem2TPID",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},//5
	{ "EquipGem3TPID",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},//5
	{ "EquipGem4TPID",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},//5
	{ "",						BSLib::Database::EDT_NULL,		0,						BSLib::Database::EDF_NULL		}
};

struct SRoleKey
{
	SRoleKey()
	{
		m_accountID = 0;
		m_zoneID = 0;
		m_roleIndex = 0;
	}
	GFLib::AccountID m_accountID;
	GFLib::ZoneID m_zoneID;
	BSLib::uint32 m_roleIndex;
};

struct SRoleEquipData //: public GSLib::PlayerSystem::DB::CRoleKey
{
	GFLib::AccountID m_accountID;
	GFLib::ZoneID m_zoneID;
	GSLib::RoleIndex m_roleIndex;
	BSLib::uint32 m_equipID;
	BSLib::uint32 m_equipTPID;
	BSLib::uint32 m_equipLevel;
	BSLib::uint32 m_equipAddLevel;
	BSLib::uint32 m_equipQuality;
	BSLib::uint32 m_equipStatus;
    float m_resetSum;
    BSLib::uint64 m_equipColorGemsCount[EQUIP_COLOR_GEMS_COUNT];
    SBattleAttribute m_equipAttr;
    CAttachAttr m_equipAttachAttr;
    SBattleAttribute m_equipAddAttr;

    BSLib::uint32 m_slotCount;
	BSLib::uint32 m_slotGemTPID[4];
	SRoleEquipData()
	{
		m_accountID = 0;
		m_zoneID = 0;
		m_roleIndex = 0;
		m_equipID = 0;
		m_equipTPID = 0;
		m_equipLevel = 0;
		m_equipAddLevel = 0;
		m_equipQuality = 0;
        for(int i=0;i<EQUIP_COLOR_GEMS_COUNT;++i){
            m_equipColorGemsCount[i] = 0;
        }
        m_equipStatus= GM::EQUIP_STATUS_ON;
        m_slotCount = 0;
        m_resetSum = 0.0f;
		for(int i=0;i<4;++i){
           m_slotGemTPID[i] = 0;
		}
	}

	bool serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_accountID;
		stream << m_zoneID;
		stream << m_roleIndex;

		stream << m_equipID;
		stream << m_equipTPID;
		stream << m_equipLevel;

		stream << m_equipAddLevel;
		stream << m_equipQuality;
        BSLib::uint32 equipStatus = (BSLib::uint32)m_equipStatus;
        stream << equipStatus;
		stream << m_resetSum;
        for(int i=0;i<EQUIP_COLOR_GEMS_COUNT;++i){
            stream << m_equipColorGemsCount[i];
        }
        BSLib::uint32 buffSize = sizeof(SBattleAttribute);
        stream << buffSize; 
        m_equipAttr.serializeTo(stream);
        m_equipAttachAttr.serializeToDB(stream);
        stream << buffSize; 
        m_equipAddAttr.serializeTo(stream);

        stream << m_slotCount;
		for(int i=0;i<4;++i){
			stream << m_slotGemTPID[i];
		}
		return true;
	}

	bool serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_accountID;
		stream >> m_zoneID;
		stream >> m_roleIndex;

		stream >> m_equipID;
		stream >> m_equipTPID;
		stream >> m_equipLevel;

		stream >> m_equipAddLevel;
		stream >> m_equipQuality;
        BSLib::uint32 equip_status = 0;
		stream >> equip_status;
        m_equipStatus = (GM::EEquipStatus)equip_status;
		stream >> m_resetSum;
        for(int i=0;i<EQUIP_COLOR_GEMS_COUNT;++i){
            stream >> m_equipColorGemsCount[i];
        }
        BSLib::uint32 buffSize = 0;
        stream >> buffSize;
        if (buffSize <= 0) {
            return true;
        }
        if (buffSize > stream.readSize()) {
            return false;
        }
        m_equipAttr.serializeFrom(stream);
        m_equipAttachAttr.serializeFromDB(stream);
        stream >> buffSize;
        if (buffSize <= 0) {
            return true;
        }
        if (buffSize > stream.readSize()) {
            return false;
        }
        m_equipAddAttr.serializeFrom(stream);

        stream >> m_slotCount;
		for(int i=0;i<4;++i){
			stream >> m_slotGemTPID[i];
		}
		return true;
	}

    void clearEquipData()
    {
        m_accountID = 0;
        m_zoneID = 0;
        m_roleIndex = 0;
        m_equipID = 0;
        m_equipTPID = 0;
        m_equipLevel = 0;
        m_equipAddLevel = 0;
        m_equipQuality = 0;
        m_equipStatus= GM::EQUIP_STATUS_ON;
        m_equipAttr.cleanAttr();
        m_equipAttachAttr.cleanAttr();
        m_equipAddAttr.cleanAttr();
        m_slotCount = 0;
        m_resetSum = 0.0f;
        for(int i=0;i<EQUIP_COLOR_GEMS_COUNT;++i){
            m_equipColorGemsCount[i] = 0;
        }
        for(int i=0;i<4;++i){
            m_slotGemTPID[i] = 0;
        }
    }
};
 
#ifdef WIN32
#pragma pack (pop) 
#else
#pragma pack ()
#endif

class CRoleEquipData
{
public:
	std::vector<SRoleEquipData> m_roleEquipList;
public:
	bool serializeTo(BSLib::Utility::CStream& stream) const;
	bool serializeFrom(BSLib::Utility::CStream& stream);
};

}//DB

}//EquipSystem



}//GSLib

#endif//__GSLIB_EQUIPSYSTEM_DB_TABLEEQUIPDB_H__

