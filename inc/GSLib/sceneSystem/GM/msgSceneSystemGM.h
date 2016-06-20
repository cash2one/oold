//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	GSLib\sceneSystem\GM\msgSceneSystemGM.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SCENESYSTEM_GM_MSGSCENESYSTEMGM_H__
#define __GSLIB_SCENESYSTEM_GM_MSGSCENESYSTEMGM_H__

#include <GSLib/sceneSystem/msgNumIDSceneSystem.h>
#include <GSLib/sceneSystem/sceneSystemDefine.h>
#include <BSLib/math/vector3.h>
#include <GSLib/sceneSystem/sceneSystemCommonData.h>
#include <GSLib/sceneSystem/GM/sceneSystemData.h>

namespace GSLib
{

namespace SceneSystem
{

const BSLib::uint32 MsgIDSceneSystemGC2GMReqEnterScene = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ENTER_SCENE);
class CMsgSceneSystemGC2GMReqEnterScene : public GFLib::CMessage
{
public:
	CMsgSceneSystemGC2GMReqEnterScene() : GFLib::CMessage(MsgIDSceneSystemGC2GMReqEnterScene)
	{
	}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			stream >> m_sceneTPID;
			return true;
		}
	public:
		BSLib::uint32 m_sceneTPID;
	};

const BSLib::uint32 MsgIDSceneSystemGC2GMReqQuitScene = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_QUIT_SCENE);
class CMsgSceneSystemGC2GMReqQuitScene : public GFLib::CMessage
{
public:
	CMsgSceneSystemGC2GMReqQuitScene() : GFLib::CMessage(MsgIDSceneSystemGC2GMReqQuitScene)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_sceneTypeID;
		return true;
	}
public:
	BSLib::uint32 m_sceneTypeID;
};

//获取竞玩家竞技场数据
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDSceneSystemGC2GMReqGetRoleArenaData = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_ROLE_ARENA_DATA);
class CMsgSceneSystemGC2GMReqGetRoleArenaData : public GFLib::CMessage
{
public:
	CMsgSceneSystemGC2GMReqGetRoleArenaData() : GFLib::CMessage(MsgIDSceneSystemGC2GMReqGetRoleArenaData)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		return true;
	}
};

//获取新一批可挑战玩家的信息
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDSceneSystemGC2GMReqGetNewArenaChallengees = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_NEW_ARENA_CHALLENGEES);
class CMsgSceneSystemGC2GMReqGetNewArenaChallengees : public GFLib::CMessage
{
public:
	CMsgSceneSystemGC2GMReqGetNewArenaChallengees() : GFLib::CMessage(MsgIDSceneSystemGC2GMReqGetNewArenaChallengees)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		return true;
	}
};

//挑战竞技场玩家
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDSceneSystemGC2GMReqChallengeArenaRole = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_CHALLENGE_ARENA_ROLE);
class CMsgSceneSystemGC2GMReqChallengeArenaRole : public GFLib::CMessage
{
public:
	CMsgSceneSystemGC2GMReqChallengeArenaRole()
	: GFLib::CMessage(MsgIDSceneSystemGC2GMReqChallengeArenaRole)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		m_challengeInfo.serializeFrom(stream);
		return true;
	}
public:
	GM::CChallengeInfo m_challengeInfo;
};

//挑战竞技场玩家结束
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDSceneSystemGC2GMReqChallengeArenaRoleFinish = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_CHALLENGE_ARENA_ROLE_FINISH);
class CMsgSceneSystemGC2GMReqChallengeArenaRoleFinish : public GFLib::CMessage
{
public:
	CMsgSceneSystemGC2GMReqChallengeArenaRoleFinish()
	:GFLib::CMessage(MsgIDSceneSystemGC2GMReqChallengeArenaRoleFinish)
	,m_isWin(false)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		BSLib::int8 result = 0;
		stream >> result;
		m_isWin = (result == 1);

		return true;
	}
public:
	bool m_isWin;
};

//获取剧情任务进度
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDSceneSystemGC2GMReqGetStroyInstanceProgress = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_STORY_INSTANCE_PROGRESS);
class CMsgSceneSystemGC2GMReqGetStroyInstanceProgress : public GFLib::CMessage
{
public:
	CMsgSceneSystemGC2GMReqGetStroyInstanceProgress() : GFLib::CMessage(MsgIDSceneSystemGC2GMReqGetStroyInstanceProgress)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		return true;
	}
};                     

//获取通关副本详情
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDSceneSystemGC2GMReqGetStroyInstanceData = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_INSTANCE_DATA);
class CMsgSceneSystemGC2GMReqGetInstanceData : public GFLib::CMessage
{
public:
	CMsgSceneSystemGC2GMReqGetInstanceData() : GFLib::CMessage(MsgIDSceneSystemGC2GMReqGetStroyInstanceData)
	,m_instanceID(0)
	{
	}
	
protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_instanceID;
		return true;
	}
public:
	BSLib::uint32 m_instanceID;
};                     

//申请进入关卡
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDSceneSystemGC2GMReqEnterStage = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ENTER_STAGE);
class CMsgSceneSystemGC2GMReqEnterStage : public GFLib::CMessage
{
public:
	CMsgSceneSystemGC2GMReqEnterStage() : GFLib::CMessage(MsgIDSceneSystemGC2GMReqEnterStage)
	{
	}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			stream >> m_instanceID;
			stream >> m_stageIndex;
			m_helperKey.serializeFrom(stream);
			return true;
		}
	public:
		BSLib::uint32 m_instanceID;
		BSLib::uint16 m_stageIndex;
		SRoleKey m_helperKey;
	};                     

//关卡结束
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDSceneSystemGC2GMReqStageResultReport = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_STAGE_REPORT_RESULT);
class CMsgSceneSystemGC2GMReqStageResultReport : public GFLib::CMessage
{
public:
	CMsgSceneSystemGC2GMReqStageResultReport()
	:GFLib::CMessage(MsgIDSceneSystemGC2GMReqStageResultReport)
	,m_isWin(false)
	,m_star(0) 
	,m_useTime(0)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		BSLib::uint8 result;
		stream >> result;
		m_isWin = result > 0;
		stream >> m_star;
		stream >> m_useTime;
		BSLib::uint16 count = 0;
		stream >> count;	
		for (BSLib::uint16 i = 0; i < count; ++i) {
			BSLib::uint32 monsterIndex = 0;
			stream >> monsterIndex;
			m_clearedRandomMonster.push_back(monsterIndex);
		}
		return true;
	}
public:
	bool m_isWin;
	BSLib::int8 m_star;
	BSLib::int32 m_useTime;
	std::vector<BSLib::uint32> m_clearedRandomMonster;
};                     
	
	//扫荡
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGC2GMReqClearStage = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_CLEAR_STAGE);
	class CMsgSceneSystemGC2GMReqClearStage : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGC2GMReqClearStage()
		:GFLib::CMessage(MsgIDSceneSystemGC2GMReqClearStage)
		,m_instanceID(0)
		,m_stageIndex(0)
		,m_breakDownItem(0)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			stream >> m_instanceID;
			stream >> m_stageIndex;
			stream >> m_breakDownItem;
			return true;
		}
	public:
		BSLib::uint32 m_instanceID;
		BSLib::uint16 m_stageIndex;
		bool m_breakDownItem;
	};                     

	//获取副本星级奖励
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGC2GMReqGetInstanceStarPrize = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_INSTANCE_STAR_PRIZE);
	class CMsgSceneSystemGC2GMReqGetInstanceStarPrize : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGC2GMReqGetInstanceStarPrize() 
		: GFLib::CMessage(MsgIDSceneSystemGC2GMReqGetInstanceStarPrize)
		, m_instanceTPID(0)
		{
		}
	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			stream >> m_instanceTPID;
			return true;
		}
	public:
		BSLib::uint32 m_instanceTPID;
	};                     

	//获取副本星级奖励进度
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGC2GMReqGetIntanceStarPrizeProgress = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_INSTANCE_STAR_PRIZE_PROGRESS);
	class CMsgSceneSystemGC2GMReqGetIntanceStarPrizeProgress : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGC2GMReqGetIntanceStarPrizeProgress() 
		: GFLib::CMessage(MsgIDSceneSystemGC2GMReqGetIntanceStarPrizeProgress)
		,m_instanceTPID(0)
		{
		}
	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			stream >> m_instanceTPID;
			return true;
		}
	public:
		BSLib::uint32 m_instanceTPID;
	};                     

	//获取连续闯关副本信息
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGC2GMReqGetContinuousInstanceData = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_CONTINUOUS_INSTANCE_DATA);
	class CMsgSceneSystemGC2GMReqGetContinuousInstanceData : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGC2GMReqGetContinuousInstanceData() 
		:GFLib::CMessage(MsgIDSceneSystemGC2GMReqGetContinuousInstanceData)
		,m_instanceTPID(0)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			stream >> m_instanceTPID;
			return true;
		}
	public:
		BSLib::uint32 m_instanceTPID;

	};                     

	//进入连续关卡
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGC2GMReqEnterContinuousStage = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ENTER_CONTINUOUS_STAGE);
	class CMsgSceneSystemGC2GMReqEnterContinuousStage : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGC2GMReqEnterContinuousStage() 
		:GFLib::CMessage(MsgIDSceneSystemGC2GMReqEnterContinuousStage)
		,m_instanceTPID(0)
		,m_stageIndex(0)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			stream >> m_instanceTPID;
			stream >> m_stageIndex;
			return true;
		}
	public:	
		BSLib::uint32 m_instanceTPID;
		BSLib::uint32 m_stageIndex;
	};                     
//玩家控制角色移动
const BSLib::uint32 MsgIDSceneSystemGC2GMReqRoleMove = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ROLE_MOVE);
class CMsgSceneSystemGC2GMReqRoleMove : public GFLib::CMessage
{
public:
	CMsgSceneSystemGC2GMReqRoleMove()
		:GFLib::CMessage(MsgIDSceneSystemGC2GMReqRoleMove)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		return true;
	}
public:
	BSLib::uint64 m_serverTimer;
	BSLib::uint8 m_state;
	BSLib::Math::SVector3 m_direction;
	BSLib::Math::SVector3 m_position;
};      

	//汇报连续关卡闯关成绩
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGC2GMReqReportContinuousStageResult = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_REPORT_CONTINUOUS_STAGE_RESULT);
	class CMsgSceneSystemGC2GMReqReportContinuousStageResult : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGC2GMReqReportContinuousStageResult()
		:GFLib::CMessage(MsgIDSceneSystemGC2GMReqReportContinuousStageResult)
		,m_isWin(false)
		,m_score(0)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			BSLib::int8 result;
			stream >> result;
			m_isWin = result > 0;
			stream >> m_score;
			return true;
		}
	public:
		bool m_isWin;
		BSLib::uint32 m_score;
	};                     

	//掷筛子快速通关
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGC2GMReqRollFastClearContinuousStageNum = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ROLL_FAST_CLEAR_CONTINUOUS_STAGE_NUM);
	class CMsgSceneSystemGC2GMReqRollFastClearContinuousStageCount : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGC2GMReqRollFastClearContinuousStageCount()
		:GFLib::CMessage(MsgIDSceneSystemGC2GMReqRollFastClearContinuousStageNum)
		,m_instanceTPID(0)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			stream >> m_instanceTPID;
			return true;
		}
	public:
		BSLib::uint32 m_instanceTPID;
	};                     

	//充值连续关卡副本
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGC2GMReqResetContinuousInstance = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_RESET_CONTINUOUS_INSTANCE_DATA);
	class CMsgSceneSystemGC2GMReqResetContinuousInstance : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGC2GMReqResetContinuousInstance()
		:GFLib::CMessage(MsgIDSceneSystemGC2GMReqResetContinuousInstance)
		,m_instanceTPID(0)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			stream >> m_instanceTPID;
			return true;
		}
	public:
		BSLib::uint32 m_instanceTPID;
	};                     

	//竞技场中心服务器返回
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemCN2GMAckArenaAction = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2CN_ACK_ARENA_ACTION);
	class CMsgSceneSystemCN2GMAckArenaAction : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemCN2GMAckArenaAction()
		:GFLib::CMessage(MsgIDSceneSystemCN2GMAckArenaAction)
		,m_actionID(EARENA_ACTION_NONE )
		,m_param1(0)
		,m_param2(0)
		,m_param3(0)
		,m_rank(0)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			BSLib::uint8 actionID = 0;
			stream >> actionID;
			m_actionID = (EArenaAction)actionID;
			stream >> m_param1;
			stream >> m_param2;
			stream >> m_param3;
			stream >> m_rank;
			BSLib::uint16 count = 0;
			stream >> count;
			for (BSLib::uint16 i = 0; i < count; ++i) {
				SceneSystem::CArenaChallengeeData challengeeData;	
				challengeeData.serializeFrom(stream);
				m_vecChallengeeData.push_back(challengeeData);
			}
			m_challengerRecord.serializeFrom(stream);
			return true;
		}

		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::uint8)m_actionID;
			stream << m_param1;
			stream << m_param2;
			stream << m_param3;
			stream << m_rank;
			stream << (BSLib::uint16)m_vecChallengeeData.size();
			for (std::vector<SceneSystem::CArenaChallengeeData>::size_type index = 0; index < m_vecChallengeeData.size(); ++index) {
				m_vecChallengeeData[index].serializeTo(stream);
			}
			m_challengerRecord.serializeTo(stream);
			return true;
		}
	public:
		EArenaAction m_actionID;
		BSLib::uint32 m_param1;
		BSLib::uint32 m_param2;
		BSLib::uint32 m_param3;
		BSLib::uint32 m_rank;
		std::vector<SceneSystem::CArenaChallengeeData> m_vecChallengeeData;
		SceneSystem::CArenaChallengeRecord m_challengerRecord;
	}; 


	//关卡物品鉴定
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGC2GMReqDetermineStagePrizeItem = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_DETERMINE_STAGE_PRIZE_ITEM);
	class CMsgSceneSystemGC2GMReqDetermineStagePrizeItem : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGC2GMReqDetermineStagePrizeItem() : GFLib::CMessage(MsgIDSceneSystemGC2GMReqDetermineStagePrizeItem)
		{
		}
	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			BSLib::uint16 count = 0;
			stream >> count;
			for (BSLib::int32 i = 0; i < count; ++i) {
				BSLib::uint32 itemTPID = 0;
				stream >> itemTPID;
				m_receiveItems.push_back(itemTPID);
			}
			return true;
		}
	public:
		std::vector<BSLib::uint32> m_receiveItems;
	};                


	//进入随机关卡
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGC2GMReqEnterRandomStage = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ENTER_RANDOM_STAGE);
	class CMsgSceneSystemGC2GMReqEnterRandomStage : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGC2GMReqEnterRandomStage() 
		:GFLib::CMessage(MsgIDSceneSystemGC2GMReqEnterRandomStage)
		,m_stageTPID(0)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			stream >> m_stageTPID;
			return true;
		}
	public:
		BSLib::uint32 m_stageTPID;
	};                     

	//汇报随机关卡结果
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGC2GMReqReportRandomStageResult = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_SEND_RANDOM_STAGE_RESULT);
	class CMsgSceneSystemGC2GMReqReportRandomStageResult : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGC2GMReqReportRandomStageResult()
		:GFLib::CMessage(MsgIDSceneSystemGC2GMReqReportRandomStageResult)
		,m_isWin(false)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			BSLib::int8 isWin = 0;
			stream >> isWin; 
			m_isWin = isWin > 0;
			return true;
		}

	public:
		bool m_isWin;
	};                     

	//场景内复活
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGC2GMReqRoleRevive = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ROLE_REVIVE);
	class CMsgSceneSystemGC2GMReqRoleRevive : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGC2GMReqRoleRevive() : GFLib::CMessage(MsgIDSceneSystemGC2GMReqRoleRevive)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			return true;
		}

	};                     

	//获取金币副本、经验副本信息
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGC2GMReqGetGreedLandInfo = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_GREED_LAND_INFO);
	class CMsgSceneSystemGC2GMReqGetGreedLandInfo : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGC2GMReqGetGreedLandInfo() : GFLib::CMessage(MsgIDSceneSystemGC2GMReqGetGreedLandInfo)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			return true;
		}

	};                     

	const BSLib::uint32 MsgIDSceneSystemGC2GMReqPurchaseArenaTickts = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_PURCHASE_ARENA_TICKETS);
	class CMsgSceneSystemGC2GMReqPurchaseArenaTickts : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGC2GMReqPurchaseArenaTickts() : GFLib::CMessage(MsgIDSceneSystemGC2GMReqPurchaseArenaTickts)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			return true;
		}
	};                     



	const BSLib::uint32 MsgIDSceneSystemGC2GMReqRestoreStageTickets = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_REQ_RESTORE_STAGE_TICKET);
	class CMsgSceneSystemGC2GMReqRestoreStageTickets : public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGC2GMReqRestoreStageTickets() : GFLib::CMessage(MsgIDSceneSystemGC2GMReqRestoreStageTickets)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			stream >> m_instanceTPID;
			stream >> m_stageIndex;
			return true;
		}
	public:
		BSLib::uint32 m_instanceTPID;
		BSLib::uint32 m_stageIndex;
	};                     






}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_MSGSCENESYSTEMGM_H__
