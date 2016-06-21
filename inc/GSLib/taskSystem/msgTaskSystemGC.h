#ifndef __GSLIB_TASKSYSTEM_MSGTASKSYSTEMGC_H__
#define __GSLIB_TASKSYSTEM_MSGTASKSYSTEMGC_H__

#include <list>
#include <GSLib/taskSystem/msgNumIDTaskSystem.h>
#include <GSLib/taskSystem/GM/taskData.h>
#include <GSLib/taskSystem/GM/taskSystemError.h>

namespace GSLib
{

namespace TaskSystem
{
const BSLib::uint32 MsgIDTaskSystemGM2GCAckGetDailyTaskList = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GM2GC_ACK_GET_DAILY_TASK_LIST);
class CMsgTaskSystemGM2GCAckGetDailyTaskList: public GFLib::CMessage
{
public:
	CMsgTaskSystemGM2GCAckGetDailyTaskList() 
	:GFLib::CMessage(MsgIDTaskSystemGM2GCAckGetDailyTaskList)
	{
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::int8)m_result;
		if (m_result == GM::EGET_TASK_DAILY_LIST_RESULT_SUCCESS) {
			BSLib::uint16 size = (BSLib::uint16)m_listRoleDailyTask.size();
			stream << size;
			for (std::list<GM::CRoleDailyTaskDataSend>::const_iterator itr = m_listRoleDailyTask.begin(); itr != m_listRoleDailyTask.end(); ++itr) {
				itr->serializeTo(stream);
			}
		}
		return true;
	}

public:
	GM::EGetTaskDailyListResult m_result;
	std::list<GM::CRoleDailyTaskDataSend> m_listRoleDailyTask;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGM2GCAckGetDailyTaskPrize = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GM2GC_ACK_GET_DAILY_TASK_PRIZE);
class CMsgTaskSystemGM2GCAckGetDailyTaskPrize: public GFLib::CMessage
{
public:
	CMsgTaskSystemGM2GCAckGetDailyTaskPrize() 
		:GFLib::CMessage(MsgIDTaskSystemGM2GCAckGetDailyTaskPrize)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::int8)m_result;
		return true;
	}

public:
	GM::EGetDailyTaskPrizeResult m_result;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGM2GCAckGetMainTaskList = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GM2GC_ACK_GET_MAIN_TASK_LIST);
class CMsgTaskSystemGM2GCAckGetMainTaskList: public GFLib::CMessage
{
public:
	CMsgTaskSystemGM2GCAckGetMainTaskList() 
		:GFLib::CMessage(MsgIDTaskSystemGM2GCAckGetMainTaskList)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::int8)m_result;
		if (m_result == GM::EGET_TASK_MAIN_LIST_RESULT_SUCCESS) {
			m_roleMainTask.serializeTo(stream);
		}

		return true;
	}
public:
	GM::EGetTaskMainListResult m_result;
	GM::CRoleMainTaskDataSend m_roleMainTask;
};

const BSLib::uint32 MsgIDTaskSystemGM2GCAckNotifyMainTaskStateUpdate = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GM2GC_ACK_NOTIFY_MAIN_TASK_UPDATE);
class CMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate: public GFLib::CMessage
{
public:
	CMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate() 
	:GFLib::CMessage(MsgIDTaskSystemGM2GCAckNotifyMainTaskStateUpdate)
	{
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::int8)m_result;
		return true;
	}
public:
	GM::EUpdateMainTaskStateResult m_result;
public:
};               
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGM2GCAckGetMainTaskPrize = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GM2GC_ACK_GET_MAIN_TASK_PRIZE);
class CMsgTaskSystemGM2GCAckGetMainTaskPrize: public GFLib::CMessage
{
public:
	CMsgTaskSystemGM2GCAckGetMainTaskPrize() 
	:GFLib::CMessage(MsgIDTaskSystemGM2GCAckGetMainTaskPrize)
	{
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::int8)m_result;
		if(m_result == GM::EGET_MAIN_TASK_PRIZE_RESULT_SUCCESS) {
			//m_nextMainTask.serializeTo(stream);
		}
		return true;
	}
public:
	GM::EGetMainTaskPrizeResult m_result;
	//GM::CRoleMainTaskDataSend m_nextMainTask;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGM2GCNtfMainTaskState = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GM2GC_NTF_MAIN_TASK_STATE);
class CMsgTaskSystemGM2GCNtfMainTaskState: public GFLib::CMessage
{
public:
	CMsgTaskSystemGM2GCNtfMainTaskState() 
	:GFLib::CMessage(MsgIDTaskSystemGM2GCNtfMainTaskState)
	,m_mainTaskTPID(0)
	,m_curCount(0)
	,m_state(GM::ETASKSTATE_NONE)
	{
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_mainTaskTPID;
		stream << m_curCount;
		stream << (BSLib::int8)m_state;
		return true;
	}
public:
	BSLib::uint32 m_mainTaskTPID;
	BSLib::uint32 m_curCount;
	GM::ETaskState m_state;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGM2GCAckGetPetTask = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GM2GC_ACK_GET_PET_TASK);
class CMsgTaskSystemGM2GCAckGetPetTask: public GFLib::CMessage
{
public:
	CMsgTaskSystemGM2GCAckGetPetTask() 
	:GFLib::CMessage(MsgIDTaskSystemGM2GCAckGetPetTask)
	,m_result(GM::EGET_PET_TASK_RESULT_FAIL)
	{
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::uint8)m_result;
		m_petTaskInfo.serializeTo(stream);
		return true;
	}

public:
	GM::EGetPetTaskResult m_result;
	GM::CPetTaskInfo m_petTaskInfo;
};               

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGM2GCAckRefreshPetTask = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GM2GC_ACK_REFRESH_PET_TASK);
class CMsgTaskSystemGM2GCAckRefreshPetTask: public GFLib::CMessage
{
public:
	CMsgTaskSystemGM2GCAckRefreshPetTask() 
	:GFLib::CMessage(MsgIDTaskSystemGM2GCAckRefreshPetTask)
	,m_result(GM::EREFRESH_PET_TASK_RESULT_FAIL)
	{
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::uint8)m_result;
		m_refreshInfo.serializeTo(stream);
		return true;
	}

public:
	GM::ERefreshPetTaskResult m_result;
	GM::CRefreshPetTaskInfo m_refreshInfo;
};               

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGM2GCAckUpdatePetTaskState = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GM2GC_ACK_UPDATE_PET_TASK_STATE);
class CMsgTaskSystemGM2GCAckUpdatePetTaskState: public GFLib::CMessage
{
public:
	CMsgTaskSystemGM2GCAckUpdatePetTaskState() 
	:GFLib::CMessage(MsgIDTaskSystemGM2GCAckUpdatePetTaskState)
	,m_result(GM::EUPDATE_PET_TASK_STATE_FAIL)
	,m_taskIndex(0)
	,m_taskState(GM::ETASKSTATE_NONE)
	,m_curCount(0)
	{
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::uint8)m_result;
		stream << m_taskIndex;
		stream << (BSLib::uint8)m_taskState;
		stream << m_curCount;
		return true;
	}

public:
	GM::EUpdatePetTaskStateResult m_result;
	BSLib::uint32 m_taskIndex;
	GM::ETaskState m_taskState;
	BSLib::uint16 m_curCount;
};               

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGM2GCAckGetPetTaskPrize = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GM2GC_ACK_GET_PET_TASK_PRIZE);
class CMsgTaskSystemGM2GCAckGetPetTaskPrize: public GFLib::CMessage
{
public:
	CMsgTaskSystemGM2GCAckGetPetTaskPrize() 
	:GFLib::CMessage(MsgIDTaskSystemGM2GCAckGetPetTaskPrize)
	,m_result(GM::EGET_PET_TASK_PRIZE_FAIL)
	,m_taskIndex(0)
	{
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::uint8)m_result;
		stream << m_taskIndex;
		return true;
	}

public:
	GM::EGetPetTaskPrizeResult m_result;
	BSLib::uint32 m_taskIndex;
};               





}//TaskSystem

}//GSLib

#endif//__GSLIB_TASKSYSTEM_MSGTASKSYSTEMGC_H__

