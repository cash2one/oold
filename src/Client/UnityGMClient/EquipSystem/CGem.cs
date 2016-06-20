using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    /// <summary>
    /// 宝石孔
    /// </summary>
    public enum EGemSlot
    {
        GEM_SLOT_FIRST = 0,
        GEM_SLOT_SECOND = 1,
        GEM_SLOT_THIRD = 2,
        GEM_SLOT_FORTH = 3,
        GEM_SLOT_MAX = 4,
        GEM_SLOT_INVALID = 5,
    }

    public class CGem
    {
        private EGemSlot m_gemSlot = 0;

        public EGemSlot GemSlot
        {
            get { return m_gemSlot; }
            set { m_gemSlot = value; }
        }
        private UInt32 m_gemTPID = 0;


        public UInt32 GemTPID
        {
            set { m_gemTPID = value; }
            get { return m_gemTPID; }
        }

        public  bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_gemTPID = msgStream.ReadUInt();
            m_gemSlot = (EGemSlot)msgStream.ReadUInt();
            return true;
        }

    }
}
