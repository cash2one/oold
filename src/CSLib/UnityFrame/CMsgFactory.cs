using System;
using System.Collections;
using System.Reflection;

namespace UnityFrame
{
    public class CMsgFactory
    {
        public void AddMsgType(CMsgID msgID, Type type)
        {
            m_hashtable.Add(msgID.MsgID, type.FullName);
        }

        public void AddMsgType(Type type)
        {
            CMsgID msg = CreateMsgIDByType(type);
            if (msg == null)
            {
                return;
            }
            m_hashtable.Add(msg.MsgID, type.FullName);
        }

        public void DelMsgType(Type type)
        {
            CMsgID msg = CreateMsgIDByType(type);
            if (msg == null)
            {
                return;
            }
            m_hashtable.Remove(msg.MsgID);
        }

        public void DelMsgType(CMsgID msgID)
        {
            m_hashtable.Remove(msgID.MsgID);
        }

        public CMsg CreateMessageByType(Type type)
        {
            return CreateMessageByTypeName(type.FullName);
        }

        public CMsg CreateMessageByMsgID(CMsgID msgID)
        {
            try
            {
                if (!m_hashtable.ContainsKey(msgID.MsgID))
                {
                    return null;
                }
                string typeName = (string)m_hashtable[msgID.MsgID];
                return CreateMessageByTypeName(typeName);
            }
            catch (System.Exception)
            {
                return null;
            }
        }

        public virtual CMsg CreateMessageByTypeName(string typeName)
        {
            try
            {
                Assembly asm = Assembly.GetExecutingAssembly();
                Object obj = asm.CreateInstance(typeName, true);
                return (CMsg)obj;
            }
            catch (System.Exception)
            {
                return null;
            }
        }

        public virtual CMsgID CreateMsgIDByType(Type type)
        {
            try
            {
                Assembly asm = Assembly.GetExecutingAssembly();
                Object obj = asm.CreateInstance(type.FullName, true);
                if (obj != null)
                {
                    CMsg msg = (CMsg)obj;
                    if (msg != null)
                    {
                        return msg.MsgID;
                    }
                }
                return null;
            }
            catch (System.Exception)
            {
                return null;
            }
        }

        private Hashtable m_hashtable = new Hashtable();
    }
}
