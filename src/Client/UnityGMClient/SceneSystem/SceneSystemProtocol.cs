using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    partial class CSceneSystem
    {
        public void Init()
        {
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckRoleRevive), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckRoleRevive));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckEnterScene), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckEnterScene));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckQuitScene), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckQuitScene));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckGetRoleArenaData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckGetRoleArenaData));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckGetNewArenaChallengees), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckGetNewArenaChallengees));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckChallengeArenaRole), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnCMsgSceneSystemGM2GCAckChallengeArenaRole));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckChallengeArenaRoleFinish), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnCMsgSceneSystemGM2GCAckChallengeArenaRoleFinish));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckAddNewArenaChallengeRecord), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnCMsgSceneSystemGM2GCAckAddNewArenaChallengeRecord));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckGetStroyInstanceProgress), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckGetStroyInstanceProgress));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckGetInstanceData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckGetStroyInstanceData));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckEnterStage), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckEnterStage));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckStageResultReport), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckStageResultReport));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckClearStage), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckClearStage));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckGetInstanceStarPrize), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckGetInstanceStarPrize));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckEnterContinuousStage), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckEnterContinuousStage));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckReportContinuousStageResult), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckReportContinuousStageResult));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckRollFastClearContinuousStageCount));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckGetContinuousInstanceData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckGetContinuousInstanceData));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckResetContinuousInstance), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckResetContinuousInstance));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckDetermineStagePrizeItem), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckDeterminePrizeItem));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckEnterRandomStage), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckEnterRandomStage));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckReportRandomStageResult), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckReportRandomStageResult));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckGetGreedLandInfo), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckGetGreedLandInfo));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckPurchaseArenaTickts), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckPurchaseArenaTickts));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSceneSystemGM2GCAckRestoreStageTickets), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSceneSystemGM2GCAckRestoreStageTickets));



        }

        private void OnMsgSceneSystemGM2GCAckRoleRevive(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckRoleRevive ack = (CMsgSceneSystemGM2GCAckRoleRevive)msgData;
            CMsgSceneSystemGM2GCAckRoleRevive.CallBack(ack);
        }

         void OnMsgSceneSystemGM2GCAckEnterScene(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckEnterScene ack = (CMsgSceneSystemGM2GCAckEnterScene)msgData;
            CMsgSceneSystemGM2GCAckEnterScene.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckQuitScene(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckQuitScene ack = (CMsgSceneSystemGM2GCAckQuitScene)msgData;
            CMsgSceneSystemGM2GCAckQuitScene.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckGetRoleArenaData(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckGetRoleArenaData ack = (CMsgSceneSystemGM2GCAckGetRoleArenaData)msgData;
            CMsgSceneSystemGM2GCAckGetRoleArenaData.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckGetNewArenaChallengees(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckGetNewArenaChallengees ack = (CMsgSceneSystemGM2GCAckGetNewArenaChallengees)msgData;
            CMsgSceneSystemGM2GCAckGetNewArenaChallengees.CallBack(ack);
        }

        private void OnCMsgSceneSystemGM2GCAckChallengeArenaRole(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckChallengeArenaRole ack = (CMsgSceneSystemGM2GCAckChallengeArenaRole)msgData;
            CMsgSceneSystemGM2GCAckChallengeArenaRole.CallBack(ack);
        }

        private void OnCMsgSceneSystemGM2GCAckChallengeArenaRoleFinish(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckChallengeArenaRoleFinish ack = (CMsgSceneSystemGM2GCAckChallengeArenaRoleFinish)msgData;
            CMsgSceneSystemGM2GCAckChallengeArenaRoleFinish.CallBack(ack);
        }

        private void OnCMsgSceneSystemGM2GCAckAddNewArenaChallengeRecord(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckAddNewArenaChallengeRecord ack = (CMsgSceneSystemGM2GCAckAddNewArenaChallengeRecord)msgData;
            CMsgSceneSystemGM2GCAckAddNewArenaChallengeRecord.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckGetStroyInstanceProgress(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckGetStroyInstanceProgress ack = (CMsgSceneSystemGM2GCAckGetStroyInstanceProgress)msgData;
            CMsgSceneSystemGM2GCAckGetStroyInstanceProgress.CallBack(ack);
        }
        
        private void OnMsgSceneSystemGM2GCAckGetStroyInstanceData(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckGetInstanceData ack = (CMsgSceneSystemGM2GCAckGetInstanceData)msgData;
            CMsgSceneSystemGM2GCAckGetInstanceData.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckEnterStage(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckEnterStage ack = (CMsgSceneSystemGM2GCAckEnterStage)msgData;
            CMsgSceneSystemGM2GCAckEnterStage.CallBack(ack);
        }

        
        private void OnMsgSceneSystemGM2GCAckStageResultReport(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckStageResultReport ack = (CMsgSceneSystemGM2GCAckStageResultReport)msgData;
            CMsgSceneSystemGM2GCAckStageResultReport.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckClearStage(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckClearStage ack = (CMsgSceneSystemGM2GCAckClearStage)msgData;
            CMsgSceneSystemGM2GCAckClearStage.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckGetInstanceStarPrize(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckGetInstanceStarPrize ack = (CMsgSceneSystemGM2GCAckGetInstanceStarPrize)msgData;
            CMsgSceneSystemGM2GCAckGetInstanceStarPrize.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress ack = (CMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress)msgData;
            CMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckEnterContinuousStage(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckEnterContinuousStage ack = (CMsgSceneSystemGM2GCAckEnterContinuousStage)msgData;
            CMsgSceneSystemGM2GCAckEnterContinuousStage.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckReportContinuousStageResult(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckReportContinuousStageResult ack = (CMsgSceneSystemGM2GCAckReportContinuousStageResult)msgData;
            CMsgSceneSystemGM2GCAckReportContinuousStageResult.CallBack(ack);
        }


        private void OnMsgSceneSystemGM2GCAckRollFastClearContinuousStageCount(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum ack = (CMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum)msgData;
            CMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckGetContinuousInstanceData(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckGetContinuousInstanceData ack = (CMsgSceneSystemGM2GCAckGetContinuousInstanceData)msgData;
            CMsgSceneSystemGM2GCAckGetContinuousInstanceData.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckResetContinuousInstance(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckResetContinuousInstance ack = (CMsgSceneSystemGM2GCAckResetContinuousInstance)msgData;
            CMsgSceneSystemGM2GCAckResetContinuousInstance.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckDeterminePrizeItem(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckDetermineStagePrizeItem ack = (CMsgSceneSystemGM2GCAckDetermineStagePrizeItem)msgData;
            CMsgSceneSystemGM2GCAckDetermineStagePrizeItem.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckEnterRandomStage(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckEnterRandomStage ack = (CMsgSceneSystemGM2GCAckEnterRandomStage)msgData;
            CMsgSceneSystemGM2GCAckEnterRandomStage.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckReportRandomStageResult(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckReportRandomStageResult ack = (CMsgSceneSystemGM2GCAckReportRandomStageResult)msgData;
            CMsgSceneSystemGM2GCAckReportRandomStageResult.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckGetGreedLandInfo(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckGetGreedLandInfo ack = (CMsgSceneSystemGM2GCAckGetGreedLandInfo)msgData;
            CMsgSceneSystemGM2GCAckGetGreedLandInfo.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckPurchaseArenaTickts(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckPurchaseArenaTickts ack = (CMsgSceneSystemGM2GCAckPurchaseArenaTickts)msgData;
            CMsgSceneSystemGM2GCAckPurchaseArenaTickts.CallBack(ack);
        }

        private void OnMsgSceneSystemGM2GCAckRestoreStageTickets(UnityFrame.CMsg msgData)
        {
            CMsgSceneSystemGM2GCAckRestoreStageTickets ack = (CMsgSceneSystemGM2GCAckRestoreStageTickets)msgData;
            CMsgSceneSystemGM2GCAckRestoreStageTickets.CallBack(ack);
        }



    }
}