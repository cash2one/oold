using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    partial class CAchieveSystem
    {
        public void Init()
        {
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgAchieveSystemGM2GCNtfRoleAchieveFinished), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgAchieveSystemGM2GCNtfRoleAchieveFinished));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgAchieveSystemGM2GCAckGetAchievePrize), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgAchieveSystemGM2GCAckGetAchievePrize));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgAchieveSystemGM2GCAckGetAchieveList), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgAchieveSystemGM2GCAckGetAchieveList));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgAchieveSystemGM2GCAckSaveAchieveData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgAchieveSystemGM2GCAckSaveAchieveData));
        }

        private void OnMsgAchieveSystemGM2GCNtfRoleAchieveFinished(UnityFrame.CMsg msgData)
        {
            CMsgAchieveSystemGM2GCNtfRoleAchieveFinished ack = (CMsgAchieveSystemGM2GCNtfRoleAchieveFinished)msgData;
            CMsgAchieveSystemGM2GCNtfRoleAchieveFinished.CallBack(ack);
        }

        private void OnMsgAchieveSystemGM2GCAckGetAchievePrize(UnityFrame.CMsg msgData)
        {
            CMsgAchieveSystemGM2GCAckGetAchievePrize ack = (CMsgAchieveSystemGM2GCAckGetAchievePrize)msgData;
            CMsgAchieveSystemGM2GCAckGetAchievePrize.CallBack(ack);
        }

        private void OnMsgAchieveSystemGM2GCAckGetAchieveList(UnityFrame.CMsg msgData)
        {
            CMsgAchieveSystemGM2GCAckGetAchieveList ack = (CMsgAchieveSystemGM2GCAckGetAchieveList)msgData;
            CMsgAchieveSystemGM2GCAckGetAchieveList.CallBack(ack);
        }

        private void OnMsgAchieveSystemGM2GCAckSaveAchieveData(UnityFrame.CMsg msgData)
        {
            CMsgAchieveSystemGM2GCAckSaveAchieveData ack = (CMsgAchieveSystemGM2GCAckSaveAchieveData)msgData;
            CMsgAchieveSystemGM2GCAckSaveAchieveData.CallBack(ack);
        }
    }
}
