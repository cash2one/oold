using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    /// <summary>
    /// 装备数据
    /// </summary>
    public class CEquipData
    {
        private UInt32 m_equipCount = 0;
        private List<CEquipItem> m_equipList = new List<CEquipItem>();
        public UInt32 EquipCount
        {
            get { return m_equipCount; }
            set { m_equipCount = value; }
        }

        public List<CEquipItem> EquipList
        {
            get { return m_equipList; }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_equipCount = msgStream.ReadUInt();
            for (int i = 0; i < m_equipCount; ++i)
            {
                CEquipItem equipItem = new CEquipItem();
                equipItem.SerializeFrom(msgStream);
                m_equipList.Add(equipItem);
            }

            return true;
        }

        public string getLogString()
        {
            string lg = "";
            lg += "m_equipCount:" + m_equipCount + "\r\n";
            for (int i = 0; i < m_equipCount; i++)
            {
                lg += m_equipList[i].getLogString();
            }
            lg += "\r\n";
            return lg;
        }
    }
}
