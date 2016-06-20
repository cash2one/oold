using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
     //进入场景
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGM2GCAckEnterScene : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckEnterScene()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ENTER_SCENE)
        {

        }
        public UInt32 m_currentSceneID = 0;
        public UInt32 m_retCode = 0;
        public List<CSceneRoleInfo> m_listSceneRoles = new List<CSceneRoleInfo>();
        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            m_currentSceneID = msgStream.ReadUInt();
            UInt16 count = msgStream.ReadUShort() ;
            for (UInt16 i = 0; i < count; ++i)
            {
                CSceneRoleInfo sceneRoleInfo = new CSceneRoleInfo();
                sceneRoleInfo.SerializeFrom(msgStream);
                m_listSceneRoles.Add(sceneRoleInfo);
            }
            return true;
        }

        public static CClientCore.CBMsgSceneSystemGM2GCAckEnterScene cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckEnterScene ack)
        {
            if (CMsgSceneSystemGM2GCAckEnterScene.cb != null)
            {
                CMsgSceneSystemGM2GCAckEnterScene.cb((EEnterSceneResult)ack.m_retCode, ack.m_currentSceneID, ack.m_listSceneRoles);
            }
        }
    }
    //退出场景
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGM2GCAckQuitScene : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckQuitScene()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_QUIT_SCENE)
        {

        }

        public UInt32 m_retCode = 0;
        public UInt32 m_currentSceneID = 0;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            if (m_retCode != (UInt32)EQuitSceneResult.EQUITSCENE_RESUlT_SUCCESS)
            {
                return true;
            }
            m_currentSceneID = msgStream.ReadUInt();

            return true;
        }

        public static CClientCore.CBMsgSceneSystemGM2GCAckQuitScene cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckQuitScene ack)
        {
            if (CMsgSceneSystemGM2GCAckQuitScene.cb == null)
            {
                return;
            }
            CMsgSceneSystemGM2GCAckQuitScene.cb((EQuitSceneResult)ack.m_retCode, ack.m_currentSceneID);
        }

    }
    //场景人物复活
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGM2GCAckRoleRevive : UnityFrame.CMsg
    {
        public ESceneRoleReviveResult m_result;
        static public CClientCore.CBMsgSceneSystemGM2GCAckRoleRevive s_cb = null;

        public CMsgSceneSystemGM2GCAckRoleRevive()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ROLE_REVIVE)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (ESceneRoleReviveResult)msgStream.ReadByte();
            return true;
        }

        static public void CallBack(CMsgSceneSystemGM2GCAckRoleRevive msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb((UnityGMClient.ESceneRoleReviveResult)msg.m_result);
                }
            }
        }
    }
    //打开竞技场界面获取角色竞技场信息
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGM2GCAckGetRoleArenaData : UnityFrame.CMsg
    {
        public CRoleArenaData m_roleArenaData = null;
        static public CClientCore.CBMsgSceneSystemGM2GCAckGetRoleArenaData s_cb = null;

        public CMsgSceneSystemGM2GCAckGetRoleArenaData()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_ROLE_ARENA_DATA)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_roleArenaData = new CRoleArenaData();
            m_roleArenaData.SerializeFrom(msgStream);

            return true;
        }

        static public void CallBack(CMsgSceneSystemGM2GCAckGetRoleArenaData msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb(msg.m_roleArenaData);
                }
            }
        }
    }

    //更新一批竞技场挑战者
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGM2GCAckGetNewArenaChallengees : UnityFrame.CMsg
    {
        List<CArenaChallengeeData> m_listChallengees = new List<CArenaChallengeeData>();
        static public CClientCore.CBMsgSceneSystemGM2GCAckGetNewArenaChallengees s_cb = null;

        public CMsgSceneSystemGM2GCAckGetNewArenaChallengees()
        :base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_NEW_ARENA_CHALLENGEES)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            UInt16 count = msgStream.ReadUShort();
            for (UInt32 i = 0; i < count; ++i )
            {
                CArenaChallengeeData challenge = new CArenaChallengeeData();
                challenge.SerializeFrom(msgStream);
                m_listChallengees.Add(challenge);
            }
            
            return true;
        }

        static public void CallBack(CMsgSceneSystemGM2GCAckGetNewArenaChallengees msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb(msg.m_listChallengees);
                }
            }
        }
    }
    //挑战竞技场角色
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   class CMsgSceneSystemGM2GCAckChallengeArenaRole : UnityFrame.CMsg
   {
       public EEnterSceneResult m_result;
       public CBattleRoleData m_challengingRoleData = new CBattleRoleData();
       static public CClientCore.CBMsgSceneSystemGC2GMReqChallengeArenaRole s_cb = null;

       public CMsgSceneSystemGM2GCAckChallengeArenaRole()
           : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_CHALLENGE_ARENA_ROLE)
       {
       }

       protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
       {
           byte result = msgStream.ReadByte();
           m_result = (EEnterSceneResult)result;
           m_challengingRoleData.SerializeFrom(msgStream);

           return true;
       }

       static public void CallBack(CMsgSceneSystemGM2GCAckChallengeArenaRole msg)
       {
           if (msg != null)
           {
               if (s_cb != null)
               {
                   s_cb(msg.m_result, msg.m_challengingRoleData);
               }
           }
       }
   }

   //挑战竞技场角色结束
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   class CMsgSceneSystemGM2GCAckChallengeArenaRoleFinish : UnityFrame.CMsg
   {
       public EChallengeArenaRoleFinishResult m_result;
       static public CClientCore.CBChallengeArenaRoleFinish s_cb = null;

       public CMsgSceneSystemGM2GCAckChallengeArenaRoleFinish()
           : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_CHALLENGE_ARENA_ROLE_FINISH)
       {
       }

       protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
       {
           byte result = msgStream.ReadByte();
           m_result = (EChallengeArenaRoleFinishResult)result;

           return true;
       }

       static public void CallBack(CMsgSceneSystemGM2GCAckChallengeArenaRoleFinish msg)
       {
           if (msg != null)
           {
               if (s_cb != null)
               {
                   s_cb(msg.m_result);
               }
           }
       }
   }

   //服务端推送在线玩家的挑战纪录
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   class CMsgSceneSystemGM2GCAckAddNewArenaChallengeRecord : UnityFrame.CMsg
   {
       public CArenaChallengeRecord m_record = new CArenaChallengeRecord();
       static public CClientCore.CBMsgSceneSystemGM2GCAckAddNewArenaChallengeRecord s_cb = null;

       public CMsgSceneSystemGM2GCAckAddNewArenaChallengeRecord()
       : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ADD_NEW_ARENA_CHALLENGE_RECORD)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_record.SerializeFrom(msgStream);

            return true;
        }

        static public void CallBack(CMsgSceneSystemGM2GCAckAddNewArenaChallengeRecord msg)
        {
           if (msg != null)
           {
                if (s_cb != null)
                {
                    s_cb(msg.m_record);
                }
            }
        }
    }

    //购买竞技场入场券
    class CMsgSceneSystemGM2GCAckPurchaseArenaTickts : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckPurchaseArenaTickts()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_PURCHASE_ARENA_TICKETS)
        {

        }

        public EPurchaseArenaTicketsResult m_result;
        public UInt32 m_curTicketCount;
        public UInt32 m_nextTicketPrice;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EPurchaseArenaTicketsResult)msgStream.ReadByte();
            m_curTicketCount = msgStream.ReadUInt();
            m_nextTicketPrice = msgStream.ReadUInt();
            return true;
        }

        public static CClientCore.CBMsgSceneSystemGM2GCAckPurchaseArenaTickts s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckPurchaseArenaTickts ack)
        {
            if (CMsgSceneSystemGM2GCAckPurchaseArenaTickts.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckPurchaseArenaTickts.s_cb(ack.m_result, ack.m_curTicketCount, ack.m_nextTicketPrice);
            }

        }
    }

    class CMsgSceneSystemGM2GCAckGetStroyInstanceProgress : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckGetStroyInstanceProgress()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_STORY_INSTANCE_PROGRESS)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_instanceID = msgStream.ReadUInt();
            m_index = msgStream.ReadUShort();
            return true;
        }

        public UInt32 m_instanceID = 0;
        public UInt16 m_index = 0;

        public static CClientCore.CBMsgSceneSystemGM2GCAckGetStroyInstanceProgress s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckGetStroyInstanceProgress ack)
        {
            if (CMsgSceneSystemGM2GCAckGetStroyInstanceProgress.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckGetStroyInstanceProgress.s_cb(ack.m_instanceID, ack.m_index);
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGM2GCAckGetInstanceData : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckGetInstanceData()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_INSTANCE_DATA)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EGetInstanceDataResult)msgStream.ReadByte();
            m_instanceID = msgStream.ReadUInt();
            UInt16 count = msgStream.ReadUShort();
            for (Int32 i = 0; i < count; ++i)
            {
                CStageData instanceData = new CStageData();
                instanceData.SerializeFrom(msgStream);
                m_listInstanceData.Add(instanceData);
            }
            return true;
        }

        public EGetInstanceDataResult m_result;
        public UInt32 m_instanceID = 0;
        public List<CStageData> m_listInstanceData = new List<CStageData>();
        public static CClientCore.CBMsgSceneSystemGM2GCAckGetInstanceData s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckGetInstanceData ack)
        {
            if (CMsgSceneSystemGM2GCAckGetInstanceData.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckGetInstanceData.s_cb(ack.m_result, ack.m_instanceID, ack.m_listInstanceData);
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGM2GCAckEnterStage : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckEnterStage()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ENTER_STAGE)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EEnterSceneResult)msgStream.ReadByte();
            UInt16 zoneID = msgStream.ReadUShort();
            if (zoneID > 0) {
                m_helperData.SerializeFrom(msgStream);
            }
            m_stageMonster.serializeFrom(msgStream);
            return true;
        }

        public EEnterSceneResult m_result;
        public CBattleRoleData m_helperData = new CBattleRoleData();
        public CStageMonster m_stageMonster = new CStageMonster();
        public static CClientCore.CBMsgSceneSystemGM2GCAckEnterStage s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckEnterStage ack)
        {
            if (CMsgSceneSystemGM2GCAckEnterStage.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckEnterStage.s_cb(ack.m_result, ack.m_helperData, ack.m_stageMonster);
            }
        }
    }

    class CMsgSceneSystemGM2GCAckStageResultReport : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckStageResultReport()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_STAGE_REPORT_RESULT)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (ESendStageResultReportResult)msgStream.ReadByte();
            return true;
        }

        ESendStageResultReportResult m_result;
        public static CClientCore.CBMsgSceneSystemGM2GCAckStageResultReport s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckStageResultReport ack)
        {
            if (CMsgSceneSystemGM2GCAckStageResultReport.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckStageResultReport.s_cb(ack.m_result);
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGM2GCAckClearStage : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckClearStage()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_CLEAR_STAGE)
        {

        }
        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EClearStageResult)msgStream.ReadByte();
            if (m_result == EClearStageResult.ECLEAR_STAGE_RESULT_SUCCESS) {
                m_stagePrize.SerializeFrom(msgStream);
            }
            return true;
        }

        EClearStageResult m_result;
        CStagePrize m_stagePrize = new CStagePrize();

        public static CClientCore.CBMsgSceneSystemGM2GCAckClearStage s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckClearStage ack)
        {
            if (CMsgSceneSystemGM2GCAckClearStage.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckClearStage.s_cb(ack.m_result, ack.m_stagePrize);
            }
        }
    }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGM2GCAckGetInstanceStarPrize : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckGetInstanceStarPrize()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_INSTANCE_STAR_PRIZE)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EGetInstanceStarPrizeResult)msgStream.ReadByte();
            if (m_result ==  EGetInstanceStarPrizeResult.EGET_INSTANCE_PRIZE_RESULT_SUCCESS) 
            {
                UInt16 count = msgStream.ReadUShort();
                for (UInt16 i = 0; i < count; ++i ) {
                    CPrizeItem item = new CPrizeItem();
                    item.SerializeFrom(msgStream);
                    m_listPrizeItem.Add(item);
                }
            }
            return true;
        }

        EGetInstanceStarPrizeResult m_result;
        List<CPrizeItem> m_listPrizeItem = new List<CPrizeItem>();

        public static CClientCore.CBMsgSceneSystemGM2GCAckGetInstanceStarPrize s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckGetInstanceStarPrize ack)
        {
            if (CMsgSceneSystemGM2GCAckGetInstanceStarPrize.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckGetInstanceStarPrize.s_cb(ack.m_result, ack.m_listPrizeItem);
            }
        }
    }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_INSTANCE_STAR_PRIZE_PROGRESS)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_instanceTPID = msgStream.ReadUInt();
            m_star = msgStream.ReadUShort();
            return true;
        }

        UInt32 m_instanceTPID = 0;
        UInt16 m_star = 0;
        public static CClientCore.CBMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress ack)
        {
            if (CMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckGetIntanceStarPrizeProgress.s_cb(ack.m_instanceTPID, ack.m_star);
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////// 
    class CMsgSceneSystemGM2GCAckGetContinuousInstanceData : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckGetContinuousInstanceData()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_CONTINUOUS_INSTANCE_DATA)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EGetContinuousInstanceDataResult)msgStream.ReadByte();
            m_dailyFreeRollFastClearStageCount = msgStream.ReadUInt();
            m_instanceTPID = msgStream.ReadUInt();
            m_curStageIndex = msgStream.ReadUInt();
            return true;
        }

        EGetContinuousInstanceDataResult m_result;
        UInt32 m_dailyFreeRollFastClearStageCount = 0;
        UInt32 m_instanceTPID = 0;
        UInt32 m_curStageIndex = 0;
        public static CClientCore.CBMsgSceneSystemGM2GCAckGetContinuousInstanceData s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckGetContinuousInstanceData ack)
        {
            if (CMsgSceneSystemGM2GCAckGetContinuousInstanceData.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckGetContinuousInstanceData.s_cb(ack.m_result, ack.m_dailyFreeRollFastClearStageCount ,ack.m_instanceTPID, ack.m_curStageIndex);
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGM2GCAckEnterContinuousStage : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckEnterContinuousStage()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ENTER_CONTINUOUS_STAGE)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EEnterSceneResult)msgStream.ReadByte();
            return true;
        }

        public static CClientCore.CBMsgSceneSystemGM2GCAckEnterContinuousStage s_cb = null;
        public EEnterSceneResult m_result;
        public static void CallBack(CMsgSceneSystemGM2GCAckEnterContinuousStage ack)
        {
            if (CMsgSceneSystemGM2GCAckEnterContinuousStage.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckEnterContinuousStage.s_cb(ack.m_result);
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGM2GCAckReportContinuousStageResult : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckReportContinuousStageResult()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_REPORT_CONTINUOUS_STAGE_RESULT)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EReportContinuousStageResultResult)msgStream.ReadByte();
            if (m_result == EReportContinuousStageResultResult.EREPORT_CONTINUOUS_STAGE_RESULT_RESULT_SUCCESS)
            {
                m_lastScore = msgStream.ReadUInt();
                m_stagePrize.SerializeFrom(msgStream);
            }
            return true;
        }

        EReportContinuousStageResultResult m_result;
        UInt32 m_lastScore = 0;
        CStagePrize m_stagePrize = new CStagePrize();
        public static CClientCore.CBMsgSceneSystemGM2GCAckReportContinuousStageResult s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckReportContinuousStageResult ack)
        {
            if (CMsgSceneSystemGM2GCAckReportContinuousStageResult.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckReportContinuousStageResult.s_cb(ack.m_result, ack.m_lastScore, ack.m_stagePrize);
            }

        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum()
        :base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ROLL_FAST_CLEAR_CONTINUOUS_STAGE_NUM)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (ERollFastClearContinuousStageNum)msgStream.ReadByte();
            if (m_result == ERollFastClearContinuousStageNum.EROLL_FAST_CLAER_CONTINUOUS_STAGE_NUM_SUCCESS)
            {
                m_dailyFreeRollFastClearStageCount = msgStream.ReadUInt();
                m_rollNum = msgStream.ReadUInt();
                m_finalStageIndex = msgStream.ReadUInt();
                UInt16 count = msgStream.ReadUShort();
                for (UInt16 i = 0; i < count; ++i)
                {
                    CStagePrize stagePrize = new CStagePrize();
                    stagePrize.SerializeFrom(msgStream);
                    m_listStagePrize.Add(stagePrize);
                }
            }
            return true;
        }

        ERollFastClearContinuousStageNum m_result;
        UInt32 m_rollNum = 0;
        UInt32 m_dailyFreeRollFastClearStageCount = 0;
        UInt32 m_finalStageIndex = 0;
        List<CStagePrize> m_listStagePrize = new List<CStagePrize>();
        public static CClientCore.CBMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum ack)
        {
            if (CMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckRollFastClearContinuousStageNum.s_cb(ack.m_result, ack.m_dailyFreeRollFastClearStageCount, ack.m_rollNum, ack.m_finalStageIndex, ack.m_listStagePrize);
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGM2GCAckResetContinuousInstance : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckResetContinuousInstance()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_RESET_CONTINUOUS_INSTANCE_DATA)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EResetContinuousInstanceResult)msgStream.ReadByte();
            m_instanceTPID = msgStream.ReadUInt();
            return true;
        }

        EResetContinuousInstanceResult m_result = EResetContinuousInstanceResult.ERESET_CONTINUOUS_INSTANCE_RESULT_FAIL;
        UInt32 m_instanceTPID = 0;
        public static CClientCore.CBMsgSceneSystemGM2GCAckResetContinuousInstance s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckResetContinuousInstance ack)
        {
            if (CMsgSceneSystemGM2GCAckResetContinuousInstance.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckResetContinuousInstance.s_cb(ack.m_result, ack.m_instanceTPID);
            }

        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGM2GCAckDetermineStagePrizeItem : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckDetermineStagePrizeItem()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_DETERMINE_STAGE_PRIZE_ITEM)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EDetermineStagePrizeItemResult)msgStream.ReadByte();
            return true;
        }

        public EDetermineStagePrizeItemResult m_result;
        public static CClientCore.CBMsgSceneSystemGM2GCAckDetermineStagePrizeItem s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckDetermineStagePrizeItem ack)
        {
            if (CMsgSceneSystemGM2GCAckDetermineStagePrizeItem.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckDetermineStagePrizeItem.s_cb(ack.m_result);
            }

        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public delegate void CBMsgSceneSystemGM2GCAckEnterRandomStage();
    class CMsgSceneSystemGM2GCAckEnterRandomStage : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckEnterRandomStage()
        :base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ENTER_RANDOM_STAGE)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EEnterSceneResult)msgStream.ReadByte();
            m_stageMonster.serializeFrom(msgStream);
            return true;
        }

        public EEnterSceneResult m_result;
        public CStageMonster m_stageMonster = new CStageMonster();
        public static CClientCore.CBMsgSceneSystemGM2GCAckEnterRandomStage s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckEnterRandomStage ack)
        {
            if (CMsgSceneSystemGM2GCAckEnterRandomStage.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckEnterRandomStage.s_cb(ack.m_result, ack.m_stageMonster);
            }
        }
    }


    class CMsgSceneSystemGM2GCAckReportRandomStageResult : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckReportRandomStageResult()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_SEND_RANDOM_STAGE_RESULT)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (ESendRandomStageReportResult)msgStream.ReadByte();
            return true;
        }

        public ESendRandomStageReportResult m_result;
        public static CClientCore.CBMsgSceneSystemGM2GCAckReportRandomStageResult s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckReportRandomStageResult ack)
        {
            if (CMsgSceneSystemGM2GCAckReportRandomStageResult.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckReportRandomStageResult.s_cb(ack.m_result);
            }

        }
    }

    class CMsgSceneSystemGM2GCAckGetGreedLandInfo : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckGetGreedLandInfo()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_GREED_LAND_INFO)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_greedLandInfo.serializeFrom(msgStream);
            return true;
        }

        public EGetGreedLandInfoResult m_result = EGetGreedLandInfoResult.EGET_GREEDLAND_INFO_FAIL;
        public CGreedLandInfo m_greedLandInfo = new CGreedLandInfo();

        public static CClientCore.CBMsgSceneSystemGM2GCAckGetGreedLandInfo s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckGetGreedLandInfo ack)
        {
            if (CMsgSceneSystemGM2GCAckGetGreedLandInfo.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckGetGreedLandInfo.s_cb(ack.m_result, ack.m_greedLandInfo);
            }
        }
    }

    class CMsgSceneSystemGM2GCAckRestoreStageTickets : UnityFrame.CMsg
    {
        public CMsgSceneSystemGM2GCAckRestoreStageTickets()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_RESTORE_STAGE_TICKETS)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (ERestoreStageTicketsResult)msgStream.ReadByte();
            m_instanceTPID = msgStream.ReadUInt();
            m_stageIndex = msgStream.ReadUInt();
            m_ticketCount = msgStream.ReadUInt();
            m_nextRestoreRequireDiamond = msgStream.ReadUInt();

            return true;
        }

        ERestoreStageTicketsResult m_result;
        UInt32 m_instanceTPID;
        UInt32 m_stageIndex;
        UInt32 m_ticketCount;
        UInt32 m_nextRestoreRequireDiamond;
        public static CClientCore.CBMsgSceneSystemGM2GCAckRestoreStageTickets s_cb = null;
        public static void CallBack(CMsgSceneSystemGM2GCAckRestoreStageTickets ack)
        {
            if (CMsgSceneSystemGM2GCAckRestoreStageTickets.s_cb != null)
            {
                CMsgSceneSystemGM2GCAckRestoreStageTickets.s_cb(ack.m_result, ack.m_instanceTPID, ack.m_stageIndex, ack.m_ticketCount, ack.m_nextRestoreRequireDiamond);
            }

        }
    }



                                  



                                  
                                  


                                  

                                  

                                  













                                  
                                  

                                  




}
