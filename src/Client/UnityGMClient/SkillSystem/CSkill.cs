using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CSkill
    {
        private UInt32 m_skillTPID;
        private UInt32 m_skillLevel;
        
        public UInt32 SkillTPID
        {
            set 
            {
                m_skillTPID = value; 
            }

            get 
            { 
                return m_skillTPID; 
            }
        }

        public UInt32 SkillLevel
        {
            set 
            { 
                m_skillLevel = value; 
            }

            get 
            { 
                return m_skillLevel;  
            }
        }

        public void SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_skillTPID = msgStream.ReadUInt();
            m_skillLevel = msgStream.ReadUInt();
        }

    };
}
