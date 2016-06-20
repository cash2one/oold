using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {
        /// <summary>
        /// 获取排行榜信息
        /// </summary>
        /// <param name="result"></param>
        /// <param name="listRankData"></param>
        public delegate void CBMsgRankSystemGC2GMReqGetRankData(EGetRankDataResult result, ERankType type, List<CRankData> listRankData);

        public bool SendMsgRankSystemGC2GMReqGetRankData(ERankType type, CBMsgRankSystemGC2GMReqGetRankData cb)
        {
            CMsgRankSystemGC2GMReqGetRankData msgReq = new CMsgRankSystemGC2GMReqGetRankData(type);
            CMsgRankSystemGM2GCAckGetRankData.s_cb = cb;
            return CGameClient.Singleton.SendMsg(msgReq);
        }
		
		public delegate void CBMsgRankSystemGC2GMReqGetRankList(UInt32 id, bool isMySelf, List<CRankCell> rankList);
        /// <summary>
        /// 获取排行榜或者自己在排行榜的位置
        /// </summary>
        /// <param name="id"></param>
        /// <param name="isMyself"> false: 获取整个排行榜, true: 获取自己的排行榜</param>
        /// <param name="param">当 isMyself 为 true, param 为自己自己现有值(比如战斗力, 积分, 之类的)</param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgRankSystemGC2GMReqGetRankList(UInt32 id, bool isMyself, Int32 param, CBMsgRankSystemGC2GMReqGetRankList cb)
        {
            CMsgRankSystemGC2CNReqGetRankList msgReq = new CMsgRankSystemGC2CNReqGetRankList(id, isMyself, param);
            CMsgRankSystemGM2GCAckGetRankList.s_cb = cb;
            return CGameClient.Singleton.SendMsg(msgReq);
        }

    }
}