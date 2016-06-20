using System;
using System.IO;
using System.Collections.Generic;

namespace UnityGMClient
{
    public partial class CMsgPrizeSystemGM2GCAckState : UnityFrame.CMsg
    {
        public static CClientCore.CBMsgPrizeSystemGM2GCAckState s_cb = null;

        static public void CallBack(CMsgPrizeSystemGM2GCAckState msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb(msg.states);
                }
            }
        }
    }

    public partial class CMsgPrizeSystemGM2GCAck : UnityFrame.CMsg
    {
        public static CClientCore.CBMsgPrizeSystemGM2GCAck s_cb = null;

        static public void CallBack(CMsgPrizeSystemGM2GCAck msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb(msg.vip, msg.result);
                }
            }
        }

    }

    public partial class CMsgPrizeSystemGM2GCNtfCharge : UnityFrame.CMsg
    {
        public static CClientCore.CBMsgPrizeSystemGM2GCNtfCharge s_cb = null;

        static public void CallBack(CMsgPrizeSystemGM2GCNtfCharge msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb(msg.id, msg.time);
                }
            }
        }

    }


    public partial class CMsgPrizeSystemGM2GCAckTime : UnityFrame.CMsg
    {
        public static CClientCore.CBMsgPrizeSystemGM2GCAckTime s_cb = null;

        static public void CallBack(CMsgPrizeSystemGM2GCAckTime msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb(msg.time);
                }
            }
        }

    }


    public partial class CMsgPrizeSystemGM2GCAckChargeInfo : UnityFrame.CMsg
    {
        public static CClientCore.CBMsgPrizeSystemGM2GCAckChargeInfo s_cb = null;

        static public void CallBack(CMsgPrizeSystemGM2GCAckChargeInfo msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb(msg.info);
                }
            }
        }

    }


}