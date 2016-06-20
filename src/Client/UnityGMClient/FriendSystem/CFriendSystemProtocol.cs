using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    class CFriendSystem
    {

        public void Init()
        {
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgFriendSystemCN2GCAckFriendsOpen),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgFriendSystemCN2GCAckFriendsOpen));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgFriendSystemCN2GCReqFriendsAddConfirm),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgFriendSystemCN2GCReqFriendsAddConfirm));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgFriendSystemCN2GCAckFriendsDel),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgFriendSystemCN2GCAckFriendsDel));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgFriendSystemCN2GCAckFriendsNewStrangers),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgFriendSystemCN2GCAckFriendsNewStrangers));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgFriendSystemCN2GCAckFriendsSearch),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgFriendSystemCN2GCAckFriendsSearch));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgFriendSystemGM2GCAckFriendsLocal),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgFriendSystemGM2GCAckFriendsLocal));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgFriendSystemCN2GCNtfFriendsAddResult),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(onCMsgFriendSystemCN2GCNtfFriendsAddResult));
        }

        public void OnMsgFriendSystemCN2GCAckFriendsOpen(UnityFrame.CMsg msgData)
        {
            CMsgFriendSystemCN2GCAckFriendsOpen ack = (CMsgFriendSystemCN2GCAckFriendsOpen)msgData;
            CMsgFriendSystemCN2GCAckFriendsOpen.CallBack(ack);
        }

        public void OnMsgFriendSystemCN2GCReqFriendsAddConfirm(UnityFrame.CMsg msgData)
        {
            CMsgFriendSystemCN2GCReqFriendsAddConfirm ack = (CMsgFriendSystemCN2GCReqFriendsAddConfirm)msgData;
            CMsgFriendSystemCN2GCReqFriendsAddConfirm.CallBack(ack);
        }

        public void OnMsgFriendSystemCN2GCAckFriendsDel(UnityFrame.CMsg msgData)
        {
            CMsgFriendSystemCN2GCAckFriendsDel ack = (CMsgFriendSystemCN2GCAckFriendsDel)msgData;
            CMsgFriendSystemCN2GCAckFriendsDel.CallBack(ack);
        }

        public void OnMsgFriendSystemCN2GCAckFriendsNewStrangers(UnityFrame.CMsg msgData)
        {
            CMsgFriendSystemCN2GCAckFriendsNewStrangers ack = (CMsgFriendSystemCN2GCAckFriendsNewStrangers)msgData;
            CMsgFriendSystemCN2GCAckFriendsNewStrangers.CallBack(ack);
        }

        public void OnMsgFriendSystemCN2GCAckFriendsSearch(UnityFrame.CMsg msgData)
        {
            CMsgFriendSystemCN2GCAckFriendsSearch ack = (CMsgFriendSystemCN2GCAckFriendsSearch)msgData;
            CMsgFriendSystemCN2GCAckFriendsSearch.CallBack(ack);
        }

        public void OnMsgFriendSystemGM2GCAckFriendsLocal(UnityFrame.CMsg msgData)
        {
            CMsgFriendSystemGM2GCAckFriendsLocal ack = (CMsgFriendSystemGM2GCAckFriendsLocal)msgData;
            CMsgFriendSystemGM2GCAckFriendsLocal.CallBack(ack);
        }

        public void onCMsgFriendSystemCN2GCNtfFriendsAddResult(UnityFrame.CMsg msgData)
        {
            CMsgFriendSystemCN2GCNtfFriendsAddResult ack = (CMsgFriendSystemCN2GCNtfFriendsAddResult)msgData;
            CMsgFriendSystemCN2GCNtfFriendsAddResult.CallBack(ack);
        }

    }
}
