using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgActivitySystemGC2GMReqGetAttendenceData : UnityFrame.CMsg
    {
        public CMsgActivitySystemGC2GMReqGetAttendenceData()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_ACTIVITYSYSTEM, CActivitySystemMsgNumID.EMSGNUMID_ACTIVITYSYSTEM_GC2GM_REQ_GET_ATTENDENCE_DATA)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CMsgActivitySystemGC2GMReqSignIn : UnityFrame.CMsg
    {
        public CMsgActivitySystemGC2GMReqSignIn()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_ACTIVITYSYSTEM, CActivitySystemMsgNumID.EMSGNUMID_ACTIVITYSYSTEM_GC2GM_REQ_SGIN_IN)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    class CMsgActivitySystemGC2GMReqDrawCard : UnityFrame.CMsg
    {
        public CMsgActivitySystemGC2GMReqDrawCard(EDrawCardType type, UInt16 count)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_ACTIVITYSYSTEM, CActivitySystemMsgNumID.EMSGNUMID_ACTIVITYSYSTEM_GC2GM_REQ_DRAW_CARD)
        {
            m_type = type;
            m_count = count;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write((byte)m_type);
            msgStream.Write(m_count);
            return true;
        }

        EDrawCardType m_type;
        UInt16 m_count = 0;
    }

    class CMsgActivitySystemGC2GMReqGetDrawCardInfo : UnityFrame.CMsg
    {
        public CMsgActivitySystemGC2GMReqGetDrawCardInfo()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_ACTIVITYSYSTEM, CActivitySystemMsgNumID.EMSGNUMID_ACTIVITYSYSTEM_GC2GM_REQ_GET_DRAW_CARD_INFO)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }


                       
                                           
                       




}
