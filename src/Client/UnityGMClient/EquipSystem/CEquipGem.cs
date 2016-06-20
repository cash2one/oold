using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public enum EGemType
    {
        GEM_TYPE1 = 0,
        GEM_TYPE2 = 1,
        GEM_TYPE3 = 2,
        GEM_TYPE4 = 3,
        GEM_TYPE_NUMBER = 4,
    }

    public class CEquipGem
    {
        private UInt32 m_gemID = 0;
        private EGemType m_gemType = 0;
        private UInt32 m_gemTPID = 0;
        private UInt32 m_gemLevel = 0;
        private UInt32 m_gemMatarialCount = 0;

        public UInt32 GemID
        {
            set { m_gemID = value; }
            get { return m_gemID; }
        }


        public UInt32 GemTPID
        {
            set { m_gemTPID = value; }
            get { return m_gemTPID; }
        }

        public EGemType GemType
        {
            set { m_gemType = value; }
            get { return m_gemType; }
        }

        public UInt32 GemLevel
        {
            set { m_gemLevel = value; }
            get { return m_gemLevel; }
        }
        public UInt32 GemMatarialCount
        {
            set { m_gemMatarialCount = value; }
            get { return m_gemMatarialCount; }
        }

        public  bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_gemID = msgStream.ReadUInt();
            m_gemType = (EGemType)msgStream.ReadUInt();
            m_gemTPID = msgStream.ReadUInt();
            m_gemLevel = msgStream.ReadUInt();
            m_gemMatarialCount = msgStream.ReadUInt();
            return true;
        }

    }
}
