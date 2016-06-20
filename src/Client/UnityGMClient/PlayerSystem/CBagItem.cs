using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
  public static class CItemTPID
    {
        public const UInt32 EITEM_TP_EQUIP_BEGIN = 1;
        public const UInt32 EITEM_TP_EQUIP_END = 100;

        public const UInt32 EITEM_TP_MATERIAL_BEGIN = 101;
        public const UInt32 EITEM_TP_MATERIAL_END = 1000;

        public const UInt32 EITEM_TP_PIECE_BEGIN = 1001;
        public const UInt32 EITEM_TP_PIECE_END = 10000;

        public const UInt32 EITEM_TP_PRO_BEGIN = 10001;
        public const UInt32 EITEM_TP_PRO_END = 100000;
        public static EBagType getItemType(EItemType a_itemType)
        {
            UInt32 type = (UInt32)a_itemType;
            if ((type >= CItemTPID.EITEM_TP_EQUIP_BEGIN) && (type <= CItemTPID.EITEM_TP_EQUIP_END))
            {
                return EBagType.EBAG_EQUIP;
            }
            else if ((type >= CItemTPID.EITEM_TP_PRO_BEGIN) && (type <= CItemTPID.EITEM_TP_PRO_END))
            {
                return EBagType.EBAG_ITEM;
            }
            else if ((type >= CItemTPID.EITEM_TP_MATERIAL_BEGIN) && (type <= CItemTPID.EITEM_TP_MATERIAL_END))
            {
                return EBagType.EBAG_MATERIAL;
            }
            else if ((type >= CItemTPID.EITEM_TP_PIECE_BEGIN) && (type <= CItemTPID.EITEM_TP_PIECE_END))
            {
                return EBagType.EBAG_PIECE;
            }

            return EBagType.EBAG_INVALID;
        }

        public static string getItemTypeName(EItemType type)
        {
            switch(type){
              case EItemType.EITEM_TP_EQUIP_WEAPONS: { return "武器"; }
              case EItemType.EITEM_TP_EQUIP_JADE: { return "玉佩"; }
              case EItemType.EITEM_TP_EQUIP_CAP: { return "头盔"; }
              case EItemType.EITEM_TP_EQUIP_ARMOR: { return "铠甲"; }
              case EItemType.EITEM_TP_EQUIP_GLOVE: { return "手套"; }
              case EItemType.EITEM_TP_EQUIP_SHOES: { return "战靴"; }
              case EItemType.EITEM_TP_EQUIP_NECKLACE: { return "项链"; }
              case EItemType.EITEM_TP_EQUIP_RING: { return "戒子"; }
              case EItemType.EITEM_TP_GEMS: { return "宝石"; }
            }
            EBagType bagType = getItemType(type);
            switch (bagType)
            {
                case EBagType.EBAG_EQUIP: { return "装备"; }
                case EBagType.EBAG_INVALID: { return "未知分类"; }
                case EBagType.EBAG_ITEM: { return "道具"; }
                case EBagType.EBAG_MATERIAL: { return "材料"; }
                case EBagType.EBAG_PIECE: { return "碎片"; }
            }
            return "";
        }
    }


    public class CItem
    {
        private UInt32 m_ItemIndex = 0;
        private UInt32 m_ItemTPID = 0;
        private EItemType m_ItemType = EItemType.EITEM_TP_IVALID;
        private UInt32 m_ItemCount = 0;

        private UInt32 m_addLevel = 0;
        private UInt32 m_instanceID = 0;

        public UInt32 InstanceID
        {
            get { return m_instanceID; }
            set { m_instanceID = value; }
        }
        private List<CGem> m_gemsList = new List<CGem>();

        public List<CGem> GemList
        {
            get { return m_gemsList; }
        }

        /// <summary>
        /// 强化等级 只对装备有效
        /// </summary>
        public UInt32 AddLevel
        {
            get { return m_addLevel; }
            set { m_addLevel = value; }
        }

        /// <summary>
        /// 配表物品ID
        /// </summary>
        public UInt32 ItemTPID
        {
            set { m_ItemTPID = value; }
            get { return m_ItemTPID; }
        }
        /// <summary>
        /// 叠加个数
        /// </summary>
        public UInt32 ItemCount
        {
            set { m_ItemCount = value; }
            get { return m_ItemCount; }
        }

        /// <summary>
        /// 物品类型
        /// </summary>
        public EItemType ItemType
        {
            set { m_ItemType = value; }
            get { return m_ItemType; }
        }

        /// <summary>
        /// 格子索引
        /// </summary>
        public UInt32 ItemIndex
        {
            set { m_ItemIndex = value; }
            get { return m_ItemIndex; }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_ItemIndex = msgStream.ReadUInt();
            m_ItemCount = msgStream.ReadUInt();
            m_ItemTPID = msgStream.ReadUInt();
            UInt32 type = msgStream.ReadUInt();
            m_ItemType = (EItemType)type;
            m_instanceID = msgStream.ReadUInt();
            m_addLevel = msgStream.ReadUInt();
            UInt32 gemsCount = msgStream.ReadUInt();
            for (int j = 0; j < gemsCount; ++j)
            {
                CGem equipGem = new CGem();
                equipGem.SerializeFrom(msgStream);
                m_gemsList.Add(equipGem);
            }
            return true;
        }

        public bool SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_ItemIndex);
            msgStream.Write(m_ItemCount);
            msgStream.Write(m_ItemTPID);
            msgStream.Write((uint)m_ItemType);
            return true;
        }

        public string getLogString()
        {
            string lg = "";
            lg += "m_ItemIndex:" + m_ItemIndex + " ";
            lg += "m_ItemTPID:" + m_ItemTPID + " ";
            lg += "m_ItemType:" + m_ItemType + " ";
            lg += "m_ItemCount:" + m_ItemCount + " ";
            lg += " [" + CItemTPID.getItemTypeName(m_ItemType) + "]\r\n";
            lg += "\r\n";

            lg += "m_instanceID:" + m_instanceID + " ";
            lg += "m_addLevel:" + m_addLevel + " ";
            lg += "gemsCount:" + m_gemsList.Count + " ";
            for (int j = 0; j < m_gemsList.Count; ++j)
            {
                CGem equipGem = m_gemsList[j];
                lg += "孔[" + equipGem.GemSlot + "]：" + equipGem.GemTPID;
            }
            lg += "\r\n";
            return lg;
        }
    }

    /// <summary>
    /// 单个格子物品
    /// </summary>
     public class CBagItem
    {
         private CItem m_itemData =  new CItem();

         /// <summary>
         /// 背包数据
         /// </summary>
         public CItem ItemData
         {
             set { m_itemData = value; }
             get { return m_itemData; }
         }

         public bool SerializeFrom(UnityUtility.CStream msgStream)
         { 
             m_itemData.SerializeFrom(msgStream);
             return true;
         }


         public bool SerializeTo(UnityUtility.CStream msgStream)
         {
             m_itemData.SerializeTo(msgStream);
             return true;
         }

         public string getLogString()
         {
             string lg = m_itemData.getLogString();
             return lg;
         }
    }
}
