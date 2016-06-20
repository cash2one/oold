using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CTalkAnswer
    {
        private UInt32 m_answerID = 0;

        public UInt32 AnswerID
        {
            get { return m_answerID; }
            set { m_answerID = value; }
        }

        private string m_answer = "";

        public string Answer
        {
            get { return m_answer; }
            set { m_answer = value; }
        }
        private List<CTalkItem> m_answerSubList = new List<CTalkItem>();

        public List<CTalkItem> AnswerSubList
        {
            get { return m_answerSubList; }
            set { m_answerSubList = value; }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_answerID = msgStream.ReadUInt();
            m_answer = msgStream.ReadString();
            UInt32 answerCount = msgStream.ReadUInt();
            for (UInt32 i = 0; i < answerCount; ++i)
            {
                CTalkItem item = new CTalkItem();
                item.SerializeFrom(msgStream);
                m_answerSubList.Add(item);
            }
            return true;
        }
        public string getLogString()
        {
            string lg = "";
            lg += "m_answerID=" + m_answerID + " ";
            lg += "m_answer=" + m_answer + " ";
            lg += "\r\n";
            UInt32 count = (UInt32)m_answerSubList.Count;
            for (UInt32 i = 0; i < count; ++i)
            {
                CTalkItem item = m_answerSubList[(int)i];
                lg += item.getLogString();
            }
            lg += "\r\n";
            return lg;
        }
    }
}
