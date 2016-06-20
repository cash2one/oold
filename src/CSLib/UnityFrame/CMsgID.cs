using System;
using System.Collections.Generic;
using System.Text;

namespace UnityFrame
{
    public class CMsgID
    {
        public CMsgID()
        {
            m_msgID = 0;
        }

        public CMsgID(uint msgID)
        {
            m_msgID = msgID;
        }

        public CMsgID(uint serverType, uint funcType, uint msgNumber)
        {
            m_msgID = SetMsgID(serverType, funcType, msgNumber);
        }

        public CMsgID(CServerType serverType, CFuncType funcType, UInt16 msgNumber)
        {
            m_msgID = SetMsgID(serverType, funcType, msgNumber);
        }

        public UInt32 MsgID
        {
            get
            {
                return m_msgID;
            }
            set
            {
                m_msgID = value;
            }
        }

        public CServerType ServerType
        {
            get
            {
                return new CServerType((byte)((m_msgID & 0X0000FF00) >> 8)); ;
            }
        }

        public CFuncType FuncType
        {
            get
            {
                return new CFuncType((byte)(m_msgID & 0X000000FF)); ;
            }
        }

        public UInt16 MsgNumber
        {
            get
            {
                return (UInt16)((m_msgID & 0XFFFF0000) >> 16);
            }
        }

        public bool IsInvalid
        {
            get
            {
                return m_msgID == 0;
            }
        }

        public static uint SetMsgID(CServerType serverType, CFuncType funcType, UInt16 msgNumber)
        {
            return (((UInt32)msgNumber & 0X0000FFFF) << 16) + (((UInt32)serverType.ServerType & 0X000000FF) << 8) + (UInt32)funcType.FuncType;
        }

        public static uint SetMsgID(uint serverType, uint funcType, uint msgNumber)
        {
            return (((UInt32)msgNumber & 0X0000FFFF) << 16) + (((UInt32)serverType & 0X000000FF) << 8) + (UInt32)funcType;
        }

        public static CMsgID CreateMsgID(CServerType serverType, CFuncType funcType, UInt16 msgNumber)
        {
            return new CMsgID(serverType, funcType, msgNumber);
        }

        public static CMsgID CreateMsgID(uint serverType, uint funcType, uint msgNumber)
        {
            return new CMsgID(serverType, funcType, msgNumber);
        }

        public static CMsgID CreateMsgID(uint msgID)
        {
            return new CMsgID(msgID);
        }

        private uint m_msgID = 0;
    }
}