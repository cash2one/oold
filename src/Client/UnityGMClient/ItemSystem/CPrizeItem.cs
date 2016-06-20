using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CPrizeItem
    {
        public UInt32 m_ItemTPID = 0;
        public EItemType m_ItemType = EItemType.EITEM_TP_IVALID;
        public UInt32 m_ItemCount = 0;

        public void SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_ItemTPID = msgStream.ReadUInt();
            m_ItemType = (EItemType)msgStream.ReadUInt();
            m_ItemCount = msgStream.ReadUInt();
        }

        public void SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_ItemTPID);
            UInt32 itemType = (UInt32)m_ItemType;
            msgStream.Write(itemType);
            msgStream.Write(m_ItemCount);
        }

        public string getLogString()
        {
            string lg = "";
            lg += "m_ItemTPID:" + m_ItemTPID + " ";
            lg += "m_ItemType:" + m_ItemType + " ";
            lg += "m_ItemCount:" + m_ItemCount + " ";

            lg += "\r\n";
            return lg;
        }
    }
}
