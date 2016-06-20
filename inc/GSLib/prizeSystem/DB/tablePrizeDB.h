#ifndef __GSLIB_PRIZESYSTEM_DB_TABLEPRIZEDB_H__
#define __GSLIB_PRIZESYSTEM_DB_TABLEPRIZEDB_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/dbTableID.h>
#include <GSLib/prizeSystem/GM/prizeConfig.h>

namespace GSLib
{

namespace PrizeSystem
{

namespace DB
{

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

const BSLib::Database::SDbColumn g_rolePrizeDataColumn[] = {
	{ "AccountID",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY		},//0
	{ "ZoneID",					BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		},//1
	{ "RoleIndex",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		},//2
	{ "PrizeID",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_INDEX		},
	{ "StartTime",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},
	{ "EndTime",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},
	{ "Timestamp",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},
	{ "Num",					BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},
	{ "States",					BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "Param",					BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "",						BSLib::Database::EDT_NULL,		0,						BSLib::Database::EDF_NULL		}
};


struct SRolePrizeData
{
	SRolePrizeData()
	{
		m_accountID = 0;
		m_zoneID = 0;
		m_roleIndex = 0;
		m_prizeID = 0;
		m_startTime = 0;
		m_endTime = 0;
		m_timestamp = 0;
		m_num = 0;
	}

	SRolePrizeData(const SRoleKey& a_roleKey, BSLib::uint32 a_prizeId, BSLib::uint32 a_num, BSLib::uint64 a_timestamp)
	{
		m_accountID = a_roleKey.getAccountID();
		m_zoneID = a_roleKey.getZoneID();
		m_roleIndex = a_roleKey.getIndex();
		m_prizeID = a_prizeId;
		m_timestamp = a_timestamp;
		m_num = a_num;
		m_startTime = 0;
		m_endTime = 0;
	}
	
	bool serializeTo(BSLib::Utility::CStream& a_stream){
		a_stream << m_accountID;
		a_stream << m_zoneID;
		a_stream << m_roleIndex;
		a_stream << m_prizeID;
		a_stream << m_startTime;
		a_stream << m_endTime;
		a_stream << m_timestamp;
		a_stream << m_num;

		{
			BSLib::Utility::CStream bufExact;
			bufExact << m_states.size();
			std::vector<GM::StateMachineSt>::iterator it = m_states.begin();
			for(; it != m_states.end(); ++it)
			{
				bufExact << it->type;
				bufExact << it->key;
				bufExact << it->value;
			}

			std::vector<char> sExact;
			sExact.resize(bufExact.getWritePosition());
			bufExact.read(&sExact[0], bufExact.getWritePosition());
			a_stream << sExact;
		}

		{
			a_stream << m_param;
		}

		return true;
	}


	bool serializeFrom(BSLib::Utility::CStream& a_stream){
		a_stream >> m_accountID;
		a_stream >> m_zoneID;
		a_stream >> m_roleIndex;
		a_stream >> m_prizeID;
		a_stream >> m_startTime;
		a_stream >> m_endTime;
		a_stream >> m_timestamp;
		a_stream >> m_num;

		{
			std::vector<char> sExact;
			a_stream >> sExact;

			BSLib::Utility::CStream exactStream;
			exactStream.write(&sExact[0], sExact.size());

			BSLib::uint32 size  = 0;
			exactStream >> size;
			for(BSLib::uint32 i = 0; i < size; i++)
			{
				GM::StateMachineSt st;

				exactStream >> st.type;
				exactStream >> st.key;
				exactStream >> st.value;
				m_states.push_back(st);
			}
		}

		{
			a_stream >> m_param;
		}

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
		key.append((char*)&m_prizeID, sizeof(m_prizeID));
		return key;
	}


	GFLib::AccountID m_accountID;
	GFLib::ZoneID m_zoneID;
	BSLib::uint32 m_roleIndex;
	BSLib::uint32 m_prizeID;
	BSLib::uint64 m_startTime;
	BSLib::uint64 m_endTime;
	BSLib::uint64 m_timestamp;	
	BSLib::uint32 m_num;
	std::vector<GM::StateMachineSt> m_states;
	std::vector<char> m_param; // ×Ô¶¨Òå
};


#ifdef WIN32
#pragma pack (pop) 
#else
#pragma pack ()
#endif


}//DB

}//PrizeSystem

}//GSLib

#endif
