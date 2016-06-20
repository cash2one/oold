namespace UnityGMClient
{
    public enum EChatResult
    {
        CHAT_RESULT_SUCCESS,									//成功
        CHAT_RESULT_FAIL,										//失败
        CHAT_RESULT_NOT_ONLINE,									//接收玩家不在线
        CHAT_RESULT_CAN_NOT_TALK_TO_SELF,						//无法私聊自己
        CHAT_RESULT_NOT_ENOUGH_ITEM,							//没有聊天所需物品
        CHAT_RESULT_TALK_TOO_FREQUENTLY,						//发言过于频繁
        CHAT_RESULT_NOT_IN_MAIN_CITY,							//不在主城
        CHAT_RESULT_NOT_FRIEND,									//非好友
    };


};