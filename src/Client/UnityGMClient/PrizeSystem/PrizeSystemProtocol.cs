using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    partial class CPrizeSystem
    {
        public void Init()
        {
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPrizeSystemGM2GCAckState), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPrizeSystemGM2GCAckState));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPrizeSystemGM2GCAck), 
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPrizeSystemGM2GCAck));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPrizeSystemGM2GCNtfCharge),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPrizeSystemGM2GCNtfCharge));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPrizeSystemGM2GCAckTime),
               new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPrizeSystemGM2GCAckTime));


            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPrizeSystemGM2GCAckChargeInfo),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPrizeSystemGM2GCAckChargeInfo));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgShopSystemGM2GCAckOpenCard),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgShopSystemGM2GCAckOpenCard));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgShopSystemGM2GCAckEventState),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgShopSystemGM2GCAckEventState));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgShopSystemGM2GCAckClick),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgShopSystemGM2GCAckClick));

        }

        public void OnMsgShopSystemGM2GCAckClick(UnityFrame.CMsg msgData)
        {
            CMsgShopSystemGM2GCAckClick ack = (CMsgShopSystemGM2GCAckClick)msgData;
            CMsgShopSystemGM2GCAckClick.CallBack(ack);
        }


        public void OnMsgShopSystemGM2GCAckEventState(UnityFrame.CMsg msgData)
        {
            CMsgShopSystemGM2GCAckEventState ack = (CMsgShopSystemGM2GCAckEventState)msgData;
            CMsgShopSystemGM2GCAckEventState.CallBack(ack);
        }


        public void OnMsgShopSystemGM2GCAckOpenCard(UnityFrame.CMsg msgData)
        {
            CMsgShopSystemGM2GCAckOpenCard ack = (CMsgShopSystemGM2GCAckOpenCard)msgData;
            CMsgShopSystemGM2GCAckOpenCard.CallBack(ack);
        }


        public void OnMsgPrizeSystemGM2GCAckChargeInfo(UnityFrame.CMsg msgData)
        {
            CMsgPrizeSystemGM2GCAckChargeInfo ack = (CMsgPrizeSystemGM2GCAckChargeInfo)msgData;
            CMsgPrizeSystemGM2GCAckChargeInfo.CallBack(ack);
        }

        public void OnMsgPrizeSystemGM2GCAckState(UnityFrame.CMsg msgData)
        {
            CMsgPrizeSystemGM2GCAckState ack = (CMsgPrizeSystemGM2GCAckState)msgData;
            CMsgPrizeSystemGM2GCAckState.CallBack(ack);
        }

        public void OnMsgPrizeSystemGM2GCAck(UnityFrame.CMsg msgData)
        {
            CMsgPrizeSystemGM2GCAck ack = (CMsgPrizeSystemGM2GCAck)msgData;
            CMsgPrizeSystemGM2GCAck.CallBack(ack);
        }

        public void OnMsgPrizeSystemGM2GCNtfCharge(UnityFrame.CMsg msgData)
        {
            CMsgPrizeSystemGM2GCNtfCharge ack = (CMsgPrizeSystemGM2GCNtfCharge)msgData;
            CMsgPrizeSystemGM2GCNtfCharge.CallBack(ack);
        }

        public void OnMsgPrizeSystemGM2GCAckTime(UnityFrame.CMsg msgData)
        {
            CMsgPrizeSystemGM2GCAckTime ack = (CMsgPrizeSystemGM2GCAckTime)msgData;
            CMsgPrizeSystemGM2GCAckTime.CallBack(ack);
        }

    }
}