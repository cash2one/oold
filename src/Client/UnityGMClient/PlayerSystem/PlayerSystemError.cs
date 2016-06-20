using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    /// <summary>
    /// 初始化角色列表
    /// </summary>
    public enum EInitRoleListResult
    {
        EINITROLELIST_RESUlT_SUCCESS = 0,
        EINITROLELIST_RESUlT_FAIL = 1,
    }

    public enum ECreateRoleResult
    {
        ECREATEROLE_RESUlT_SUCCESS = 0,
        ECREATEROLE_RESUlT_FAIL = 1,
        ECREATEROLE_RESUlT_INVALID_PROTYPE = 2,
        ECREATEROLE_RESUlT_INVALID_ROLENAME = 3,
        ECREATEROLE_RESUlT_ROLECOUNT_LIMIT = 4,
    }

    public enum ESelectRoleResult
    {
        ESELECTROLE_RESUlT_SUCCESS = 0,
        ESELECTROLE_RESUlT_FAIL = 1,
    }

    public enum EInitRoleDataResult
    {
        EINITROLEDATA_RESUlT_SUCCESS = 0,
        EINITROLEDATA_RESUlT_FAIL = 1,
    }

    public enum EUpdateAttributeResult
    {
        EUPDATEATTRIBUTE_RESUlT_SUCCESS = 0,
        EUPDATEATTRIBUTE_RESUlT_FAIL = 1,
    }

    public enum EGetBagDataResult
    {
        EINITPACKAGEDATA_RESUlT_SUCCESS = 0,
        EINITPACKAGEDATA_RESUlT_FAIL = 1,
    }

    /// <summary>
    /// 添加物品返回结果
    /// </summary>
    public enum ESoldBagItemDataResult
    {
        ESOLDPACKAGEDATA_RESUlT_SUCCESS = 0,
        ESOLDPACKAGEDATA_RESUlT_FAIL = 1,
    }

    /// <summary>
    /// 移动物品返回结果
    /// </summary>
    public enum EUseBagItemDataResult
    {
        EUSEITEMPACKAGEDATA_RESUlT_SUCCESS = 0,
        EUSEITEMPACKAGEDATA_RESUlT_FAIL = 1,
    }

    /// <summary>
    /// 移除物品返回结果
    /// </summary>
    public enum EUpdateBagItemDataResult
    {
        EUPDATEPACKAGEDATA_RESUlT_SUCCESS = 0,
        EUPDATEPACKAGEDATA_RESUlT_FAIL = 1,
    }


    /// <summary>
    /// 技能点成长返回结果
    /// </summary>
    public enum EUpdateSkillPointResult
    {
        EUPDATESKILLPOINT_RESULT_SUCCESS = 0,
        EUPDATESKILLPOINT_RESULT_FAIL = 1,
    }

    /// <summary>
    /// 获取体力
    /// </summary>
    public enum EGetVitalityResult
    {
        EGETVITALITY_RESULT_SUCCESS = 0,
        EGETVITALITY_RESULT_FAIL = 1,
    }

    /// <summary>
    /// 购买体力
    /// </summary>
    public enum EBuyVitalityResult
    {
        EBUYVITALITY_RESULT_SUCCESS = 0,
        EBUYVITALITY_RESULT_FAIL = 1,
        EBUYVITALITY_RESULT_BUYTIMES_LIMIT = 2,
        EBUYVITALITY_RESULT_DIAMOND_LIMIT = 3,
    }

    /// <summary>
    /// 获取购买体力所需钻石
    /// </summary>
    public enum EGetNeedDiamondResult
    {
        EGETNEEDDIAMOND_RESULT_SUCCESS = 0,
        EGETNEEDDIAMOND_RESULT_FAIL = 1,
    }

    public enum ERoleQuitResult
    {
        EROLEQUIT_RESUlT_SUCCESS = 0,
        EROLEQUIT_RESUlT_FAIL = 1,
    }

    /// <summary>
    /// 删除角色 
    /// </summary>
    public enum EDeleteRoleResult
    {
        EDELETEROLE_RESUlT_SUCCESS = 0,
        EDELETEROLE_RESUlT_FAIL = 1,
    }

    public enum EGetRoleDataResult
    {
        EGETROLEDATA_RESUlT_SUCCESS = 0,
        EGETROLEDATA_RESUlT_FAIL = 1,
    }

    public enum EGetVipLevelGiftResult
    {
        EGETVIPLEVEL_GIFTRESULT_SUCCESS = 0,
        EGETVIPLEVEL_GIFTRESULT_FAIL = 1,
    }

    public enum EVipLevelGiftStatusResult
    {
        EVIPLEVEL_GIFT_STATUS_RESULT_SUCCESS = 0,
        EVIPLEVEL_GIFT_STATUS_RESULT_FAIL = 1,
    }

    public enum EPurchaseGoldResult
    {
        EPURCHASE_GOLD_RESULT_SUCCESS = 0,
        EPURCHASE_GOLD_RESULT_FAIL,
    }

    public enum EGetPurchaseGoldInfoResult
    {
        EGET_PURCHASE_GOLD_INFO_RESULT_SUCCESS = 0,
        EGET_PURCHASE_GOLD_INFO_RESULT_FAIL,

    }


 
}
