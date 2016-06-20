using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    /// <summary>
    /// 兵工厂数据
    /// </summary>
    public enum EEquipDataResult
    {
        EEQUIPEDATA_RESUlT_SUCCESS = 0,
        EEQUIPEDATA_RESUlT_FAIL = 1,
    }

    public enum EConditionResult
    {
        ECONDITION_RESUlT_SUCCESS = 0,
        ECONDITION_RESUlT_FAIL = 1,
    }

    public enum ESaveOperationResult
    {
        ESAVEOPERATION_RESUlT_SUCCESS = 0,
        ESAVEOPERATION_RESUlT_FAIL = 1,
    }

    /// <summary>
    /// 初始装备信息
    /// </summary>
    public enum EGetEquipItemResult
    {
        EGETEQUIPITEM_RESUlT_SUCCESS = 0,
        EGETEQUIPITEM_RESUlT_FAIL = 1,
    }

    /// <summary>
    /// 更新装备
    /// </summary>
    public enum EUpdateRoleEquipDataResult
    {
        EUPDATEEQUIPEDATA_RESUlT_SUCCESS = 0,
        EIUPDATEEQUIPEDATA_RESUlT_FAIL = 1,
    }

    /// <summary>
    /// 装备强化
    /// </summary>
    public enum EUPGRADELEVELResult
    {
        EUPGRADELEVEL_RESUlT_SUCCESS = 0,
        EUPGRADELEVEL_RESUlT_FAIL = 1,
        EUPGRADELEVEL_RESUlT_GOLD_LIMIT = 2,       //金币不足
        EUPGRADELEVEL_RESUlT_EQUIP_NOT_EXIST = 3,  //无效装备ID
        EUPGRADELEVEL_RESUlT_LEVEL_LIMIT = 4,      //超出强化等级
        EUPGRADELEVEL_RESUlT_METARIAL_LIMIT = 5,   //材料不足
        EUPGRADELEVEL_RESULT_ROLELEVEL_LIMIT = 6,  //超出角色等级
    };

    /// <summary>
    /// 装备熔炼
    /// </summary>
    public enum EUpgradeQualityResult
    {
        EUPGRADEQUALITY_RESUlT_SUCCESS = 0,
        EUPGRADEQUALITY_RESUlT_FAIL = 1,
        EUPGRATEQUALITY_RESUlT_GOLD_LIMIT = 2,       //金币不足
        EUPGRATEQUALITY_RESUlT_EQUIP_NOT_EXIST = 3,  //无效装备ID
        EUPGRATEQUALITY_RESUlT_QUALITY_LIMIT = 4,    //超出品质等级
        EUPGRATEQUALITY_RESUlT_METARIAL_LIMIT = 5,   //材料不足
    }

    /// <summary>
    /// 装备洗练
    /// </summary>
    public enum EResetAttrResult
    {
        ERESETATTR_RESULT_SUCCESS = 0,
        ERESETATTR_RESULT_FAIL = 1,
        ERESETATTR_RESULT_GOLD_LIMIT = 2,         //金币不足
        ERESETATTR_RESULT_EQUIP_NOT_EXIST = 3,    //无效装备ID
        ERESETATTR_RESULT_DIAMOND_LIMIT = 4,      //宝石不足
        ERESETATTR_RESULT_LOCK_COUNT_LIMIT = 5,   //超出锁定上限
    }

    public enum EGetNextAddLevelEquipResult
    {
        EGETEQUIP_RESULT_SUCCESS = 0,
        EGETEQUIP_RESULT_FAIL = 1,
        EGETEQUIP_RESULT_EQUIP_NOT_EXIST = 2,  //无效装备ID
    }

    public enum EDisassemblyEquipResult
    {
        EDISASSEMBLYEQUIP_RESULT_SUCCESS = 0,
        EDISASSEMBLYEQUIP_RESULT_FAIL = 1,
        EDISASSEMBLYEQUIP_RESULT_EQUIP_NOT_EXIST = 2,  //无效装备ID
    }

    public enum EGetDisassemblyEquipResult
    {
        EGETDISASSEMBLYEQUIP_RESULT_SUCCESS = 0,
        EGETDISASSEMBLYEQUIP_RESULT_FAIL = 1,
        EGETDISASSEMBLYEQUIP_RESULT_EQUIP_NOT_EXIST = 2,
    }

    public enum EChangeStatusResult
    {
        ECHANGESTATUS_RESULT_SUCCESS = 0,
        ECHANGESTATUS_RESULT_FAIL = 1,
        ECHANGESTATUS_RESULT_STATUS_ERROR = 2,    // 装备已穿在身上
        ECHANGESTATUS_RESULT_STATUS_BAGFULL = 3,  // 背包已满
        ECHANGESTATUS_RESULT_STATUS_NOT_INBAG = 4,  // 不在背包
        ECHANGESTATUS_RESULT_INVALID_EQUIP_PROTYPE = 5,  // 无效的职业类型
        ECHANGESTATUS_RESULT_ROLE_LEVEL_LIMIT = 6,  // 角色等级限制 
    }

    /// <summary>
    /// 宝石操作结果
    /// </summary>
    public enum EGemUpdateStatusResult
    {
        EGEM_UPDATESTATUS_RESULT_FAIL = 0,
        EGEM_UPDATESTATUS_RESULT_SUCCESS = 1,
        EGEM_UPDATESTATUS_RESULT_EQUIP_NOT_EXIST = 2,       // 无效的装备
        EGEM_UPDATESTATUS_RESULT_INVALID_SLOT_INDEX = 3,    // 无效的槽位
        EGEM_UPDATESTATUS_RESULT_GEM_EXIST = 4,             // 当前位置已经镶嵌宝石
        EGEM_UPDATESTATUS_RESULT_NOT_ENOUGH_GEM = 5,        // 背包中不存在宝石
        EGEM_UPDATESTATUS_RESULT_GEM_NOT_INSLOT = 6,        // 宝石不在镶嵌槽中
        EGEM_UPDATESTATUS_RESULT_BAGFULL = 7,               // 背包已满
    }

    /// <summary>
    /// 宝石升级
    /// </summary>
    public enum EGemCombineResult
    {
        EGEM_COMBINE_RESULT_SUCCESS = 0,
        EGEM_COMBINE_RESULT_FAIL = 1,
        EGEM_COMBINE_RESULT_METARIAL_LIMIT = 2,    // 宝石不足
        EGEM_COMBINE_RESULT_INVALID_GEMTPID = 3,   // 宝石TPID无效（无配置或配置类型错误）
    }
}
