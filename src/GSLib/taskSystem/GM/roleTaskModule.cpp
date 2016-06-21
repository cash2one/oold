#include <vector>
#include <GSLib/taskSystem/GM/roleTaskModule.h>
#include <GSLib/taskSystem/DB/tableTaskDB.h>
#include <GSLib/taskSystem/GM/taskData.h>
#include <GSLib/taskSystem/GM/taskDataMgr.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <BSLib/utility/random.h>
#include <GSLib/taskSystem/GM/taskSystemDefine.h>
#include <GSLib/taskSystem/GM/taskSystemGM.h>
#include <GSLib/taskSystem/msgNumIDTaskSystem.h>
#include <GSLib/taskSystem/msgTaskSystem.h>
#include <GSLib/prizeSystem/GM/rolePrizeModule.h>
#include <GSLib/petSystem/GM/petModule.h>

namespace GSLib
{

namespace TaskSystem
{

namespace GM
{

CRoleTaskModule::CRoleTaskModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType)
:  GSLib::PlayerSystem::GM::CRoleModuleGM(a_roleGM, a_moduleType)
{
	;
}

CRoleTaskModule::~CRoleTaskModule()
{
	;
}

void CRoleTaskModule::preInit(bool isFirst)
{
	;
}

void CRoleTaskModule::postInit(bool isFirst)
{
	;
}


void CRoleTaskModule::initToClient()
{
	;
}

void CRoleTaskModule::final()
{
	;
}

void CRoleTaskModule::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDTaskSystemGC2GMReqGetDailyTaskList, &BSLib::Framework::CreateCMessage<CMsgTaskSystemGC2GMReqGetDailyTaskList>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDTaskSystemGC2GMReqGetDailyTaskList, &CRoleTaskModule::_onMsgTaskSystemGC2GMReqGetDailyTaskList, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDTaskSystemGC2GMReqGetDailyTaskPrize, &BSLib::Framework::CreateCMessage<CMsgTaskSystemGC2GMReqGetDailyTaskPrize>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDTaskSystemGC2GMReqGetDailyTaskPrize, &CRoleTaskModule::_onMsgTaskSystemGC2GMReqGetDailyTaskPrize, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDTaskSystemGC2GMReqGetMainTaskList, &BSLib::Framework::CreateCMessage<CMsgTaskSystemGC2GMReqGetMainTaskList>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDTaskSystemGC2GMReqGetMainTaskList, &CRoleTaskModule::_onMsgTaskSystemGC2GMReqGetMainTaskList, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDTaskSystemGC2GMReqGetMainTaskPrize, &BSLib::Framework::CreateCMessage<CMsgTaskSystemGC2GMReqGetMainTaskPrize>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDTaskSystemGC2GMReqGetMainTaskPrize, &CRoleTaskModule::_onMsgTaskSystemGC2GMReqGetMainTaskPrize, this);

	//BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDTaskSystemGC2GMNtfFinishMainTaskEvent, &BSLib::Framework::CreateCMessage<CMsgTaskSystemGC2GMNtfFinishMainTaskEvent>);
	//GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDTaskSystemGC2GMNtfFinishMainTaskEvent, &CRoleTaskModule::_onMsgTaskSystemGC2GMNtfFinishMainTaskEvent, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDTaskSystemGC2GMReqNotifyMainTaskStateUpdate, &BSLib::Framework::CreateCMessage<CMsgTaskSystemGC2GMReqNotifyMainTaskStateUpdate>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDTaskSystemGC2GMReqNotifyMainTaskStateUpdate, &CRoleTaskModule::_onMsgTaskSystemGC2GMReqNotifyMainTaskStateUpdate, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDTaskSystemGC2GMReqGetPetTask, &BSLib::Framework::CreateCMessage<CMsgTaskSystemGC2GMReqGetPetTask>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDTaskSystemGC2GMReqGetPetTask, &CRoleTaskModule::_onMsgTaskSystemGC2GMReqGetPetTask, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDTaskSystemGC2GMReqRefreshPetTask, &BSLib::Framework::CreateCMessage<CMsgTaskSystemGC2GMReqRefreshPetTask>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDTaskSystemGC2GMReqRefreshPetTask, &CRoleTaskModule::_onMsgTaskSystemGC2GMReqRefreshPetTask, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDTaskSystemGC2GMReqUpdatePetTaskState, &BSLib::Framework::CreateCMessage<CMsgTaskSystemGC2GMReqUpdatePetTaskState>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDTaskSystemGC2GMReqUpdatePetTaskState, &CRoleTaskModule::_onMsgTaskSystemGC2GMReqUpdatePetTaskState, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDTaskSystemGC2GMReqGetPetTaskPrize, &BSLib::Framework::CreateCMessage<CMsgTaskSystemGC2GMReqGetPetTaskPrize>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDTaskSystemGC2GMReqGetPetTaskPrize, &CRoleTaskModule::_onMsgTaskSystemGC2GMReqGetPetTaskPrize, this);

}

void CRoleTaskModule::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(MsgIDTaskSystemGC2GMReqGetDailyTaskList);
	a_msgExecMgr->delMsgExecPtr(MsgIDTaskSystemGC2GMReqGetDailyTaskPrize);
	a_msgExecMgr->delMsgExecPtr(MsgIDTaskSystemGC2GMReqGetMainTaskList);
	a_msgExecMgr->delMsgExecPtr(MsgIDTaskSystemGC2GMReqGetMainTaskPrize);
	//a_msgExecMgr->delMsgExecPtr(MsgIDTaskSystemGC2GMNtfFinishMainTaskEvent);
	a_msgExecMgr->delMsgExecPtr(MsgIDTaskSystemGC2GMReqNotifyMainTaskStateUpdate);
	a_msgExecMgr->delMsgExecPtr(MsgIDTaskSystemGC2GMReqGetPetTask);
	a_msgExecMgr->delMsgExecPtr(MsgIDTaskSystemGC2GMReqRefreshPetTask);
	a_msgExecMgr->delMsgExecPtr(MsgIDTaskSystemGC2GMReqUpdatePetTaskState);
	a_msgExecMgr->delMsgExecPtr(MsgIDTaskSystemGC2GMReqGetPetTaskPrize);

}

void CRoleTaskModule::onRoleActive()
{
	_onRoleActive();
	//todo test code
	//CRoleTaskSystemData data;
	//data.m_dailyRefreshNewTaskCount = 1;
	//data.m_lastUpdateTime = 2;
	//_updateTaskSystemData(data);

	//CRolePetTaskData rolePetTaskData;
	//rolePetTaskData.m_taskTPID = 2;
	//rolePetTaskData.m_count = 1;
	//rolePetTaskData.m_state = ETASKSTATE_ACCEPT;
	//rolePetTaskData.m_taskAcceptTime = 1;
	//rolePetTaskData.m_taskAttr = NULL;
	//_updatePetTask(rolePetTaskData);
	//_removeAllPetTableData();
}

void CRoleTaskModule::onRoleInactive()
{
	;
}

void CRoleTaskModule::updateDataToDB()
{
	;
}

bool CRoleTaskModule::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	if (a_tableID == EDBABLEID_ROLE_MAIN_TASK_DATA) {
		m_mainTaskTable = a_keyTable;
	} else if (a_tableID == EDBABLEID_ROLE_TASK_SYSTEM_DATA ) {
		m_roleTaskSystemDataTable = a_keyTable;
	}

	if (a_sessionID == 0) {
		if (a_tableID == EDBABLEID_ROLE_MAIN_TASK_DATA) {
			DB::CRoleMainTaskDataDB task;
			task.m_accountID = getRoleGM()->getAccountID();
			task.m_zoneID = getRoleGM()->getZoneID();
			task.m_roleIndex = getRoleGM()->getRoleIndex();

			BSLib::Database::CDBTableRow*  row = a_keyTable->getRow(task.getDBKey());
			if (row != NULL) {
				BSLib::Utility::CStream stream;
				row->serializeTo(stream);
				task.serializeFrom(stream);
				const CMainTaskAttr * taskAttr = CTaskDataMgr::singleton().getMainTask(task.m_curTaskTPID);
				if (taskAttr != NULL) {
					m_roleMainTaskData.m_curTaskTPID = task.m_curTaskTPID;
					m_roleMainTaskData.m_acceptTime = task.m_acceptTime;
					m_roleMainTaskData.m_curCount = task.m_curCount;
					m_roleMainTaskData.m_state = task.m_state;
					m_roleMainTaskData.m_taskAttr = taskAttr;
				}
			}
		} else if (a_tableID == EDBABLEID_ROLE_TASK_SYSTEM_DATA) {
			DB::CRoleTaskSystemData taskSystemData;
			taskSystemData.m_accountID = getRoleGM()->getAccountID();
			taskSystemData.m_zoneID = getRoleGM()->getZoneID();
			taskSystemData.m_roleIndex = getRoleGM()->getRoleIndex();
			BSLib::Database::CDBTableRow * row = a_keyTable->getRow(taskSystemData.getKey());			
			if (row != NULL) {
				BSLib::Utility::CStream stream;
				row->serializeTo(stream);
				taskSystemData.serializeFrom(stream);
				m_roleTaskSystemData.m_taskCompletedCount = taskSystemData.m_taskCompletedCount;
				m_roleTaskSystemData.m_dailyRefreshNewTaskCount = taskSystemData.m_dailyRefreshNewTaskCount;
				m_roleTaskSystemData.m_lastUpdateTime = taskSystemData.m_lastUpdateTime;
			}
		}
	} else if (a_sessionID == GSLIB_SESSIONID_CREATE_ROLE_FINISH) {
		const CMainTaskAttr *mainTaskAttr = CTaskDataMgr::singleton().getFirstMainTask();
		if (mainTaskAttr != NULL) {
			m_roleMainTaskData.m_curTaskTPID = mainTaskAttr->m_taskTPID;
			m_roleMainTaskData.m_acceptTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
			m_roleMainTaskData.m_state = ETASKSTATE_ACCEPT;
			m_roleMainTaskData.m_taskAttr = mainTaskAttr;
			updateMainTaskTable(m_roleMainTaskData);
		}
	}

	return true;
}

bool CRoleTaskModule::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	class CDailyTaskTableCallBack : public BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
	{
	public:
		CDailyTaskTableCallBack(BSLib::Utility::CHashMap<BSLib::uint32, CRoleDailyTaskData> & hashDailyTask)
			:m_hashDailyTask(hashDailyTask)
		{
		}
		~CDailyTaskTableCallBack()
		{
		}
	public:
		virtual bool exec(const std::string& _key, BSLib::Database::CDBTableRow* & _value)
		{
			if (_value != NULL) {
				BSLib::Utility::CStream stream;
				_value->serializeTo(stream);
				DB::CRoleDailyTaskDataDB data;
				data.serializeFrom(stream);

				const CDailyTaskAttr * taskAttr = CTaskDataMgr::singleton().getDailyTask(data.m_taskTPID);
				if (taskAttr != NULL) {
					CRoleDailyTaskData dailyTask;
					dailyTask.m_taskTPID = data.m_taskTPID;
					dailyTask.m_taskAcceptTime = data.m_acceptTime;
					dailyTask.m_count = data.m_count;
					dailyTask.m_state = data.m_state;
					dailyTask.m_taskAttr = taskAttr;
					m_hashDailyTask.setValue(dailyTask.m_taskTPID, dailyTask);
				}
			}
			return true;
		}
	private:
		BSLib::Utility::CHashMap<BSLib::uint32, CRoleDailyTaskData> & m_hashDailyTask;
	};

	class CPetTaskTableCallBack : public BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
	{
	public:
		CPetTaskTableCallBack(BSLib::Utility::CHashMap<BSLib::uint32, CRolePetTaskData> & hashPetTask)
			:m_hashPetTask(hashPetTask)
		{
		}
		~CPetTaskTableCallBack()
		{
		}
	public:
		virtual bool exec(const std::string& _key, BSLib::Database::CDBTableRow* & _value)
		{
			if (_value != NULL) {
				BSLib::Utility::CStream stream;
				_value->serializeTo(stream);
				DB::CRolePetTaskDataDB data;
				data.serializeFrom(stream);

				const CPetTaskAttr * taskAttr = CTaskDataMgr::singleton().getPetTaskByTaskID(data.m_taskTPID);
				if (taskAttr != NULL) {
					CRolePetTaskData petTask;
					petTask.m_taskIndex = data.m_taskIndex;
					petTask.m_color = data.m_taskColor;
					petTask.m_taskAcceptTime = data.m_acceptTime;
					petTask.m_curCount = data.m_count;
					petTask.m_state = data.m_state;
					petTask.m_taskAttr = taskAttr;
					m_hashPetTask.setValue(petTask.m_taskIndex, petTask);
				}
			}
			return true;
		}
	private:
		BSLib::Utility::CHashMap<BSLib::uint32, CRolePetTaskData> & m_hashPetTask;
	};

	if (a_tableID == EDBABLEID_ROLE_DAILY_TASK_DATA) {
		m_dailyTaskTable = a_keyTable;
	} else if (a_tableID == EDBABLEID_ROLE_PET_TASK_DATA ) {
		m_petTaskTable = a_keyTable;
	}
	
	if (a_sessionID != 1) {
		if (a_tableID == EDBABLEID_ROLE_DAILY_TASK_DATA) {
			CDailyTaskTableCallBack callBack(m_hashDailyTask);
			a_keyTable->traversal(callBack);
		} else if (a_tableID == EDBABLEID_ROLE_PET_TASK_DATA) {
			CPetTaskTableCallBack callBack(m_hashPetTask);
			a_keyTable->traversal(callBack);
		}
	}

	return true;
}

void CRoleTaskModule::_onMsgTaskSystemGC2GMReqGetDailyTaskList(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgTaskSystemGM2GCAckGetDailyTaskList	msgAck;
	msgAck.m_result = EGET_TASK_DAILY_LIST_RESULT_SUCCESS;
	for (BSLib::Utility::CHashMap<BSLib::uint32, CRoleDailyTaskData>::iterator itr = m_hashDailyTask.begin(); itr != m_hashDailyTask.end(); ++itr) {
		if (itr->second.m_taskAttr != NULL) {
			CRoleDailyTaskData & task = itr->second;
			if (task.getState() < ETASKSTATE_GOT_PRIZE) {
				CRoleDailyTaskDataSend taskSend;	
				taskSend.m_taskAttr = *(task.m_taskAttr);
				taskSend.m_count = task.m_count;
				taskSend.m_state = task.m_state;
				msgAck.m_listRoleDailyTask.push_back(taskSend);
			}
		}
	}

	sendMsgToClient(msgAck);
}

void CRoleTaskModule::_onMsgTaskSystemGC2GMReqGetDailyTaskPrize(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL || getRoleGM() == NULL) {
		return;
	}

	CMsgTaskSystemGC2GMReqGetDailyTaskPrize *msgReq = (CMsgTaskSystemGC2GMReqGetDailyTaskPrize *)a_msg;
	BSLib::Utility::CHashMap<BSLib::uint32, CRoleDailyTaskData>::iterator itr = m_hashDailyTask.find(msgReq->m_taskTPID);	
	EGetDailyTaskPrizeResult result(EGET_DAILY_TASK_PRIZE_RESULT_SUCCESS);
	if (itr == m_hashDailyTask.end()) {
		result = EGET_DAILY_TASK_PRIZE_RESULT_NOT_EXIST;
	} else {
		CRoleDailyTaskData & task = itr->second;
		if (!task.isValid()) {
			result = EGET_DAILY_TASK_PRIZE_RESULT_FAIL;
		}
		if (!task.hasCompleted()) {
			result = EGET_DAILY_TASK_PRIZE_RESULT_NOT_COMPLETE_YET;
		}

		if (task.getState() == ETASKSTATE_GOT_PRIZE) {
			result = EGET_DAILY_TASK_PRIZE_RESULT_ALREADY_GOT_PRIZE;
		}

		if (result != EGET_DAILY_TASK_PRIZE_RESULT_SUCCESS) {
			CMsgTaskSystemGM2GCAckGetDailyTaskPrize msgAck;
			msgAck.m_result = result;
			sendMsgToClient(msgAck);
		} else {
			GSLib::PrizeSystem::GM::CRolePrizeModule *prizeModule = (GSLib::PrizeSystem::GM::CRolePrizeModule*)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PRIZE);
			if (prizeModule != NULL) {
				std::string sneder = toMailString("系统信息");
				std::string title = toMailString("日常任务奖励(背包满)");
				std::string content = toMailString("恭喜您!获得了日常任务奖励，奖励如下：");
				std::vector<GSLib::ItemSystem::GM::CPrizeItem> vecItems;
				prizeModule->prizeRequest(task.m_taskAttr->m_vecItems, sneder, title, content, "");//todo
				task.m_state = ETASKSTATE_GOT_PRIZE;
				updateDailyTaskTable(task);
				CMsgTaskSystemGM2GCAckGetDailyTaskPrize msgAck;
				msgAck.m_result = EGET_DAILY_TASK_PRIZE_RESULT_SUCCESS;
				sendMsgToClient(msgAck);
			}
		}
	}
}

void CRoleTaskModule::_onMsgTaskSystemGC2GMReqGetMainTaskList(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL || getRoleGM() == NULL || m_roleMainTaskData.m_taskAttr == NULL) {
		return;
	}

	if (m_roleMainTaskData.m_state > ETASKSTATE_FINISH) {
		const CMainTaskAttr *nextTaskAttr = CTaskDataMgr::singleton().getNextMainTask(m_roleMainTaskData.m_curTaskTPID);
		if (nextTaskAttr != NULL) {
			m_roleMainTaskData.m_curTaskTPID = nextTaskAttr->m_taskTPID;
			m_roleMainTaskData.m_state = ETASKSTATE_NONE ;
			m_roleMainTaskData.m_acceptTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
			m_roleMainTaskData.m_curCount = 0;
			if (getRoleGM()->getLevel() >= nextTaskAttr->getLevelLimit()) {
				m_roleMainTaskData.m_state = ETASKSTATE_ACCEPT;
			}
			m_roleMainTaskData.m_taskAttr = nextTaskAttr;
		}
		updateMainTaskTable(m_roleMainTaskData);
	}

	CMsgTaskSystemGM2GCAckGetMainTaskList msgAck;
	msgAck.m_result = EGET_TASK_MAIN_LIST_RESULT_SUCCESS;
	msgAck.m_roleMainTask.m_taskAttr = *m_roleMainTaskData.m_taskAttr;
	msgAck.m_roleMainTask.m_state = m_roleMainTaskData.m_state;
	msgAck.m_roleMainTask.m_curCount = m_roleMainTaskData.m_curCount;
	sendMsgToClient(msgAck);	
}

void CRoleTaskModule::_onMsgTaskSystemGC2GMReqNotifyMainTaskStateUpdate(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgTaskSystemGC2GMReqNotifyMainTaskStateUpdate *msgReq = (CMsgTaskSystemGC2GMReqNotifyMainTaskStateUpdate *)a_msg;
	if (msgReq == NULL) {
		return;
	}
	EUpdateMainTaskStateResult result = _canUpdateMainTaskStage(msgReq->m_taskID, msgReq->m_curCount);
	if (result == EUPDATE_MAIN_TASK_STATE_RESULT_SUCCESS ) {
		_updateMainTask(msgReq->m_taskID, msgReq->m_curCount);
	}

	CMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate msgAck;
	msgAck.m_result = result;
	sendMsgToClient(msgAck);

	if (result == EUPDATE_MAIN_TASK_STATE_RESULT_SUCCESS) {
		CMsgTaskSystemGM2GCNtfMainTaskState msgNtf;
		msgNtf.m_mainTaskTPID = m_roleMainTaskData.m_curTaskTPID;
		msgNtf.m_state = m_roleMainTaskData.m_state;
		msgNtf.m_curCount = m_roleMainTaskData.m_curCount;
		sendMsgToClient(msgNtf);
	}
}

void CRoleTaskModule::_onMsgTaskSystemGC2GMReqGetMainTaskPrize(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL || getRoleGM() == NULL) {
		return;
	}

	CMsgTaskSystemGM2GCAckGetMainTaskPrize msgAck;
	EGetMainTaskPrizeResult result = EGET_MAIN_TASK_PRIZE_RESULT_SUCCESS;
	if (m_roleMainTaskData.m_curTaskTPID == 0) {
		result = EGET_MAIN_TASK_PRIZE_RESULT_NOT_EXIST;
	}

	if (!m_roleMainTaskData.isValid()) {
		result = EGET_MAIN_TASK_PRIZE_RESULT_FAIL;	
	}

	if (m_roleMainTaskData.getState() < ETASKSTATE_FINISH) {
		result = EGET_MAIN_TASK_PRIZE_RESULT_NOT_COMPLETE_YET;	
	}

	if (m_roleMainTaskData.getState() > ETASKSTATE_FINISH) {
		result = EGET_MAIN_TASK_PRIZE_RESULT_ALREADY_GOT_PRIZE;
	}

	msgAck.m_result = result;
	if (result != EGET_MAIN_TASK_PRIZE_RESULT_SUCCESS) {
		msgAck.m_result = result;
		sendMsgToClient(msgAck);
	} else {
		GSLib::PrizeSystem::GM::CRolePrizeModule *prizeModule = (GSLib::PrizeSystem::GM::CRolePrizeModule*)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PRIZE);
		if (prizeModule != NULL) {
			std::string sneder = toMailString("系统信息");
			std::string title = toMailString("主线任务奖励(背包满)");
			std::string content = toMailString("恭喜您获得主线任务奖励,奖励如下:");
			prizeModule->prizeRequest(m_roleMainTaskData.m_taskAttr->m_vecPrizeItem, sneder, title, content, "MainTaskPrize");//todo
			for (std::vector<ItemSystem::GM::CPrizeItem>::const_iterator itr = m_roleMainTaskData.m_taskAttr->m_vecPrizeItem.begin(); 
				itr != m_roleMainTaskData.m_taskAttr->m_vecPrizeItem.end(); ++itr) {
					BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "获得主线任务奖励:id[%d] count[%d]", itr->m_itemTPID, itr->m_itemCount);
			}
			m_roleMainTaskData.m_state = ETASKSTATE_GOT_PRIZE;
			sendMsgToClient(msgAck);
		}
		if (m_roleMainTaskData.getType() == EMAIN_TASK_TYPE_ITEM_DROP) {
			PlayerSystem::GM::CRoleBagModuleGM *roleBag = (PlayerSystem::GM::CRoleBagModuleGM *)getRoleGM()->getRoleBag();
			BSLib::uint32 count = roleBag->getItemCount(m_roleMainTaskData.getAttr()->getDropItemTPID());
			roleBag->forceRemoveItemCount( m_roleMainTaskData.getAttr()->getDropItemTPID(), count, "", true);
		}
		const CMainTaskAttr *nextTaskAttr = CTaskDataMgr::singleton().getNextMainTask(m_roleMainTaskData.m_curTaskTPID);
		if (nextTaskAttr != NULL) {
			m_roleMainTaskData.m_curTaskTPID = nextTaskAttr->m_taskTPID;
			m_roleMainTaskData.m_acceptTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
			m_roleMainTaskData.m_curCount = 0;
			m_roleMainTaskData.m_state = ETASKSTATE_NONE;
			if (getRoleGM()->getLevel() >= nextTaskAttr->getLevelLimit()) {
				m_roleMainTaskData.m_state = ETASKSTATE_ACCEPT;
			}
			m_roleMainTaskData.m_taskAttr = nextTaskAttr;
		}
		updateMainTaskTable(m_roleMainTaskData);
	}
}

void CRoleTaskModule::_onMsgTaskSystemGC2GMNtfFinishMainTaskEvent(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	//if (a_msg == NULL) {
	//	return;
	//}
	//CMsgTaskSystemGC2GMNtfFinishMainTaskEvent *msgNtf = (CMsgTaskSystemGC2GMNtfFinishMainTaskEvent *)a_msg;
	//EMainTaskType type = msgNtf->m_taskType;
	//BSLib::uint32 param1 = msgNtf->m_param1;
	//BSLib::uint32 param2 = msgNtf->m_param2;
	//if (type == EMAIN_TASK_TYPE_DIALOGUE) {
	//	if (m_roleMainTaskData.getType() == type) {
	//		if (m_roleMainTaskData.m_taskAttr->m_para1 == param1 && m_roleMainTaskData.m_taskAttr->m_para2 == param2) {
	//			m_roleMainTaskData.m_state = ETASKSTATE_FINISH;
	//			updateMainTaskTable(m_roleMainTaskData);
	//			CMsgTaskSystemGM2GCNtfMainTaskState msgNtf;
	//			msgNtf.m_mainTaskTPID = m_roleMainTaskData.m_curTaskTPID;
	//			msgNtf.m_state = m_roleMainTaskData.m_state;
	//			sendMsgToClient(msgNtf);
	//		}
	//	}
	//}
}

void CRoleTaskModule::_onMsgTaskSystemGC2GMReqGetPetTask(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL || getRoleGM() == NULL) {
		return;
	}

	if (m_hashPetTask.empty()) {
		_getNewPetTaskData(C_MAX_PET_TASK_PER_TIME);
	}
	CMsgTaskSystemGM2GCAckGetPetTask msgAck;
	msgAck.m_result = EGET_PET_TASK_RESULT_SUCCESS;
	for (BSLib::Utility::CHashMap<BSLib::uint32, CRolePetTaskData>::iterator itr = m_hashPetTask.begin(); itr != m_hashPetTask.end(); ++itr) {
		msgAck.m_petTaskInfo.m_petTaskList.push_back(itr->second);
	}
	msgAck.m_petTaskInfo.m_dailyRefreshCount = m_roleTaskSystemData.m_dailyRefreshNewTaskCount;
	msgAck.m_petTaskInfo.m_nextRefreshDiamondCost = _getRefreshDiamondCost(m_roleTaskSystemData.m_dailyRefreshNewTaskCount);
	msgAck.m_petTaskInfo.m_taskCompletedCount = m_roleTaskSystemData.m_taskCompletedCount;
	msgAck.m_petTaskInfo.m_totalCount = C_MAX_DAILY_PET_TASK;
	sendMsgToClient(msgAck);
}

void CRoleTaskModule::_onMsgTaskSystemGC2GMReqRefreshPetTask(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (getRoleGM() == NULL) {
		return;
	}
	ERefreshPetTaskResult result(EREFRESH_PET_TASK_RESULT_SUCCESS);
	PetSystem::GM::CPetModule *petModule = (PetSystem::GM::CPetModule *)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PET);
	if (petModule == NULL) {
		result = EREFRESH_PET_TASK_RESULT_FAIL;
	}
	if (petModule->getPetCount() <= 0) {
		result = EREFRESH_PET_TASK_RESULT_FAIL;
	}

	if (m_roleTaskSystemData.m_taskCompletedCount >= C_MAX_DAILY_PET_TASK) {
		result = EREFRESH_PET_TASK_RESULT_REACH_MAX_DAILY_COUNT;
	}
	BSLib::uint32 costDiamond = _getRefreshDiamondCost(m_roleTaskSystemData.m_dailyRefreshNewTaskCount + 1);
	//todo
	if (!getRoleGM()->delDiamond(costDiamond,"")) {
		result = EREFRESH_PET_TASK_RESULT_NOT_ENOUGH_DIAMOND;
	}
	CMsgTaskSystemGM2GCAckRefreshPetTask msgAck;
	msgAck.m_result = result;
	if (result == EREFRESH_PET_TASK_RESULT_SUCCESS) {
		++m_roleTaskSystemData.m_dailyRefreshNewTaskCount;
		m_hashPetTask.clear();
		_updateTaskSystemData(m_roleTaskSystemData);
		_removeAllPetTableData();

		for (BSLib::uint32 i = 0; i < C_MAX_PET_TASK_PER_TIME; ++i) {
			CRolePetTaskData petData;
			_getRandomPetTask(petData);
			if (petData.isValid()) {
				m_hashPetTask.setValue(petData.m_taskIndex, petData);
				_updatePetTask(petData);
				msgAck.m_refreshInfo.m_rolePetTaskList.push_back(petData);
				msgAck.m_refreshInfo.m_dailyRefreshCount = m_roleTaskSystemData.m_dailyRefreshNewTaskCount;
				msgAck.m_refreshInfo.m_nextRefreshDiamondCost = _getRefreshDiamondCost(m_roleTaskSystemData.m_dailyRefreshNewTaskCount + 1);
			}
		}
	}

	sendMsgToClient(msgAck);
}
void CRoleTaskModule::_onMsgTaskSystemGC2GMReqUpdatePetTaskState(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}
	CMsgTaskSystemGC2GMReqUpdatePetTaskState *msgReq = (CMsgTaskSystemGC2GMReqUpdatePetTaskState *)a_msg;

	EUpdatePetTaskStateResult result = _canUpdatePetTaskResult(msgReq->m_taskIndex, msgReq->m_state, msgReq->m_curCount);
	if (result == EUPDATE_PET_TASK_STATE_SUCCESS) {
		BSLib::Utility::CHashMap<BSLib::uint32, CRolePetTaskData>::iterator itr = m_hashPetTask.find(msgReq->m_taskIndex);
		if (itr != m_hashPetTask.end()) {
			CRolePetTaskData & petTask = itr->second;
			if (petTask.m_state != msgReq->m_state || petTask.m_curCount != msgReq->m_curCount) {
				petTask.m_state = msgReq->m_state;
				petTask.m_curCount = msgReq->m_curCount;
				if (msgReq->m_state == ETASKSTATE_ACCEPT) {
					petTask.m_taskAcceptTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
				}
				_updatePetTask(petTask);
			}
		}
	}
	CMsgTaskSystemGM2GCAckUpdatePetTaskState msgAck;
	msgAck.m_result = result;
	msgAck.m_taskIndex = msgReq->m_taskIndex;
	msgAck.m_taskState = msgReq->m_state;	
	msgAck.m_curCount = msgReq->m_curCount;
	sendMsgToClient(msgAck);
}

void CRoleTaskModule::_onMsgTaskSystemGC2GMReqGetPetTaskPrize(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL || getRoleGM() == NULL) {
		return;
	}

	CMsgTaskSystemGC2GMReqGetPetTaskPrize *msgReq = (CMsgTaskSystemGC2GMReqGetPetTaskPrize *)a_msg;
	EGetPetTaskPrizeResult result(EGET_PET_TASK_PRIZE_SUCCESS);
	BSLib::Utility::CHashMap<BSLib::uint32, CRolePetTaskData>::iterator itr = 
		m_hashPetTask.find(msgReq->m_taskIndex);
	if (itr == m_hashPetTask.end()) {
		result = EGET_PET_TASK_PRIZE_INVALID_TASK_INDEX;
	}
	CRolePetTaskData & petTask = itr->second;
	if (petTask.m_state != ETASKSTATE_FINISH) {
		result = EGET_PET_TASK_PRIZE_INVALID_TASK_STATE;
	}
	if (result == EGET_PET_TASK_PRIZE_SUCCESS) {
		//prize
		GSLib::PrizeSystem::GM::CRolePrizeModule *prizeModule = (GSLib::PrizeSystem::GM::CRolePrizeModule*)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PRIZE);
		if (prizeModule != NULL) {
			std::string sneder = toMailString("系统信息");
			std::string title = toMailString("伙伴任务奖励(背包满)");
			std::string content = toMailString("恭喜您获得丰厚的伙伴任务奖励，奖励如下:");
			CPetTaskColorPrize prize;
			petTask.getPrize(prize);
			PetSystem::GM::CPetModule *petModule = (PetSystem::GM::CPetModule *)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PET);
			if (petModule != NULL) {
				petModule->addPetFriendlyValueByPetTPID(petTask.m_taskAttr->m_petID, prize.m_freindlyValue);
			}
			prizeModule->prizeRequest(prize.m_prizeItemList, sneder, title, content, "PetTaskPrize");//todo
			for (std::vector<ItemSystem::GM::CPrizeItem>::const_iterator itr = prize.m_prizeItemList.begin(); 
				itr != prize.m_prizeItemList.end(); ++itr) {
					BSLIB_LOG_ERROR(ETT_GSLIB_TASKSYSTEM, "获得伙伴任务任务奖励:id[%d] count[%d]\n", itr->m_itemTPID, itr->m_itemCount);
			}
		}
		if (petTask.getType() == EPET_TASK_TYPE_MONSTER_DROP || petTask.getType() == EPET_TASK_TYPE_BOSS_DROP) {
			PlayerSystem::GM::CRoleBagModuleGM *roleBag = (PlayerSystem::GM::CRoleBagModuleGM *)getRoleGM()->getRoleBag();
			BSLib::uint32 count = roleBag->getItemCount(petTask.getDropItemTPID());
			roleBag->forceRemoveItemCount( petTask.getDropItemTPID(), count, "", true);
		}
		petTask.m_state = ETASKSTATE_GOT_PRIZE;
		_updatePetTask(petTask);
		++m_roleTaskSystemData.m_taskCompletedCount;
		_updateTaskSystemData(m_roleTaskSystemData);
		if (_curRoundPetTaskFinished()) {
			if (m_roleTaskSystemData.m_taskCompletedCount < C_MAX_DAILY_PET_TASK) {
				m_hashPetTask.clear();
				_removeAllPetTableData();
				_getNewPetTaskData(C_MAX_PET_TASK_PER_TIME);
			}
		}
	}

	CMsgTaskSystemGM2GCAckGetPetTaskPrize msgAck;
	msgAck.m_result = result;
	msgAck.m_taskIndex = msgReq->m_taskIndex;
	sendMsgToClient(msgAck);
}

void CRoleTaskModule::onTaskSystemDataReset()
{
	onDailyTaskDataReset();
	onPetTaskDataReset();
}

void CRoleTaskModule::onDailyTaskDataReset()
{
	removeAllDailyTableData();
	m_hashDailyTask.clear();
	_getRandomDailyTask(m_hashDailyTask);
}

void CRoleTaskModule::onPetTaskDataReset()
{
	_removeAllPetTableData();
	m_hashPetTask.clear();
	m_roleTaskSystemData.m_dailyRefreshNewTaskCount = 0;
	m_roleTaskSystemData.m_taskCompletedCount = 0;
	m_roleTaskSystemData.m_lastUpdateTime =  (BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds();

	_updateTaskSystemData(m_roleTaskSystemData);
}

void CRoleTaskModule::updateDailyTask(EDailyTaskType taskType)
{
	for (BSLib::Utility::CHashMap<BSLib::uint32, CRoleDailyTaskData>::iterator itr = m_hashDailyTask.begin(); itr != m_hashDailyTask.end(); ++itr) {
		CRoleDailyTaskData & task = itr->second;
		if (task.isValid()) {
			if (task.getType() == taskType) {
				if (!task.hasCompleted()) {
					task.update();
					updateDailyTaskTable(task);
				}
			}
		}
	}
}

CRoleMainTaskData & CRoleTaskModule::getMainTaskData()
{
	return m_roleMainTaskData;
}

void CRoleTaskModule::updateDailyTaskTable(CRoleDailyTaskData &dailyTask)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_TASKSYSTEM, "CRoleTaskModule::updateDailyTable:getRoleGM OR getRoleGM()->getPlayerGM() error");
		return;
	}

	DB::CRoleDailyTaskDataDB dailyTaskDB;
	dailyTaskDB.m_accountID = getRoleGM()->getAccountID();
	dailyTaskDB.m_zoneID = getRoleGM()->getZoneID();
	dailyTaskDB.m_roleIndex = getRoleGM()->getRoleIndex();
	dailyTaskDB.m_taskTPID = dailyTask.m_taskTPID;
	dailyTaskDB.m_acceptTime = dailyTask.m_taskAcceptTime;
	dailyTaskDB.m_count = dailyTask.m_count;
	dailyTaskDB.m_state = dailyTask.m_state;

	BSLib::Utility::CStream stream;
	dailyTaskDB.serializeTo(stream);
	m_dailyTaskTable->update(dailyTaskDB.getDBKey(), stream);
	m_dailyTaskTable->saveDataToDBServer(dailyTaskDB.getDBKey(), dailyTaskDB.getIndexKey(), true);
}

void CRoleTaskModule::removeAllDailyTableData()
{
	m_dailyTaskTable->removeAll();
	m_dailyTaskTable->saveDataToDBServer(true);
}

void CRoleTaskModule::updateMainTaskTable(CRoleMainTaskData &mainTask)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_TASKSYSTEM, "CRoleTaskModule::updateMainTaskTable:getRoleGM OR getRoleGM()->getPlayerGM() error");
		return;
	}
	DB::CRoleMainTaskDataDB roleMainTaskDB;
	roleMainTaskDB.m_accountID = getRoleGM()->getAccountID();
	roleMainTaskDB.m_zoneID = getRoleGM()->getZoneID();
	roleMainTaskDB.m_roleIndex = getRoleGM()->getRoleIndex();
	roleMainTaskDB.m_curTaskTPID = m_roleMainTaskData.m_curTaskTPID;
	roleMainTaskDB.m_curCount = m_roleMainTaskData.m_curCount;
	roleMainTaskDB.m_acceptTime = m_roleMainTaskData.m_acceptTime;
	roleMainTaskDB.m_state = m_roleMainTaskData.m_state;
	BSLib::Utility::CStream stream;
	roleMainTaskDB.serializeTo(stream);
	m_mainTaskTable->update(roleMainTaskDB.getDBKey(), stream);
	m_mainTaskTable->saveDataToDBServer(roleMainTaskDB.getDBKey(), true);
}

void CRoleTaskModule::updateMainTask(BSLib::uint32 a_curRoleLevel)
{
	if (m_roleMainTaskData.isValid()) {
		if (m_roleMainTaskData.m_state == ETASKSTATE_NONE) {
			if (a_curRoleLevel >= m_roleMainTaskData.m_taskAttr->m_levelLimit) {
				m_roleMainTaskData.m_state = ETASKSTATE_ACCEPT;
				CMsgTaskSystemGM2GCNtfMainTaskState msgNtf;
				msgNtf.m_mainTaskTPID = m_roleMainTaskData.m_curTaskTPID;
				msgNtf.m_state = m_roleMainTaskData.m_state;
				msgNtf.m_curCount = m_roleMainTaskData.m_curCount;
				sendMsgToClient(msgNtf);
			}
		}
	}
}

void CRoleTaskModule::_getRandomDailyTask(BSLib::Utility::CHashMap<BSLib::uint32, CRoleDailyTaskData> &hashDailyTask)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_TASKSYSTEM, "CRoleTaskModule::_getRandomDailyTask:getRoleGM OR getRoleGM()->getPlayerGM() error");
	}

	const BSLib::Utility::CHashMap<BSLib::uint32, CDailyTaskAttr*> & hashDailyTaskAttrs = CTaskDataMgr::singleton().getDailyTask();
	std::vector<CDailyTaskAttr *> vecDailyTaskAttrs;
	for (BSLib::Utility::CHashMap<BSLib::uint32, CDailyTaskAttr*>::const_iterator itr = hashDailyTaskAttrs.begin(); itr != hashDailyTaskAttrs.end(); ++itr) {
		if (itr->second != NULL) {
			if (getRoleGM()->getLevel() >= itr->second->m_minRequiredRoleLevel && getRoleGM()->getLevel() <= itr->second->m_maxRequiredRoleLevel) {
				vecDailyTaskAttrs.push_back(itr->second);
			}
		}
	}

	if (vecDailyTaskAttrs.size() <= C_MAX_DAILY_TASK_COUNT) {
		for (std::vector<CDailyTaskAttr *>::iterator itr = vecDailyTaskAttrs.begin(); itr != vecDailyTaskAttrs.end(); ++itr) {
			CRoleDailyTaskData dailyTask(**itr);
			hashDailyTask.setValue(dailyTask.m_taskTPID, dailyTask);
			updateDailyTaskTable(dailyTask);
		}
	} else {
		BSLib::Utility::CRandom::setRandomSeed((BSLib::uint32)getRoleGM()->getAccountID() + (BSLib::uint32)time(NULL));
		for (BSLib::uint32 i = 0; i < C_MAX_DAILY_TASK_COUNT; ++i) {
			if (vecDailyTaskAttrs.empty()) {
				break;
			}
			BSLib::int32 pos = BSLib::Utility::CRandom::randomBetween(0, vecDailyTaskAttrs.size() - 1);
			CDailyTaskAttr* dailyTaskAttr = vecDailyTaskAttrs[pos];
			if (dailyTaskAttr != NULL) {
				CRoleDailyTaskData dailyTask(*dailyTaskAttr);
				hashDailyTask.setValue(dailyTask.m_taskTPID, dailyTask);
				vecDailyTaskAttrs.erase(vecDailyTaskAttrs.begin() + pos);
				updateDailyTaskTable(dailyTask);
			}
		}
	}
}

void CRoleTaskModule::_onRoleActive()
{
	if (m_hashDailyTask.empty()) {
		_getRandomDailyTask(m_hashDailyTask);
	}

	if (m_roleTaskSystemData.m_lastUpdateTime < CTaskSystemGM::singleton().getLastTaskSystemDataResetTime()) {
		onTaskSystemDataReset();
	}

	if (m_roleMainTaskData.m_curTaskTPID == 0) {
		const CMainTaskAttr *mainTaskAttr = CTaskDataMgr::singleton().getFirstMainTask();
		if (mainTaskAttr != NULL) {
			m_roleMainTaskData.m_curTaskTPID = mainTaskAttr->m_taskTPID;
			m_roleMainTaskData.m_acceptTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
			if (getRoleGM() != NULL) {
				if (getRoleGM()->getLevel() >= mainTaskAttr->getLevelLimit()) {
					m_roleMainTaskData.m_state = ETASKSTATE_ACCEPT;
				}
			}
			m_roleMainTaskData.m_state = ETASKSTATE_ACCEPT;
			m_roleMainTaskData.m_taskAttr = mainTaskAttr;
			updateMainTaskTable(m_roleMainTaskData);
		} 
	}
	if (m_hashPetTask.empty()) {
		_getNewPetTaskData(C_MAX_PET_TASK_PER_TIME);
	}
	m_roleTaskSystemData.m_curPetTaskIndex = _getPetTaskIndex() + 1;
}

void CRoleTaskModule::_updateMainTask(BSLib::uint32 a_mainTaskTPID, BSLib::uint32 a_reportCount)
{
	if (m_roleMainTaskData.updateStage(a_mainTaskTPID, a_reportCount)) {
		updateMainTaskTable(m_roleMainTaskData);
	}
}

void CRoleTaskModule::_updateTaskSystemData(const CRoleTaskSystemData &a_roleTaskSystemData)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_TASKSYSTEM, "CRoleTaskModule::_updateTaskSystemData:getRoleGM OR getRoleGM()->getPlayerGM() error");
		return;
	}
	DB::CRoleTaskSystemData roleTaskSystemData;
	roleTaskSystemData.m_accountID = getRoleGM()->getAccountID();
	roleTaskSystemData.m_zoneID = getRoleGM()->getZoneID();
	roleTaskSystemData.m_roleIndex = getRoleGM()->getRoleIndex();
	roleTaskSystemData.m_taskCompletedCount = a_roleTaskSystemData.m_taskCompletedCount;
	roleTaskSystemData.m_dailyRefreshNewTaskCount = a_roleTaskSystemData.m_dailyRefreshNewTaskCount;
	roleTaskSystemData.m_lastUpdateTime = a_roleTaskSystemData.m_lastUpdateTime;
	BSLib::Utility::CStream stream;
	roleTaskSystemData.serializeTo(stream);
	m_roleTaskSystemDataTable->update(roleTaskSystemData.getKey(), stream);
	m_roleTaskSystemDataTable->saveDataToDBServer(roleTaskSystemData.getKey(), true);
}

void CRoleTaskModule::_updatePetTask(const CRolePetTaskData & a_petTaskData)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_TASKSYSTEM, "CRoleTaskModule::_updatePetTask:getRoleGM OR getRoleGM()->getPlayerGM() error");
		return;
	}
	if (!a_petTaskData.isValid()) {
		return;
	}

	DB::CRolePetTaskDataDB petTaskDB;
	petTaskDB.m_accountID = getRoleGM()->getAccountID();
	petTaskDB.m_zoneID = getRoleGM()->getZoneID();
	petTaskDB.m_roleIndex = getRoleGM()->getRoleIndex();
	petTaskDB.m_taskIndex = a_petTaskData.m_taskIndex;
	petTaskDB.m_taskTPID = a_petTaskData.getTPID();
	petTaskDB.m_taskColor = a_petTaskData.m_color;
	petTaskDB.m_acceptTime = a_petTaskData.m_taskAcceptTime;
	petTaskDB.m_count = a_petTaskData.m_curCount;
	petTaskDB.m_state = a_petTaskData.m_state;

	BSLib::Utility::CStream stream;
	petTaskDB.serializeTo(stream);
	m_petTaskTable->update(petTaskDB.getDBKey(), stream);
	m_petTaskTable->saveDataToDBServer(petTaskDB.getDBKey(), petTaskDB.getIndexKey(), true);	
}

void CRoleTaskModule::_removeAllPetTableData()
{
	m_petTaskTable->removeAll();
	m_petTaskTable->saveDataToDBServer(true);
}

GSLib::TaskSystem::GM::EUpdateMainTaskStateResult CRoleTaskModule::_canUpdateMainTaskStage(BSLib::uint32 a_mainTaskTPID, BSLib::uint32 a_reportCount)
{
	if (a_mainTaskTPID != m_roleMainTaskData.m_curTaskTPID) {
		return EUPDATE_MAIN_TASK_STATE_RESULT_INVALID_TASK_ID;
	}
	if (m_roleMainTaskData.m_state != ETASKSTATE_ACCEPT) {
		return EUPDATE_MAIN_TASK_STATE_RESULT_INVALID_TASK_STATE;
	}
	if (m_roleMainTaskData.m_curCount > a_reportCount) {
		return EUPDATE_MAIN_TASK_STATE_RESULT_INVALID_REPORT_COUNT;
	}
	return EUPDATE_MAIN_TASK_STATE_RESULT_SUCCESS;
}

void CRoleTaskModule::_getRandomPetTask(CRolePetTaskData & a_petTaskData)
{
	if (getRoleGM() == NULL) {
		return;
	}
	PetSystem::GM::CPetModule *petModule = (PetSystem::GM::CPetModule *)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PET);
	if (petModule != NULL) {
		PetSystem::GM::CPetGM *pet = petModule->randomPet();
		if (pet != NULL) {
			CPetTaskAttr *petTaskAttr = CTaskDataMgr::singleton().getRandomPetTask(pet->getTPID(), getRoleGM()->getLevel());	
			if (petTaskAttr != NULL) {
				a_petTaskData.m_taskAttr = petTaskAttr;
				a_petTaskData.m_taskAcceptTime = 0;
				a_petTaskData.m_curCount = 0;
				a_petTaskData.m_state = ETASKSTATE_NONE ;
				a_petTaskData.m_taskIndex = m_roleTaskSystemData.m_curPetTaskIndex++;
				//a_petTaskData.m_taskIndex = m_hashPetTask.size();
				a_petTaskData.m_color = CTaskDataMgr::singleton().genRandomPetTaskColor();
			}
		}
	}
}

BSLib::uint32 CRoleTaskModule::_getRefreshDiamondCost(BSLib::uint32 a_refreshCount)
{
	if (a_refreshCount < 3) {
		return 0;
	}
	return a_refreshCount * 5;
}

void CRoleTaskModule::_getNewPetTaskData(BSLib::uint32 a_count)
{
	for (BSLib::uint32 i = 0; i < a_count; ++i) {
		CRolePetTaskData petData;
		_getRandomPetTask(petData);
		if (petData.isValid()) {
			m_hashPetTask.setValue(petData.m_taskIndex, petData);
			_updatePetTask(petData);
		}
	}
}

GSLib::TaskSystem::GM::EUpdatePetTaskStateResult CRoleTaskModule::_canUpdatePetTaskResult(BSLib::uint32 a_taskIndex, ETaskState a_state, BSLib::int32 a_count)
{
	BSLib::Utility::CHashMap<BSLib::uint32, CRolePetTaskData>::iterator itr = 
		m_hashPetTask.find(a_taskIndex);
	if (itr == m_hashPetTask.end()) {
		return EUPDATE_PET_TASK_STATE_INVALID_TASK_INDEX;
	}
	CRolePetTaskData & petTask = itr->second;
	if (a_state < ETASKSTATE_ACCEPT || a_state > ETASKSTATE_FINISH || petTask.m_state > a_state) {
		return EUPDATE_PET_TASK_STATE_INVALID_TASK_STATE;
	}
	if (a_state == ETASKSTATE_ACCEPT) {
		if (petTask.m_state != ETASKSTATE_NONE && a_count == 0) {
			return EUPDATE_PET_TASK_STATE_INVALID_TASK_STATE;
		}
		if (m_roleTaskSystemData.m_taskCompletedCount >= C_MAX_DAILY_PET_TASK) {
			return EUPDATE_PET_TASK_STATE_REACH_DAILY_MAX_COUNT;
		}
	}
	if (a_state == ETASKSTATE_FINISH) {
		if (petTask.m_state != ETASKSTATE_ACCEPT) {
			return EUPDATE_PET_TASK_STATE_INVALID_TASK_STATE;
		}
	}
	if (a_count < petTask.m_curCount) {
		return EUPDATE_PET_TASK_STATE_INVALID_COUNT;
	}

	return EUPDATE_PET_TASK_STATE_SUCCESS;
}

BSLib::uint32 CRoleTaskModule::_getPetTaskIndex() const
{
	BSLib::uint32 index = 0;
	for (BSLib::Utility::CHashMap<BSLib::uint32, CRolePetTaskData>::const_iterator itr = m_hashPetTask.begin(); itr != m_hashPetTask.end(); ++itr) {
		CRolePetTaskData petTask = itr->second;
		if (petTask.m_taskIndex > index) {
			index = petTask.m_taskIndex;
		}
	}

	return index;
}

bool CRoleTaskModule::_curRoundPetTaskFinished() const
{
	for (BSLib::Utility::CHashMap<BSLib::uint32, CRolePetTaskData>::const_iterator itr = m_hashPetTask.begin(); itr != m_hashPetTask.end(); ++itr) {
		CRolePetTaskData petTask = itr->second;
		if (petTask.m_state != ETASKSTATE_GOT_PRIZE) {
			return false;
		}
	}
	return true;
}



}//GM

}//TaskSystem

}//GSLib
