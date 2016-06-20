using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public enum EMainTaskType
    {
        EMAIN_TASK_TYPE_NONE = 0,
        EMAIN_TASK_TYPE_DIALOGUE,			//对白任务
        EMAIN_TASK_TYPE_INSTANCE,			//副本任务
        EMAIN_TASK_TYPE_ITEM_DROP,			//物品掉落
        EMAIN_TASK_TYPE_ITEM_KILL_MONSTER,	//扑杀怪物
    };

    public enum EDailyTaskType
    {
        EDAILY_TASK_TYPE_NONE = 0,
        EDAILY_TASK_TYPE_ROLE_ARENA,
        EDAILY_TASK_TYPE_STRENTHEN_EQUIPMENT,
        EDAILY_TASK_TYPE_UPGRADE_SKILL,
        EDAILY_TASK_TYPE_STRENTHEN_PET,
    };

    public enum ETaskState
    {
        ETASKSTATE_NONE = 0,
        ETASKSTATE_ACCEPT,
        ETASKSTATE_COMPLETE,
        ETASKSTATE_GOT_PRIZE,
    };

    public enum EPetTaskType
    {
        EPET_TASK_TYPE_NONE = 0,
        EPET_TASK_TYPE_STAGE,
        EPET_TASK_TYPE_KILL_MONSTER,
        EPET_TASK_TYPE_MONSTER_DROP,
        EPET_TASK_TYPE_BOSS_DROP,

    };

    public enum EPetTaskColor
    {
        EPET_TASK_COLOR_NONE = 0,
        EPET_TASK_COLOR_WHITE,
        EPET_TASK_COLOR_GREEN,
        EPET_TASK_COLOR_BLUE,
        EPET_TASK_COLOR_PURPLE,
        EPET_TASK_COLOR_ORANGE,
    };


}