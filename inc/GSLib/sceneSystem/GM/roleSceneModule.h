//////////////////////////////////////////////////////////////////////
//	created:	2014/09/22
//	filename: 	src\GSLib\sceneSystem\GM\roleSceneModule.cpp
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SCENESYSTEM_GM_ROLESCENEMODULE_H__
#define __GSLIB_SCENESYSTEM_GM_ROLESCENEMODULE_H__

#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <GSLib/sceneSystem/GM/roleArenaData.h>
#include <GSLib/sceneSystem/sceneSystemCommonData.h>
#include <GSLib/sceneSystem/GM/sceneErrorGM.h>
#include <GSLib/sceneSystem/GM/sceneSystemData.h>

namespace GSLib
{

class SRoleKey;

namespace PlayerSystem
{
namespace GM
{
	class CRoleAllData;
}
}

namespace SceneSystem
{

class CMsgSceneSystemCN2GMAckArenaAction;
namespace GM
{
	const BSLib::uint32 C_GET_ARENA_CHALLENGEE_DATA_SESSION = 1;
	const BSLib::uint32 C_GET_HELPER_DATA_SESSION = 2;

	const BSLib::uint32 C_MAX_STAGES_PER_INSTANCE = 1000;
	const BSLib::int8 C_CLEAR_STAGE_REQUIRE_STAR = 3;
	const BSLib::uint32 C_CLEAR_STAGE_REQUIRE_ROLE_LEVEL = 15;
	const BSLib::uint32 C_CLEAR_STAGE_EXP_PERCENT_SCALE_FACTOR = 80;
	const BSLib::int8 C_CLEAR_STAGE_DEFAULT_STAR = 3;
	const BSLib::int32 C_STAGE_HELP_COST_DIAMOND_STEP = 5;

class CScene;
class CRoleSceneModule : public GSLib::PlayerSystem::GM::CRoleModuleGM
{
public:
	friend class CSceneArena;
	friend class CSceneCity;
	friend class CSceneStage;
	friend class CSceneContinuousStage;
	friend class CSceneRandomStage;
	friend class CSceneGoldLandStage;
	friend class CSceneExpLandStage;

	CRoleSceneModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CRoleSceneModule();

	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void updateDataToDB();

	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);

	virtual bool cbSelectGetTableData(const GSLib::SRoleKey& a_roleKey,GSLib::DBSystem::ETableKeyType a_TableKeyType,GSLib::DBSystem::CKeyIndexTablePtr& a_keyIndexTable, 
		                              GSLib::DBSystem::CKeyTablePtr& a_keyTable,EDBTableID a_tableID, BSLib::uint32 a_sessionID,BSLib::Utility::CStream& a_stream);
	virtual bool cbSelectMultiTableData(bool a_success,BSLib::uint32 a_sessionID,void* a_ptr,PlayerSystem::GM::CRoleAllData& a_roleAllData);

	virtual void onRoleActive();
	virtual void onRoleInactive();

public:
	void addChallengeRecord(SceneSystem::CArenaChallengeRecord &record);
private:
	void _onMsgSceneSystemGC2GMReqEnterScene(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqQuitScene(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqGetRoleArenaData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqGetNewArenaChallengees(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqChallengeArenaRole(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqChallengeArenaRoleFinish(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqPurchaseArenaTickts(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqGetStroyInstanceProgress(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqGetInstanceData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqEnterStage(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqStageResultReport(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqDetermineStagePrizeItem(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqClearStage(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqGetInstanceStarPrize(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqGetIntanceStarPrizeProgress(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqGetContinuousInstanceData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqEnterContinuousStage(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqReportContinuousStageResult(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqRollFastClearContinuousStageNum(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqResetContinuousInstance(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemCN2GMAckArenaAction(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqEnterRandomStage(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqReportRandomStageResult(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqRoleRevive(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqGetGreedLandInfo(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgSceneSystemGC2GMReqRestoreStageTickets(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);


	void _onMsgSceneSystemGC2GMReqRoleMove(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	
public:
	void enterScene(ESceneType a_sceneType, BSLib::uint32 a_sceneTPID);
	void exitScene();
	void getSceneRoles(std::vector<CSceneRoleInfo> & a_vecSceneRoles);

	void setCurScene(CScene *a_scene);
	CScene *getScene() const;

	CRoleInstanceData & getRoleInstanceData();
	CRoleContinuousStageData & getRoleConStageData();
public:
	void onContinuousStageDailyReset();
	void onStageHelperDailyReset();
	void onArenaReset();
	void announceItem(const std::string & a_sceneName, const std::vector<ItemSystem::GM::CPrizeItem> & a_prizeItemList);
	BSLib::uint32 getMaxPurchaseArenaTicketCount() const;

private:
	EEnterSceneResult _enterScene(ESceneType a_sceneType, SceneTPID a_TPID);
	void _updateChallengeDataToDB();
	void _updateChallengeRecordToDB(CArenaChallengeRecord &a_record, const GSLib::SRoleKey & a_roleKey);
	void _updateStoryInstanceProgressTable(const CRoleStoryInstanceProgress &a_storyInstanceProgress);
	void _updateRoleFinishStageDataTable(CFinishStage & a_finishStageData);
	void _updateRoleInstanceStarPrize(CRoleInstanceStarPrize & a_instanceStarPrize);
	void _updateRoleConInstanceData(const CRoleConInstanceBriefData & a_roleConInstanceBriefData);
	void _updateRoleContinuousInstanceProgressData(const CConInstanceProgressData & a_stageProgressData);
	void _updateRoleContinuousInstanceResultData(const CContinuousStageResultData & a_stageResultData);
	void _updateRoleStageSystemData(const CRoleStageSystemData & a_roleStageGetHelpData);
private:
	EChallengeArenaRoleFinishResult _canReportFinishChallengeArenaRoleResult();
	ESendStageResultReportResult _canReportStageResult();
	EClearStageResult _canClearStage(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_stageIndex);
	EReportContinuousStageResultResult _canReportConStageResult();
	EGetInstanceStarPrizeResult _canGetInstanceStarPrize(BSLib::uint32 a_instanceTPID);
	ERollFastClearContinuousStageNum _canRollFastClearContinuousStageNum(BSLib::uint32 a_instanceTPID);
	EResetContinuousInstanceResult _canResetContinuousInstance(BSLib::uint32 a_instanceTPID);
	EEnterSceneResult _canGetStageHelper(BSLib::uint32 a_instanceTPID, BSLib::uint32 a_stageIndex, const SRoleKey & a_helperKey) const;
	EDetermineStagePrizeItemResult _canDetermineStagePrizeResult() const;
	ESceneRoleReviveResult _canRevive() const;
	EPurchaseArenaTicketsResult _canPurchaseTicket() const;
	ERestoreStageTicketsResult _canRestoreStageTicket(BSLib::uint32 a_instanceTPID, BSLib::uint32 a_stageIndex);

	void _nextStoryStage(CRoleStage & a_stage) const;
	void _getStagePrizeItem(BSLib::uint32 a_dropItemTableID, std::vector<ItemSystem::GM::CPrizeItem> & a_prizeItem, BSLib::uint32 a_percent = 100) const;
	void _updateInstanceAchieve(BSLib::uint32 a_instanceID, BSLib::uint32 a_stageID);
	void _updateContinuousInstanceAchieve(BSLib::uint32 a_curMaxStage);
	void _updateRollContiuousStageFastClearCountAchieve();
private:
	void _onGetArenaDataFromCNServer(const CMsgSceneSystemCN2GMAckArenaAction &a_msg);
	void _onGetArenaChallengableRolesFromCNServer(const CMsgSceneSystemCN2GMAckArenaAction &a_msg);
	void _onFinishChallengeFromCNServer(const CMsgSceneSystemCN2GMAckArenaAction &a_msg);
	void _onUpdateArenaRecordFromCNServer(const CMsgSceneSystemCN2GMAckArenaAction &a_msg);

	void _setBattleRoleData(CBattleRoleData & challengeeData, const PlayerSystem::GM::CRoleAllData& a_roleAllData);
	void _cbGetArenaChallengingData(const PlayerSystem::GM::CRoleAllData& a_roleAllData);
	void _cbGetStagehelperData(const PlayerSystem::GM::CRoleAllData& a_roleAllData);
	void _reportStageResult();
	void _updateGreedLandInfo();
	BSLib::uint64 _genArenaRecordID(BSLib::int32 a_time);
	BSLib::int32 _getSendArenaPrizeTime() const;
	void _resetInstanceStage(BSLib::uint32 a_instanceTPID);
	BSLib::uint32 _getMaxRestoreStageTicketCount() const;
private:
	CRoleArenaData m_arenaData;	
	CRoleInstanceData m_roleInstanceData;
	CRoleContinuousStageData m_roleContinuousStageData;
	BSLib::uint32 m_reviveCount;
	CScene* m_curScene;
private:
	GSLib::DBSystem::CKeyTablePtr m_arenaDataTable;
	GSLib::DBSystem::CKeyIndexTablePtr m_arenaChallengeRecordTable;
	GSLib::DBSystem::CKeyTablePtr m_roleStoryInstanceProgressTable;
	GSLib::DBSystem::CKeyIndexTablePtr m_roleStageDataTable;
	GSLib::DBSystem::CKeyIndexTablePtr m_roleInstancePrizeTable;
	GSLib::DBSystem::CKeyTablePtr m_roleContinuousStageTable;
	GSLib::DBSystem::CKeyIndexTablePtr m_roleContinuousStageProgressTable;
	GSLib::DBSystem::CKeyIndexTablePtr m_roleContinuousStageResultTable;
	GSLib::DBSystem::CKeyTablePtr m_roleStageSystemDataTable;
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_ROLESCENEMODULE_H__