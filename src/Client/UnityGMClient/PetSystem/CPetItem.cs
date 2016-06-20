using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{

    public class CPetItem
    {
        private UInt32 m_petID = 0;
        private UInt32 m_petTPID = 0;
        private UInt32 m_petFriendlyValue = 0;
        private UInt32 m_maxPetFriendlyValue = 0;
        private UInt32 m_petFriendlyLevel = 0;
        private UInt32 m_leftTime = 0;
        private EPetStatus m_petStatus = EPetStatus.EPetStatusInvalid;
        private EHotSpringType m_hotSpringType = EHotSpringType.EInvalidHotSpring;
        private EHotSpringTaskStatus m_petTaskType = EHotSpringTaskStatus.EHotSpringInvalidTask;
        private EHotSpringTaskType m_hotSpringTaskType = EHotSpringTaskType.EHotSpringTaskTypeInvalid;
        private CBattleAttribute m_petBattleAttribute = new CBattleAttribute();
        private CBattleAttribute m_petGrowUpAttribute = new CBattleAttribute();

        public CBattleAttribute PetGrowUpAttribute
        {
            get { return m_petGrowUpAttribute; }
            set { m_petGrowUpAttribute = value; }
        }
        private UInt32 m_combat = 0;

        public UInt32 Combat
        {
            get { return m_combat; }
            set { m_combat = value; }
        }

        public EHotSpringType HotSpringType
        {
            get { return m_hotSpringType; }
            set { m_hotSpringType = value; }
        }

        public EHotSpringTaskStatus PetTaskType
        {
            get { return m_petTaskType; }
            set { m_petTaskType = value; }
        }

        public EHotSpringTaskType HotSpringTaskType
        {
            get { return m_hotSpringTaskType; }
            set { m_hotSpringTaskType = value; }
        }

        public UInt32 LeftTime
        {
            get { return m_leftTime; }
            set { m_leftTime = value; }
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

        public UInt32 PetFriendlyLevel
        {
            set { m_petFriendlyLevel = value; }
            get { return m_petFriendlyLevel; }
        }

        public UInt32 MaxPetFriendlyValue
        {
            set { m_maxPetFriendlyValue = value; }
            get { return m_maxPetFriendlyValue; }
        }

        public UInt32 PetFriendlyValue
        {
            set { m_petFriendlyValue = value; }
            get { return m_petFriendlyValue; }
        }

        public EPetStatus PetStatus
        {
            set { m_petStatus = value; }
            get { return m_petStatus; }
        }

        public CBattleAttribute BattelAttribute 
        {
            set { m_petBattleAttribute = value; }
            get { return m_petBattleAttribute; }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_petID = msgStream.ReadUInt();
            m_petTPID = msgStream.ReadUInt();
            m_petFriendlyLevel = msgStream.ReadUInt();
            m_petFriendlyValue = msgStream.ReadUInt();
            m_maxPetFriendlyValue = msgStream.ReadUInt();
            m_petStatus = (EPetStatus)msgStream.ReadUInt();
            m_hotSpringType = (EHotSpringType)msgStream.ReadUInt();
            m_petTaskType = (EHotSpringTaskStatus)msgStream.ReadUInt();
            m_hotSpringTaskType = (EHotSpringTaskType)msgStream.ReadUInt();
            m_leftTime = msgStream.ReadUInt();
            m_petBattleAttribute.SerializeFrom(msgStream);
            m_petGrowUpAttribute.SerializeFrom(msgStream);
            // 战斗力公式 i.	战斗力=攻击力*2 + 防御力 + 生命值/5 + 命中/5 + 闪避/2 + 暴击/2 + 抗暴/5 
            m_combat = m_petBattleAttribute.Atk * 2
                + m_petBattleAttribute.Def
                + m_petBattleAttribute.MaxHP / 5
                + m_petBattleAttribute.AtkCrift / 2
                + m_petBattleAttribute.DefCrift / 5
                + m_petBattleAttribute.HitRate / 5
                + m_petBattleAttribute.MissRate / 2;
            return true;
        }

        public string getLogString()
        {
            string lg = "";
          
            lg += "\r\n";
                lg += "PetID:" + PetID + " ";
                lg += "TPID:" + PetTPID + " ";
                lg += "lv" + PetFriendlyLevel + ",";
                lg += "亲密度:" + PetFriendlyValue + "/" + MaxPetFriendlyValue + ",";
                lg += "状态：" + PetStatus.ToString() + "\r\n";
                lg += "温泉类型:" + m_hotSpringType.ToString() + "\r\n";
                lg += "温泉任务类型:" + m_petTaskType.ToString() + " 温泉任务子类型:" + m_hotSpringTaskType.ToString() + "\r\n";
                lg += "温泉完成剩余时间:" + getLeftTime(m_leftTime) + "\r\n";
                lg += "伙伴属性：" + m_petBattleAttribute.getLogString()+ "\r\n";
                lg += "成长属性：" + m_petGrowUpAttribute.getLogString() + "\r\n";
                lg += "m_combat：" + m_combat + "\r\n";
            return lg;
        }

        private string getLeftTime(UInt32 a_time)
        {
            UInt32 hours = a_time / 3600;
            UInt32 mins = (a_time % 3600)/60;
            UInt32 seconds = (a_time % 3600) % 60;
            string time = hours + "小时" + mins + "分" + seconds +"秒";
            return time;
        }
    }
}
