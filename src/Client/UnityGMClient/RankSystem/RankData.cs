using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{

    public class CRankData
    {
        public UInt16 m_zoneID = 0;
        public UInt64 m_accountID = 0;
        public UInt32 m_roleIndex = 0;
        public UInt32 m_roleTPID = 0;
        public string m_strRoleName;
        public UInt32 m_rank = 0;
        public UInt32 m_level = 0;
        public UInt32 m_combatPower = 0;

        public void SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_zoneID = msgStream.ReadUShort();
            m_accountID = msgStream.ReadULong();
            m_roleIndex = msgStream.ReadUInt();
            m_roleTPID = msgStream.ReadUInt();
            m_strRoleName = msgStream.ReadString();
            m_rank = msgStream.ReadUInt();
            m_level = msgStream.ReadUInt();
            m_combatPower = msgStream.ReadUInt();
        }
    }
	
	public class CRankCell
    {
        public UInt64 m_accountID = 0;
        public UInt16 m_zoneID = 0;
        public UInt32 m_roleIndex = 0;

        public UInt32 m_pos = 0;
        public string m_name;
        public UInt32 m_level = 0;
        public UInt32 m_vip = 0;
        public UInt32 m_job = 0;
        public UInt32 m_power = 0;
        public Int32 m_param = 0;

        public void SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_accountID = msgStream.ReadULong();
            m_zoneID = msgStream.ReadUShort();
            m_roleIndex = msgStream.ReadUInt();

            m_pos = msgStream.ReadUInt();
            m_name = msgStream.ReadString();
            m_level = msgStream.ReadUInt();
            m_vip = msgStream.ReadUInt();
            m_job = msgStream.ReadUInt();
            m_power = msgStream.ReadUInt();
            m_param = msgStream.ReadInt();
        }
    }

}









