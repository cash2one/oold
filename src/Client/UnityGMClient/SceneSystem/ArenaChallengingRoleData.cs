using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CBattleRoleData
    {
        public UInt16 m_zoneID = 0;
        public UInt64 m_accountID = 0;
        public UInt32 m_roleIndex = 0;
        public UInt32 m_roleTPID = 0;
        public string  m_roleName;
        public UInt32 m_level = 0;
        public UInt32 m_combatPower = 0;
        public CBattleAttribute m_battleAttribute = new CBattleAttribute();
        public List<CSkill> m_listSkill = new List<CSkill>();
        public UInt32[] m_skillButtons = new UInt32[CSkillDefine.SKILL_BUTTON_COUNT];

        public void SerializeFrom(UnityUtility.CStream stream)
        {
            m_zoneID = stream.ReadUShort();
            m_accountID = stream.ReadULong();
            m_roleIndex = stream.ReadUInt();
            m_roleTPID = stream.ReadUInt();
            m_roleName = stream.ReadString();
            m_level = stream.ReadUInt();
            m_combatPower = stream.ReadUInt();
            m_battleAttribute.SerializeFrom(stream);
            UInt16 size = stream.ReadUShort();
            if (size > 0)
            {
                for (UInt32 i = 0; i < size; ++i)
                {
                    CSkill skill = new CSkill();
                    skill.SerializeFrom(stream);
                    m_listSkill.Add(skill);
                }
            }

            for (int i = 0; i < CSkillDefine.SKILL_BUTTON_COUNT; ++i)
            {
                UInt32 skillTPID = stream.ReadUInt();
                m_skillButtons[i] = skillTPID;
            }
        }

    };
}













