#ifndef	__GSLIB_TASKSYSTEM_GM_TASKSYSTEM_DEFINE__
#define __GSLIB_TASKSYSTEM_GM_TASKSYSTEM_DEFINE__

#include <BSLib/utility/baseDef.h>

namespace GSLib
{

namespace TaskSystem
{

namespace GM
{

	const BSLib::uint32 C_MAX_DAILY_TASK_COUNT = 20;

	const BSLib::uint32 C_MAX_PET_TASK_PER_TIME = 4;

	const BSLib::uint32 C_MAX_DAILY_PET_TASK = 30;

	enum EDailyTaskType
	{
		EDAILY_TASK_TYPE_NONE = 0,
		EDAILY_TASK_TYPE_ROLE_ARENA,
		EDAILY_TASK_TYPE_STRENTHEN_EQUIPMENT,
		EDAILY_TASK_TYPE_UPGRADE_SKILL,
		EDAILY_TASK_TYPE_STRENTHEN_PET,
	};

	enum EMainTaskType
	{
		EMAIN_TASK_TYPE_NONE,
		EMAIN_TASK_TYPE_DIALOGUE,			//对白任务
		EMAIN_TASK_TYPE_INSTANCE,			//副本任务
		EMAIN_TASK_TYPE_ITEM_DROP,			//物品掉落
		EMAIN_TASK_TYPE_ITEM_KILL_MONSTER,	//扑杀怪物
	};

	enum ETaskState
	{
		ETASKSTATE_NONE = 0,	
		ETASKSTATE_ACCEPT,
		ETASKSTATE_FINISH,
		ETASKSTATE_GOT_PRIZE,	
	};

	enum EPetTaskType
	{
		EPET_TASK_TYPE_NONE = 0,	
		EPET_TASK_TYPE_STAGE,
		EPET_TASK_TYPE_KILL_MONSTER,
		EPET_TASK_TYPE_MONSTER_DROP,
		EPET_TASK_TYPE_BOSS_DROP,

	};

	enum EPetTaskColor
	{
		EPET_TASK_COLOR_NONE = 0,
		EPET_TASK_COLOR_WHITE,
		EPET_TASK_COLOR_GREEN,
		EPET_TASK_COLOR_BLUE,
		EPET_TASK_COLOR_PURPLE,
		EPET_TASK_COLOR_ORANGE,
	};

}//GM
}//TaskSystem

}//GSLib

#endif//__GSLIB_TASKSYSTEM_GM_TASKSYSTEM_DEFINE__

