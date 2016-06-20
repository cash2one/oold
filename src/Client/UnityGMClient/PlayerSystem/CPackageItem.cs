using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    enum eItemType
    {
        EITEMTYPE_EQUIP,
        EITEMTYPE_SPECIAL,
        EITEMTYPE_OTHER
    }

    public class CItem
    {
        private string m_ItemName = "";
        private UInt32 m_ItemTPID = 0 ;

        public void setItemName(string itemName)
        {
            m_ItemName = itemName;
        }

        public string getItemName()
        {
            return m_ItemName;
        }

        public void setItemTPID(UInt32 ItemTPID)
        {
            m_ItemTPID = ItemTPID;
        }

        public UInt32 getItemTPID()
        {
            return m_ItemTPID;
        }
    }

    /// <summary>
    /// 单个格子物品
    /// </summary>
     public class CPackageItem
    {
        private UInt32 m_PackageItemCount = 1;
        private UInt32 m_ItemIndex = 0;
        private CItem m_ItemData = null;

         /// <summary>
        /// 设置叠加个数
         /// </summary>
         /// <param name="itemCount"></param>
        public void setPackageItemCout(UInt32 itemCount)
        {
            m_PackageItemCount = itemCount;
        }
        
        /// <summary>
        /// 获取叠加个数
        /// </summary>
        /// <returns></returns>
        public UInt32 getPackageItemCount()
        {
            return m_PackageItemCount;
        }

        /// <summary>
        /// 设置格子中的索引
        /// </summary>
        /// <param name="itemIndex"></param>
        public void setPackageItemIndex(UInt32 itemIndex)
        {
            m_ItemIndex = itemIndex;
        }

         /// <summary>
         /// 获取格子索引
         /// </summary>
         /// <returns></returns>
        public UInt32 getPackageItemIndex()
        {
            return m_ItemIndex;
        }
        
        /// <summary>
        /// 设置背包数据
        /// </summary>
        /// <param name="ItemData"></param>
        public void setPackageItemData(CItem ItemData)
        {
            m_ItemData = ItemData;
        }

        /// <summary>
        /// 获取背包数目
        /// </summary>
        /// <returns></returns>
        public CItem getPackageItemData()
        {
            return m_ItemData ;
        }
    }
}
