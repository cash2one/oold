using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CAchieveSystemMsgNumID
    {
        public const uint EMSGNUMID_ACHIEVESYSTEM_GC2GM_REQ_GET_ACHIEVE_LIST = 1;
        public const uint EMSGNUMID_ACHIEVESYSTEM_GM2GC_ACK_GET_ACHIEVE_LIST = 2;

	    public const uint EMSGNUMID_ACHIEVESYSTEM_GC2GM_REQ_GET_ACHIEVE_PRIZE = 3;
        public const uint EMSGNUMID_ACHIEVESYSTEM_GM2GC_ACK_GET_ACHIEVE_PRIZE = 4;

        public const uint EMSGNUMID_ACHIEVESYSTEM_GC2GM_REQ_SAVE_ACHIEVE_DATA = 5;
        public const uint EMSGNUMID_ACHIEVESYSTEM_GM2GC_ACK_SAVE_ACHIEVE_DATA = 6;

        public const uint EMSGNUMID_ACHIEVESYSTEM_GM2GC_NTF_ACHIEVE_FINISHED = 7;
    }

    class CMsgAchieveSystemGC2GMReqGetAchieveList: UnityFrame.CMsg
    {
        public CMsgAchieveSystemGC2GMReqGetAchieveList(EAchieveType a_achieveType)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_ACHIEVESYSTEM, CAchieveSystemMsgNumID.EMSGNUMID_ACHIEVESYSTEM_GC2GM_REQ_GET_ACHIEVE_LIST)
        {
            m_achieveType = a_achieveType;
        }
        EAchieveType m_achieveType;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write((UInt32)m_achieveType);
            return true;
        }
    }

    public class CMsgAchieveSystemGM2GCAckGetAchieveList : UnityFrame.CMsg
    {
        public CMsgAchieveSystemGM2GCAckGetAchieveList()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_ACHIEVESYSTEM, CAchieveSystemMsgNumID.EMSGNUMID_ACHIEVESYSTEM_GM2GC_ACK_GET_ACHIEVE_LIST)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EGetAchieveListResult)msgStream.ReadUInt();
            if (m_retCode == EGetAchieveListResult.EGETACHIEVELIST_RESUlT_FAIL)
            {
                return true;
            }
            m_achieveData.SerializeFrom(msgStream);
            return true;
        }

        public static void CallBack(CMsgAchieveSystemGM2GCAckGetAchieveList ack)
        {
            if (CMsgAchieveSystemGM2GCAckGetAchieveList.cb == null)
            {
                return;
            }
            CMsgAchieveSystemGM2GCAckGetAchieveList.cb(ack.m_retCode,ack.m_achieveData);
        }

        public EGetAchieveListResult m_retCode;
        public EAchieveType m_achieveType = EAchieveType.ACHIEVE_INVALID;
        public CAchieveData m_achieveData = new CAchieveData();
        public static CClientCore.CBMsgAchieveSystemGM2GCAckGetAchieveList cb = null;
    }

    public class CMsgAchieveSystemGM2GCNtfRoleAchieveFinished : UnityFrame.CMsg
    {
        public CMsgAchieveSystemGM2GCNtfRoleAchieveFinished()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_ACHIEVESYSTEM, CAchieveSystemMsgNumID.EMSGNUMID_ACHIEVESYSTEM_GM2GC_NTF_ACHIEVE_FINISHED)
        {
        }
        public UInt32 m_achieveID = 0;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_achieveID = msgStream.ReadUInt();
            return true; 
        }

        public static void CallBack(CMsgAchieveSystemGM2GCNtfRoleAchieveFinished ack)
        {
            if (CMsgAchieveSystemGM2GCNtfRoleAchieveFinished.cb == null)
            {
                return;
            }
            CMsgAchieveSystemGM2GCNtfRoleAchieveFinished.cb(ack.m_achieveID);
        }
        public static CClientCore.CBMsgAchieveSystemGM2GCNtfRoleAchieveFinished cb = null;
    }

    /// <summary>
    /// 获取成就奖励 
    /// </summary>
    class CMsgAchieveSystemGC2GMReqGetAchievePrize : UnityFrame.CMsg
    {
        public CMsgAchieveSystemGC2GMReqGetAchievePrize(UInt32 achieveID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_ACHIEVESYSTEM, CAchieveSystemMsgNumID.EMSGNUMID_ACHIEVESYSTEM_GC2GM_REQ_GET_ACHIEVE_PRIZE)
        {
            m_achieveID = achieveID;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_achieveID);
            return true;
        }

        public UInt32 m_achieveID;
    }

    public class CMsgAchieveSystemGM2GCAckGetAchievePrize : UnityFrame.CMsg
    {
        public CMsgAchieveSystemGM2GCAckGetAchievePrize()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_ACHIEVESYSTEM, CAchieveSystemMsgNumID.EMSGNUMID_ACHIEVESYSTEM_GM2GC_ACK_GET_ACHIEVE_PRIZE)
        {
            m_retCode = EGetAchievePrizeResult.EGETACHIEVEPRIZE_RESUlT_FAIL;
        }
        public EGetAchievePrizeResult m_retCode;
        public UInt32 m_achieveID;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (EGetAchievePrizeResult)msgStream.ReadUInt();
            m_achieveID = msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgAchieveSystemGM2GCAckGetAchievePrize ack)
        {
            if (CMsgAchieveSystemGM2GCAckGetAchievePrize.cb == null)
            {
                return;
            }
            CMsgAchieveSystemGM2GCAckGetAchievePrize.cb(ack.m_retCode,ack.m_achieveID);
        }
        public static CClientCore.CBMsgAchieveSystemGM2GCAckGetAchievePrize cb = null;
    }

    /// <summary>
    /// 数据采集 
    /// </summary>
    class CMsgAchieveSystemGC2GMReqSaveAchieveData : UnityFrame.CMsg
    {
        public CMsgAchieveSystemGC2GMReqSaveAchieveData(UInt32 a_achieveSubType, UInt32 a_achieveData)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_ACHIEVESYSTEM, CAchieveSystemMsgNumID.EMSGNUMID_ACHIEVESYSTEM_GC2GM_REQ_SAVE_ACHIEVE_DATA)
        {
            m_achieveSubType = a_achieveSubType;
            m_achieveData = a_achieveData;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_achieveSubType);
            msgStream.Write(m_achieveData);
            return true;
        }
        public UInt32 m_achieveSubType = 0;
        public UInt32 m_achieveData;
    }

    public class CMsgAchieveSystemGM2GCAckSaveAchieveData : UnityFrame.CMsg
    {
        public CMsgAchieveSystemGM2GCAckSaveAchieveData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_ACHIEVESYSTEM, CAchieveSystemMsgNumID.EMSGNUMID_ACHIEVESYSTEM_GM2GC_ACK_SAVE_ACHIEVE_DATA)
        {
            m_retCode = ESaveAchieveDataResult.ESAVEACHIEVEDATA_RESUlT_FAIL;
        }
        public ESaveAchieveDataResult m_retCode;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_retCode = (ESaveAchieveDataResult)msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgAchieveSystemGM2GCAckSaveAchieveData ack)
        {
            if (CMsgAchieveSystemGM2GCAckSaveAchieveData.cb == null)
            {
                return;
            }
            CMsgAchieveSystemGM2GCAckSaveAchieveData.cb(ack.m_retCode);
        }
        public static CClientCore.CBMsgAchieveSystemGM2GCAckSaveAchieveData cb = null;
    }
}
