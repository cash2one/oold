using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    partial class CPetSystem
    {
        public void Init()
        {
            //CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCNtfUpgradePet), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCNtfUpdateHotSpring));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCNtfActiveHotSpringTask), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCNtfActiveHotSpringTask));
            //CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCNtfHotSpringEggFull), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCNtfActiveHotSpringTask));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCAckInitPetData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCAckInitPetData));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCAckExpandHotSpring), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCAckExpandHotSpring));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCAckHotSpringTaskEnd), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCAckHotSpringTaskEnd));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCAckPetFinishHotSpringTask), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCAckPetFinishHotSpringTask));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCAckSendPetGift), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCAckSendPetGift));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCAckGetPetUnlockData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCAckGetPetUnlockData));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCAckUnlockPet), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCAckUnlockPet));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCAckGetPetBaseInforList), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCAckGetPetBaseInforList));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCAckPetSitDown), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCAckPetSitDown));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCAckPetStandUp), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCAckPetStandUp));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCAckGetPetData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCAckGetPetData));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCAckPetEnterPool), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCAckPetEnterPool));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCAckPetQuitPool), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCAckPetQuitPool));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPetSystemGM2GCAckPetFastQuitPool), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPetSystemGM2GCAckPetFastQuitPool));
        }

        private void OnMsgPetSystemGM2GCAckExpandHotSpring(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCAckExpandHotSpring ack = (CMsgPetSystemGM2GCAckExpandHotSpring)msgData;
            CMsgPetSystemGM2GCAckExpandHotSpring.CallBack(ack);
        }

        private void OnMsgPetSystemGM2GCAckInitPetData(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCAckInitPetData ack = (CMsgPetSystemGM2GCAckInitPetData)msgData;
            CMsgPetSystemGM2GCAckInitPetData.CallBack(ack);
        }

//         private void OnMsgPetSystemGM2GCNtfUpdateHotSpring(UnityFrame.CMsg msgData)
//         {
//             CMsgPetSystemGM2GCNtfUpgradePet ack = (CMsgPetSystemGM2GCNtfUpgradePet)msgData;
//             CMsgPetSystemGM2GCNtfUpgradePet.CallBack(ack);
//         }

        private void OnMsgPetSystemGM2GCNtfActiveHotSpringTask(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCNtfActiveHotSpringTask ack = (CMsgPetSystemGM2GCNtfActiveHotSpringTask)msgData;
            CMsgPetSystemGM2GCNtfActiveHotSpringTask.CallBack(ack);
        }

        private void OnMsgPetSystemGM2GCAckHotSpringTaskEnd(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCAckHotSpringTaskEnd ack = (CMsgPetSystemGM2GCAckHotSpringTaskEnd)msgData;
            CMsgPetSystemGM2GCAckHotSpringTaskEnd.CallBack(ack);
        }

        private void OnMsgPetSystemGM2GCAckPetFinishHotSpringTask(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCAckPetFinishHotSpringTask ack = (CMsgPetSystemGM2GCAckPetFinishHotSpringTask)msgData;
            CMsgPetSystemGM2GCAckPetFinishHotSpringTask.CallBack(ack);
        }

        private void OnMsgPetSystemGM2GCAckSendPetGift(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCAckSendPetGift ack = (CMsgPetSystemGM2GCAckSendPetGift)msgData;
            CMsgPetSystemGM2GCAckSendPetGift.CallBack(ack);
        }

        private void OnMsgPetSystemGM2GCAckGetPetUnlockData(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCAckGetPetUnlockData ack = (CMsgPetSystemGM2GCAckGetPetUnlockData)msgData;
            CMsgPetSystemGM2GCAckGetPetUnlockData.CallBack(ack);
        }

        private void OnMsgPetSystemGM2GCAckUnlockPet(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCAckUnlockPet ack = (CMsgPetSystemGM2GCAckUnlockPet)msgData;
            CMsgPetSystemGM2GCAckUnlockPet.CallBack(ack);
        }

        private void OnMsgPetSystemGM2GCAckGetPetBaseInforList(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCAckGetPetBaseInforList ack = (CMsgPetSystemGM2GCAckGetPetBaseInforList)msgData;
            CMsgPetSystemGM2GCAckGetPetBaseInforList.CallBack(ack);
        }

        private void OnMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail ack = (CMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail)msgData;
            CMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail.CallBack(ack);
        }

        private void OnMsgPetSystemGM2GCAckPetSitDown(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCAckPetSitDown ack = (CMsgPetSystemGM2GCAckPetSitDown)msgData;
            CMsgPetSystemGM2GCAckPetSitDown.CallBack(ack);
        }
        
        private void OnMsgPetSystemGM2GCAckPetStandUp(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCAckPetStandUp ack = (CMsgPetSystemGM2GCAckPetStandUp)msgData;
            CMsgPetSystemGM2GCAckPetStandUp.CallBack(ack);
        }

        private void OnMsgPetSystemGM2GCAckGetPetData(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCAckGetPetData ack = (CMsgPetSystemGM2GCAckGetPetData)msgData;
            CMsgPetSystemGM2GCAckGetPetData.CallBack(ack);
        }
        private void OnMsgPetSystemGM2GCAckPetEnterPool(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCAckPetEnterPool ack = (CMsgPetSystemGM2GCAckPetEnterPool)msgData;
            CMsgPetSystemGM2GCAckPetEnterPool.CallBack(ack);
        }

        private void OnMsgPetSystemGM2GCAckPetQuitPool(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCAckPetQuitPool ack = (CMsgPetSystemGM2GCAckPetQuitPool)msgData;
            CMsgPetSystemGM2GCAckPetQuitPool.CallBack(ack);
        }

        private void OnMsgPetSystemGM2GCAckPetFastQuitPool(UnityFrame.CMsg msgData)
        {
            CMsgPetSystemGM2GCAckPetFastQuitPool ack = (CMsgPetSystemGM2GCAckPetFastQuitPool)msgData;
            CMsgPetSystemGM2GCAckPetFastQuitPool.CallBack(ack);
        }
    }
}
