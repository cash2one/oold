using System;
using System.IO;
using System.Collections.Generic;

namespace UnityGMClient
{
    public partial class CMsgShopSystemGM2GCAckOpenCard : UnityFrame.CMsg
    {
        public static CClientCore.CBMsgShopSystemGM2GCAckOpenCard s_cb = null;

        static public void CallBack(CMsgShopSystemGM2GCAckOpenCard msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb(msg.fun_type, msg.glod1_free, msg.gold1_next_cost, msg.gold1_next_secs, msg.gold10_next_cost,
                        msg.diamond1_free, msg.diamond1_next_cost, msg.diamond1_next_secs, msg.diamond10_next_cost);
                }
            }
        }
    }



    public partial class CMsgShopSystemGM2GCAckEventState : UnityFrame.CMsg
    {
        public static CClientCore.CBMsgShopSystemGM2GCAckEventState s_cb = null;

        static public void CallBack(CMsgShopSystemGM2GCAckEventState msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb(msg.update_type, msg.triggered, msg.item_id, msg.event_names);
                }
            }
        }

    }



    public partial class CMsgShopSystemGM2GCAckClick : UnityFrame.CMsg
    {
        public static CClientCore.CBMsgShopSystemGM2GCAckClick s_cb = null;

        static public void CallBack(CMsgShopSystemGM2GCAckClick msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb(msg.fun_type, msg.cost_type, msg.result, msg.item_ids, msg.item_nums);
                }
            }
        }

    }


}