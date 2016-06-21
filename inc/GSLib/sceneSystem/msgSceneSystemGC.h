#ifndef __GSLIB_SCENESYSTEM_MSGSCENESYSTEMGC_H__
#define __GSLIB_SCENESYSTEM_MSGSCENESYSTEMGC_H__

#include <vector>
#include <list>
#include <GSLib/baseDef.h>
#include <GSLib/playerSystem/baseDef.h>
#include <GSLib/sceneSystem/GM/sceneData.h>
#include <GSLib/sceneSystem/msgNumIDSceneSystem.h>
#include <GSLib/sceneSystem/GM/sceneErrorGM.h>
#include <GSLib/sceneSystem/GM/roleArenaData.h>
#include <GSLib/sceneSystem/sceneSystemCommonData.h>
#include <GSLib/sceneSystem/GM/sceneSystemData.h>
#include <GSLib/sceneSystem/GM/scenePrize.h>

namespace GSLib
{

namespace SceneSystem
{
	
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckEnterScene = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ENTER_SCENE);
	class CMsgSceneSystemGM2GCAckEnterScene: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckEnterScene() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckEnterScene)
		,m_result(GM::EENTER_SCENE_RESULT_FAIL)
		,m_roleSceneID(INVALID_SCENEID)
		{
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream <<m_result;
			stream << m_roleSceneID;
			BSLib::uint16 count = m_vecSceneRoles.size();
			stream << count;
			for (std::vector<GM::CSceneRoleInfo>::const_iterator itr = m_vecSceneRoles.begin(); itr != m_vecSceneRoles.end(); ++itr) {
				itr->serializeTo(stream);
			}
			return true;
		}
	public:
		BSLib::uint32 m_result;
		BSLib::uint32 m_roleSceneID;
		std::vector<GM::CSceneRoleInfo> m_vecSceneRoles;
	};

	const BSLib::uint32 MsgIDSceneSystemGM2GCAckQuitScene = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_QUIT_SCENE);
	class CMsgSceneSystemGM2GCAckQuitScene: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckQuitScene() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckQuitScene)
		,m_result(GM::EQUITSCENE_RESUlT_FAIL)
		,m_roleSceneID(INVALID_SCENEID)
		{
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << m_result;
			stream << m_roleSceneID;
			return true;
		}
	public:
		BSLib::uint32 m_result;
		BSLib::uint32 m_roleSceneID;
	};

	//获取玩家竞技场数据
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckGetRoleArenaData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_ROLE_ARENA_DATA);
	class CMsgSceneSystemGM2GCAckGetRoleArenaData: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckGetRoleArenaData(const GM::CRoleArenaData & a_roleArenaData) 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckGetRoleArenaData)
		,m_roleArenaData(a_roleArenaData)
		,m_nextSendArenaPrizeTime(0)
		,m_ticketPrice(0)
		{
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << m_nextSendArenaPrizeTime;
			stream << m_ticketPrice;
			m_roleArenaData.serializeTo(stream);
			return true;
		}
	public:
		const GM::CRoleArenaData & m_roleArenaData;
		BSLib::int32 m_nextSendArenaPrizeTime;
		BSLib::uint32 m_ticketPrice;
	};

	//获取新一批玩家可挑战玩家的信息
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckGetNewArenaChallengees = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_NEW_ARENA_CHALLENGEES);
	class CMsgSceneSystemGM2GCAckGetNewArenaChallengees: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckGetNewArenaChallengees() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckGetNewArenaChallengees)
		{
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::uint16)m_vecChallengees.size();
			for (std::vector<CArenaChallengeeData>::const_iterator itr = m_vecChallengees.begin(); itr != m_vecChallengees.end(); ++itr) {
				itr->serializeTo(stream);
			}
			return true;
		}
	public:
		std::vector<CArenaChallengeeData> m_vecChallengees;
	};

	//挑战竞技场玩家返回
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckChallengeArenaRole = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_CHALLENGE_ARENA_ROLE);
	class CMsgSceneSystemGM2GCAckChallengeArenaRole: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckChallengeArenaRole() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckChallengeArenaRole)
		{
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::int8)m_result;
			m_roleData.serializeTo(stream);
			return true;
		}
	public:
		GM::EEnterSceneResult	m_result;
		CBattleRoleData	m_roleData;
	};

	//挑战结束返回
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckChallengeArenaRoleFinish = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_CHALLENGE_ARENA_ROLE_FINISH);
	class CMsgSceneSystemGM2GCAckChallengeArenaRoleFinish: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckChallengeArenaRoleFinish() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckChallengeArenaRoleFinish)
		{
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::int8)m_result;
			return true;
		}
	public:
		GM::EChallengeArenaRoleFinishResult	m_result;
	};

	//推送新的挑战纪录
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckAddNewArenaChallegenRecord = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ADD_NEW_ARENA_CHALLENGE_RECORD);
	class CMsgSceneSystemGM2GCAckAddNewArenaChallegenRecord: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckAddNewArenaChallegenRecord() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckAddNewArenaChallegenRecord)
		{
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			m_record.serializeTo(stream);
			return true;
		}
	public:
		CArenaChallengeRecord	m_record;
	};

	//获取剧情副本进度
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckGetStroyInstanceProgress = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_STORY_INSTANCE_PROGRESS);
	class CMsgSceneSystemGM2GCAckGetStroyInstanceProgress: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckGetStroyInstanceProgress() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckGetStroyInstanceProgress)
		,m_instanceID(0)
		,m_stageIndex(0)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << m_instanceID;
			stream << m_stageIndex;

			return true;
		}

	public:
		BSLib::uint32 m_instanceID;
		BSLib::uint16 m_stageIndex;
	};               

	//获取副本关卡信息
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckGetInstanceData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_INSTANCE_DATA);
	class CMsgSceneSystemGM2GCAckGetInstanceData: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckGetInstanceData() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckGetInstanceData)
		,m_result(GM::EGET_INSTANCE_DATA_RESULT_SUCCESS)
		,m_instanceID(0)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::int8)m_result;
			stream << m_instanceID;
			BSLib::uint16 count = 0;
			for (std::vector<GM::CFinishStage>::const_iterator itr = m_vecStage.begin(); itr != m_vecStage.end(); ++itr) {
				if (itr->isValid()) {
					++count;
				}
			}
			stream << count;
			for (std::vector<GM::CFinishStage>::const_iterator itr = m_vecStage.begin(); itr != m_vecStage.end(); ++itr) {
				if (itr->isValid()) {
					itr->serializeTo(stream);
				}
			}
			return true;
		}
	public:
		GM::EGetInstanceDataResult m_result;
		BSLib::uint32 m_instanceID;
		std::vector<GM::CFinishStage> m_vecStage;
	};                        

	//进入关卡
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckEnterStage = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ENTER_STAGE);
	class CMsgSceneSystemGM2GCAckEnterStage: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckEnterStage() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckEnterStage)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::int8)m_result;
			stream << m_battleRoleData.m_zoneID;
			if (m_battleRoleData.m_zoneID > 0) {
				m_battleRoleData.serializeTo(stream);
			}
			m_stageMonster.serializeTo(stream);
			return true;
		}
	public:
		GM::EEnterSceneResult m_result;
		SceneSystem::CBattleRoleData m_battleRoleData;
		GM::CStageMonster m_stageMonster;
	};               

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckStageResultReport = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_STAGE_REPORT_RESULT);
	class CMsgSceneSystemGM2GCAckStageResultReport: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckStageResultReport() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckStageResultReport)
		,m_result(GM::ESEND_STAGE_RESULT_REPORT_RESULT_FAIL )
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::int8)m_result;
			return true;
		}
	public:
		GM::ESendStageResultReportResult m_result;
	};               

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckClearStage = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_CLEAR_STAGE);
	class CMsgSceneSystemGM2GCAckClearStage: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckClearStage() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckClearStage)
		,m_result(GM::ECLEAR_STAGE_RESULT_FAIL)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::int8)m_result;
			if (m_result == GM::ECLEAR_STAGE_RESULT_SUCCESS) {
				m_stagePrize.serializeTo(stream);
			}

			return true;
		}
	public:
		GM::EClearStageResult m_result;
		GM::CStagePrize m_stagePrize;
	};               

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckGetInstanceStarPrize = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_INSTANCE_STAR_PRIZE);
	class CMsgSceneSystemGM2GCAckGetInstanceStarPrize: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckGetInstanceStarPrize() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckGetInstanceStarPrize)
		,m_result(GM::EGET_INSTANCE_PRIZE_RESULT_SUCCESS)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::int8)m_result;
			BSLib::uint16 count = m_vecPrizeItem.size();
			stream << count;
			for (BSLib::uint16 i = 0; i < count; ++i) {
				m_vecPrizeItem[i].serializeTo(stream);
			}
			return true;
		}
	public:
		GM::EGetInstanceStarPrizeResult m_result;
		std::vector<ItemSystem::GM::CPrizeItem> m_vecPrizeItem;
	};               

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckGetIntanceStarPrizeProgress = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_INSTANCE_STAR_PRIZE_PROGRESS);
	class CMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckGetIntanceStarPrizeProgress)
		,m_instanceTPID(0)
		,m_star(0)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << m_instanceTPID;
			stream << m_star;
			return true;
		}

	public:
		BSLib::uint32 m_instanceTPID;
		BSLib::uint16 m_star;
	};               

	//获取闯关副本信息
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckGetContinuousInstanceData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_CONTINUOUS_INSTANCE_DATA);
	class CMsgSceneSystemGM2GCAckGetContinuousInstanceData: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckGetContinuousInstanceData() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckGetContinuousInstanceData)
		,m_result(GM::EGET_CONTINUOUS_INSTANCE_FAIL)
		,m_dailyFreeRollFastClearStageCount(0)
		,m_instanceTPID(0)
		,m_stageIndex(0)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::int8)m_result;
			stream << m_dailyFreeRollFastClearStageCount;
			stream << m_instanceTPID;
			stream << m_stageIndex;
			return true;
		}

	public:
		GM::EGetContinuousInstanceDataResult m_result;
		BSLib::uint32 m_dailyFreeRollFastClearStageCount;
		BSLib::uint32 m_instanceTPID;
		BSLib::uint32 m_stageIndex;
	};               

	//进入连续闯关关卡
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckEnterContinuousStage = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ENTER_CONTINUOUS_STAGE);
	class CMsgSceneSystemGM2GCAckEnterContinuousStage: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckEnterContinuousStage() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckEnterContinuousStage)
		,m_result(GM::EENTER_CON_STAGE_RESULT_FAIL)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			BSLib::int8 result = (BSLib::int8)m_result;
			stream << result;
			return true;
		}
	public:
		GM::EEnterSceneResult m_result;
	};               

	//汇报连续闯关关卡战绩
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckReportContinuousStageResult = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_REPORT_CONTINUOUS_STAGE_RESULT);
	class CMsgSceneSystemGM2GCAckReportContinuousStageResult: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckReportContinuousStageResult() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckReportContinuousStageResult)
		,m_result(GM::EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_FAIL)
		,m_lastScore(0)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::int8)m_result;
			if (m_result == GM::EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_SUCCESS) {
				stream << m_lastScore;
				m_stagePrize.serializeTo(stream);
			}
			return true;
		}

	public:
		GM::EReportContinuousStageResultResult m_result;
		BSLib::uint32 m_lastScore;
		GM::CStagePrize m_stagePrize;
	};               

	//掷筛子
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckRollFastClearContinuousStageNum = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ROLL_FAST_CLEAR_CONTINUOUS_STAGE_NUM);
	class CMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckRollFastClearContinuousStageNum)
		,m_result(GM::EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_FAIL)
		,m_dailyFreeRollFastClearStageCount(0)
		,m_rollNum(0)
		,m_finalStageIndex()
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::int8)m_result;
			if (m_result == GM::EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_SUCCESS) {
				stream << m_dailyFreeRollFastClearStageCount;
				stream << m_rollNum;
				stream << m_finalStageIndex;
				BSLib::uint16 count = (BSLib::uint16)m_vecStagePrize.size();
				stream << count;
				for (std::vector<GM::CStagePrize>::size_type i = 0; i < m_vecStagePrize.size(); ++i) {
					m_vecStagePrize[i].serializeTo(stream);
				}
			}

			return true;
		}
	public:
		GM::ERollFastClearContinuousStageNum m_result;
		BSLib::uint32 m_dailyFreeRollFastClearStageCount;
		BSLib::uint32 m_rollNum;
		BSLib::uint32 m_finalStageIndex;
		std::vector<GM::CStagePrize> m_vecStagePrize;
	};               

	//重置连续关卡副本
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckResetContinuousInstance = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_RESET_CONTINUOUS_INSTANCE_DATA);
	class CMsgSceneSystemGM2GCAckResetContinuousInstance: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckResetContinuousInstance() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckResetContinuousInstance)
		,m_result(GM::ERESET_CONTINUOUS_INSTANCE_RESULT_FAIL)
		,m_instanceTPID(0)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::int8)m_result;
			stream << m_instanceTPID;
			return true;
		}
	public:
		GM::EResetContinuousInstanceResult m_result;
		BSLib::uint32 m_instanceTPID;
	};               

	//鉴定关卡奖励物品返回
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckDetermineStagePrizeItem = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_DETERMINE_STAGE_PRIZE_ITEM);
	class CMsgSceneSystemGM2GCAckDetermineStagePrizeItem: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckDetermineStagePrizeItem() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckDetermineStagePrizeItem)
		,m_result(GM::EDETERMINE_STAGE_PRIZE_ITEM_FAIL)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			BSLib::int8 result = (BSLib::int8)m_result;
			stream << result;
			return true;
		}
	public:
		GM::EDetermineStagePrizeItemResult m_result;
	};               

	//进入随机关卡返回
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckEnterRandomStage = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ENTER_RANDOM_STAGE);
	class CMsgSceneSystemGM2GCAckEnterRandomStage: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckEnterRandomStage() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckEnterRandomStage)
		,m_result(GM::EENTER_RANDOM_STAGE_FAIL)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::int8)m_result;
			m_stageMonster.serializeTo(stream);
			return true;
		}

	public:
		GM::EEnterSceneResult m_result;
		GM::CStageMonster m_stageMonster;
	};               

	//汇报随机关卡结果返回
	///////////////////////

	//const BSLib::uint32 MsgIDSceneSystemGM2GCAckReportRandomStageResult = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GC2GM_ACK_SEND_RANDOM_STAGE_RESULT);
	//class CMsgSceneSystemGM2GCAckReportRandomStageResult: public GFLib::CMessage
	//{
	//public:
	//	CMsgSceneSystemGM2GCAckReportRandomStageResult() 
	//	:GFLib::CMessage(MsgIDSceneSystemGM2GCAckReportRandomStageResult)
	//	,m_result(GM::ESEND_RANDOM_STAGE_REPORT_RESULT_FAIL)
	//	{
	//	}
	//protected:
	//	bool _serializeTo(BSLib::Utility::CStream& stream) const
	//	{
	//		stream << (BSLib::int8)m_result;
	//		return true;
	//	}
	//public:
	//	GM::ESendStageResultReportResult m_result;
	//};               

	//场景内复活回复
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckRoleRevive = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ROLE_REVIVE);
	class CMsgSceneSystemGM2GCAckRoleRevive: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckRoleRevive() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckRoleRevive)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::int8)m_result;
			return true;
		}

	public:
		GM::ESceneRoleReviveResult m_result;
	}; 


	//获取贪婪之地信息
	///////////////////////
	const BSLib::uint32 MsgIDSceneSystemGM2GCAckGetGreedLandInfo = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_GREED_LAND_INFO);
	class CMsgSceneSystemGM2GCAckGetGreedLandInfo: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckGetGreedLandInfo() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckGetGreedLandInfo)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			m_greedLandInfo.serializeTo(stream);
			return true;
		}

	public:
		GM::CGreedLandInfo m_greedLandInfo;
	};               

	const BSLib::uint32 MsgIDSceneSystemGM2GCAckPurchaseArenaTickts = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_PURCHASE_ARENA_TICKETS);
	class CMsgSceneSystemGM2GCAckPurchaseArenaTickts: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckPurchaseArenaTickts() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckPurchaseArenaTickts)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::int8)m_result;
			stream << m_curTicketCount;
			stream << m_nextTicketPrice;
			return true;
		}
	public:
		GM::EPurchaseArenaTicketsResult m_result;
		BSLib::uint32 m_curTicketCount;
		BSLib::uint32 m_nextTicketPrice;
	};               

	const BSLib::uint32 MsgIDSceneSystemGM2GCAckRestoreStageTickets = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SCENESYSTEM, EMSGNUMID_SCENESYSTEM_GM2GC_ACK_RESTORE_STAGE_TICKETS);
	class CMsgSceneSystemGM2GCAckRestoreStageTickets: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2GCAckRestoreStageTickets() 
		:GFLib::CMessage(MsgIDSceneSystemGM2GCAckRestoreStageTickets)
		,m_result(GM::ERESTORE_STAGE_TICKETS_FAIL)
		,m_instanceTPID(0)
		,m_stageIndex(0)
		,m_ticketCount(0)
		,m_nextRestoreRequireDiamond(0)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::int8)m_result;
			stream << m_instanceTPID;
			stream << m_stageIndex;
			stream << m_ticketCount;
			stream << m_nextRestoreRequireDiamond;
			return true;
		}

	public:
		GM::ERestoreStageTicketsResult m_result;
		BSLib::uint32 m_instanceTPID;
		BSLib::uint32 m_stageIndex;
		BSLib::uint32 m_ticketCount;
		BSLib::uint32 m_nextRestoreRequireDiamond;
	};               



}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_MSGSCENESYSTEMGC_H__

