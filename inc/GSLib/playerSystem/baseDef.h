//////////////////////////////////////////////////////////////////////
//	created:	2014/08/12
//	filename:	GSLib\playerSystem\baseDef.h
//	author:		zhangping
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_BASEDEF_H__
#define __GSLIB_PLAYERSYSTEM_BASEDEF_H__

#define TIME_ROLE_SKILL_UPDATE (30 * 60)     // 技能点更新时间
#define TIME_ROLE_VITALITY_UPDATE (180)      // 体力恢复时间

#define PLAYERSYSTEM_DEFAULT_SCENE_TYPEID 1

#define ROLE_MAX_COUNT             3
#define ROLE_MAX_INDEX             BSLIB_INT32_MAX
#define INVALID_ROLE_INDEX         -1 
#define INVALID_UINT64_ATTR_VALUE  0XFFFFFFFFFFFFFFFF
#define INVALID_UINT32_ATTR_VALUE  0XFFFFFFFF
#define INVALID_STR_ATTR_VALUE     ""

#define INVALID_PLAYERID          0XFFFFFFFFFFFFFFFF
#define INVALID_ZONEID            0XFFFF
#define INVALID_SCENEID           0XFFFFFFFF

#define INVALID_ROLE_ATTR_INDEX   0XFFFFFFFF

#define DEFAULT_SCENE_TYPEID     1

#define MAX_LEVEL   10
#define ROLEP_MAXTYPE_ID       0XFFFF // 角色数据

// 角色资源修改
enum EModifyReason{
	EREASON_GOLD_DEC_EQUIP_EQUIP_UPGRAGE=0,  // 装备强化
	EREASON_GOLD_DEC_EQUIP_EQUIP_EVOLVE =1,  // 装备进阶
};

#endif//__GSLIB_PLAYERSYSTEM_BASEDEF_H__