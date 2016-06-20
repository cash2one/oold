using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CVitalityData
    {
        private UInt32 m_needDiamond = 0;

        public UInt32 NeedDiamond
        {
            get { return m_needDiamond; }
            set { m_needDiamond = value; }
        }
        UInt32 m_maxBuyCount = 0;

        public UInt32 MaxBuyCount
        {
            get { return m_maxBuyCount; }
            set { m_maxBuyCount = value; }
        }
        UInt32 m_curBuyCount = 0;

        public UInt32 CurBuyCount
        {
            get { return m_curBuyCount; }
            set { m_curBuyCount = value; }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_needDiamond = msgStream.ReadUInt();
            m_maxBuyCount = msgStream.ReadUInt();
            m_curBuyCount = msgStream.ReadUInt();
            return true;
        }
    }
}
