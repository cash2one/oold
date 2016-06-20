using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    partial class CRankSystem
    {
        public void Init()
        {
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgRankSystemGM2GCAckGetRankData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgRankSystemGM2GCAckGetRankData));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgRankSystemGM2GCAckGetRankList), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgRankSystemGM2GCAckGetRankList));
        }

        public void OnMsgRankSystemGM2GCAckGetRankData(UnityFrame.CMsg msgData)
        {
            CMsgRankSystemGM2GCAckGetRankData ack = (CMsgRankSystemGM2GCAckGetRankData)msgData;
            CMsgRankSystemGM2GCAckGetRankData.CallBack(ack);
        }
		
		public void OnMsgRankSystemGM2GCAckGetRankList(UnityFrame.CMsg msgData)
        {
            CMsgRankSystemGM2GCAckGetRankList ack = (CMsgRankSystemGM2GCAckGetRankList)msgData;
            CMsgRankSystemGM2GCAckGetRankList.CallBack(ack);
        }



    }
}