using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    partial class CTaskSystem
    {
        public void Init()
        {
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgTaskSystemGM2GCAckGetDailyTaskList), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgTaskSystemGM2GCAckGetDailyTaskList));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgTaskSystemGM2GCAckGetDailyTaskPrize), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgTaskSystemGM2GCAckGetDailyTaskPrize));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgTaskSystemGM2GCAckGetMainTaskList), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgTaskSystemGM2GCAckGetMainTaskList));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgTaskSystemGM2GCAckGetMainTaskPrize), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgTaskSystemGM2GCAckGetMainTaskPrize));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgTaskSystemGM2GCNtfMainTaskState), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgTaskSystemGM2GCNtfMainTaskState));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgTaskSystemGM2GCAckGetPetTask), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgTaskSystemGM2GCAckGetPetTask));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgTaskSystemGM2GCAckRefreshPetTask), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgTaskSystemGM2GCAckRefreshPetTask));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgTaskSystemGM2GCAckUpdatePetTaskState), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgTaskSystemGM2GCAckUpdatePetTaskState));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgTaskSystemGM2GCAckGetPetTaskPrize), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgTaskSystemGM2GCAckGetPetTaskPrize));


        }

        private void OnMsgTaskSystemGM2GCAckGetDailyTaskList(UnityFrame.CMsg msgData)
        {
            CMsgTaskSystemGM2GCAckGetDailyTaskList ack = (CMsgTaskSystemGM2GCAckGetDailyTaskList)msgData;
            CMsgTaskSystemGM2GCAckGetDailyTaskList.CallBack(ack);
        }

        private void OnMsgTaskSystemGM2GCAckGetDailyTaskPrize(UnityFrame.CMsg msgData)
        {
            CMsgTaskSystemGM2GCAckGetDailyTaskPrize ack = (CMsgTaskSystemGM2GCAckGetDailyTaskPrize)msgData;
            CMsgTaskSystemGM2GCAckGetDailyTaskPrize.CallBack(ack);
        }

        private void OnMsgTaskSystemGM2GCAckGetMainTaskList(UnityFrame.CMsg msgData)
        {
            CMsgTaskSystemGM2GCAckGetMainTaskList ack = (CMsgTaskSystemGM2GCAckGetMainTaskList)msgData;
            CMsgTaskSystemGM2GCAckGetMainTaskList.CallBack(ack);
        }

        private void OnMsgTaskSystemGM2GCAckGetMainTaskPrize(UnityFrame.CMsg msgData)
        {
            CMsgTaskSystemGM2GCAckGetMainTaskPrize ack = (CMsgTaskSystemGM2GCAckGetMainTaskPrize)msgData;
            CMsgTaskSystemGM2GCAckGetMainTaskPrize.CallBack(ack);
        }

        private void OnMsgTaskSystemGM2GCNtfMainTaskState(UnityFrame.CMsg msgData)
        {
            CMsgTaskSystemGM2GCNtfMainTaskState ack = (CMsgTaskSystemGM2GCNtfMainTaskState)msgData;
            CMsgTaskSystemGM2GCNtfMainTaskState.CallBack(ack);
        }

        private void OnMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate(UnityFrame.CMsg msgData)
        {
            CMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate ack = (CMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate)msgData;
            CMsgTaskSystemGM2GCAckNotifyMainTaskStateUpdate.CallBack(ack);
        }

        private void OnMsgTaskSystemGM2GCAckGetPetTask(UnityFrame.CMsg msgData)
        {
            CMsgTaskSystemGM2GCAckGetPetTask ack = (CMsgTaskSystemGM2GCAckGetPetTask)msgData;
            CMsgTaskSystemGM2GCAckGetPetTask.CallBack(ack);
        }

        private void OnMsgTaskSystemGM2GCAckRefreshPetTask(UnityFrame.CMsg msgData)
        {
            CMsgTaskSystemGM2GCAckRefreshPetTask ack = (CMsgTaskSystemGM2GCAckRefreshPetTask)msgData;
            CMsgTaskSystemGM2GCAckRefreshPetTask.CallBack(ack);
        } 

        private void OnMsgTaskSystemGM2GCAckUpdatePetTaskState(UnityFrame.CMsg msgData)
        {
            CMsgTaskSystemGM2GCAckUpdatePetTaskState ack = (CMsgTaskSystemGM2GCAckUpdatePetTaskState)msgData;
            CMsgTaskSystemGM2GCAckUpdatePetTaskState.CallBack(ack);
        }

        private void OnMsgTaskSystemGM2GCAckGetPetTaskPrize(UnityFrame.CMsg msgData)
        {
            CMsgTaskSystemGM2GCAckGetPetTaskPrize ack = (CMsgTaskSystemGM2GCAckGetPetTaskPrize)msgData;
            CMsgTaskSystemGM2GCAckGetPetTaskPrize.CallBack(ack);
        }



    }
}