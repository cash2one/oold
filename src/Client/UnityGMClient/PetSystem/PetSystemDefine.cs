using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    /// <summary>
    /// 伙伴状态
    /// </summary>
    public enum EPetStatus
    {
        /// <summary>
        /// 普通状态 
        /// </summary>
        EPetStatusInvalid = 0,
        /// <summary>
        /// 坐下喝茶状态(援护)
        /// </summary>
        EPetStatusSit = 1,
        /// <summary>
        /// 泡温泉状态
        /// </summary>
        EPetStatusInSpring = 2,
    }

    /// <summary>
    /// 发布任务结果
    /// </summary>
    public enum EPetHotSprintEnd
    {
        /// <summary>
        /// 胜利
        /// </summary>
        EPetHotSprintEndWin = 0,
        /// <summary>
        /// 失败
        /// </summary>
        EPetHotSprintEndLoss = 1,
    }


    /// <summary>
    /// 伙伴解锁状态
    /// </summary>
    public enum EPetUnlockStatus
    {
        /// <summary>
        /// 已经解锁状态 
        /// </summary>
        EPetStatusUnlocked = 0,
        /// <summary>
        /// 可解锁状态 
        /// </summary>
        EPetStatusReadyUnlock = 1,
        /// <summary>
        /// 不可解锁状态
        /// </summary>
        EPetStatusCannotUnlock = 2,
    }

    /// <summary>
    /// 温泉类型
    /// </summary>
    public enum EHotSpringType
    {
        /// <summary>
        /// 无效温泉 
        /// </summary>
        EInvalidHotSpring = 0,
        /// <summary>
        /// 五分钟温泉
        /// </summary>
        EFiveMiniteHotSpring=1,
        /// <summary>
        /// 四小时温泉
        /// </summary>
        EFourHoursHotSpring=2,
        /// <summary>
        /// 八小时温泉
        /// </summary>
        EEightHoursHotSpring=3,
    }
    /// <summary>
    /// 温泉任务类型
    /// </summary>
    public enum EHotSpringTaskStatus
    {
        /// <summary>
        /// 无效任务
        /// </summary>
        EHotSpringInvalidTask = 0,
        /// <summary>
        /// 日常任务
        /// </summary>
        EHotSpringTaskNormal = 1,
        /// <summary>
        /// 主线任务
        /// </summary>
        EHotSpringMainTask = 2,
        /// <summary>
        /// 支线任务
        /// </summary>
        EHotSpringRandomTask = 3,
    }

    /// <summary>
    /// 温泉任务子类型
    /// </summary>
    public enum EHotSpringTaskType
    {
        EHotSpringTaskTypeInvalid = 0,
        /// <summary>
        /// 聊天任务
        /// </summary>
        EHotSpringTaskTypeTalk = 1,
        /// <summary>
        /// 问答任务
        /// </summary>
        EHotSpringTaskTypeQuestion = 2,
        /// <summary>
        /// 索要礼物
        /// </summary>
        EHotSpringTaskTypeGetGift = 3,
        /// <summary>
        /// 发布任务
        /// </summary>
        EHotSpringTaskTypePublishTask = 4,
    }
}
