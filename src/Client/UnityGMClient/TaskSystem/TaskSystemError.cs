namespace UnityGMClient
{

    public enum EGetDailyTaskListResult
    {
        EGET_TASK_DAILY_LIST_RESULT_SUCCESS,
        EGET_TASK_DAILY_LIST_RESULT_FAIL,

    };

    public enum EGetMainTaskListResult
    {
        EGET_TASK_MAIN_LIST_RESULT_SUCCESS,
        EGET_TASK_MAIN_LIST_RESULT_FAIL,

    };

    public enum EUpdateMainTaskStateResult
    {
        EUPDATE_MAIN_TASK_STATE_RESULT = 0,
        EUPDATE_MAIN_TASK_STATE_FAIL,
    };

    public enum EGetDailyTaskPrizeResult
    {
        EGET_TASK_DAILY_RESULT_SUCCESS,              //成功
        EGET_TASK_DAILY_RESULT_FAIL,                 //失败
        EGET_TASK_DAILY_RESULT_TASK_NOT_EXIST,       //任务不存在
        EGET_TASK_DAILY_RESULT_NOT_COMPLETE_YET,     //任务尚未完成
        EGET_TASK_DAILY_RESULT_ALREADY_GOT_PRIZE,    //已领取奖励

    };

    public enum EGetMainTaskPrizeResult
    {
        EGET_MAIN_TASK_PRIZE_RESULT_SUCCESS,
        EGET_MAIN_TASK_PRIZE_RESULT_FAIL,
        EGET_MAIN_TASK_PRIZE_RESULT_NOT_EXIST,
        EGET_MAIN_TASK_PRIZE_RESULT_NOT_COMPLETE_YET,
        EGET_MAIN_TASK_PRIZE_RESULT_ALREADY_GOT_PRIZE,
    };

    public enum EGetPetTaskResult
    {
        EGET_PET_TASK_RESULT_SUCCESS = 0,
        EGET_PET_TASK_RESULT_FAIL,
    };

    public enum ERefreshPetTaskResult
    {
        EREFRESH_PET_TASK_RESULT_SUCCESS = 0,
        EREFRESH_PET_TASK_RESULT_FAIL,
        EREFRESH_PET_TASK_RESULT_NOT_ENOUGH_DIAMOND,
    };

    public enum EUpdatePetTaskStateResult
    {
        EUPDATE_PET_TASK_STATE_SUCCESS = 0,
        EUPDATE_PET_TASK_STATE_FAIL,
        EUPDATE_PET_TASK_STATE_INVALID_TASK_INDEX,
        EUPDATE_PET_TASK_STATE_INVALID_TASK_STATE,
        EUPDATE_PET_TASK_STATE_INVALID_COUNT,
    };

    public enum EGetPetTaskPrizeResult
    {
        EGET_PET_TASK_PRIZE_SUCCESS = 0,
        EGET_PET_TASK_PRIZE_FAIL,
        EGET_PET_TASK_PRIZE_INVALID_TASK_INDEX,
        EGET_PET_TASK_PRIZE_INVALID_TASK_STATE,

    };

};