#ifndef cmmhdr_h__
#define cmmhdr_h__
#include <GSLib/baseDef.h>

namespace GSLib
{
namespace RankSystem
{

enum ERankType
{	
	ERANKTYPE_ORDERED	= 1,
	ERANKTYPE_BUCKET,
	ERANKTYPE_TRANSPOSITION,
	ERANKTYPE_ORDEREDLESS
};

enum ERankId
{	
	ERANKID_BEGIN			= 0,

	ERANKID_ARENA			= 0,		// 竞技场
	ERANKID_INFINITE,					// 试炼空间
	ERANKID_PLAYER_ACTIVITY,			// 玩家活跃度
	ERANKID_POWER,						// 战斗力
	ERANKID_LEVEL,						// 等级
	ERANKID_END,		
};

struct  SRoleRank 
{
		SRoleKey		m_role;
		BSLib::int32	m_power;				// 最大战斗力

		SRoleRank()
			:m_role(0, 0, 0)
			,m_power(0)
		{

		}

		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	
			stream << m_role.getAccountID();
			stream << m_role.getZoneID();
			stream << m_role.getIndex();
			stream << m_power;
			return true;
		}

		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{	
			GFLib::AccountID account = 0;
			GFLib::ZoneID zone = 0;
			GSLib::RoleIndex index = 0;
			stream >> account;
			stream >> zone;
			stream >> index;
			m_role.setAccountID(account);
			m_role.setZoneID(zone);
			m_role.setIndex(index);
			stream >> m_power;
			return true;
		}
};

struct  SRoleRankCN 
{
	SRoleKey		m_role;

	BSLib::int32	m_infinite;				// 无限挑战总积分
	BSLib::uint64	m_infiniteRefreshTime;	// 无限挑战最后一次更新时间

	SRoleRankCN()
		:m_role(0, 0, 0)
		,m_infinite(0)
		,m_infiniteRefreshTime(0)
	{

	}

	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{	
		stream << m_role.getAccountID();
		stream << m_role.getZoneID();
		stream << m_role.getIndex();
		stream << m_infinite;
		stream << m_infiniteRefreshTime;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{	
		GFLib::AccountID account = 0;
		GFLib::ZoneID zone = 0;
		GSLib::RoleIndex index = 0;
		stream >> account;
		stream >> zone;
		stream >> index;
		m_role.setAccountID(account);
		m_role.setZoneID(zone);
		m_role.setIndex(index);
		stream >> m_infinite;
		stream >> m_infiniteRefreshTime;
		return true;
	}
};


struct SRankCell
{	
	SRankCell()
		:m_role(0, 0, 0)
		,m_pos(0)
		,m_level(0)
		,m_vip(0)
		,m_job(0)
		,m_power(0)
		,m_param(0)
	{
	}

	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{	
		stream << m_role.getAccountID();
		stream << m_role.getZoneID();
		stream << m_role.getIndex();
		stream << m_pos;
		stream << m_name;
		stream << m_level;
		stream << m_vip;
		stream << m_job;
		stream << m_power;
		stream << m_param;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{	
		GFLib::AccountID account = 0;
		GFLib::ZoneID zone = 0;
		GSLib::RoleIndex index = 0;
		stream >> account;
		stream >> zone;
		stream >> index;
		m_role.setAccountID(account);
		m_role.setZoneID(zone);
		m_role.setIndex(index);
		stream >> m_pos;
		stream >> m_name;
		stream >> m_level;
		stream >> m_vip;
		stream >> m_job;
		stream >> m_power;
		stream >> m_param;
		return true;
	}

	SRoleKey		m_role;
	BSLib::uint32	m_pos;
	std::string		m_name;
	BSLib::uint32	m_level;
	BSLib::uint32	m_vip;
	BSLib::uint32	m_job;		// 1 , 2, 3
	BSLib::uint32	m_power;
	BSLib::int32	m_param;
};


} // RankSystem
} // GSLib

#endif // cmmhdr_h__
