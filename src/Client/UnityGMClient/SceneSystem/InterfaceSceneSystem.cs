using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {

        /// <summary>
        /// 服务端推送新增挑战纪录回调
        /// </summary>
        /// <param name="record"></param>
        public delegate void CBMsgSceneSystemGM2GCAckAddNewArenaChallengeRecord(CArenaChallengeRecord record);

        public void RegisterInitAddNewArenaChallengeRecordCallBack(CBMsgSceneSystemGM2GCAckAddNewArenaChallengeRecord cb)
        {
            CMsgSceneSystemGM2GCAckAddNewArenaChallengeRecord.s_cb = cb;
        }

        /// <summary>
        /// 进入场景回调
        /// </summary>
        /// <param name="retCode"></param>
        /// <param name="currentSceneID"></param>
        /// <param name="prizeCount"></param>
        /// <param name="prizeList"></param>
        public delegate void CBMsgSceneSystemGM2GCAckEnterScene(EEnterSceneResult retCode, UInt32 currentSceneID, List<CSceneRoleInfo> listSceneRoleInfo);

        /// <summary>
        /// 进入场景
        /// </summary>
        /// <param name="SceneTypeID"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqEnterScene(UInt32 SceneTypeID, CBMsgSceneSystemGM2GCAckEnterScene cb)
        {
            CMsgSceneSystemGC2GMReqEnterScene req = new CMsgSceneSystemGC2GMReqEnterScene(SceneTypeID);
            CMsgSceneSystemGM2GCAckEnterScene.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 退出场景回调
        /// </summary>
        /// <param name="retCode"></param>
        /// <param name="currentSceneID"></param>
        public delegate void CBMsgSceneSystemGM2GCAckQuitScene(EQuitSceneResult retCode, UInt32 currentSceneID);

        /// <summary>
        /// 退出场景
        /// </summary>
        /// <param name="SceneTypeID"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqQuitScene(UInt32 SceneTypeID, CBMsgSceneSystemGM2GCAckQuitScene cb)
        {
            CMsgSceneSystemGC2GMReqQuitScene req = new CMsgSceneSystemGC2GMReqQuitScene(SceneTypeID);
            CMsgSceneSystemGM2GCAckQuitScene.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>
        /// 副本内人物复活回调
        /// </summary>
        /// <param name="error"></param>
        public delegate void CBMsgSceneSystemGM2GCAckRoleRevive(UnityGMClient.ESceneRoleReviveResult result);

        /// <summary>
        /// 副本内角色复活
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqRoleRevive(CBMsgSceneSystemGM2GCAckRoleRevive cb)
        {
            CMsgSceneSystemGC2GMReqRoleRevive req = new CMsgSceneSystemGC2GMReqRoleRevive();
            CMsgSceneSystemGM2GCAckRoleRevive.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 获取角色竞技场数据回调
        /// </summary>
        /// <param name="roleArenaData"></param>
        public delegate void CBMsgSceneSystemGM2GCAckGetRoleArenaData(CRoleArenaData roleArenaData);

        /// <summary>
        /// 发送获取竞技场数据接口
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqGetArenaData(CBMsgSceneSystemGM2GCAckGetRoleArenaData cb)
        {
            CMsgSceneSystemGC2GMReqGetRoleArenaData req = new CMsgSceneSystemGC2GMReqGetRoleArenaData();
            CMsgSceneSystemGM2GCAckGetRoleArenaData.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 更新一批新的被挑战者回调
        /// </summary>
        /// <param name="listChallengees">新一批挑战者的信息列表</param>
        public delegate void CBMsgSceneSystemGM2GCAckGetNewArenaChallengees(List<CArenaChallengeeData> listChallengees);

        /// <summary>
        /// 获取新一批竞技场被挑战者
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGM2GCAckGetNewArenaChallengees(CBMsgSceneSystemGM2GCAckGetNewArenaChallengees cb)
        {
            CMsgSceneSystemGC2GMReqGetNewArenaChallengees msgReq = new CMsgSceneSystemGC2GMReqGetNewArenaChallengees();
            CMsgSceneSystemGM2GCAckGetNewArenaChallengees.s_cb = cb;
            return CGameClient.Singleton.SendMsg(msgReq);
        }

        /// <summary>
        /// 挑战竞技场角色回调
        /// </summary>
        /// <param name="result">成功或失败</param>
        /// <param name="roleData">返回的被挑战者的数据</param>
        public delegate void CBMsgSceneSystemGC2GMReqChallengeArenaRole(EEnterSceneResult result, CBattleRoleData roleData);

        /// <summary>
        /// 挑战竞技场
        /// </summary>
        /// <param name="CChallengeInfo">挑战信息</param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqChallengeArenaRole(CChallengeInfo challengeID, CBMsgSceneSystemGC2GMReqChallengeArenaRole cb)
        {
            CMsgSceneSystemGC2GMReqChallengeArenaRole msgReq = new CMsgSceneSystemGC2GMReqChallengeArenaRole(challengeID);
            CMsgSceneSystemGM2GCAckChallengeArenaRole.s_cb = cb;
            return CGameClient.Singleton.SendMsg(msgReq);
        }

        /// <summary>
        /// 挑战结束返回结果
        /// </summary>
        /// <param name="result"></param>
        /// <param name="newRank">该挑战之后的排名</param>
        /// <param name="record">新增的战斗记录</param>
        public delegate void CBChallengeArenaRoleFinish(EChallengeArenaRoleFinishResult result);

        /// <summary>
        /// 发送竞技场结果
        /// </summary>
        /// <param name="result"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgCMsgSceneSystemGM2GCAckChallengeArenaRoleFinish(bool result, CBChallengeArenaRoleFinish cb)
        {
            CMsgSceneSystemGC2GMReqChallengeArenaRoleFinish msgReq = new CMsgSceneSystemGC2GMReqChallengeArenaRoleFinish(result);
            CMsgSceneSystemGM2GCAckChallengeArenaRoleFinish.s_cb = cb;
           return CGameClient.Singleton.SendMsg(msgReq);
        }

        /// <summary>
        /// 获取剧情副本进度回调
        /// </summary>
        /// <param name="instanceID"></param>
        /// <param name="stageID"></param>
        public delegate void CBMsgSceneSystemGM2GCAckGetStroyInstanceProgress(UInt32 instanceID, UInt16 index);

        /// <summary>
        /// 发送获取副本进度消息
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqGetStroyInstanceProgress(CBMsgSceneSystemGM2GCAckGetStroyInstanceProgress cb)
        {
            CMsgSceneSystemGC2GMReqGetStroyInstanceProgress req = new CMsgSceneSystemGC2GMReqGetStroyInstanceProgress();
            CMsgSceneSystemGM2GCAckGetStroyInstanceProgress.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 获取剧本剧情关卡信息回调
        /// </summary>
        public delegate void CBMsgSceneSystemGM2GCAckGetInstanceData(EGetInstanceDataResult result, UInt32 instanceID, List<CStageData> listInstanceData);
        /// <summary>
        /// 发送获取剧情副本关卡信息
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqGetInstanceData(UInt32 instanceID, CBMsgSceneSystemGM2GCAckGetInstanceData cb)
        {
            CMsgSceneSystemGC2GMReqGetInstanceData req = new CMsgSceneSystemGC2GMReqGetInstanceData(instanceID);
            CMsgSceneSystemGM2GCAckGetInstanceData.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 进入关卡回调 
        /// </summary>
        /// <param name="result"></param>
        public delegate void CBMsgSceneSystemGM2GCAckEnterStage(EEnterSceneResult result, CBattleRoleData helperData, CStageMonster stageMonster);
        /// <summary>
        /// 发送进入关卡的消息
        /// </summary>
        /// <param name="instanceID">副本ID</param>
        /// <param name="index">副本内关卡序号</param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqEnterStage(UInt32 instanceID, UInt16 index , SRoleKey helperKey, CBMsgSceneSystemGM2GCAckEnterStage cb)
        {
            CMsgSceneSystemGC2GMReqEnterStage req = new CMsgSceneSystemGC2GMReqEnterStage(instanceID, index, helperKey);
            CMsgSceneSystemGM2GCAckEnterStage.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 发送关卡结果消息回调
        /// </summary>
        /// <param name="listPrizeItem"></param>
        public delegate void CBMsgSceneSystemGM2GCAckStageResultReport(ESendStageResultReportResult result);
        /// <summary>
        /// 发送关卡结果
        /// </summary>
        /// <param name="isWin"></param>
        /// <param name="star"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqStageResultReport(bool isWin, UInt32 star, Int32 useTime, List<UInt32> clearedMonsters, CBMsgSceneSystemGM2GCAckStageResultReport cb)
        {
            CMsgSceneSystemGC2GMReqStageResultReport req = new CMsgSceneSystemGC2GMReqStageResultReport(isWin,(byte)star, useTime, clearedMonsters);
            CMsgSceneSystemGM2GCAckStageResultReport.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 扫荡功能回调
        /// </summary>
        /// <param name="result"></param>
        /// <param name="exp"></param>
        /// <param name="gold"></param>
        /// <param name="listPrizeItem"></param>
        public delegate void CBMsgSceneSystemGM2GCAckClearStage(EClearStageResult result, CStagePrize stagePrize);
        /// <summary>
        /// 发送扫荡请求消息
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqClearStage(UInt32 instanceID, UInt16 stageIndex, bool breakDownItem, CBMsgSceneSystemGM2GCAckClearStage cb)
        {
            CMsgSceneSystemGC2GMReqClearStage req = new CMsgSceneSystemGC2GMReqClearStage(instanceID, stageIndex, breakDownItem);
            CMsgSceneSystemGM2GCAckClearStage.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 获取副本奖励回调
        /// </summary>
        /// <param name="result"></param>
        /// <param name="listPrizeItem"></param>
        public delegate void CBMsgSceneSystemGM2GCAckGetInstanceStarPrize(EGetInstanceStarPrizeResult result, List<CPrizeItem> listPrizeItem);
        /// <summary>
        /// 发送获取副本奖励
        /// </summary>
        /// <param name="instanceTPID"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqGetInstanceStarPrize(UInt32 instanceTPID, CBMsgSceneSystemGM2GCAckGetInstanceStarPrize cb)
        {
            CMsgSceneSystemGC2GMReqGetInstanceStarPrize req = new CMsgSceneSystemGC2GMReqGetInstanceStarPrize(instanceTPID);
            CMsgSceneSystemGM2GCAckGetInstanceStarPrize.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 获取副本星级奖励进度回调
        /// </summary>
        /// <param name="instanceTPID"></param>
        /// <param name="star"></param>
        public delegate void CBMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress(UInt32 instanceTPID, UInt16 star);

        /// <summary>
        /// 申请获取副本星级奖励进度
        /// </summary>
        /// <param name="instanceTPID"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqGetIntanceStarPrizeProgress(UInt32 instanceTPID, CBMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress cb)
        {
            CMsgSceneSystemGC2GMReqGetIntanceStarPrizeProgress req = new CMsgSceneSystemGC2GMReqGetIntanceStarPrizeProgress(instanceTPID);
            CMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 获取连续闯关副本信息
        /// </summary>
        /// <param name="result"></param>
        /// <param name="instanceTPID"></param>
        /// <param name="stageIndex"></param>
        public delegate void CBMsgSceneSystemGM2GCAckGetContinuousInstanceData(EGetContinuousInstanceDataResult result, UInt32 dailyFreeRollFastClearStageCount, UInt32 instanceTPID, UInt32 stageIndex);
        /// <summary>
        /// 发送获取连续闯关副本信息
        /// </summary>
        /// <param name="instanceTPID"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqGetContinuousInstanceData(UInt32 instanceTPID, CBMsgSceneSystemGM2GCAckGetContinuousInstanceData cb)
        {
            CMsgSceneSystemGC2GMReqGetContinuousInstanceData req = new CMsgSceneSystemGC2GMReqGetContinuousInstanceData(instanceTPID);
            CMsgSceneSystemGM2GCAckGetContinuousInstanceData.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }
       
        /// <summary>
        /// 进入连续闯关关卡回调
        /// </summary>
        /// <param name="result"></param>
        public delegate void CBMsgSceneSystemGM2GCAckEnterContinuousStage(EEnterSceneResult result);
        /// <summary>
        /// 申请进入连续闯关关卡
        /// </summary>
        /// <param name="instanceTPID"></param>
        /// <param name="stageIndex"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqEnterContinuousStage(UInt32 instanceTPID, UInt32 stageIndex, CBMsgSceneSystemGM2GCAckEnterContinuousStage cb)
        {
            CMsgSceneSystemGC2GMReqEnterContinuousStage req = new CMsgSceneSystemGC2GMReqEnterContinuousStage(instanceTPID, stageIndex);
            CMsgSceneSystemGM2GCAckEnterContinuousStage.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 汇报连续闯关战绩回调
        /// </summary>
        /// <param name="result"></param>
        /// <param name="m_stagePrize"></param>
        public delegate void CBMsgSceneSystemGM2GCAckReportContinuousStageResult(EReportContinuousStageResultResult result, UInt32 lastScore, CStagePrize m_stagePrize);
        /// <summary>
        /// 汇报连续闯关战绩
        /// </summary>
        /// <param name="isWin"></param>
        /// <param name="score"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqReportContinuousStageResult(bool isWin, UInt32 score, CBMsgSceneSystemGM2GCAckReportContinuousStageResult cb)
        {
            CMsgSceneSystemGC2GMReqReportContinuousStageResult req = new CMsgSceneSystemGC2GMReqReportContinuousStageResult(isWin, score);
            CMsgSceneSystemGM2GCAckReportContinuousStageResult.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 掷筛子回调
        /// </summary>
        /// <param name="result"></param>
        /// <param name="rollNum"></param>
        /// <param name="curStageIndex"></param>
        /// <param name="listStagePrize"></param>
        public delegate void CBMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum(ERollFastClearContinuousStageNum result, UInt32 dailyFreeRollFastClearStageCount, UInt32 rollNum, UInt32 finalStageIndex, List<CStagePrize> listStagePrize);
        /// <summary>
        /// 发送掷筛子申请
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqRollFastClearContinuousStageCount(UInt32 instanceTPID, CBMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum cb)
        {
            CMsgSceneSystemGC2GMReqRollFastClearContinuousStageNum req = new CMsgSceneSystemGC2GMReqRollFastClearContinuousStageNum(instanceTPID);
            CMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="result"></param>
        /// <param name="instanceTPID"></param>
        public delegate void CBMsgSceneSystemGM2GCAckResetContinuousInstance(EResetContinuousInstanceResult result, UInt32 instanceTPID);
        public bool SendMsgSceneSystemGC2GMReqResetContinuousInstance(UInt32 instanceTPID, CBMsgSceneSystemGM2GCAckResetContinuousInstance cb)
        {
            CMsgSceneSystemGC2GMReqResetContinuousInstance req = new CMsgSceneSystemGC2GMReqResetContinuousInstance(instanceTPID);
            CMsgSceneSystemGM2GCAckResetContinuousInstance.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }


        /// <summary>
        /// 关卡鉴定
        /// </summary>
        /// <param name="result"></param>
        public delegate void CBMsgSceneSystemGM2GCAckDetermineStagePrizeItem(EDetermineStagePrizeItemResult result);
        /// <summary>
        /// 发送随机关卡鉴定消息
        /// </summary>
        /// <param name="receiveItems"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqDeterminePrizeItem(List<UInt32> receiveItems, CBMsgSceneSystemGM2GCAckDetermineStagePrizeItem cb)
        {
            CMsgSceneSystemGC2GMReqDeterminePrizeItem req = new CMsgSceneSystemGC2GMReqDeterminePrizeItem(receiveItems);
            CMsgSceneSystemGM2GCAckDetermineStagePrizeItem.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 进入随机关卡回调
        /// </summary>
        /// <param name="result"></param>
        /// <param name="stageMonster"></param>
        public delegate void CBMsgSceneSystemGM2GCAckEnterRandomStage(EEnterSceneResult result, CStageMonster stageMonster);
        /// <summary>
        /// 发送进入随机关卡消息
        /// </summary>
        /// <param name="stageID"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqEnterRandomStage(UInt32 stageID, CBMsgSceneSystemGM2GCAckEnterRandomStage cb)
        {
            CMsgSceneSystemGC2GMReqEnterRandomStage req = new CMsgSceneSystemGC2GMReqEnterRandomStage(stageID);
            CMsgSceneSystemGM2GCAckEnterRandomStage.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 汇报随机关卡战绩回调
        /// </summary>
        /// <param name="result"></param>
        public delegate void CBMsgSceneSystemGM2GCAckReportRandomStageResult(ESendRandomStageReportResult result);
        /// <summary>
        /// 发送汇报随机关卡战绩消息
        /// </summary>
        /// <param name="isWin"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqReportRandomStageResult(bool isWin, CBMsgSceneSystemGM2GCAckReportRandomStageResult cb)
        {
            CMsgSceneSystemGC2GMReqReportRandomStageResult req = new CMsgSceneSystemGC2GMReqReportRandomStageResult(isWin);
            CMsgSceneSystemGM2GCAckReportRandomStageResult.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 获取贪婪之地信息回调函数
        /// </summary>
        /// <param name="result"></param>
        /// <param name="greedLandInfo"></param>
        public delegate void CBMsgSceneSystemGM2GCAckGetGreedLandInfo(EGetGreedLandInfoResult result, CGreedLandInfo greedLandInfo);
        /// <summary>
        /// 发送获取贪婪之地信息请求
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSceneSystemGC2GMReqGetGreedLandInfo(CBMsgSceneSystemGM2GCAckGetGreedLandInfo cb)
        {
            CMsgSceneSystemGC2GMReqGetGreedLandInfo req = new CMsgSceneSystemGC2GMReqGetGreedLandInfo();
            CMsgSceneSystemGM2GCAckGetGreedLandInfo.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 购买竞技场门票回调
        /// </summary>
        /// <param name="result"></param>
        /// <param name="curTicketCount">购买后的门票数</param>
        /// <param name="nextTicketPrice">下次购买门票所需钻石</param>
        public delegate void CBMsgSceneSystemGM2GCAckPurchaseArenaTickts(EPurchaseArenaTicketsResult result, UInt32 curTicketCount, UInt32 nextTicketPrice);
        public bool SendMsgSceneSystemGC2GMReqPurchaseArenaTickts(CBMsgSceneSystemGM2GCAckPurchaseArenaTickts cb)
        {
            CMsgSceneSystemGC2GMReqPurchaseArenaTickts req = new CMsgSceneSystemGC2GMReqPurchaseArenaTickts();
            CMsgSceneSystemGM2GCAckPurchaseArenaTickts.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        public delegate void CBMsgSceneSystemGM2GCAckRestoreStageTickets(ERestoreStageTicketsResult result, UInt32 instanceTPID, UInt32 stageIndex, UInt32 ticketCount, UInt32 nextRestoreRequireDiamond);
        public bool SendMsgSceneSystemGC2GMReqRestoreStageTickets(UInt32 instanceTPID, UInt32 stageIndex, CBMsgSceneSystemGM2GCAckRestoreStageTickets cb)
        {
            CMsgSceneSystemGC2GMReqRestoreStageTickets req = new CMsgSceneSystemGC2GMReqRestoreStageTickets(instanceTPID, stageIndex);
            CMsgSceneSystemGM2GCAckRestoreStageTickets.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }
       


    }
}








