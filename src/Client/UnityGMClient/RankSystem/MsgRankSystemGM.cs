using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    class CMsgRankSystemGC2GMReqGetRankData : UnityFrame.CMsg
    {
        ERankType m_rankType;

        public CMsgRankSystemGC2GMReqGetRankData(ERankType type)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_RANKSYSTEM, CRankSystemMsgNumID.EMSGNUMID_RANKSYSTEM_GC2GM_REQ_GET_RANK_DATA)
        {
            m_rankType = type;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write((byte)m_rankType);

            return true;
        }
    }

    class CMsgRankSystemGC2CNReqGetRankList : UnityFrame.CMsg
    {
        UInt32 m_rankId;
        bool m_myself;
        Int32 m_param;

        public CMsgRankSystemGC2CNReqGetRankList(UInt32 id, bool isMyself, Int32 param)
            : base(CServerType.SRVTYPE_CENTERSERVER, CFuncType.EFUNCTYPE_RANKSYSTEM, CRankSystemMsgNumID.EMSGNUMID_RANKSYSTEM_GC2CN_REQ_GET_RANK_LIST)
        {
            m_rankId = id;
            m_myself = isMyself;
            m_param = param;

        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            UInt32 id = (UInt32)m_rankId;
            msgStream.Write(id);

            UInt32 type = 1;
            if(m_myself)
                type = 2;
            msgStream.Write(type);

            msgStream.Write(m_param);
            return true;
        }
    }


}
