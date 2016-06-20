using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    class CChatSystemMsgNumID
    {
        public const uint EMSGNUMID_CHATSYSTEM_GC2GM_REQ_CHAT = 1;
        public const uint EMSGNUMID_CHATSYSTEM_GC2GM_ACK_CHAT= 2;
        public const uint EMSGNUMID_CHATSYSTEM_GC2GM_ACK_CHAT2ALL = 3;
        public const uint EMSGNUMID_CHATSYSTEM_GC2GM_ACK_INIT_CHAT_INFO = 4;
    }

    class CMsgChatC2GMReqChat : UnityFrame.CMsg
    {
        SRoleKey m_roleKey;
        EChatChanel m_channel;
        public string m_content;
        public CChatEquipID m_chatEquipID;

        public CMsgChatC2GMReqChat(SRoleKey receiverKey, EChatChanel channel, string content, CChatEquipID equipID)
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_CHATSYSTEM, CChatSystemMsgNumID.EMSGNUMID_CHATSYSTEM_GC2GM_REQ_CHAT)
        {
            m_roleKey = receiverKey;
            m_channel = channel;
            m_content = content;
            m_chatEquipID = equipID;
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            m_roleKey.serializeTo(msgStream);
            msgStream.Write((byte)m_channel);
            msgStream.Write(m_content);
            if (m_chatEquipID == null)
            {
                UInt32 invalid_index = 0xffff;
                m_chatEquipID = new CChatEquipID(invalid_index, invalid_index);
            }
            m_chatEquipID.serializeTo(msgStream);

            return true;
        }
    }

    class CMsgChatSystemGM2GCAckChat : UnityFrame.CMsg
    {
        public byte m_result;
        static public CClientCore.CBMsgChatSystemGM2GCAckChat s_cb = null;

        public CMsgChatSystemGM2GCAckChat()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_CHATSYSTEM, CChatSystemMsgNumID.EMSGNUMID_CHATSYSTEM_GC2GM_ACK_CHAT)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = msgStream.ReadByte();
            return true;
        }

        static public void CallBack(CMsgChatSystemGM2GCAckChat msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb((UnityGMClient.EChatResult)msg.m_result);
                }
            }
        }
    }

    class CMsgChatSystemGM2GCAckChat2All : UnityFrame.CMsg
    {
        CChatContent m_chatContent = new CChatContent();
        static public CClientCore.CBMsgChatSystemGM2GCAckChat2All s_cb = null;

        public CMsgChatSystemGM2GCAckChat2All()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_CHATSYSTEM, CChatSystemMsgNumID.EMSGNUMID_CHATSYSTEM_GC2GM_ACK_CHAT2ALL)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_chatContent.SerializeFrom(msgStream);

            return true;
        }

        static public void CallBack(CMsgChatSystemGM2GCAckChat2All msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb(msg.m_chatContent);
                }
            }
        }
    }


    class CMsgChatSystemGM2GCAckInitChatData : UnityFrame.CMsg
    {
        public List<CChatContent> m_listWorldContent = new List<CChatContent>();
        public List<CChatContent> m_listAnnounceContent = new List<CChatContent>();
        static public CClientCore.CBChatSystemGM2GCAckInitChatData s_cb = null;

        public CMsgChatSystemGM2GCAckInitChatData()
        :base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_CHATSYSTEM, CChatSystemMsgNumID.EMSGNUMID_CHATSYSTEM_GC2GM_ACK_INIT_CHAT_INFO)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            UInt16 count = msgStream.ReadUShort();
            for (Int32 i = 0; i < count; ++i)
            {
                CChatContent content = new CChatContent();
                content.SerializeFrom(msgStream);
                m_listWorldContent.Add(content);
            }

            count = msgStream.ReadUShort();
            for (Int32 i = 0; i < count; ++i)
            {
                CChatContent content = new CChatContent();
                content.SerializeFrom(msgStream);
                m_listAnnounceContent.Add(content);
            }

            return true;
        }

        static public void CallBack(CMsgChatSystemGM2GCAckInitChatData msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb(msg.m_listWorldContent, msg.m_listAnnounceContent);
                }
            }
        }
    }


}
