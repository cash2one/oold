using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    /// <summary>
    /// 玩家数据
    /// </summary>
    public class CPlayerData
    {
        private string m_accountName = "";
        private UInt32 m_vipScore= 0;
        private UInt32 m_roleCount = 0;
        private List<CRoleBaseInfo> m_roleList = new List<CRoleBaseInfo>();

        public string AccountName
        {
            get { return m_accountName; }
            set { m_accountName = value; }
        }

        public UInt32 VipScore
        {
            get { return m_vipScore; }
            set { m_vipScore= value; }
        }

        public UInt32 RoleCount
        {
            get { return m_roleCount; }
            set { m_roleCount = value; }
        }

        public List<CRoleBaseInfo> RoleList
        {
            get { return m_roleList; }
            set { m_roleList = value; }
        }

        public void addRole(CRoleBaseInfo role)
        {
            if (m_roleList == null)
            {
                m_roleList = new List<CRoleBaseInfo>();
            }
            m_roleList.Add(role);
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_accountName = msgStream.ReadString();
            m_vipScore= msgStream.ReadUInt();
            m_roleCount = msgStream.ReadUInt();
            m_roleList.Clear();
            for (UInt32 i = 0; i < m_roleCount; i++)
            {
                UnityUtility.CStream roleStream = msgStream;
                CRoleBaseInfo role = new CRoleBaseInfo();
                role.SerializeFrom(msgStream);
                addRole(role);
            }
            return true;
        }
    }
}
