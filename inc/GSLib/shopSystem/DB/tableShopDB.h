
#ifndef __GSLIB_SHOPSYSTEM_DB_TABLESHOPDB_H__
#define __GSLIB_SHOPSYSTEM_DB_TABLESHOPDB_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/dbTableID.h>

namespace GSLib
{

namespace ShopSystem
{

namespace DB
{

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

	
enum EDBColumnIndexRoleShopData
{
	EDBCOLUMNINDEXROLESHOPDATA_ACCOUNTID,
	EDBCOLUMNINDEXROLESHOPDATA_ZONEID,
	EDBCOLUMNINDEXROLESHOPDATA_ROLEINDEX,
	EDBCOLUMNINDEXROLESHOPDATA_SHOPTYPE,
	EDBCOLUMNINDEXROLESHOPDATA_REFRESHTIME,
	EDBCOLUMNINDEXROLESHOPDATA_REFRESHIDS,
	EDBCOLUMNINDEXROLESHOPDATA_BOUGHTIDS,
	EDBCOLUMNINDEXROLESHOPDATA_BOUGHTNUMS,
	EDBCOLUMNINDEXROLESHOPDATA_PAIDREFRESHCOUNT,
};

const BSLib::Database::SDbColumn g_roleShopDataColumn[] = {
	{ "AccountID",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY		},//0
	{ "ZoneID",					BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		},//1
	{ "RoleIndex",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		},//2
	{ "ShopType",				BSLib::Database::EDT_INT32,		sizeof(BSLib::int32),	BSLib::Database::EDF_INDEX		},
	{ "RefreshTime",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},
	{ "RefreshIds",				BSLib::Database::EDT_BLOB,							0,	BSLib::Database::EDF_NULL		},
	{ "BoughtIds",				BSLib::Database::EDT_BLOB,							0,	BSLib::Database::EDF_NULL		},
	{ "BoughtNums",				BSLib::Database::EDT_BLOB,							0,	BSLib::Database::EDF_NULL		},
	{ "PaidRefreshCount",		BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},
	{ "",						BSLib::Database::EDT_NULL,		0,						BSLib::Database::EDF_NULL		}
};


struct SRoleShopData
{
	SRoleShopData()
	{
		m_accountID = 0;
		m_zoneID = 0;
		m_roleIndex = 0;
		m_shopType = 0;
		m_refreshTime = 0;
		m_paidRefreshCount = 0;
	}

	SRoleShopData(const SRoleKey& a_roleKey)
	{
		m_accountID = a_roleKey.getAccountID();
		m_zoneID = a_roleKey.getZoneID();
		m_roleIndex = a_roleKey.getIndex();
		m_shopType = 0;
		m_refreshTime = 0;
		m_paidRefreshCount = 0;
	}

	bool serializeTo(BSLib::Utility::CStream& a_stream){
		a_stream << m_accountID;
		a_stream << m_zoneID;
		a_stream << m_roleIndex;
		a_stream << m_shopType;
		a_stream << m_refreshTime;
		a_stream << m_refreshIds;
		a_stream << m_boughtIds;
		a_stream << m_boughtNums;
		a_stream << m_paidRefreshCount;
		return true;
	}


	bool serializeFrom(BSLib::Utility::CStream& a_stream){
		a_stream >> m_accountID;
		a_stream >> m_zoneID;
		a_stream >> m_roleIndex;
		a_stream >> m_shopType;
		a_stream >> m_refreshTime;
		a_stream >> m_refreshIds;
		a_stream >> m_boughtIds;
		a_stream >> m_boughtNums;
		a_stream >> m_paidRefreshCount;
		return true;
	}

	std::string getDBKey() const {
		std::string key;
		key.append((char*)&m_accountID, sizeof(m_accountID));
		key.append((char*)&m_zoneID, sizeof(m_zoneID));
		key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
		return key;
	}

	std::string getIndex(){
		std::string key;
		key.append((char*)&m_shopType, sizeof(m_shopType));
		return key;
	}
	
	void pushBought(BSLib::uint32 a_id, BSLib::uint32 a_num){
		m_boughtIds.push_back(a_id);
		m_boughtNums.push_back(a_num);
	}

	GFLib::AccountID m_accountID;
	GFLib::ZoneID m_zoneID;
	BSLib::uint32 m_roleIndex;
	BSLib::int32 m_shopType;
	BSLib::uint64 m_refreshTime;
	std::vector<BSLib::int32> m_refreshIds;
	std::vector<BSLib::int32> m_boughtIds;
	std::vector<BSLib::int32> m_boughtNums;
	BSLib::uint32 m_paidRefreshCount;
};


#ifdef WIN32
#pragma pack (pop) 
#else
#pragma pack ()
#endif


}//DB

}

}//GSLib

#endif
