using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CChatEquipID
    {
        public CChatEquipID(UInt32 bagIndex, UInt32 equipID)
        {
            m_bagIndex = bagIndex;
            m_equipID = equipID;
        }
        public UInt32 m_bagIndex;
        public UInt32 m_equipID;

        public void serializeTo(UnityUtility.CStream stream)
        {
            stream.Write(m_bagIndex);
            stream.Write(m_equipID);
        }
    }

}
