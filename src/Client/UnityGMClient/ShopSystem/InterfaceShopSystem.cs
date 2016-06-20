using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{

    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {

        public delegate void CBMsgShopSystemGM2GCAckShopOpen(EShopType type, List<ShopSystemItemInfo> itemInfo, UInt64 refreshTime);

        public bool SendMsgShopSystemGC2GMReqShopOpen(EShopType type, CBMsgShopSystemGM2GCAckShopOpen cb)
        {
            CMsgShopSystemGC2GMReqShopOpen req = new CMsgShopSystemGC2GMReqShopOpen(type);

            CMsgShopSystemGM2GCAckShopOpen.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }


        public delegate void CBMsgShopSystemGM2GCAckShopBuy(EShopType type, Int32 id, Int32 num, EShopSystemResult result);

        public bool SendMsgShopSystemGC2GMReqShopBuy(EShopType type,  UInt32 id, UInt32 num, CBMsgShopSystemGM2GCAckShopBuy cb)
        {
            CMsgShopSystemGC2GMReqShopBuy req = new CMsgShopSystemGC2GMReqShopBuy(type, id, num);

            CMsgShopSystemGM2GCAckShopBuy.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }


        public delegate void CBMsgShopSystemGM2GCAckShopRefresh(EShopType type, List<Int32> ids, List<Int32> nums, EShopSystemResult result, UInt64 refreshTime);

        public bool SendMsgShopSystemGC2GMReqShopRefresh(EShopType type, CBMsgShopSystemGM2GCAckShopRefresh cb)
        {
            CMsgShopSystemGC2GMReqShopRefresh req = new CMsgShopSystemGC2GMReqShopRefresh(type);

            CMsgShopSystemGM2GCAckShopRefresh.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }


        public delegate void CBMsgShopSystemGM2GCAckShopPaidRefresh(EShopType type, List<Int32> ids, List<Int32> nums, EShopSystemResult result);

        public bool SendMsgShopSystemGC2GMReqShopPaidRefresh(EShopType type, CBMsgShopSystemGM2GCAckShopPaidRefresh cb)
        {
            CMsgShopSystemGC2GMReqShopPaidRefresh req = new CMsgShopSystemGC2GMReqShopPaidRefresh(type);

            CMsgShopSystemGM2GCAckShopPaidRefresh.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


        public delegate void CBMsgShopSystemGM2GCAckOpenCard(UInt32 fun_type, UInt32 glod1_free, UInt32 gold1_next_cost, UInt64 gold1_next_secs, UInt32 gold10_next_cost,
            UInt32 diamond1_free, UInt32 diamond1_next_cost, UInt64 diamond1_next_secs, UInt32 diamond10_next_cost);

        public bool SendMsgShopSystemGC2GMReqOpenCard(UInt32 fun_type, CBMsgShopSystemGM2GCAckOpenCard cb)
        {
            CMsgShopSystemGC2GMReqOpenCard req = new CMsgShopSystemGC2GMReqOpenCard();
            req.fun_type = fun_type;

            CMsgShopSystemGM2GCAckOpenCard.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }




        public delegate void CBMsgShopSystemGM2GCAckEventState(UInt32 update_typ, UInt32 triggered,
            UInt32 item_id, List<UInt32> event_names);

        public bool SendMsgShopSystemGC2GMReqEventState(CBMsgShopSystemGM2GCAckEventState cb)
        {
            CMsgShopSystemGC2GMReqEventState req = new CMsgShopSystemGC2GMReqEventState();

            CMsgShopSystemGM2GCAckEventState.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }


        public delegate void CBMsgShopSystemGM2GCAckClick(UInt32 fun_type, UInt32 cost_type, UInt32 result, List<UInt32> item_ids, List<UInt32> item_nums);

        public bool SendMsgShopSystemGC2GMReqClick(UInt32 fun_type, UInt32 cost_type, CBMsgShopSystemGM2GCAckClick cb)
        {
            CMsgShopSystemGC2GMReqClick req = new CMsgShopSystemGC2GMReqClick();

            req.fun_type = fun_type;
            req.cost_type = cost_type;
            CMsgShopSystemGM2GCAckClick.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }


    } // CClientCore

} // UnityGMClient
