using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    class CShopSystem
    {

        public void Init()
        {
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgShopSystemGM2GCAckShopOpen),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgShopSystemGM2GCAckShopOpen));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgShopSystemGM2GCAckShopBuy),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgShopSystemGM2GCAckShopBuy));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgShopSystemGM2GCAckShopRefresh),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgShopSystemGM2GCAckShopRefresh));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgShopSystemGM2GCAckShopPaidRefresh),
                new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgShopSystemGM2GCAckShopPaidRefresh));

        }

        public void OnMsgShopSystemGM2GCAckShopOpen(UnityFrame.CMsg msgData)
        {
            CMsgShopSystemGM2GCAckShopOpen ack = (CMsgShopSystemGM2GCAckShopOpen)msgData;
            CMsgShopSystemGM2GCAckShopOpen.CallBack(ack);
        }

        public void OnMsgShopSystemGM2GCAckShopBuy(UnityFrame.CMsg msgData)
        {
            CMsgShopSystemGM2GCAckShopBuy ack = (CMsgShopSystemGM2GCAckShopBuy)msgData;
            CMsgShopSystemGM2GCAckShopBuy.CallBack(ack);
        }

        public void OnMsgShopSystemGM2GCAckShopRefresh(UnityFrame.CMsg msgData)
        {
            CMsgShopSystemGM2GCAckShopRefresh ack = (CMsgShopSystemGM2GCAckShopRefresh)msgData;
            CMsgShopSystemGM2GCAckShopRefresh.CallBack(ack);
        }

        public void OnMsgShopSystemGM2GCAckShopPaidRefresh(UnityFrame.CMsg msgData)
        {
            CMsgShopSystemGM2GCAckShopPaidRefresh ack = (CMsgShopSystemGM2GCAckShopPaidRefresh)msgData;
            CMsgShopSystemGM2GCAckShopPaidRefresh.CallBack(ack);
        }

    }
}
