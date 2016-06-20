using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{

    public class CShopSystemMsgNumID
    {
        public const uint EMSGID_SHOPSYSTEM_GC2GM_REQ_SHOP_OPEN         = 1;
        public const uint EMSGID_SHOPSYSTEM_GM2GC_ACK_SHOP_OPEN         = 2;
        public const uint EMSGID_SHOPSYSTEM_GC2GM_REQ_SHOP_BUY          = 3;
        public const uint EMSGID_SHOPSYSTEM_GM2GC_ACK_SHOP_BUY          = 4;
        public const uint EMSGID_SHOPSYSTEM_GC2GM_REQ_SHOP_REFRESH      = 5;
        public const uint EMSGID_SHOPSYSTEM_GM2GC_ACK_SHOP_REFRESH      = 6;
        public const uint EMSGID_SHOPSYSTEM_GC2GM_REQ_SHOP_PAIDREFRESH  = 7;
        public const uint EMSGID_SHOPSYSTEM_GM2GC_ACK_SHOP_PAIDREFRESH  = 8;
    }

    public enum EShopType
    {
        ESHOPTYPE_PROP  = 1,    // 道具商店
        ESHOPTYPE_PVP   = 2,    // pvp商店
        ESHOPTYPE_DAILY = 3,    // 每日限购
    }

    public enum EShopSystemResult
    {
        ESHOPSYSTEMRESULT_SUCCESS   = 1,    // 成功
        ESHOPSYSTEMRESULT_FAILED    = 2,    // 失败
    }

    // 打开商店
    class CMsgShopSystemGC2GMReqShopOpen : UnityFrame.CMsg
    {
        public CMsgShopSystemGC2GMReqShopOpen(EShopType type)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SHOPSYSTEM, CShopSystemMsgNumID.EMSGID_SHOPSYSTEM_GC2GM_REQ_SHOP_OPEN)
        {
            m_type = type; 
        }

        public EShopType m_type;

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return msgStream.Write((UInt32)m_type);
        }
    }

    // 打开商店返回
    public class CMsgShopSystemGM2GCAckShopOpen : UnityFrame.CMsg
    {
        public CMsgShopSystemGM2GCAckShopOpen()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SHOPSYSTEM, CShopSystemMsgNumID.EMSGID_SHOPSYSTEM_GM2GC_ACK_SHOP_OPEN)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_type = (EShopType)msgStream.ReadUInt();
            m_info.deserialize(msgStream);
            m_refreshTime = msgStream.ReadULong();
            return true;
        }

        public static void CallBack(CMsgShopSystemGM2GCAckShopOpen ack)
        {
            if (CMsgShopSystemGM2GCAckShopOpen.cb == null)
            {
                return;
            }
            CMsgShopSystemGM2GCAckShopOpen.cb(ack.m_type, ack.m_info.info, ack.m_refreshTime);
        }

        public EShopType    m_type = EShopType.ESHOPTYPE_PROP;
        public ShopSystemAllItemsInfo m_info = new ShopSystemAllItemsInfo();
        public UInt64 m_refreshTime = 0;
        public static CClientCore.CBMsgShopSystemGM2GCAckShopOpen cb = null;
    }


    // 购买物品
    class CMsgShopSystemGC2GMReqShopBuy : UnityFrame.CMsg
    {
        public CMsgShopSystemGC2GMReqShopBuy(EShopType type, UInt32 id, UInt32 num)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SHOPSYSTEM, CShopSystemMsgNumID.EMSGID_SHOPSYSTEM_GC2GM_REQ_SHOP_BUY)
        {
            m_type = type;
            m_id = id;
            m_num = num;
        }

        public EShopType m_type;
        public UInt32 m_id;
        public UInt32 m_num;

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write((UInt32)m_type);
            msgStream.Write(m_id);
            msgStream.Write(m_num);
            return true;
        }
    }

    // 购买物品返回
    public class CMsgShopSystemGM2GCAckShopBuy : UnityFrame.CMsg
    {
        public CMsgShopSystemGM2GCAckShopBuy()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SHOPSYSTEM, CShopSystemMsgNumID.EMSGID_SHOPSYSTEM_GM2GC_ACK_SHOP_BUY)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_type = (EShopType)msgStream.ReadUInt();
            m_id = msgStream.ReadInt();
            m_num = msgStream.ReadInt();
            m_result = (EShopSystemResult)msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgShopSystemGM2GCAckShopBuy ack)
        {
            if (CMsgShopSystemGM2GCAckShopBuy.cb == null)
            {
                return;
            }
            CMsgShopSystemGM2GCAckShopBuy.cb(ack.m_type, ack.m_id, ack.m_num, ack.m_result);
        }

        public EShopType m_type = EShopType.ESHOPTYPE_PROP;
        public Int32 m_id;
        public Int32 m_num;
        public EShopSystemResult m_result = EShopSystemResult.ESHOPSYSTEMRESULT_FAILED;
        public static CClientCore.CBMsgShopSystemGM2GCAckShopBuy cb = null;
    }


    // 刷新商店
    class CMsgShopSystemGC2GMReqShopRefresh : UnityFrame.CMsg
    {
        public CMsgShopSystemGC2GMReqShopRefresh(EShopType type)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SHOPSYSTEM, CShopSystemMsgNumID.EMSGID_SHOPSYSTEM_GC2GM_REQ_SHOP_REFRESH)
        {
            m_type = type;
        }

        public EShopType m_type;

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return msgStream.Write((UInt32)m_type);
        }
    }

    // 刷新商店返回
    public class CMsgShopSystemGM2GCAckShopRefresh : UnityFrame.CMsg
    {
        public CMsgShopSystemGM2GCAckShopRefresh()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SHOPSYSTEM, CShopSystemMsgNumID.EMSGID_SHOPSYSTEM_GM2GC_ACK_SHOP_REFRESH)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_type = (EShopType)msgStream.ReadUInt();
            UInt32 size = msgStream.ReadUInt();
            for (UInt32 i = 0; i < size; i++)
            {
                m_ids.Add(msgStream.ReadInt());
                m_nums.Add(msgStream.ReadInt());
            }
            m_result = (EShopSystemResult)msgStream.ReadUInt();
            m_refreshTime = msgStream.ReadULong();
            return true;
        }

        public static void CallBack(CMsgShopSystemGM2GCAckShopRefresh ack)
        {
            if (CMsgShopSystemGM2GCAckShopRefresh.cb == null)
            {
                return;
            }
            CMsgShopSystemGM2GCAckShopRefresh.cb(ack.m_type, ack.m_ids, ack.m_nums, ack.m_result, ack.m_refreshTime);
        }

        public EShopType m_type = EShopType.ESHOPTYPE_PROP;
        public List<Int32> m_ids = new List<Int32>();
        public List<Int32> m_nums = new List<Int32>();
        public EShopSystemResult m_result = EShopSystemResult.ESHOPSYSTEMRESULT_FAILED;
        public UInt64 m_refreshTime = 0;
        public static CClientCore.CBMsgShopSystemGM2GCAckShopRefresh cb = null;
    }


    // 付款刷新商店
    class CMsgShopSystemGC2GMReqShopPaidRefresh : UnityFrame.CMsg
    {
        public CMsgShopSystemGC2GMReqShopPaidRefresh(EShopType type)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SHOPSYSTEM, CShopSystemMsgNumID.EMSGID_SHOPSYSTEM_GC2GM_REQ_SHOP_PAIDREFRESH)
        {
            m_type = type;
        }

        public EShopType m_type;

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return msgStream.Write((UInt32)m_type);
        }
    }

    // 付款刷新商店返回
    public class CMsgShopSystemGM2GCAckShopPaidRefresh : UnityFrame.CMsg
    {
        public CMsgShopSystemGM2GCAckShopPaidRefresh()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SHOPSYSTEM, CShopSystemMsgNumID.EMSGID_SHOPSYSTEM_GM2GC_ACK_SHOP_PAIDREFRESH)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_type = (EShopType)msgStream.ReadUInt();
            UInt32 size = msgStream.ReadUInt();
            for (UInt32 i = 0; i < size; i++)
            {
                m_ids.Add(msgStream.ReadInt());
                m_nums.Add(msgStream.ReadInt());
            }
            m_result = (EShopSystemResult)msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgShopSystemGM2GCAckShopPaidRefresh ack)
        {
            if (CMsgShopSystemGM2GCAckShopPaidRefresh.cb == null)
            {
                return;
            }
            CMsgShopSystemGM2GCAckShopPaidRefresh.cb(ack.m_type, ack.m_ids, ack.m_nums, ack.m_result);
        }

        public EShopType m_type = EShopType.ESHOPTYPE_PROP;
        public List<Int32> m_ids = new List<Int32>();
        public List<Int32> m_nums = new List<Int32>();
        public EShopSystemResult m_result = EShopSystemResult.ESHOPSYSTEMRESULT_FAILED;
        public static CClientCore.CBMsgShopSystemGM2GCAckShopPaidRefresh cb = null;
    }


} // UnityGMClient