#ifndef __GSLIB_ITEMSYSTEM_GM_ITEMATTRIBUTEGM_H__
#define __GSLIB_ITEMSYSTEM_GM_ITEMATTRIBUTEGM_H__

#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/itemSystem/baseDef.h>
namespace GSLib
{

namespace ItemSystem
{

namespace GM
{       
// 物品类型
enum EItemType
{
    EITEM_TP_IVALID = 0,           // 无效物品

    EITEM_TP_EQUIP_BEGIN = 1, // 装备开始
    EITEM_TP_EQUIP_WEAPONS = 1,     //武器
    EITEM_TP_EQUIP_JADE = 2,		//玉佩
    EITEM_TP_EQUIP_CAP = 3,		//头盔
    EITEM_TP_EQUIP_ARMOR = 4,		//铠甲	
    EITEM_TP_EQUIP_GLOVE = 5,		//手套	
    EITEM_TP_EQUIP_SHOES = 6,		//战靴	
    EITEM_TP_EQUIP_NECKLACE = 7,		//项链	
    EITEM_TP_EQUIP_RING = 8,		//戒子	
	EITEM_TP_EQUIP_FASHION = 9,		//时装
	EITEM_TP_EQUIP_NENGLIANGQIU = 10,	// 能量球
    EITEM_TP_EQUIP_END = 100, // 装备结束
    ///材料类
    EITEM_TP_MATERIAL_BEGIN = 101, //开始
    EITEM_TP_EQUIP_UPGRADE_MATERIAL = 101, // 装备强化材料
    EITEM_TP_EQUIP_QUALITY_MATERIAL = 102,    // 装备熔炼材料
    EITEM_TP_EQUIP_RESET_MATERIAL = 103,   // 装备洗练材料
    EITEM_TP_GEMS = 104,                   // 宝石
    EITEM_TP_MATERIAL_END = 1000, //结束

    ///碎片类
    EITEM_TP_PIECE_BEGIN = 1001, //开始
    EITEM_TP_VIR_PET_MATERIAL = 1001,  // 僚姬碎片 
    EITEM_TP_GEMS_MATERIAL = 1002, // 宝石碎片
    EITEM_TP_PIECE_END = 10000,

    ///道具类
    EITEM_TP_PRO_BEGIN = 10001, //开始
    EITEM_TP_PROP_GIFT = 10001,               // 礼包	
    EITEM_TP_PROP_SPEAKER = 10002,            // 喇叭	
    EITEM_TP_PROP_MEDICINE = 10003,           // 药水 
    EITEM_TP_PROP_PET_FRIENDLY = 10004,       // 好感度道具	
    EITEM_TP_PROP_PET_WATER = 10005,          // 温泉汤药
    EITEM_TP_PROP_KEY = 10006,                // 钥匙 
    EITEM_TP_PROP_BOX = 10007,                // 宝箱
    EITEM_TP_PROP_VITALITY = 10008,           // 体力道具 
	EITEM_TP_PROP_DRESS = 10009,			  // 时装
    EITEM_TP_PRO_END = 100000, //结束

    ///特殊类 不在背包显示(100001~)
    EITEM_TP_VIR_PET = 100001,           // 伙伴 
    EITEM_TP_VIR_PVPCOIN = 100002,       // PVP币
    EITEM_TP_VIR_VIPSCORE = 100003,     // VIP积分
    EITEM_TP_VIR_ACTIVE_DEGREE = 100004, // 活跃度
    EITEM_TP_VIR_BAGEXPAND = 100005,     // 背包扩充
    EITEM_TP_VIR_GOLD = 100006,          // 金币
    EITEM_TP_VIR_DIAMOND = 100007,       // 钻石
    EITEM_TP_VIR_EXP = 100008,           // 经验
    EITEM_TP_VIR_VIP_CARD = 100009,      // vip体验卡 
    EITEM_TP_VIR_VITALITY = 100010,      // 体力
	EITEM_TP_VIR_LIGHT_POWER = 100011,	// 光子力
    EITEM_TP_MAX,
};

enum EMainType
{
	EMAIN_TP_IVALID=0,      // 无效类型
    EMAIN_TP_ITEM=1,        // 物品
    EMAIN_TP_RESOURCE=2,    // 资源
	EMAIN_TP_PET=3,         // 伙伴 
	EMAIN_TP_EQUIP=4,       // 装备
};

// 背包物品
class CPrizeItem
{
public:
	CPrizeItem(ItemTPID a_TPID = 0, GSLib::ItemSystem::GM::EItemType a_itemType = GSLib::ItemSystem::GM::EITEM_TP_IVALID, BSLib::uint32 a_itemCount = 0);
	~CPrizeItem();
public:
    bool init(const std::string& a_strItem, const std::string& a_separator);
public:
	void serializeTo(BSLib::Utility::CStream& stream) const;
    void serializeFrom(BSLib::Utility::CStream& stream);
public:
	ItemTPID m_itemTPID;
	GSLib::ItemSystem::GM::EItemType m_itemType;
	BSLib::uint32 m_itemCount;
};

}//GM

}//ItemSystem

}//GSLib
#endif//__GSLIB_ITEMSYSTEM_GM_ITEMATTRIBUTEGM_H__

