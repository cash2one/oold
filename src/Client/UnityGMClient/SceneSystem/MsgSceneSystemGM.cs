using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// 人物进入场景
    /// </summary>
    class CMsgSceneSystemGC2GMReqEnterScene : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqEnterScene(UInt32 a_sceneTypeID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ENTER_SCENE)
        {
            m_sceneTypeID = a_sceneTypeID;
        }
        public UInt32 m_sceneTypeID = 0;

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_sceneTypeID);
            return true;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// 人物退出场景
    /// </summary>
    class CMsgSceneSystemGC2GMReqQuitScene : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqQuitScene(UInt32 a_sceneTypeID)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_QUIT_SCENE)
        {
            m_sceneTypeID = a_sceneTypeID;
        }
        private UInt32 m_sceneTypeID = 0;

        //把数据序列化到msgBuffer中
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {

            msgStream.Write(m_sceneTypeID);
            return true;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// 副本中人物复活
    /// </summary>
    class CMsgSceneSystemGC2GMReqRoleRevive : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqRoleRevive()
        :base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ROLE_REVIVE)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    //打开竞技场界面获取角色相关信息
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqGetRoleArenaData : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqGetRoleArenaData()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_ROLE_ARENA_DATA)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    //获取新一批挑战角色列表
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqGetNewArenaChallengees : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqGetNewArenaChallengees()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_NEW_ARENA_CHALLENGEES)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    //挑战竞技场角色
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqChallengeArenaRole : UnityFrame.CMsg
    {
        public CChallengeInfo m_challengeID = new CChallengeInfo();

        public CMsgSceneSystemGC2GMReqChallengeArenaRole(CChallengeInfo challengeID)
        :base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_CHALLENGE_ARENA_ROLE)
        {
            m_challengeID = challengeID;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            m_challengeID.serializeTo(msgStream);
            return true;
        }
    }

    //挑战竞技场角色结束，返回比赛结果
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqChallengeArenaRoleFinish : UnityFrame.CMsg
    {
        public bool m_isWin = false;

        public CMsgSceneSystemGC2GMReqChallengeArenaRoleFinish(bool result)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_CHALLENGE_ARENA_ROLE_FINISH)
        {
            m_isWin = result;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            byte result = (byte)(m_isWin ? 1 : 0);
            msgStream.Write(result);
            return true;
        }
    }

    //购买竞技场入场券
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqPurchaseArenaTickts : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqPurchaseArenaTickts()
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_PURCHASE_ARENA_TICKETS)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqGetStroyInstanceProgress : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqGetStroyInstanceProgress()
                : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_STORY_INSTANCE_PROGRESS)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqGetInstanceData : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqGetInstanceData(UInt32 instanceID)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_INSTANCE_DATA)
        {
            m_instanceID = instanceID;
        }

        public UInt32 m_instanceID = 0;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_instanceID);
            return true;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqEnterStage : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqEnterStage(UInt32 instanceID, UInt16 index, SRoleKey helperKey)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ENTER_STAGE)
        {
            m_instanceID = instanceID;
            m_index = index;
            m_helperKey = helperKey;
        }

        public UInt32 m_instanceID = 0;
        public UInt16 m_index = 0;
        public SRoleKey m_helperKey;

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_instanceID);
            msgStream.Write(m_index);
            m_helperKey.serializeTo(msgStream);

            return true;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqStageResultReport : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqStageResultReport(bool isWin, byte star, Int32 useTime, List<UInt32> clearRandomMonster)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_STAGE_REPORT_RESULT)
        {
            m_isWin = isWin;
            m_star = star;
            m_useTime = useTime;
            m_clearRandomMonster = clearRandomMonster;
        }

        public bool m_isWin = false;
        public byte m_star = 0;
        public Int32 m_useTime = 0;
        public List<UInt32> m_clearRandomMonster;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            byte result = m_isWin ? (byte)1 : (byte)0;
            msgStream.Write(result);
            msgStream.Write(m_star);
            msgStream.Write(m_useTime);
            UInt16 count = (UInt16)m_clearRandomMonster.Count;
            msgStream.Write(count);
            for (UInt16 i = 0; i < count; ++i )
            {
                msgStream.Write(m_clearRandomMonster[i]);
            }
            return true;
        }
    }

     //////////////////////////////////////////////////////////////////////////////////////////////////////////////
     class CMsgSceneSystemGC2GMReqClearStage : UnityFrame.CMsg
     {
        public CMsgSceneSystemGC2GMReqClearStage(UInt32 instanceID, UInt16 stageIndex, bool breakDownItem)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_CLEAR_STAGE)
        {
            m_instanceID = instanceID;
            m_stageIndex = stageIndex;
            m_breakDownItem = breakDownItem;
        }

        public UInt32 m_instanceID = 0;
        public UInt16 m_stageIndex = 0;
        public bool m_breakDownItem = false;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_instanceID);
            msgStream.Write(m_stageIndex);
            msgStream.Write(m_breakDownItem);
            return true;
        }
     }

     //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqGetInstanceStarPrize : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqGetInstanceStarPrize(UInt32 instanceTPID)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_INSTANCE_STAR_PRIZE)
        {
            m_instanceTPID = instanceTPID;
        }

        public UInt32 m_instanceTPID = 0;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_instanceTPID);
            return true;
        }
    }

     //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqGetIntanceStarPrizeProgress : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqGetIntanceStarPrizeProgress(UInt32 instanceTPID)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_INSTANCE_STAR_PRIZE_PROGRESS)
        {
            m_instanceTPID = instanceTPID;
        }

        public UInt32 m_instanceTPID = 0;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_instanceTPID);
            return true;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqGetContinuousInstanceData : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqGetContinuousInstanceData(UInt32 instanceTPID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_CONTINUOUS_INSTANCE_DATA)
        {
            m_instanceTPID = instanceTPID;
        }

        UInt32 m_instanceTPID = 0;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_instanceTPID);
            return true;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqEnterContinuousStage : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqEnterContinuousStage(UInt32 instanceTPID, UInt32 stageIndex)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ENTER_CONTINUOUS_STAGE)
        {
            m_instanceTPID = instanceTPID;
            m_stageIndex = stageIndex; 
        }

        public UInt32 m_instanceTPID = 0;
        public UInt32 m_stageIndex = 0;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_instanceTPID);
            msgStream.Write(m_stageIndex);
            return true;
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqReportContinuousStageResult : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqReportContinuousStageResult(bool isWin, UInt32 score)
        :base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_REPORT_CONTINUOUS_STAGE_RESULT)
        {
            m_isWin = isWin;
            m_score = score;
        }

        public bool m_isWin = false;
        public UInt32 m_score = 0;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            byte result = m_isWin ? (byte)1 : (byte)0;
            msgStream.Write(result);
            msgStream.Write(m_score);
            return true;
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqRollFastClearContinuousStageNum : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqRollFastClearContinuousStageNum(UInt32 instanceTPID)
        :base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ROLL_FAST_CLEAR_CONTINUOUS_STAGE_NUM)
        {
            m_instanceTPID = instanceTPID;
        }

        public UInt32 m_instanceTPID = 0;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_instanceTPID);
            return true;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqResetContinuousInstance : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqResetContinuousInstance(UInt32 instanceTPID)
        :base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_RESET_CONTINUOUS_INSTANCE_DATA)
        {
            m_instanceTPID = instanceTPID;
        }

        public UInt32 m_instanceTPID = 0;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_instanceTPID);
            return true;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqDeterminePrizeItem : UnityFrame.CMsg
    {
        public List<UInt32> m_receiveItems = new List<UInt32>();
        public CMsgSceneSystemGC2GMReqDeterminePrizeItem(List<UInt32> receiveItems)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_DETERMINE_STAGE_PRIZE_ITEM)
        {
            m_receiveItems = receiveItems;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            UInt16 count = (UInt16)m_receiveItems.Count;
            msgStream.Write(count);
            foreach (UInt32 item in m_receiveItems) {
                msgStream.Write(item);
            }
            return true;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqEnterRandomStage : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqEnterRandomStage(UInt32 stageID)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ENTER_RANDOM_STAGE)
        {
            m_stageID = stageID;
        }

        public UInt32 m_stageID = 0;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_stageID);
            return true;
        }
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgSceneSystemGC2GMReqReportRandomStageResult : UnityFrame.CMsg
    {
        public bool m_isWin;
        public CMsgSceneSystemGC2GMReqReportRandomStageResult(bool isWin)
        :base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_SEND_RANDOM_STAGE_RESULT)
        {
            m_isWin = isWin;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            byte result = m_isWin ? (byte)1 : (byte)0;
            msgStream.Write(result);
            return true;
        }
    }

    class CMsgSceneSystemGC2GMReqGetGreedLandInfo : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqGetGreedLandInfo()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_GREED_LAND_INFO)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    class CMsgSceneSystemGC2GMReqRestoreStageTickets : UnityFrame.CMsg
    {
        public UInt32 m_instanceTPID;
        public UInt32 m_index;

        public CMsgSceneSystemGC2GMReqRestoreStageTickets(UInt32 instanceTPID, UInt32 index)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CSceneSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_RESTORE_STAGE_TICKET)
        {
            m_instanceTPID = instanceTPID;
            m_index = index;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_instanceTPID);
            msgStream.Write(m_index);
            return true;
        }
    }
                


                       
                       

                       
                       
                                                            

                       
                                  
                                                                              
                       
                       
          

}
