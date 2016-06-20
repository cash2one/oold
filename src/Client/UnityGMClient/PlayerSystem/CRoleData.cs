using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    /// <summary>
    /// 角色
    /// </summary>
    public class CRoleData
    {
        private SRoleKey m_roleKey = new SRoleKey();
        private string m_roleName = "";

        private UInt32 m_roleVipScore = 0;
        private UInt32 m_roleActiveDegree = 0;
        private UInt32 m_roleVipLevel = 0;
		
        private UInt64 m_roleID = 0;
        private UInt32 m_roleTPID = 0;

        private UInt32 m_roleLevel = 0;
        private UInt32 m_roleQuality = 0;

        private UInt32 m_roleStarLevel= 0;
        private UInt32 m_rolePVPCoin = 0;
        private UInt32 m_roleDiamond = 0;
        private UInt32 m_roleVitality = 0;
        private UInt32 m_rolePOP = 0;

        private UInt32 m_roleSkillPoint= 0;
        private UInt32 m_roleHP = 0;
        private UInt32 m_roleSP = 0;

        private UInt64 m_gold = 0;
        private UInt64 m_exp = 0;

        private UInt32 m_SenceID = 0;
        private UInt32 m_combat = 0;
        CBattleAttribute m_roleBattleAttr = new CBattleAttribute();
        private UInt32[] m_equipTPID = new UInt32[6];
        private UInt32[] m_equipLevel = new UInt32[6];

        public UInt32 Combat
        {
            get { return m_combat; }
            set { m_combat = value; }
        }

        public SRoleKey RoleKey
        {
            get { return m_roleKey; }
            set { m_roleKey = value; }
        }

        public CBattleAttribute RoleBattleAttribute
        {
            get { return m_roleBattleAttr; }
            set { m_roleBattleAttr = value; }
        }

        public UInt32 getEquipTPID(EEquipType a_equipType)
        {
            return m_equipTPID[(int)a_equipType];
        }

        public UInt32 getEquipLevel(EEquipType a_equipType)
        {
            return m_equipLevel[(int)a_equipType];
        }

        private void updateValue(ERoleAttributeIndex a_attributeID, UInt32 value)
        {
            switch (a_attributeID)
            {
                case ERoleAttributeIndex.ATTR_SCENEID:       { m_SenceID = value; }        break;
                case ERoleAttributeIndex.ATTR_LEVEL:         { m_roleLevel = value; }      break;
                case ERoleAttributeIndex.ATTR_QUALITY:       { m_roleQuality = value; }    break;
                case ERoleAttributeIndex.ATTR_STARLEVEL:     { m_roleStarLevel = value; }  break;
                case ERoleAttributeIndex.ATTR_PVPCOIN:       { m_rolePVPCoin = value; }    break;
                case ERoleAttributeIndex.ATTR_DIAMOND:       { m_roleDiamond = value; }    break;
                case ERoleAttributeIndex.ATTR_POP:           { m_rolePOP = value; }        break;
                case ERoleAttributeIndex.ATTR_SKILLPOINT:    { m_roleSkillPoint = value; } break;
                case ERoleAttributeIndex.ATTR_HP:            { m_roleHP = value; }         break;
                case ERoleAttributeIndex.ATTR_SP:            { m_roleSP = value; }         break;
                case ERoleAttributeIndex.ATTR_VITALITY:      { m_roleVitality = value; }   break;
                case ERoleAttributeIndex.ATTR_VIP_SCORE:     { m_roleVipScore = value; }       break;
                case ERoleAttributeIndex.ATTR_VIP_LEVEL:     { m_roleVipLevel = value; }       break;
                case ERoleAttributeIndex.ATTR_ACTIVE_DEGREE: { m_roleActiveDegree = value; }   break;
                default:                                     { }                           break;
            }
        }

        private UInt32 _getValue(ERoleAttributeIndex a_attributeID)
        {
            switch (a_attributeID)
            {
                case ERoleAttributeIndex.ATTR_SCENEID:       { return m_SenceID; }
                case ERoleAttributeIndex.ATTR_LEVEL:         { return m_roleLevel; }
                case ERoleAttributeIndex.ATTR_QUALITY:       { return m_roleQuality; }
                case ERoleAttributeIndex.ATTR_STARLEVEL:     { return m_roleStarLevel; }
                case ERoleAttributeIndex.ATTR_PVPCOIN:       { return m_rolePVPCoin; }
                case ERoleAttributeIndex.ATTR_DIAMOND:       { return m_roleDiamond; }
                case ERoleAttributeIndex.ATTR_POP:           { return m_rolePOP; }
                case ERoleAttributeIndex.ATTR_SKILLPOINT:    { return m_roleSkillPoint; }
                case ERoleAttributeIndex.ATTR_HP:            { return m_roleHP; }
                case ERoleAttributeIndex.ATTR_SP:            { return m_roleSP; }
                case ERoleAttributeIndex.ATTR_VITALITY:      { return m_roleVitality; }
                case ERoleAttributeIndex.ATTR_VIP_SCORE:     { return m_roleVipScore; }
                case ERoleAttributeIndex.ATTR_VIP_LEVEL:     { return m_roleVipLevel; }
                case ERoleAttributeIndex.ATTR_ACTIVE_DEGREE: { return m_roleActiveDegree; }
                default:                                     { return 0; }
            }
        }

        public void setRoleIndex(UInt32 roleIndex) 
        {
            m_roleKey.m_roleIndex = roleIndex;
        }

        public void setRoleID(UInt64 roleID)
        {
            m_roleID = roleID;
        }

        public void setRoleName(string roleName)
        {
            m_roleName = roleName;
        }

        public void setRoleLevel(UInt32 value)
        {
            m_roleLevel = value;
        }

        public void setPOP(UInt32 value)
        {
            m_rolePOP = value;
        }

        public void setSceneID(UInt32 value)
        {
            m_roleHP = value;
        }

        public void setHP(UInt32 value)
        {
            m_roleHP = value;
        }

        public void setSP(UInt32 value)
        {
            m_roleSP = value;
        }

        public void setVitality(UInt32 value)
        {
            m_roleVitality = value;
        }

        public void setExp(UInt64 value)
        {
            m_exp = value;
        }

        public void setGold(UInt64 value)
        {
            m_gold = value;
        }

        public void setRoleTPID(UInt32 value)
        {
            m_roleTPID = value; 
        }

        public void setDiamond(UInt32 value)
        {
            m_roleDiamond = value;
        }

        public void setSkillPoint(UInt32 value)
        {
            m_roleSkillPoint = value;
        }

        public void setPVPCoin(UInt32 value)
        {
            m_rolePVPCoin = value;
        }

        public void setStarLevel(UInt32 value)
        {
            m_roleStarLevel = value;
        }

        public void setVipLevel(UInt32 value)
        {
            m_roleVipLevel = value;
        }

        public void setVipScore(UInt32 value)
        {
            m_roleVipScore = value;
        }

        public void setActiveDegree(UInt32 value)
        {
            m_roleActiveDegree = value;
        }

        public UInt32 getRoleIndex() 
        {
            return m_roleKey.m_roleIndex;
        }

        public UInt64 getRoleID()
        {
            return m_roleID;
        }

        public string getRoleName() 
        {
            return m_roleName;
        }

        public UInt32 getLevel()
        {
            return m_roleLevel; 
        }

        public UInt32 getVipScore()
        {
            return m_roleVipScore;
        }

        public UInt32 getPVPCoin()
        {
            return m_rolePVPCoin; 
        }

        public UInt32 getVitality()
        {
            return m_roleVitality; 
        }

        public UInt64 getExp()
        {
            return m_exp;
        }

        public UInt64 getGold()
        {
            return m_gold;
        }

        public UInt32 getRoleTPID()
        {
            return m_roleTPID; 
        }

        public UInt32 getVipLevel()
        {
            return m_roleVipLevel; 
        }

        public UInt32 getActiveDegree()
        {
            return m_roleActiveDegree;
        }

        public UInt32 getDiamond()
        {
            return m_roleDiamond; 
        }

        public UInt32 getSkillPoint()
        {
            return m_roleSkillPoint; 
        }

        public void SerializeFrom(UnityUtility.CStream roleStream) 
        {
             m_roleKey.m_accountID = roleStream.ReadULong();
             m_roleKey.m_zoneID = roleStream.ReadUShort();
             m_roleKey.m_roleIndex = roleStream.ReadUInt();
             setRoleName(roleStream.ReadString());

             m_roleTPID = roleStream.ReadUInt();
             m_roleID = roleStream.ReadULong();
             m_roleLevel = roleStream.ReadUInt();
            setExp(roleStream.ReadULong());
            setGold(roleStream.ReadULong());

            setVitality(roleStream.ReadUInt());
            setStarLevel(roleStream.ReadUInt());
            setPVPCoin(roleStream.ReadUInt());
            setDiamond(roleStream.ReadUInt());
            setSkillPoint(roleStream.ReadUInt());

            setPOP(roleStream.ReadUInt());
            setVitality(roleStream.ReadUInt());

            setHP(roleStream.ReadUInt());
            setSP(roleStream.ReadUInt());
            setSceneID(roleStream.ReadUInt());
            setVipLevel(roleStream.ReadUInt());
            setVipScore(roleStream.ReadUInt());
            setActiveDegree(roleStream.ReadUInt());
            m_roleBattleAttr.SerializeFrom(roleStream);
            Combat = roleStream.ReadUInt();

            for (int i = 0; i < 6; i++)
            {
                m_equipTPID[i] = roleStream.ReadUInt();
                m_equipLevel[i] = roleStream.ReadUInt();
            }
        }

        public bool initData(CRole a_role)
        {
            if (a_role == null)
            {
                return false;
            }

            RoleKey = a_role.RoleKey;
            setRoleID(a_role.getRoleID());
            setRoleName(a_role.getRoleName());
            setExp(a_role.getExp());
            setGold(a_role.getGold());

            for (int i = (int)ERoleAttributeIndex.ATTR_VIP_SCORE; i < (int)(ERoleAttributeIndex.ATTR_VIP_LEVEL + 1); i++)
            {
                ERoleAttributeIndex attributeIndex = (ERoleAttributeIndex)i;
                updateValue(attributeIndex, a_role.getValue(attributeIndex));
            }

            return true;
        }
    }
}
