using System;
using System.Text;
using System.Collections.Generic;

namespace UnityGMClient
{

    /// <summary>
    /// 背包
    /// </summary>
    public class CBagData
    {
        private UInt32 m_bagSize;
        private UInt32 m_bagItemCount;
        List<CBagItem> m_itemList = new List<CBagItem>();

        public UInt32 BagSize
        {
            get { return m_bagSize; }
            set { m_bagSize = value; }
        }

        public UInt32 BagItemCount
        {
            get { return m_bagItemCount; }
            set { m_bagItemCount = value; }
        }

        public void AddBagItem(CBagItem bagItem)
        {
            if (bagItem == null)
            {
                return;
            }
            m_itemList.Add(bagItem);
        }

        public void RemoveAll()
        {
            m_itemList.Clear();
        }

        public List<CBagItem> getBagList()
        {
            return m_itemList;
        }

        private bool _updateItem(CItem a_item)
        {
            if (a_item.ItemCount == 0)
            {
                _deleteItem(a_item.ItemIndex);
                return true;
            }
             for (int i = 0; i < m_itemList.Count; ++i)
             {
                 if (m_itemList[i].ItemData.ItemIndex == a_item.ItemIndex)
                 {
                     m_itemList[i].ItemData = a_item;
                     return true;
                 }
             }
             return false;
        }
        public void UpdateBagItem(CItem Item)
        {
            if (!_updateItem(Item))
            {
                 CBagItem newitem = new CBagItem();
                 newitem.ItemData = Item;
                 AddBagItem(newitem);
            }
        }

        public bool getBagIndex(CItem a_item,out UInt32 a_index)
        {
            for (int i = 0; i < m_itemList.Count; ++i)
            {
                if (m_itemList[i].ItemData.ItemIndex == a_item.ItemIndex)
                {
                    a_index = (UInt32)i;
                    return true;
                }
            }
            a_index = 0;
            return false;
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_bagSize = msgStream.ReadUInt();
            m_bagItemCount = msgStream.ReadUInt();
            for (int i = 0; i < m_bagItemCount; i++)
            {
                CBagItem bagItem = new CBagItem();
                bagItem.SerializeFrom(msgStream);
                AddBagItem(bagItem);
            }
            return true;
        }

        private bool _deleteItem(UInt32 a_positionIndex)
        {
            for (int i = 0; i < m_itemList.Count; ++i)
            {
                if (m_itemList[i].ItemData.ItemIndex == a_positionIndex)
                {
                    m_itemList.RemoveAt(i);
                    return true;
                }
            }

            return false;
        }

        public string getLogString()
        {
            UnityGMClient.CBagData bagData = this;
            string lg = "bagSize:" + this.BagItemCount + "/" + this.BagSize + "\r\n";
            for (int i = 0; i < m_itemList.Count; ++i)
            {
                UnityGMClient.CBagItem srcItem = m_itemList[i];
                lg += "[" + i + "] " + srcItem.getLogString();
            }
            return lg;
        }
    }
}
