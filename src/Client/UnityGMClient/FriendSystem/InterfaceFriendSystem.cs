using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{

    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {

        public delegate void CBMsgFriendSystemCN2GCAckFriendsOpen(List<SFriendInfo> info, UInt32 capacity);
        /// <summary>
        /// 打开好友面板
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgFriendSystemGC2CNReqFriendsOpen(CBMsgFriendSystemCN2GCAckFriendsOpen cb)
        {
            CMsgFriendSystemGC2CNReqFriendsOpen req = new CMsgFriendSystemGC2CNReqFriendsOpen();

            CMsgFriendSystemCN2GCAckFriendsOpen.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 添加好友, 无返回
        /// </summary>
        /// <param name="a_list"></param>
        /// <returns></returns>
        public bool SendMsgFriendSystemGC2CNReqFriendsAdd(List<SFriendRoleInfo> a_list)
        {
            CMsgFriendSystemGC2CNReqFriendsAdd req = new CMsgFriendSystemGC2CNReqFriendsAdd(a_list);
            return CGameClient.Singleton.SendMsg(req);
        }


        public delegate void CBMsgFriendSystemCN2GCReqFriendAddConfirm(List<SFriendInfo> a_list);
        /// <summary>
        /// 注册接收别的玩家发过来的好友请求
        /// </summary>
        /// <param name="cb"></param>
        public void RegisterFriendSystemCN2GCFriendsAddConfirm(CBMsgFriendSystemCN2GCReqFriendAddConfirm cb)
        {
            CMsgFriendSystemCN2GCReqFriendsAddConfirm.cb = cb;
        }

        /// <summary>
        /// 同意好友请求
        /// </summary>
        /// <param name="type">1 同意, 2:拒绝</param>
        /// <param name="a_list"></param>
        /// <returns></returns>
        public bool SendMsgFriendSystemGC2CNAckFriendsAddConfirm(UInt32 type, List<SFriendRoleInfo> a_list)
        {
            CMsgFriendSystemGC2CNAckFriendsAddConfirm req = new CMsgFriendSystemGC2CNAckFriendsAddConfirm(type, a_list);
            return CGameClient.Singleton.SendMsg(req);
        }

        public delegate void CBMsgFriendSystemCN2GCAckFriendsDel(List<SFriendRoleInfo> role_info);
        /// <summary>
        /// 删除好友
        /// </summary>
        /// <param name="a_list"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgFriendSystemGC2CNReqFriendsDel(List<SFriendRoleInfo> a_list, CBMsgFriendSystemCN2GCAckFriendsDel cb)
        {
            CMsgFriendSystemGC2CNReqFriendsDel req = new CMsgFriendSystemGC2CNReqFriendsDel(a_list);

            CMsgFriendSystemCN2GCAckFriendsDel.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        public delegate void CBMsgFriendSystemCN2GCNtfFriendsAddResult(List<SFriendInfo> info, List<FriendResult> result);
        public void RegisterFriendSystemCN2GCNtfFriendsAddResult(CBMsgFriendSystemCN2GCNtfFriendsAddResult cb)
        {
            CMsgFriendSystemCN2GCNtfFriendsAddResult.cb = cb;
        }   


        public delegate void CBMsgFriendSystemCN2GCAckFriendsNewStrangers(List<SFriendInfo> info);
        /// <summary>
        /// 请求系统推荐的好友
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgFriendSystemGC2CNReqFriendsNewStrangers(CBMsgFriendSystemCN2GCAckFriendsNewStrangers cb)
        {
            CMsgFriendSystemGC2CNReqFriendsNewStrangers req = new CMsgFriendSystemGC2CNReqFriendsNewStrangers();

            CMsgFriendSystemCN2GCAckFriendsNewStrangers.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        public delegate void CBMsgFriendSystemCN2GCAckFriendsSearch(List<SFriendInfo> info);
        /// <summary>
        /// 搜索好友
        /// </summary>
        /// <param name="a_type">  0:昵称搜索 1:id搜索</param>
        /// <param name="a_buf"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgFriendSystemGC2CNReqFriendsSearch(UInt32 a_type, string a_buf, CBMsgFriendSystemCN2GCAckFriendsSearch cb)
        {
            CMsgFriendSystemGC2CNReqFriendsSearch req = new CMsgFriendSystemGC2CNReqFriendsSearch(a_type, a_buf);

            CMsgFriendSystemCN2GCAckFriendsSearch.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }


        public delegate void CBMsgFriendSystemGM2GCAckFriendsLocal(List<SFriendInfo> info);
        /// <summary>
        /// 请求系统发送附近的人
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgFriendSystemGC2GMReqFriendsLocal(CBMsgFriendSystemGM2GCAckFriendsLocal cb)
        {
            CMsgFriendSystemGC2GMReqFriendsLocal req = new CMsgFriendSystemGC2GMReqFriendsLocal();

            CMsgFriendSystemGM2GCAckFriendsLocal.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }


    } // CClientCore

} // UnityGMClient
