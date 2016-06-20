using System;
using System.Collections.Generic;
using System.Text;

namespace UnityFrame
{

    public class CServerType
    {
        public CServerType()
        {
            m_serverType = 0;
        }

        public CServerType(byte serverType)
        {
            m_serverType = serverType;
        }

        public byte ServerType
        {
            get
            {
                return m_serverType;
            }
            set
            {
                m_serverType = value;
            }
        }

        private byte m_serverType = 0;
    }
}