using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {
        /// <summary>
        /// 获取日常任务列表回调
        /// </summary>
        /// <param name="result"></param>
        /// <param name="listDailyTaskData"></param>
        public delegate void CBMsgTaskSystemGM2GCAckGetDailyTaskList(EGetDailyTaskListResult result, List<CRoleDailyTaskData> listDailyTaskData);
        /// <summary>
        /// 发送获取日常任务列表接口
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgTaskSystemGC2GMReqGetDailyTaskList(CBMsgTaskSystemGM2GCAckGetDailyTaskList cb)
        {
            CMsgTaskSystemGC2GMReqGetDailyTaskList req = new CMsgTaskSystemGC2GMReqGetDailyTaskList();
            CMsgTaskSystemGM2GCAckGetDailyTaskList.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>
        /// 获取日常任务奖励回调
        /// </summary>
        /// <param name="result"></param>
        public delegate void CBMsgTaskSystemGM2GCAckGetDailyTaskPrize(EGetDailyTaskPrizeResult result);
        /// <summary>
        /// 发送获取日常任务奖励接口
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgTaskSystemGC2GMReqGetDailyTaskPrize(UInt32 taskTPID, CBMsgTaskSystemGM2GCAckGetDailyTaskPrize cb)
        {
            CMsgTaskSystemGC2GMReqGetDailyTaskPrize req = new CMsgTaskSystemGC2GMReqGetDailyTaskPrize(taskTPID);
            CMsgTaskSystemGM2GCAckGetDailyTaskPrize.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        public bool SendMsgTaskSystemGC2GMNtfFinishMainTaskEvent(EMainTaskType type, UInt32 param1, UInt32 param2)
        {
            CMsgTaskSystemGC2GMNtfFinishMainTaskEvent ntf = new CMsgTaskSystemGC2GMNtfFinishMainTaskEvent(type, param1, param2);
            return CGameClient.Singleton.SendMsg(ntf);
        }

        /// <summary>
        /// 通知服务器已完成某个对白任务
        /// </summary>
        /// <param name="type"></param>
        /// <param name="param1"></param>
        /// <param name="param2"></param>
        /// <returns></returns>
        public bool FinishMainTaskDialogueEvent(UInt32 param1, UInt32 param2)
        {
            return SendMsgTaskSystemGC2GMNtfFinishMainTaskEvent(EMainTaskType.EMAIN_TASK_TYPE_DIALOGUE, param1, param2);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>
        /// 获取主线任务信息回调
        /// </summary>
        /// <param name="result"></param>
        /// <param name="mainTaskList"></param>
        public delegate void CBMsgTaskSystemGM2GCAckGetMainTaskList(EGetMainTaskListResult result, CRoleMainTaskData mainTaskList);
        /// <summary>
        /// 发送获取主线信息请求
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgTaskSystemGC2GMReqGetMainTaskList(CBMsgTaskSystemGM2GCAckGetMainTaskList cb)
        {
            CMsgTaskSystemGC2GMReqGetMainTaskList req = new CMsgTaskSystemGC2GMReqGetMainTaskList();
            CMsgTaskSystemGM2GCAckGetMainTaskList.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>
        /// 服务器推送主线任务改变
        /// </summary>
        /// <param name="mainTaskTPID"></param>
        /// <param name="state"></param>
        public delegate void CBMsgTaskSystemGM2GCNtfMainTaskState(UInt32 mainTaskTPID, ETaskState state, UInt32 curCount);

        /// <summary>
        /// 注册服务器推送更新主线任务状态的回调函数
        /// </summary>
        /// <param name="cb"></param>
        public void RegisterMsgTaskSystemGM2GCNtfMainTaskCallBack(CBMsgTaskSystemGM2GCNtfMainTaskState cb)
        {
            CMsgTaskSystemGM2GCNtfMainTaskState.s_cb = cb;
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>
        /// 客户端通知任务状态更新函数回调
        /// </summary>
        public delegate void CBMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate(EUpdateMainTaskStateResult result);
        /// <summary>
        /// 客户端通知任务状态更新接口
        /// </summary>
        /// <param name="taksID">任务ID</param>
        /// <param name="curCount">当前完成的数量</param>
        /// <param name="cb">回调函数</param>
        /// <returns></returns>
        public bool SendMsgTaskSystemGC2GMReqNotifyMainTaskStateUpdate(UInt32 taksID, UInt32 curCount, CBMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate cb)
        {
            CMsgTaskSystemGC2GMReqNotifyMainTaskStateUpdate req = new CMsgTaskSystemGC2GMReqNotifyMainTaskStateUpdate(taksID, curCount);
            CMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>
        /// 获取主线任务奖励请求回调
        /// </summary>
        /// <param name="result"></param>
        /// <param name="nextMainTask"></param>
        public delegate void CBMsgTaskSystemGM2GCAckGetMainTaskPrize(EGetDailyTaskPrizeResult result);
        /// <summary>
        /// 获取获取主线任务奖励请求
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgTaskSystemGC2GMReqGetMainTaskPrize(CBMsgTaskSystemGM2GCAckGetMainTaskPrize cb)
        {
            CMsgTaskSystemGC2GMReqGetMainTaskPrize req = new CMsgTaskSystemGC2GMReqGetMainTaskPrize();
            CMsgTaskSystemGM2GCAckGetMainTaskPrize.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 获取伙伴任务信息回调
        /// </summary>
        /// <param name="result"></param>
        /// <param name="petTaskInfo"></param>
        public delegate void CBMsgTaskSystemGM2GCAckGetPetTask(EGetPetTaskResult result, CPetTaskInfo petTaskInfo);
        /// <summary>
        /// 发送获取伙伴任务请求
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgTaskSystemGC2GMReqGetPetTask(CBMsgTaskSystemGM2GCAckGetPetTask cb)
        {
            CMsgTaskSystemGC2GMReqGetPetTask req = new CMsgTaskSystemGC2GMReqGetPetTask();
            CMsgTaskSystemGM2GCAckGetPetTask.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 刷新任务回调
        /// </summary>
        /// <param name="result"></param>
        /// <param name="refreshPetTaskInfo"></param>
        public delegate void CBMsgTaskSystemGM2GCAckRefreshPetTask(ERefreshPetTaskResult result, CRefreshPetTaskInfo refreshPetTaskInfo);
        /// <summary>
        /// 发送刷新伙伴任务请求
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgTaskSystemGC2GMReqRefreshPetTask(CBMsgTaskSystemGM2GCAckRefreshPetTask cb)
        {
            CMsgTaskSystemGC2GMReqRefreshPetTask req = new CMsgTaskSystemGC2GMReqRefreshPetTask();
            CMsgTaskSystemGM2GCAckRefreshPetTask.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 更新伙伴任务回调
        /// </summary>
        /// <param name="result"></param>
        /// <param name="petTaskIndex"></param>
        /// <param name="state"></param>
        public delegate void CBMsgTaskSystemGM2GCAckUpdatePetTaskState(EUpdatePetTaskStateResult result, UInt32 petTaskIndex, ETaskState state, UInt16 curCount);
        /// <summary>
        /// 发送更新伙伴任务状态消息
        /// </summary>
        /// <param name="petTaskIndex"></param>
        /// <param name="state"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgTaskSystemGC2GMReqUpdatePetTaskState(UInt32 petTaskIndex, ETaskState state, UInt16 curCount, CBMsgTaskSystemGM2GCAckUpdatePetTaskState cb)
        {
            CMsgTaskSystemGC2GMReqUpdatePetTaskState req = new CMsgTaskSystemGC2GMReqUpdatePetTaskState(petTaskIndex, state, curCount);
            CMsgTaskSystemGM2GCAckUpdatePetTaskState.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 获取伙伴任务奖励回调
        /// </summary>
        /// <param name="result"></param>
        /// <param name="petTaskIndex"></param>
        public delegate void CBMsgTaskSystemGM2GCAckGetPetTaskPrize(EGetPetTaskPrizeResult result, UInt32 petTaskIndex);
        /// <summary>
        /// 发送获取伙伴任务奖励消息
        /// </summary>
        /// <param name="petTaskIndex"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgTaskSystemGC2GMReqGetPetTaskPrize(UInt32 petTaskIndex, CBMsgTaskSystemGM2GCAckGetPetTaskPrize cb)
        {
            CMsgTaskSystemGC2GMReqGetPetTaskPrize req = new CMsgTaskSystemGC2GMReqGetPetTaskPrize(petTaskIndex);
            CMsgTaskSystemGM2GCAckGetPetTaskPrize.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }














    }
}








