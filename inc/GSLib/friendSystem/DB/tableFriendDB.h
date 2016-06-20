
#ifndef __GSLIB_FRIENDSYSTEM_DB_TABLEFRIENDDB_H__
#define __GSLIB_FRIENDSYSTEM_DB_TABLEFRIENDDB_H__

#include <BSLib/database/dbParam.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/dbTableID.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace FriendSystem
{

namespace DB
{

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif


enum EDBColumnIndexRoleFriendData
{
	EDBCOLUMNINDEXROLEFRIENDDATA_ACCOUNTID,
	EDBCOLUMNINDEXROLEFRIENDDATA_ZONEID,
	EDBCOLUMNINDEXROLEFRIENDDATA_ROLEINDEX,
	EDBCOLUMNINDEXROLEFRIENDDATA_FRIENDS,
	EDBCOLUMNINDEXROLEFRIENDDATA_PAIDCOUNT,
	EDBCOLUMNINDEXROLEFRIENDDATA_REQUESTS,
	EDBCOLUMNINDEXROLEFRIENDDATA_REQUESTTIMES,
};

const BSLib::Database::SDbColumn g_roleFriendDataColumn[] = {
	{ "AccountID",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY		},//0
	{ "ZoneID",					BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		},//1
	{ "RoleIndex",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		},//2
	{ "Friends",				BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "PaidCount",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},
	{ "Requests",				BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "RequestTimes",			BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "",						BSLib::Database::EDT_NULL,		0,						BSLib::Database::EDF_NULL		}
};


enum EDBColumnIndexFriendPendingQueueData
{
	EDBCOLUMNINDEXFRIENDPENDINGQUEUEDATA_ACCOUNTID,
	EDBCOLUMNINDEXFRIENDPENDINGQUEUEDATA_ZONEID,
	EDBCOLUMNINDEXFRIENDPENDINGQUEUEDATA_ROLEINDEX,
	EDBCOLUMNINDEXFRIENDPENDINGQUEUEDATA_LEFT,
	EDBCOLUMNINDEXFRIENDPENDINGQUEUEDATA_LEFTADDTIME,
	EDBCOLUMNINDEXFRIENDPENDINGQUEUEDATA_TOBEDECIDED,
	EDBCOLUMNINDEXFRIENDPENDINGQUEUEDATA_TOBEDEL,
	EDBCOLUMNINDEXFRIENDPENDINGQUEUEDATA_QUASIFRIENDS,
};

const BSLib::Database::SDbColumn g_FriendPendingQueueDataColumn[] = {
	{ "AccountID",				BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_KEY		},//0
	{ "ZoneID",					BSLib::Database::EDT_UINT16,	sizeof(BSLib::uint16),	BSLib::Database::EDF_KEY		},//1
	{ "RoleIndex",				BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_KEY		},//2
	{ "LeftSpace"	,			BSLib::Database::EDT_UINT32,	sizeof(BSLib::uint32),	BSLib::Database::EDF_NULL		},
	{ "LeftAddTime",			BSLib::Database::EDT_UINT64,	sizeof(BSLib::uint64),	BSLib::Database::EDF_NULL		},
	{ "ToBeDecided",			BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "ToBeDel",				BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "QuasiFriends",			BSLib::Database::EDT_BLOB,		0,						BSLib::Database::EDF_NULL		},
	{ "",						BSLib::Database::EDT_NULL,		0,						BSLib::Database::EDF_NULL		}
};


struct SRoleFriendData
{
	SRoleFriendData()
		:m_paidCount(0)
	{
	}

	SRoleKey m_role;					
	std::vector<SRoleKey> m_friends;	// �����б�
	BSLib::uint32 m_paidCount;			// ����ĺ�������
	std::vector<SRoleKey> m_requests;	// �����б�	
	std::vector<BSLib::uint64> m_requestTimes; // �����ʱ��

	bool serializeTo(BSLib::Utility::CStream& a_stream)
	{
		a_stream << m_role.getAccountID();
		a_stream << m_role.getZoneID();
		a_stream << m_role.getIndex();
		a_stream << m_friends;
		a_stream << m_paidCount;
		a_stream << m_requests;
		a_stream << m_requestTimes;

		return true;
	}

	bool deserializeFrom(BSLib::Utility::CStream& a_stream)
	{	
		GFLib::AccountID account = 0;
		GFLib::ZoneID	zone = 0;
		RoleIndex index = 0;
		a_stream >> account;
		a_stream >> zone;
		a_stream >> index;
		m_role.setAccountID(account);
		m_role.setZoneID(zone);
		m_role.setIndex(index);
		a_stream >> m_friends;
		a_stream >> m_paidCount;
		a_stream >> m_requests;
		a_stream >> m_requestTimes;
		return true;
	}

	std::string getDBKey() const {
		std::string key;
		key.append(m_role.getDBKey());
		return key;
	}

};

  
struct SRoleFriendPendingQueueData
{
	SRoleFriendPendingQueueData()
		:m_left(0)
		,m_leftAddTime(0)
	{
	}


	SRoleKey m_role;

	// ���������Ӻ���ʱʹ��
	BSLib::uint32 m_left;					// ����ʣ������
	BSLib::uint64 m_leftAddTime;			// ���һ����Ӻ���ʱ��, �����������Ч���ж�, ����clean memory

	// ��������� ,������ߺ�ʹ��,ʹ�ú����..
	std::vector<SRoleKey> m_toBeDecided;	// �ύ�����б�
	std::vector<SRoleKey> m_tobeDel;		// ��ɾ���б�
	std::vector<SRoleKey> m_quasiFriends;	// ׼�����б�

	bool serializeTo(BSLib::Utility::CStream& a_stream)
	{
		a_stream << m_role.getAccountID();
		a_stream << m_role.getZoneID();
		a_stream << m_role.getIndex();
		a_stream << m_left;
		a_stream << m_leftAddTime;
		a_stream << m_toBeDecided;
		a_stream << m_tobeDel;
		a_stream << m_quasiFriends;

		return true;
	}

	bool deserializeFrom(BSLib::Utility::CStream& a_stream)
	{
		GFLib::AccountID account = 0;
		GFLib::ZoneID	zone = 0;
		RoleIndex index = 0;
		a_stream >> account;
		a_stream >> zone;
		a_stream >> index;
		m_role.setAccountID(account);
		m_role.setZoneID(zone);
		m_role.setIndex(index);
		a_stream >> m_left;
		a_stream >> m_leftAddTime;
		a_stream >> m_toBeDecided;
		a_stream >> m_tobeDel;
		a_stream >> m_quasiFriends;
		return true;
	}

	std::string getDBKey() const {
		std::string key;
		key.append(m_role.getDBKey());
		return key;
	}

private:
	bool	_serializeTo(std::vector<SRoleKey>& a_key, BSLib::Utility::CStream& a_stream)
	{
		BSLib::uint32 size = a_key.size();
		a_stream << size;
		for(BSLib::uint32 i = 0; i < size; i++)
		{
			a_stream << a_key[i].getAccountID();
			a_stream << a_key[i].getZoneID();
			a_stream << a_key[i].getIndex();
		}

		return true;
	}

	bool _deserializeFrom(std::vector<SRoleKey>& a_key, BSLib::Utility::CStream& a_stream)
	{
		BSLib::uint32 size = 0;
		a_stream >> size;
		for(BSLib::uint32 i = 0; i < size; i++)
		{	
			GFLib::AccountID account = 0;
			GFLib::ZoneID	zone = 0;
			RoleIndex index = 0;

			a_stream >> account;
			a_stream >> zone;
			a_stream >> index;
			a_key.push_back(SRoleKey(account, zone, index));
		}
		return true;
	}

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
