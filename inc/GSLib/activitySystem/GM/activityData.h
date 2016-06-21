
#ifndef		__GSLIB_ACTIVITYSYSTEM_GM_ACTIVITYDATA_H__
#define		__GSLIB_ACTIVITYSYSTEM_GM_ACTIVITYDATA_H__

#include <BSLib/utility/baseDef.h>
#include <GSLib/itemSystem/GM/itemAttributeGM.h>
#include <GSLib/activitySystem/GM/activitySystemDefine.h>
#include <BSLib/utility/stream.h>
#include <vector>

namespace GSLib
{

namespace ActivitySystem
{

namespace GM
{

class CAttendenceAttr
{
public:
	CAttendenceAttr();
	~CAttendenceAttr();
public:
	BSLib::uint32 getDays() const;
	BSLib::uint32 getEmoticonID() const;
	BSLib::uint32 isSpecialPrize() const;
	const std::vector<GSLib::ItemSystem::GM::CPrizeItem> & getPrizeItems() const;
public:
	void serializeTo(BSLib::Utility::CStream &stream) const;
public:
	BSLib::uint32 m_days;
	BSLib::uint32 m_emoticonID;
	bool m_isSpecialPrize;
	std::vector<GSLib::ItemSystem::GM::CPrizeItem> m_vecPrizeItems;
};

///////////////////////////////////////////////////////////////////////////////////////
class CRoleAttendenceData
{
public:
	CRoleAttendenceData();
	~CRoleAttendenceData();
public:
	BSLib::uint32 m_prizeTableID;
	BSLib::int32 m_startTime;
	BSLib::int32 m_endTime;
	BSLib::int32 m_lastSignInTime;
	BSLib::uint32 m_attendenceCount;
};

///////////////////////////////////////////////////////////////////////////////////////
class CRoleDrawCardData
{
public:
	CRoleDrawCardData();
	~CRoleDrawCardData();
public:
	BSLib::int32 getLastDailyFreeGoldDrawCardCountResetTime() const;
	bool isGoldDrawCardFree() const;
	bool isDiamondDrawCardFree() const;
	void onDailyFreeGoldDrawCardCountReset();
public:
	BSLib::int32 m_lastDailyFreeGoldDrawCardCountResetTime;
	BSLib::uint32 m_curFreeGoldDrawCardCount;
	BSLib::int32 m_lastGoldDrawCardTime;
	BSLib::int32 m_lastDiamondDrawCardTime;
};

///////////////////////////////////////////////////////////////////////////////////////
class CPetCardInfo
{
public:
	CPetCardInfo();
	~CPetCardInfo();
public:
	BSLib::uint32 m_petTPID;
	BSLib::uint32 m_level;
	BSLib::uint32 m_petWeight;
	BSLib::uint32 m_petPieceTPID;
	BSLib::uint32 m_petPieceCount;
	BSLib::uint32 m_petPieceWeight;
};

///////////////////////////////////////////////////////////////////////////////////////
class CCardLevelWeightBonus
{
public:
	CCardLevelWeightBonus();
	~CCardLevelWeightBonus();
public:
	BSLib::uint32 m_para;
	std::vector<BSLib::uint32> m_vecBonus;
};

///////////////////////////////////////////////////////////////////////////////////////
class CDrawWeightItem
{
public:
	CDrawWeightItem();
	~CDrawWeightItem();
public:
	bool m_isPet;
	BSLib::uint32 m_TPID;
	BSLib::uint32 m_weight;
	BSLib::uint16 m_count;
};

///////////////////////////////////////////////////////////////////////////////////////
class CRolledItem
{
public:
	CRolledItem();
	~CRolledItem();
public:
	bool m_isPet;
	BSLib::uint32 m_TPID;
	BSLib::uint16 m_count;
public:
	void serialzeTo(BSLib::Utility::CStream & stream) const;
};

///////////////////////////////////////////////////////////////////////////////////////
class CDrawItemPool
{
public:
	CDrawItemPool();
	~CDrawItemPool();
public:
	BSLib::uint32 m_totalWeight;
	std::vector<CDrawWeightItem> m_vecDrawItem;
};
} //GM

} //ActivitySystem

} //GSLib


#endif



