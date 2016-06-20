using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CConditionData
    {
        public UInt32 m_gold = 0;
        public UInt32 m_diamond = 0;
        public UInt32 m_guangzili = 0;
        private UInt32 m_itemCount = 0;
        private List<CPrizeItem> m_prizeList = new List<CPrizeItem>();
        public UInt32 ItemCount
        {
            get { return m_itemCount; }
            set { m_itemCount = value; }
        }

        public List<CPrizeItem> PrizeList
        {
            get { return m_prizeList; }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_gold = msgStream.ReadUInt();
            m_diamond = msgStream.ReadUInt();
            m_guangzili = msgStream.ReadUInt();

            m_itemCount = msgStream.ReadUInt();
            for (int i = 0; i < m_itemCount; ++i)
            {
                CPrizeItem item = new CPrizeItem();
                item.SerializeFrom(msgStream);
                m_prizeList.Add(item);
            }
            return true;
        }

        public string getLogString()
        {
            string lg = "";
            lg += "m_itemCount:" + m_itemCount + " ";
            for (int i = 0; i < m_itemCount; i++)
            {
                lg += m_prizeList[i].getLogString();
            }
            lg += "\r\n";
            return lg;
        }
    }
}
