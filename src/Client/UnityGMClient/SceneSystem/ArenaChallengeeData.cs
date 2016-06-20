using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CArenaChallengeeData
    {
        public UInt16 m_zoneID = 0;
        public UInt64 m_accountID = 0;
    	public UInt32 m_roleIndex = 0;
    	public string m_strRoleName;
    	public UInt32 m_roleTPID = 0;
        public UInt32 m_roleLevel = 0;
    	public UInt32 m_rank = 0;
    	public UInt32 m_combatPower = 0;

        public void SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_zoneID = msgStream.ReadUShort();
            m_accountID = msgStream.ReadULong();
            m_roleIndex = msgStream.ReadUInt();
            m_strRoleName = msgStream.ReadString();
            m_roleTPID = msgStream.ReadUInt();
            m_roleLevel = msgStream.ReadUInt();
            m_rank = msgStream.ReadUInt();
            m_combatPower = msgStream.ReadUInt();
        }

    }


}
