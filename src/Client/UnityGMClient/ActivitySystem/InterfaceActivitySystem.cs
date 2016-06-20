using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {
        public delegate void CBMsgActivitySystemGM2GCAckGetAttendenceData(EGetAttendenceDataResult result, CRoleAttendenceData roleAttendenceData);
        public bool SendMsgActivitySystemGC2GMReqGetAttendenceData(CBMsgActivitySystemGM2GCAckGetAttendenceData cb)
        {
            CMsgActivitySystemGC2GMReqGetAttendenceData req = new CMsgActivitySystemGC2GMReqGetAttendenceData();
            CMsgActivitySystemGM2GCAckGetAttendenceData.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        public delegate void CBMsgActivitySystemGM2GCAckSignIn(EAttendenceSignInResult result, Int32 signInTime);
        public bool SendMsgActivitySystemGC2GMReqSignIn(CBMsgActivitySystemGM2GCAckSignIn cb)
        {
            CMsgActivitySystemGC2GMReqSignIn req = new CMsgActivitySystemGC2GMReqSignIn();
            CMsgActivitySystemGM2GCAckSignIn.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        public delegate void CBMsgActivitySystemGM2GCAckDrawCard(EDrawCardResult result, CDrawCardInfo drawCardInfo, List<CRolledItem> listRolledItems);
        public bool SendMsgActivitySystemGC2GMReqDrawCard(EDrawCardType type, UInt16 count, CBMsgActivitySystemGM2GCAckDrawCard cb)
        {
            CMsgActivitySystemGC2GMReqDrawCard req = new CMsgActivitySystemGC2GMReqDrawCard(type, count);
            CMsgActivitySystemGM2GCAckDrawCard.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        public delegate void CBMsgActivitySystemGM2GCAckGetDrawCardInfo(CDrawCardInfo drawCardInfo);
        public bool SendMsgActivitySystemGC2GMReqGetDrawCardInfo(CBMsgActivitySystemGM2GCAckGetDrawCardInfo cb)
        {
            CMsgActivitySystemGC2GMReqGetDrawCardInfo req = new CMsgActivitySystemGC2GMReqGetDrawCardInfo();
            CMsgActivitySystemGM2GCAckGetDrawCardInfo.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

    }
}








