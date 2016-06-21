#ifndef __GSLIB_TASKSYSTEM_MSGTASKSYSTEMGM_H__
#define __GSLIB_TASKSYSTEM_MSGTASKSYSTEMGM_H__

#include <GSLib/taskSystem/msgNumIDTaskSystem.h>
#include <GSLib/taskSystem/GM/taskSystemDefine.h>

namespace GSLib
{

namespace TaskSystem
{

//获取每日日常任务列表
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGC2GMReqGetDailyTaskList = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GC2GM_REQ_GET_DAILY_TASK_LIST);
class CMsgTaskSystemGC2GMReqGetDailyTaskList : public GFLib::CMessage
{
public:
	CMsgTaskSystemGC2GMReqGetDailyTaskList() : GFLib::CMessage(MsgIDTaskSystemGC2GMReqGetDailyTaskList)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		return true;
	}

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGC2GMReqGetDailyTaskPrize = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GC2GM_REQ_GET_DAILY_TASK_PRIZE);
class CMsgTaskSystemGC2GMReqGetDailyTaskPrize : public GFLib::CMessage
{
public:
	CMsgTaskSystemGC2GMReqGetDailyTaskPrize()
	:GFLib::CMessage(MsgIDTaskSystemGC2GMReqGetDailyTaskPrize)
	,m_taskTPID(0)
	{
	}
protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_taskTPID;
		return true;
	}
public:
	BSLib::uint32 m_taskTPID;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGC2GMReqGetMainTaskList = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GC2GM_REQ_GET_MAIN_TASK_LIST);
class CMsgTaskSystemGC2GMReqGetMainTaskList : public GFLib::CMessage
{
public:
	CMsgTaskSystemGC2GMReqGetMainTaskList() : GFLib::CMessage(MsgIDTaskSystemGC2GMReqGetMainTaskList)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		return true;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGC2GMReqNotifyMainTaskStateUpdate = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GC2GM_REQ_NOTIFY_MAIN_TASK_UPDATE);
class CMsgTaskSystemGC2GMReqNotifyMainTaskStateUpdate : public GFLib::CMessage
{
public:
	CMsgTaskSystemGC2GMReqNotifyMainTaskStateUpdate()
	:GFLib::CMessage(MsgIDTaskSystemGC2GMReqNotifyMainTaskStateUpdate)
	,m_taskID(0)
	,m_curCount(0)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_taskID;
		stream >> m_curCount;
		return true;
	}
public:
	BSLib::uint32 m_taskID;
	BSLib::uint32 m_curCount;
};                     

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGC2GMReqGetMainTaskPrize = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GC2GM_REQ_GET_MAIN_TASK_PRIZE);
class CMsgTaskSystemGC2GMReqGetMainTaskPrize : public GFLib::CMessage
{
public:
	CMsgTaskSystemGC2GMReqGetMainTaskPrize()
	:GFLib::CMessage(MsgIDTaskSystemGC2GMReqGetMainTaskPrize)
	{
	}
protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		return true;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGC2GMNtfFinishMainTaskEvent = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GC2GM_NTF_FINISH_MAIN_TASK_EVENT);
class CMsgTaskSystemGC2GMNtfFinishMainTaskEvent : public GFLib::CMessage
{
public:
	CMsgTaskSystemGC2GMNtfFinishMainTaskEvent()
	:GFLib::CMessage(MsgIDTaskSystemGC2GMNtfFinishMainTaskEvent)
	,m_taskType(GM::EMAIN_TASK_TYPE_NONE)
	,m_param1(0)
	,m_param2(0)
	{
	}
protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		BSLib::int8 type;
		stream >> type;
		m_taskType = (GM::EMainTaskType)type;
		stream >> m_param1;
		stream >> m_param2;
		return true;
	}
public:
	GM::EMainTaskType m_taskType;
	BSLib::uint32 m_param1;
	BSLib::uint32 m_param2;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGC2GMReqGetPetTask = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GC2GM_REQ_GET_PET_TASK);
class CMsgTaskSystemGC2GMReqGetPetTask : public GFLib::CMessage
{
public:
	CMsgTaskSystemGC2GMReqGetPetTask() : GFLib::CMessage(MsgIDTaskSystemGC2GMReqGetPetTask)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		return true;
	}

};                     

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGC2GMReqRefreshPetTask = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GC2GM_REQ_REFRESH_PET_TASK);
class CMsgTaskSystemGC2GMReqRefreshPetTask : public GFLib::CMessage
{
public:
	CMsgTaskSystemGC2GMReqRefreshPetTask() : GFLib::CMessage(MsgIDTaskSystemGC2GMReqRefreshPetTask)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		return true;
	}

};                     

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGC2GMReqUpdatePetTaskState = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GC2GM_REQ_UPDATE_PET_TASK_STATE);
class CMsgTaskSystemGC2GMReqUpdatePetTaskState : public GFLib::CMessage
{
public:
	CMsgTaskSystemGC2GMReqUpdatePetTaskState() : GFLib::CMessage(MsgIDTaskSystemGC2GMReqUpdatePetTaskState)
	,m_taskIndex(0)
	,m_state(GM::ETASKSTATE_NONE)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_taskIndex;
		BSLib::uint8 state;
		stream >> state;
		m_state = (GM::ETaskState)state;
		stream >> m_curCount;
		return true;
	}
public:
	BSLib::uint32 m_taskIndex;
	GM::ETaskState m_state;
	BSLib::uint16 m_curCount;
};                     

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDTaskSystemGC2GMReqGetPetTaskPrize = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_TASKSYSTEM, EMSGNUMID_TASKSYSTEM_GC2GM_REQ_GET_PET_TASK_PRIZE);
class CMsgTaskSystemGC2GMReqGetPetTaskPrize : public GFLib::CMessage
{
public:
	CMsgTaskSystemGC2GMReqGetPetTaskPrize() : GFLib::CMessage(MsgIDTaskSystemGC2GMReqGetPetTaskPrize)
	,m_taskIndex(0)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_taskIndex;
		return true;
	}
public:
	BSLib::uint32 m_taskIndex;
};                     



}//TaskSystem

}//GSLib

#endif//__GSLIB_TASKSYSTEM_MSGTASKSYSTEMGM_H__

