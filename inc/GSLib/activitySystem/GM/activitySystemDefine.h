
#ifndef		__GSLIB_ACTIVITYSYSTEM_GM_ACTIVITY_SYSTEM_DEFINE_H__
#define		__GSLIB_ACTIVITYSYSTEM_GM_ACTIVITY_SYSTEM_DEFINE_H__

#include <BSLib/utility/baseDef.h>

namespace GSLib
{

namespace ActivitySystem
{

namespace GM
{
	const BSLib::uint32	MAX_SIGN_IN_PERIOD = 30;
	const BSLib::uint32 MAX_SIGN_IN_DAYS = 21;
	const BSLib::int32 MAX_FREE_GOLD_DRAW_CARD_TIME = 60 * 5;
	const BSLib::int32 MAX_FREE_DIAMOND_DRAW_CARD_TIME = 24 * 60 * 60;
	const BSLib::int32 MAX_DRAW_CARD_LEVEL = 11;
	const BSLib::int32 DRAW_CARD_COST_GOLD_PER_TIME = 3000;
	const BSLib::int32 DRAW_CARD_COST_DIAMOND_PER_TIME = 100;

	enum EDrawCardType
	{
		DRAW_CARD_TYPE_GOLD,				//½ð±Ò³é¿¨
		DRAW_CARD_TYPE_DIAMOND,       //×êÊ¯³é¿¨ 
	};

	enum EDrawCardWeightBonusType
	{
		EDRAW_CARD_WEIGHT_BONUS_TYPE_NONE = 0,	
		EDRAW_CARD_WEIGHT_BONUS_TYPE_CHARGE,	
		EDRAW_CARD_WEIGHT_BONUS_TYPE_USE_DIAMOD,
		EDRAW_CARD_WEIGHT_BONUS_TYPE_CHARGE_USE_DIAMOND_RATE,

		EDRAW_CARD_WEIGHT_BONUS_TYPE_MAX,
	};



} //GM

} //ActivitySystem

} //GSLib


#endif



