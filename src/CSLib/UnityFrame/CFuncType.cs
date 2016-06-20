using System;
using System.Collections.Generic;
using System.Text;

namespace UnityFrame
{
    public class CFuncType
    {
        public CFuncType()
        {
            m_funcType = 0;
        }

        public CFuncType(byte funcType)
        {
            m_funcType = funcType;
        }

        public byte FuncType
        {
            get
            {
                return m_funcType;
            }
            set
            {
                m_funcType = value;
            }
        }
        private byte m_funcType = 0;
    }
}