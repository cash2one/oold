#include <BSLib/database/dbTableRow.h>
#include <BSLib/utility/random.h>
#include <GSLib/sceneSystem/GM/roleSceneModule.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/playerGMMgr.h>
#include <GSLib/sceneSystem/msgSceneSystem.h>
#include <GSLib/rankSystem/GM/rankMgr.h>
#include <GSLib/sceneSystem/DB/tableSceneDB.h>
#include <GSLib/taskSystem/GM/roleTaskModule.h>
#include <GSLib/taskSystem/GM/taskSystemDefine.h>
#include <GSLib/sceneSystem/GM/sceneSystemDataMgr.h>
#include <GSLib/prizeSystem/GM/rolePrizeModule.h>
#include <GSLib/sceneSystem/GM/dropItem.h>
#include <GSLib/sceneSystem/GM/dropItemEntry.h>
#include <GSLib/sceneSystem/GM/sceneMgr.h>
#include <GSLib/sceneSystem/GM/scene.h>
#include <GSLib/sceneSystem/GM/sceneSystemGM.h>
#include <GSLib/rankSystem/GM/roleRankModule.h>
#include <GSLib/skillSystem/GM/roleSkillModule.h>
#include <GFLib/commonServer/eventMgr.h>
#include <GSLib/sceneSystem/sceneSystemCommonData.h>
#include <GSLib/rankSystem/GM/roleRankModule.h>
#include <GSLib/skillSystem/GM/skill.h>
#include <GSLib/friendSystem/GM/roleFriendModule.h>
#include <GSLib/chatSystem/GM/roleChatModule.h>
#include <GSLib/itemSystem/GM/itemDataGM.h>
#include <GSLib/itemSystem/GM/itemGMMgr.h>
#include <set>
#include <GSLib/chatSystem/GM/chatContent.h>
#include <GSLib/equipSystem/GM/roleEquipGM.h>
#include <GSLib/equipSystem/GM/roleEquipModule.h>
#include <GSLib/sceneSystem/GM/sceneImpl.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

CRoleSceneModule::CRoleSceneModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType)
:GSLib::PlayerSystem::GM::CRoleModuleGM(a_roleGM, a_moduleType)
,m_reviveCount(0)
,m_curScene(NULL)
{
	m_arenaData.setSceneRole(this);
}

CRoleSceneModule::~CRoleSceneModule()
{
	;
}

void CRoleSceneModule::preInit(bool isFirst)
{
	;
}

void CRoleSceneModule::postInit(bool isFirst)
{
	;
}

void CRoleSceneModule::initToClient()
{
	;
}

void CRoleSceneModule::final()
{
	;
}

void CRoleSceneModule::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqEnterScene, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqEnterScene>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqEnterScene, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqEnterScene, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqQuitScene, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqQuitScene>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqQuitScene, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqQuitScene, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqGetRoleArenaData, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqGetRoleArenaData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqGetRoleArenaData, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetRoleArenaData, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqGetNewArenaChallengees, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqGetNewArenaChallengees>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqGetNewArenaChallengees, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetNewArenaChallengees, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqChallengeArenaRole, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqChallengeArenaRole>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqChallengeArenaRole, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqChallengeArenaRole, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqChallengeArenaRoleFinish, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqChallengeArenaRoleFinish>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqChallengeArenaRoleFinish, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqChallengeArenaRoleFinish, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqPurchaseArenaTickts, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqPurchaseArenaTickts>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqPurchaseArenaTickts, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqPurchaseArenaTickts, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqGetStroyInstanceProgress, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqGetStroyInstanceProgress>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqGetStroyInstanceProgress, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetStroyInstanceProgress, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqGetStroyInstanceData, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqGetInstanceData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqGetStroyInstanceData, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetInstanceData, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqEnterStage, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqEnterStage>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqEnterStage, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqEnterStage, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqStageResultReport, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqStageResultReport>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqStageResultReport, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqStageResultReport, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqClearStage, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqClearStage>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqClearStage, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqClearStage, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqGetInstanceStarPrize, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqGetInstanceStarPrize>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqGetInstanceStarPrize, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetInstanceStarPrize, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqGetIntanceStarPrizeProgress, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqGetIntanceStarPrizeProgress>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqGetIntanceStarPrizeProgress, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetIntanceStarPrizeProgress, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqGetContinuousInstanceData, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqGetContinuousInstanceData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqGetContinuousInstanceData, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetContinuousInstanceData, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqEnterContinuousStage, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqEnterContinuousStage>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqEnterContinuousStage, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqEnterContinuousStage, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqReportContinuousStageResult, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqReportContinuousStageResult>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqReportContinuousStageResult, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqReportContinuousStageResult, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqRollFastClearContinuousStageNum, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqRollFastClearContinuousStageCount>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqRollFastClearContinuousStageNum, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqRollFastClearContinuousStageNum, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqResetContinuousInstance, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqResetContinuousInstance>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqResetContinuousInstance, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqResetContinuousInstance, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqRoleMove, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqRoleMove>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqRoleMove, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqRoleMove, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemCN2GMAckArenaAction, &BSLib::Framework::CreateCMessage<CMsgSceneSystemCN2GMAckArenaAction>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemCN2GMAckArenaAction, &CRoleSceneModule::_onMsgSceneSystemCN2GMAckArenaAction, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqDetermineStagePrizeItem, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqDetermineStagePrizeItem>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqDetermineStagePrizeItem, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqDetermineStagePrizeItem, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqEnterRandomStage, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqEnterRandomStage>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqEnterRandomStage, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqEnterRandomStage, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqRoleRevive, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqRoleRevive>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqRoleRevive, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqRoleRevive, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqGetGreedLandInfo, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqGetGreedLandInfo>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqGetGreedLandInfo, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetGreedLandInfo, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGC2GMReqRestoreStageTickets, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGC2GMReqRestoreStageTickets>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGC2GMReqRestoreStageTickets, &CRoleSceneModule::_onMsgSceneSystemGC2GMReqRestoreStageTickets, this);



}

void CRoleSceneModule::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqEnterScene);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqQuitScene);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqGetRoleArenaData);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqGetNewArenaChallengees);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqChallengeArenaRole);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqChallengeArenaRoleFinish);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqPurchaseArenaTickts);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqGetStroyInstanceProgress);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqGetStroyInstanceData);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqEnterStage);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqStageResultReport);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqClearStage);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqGetInstanceStarPrize);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqGetIntanceStarPrizeProgress);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqGetContinuousInstanceData);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqEnterContinuousStage);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqReportContinuousStageResult);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqRollFastClearContinuousStageNum);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqResetContinuousInstance);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemCN2GMAckArenaAction);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqRoleMove);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqDetermineStagePrizeItem);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqEnterRandomStage);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqRoleRevive);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqGetGreedLandInfo);
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGC2GMReqRestoreStageTickets);

}

void CRoleSceneModule::updateDataToDB()
{	

}

bool CRoleSceneModule::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "CRoleSceneModule::cbSelectKeyTableData:getRoleGM OR getRoleGM()->getPlayerGM() error");
		return false;
	}

	switch(a_tableID)
	{
	case EDBTABLEID_ROLE_SCENE_ARENA_ROLE_DATA:
		{
			m_arenaDataTable = a_keyTable;
			if (a_sessionID == 0) {
				DB::CRoleArenaDataDB data;
				data.m_accountID = getRoleGM()->getAccountID();
				data.m_zoneID = getRoleGM()->getZoneID();
				data.m_roleIndex = getRoleGM()->getRoleIndex();

				BSLib::Database::CDBTableRow*  row = a_keyTable->getRow(data.getKey());
				if (row != NULL) {
					BSLib::Utility::CStream stream;
					row->serializeTo(stream);
					data.serializeFrom(stream);
					m_arenaData.m_arenaTicketCount = data.m_arenaTicketCount;
					m_arenaData.m_dailyTicketPurchasedCount = data.m_dailyTicketHasPurchasedCount;
					m_arenaData.m_lastChallengeTime = data.m_lastChallengeTime;
					m_arenaData.m_dailyCoolDownCount = data.m_dailyCoolDownCount;
					m_arenaData.m_lastResetTime = data.m_lastResetTime;
				}
			}
		}
		break;
	case EDBTABLEID_ROLE_STORY_INSTANCE_PROGRESS_DATA:
		{
			m_roleStoryInstanceProgressTable = a_keyTable;
			if (a_sessionID == 0) {
				DB::CRoleStoryInstanceProgressDB dbData;
				dbData.m_accountID = getRoleGM()->getAccountID();
				dbData.m_zoneID = getRoleGM()->getZoneID();
				dbData.m_roleIndex = getRoleGM()->getRoleIndex();
				BSLib::Database::CDBTableRow*  row = a_keyTable->getRow(dbData.getKey());
				if (row != NULL) {
					BSLib::Utility::CStream stream;
					row->serializeTo(stream);
					dbData.serializeFrom(stream);
					m_roleInstanceData.setStoryInstanceProgress(dbData.m_instanceID, dbData.m_stageIndex);
				}
			}
		}
		break;
	case EDBTABLEID_ROLE_CONTINUOUS_INSTANCE_DATA:
		{
			m_roleContinuousStageTable = a_keyTable;
			if (a_sessionID == 0) {
				DB::CRoleConInstanceBriefDataDB dbData;
				dbData.m_accountID = getRoleGM()->getAccountID();
				dbData.m_zoneID = getRoleGM()->getZoneID();
				dbData.m_roleIndex = getRoleGM()->getRoleIndex();
				BSLib::Database::CDBTableRow*  row = a_keyTable->getRow(dbData.getDBKey());
				if (row != NULL) {
					BSLib::Utility::CStream stream;
					row->serializeTo(stream);
					dbData.serializeFrom(stream);
					m_roleContinuousStageData.m_roleConInstanceBriefData.m_dailyActivateInstanceCount = dbData.m_dailyActivateInstanceCount;
					m_roleContinuousStageData.m_roleConInstanceBriefData.m_lastResetTime = dbData.m_lastResetTime;
				}
			}
		}
		break;
	case EDBTABLEID_ROLE_STAGE_SYSTEM_DATA:
		{
			m_roleStageSystemDataTable = a_keyTable;
			if (a_sessionID == 0) {
				DB::CRoleStageSystemData dbData;
				dbData.m_accountID = getRoleGM()->getAccountID();
				dbData.m_zoneID = getRoleGM()->getZoneID();
				dbData.m_roleIndex = getRoleGM()->getRoleIndex();
				BSLib::Database::CDBTableRow*  row = a_keyTable->getRow(dbData.getKey());
				if (row != NULL) {
					BSLib::Utility::CStream stream;
					row->serializeTo(stream);
					dbData.serializeFrom(stream);
					m_roleInstanceData.m_roleStageSystemData.m_dailyGetHelperCount = dbData.m_dailyGetHelpCount;
					m_roleInstanceData.m_roleStageSystemData.m_greedLandTickets = dbData.m_greedLandEnterCountRemaining;
					m_roleInstanceData.m_roleStageSystemData.m_lastGreedLandUpdateTime = dbData.m_lastGreedLandUpdateTime;
					m_roleInstanceData.m_roleStageSystemData.m_lastUpdateTime = dbData.m_lastUpdateTime;
				} else {
					m_roleInstanceData.m_roleStageSystemData.m_greedLandTickets = C_MAX_GREED_LAND_ENTRANCE_TICKETS;
					_updateRoleStageSystemData(m_roleInstanceData.m_roleStageSystemData);
				}
			}
		}
		break;
	default:
		;
	}

	return true;
}

bool CRoleSceneModule::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	class CChallengeRecordCallBack : public BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
	{
	public:
		CChallengeRecordCallBack(CRoleSceneModule & a_sceneMudule)
		:m_sceneMudule(a_sceneMudule)
		{
		}
		~CChallengeRecordCallBack()
		{
		}
	public:
			virtual bool exec(const std::string& _key, BSLib::Database::CDBTableRow* & _value)
			{
				if (_value != NULL) {
					BSLib::Utility::CStream stream;
					_value->serializeTo(stream);
					DB::CArenaChallgengeRecordDB data;
					data.serializeFrom(stream);
					SceneSystem::CArenaChallengeRecord challengeRecord;
					challengeRecord.m_recordID = data.m_recordID;
					challengeRecord.m_isActive = data.m_isActive;
					challengeRecord.m_isWin = data.m_isWin;
					challengeRecord.m_challengeTime = data.m_challengeTime;
					challengeRecord.m_newRank = data.m_newRank;
					challengeRecord.m_challengeeZoneID = data.m_challengeeZoneID;
					challengeRecord.m_challengeeAccountID = data.m_challengeeAccountID;
					challengeRecord.m_challengeeRoleIndex = data.m_challengeeRoleIndex;
					challengeRecord.m_challengeeTPID = data.m_challengeeTPID;
					challengeRecord.m_challengeeName = data.m_challengeeName;
					challengeRecord.m_isRevenged = data.m_isRevenged;
					m_sceneMudule.addChallengeRecord(challengeRecord);
				}
				return true;
			}
	private:
		CRoleSceneModule & m_sceneMudule;
	};

	class CRoleInstancePrizeCallBack : public BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
	{
	public:
		CRoleInstancePrizeCallBack(BSLib::Utility::CHashMap<BSLib::uint32, CRoleInstanceStarPrize> & a_hashRoleInstancePrize)
		:m_hashRoleInstancePrize(a_hashRoleInstancePrize)
		{
		}
		~CRoleInstancePrizeCallBack()
		{
		}
	public:
		virtual bool exec(const std::string& _key, BSLib::Database::CDBTableRow* & _value)
		{
			if (_value != NULL) {
				BSLib::Utility::CStream stream;
				_value->serializeTo(stream);
				DB::CRoleInstancePrizeDB data;
				data.serializeFrom(stream);
				CRoleInstanceStarPrize roleInstancePrize;
				roleInstancePrize.m_instanceTPID = data.m_instanceID;
				roleInstancePrize.m_star = data.m_star;
				m_hashRoleInstancePrize.setValue(roleInstancePrize.m_instanceTPID, roleInstancePrize);
			}
			return true;
		}
	private:
		BSLib::Utility::CHashMap<BSLib::uint32, CRoleInstanceStarPrize> & m_hashRoleInstancePrize;
	};

	class CRoleStageCallBack : public BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
	{
	public:
		CRoleStageCallBack(CRoleInstanceData & a_roleInstanceData)
		:m_roleInstanceData(a_roleInstanceData)
		{
		}
		~CRoleStageCallBack()
		{
		}
	public:
		virtual bool exec(const std::string& _key, BSLib::Database::CDBTableRow* & _value)
		{
			if (_value != NULL) {
				BSLib::Utility::CStream stream;
				_value->serializeTo(stream);
				DB::CFinishStageDataDB data;
				data.serializeFrom(stream);
				CFinishStage roleFinshStage;
				roleFinshStage.m_instanceID = data.m_instanceID;
				roleFinshStage.m_stageIndex = data.m_stageIndex;
				roleFinshStage.m_star = data.m_star;
				roleFinshStage.m_dailyEnteredTimes = data.m_dailyEnteredTimes;
				roleFinshStage.m_lastResetTime = data.m_lastResetTime;
				roleFinshStage.m_dailyRestoreCount = data.m_dailyRestoreCount;
				const CStageAttr *stageAttr = CSceneSystemDataMgr::singleton().getStageAttr(data.m_instanceID, data.m_stageIndex);
				if (stageAttr != NULL) {
					m_roleInstanceData.addStageData(roleFinshStage);
				}
			}
			return true;
		}
	private:
		CRoleInstanceData & m_roleInstanceData;
	};

	class CRoleContinuousStageResultCallBack : public BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
	{
	public:
		CRoleContinuousStageResultCallBack(CRoleContinuousStageData & roleContinuousStageResultData)
		:m_roleContinuousStageData(roleContinuousStageResultData)
		{
		}
		~CRoleContinuousStageResultCallBack()
		{
		}
	public:
		virtual bool exec(const std::string& _key, BSLib::Database::CDBTableRow* & _value)
		{
			if (_value != NULL) {
				BSLib::Utility::CStream stream;
				_value->serializeTo(stream);
				DB::CContinuousStageResultDataDB data;
				data.serializeFrom(stream);
				CContinuousStageResultData roleContinuousStageResult;
				roleContinuousStageResult.m_instanceTPID = data.m_instanceTPID;
				roleContinuousStageResult.m_stageIndex = data.m_stageIndex;
				roleContinuousStageResult.m_score = data.m_score;
				const CInstanceAttr *instanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(data.m_instanceTPID);
				if (instanceAttr != NULL) {
					m_roleContinuousStageData.addConStageResult(roleContinuousStageResult, instanceAttr);
				}
			}
			return true;
		}
	private:
		CRoleContinuousStageData & m_roleContinuousStageData;
	};

	class CRoleConInstanceProgressCallBack : public BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
	{
	public:
		CRoleConInstanceProgressCallBack(CRoleContinuousStageData & roleContinuousStageResultData)
		:m_roleContinuousStageData(roleContinuousStageResultData)
		{
		}
		~CRoleConInstanceProgressCallBack()
		{
		}
	public:
		virtual bool exec(const std::string& _key, BSLib::Database::CDBTableRow* & _value)
		{
			if (_value != NULL) {
				BSLib::Utility::CStream stream;
				_value->serializeTo(stream);
				DB::CRoleConInstanceProgressDB data;
				data.serializeFrom(stream);
				CConInstanceProgressData roleConInstanceProgressData;
				roleConInstanceProgressData.m_instanceTPID = data.m_instanceTPID;
				roleConInstanceProgressData.m_isActivated = data.m_isActivated == 1;
				roleConInstanceProgressData.m_curDayStageIndex = data.m_curDayStageIndex;
				roleConInstanceProgressData.m_maxClearStageIndex = data.m_maxClearStageIndex;
				const CInstanceAttr *instanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(data.m_instanceTPID);
				if (instanceAttr != NULL) {
					roleConInstanceProgressData.m_instanceAttr = instanceAttr;
					m_roleContinuousStageData.addConInstanceProgressData(roleConInstanceProgressData);
				}
			}
			return true;
		}
	private:
		CRoleContinuousStageData & m_roleContinuousStageData;
	};

	switch(a_tableID)
	{
	case EDBTABLEID_ROLE_SCENE_ARENA_CHALLENGE_RECORD:
		{
			m_arenaChallengeRecordTable = a_keyTable;
			if (a_sessionID == 0) {
				CChallengeRecordCallBack cb(*this);
				a_keyTable->traversal(cb);
				return true;
			}
		}	
		break;
	case EDBTABLEID_ROLE_STAGE_DATA:
		{
			m_roleStageDataTable = a_keyTable;
			if (a_sessionID == 0) {
				CRoleStageCallBack cb(m_roleInstanceData);
				a_keyTable->traversal(cb);
			}
		}
		break;
	case EDBTABLEID_ROLE_INSTANCE_PRIZE_DATA:
		{
			m_roleInstancePrizeTable = a_keyTable;
			if (a_sessionID == 0) {
				CRoleInstancePrizeCallBack cb(m_roleInstanceData.getRoleInstancPrizeMap());
				a_keyTable->traversal(cb);
				return true;
			}
		}
		break;
	case EDBTABLEID_ROLE_CONTINUOUS_INSTANCE_PROGRESS_DATA:
		{
			m_roleContinuousStageProgressTable = a_keyTable;	
			if (a_sessionID == 0) {
				CRoleConInstanceProgressCallBack cb(m_roleContinuousStageData);
				a_keyTable->traversal(cb);
				return true;
			}
		}
		break;
	case EDBTABLEID_ROLE_CONTINUOUS_STAGE_RESULT_DATA:
		{
			m_roleContinuousStageResultTable = a_keyTable;
			if (a_sessionID == 0) {
				CRoleContinuousStageResultCallBack cb(m_roleContinuousStageData);
				a_keyTable->traversal(cb);
				return true;
			}
		}
		break;
	default:
		;
	}

	return true; 
}



bool CRoleSceneModule::cbSelectGetTableData(const GSLib::SRoleKey& a_roleKey,GSLib::DBSystem::ETableKeyType a_TableKeyType,GSLib::DBSystem::CKeyIndexTablePtr& a_keyIndexTable, 
											GSLib::DBSystem::CKeyTablePtr& a_keyTable,EDBTableID a_tableID, BSLib::uint32 a_sessionID,BSLib::Utility::CStream& a_stream)
{
	return true;
}

bool CRoleSceneModule::cbSelectMultiTableData(bool a_success,BSLib::uint32 a_sessionID,void* a_ptr,PlayerSystem::GM::CRoleAllData& a_roleAllData)
{
	if (a_success) {
		if (a_sessionID == C_GET_ARENA_CHALLENGEE_DATA_SESSION) {
			_cbGetArenaChallengingData(a_roleAllData);
		} else if (a_sessionID == C_GET_HELPER_DATA_SESSION) {
			_cbGetStagehelperData(a_roleAllData);
		}
	}

	return true;
}

void CRoleSceneModule::onRoleActive()
{
	if (m_roleContinuousStageData.getLastResetTime() < CSceneSystemGM::singleton().getLastContinuousStageResetTime()) {
		//onContinuousStageDailyReset();
	}
	if (m_roleInstanceData.getLastStageGetHelpUpdateTime() < CSceneSystemGM::singleton().getLastStageHelperResetTime()) {
		onStageHelperDailyReset();
	}
	if (m_arenaData.m_lastResetTime < CSceneSystemGM::singleton().getLastArenaResetTime()) {
		onArenaReset();
	}
}

void CRoleSceneModule::onRoleInactive()
{
	exitScene();
}

void CRoleSceneModule::addChallengeRecord(SceneSystem::CArenaChallengeRecord &record)
{
	m_arenaData.addChallengeRecord(record);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqEnterScene(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgSceneSystemGC2GMReqEnterScene* msgReq = (CMsgSceneSystemGC2GMReqEnterScene*)a_msg;
	enterScene(ESCENE_TYPE_CITY, msgReq->m_sceneTPID);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqQuitScene(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	//CMsgSceneSystemGC2GMReqQuitScene* req = (CMsgSceneSystemGC2GMReqQuitScene*)a_msg;
	GSLib::SceneSystem::GM::CScene* scene = getScene();
	if(scene != NULL){
		scene->exitScene(this);
		CMsgSceneSystemGM2GCAckQuitScene ack;
		ack.m_result = EQUITSCENE_RESUlT_SUCCESS;
		sendMsgToClient(ack);
	}
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetRoleArenaData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	BSLib::int32 challengeTime = (BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
	if (m_arenaData.getCombatRole() > 0) {
		return;
	}
	m_arenaData.m_vecChallengees.clear();
	CMsgSceneSystemGM2CNReqArenaAction msgReqCN;
	msgReqCN.m_actionID = EARENA_ACTION_GET_ARENA_DATA;
	sendMsgToCenterServer(msgReqCN);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetNewArenaChallengees(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgSceneSystemGM2CNReqArenaAction msgReqCN;
	msgReqCN.m_actionID = EARENA_ACTION_GET_ARENA_CHALLENGABLE_CHALLENGEES;
	sendMsgToCenterServer(msgReqCN);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqChallengeArenaRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL || getRoleGM() == NULL) {
		return;
	}
	CMsgSceneSystemGC2GMReqChallengeArenaRole *msgReq = (CMsgSceneSystemGC2GMReqChallengeArenaRole *)a_msg;
	m_arenaData.m_challengeInfo = msgReq->m_challengeInfo;
	EEnterSceneResult result =_enterScene(ESCENE_TYPE_ARENA, C_ARENA_SCENE_ID);
	if (result == EENTER_SCENE_RESULT_SUCCESS) {
		BSLib::uint32 index = 0;
		CArenaChallengeeData challengeeData;
		if (m_arenaData.m_challengeInfo.m_type == ECHALLENGE_TYPE_RANKING_ROLE) {
			index = (BSLib::uint32)m_arenaData.m_challengeInfo.m_param;
			challengeeData = m_arenaData.m_vecChallengees[index];
		} else if (m_arenaData.m_challengeInfo.m_type == ECHALLENGE_TYPE_REVENGE) {
			const CArenaChallengeRecord * record = m_arenaData.getChallengeRecord(m_arenaData.m_challengeInfo.m_param);
			if (record != NULL) {
				challengeeData.m_accountID = record->m_challengeeAccountID;
				challengeeData.m_zoneID = record->m_challengeeZoneID;
				challengeeData.m_roleIndex = record->m_challengeeRoleIndex;
				challengeeData.m_roleName = record->m_challengeeName;
				challengeeData.m_roleTPID = record->m_challengeeTPID;

				m_arenaData.m_vecChallengees.push_back(challengeeData);
				index = m_arenaData.m_vecChallengees.size() - 1;
			}
		}
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "被挑战者index[%d], accountID[%d] zoneID[%d] RoleIndex[%d]", 
			index, challengeeData.m_accountID, challengeeData.m_zoneID, challengeeData.m_roleIndex);
		if (challengeeData.m_accountID > 0) {
			SRoleKey searchRole(challengeeData.m_accountID, challengeeData.m_zoneID, challengeeData.m_roleIndex);
			m_arenaData.setCombatRole(index);
			getRoleGM()->selectRoleData(searchRole, C_GET_ARENA_CHALLENGEE_DATA_SESSION, EMODULECTYPE_SCENE);
		}
	} else {
		CMsgSceneSystemGM2GCAckChallengeArenaRole msgAck;
		msgAck.m_result = result;
		sendMsgToClient(msgAck);
	}

}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqChallengeArenaRoleFinish(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}
	CMsgSceneSystemGC2GMReqChallengeArenaRoleFinish *msgReq = (CMsgSceneSystemGC2GMReqChallengeArenaRoleFinish *)a_msg;
	EChallengeArenaRoleFinishResult result = _canReportFinishChallengeArenaRoleResult();
	if (result != ECHALLENGE_ARENA_ROLE_FINISH_RESULT_SUCCESS) {
		CMsgSceneSystemGM2GCAckChallengeArenaRoleFinish msgAck;
		msgAck.m_result = result;
		sendMsgToClient(msgAck);
		return;
	}
	if (msgReq->m_isWin) {
		getRoleGM()->addLightPower(C_MAX_AREN_WIN_LIGHT_POWER_PRIZE, "ArenaChallenge");
	} else {
		getRoleGM()->addLightPower(C_MAX_AREN_LOSE_LIGHT_POWER_PRIZE, "ArenaChallenge");
	}

	CArenaChallengeeData &challengee = m_arenaData.m_vecChallengees[m_arenaData.m_combatRole];

	BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "竞技场挑战结束,被挑战者index[%d], accountID[%d] zoneID[%d] RoleIndex[%d]", 
		m_arenaData.m_combatRole, challengee.m_accountID, challengee.m_zoneID, challengee.m_roleIndex);

	BSLib::int32 challengeTime = (BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds();

	CArenaChallengeRecord activeRecord;
	activeRecord.m_recordID = _genArenaRecordID((BSLib::int32)challengeTime);
	activeRecord.m_isActive = true;
	activeRecord.m_challengeeZoneID = challengee.m_zoneID;
	activeRecord.m_challengeeAccountID = challengee.m_accountID;
	activeRecord.m_challengeeRoleIndex = challengee.m_roleIndex;
	activeRecord.m_challengeeTPID = challengee.m_roleTPID;
	activeRecord.m_challengeeName = challengee.m_roleName;
	activeRecord.m_isWin = msgReq->m_isWin;
	activeRecord.m_challengeTime = challengeTime;

	CArenaChallengeRecord passiveRecord;
	passiveRecord.m_recordID = _genArenaRecordID((BSLib::int32)challengeTime);
	passiveRecord.m_isActive = false;
	passiveRecord.m_challengeeZoneID = getRoleGM()->getPlayerGM()->getZoneID();
	passiveRecord.m_challengeeAccountID = getRoleGM()->getPlayerGM()->getAccountID();
	passiveRecord.m_challengeeRoleIndex = getRoleGM()->getRoleIndex();
	passiveRecord.m_challengeeTPID = getRoleGM()->getTPID();
	passiveRecord.m_challengeeName = getRoleGM()->getName();
	passiveRecord.m_isWin = !msgReq->m_isWin;
	passiveRecord.m_challengeTime = challengeTime;

	CMsgSceneSystemGM2CNReqArenaAction msgReqCN;
	msgReqCN.m_actionID = EARENA_ACTION_FINISH_ARENA_CHALLENGE;
	msgReqCN.m_challengerRecord = activeRecord;
	msgReqCN.m_challengeeRecord = passiveRecord;
	sendMsgToCenterServer(msgReqCN);

	if (m_arenaData.m_challengeInfo.m_type == ECHALLENGE_TYPE_REVENGE) {
		CArenaChallengeRecord *record = m_arenaData.getChallengeRecord(m_arenaData.m_challengeInfo.m_param);
		if (record != NULL) {
			record->m_isRevenged = true;
		}
		_updateChallengeRecordToDB(*record, getRoleGM()->getRoleKey());
	}
	CMsgSceneSystemGM2GCAckChallengeArenaRoleFinish msgAck;
	msgAck.m_result = ECHALLENGE_ARENA_ROLE_FINISH_RESULT_SUCCESS;
	sendMsgToClient(msgAck);

	GSLib::TaskSystem::GM::CRoleTaskModule *taskModule = (GSLib::TaskSystem::GM::CRoleTaskModule *)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_TASK);
	if (taskModule != NULL) {
		taskModule->updateDailyTask(GSLib::TaskSystem::GM::EDAILY_TASK_TYPE_ROLE_ARENA);
	}

	exitScene();
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqPurchaseArenaTickts(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	EPurchaseArenaTicketsResult result = _canPurchaseTicket();
	if (result == EPURCHASE_ARENA_TICKETS_SUCCESS ) {
		getRoleGM()->delDiamond(m_arenaData.getArenaTicketPrice(), "BuyArenaTicket");
		++m_arenaData.m_dailyTicketPurchasedCount;
		m_arenaData.setArenaTicketCount(m_arenaData.getArenaTicketCount() + C_MAX_ARENA_TICKETS_PER_PURCHASE);			
		_updateChallengeDataToDB();
	}
	CMsgSceneSystemGM2GCAckPurchaseArenaTickts msgAck;
	msgAck.m_result = result;
	msgAck.m_curTicketCount = m_arenaData.getArenaTicketCount();
	msgAck.m_nextTicketPrice = m_arenaData.getArenaTicketPrice();
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetStroyInstanceProgress(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgSceneSystemGM2GCAckGetStroyInstanceProgress msgAck;
	msgAck.m_instanceID = m_roleInstanceData.getProgressInstanceTPID();
	msgAck.m_stageIndex = m_roleInstanceData.getProgressStageIndex();
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetInstanceData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}
	CMsgSceneSystemGC2GMReqGetInstanceData *msgReq = (CMsgSceneSystemGC2GMReqGetInstanceData *)a_msg;
	BSLib::int32 instanceID = msgReq->m_instanceID;
	CMsgSceneSystemGM2GCAckGetInstanceData msgAck;

	CFinishInstanceData * instanceData = m_roleInstanceData.getFinishInstanceData(instanceID);
	EGetInstanceDataResult result(EGET_INSTANCE_DATA_RESULT_SUCCESS);
	_resetInstanceStage(instanceID);
	if (instanceData != NULL) {
		msgAck.m_vecStage = instanceData->getStages();
	}
	msgAck.m_result = result;
	msgAck.m_instanceID = instanceID;
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqEnterStage(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL || getRoleGM() == NULL) {
		return;
	}

	EEnterSceneResult result(EENTER_SCENE_RESULT_NOT_EXIST);
	CMsgSceneSystemGC2GMReqEnterStage *msgReq = (CMsgSceneSystemGC2GMReqEnterStage *)a_msg;
	const CStageAttr * stageAttr= CSceneSystemDataMgr::singleton().getStageAttr(msgReq->m_instanceID, msgReq->m_stageIndex);
	_resetInstanceStage(msgReq->m_instanceID);
	if (stageAttr != NULL) {
		if (msgReq->m_helperKey.getAccountID()> 0) {
			m_roleInstanceData.m_tryEnterStageAttr = stageAttr;
			if (stageAttr->getSceneType() == ESCENE_TYPE_STAGE) {
				EEnterSceneResult helpResult = _canGetStageHelper(msgReq->m_instanceID, msgReq->m_stageIndex, msgReq->m_helperKey);
				if (helpResult == EENTER_SCENE_RESULT_SUCCESS) {
					getRoleGM()->selectRoleData(msgReq->m_helperKey, C_GET_HELPER_DATA_SESSION, EMODULECTYPE_SCENE);
					return;
				} 
				result = helpResult;
			} 
		} else {
			result = _enterScene(stageAttr->getSceneType(), stageAttr->getSceneTPID());
		}
	}
	CMsgSceneSystemGM2GCAckEnterStage msgAck;
	if (result == EENTER_SCENE_RESULT_SUCCESS) {
		if (m_curScene != NULL) {
			msgAck.m_stageMonster = m_curScene->getStageMonsterPrize();
		}
	}
	msgAck.m_result = result ;
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqStageResultReport(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}
	if (m_curScene == NULL) {
		return;
	}
	CMsgSceneSystemGC2GMReqStageResultReport *msgReq = (CMsgSceneSystemGC2GMReqStageResultReport *)a_msg;
	CStageReportResult reportResult;
	reportResult.m_isWin = msgReq->m_isWin;
	reportResult.m_star = msgReq->m_star;
	reportResult.m_useTime = msgReq->m_useTime;
	reportResult.m_clearedRandomMonster = msgReq->m_clearedRandomMonster;
	m_curScene->reportStageResult(*this, reportResult);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqDetermineStagePrizeItem(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgSceneSystemGC2GMReqDetermineStagePrizeItem *msgReq = (CMsgSceneSystemGC2GMReqDetermineStagePrizeItem *)a_msg;
	EDetermineStagePrizeItemResult result = EDETERMINE_STAGE_PRIZE_ITEM_FAIL;
	if (msgReq != NULL) {
		result = _canDetermineStagePrizeResult();
	}
	if (result == EDETERMINE_STAGE_PRIZE_ITEM_SUCCESS) {
		if (m_curScene != NULL) {
			m_curScene->determineStagePrizeItem(*this, msgReq->m_receiveItems);
			exitScene();
		}
	}
	CMsgSceneSystemGM2GCAckDetermineStagePrizeItem msgAck;
	msgAck.m_result = result;
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqClearStage(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}
	CMsgSceneSystemGC2GMReqClearStage * msgReq = (CMsgSceneSystemGC2GMReqClearStage *)a_msg;
	EClearStageResult result = _canClearStage(msgReq->m_instanceID, msgReq->m_stageIndex);
	CMsgSceneSystemGM2GCAckClearStage msgAck;
	if (result != ECLEAR_STAGE_RESULT_SUCCESS ) {
		msgAck.m_result = result;
		sendMsgToClient(msgAck);
		return;
	}
	const CStageAttr *stageAttr = CSceneSystemDataMgr::singleton().getStageAttr(msgReq->m_instanceID, msgReq->m_stageIndex);
	if (stageAttr != NULL) {
		CSceneStage scene(stageAttr->getSceneType(), stageAttr);
		scene.clearStage(*this, msgReq->m_breakDownItem);
	}
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetInstanceStarPrize(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}
	CMsgSceneSystemGC2GMReqGetInstanceStarPrize *msgReq =(CMsgSceneSystemGC2GMReqGetInstanceStarPrize *)a_msg;
	EGetInstanceStarPrizeResult result = _canGetInstanceStarPrize(msgReq->m_instanceTPID);
	if (result != EGET_INSTANCE_PRIZE_RESULT_SUCCESS) {
		CMsgSceneSystemGM2GCAckGetInstanceStarPrize msgAck;
		msgAck.m_result = result;
		sendMsgToClient(msgAck);
		return;
	}
	std::vector<ItemSystem::GM::CPrizeItem> vecPrizeItem;
	const CInstanceStarPrizeAttr *instanceStarPrizeAttr = CSceneSystemDataMgr::singleton().getInstanceStarPrizeAttr(msgReq->m_instanceTPID);
	if (instanceStarPrizeAttr != NULL) {
		BSLib::uint16 curInstancePrizeStar = m_roleInstanceData.getCurrentInstancePrizeStar(msgReq->m_instanceTPID);
		BSLib::uint16 nextInstancePrizeStar = instanceStarPrizeAttr->getNextStarLevel(curInstancePrizeStar);
		PrizeSystem::GM::CRolePrizeModule *prizeModue = (PrizeSystem::GM::CRolePrizeModule *)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PRIZE);
		if (prizeModue != NULL) {
			const CInstanceStarPrizeAttr *instancePrizeAttr = CSceneSystemDataMgr::singleton().getInstanceStarPrizeAttr(msgReq->m_instanceTPID);
			if (instancePrizeAttr != NULL) {
				instancePrizeAttr->getStarLevelPrize(nextInstancePrizeStar, vecPrizeItem);
				prizeModue->prizeRequest(vecPrizeItem, toMailString("系统信息"), toMailString("副本星级奖励(背包满)"), toMailString("恭喜您!获得了丰厚的奖励，奖励如下："), "GetInstanceStarPrize");//todo
			}
			CRoleInstanceStarPrize *instancePrize = m_roleInstanceData.getInstanceStarPrize(msgReq->m_instanceTPID);
			if (instancePrize != NULL) {
				instancePrize->m_instanceTPID = msgReq->m_instanceTPID;
				instancePrize->m_star = nextInstancePrizeStar;
				_updateRoleInstanceStarPrize(*instancePrize);
			} else {
				CRoleInstanceStarPrize prize;
				prize.m_instanceTPID = msgReq->m_instanceTPID;
				prize.m_star = nextInstancePrizeStar;
				m_roleInstanceData.addInstancePrizeData(prize);
				_updateRoleInstanceStarPrize(prize);
		   }
		}
	}
	CMsgSceneSystemGM2GCAckGetInstanceStarPrize msgAck;
	msgAck.m_result = result;
	msgAck.m_vecPrizeItem = vecPrizeItem;
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetIntanceStarPrizeProgress(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}
	CMsgSceneSystemGC2GMReqGetIntanceStarPrizeProgress *msgReq = (CMsgSceneSystemGC2GMReqGetIntanceStarPrizeProgress *)a_msg;
	CMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress	msgAck;
	msgAck.m_instanceTPID = msgReq->m_instanceTPID;
	msgAck.m_star = m_roleInstanceData.getNextInstancePrizeStar(msgReq->m_instanceTPID);
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqRoleMove(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	//CMsgSceneSystemGC2GMReqRoleMove* msgReq = (CMsgSceneSystemGC2GMReqRoleMove*)a_msg;
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetContinuousInstanceData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}

	CMsgSceneSystemGC2GMReqGetContinuousInstanceData *msgReq = (CMsgSceneSystemGC2GMReqGetContinuousInstanceData *)a_msg;
	EGetContinuousInstanceDataResult result(EGET_CONTINUOUS_INSTANCE_SUCCESS);
	const CInstanceAttr * instanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(msgReq->m_instanceTPID);
	if (instanceAttr == NULL) {
		result = EGET_CONTINUOUS_INSTANCE_NO_SUCN_INSTANCE;
	}
	if (instanceAttr->getInstanceType() != EINSTANCE_TYPE_CONTINUOUS_STAGE) {
		result = EGET_CONTINUOUS_INSTANCE_INSTANCE_NOT_CONTINUOUS_STAGE_INSTANCE;
	}
	CMsgSceneSystemGM2GCAckGetContinuousInstanceData msgAck;
	msgAck.m_instanceTPID = msgReq->m_instanceTPID;
	if (result == EGET_CONTINUOUS_INSTANCE_SUCCESS) {
		const CConInstanceProgressData * conInstanceProgress = m_roleContinuousStageData.getConInstanceProgressData(msgReq->m_instanceTPID); 
		if (conInstanceProgress != NULL) {
			msgAck.m_stageIndex = conInstanceProgress->m_curDayStageIndex;
		}
	}
	msgAck.m_result = result;
	msgAck.m_dailyFreeRollFastClearStageCount = m_roleContinuousStageData.getDailyFreeRollFastClearStageCount();
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqEnterContinuousStage(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}
	EEnterSceneResult result(EENTER_CON_STAGE_RESULT_NO_SUCH_STAGE_INDEX);
	CMsgSceneSystemGC2GMReqEnterContinuousStage *msgReq = (CMsgSceneSystemGC2GMReqEnterContinuousStage *)a_msg;
	const CStageAttr * stageAttr= CSceneSystemDataMgr::singleton().getContinuousStageAttr(msgReq->m_instanceTPID, msgReq->m_stageIndex);
	if (stageAttr != NULL) {
		if (stageAttr->getSceneType() == ESCENE_TYPE_CONTINUOUS_STAGE) {
			result = _enterScene(ESCENE_TYPE_CONTINUOUS_STAGE, stageAttr->getSceneTPID());
		}
	}
	CMsgSceneSystemGM2GCAckEnterContinuousStage msgAck;
	msgAck.m_result = result ;
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqReportContinuousStageResult(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}
	CMsgSceneSystemGM2GCAckReportContinuousStageResult msgAck;
	msgAck.m_result = EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_SUCCESS;
	CMsgSceneSystemGC2GMReqReportContinuousStageResult *msgReq = (CMsgSceneSystemGC2GMReqReportContinuousStageResult *)a_msg;
	if (msgReq->m_isWin) {
		EReportContinuousStageResultResult result = _canReportConStageResult();
		if (result == EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_SUCCESS) {
			CConInstanceProgressData conInstanceProgress;
			CContinuousStageResultData conStageResult;
			//TODO 更新积分
			BSLib::uint32 curInstanceTPID = m_roleContinuousStageData.getCurEnteredConInstanceTPID();
			BSLib::uint16 curStageIndex = m_roleContinuousStageData.getCurEnteredConStageIndex();
			BSLib::uint32 lastScore = m_roleContinuousStageData.getConStageScore(curInstanceTPID, curStageIndex);
			if (msgReq->m_score > lastScore) {
				RankSystem::GM::CRoleRankModule * rankModule = static_cast<RankSystem::GM::CRoleRankModule*>(getRoleGM()->getPlayerModuleGM(EMODULECTYPE_RANK));
				if (rankModule != NULL) {
					rankModule->update(RankSystem::ERANKID_INFINITE, msgReq->m_score - lastScore);
				}
			}
			msgAck.m_lastScore = lastScore;
			m_roleContinuousStageData.reportConStageResult(msgReq->m_score, conStageResult, conInstanceProgress);
			_updateRoleContinuousInstanceProgressData(conInstanceProgress);
			_updateRoleContinuousInstanceResultData(conStageResult);
			const CStageAttr *stageAttr = CSceneSystemDataMgr::singleton().getContinuousStageAttr(curInstanceTPID, curStageIndex);
			std::vector<ItemSystem::GM::CPrizeItem> vecPrizeItem;
			if (stageAttr != NULL) {
				getRoleGM()->modifyExp(stageAttr->m_prizeExp, "", true);
				getRoleGM()->modifyGold(stageAttr->m_prizeGold, "");
				PrizeSystem::GM::CRolePrizeModule *prizeModue = (PrizeSystem::GM::CRolePrizeModule *)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PRIZE);
				if (prizeModue != NULL) {
					BSLib::uint32 dropItemTable = stageAttr->getDropItem(1);
					_getStagePrizeItem(dropItemTable, vecPrizeItem);
					prizeModue->prizeRequest(vecPrizeItem, toMailString("系统信息"), toMailString("副本掉落道具(背包满)"), toMailString("恭喜您!通关副本，获得了丰厚的奖励，奖励如下："), "InstancePrize");//todo
					announceItem(stageAttr->getName() ,vecPrizeItem);
				}
				msgAck.m_stagePrize.m_exp = stageAttr->m_prizeExp;
				msgAck.m_stagePrize.m_gold = stageAttr->m_prizeGold;
				msgAck.m_stagePrize.m_vecPrizeItem = vecPrizeItem;
			}
			//成就相关
			BSLib::uint32 curMaxClearStageIndex = conInstanceProgress.getMaxClearStageIndex();
			if (curStageIndex > curMaxClearStageIndex) {
				_updateContinuousInstanceAchieve(curMaxClearStageIndex);
			}
		}
		msgAck.m_result = result;
	}

	exitScene();
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqRollFastClearContinuousStageNum(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}
	CMsgSceneSystemGC2GMReqRollFastClearContinuousStageCount *msgReq = static_cast<CMsgSceneSystemGC2GMReqRollFastClearContinuousStageCount *>(a_msg);	
	CMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum msgAck;
	ERollFastClearContinuousStageNum  result = _canRollFastClearContinuousStageNum(msgReq->m_instanceTPID);
	if (result == EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_SUCCESS) {
		BSLib::uint32 rollNum = BSLib::Utility::CRandom::randomBetween(1,6);
		msgAck.m_rollNum = rollNum;
		CConInstanceProgressData *conInstanceProgress = m_roleContinuousStageData.getConInstanceProgressData(msgReq->m_instanceTPID);
		if (conInstanceProgress != NULL) {
			BSLib::uint32 curStageIndex = conInstanceProgress->getCurDayStageIndex();
			BSLib::uint32 finalStageIndex = curStageIndex + rollNum > conInstanceProgress->getMaxClearStageIndex() ? conInstanceProgress->getMaxClearStageIndex() : curStageIndex + rollNum;
			msgAck.m_finalStageIndex = finalStageIndex;
			if (finalStageIndex > curStageIndex) {
				for (BSLib::uint32 index = curStageIndex; index < finalStageIndex; ++index) {
					const CStageAttr *stageAttr = CSceneSystemDataMgr::singleton().getStageAttr(msgReq->m_instanceTPID, index);
					if (stageAttr != NULL) {
						CStagePrize stagePrize;
						stagePrize.m_exp = stageAttr->getExp();
						stagePrize.m_gold = stageAttr->getGold();
						BSLib::uint32 dropItemTableID = stageAttr->getDropItem(1);
						getRoleGM()->modifyExp(stagePrize.m_exp, "", true);
						getRoleGM()->modifyGold(stagePrize.m_gold, "");
						PrizeSystem::GM::CRolePrizeModule *prizeModue = (PrizeSystem::GM::CRolePrizeModule *)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PRIZE);
						if (prizeModue != NULL) {
							//BSLib::uint32 dropItemTable = stageAttr->getDropItem(dropItemTableID);
							_getStagePrizeItem(dropItemTableID, stagePrize.m_vecPrizeItem);
							prizeModue->prizeRequest(stagePrize.m_vecPrizeItem, toMailString("系统信息"), toMailString("副本掉落道具(背包满)"), toMailString("恭喜您!通关副本，获得了丰厚的奖励，奖励如下："), "FastClearContinuousStagePrize");//todo
							msgAck.m_vecStagePrize.push_back(stagePrize);
						}
						msgAck.m_vecStagePrize.push_back(stagePrize);
					}
				}
				conInstanceProgress->setCurDayStageIndex(finalStageIndex);
				_updateRoleContinuousInstanceProgressData(*conInstanceProgress);
			}
			if (m_roleContinuousStageData.getDailyFreeRollFastClearStageCount() > 0) {
				m_roleContinuousStageData.setDailyFreeRollFastClearStageCount(m_roleContinuousStageData.getDailyFreeRollFastClearStageCount() - 1);
				_updateRoleConInstanceData(m_roleContinuousStageData.getRoleConInstanceBriefData());
			}
			//成就相关
			_updateRollContiuousStageFastClearCountAchieve();
		}
	}
	msgAck.m_result = result;
	msgAck.m_dailyFreeRollFastClearStageCount = m_roleContinuousStageData.getDailyFreeRollFastClearStageCount();
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqResetContinuousInstance(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}
	CMsgSceneSystemGC2GMReqResetContinuousInstance *msgReq = static_cast<CMsgSceneSystemGC2GMReqResetContinuousInstance*>(a_msg);
	EResetContinuousInstanceResult result =_canResetContinuousInstance(msgReq->m_instanceTPID);
	if (result == ERESET_CONTINUOUS_INSTANCE_RESULT_SUCCESS) {
		CConInstanceProgressData * conInstancePregress = m_roleContinuousStageData.getConInstanceProgressData(msgReq->m_instanceTPID);
		if (conInstancePregress != NULL) {
			conInstancePregress->setCurDayStageIndex(0);
			_updateRoleContinuousInstanceProgressData(*conInstancePregress);
			BSLib::uint32 dailyActivatedCount = m_roleContinuousStageData.getDailyActivateInstanceCount();
			if (dailyActivatedCount > 0) {
				m_roleContinuousStageData.setDailyActivateInstanceCount(dailyActivatedCount - 1);
				_updateRoleConInstanceData(m_roleContinuousStageData.getRoleConInstanceBriefData());
			}
		}
	}
	CMsgSceneSystemGM2GCAckResetContinuousInstance msgAck;
	msgAck.m_result = result;
	msgAck.m_instanceTPID = msgReq->m_instanceTPID;
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onMsgSceneSystemCN2GMAckArenaAction(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgSceneSystemCN2GMAckArenaAction *msgAck = (CMsgSceneSystemCN2GMAckArenaAction *)a_msg;
	if (msgAck == NULL) {
		return;
	}
	switch (msgAck->m_actionID) 
	{
	case EARENA_ACTION_GET_ARENA_DATA:
		{
			_onGetArenaDataFromCNServer(*msgAck);
		}
		break;
	case EARENA_ACTION_GET_ARENA_CHALLENGABLE_CHALLENGEES:
		{
			_onGetArenaChallengableRolesFromCNServer(*msgAck);	
		}
	case EARENA_ACTION_FINISH_ARENA_CHALLENGE:
		{
			_onFinishChallengeFromCNServer(*msgAck);	
		}
		break;
	default:
		break;
	}
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqEnterRandomStage(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}
	CMsgSceneSystemGC2GMReqEnterRandomStage* msgReq = (CMsgSceneSystemGC2GMReqEnterRandomStage*)a_msg;
	EEnterSceneResult result = _enterScene(ESCENE_TYPE_RANDOM_STAGE, msgReq->m_stageTPID);

	CMsgSceneSystemGM2GCAckEnterRandomStage msgAck;
	msgAck.m_result = result;
	if (result == EENTER_SCENE_RESULT_SUCCESS) {
		if (m_curScene != NULL) {
			msgAck.m_stageMonster = m_curScene->getStageMonsterPrize();
		}
	}
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqRoleRevive(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	ESceneRoleReviveResult result = _canRevive();		
	if (result == SCENE_ROLE_REVIVE_RESULT_SUCCESS ) {
		BSLib::int32 nextCount = m_reviveCount + 1;	
		BSLib::uint32 requiredDiamond = (BSLib::uint32)(8 + ::pow(2.2, nextCount));
		getRoleGM()->delDiamond(requiredDiamond, "");
		++m_reviveCount;
	}
	CMsgSceneSystemGM2GCAckRoleRevive msgAck;
	msgAck.m_result = result;
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqRestoreStageTickets(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgSceneSystemGC2GMReqRestoreStageTickets *msgReq = (CMsgSceneSystemGC2GMReqRestoreStageTickets *)a_msg;	
	if (msgReq == NULL) {
		return;
	}
	ERestoreStageTicketsResult result = _canRestoreStageTicket(msgReq->m_instanceTPID, msgReq->m_stageIndex);
	CMsgSceneSystemGM2GCAckRestoreStageTickets msgAck;
	msgAck.m_result = result;
	msgAck.m_instanceTPID = msgReq->m_instanceTPID;
	msgAck.m_stageIndex = msgReq->m_stageIndex;
	if (result == ERESTORE_STAGE_TICKETS_SUCCESS) {
		CFinishStage *finishStage = m_roleInstanceData.getStage(msgReq->m_instanceTPID, msgReq->m_stageIndex);
		if (finishStage != NULL) {
			getRoleGM()->delDiamond(finishStage->getNextRestoreStageRequireDiamond(), "Restore Stage Ticket");
			++finishStage->m_dailyRestoreCount;
			finishStage->m_dailyEnteredTimes = 0;
			_updateRoleFinishStageDataTable(*finishStage);
			msgAck.m_nextRestoreRequireDiamond = finishStage->getNextRestoreStageRequireDiamond();
			const CStageAttr *stageAttr = CSceneSystemDataMgr::singleton().getStageAttr(msgReq->m_instanceTPID, msgReq->m_stageIndex);
			if (stageAttr != NULL) {
				msgAck.m_ticketCount = stageAttr->m_dailyEnterCount;
			}
		}
	}
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onMsgSceneSystemGC2GMReqGetGreedLandInfo(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgSceneSystemGM2GCAckGetGreedLandInfo	msgAck;
	_updateGreedLandInfo();
	msgAck.m_greedLandInfo.m_curTickets = m_roleInstanceData.getGreedLandTicketsCount();
	msgAck.m_greedLandInfo.m_maxTicketsCount = C_MAX_GREED_LAND_ENTRANCE_TICKETS;
	if (msgAck.m_greedLandInfo.m_maxTicketsCount >= C_MAX_GREED_LAND_ENTRANCE_TICKETS) {
		msgAck.m_greedLandInfo.m_nextUpdateTimeRemaining = C_GREED_LAND_TICKETSUPDATE_SECONDS;
	}
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::onContinuousStageDailyReset()
{
	m_roleContinuousStageData.onDailyRest();
	_updateRoleConInstanceData(m_roleContinuousStageData.getRoleConInstanceBriefData());
	const BSLib::Utility::CHashMap<BSLib::uint32, CConInstanceProgressData> & conInstanceHashMap = m_roleContinuousStageData.getConInstanceDataMap();
	for (BSLib::Utility::CHashMap<BSLib::uint32, CConInstanceProgressData>::const_iterator itr = conInstanceHashMap.begin(); itr != conInstanceHashMap.end(); ++itr) {
		_updateRoleContinuousInstanceProgressData(itr->second);		
	}
}

void CRoleSceneModule::onStageHelperDailyReset()
{
	m_roleInstanceData.onRoleStageGetHelpReset();
	_updateRoleStageSystemData(m_roleInstanceData.m_roleStageSystemData);
}

void CRoleSceneModule::onArenaReset()
{
	m_arenaData.reset();
	_updateChallengeDataToDB();
}

void CRoleSceneModule::announceItem(const std::string & a_sceneName, const std::vector<ItemSystem::GM::CPrizeItem> & a_prizeItemList)
{
	if (getRoleGM() == NULL) {
		return;
	}
	ChatSystem::GM::CRoleChatModule *chatRole = getRoleGM()->getChatModule();
	if (chatRole == NULL) {
		return;
	}
	for (std::vector<ItemSystem::GM::CPrizeItem>::const_iterator itr = a_prizeItemList.begin(); itr != a_prizeItemList.end(); ++itr) {
		ItemSystem::GM::CItemDataGM* item = ItemSystem::GM::CItemGMMgr::singleton().getItem(itr->m_itemTPID);
		if (item != NULL) {
			if (item->enableAnnounce()) {
				std::string content(toMailString("恭喜"));
				content.append(getRoleGM()->getName());
				content.append(toMailString("在通关"));
				content.append(a_sceneName);
				content.append(toMailString("关卡,获得高级道具【"));
				content.append(item->getName());
				content.append(toMailString("】"));
				ChatSystem::GM::CChatContent chatContent;
				chatContent.m_content = content;
				EquipSystem::GM::CRoleEquipGM equip;
				chatContent.m_hasEquip = true;
				equip.setEquipTPID(item->getTPID());
				equip.serializeTo(chatContent.m_equipStream);
				chatRole->sendAnnounce(chatContent);
			}
		}
	}
}

void CRoleSceneModule::enterScene(ESceneType a_sceneType, BSLib::uint32 a_sceneTPID)
{
	CScene *scene = CSceneMgr::singleton().allocateScene(a_sceneType, a_sceneTPID);
	if (scene != NULL) {
		EEnterSceneResult result = (EEnterSceneResult)scene->canEnterScene(this);
		if (result == EENTER_SCENE_RESULT_SUCCESS) {
			if (m_curScene != NULL) {
				m_curScene->exitScene(this);
			}
			scene->enterScene(this);
			m_curScene = scene;
		} 
		CMsgSceneSystemGM2GCAckEnterScene msgAck;
		msgAck.m_result = result;
		msgAck.m_roleSceneID = a_sceneTPID;
		for (std::set<SRoleKey>::iterator itr = m_curScene->m_setSceneRole.begin(); itr != m_curScene->m_setSceneRole.end(); ++itr) {
			PlayerSystem::GM::CRoleGM * sceneRole = PlayerSystem::GM::CPlayerGMMgr::singleton().getRoleGM(*itr);
			if (sceneRole != NULL) {
				if (sceneRole != getRoleGM()) {
					CSceneRoleInfo sceneRoleInfo;
					sceneRoleInfo.m_roleKey = sceneRole->getRoleKey();
					sceneRoleInfo.m_roleTPID = sceneRole->getTPID();
					sceneRoleInfo.m_roleName = sceneRole->getName();
					sceneRoleInfo.m_level = sceneRole->getLevel();
					sceneRoleInfo.m_VIPLevel = sceneRole->getVipLevel();
					EquipSystem::GM::CRoleEquipModule *equipMudule = sceneRole->getEquipModule();
					if (equipMudule != NULL) {
						sceneRoleInfo.m_fashionTPID = equipMudule->getFashionTPID();
					}
					msgAck.m_vecSceneRoles.push_back(sceneRoleInfo);
				}
			}
		}
		sendMsgToClient(msgAck);
	}
}

void CRoleSceneModule::exitScene()
{
	if (m_curScene != NULL) {
		m_curScene->exitScene(this);
		m_curScene = NULL;
	}
	m_reviveCount = 0;
}

void CRoleSceneModule::getSceneRoles(std::vector<CSceneRoleInfo> & a_vecSceneRoles)
{
	if (m_curScene != NULL) {
		if (m_curScene->getSceneType() == ESCENE_TYPE_CITY) {
			for (std::set<SRoleKey>::iterator itr = m_curScene->m_setSceneRole.begin(); itr != m_curScene->m_setSceneRole.end(); ++itr) {
				PlayerSystem::GM::CRoleGM * sceneRole = PlayerSystem::GM::CPlayerGMMgr::singleton().getRoleGM(*itr);
				if (sceneRole != NULL) {
					if (sceneRole != getRoleGM()) {
						CSceneRoleInfo sceneRoleInfo;
						sceneRoleInfo.m_roleKey = sceneRole->getRoleKey();
						sceneRoleInfo.m_roleTPID = sceneRole->getTPID();
						sceneRoleInfo.m_roleName = sceneRole->getName();
						sceneRoleInfo.m_level = sceneRole->getLevel();
						sceneRoleInfo.m_VIPLevel = sceneRole->getVipLevel();
						sceneRoleInfo.m_combatPower = sceneRole->getCombat();
						a_vecSceneRoles.push_back(sceneRoleInfo);
					}
				}
			}
		}
	}
}

void CRoleSceneModule::setCurScene(CScene* a_scene)
{
	m_curScene = a_scene;
}

CScene *CRoleSceneModule::getScene() const
{
	return m_curScene;
}

CRoleInstanceData & CRoleSceneModule::getRoleInstanceData()
{
	return m_roleInstanceData;
}

CRoleContinuousStageData & CRoleSceneModule::getRoleConStageData()
{
	return m_roleContinuousStageData;
}

EEnterSceneResult CRoleSceneModule::_enterScene(ESceneType a_sceneType, SceneTPID a_TPID)
{
	GSLib::SceneSystem::GM::CScene* scene = GSLib::SceneSystem::GM::CSceneMgr::singleton().allocateScene(a_sceneType, a_TPID);
	if (scene == NULL) {
		return EENTER_SCENE_RESULT_FAIL;
	}
	EEnterSceneResult result =  scene->canEnterScene(this);
	if(result != EENTER_SCENE_RESULT_SUCCESS){
		return result;
	}
	GSLib::SceneSystem::GM::CScene* currentScenGM = getScene();
	if (currentScenGM != NULL){
		currentScenGM->exitScene(this);
	}
	scene->enterScene(this);
	m_curScene = scene;
	return EENTER_SCENE_RESULT_SUCCESS;
}

void CRoleSceneModule::_updateChallengeDataToDB()
{
	if (m_arenaDataTable == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "updateChallengeDataToDB:m_arenaDataTable is NULL");
		return;
	}
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "updateChallengeDataToDB:getRoleGM OR getRoleGM()->getPlayerGM() error");
		return;
	}
	GSLib::PlayerSystem::GM::CRoleGM *roleGM = getRoleGM();
	DB::CRoleArenaDataDB roleArenaDataDB;
	roleArenaDataDB.m_zoneID = roleGM->getZoneID();
	roleArenaDataDB.m_accountID = roleGM->getAccountID();
	roleArenaDataDB.m_roleIndex = roleGM->getRoleIndex();
	roleArenaDataDB.m_arenaTicketCount = m_arenaData.m_arenaTicketCount;
	roleArenaDataDB.m_dailyTicketHasPurchasedCount = m_arenaData.m_dailyTicketPurchasedCount;
	roleArenaDataDB.m_lastChallengeTime = m_arenaData.m_lastChallengeTime;
	roleArenaDataDB.m_dailyCoolDownCount = m_arenaData.m_dailyCoolDownCount;
	roleArenaDataDB.m_lastResetTime = m_arenaData.m_lastResetTime;
	BSLib::Utility::CStream stream;
	roleArenaDataDB.serializeTo(stream);
	m_arenaDataTable->update(roleArenaDataDB.getKey(), stream);
	m_arenaDataTable->saveDataToDBServer(roleArenaDataDB.getKey(), true);
}

void CRoleSceneModule::_updateChallengeRecordToDB(CArenaChallengeRecord &a_record, const GSLib::SRoleKey & a_roleKey)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "updateChallengeRecordToDB:getRoleGM OR getRoleGM()->getPlayerGM() error");
		return;
	}
	DB::CArenaChallgengeRecordDB record;
	record.m_accountID = a_roleKey.getAccountID();
	record.m_zoneID = a_roleKey.getZoneID();
	record.m_roleIndex = a_roleKey.getIndex();
	record.m_recordID = a_record.m_recordID;
	record.m_isActive = a_record.m_isActive;
	record.m_isWin = a_record.m_isWin;
	record.m_challengeTime = a_record.m_challengeTime;
	record.m_newRank = a_record.m_newRank;
	record.m_challengeeZoneID = a_record.m_challengeeZoneID;
	record.m_challengeeAccountID = a_record.m_challengeeAccountID;
	record.m_challengeeRoleIndex = a_record.m_challengeeRoleIndex;
	record.m_challengeeTPID = a_record.m_challengeeTPID;
	record.m_challengeeName = a_record.m_challengeeName;
	record.m_isRevenged = a_record.m_isRevenged;
	BSLib::Utility::CStream stream;
	record.serializeTo(stream);
	m_arenaChallengeRecordTable->update(record.getDBKey(), stream);
	m_arenaChallengeRecordTable->saveDataToDBServer(record.getDBKey(), record.getIndexKey(), true);
}

void CRoleSceneModule::_updateStoryInstanceProgressTable(const CRoleStoryInstanceProgress &a_storyInstanceProgress)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "updateStoryInstanceProgressTable:getRoleGM OR getRoleGM()->getPlayerGM() error");
		return;
	}
	DB::CRoleStoryInstanceProgressDB roleInstanceProgressDB;
	roleInstanceProgressDB.m_accountID = getRoleGM()->getAccountID();
	roleInstanceProgressDB.m_zoneID = getRoleGM()->getZoneID();
	roleInstanceProgressDB.m_roleIndex = getRoleGM()->getRoleIndex();
	roleInstanceProgressDB.m_instanceID = a_storyInstanceProgress.m_instanceTPID;
	roleInstanceProgressDB.m_stageIndex = a_storyInstanceProgress.m_stageIndex;
	m_roleInstanceData.setStoryInstanceProgress(a_storyInstanceProgress);
	BSLib::Utility::CStream stream;
	roleInstanceProgressDB.serializeTo(stream);
	m_roleStoryInstanceProgressTable->update(roleInstanceProgressDB.getKey(), stream);
	m_roleStoryInstanceProgressTable->saveDataToDBServer(roleInstanceProgressDB.getKey(), true);
}

void CRoleSceneModule::_updateRoleFinishStageDataTable(CFinishStage & a_finishStageData)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "updateRoleFinishStageDataTable:getRoleGM OR getRoleGM()->getPlayerGM() error");
		return;
	}
	DB::CFinishStageDataDB stageDataDB;
	stageDataDB.m_accountID = getRoleGM()->getAccountID();
	stageDataDB.m_zoneID = getRoleGM()->getZoneID();
	stageDataDB.m_roleIndex = getRoleGM()->getRoleIndex();
	stageDataDB.m_instanceID = a_finishStageData.m_instanceID;
	stageDataDB.m_stageIndex = a_finishStageData.m_stageIndex;
	stageDataDB.m_star = a_finishStageData.m_star;
	stageDataDB.m_dailyEnteredTimes = a_finishStageData.m_dailyEnteredTimes;
	stageDataDB.m_lastResetTime = a_finishStageData.m_lastResetTime;
	stageDataDB.m_dailyRestoreCount = a_finishStageData.m_dailyRestoreCount;
	BSLib::Utility::CStream stream;
	stageDataDB.serializeTo(stream);
	m_roleStageDataTable->update(stageDataDB.getDBKey(), stageDataDB.getIndexKey(), stream);
	m_roleStageDataTable->saveDataToDBServer(stageDataDB.getDBKey(), stageDataDB.getIndexKey(), true);
}

void CRoleSceneModule::_updateRoleInstanceStarPrize(CRoleInstanceStarPrize & a_instanceStarPrize)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "updateRoleInstanceStarPrize:getRoleGM OR getRoleGM()->getPlayerGM() error");
		return;
	}
	DB::CRoleInstancePrizeDB prizeDB;
	prizeDB.m_accountID = getRoleGM()->getAccountID();
	prizeDB.m_zoneID = getRoleGM()->getZoneID();
	prizeDB.m_roleIndex = getRoleGM()->getRoleIndex();
	prizeDB.m_instanceID = a_instanceStarPrize.m_instanceTPID;
	prizeDB.m_star = a_instanceStarPrize.m_star;
	BSLib::Utility::CStream stream;
	prizeDB.serializeTo(stream);
	m_roleInstancePrizeTable->update(prizeDB.getDBKey(), prizeDB.getIndexKey(), stream);
	m_roleInstancePrizeTable->saveDataToDBServer(prizeDB.getDBKey(), prizeDB.getIndexKey(), true);
}

void CRoleSceneModule::_updateRoleConInstanceData(const CRoleConInstanceBriefData & a_roleConInstanceBriefData)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "_updateRoleContinuousStageProgressData:getRoleGM OR getRoleGM()->getPlayerGM() error");
		return;
	}
	DB::CRoleConInstanceBriefDataDB conInstanceBriefDataDB;
	conInstanceBriefDataDB.m_accountID = getRoleGM()->getAccountID();
	conInstanceBriefDataDB.m_zoneID = getRoleGM()->getZoneID();
	conInstanceBriefDataDB.m_roleIndex = getRoleGM()->getRoleIndex();
	conInstanceBriefDataDB.m_dailyActivateInstanceCount = a_roleConInstanceBriefData.m_dailyActivateInstanceCount;
	conInstanceBriefDataDB.m_dailyFreeRollFastClearStageCount = a_roleConInstanceBriefData.m_dailyFreeRollFastClearStageCount;
	conInstanceBriefDataDB.m_lastResetTime = a_roleConInstanceBriefData.m_lastResetTime;
	BSLib::Utility::CStream stream;
	conInstanceBriefDataDB.serializeTo(stream);
	m_roleContinuousStageTable->update(conInstanceBriefDataDB.getDBKey(), stream);
	m_roleContinuousStageTable->saveDataToDBServer(conInstanceBriefDataDB.getDBKey(), true);	
}

void CRoleSceneModule::_updateRoleContinuousInstanceProgressData(const CConInstanceProgressData & a_stageProgressData)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "_updateRoleContinuousStageProgressData:getRoleGM OR getRoleGM()->getPlayerGM() error");
		return;
	}
	DB::CRoleConInstanceProgressDB progressDataDB;
	progressDataDB.m_accountID = getRoleGM()->getAccountID();
	progressDataDB.m_zoneID = getRoleGM()->getZoneID();
	progressDataDB.m_roleIndex = getRoleGM()->getRoleIndex();
	progressDataDB.m_instanceTPID = a_stageProgressData.m_instanceTPID;
	progressDataDB.m_isActivated = a_stageProgressData.m_isActivated;
	progressDataDB.m_curDayStageIndex = a_stageProgressData.m_curDayStageIndex;
	progressDataDB.m_maxClearStageIndex = a_stageProgressData.m_maxClearStageIndex;
	BSLib::Utility::CStream stream;
	progressDataDB.serializeTo(stream);
	m_roleContinuousStageProgressTable->update(progressDataDB.getDBKey(), progressDataDB.getIndexKey(), stream);
	m_roleContinuousStageProgressTable->saveDataToDBServer(progressDataDB.getDBKey(), progressDataDB.getIndexKey(), true);
}

void CRoleSceneModule::_updateRoleContinuousInstanceResultData(const CContinuousStageResultData & a_stageResultData)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "_updateRoleContinuousStageResultData:getRoleGM OR getRoleGM()->getPlayerGM() error");
		return;
	}
	DB::CContinuousStageResultDataDB stageResultDB;
	stageResultDB.m_accountID = getRoleGM()->getAccountID();
	stageResultDB.m_zoneID = getRoleGM()->getZoneID();
	stageResultDB.m_roleIndex = getRoleGM()->getRoleIndex();
	stageResultDB.m_instanceTPID = a_stageResultData.m_instanceTPID;
	stageResultDB.m_stageIndex = a_stageResultData.m_stageIndex;
	stageResultDB.m_score = a_stageResultData.m_score;
	BSLib::Utility::CStream stream;
	stageResultDB.serializeTo(stream);
	m_roleContinuousStageResultTable->update(stageResultDB.getDBKey(), stageResultDB.getIndexKey(), stream);
	m_roleContinuousStageResultTable->saveDataToDBServer(stageResultDB.getDBKey(), stageResultDB.getIndexKey(), true);
}

void CRoleSceneModule::_updateRoleStageSystemData(const CRoleStageSystemData & a_roleStageGetHelpData)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "_updateRoleStageGetHelpData:getRoleGM OR getRoleGM()->getPlayerGM() error");
		return;
	}
	DB::CRoleStageSystemData stageGetHelpDataDB;
	stageGetHelpDataDB.m_accountID = getRoleGM()->getAccountID();
	stageGetHelpDataDB.m_zoneID = getRoleGM()->getZoneID();
	stageGetHelpDataDB.m_roleIndex = getRoleGM()->getRoleIndex();
	stageGetHelpDataDB.m_dailyGetHelpCount = a_roleStageGetHelpData.m_dailyGetHelperCount; 
	stageGetHelpDataDB.m_greedLandEnterCountRemaining = a_roleStageGetHelpData.m_greedLandTickets; 
	stageGetHelpDataDB.m_lastGreedLandUpdateTime = a_roleStageGetHelpData.m_lastGreedLandUpdateTime; 
	stageGetHelpDataDB.m_lastUpdateTime = a_roleStageGetHelpData.m_lastUpdateTime;
	BSLib::Utility::CStream stream;
	stageGetHelpDataDB.serializeTo(stream);
	m_roleStageSystemDataTable->update(stageGetHelpDataDB.getKey(), stream);
	m_roleStageSystemDataTable->saveDataToDBServer(stageGetHelpDataDB.getKey(), true);	
}

EChallengeArenaRoleFinishResult CRoleSceneModule::_canReportFinishChallengeArenaRoleResult()
{
	EChallengeArenaRoleFinishResult result = ECHALLENGE_ARENA_ROLE_FINISH_RESULT_SUCCESS;
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		result = ECHALLENGE_ARENA_ROLE_FINISH_RESULT_FAIL;
	}
	if (m_curScene == NULL || m_curScene->getSceneType() != ESCENE_TYPE_ARENA) {
		return ECHALLENGE_ARENA_ROLE_FINISH_RESULT_NOT_IN_ARENA;
	}
	if (m_arenaData.getCombatRole() < 0) {
		return ECHALLENGE_ARENA_ROLE_FINISH_RESULT_NOT_CHALLENGE_ANY_ROLE_YET;
	}
	if (m_arenaData.m_arenaTicketCount < 0) {
		return ECHALLENGE_ARENA_ROLE_FINISH_RESULT_FAIL;
	}
	if (m_arenaData.m_vecChallengees.size() == 0 || m_arenaData.m_combatRole > BSLib::int32(m_arenaData.m_vecChallengees.size() - 1)) {
		return ECHALLENGE_ARENA_ROLE_FINISH_RESULT_CHALLENGEE_NOT_EXIST;
	}
	return ECHALLENGE_ARENA_ROLE_FINISH_RESULT_SUCCESS;
}

ESendStageResultReportResult CRoleSceneModule::_canReportStageResult()
{
	if (m_curScene == NULL || m_curScene->getSceneType() != ESCENE_TYPE_STAGE || !m_roleInstanceData.isInStage()) {
		return ESEND_STAGE_RESULT_REPORT_NOT_IN_STAGE;
	}
	if (m_curScene->getStageMonsterPrize().isValid()) {
		return ESEND_STAGE_RESULT_REPORT_HAS_REPROT_RESULT;
	}
	const CInstanceAttr *instanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(m_roleInstanceData.getCurInstanceTPID());
	if (instanceAttr == NULL ) {
		return ESEND_STAGE_RESULT_REPORT_ERROR_INSTANCE;
	}
	if (instanceAttr->m_vecStage[m_roleInstanceData.getCurStageIndex()] == NULL) {
		return ESEND_STAGE_RESULT_REPORT_ERROR_STAGE;
	} 

	return ESEND_STAGE_RESULT_REPORT_RESULT_SUCCESS;
}

EClearStageResult CRoleSceneModule::_canClearStage(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_stageIndex)
{
	if (getRoleGM() == NULL) {
		return ECLEAR_STAGE_RESULT_FAIL;
	}
	const CStageAttr *stageAttr = CSceneSystemDataMgr::singleton().getStageAttr(a_instanceTPID, a_stageIndex);
	if (stageAttr == NULL) {
		return ECLEAR_STAGE_RESULT_ERROR_STAGE;
	}
	const CInstanceAttr * instanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(a_instanceTPID);	
	if (instanceAttr->getType() != EINSTANCE_TYPE_STORY && instanceAttr->getType() != EINSTANCE_TYPE_ADVANCE) {
		return ECLEAR_STAGE_RESULT_ERROR_INSTANCE_TYPE;
	}
	const CFinishStage * stage = m_roleInstanceData.getStage(a_instanceTPID, a_stageIndex);
	if (stage == NULL || stage->getStar() != C_CLEAR_STAGE_REQUIRE_STAR) {
		return ECLEAR_STAGE_RESULT_ERROR_NOT_REACH_STAR_REQUIREMENT;
	}
	if (stageAttr->getMaxDailyEnterTimes() != 0) {
		if (stage->getDailyEnteredTimes() >= stageAttr->getMaxDailyEnterTimes()) {
			return ECLEAR_STAGE_RESULT_ERROR_NOT_REACH_MAX_DAILY_ENTER_TIME;
		}
	}

	if (getRoleGM()->getLevel() < C_CLEAR_STAGE_REQUIRE_ROLE_LEVEL ) {
		return ECLEAR_STAGE_RESULT_ERROR_NOT_REACH_LV_REQUIREMENT;
	}
	if (getRoleGM()->getVitality() < stageAttr->getCostVitality()) {
		return ECLEAR_STAGE_RESULT_ERROR_NOT_ENOUGH_VITALITY;
	}
	return ECLEAR_STAGE_RESULT_SUCCESS;	
}

GSLib::SceneSystem::GM::EReportContinuousStageResultResult CRoleSceneModule::_canReportConStageResult()
{
	if (m_curScene == NULL || m_curScene->getSceneType() != ESCENE_TYPE_CONTINUOUS_STAGE) {
		return EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_NOT_IN_STAGE;
	}
	const CConInstanceProgressData * conInstanceProgressData = m_roleContinuousStageData.getCurConInstanceProgressData();
	if (conInstanceProgressData == NULL) {
		return EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_NOT_IN_CONTINUOUS_STAGE;
	}
	const CInstanceAttr *instanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(m_roleContinuousStageData.getCurEnteredConInstanceTPID());
	if (instanceAttr == NULL || instanceAttr->getInstanceType() != EINSTANCE_TYPE_CONTINUOUS_STAGE) {
		return EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_NOT_ERROR_CONTINUOUS_INSTANCE_ID;
	}
	if (instanceAttr->m_vecStage[m_roleContinuousStageData.getCurEnteredConStageIndex()] == NULL) {
		return EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_NOT_ERROR_CONTINUOUS_STAGE_INDEX;
	} 
	
	return EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_SUCCESS;
}

EGetInstanceStarPrizeResult CRoleSceneModule::_canGetInstanceStarPrize(BSLib::uint32 a_instanceTPID)
{
	const CInstanceAttr * instanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(a_instanceTPID);
	if (instanceAttr == NULL) {
		return EGET_INSTANCE_PRIZE_RESULT_NO_SUCH_INSTANCE;
	}
	const CInstanceStarPrizeAttr* instanceStarPrizeAttr = CSceneSystemDataMgr::singleton().getInstanceStarPrizeAttr(a_instanceTPID);
	if (instanceStarPrizeAttr == NULL) {
		return EGET_INSTANCE_PRIZE_RESULT_NO_SUCH_PRIZE;
	}
	const CFinishInstanceData *finishInstance = m_roleInstanceData.getFinishInstanceData(a_instanceTPID);
	if (finishInstance == NULL) {
		return EGET_INSTANCE_PRIZE_RESULT_NO_STARS;
	}
	BSLib::uint16 curInstancePrizeStar = m_roleInstanceData.getCurrentInstancePrizeStar(a_instanceTPID);
	BSLib::uint16 nextInstancePrizeStar = instanceStarPrizeAttr->getNextStarLevel(curInstancePrizeStar);
	if (nextInstancePrizeStar == 0) {
		return EGET_INSTANCE_PRIZE_RESULT_NO_PRIZE_ANY_MORE;
	}
	BSLib::uint16 instanceStars = finishInstance->getStars();
	if (instanceStars < nextInstancePrizeStar) {
		return EGET_INSTANCE_PRIZE_RESULT_NOT_ENOUGH_STARS;
	}
	return EGET_INSTANCE_PRIZE_RESULT_SUCCESS ;
}

ERollFastClearContinuousStageNum CRoleSceneModule::_canRollFastClearContinuousStageNum(BSLib::uint32 a_instanceTPID)
{
	if (m_roleContinuousStageData.getDailyFreeRollFastClearStageCount() <= 0) {
		return EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_NO_ROLL_COUNT;
	}
	if (m_curScene != NULL) {
		if (m_curScene->getSceneType() != ESCENE_TYPE_CITY) {
			return EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_ALEADY_IN_STAGE;
		}
	}
	const CInstanceAttr *conInstance = CSceneSystemDataMgr::singleton().getInstanceAttr(a_instanceTPID);
	if (conInstance == NULL || conInstance->getType() != EINSTANCE_TYPE_CONTINUOUS_STAGE) {
		return EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_ERROR_CONTINUOUS_INSTANCE_ID;
	}
	const CConInstanceProgressData *conInstanceProgress =  m_roleContinuousStageData.getConInstanceProgressData(a_instanceTPID);
	if (conInstanceProgress == NULL || !conInstanceProgress->isActivated()) {
		return EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_CONTINUOUS_INSTANCE_NOT_ACTIVATED;
	}
	if (conInstanceProgress->getMaxClearStageIndex() == 0) {
		return EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_NOT_CLEAR_STAGE_YET;
	}
	if ((conInstanceProgress->getMaxClearStageIndex() + 1) == conInstanceProgress->getInstanceStageSize()) {
		return EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_REACH_MAX_STAGE_SIZE;
	}

	return EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_SUCCESS;
}

void CRoleSceneModule::_nextStoryStage(CRoleStage & a_stage) const
{
	const CInstanceAttr *instanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(a_stage.m_instanceTPID);
	if (instanceAttr != NULL) {
		if (a_stage.m_stageIndex + 1 < instanceAttr->stageSize()) {
			++a_stage.m_stageIndex;
		} else {
			BSLib::uint32 nextInstanceTPID = a_stage.m_instanceTPID + 1;
			const CInstanceAttr *nextInstanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(nextInstanceTPID);
			if (nextInstanceAttr != NULL /*&& nextInstanceAttr->getInstanceType() == EINSTANCE_TYPE_STORY */) {
				a_stage.m_instanceTPID = nextInstanceTPID;
				a_stage.m_stageIndex = 0;
			}
		}
	}
}

void CRoleSceneModule::_getStagePrizeItem(BSLib::uint32 a_dropItemTableID, std::vector<ItemSystem::GM::CPrizeItem> & a_prizeItem, BSLib::uint32 a_percent) const
{
	const CDropTableEntry * dropItem = CSceneSystemDataMgr::singleton().getDropItemEntry(a_dropItemTableID);
	if (dropItem != NULL) {
		for (BSLib::Utility::CHashMap<BSLib::uint32, CDropItem*>::const_iterator itr = dropItem->m_mapDropItems.begin(); itr != dropItem->m_mapDropItems.end(); ++itr) {
			const CDropItem *item = itr->second;
			if (item != NULL) {
				BSLib::uint32 itemPercent = item->m_weight * a_percent / 100;
				if (BSLib::Utility::CRandom::selectByPercent(itemPercent)) {
					GSLib::ItemSystem::GM::CPrizeItem prizeItem;
					prizeItem.m_itemTPID = item->m_itemTPID;
					prizeItem.m_itemCount = item->m_itemCount * a_percent / 100;
					if (prizeItem.m_itemCount > 0) {
						a_prizeItem.push_back(prizeItem);	
					}
				}
			}
		}
	}
}


GSLib::SceneSystem::GM::EResetContinuousInstanceResult CRoleSceneModule::_canResetContinuousInstance(BSLib::uint32 a_instanceTPID)
{
	if (m_curScene != NULL) {
		if (m_curScene->getSceneType() != ESCENE_TYPE_CITY) {
			return ERESET_CONTINUOUS_INSTANCE_RESULT_ALREADY_IN_INSTANCE;
		}
	}
	const CInstanceAttr *conInstance = CSceneSystemDataMgr::singleton().getInstanceAttr(a_instanceTPID);
	if (conInstance == NULL || conInstance->getType() != EINSTANCE_TYPE_CONTINUOUS_STAGE) {
		return ERESET_CONTINUOUS_INSTANCE_RESULT_ERROR_CONTINUOUS_INSTANCE_TPID;
	}	
	const CConInstanceProgressData *conInstanceProgress =  m_roleContinuousStageData.getConInstanceProgressData(a_instanceTPID);
	if (conInstanceProgress == NULL || !conInstanceProgress->isActivated()) {
		return ERESET_CONTINUOUS_INSTANCE_RESULT_INSTANCE_NOT_ACTIVATED_YET;
	}
	if (conInstanceProgress->getCurDayStageIndex() == 0) {
		return ERESET_CONTINUOUS_INSTANCE_RESULT_STAGE_INDEX_IS_ZERO;
	}
	if (m_roleContinuousStageData.getDailyActivateInstanceCount() <= 0) {
		return ERESET_CONTINUOUS_INSTANCE_RESULT_NO_INSTANCE_RESET_COUNT;
	}

	return ERESET_CONTINUOUS_INSTANCE_RESULT_SUCCESS;
}

EEnterSceneResult CRoleSceneModule::_canGetStageHelper(BSLib::uint32 a_instanceTPID, BSLib::uint32 a_stageIndex, const SRoleKey & a_helperKey) const
{
	if (getRoleGM() == NULL) {
		return EENTER_STAGE_RESULT_FAIL;
	}
	const CStageAttr* stageAttr = CSceneSystemDataMgr::singleton().getStageAttr(a_instanceTPID, a_stageIndex);
	if (stageAttr == NULL) {
		return EENTER_SCENE_RESULT_NOT_EXIST;
	}
	if (stageAttr->getSceneType() != ESCENE_TYPE_STAGE) {
		return EENTER_STAGE_RESULT_ERROR_INSTANCE;
	}

	FriendSystem::GM::CRoleFriendModule *friendModule = (FriendSystem::GM::CRoleFriendModule *)getRoleGM()->getPlayerModuleGM(EMODULETYPE_FRIEND);
	if (friendModule == NULL) {
		return EENTER_STAGE_RESULT_FAIL;
	}
	if (!friendModule->isMyFriend(a_helperKey)) {
		return EENTER_STAGE_RESULT_NOT_FRIEND;
	}
	if (getRoleGM()->getTotalDiamond() < m_roleInstanceData.m_roleStageSystemData.m_dailyGetHelperCount * C_STAGE_HELP_COST_DIAMOND_STEP) {
		return EENTER_STAGE_RESULT_NOT_ENOUGH_DIAMOND;
	}

	return EENTER_SCENE_RESULT_SUCCESS;
}

GSLib::SceneSystem::GM::EDetermineStagePrizeItemResult CRoleSceneModule::_canDetermineStagePrizeResult() const
{
	if (m_curScene == NULL || !m_curScene->getStageMonsterPrize().isValid()) {
		return EDETERMINE_STAGE_PRIZE_ITEM_NOT_FINISHED_STAGE ;
	}

	return EDETERMINE_STAGE_PRIZE_ITEM_SUCCESS;
}

ESceneRoleReviveResult CRoleSceneModule::_canRevive() const
{
	if (getRoleGM() == NULL) {
		return SCENE_ROLE_REVIVE_RESULT_FAIL;
	}
	if (m_curScene == NULL) {
		return SCENE_ROLE_REVIVE_RESULT_NOT_IN_SCENE;
	}
	if (m_curScene->getSceneAttr() == NULL) {
		return SCENE_ROLE_REVIVE_RESULT_FAIL;
	}
	CStageAttr *stageAttr = (CStageAttr *)m_curScene->getSceneAttr();
	EInstanceType type = stageAttr->getInstanceType();
	if (type != EINSTANCE_TYPE_STORY && type != EINSTANCE_TYPE_ADVANCE && type != EINSTANCE_TYPE_CONTINUOUS_STAGE && 
		type != EINSTANCE_TYPE_RANDOM_STAGE && type != EINSTANCE_TYPE_RANDOM_GOLD_STAGE && type != EINSTANCE_TYPE_RANDOM_EXP_STAGE) {
		return SCENE_ROLE_REVIVE_RESULT_DISABLE_REVIVE;
	}
	if (type != EINSTANCE_TYPE_STORY) {
		if (m_reviveCount >= C_REVIVE_COUNT) {
			return SCENE_ROLE_REVIVE_RESULT_REACH_MAX_TIMES;
		}
	}

	BSLib::int32 nextCount = m_reviveCount + 1;	
	BSLib::uint32 requiredDiamond = 8 + (BSLib::uint32)::pow(2.2, nextCount);
	BSLib::uint32 diamond = getRoleGM()->getTotalDiamond();
	if (requiredDiamond > diamond) {
		return SCENE_ROLE_REVIVE_RESULT_NOT_ENOUGH_DIAMOND;
	}

	return SCENE_ROLE_REVIVE_RESULT_SUCCESS;
}

EPurchaseArenaTicketsResult CRoleSceneModule::_canPurchaseTicket() const
{
	if (getRoleGM() == NULL) {
		return EPURCHASE_ARENA_TICKETS_FAIL;
	}
	if (m_arenaData.getArenaTicketPrice() > getRoleGM()->getTotalDiamond()) {
		return EPURCHASE_ARENA_NOT_ENOUGH_DIAMOND;
	}
	if (m_arenaData.m_dailyTicketPurchasedCount >= getMaxPurchaseArenaTicketCount()) {
		return EPURCHASE_ARENA_DAILY_LIMITED;
	}
		
	return EPURCHASE_ARENA_TICKETS_SUCCESS;
}

ERestoreStageTicketsResult CRoleSceneModule::_canRestoreStageTicket(BSLib::uint32 a_instanceTPID, BSLib::uint32 a_stageIndex)
{
	if (getRoleGM() == NULL) {
		return ERESTORE_STAGE_TICKETS_FAIL;
	}
	const CStageAttr * stageAttr = CSceneSystemDataMgr::singleton().getStageAttr(a_instanceTPID, a_stageIndex);
	if (stageAttr == NULL) {
		return ERESTORE_STAGE_TICKETS_STAGE_NOT_EXIST;
	}
	if (stageAttr->getMaxDailyEnterTimes() == 0) {
		return ERESTORE_STAGE_TICKETS_STAGE_NOT_NO_TICKET_LIMIT;
	}
	CFinishStage *finsishedStage = m_roleInstanceData.getStage(a_instanceTPID, (BSLib::uint16)a_stageIndex);
	if (finsishedStage == NULL || !finsishedStage->isValid()) {
		return ERESTORE_STAGE_TICKETS_STAGE_NOT_OPEN;
	}
	if (finsishedStage->getDailyEnteredTimes() < stageAttr->getMaxDailyEnterTimes()) {
		return ERESTORE_STAGE_TICKETS_STAGE_NOT_EMPTY_TICKET;
	}

	if (getRoleGM()->getTotalDiamond() < finsishedStage->getNextRestoreStageRequireDiamond()) {
		return ERESTORE_STAGE_TICKETS_STAGE_NOT_ENOUGH_DIAMOND;
	}
	if (finsishedStage->getDailyRestoreCount() >= _getMaxRestoreStageTicketCount()) {
		return ERESTORE_STAGE_TICKETS_STAGE_RESTORE_COUNT_LIMIT;
	}

	return ERESTORE_STAGE_TICKETS_SUCCESS;
}

void CRoleSceneModule::_updateInstanceAchieve(BSLib::uint32 a_instanceID, BSLib::uint32 a_stageID)
{
	if (getRoleGM() == NULL) {
		return;
	}
	const CStageAttr * stageAttr = CSceneSystemDataMgr::singleton().getStageAttr(a_stageID);
	if (stageAttr != NULL) {
		BSLib::Utility::CStream stream;
		stream.reset();
		const GSLib::SRoleKey roleKey = getRoleGM()->getRoleKey();
		roleKey.serializeTo(stream);
		stream << a_stageID;
		GFLib::CommonServer::CEventMgr::singleton().sendEvent(EEVENTID_ACHIEVE_PASS_INSTANCE,stream);

		BSLib::uint32 bossID = stageAttr->getBossID();
		if (bossID > 0) {
			const GSLib::SRoleKey roleKey = getRoleGM()->getRoleKey();
			roleKey.serializeTo(stream);
			stream << bossID;
			GFLib::CommonServer::CEventMgr::singleton().sendEvent(EEVENTID_ACHIEVE_KILL_BOSS,stream);
		}
	}
}

void CRoleSceneModule::_updateContinuousInstanceAchieve(BSLib::uint32 a_curMaxStage)
{
	if (getRoleGM() == NULL) {
		return;
	}
	BSLib::Utility::CStream stream;
	stream.reset();
	const GSLib::SRoleKey roleKey = getRoleGM()->getRoleKey();
	roleKey.serializeTo(stream);
	stream << a_curMaxStage;
	GFLib::CommonServer::CEventMgr::singleton().sendEvent(EEVENTID_ACHIEVE_PASS_STAGE,stream);
}

void CRoleSceneModule::_updateRollContiuousStageFastClearCountAchieve()
{
	if (getRoleGM() == NULL) {
		return;
	}
	BSLib::Utility::CStream stream;
	stream.reset();
	const GSLib::SRoleKey roleKey = getRoleGM()->getRoleKey();
	roleKey.serializeTo(stream);
	BSLib::uint32 throwCount = 1; // 投掷次数
	stream << throwCount;
	GFLib::CommonServer::CEventMgr::singleton().sendEvent(EEVENTID_ACHIEVE_DICE,stream);
}

void CRoleSceneModule::_onGetArenaDataFromCNServer(const CMsgSceneSystemCN2GMAckArenaAction &a_msg)
{
	m_arenaData.m_rank = a_msg.m_rank;
	m_arenaData.m_vecChallengees = a_msg.m_vecChallengeeData;
	CMsgSceneSystemGM2GCAckGetRoleArenaData msgAck(m_arenaData);
	msgAck.m_nextSendArenaPrizeTime = _getSendArenaPrizeTime();
	msgAck.m_ticketPrice = m_arenaData.getArenaTicketPrice();
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onGetArenaChallengableRolesFromCNServer(const CMsgSceneSystemCN2GMAckArenaAction &a_msg)
{
	m_arenaData.m_vecChallengees = a_msg.m_vecChallengeeData;
	CMsgSceneSystemGM2GCAckGetNewArenaChallengees msgAck;
	msgAck.m_vecChallengees = a_msg.m_vecChallengeeData;
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_onFinishChallengeFromCNServer(const CMsgSceneSystemCN2GMAckArenaAction &a_msg)
{
	m_arenaData.addChallengeRecord(a_msg.m_challengerRecord);
	CMsgSceneSystemGM2GCAckAddNewArenaChallegenRecord msgPush;
	msgPush.m_record = a_msg.m_challengerRecord;
	sendMsgToClient(msgPush);
}

void CRoleSceneModule::_onUpdateArenaRecordFromCNServer(const CMsgSceneSystemCN2GMAckArenaAction &a_msg)
{
	m_arenaData.addChallengeRecord(a_msg.m_challengerRecord);
	CMsgSceneSystemGM2GCAckAddNewArenaChallegenRecord msgPush;
	msgPush.m_record = a_msg.m_challengerRecord;
	sendMsgToClient(msgPush);
}

void CRoleSceneModule::_setBattleRoleData(CBattleRoleData & challengeeData, const PlayerSystem::GM::CRoleAllData& a_roleAllData)
{
	challengeeData.m_accountID = a_roleAllData.roleData.m_accountID;
	challengeeData.m_zoneID = a_roleAllData.roleData.m_zoneID;
	challengeeData.m_roleIndex = a_roleAllData.roleData.m_roleIndex;
	challengeeData.m_roleTPID = a_roleAllData.roleData.m_roleTPID;
	challengeeData.m_roleName = a_roleAllData.roleData.m_roleName;
	challengeeData.m_level = a_roleAllData.roleData.m_roleLevel;
	challengeeData.m_combatPower = a_roleAllData.roleData.m_combat;
	for (std::vector<SkillSystem::GM::CSkill>::const_iterator itr = a_roleAllData.roleSkillData.m_vecSkill.begin(); itr != a_roleAllData.roleSkillData.m_vecSkill.end(); ++itr) {
		SkillSystem::GM::CSkill skill(*itr);
		challengeeData.m_skills.setValue(itr->getSkillTPID(), skill);
	}
	for (BSLib::uint32 i = 0; i < a_roleAllData.roleSkillData.m_vecSkillPos.size() && (int)i < SkillSystem::GM::SKILL_BOTTON_COUNT; ++i) {
		challengeeData.m_skillButtons[i] = a_roleAllData.roleSkillData.m_vecSkillPos[i];
	}
	//TODO 战斗属性 会修改
	challengeeData.m_battleAttr.m_atk = a_roleAllData.roleData.m_atk;
	challengeeData.m_battleAttr.m_def = a_roleAllData.roleData.m_def;
	challengeeData.m_battleAttr.m_atkCrift = a_roleAllData.roleData.m_atkCrift;
	challengeeData.m_battleAttr.m_defCrift = a_roleAllData.roleData.m_defCrift;
	challengeeData.m_battleAttr.m_hitRate = a_roleAllData.roleData.m_hitRate;
	challengeeData.m_battleAttr.m_missRate = a_roleAllData.roleData.m_missRate;
	challengeeData.m_battleAttr.m_maxHP = a_roleAllData.roleData.m_maxHP;
}

void CRoleSceneModule::_cbGetArenaChallengingData(const PlayerSystem::GM::CRoleAllData& a_roleAllData)
{
	CMsgSceneSystemGM2GCAckChallengeArenaRole msgAck;
	if (a_roleAllData.roleData.m_accountID <= 0) { // not exist
		m_arenaData.setCombatRole(-1);
		msgAck.m_result = EENTER_SCENE_RESULT_FAIL;
	} else { //success
		msgAck.m_result = EENTER_SCENE_RESULT_SUCCESS;
		m_arenaData.setDailyChallengeTimes(m_arenaData.getDailyChallengeTimes() - 1);
		_setBattleRoleData(msgAck.m_roleData, a_roleAllData);
		m_arenaData.setLastChallengeTime((BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds());
		if (m_arenaData.m_challengeInfo.m_useDiamond) {
			getRoleGM()->delDiamond(m_arenaData.getArenaCoolDownCost(), "EraseChallengeColdTime");
			++m_arenaData.m_dailyCoolDownCount;
		}
		
		_updateChallengeDataToDB();
	}
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_cbGetStagehelperData(const PlayerSystem::GM::CRoleAllData& a_roleAllData)
{
	CMsgSceneSystemGM2GCAckEnterStage msgAck;
	if (a_roleAllData.roleData.m_accountID <= 0) {
		msgAck.m_result = EENTER_STAGE_RESULT_GET_FRIEND_DATA_ERROR;
	} else {
		const CStageAttr *stageAttr = m_roleInstanceData.m_tryEnterStageAttr;
		if (stageAttr != NULL) {
			msgAck.m_result = _enterScene(ESCENE_TYPE_STAGE, stageAttr->getSceneTPID());	
			if (msgAck.m_result == EENTER_SCENE_RESULT_SUCCESS) {
				_setBattleRoleData(msgAck.m_battleRoleData, a_roleAllData);
				if (m_curScene != NULL) {
					msgAck.m_stageMonster = m_curScene->getStageMonsterPrize();
				}
				BSLib::uint32 costDiamond = m_roleInstanceData.m_roleStageSystemData.m_dailyGetHelperCount * C_STAGE_HELP_COST_DIAMOND_STEP;
				if (costDiamond > 0) {
					getRoleGM()->delDiamond(costDiamond, "stage friend help");	
				}
			}
		}
	}
	sendMsgToClient(msgAck);
}

void CRoleSceneModule::_updateGreedLandInfo()
{
	BSLib::int32 curTime = (BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
	BSLib::int32 lastUpdateTime = m_roleInstanceData.getLastGreedLandTicketsUpdateTime();
	if (curTime > lastUpdateTime) {
		if (m_roleInstanceData.getGreedLandTicketsCount() < C_MAX_GREED_LAND_ENTRANCE_TICKETS) {
			BSLib::int32 timeInterval = curTime - lastUpdateTime;
			BSLib::uint32 addCount = (timeInterval) / C_GREED_LAND_TICKETSUPDATE_SECONDS;
			if (addCount > 0) {
				BSLib::uint32 newTicketCount = m_roleInstanceData.getGreedLandTicketsCount() + addCount;	
				if (newTicketCount >= C_MAX_GREED_LAND_ENTRANCE_TICKETS) {
					m_roleInstanceData.setLastGreedLandTicktsUpdateTime(curTime);	
					m_roleInstanceData.setGreedLandTicketsCount(C_MAX_GREED_LAND_ENTRANCE_TICKETS);
				} else {
					lastUpdateTime += addCount * C_GREED_LAND_TICKETSUPDATE_SECONDS;
					m_roleInstanceData.setLastGreedLandTicktsUpdateTime(lastUpdateTime);
					m_roleInstanceData.setGreedLandTicketsCount(newTicketCount);
				}
				_updateRoleStageSystemData(m_roleInstanceData.m_roleStageSystemData);
			}
		}
	}
}

BSLib::uint64 CRoleSceneModule::_genArenaRecordID(BSLib::int32 a_time)
{
	return CSceneSystemGM::singleton().genArenaRecordID(a_time);
}

BSLib::int32 CRoleSceneModule::_getSendArenaPrizeTime() const
{
	return 0;
}

void CRoleSceneModule::_resetInstanceStage(BSLib::uint32 a_instanceTPID)
{
	CFinishInstanceData * instanceData = m_roleInstanceData.getFinishInstanceData(a_instanceTPID);
	if (instanceData != NULL) {
		for (std::vector<CFinishStage>::iterator itr = instanceData->m_vecFinishStage.begin(); 
			itr != instanceData->m_vecFinishStage.end(); ++itr) {
				if (itr->isValid()) {
					if (CSceneSystemGM::singleton().getLastInstanceStageResetTime() > itr->getLastResetTime()) {
						itr->m_lastResetTime = CSceneSystemGM::singleton().getLastInstanceStageResetTime();
						itr->m_dailyEnteredTimes = 0;
						itr->m_dailyRestoreCount = 0;
						_updateRoleFinishStageDataTable(*itr);
					}
				}
		}
	}
}

BSLib::uint32 CRoleSceneModule::_getMaxRestoreStageTicketCount() const
{
	if (getRoleGM() == NULL) {
		return 0;
	}
	BSLib::uint32 VIPLevel = getRoleGM()->getVipLevel();
	switch (VIPLevel) {
		case 0 : return 0; break;
		case 1 : return 1; break;
		case 2 : return 1; break;
		case 3 : return 2; break;
		case 4 : return 2; break;
		case 5 : return 3; break;
		case 6 : return 3; break;
		case 7 : return 4; break;
		case 8 : return 4; break;
		case 9 : return 5; break;
		case 10 : return 6; break;
		default:return 6;
	}
}

BSLib::uint32 CRoleSceneModule::getMaxPurchaseArenaTicketCount() const
{
	if (getRoleGM() == NULL) {
		return 0;
	}
	BSLib::uint32 VIPLevel = getRoleGM()->getVipLevel();
	switch (VIPLevel) {
		case 0 : return 0; break;
		case 1 : return 0; break;
		case 2 : return 1; break;
		case 3 : return 2; break;
		case 4 : return 3; break;
		case 5 : return 4; break;
		case 6 : return 5; break;
		case 7 : return 6; break;
		case 8 : return 7; break;
		case 9 : return 8; break;
		case 10 : return 9; break;
		default:return 9;
	}
}







}//GM

}//SceneSystem

}//GSLib



