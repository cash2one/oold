//////////////////////////////////////////////////////////////////////
//	created:	2014/12/6
//	filename: 	GSLib\activitySystem\GM\activityData.cpp
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////

#include <BSLib/utility/dateTime.h>
#include <GSLib/activitySystem/GM/activityData.h>
#include <GSLib/activitySystem/GM/activitySystemDataMgr.h>
#include <GSLib/activitySystem/GM/activitySystemDefine.h>

namespace GSLib
{

namespace ActivitySystem
{

namespace GM
{

CAttendenceAttr::CAttendenceAttr()
:m_days(0)
,m_emoticonID(0)
,m_isSpecialPrize(0)
{
}

CAttendenceAttr::~CAttendenceAttr()
{

}

BSLib::uint32 CAttendenceAttr::getDays() const
{
	return m_days;
}

BSLib::uint32 CAttendenceAttr::getEmoticonID() const
{
	return m_emoticonID;
}

BSLib::uint32 CAttendenceAttr::isSpecialPrize() const
{
	return m_isSpecialPrize;
}

const std::vector<GSLib::ItemSystem::GM::CPrizeItem> & CAttendenceAttr::getPrizeItems() const
{
	return m_vecPrizeItems;
}

void CAttendenceAttr::serializeTo(BSLib::Utility::CStream &stream) const
{
	std::vector<GSLib::ItemSystem::GM::CPrizeItem> m_vecPrizeItems;
	stream << m_days;
	stream << m_emoticonID;
	stream << (BSLib::int8)(m_isSpecialPrize ? 1 : 0);
	stream << (BSLib::uint16)m_vecPrizeItems.size();
	for (std::vector<GSLib::ItemSystem::GM::CPrizeItem>::iterator itr = m_vecPrizeItems.begin(); itr != m_vecPrizeItems.end(); ++itr) {
		itr->serializeTo(stream);
	}
}


///////////////////////////////////////////////////////////////////////////////////////
CRoleAttendenceData::CRoleAttendenceData()
:m_prizeTableID(0)
,m_startTime(0)
,m_endTime(0)
,m_lastSignInTime(0)
,m_attendenceCount(0)
{
	;
}

CRoleAttendenceData::~CRoleAttendenceData()
{
	;
}

///////////////////////////////////////////////////////////////////////////////////////
CRoleDrawCardData::CRoleDrawCardData()
: m_lastDailyFreeGoldDrawCardCountResetTime(0)
,m_curFreeGoldDrawCardCount(0) 
,m_lastGoldDrawCardTime(0)
,m_lastDiamondDrawCardTime(0)
{

}

CRoleDrawCardData::~CRoleDrawCardData()
{

}

BSLib::int32 CRoleDrawCardData::getLastDailyFreeGoldDrawCardCountResetTime() const
{
	return m_lastDailyFreeGoldDrawCardCountResetTime;
}

bool CRoleDrawCardData::isGoldDrawCardFree() const
{
	return BSLib::Utility::CDateTime::getCurrentTime().getSeconds() >= m_lastGoldDrawCardTime + MAX_FREE_GOLD_DRAW_CARD_TIME;	
}

bool CRoleDrawCardData::isDiamondDrawCardFree() const
{
	return BSLib::Utility::CDateTime::getCurrentTime().getSeconds() >= m_lastDiamondDrawCardTime + MAX_FREE_DIAMOND_DRAW_CARD_TIME;	
}

void CRoleDrawCardData::onDailyFreeGoldDrawCardCountReset()
{
	m_curFreeGoldDrawCardCount = 0;
	m_lastDailyFreeGoldDrawCardCountResetTime = (BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
}

///////////////////////////////////////////////////////////////////////////////////////
CPetCardInfo::CPetCardInfo()
:m_petTPID(0)
,m_level(0)
,m_petWeight(0)
,m_petPieceTPID(0)
,m_petPieceCount(0)
,m_petPieceWeight(0)
{

}

CPetCardInfo::~CPetCardInfo()
{

}

///////////////////////////////////////////////////////////////////////////////////////
CCardLevelWeightBonus::CCardLevelWeightBonus()
:m_para(0)
{

}

CCardLevelWeightBonus::~CCardLevelWeightBonus()
{

}

///////////////////////////////////////////////////////////////////////////////////////
CDrawWeightItem::CDrawWeightItem()
:m_isPet(false)
,m_TPID(0)
,m_weight(0)
,m_count(0)
{

}

CDrawWeightItem::~CDrawWeightItem()
{

}

///////////////////////////////////////////////////////////////////////////////////////
CRolledItem::CRolledItem()
:m_isPet(false)
,m_TPID(0)
,m_count(0)
{

}

CRolledItem::~CRolledItem()
{

}

void CRolledItem::serialzeTo(BSLib::Utility::CStream & stream) const
{
	BSLib::int8 result = m_isPet ? (BSLib::int8)1 : (BSLib::int8)0;
	stream << result;
	stream << m_TPID;
	stream << m_count;
}

///////////////////////////////////////////////////////////////////////////////////////
CDrawItemPool::CDrawItemPool()
:m_totalWeight(0)
{

}

CDrawItemPool::~CDrawItemPool()
{

}


} //GM

} //ActivitySystem

} //GSLib
