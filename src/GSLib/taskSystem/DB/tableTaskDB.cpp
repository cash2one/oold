//////////////////////////////////////////////////////////////////////
//	created:	2014/10/09
//	filename: 	src\GSLib\taskSystem\DB\tableTaskDB.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/taskSystem/DB/tableTaskDB.h>
#include <GSLib/tracer.h>

namespace GSLib
{

namespace TaskSystem
{

namespace DB
{

CRoleDailyTaskDataDB::CRoleDailyTaskDataDB()
:m_taskTPID(0)
,m_acceptTime(0)
,m_count(0)
,m_state(GM::ETASKSTATE_NONE)
{

}

CRoleDailyTaskDataDB::~CRoleDailyTaskDataDB()
{

}

std::string CRoleDailyTaskDataDB::getDBKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));

	return key;
}

bool CRoleDailyTaskDataDB::_serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_taskTPID;
	stream << m_acceptTime;
	stream << m_count;
	stream << (BSLib::uint8)m_state;
	return true;
}

bool CRoleDailyTaskDataDB::_serializeFrom(BSLib::Utility::CStream& stream)
{
	stream >> m_taskTPID;
	stream >> m_acceptTime;
	stream >> m_count;
	BSLib::uint8 state;
	stream >> state;
	m_state = (GM::ETaskState)state;
	return true;
}

std::string CRoleDailyTaskDataDB::getIndexKey() const
{
	std::string indexKey;
	indexKey.append((char*)&m_taskTPID, sizeof(m_taskTPID));	
	return indexKey;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CRoleMainTaskDataDB::CRoleMainTaskDataDB()
:m_curTaskTPID(0)
,m_acceptTime(0)
,m_state(GM::ETASKSTATE_NONE)
{

}

CRoleMainTaskDataDB::~CRoleMainTaskDataDB()
{

}

std::string CRoleMainTaskDataDB::getDBKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));

	return key;
}

bool CRoleMainTaskDataDB::_serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_curTaskTPID;
	stream << m_curCount;
	stream << m_acceptTime;
	stream << (BSLib::uint8)m_state;
	return true;
}

bool CRoleMainTaskDataDB::_serializeFrom(BSLib::Utility::CStream& stream)
{
	stream >> m_curTaskTPID;
	stream >> m_curCount;
	stream >> m_acceptTime;
	BSLib::uint8 state;
	stream >> state;
	m_state = (GM::ETaskState)state;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CRolePetTaskDataDB::CRolePetTaskDataDB()
:m_taskIndex(0)
,m_taskTPID(0)
,m_taskColor(GM::EPET_TASK_COLOR_NONE)
,m_acceptTime(0)
,m_count(0)
,m_state(GM::ETASKSTATE_NONE)
{

}

CRolePetTaskDataDB::~CRolePetTaskDataDB()
{

}

std::string CRolePetTaskDataDB::getDBKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));

	return key;
}

std::string CRolePetTaskDataDB::getIndexKey() const
{
	std::string indexKey;
	indexKey.append((char*)&m_taskIndex, sizeof(m_taskIndex));	
	return indexKey;
}

bool CRolePetTaskDataDB::_serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_taskIndex;
	stream << m_taskTPID;
	stream << (BSLib::uint8)m_taskColor;
	stream << m_acceptTime;
	stream << m_count;
	stream << (BSLib::uint8)m_state;
	return true;
}

bool CRolePetTaskDataDB::_serializeFrom(BSLib::Utility::CStream& stream)
{
	stream >> m_taskIndex;
	stream >> m_taskTPID;
	BSLib::uint8 color;
	stream >> color;
	m_taskColor = (GM::EPetTaskColor)color;
	stream >> m_acceptTime;
	stream >> m_count;
	BSLib::uint8 state;
	stream >> state;
	m_state = (GM::ETaskState)state;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
CRoleTaskSystemData::CRoleTaskSystemData()
:m_taskCompletedCount(0)
,m_dailyRefreshNewTaskCount(0)
,m_lastUpdateTime(0)
{

}

CRoleTaskSystemData::~CRoleTaskSystemData()
{

}

std::string CRoleTaskSystemData::getKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
	return key;
}

bool CRoleTaskSystemData::_serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_taskCompletedCount;
	stream << m_dailyRefreshNewTaskCount;
	stream << m_lastUpdateTime;
	return true;
}

bool CRoleTaskSystemData::_serializeFrom(BSLib::Utility::CStream& stream)
{
	stream >> m_taskCompletedCount;
	stream >> m_dailyRefreshNewTaskCount;
	stream >> m_lastUpdateTime;
	return true;
}

}//DB

}//TaskSystem

}//GSLib