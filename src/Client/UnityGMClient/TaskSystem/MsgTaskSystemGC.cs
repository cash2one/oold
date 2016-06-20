using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
     //获取日常任务列表返回
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgTaskSystemGM2GCAckGetDailyTaskList : UnityFrame.CMsg
    {
        public CMsgTaskSystemGM2GCAckGetDailyTaskList()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GM2GC_ACK_GET_DAILY_TASK_LIST)
        {

        }

        public EGetDailyTaskListResult m_result;
        public List<CRoleDailyTaskData> m_listRoleDailyTask = new List<CRoleDailyTaskData>();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            byte result = 0;
            result = msgStream.ReadByte();
            m_result = (EGetDailyTaskListResult)result;
            if (m_result == EGetDailyTaskListResult.EGET_TASK_DAILY_LIST_RESULT_SUCCESS)
            {
                UInt16 count = msgStream.ReadUShort();
                for (UInt16 i = 0; i < count; ++i )
                {
                    CRoleDailyTaskData task = new CRoleDailyTaskData();
                    task.serializeFrom(msgStream);
                    m_listRoleDailyTask.Add(task);
                }
            }

            return true;
        }

        public static CClientCore.CBMsgTaskSystemGM2GCAckGetDailyTaskList s_cb = null;
        public static void CallBack(CMsgTaskSystemGM2GCAckGetDailyTaskList ack)
        {
            if (CMsgTaskSystemGM2GCAckGetDailyTaskList.s_cb == null)
            {
                return;
            }
            CMsgTaskSystemGM2GCAckGetDailyTaskList.s_cb((EGetDailyTaskListResult)ack.m_result, ack.m_listRoleDailyTask);
        }
    }

    class CMsgTaskSystemGM2GCAckGetDailyTaskPrize : UnityFrame.CMsg
    {
        public CMsgTaskSystemGM2GCAckGetDailyTaskPrize()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GM2GC_ACK_GET_DAILY_TASK_PRIZE)
        {

        }

        public EGetDailyTaskPrizeResult m_result;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            byte result = 0;
            result = msgStream.ReadByte();
            m_result = (EGetDailyTaskPrizeResult)result;

            return true;
        }

        public static CClientCore.CBMsgTaskSystemGM2GCAckGetDailyTaskPrize s_cb = null;
        public static void CallBack(CMsgTaskSystemGM2GCAckGetDailyTaskPrize ack)
        {
            if (CMsgTaskSystemGM2GCAckGetDailyTaskPrize.s_cb != null)
            {
                CMsgTaskSystemGM2GCAckGetDailyTaskPrize.s_cb((EGetDailyTaskPrizeResult)ack.m_result);
            }
        }
    }
 
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgTaskSystemGM2GCAckGetMainTaskPrize : UnityFrame.CMsg
    {
        public CMsgTaskSystemGM2GCAckGetMainTaskPrize()
        :base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GM2GC_ACK_GET_MAIN_TASK_PRIZE)
        {
        }

        public EGetMainTaskPrizeResult m_result;
        //public CRoleMainTaskData m_roleNextMainTask = new CRoleMainTaskData();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EGetMainTaskPrizeResult)msgStream.ReadByte();
            if (m_result == EGetMainTaskPrizeResult.EGET_MAIN_TASK_PRIZE_RESULT_SUCCESS)
            {
                //m_roleNextMainTask.serializeFrom(msgStream);
            }

            return true;
        }

        public static CClientCore.CBMsgTaskSystemGM2GCAckGetMainTaskPrize s_cb = null;
        public static void CallBack(CMsgTaskSystemGM2GCAckGetMainTaskPrize ack)
        {
            if (CMsgTaskSystemGM2GCAckGetMainTaskPrize.s_cb != null)
            {
                CMsgTaskSystemGM2GCAckGetMainTaskPrize.s_cb((EGetDailyTaskPrizeResult)ack.m_result);
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgTaskSystemGM2GCNtfMainTaskState : UnityFrame.CMsg
    {
        public CMsgTaskSystemGM2GCNtfMainTaskState()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GM2GC_NTF_MAIN_TASK_STATE)
        {
        }

        public UInt32 m_mainTaskTPID = 0;
        public UInt32 m_curCount = 0;
        public ETaskState m_state;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_mainTaskTPID = msgStream.ReadUInt();
            m_curCount = msgStream.ReadUInt();
            m_state = (ETaskState)msgStream.ReadByte();

            return true;
        }

        public static CClientCore.CBMsgTaskSystemGM2GCNtfMainTaskState s_cb = null;
        public static void CallBack(CMsgTaskSystemGM2GCNtfMainTaskState ack)
        {
            if (CMsgTaskSystemGM2GCNtfMainTaskState.s_cb != null)
            {
                CMsgTaskSystemGM2GCNtfMainTaskState.s_cb(ack.m_mainTaskTPID, ack.m_state, ack.m_curCount);
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgTaskSystemGM2GCAckGetMainTaskList : UnityFrame.CMsg
    {
        public CMsgTaskSystemGM2GCAckGetMainTaskList()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GM2GC_ACK_GET_MAIN_TASK_LIST)
        {
        }

        public EGetMainTaskListResult m_result;
        public CRoleMainTaskData m_roleDailyTask = new CRoleMainTaskData();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            byte result = 0;
            result = msgStream.ReadByte();
            m_result = (EGetMainTaskListResult)result;
            if (m_result == EGetMainTaskListResult.EGET_TASK_MAIN_LIST_RESULT_SUCCESS)
            {
                    m_roleDailyTask.serializeFrom(msgStream);
            }

            return true;
        }

        public static CClientCore.CBMsgTaskSystemGM2GCAckGetMainTaskList s_cb = null;
        public static void CallBack(CMsgTaskSystemGM2GCAckGetMainTaskList ack)
        {
            if (CMsgTaskSystemGM2GCAckGetMainTaskList.s_cb != null)
            {
                CMsgTaskSystemGM2GCAckGetMainTaskList.s_cb((EGetMainTaskListResult)ack.m_result, ack.m_roleDailyTask);
            }
        }
    }
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate : UnityFrame.CMsg
    {
        public CMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GM2GC_ACK_NOTIFY_MAIN_TASK_UPDATE)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EUpdateMainTaskStateResult)msgStream.ReadByte();
            return true;
        }

        public EUpdateMainTaskStateResult m_result;
        public static CClientCore.CBMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate s_cb = null;
        public static void CallBack(CMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate ack)
        {
            if (CMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate.s_cb != null)
            {
                CMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate.s_cb(ack.m_result);
            }
        }
    }

    class CMsgTaskSystemGM2GCAckGetPetTask : UnityFrame.CMsg
    {
        public CMsgTaskSystemGM2GCAckGetPetTask()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GM2GC_ACK_GET_PET_TASK)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EGetPetTaskResult)msgStream.ReadByte();
            m_petTaskInfo.serializeFrom(msgStream);

            return true;
        }

        public EGetPetTaskResult m_result;
        public CPetTaskInfo m_petTaskInfo = new CPetTaskInfo();
        public static CClientCore.CBMsgTaskSystemGM2GCAckGetPetTask s_cb = null;
        public static void CallBack(CMsgTaskSystemGM2GCAckGetPetTask ack)
        {
            if (CMsgTaskSystemGM2GCAckGetPetTask.s_cb != null)
            {
                CMsgTaskSystemGM2GCAckGetPetTask.s_cb(ack.m_result, ack.m_petTaskInfo);
            }

        }
    }

    class CMsgTaskSystemGM2GCAckRefreshPetTask : UnityFrame.CMsg
    {
        public CMsgTaskSystemGM2GCAckRefreshPetTask()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GM2GC_ACK_REFRESH_PET_TASK)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (ERefreshPetTaskResult)msgStream.ReadByte();
            m_refreshInfo.serializeFrom(msgStream);

            return true;
        }

        ERefreshPetTaskResult m_result;
        CRefreshPetTaskInfo m_refreshInfo = new CRefreshPetTaskInfo();
        public static CClientCore.CBMsgTaskSystemGM2GCAckRefreshPetTask s_cb = null;
        public static void CallBack(CMsgTaskSystemGM2GCAckRefreshPetTask ack)
        {
            if (CMsgTaskSystemGM2GCAckRefreshPetTask.s_cb != null)
            {
                CMsgTaskSystemGM2GCAckRefreshPetTask.s_cb(ack.m_result, ack.m_refreshInfo);
            }

        }
    }

    class CMsgTaskSystemGM2GCAckUpdatePetTaskState : UnityFrame.CMsg
    {
        public CMsgTaskSystemGM2GCAckUpdatePetTaskState()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GM2GC_ACK_UPDATE_PET_TASK_STATE)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EUpdatePetTaskStateResult)msgStream.ReadByte();
            m_taskIndex = msgStream.ReadUInt();
            m_taskState = (ETaskState)msgStream.ReadByte();
            m_curCount = msgStream.ReadUShort();

            return true;
        }

        EUpdatePetTaskStateResult m_result;
        UInt32 m_taskIndex;
        ETaskState m_taskState;
        UInt16 m_curCount;
        public static CClientCore.CBMsgTaskSystemGM2GCAckUpdatePetTaskState s_cb = null;
        public static void CallBack(CMsgTaskSystemGM2GCAckUpdatePetTaskState ack)
        {
            if (CMsgTaskSystemGM2GCAckUpdatePetTaskState.s_cb != null)
            {
                CMsgTaskSystemGM2GCAckUpdatePetTaskState.s_cb(ack.m_result, ack.m_taskIndex, ack.m_taskState, ack.m_curCount);
            }

        }
    }

    class CMsgTaskSystemGM2GCAckGetPetTaskPrize : UnityFrame.CMsg
    {
        public CMsgTaskSystemGM2GCAckGetPetTaskPrize()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_TASKSYSTEM, CTaskSystemMsgNumID.EMSGNUMID_TASKSYSTEM_GM2GC_ACK_GET_PET_TASK_PRIZE)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EGetPetTaskPrizeResult)msgStream.ReadByte();
            m_taskIndex = msgStream.ReadUInt();

            return true;
        }

        EGetPetTaskPrizeResult m_result;
        UInt32 m_taskIndex;
        public static CClientCore.CBMsgTaskSystemGM2GCAckGetPetTaskPrize s_cb = null;
        public static void CallBack(CMsgTaskSystemGM2GCAckGetPetTaskPrize ack)
        {
            if (CMsgTaskSystemGM2GCAckGetPetTaskPrize.s_cb != null)
            {
                CMsgTaskSystemGM2GCAckGetPetTaskPrize.s_cb(ack.m_result, ack.m_taskIndex);
            }

        }
    }



                                  
                                  

                                  

                                  
                                  



}
