using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CPetSystemMsgNumID
    {
        public const uint EMSGNUMID_PETSYSTEM_GC2GM_REQ_EXPANDHOTSPRING = 1;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_ACK_EXPANDHOTSPRING = 2;

        public const uint EMSGNUMID_PETSYSTEM_GM2GC_NTF_ACTIVE_HOTSPRINGTASK = 3;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_NTF_HOTSPRINGEGG_FULL = 4;

        public const uint EMSGNUMID_PETSYSTEM_GC2GM_REQ_HOTSPRINGTASK_END = 5;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_ACK_HOTSPRINGTASK_END = 6;

        public const uint EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_FINISH_HOTSPRINGTASK = 7;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_FINISH_HOTSPRINGTASK = 8;

        public const uint EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_GETPETUNLOCKDATA = 9;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_GETPETUNLOCKDATA = 10;

        public const uint EMSGNUMID_PETSYSTEM_GC2GM_REQ_UNLOCKPET = 11;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_ACK_UNLOCKPET = 12;

        public const uint EMSGNUMID_PETSYSTEM_GC2GM_REQ_SENDPET_GIFT = 13;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_ACK_SENDPET_GIFT = 14;

        public const uint EMSGNUMID_PETSYSTEM_GM2GC_NTF_UPGRADEPET = 15;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_NTF_ACTIVE_HOTSPRING_BOSSTASK = 16;

        public const uint EMSGNUMID_PETSYSTEM_GC2GM_REQ_GET_PET_BASEINFOR_LIST = 17;    
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_ACK_GET_PET_BASEINFOR_LIST = 18;

        public const uint EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_GET_HOTSPRING_TASK_DETAIL = 19;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_GET_HOTSPRING_TASK_DETAIL = 20;

        public const uint EMSGNUMID_PETSYSTEM_GC2GM_REQ_INIT_ROLEPETDATA = 21;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_ACK_INIT_ROLEPETDATA = 22;

        // 进入援护
        public const uint EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_SITDOWN = 23;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_SITDOWN = 24;
        // 取消援护
        public const uint EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_STANDUP = 25;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_STANDUP = 26;
        // 获取伙伴数据
        public const uint EMSGNUMID_PETSYSTEM_GC2GM_REQ_GET_PETDATA = 27;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_ACK_GET_PETDATA = 28;
        // 进入温泉
        public const uint EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_ENTERPOOL = 29;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_ENTERPOOL = 30;
        // 离开温泉
        public const uint EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_QUITPOOL = 31;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_QUITPOOL = 32;
        // 快速离开温泉
        public const uint EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_FAST_QUITPOOL = 33;
        public const uint EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_FAST_QUITPOOL = 34;
    }

    /// <summary>
    /// 温泉扩建 
    /// </summary>
    public class CMsgPetSystemGC2GMReqExpandHotSpring : UnityFrame.CMsg
    {
        public CMsgPetSystemGC2GMReqExpandHotSpring()
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GC2GM_REQ_EXPANDHOTSPRING)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    public class CMsgPetSystemGM2GCAckExpandHotSpring : UnityFrame.CMsg
    {
        public CMsgPetSystemGM2GCAckExpandHotSpring()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_ACK_EXPANDHOTSPRING)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EExpandHotSpringResult)msgStream.ReadUInt();
            if (m_retCode != EExpandHotSpringResult.EEXPANDHOTSPRING_RESULT_SUCCESS)
            {
                return true;
            }
            return m_hotSpring.SerializeFrom(msgStream);
        }

        public static void CallBack(CMsgPetSystemGM2GCAckExpandHotSpring ack)
        {
            if (CMsgPetSystemGM2GCAckExpandHotSpring.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCAckExpandHotSpring.cb(ack.m_retCode, ack.m_hotSpring);
        }

        EExpandHotSpringResult m_retCode = EExpandHotSpringResult.EEXPANDHOTSPRING_RESULT_FAIL;
        CHotSpring m_hotSpring = new CHotSpring();
        public static CClientCore.CBMsgPetSystemGM2GCAckExpandHotSpring cb = null;
    }

    /// <summary>
    /// 援护状态 
    /// </summary>
    public class CMsgPetSystemGC2GMReqSitDown : UnityFrame.CMsg
    {
        public CMsgPetSystemGC2GMReqSitDown(UInt32 petID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_SITDOWN)
        {
            m_petID = petID;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_petID);
            return true;
        }

        public UInt32 m_petID;
    }

    public class CMsgPetSystemGM2GCAckPetSitDown : UnityFrame.CMsg
    {
        public CMsgPetSystemGM2GCAckPetSitDown()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_SITDOWN)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EPetSitDownResult)msgStream.ReadUInt();
            if (m_retCode != EPetSitDownResult.EPETSITDOWN_RESULT_SUCCESS)
            {
                return true;
            }
            return true; 
        }

        public static void CallBack(CMsgPetSystemGM2GCAckPetSitDown ack)
        {
            if (CMsgPetSystemGM2GCAckPetSitDown.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCAckPetSitDown.cb(ack.m_retCode);
        }

        EPetSitDownResult m_retCode = EPetSitDownResult.EPETSITDOWN_RESULT_FAIL;
        public static CClientCore.CBMsgPetSystemGM2GCAckPetSitDown cb = null;
    }

    public class CMsgPetSystemGC2GMReqPetStandUp : UnityFrame.CMsg
    {
        public CMsgPetSystemGC2GMReqPetStandUp(UInt32 petID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_STANDUP)
        {
            m_petID = petID;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_petID);
            return true;
        }
        public UInt32 m_petID;
    }

    public class CMsgPetSystemGM2GCAckPetStandUp : UnityFrame.CMsg
    {
        public CMsgPetSystemGM2GCAckPetStandUp()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_STANDUP)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EPetStandUpResult)msgStream.ReadUInt();
            if (m_retCode != EPetStandUpResult.EPETSTANDUP_RESULT_SUCCESS)
            {
                return true;
            }
            return true;
        }

        public static void CallBack(CMsgPetSystemGM2GCAckPetStandUp ack)
        {
            if (CMsgPetSystemGM2GCAckPetStandUp.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCAckPetStandUp.cb(ack.m_retCode);
        }

        EPetStandUpResult m_retCode = EPetStandUpResult.EPETSTANDUP_RESULT_FAIL;
        public static CClientCore.CBMsgPetSystemGM2GCAckPetStandUp cb = null;
    }

    public class CMsgPetSystemGC2GMReqGetPetData : UnityFrame.CMsg
    {
        public CMsgPetSystemGC2GMReqGetPetData(UInt32 petID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GC2GM_REQ_GET_PETDATA)
        {
            m_petID = petID;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_petID);
            return true;
        }
        public UInt32 m_petID;
    }

    public class CMsgPetSystemGM2GCAckGetPetData : UnityFrame.CMsg
    {
        public CMsgPetSystemGM2GCAckGetPetData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_ACK_GET_PETDATA)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EGetPetDataResult)msgStream.ReadUInt();
            if (m_retCode != EGetPetDataResult.EGETPETDATA_RESULT_SUCCESS)
            {
                return true;
            }
            m_petItem.SerializeFrom(msgStream);
            return true;
        }

        public static void CallBack(CMsgPetSystemGM2GCAckGetPetData ack)
        {
            if (CMsgPetSystemGM2GCAckGetPetData.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCAckGetPetData.cb(ack.m_retCode,ack.m_petItem);
        }

        public EGetPetDataResult m_retCode = EGetPetDataResult.EGETPETDATA_RESULT_FAIL;
        public CPetItem m_petItem = new CPetItem();
        public static CClientCore.CBMsgPetSystemGM2GCAckGetPetData cb = null;
    }

    public class CMsgPetSystemGC2GMReqPetEnterPool : UnityFrame.CMsg
    {
        public CMsgPetSystemGC2GMReqPetEnterPool(UInt32 petID,EHotSpringType hotSpringType)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_ENTERPOOL)
        {
            m_petID = petID;
            m_hotSpringType = hotSpringType;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_petID);
            UInt32 type = (UInt32)m_hotSpringType;
            msgStream.Write(type);
            return true;
        }
        public UInt32 m_petID;
        EHotSpringType m_hotSpringType;
    }

    public class CMsgPetSystemGM2GCAckPetEnterPool : UnityFrame.CMsg
    {
        public CMsgPetSystemGM2GCAckPetEnterPool()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_ENTERPOOL)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EPetEnterPoolResult)msgStream.ReadUInt();
            if (m_retCode != EPetEnterPoolResult.EPETENTERPOOL_RESULT_SUCCESS)
            {
                return true;
            }
            return true;
        }

        public static void CallBack(CMsgPetSystemGM2GCAckPetEnterPool ack)
        {
            if (CMsgPetSystemGM2GCAckPetEnterPool.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCAckPetEnterPool.cb(ack.m_retCode);
        }

        EPetEnterPoolResult m_retCode = EPetEnterPoolResult.EPETENTERPOOL_RESULT_FAIL;
        public static CClientCore.CBMsgPetSystemGM2GCAckPetEnterPool cb = null;
    }


    public class CMsgPetSystemGC2GMReqPetQuitPool : UnityFrame.CMsg
    {
        public CMsgPetSystemGC2GMReqPetQuitPool(UInt32 petID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_QUITPOOL)
        {
            m_petID = petID;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_petID);
            return true;
        }
        public UInt32 m_petID;
    }

    public class CMsgPetSystemGM2GCAckPetQuitPool : UnityFrame.CMsg
    {
        public CMsgPetSystemGM2GCAckPetQuitPool()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_QUITPOOL)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EPetQuitPoolResult)msgStream.ReadUInt();
            if (m_retCode != EPetQuitPoolResult.EPETQUITPOOL_RESULT_SUCCESS)
            {
                return true;
            }
            m_petItem.SerializeFrom(msgStream);
            return true;
        }

        public static void CallBack(CMsgPetSystemGM2GCAckPetQuitPool ack)
        {
            if (CMsgPetSystemGM2GCAckPetQuitPool.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCAckPetQuitPool.cb(ack.m_retCode, ack.m_petItem);
        }

        EPetQuitPoolResult m_retCode = EPetQuitPoolResult.EPETQUITPOOL_RESULT_FAIL;
        CPetItem m_petItem = new CPetItem();
        public static CClientCore.CBMsgPetSystemGM2GCAckPetQuitPool cb = null;
    }

    public class CMsgPetSystemGC2GMReqPetFastQuitPool : UnityFrame.CMsg
    {
        public CMsgPetSystemGC2GMReqPetFastQuitPool(UInt32 petID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_FAST_QUITPOOL)
        {
            m_petID = petID;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_petID);
            return true;
        }
        public UInt32 m_petID;
    }

    public class CMsgPetSystemGM2GCAckPetFastQuitPool : UnityFrame.CMsg
    {
        public CMsgPetSystemGM2GCAckPetFastQuitPool()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_FAST_QUITPOOL)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EPetFastQuitPoolResult)msgStream.ReadUInt();
            if (m_retCode != EPetFastQuitPoolResult.EPET_FASTQUITPOOL_RESULT_SUCCESS)
            {
                return true;
            }
            m_petItem.SerializeFrom(msgStream);
            return true;
        }

        public static void CallBack(CMsgPetSystemGM2GCAckPetFastQuitPool ack)
        {
            if (CMsgPetSystemGM2GCAckPetFastQuitPool.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCAckPetFastQuitPool.cb(ack.m_retCode, ack.m_petItem);
        }

        EPetFastQuitPoolResult m_retCode = EPetFastQuitPoolResult.EPET_FASTQUITPOOL_RESULT_FAIL;
        CPetItem m_petItem = new CPetItem();
        public static CClientCore.CBMsgPetSystemGM2GCAckPetFastQuitPool cb = null;
    }
    
    /// <summary>
    ///  任务激活通知
    /// </summary>
     public class CMsgPetSystemGM2GCNtfActiveHotSpringTask: UnityFrame.CMsg
    {
         public CMsgPetSystemGM2GCNtfActiveHotSpringTask()
             : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_NTF_ACTIVE_HOTSPRINGTASK)
        {
        }
         public UInt32 m_petID = 0;
         EHotSpringTaskStatus m_hotSprintTaskStatus = EHotSpringTaskStatus.EHotSpringInvalidTask;
         public EHotSpringTaskType m_type = EHotSpringTaskType.EHotSpringTaskTypeInvalid;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_petID = msgStream.ReadUInt();
            m_hotSprintTaskStatus = (EHotSpringTaskStatus)msgStream.ReadUInt();
            m_type = (EHotSpringTaskType)msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgPetSystemGM2GCNtfActiveHotSpringTask ack)
        {
            if (CMsgPetSystemGM2GCNtfActiveHotSpringTask.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCNtfActiveHotSpringTask.cb(ack.m_petID, ack.m_hotSprintTaskStatus, ack.m_type);
        }
        public static CClientCore.CBMsgPetSystemGM2GCNtfActiveHotSpringTask cb = null;
    }

//      /// <summary>
//      /// 温泉升级推送 
//      /// </summary>
//      public class CMsgPetSystemGM2GCNtfUpgradePet : UnityFrame.CMsg
//      {
//          public CMsgPetSystemGM2GCNtfUpgradePet()
//              : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_NTF_UPGRADEPET)
//          {
//          }
//          public CPetItem m_petItem = new CPetItem();
// 
//          protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
//          {
//              return m_petItem.SerializeFrom(msgStream);
//          }
// 
//          public static void CallBack(CMsgPetSystemGM2GCNtfUpgradePet ack)
//          {
//              if (CMsgPetSystemGM2GCNtfUpgradePet.cb == null)
//              {
//                  return;
//              }
//              CMsgPetSystemGM2GCNtfUpgradePet.cb(ack.m_petItem);
//          }
//          public static CClientCore.CBMsgPetSystemGM2GCNtfUpgradePet cb = null;
//      }

     /// <summary>
     /// 伙伴初始化请求
     /// </summary>
     public class CMsgPetSystemGC2GMReqInitPetData : UnityFrame.CMsg
     {
         public CMsgPetSystemGC2GMReqInitPetData()
             : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GC2GM_REQ_INIT_ROLEPETDATA)
         {
         }

         protected override bool _SerializeTo(UnityUtility.CStream msgStream)
         {
             return true;
         }
     }

    /// <summary>
    /// 伙伴初始化
    /// </summary>
    public class CMsgPetSystemGM2GCAckInitPetData : UnityFrame.CMsg
    {
        public CMsgPetSystemGM2GCAckInitPetData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_ACK_INIT_ROLEPETDATA)
        {
        }
        
        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EGetInitRolePetDataResult)msgStream.ReadUInt();
            if(m_retCode != EGetInitRolePetDataResult.EGET_INITROLEPETDATA_RESULT_SUCCESS){
                return true;
            }
            return m_petData.SerializeFrom(msgStream);
        }

        public static void CallBack(CMsgPetSystemGM2GCAckInitPetData ack)
        {
            if (CMsgPetSystemGM2GCAckInitPetData.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCAckInitPetData.cb(ack.m_retCode,ack.m_petData);
        }

        public EGetInitRolePetDataResult m_retCode = EGetInitRolePetDataResult.EGET_INITROLEPETDATA_RESULT_FAIL;
        public CPetData m_petData = new CPetData();
        public static CClientCore.CBMsgPetSystemGM2GCAckInitPetData cb = null;
    }

    /// <summary>
    /// 任务结束 
    /// </summary>
    class CMsgPetSystemGC2GMReqHotSpringTaskEnd : UnityFrame.CMsg
    {
        public CMsgPetSystemGC2GMReqHotSpringTaskEnd(UInt32 petID, EPetHotSprintEnd endStatus)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GC2GM_REQ_HOTSPRINGTASK_END)
        {
            m_petID = petID;
            m_endStatus = endStatus;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_petID);
            msgStream.Write((UInt32)m_endStatus);
            return true;
        }

        UInt32 m_petID;
        EPetHotSprintEnd m_endStatus;
    }

    public class CMsgPetSystemGM2GCAckHotSpringTaskEnd : UnityFrame.CMsg
    {
        public CMsgPetSystemGM2GCAckHotSpringTaskEnd()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_ACK_HOTSPRINGTASK_END)
        {
            m_retCode = EHotSpringTaskEndResult.EHOTSPRINGTASK_END_RESULT_FAIL;
        }
       
        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EHotSpringTaskEndResult)msgStream.ReadUInt();
            if (m_retCode == EHotSpringTaskEndResult.EHOTSPRINGTASK_END_RESULT_FAIL)
            {
                return true;
            }
            m_answer.SerializeFrom(msgStream);

            return true;
        }

        public static void CallBack(CMsgPetSystemGM2GCAckHotSpringTaskEnd ack)
        {
            if (CMsgPetSystemGM2GCAckHotSpringTaskEnd.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCAckHotSpringTaskEnd.cb(ack.m_retCode, ack.m_answer);
        }

        public EHotSpringTaskEndResult m_retCode;
        public CTalkAnswer m_answer = new CTalkAnswer();
        public static CClientCore.CBMsgPetSystemGM2GCAckHotSpringTaskEnd cb = null;
    }

    /// <summary>
    /// 伙伴任务完成请求 
    /// </summary>
    class CMsgPetSystemGC2GMReqPetFinishHotSpringTask : UnityFrame.CMsg
    {
        public CMsgPetSystemGC2GMReqPetFinishHotSpringTask(UInt32 petID, UInt32 answerID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_FINISH_HOTSPRINGTASK)
        {
            m_petID = petID;
            m_answerID = answerID;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_petID);
            msgStream.Write(m_answerID);
            return true;
        }
        UInt32 m_petID;
        UInt32 m_answerID;
    }

    /// <summary>
    ///  温泉任务完成
    /// </summary>
    public class CMsgPetSystemGM2GCAckPetFinishHotSpringTask : UnityFrame.CMsg
    {
        public CMsgPetSystemGM2GCAckPetFinishHotSpringTask()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_FINISH_HOTSPRINGTASK)
        {
            m_retCode = EPetTaskFinishResult.EPETTASKFINISH_RESULT_FAIL;
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EPetTaskFinishResult)msgStream.ReadUInt();
            m_petID = msgStream.ReadUInt();

            return true;
        }

        public static void CallBack(CMsgPetSystemGM2GCAckPetFinishHotSpringTask ack)
        {
            if (CMsgPetSystemGM2GCAckPetFinishHotSpringTask.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCAckPetFinishHotSpringTask.cb(ack.m_retCode, ack.m_petID);
        }

        public EPetTaskFinishResult m_retCode;
        public UInt32 m_petID;
        public static CClientCore.CBMsgPetSystemGM2GCAckPetFinishHotSpringTask cb = null;
    }
    
    /// <summary>
    /// 伙伴任务请求 
    /// </summary>
    class CMsgPetSystemGC2GMReqGetPetBaseInforList : UnityFrame.CMsg
    {
        public CMsgPetSystemGC2GMReqGetPetBaseInforList()
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GC2GM_REQ_GET_PET_BASEINFOR_LIST)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    /// <summary>
    ///  温泉任务
    /// </summary>
    public class CMsgPetSystemGM2GCAckGetPetBaseInforList: UnityFrame.CMsg
    {
        public CMsgPetSystemGM2GCAckGetPetBaseInforList()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_ACK_GET_PET_BASEINFOR_LIST)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EGetPetBaseInforListResult)msgStream.ReadUInt();
            if (m_retCode != EGetPetBaseInforListResult.EGET_PETBASEINFORLIST_RESULT_SUCCESS)
            {
                return true;
            }
            UInt32 petCount = msgStream.ReadUInt();
            for (int i = 0; i < petCount; ++i)
            {
                CPetBaseInfor pet = new CPetBaseInfor();
                pet.SerializeFrom(msgStream);
                m_petBaseInfoList.Add(pet);
            }
            return true;
        }

        public static void CallBack(CMsgPetSystemGM2GCAckGetPetBaseInforList ack)
        {
            if (CMsgPetSystemGM2GCAckGetPetBaseInforList.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCAckGetPetBaseInforList.cb(ack.m_retCode, ack.m_petBaseInfoList);
        }

        public EGetPetBaseInforListResult m_retCode = EGetPetBaseInforListResult.EGET_PETBASEINFORLIST_RESULT_FAIL;
        public List<CPetBaseInfor> m_petBaseInfoList = new List<CPetBaseInfor>();
        public static CClientCore.CBMsgPetSystemGM2GCAckGetPetBaseInforList cb = null;
    }


    /// <summary>
    /// 伙伴任务请求 
    /// </summary>
    class CMsgPetSystemGC2GMReqPetGetHotSpringTaskDetail : UnityFrame.CMsg
    {
        public CMsgPetSystemGC2GMReqPetGetHotSpringTaskDetail(UInt32 petID,EHotSpringTaskType petTaskType)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_GET_HOTSPRING_TASK_DETAIL)
        {
            m_petID = petID;
            m_petTaskType = petTaskType;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_petID);
            UInt32 task = (UInt32)m_petTaskType;
            msgStream.Write(task);
            return true;
        }
        public UInt32 m_petID;
        public EHotSpringTaskType m_petTaskType = EHotSpringTaskType.EHotSpringTaskTypeInvalid;
    }


    /// <summary>
    ///  温泉任务
    /// </summary>
    public class CMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail : UnityFrame.CMsg
    {
        public CMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_GET_HOTSPRING_TASK_DETAIL)
        {
            m_retCode = EPetGetHotSpringTaskDetailResult.EPETGET_HOTSPRING_TASKDETAIL_RESULT_FAIL;
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EPetGetHotSpringTaskDetailResult)msgStream.ReadUInt();
            if (m_retCode != EPetGetHotSpringTaskDetailResult.EPETGET_HOTSPRING_TASKDETAIL_RESULT_SUCCESS)
            {
                return true;
            }
            m_hotSpringTaskData.SerializeFrom(msgStream);

            return true;
        }

        public static void CallBack(CMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail ack)
        {
            if (CMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail.cb(ack.m_retCode, ack.m_hotSpringTaskData);
        }

        public EPetGetHotSpringTaskDetailResult m_retCode;
        public UInt32 m_petID;
        public CHotSpringTaskData m_hotSpringTaskData = new CHotSpringTaskData();
        public static CClientCore.CBMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail cb = null;
    }

    /// <summary>
    /// 伙伴送礼 
    /// </summary>
    class CMsgPetSystemGC2GMReqSendPetGift : UnityFrame.CMsg
    {
        public CMsgPetSystemGC2GMReqSendPetGift(UInt32 petID,List<CPrizeItem> itemList)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GC2GM_REQ_SENDPET_GIFT)
        {
            m_petID = petID;
            m_itemList = itemList;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_petID);
            if (m_itemList == null)
            {
                UInt32 totalCount = 0;
                msgStream.Write(totalCount);
                return true;
            }
            UInt32 count = (uint)m_itemList.Count;
            msgStream.Write(count);
            foreach (CPrizeItem item in m_itemList)
            {
                item.SerializeTo(msgStream);
            }
            return true;
        }

        public UInt32 m_petID = 0;
        public List<CPrizeItem> m_itemList = new List<CPrizeItem>();
    }

    /// <summary>
    /// 送礼 
    /// </summary>
    public class CMsgPetSystemGM2GCAckSendPetGift : UnityFrame.CMsg
    {
        public CMsgPetSystemGM2GCAckSendPetGift()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_ACK_SENDPET_GIFT)
        {
            m_retCode = ESendPetGiftResult.ESENDPET_GIFT_RESULT_FAIL;
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (ESendPetGiftResult)msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgPetSystemGM2GCAckSendPetGift ack)
        {
            if (CMsgPetSystemGM2GCAckSendPetGift.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCAckSendPetGift.cb(ack.m_retCode);
        }

        public ESendPetGiftResult m_retCode;
        public static CClientCore.CBMsgPetSystemGM2GCAckSendPetGift cb = null;
    }

    /// <summary>
    /// 获取解锁数据 
    /// </summary>
    class CMsgPetSystemGC2GMReqGetPetUnlockData : UnityFrame.CMsg
    {
        public CMsgPetSystemGC2GMReqGetPetUnlockData()
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_GETPETUNLOCKDATA)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    public class CMsgPetSystemGM2GCAckGetPetUnlockData : UnityFrame.CMsg
    {
        public CMsgPetSystemGM2GCAckGetPetUnlockData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_GETPETUNLOCKDATA)
        {
            m_retCode = EGetPetUnlockDataResult.EGETPETUNLOCKDATARESULT_FAIL;
        }
        public EGetPetUnlockDataResult m_retCode;
        public CPetUnlockData m_petUnlockData = new CPetUnlockData(); 

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EGetPetUnlockDataResult)msgStream.ReadUInt();
            if (m_retCode != EGetPetUnlockDataResult.EGETPETUNLOCKDATARESULT_SUCCESS)
            {
                return true;
            }
            m_petUnlockData.SerializeFrom(msgStream);

            return true;
        }

        public static void CallBack(CMsgPetSystemGM2GCAckGetPetUnlockData ack)
        {
            if (CMsgPetSystemGM2GCAckGetPetUnlockData.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCAckGetPetUnlockData.cb(ack.m_retCode,ack.m_petUnlockData);
        }
        public static CClientCore.CBMsgPetSystemGM2GCAckGetPetUnlockData cb = null;
    }

    /// <summary>
    /// 解锁伙伴 
    /// </summary>
    class CMsgPetSystemGC2GMReqUnlockPet : UnityFrame.CMsg
    {
        public CMsgPetSystemGC2GMReqUnlockPet(UInt32 petTPID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GC2GM_REQ_UNLOCKPET)
        {
            m_petTPID = petTPID;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_petTPID);
            return true;
        }

        public UInt32 m_petTPID;
    }

    public class CMsgPetSystemGM2GCAckUnlockPet : UnityFrame.CMsg
    {
        public CMsgPetSystemGM2GCAckUnlockPet()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PETSYSTEM, CPetSystemMsgNumID.EMSGNUMID_PETSYSTEM_GM2GC_ACK_UNLOCKPET)
        {
            m_retCode = EUnlockPetResult.EUNLOCKPET_RESULT_FAIL;
        }
        public EUnlockPetResult m_retCode;
        public CPetItem m_petItem = new CPetItem();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EUnlockPetResult)msgStream.ReadUInt();
            if (m_retCode != EUnlockPetResult.EUNLOCKPET_RESULT_SUCCESS)
            {
                return true;
            }
            m_petItem.SerializeFrom(msgStream);
            return true;
        }

        public static void CallBack(CMsgPetSystemGM2GCAckUnlockPet ack)
        {
            if (CMsgPetSystemGM2GCAckUnlockPet.cb == null)
            {
                return;
            }
            CMsgPetSystemGM2GCAckUnlockPet.cb(ack.m_retCode, ack.m_petItem);
        }
        public static CClientCore.CBMsgPetSystemGM2GCAckUnlockPet cb = null;
    }
}
