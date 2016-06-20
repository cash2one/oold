//////////////////////////////////////////////////////////////////////
//	created:	2014/08/20
//	filename:	GSLib\inc\baseDef.h
//	author:		zhangping
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_EQUIPSYSTEM_BASEDEF_H__
#define __GSLIB_EQUIPSYSTEM_BASEDEF_H__
#define EQUIP_ATTRIBUTE_TYPE(attributeID) (BSLIB_LO_SHIFT(attributeID, 24)& 0X000000FF)
#define EQUIP_ATTRIBUTE_CLASSIFY(attributeID) (BSLIB_LO_SHIFT(attributeID, 16) & 0X000000FF)
#define EQUIP_ATTRIBUTE_SUBID(attributeID) (attributeID & 0X0000FFFF)

#define EQUIP_ATTRIBUTE_ID(type,classify,eAttributeType) \
	( (BSLIB_HI_SHIFT(type, 24) & 0XFF000000) + (BSLIB_HI_SHIFT(classify, 16) & 0X00FF0000) + (eAttributeType & 0X0000FFFF) )

typedef BSLib::uint32 EquipID;

#define  MAX_EQUIP_EQUIPID    BSLIB_UINT32_MAX     // 装备索引最大分配值
#define  INVALID_EQUIPID		 0 
#define  EQUIP_GEM_MAXCOUNT      4       // 宝石最大数
#define  INVALID_EQUIPGEM_DATA   65535   // 无效宝石数据


#define GEMS_COLOR_WHITE_TPID 2321
#define GEMS_COLOR_GREEN_TPID 2322 
#define GEMS_COLOR_BLUE_TPID 2323
#define GEMS_COLOR_PURPLE_TPID 2324
#define GEMS_COLOR_ORANGE_TPID 2325
#define EQUIP_COLOR_GEMS_COUNT   5      // 装备强化石颜色个数
#define EQUIP_TYPE_COUNT         10
#define EQUIP_FASHION_TYPE		 9

/// <summary>
/// 装备操作类型
/// </summary>
enum EEquipOperation
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
};

enum EGemSlot
{
    GEM_SLOT_FIRST=0,
    GEM_SLOT_SECOND=1,
    GEM_SLOT_THIRD=2,
    GEM_SLOT_FORTH=3,
    GEM_SLOT_MAX=4,
    GEM_SLOT_INVALID=5,
};

/// <summary>
/// 操作结果
/// </summary>
enum EOperationResult
{
    OPRESULT_SAVE = 0,
    OPRESULT_NOT_SAVE = 1,
};

#define  EQUIP_ADD_MAX_LEVEL 15

#define EQUIP_UPGRADE_GEM_LOW	2321
#define EQUIP_UPGRADE_GEM_MID	2322
#define EQUIP_UPGRADE_GEM_HIGH	2323

#define EQUIP_LEVEL_GEM_1_20	2500
#define EQUIP_LEVEL_GEM_21_30	2501
#define EQUIP_LEVEL_GEM_31_40	2502
#define EQUIP_LEVEL_GEM_41_50	2503
#define EQUIP_LEVEL_GEM_51_60	2504


#endif//__GSLIB_EQUIPSYSTEM_BASEDEF_H__