using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{

    class CMsgRankSystemGM2GCAckGetRankData : UnityFrame.CMsg
    {
        EGetRankDataResult m_result;
        ERankType m_rankType;
        List<CRankData> m_listRankData = new List<CRankData>();
        static public CClientCore.CBMsgRankSystemGC2GMReqGetRankData s_cb = null;

        public CMsgRankSystemGM2GCAckGetRankData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_RANKSYSTEM, CRankSystemMsgNumID.EMSGNUMID_RANKSYSTEM_GC2GM_ACK_GET_RANK_DATA)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            byte result = msgStream.ReadByte();
            m_result = (EGetRankDataResult)result;
            if (m_result == EGetRankDataResult.EGET_RANK_DATA_RESULT_SUCCESS)
            {
                byte rankType = msgStream.ReadByte();
                m_rankType = (ERankType)rankType;
                UInt16 count = msgStream.ReadUShort();
                for (Int16 i = 0; i < count; ++i )
                {
                    CRankData data = new CRankData();
                    data.SerializeFrom(msgStream);
                    m_listRankData.Add(data);
                }
            }
            
            return true;
        }

        static public void CallBack(CMsgRankSystemGM2GCAckGetRankData msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb(msg.m_result, msg.m_rankType, msg.m_listRankData);
                }
            }
        }
    }


    class CMsgRankSystemGM2GCAckGetRankList : UnityFrame.CMsg
    {
        UInt32 m_id;
        bool m_myself = false;
        List<CRankCell> m_rankList = new List<CRankCell>();
        static public CClientCore.CBMsgRankSystemGC2GMReqGetRankList s_cb = null;

        public CMsgRankSystemGM2GCAckGetRankList()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_RANKSYSTEM, CRankSystemMsgNumID.EMSGNUMID_RANKSYSTEM_CN2GC_ACK_GET_RANK_LIST)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_id = (UInt32)msgStream.ReadUInt();
            UInt32 type = msgStream.ReadUInt();
            if (2 == type)
                m_myself = true;

            UInt32 count = msgStream.ReadUInt();
            for (UInt32 i = 0; i < count; ++i)
            {
                CRankCell data = new CRankCell();
                data.SerializeFrom(msgStream);
                m_rankList.Add(data);
            }
            return true;
        }

        static public void CallBack(CMsgRankSystemGM2GCAckGetRankList msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb(msg.m_id, msg.m_myself, msg.m_rankList);
                }
            }
        }
    }

}
