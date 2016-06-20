using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    
    public class CEquipSystemMsgNumID
    {
        public const uint EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_RESETATTR = 1;
        public const uint EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_RESETATTR = 2;

        public const uint EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_GET_ROLEEQUIPDATA = 3;
        public const uint EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_GET_ROLEEQUIPDATA = 4;

	    public const uint EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_STRENGTHEN_EQUIP = 5;
        public const uint EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_STRENGTHEN_EQUIP = 6;

	    public const uint EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_EVOLVE_EQUIP = 7;
        public const uint EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_EVOLVE_EQUIP = 8;

        public const uint EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_GEM_COMBINE = 9;
        public const uint EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_GEM_COMBINE = 10;

        public const uint EMSGNUMID_EQUIPSYSTEM_GM2GC_NTF_UPDATE_ROLEEQUIPDATA = 11;

        public const uint EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_CHANGE_EQUIPSTATUS = 13;
        public const uint EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_CHANGE_EQUIPSTATUS = 14;

        public const uint EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_EQUIP_DATA = 15;
        public const uint EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_EQUIP_DATA = 16;

        public const uint EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_CONDITION = 17;
        public const uint EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_CONDITION = 18;

        public const uint EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_SAVE_OPERATION = 19;
        public const uint EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_SAVE_OPERATION = 20;

        public const uint EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_CHANGE_GEM_STATUS = 21;
        public const uint EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_CHANGE_GEM_STATUS = 22;

        public const uint EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_NEXT_ADDLEVEL_EQUIPSTATUS = 23;
        public const uint EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_NEXT_ADDLEVEL_EQUIPSTATUS = 24;

        public const uint EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_DISASSEMBLY_EQUIP = 25;
        public const uint EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_DISASSEMBLY_EQUIP = 26;

        public const uint EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_GET_DISASSEMBLY_EQUIP_RESULT = 27;
        public const uint EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_GET_DISASSEMBLY_EQUIP_RESULT = 28;
    }

    class CMsgEquipSystemGC2GMReqChangeGemStatus : UnityFrame.CMsg
    {
        public CMsgEquipSystemGC2GMReqChangeGemStatus(UInt32 equipID,EGemSlot gemSlot, EGemStatus operation,UInt32 gemTPID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_CHANGE_GEM_STATUS)
        {
            m_operation = operation;
            m_equipID = equipID;
            m_gemTPID = gemTPID;
            m_gemSlot = gemSlot;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_equipID);
            UInt32 gemSlot = (UInt32)m_gemSlot;
            msgStream.Write(gemSlot);
            UInt32 operation = (UInt32)m_operation;
            msgStream.Write(operation);
            msgStream.Write(m_gemTPID);
            return true;
        }
        private UInt32 m_equipID = 0;
        private EGemSlot m_gemSlot = EGemSlot.GEM_SLOT_INVALID;
        private EGemStatus m_operation = EGemStatus.GEM_STATUS_OFF;
        private UInt32 m_gemTPID = 0;
    }

    public class CMsgEquipSystemGM2GCAckChangeGemStatus : UnityFrame.CMsg
    {
        public CMsgEquipSystemGM2GCAckChangeGemStatus()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_CHANGE_GEM_STATUS)
        {
        }
        public EGemUpdateStatusResult m_retCode = EGemUpdateStatusResult.EGEM_UPDATESTATUS_RESULT_FAIL;
        private CEquipItem m_equip = new CEquipItem();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EGemUpdateStatusResult)msgStream.ReadUInt();
            if (m_retCode != EGemUpdateStatusResult.EGEM_UPDATESTATUS_RESULT_SUCCESS)
            {
                return true;
            }
            m_equip.SerializeFrom(msgStream);
            return true;
        }

        public static void CallBack(CMsgEquipSystemGM2GCAckChangeGemStatus ack)
        {
            if (CMsgEquipSystemGM2GCAckChangeGemStatus.cb == null)
            {
                return;
            }
            CMsgEquipSystemGM2GCAckChangeGemStatus.cb(ack.m_retCode, ack.m_equip);
        }
        public static CClientCore.CBMsgEquipSystemGM2GCAckChangeGemStatus cb = null;
    }


    class CMsgEquipSystemGC2GMReqSaveOperation : UnityFrame.CMsg
    {
        public CMsgEquipSystemGC2GMReqSaveOperation(UInt32 equipID, EEquipOperation a_operation,EOperationResult a_opResult)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_SAVE_OPERATION)
        {
            m_operation = a_operation;
            m_equipID = equipID;
            m_opResult = a_opResult;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_equipID);
            UInt32 operation = (UInt32)m_operation;
            msgStream.Write(operation);
            UInt32 opResult = (UInt32)m_opResult;
            msgStream.Write(opResult);
            return true;
        }
        private EEquipOperation m_operation = EEquipOperation.EQUIP_UPGRADE_INVALID;
        private UInt32 m_equipID = 0;
        private EOperationResult m_opResult = EOperationResult.OPRESULT_NOT_SAVE;
    }

    public class CMsgEquipSystemGM2GCAckSaveOperation : UnityFrame.CMsg
    {
        public CMsgEquipSystemGM2GCAckSaveOperation()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_SAVE_OPERATION)
        {
            m_retCode = ESaveOperationResult.ESAVEOPERATION_RESUlT_FAIL;
        }
        public ESaveOperationResult m_retCode;
        private UInt32 m_equipID = 0;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (ESaveOperationResult)msgStream.ReadUInt();
            m_equipID = msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgEquipSystemGM2GCAckSaveOperation ack)
        {
            if (CMsgEquipSystemGM2GCAckSaveOperation.cb == null)
            {
                return;
            }
            CMsgEquipSystemGM2GCAckSaveOperation.cb(ack.m_retCode, ack.m_equipID);
        }
        public static CClientCore.CBMsgEquipSystemGM2GCAckSaveOperation cb = null;
    }


    class CMsgEquipSystemGC2GMReqCondition : UnityFrame.CMsg
    {
        public CMsgEquipSystemGC2GMReqCondition(UInt32 equipID, EEquipOperation a_operation)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_CONDITION)
        {
            m_operation = a_operation;
            m_equipID = equipID;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_equipID);
            UInt32 operation = (UInt32)m_operation;
            msgStream.Write(operation);
            return true;
        }
        private EEquipOperation m_operation = EEquipOperation.EQUIP_UPGRADE_INVALID;
        private UInt32 m_equipID = 0;
    }

    public class CMsgEquipSystemGM2GCAckCondition : UnityFrame.CMsg
    {
        public CMsgEquipSystemGM2GCAckCondition()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_CONDITION)
        {
            m_retCode = EConditionResult.ECONDITION_RESUlT_FAIL;
        }
        public EConditionResult m_retCode;
        public CConditionData m_condition = new CConditionData();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EConditionResult)msgStream.ReadUInt();
            if (m_retCode != EConditionResult.ECONDITION_RESUlT_SUCCESS)
            {
                return true;
            }
            return m_condition.SerializeFrom(msgStream);
        }

        public static void CallBack(CMsgEquipSystemGM2GCAckCondition ack)
        {
            if (CMsgEquipSystemGM2GCAckCondition.cb == null)
            {
                return;
            }
            CMsgEquipSystemGM2GCAckCondition.cb(ack.m_retCode, ack.m_condition);
        }
        public static CClientCore.CBMsgEquipSystemGM2GCAckCondition cb = null;
    }

    class CMsgEquipSystemGC2GMReqEquipData : UnityFrame.CMsg
    {
        public CMsgEquipSystemGC2GMReqEquipData(EReqEquipType a_reqEquipType)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_EQUIP_DATA)
        {
            m_reqEquipType = a_reqEquipType;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            UInt32 reqEquipType = (UInt32)m_reqEquipType;
            msgStream.Write(reqEquipType);
            return true;
        }
        public EReqEquipType m_reqEquipType = EReqEquipType.REQ_EQUIP_ALL;
    }
    
    public class CMsgEquipSystemGM2GCAckEquipData : UnityFrame.CMsg
    {
        public CMsgEquipSystemGM2GCAckEquipData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_EQUIP_DATA)
        {
            m_retCode = EEquipDataResult.EEQUIPEDATA_RESUlT_FAIL;
        }
        public EEquipDataResult m_retCode;
        public CEquipData m_equipData = new CEquipData();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EEquipDataResult)msgStream.ReadUInt();
            if (m_retCode != EEquipDataResult.EEQUIPEDATA_RESUlT_SUCCESS)
            {
                return true;
            }
            return m_equipData.SerializeFrom(msgStream);
        }

        public static void CallBack(CMsgEquipSystemGM2GCAckEquipData ack)
        {
            if (CMsgEquipSystemGM2GCAckEquipData.cb == null)
            {
                return;
            }
            CMsgEquipSystemGM2GCAckEquipData.cb(ack.m_retCode, ack.m_equipData);
        }
        public static CClientCore.CBMsgEquipSystemGM2GCAckEquipData cb = null;
    }

    class CMsgEquipSystemGC2GMReqChangeEquipStatus: UnityFrame.CMsg
    {
        public CMsgEquipSystemGC2GMReqChangeEquipStatus(UInt32 a_equipID, UInt32 a_index, EEquipStatus a_status)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_CHANGE_EQUIPSTATUS)
        {
            m_equipID = a_equipID;
            m_index = a_index;
            m_status = a_status;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_equipID);
            msgStream.Write(m_index);
            UInt32 status = (UInt32)m_status;
            msgStream.Write(status);
            return true;
        }

        public UInt32 m_equipID = 0;
        public UInt32 m_index = 0;
        public EEquipStatus m_status = EEquipStatus.EQUIP_STATUS_OFF;
    }

    public class CMsgEquipSystemGM2GCAckChangeEquipStatus : UnityFrame.CMsg
    {
        public CMsgEquipSystemGM2GCAckChangeEquipStatus()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_CHANGE_EQUIPSTATUS)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EChangeStatusResult)msgStream.ReadUInt();
            m_equipID = msgStream.ReadUInt();
            m_itemIndex = msgStream.ReadUInt();
            m_status = (EEquipStatus)msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgEquipSystemGM2GCAckChangeEquipStatus ack)
        {
            if (CMsgEquipSystemGM2GCAckChangeEquipStatus.cb == null)
            {
                return;
            }
            CMsgEquipSystemGM2GCAckChangeEquipStatus.cb(ack.m_retCode, ack.m_equipID,ack.m_itemIndex, ack.m_status);
        }
        public EChangeStatusResult m_retCode = EChangeStatusResult.ECHANGESTATUS_RESULT_FAIL;
        public UInt32 m_equipID = 0;
        public UInt32 m_itemIndex = 0;
        public EEquipStatus m_status = EEquipStatus.EQUIP_STATUS_OFF;
        public static CClientCore.CBMsgEquipSystemGM2GCAckChangeEquipStatus cb = null;
    }

    /// <summary>
    /// 装备洗练
    /// </summary>
    class CMsgEquipSystemGC2GMReqResetAttr: UnityFrame.CMsg
    {
        public CMsgEquipSystemGC2GMReqResetAttr(EResetEquipType resetEquipType, UInt32 a_equipID, List<UInt32> a_lockAttrIndexList, UInt32 a_itemEquipID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_RESETATTR)
        {
           m_equipID = a_equipID;
           m_resetEquipType = resetEquipType;
           m_lockAttrIndexList = a_lockAttrIndexList;
           m_itemEquipID = a_itemEquipID;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_equipID);
            UInt32 resetEquipType = (UInt32)m_resetEquipType;
            msgStream.Write(resetEquipType);
            UInt32 attrCount = 0;
            if (m_lockAttrIndexList == null)
            {
                attrCount = 0;
                msgStream.Write(attrCount);
                return true;
            }
            attrCount = (UInt32)m_lockAttrIndexList.Count;
            msgStream.Write(attrCount);
            for (UInt32 i = 0; i < attrCount; ++i)
            {
                UInt32 attrIndex = m_lockAttrIndexList[(int)i];
                msgStream.Write(attrIndex);
            }
            msgStream.Write(m_itemEquipID);
            return true;
        }

        EResetEquipType m_resetEquipType;
        public UInt32 m_equipID;
        public List<UInt32> m_lockAttrIndexList = null;
        public UInt32 m_itemEquipID;
    }

    public class CMsgEquipSystemGM2GCAckResetAttr: UnityFrame.CMsg
    {
        public CMsgEquipSystemGM2GCAckResetAttr()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_RESETATTR)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EResetAttrResult)msgStream.ReadUInt();
            if (m_retCode != EResetAttrResult.ERESETATTR_RESULT_SUCCESS)
            {
                return true;
            }
            m_equip.SerializeFrom(msgStream);

            return true;
        }

        public static void CallBack(CMsgEquipSystemGM2GCAckResetAttr ack)
        {
            if (CMsgEquipSystemGM2GCAckResetAttr.cb == null)
            {
                return;
            }
            CMsgEquipSystemGM2GCAckResetAttr.cb(ack.m_retCode, ack.m_equip);
        }
        public EResetAttrResult m_retCode = EResetAttrResult.ERESETATTR_RESULT_FAIL;
        public CEquipItem m_equip = new CEquipItem();
        public static CClientCore.CBMsgEquipSystemGM2GCAckResetAttr cb = null;
    }

    class CMsgEquipSystemGC2GMReqGetEquipItem : UnityFrame.CMsg
    {
        public CMsgEquipSystemGC2GMReqGetEquipItem(EReqGetEquip reqType,UInt32 reqID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_GET_ROLEEQUIPDATA)
        {
            m_reqType = (UInt32)reqType;
            m_reqID = reqID;
        }
        
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_reqType);
            msgStream.Write(m_reqID);
            return true;
        }
        private UInt32 m_reqType;
        private UInt32 m_reqID;
    }

    public class CMsgEquipSystemGM2GCAckGetEquipItem : UnityFrame.CMsg
    {
        public CMsgEquipSystemGM2GCAckGetEquipItem()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_GET_ROLEEQUIPDATA)
        {
            m_retCode = EGetEquipItemResult.EGETEQUIPITEM_RESUlT_FAIL;
        }
        public EGetEquipItemResult m_retCode;
        public CEquipItem m_equipItem = new CEquipItem();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EGetEquipItemResult)msgStream.ReadUInt();
            if (m_retCode != EGetEquipItemResult.EGETEQUIPITEM_RESUlT_SUCCESS){
                return true;
            }
            return m_equipItem.SerializeFrom(msgStream);
        }

        public static void CallBack(CMsgEquipSystemGM2GCAckGetEquipItem ack)
        {
            if (CMsgEquipSystemGM2GCAckGetEquipItem.cb == null)
            {
                return;
            }
            CMsgEquipSystemGM2GCAckGetEquipItem.cb(ack.m_retCode, ack.m_equipItem);
        }
        public static CClientCore.CBMsgEquipSystemGM2GCAckGetEquipItem cb = null;
    }

    public class CMsgEquipSystemGM2GCNtfUpdateRoleEquipData : UnityFrame.CMsg
    {
        public CMsgEquipSystemGM2GCNtfUpdateRoleEquipData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GM2GC_NTF_UPDATE_ROLEEQUIPDATA)
        {
            m_retCode = EUpdateRoleEquipDataResult.EIUPDATEEQUIPEDATA_RESUlT_FAIL;
        }
        public EUpdateRoleEquipDataResult m_retCode;
        public CEquipItem m_equipItem = new CEquipItem();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EUpdateRoleEquipDataResult)msgStream.ReadUInt();
            if (m_retCode != EUpdateRoleEquipDataResult.EUPDATEEQUIPEDATA_RESUlT_SUCCESS)
            {
                return true;
            }
            return m_equipItem.SerializeFrom(msgStream);
        }

        public static void CallBack(CMsgEquipSystemGM2GCNtfUpdateRoleEquipData ack)
        {
            if (CMsgEquipSystemGM2GCNtfUpdateRoleEquipData.cb == null)
            {
                return;
            }
            CMsgEquipSystemGM2GCNtfUpdateRoleEquipData.cb(ack.m_retCode, ack.m_equipItem);
        }
        public static CClientCore.CBMsgEquipSystemGM2GCAckUpdateRoleEquipData cb = null;
    }

    /// <summary>
    /// 装备强化
    /// </summary>
    class CMsgEquipSystemGC2GMReqUpgradeLevel : UnityFrame.CMsg
    {
        public CMsgEquipSystemGC2GMReqUpgradeLevel(UInt32 equipID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_STRENGTHEN_EQUIP)
        {
            m_equipID = equipID;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_equipID);
            return true;
        }

        public UInt32 m_equipID;
    }

    public class CMsgEquipSystemGM2GCAckUpgradeLevel : UnityFrame.CMsg
    {
        public CMsgEquipSystemGM2GCAckUpgradeLevel()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_STRENGTHEN_EQUIP)
        {
            m_retCode = EUPGRADELEVELResult.EUPGRADELEVEL_RESUlT_FAIL;
        }
        public EUPGRADELEVELResult m_retCode;
        public CEquipItem m_equip = new CEquipItem();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EUPGRADELEVELResult)msgStream.ReadUInt();
            if (m_retCode != EUPGRADELEVELResult.EUPGRADELEVEL_RESUlT_SUCCESS)
            {
                return true;
            }
            m_equip.SerializeFrom(msgStream);

            return true;
        }

        public static void CallBack(CMsgEquipSystemGM2GCAckUpgradeLevel ack)
        {
            if (CMsgEquipSystemGM2GCAckUpgradeLevel.cb == null)
            {
                return;
            }
            CMsgEquipSystemGM2GCAckUpgradeLevel.cb(ack.m_retCode, ack.m_equip);
        }
        public static CClientCore.CBMsgEquipSystemGM2GCAckUpgradeLevel cb = null;
    }


    /// <summary>
    /// 装备熔炼
    /// </summary>
    class CMsgEquipSystemGC2GMReqUpgradeQuality : UnityFrame.CMsg
    {
        public CMsgEquipSystemGC2GMReqUpgradeQuality(UInt32 equipID, UInt32 itemTPID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_EVOLVE_EQUIP)
        {
            m_equipID = equipID;
            m_itemTPID = itemTPID;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_equipID);
            msgStream.Write(m_itemTPID);
            return true;
        }

        public UInt32 m_equipID = 0;
        public UInt32 m_itemTPID = 0;
    }

    public class CMsgEquipSystemGM2GCAckUpgradeQuality : UnityFrame.CMsg
    {
        public CMsgEquipSystemGM2GCAckUpgradeQuality()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_EVOLVE_EQUIP)
        {
            m_retCode = EUpgradeQualityResult.EUPGRADEQUALITY_RESUlT_FAIL;
        }
        public EUpgradeQualityResult m_retCode;
        public CEquipItem m_equip = new CEquipItem();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EUpgradeQualityResult)msgStream.ReadUInt();
            if (m_retCode != EUpgradeQualityResult.EUPGRADEQUALITY_RESUlT_SUCCESS)
            {
                return true;
            }
            m_equip.SerializeFrom(msgStream);
            return true;
        }

        public static void CallBack(CMsgEquipSystemGM2GCAckUpgradeQuality ack)
        {
            if (CMsgEquipSystemGM2GCAckUpgradeQuality.cb == null)
            {
                return;
            }
            CMsgEquipSystemGM2GCAckUpgradeQuality.cb(ack.m_retCode,ack.m_equip);
        }
        public static CClientCore.CBMsgEquipSystemGM2GCAckUpgradeQuality cb = null;
    }


    /// <summary>
    /// 装备宝石
    /// </summary>
    class CMsgEquipSystemGC2GMReqGemCombine : UnityFrame.CMsg
    {
        public CMsgEquipSystemGC2GMReqGemCombine(EGemsCombineType type,UInt32 gemTPID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_GEM_COMBINE)
        {
            m_gemTPID = gemTPID;
            m_type = type;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_gemTPID);
            UInt32 type = (UInt32)m_type;
            msgStream.Write(type);
            return true;
        }

         public UInt32 m_gemTPID = 0;
         public EGemsCombineType m_type = EGemsCombineType.EGEMS_COMBINE_TYPE_SINGLE;
    }

    public class CMsgEquipSystemGM2GCAckGemCombine : UnityFrame.CMsg
    {
        public CMsgEquipSystemGM2GCAckGemCombine()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_GEM_COMBINE)
        {
        }
       
        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EGemCombineResult)msgStream.ReadUInt();
            m_newGemTPID = msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgEquipSystemGM2GCAckGemCombine ack)
        {
            if (CMsgEquipSystemGM2GCAckGemCombine.cb == null)
            {
                return;
            }
            CMsgEquipSystemGM2GCAckGemCombine.cb(ack.m_retCode, ack.m_newGemTPID);
        }

        public EGemCombineResult m_retCode = EGemCombineResult.EGEM_COMBINE_RESULT_FAIL;
        public UInt32 m_newGemTPID = 0;
        public static CClientCore.CBMsgEquipSystemGM2GCAckGemCombine cb = null;
    }

    /// <summary>
    /// 获取装备 
    /// </summary>
    class CMsgEquipSystemGC2GMReqNextAddLevelEquip : UnityFrame.CMsg
    {
        public CMsgEquipSystemGC2GMReqNextAddLevelEquip(UInt32 equipID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_NEXT_ADDLEVEL_EQUIPSTATUS)
        {
            m_equipID = equipID;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_equipID);
            return true;
        }

        public UInt32 m_equipID = 0;
    }

    public class CMsgEquipSystemGM2GCAckNextAddLevelEquip : UnityFrame.CMsg
    {
        public CMsgEquipSystemGM2GCAckNextAddLevelEquip()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_NEXT_ADDLEVEL_EQUIPSTATUS)
        {
        }
      
        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EGetNextAddLevelEquipResult)msgStream.ReadUInt();
            if (m_retCode != EGetNextAddLevelEquipResult.EGETEQUIP_RESULT_SUCCESS)
            {
                return true;
            }
            m_equip.SerializeFrom(msgStream);

            return true;
        }

        public static void CallBack(CMsgEquipSystemGM2GCAckNextAddLevelEquip ack)
        {
            if (CMsgEquipSystemGM2GCAckNextAddLevelEquip.cb == null)
            {
                return;
            }
            CMsgEquipSystemGM2GCAckNextAddLevelEquip.cb(ack.m_retCode, ack.m_equip);
        }

        public static CClientCore.CBMsgEquipSystemGM2GCAckNextAddLevelEquip cb = null;
        public EGetNextAddLevelEquipResult m_retCode = EGetNextAddLevelEquipResult.EGETEQUIP_RESULT_FAIL;
        public CEquipItem m_equip = new CEquipItem();

    }

    /// <summary>
    /// 拆解装备 
    /// </summary>
    class CMsgEquipSystemGC2GMReqDisassemblyEquip : UnityFrame.CMsg
    {
        public CMsgEquipSystemGC2GMReqDisassemblyEquip(List<UInt32> equipIDList)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_DISASSEMBLY_EQUIP)
        {
            m_equipIDList = equipIDList;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            UInt32 count = (UInt32)m_equipIDList.Count;
            msgStream.Write(count);
            for (UInt32 i = 0; i < count; ++i)
            {
                UInt32 equipID = (UInt32)m_equipIDList[(int)i];
                msgStream.Write(equipID);
            }
               
            return true;
        }

        List<UInt32> m_equipIDList = new List<UInt32>();
    }

    public class CMsgEquipSystemGM2GCAckDisassemblyEquip: UnityFrame.CMsg
    {
        public CMsgEquipSystemGM2GCAckDisassemblyEquip()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_DISASSEMBLY_EQUIP)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EDisassemblyEquipResult)msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgEquipSystemGM2GCAckDisassemblyEquip ack)
        {
            if (CMsgEquipSystemGM2GCAckDisassemblyEquip.cb == null)
            {
                return;
            }
            CMsgEquipSystemGM2GCAckDisassemblyEquip.cb(ack.m_retCode);
        }

        public static CClientCore.CBMsgEquipSystemGM2GCAckDisassemblyEquip cb = null;
        public EDisassemblyEquipResult m_retCode = EDisassemblyEquipResult.EDISASSEMBLYEQUIP_RESULT_FAIL;
    }

    /// <summary>
    /// 拆解装备结果
    /// </summary>
    class CMsgEquipSystemGC2GMReqGetDisassemblyEquipResult : UnityFrame.CMsg
    {
        public CMsgEquipSystemGC2GMReqGetDisassemblyEquipResult(List<UInt32> equipIDList)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GC2GM_REQ_GET_DISASSEMBLY_EQUIP_RESULT)
        {
            m_equipIDList = equipIDList;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            UInt32 count = (UInt32)m_equipIDList.Count;
            msgStream.Write(count);
            for (UInt32 i = 0; i < count; ++i)
            {
                UInt32 equipID = (UInt32)m_equipIDList[(int)i];
                msgStream.Write(equipID);
            }
               
            return true;
        }

        List<UInt32> m_equipIDList = new List<UInt32>();
    }

    public class CMsgEquipSystemGM2GCAckGetDisassemblyEquipResult : UnityFrame.CMsg
    {
        public CMsgEquipSystemGM2GCAckGetDisassemblyEquipResult()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_EQUIPSYSTEM, CEquipSystemMsgNumID.EMSGNUMID_EQUIPSYSTEM_GM2GC_ACK_GET_DISASSEMBLY_EQUIP_RESULT)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EGetDisassemblyEquipResult)msgStream.ReadUInt();
            if (m_retCode != EGetDisassemblyEquipResult.EGETDISASSEMBLYEQUIP_RESULT_SUCCESS)
            {
                return true;
            }
            UInt32 count = msgStream.ReadUInt();
            for (uint i = 0; i < count; ++i)
            {
                CPrizeItem item = new CPrizeItem();
                item.SerializeFrom(msgStream);
                m_itemList.Add(item);
            }
            return true;
        }

        public static void CallBack(CMsgEquipSystemGM2GCAckGetDisassemblyEquipResult ack)
        {
            if (CMsgEquipSystemGM2GCAckGetDisassemblyEquipResult.cb == null)
            {
                return;
            }
            CMsgEquipSystemGM2GCAckGetDisassemblyEquipResult.cb(ack.m_retCode, ack.m_itemList);
        }

        public static CClientCore.CBMsgEquipSystemGM2GCAckGetDisassemblyEquipResult cb = null;
        public EGetDisassemblyEquipResult m_retCode = EGetDisassemblyEquipResult.EGETDISASSEMBLYEQUIP_RESULT_FAIL;
        public List<CPrizeItem> m_itemList = new List<CPrizeItem>();
    }
}
