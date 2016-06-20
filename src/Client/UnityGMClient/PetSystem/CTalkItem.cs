using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CTalkItem
    {
        private EUserType m_userType = EUserType.EUserMe;
        private UInt32 m_userID = 0;

        public UInt32 UserID
        {
            get { return m_userID; }
            set { m_userID = value; }
        }

        public EUserType UserType
        {
            get { return m_userType; }
            set { m_userType = value; }
        }
        private Int32 m_soundID = 0;

        public Int32 SoundID
        {
            get { return m_soundID; }
            set { m_soundID = value; }
        }

        private string m_content = "";

        public string Content
        {
            get { return m_content; }
            set { m_content = value; }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            UInt32 userType = msgStream.ReadUInt();
            m_userType = (EUserType)userType;
            m_userID = msgStream.ReadUInt();
            m_soundID = msgStream.ReadInt();
            m_content = msgStream.ReadString();
            return true;
        }

        public string getLogString()
        {
            string lg = "";
            lg += "userType:" + m_userType + " ";
            lg += "m_userID:" + m_userID + " ";
            lg += "m_soundID:" + m_soundID + " ";
            lg += "m_content:" + m_content + " ";
            lg += "\r\n";
            return lg;
        }
    }
}
