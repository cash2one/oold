#ifndef __GSLIB_PLAYERSYSTEM_DB_TABLEPLAYERDB_H__
#define __GSLIB_PLAYERSYSTEM_DB_TABLEPLAYERDB_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/dbTableID.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace DB
{
class CRoleSkillData;
#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////

enum EDBColumnIndexPlayerData
{
    EDBCOLUMN_PLAYERDATA_AccountID = 0,
    EDBCOLUMN_PLAYERDATA_ZoneID,
    EDBCOLUMN_PLAYERDATA_CurrentRoleIndex,
    EDBCOLUMN_PLAYERDATA_VIPScore,
    EDBCOLUMN_PLAYERDATA_MaxRoleIndex,
    EDBCOLUMN_PLAYERDATA_RegisterTime,
};

const BSLib::Database::SDbColumn g_playerDataColumn[] = {
    { "AccountID",          BSLib::Database::EDT_UINT64,    sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY		},
    { "ZoneID",             BSLib::Database::EDT_UINT16,    sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		},
    { "CurrentRoleIndex",   BSLib::Database::EDT_INT32,	    sizeof(BSLib::int32),	BSLib::Database::EDF_NULL		},
    { "VIPScore",           BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},
    { "MaxRoleIndex",       BSLib::Database::EDT_INT32,	    sizeof(BSLib::int32),	BSLib::Database::EDF_NULL		},
    { "",                   BSLib::Database::EDT_NULL,      0,                      BSLib::Database::EDF_NULL       }
};

struct SPlayerData
{
    SPlayerData()
    {
        m_accountID        = 0;
        m_zoneID           = 0;
        m_currentRoleIndex = GSLib::INVALID_ROLEINDEX;
        m_vipScore         = 0;
        m_maxRoleIndex     = GSLib::INVALID_ROLEINDEX;
    }

    GFLib::AccountID m_accountID;
    GFLib::ZoneID    m_zoneID;
    GSLib::RoleIndex m_currentRoleIndex;
    BSLib::uint32    m_vipScore;
    GSLib::RoleIndex m_maxRoleIndex;
};

enum EDBColumnIndexRoleNameData
{
    EDBCOLUMN_ROLENAMEDATA_RoleID = 0,
    EDBCOLUMN_ROLENAMEDATA_RoleName,
};

const BSLib::Database::SDbColumn g_roleNameDataColumn[] = {
    { "RoleID",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	        BSLib::Database::EDF_NULL               },
    { "RoleName",		BSLib::Database::EDT_VARCHAR,	GSLIB_TEXT_MAX_ROLE_NAME + 1,	BSLib::Database::EDF_KEY                },
    { "",		        BSLib::Database::EDT_NULL,      0,                              BSLib::Database::EDF_NULL               }
};

struct SRoleNameData
{
    SRoleNameData()
    {
        m_roleID = 0;
    }

    GSLib::RoleID m_roleID;
    char m_roleName[GSLIB_TEXT_MAX_ROLE_NAME + 1];
};


////////////////////////////////////////////////////////////////////////////////////////////////

enum EDBColumnIndexPRoleData
{
    EDBCOLUMN_ROLEDATA_AccountID = 0,
    EDBCOLUMN_ROLEDATA_ZoneID = 1,
    EDBCOLUMN_ROLEDATA_RoleIndex = 2,
    EDBCOLUMN_ROLEDATA_RoleName = 3,
    EDBCOLUMN_ROLEDATA_RoleTPID = 4,

    EDBCOLUMN_ROLEDATA_RoleID = 5,
    EDBCOLUMN_ROLEDATA_RoleEXP = 6,
    EDBCOLUMN_ROLEDATA_Vitality = 7,
    EDBCOLUMN_ROLEDATA_Gold = 8,
    EDBCOLUMN_ROLEDATA_ChargeDiamond = 9,
    EDBCOLUMN_ROLEDATA_BindDiamond = 10,

    EDBCOLUMN_ROLEDATA_RoleLevel,
    EDBCOLUMN_ROLEDATA_StarLevel,
    EDBCOLUMN_ROLEDATA_Quality,

    EDBCOLUMN_ROLEDATA_SkillPoint,
    EDBCOLUMN_ROLEDATA_PVPCoin,
    EDBCOLUMN_ROLEDATA_RolePOP,
    EDBCOLUMN_ROLEDATA_SceneID,

    EDBCOLUMN_ROLEDATA_Atk,
    EDBCOLUMN_ROLEDATA_Def,
    EDBCOLUMN_ROLEDATA_AtkCrift,
    EDBCOLUMN_ROLEDATA_DefCriftf,
    EDBCOLUMN_ROLEDATA_HitRate,
    EDBCOLUMN_ROLEDATA_MissRate,
    EDBCOLUMN_ROLEDATA_MaxHP,
    EDBCOLUMN_ROLEDATA_Combat,

    EDBCOLUMN_ROLEDATA_BagCount,
    EDBCOLUMN_ROLEDATA_CreateTime,
    EDBCOLUMN_ROLEDATA_LastLoginTime,
    EDBCOLUMN_ROLEDATA_LastQuitTime,
    EDBCOLUMN_ROLEDATA_LastSkillUpdateTime,
    EDBCOLUMN_ROLEDATA_LastVitalityUpdateTime,

    EDBCOLUMN_ROLEDATA_VipLevel,
    EDBCOLUMN_ROLEDATA_VipScore,
    EDBCOLUMN_ROLEDATA_ActiveDegree,

    EDBCOLUMN_ROLEDATA_TotalUseChargeDiamond,
    EDBCOLUMN_ROLEDATA_TotalUseBindDiamond,
    EDBCOLUMN_ROLEDATA_TotalChargeDiamond,

    EDBCOLUMN_ROLEDATA_InvalidFlag,
};

const BSLib::Database::SDbColumn g_roleDataColumn[] = {
    { "AccountID",          BSLib::Database::EDT_UINT64,    sizeof(BSLib::uint64),          BSLib::Database::EDF_KEY        },//0
    { "ZoneID",             BSLib::Database::EDT_UINT16,    sizeof(BSLib::uint16),          BSLib::Database::EDF_KEY        },
    { "RoleIndex",          BSLib::Database::EDT_INT32,     sizeof(BSLib::int32),           BSLib::Database::EDF_INDEX      },
    { "RoleName",           BSLib::Database::EDT_VARCHAR,   GSLIB_TEXT_MAX_ROLE_NAME + 1,   BSLib::Database::EDF_NULL       },
    { "RoleTPID",           BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),          BSLib::Database::EDF_NULL       },

    { "RoleID",             BSLib::Database::EDT_UINT64,    sizeof(BSLib::uint64),          BSLib::Database::EDF_NULL	    },//5
    { "RoleEXP",            BSLib::Database::EDT_UINT64,    sizeof(BSLib::uint64),          BSLib::Database::EDF_NULL       },
    { "Vitality",           BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),          BSLib::Database::EDF_NULL       },
    { "Gold",               BSLib::Database::EDT_UINT64,    sizeof(BSLib::uint32),          BSLib::Database::EDF_NULL       },
    { "ChargeDiamond",      BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),          BSLib::Database::EDF_NULL       },
    { "BindDiamond",        BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),          BSLib::Database::EDF_NULL       },

    { "RoleLevel",          BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),          BSLib::Database::EDF_NULL       },//10
    { "StarLevel",          BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),          BSLib::Database::EDF_NULL       },
    { "Quiality",           BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),          BSLib::Database::EDF_NULL       },
    { "SkillPoint",         BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),          BSLib::Database::EDF_NULL       },
    { "PVPCoin",            BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),          BSLib::Database::EDF_NULL       },
    { "RolePOP",            BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),          BSLib::Database::EDF_NULL       },
    { "SceneID",            BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),          BSLib::Database::EDF_NULL       },

    { "Atk",                BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),          BSLib::Database::EDF_NULL       },//23
    { "Def",	        	BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	        BSLib::Database::EDF_NULL		},

    { "AtkCrift",		    BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	        BSLib::Database::EDF_NULL		},//27
    { "DefCrift",		    BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	        BSLib::Database::EDF_NULL		},

    { "HitRate",		    BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	        BSLib::Database::EDF_NULL		},//31
    { "MissRate",		    BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	        BSLib::Database::EDF_NULL		},
    { "MaxHP",		    	BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	        BSLib::Database::EDF_NULL		},
    { "Combat",             BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	        BSLib::Database::EDF_NULL	    },

    { "BagCount",           BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	        BSLib::Database::EDF_NULL	    },//52
    { "CreateTime",         BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	        BSLib::Database::EDF_NULL		},
    { "LastLoginTime",      BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	        BSLib::Database::EDF_NULL		},
    { "LastQuitTime",       BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	        BSLib::Database::EDF_NULL		},
    { "LastSkillUpdateTime",BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	        BSLib::Database::EDF_NULL		},
    { "LastVitalityUpdateTime",BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	        BSLib::Database::EDF_NULL		},

    { "VIPLevel",           BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),      	BSLib::Database::EDF_NULL		},
    { "VIPScore",           BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),      	BSLib::Database::EDF_NULL		},
    { "ActiveDegree",       BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),      	BSLib::Database::EDF_NULL		},

    { "TotalUseChargeDiamond", BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),   	BSLib::Database::EDF_NULL		},
    { "TotalUseBindDiamond",   BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),	    BSLib::Database::EDF_NULL		},
    { "TotalChargeDiamond",    BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),	    BSLib::Database::EDF_NULL		},

    { "InvalidFlag",		BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	        BSLib::Database::EDF_NULL		},//57
    { "LightPower",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	        BSLib::Database::EDF_NULL		},
    { "HistoryMaxCombatPower",			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	        BSLib::Database::EDF_NULL		},
    { "",                   BSLib::Database::EDT_NULL,		0,						        BSLib::Database::EDF_NULL		}
};

struct STalbeRoleKey
{
	STalbeRoleKey()
	{
		m_accountID = 0;
		m_zoneID = 0;
		m_roleIndex = 0;
	}
	GFLib::AccountID m_accountID;
	GFLib::ZoneID m_zoneID;
	GSLib::RoleIndex m_roleIndex;
};

struct SRoleData : public STalbeRoleKey
{
    SRoleData()
    {
        m_roleName[0] = 0;
        m_roleTPID = 0;
        m_roleEXP = 0;
        m_vitality = 0;
        m_gold = 0;
        m_chargeDiamond = 0;
        m_bindDiamond = 0;

        m_sceneID = 0;
        m_roleLevel = 0;
        m_starLevel = 0;
        m_quality = 0;

        m_atk = 0;
        m_def = 0;
        m_atkCrift = 0;
        m_defCrift = 0;
        m_hitRate = 0;
        m_missRate = 0;
        m_maxHP = 0;
        m_combat = 0;

        m_roleID = 0;
        m_createTime = 0;
        m_lastLoginTime = 0;
        m_lastQuitTime = 0;
        m_lastSkillUpdateTime = 0;
        m_lastVitalityUpdateTime = 0;

        m_vipLevel = 0;
        m_vipScore = 0;
        m_activeDegree = 0;

        m_totalUseChargeDiamond = 0;
        m_totalUseBindDiamond = 0;
        m_totalChargeDiamond = 0;

        m_invalidFlag = 0;

		m_lightPower = 0;

		m_historyMaxCombatPower = 0;
    } 

    char m_roleName[GSLIB_TEXT_MAX_ROLE_NAME + 1];
    BSLib::uint32 m_roleTPID;
    BSLib::uint64 m_roleID;
    BSLib::uint64 m_roleEXP;
    BSLib::uint32 m_vitality;

    BSLib::uint64 m_gold;

    BSLib::uint32 m_chargeDiamond;
    BSLib::uint32 m_bindDiamond;

    BSLib::uint32 m_roleLevel;
    BSLib::uint32 m_starLevel;
    BSLib::uint32 m_quality;
    BSLib::uint32 m_skillPoint;
    BSLib::uint32 m_PVPCoin;
    BSLib::uint32 m_rolePOP;
    BSLib::uint32 m_sceneID;

    BSLib::uint32 m_atk;
    BSLib::uint32 m_def;

    BSLib::uint32 m_atkCrift;
    BSLib::uint32 m_defCrift;

    BSLib::uint32 m_hitRate;
    BSLib::uint32 m_missRate;
    BSLib::uint32 m_maxHP;
    BSLib::uint32 m_combat;

    BSLib::uint32 m_bagCount;
    BSLib::uint64 m_createTime;
    BSLib::uint64 m_lastLoginTime;
    BSLib::uint64 m_lastQuitTime;
    BSLib::uint64 m_lastSkillUpdateTime;
    BSLib::uint64 m_lastVitalityUpdateTime;

    BSLib::uint32    m_vipLevel;
    BSLib::uint32    m_vipScore;
    BSLib::uint32    m_activeDegree;

    BSLib::uint32    m_totalUseChargeDiamond;
    BSLib::uint32    m_totalUseBindDiamond;
    BSLib::uint32    m_totalChargeDiamond;

    BSLib::uint32 m_invalidFlag;

	BSLib::uint32 m_lightPower;

	BSLib::uint32 m_historyMaxCombatPower;

};

enum EDBColumnIndexVipGiftData
{
    EDBCOLUMN_VIPGIFT_AccountID = 0,
    EDBCOLUMN_VIPGIFT_ZoneID,
    EDBCOLUMN_VIPGIFT_RoleIndex,
    EDBCOLUMN_VIPGIFT_NextUpdateTime,
    EDBCOLUMN_VIPGIFT_VipGift,
};

const BSLib::Database::SDbColumn g_roleVipGiftDataColumn[] = {
    { "AccountID",      BSLib::Database::EDT_UINT64,    sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY                },//0
    { "ZoneID",	        BSLib::Database::EDT_UINT16,    sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY                },//1
    { "RoleIndex",      BSLib::Database::EDT_INT32,     sizeof(BSLib::int32),	BSLib::Database::EDF_KEY              },//2
    { "NextUpdateTime", BSLib::Database::EDT_UINT64,    sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL               },//4
    { "VipGift",        BSLib::Database::EDT_BLOB,      0,                   	BSLib::Database::EDF_NULL               },//3
    { "",               BSLib::Database::EDT_NULL,      0,                      BSLib::Database::EDF_NULL               }
};

struct SVipGift
{
    BSLib::uint32 m_vipLevel;
    BSLib::uint32 m_giftStatus;
};

struct SRoleVipGiftData
{
public:
	GFLib::AccountID m_accountID;
	GFLib::ZoneID m_zoneID;
	GSLib::RoleIndex m_roleIndex;
    BSLib::uint64 m_vipGiftRefreshTime; 
    std::vector<SVipGift> m_vipGiftList;
	SRoleVipGiftData()
	{
		m_accountID = 0;
		m_zoneID = 0;
		m_roleIndex = 0;
        m_vipGiftRefreshTime = 0;
        m_vipGiftList.clear();
	}

	bool  serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_accountID;
		stream << m_zoneID;
		stream << m_roleIndex;
		stream << m_vipGiftRefreshTime;
        BSLib::uint32 buffSize = m_vipGiftList.size() * sizeof(SVipGift);
        stream << buffSize; 
        for (BSLib::uint32 i=0; i<m_vipGiftList.size(); ++i) {
            stream << m_vipGiftList[i].m_vipLevel;
            stream << m_vipGiftList[i].m_giftStatus;
        }
		
		return true;
	}

	bool serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_accountID;
		stream >> m_zoneID;
		stream >> m_roleIndex;
        stream >> m_vipGiftRefreshTime;
        BSLib::uint32 buffSize = 0;
        stream >> buffSize;
        if (buffSize <= 0) {
            return true;
        }
        if (buffSize > stream.readSize()) {
            return false;
        }
        BSLib::uint32 count = buffSize / sizeof(SVipGift);
        m_vipGiftList.clear();
        for (BSLib::uint32 i=0; i<count; ++i) {
            SVipGift gift;
            stream >> gift.m_vipLevel;
            stream >> gift.m_giftStatus;
            m_vipGiftList.push_back(gift);
        }
		return true;
	}

	std::string getDBKey() const
	{
		std::string key;
		key.append((char*)&m_accountID, sizeof(m_accountID));
		key.append((char*)&m_zoneID, sizeof(m_zoneID));
		key.append((char*)&m_roleIndex,sizeof(m_roleIndex));
		return key;
	}

	std::string getDBIndex() const
	{
		std::string index;
		index.append((char*)&m_roleIndex, sizeof(m_roleIndex));
		return index;
	}
};
enum EDBColumnIndexBagData
{
    EDBCOLUMN_BAGDATA_AccountID = 0,
    EDBCOLUMN_BAGDATA_ZoneID,
    EDBCOLUMN_BAGDATA_RoleIndex,
    EDBCOLUMN_BAGDATA_ItemIndex,
    EDBCOLUMN_BAGDATA_ItemCount,
    EDBCOLUMN_BAGDATA_ItemType,
    EDBCOLUMN_BAGDATA_ItemTPID,
    EDBCOLUMN_BAGDATA_InstanceID,
};

const BSLib::Database::SDbColumn g_roleBagDataColumn[] = {
    { "AccountID",      BSLib::Database::EDT_UINT64,    sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY                },//0
    { "ZoneID",	        BSLib::Database::EDT_UINT16,    sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY                },//1
    { "RoleIndex",      BSLib::Database::EDT_INT32,     sizeof(BSLib::int32),	BSLib::Database::EDF_KEY                },//2
    { "ItemIndex",      BSLib::Database::EDT_INT32,     sizeof(BSLib::int32),	BSLib::Database::EDF_INDEX              },//3
    { "ItemCount",      BSLib::Database::EDT_INT32,     sizeof(BSLib::int32),	BSLib::Database::EDF_NULL               },//4
    { "ItemType",       BSLib::Database::EDT_INT32,     sizeof(BSLib::int32),	BSLib::Database::EDF_NULL               },//5
    { "ItemTPID",       BSLib::Database::EDT_INT32,     sizeof(BSLib::int32),	BSLib::Database::EDF_NULL               },//6
    { "InstanceID",     BSLib::Database::EDT_UINT32,    sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL               },//7
    { "",               BSLib::Database::EDT_NULL,      0,                      BSLib::Database::EDF_NULL               }
};


////////////////////////////////////////////////////////////////////////////////////////////////
struct SRoleBagItemData
{
public:
	GFLib::AccountID m_accountID;
	GFLib::ZoneID m_zoneID;
	GSLib::RoleIndex m_roleIndex;
	BSLib::uint32 m_index;
	BSLib::uint32 m_itemCount;           
	BSLib::uint32 m_itemType;       
	BSLib::uint32 m_itemTPID;
    BSLib::uint32 m_instanceID;        

	SRoleBagItemData()
	{
		m_accountID = 0;
		m_zoneID = 0;
		m_roleIndex = 0;
		m_index = 0;
		m_itemCount=0;
		m_itemType=0;
		m_itemTPID=0;
        m_instanceID = 0;
	}

	bool  serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_accountID;
		stream << m_zoneID;
		stream << m_roleIndex;
		stream << m_index;
		stream << m_itemCount;
		stream << m_itemType;
		stream << m_itemTPID;
        stream << m_instanceID;
		
		return true;
	}

	bool serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_accountID;
		stream >> m_zoneID;
		stream >> m_roleIndex;
		stream >> m_index;
		stream >> m_itemCount;
		stream >> m_itemType;
		stream >> m_itemTPID;
        stream >> m_instanceID;
		return true;
	}

	std::string getDBKey() const
	{
		std::string key;
		key.append((char*)&m_accountID, sizeof(m_accountID));
		key.append((char*)&m_zoneID, sizeof(m_zoneID));
		key.append((char*)&m_roleIndex,sizeof(m_roleIndex));
		return key;
	}
};


#ifdef WIN32
#pragma pack (pop) 
#else
#pragma pack ()
#endif

class CRoleKey : public STalbeRoleKey
{
public:
	bool serializeTo(BSLib::Utility::CStream& stream) const;
	bool serializeFrom(BSLib::Utility::CStream& stream);

protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		return true;
	}

	virtual bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		return true;
	}
};

class CRoleBagData
{
public:
    bool serializeTo(BSLib::Utility::CStream& stream) const;
public:
	std::vector<SRoleBagItemData> m_bagItemArray;
};
}//DB

}//DBSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_DB_TABLEPLAYERDB_H__

