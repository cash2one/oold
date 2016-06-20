using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    // 物品类型
    public enum EItemType
    {
        EITEM_TP_IVALID = 0,           // 无效物品

        // 装备(1~100)
        EITEM_TP_EQUIP_WEAPONS = 1,     //武器
        EITEM_TP_EQUIP_JADE = 2,		//玉佩
        EITEM_TP_EQUIP_CAP = 3,		//头盔
        EITEM_TP_EQUIP_ARMOR = 4,		//铠甲	
        EITEM_TP_EQUIP_GLOVE = 5,		//手套	
        EITEM_TP_EQUIP_SHOES = 6,		//战靴	
        EITEM_TP_EQUIP_NECKLACE = 7,		//项链	
        EITEM_TP_EQUIP_RING = 8,		//戒子	
        EITEM_TP_EQUIP_FASHION = 9,
        EITEM_TP_EQUIP_NENGLIANGQIU = 10,

        ///材料类(101~1000)
        EITEM_TP_EQUIP_UPGRADE_MATERIAL = 101, // 装备强化材料（强化石）
        EITEM_TP_EQUIP_QUALITY_MATERIAL = 102,    // 装备熔炼材料（熔炼石）
        EITEM_TP_EQUIP_RESET_MATERIAL = 103,   // 装备洗练材料（洗练石）
        EITEM_TP_GEMS = 104,                   // 装备镶嵌宝石

        ///碎片类(1001~10000)
        EITEM_TP_PET_MATERIAL = 1001,  // 伙伴碎片 
        EITEM_TP_GEMS_MATERIAL = 1002, // 宝石碎片

        ///道具类(10001~100000)
        EITEM_TP_PROP_GIFT = 10001,               // 礼包	
        EITEM_TP_PROP_SPEAKER = 10002,            // 喇叭	
        EITEM_TP_PROP_MEDICINE = 10003,           // 药水 
        EITEM_TP_PROP_PET_FRIENDLY = 10004,       // 好感度道具	
        EITEM_TP_PROP_PET_WATER = 10005,          // 温泉汤药
        EITEM_TP_PROP_KEY = 10006,                // 钥匙 
        EITEM_TP_PROP_BOX = 10007,                // 宝箱
        EITEM_TP_PROP_VITALITY = 10008,      // 体力道具 

        ///特殊类 不在背包显示(100001~)
        EITEM_TP_VIR_PET = 100001,           // 伙伴 
        EITEM_TP_VIR_PVPCOIN = 100002,       // PVP币
        EITEM_TP_VIR_VIP_SCORE = 100003,     // VIP积分
        EITEM_TP_VIR_ACTIVE_DEGREE = 100004, // 活跃度
        EITEM_TP_VIR_BAGEXPAND = 100005,     // 背包扩充
        EITEM_TP_VIR_GOLD = 100006,          // 金币
        EITEM_TP_VIR_DIAMOND = 100007,       // 钻石
        EITEM_TP_VIR_EXP = 100008,           // 经验
        EITEM_TP_VIR_VIP_CARD = 100009,      // vip体验卡 
        EITEM_TP_VIR_VITALITY = 100010,      // 体力

        EITEM_TP_MAX,
    }

    // 物品栏类型
    public enum EBagType
    {
        EBAG_INVALID = 0,    // 无效类型
        EBAG_ITEM = 1,       // 道具 
        EBAG_MATERIAL = 2,   // 材料
        EBAG_PIECE = 3,      // 碎片
        EBAG_EQUIP = 4,      // 装备
    }
}
