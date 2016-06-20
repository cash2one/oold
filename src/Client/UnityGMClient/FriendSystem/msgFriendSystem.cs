using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{

    public enum FriendResult
    {
        eFriendResultOK,				// 没问题,可以向下执行, 不需返回提示

        // 条件不满足
        eFriendResultNotExisted,		// 玩家不存在
        eFriendResultIsMyFriend,		// 已经是好友
        eFriendResultMaxReq,			// 好友请求已达上限
        eFriendResultMaxFriend,			// 好友已满

        // 状态返回
        eFriendResultReqSended,			// 你的请求发送成功(对方离线)
        eFriendResultReqReceived,		// 对方收到了好友申请信息(对方在线)
        eFriendResultFriended,			// 对方通过了好友申请
        efriendResultSuccess,			// 添加好友成功
    };



    public class SFriendRoleInfo
    {
       public  UInt64 m_account = 0;
       public  UInt16 m_zone = 0;
       public  Int32 m_index = 0;

       public virtual bool SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_account);
            msgStream.Write(m_zone);
            msgStream.Write(m_index);
            return true;
        }

       public virtual bool SerializeFrom(UnityUtility.CStream msgStream)
        {
 
            m_account = msgStream.ReadULong();
            m_zone = msgStream.ReadUShort();
            m_index = msgStream.ReadInt();
            return true;
        }

    }


    public class SFriendShortInfo 
        : SFriendRoleInfo
    {
        public string  m_name;

        public override bool SerializeTo(UnityUtility.CStream msgStream)
        {
            base.SerializeTo(msgStream);
            msgStream.Write(m_name);
            return true;
        }

        public override bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            
            base.SerializeFrom(msgStream);
            m_name = msgStream.ReadString();
            return true;
        }

    }

    public class SFriendInfo
        :SFriendShortInfo
    {
       public  UInt32 m_state;
       public  UInt32 m_job;
       public  UInt32 m_level;
       public  UInt32 m_power;
       public  UInt32 m_position;
       public UInt32 m_vip;
       public UInt64 m_roleID;

       public override bool SerializeTo(UnityUtility.CStream msgStream)
        {
            
            base.SerializeTo(msgStream);
            msgStream.Write(m_state);
            msgStream.Write(m_job);
            msgStream.Write(m_level);
            msgStream.Write(m_power);
            msgStream.Write(m_position);
            msgStream.Write(m_vip);
            msgStream.Write(m_roleID);
            return true;
        }

       public override bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            base.SerializeFrom(msgStream);
            m_state = msgStream.ReadUInt();
            m_job = msgStream.ReadUInt();
            m_level = msgStream.ReadUInt();
            m_power = msgStream.ReadUInt();
            m_position = msgStream.ReadUInt();
            m_vip = msgStream.ReadUInt();
            m_roleID = msgStream.ReadULong();
            return true;
        }
    }

    public class CFriendSystemMsgNumID
    {
        public const uint EMSGID_FRIENDSYSTEM_GC2CN_REQ_FRIENDS_OPEN = 1;
        public const uint EMSGID_FRIENDSYSTEM_CN2GC_ACK_FRIENDS_OPEN = 2;
        public const uint EMSGID_FRIENDSYSTEM_GC2CN_REQ_FRIENDS_ADD = 3;
        public const uint EMSGID_FRIENDSYSTEM_CN2GC_REQ_FRIENDS_ADD_CONFIRM = 4;
        public const uint EMSGID_FRIENDSYSTEM_GC2CN_ACK_FRIENDS_ADD_CONFIRM = 5;
        public const uint EMSGID_FRIENDSYSTEM_CN2GC_NTF_FRIENDS_ADD_RESULT = 6;
        public const uint EMSGID_FRIENDSYSTEM_GC2CN_REQ_FRIENDS_DEL = 7;
        public const uint EMSGID_FRIENDSYSTEM_CN2GC_ACK_FRIENDS_DEL = 8;
        public const uint EMSGID_FRIENDSYSTEM_GC2CN_REQ_FRIENDS_NEW_STRANGERS = 9;
        public const uint EMSGID_FRIENDSYSTEM_CN2GC_ACK_FRIENDS_NEW_STRANGERS = 10;
        public const uint EMSGID_FRIENDSYSTEM_GC2CN_REQ_FRIENDS_SEARCH = 11;
        public const uint EMSGID_FRIENDSYSTEM_CN2GC_ACK_FRIENDS_SEARCH = 12;

        public const uint EMSGID_FRIENDSYSTEM_GC2GM_REQ_FRIENDS_LOCAL = 14;
        public const uint EMSGID_FRIENDSYSTEM_GM2GC_ACK_FRIENDS_LOCAL = 15;
    }

    // 请求批量好友
    class CMsgFriendSystemGC2CNReqFriendsNewStrangers : UnityFrame.CMsg
    {
        public CMsgFriendSystemGC2CNReqFriendsNewStrangers()
            : base(CServerType.SRVTYPE_CENTERSERVER, CFuncType.EFUNCTYPE_FRIENDYSTEM, CFriendSystemMsgNumID.EMSGID_FRIENDSYSTEM_GC2CN_REQ_FRIENDS_NEW_STRANGERS)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    // 批量好友返回
    public class CMsgFriendSystemCN2GCAckFriendsNewStrangers : UnityFrame.CMsg
    {
        public CMsgFriendSystemCN2GCAckFriendsNewStrangers()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_FRIENDYSTEM, CFriendSystemMsgNumID.EMSGID_FRIENDSYSTEM_CN2GC_ACK_FRIENDS_NEW_STRANGERS)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            UInt32 size = msgStream.ReadUInt();
            for (UInt32 i = 0; i < size; i++)
            {
                SFriendInfo info = new SFriendInfo();
                info.SerializeFrom(msgStream);
                m_ids.Add(info);
            }
            return true;
        }

        public static void CallBack(CMsgFriendSystemCN2GCAckFriendsNewStrangers ack)
        {
            if (CMsgFriendSystemCN2GCAckFriendsNewStrangers.cb == null)
            {
                return;
            }
            CMsgFriendSystemCN2GCAckFriendsNewStrangers.cb(ack.m_ids);
        }

        public List<SFriendInfo> m_ids = new List<SFriendInfo>();
        public static CClientCore.CBMsgFriendSystemCN2GCAckFriendsNewStrangers cb = null;
    }


    // 添加好友状态返回
    public class CMsgFriendSystemCN2GCNtfFriendsAddResult : UnityFrame.CMsg
    {
        public CMsgFriendSystemCN2GCNtfFriendsAddResult()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_FRIENDYSTEM, CFriendSystemMsgNumID.EMSGID_FRIENDSYSTEM_CN2GC_NTF_FRIENDS_ADD_RESULT)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            UInt32 size = msgStream.ReadUInt();
            for (UInt32 i = 0; i < size; i++)
            {
                SFriendInfo info = new SFriendInfo();
                info.SerializeFrom(msgStream);
                m_ids.Add(info);
            }

            size = msgStream.ReadUInt();
            for (UInt32 i = 0; i < size; i++)
            {
                m_results.Add((FriendResult)msgStream.ReadUInt());    
            }
            return true;
        }

        public static void CallBack(CMsgFriendSystemCN2GCNtfFriendsAddResult ack)
        {
            if (CMsgFriendSystemCN2GCNtfFriendsAddResult.cb == null)
            {
                return;
            }
            CMsgFriendSystemCN2GCNtfFriendsAddResult.cb(ack.m_ids, ack.m_results);
        }

        public List<SFriendInfo> m_ids = new List<SFriendInfo>();
        public List<FriendResult> m_results = new List<FriendResult>();
        public static CClientCore.CBMsgFriendSystemCN2GCNtfFriendsAddResult cb = null;
    }



    // 搜索好友请求
    class CMsgFriendSystemGC2CNReqFriendsSearch : UnityFrame.CMsg
    {
        public CMsgFriendSystemGC2CNReqFriendsSearch(UInt32 a_type, string a_str)
            : base(CServerType.SRVTYPE_CENTERSERVER, CFuncType.EFUNCTYPE_FRIENDYSTEM, CFriendSystemMsgNumID.EMSGID_FRIENDSYSTEM_GC2CN_REQ_FRIENDS_SEARCH)
        {
            m_type = a_type;
            m_buf = a_str;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_type);
            msgStream.Write(m_buf);
            return true;
        }

        public UInt32 m_type = 0;
        public string m_buf = "";
    }

    // 搜索好友返回
    public class CMsgFriendSystemCN2GCAckFriendsSearch : UnityFrame.CMsg
    {
        public CMsgFriendSystemCN2GCAckFriendsSearch()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_FRIENDYSTEM, CFriendSystemMsgNumID.EMSGID_FRIENDSYSTEM_CN2GC_ACK_FRIENDS_SEARCH)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            UInt32 size = msgStream.ReadUInt();
            for (UInt32 i = 0; i < size; i++)
            {
                SFriendInfo info = new SFriendInfo();
                info.SerializeFrom(msgStream);
                m_ids.Add(info);
            }
            return true;
        }

        public static void CallBack(CMsgFriendSystemCN2GCAckFriendsSearch ack)
        {
            if (CMsgFriendSystemCN2GCAckFriendsSearch.cb == null)
            {
                return;
            }
            CMsgFriendSystemCN2GCAckFriendsSearch.cb(ack.m_ids);
        }

        public List<SFriendInfo> m_ids = new List<SFriendInfo>();
        public static CClientCore.CBMsgFriendSystemCN2GCAckFriendsSearch cb = null;
    }

    // 删除好友请求
    class CMsgFriendSystemGC2CNReqFriendsDel : UnityFrame.CMsg
    {
        public CMsgFriendSystemGC2CNReqFriendsDel(List<SFriendRoleInfo> a_list)
            : base(CServerType.SRVTYPE_CENTERSERVER, CFuncType.EFUNCTYPE_FRIENDYSTEM, CFriendSystemMsgNumID.EMSGID_FRIENDSYSTEM_GC2CN_REQ_FRIENDS_DEL)
        {
            m_list = a_list;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            Int32 size = m_list.Count;
            msgStream.Write(size);
            for (Int32 i = 0; i < size; i++)
            {
                m_list[i].SerializeTo(msgStream);
            }
            return true;
        }

        public List<SFriendRoleInfo> m_list = new List<SFriendRoleInfo>();
    }

    // 删除好友返回
    public class CMsgFriendSystemCN2GCAckFriendsDel : UnityFrame.CMsg
    {
        public CMsgFriendSystemCN2GCAckFriendsDel()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_FRIENDYSTEM, CFriendSystemMsgNumID.EMSGID_FRIENDSYSTEM_CN2GC_ACK_FRIENDS_DEL)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            UInt32 size = msgStream.ReadUInt();
            for (UInt32 i = 0; i < size; i++)
            {
                SFriendRoleInfo info = new SFriendRoleInfo();
                info.SerializeFrom(msgStream);
                m_ids.Add(info);
            }
            return true;
        }

        public static void CallBack(CMsgFriendSystemCN2GCAckFriendsDel ack)
        {
            if (CMsgFriendSystemCN2GCAckFriendsDel.cb == null)
            {
                return;
            }
            CMsgFriendSystemCN2GCAckFriendsDel.cb(ack.m_ids);
        }

        public List<SFriendRoleInfo> m_ids = new List<SFriendRoleInfo>();
        public static CClientCore.CBMsgFriendSystemCN2GCAckFriendsDel cb = null;
    }


    // 添加好友确认通知
    class CMsgFriendSystemCN2GCReqFriendsAddConfirm : UnityFrame.CMsg
    {
        public CMsgFriendSystemCN2GCReqFriendsAddConfirm()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_FRIENDYSTEM, CFriendSystemMsgNumID.EMSGID_FRIENDSYSTEM_CN2GC_REQ_FRIENDS_ADD_CONFIRM)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            UInt32 size = msgStream.ReadUInt();
            for (UInt32 i = 0; i < size; i++)
            {
                SFriendInfo info = new SFriendInfo();
                info.SerializeFrom(msgStream);
                m_list.Add(info);
            }
            return true;
        }

        public static void CallBack(CMsgFriendSystemCN2GCReqFriendsAddConfirm ack)
        {
            if (CMsgFriendSystemCN2GCReqFriendsAddConfirm.cb == null)
            {
                return;
            }
            CMsgFriendSystemCN2GCReqFriendsAddConfirm.cb(ack.m_list);
        }

        public static CClientCore.CBMsgFriendSystemCN2GCReqFriendAddConfirm cb = null;

        public List<SFriendInfo> m_list = new List<SFriendInfo>();
    }

    
    // 添加好友确认返回
    public class CMsgFriendSystemGC2CNAckFriendsAddConfirm : UnityFrame.CMsg
    {
        public CMsgFriendSystemGC2CNAckFriendsAddConfirm(UInt32 type, List<SFriendRoleInfo> a_list)
            : base(CServerType.SRVTYPE_CENTERSERVER, CFuncType.EFUNCTYPE_FRIENDYSTEM, CFriendSystemMsgNumID.EMSGID_FRIENDSYSTEM_GC2CN_ACK_FRIENDS_ADD_CONFIRM)
        {
            m_list = a_list;
            m_type = type;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_type);
            Int32 size = m_list.Count;
            msgStream.Write(size);
            for (Int32 i = 0; i < size; i++)
            {
                m_list[i].SerializeTo(msgStream);
            }
            return true;
        }

        public List<SFriendRoleInfo> m_list = new List<SFriendRoleInfo>();
        public UInt32 m_type = 0;
    }


    // 添加好友
    class CMsgFriendSystemGC2CNReqFriendsAdd : UnityFrame.CMsg
    {
        public CMsgFriendSystemGC2CNReqFriendsAdd(List<SFriendRoleInfo> a_list)
            : base(CServerType.SRVTYPE_CENTERSERVER, CFuncType.EFUNCTYPE_FRIENDYSTEM, CFriendSystemMsgNumID.EMSGID_FRIENDSYSTEM_GC2CN_REQ_FRIENDS_ADD)
        {
            m_list = a_list;
        }


        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            Int32 size = m_list.Count;
            msgStream.Write(size);
            for (Int32 i = 0; i < size; i++)
            {
                m_list[i].SerializeTo(msgStream);
            }
            return true;
        }

        public List<SFriendRoleInfo> m_list = new List<SFriendRoleInfo>();
    }


    // 打开界面
    class CMsgFriendSystemGC2CNReqFriendsOpen : UnityFrame.CMsg
    {
        public CMsgFriendSystemGC2CNReqFriendsOpen()
            : base(CServerType.SRVTYPE_CENTERSERVER, CFuncType.EFUNCTYPE_FRIENDYSTEM, CFriendSystemMsgNumID.EMSGID_FRIENDSYSTEM_GC2CN_REQ_FRIENDS_OPEN)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    // 打开界面返回
    public class CMsgFriendSystemCN2GCAckFriendsOpen : UnityFrame.CMsg
    {
        public CMsgFriendSystemCN2GCAckFriendsOpen()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_FRIENDYSTEM, CFriendSystemMsgNumID.EMSGID_FRIENDSYSTEM_CN2GC_ACK_FRIENDS_OPEN)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            UInt32 size = msgStream.ReadUInt();
            for (UInt32 i = 0; i < size; i++)
            {
                SFriendInfo info = new SFriendInfo();
                info.SerializeFrom(msgStream);
                m_ids.Add(info);
            }
            m_capacity = msgStream.ReadUInt();
            return true;
        }

        public static void CallBack(CMsgFriendSystemCN2GCAckFriendsOpen ack)
        {
            if (CMsgFriendSystemCN2GCAckFriendsOpen.cb == null)
            {
                return;
            }
            CMsgFriendSystemCN2GCAckFriendsOpen.cb(ack.m_ids, ack.m_capacity);
        }

        public List<SFriendInfo> m_ids = new List<SFriendInfo>();
        public UInt32 m_capacity = 0;
        public static CClientCore.CBMsgFriendSystemCN2GCAckFriendsOpen cb = null;
    }


    // 请求附近的人
    class CMsgFriendSystemGC2GMReqFriendsLocal : UnityFrame.CMsg
    {
        public CMsgFriendSystemGC2GMReqFriendsLocal()
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_FRIENDYSTEM, CFriendSystemMsgNumID.EMSGID_FRIENDSYSTEM_GC2GM_REQ_FRIENDS_LOCAL)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    // 请求附近的人返回
    public class CMsgFriendSystemGM2GCAckFriendsLocal : UnityFrame.CMsg
    {
        public CMsgFriendSystemGM2GCAckFriendsLocal()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_FRIENDYSTEM, CFriendSystemMsgNumID.EMSGID_FRIENDSYSTEM_GM2GC_ACK_FRIENDS_LOCAL)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            UInt32 size = msgStream.ReadUInt();
            for (UInt32 i = 0; i < size; i++)
            {
                SFriendInfo info = new SFriendInfo();
                info.SerializeFrom(msgStream);
                m_ids.Add(info);
            }
            return true;
        }

        public static void CallBack(CMsgFriendSystemGM2GCAckFriendsLocal ack)
        {
            if (CMsgFriendSystemGM2GCAckFriendsLocal.cb == null)
            {
                return;
            }
            CMsgFriendSystemGM2GCAckFriendsLocal.cb(ack.m_ids);
        }

        public List<SFriendInfo> m_ids = new List<SFriendInfo>();
        public static CClientCore.CBMsgFriendSystemGM2GCAckFriendsLocal cb = null;
    }

}