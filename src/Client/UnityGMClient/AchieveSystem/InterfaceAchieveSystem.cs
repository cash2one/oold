using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public enum EGetAchieveListResult
    {
        EGETACHIEVELIST_RESUlT_SUCCESS = 0,
        EGETACHIEVELIST_RESUlT_FAIL = 1,
    }

    public enum EGetAchievePrizeResult
    {
        EGETACHIEVEPRIZE_RESUlT_SUCCESS = 0,
        EGETACHIEVEPRIZE_RESUlT_FAIL = 1,
    }

    public enum ESaveAchieveDataResult
    {
        ESAVEACHIEVEDATA_RESUlT_SUCCESS = 0,
        ESAVEACHIEVEDATA_RESUlT_FAIL = 1,
    }

    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {
        /// <summary>
        /// 获取成就列表 
        /// </summary>
        public delegate void CBMsgAchieveSystemGM2GCAckGetAchieveList(EGetAchieveListResult a_retCode,CAchieveData a_achieveData);
        public bool SendMsgAchieveSystemGC2GMReqGetAchieveList(EAchieveType a_achieveType, CBMsgAchieveSystemGM2GCAckGetAchieveList cb)
        {
            CMsgAchieveSystemGC2GMReqGetAchieveList req = new CMsgAchieveSystemGC2GMReqGetAchieveList(a_achieveType);
            CMsgAchieveSystemGM2GCAckGetAchieveList.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 成就完成通知 
        /// </summary>
        /// <param name="retCode"></param>
        /// <param name="equipItem"></param>
        public delegate void CBMsgAchieveSystemGM2GCNtfRoleAchieveFinished(UInt32 a_achieveID);
        public void RegisterRoleAchieveFinishedCallBack(CBMsgAchieveSystemGM2GCNtfRoleAchieveFinished callBackFunction)
        {
            CMsgAchieveSystemGM2GCNtfRoleAchieveFinished.cb = callBackFunction;
        }

        /// <summary>
        /// 领取奖励 
        /// </summary>
        public delegate void CBMsgAchieveSystemGM2GCAckGetAchievePrize(EGetAchievePrizeResult retCode, UInt32 a_achieveID);
        public bool SendMsgAchieveSystemGC2GMReqGetAchievePrize(UInt32 achieveID, CBMsgAchieveSystemGM2GCAckGetAchievePrize cb)
        {
            CMsgAchieveSystemGC2GMReqGetAchievePrize req = new CMsgAchieveSystemGC2GMReqGetAchievePrize(achieveID);
            CMsgAchieveSystemGM2GCAckGetAchievePrize.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        public delegate void CBMsgAchieveSystemGM2GCAckSaveAchieveData(ESaveAchieveDataResult retCode);
        public bool SendMsgAchieveSystemGC2GMReqSaveAchieveData(UInt32 a_achieveSubType, UInt32 a_achieveData, CBMsgAchieveSystemGM2GCAckSaveAchieveData cb)
        {
            CMsgAchieveSystemGC2GMReqSaveAchieveData req = new CMsgAchieveSystemGC2GMReqSaveAchieveData(a_achieveSubType, a_achieveData);
            CMsgAchieveSystemGM2GCAckSaveAchieveData.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

    }
}
