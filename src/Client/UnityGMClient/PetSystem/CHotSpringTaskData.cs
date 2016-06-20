using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CHotSpringTaskData
    {
        private UInt32 m_petID = 0;
        private UInt32 m_petTPID = 0;
        private EHotSpringTaskType m_taskType = EHotSpringTaskType.EHotSpringTaskTypeInvalid;
        private UInt32 m_itemID = 0;
        private CTalkQuestion m_question = new CTalkQuestion();
        private List<CTalkAnswer> m_answerList = new List<CTalkAnswer>();

        public UInt32 ItemID
        {
            get { return m_itemID; }
            set { m_itemID = value; }
        }

        public CTalkQuestion Question
        {
            get { return m_question; }
            set { m_question = value; }
        }

        public List<CTalkAnswer> AnswerList
        {
            get { return m_answerList; }
            set { m_answerList = value; }
        }

        public UInt32 PetID
        {
            set { m_petID = value; }
            get { return m_petID; }
        }

        public UInt32 PetTPID
        {
            set { m_petTPID = value; }
            get { return m_petTPID; }
        }

        public EHotSpringTaskType TaskType
        {
            set { m_taskType = value; }
            get { return m_taskType; }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_petID = msgStream.ReadUInt();
            m_petTPID = msgStream.ReadUInt();
            m_taskType = (EHotSpringTaskType)msgStream.ReadUInt();
            m_itemID = msgStream.ReadUInt();
            m_question.SerializeFrom(msgStream);

            UInt32 answerCount = msgStream.ReadUInt();
            for (UInt32 i = 0; i < answerCount; ++i)
            {
                CTalkAnswer item = new CTalkAnswer();
                item.SerializeFrom(msgStream);
                m_answerList.Add(item);
            }
            return true;
        }

        public string getLogString()
        {
            string lg = "";
            lg += "\r\n";
            lg += "m_petID=" + m_petID + "\r\n";
            lg += "m_taskType=" + m_taskType.ToString() + "\r\n";
            lg += "m_itemID=" + m_itemID.ToString() + "\r\n";
            
            lg += m_question.getLogString();
            for (Int32 i = 0; i < m_answerList.Count; ++i)
            {
                CTalkAnswer item = m_answerList[i];
                lg += item.getLogString();
            }
            lg += "\r\n";
            return lg;
        }
    }
}
