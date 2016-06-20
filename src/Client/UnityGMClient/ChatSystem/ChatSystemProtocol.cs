using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    partial class CChatSystem
    {
        public void Init()
        {
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgChatSystemGM2GCAckChat), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgChatSystemGM2GCAckChat));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgChatSystemGM2GCAckChat2All), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgChatSystemGM2GCPAckChat2All));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgChatSystemGM2GCAckInitChatData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgChatSystemGM2GCPAckInitChatData));
        }

        private void OnMsgChatSystemGM2GCAckChat(UnityFrame.CMsg msgData)
        {
            CMsgChatSystemGM2GCAckChat ack = (CMsgChatSystemGM2GCAckChat)msgData;
            CMsgChatSystemGM2GCAckChat.CallBack(ack);
        }

        private void OnMsgChatSystemGM2GCPAckChat2All(UnityFrame.CMsg msgData)
        {
            CMsgChatSystemGM2GCAckChat2All ack = (CMsgChatSystemGM2GCAckChat2All)msgData;
            CMsgChatSystemGM2GCAckChat2All.CallBack(ack);
        }

        private void OnMsgChatSystemGM2GCPAckInitChatData(UnityFrame.CMsg msgData)
        {
            CMsgChatSystemGM2GCAckInitChatData ack = (CMsgChatSystemGM2GCAckInitChatData)msgData;
            CMsgChatSystemGM2GCAckInitChatData.CallBack(ack);
        }

    }
}