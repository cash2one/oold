//////////////////////////////////////////////////////////////////////
//	created:	2014/10/22
//	filename: 	GSLib\sceneSystem\GM\arenaDailyPrize.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef		__GSLIB_SCENESYSTEM_GM_ARENAPRIZE_H__
#define		__GSLIB_SCENESYSTEM_GM_ARENAPRIZE_H__

#include <BSLib/utility/baseDef.h>

namespace GSLib
{
namespace SceneSystem
{

namespace GM
{

class CArenaPrize	
{
public:
	CArenaPrize(BSLib::int64 a_gold = 0, BSLib::uint32 a_diamond = 0, BSLib::uint32 a_pvpCoin = 0);
	~CArenaPrize();
public:
	BSLib::uint64 m_gold;
	BSLib::uint32 m_diamond;
	BSLib::uint32 m_pvpCoin;
};

} // GM

} // SceneSystem

} // GSLib



#endif

