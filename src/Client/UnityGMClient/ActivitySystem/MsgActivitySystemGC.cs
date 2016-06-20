using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{

//////////////////////////////////////////////////////////////////////////////////////////////////
class CMsgActivitySystemGM2GCAckGetAttendenceData : UnityFrame.CMsg
{
    public CMsgActivitySystemGM2GCAckGetAttendenceData()
    :base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_ACTIVITYSYSTEM, CActivitySystemMsgNumID.EMSGNUMID_ACTIVITYSYSTEM_GM2GC_ACK_GET_ATTENDENCE_DATA)
    {
    }

    public EGetAttendenceDataResult m_result;
    public CRoleAttendenceData m_roleAttendenceData = new CRoleAttendenceData();

    protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
    {
        m_result = (EGetAttendenceDataResult)msgStream.ReadByte();
        m_roleAttendenceData.serializeFrom(msgStream);
        return true;
    }

    public static CClientCore.CBMsgActivitySystemGM2GCAckGetAttendenceData s_cb = null;
    public static void CallBack(CMsgActivitySystemGM2GCAckGetAttendenceData ack)
    {
        if (CMsgActivitySystemGM2GCAckGetAttendenceData.s_cb != null)
        {
            CMsgActivitySystemGM2GCAckGetAttendenceData.s_cb(ack.m_result, ack.m_roleAttendenceData);
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
class CMsgActivitySystemGM2GCAckSignIn : UnityFrame.CMsg
{
    public CMsgActivitySystemGM2GCAckSignIn()
    : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_ACTIVITYSYSTEM, CActivitySystemMsgNumID.EMSGNUMID_ACTIVITYSYSTEM_GM2GC_ACK_SIGN_IN)
    {

    }

    protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
    {
        m_result = (EAttendenceSignInResult)msgStream.ReadByte();
        m_signInTime = msgStream.ReadInt();
        return true;
    }

    EAttendenceSignInResult m_result;
    Int32 m_signInTime = 0;
    public static CClientCore.CBMsgActivitySystemGM2GCAckSignIn s_cb = null;
    public static void CallBack(CMsgActivitySystemGM2GCAckSignIn ack)
    {
        if (CMsgActivitySystemGM2GCAckSignIn.s_cb != null)
        {
            CMsgActivitySystemGM2GCAckSignIn.s_cb(ack.m_result, ack.m_signInTime);
        }

    }
}

class CMsgActivitySystemGM2GCAckDrawCard : UnityFrame.CMsg
{
    public CMsgActivitySystemGM2GCAckDrawCard()
    : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_ACTIVITYSYSTEM, CActivitySystemMsgNumID.EMSGNUMID_ACTIVITYSYSTEM_GM2GC_ACK_DRAW_CARD)
    {
    }

    protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
    {
        byte result = msgStream.ReadByte();
        m_result = (EDrawCardResult)result;
        if (m_result == EDrawCardResult.EDRAW_CARD_RESULT_SUCCESS) {
            m_drawCardInfo.m_nextFreeGoldDrawCardRemaindTime = msgStream.ReadInt();
            m_drawCardInfo.m_nextFreeDiamondDrawCardRemainTime = msgStream.ReadInt();
            m_drawCardInfo.m_curFreeGoldDrawCardRemaindCount = msgStream.ReadInt();
            UInt16 count = msgStream.ReadUShort();
            for (UInt16 i = 0; i < count; ++i )
            {
                CRolledItem rolledItem = new CRolledItem();
                rolledItem.serializeFrom(msgStream);
                m_listRolledItems.Add(rolledItem);
            }
        }
        return true;
    }

    EDrawCardResult m_result;
    CDrawCardInfo m_drawCardInfo = new CDrawCardInfo();
    List<CRolledItem> m_listRolledItems = new List<CRolledItem>();
    public static CClientCore.CBMsgActivitySystemGM2GCAckDrawCard s_cb = null;
    public static void CallBack(CMsgActivitySystemGM2GCAckDrawCard ack)
    {
        if (CMsgActivitySystemGM2GCAckDrawCard.s_cb != null)
        {
            CMsgActivitySystemGM2GCAckDrawCard.s_cb(ack.m_result, ack.m_drawCardInfo, ack.m_listRolledItems);
        }
    }
}

class CMsgActivitySystemGM2GCAckGetDrawCardInfo : UnityFrame.CMsg
{
    public CMsgActivitySystemGM2GCAckGetDrawCardInfo()
    :base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_ACTIVITYSYSTEM, CActivitySystemMsgNumID.EMSGNUMID_ACTIVITYSYSTEM_GM2GC_ACK_GET_DRAW_CARD_INFO)
    {
    }

    protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
    {
        m_drawCardInfo.m_nextFreeGoldDrawCardRemaindTime = msgStream.ReadInt();
        m_drawCardInfo.m_nextFreeDiamondDrawCardRemainTime = msgStream.ReadInt();
        m_drawCardInfo.m_curFreeGoldDrawCardRemaindCount = msgStream.ReadInt();
        return true;
    }

    CDrawCardInfo m_drawCardInfo = new CDrawCardInfo();
    public static CClientCore.CBMsgActivitySystemGM2GCAckGetDrawCardInfo s_cb = null;
    public static void CallBack(CMsgActivitySystemGM2GCAckGetDrawCardInfo ack)
    {
        if (CMsgActivitySystemGM2GCAckGetDrawCardInfo.s_cb != null)
        {
            CMsgActivitySystemGM2GCAckGetDrawCardInfo.s_cb(ack.m_drawCardInfo);
        }
    }
}


           

                                  




}
