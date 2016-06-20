using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CPetBaseInfor
    {
        private UInt32 m_petID = 0;
        private UInt32 m_petTPID = 0;
        private UInt32 m_leftTime = 0;
        private EPetStatus m_petStatus = EPetStatus.EPetStatusInvalid;
 
        public UInt32 LeftTime
        {
            get { return m_leftTime; }
            set { m_leftTime = value; }
        }

        public UInt32 PetID
        {
            set { m_petID = value; }
            get { return m_petID; }
        }

        public UInt32 PetTPID
        {
            set { m_petTPID = value; }
            get { return m_petTPID; }
        }

        public EPetStatus PetStatus
        {
            set { m_petStatus = value; }
            get { return m_petStatus; }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_petID = msgStream.ReadUInt();
            m_petTPID = msgStream.ReadUInt();
            m_petStatus = (EPetStatus)msgStream.ReadUInt();
            m_leftTime = msgStream.ReadUInt();
            return true;
        }

        public string getLogString()
        {
            string lg = "";

            lg += "\r\n";
            lg += "PetID:" + PetID + ",";
            lg += "TPID:" + PetTPID + ",";
            lg += "Status:" + PetStatus.ToString() + ",";
            lg += "m_leftTime:" + m_leftTime.ToString() + "\r\n";
            lg += "\r\n";
            return lg;
        }
    }
}
