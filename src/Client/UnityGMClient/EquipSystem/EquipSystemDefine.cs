using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CEquipDefine
    {
        public const uint g_roleMaxEquipCount = 10;   // 身上装备数量
    }
    /// <summary>
    /// 装备状态
    /// </summary>
    public enum EEquipStatus
    {
        /// <summary>
        /// 装备穿上
        /// </summary>
        EQUIP_STATUS_ON = 0,
        /// <summary>
        /// 装备脱下
        /// </summary>
        EQUIP_STATUS_OFF = 1,
    }

    /// <summary>
    /// 宝石状态
    /// </summary>
    public enum EGemStatus
    {
        /// <summary>
        /// 镶嵌
        /// </summary>
        GEM_STATUS_ON = 0,
        /// <summary>
        /// 取下
        /// </summary>
        GEM_STATUS_OFF = 1,
    }

    /// <summary>
    /// 装备操作类型
    /// </summary>
    public enum EEquipOperation
    {
        /// <summary>
        /// 无效操作
        /// </summary>
        EQUIP_UPGRADE_INVALID = 0,
        /// <summary>
        /// 装备强化
        /// </summary>
        EQUIP_UPGRADE_LEVEL = 1,
        /// <summary>
        /// 熔炼
        /// </summary>
        EQUIP_UPGRADE_QUALITY = 2,
        /// <summary>
        /// 洗练
        /// </summary>
        EQUIP_RESET_ATTR = 3,

        // 能量球升级
        EQUIP_UPGRADE_NENGLIANGQIU = 4,
    }

    /// <summary>
    /// 操作结果
    /// </summary>
    public enum EOperationResult
    {
        OPRESULT_SAVE = 0,
        OPRESULT_NOT_SAVE = 1,
    }

    /// <summary>
    /// 品级
    /// </summary>
    public enum EQualityID
    {
        QUALITY_INVALID = 0,     // 无效品级 
        QUALITY_WHITE = 1,       // 白
        QUALITY_GREEN = 2,       // 绿
        QUALITY_BLUE = 3,        // 蓝
        QUALITY_PURPLE = 4,       // 紫
        QUALITY_ORANGE = 5,       // 橙
        QUALITY_RED = 6,          // 红
    }

    public enum EEquipType
    {
        EQUIP_INVALID = 0,  //无效装备
        EQUIP_WEAPONS = 1,  //武器
        EQUIP_CAP = 2,	    //胸甲
        EQUIP_ARMOR = 3,    //头盔
        EQUIP_CLOTHES = 4,	//制服	
        EQUIP_UNDERPANTS = 5,//内裤	
        EQUIP_SHOES = 6,	//袜靴	
        EQUIP_NECKLACE = 7,	//项链	
        EQUIP_RING = 8,		//腕轮	
        EQUIP_FASHION=9,    //时装
        EQUIP_NENGLIANGQIU = 10,    //能量球
    }

    public enum EReqEquipType
    {
        REQ_EQUIP_ON = 0,           // 装备穿上
        REQ_EQUIP_OFF = 1,          // 装备脱下
        REQ_EQUIP_ALL = 2,          // 装备穿上
    }

    public enum EResetEquipType
    {
        ERESET_EQUIP_TYPE_XILIAN = 0,           // 洗练
        ERESET_EQUIP_TYPE_ZHUANYI = 1,          // 转移
    }

    public enum EReqGetEquip
    {
        /// <summary>
        /// 装备ID
        /// </summary>
        REQ_BY_EQUIPID = 0,
        /// <summary>
        /// 背包索引
        /// </summary>
        REQ_BY_INDEX = 1,
    }

    /// <summary>
    /// 宝石合并类型
    /// </summary>
    public enum EGemsCombineType
    {
        EGEMS_COMBINE_TYPE_SINGLE = 0,      // 宝石合成
        EGEMS_COMBINE_TYPE_ALL = 1,         // 一键合成
    };

}
