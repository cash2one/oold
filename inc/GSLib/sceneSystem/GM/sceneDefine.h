//////////////////////////////////////////////////////////////////////
//	created:	2014/09/29
//	filename: 	GSLib\sceneSystem\GM\sceneDefine.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef		__GSLIB_SCENESYSTEM_GM_SCENEDEFINE_H__
#define		__GSLIB_SCENESYSTEM_GM_SCENEDEFINE_H__



namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

	const BSLib::uint32 C_DAILY_ARENA_CHALLENGE_TIMES = 10;				//每日挑战次数
	const BSLib::uint32 C_MAX_DAILY_ARENA_TICKET_PURCHASE_COUNT = 4;	//每日可购买门票次数
	const BSLib::uint32 C_MAX_ARENA_TICKETS_PER_PURCHASE = 5;			//每次购买门票数
	const BSLib::uint32 C_MAX_AREN_WIN_LIGHT_POWER_PRIZE = 100;			//竞技场胜利加100光子力
	const BSLib::uint32 C_MAX_AREN_LOSE_LIGHT_POWER_PRIZE = 20;			//竞技场胜利加20光子力
	const BSLib::uint32 C_ERASE_CHALLENGE_COLD_DOWN_DIAMOND_COST = 20;	//去除CD所消耗钻石数

	const BSLib::uint32 C_GET_ARENA_INFO_INTERVAL = 5;					
	const BSLib::uint32 C_ARENA_SCENE_ID = 1;
	const BSLib::uint32 C_STAGE_LEVEL_REQUIRE_STAR = 3;

	const BSLib::uint32 C_REVIVE_COUNT = 3;
	const BSLib::uint32 C_MAX_GREED_LAND_ENTRANCE_TICKETS = 10;
	const BSLib::uint32 C_GREED_LAND_TICKETSUPDATE_SECONDS = 2* 60;
	const BSLib::uint32 C_CHALLENGE_COOL_DWON_INTERVAL = 600;
	const BSLib::uint32 C_MAX_CHALLENGE_RECORD_COUNT = 50;

enum ESceneType
{
	ESCENE_TYPE_NONE = 0,
	ESCENE_TYPE_CITY,				//主城
	ESCENE_TYPE_STAGE,				//剧情关卡 精英副本 
	ESCENE_TYPE_ARENA,				//竞技场
	ESCENE_TYPE_CONTINUOUS_STAGE,	//连续闯关
	ESCENE_TYPE_RANDOM_STAGE,		//随机关卡
	ESCENE_TYPE_RANDOM_GOLD_STAGE,	//金币副本
	ESCENE_TYPE_RANDOM_EXP_STAGE,	//经验副本

	ESCENE_TYPE_MAX,
};

enum ESceneState
{
	ESCENE_NONE,
	ESCENE_BEGIN,
	ESCENE_END,
};

enum EInstanceType
{
	EINSTANCE_TYPE_NONE = 0,			//无
	EINSTANCE_TYPE_STORY,				//普通剧情副本
	EINSTANCE_TYPE_ADVANCE,				//精英副本
	EINSTANCE_TYPE_ACTIVITY,			//活动副本
	EINSTANCE_TYPE_CONTINUOUS_STAGE,	//连续闯关
	EINSTANCE_TYPE_RANDOM_STAGE,		//随机关卡
	EINSTANCE_TYPE_RANDOM_EXP_STAGE,	//经验副本
	EINSTANCE_TYPE_RANDOM_GOLD_STAGE,	//金币副本

	EINSTANCE_TYPE_MAX,					//
};

enum EMonsterDropType
{
	None,
	CertainlyDropMonster,
	RandomDropMonster,
	Boss,
	Elite,
};

enum EChallengeType
{
	ECHALLENGE_TYPE_RANKING_ROLE = 0,
	ECHALLENGE_TYPE_REVENGE,
};




} // GSLib

} // SceneSystem

} // GSLib






#endif
