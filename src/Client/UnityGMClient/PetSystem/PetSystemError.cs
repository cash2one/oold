using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{

    /// <summary>
    /// 温泉扩建 
    /// </summary>
    public enum EExpandHotSpringResult
    {
        EEXPANDHOTSPRING_RESULT_SUCCESS = 0,
        EEXPANDHOTSPRING_RESULT_FAIL = 1,
        EEXPANDHOTSPRING_RESULT_LEVEL_LIMIT = 2,   // 达到温泉等级上限
        EEXPANDHOTSPRING_RESULT_DIAMOND_LIMIT = 3, // 钻石不足
        EEXPANDHOTSPRING_RESULT_VIPLEVEL_LIMIT = 4, // VIP等级不足(预留)
    }

    /// <summary>
    /// 任务结束 
    /// </summary>
    public enum EHotSpringTaskEndResult
    {
        EHOTSPRINGTASK_END_RESULT_SUCCESS = 0,
        EHOTSPRINGTASK_END_RESULT_FAIL = 1,
        EHOTSPRINGTASK_END_RESULT_INVALID_PETID = 2, // 无效的伙伴ID
        EHOTSPRINGTASK_END_RESULT_INVALID_TASK = 3,  // 当前任务无效
    }

    /// <summary>
    /// 伙伴任务 
    /// </summary>
    public enum EPetTaskFinishResult
    {
        EPETTASKFINISH_RESULT_SUCCESS = 0,
        EPETTASKFINISH_RESULT_FAIL = 1,
        EPETTASKFINISH_RESULT_INVALID_PETID = 2, // 无效的伙伴ID
        EPETTASKFINISH_RESULT_INVALID_TASK = 3,  // 当前任务无效
        EPETTASKFINISH_RESULT_ITEM_LIMIT = 4, // 数量不足或不存在该物品
    }

    /// <summary>
    /// 伙伴送礼 
    /// </summary>
    public enum ESendPetGiftResult
    {
        ESENDPET_GIFT_RESULT_SUCCESS = 0,
        ESENDPET_GIFT_RESULT_FAIL = 1,
        ESENDPET_GIFT_RESULT_INVALID_PETID = 2, // 无效的伙伴ID
        ESENDPET_GIFT_RESULT_INVALID_GIFT = 3,  // 存在无效的礼物
        ESENDPET_GIFT_RESULT_ITEM_LIMIT = 4,  // 数量不足或不存在该物品
    }

    /// <summary>
    /// 查看伙伴解锁进度 
    /// </summary>
    public enum EGetPetUnlockDataResult
    {
        EGETPETUNLOCKDATARESULT_SUCCESS = 0,
        EGETPETUNLOCKDATARESULT_FAIL = 1,
    }

    /// <summary>
    /// 解锁伙伴
    /// </summary>
    public enum EUnlockPetResult
    {
        EUNLOCKPET_RESULT_SUCCESS = 0,
        EUNLOCKPET_RESULT_FAIL = 1,
        EUNLOCKPET_RESULT_INVALID_PETTPID = 2, // 无效的伙伴TPID
        EUNLOCKPET_RESULT_METARIAL_LIMIT = 3,  // 伙伴合成材料不足
        EUNLOCKPET_RESULT_ALREADY_UNLOCK = 4,  // 伙伴已解锁
    }

    /// <summary>
    /// 伙伴任务 
    /// </summary>
    public enum EPetGetHotSpringTaskDetailResult
    {
        EPETGET_HOTSPRING_TASKDETAIL_RESULT_SUCCESS = 0,
        EPETGET_HOTSPRING_TASKDETAIL_RESULT_FAIL = 1,
    }

    public enum EGetInitRolePetDataResult
    {
        EGET_INITROLEPETDATA_RESULT_SUCCESS = 0,
        EGET_INITROLEPETDATA_RESULT_FAIL = 1,
    }

    /// <summary>
    /// 援护
    /// </summary>
    public enum EPetSitDownResult
    {
        EPETSITDOWN_RESULT_SUCCESS = 0,
        EPETSITDOWN_RESULT_FAIL = 1,
        EPETSITDOWN_RESULT_INVALID_PETID = 2,     // 伙伴不存在
        EPETSITDOWN_RESULT_ALREADY_SITDOWN = 3,   // 伙伴已经坐下（已经是援护状态）
        EPETSITDOWN_RESULT_ALREADY_INPOOL = 4,    // 伙伴在泡温泉（不可进入援护状态）
    }

    /// <summary>
    /// 取消援护
    /// </summary>
    public enum EPetStandUpResult
    {
        EPETSTANDUP_RESULT_SUCCESS = 0,
        EPETSTANDUP_RESULT_FAIL = 1,
        EPETSTANDUP_RESULT_INVALID_PETID = 2,   // 伙伴不存在
        EPETSTANDUP_RESULT_NOT_SITDOWN = 3,     // 伙伴不是援护状态
    }

    /// <summary>
    /// 获取伙伴数据 
    /// </summary>
    public enum EGetPetDataResult
    {
        EGETPETDATA_RESULT_SUCCESS = 0,
        EGETPETDATA_RESULT_FAIL = 1,
        EGETPETDATA_RESULT_INVALID_PETID = 2,   // 伙伴不存在
    }

    /// <summary>
    /// 进入温泉
    /// </summary>
    public enum EPetEnterPoolResult
    {
        EPETENTERPOOL_RESULT_SUCCESS = 0,
        EPETENTERPOOL_RESULT_FAIL = 1,
        EPETENTERPOOL_RESULT_INVALID_PETID = 2,   // 伙伴不存在
        EPETENTERPOOL_ALREADY_INPOOL = 3,         // 伙伴已在温泉中
        EPETENTERPOOL_ALREADY_SITDOWN = 4,        // 伙伴已援护，不可进入温泉中
        EPETENTERPOOL_ALREADY_FULL = 5,           // 温泉已满
    }

    /// <summary>
    /// 离开温泉
    /// </summary>
    public enum EPetQuitPoolResult
    {
        EPETQUITPOOL_RESULT_SUCCESS = 0,
        EPETQUITPOOL_RESULT_FAIL = 1,
        EPETQUITPOOL_RESULT_INVALID_PETID = 2, // 伙伴不存在
        EPETQUITPOOL_RESULT_NOT_INPOOL = 3,    // 伙伴不温泉中
    }

    /// <summary>
    /// 快速离开温泉
    /// </summary>
    public enum EPetFastQuitPoolResult
    {
        EPET_FASTQUITPOOL_RESULT_SUCCESS = 0,
        EPET_FASTQUITPOOL_RESULT_FAIL = 1,
        EPET_FASTQUITPOOL_RESULT_INVALID_PETID = 2,      // 伙伴不存在
        EPET_FASTQUITPOOL_RESULT_NOT_INPOOL = 3,         // 伙伴不温泉中
        EPET_FASTQUITPOOL_RESULT_DIAMOND_LIMIT = 4,      // 钻石不足
    }

    /// <summary>
    /// 获取伙伴基本信息列表 
    /// </summary>
    public enum EGetPetBaseInforListResult
    {
        EGET_PETBASEINFORLIST_RESULT_SUCCESS = 0,
        EGET_PETBASEINFORLIST_RESULT_FAIL = 1,
    }
}