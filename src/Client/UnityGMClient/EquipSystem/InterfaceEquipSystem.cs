using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {
        /// <summary>
        /// 装备洗练
        /// </summary>
        /// <param name="retCode"></param>
        /// <param name="equipID"></param>

        public delegate void CBMsgEquipSystemGM2GCAckResetAttr(EResetAttrResult retCode,CEquipItem equip);
        public bool SendMsgEquipSystemGM2GCReqResetAttr(EResetEquipType resetEquipType, UInt32 equipID,List<UInt32> lockAttrIndexList, UInt32 itemEquipID, CBMsgEquipSystemGM2GCAckResetAttr cb)
        {
            CMsgEquipSystemGC2GMReqResetAttr req = new CMsgEquipSystemGC2GMReqResetAttr(resetEquipType,equipID,lockAttrIndexList, itemEquipID);
            CMsgEquipSystemGM2GCAckResetAttr.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 发送改变装备状态请求
        /// </summary>
        /// <param name="retCode"></param>
        /// <param name="equipID"></param>
        public delegate void CBMsgEquipSystemGM2GCAckChangeEquipStatus(EChangeStatusResult retCode, UInt32 equipID, UInt32 itemIndex, EEquipStatus status);
        public bool SendMsgEquipSystemGM2GCReqChangeEquipStatus(UInt32 equipID, UInt32 index, EEquipStatus status, CBMsgEquipSystemGM2GCAckChangeEquipStatus cb)
        {
            CMsgEquipSystemGC2GMReqChangeEquipStatus req = new CMsgEquipSystemGC2GMReqChangeEquipStatus(equipID, index, status);
            CMsgEquipSystemGM2GCAckChangeEquipStatus.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        public delegate void CBMsgEquipSystemGM2GCAckCondition(EConditionResult retCode, CConditionData condition);
        /// <summary>
        /// 请求条件
        /// </summary>
        public bool SendMsgEquipSystemGM2GCReqGetCondition(UInt32 equipID, EEquipOperation operation, CBMsgEquipSystemGM2GCAckCondition cb)
        {
            CMsgEquipSystemGC2GMReqCondition req = new CMsgEquipSystemGC2GMReqCondition(equipID,operation);
            CMsgEquipSystemGM2GCAckCondition.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        // 保存操作
        public delegate void CBMsgEquipSystemGM2GCAckSaveOperation(ESaveOperationResult retCode, UInt32 equipID);
        /// <summary>
        /// 保存操作
        /// </summary>
        /// <param name="callBackFunction"></param>
        public bool SendMsgEquipSystemGM2GCReqSaveOperation(UInt32 equipID, EEquipOperation operation,EOperationResult opResult, CBMsgEquipSystemGM2GCAckSaveOperation cb)
        {
            CMsgEquipSystemGC2GMReqSaveOperation req = new CMsgEquipSystemGC2GMReqSaveOperation(equipID, operation, opResult);
            CMsgEquipSystemGM2GCAckSaveOperation.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        public delegate void CBMsgEquipSystemGM2GCAckEquipData(EEquipDataResult retCode, CEquipData equipData);
        /// <summary>
        /// 请求兵工厂数据
        /// </summary>
        /// <param name="cb"></param>
        public bool SendMsgEquipSystemGM2GCReqEquipData(EReqEquipType reqEquipType,CBMsgEquipSystemGM2GCAckEquipData cb)
        {
            CMsgEquipSystemGC2GMReqEquipData req = new CMsgEquipSystemGC2GMReqEquipData(reqEquipType);
            CMsgEquipSystemGM2GCAckEquipData.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

       
        public delegate void CBMsgEquipSystemGM2GCAckGetEquipItem(EGetEquipItemResult retCode, CEquipItem equipItem);
        public bool SendMsgEquipSystemGM2GCReqGetEquipItem(EReqGetEquip reqType,UInt32 reqID, CBMsgEquipSystemGM2GCAckGetEquipItem cb)
        {
            CMsgEquipSystemGC2GMReqGetEquipItem req = new CMsgEquipSystemGC2GMReqGetEquipItem(reqType, reqID);
            CMsgEquipSystemGM2GCAckGetEquipItem.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 更新单件装备
        /// </summary>
        /// <param name="retCode"></param>
        /// <param name="equipItem"></param>
        public delegate void CBMsgEquipSystemGM2GCAckUpdateRoleEquipData(EUpdateRoleEquipDataResult retCode, CEquipItem equipItem);
        public void RegisterUpdateRoleEquipDataCallBack(CBMsgEquipSystemGM2GCAckUpdateRoleEquipData callBackFunction)
        {
            CMsgEquipSystemGM2GCNtfUpdateRoleEquipData.cb = callBackFunction;
        }

        /// <summary>
        /// 装备获取
        /// </summary>
        public delegate void CBMsgEquipSystemGM2GCAckNextAddLevelEquip(EGetNextAddLevelEquipResult retCode, CEquipItem equip);
        public bool SendMsgEquipSystemGC2GMReqNextAddLevelEquip(UInt32 equipID, CBMsgEquipSystemGM2GCAckNextAddLevelEquip cb)
        {
            CMsgEquipSystemGC2GMReqNextAddLevelEquip req = new CMsgEquipSystemGC2GMReqNextAddLevelEquip(equipID);
            CMsgEquipSystemGM2GCAckNextAddLevelEquip.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 装备拆解
        /// </summary>
        public delegate void CBMsgEquipSystemGM2GCAckDisassemblyEquip(EDisassemblyEquipResult retCode);
        public bool SendMsgEquipSystemGC2GMReqDisassemblyEquip(List<UInt32> equipIDList, CBMsgEquipSystemGM2GCAckDisassemblyEquip cb)
        {
            CMsgEquipSystemGC2GMReqDisassemblyEquip req = new CMsgEquipSystemGC2GMReqDisassemblyEquip(equipIDList);
            CMsgEquipSystemGM2GCAckDisassemblyEquip.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 装备拆解结果
        /// </summary>
        public delegate void CBMsgEquipSystemGM2GCAckGetDisassemblyEquipResult(EGetDisassemblyEquipResult retCode,List<CPrizeItem> itemList);
        public bool SendMsgEquipSystemGC2GMReqGetDisassemblyEquipResult(List<UInt32> equipIDList, CBMsgEquipSystemGM2GCAckGetDisassemblyEquipResult cb)
        {
            CMsgEquipSystemGC2GMReqGetDisassemblyEquipResult req = new CMsgEquipSystemGC2GMReqGetDisassemblyEquipResult(equipIDList);
            CMsgEquipSystemGM2GCAckGetDisassemblyEquipResult.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 装备强化
        /// </summary>
        public delegate void CBMsgEquipSystemGM2GCAckUpgradeLevel(EUPGRADELEVELResult retCode, CEquipItem equip);
        public bool SendMsgEquipSystemGC2GMReqUpgradeLevel(UInt32 equipID, CBMsgEquipSystemGM2GCAckUpgradeLevel cb)
        {
            CMsgEquipSystemGC2GMReqUpgradeLevel req = new CMsgEquipSystemGC2GMReqUpgradeLevel(equipID);
            CMsgEquipSystemGM2GCAckUpgradeLevel.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 装备熔炼
        /// </summary>
        public delegate void CBMsgEquipSystemGM2GCAckUpgradeQuality(EUpgradeQualityResult retCode, CEquipItem equip);

        public bool SendMsgEquipSystemGC2GMReqUpgradeQuality(UInt32 equipID, UInt32 itemTPID, CBMsgEquipSystemGM2GCAckUpgradeQuality cb)
        {
            CMsgEquipSystemGC2GMReqUpgradeQuality req = new CMsgEquipSystemGC2GMReqUpgradeQuality(equipID, itemTPID);
            CMsgEquipSystemGM2GCAckUpgradeQuality.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 宝石镶嵌
        /// </summary>
        public delegate void CBMsgEquipSystemGM2GCAckChangeGemStatus(EGemUpdateStatusResult retCode, CEquipItem equipItem);
        public bool SendMsgEquipSystemGM2GCReqChangeGemStatus(UInt32 equipID, EGemSlot gemSlot, EGemStatus operation, UInt32 gemTPID, CBMsgEquipSystemGM2GCAckChangeGemStatus cb)
        {
            CMsgEquipSystemGC2GMReqChangeGemStatus req = new CMsgEquipSystemGC2GMReqChangeGemStatus(equipID, gemSlot, operation, gemTPID);
            CMsgEquipSystemGM2GCAckChangeGemStatus.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 宝石合成
        /// </summary>
        public delegate void CBMsgEquipSystemGM2GCAckGemCombine(EGemCombineResult retCode, UInt32 newGemTPID);

        public bool SendMsgEquipSystemGC2GMReqGemCombine(EGemsCombineType type,UInt32 gemTPID, CBMsgEquipSystemGM2GCAckGemCombine cb)
        {
            CMsgEquipSystemGC2GMReqGemCombine req = new CMsgEquipSystemGC2GMReqGemCombine(type,gemTPID);
            CMsgEquipSystemGM2GCAckGemCombine.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

    }
}
