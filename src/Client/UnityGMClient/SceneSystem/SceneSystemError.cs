namespace UnityGMClient
{

    public enum EEnterSceneResult
    {
        EENTER_SCENE_RESULT_SUCCESS = 0,				//成功
        EENTER_SCENE_RESULT_FAIL,						//失败
        EENTER_SCENE_RESULT_ALLOCATE_SCENE_FAIL,		//分配场景失败
        EENTER_SCENE_RESULT_SYSTEM_ERROR,				//系统错误
        EENTER_SCENE_RESULT_NOT_EXIST,					//场景不存在
        EENTER_SCENE_RESULT_ALREADY_IN_SCENE,			//已经在该场景中
        EENTER_SCENE_RESULT_NOT_ENOUGH_ROLE_LEVEL,		//等级不够,
        EENTER_SCENE_RESULT_ALREADY_IN_OTHER_INSTANCE,	//已经在其他副本场景中,

        //进入关卡
        EENTER_STAGE_RESULT_FAIL,
        EENTER_STAGE_RESULT_ERROR_INSTANCE,
        EENTER_STAGE_RESULT_REACH_DAILY_ENTER_TIMES_LIMIT,
        EENTER_STAGE_RESULT_IS_IN_STAGE,
        EENTER_STAGE_RESULT_NO_SUCH_STAGE_INDEX,
        EENTER_STAGE_RESULT_NOT_SUCH_INSTANCE,
        EENTER_STAGE_RESULT_STAGE_NOT_OPEN,
        EENTER_STAGE_RESULT_INSTANCE_NOT_OPEN,
        EENTER_STAGE_RESULT_NOT_ENOUGH_VATALITY,
        EENTER_STAGE_RESULT_NOT_SUPPORT_HELPER,
        EENTER_STAGE_RESULT_NOT_FRIEND,
        EENTER_STAGE_RESULT_GET_FRIEND_DATA_ERROR,
        EENTER_STAGE_RESULT_NOT_ENOUGH_DIAMOND,
        EENTER_STAGE_RESULT_NOT_ENOUGH_ROLE_LEVEL,
        EENTER_STAGE_RESULT_NOT_ENOUGH_STAR,


        //进入连续闯关
        EENTER_CON_STAGE_RESULT_FAIL,
        EENTER_CON_STAGE_DATA_ERROR,
        EENTER_CON_STAGE_RESULT_NO_SUCH_STAGE_INDEX,
        EENTER_CON_STAGE_RESULT_NOT_ENOUGH_ACTIVATE_COUNT,
        EENTER_CON_STAGE_RESULT_ERROR_NEXT_STAGE_INDEX,
        EENTER_CON_STAGE_RESULT_NOT_ENOUGH_ROLE_LEVEL,

        //进入竞技场挑战玩家
        EENTER_ARENA_RESULT_SUCCESS,
        EENTER_ARENA_RESULT_FAIL,
        EENTER_ARENA_RESULT_ALREADY_IN_OTHER_INSTANCE,
        EENTER_ARENA_RESULT_CHALLENGEE_NO_DAILY_CHALLENGE_COUNT,
        EENTER_ARENA_RESULT_NOT_CHOOSE_PLAYER_YET,
        EENTER_ARENA_RESULT_CHALLENGEE_NOT_EXIST,
        EENTER_ARENA_RESULT_NOT_ENOUGH_ROLE_LEVEL,
        EENTER_ARENA_RESULT_NOT_SUCH_RECORD,
        EENTER_ARENA_RESULT_IN_COLD_DOWN,
        EENTER_ARENA_RESULT_NOT_ENOUGH_DIAMOND,
        EENTER_ARENA_RESULT_HAS_REVENGED,
        EENTER_ARENA_RESULT_IS_ACTIVE_RECORD,
        EENTER_ARENA_RESULT_NOT_ENOUGH_COOLDOWN_COUNT,

        //进入随机关卡
        EENTER_RANDOM_STAGE_SUCCESS,
        EENTER_RANDOM_STAGE_FAIL,
        EENTER_RANDOM_STAGE_RESULT_NOT_ENOUGH_ROLE_LEVEL,
        EENTER_RANDOM_STAGE_RESULT_ALREADY_IN_OTHER_INSTANCE,

        //enter gold land stage
        EEnter_GREED_LAND_STAGE_SUCCESS,
        EEnter_GREED_LAND_STAGE_FAIL,
        EEnter_GREED_LAND_STAGE_NO_ENTRANCE_TICKET,
        EEnter_GREED_LAND_STAGE_INVALIDE_STAGE_INDEX,
        EEnter_GREED_LAND_STAGE_NOT_OPEN,

    };

    public enum EQuitSceneResult
    {
        EQUITSCENE_RESUlT_SUCCESS = 0,
        EQUITSCENE_RESUlT_FAIL = 1,
    }

    public enum ESceneRoleReviveResult
    {
        SCENE_ROLE_REVIVE_RESULT_SUCCESS = 0,             //复活成功
        SCENE_ROLE_REVIVE_RESULT_FAIL,					  //失败
        SCENE_ROLE_REVIVE_RESULT_NOT_IN_SCENE,			  //不在场景内
        SCENE_ROLE_REVIVE_RESULT_DISABLE_REVIVE,          //场景无法复活
        SCENE_ROLE_REVIVE_RESULT_IS_ALIVE,                //角色未死亡
        SCENE_ROLE_REVIVE_RESULT_NOT_ENOUGH_DIAMOND,      //复活所需钻石不足
        SCENE_ROLE_REVIVE_RESULT_NOT_REACH_MAX_TIMES,     //已到达复活最大数
    };

    public enum EChallengeArenaRoleResult
    {
        ECHALLENGE_ARENA_ROLE_RESULT_SUCCESS,
    }

    public enum EChallengeArenaRoleFinishResult
    {
        ECHALLENGE_ARENA_ROLE_FINISH_RESULT_SUCCESS,
    }

    public enum EGetInstanceDataResult
    {
        EGET_INSTANCE_DATA_RESULT_SUCCESS = 0,
        EGET_INSTANCE_DATA_RESULT_FAIL,
    }

    public enum ESendStageResultReportResult
    {
        ESEND_STAGE_RESULT_REPORT_RESULT_SUCCESS = 0,
        ESEND_STAGE_RESULT_REPORT_RESULT_FAIL,
        ESEND_STAGE_RESULT_REPORT_NOT_IN_STAGE,
        ESEND_STAGE_RESULT_REPORT_ERROR_INSTANCE,
        ESEND_STAGE_RESULT_REPORT_ERROR_STAGE,
        ESEND_STAGE_RESULT_REPORT_INCORRECT_STAGE_STATE,

    }

    public enum EClearStageResult
    {
        ECLEAR_STAGE_RESULT_SUCCESS = 0,
        ECLEAR_STAGE_RESULT_FAIL,
        ECLEAR_STAGE_RESULT_ERROR_INSTANCE_TYPE,
        ECLEAR_STAGE_RESULT_ERROR_STAGE,
        ECLEAR_STAGE_RESULT_ERROR_NOT_REACH_STAR_REQUIREMENT,
        ECLEAR_STAGE_RESULT_ERROR_NOT_CLEAR_TIME_IS_ZERO,
        ECLEAR_STAGE_RESULT_ERROR_NOT_REACH_MAX_DAILY_ENTER_TIME,
        ECLEAR_STAGE_RESULT_ERROR_NOT_ENOUGH_CLEAR_TIMES,
        ECLEAR_STAGE_RESULT_ERROR_NOT_REACH_LV_REQUIREMENT,
        ECLEAR_STAGE_RESULT_ERROR_NOT_REQUIRE_ITEM,
        ECLEAR_STAGE_RESULT_ERROR_NOT_ENOUGH_VITALITY,

    }

    public enum EGetInstanceStarPrizeResult
    {
        EGET_INSTANCE_PRIZE_RESULT_SUCCESS = 0,
        EGET_INSTANCE_PRIZE_RESULT_FAIL,
        EGET_INSTANCE_PRIZE_RESULT_NO_SUCH_INSTANCE,
        EGET_INSTANCE_PRIZE_RESULT_NO_SUCH_PRIZE,
        EGET_INSTANCE_PRIZE_RESULT_NO_STARS,
        EGET_INSTANCE_PRIZE_RESULT_NO_PRIZE_ANY_MORE,
        EGET_INSTANCE_PRIZE_RESULT_NOT_ENOUGH_STARS,

    }

    public enum EGetContinuousInstanceDataResult
    {
        EGET_CONTINUOUS_INSTANCE_SUCCESS = 0,
        EGET_CONTINUOUS_INSTANCE_FAIL,
        EGET_CONTINUOUS_INSTANCE_NO_SUCN_INSTANCE,
        EGET_CONTINUOUS_INSTANCE_INSTANCE_NOT_CONTINUOUS_STAGE_INSTANCE,


    };

    public enum EReportContinuousStageResultResult
    {
        EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_SUCCESS = 0,
        EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_FAIL,
        EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_NOT_IN_STAGE,
        EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_NOT_IN_CONTINUOUS_STAGE,
        EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_NOT_ERROR_CONTINUOUS_INSTANCE_ID,
        EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_NOT_ERROR_CONTINUOUS_STAGE_INDEX,

    }

    public enum ERollFastClearContinuousStageNum
    {
        EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_SUCCESS = 0,
        EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_FAIL,
        EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_NO_FREE_ROLL_COUNT,
        EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_ALEADY_IN_STAGE,
        EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_ERROR_CONTINUOUS_INSTANCE_ID,
        EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_CONTINUOUS_INSTANCE_NOT_ACTIVATED,
        EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_NOT_CLEAR_STAGE_YET,
        EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_REACH_MAX_STAGE_SIZE,

    }

    public enum EResetContinuousInstanceResult
    {
        ERESET_CONTINUOUS_INSTANCE_RESULT_SUCCESS = 0,
        ERESET_CONTINUOUS_INSTANCE_RESULT_FAIL,
        ERESET_CONTINUOUS_INSTANCE_RESULT_ALREADY_IN_INSTANCE,
        ERESET_CONTINUOUS_INSTANCE_RESULT_ERROR_CONTINUOUS_INSTANCE_TPID,
        ERESET_CONTINUOUS_INSTANCE_RESULT_INSTANCE_NOT_ACTIVATED_YET,
        ERESET_CONTINUOUS_INSTANCE_RESULT_STAGE_INDEX_IS_ZERO,
        ERESET_CONTINUOUS_INSTANCE_RESULT_NO_INSTANCE_RESET_COUNT, 

    }

    public enum EDetermineStagePrizeItemResult
    {
        EDETERMINE_STAGE_PRIZE_ITEM_SUCCESS = 0,
        EDETERMINE_STAGE_PRIZE_ITEM_FAIL,
        EDETERMINE_STAGE_PRIZE_ITEM_NOT_FINISHED_STAGE,


    }

    public enum ESendRandomStageReportResult
    {
       ESEND_RANDOM_STAGE_REPORT_RESULT_SUCCESS,
       ESEND_RANDOM_STAGE_REPORT_RESULT_FAIL,

    }

    public enum EGetGreedLandInfoResult
    {
        EGET_GREEDLAND_INFO_SUCCESS = 0,
        EGET_GREEDLAND_INFO_FAIL,

    }

    public enum EPurchaseArenaTicketsResult
    {
        EPURCHASE_ARENA_TICKETS_SUCCESS = 0,
        EPURCHASE_ARENA_TICKETS_FAIL,
    }

    public enum ERestoreStageTicketsResult
    {
        ERESTORE_STAGE_TICKETS_SUCCESS,
        ERESTORE_STAGE_TICKETS_FAIL,
        ERESTORE_STAGE_TICKETS_STAGE_NOT_EXIST,
        ERESTORE_STAGE_TICKETS_STAGE_NOT_OPEN,
        ERESTORE_STAGE_TICKETS_STAGE_NOT_EMPTY_TICKET,
        ERESTORE_STAGE_TICKETS_STAGE_NOT_ENOUGH_DIAMOND,
        ERESTORE_STAGE_TICKETS_STAGE_NOT_NO_TICKET_LIMIT,
        ERESTORE_STAGE_TICKETS_STAGE_RESTORE_COUNT_LIMIT,	//达到恢复上限

        
    }


};