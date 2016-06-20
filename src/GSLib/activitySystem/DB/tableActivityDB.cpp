//////////////////////////////////////////////////////////////////////
//	created:	2014/12/5
//	filename: 	GSLib\activitySystem\DB\tableActivityDB.cpp
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/activitySystem/DB/tableActivityDB.h>
#include <GSLib/tracer.h>

namespace GSLib
{

namespace ActivitySystem
{

namespace DB
{

CRoleAttendenceDataDB::CRoleAttendenceDataDB()
:m_prizeTableID(0)
,m_startTime(0)
,m_lastSignInTime(0)
,m_attendenceCount(0)
{

}

CRoleAttendenceDataDB::~CRoleAttendenceDataDB()
{

}

std::string CRoleAttendenceDataDB::getDBKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
	return key;
}

bool CRoleAttendenceDataDB::_serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_prizeTableID;
	stream << m_startTime;
	stream << m_lastSignInTime;
	stream << m_attendenceCount;
	return true;
}

bool CRoleAttendenceDataDB::_serializeFrom(BSLib::Utility::CStream& stream)
{
	stream >> m_prizeTableID;
	stream >> m_startTime;
	stream >> m_lastSignInTime;
	stream >> m_attendenceCount;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CRoleDrawCardDataDB::CRoleDrawCardDataDB()
:m_curFreeGoldDrawCardCount(0) 
,m_lastFreeGoldDrawCardCountResetTime(0)
,m_lastGoldDrawCardTime(0)
,m_lastDiamondDrawCardTime(0)
{

}

CRoleDrawCardDataDB::~CRoleDrawCardDataDB()
{

}

std::string CRoleDrawCardDataDB::getDBKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
	return key;
}

bool CRoleDrawCardDataDB::_serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_curFreeGoldDrawCardCount;
	stream << m_lastFreeGoldDrawCardCountResetTime;
	stream << m_lastGoldDrawCardTime;
	stream << m_lastDiamondDrawCardTime;
	return true;
}

bool CRoleDrawCardDataDB::_serializeFrom(BSLib::Utility::CStream& stream)
{
	stream >> m_curFreeGoldDrawCardCount;
	stream >> m_lastFreeGoldDrawCardCountResetTime;
	stream >> m_lastGoldDrawCardTime;
	stream >> m_lastDiamondDrawCardTime;
	return true;
}

}//DB

}

}//GSLib