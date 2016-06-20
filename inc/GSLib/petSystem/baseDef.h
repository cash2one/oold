//////////////////////////////////////////////////////////////////////
//	created:	2014/08/20
//	filename:	GSLib\inc\baseDef.h
//	author:		zhangping
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PETSYSTEM_BASEDEF_H__
#define __GSLIB_PETSYSTEM_BASEDEF_H__

typedef BSLib::uint32 PetID;          // 伙伴ID 内存自增分配
typedef BSLib::uint32 PetTPID;        // 伙伴TPID 物品表中配置的物品TPID
typedef BSLib::uint32 PetSkillID;     // 伙伴技能ID

typedef BSLib::uint64 PetLevelFriendlyValue; // 伙伴TPID与等级组合ID
typedef BSLib::uint64 PetFRangeID;    // 伙伴友好度上限与下限组成的ID

#define  PET_MAX_ID        65535      // 伙伴数据

//僚姬ID
#define  INVALID_PETINDEX   0         // 无效索引
#define  INVALID_PETTPID   -1         // 无效TPID
#define  INVALID_PETSKILLID   -1      // 无效技能ID



// 伙伴状态
enum EPetStatus
{
    /// <summary>
    /// 无效状态
    /// </summary>
    EPetStatusFree = 0,
    /// <summary>
    /// 坐下喝茶状态
    /// </summary>
    EPetStatusSit = 1,
    /// <summary>
    /// 泡温泉状态
    /// </summary>
    EPetStatusInSpring = 2,
};


/// <summary>
/// 对战结果
/// </summary>
enum EPetHotSprintEnd
{
    /// <summary>
    ///  胜利
    /// </summary>
    EPetHotSprintEndWin = 0,
    /// <summary>
    /// 失败
    /// </summary>
    EPetHotSprintEndLoss = 1,
};

/// <summary>
/// 伙伴解锁状态
/// </summary>
enum EPetUnlockStatus
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
};

// 任务角色状态
enum ETaskUser
{
    /// <summary>
    /// 无效状态
    /// </summary>
    ETaskUserInvalid = 0,
    /// <summary>
    /// 伙伴 
    /// </summary>
    ETaskUserPet = 1,
    /// <summary>
    /// 老板娘 
    /// </summary>
    ETaskUserBoss = 2,
};

/// <summary>
/// 伙伴状态
/// </summary>
enum EHotSpringType
{
    /// <summary>
    /// 无效温泉 
    /// </summary>
    EInvalidHotSpring=0,
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
};

/// <summary>
/// 温泉任务类型
/// </summary>
enum EHotSpringTaskStatus
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
};

/// <summary>
/// 任务类型
/// </summary>
enum EHotSpringTaskType
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
};

enum EUserType
{
    EUserMe=0,
    EUserYou=1,
};

enum EAnswerType
{
    EAnswerYes=0,
    EAnswerNo=1,
};

enum EHotSpringTimerStatus
{
    EHotSpringTimerStop = 0,
    EHotSpringTimerWork = 1,
};

#ifdef __GNUC__

namespace __gnu_cxx
{
	template< > struct hash< EHotSpringTaskType >
	{
		size_t operator()(const EHotSpringTaskType& x) const
		{
			return (size_t)x;
		}
	};
}

#endif

#endif//__GSLIB_PETSYSTEM_BASEDEF_H__