using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CSendItem
    {
        private List<CPrizeItem> m_itemList = new List<CPrizeItem>();
        public List<CPrizeItem> ItemList
        {
            get { return m_itemList; }
            set { m_itemList = value; }
        }

        public void addItem(CPrizeItem a_item)
        {
            m_itemList.Add(a_item);
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
             UInt32 count =msgStream.ReadUInt();
             for (UInt32 i = 0; i < count; ++i)
             {
                 CPrizeItem item = new CPrizeItem();
                 item.SerializeFrom(msgStream);
                 m_itemList.Add(item);
             }
            return true;
        }

        public bool SerializeTo(UnityUtility.CStream msgStream)
        {
            if (m_itemList == null)
            { 
                UInt32 totalCount = 0;
                msgStream.Write(totalCount);
                return true;
            }
            UInt32 count = (uint)m_itemList.Count;
            msgStream.Write(count);
            foreach (CPrizeItem item in m_itemList)
            {
                item.SerializeTo(msgStream);
            }
            return true;
        }
    }
}
