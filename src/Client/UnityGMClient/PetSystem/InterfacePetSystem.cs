using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {
        /// <summary>
        /// 扩展温泉 
        /// </summary>
        public delegate void CBMsgPetSystemGM2GCAckExpandHotSpring(EExpandHotSpringResult retCode,CHotSpring hotSpring);

          /// <summary>
        /// 扩展温泉 
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgPetSystemGM2GCReqExpandHotSpring(CBMsgPetSystemGM2GCAckExpandHotSpring cb)
        {
            CMsgPetSystemGC2GMReqExpandHotSpring req = new CMsgPetSystemGC2GMReqExpandHotSpring();
            CMsgPetSystemGM2GCAckExpandHotSpring.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 援护 
        /// </summary>
        public delegate void CBMsgPetSystemGM2GCAckPetSitDown(EPetSitDownResult retCode);
        /// <summary>
        /// 援护
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgPetSystemGM2GCReqPetSitDown(UInt32 petID,CBMsgPetSystemGM2GCAckPetSitDown cb)
        {
            CMsgPetSystemGC2GMReqSitDown req = new CMsgPetSystemGC2GMReqSitDown(petID);
            CMsgPetSystemGM2GCAckPetSitDown.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }
        
        /// <summary>
        /// 取消援护 
        /// </summary>
        public delegate void CBMsgPetSystemGM2GCAckPetStandUp(EPetStandUpResult retCode);
          /// <summary>
        /// 取消援护
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgPetSystemGM2GCReqPetStandUp(UInt32 petID, CBMsgPetSystemGM2GCAckPetStandUp cb)
        {
            CMsgPetSystemGC2GMReqPetStandUp req = new CMsgPetSystemGC2GMReqPetStandUp(petID);
            CMsgPetSystemGM2GCAckPetStandUp.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

		/// <summary>
        /// 获取伙伴 
        /// </summary>
        public delegate void CBMsgPetSystemGM2GCAckGetPetData(EGetPetDataResult retCode,CPetItem petItem);
        public bool SendMsgPetSystemGM2GCReqGetPetData(UInt32 petID, CBMsgPetSystemGM2GCAckGetPetData cb)
        {
            CMsgPetSystemGC2GMReqGetPetData req = new CMsgPetSystemGC2GMReqGetPetData(petID);
            CMsgPetSystemGM2GCAckGetPetData.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }
        
        /// <summary>
        /// 进入温泉 
        /// </summary>
        public delegate void CBMsgPetSystemGM2GCAckPetEnterPool(EPetEnterPoolResult retCode);
          /// <summary>
        /// 进入温泉
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgPetSystemGM2GCReqPetEnterPool(UInt32 petID,EHotSpringType hotSpringType, CBMsgPetSystemGM2GCAckPetEnterPool cb)
        {
            CMsgPetSystemGC2GMReqPetEnterPool req = new CMsgPetSystemGC2GMReqPetEnterPool(petID, hotSpringType);
            CMsgPetSystemGM2GCAckPetEnterPool.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 离开温泉 
        /// </summary>
        public delegate void CBMsgPetSystemGM2GCAckPetQuitPool(EPetQuitPoolResult retCode, CPetItem petItem);
        /// <summary>
        /// 离开温泉
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgPetSystemGM2GCReqPetQuitPool(UInt32 petID, CBMsgPetSystemGM2GCAckPetQuitPool cb)
        {
            CMsgPetSystemGC2GMReqPetQuitPool req = new CMsgPetSystemGC2GMReqPetQuitPool(petID);
            CMsgPetSystemGM2GCAckPetQuitPool.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 快速离开温泉 
        /// </summary>
        public delegate void CBMsgPetSystemGM2GCAckPetFastQuitPool(EPetFastQuitPoolResult retCode, CPetItem petItem);
        /// <summary>
        /// 快速离开温泉
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgPetSystemGM2GCReqPetFastQuitPool(UInt32 petID, CBMsgPetSystemGM2GCAckPetFastQuitPool cb)
        {
            CMsgPetSystemGC2GMReqPetFastQuitPool req = new CMsgPetSystemGC2GMReqPetFastQuitPool(petID);
            CMsgPetSystemGM2GCAckPetFastQuitPool.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 初始化伙伴
        /// </summary>
        /// <param name="retCode"></param>
        /// <param name="petData"></param>
        public delegate void CBMsgPetSystemGM2GCAckInitPetData(EGetInitRolePetDataResult retCode,CPetData petData);
        public bool SendMsgPetSystemGM2GCReqInitPetData(CBMsgPetSystemGM2GCAckInitPetData cb)
        {
            CMsgPetSystemGC2GMReqInitPetData req = new CMsgPetSystemGC2GMReqInitPetData();
            CMsgPetSystemGM2GCAckInitPetData.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 温泉伙伴任务激活通知
        /// </summary>
        public delegate void CBMsgPetSystemGM2GCNtfActiveHotSpringTask(UInt32 a_petID, EHotSpringTaskStatus a_hotSprintTaskStatus,EHotSpringTaskType a_hotSpringTaskType);
        public void RegisterActiveHotSpringTaskCallBack(CBMsgPetSystemGM2GCNtfActiveHotSpringTask callBackFunction)
        {
            CMsgPetSystemGM2GCNtfActiveHotSpringTask.cb = callBackFunction;
        }
//         /// <summary>
//         /// 伙伴升级通知
//         /// </summary>
//         public delegate void CBMsgPetSystemGM2GCNtfUpgradePet(CPetItem petItem);
//         public void RegisterUpgradePetCallBack(CBMsgPetSystemGM2GCNtfUpgradePet callBackFunction)
//         {
//             CMsgPetSystemGM2GCNtfUpgradePet.cb = callBackFunction;
//         }

        /// <summary>
        /// 完成副本发布任务 
        /// </summary> 
        public delegate void CBMsgPetSystemGM2GCAckHotSpringTaskEnd(EHotSpringTaskEndResult retCode,CTalkAnswer answer);
        public bool SendMsgPetSystemGC2GMReqHotSpringTaskEnd(UInt32 petID, EPetHotSprintEnd endStatus, CBMsgPetSystemGM2GCAckHotSpringTaskEnd cb)
        {
            CMsgPetSystemGC2GMReqHotSpringTaskEnd req = new CMsgPetSystemGC2GMReqHotSpringTaskEnd(petID, endStatus);
            CMsgPetSystemGM2GCAckHotSpringTaskEnd.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 获取伙伴基本信息 
        /// </summary>
        public delegate void CBMsgPetSystemGM2GCAckGetPetBaseInforList(EGetPetBaseInforListResult retCode, List<CPetBaseInfor> petBaseInforList);
        public bool SendMsgPetSystemGC2GMReqGetPetBaseInforList(CBMsgPetSystemGM2GCAckGetPetBaseInforList cb)
        {
            CMsgPetSystemGC2GMReqGetPetBaseInforList req = new CMsgPetSystemGC2GMReqGetPetBaseInforList();
            CMsgPetSystemGM2GCAckGetPetBaseInforList.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 伙伴温泉任务 
        /// </summary>
        public delegate void CBMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail(EPetGetHotSpringTaskDetailResult retCode, CHotSpringTaskData taskData);
        public bool SendMsgPetSystemGC2GMReqPetGetHotSpringTaskDetail(UInt32 petID, EHotSpringTaskType petTaskType, CBMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail cb)
        {
            CMsgPetSystemGC2GMReqPetGetHotSpringTaskDetail req = new CMsgPetSystemGC2GMReqPetGetHotSpringTaskDetail(petID, petTaskType);
            CMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 伙伴温泉任务完成 
        /// </summary>
        public delegate void CBMsgPetSystemGM2GCAckPetFinishHotSpringTask(EPetTaskFinishResult retCode, UInt32 petID);
        public bool SendMsgPetSystemGC2GMReqPetFinishHotSpringTask(UInt32 petID,UInt32 answerID, CBMsgPetSystemGM2GCAckPetFinishHotSpringTask cb)
        {
            CMsgPetSystemGC2GMReqPetFinishHotSpringTask req = new CMsgPetSystemGC2GMReqPetFinishHotSpringTask(petID, answerID);
            CMsgPetSystemGM2GCAckPetFinishHotSpringTask.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 送礼 
        /// </summary>
        public delegate void CBMsgPetSystemGM2GCAckSendPetGift(ESendPetGiftResult retCode);
        public bool SendMsgPetSystemGC2GMReqSendPetGift(UInt32 petID, List<CPrizeItem> itemList, CBMsgPetSystemGM2GCAckSendPetGift cb)
        {
            CMsgPetSystemGC2GMReqSendPetGift req = new CMsgPetSystemGC2GMReqSendPetGift(petID, itemList);
            CMsgPetSystemGM2GCAckSendPetGift.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 查看伙伴
        /// </summary>
        public delegate void CBMsgPetSystemGM2GCAckGetPetUnlockData(EGetPetUnlockDataResult retCode, CPetUnlockData petUnlockData);
        public bool SendMsgPetSystemGC2GMReqGetPetUnlockData(CBMsgPetSystemGM2GCAckGetPetUnlockData cb)
        {
            CMsgPetSystemGC2GMReqGetPetUnlockData req = new CMsgPetSystemGC2GMReqGetPetUnlockData();
            CMsgPetSystemGM2GCAckGetPetUnlockData.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 解锁伙伴
        /// </summary>
        /// <param name="retCode"></param>
        /// <param name="petID"></param>
        public delegate void CBMsgPetSystemGM2GCAckUnlockPet(EUnlockPetResult retCode, CPetItem petItem);
        public bool SendMsgPetSystemGC2GMReqUnlockPet(UInt32 petTPID, CBMsgPetSystemGM2GCAckUnlockPet cb)
        {
            CMsgPetSystemGC2GMReqUnlockPet req = new CMsgPetSystemGC2GMReqUnlockPet(petTPID);
            CMsgPetSystemGM2GCAckUnlockPet.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }
    }
}
