using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// 获取角色日常任务列表
    /// </summary>
    class CMsgTaskSystemGC2GMReqGetDailyTaskList : UnityFrame.CMsg
    {
        public CMsgTaskSystemGC2GMReqGetDailyTaskList()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GC2GM_REQ_GET_DAILY_TASK_LIST)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    /// <summary>
    /// 获取日常任务奖励
    /// </summary>
    class CMsgTaskSystemGC2GMReqGetDailyTaskPrize : UnityFrame.CMsg
    {
        public CMsgTaskSystemGC2GMReqGetDailyTaskPrize(UInt32 taskTPID)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GC2GM_REQ_GET_DAILY_TASK_PRIZE)
        {
            m_taskTPID = taskTPID;
        }

        public UInt32 m_taskTPID = 0;

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_taskTPID);
            return true;
        }
    }

    class CMsgTaskSystemGC2GMNtfFinishMainTaskEvent : UnityFrame.CMsg
    {
        public CMsgTaskSystemGC2GMNtfFinishMainTaskEvent(EMainTaskType type, UInt32 param1, UInt32 param2)
        :base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GC2GM_NTF_FINISH_MAIN_TASK_EVENT)
        {
            m_type = type;
            m_param1 = param1;
            m_param2 = param2;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write((byte)m_type);
            msgStream.Write(m_param1);
            msgStream.Write(m_param2);

            return true;
        }

        public EMainTaskType m_type;
        public UInt32 m_param1 = 0;
        public UInt32 m_param2 = 0;
    }

     /// <summary>
    /// 获取当前主线任务
    /// </summary>
    class CMsgTaskSystemGC2GMReqGetMainTaskList : UnityFrame.CMsg
    {
        public CMsgTaskSystemGC2GMReqGetMainTaskList()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GC2GM_REQ_GET_MAIN_TASK_LIST)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    /// <summary>
    /// 汇报任务进度
    /// </summary>
    class CMsgTaskSystemGC2GMReqNotifyMainTaskStateUpdate : UnityFrame.CMsg
    {
        public CMsgTaskSystemGC2GMReqNotifyMainTaskStateUpdate(UInt32 taskID, UInt32 curCount)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GC2GM_REQ_NOTIFY_MAIN_TASK_UPDATE)
        {
            m_taskID = taskID;
            m_curCount = curCount;
        }

        public UInt32 m_taskID = 0;
        public UInt32 m_curCount = 0;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_taskID);
            msgStream.Write(m_curCount);
            return true;
        }
    }

    /// <summary>
    /// 获取主线任务奖励
    /// </summary>
    class CMsgTaskSystemGC2GMReqGetMainTaskPrize : UnityFrame.CMsg
    {
        public CMsgTaskSystemGC2GMReqGetMainTaskPrize()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GC2GM_REQ_GET_MAIN_TASK_PRIZE)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    class CMsgTaskSystemGC2GMReqGetPetTask : UnityFrame.CMsg
    {
        public CMsgTaskSystemGC2GMReqGetPetTask()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GC2GM_REQ_GET_PET_TASK)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    class CMsgTaskSystemGC2GMReqRefreshPetTask : UnityFrame.CMsg
    {
        public CMsgTaskSystemGC2GMReqRefreshPetTask()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GC2GM_REQ_REFRESH_PET_TASK)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    class CMsgTaskSystemGC2GMReqUpdatePetTaskState : UnityFrame.CMsg
    {
        public CMsgTaskSystemGC2GMReqUpdatePetTaskState(UInt32 taskIndex, ETaskState state, UInt16 curCount)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GC2GM_REQ_UPDATE_PET_TASK_STATE)
        {
            m_taskIndex = taskIndex;
            m_state = state;
            m_curCount = curCount;
        }

        UInt32 m_taskIndex;
        ETaskState m_state;
        UInt16 m_curCount;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_taskIndex);
            msgStream.Write((byte)m_state);
            msgStream.Write(m_curCount);

            return true;
        }
    }

    class CMsgTaskSystemGC2GMReqGetPetTaskPrize : UnityFrame.CMsg
    {
        public CMsgTaskSystemGC2GMReqGetPetTaskPrize(UInt32 taskIndex)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GC2GM_REQ_GET_PET_TASK_PRIZE)
        {
            m_taskIndex = taskIndex;
        }

        UInt32 m_taskIndex;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_taskIndex);
            
            return true;
        }
    }


                       
                       









                       

                                          
}
