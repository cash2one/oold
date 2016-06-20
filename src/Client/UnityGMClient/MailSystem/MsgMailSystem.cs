using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{

    public class CMailSystemMsgNumID
    {
        public const uint EMSGID_MAILSYSTEM_GM2GC_ACK_PUSH_MAIL     = 3;
		public const uint EMSGID_MAILSYSTEM_GC2GM_REQ_GET_ATTACH    = 4;
		public const uint EMSGID_MAILSYSTEM_GM2GC_ACK_GET_ATTACH    = 5; 

		public const uint EMSGID_MAILSYSTEM_GC2GM_REQ_OP_MAIL       = 6;
        public const uint EMSGID_MAILSYSTEM_GM2GC_ACK_OP_MAIL       = 7;
    }

    // 提取附件
    class CMsgMailSystemGC2GMReqGetAttach : UnityFrame.CMsg
    {
        public CMsgMailSystemGC2GMReqGetAttach(List<UInt64> mail_ids)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_MAILSYSTEM, CMailSystemMsgNumID.EMSGID_MAILSYSTEM_GC2GM_REQ_GET_ATTACH)
        {
            m_mail_ids = mail_ids;
        }
        public List<UInt64> m_mail_ids =  new List<UInt64>();

        //把数据序列化到msgBuffer中
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_mail_ids.Count);
            for (int i = 0; i < m_mail_ids.Count; i++)
                msgStream.Write(m_mail_ids[i]);

            return true;
        }
    }

    // 提取附件返回
    public class CMsgMailSystemGM2GCAckGetAttach : UnityFrame.CMsg
    {
        public CMsgMailSystemGM2GCAckGetAttach()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_MAILSYSTEM, CMailSystemMsgNumID.EMSGID_MAILSYSTEM_GM2GC_ACK_GET_ATTACH)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            UInt32 mail_count = msgStream.ReadUInt();
            for (UInt32 i = 0; i < mail_count; i++)
            {
                m_mail_ids.Add(msgStream.ReadULong());
            }

            UInt32 bonus_count = msgStream.ReadUInt();
            for (UInt32 i = 0; i < bonus_count; i++)
            {
                m_bonus_ids.Add(msgStream.ReadUInt());
                m_bonus_nums.Add(msgStream.ReadUInt());
            }

            return true;
        }

        public static void CallBack(CMsgMailSystemGM2GCAckGetAttach ack)
        {
            if (CMsgMailSystemGM2GCAckGetAttach.cb == null)
            {
                return;
            }
            CMsgMailSystemGM2GCAckGetAttach.cb(ack.m_mail_ids, ack.m_bonus_ids, ack.m_bonus_nums);
        }

        public List<UInt64> m_mail_ids = new List<UInt64>();
        public List<UInt32> m_bonus_ids = new List<UInt32>();
        public List<UInt32> m_bonus_nums = new List<UInt32>();
        public static CClientCore.CBMsgMailSystemGM2GCAckGetAttach cb = null;
    }

    // 邮件推送
    public class CMsgGM2GCAckPushMail : UnityFrame.CMsg
    {
        public CMsgGM2GCAckPushMail()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_MAILSYSTEM, CMailSystemMsgNumID.EMSGID_MAILSYSTEM_GM2GC_ACK_PUSH_MAIL)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_type = msgStream.ReadUInt();
            UInt32 mail_count = msgStream.ReadUInt();
            for (UInt32 i = 0; i < mail_count; i++)
            {
                CMail mail = new CMail();
                mail.mail_id = msgStream.ReadULong();
                mail.mail_type = msgStream.ReadUInt();
                mail.is_read = msgStream.ReadUInt();
                mail.is_get = msgStream.ReadUInt();
                mail.time_stamp = msgStream.ReadULong();
                mail.title  = msgStream.ReadString();
                mail.content = msgStream.ReadString();
                mail.sender = msgStream.ReadString();
                UInt32 bonus_num = msgStream.ReadUInt();
                for(UInt32 j = 0; j < bonus_num; j++)
                {
                    mail.ids.Add(msgStream.ReadUInt());
                    mail.nums.Add(msgStream.ReadUInt());
                }
                
                m_mails.Add(mail);
            }

                return true;
        }

        public static void CallBack(CMsgGM2GCAckPushMail ack)
        {
            if (CMsgGM2GCAckPushMail.cb == null)
            {
                return;
            }

            CMsgGM2GCAckPushMail.cb(ack.m_type, ack.m_mails);
        }

        public UInt32 m_type = 0;
        public List<CMail> m_mails = new List<CMail>();
        public static CClientCore.CBMsgMailSystemGM2GCAckPushMail cb = null;
    }

    // 请求操作
    class CMsgMailSystemGC2GMReqOPMail : UnityFrame.CMsg
    {
        public CMsgMailSystemGC2GMReqOPMail(UInt32 op_type, List<UInt64> mail_ids)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_MAILSYSTEM, CMailSystemMsgNumID.EMSGID_MAILSYSTEM_GC2GM_REQ_OP_MAIL)
        {
            m_type = op_type;
            m_mail_ids = mail_ids;
        }

        public UInt32 m_type = 0;
        public List<UInt64> m_mail_ids = new List<UInt64>();

        //把数据序列化到msgBuffer中
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_type);
            msgStream.Write(m_mail_ids.Count);
            for (int i = 0; i < m_mail_ids.Count; i++)
            {
                msgStream.Write(m_mail_ids[i]);
            }

            return true;
        }
    }

    // 请求操作返回
    public class CMsgMailSystemGM2GCAckOPMail : UnityFrame.CMsg
    {
        public CMsgMailSystemGM2GCAckOPMail()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_MAILSYSTEM, CMailSystemMsgNumID.EMSGID_MAILSYSTEM_GM2GC_ACK_OP_MAIL)
        {

        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_type = msgStream.ReadUInt();
            UInt32 count = msgStream.ReadUInt();
            for (UInt32 i = 0; i < count; i++)
            {
                m_mail_ids.Add(msgStream.ReadULong());
            }

            return true;
        }

        public static void CallBack(CMsgMailSystemGM2GCAckOPMail ack)
        {
            if (CMsgMailSystemGM2GCAckOPMail.cb == null)
            {
                return;
            }
            CMsgMailSystemGM2GCAckOPMail.cb(ack.m_type, ack.m_mail_ids);
        }

        public UInt32 m_type = 0;
        public List<UInt64> m_mail_ids = new List<UInt64>();
        public static CClientCore.CBMsgMailSystemGM2GCAckOPMail cb = null;
    }

}