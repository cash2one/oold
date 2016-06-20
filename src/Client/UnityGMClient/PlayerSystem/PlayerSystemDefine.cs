using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    /// <summary>
    /// 角色属性
    /// </summary>
    public enum ERoleAttributeIndex
    {
        ATTR_VIP_SCORE = 1,
        ATTR_ACTIVE_DEGREE = 2,
        ATTR_BAG_SIZE = 3,
        ATTR_SCENEID = 4,

        ATTR_QUALITY = 5,               // 角色品级
        ATTR_STARLEVEL = 6,             // 角色星级
        ATTR_PVPCOIN = 7,
        ATTR_DIAMOND = 8,

        ATTR_POP = 9,
        ATTR_VITALITY = 10,
        ATTR_SKILLPOINT = 11,   // 技能点
        ATTR_LEVEL = 12,

        ATTR_HP = 13,
        ATTR_SP = 14,
        ATTR_VIP_LEVEL = 15,

        ATTR_TotalUseChargeDiamond = 16,
        ATTR_TotalUseBindDiamond = 17,
        ATTR_TotalChargeDiamond = 18,
        ATTR_CHARGE_DIAMOND = 19,           // 充值宝石
        ATTR_BIND_DIAMOND = 20,             // 绑定宝石
        ATTR_MAX_VITALITY = 21,             // 体力上限

        ATTR_EXP = 116,       // 经验
        ATTR_GOLD = 117,      // 金币
        ATTR_LIGHT_POWER = 118, //光子力
    }

    /// <summary>
    /// 战斗属性ID
    /// </summary>
    public enum EAttrID
    {
        ATTR_ATK = 0,            // 物理攻击   
        ATTR_DEF = 1,             // 物理防御
        ATTR_MAXHP = 2,           // maxhp
        ATTR_HIT_RATE = 3,        // 命中几率(1/10000)
        ATTR_MISS_RATE = 4,       // 避闪几率(1/10000)
        ATTR_ATK_CRIFT = 5,       // 暴击(1/10000)
        ATTR_DEF_CRIFT = 6,       // 暴击抗性
        MAX_ATTR_INDEX = 7,
        ATTR_INVALID = 8,
    };

    /// <summary>
    /// 属性更新
    /// </summary>
    public enum EUpdateAttributeReason
    {
        EGAME_UPDATE = 0,
        EACTIVITY_UPDATE = 1,
    }

    /// <summary>
    /// 领取状态
    /// </summary>
    public enum EGetVipGiftStatus
    {
        /// <summary>
        /// 尚未领取
        /// </summary>
        EGETVIPGIFT_STATUS_YES = 0,
        /// <summary>
        /// 已经领取
        /// </summary>
        EGETVIPGIFT_STATUS_NO = 1,
    }

}
