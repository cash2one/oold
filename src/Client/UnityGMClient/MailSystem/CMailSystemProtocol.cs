using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    class CMailSystem
    {

        public void init()
        {
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgGM2GCAckPushMail), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgMailSystemGM2GCAckPushMail));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgMailSystemGM2GCAckOPMail), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgGM2GCAckOpMail));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgMailSystemGM2GCAckGetAttach), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnmsgGM2GCAckGetAttach));
        }


        public void OnMsgMailSystemGM2GCAckPushMail(UnityFrame.CMsg msgData)
        {
            CMsgGM2GCAckPushMail ack = (CMsgGM2GCAckPushMail)msgData;
            CMsgGM2GCAckPushMail.CallBack(ack);
        }

        public void OnMsgGM2GCAckOpMail(UnityFrame.CMsg msgData)
        {
            CMsgMailSystemGM2GCAckOPMail ack = (CMsgMailSystemGM2GCAckOPMail)msgData;
            CMsgMailSystemGM2GCAckOPMail.CallBack(ack);
        }

        public void OnmsgGM2GCAckGetAttach(UnityFrame.CMsg msgData)
        {
            CMsgMailSystemGM2GCAckGetAttach ack = (CMsgMailSystemGM2GCAckGetAttach)msgData;
            CMsgMailSystemGM2GCAckGetAttach.CallBack(ack);
        }
    }
}
