using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CPetUnlockItem
    {
        private UInt32 m_petID = 0;

        public UInt32 PetID
        {
            get { return m_petID; }
            set { m_petID = value; }
        }
        private UInt32 m_petTPID = 0;

        public UInt32 PetTPID
        {
            get { return m_petTPID; }
            set { m_petTPID = value; }
        }
        private EPetUnlockStatus m_petUnlockStatus = EPetUnlockStatus.EPetStatusCannotUnlock;

        public EPetUnlockStatus PetUnlockStatus
        {
            get { return m_petUnlockStatus; }
            set { m_petUnlockStatus = value; }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_petID = msgStream.ReadUInt();
            m_petTPID = msgStream.ReadUInt();
            m_petUnlockStatus = (EPetUnlockStatus)msgStream.ReadUInt();
            return true;
        }
    }
}
