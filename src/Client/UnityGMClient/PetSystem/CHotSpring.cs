using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    /// <summary>
    /// 温泉
    /// </summary>
    public class CHotSpring
    {
        public UInt32 m_hotSpringLevel = 0;
        public UInt32 m_maxPetCount = 0;
        public UInt32 m_inPoolPetCount = 0;
        public List<UInt32> m_helperPetList = new List<UInt32>();
        public List<UInt32> m_inPoolPetIDList = new List<UInt32>();

        //  温泉等级 
        public UInt32 HotSpringLevel
        {
            set { m_hotSpringLevel = value; }
            get { return m_hotSpringLevel; }
        }

        //  伙伴上限 
        public UInt32 MaxInPoolPetCount
        {
            set { m_maxPetCount = value; }
            get { return m_maxPetCount; }
        }

        public UInt32 CurInPoolPetCount
        {
            set { m_inPoolPetCount = value; }
            get { return m_inPoolPetCount; }
        }


        public List<UInt32> InPoolPetIDList
        {
            get { return m_inPoolPetIDList; }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_hotSpringLevel = msgStream.ReadUInt();
            m_maxPetCount = msgStream.ReadUInt();
            UInt16 helperCount = msgStream.ReadUShort();
            for (UInt16 i = 0; i < helperCount; ++i)
            {
                UInt32 helperID = msgStream.ReadUInt();
                m_helperPetList.Add(helperID);
            }
            m_inPoolPetCount = msgStream.ReadUInt();
            for (int i = 0; i < m_inPoolPetCount; ++i)
            {
                UInt32 petID = msgStream.ReadUInt();
                m_inPoolPetIDList.Add(petID);
            }

            return true;
        }

        public string getLogString()
        {
            string lg = "";
            lg += "温泉lv" + HotSpringLevel + " 容纳人数：" + CurInPoolPetCount + "/" + MaxInPoolPetCount + " 援护:" + m_helperPetList.Count + "\r\n";
            List<UInt32> petIDList = InPoolPetIDList;
            for (int i = 0; i < petIDList.Count; i++)
            {
                lg += "petID:" + petIDList[i].ToString() + " ";
            }
            lg += "\r\n";
           
            return lg;
        }
    }
}
