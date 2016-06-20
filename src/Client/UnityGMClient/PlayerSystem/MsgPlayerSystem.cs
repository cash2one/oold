using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CPlayerSystemMsgNumID
    {
        //public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_TEST = 1;
        //public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_TEST = 2;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_INIT_ROLELIST = 3;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_INIT_ROLELIST = 4;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_CREATE_ROLE = 5;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_CREATE_ROLE = 6;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_SELECT_ROLE = 7;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_SELECT_ROLE = 8;

        //public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_ENTER_SCENE = 9;
        //public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_ENTER_SCENE = 10;

        //public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_QUIT_SCENE = 11;
        //public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_QUIT_SCENE = 12;

        //public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_UPDATE_ATTRIBUTE = 13;
        //public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_UPDATE_ATTRIBUTE = 14;

        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_INIT_ROLEDATA = 15;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_GETBAGDATA = 16;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_SOLDITEM_PACKAGEDATA = 17;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_SOLDITEM_PACKAGEDATA = 18;

        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATE_BAGSIZE = 19;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATEITEM_PACKAGEDATA = 20;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_USEITEM_PACKAGEDATA = 21;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_USEITEM_PACKAGEDATA = 22;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_ROLE_QUIT = 23;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_ROLE_QUIT = 24;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_DELETE_ROLE = 25;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_DELETE_ROLE = 26;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GET_ROLEDATA = 27;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GET_ROLEDATA = 28;

        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATE_UINT32ATTRIBUTE = 32;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATE_UINT64ATTRIBUTE = 34;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_UPDATE_SKILLPOINT = 35;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_UPDATE_SKILLPOINT = 36;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GET_VIPLEVELGIFT= 37;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GET_VIPLEVELGIFT= 38;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_VIPLEVELGIFT_STATUS = 39;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_VIPLEVELGIFT_STATUS = 40;

        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATE_PLAYERVIPSCORE= 41;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATE_ROLE_BATTLEATTRIBUTE = 42;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GETBAGDATA = 43;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GETBAGDATA = 44;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GET_VITALITY = 45;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GET_VITALITY = 46;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_BUY_VITALITY = 47;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_BUY_VITALITY = 48;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GET_BUY_VITALITY_DIAMOND = 49;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GET_BUY_VITALITY_DIAMOND = 50;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_PURCHASE_GOLD = 51;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_PURCHASE_GOLD = 52;

        public const uint EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GET_PURCHASE_GOLD_INFO = 53;
        public const uint EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GET_PURCHASE_GOLD_INFO = 54;



    }

    public class CMsgPlayerSystemGC2GMReqPlayerData : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqPlayerData()
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_INIT_ROLELIST)
        {

        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    public class CMsgPlayerSystemGM2GCAckPlayerData : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckPlayerData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_INIT_ROLELIST)
        {

        }
        public CPlayerData m_playerData = new CPlayerData();
        public UInt32 m_retCode = 0;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            if (m_retCode != (UInt32)EInitRoleListResult.EINITROLELIST_RESUlT_SUCCESS)
            {
                return true;
            }
            return m_playerData.SerializeFrom(msgStream);
        }
        public static CClientCore.CBMsgPlayerSystemGM2GCAckPlayerData cb = null;
        public static void CallBack(CMsgPlayerSystemGM2GCAckPlayerData ack)
        {
            if (CMsgPlayerSystemGM2GCAckPlayerData.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCAckPlayerData.cb((EInitRoleListResult)ack.m_retCode, ack.m_playerData);
        }
    }

    class CMsgPlayerSystemGC2GMReqCreateRole : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqCreateRole(string a_roleName, UInt32 a_roleType)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_CREATE_ROLE)
        {
            m_roleName = a_roleName;
            m_roleType = a_roleType;
        }
        public string m_roleName = "";
        public UInt32 m_roleType = 0;

        //把数据序列化到msgBuffer中
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_roleType);
            msgStream.Write(m_roleName);
            return true;
        }
    }

    class CMsgPlayerSystemGM2GCAckCreateRole : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckCreateRole()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_CREATE_ROLE)
        {

        }
        public UInt32 m_retCode = 0;
        public UInt32 m_currentRoleIndex = 0;
        public UInt32 m_SceneTypeID = 0;
        public UnityGMClient.CRole m_role = new CRole();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            if (m_retCode != (UInt32)ECreateRoleResult.ECREATEROLE_RESUlT_SUCCESS)
            {
                return true;
            }
            m_currentRoleIndex = msgStream.ReadUInt();
            m_role.SerializeFrom(msgStream);
            return true;
        }
        public static CClientCore.CBMsgPlayerSystemGM2GCAckCreateRole cb = null;
        public static void CallBack(CMsgPlayerSystemGM2GCAckCreateRole ack)
        {
            if (CMsgPlayerSystemGM2GCAckCreateRole.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCAckCreateRole.cb((ECreateRoleResult)ack.m_retCode, ack.m_currentRoleIndex, ack.m_role);
        }
    }


    class CMsgPlayerSystemGC2GMReqGetVipLevelGift: UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqGetVipLevelGift(UInt32 a_vipLevel)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GET_VIPLEVELGIFT)
        {
            m_vipLevel = a_vipLevel;
        }
        public UInt32 m_vipLevel = 0;

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_vipLevel);
            return true;
        }
    }
        class CMsgPlayerSystemGM2GCAckGetVipLevelGift : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckGetVipLevelGift()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GET_VIPLEVELGIFT)
        {
        }
        public UInt32 m_retCode = 0;
        public UInt32 m_vipLevel = 0;
        public Int32 m_nextVipLevel = -1;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            if (m_retCode != (UInt32)ECreateRoleResult.ECREATEROLE_RESUlT_SUCCESS)
            {
                return true;
            }
            m_vipLevel = msgStream.ReadUInt();
            m_nextVipLevel = msgStream.ReadInt();
            return true;
        }
        public static CClientCore.CBMsgPlayerSystemGM2GCAckGetVipLevelGift cb = null;
        public static void CallBack(CMsgPlayerSystemGM2GCAckGetVipLevelGift ack)
        {
            if (CMsgPlayerSystemGM2GCAckGetVipLevelGift.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCAckGetVipLevelGift.cb((EGetVipLevelGiftResult)ack.m_retCode, ack.m_vipLevel, ack.m_nextVipLevel);
        }
    }

    class CMsgPlayerSystemGM2GCAckVipLevelGiftStatus: UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckVipLevelGiftStatus()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_VIPLEVELGIFT_STATUS)
        {
        }
        public UInt32 m_retCode = 0;
        public UInt32 m_vipLevel = 0;
        public UInt32 m_getStatus = (uint)EGetVipGiftStatus.EGETVIPGIFT_STATUS_NO;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            if (m_retCode != (UInt32)EVipLevelGiftStatusResult.EVIPLEVEL_GIFT_STATUS_RESULT_SUCCESS)
            {
                return true;
            }
            m_vipLevel = msgStream.ReadUInt();
            m_getStatus = msgStream.ReadUInt();
            return true;
        }
        public static CClientCore.CBMsgPlayerSystemGM2GCAckVipLevelGiftStatus cb = null;
        public static void CallBack(CMsgPlayerSystemGM2GCAckVipLevelGiftStatus ack)
        {
            if (CMsgPlayerSystemGM2GCAckVipLevelGiftStatus.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCAckVipLevelGiftStatus.cb((EVipLevelGiftStatusResult)ack.m_retCode, ack.m_vipLevel, (EGetVipGiftStatus)ack.m_getStatus);
        }
    }

    class CMsgPlayerSystemGC2GMReqVipLevelGiftStatus : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqVipLevelGiftStatus(UInt32 a_vipLevel)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_VIPLEVELGIFT_STATUS)
        {
            m_vipLevel = a_vipLevel;
        }
        public UInt32 m_vipLevel = 0;

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_vipLevel);
            return true;
        }
    }

    class CMsgPlayerSystemGC2GMReqSelectRole : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqSelectRole(UInt32 a_roleIndex)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_SELECT_ROLE)
        {
            m_roleIndex = a_roleIndex;
        }
        public UInt32 m_roleIndex = 0;

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_roleIndex);
            return true;
        }
    }

    class CMsgPlayerSystemGM2GCAckSelectRole : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckSelectRole()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_SELECT_ROLE)
        {
        }
        public UInt32 m_retCode = 0;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            return true;
        }

        public static CClientCore.CBMsgPlayerSystemGM2GCAckSelectRole cb = null;
        public static void CallBack(CMsgPlayerSystemGM2GCAckSelectRole ack)
        {
            if (CMsgPlayerSystemGM2GCAckSelectRole.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCAckSelectRole.cb((ESelectRoleResult)ack.m_retCode);
        }
    }

    class CMsgPlayerSystemGM2GCNtfInitRoleData : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCNtfInitRoleData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_INIT_ROLEDATA)
        {
        }
        public UInt32 m_retCode = 0;
        public UInt32 m_currentRoleIndex = 0;
        public UInt32 m_sceneTypeID = 0;
        public UnityGMClient.CRole m_role = new CRole();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            if (m_retCode != (UInt32)EInitRoleDataResult.EINITROLEDATA_RESUlT_SUCCESS)
            {
                return true;
            }
            m_currentRoleIndex = msgStream.ReadUInt();
            m_sceneTypeID = msgStream.ReadUInt();
            if (m_retCode == (UInt32)EInitRoleDataResult.EINITROLEDATA_RESUlT_SUCCESS)
            {
                m_role.SerializeFrom(msgStream);
            }
            return true;
        }

        public static CClientCore.CBMsgPlayerSystemGM2GCNtfInitRoleData cb = null;
        public static void CallBack(CMsgPlayerSystemGM2GCNtfInitRoleData ack)
        {
            if (CMsgPlayerSystemGM2GCNtfInitRoleData.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCNtfInitRoleData.cb((EInitRoleDataResult)ack.m_retCode, ack.m_currentRoleIndex, ack.m_sceneTypeID, ack.m_role);
        }
    }

    class CMsgPlayerSystemGM2GCNtfUpdateRoleBattleAttribute : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCNtfUpdateRoleBattleAttribute()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATE_ROLE_BATTLEATTRIBUTE)
        {
        }

        public CBattleAttribute m_battleAttr = new CBattleAttribute();
        public UInt32 m_combat = 0;
        public UInt32 m_historyMaxCombatPower = 0;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_battleAttr.SerializeFrom(msgStream);
            m_combat = msgStream.ReadUInt();
            m_historyMaxCombatPower = msgStream.ReadUInt();
            return true;
        }

        public static CClientCore.CBMsgPlayerSystemGM2GCNtfUpdateRoleBattleAttribute cb = null;
        public static void CallBack(CMsgPlayerSystemGM2GCNtfUpdateRoleBattleAttribute ntf)
        {
            if (CMsgPlayerSystemGM2GCNtfUpdateRoleBattleAttribute.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCNtfUpdateRoleBattleAttribute.cb(ntf.m_battleAttr, ntf.m_combat, ntf.m_historyMaxCombatPower);
        }
    }

    class CMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATE_UINT32ATTRIBUTE)
        {
        }

        public UInt32 m_retCode = 0;
        public UInt32 m_attributeIndex = 0;
        public UInt32 m_value = 0;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            m_attributeIndex = msgStream.ReadUInt();
            m_value = msgStream.ReadUInt();

            return true;
        }

        public static CClientCore.CBMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute cb = null;
        public static void CallBack(CMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute ack)
        {
            if (CMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute.cb((EUpdateAttributeResult)ack.m_retCode, ack.m_attributeIndex, ack.m_value);
        }
    }

    class CMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATE_UINT64ATTRIBUTE)
        {
        }

        public UInt32 m_retCode = 0;
        public UInt32 m_attributeIndex = 0;
        public UInt64 m_value = 0;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            m_attributeIndex = msgStream.ReadUInt();
            m_value = msgStream.ReadULong();

            return true;
        }
        public static CClientCore.CBMsgPlayerSystemGM2GCAckUpdateUInt64Attribute cb = null;
        public static void CallBack(CMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute ack)
        {
            if (CMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute.cb((EUpdateAttributeResult)ack.m_retCode, ack.m_attributeIndex, ack.m_value);
        }
    }

    public class CMsgPlayerSystemGC2GMReqGetBagData : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqGetBagData()
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GETBAGDATA)
        {

        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_type);
            return true;
        }

        public UInt32 m_type = 0;
    }


    /// <summary>
    /// 初始化背包数据
    /// </summary>
    class CMsgPlayerSystemGM2GCNtfBagData : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCNtfBagData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_GETBAGDATA)
        {
        }

        public CBagData m_bagData = new CBagData();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_bagData.SerializeFrom(msgStream);

            return true;
        }
        public static CClientCore.CBMsgPlayerSystemGM2GCNtfBagData cb = null;
        public static void CallBack(CMsgPlayerSystemGM2GCNtfBagData ack)
        {
            if (CMsgPlayerSystemGM2GCNtfBagData.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCNtfBagData.cb(ack.m_bagData);
        }
    }

    /// <summary>
    /// 初始化背包数据
    /// </summary>
    class CMsgPlayerSystemGM2GCAckGetBagData : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckGetBagData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GETBAGDATA)
        {
        }

        public UInt32 m_retCode = 0;
        public CBagData m_bagData = new CBagData();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            if (m_retCode != (UInt32)EGetBagDataResult.EINITPACKAGEDATA_RESUlT_SUCCESS)
            {
                return true;
            }
            m_bagData.SerializeFrom(msgStream);

            return true;
        }
        public static CClientCore.CBMsgPlayerSystemGM2GCAckGetBagData cb = null;
        public static void CallBack(CMsgPlayerSystemGM2GCAckGetBagData ack)
        {
            if (CMsgPlayerSystemGM2GCAckGetBagData.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCAckGetBagData.cb((EGetBagDataResult)ack.m_retCode, ack.m_bagData);
        }
    }

    class CMsgPlayerSystemGC2GMReqSoldBagItemData : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqSoldBagItemData(EItemType a_type, UInt32 a_itemIndex, UInt32 a_itemCount)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_SOLDITEM_PACKAGEDATA)
        {
            m_type = a_type;
            m_itemIndex = a_itemIndex;
            m_itemCount = a_itemCount;
        }

        public UInt32 m_itemCount = 0;
        public UInt32 m_itemIndex = 0;
        UnityGMClient.EItemType m_type = EItemType.EITEM_TP_IVALID;

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write((int)m_type);
            msgStream.Write(m_itemIndex);
            msgStream.Write(m_itemCount);

            return true;
        }
    }

    /// <summary>
    /// 背包数据
    /// </summary>
    class CMsgPlayerSystemGM2GCAckSoldBagItemData : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckSoldBagItemData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_SOLDITEM_PACKAGEDATA)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgPlayerSystemGM2GCAckSoldBagItemData ack)
        {
            if (CMsgPlayerSystemGM2GCAckSoldBagItemData.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCAckSoldBagItemData.cb((ESoldBagItemDataResult)ack.m_retCode);
        }

        public UInt32 m_retCode = 0;
        public static CClientCore.CBMsgPlayerSystemGM2GCAckSoldBagItemData cb = null;
    }

    class CMsgPlayerSystemGC2GMReqUseBagItemData : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqUseBagItemData(EItemType a_type, UInt32 a_itemIndex)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_USEITEM_PACKAGEDATA)
        {
            m_type = a_type;
            m_itemIndex = a_itemIndex;
        }

        public UInt32 m_itemIndex = 0;
        UnityGMClient.EItemType m_type = EItemType.EITEM_TP_IVALID;

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write((int)m_type);
            msgStream.Write(m_itemIndex);
            return true;
        }
    }

    class CMsgPlayerSystemGM2GCAckUseBagItemData : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckUseBagItemData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_USEITEM_PACKAGEDATA)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgPlayerSystemGM2GCAckUseBagItemData ack)
        {
            if (CMsgPlayerSystemGM2GCAckUseBagItemData.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCAckUseBagItemData.cb((EUseBagItemDataResult)ack.m_retCode);
        }

        public UInt32 m_retCode = 0;
        public static CClientCore.CBMsgPlayerSystemGM2GCAckUseBagItemData cb = null;
    }


    class CMsgPlayerSystemGC2GMReqUpdateBagItemData : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqUpdateBagItemData(EItemType a_type, UInt32 a_itemIndex, UInt32 a_itemCount)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_SOLDITEM_PACKAGEDATA)
        {
            m_type = a_type;
            m_itemIndex = a_itemIndex;
            m_itemCount = a_itemCount;
        }

        public UInt32 m_itemCount = 0;
        public UInt32 m_itemIndex = 0;
        UnityGMClient.EItemType m_type = EItemType.EITEM_TP_IVALID;

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write((int)m_type);
            msgStream.Write(m_itemIndex);
            msgStream.Write(m_itemCount);
            return true;
        }
    }

    class CMsgPlayerSystemGM2GCNtfUpdateBagItemData : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCNtfUpdateBagItemData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATEITEM_PACKAGEDATA)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            m_Item.SerializeFrom(msgStream);
            return true;
        }

        public static void CallBack(CMsgPlayerSystemGM2GCNtfUpdateBagItemData ack)
        {
            if (CMsgPlayerSystemGM2GCNtfUpdateBagItemData.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCNtfUpdateBagItemData.cb((EUpdateBagItemDataResult)ack.m_retCode, ack.m_Item);
        }

        public UInt32 m_retCode = 0;
        public CItem m_Item = new CItem();
        public static CClientCore.CBMsgPlayerSystemGM2GCNtfUpdateBagItemData cb = null;
    }

    class CMsgPlayerSystemGM2GCNtfUpdateBagSize : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCNtfUpdateBagSize()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATE_BAGSIZE)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_bagSize = msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgPlayerSystemGM2GCNtfUpdateBagSize ack)
        {
            if (CMsgPlayerSystemGM2GCNtfUpdateBagSize.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCNtfUpdateBagSize.cb(ack.m_bagSize);
        }

        public UInt32 m_bagSize = 0;
        public static CClientCore.CBMsgPlayerSystemGM2GCNtfUpdateBagSize cb = null;
    }

     
    class CMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATE_PLAYERVIPSCORE)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_value = msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore ack)
        {
            if (CMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore.cb(ack.m_value);
        }

        public UInt32 m_value = 0;
        public static CClientCore.CBMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore cb = null;
    }

    

    class CMsgPlayerSystemGC2GMReqUpdateSkillPoint : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqUpdateSkillPoint()
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_UPDATE_SKILLPOINT)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    class CMsgPlayerSystemGM2GCAckUpdateSkillPoint : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckUpdateSkillPoint()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_UPDATE_SKILLPOINT)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            m_skillPoint = msgStream.ReadUInt();
            m_updateTime = msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgPlayerSystemGM2GCAckUpdateSkillPoint ack)
        {
            if (CMsgPlayerSystemGM2GCAckUpdateSkillPoint.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCAckUpdateSkillPoint.cb((EUpdateSkillPointResult)ack.m_retCode, ack.m_skillPoint, ack.m_updateTime);
        }

        public UInt32 m_retCode = 0;
        public UInt32 m_skillPoint = 0;
        public UInt32 m_updateTime = 0;
        public static CClientCore.CBMsgPlayerSystemGM2GCAckUpdateSkillPoint cb = null;
    }

    class CMsgPlayerSystemGC2GMReqGetVitality : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqGetVitality()
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GET_VITALITY)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    class CMsgPlayerSystemGM2GCAckGetVitality : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckGetVitality()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GET_VITALITY)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            m_vitality = msgStream.ReadUInt();
            m_updateTime = msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgPlayerSystemGM2GCAckGetVitality ack)
        {
            if (CMsgPlayerSystemGM2GCAckGetVitality.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCAckGetVitality.cb((EGetVitalityResult)ack.m_retCode, ack.m_vitality, ack.m_updateTime);
        }

        public UInt32 m_retCode = 0;
        public UInt32 m_vitality = 0;
        public UInt32 m_updateTime = 0;
        public static CClientCore.CBMsgPlayerSystemGM2GCAckGetVitality cb = null;
    }


    class CMsgPlayerSystemGC2GMReqBuyVitality : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqBuyVitality()
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_BUY_VITALITY)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    class CMsgPlayerSystemGM2GCAckBuyVitality : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckBuyVitality()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_BUY_VITALITY)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            m_vitality = msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgPlayerSystemGM2GCAckBuyVitality ack)
        {
            if (CMsgPlayerSystemGM2GCAckBuyVitality.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCAckBuyVitality.cb((EBuyVitalityResult)ack.m_retCode, ack.m_vitality);
        }

        public UInt32 m_retCode = 0;
        public UInt32 m_vitality = 0;
        public static CClientCore.CBMsgPlayerSystemGM2GCAckBuyVitality cb = null;
    }


    class CMsgPlayerSystemGC2GMReqGetBuyVitalityDiamond : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqGetBuyVitalityDiamond()
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GET_BUY_VITALITY_DIAMOND)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    class CMsgPlayerSystemGM2GCAckGetBuyVitalityDiamond : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckGetBuyVitalityDiamond()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GET_BUY_VITALITY_DIAMOND)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            if (m_retCode != (uint)UnityGMClient.EGetNeedDiamondResult.EGETNEEDDIAMOND_RESULT_SUCCESS)
            {
                return true;
            }
            m_vitalityData.SerializeFrom(msgStream);

            return true;
        }

        public static void CallBack(CMsgPlayerSystemGM2GCAckGetBuyVitalityDiamond ack)
        {
            if (CMsgPlayerSystemGM2GCAckGetBuyVitalityDiamond.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCAckGetBuyVitalityDiamond.cb((EGetNeedDiamondResult)ack.m_retCode, ack.m_vitalityData);
        }

        public UInt32 m_retCode = 0;
        public CVitalityData m_vitalityData = new CVitalityData();
        public static CClientCore.CBMsgPlayerSystemGM2GCAckGetBuyVitalityDiamond cb = null;
    }

    class CMsgPlayerSystemGC2GMReqRoleQuit : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqRoleQuit(UInt32 a_roleIndex)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_ROLE_QUIT)
        {
            m_roleIndex = a_roleIndex;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_roleIndex);
            return true;
        }
        public UInt32 m_roleIndex = 0;
    }
    class CMsgPlayerSystemGM2GCAckRoleQuit : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckRoleQuit()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_ROLE_QUIT)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgPlayerSystemGM2GCAckRoleQuit ack)
        {
            if (CMsgPlayerSystemGM2GCAckRoleQuit.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCAckRoleQuit.cb((ERoleQuitResult)ack.m_retCode);
        }

        public UInt32 m_retCode = 0;
        public static CClientCore.CBMsgPlayerSystemGM2GCAckRoleQuit cb = null;
    }


    class CMsgPlayerSystemGC2GMReqDeleteRole : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqDeleteRole(UInt32 a_roleIndex)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_DELETE_ROLE)
        {
            m_roleIndex = a_roleIndex;
        }
        public UInt32 m_roleIndex = 0;

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_roleIndex);
            return true;
        }
    }

    class CMsgPlayerSystemGM2GCAckDeleteRole : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckDeleteRole()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_DELETE_ROLE)
        {
        }
        public UInt32 m_retCode = 0;
        public UInt32 m_roleIndex = 0;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            m_roleIndex = msgStream.ReadUInt();
            return true;
        }

        public static CClientCore.CBMsgPlayerSystemGM2GCAckDeleteRole cb = null;
        public static void CallBack(CMsgPlayerSystemGM2GCAckDeleteRole ack)
        {
            if (CMsgPlayerSystemGM2GCAckDeleteRole.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCAckDeleteRole.cb((EDeleteRoleResult)ack.m_retCode, ack.m_roleIndex);
        }
    }

    public class CMsgPlayerSystemGC2GMReqGetRoleData : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqGetRoleData(SRoleKey a_roleKey)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GET_ROLEDATA)
        {
            m_roleKey = a_roleKey;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_roleKey);
            return true;
        }

        public SRoleKey m_roleKey = new SRoleKey();
    }

    public class CMsgPlayerSystemGM2GCAckGetRoleData : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckGetRoleData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GET_ROLEDATA)
        {
        }
        public UInt32 m_retCode = 0;
        public CRole m_roleData = new CRole();

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = msgStream.ReadUInt();
            if (m_retCode != (uint)UnityGMClient.EGetRoleDataResult.EGETROLEDATA_RESUlT_SUCCESS)
            {
                return true;
            }
            m_roleData.SerializeFrom(msgStream);
            return true;
        }

        public static CClientCore.CBMsgPlayerSystemGM2GCAckGetRoleData cb = null;
        public static void CallBack(CMsgPlayerSystemGM2GCAckGetRoleData ack)
        {
            if (CMsgPlayerSystemGM2GCAckGetRoleData.cb == null)
            {
                return;
            }
            CMsgPlayerSystemGM2GCAckGetRoleData.cb((EGetRoleDataResult)ack.m_retCode, ack.m_roleData);
        }
    }


    class CMsgPlayerSystemGC2GMReqPurchaseGold : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqPurchaseGold()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_PURCHASE_GOLD)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    class CMsgPlayerSystemGM2GCAckPurchaseGold : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckPurchaseGold()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_PURCHASE_GOLD)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EPurchaseGoldResult)msgStream.ReadByte();
            m_remaindTimes = msgStream.ReadUInt();
            m_maxTimes = msgStream.ReadUInt();

            return true;
        }

        public EPurchaseGoldResult m_result;
        public UInt32 m_remaindTimes;
        public UInt32 m_maxTimes;

        public static CClientCore.CBMsgPlayerSystemGM2GCAckPurchaseGold s_cb = null;
        public static void CallBack(CMsgPlayerSystemGM2GCAckPurchaseGold ack)
        {
            if (CMsgPlayerSystemGM2GCAckPurchaseGold.s_cb != null)
            {
                CMsgPlayerSystemGM2GCAckPurchaseGold.s_cb(ack.m_result, ack.m_remaindTimes, ack.m_maxTimes);
            }
        }
    }

    class CMsgPlayerSystemGC2GMReqGetPurchaseGoldInfo : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGC2GMReqGetPurchaseGoldInfo()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GET_PURCHASE_GOLD_INFO)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }


    class CMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo : UnityFrame.CMsg
    {
        public CMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PLAYERSYSTEM, CPlayerSystemMsgNumID.EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GET_PURCHASE_GOLD_INFO)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = (EGetPurchaseGoldInfoResult)msgStream.ReadByte();
            m_remainTimes = msgStream.ReadUInt();
            m_maxTimes = msgStream.ReadUInt();

            return true;
        }

        public EGetPurchaseGoldInfoResult m_result;
        public UInt32 m_remainTimes;
        public UInt32 m_maxTimes;

        public static CClientCore.CBMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo s_cb = null;
        public static void CallBack(CMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo ack)
        {
            if (CMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo.s_cb != null)
            {
                CMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo.s_cb(ack.m_result, ack.m_remainTimes, ack.m_maxTimes);
            }
        }
    }


                                  
                       

                                  

                       

}
