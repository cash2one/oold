using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public enum EUserType
    {
        /// <summary>
        /// 主角
        /// </summary>
        EUserMe = 0,
        /// <summary>
        /// 伙伴
        /// </summary>
        EUserPet = 1,
    }
    public class CTalkQuestion
    {
        private List<CTalkItem> m_questionList = new List<CTalkItem>();

        public  List<CTalkItem> QuestionList
        {
            get { return m_questionList; }
            set { m_questionList = value; }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            UInt32 questionCount = msgStream.ReadUInt();
            for (UInt32 i = 0; i < questionCount; ++i)
            {
                CTalkItem item = new CTalkItem();
                item.SerializeFrom(msgStream);
                m_questionList.Add(item);
            }
            return true;
        }


        public string getLogString()
        {
            string lg = "";
            lg += "\r\n";
            UInt32 questionCount = (UInt32)m_questionList.Count;
            for (UInt32 i = 0; i < questionCount; ++i)
            {
                CTalkItem item = m_questionList[(int)i];
                lg += item.getLogString();
            }
            lg += "\r\n";
            return lg;
        }
    }
}
