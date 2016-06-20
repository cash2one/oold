using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CPetUnlockData
    {
        private List<CPetUnlockItem> m_petUnlockItemList = new List<CPetUnlockItem>();
        private UInt32 m_totalPetCount = 0;

        public UInt32 TotalPetCount
        {
            get { return m_totalPetCount; }
            set { m_totalPetCount = value; }
        }
        private UInt32 m_unlockPetCount = 0;

        public UInt32 UnlockPetCount
        {
            get { return m_unlockPetCount; }
            set { m_unlockPetCount = value; }
        }

        public List<CPetUnlockItem> PetUnlockItemList
        {
            get { return m_petUnlockItemList; }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_totalPetCount = msgStream.ReadUInt();
            m_unlockPetCount = 0;
            for (int i = 0; i < m_totalPetCount; ++i)
            {
                CPetUnlockItem petItem = new CPetUnlockItem();
                petItem.SerializeFrom(msgStream);
                if (petItem.PetUnlockStatus == EPetUnlockStatus.EPetStatusUnlocked)
                {
                    m_unlockPetCount = m_unlockPetCount + 1;
                }
                m_petUnlockItemList.Add(petItem);
            }
            
            return true;
        }

        public string getLogString()
        {
            string lg = "\r\n";
            lg += "解锁率" + UnlockPetCount * 100 / m_totalPetCount + "%\r\n";
            for (int i = 0; i < PetUnlockItemList.Count; i++)
            {
                lg += "petID[" + i + "]:" + PetUnlockItemList[i].PetID.ToString() + ",";
                lg += "PetTPID:" + PetUnlockItemList[i].PetTPID.ToString() + ",";
                lg += "Status:" + PetUnlockItemList[i].PetUnlockStatus.ToString();
                lg += "\r\n";
            }
            lg += "\r\n";
            return lg;
        }
    }
}
