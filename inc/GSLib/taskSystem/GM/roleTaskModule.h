#ifndef __GSLIB_TASKSYSTEM_GM_ROLETASKMODULE_H__
#define __GSLIB_TASKSYSTEM_GM_ROLETASKMODULE_H__

#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <GSLib/taskSystem/GM/taskSystemDefine.h>
#include <GSLib/taskSystem/GM/taskData.h>
#include <GSLib/taskSystem/GM/taskSystemError.h>

namespace GSLib
{

namespace TaskSystem
{

namespace GM
{

class CRoleTaskModule : public GSLib::PlayerSystem::GM::CRoleModuleGM
{
public:
	friend class SceneSystem::GM::CScene;

	CRoleTaskModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CRoleTaskModule();

	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void onRoleActive();
	virtual void onRoleInactive();

	virtual void updateDataToDB();

	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
public:
	void _onMsgTaskSystemGC2GMReqGetDailyTaskList(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgTaskSystemGC2GMReqGetDailyTaskPrize(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgTaskSystemGC2GMReqGetMainTaskList(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgTaskSystemGC2GMReqNotifyMainTaskStateUpdate(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgTaskSystemGC2GMReqGetMainTaskPrize(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgTaskSystemGC2GMNtfFinishMainTaskEvent(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgTaskSystemGC2GMReqGetPetTask(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgTaskSystemGC2GMReqRefreshPetTask(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgTaskSystemGC2GMReqUpdatePetTaskState(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgTaskSystemGC2GMReqGetPetTaskPrize(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

public:
	void onTaskSystemDataReset();

	void onDailyTaskDataReset();
	void onPetTaskDataReset();
	void updateDailyTask(EDailyTaskType taskType);
	CRoleMainTaskData & getMainTaskData();
public:
	void updateDailyTaskTable(CRoleDailyTaskData &dailyTask);
	void removeAllDailyTableData();

	void updateMainTaskTable(CRoleMainTaskData &mainTask);
	void updateMainTask(BSLib::uint32 a_curRoleLevel);
private:
	void _getRandomDailyTask(BSLib::Utility::CHashMap<BSLib::uint32, CRoleDailyTaskData> &hashDailyTask);
	void _onRoleActive();
	void _updateMainTask(BSLib::uint32 a_mainTaskTPID, BSLib::uint32 a_reportCount);
	void _updateTaskSystemData(const CRoleTaskSystemData &a_roleTaskSystemData);
	void _updatePetTask(const CRolePetTaskData & a_petTaskData);
	void _removeAllPetTableData();

	EUpdateMainTaskStateResult _canUpdateMainTaskStage(BSLib::uint32 a_mainTaskTPID, BSLib::uint32 a_reportCount);
	void _getRandomPetTask(CRolePetTaskData & a_petTaskData);
	BSLib::uint32 _getRefreshDiamondCost(BSLib::uint32 a_refreshCount);
	void _getNewPetTaskData(BSLib::uint32 a_count);
	EUpdatePetTaskStateResult _canUpdatePetTaskResult(BSLib::uint32 a_taskIndex ,ETaskState a_state, BSLib::int32 a_count);
	BSLib::uint32 _getPetTaskIndex() const;
	bool _curRoundPetTaskFinished() const;
private:
	GSLib::DBSystem::CKeyIndexTablePtr m_dailyTaskTable;
	GSLib::DBSystem::CKeyIndexTablePtr m_petTaskTable;

	GSLib::DBSystem::CKeyTablePtr m_mainTaskTable;
	GSLib::DBSystem::CKeyTablePtr m_roleTaskSystemDataTable;

	CRoleMainTaskData m_roleMainTaskData;
	CRoleTaskSystemData m_roleTaskSystemData;

	BSLib::Utility::CHashMap<BSLib::uint32, CRoleDailyTaskData> m_hashDailyTask;
	BSLib::Utility::CHashMap<BSLib::uint32, CRolePetTaskData> m_hashPetTask;
};

}//GM

}//TaskSystem

}//GSLib

#endif//__GSLIB_TASKSYSTEM_GM_ROLETASKMODULE_H__
