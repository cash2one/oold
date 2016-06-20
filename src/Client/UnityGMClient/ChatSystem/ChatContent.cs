using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CChatContent
    {
        public SRoleKey m_senderKey;
        public SRoleKey m_recverKey;
        public string m_senderName;
        public UInt32 m_VIPLevel = 0;
        public EChatChanel m_channel;
        public string m_content;
        public CEquipItem m_equipment;

        public void SerializeFrom(UnityUtility.CStream stream)
        {
            m_senderKey.serializeFrom(stream);
            m_senderName = stream.ReadString();
            m_VIPLevel = stream.ReadUInt();
            byte channel = stream.ReadByte();
            m_channel = (EChatChanel)channel;
            if (m_channel == EChatChanel.CHAT_CHANNEL_PRIVATE)
            {
                m_recverKey.serializeFrom(stream);
            }
            m_content = stream.ReadString();
            byte equip = stream.ReadByte();
            if (equip > 0) {
                m_equipment = new CEquipItem();
                m_equipment.SerializeFrom(stream);
            }
        }
    }
}