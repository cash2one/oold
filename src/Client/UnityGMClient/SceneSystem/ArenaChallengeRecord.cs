using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CArenaChallengeRecord
    {
        public UInt64 m_recordID = 0;
        public bool m_isActive = false;
    	public bool m_isWin = false;
        public Int32 m_challengeTime = 0;
        public Int32 m_timeElapsed = 0;
    	public UInt32 m_newRank = 0;
    	public Int32 m_changedRank = 0;
    	public UInt16 m_challengeeZoneID = 0;
    	public UInt64 m_challengeeAccountID = 0;
    	public UInt32 m_challengeeRoleIndex = 0;
        public UInt32 m_challengeeTPID = 0;
    	public string m_challengeeName;
        public bool m_isRevenged = false;

        public void SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_recordID = msgStream.ReadULong();
            m_isActive = msgStream.ReadBoolean();
            m_isWin = msgStream.ReadBoolean();
            m_challengeTime = msgStream.ReadInt();
            m_timeElapsed = msgStream.ReadInt();
            m_newRank = msgStream.ReadUInt();
            m_changedRank = msgStream.ReadInt();
            m_challengeeZoneID = msgStream.ReadUShort();
            m_challengeeAccountID = msgStream.ReadULong();
            m_challengeeRoleIndex = msgStream.ReadUInt();
            m_challengeeTPID = msgStream.ReadUInt();
            m_challengeeName = msgStream.ReadString();
            m_isRevenged = msgStream.ReadBoolean();
        }

    }


}
