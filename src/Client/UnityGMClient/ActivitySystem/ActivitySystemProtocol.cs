using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    partial class CActivitySystem
    {
        public void Init()
        {
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgActivitySystemGM2GCAckGetAttendenceData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgActivitySystemGM2GCAckGetAttendenceData));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgActivitySystemGM2GCAckSignIn), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgActivitySystemGM2GCAckSignIn));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgActivitySystemGM2GCAckDrawCard), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgActivitySystemGM2GCAckDrawCard));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgActivitySystemGM2GCAckGetDrawCardInfo), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgActivitySystemGM2GCAckGetDrawCardInfo));

        }

        private void OnMsgActivitySystemGM2GCAckGetAttendenceData(UnityFrame.CMsg msgData)
        {
            CMsgActivitySystemGM2GCAckGetAttendenceData ack = (CMsgActivitySystemGM2GCAckGetAttendenceData)msgData;
            CMsgActivitySystemGM2GCAckGetAttendenceData.CallBack(ack);
        }

        private void OnMsgActivitySystemGM2GCAckSignIn(UnityFrame.CMsg msgData)
        {
            CMsgActivitySystemGM2GCAckSignIn ack = (CMsgActivitySystemGM2GCAckSignIn)msgData;
            CMsgActivitySystemGM2GCAckSignIn.CallBack(ack);
        }
 
        private void OnMsgActivitySystemGM2GCAckDrawCard(UnityFrame.CMsg msgData)
        {
            CMsgActivitySystemGM2GCAckDrawCard ack = (CMsgActivitySystemGM2GCAckDrawCard)msgData;
            CMsgActivitySystemGM2GCAckDrawCard.CallBack(ack);
        }

        private void OnMsgActivitySystemGM2GCAckGetDrawCardInfo(UnityFrame.CMsg msgData)
        {
            CMsgActivitySystemGM2GCAckGetDrawCardInfo ack = (CMsgActivitySystemGM2GCAckGetDrawCardInfo)msgData;
            CMsgActivitySystemGM2GCAckGetDrawCardInfo.CallBack(ack);
        }
        

    }
}