using System;
using System.Collections.Generic;
using System.Text;

namespace UnityFrame
{
    public class CMsg
    {
        public CMsg(uint msgID)
        {
            m_msgID = CMsgID.CreateMsgID(msgID); 
        }

        public CMsg(uint serverType, uint funcType, uint msgNumber)
        {
            m_msgID = CMsgID.CreateMsgID(serverType, funcType, msgNumber); 
        }

        public CMsgID MsgID
        {
            get
            {
                return m_msgID;
            }
        }

        //把数据序列化到msgBuffer中
        public bool SerializeTo(UnityUtility.CStream msgStream)
        {
            try
            {
                return _SerializeTo(msgStream);
            }
            catch (System.Exception)
            {
                UnityUtility.CTrace.Singleton.debug("SerializeTo[{0}.{1}.{2}][{3}]失败", m_msgID.ServerType.ServerType, m_msgID.FuncType.FuncType, m_msgID.MsgNumber, this.ToString());
                return false;
            }
        }

        //从msgBuffer中序列化数据
        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            try
            {
                return _SerializeFrom(msgStream);
            }
            catch (System.Exception)
            {
                UnityUtility.CTrace.Singleton.debug("SerializeFrom[{0}.{1}.{2}][{3}]失败", m_msgID.ServerType.ServerType, m_msgID.FuncType.FuncType, m_msgID.MsgNumber, this.ToString());
                return false;
            }
        }

        protected virtual bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }

        //从msgBuffer中序列化数据
        protected virtual bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            return true;
        }

        private CMsgID m_msgID = null;
    }
}
