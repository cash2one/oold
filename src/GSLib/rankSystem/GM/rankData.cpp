#include <GSLib/rankSystem/GM/rankData.h>

namespace GSLib
{

namespace RankSystem
{

namespace GM
{

CRankData::CRankData()
{

}

CRankData::~CRankData()
{

}

void CRankData::serializeTo(BSLib::Utility::CStream & a_stream) const
{
	a_stream << m_zoneID;
	a_stream << m_accountID;
	a_stream << m_roleIndex;
	a_stream << m_roleTPID;
	a_stream << m_roleName;
	a_stream << m_rank;
	a_stream << m_level;
	a_stream << m_combatPower;
}

}//GM

}//RankSystem

}//GSLib

