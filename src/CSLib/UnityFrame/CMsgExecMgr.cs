using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;

namespace UnityFrame
{
    public class CMsgExecMgr
    {
        public delegate void ParseMessageCallback(CMsg msg);

        public CMsgFactory MsgFactory
        {
            set
            {
                m_msgFactory = value;
            }
        }

        public bool AddParseMsgCb(Type type, ParseMessageCallback parsMsgCb)
        {
            try
            {
                if (m_msgFactory == null)
                {
                    return false;
                }
                CMsgID msgID = m_msgFactory.CreateMsgIDByType(type);
                if (msgID == null)
                {
                    return false;
                }
                if (m_hashtable.ContainsKey(msgID.MsgID))
                {
                    return false;
                }
                m_msgFactory.AddMsgType(type);
                m_hashtable.Add(msgID.MsgID, parsMsgCb);
            }
            catch (System.Exception)
            {
                return false;
            }
            return true;
        }

        public bool AddParseMsgCb(CMsgID msgID, ParseMessageCallback parsMsgCb)
        {
            try
            {
                if (m_hashtable.ContainsKey(msgID.MsgID))
                {
                    return false;
                }
                m_hashtable.Add(msgID.MsgID, parsMsgCb);
            }
            catch (System.Exception)
            {
                return false;
            }
            return true;
        }

        public void DelParseMsgCb(CMsgID msgID)
        {
            try
            {
                if (!m_hashtable.ContainsKey(msgID.MsgID))
                {
                    return;
                }
                m_hashtable.Remove(msgID.MsgID);
            }
            catch (System.Exception)
            {
                ;
            }
        }

        public bool DelParseMsgCb(Type type)
        {
            try
            {
                CMsgID msgID = m_msgFactory.CreateMsgIDByType(type);
                if (msgID == null)
                {
                    return false;
                }
                if (m_hashtable.ContainsKey(msgID.MsgID))
                {
                    m_hashtable.Remove(msgID.MsgID);
                }

                m_msgFactory.DelMsgType(type);
                
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool ParseMessage(CMsg msg)
        {
            try
            {
                if (!m_hashtable.ContainsKey(msg.MsgID.MsgID))
                {
                    return false;
                }
                ParseMessageCallback parsMsgCb = (ParseMessageCallback)m_hashtable[msg.MsgID.MsgID];
                parsMsgCb(msg);
                return true;
            }
            catch (System.Exception e)
            {
                UnityUtility.CTrace.Singleton.error("处理消息ParseMessage[{0}]失败", e.ToString());
                return false;
            }
        }

        private CMsgFactory m_msgFactory = null;
        private Hashtable m_hashtable = new Hashtable();
    }
}