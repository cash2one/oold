using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {
        /// <summary>
        /// 请求领取状态
        /// </summary>
        /// <param name="result"></param>
        /// <param name="listRankData"></param>
        public delegate void CBMsgPrizeSystemGM2GCAckState(Dictionary<UInt32, Int32> states);

        public bool SendMsgPrizeSystemGC2GMReqState(CBMsgPrizeSystemGM2GCAckState cb)
        {
            CMsgPrizeSystemGC2GMReqState msgReq = new CMsgPrizeSystemGC2GMReqState();
            CMsgPrizeSystemGM2GCAckState.s_cb = cb;
            return CGameClient.Singleton.SendMsg(msgReq);
        }

        public delegate void CBMsgPrizeSystemGM2GCAck(UInt32 vip, UInt32 result);
   
        public bool SendMsgPrizeSystemGC2GMReq(UInt32 vip, CBMsgPrizeSystemGM2GCAck cb)
        {
            CMsgPrizeSystemGC2GMReq msgReq = new CMsgPrizeSystemGC2GMReq();
            msgReq.vip = vip;
            CMsgPrizeSystemGM2GCAck.s_cb = cb;
            return CGameClient.Singleton.SendMsg(msgReq);
        }

        // 5倍事件通知
        public delegate void CBMsgPrizeSystemGM2GCNtfCharge(UInt32 id, Int64 time);
        public void RegMsgPrizeSystemGM2GCNtfCharge(CBMsgPrizeSystemGM2GCNtfCharge cb)
        {
            CMsgPrizeSystemGM2GCNtfCharge.s_cb = cb;
        }

        public delegate void CBMsgPrizeSystemGM2GCAckTime(Int64 time);
        public bool SendMsgPrizeSystemGC2GMReqTime(CBMsgPrizeSystemGM2GCAckTime cb)
        {
            CMsgPrizeSystemGC2GMReqTime msgReq = new CMsgPrizeSystemGC2GMReqTime();
            CMsgPrizeSystemGM2GCAckTime.s_cb = cb;
            return CGameClient.Singleton.SendMsg(msgReq);
        }


        public delegate void CBMsgPrizeSystemGM2GCAckChargeInfo(List<PrizeSystemChargeInfo> info);
        // 请求活动信息
        public bool SendMsgPrizeSystemGC2GMReqChargeInfo(UInt32 id, CBMsgPrizeSystemGM2GCAckChargeInfo cb)
        {
            CMsgPrizeSystemGC2GMReqChargeInfo msgReq = new CMsgPrizeSystemGC2GMReqChargeInfo();
            msgReq.id = id;
            CMsgPrizeSystemGM2GCAckChargeInfo.s_cb = cb;
            return CGameClient.Singleton.SendMsg(msgReq);
        }

        // 反馈5倍事件通知
        public bool SendMsgPrizeSystemGC2GMNtfAction()
        {
            CMsgPrizeSystemGC2GMNtfAction msgReq = new CMsgPrizeSystemGC2GMNtfAction();
            return CGameClient.Singleton.SendMsg(msgReq);
        }
    }
}