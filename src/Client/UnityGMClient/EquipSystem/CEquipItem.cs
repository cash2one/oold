using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{

    public class CEquipItem
    {
        private UInt32 m_equipID = 0;
        private EEquipType m_equipType;
        private UInt32 m_equipTPID = 0;
        private EQualityID m_equipQuality = 0;
        private UInt32 m_equipLevel = 0;
        private UInt32 m_equipAddLevel = 0;
        private UInt32 m_gemSlotCount = 0;
        private EEquipStatus m_equipStatus = EEquipStatus.EQUIP_STATUS_OFF;
        private UInt32 m_gemsCount = 0;
        private List<CGem> m_gemsList = new List<CGem>();
        private UInt32 m_combat = 0;
        private UInt64 m_leftSeconds = 0;

        public UInt64 LeftSeconds
        {
            get { return m_leftSeconds; }
            set { m_leftSeconds = value; }
        }

        //战斗力
        public UInt32 Combat
        {
            get { return m_combat; }
            set { m_combat = value; }
        }

        // 宝石孔个数
        public UInt32 GemSlotCount
        {
            get { return m_gemSlotCount; }
            set { m_gemSlotCount = value; }
        }

        /// <summary>
        /// 装备强化属性
        /// </summary>
        public UInt32 EquipAddLevel
        {
            get { return m_equipAddLevel; }
            set { m_equipAddLevel = value; }
        }

        public EEquipStatus EquipStatus
        {
            get { return m_equipStatus; }
            set { m_equipStatus = value; }
        }
        
        private CBattleAttribute m_battleAttr = new CBattleAttribute();
        private CBattleAttribute m_attachBattleAttr = new CBattleAttribute();
        private CBattleAttribute m_addBattleAttr = new CBattleAttribute();
        private CAttachAttr m_attachAttr = new CAttachAttr();

        public CAttachAttr AttachAttr
        {
            get { return m_attachAttr; }
            set { m_attachAttr = value; }
        }

        /// <summary>
        /// 强化属性
        /// </summary>
        public CBattleAttribute AddBattleAttr
        {
            get { return m_addBattleAttr; }
            set { m_addBattleAttr = value; }
        }

        /// <summary>
        /// 附加属性
        /// </summary>
        private CBattleAttribute AttachBattleAttr
        {
            get { return m_attachBattleAttr; }
            set { m_attachBattleAttr = value; }
        }

        /// <summary>
        /// 主属性
        /// </summary>
        public CBattleAttribute BattleAttr
        {
            get { return m_battleAttr; }
            set { m_battleAttr = value; }
        }

        public UInt32 EquipID
        {
            set { m_equipID = value; }
            get { return m_equipID; }
        }

        public UInt32 EquipTPID
        {
            set { m_equipTPID = value; }
            get { return m_equipTPID; }
        }

        public EQualityID EquipQuality
        {
            get { return m_equipQuality; }
            set { m_equipQuality = value; }
        }

        public UInt32 EquipLevel
        {
            set { m_equipLevel = value; }
            get { return m_equipLevel; }
        }

        public EEquipType EquipType
        {
            set { m_equipType = value; }
            get { return m_equipType; }
        }

        public UInt32 GemsCount
        {
            set { m_gemsCount = value; }
            get { return m_gemsCount; }
        }

        public List<CGem> GemList
        {
            get { return m_gemsList; }
        }

        public void addGem(List<CGem> a_gemsList)
        {
            for (int i = 0; i < a_gemsList.Count; i++)
            {
                m_gemsList.Add(a_gemsList[i]);
            }
        }

        public void updateGem(List<CGem> a_gemsList)
        {
            m_gemsList.Clear();
            for (int i = 0; i < a_gemsList.Count; i++)
            {
                m_gemsList.Add(a_gemsList[i]);
            }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_equipID = msgStream.ReadUInt();
            m_equipType = (EEquipType)msgStream.ReadUInt();
            m_equipTPID = msgStream.ReadUInt();
            m_equipLevel = msgStream.ReadUInt();
            m_equipAddLevel = msgStream.ReadUInt();
            m_equipQuality = (EQualityID)msgStream.ReadUInt();
            m_leftSeconds = msgStream.ReadULong();
            m_equipStatus = (EEquipStatus)msgStream.ReadUInt();
            m_battleAttr.SerializeFrom(msgStream);
            m_attachAttr.SerializeFrom(msgStream);
            //m_attachBattleAttr.SerializeFrom(msgStream);
            m_attachAttr.getTotalAttach(ref m_attachBattleAttr);
            m_addBattleAttr.SerializeFrom(msgStream);
            m_gemSlotCount = msgStream.ReadUInt();
            m_gemsCount = msgStream.ReadUInt();
            for (int j = 0; j < m_gemsCount; ++j)
            {
                CGem equipGem = new CGem();
                equipGem.SerializeFrom(msgStream);
                m_gemsList.Add(equipGem);
            }
            m_combat = msgStream.ReadUInt();
            return true;
        }

        public string getLogString()
        {
            string lg = "";

            lg += "ID:" + m_equipID + ",";
            lg += "Type:" + m_equipType + ",";
            lg += "TPID:" + m_equipTPID + ",";
            lg += "Level:" + m_equipLevel + ",";
            lg += "AddLevel:" + m_equipAddLevel + ",";
            lg += "Quality:" + m_equipQuality + ",";
            lg += "EquipStatus:" + m_equipStatus + ",";
            
            lg += "\r\n";
            lg += "基础属性：" + m_battleAttr.getLogString() + "";
            lg += "附加属性：" + m_attachBattleAttr.getLogString() + "";
            lg += "附加属性：" + m_attachAttr.getLogString() + "";
            lg += "强化属性：" + m_addBattleAttr.getLogString() + "";
           
            lg += "宝石槽个数：" + m_gemSlotCount + " ";
            lg += "镶嵌宝石个数：" + m_gemsCount + " ";
            for (int j = 0; j < m_gemsList.Count; ++j)
            {
                CGem equipGem = m_gemsList[j];
                lg += "孔[" + equipGem.GemSlot + "]：" + equipGem.GemTPID;
            }
            lg += "Combat：" + m_combat + " ";
            lg += "\r\n";
            return lg;
        }
    }
}
