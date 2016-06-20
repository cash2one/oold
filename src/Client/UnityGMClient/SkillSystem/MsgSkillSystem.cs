using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CSkillDefine
    {
            public const int SKILL_BUTTON_COUNT = 4;
    }

    class CSkillSystemMsgNumID
    {
        public const uint EMSGNUMID_SKILLSYSTEM_GC2GM_REQ_LEARN_SKILL = 1;
	    public const uint EMSGNUMID_SKILLSYSTEM_GM2GC_ACK_LEARN_SKILL = 2;

	    public const uint EMSGNUMID_SKILLSYSTEM_GC2GM_REQ_UPGRADE_SKILL = 3;
	    public const uint EMSGNUMID_SKILLSYSTEM_GM2GC_ACK_UPGRADE_SKILL = 4;

        public const uint EMSGNUMID_SKILLSYSTEM_GM2GC_REQ_INIT_ROLE_SKILLDATA = 5;
	    public const uint EMSGNUMID_SKILLSYSTEM_GM2GC_ACK_INIT_ROLE_SKILLDATA = 6;

	    public const uint EMSGNUMID_SKILLSYSTEM_GC2GM_REQ_SET_SKILL_BUTTON = 7;
        public const uint EMSGNUMID_SKILLSYSTEM_GC2GM_ACK_SET_SKILL_BUTTON = 8;
    }

    class CMsgSkillSystemGC2GMReqLearnSkill : UnityFrame.CMsg
    {
        public CMsgSkillSystemGC2GMReqLearnSkill(UInt32 skillTPID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SKILLPSYSTEM, CSkillSystemMsgNumID.EMSGNUMID_SKILLSYSTEM_GC2GM_REQ_LEARN_SKILL)
        {
            m_skillTPID = skillTPID;
        }

        public UInt32 m_skillTPID = 0;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_skillTPID);
            return true;
        }
    }

    class CMsgSkillSystemGM2GCAckLearnSkill : UnityFrame.CMsg
    {
        public byte m_result;
        public UInt32 m_skillTPID;
        static public CClientCore.CBMsgSkillSystemGM2GCAckLearnSkill s_cb = null;

        public CMsgSkillSystemGM2GCAckLearnSkill()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SKILLPSYSTEM, CSkillSystemMsgNumID.EMSGNUMID_SKILLSYSTEM_GM2GC_ACK_LEARN_SKILL)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = msgStream.ReadByte();
            m_skillTPID = msgStream.ReadUInt();
            return true;
        }

        static public void CallBack(CMsgSkillSystemGM2GCAckLearnSkill msg)
        {
            if (msg != null) 
            {
                if (s_cb != null) 
                {
                    s_cb((UnityGMClient.ELearnSkillError)msg.m_result, msg.m_skillTPID);
                }
            }
        }
    }

    class CMsgSkillSystemGC2GMReqUpgradeSkill : UnityFrame.CMsg
    {
        public CMsgSkillSystemGC2GMReqUpgradeSkill(UInt32 skillTPID)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SKILLPSYSTEM, CSkillSystemMsgNumID.EMSGNUMID_SKILLSYSTEM_GC2GM_REQ_UPGRADE_SKILL)
        {
            m_skillTPID = skillTPID;
        }

        private UInt32 m_skillTPID = 0;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_skillTPID);
            return true;
        }
    }

    class CMsgSkillSystemGM2GCAckUpgradeSkill : UnityFrame.CMsg
    {
        public byte m_result;
        public UInt32 m_skillTPID;
        static public CClientCore.CBMsgSkillSystemGM2GCAckUpgradeSkill s_cb = null;

        public CMsgSkillSystemGM2GCAckUpgradeSkill()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SKILLPSYSTEM, CSkillSystemMsgNumID.EMSGNUMID_SKILLSYSTEM_GM2GC_ACK_UPGRADE_SKILL)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = msgStream.ReadByte();
            m_skillTPID = msgStream.ReadUInt();
            return true;
        }

        static public void CallBack(CMsgSkillSystemGM2GCAckUpgradeSkill msg)
        {
            if (msg != null) 
            {
                if (s_cb != null) 
                {
                    s_cb((UnityGMClient.EUpgradeSkillError)msg.m_result, msg.m_skillTPID);
                }
            }
        }
    }


    class CMsgSkillSystemGM2GCAckInitRoleSkillData : UnityFrame.CMsg
    {

        public List<CSkill> m_listSkill = new List<CSkill>();
        UInt32[] m_skillButtons = new UInt32[CSkillDefine.SKILL_BUTTON_COUNT];
        static public CClientCore.CBMsgSkillSystemGM2GCAckInitRoleSkillData s_cb = null;

        public CMsgSkillSystemGM2GCAckInitRoleSkillData()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SKILLPSYSTEM, CSkillSystemMsgNumID.EMSGNUMID_SKILLSYSTEM_GM2GC_ACK_INIT_ROLE_SKILLDATA)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            UInt16 size = msgStream.ReadUShort();
            if (size > 0) {
                for (UInt32 i = 0; i < size; ++i)
                {
                    CSkill skill = new CSkill();
                    skill.SerializeFrom(msgStream);
                    m_listSkill.Add(skill);
                }
            }

            for (int i = 0; i < CSkillDefine.SKILL_BUTTON_COUNT; ++i)
            {
                UInt32 skillTPID = msgStream.ReadUInt();
                m_skillButtons[i] = skillTPID;
            }

            return true;
        }

        static public void CallBack(CMsgSkillSystemGM2GCAckInitRoleSkillData msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                   s_cb(msg.m_listSkill, msg.m_skillButtons);
                }
            }
        }
    }

    class CMsgSkillSystemGC2GMReqSetSkillButton : UnityFrame.CMsg
    {
        public CMsgSkillSystemGC2GMReqSetSkillButton(UInt32 skillTPID, byte skillButtonIndex)
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SKILLPSYSTEM, CSkillSystemMsgNumID.EMSGNUMID_SKILLSYSTEM_GC2GM_REQ_SET_SKILL_BUTTON)
        {
            m_skillTPID = skillTPID;
            m_skillButtonIndex = skillButtonIndex;
        }

        private UInt32 m_skillTPID = 0;
        private byte m_skillButtonIndex = 0;
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_skillTPID);
            msgStream.Write(m_skillButtonIndex);
            return true;
        }
    }

    class CMsgSkillSystemGM2GCAckSetSkillButton : UnityFrame.CMsg
    {
        public byte m_result;
        public UInt32[] m_skillButtons = new UInt32[CSkillDefine.SKILL_BUTTON_COUNT];
        public static CClientCore.CBMsgSkillSystemGM2GCAckSetSkillButton s_cb = null;

        public CMsgSkillSystemGM2GCAckSetSkillButton()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SKILLPSYSTEM, CSkillSystemMsgNumID.EMSGNUMID_SKILLSYSTEM_GC2GM_ACK_SET_SKILL_BUTTON)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = msgStream.ReadByte();
            if ((ESetSkillButtonError)m_result == ESetSkillButtonError.SET_SKILL_BUTTON_SUCCESS)
            {
                for (Int32 i = 0; i < CSkillDefine.SKILL_BUTTON_COUNT; ++i)
                {
                    m_skillButtons[i] = msgStream.ReadUInt();
                }
            }


            return true;
        }

        static public void CallBack(CMsgSkillSystemGM2GCAckSetSkillButton msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb((UnityGMClient.ESetSkillButtonError)msg.m_result, msg.m_skillButtons);
                }
            }
        }
    }

}
