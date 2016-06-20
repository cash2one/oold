using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    /// <summary>
    /// 僚机数据
    /// </summary>
    public class CPetData
    {
        private UInt32 m_petCount = 0;
        private CHotSpring m_hotSpring = new CHotSpring();
        private List<CPetItem> m_petList = new List<CPetItem>();

        public UInt32 PetCount
        {
            get { return m_petCount; }
            set { m_petCount = value; }
        }

        public CHotSpring HotSpring 
        {
            get { return m_hotSpring; }
            set { m_hotSpring = value; }
        }

        public List<CPetItem> PetList
        {
            get { return m_petList; }
        }

        public CPetItem getPetItem(UInt32 petID)
        {
            for (int i = 0; i < m_petList.Count; i++)
            {
                if (m_petList[i].PetID == petID)
                {
                    return m_petList[i];
                }
            }
            return null;
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_hotSpring.SerializeFrom(msgStream);
            m_petCount = msgStream.ReadUInt();
            for (int i = 0; i < m_petCount; ++i)
            {
                CPetItem petItem = new CPetItem();
                petItem.SerializeFrom(msgStream);
                m_petList.Add(petItem);
            }
            return true;
        }

        public string getLogString()
        {
            string lg = m_hotSpring.getLogString();
            lg += "\r\n";
            lg += "PetCount:" + PetCount + "\r\n";
            for (int i = 0; i < PetCount; i++)
            {
                lg +=  PetList[i].getLogString();
            }
            lg += "\r\n";
            return lg;
        }
    }
}
