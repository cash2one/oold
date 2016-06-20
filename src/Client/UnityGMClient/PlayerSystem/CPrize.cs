using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CPrize
    {
        private UInt32 m_ItemID = 0;

        public void setItemID(UInt32 itemID)
        {
            m_ItemID = itemID;
        }

        public UInt32 getItemID()
        {
            return m_ItemID;
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_ItemID = msgStream.ReadUInt();
            return true;
        }

    }
}
