using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    /// <summary>
    /// 数据
    /// </summary>
    public class CAchieveData
    {
        private UInt32 m_achieveCount = 0;
        private EAchieveType m_achieveType;
        private List<CAchieveItem> m_achieveList = new List<CAchieveItem>();
        public UInt32 AchieveCount
        {
            get
            {
                return m_achieveCount;
            }
            set
            {
                m_achieveCount = value;
            }
        }
        public EAchieveType AchieveType
        {
            set { m_achieveType = value; }
            get { return m_achieveType; }
        }
        public List<CAchieveItem> AchieveList
        {
            get
            {
                return m_achieveList;
            }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_achieveType = (EAchieveType)msgStream.ReadUInt();
            m_achieveCount = msgStream.ReadUInt();
            for (int i = 0; i < m_achieveCount; ++i)
            {
                CAchieveItem item = new CAchieveItem();
                item.SerializeFrom(msgStream);
                m_achieveList.Add(item);
            }

            return true;
        }


        public string getAllAchieveToLogString()
        {
            string lg = "[type=" + m_achieveType.ToString()+"]";
            lg += "[count="+m_achieveCount+"]";
            lg += "\r\n"; 
            for (int i = 0; i < m_achieveList.Count; ++i)
            {
                CAchieveItem item = m_achieveList[i];
                lg += "[AchieveID=" + item.AchieveID + "]";
                lg += "[AchieveProgress=" + item.AchieveProgress + "]";
                lg += "[AchieveSubType=" + item.AchieveSubType + "]";
                lg += "[AchieveStatus=" + item.AchieveStatus + "]";
                lg += "\r\n"; 
            }
            return lg;
        }
    }
}
