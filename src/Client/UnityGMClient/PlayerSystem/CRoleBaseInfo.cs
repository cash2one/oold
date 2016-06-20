using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CRoleBaseInfo
    {
        public void SerializeFrom(UnityUtility.CStream roleStream)
        {
            m_roleIndex = roleStream.ReadUInt();
            m_roleTPID = roleStream.ReadUInt();
            m_roleLevel = roleStream.ReadUInt();
            m_roleName = roleStream.ReadString();
        }

        /// <summary>
        /// 设置角色索引
        /// </summary>
        /// <param name="roleIndex">角色索引</param>
        public void setRoleIndex(UInt32 roleIndex)
        {
            m_roleIndex = roleIndex;
        }

        /// <summary>
        /// 设置角色类型
        /// </summary>
        /// <param name="roleType">角色类型</param>
        public void setRoleTPID(UInt32 roleTPID)
        {
            m_roleTPID = roleTPID;
        }

        /// <summary>
        /// 设置角色名称
        /// </summary>
        /// <param name="roleName">角色名称</param>
        public void setRoleName(string roleName)
        {
            m_roleName = roleName;
        }

        /// <summary>
        /// 设置角色名称
        /// </summary>
        /// <param name="roleName">角色等级</param>
        public void setRoleLevel(UInt32 roleLevel)
        {
            m_roleLevel = roleLevel;
        }

        /// <summary>
        /// 获取角色索引
        /// </summary>
        /// <returns>角色索引</returns>
        public UInt32 getRoleIndex()
        {
            return m_roleIndex;
        }

        /// <summary>
        /// 获取角色类型
        /// </summary>
        /// <returns>角色类型</returns>
        public UInt32 getRoleTPID()
        {
            return m_roleTPID;
        }

        public UInt32 getLevel()
        {
            return m_roleLevel;
        }

        /// <summary>
        /// 获取角色名
        /// </summary>
        /// <returns>角色名</returns>
        public string getRoleName()
        {
            return m_roleName;
        }

        private string m_roleName = "";
        private UInt32 m_roleIndex = 0;
        private UInt32 m_roleTPID = 0;
        private UInt32 m_roleLevel = 0;
    }

}
