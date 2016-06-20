using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CRole
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
        private UInt32 m_roleMaxVitality = 0;
        private UInt32 m_rolePOP = 0;

        private UInt32 m_roleSkillPoint= 0;
        private UInt32 m_roleHP = 0;
        private UInt32 m_roleSP = 0;

        private UInt32 m_roleLightPower = 0;

        private UInt64 m_gold = 0;
        private UInt64 m_exp = 0;

        CBattleAttribute m_roleBattleAttr = new CBattleAttribute();
        private UInt32 m_combat = 0;
        private UInt32 m_historyMaxCombatPower = 0;
        private UInt32[] m_equipID = new UInt32[CEquipDefine.g_roleMaxEquipCount];
        private UInt32[] m_equipTPID = new UInt32[CEquipDefine.g_roleMaxEquipCount];
        public CBattleAttribute getBattleAttr()
        {
            return m_roleBattleAttr;
        }

        public void setBattleAttr(CBattleAttribute battleAttr)
        {
            m_roleBattleAttr.Atk = battleAttr.Atk;
            m_roleBattleAttr.Def = battleAttr.Def;

            m_roleBattleAttr.AtkCrift = battleAttr.AtkCrift;
            m_roleBattleAttr.DefCrift = battleAttr.DefCrift;

            m_roleBattleAttr.HitRate = battleAttr.HitRate;
            m_roleBattleAttr.MissRate = battleAttr.MissRate;
            m_roleBattleAttr.MaxHP = battleAttr.MaxHP;
        }

        private UInt32 m_SenceID = 0;

        public SRoleKey RoleKey
        {
            get { return m_roleKey; }
            set { m_roleKey = value; }
        }

        public void updateUInt64Value(ERoleAttributeIndex a_attributeID, UInt64 value)
        {
            switch (a_attributeID)
            {
                case ERoleAttributeIndex.ATTR_EXP:  { m_exp = value; } break;
                case ERoleAttributeIndex.ATTR_GOLD: { m_gold = value; } break;
            }
        }

        public void updateUInt32Value(ERoleAttributeIndex a_attributeID, UInt32 value)
        {
            switch (a_attributeID)
            {
                case ERoleAttributeIndex.ATTR_SCENEID:       { m_SenceID = value; }        break;
                case ERoleAttributeIndex.ATTR_LEVEL:         
                    { 
                        m_roleLevel = value;
                        m_roleMaxVitality = _getMaxVitality(m_roleLevel);
                    }
                    break;
                case ERoleAttributeIndex.ATTR_QUALITY:       { m_roleQuality = value; }    break;
                case ERoleAttributeIndex.ATTR_STARLEVEL:     { m_roleStarLevel = value; }  break;
                case ERoleAttributeIndex.ATTR_PVPCOIN:       { m_rolePVPCoin = value; }    break;
                case ERoleAttributeIndex.ATTR_DIAMOND:       { m_roleDiamond = value; }    break;
                case ERoleAttributeIndex.ATTR_POP:           { m_rolePOP = value; }        break;
                case ERoleAttributeIndex.ATTR_SKILLPOINT:    { m_roleSkillPoint = value; } break;
                case ERoleAttributeIndex.ATTR_HP:            { m_roleHP = value; }         break;
                case ERoleAttributeIndex.ATTR_SP:            { m_roleSP = value; }         break;
                case ERoleAttributeIndex.ATTR_VITALITY:      { m_roleVitality = value; }   break;
                case ERoleAttributeIndex.ATTR_MAX_VITALITY:  { m_roleMaxVitality = value; }break;
                case ERoleAttributeIndex.ATTR_VIP_SCORE:     { m_roleVipScore = value; }   break;
                case ERoleAttributeIndex.ATTR_VIP_LEVEL:     { m_roleVipLevel = value; }   break;
                case ERoleAttributeIndex.ATTR_ACTIVE_DEGREE: { m_roleActiveDegree = value;}break;
                case ERoleAttributeIndex.ATTR_LIGHT_POWER:   { m_roleLightPower = value; } break;
                default:                                     { }                           break;
            }
        }

        public UInt32 getValue(ERoleAttributeIndex a_attributeID)
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
                case ERoleAttributeIndex.ATTR_MAX_VITALITY:  { return m_roleMaxVitality; }
                case ERoleAttributeIndex.ATTR_VIP_SCORE:     { return m_roleVipScore; }
                case ERoleAttributeIndex.ATTR_VIP_LEVEL:     { return m_roleVipLevel; }
                case ERoleAttributeIndex.ATTR_ACTIVE_DEGREE: { return m_roleActiveDegree; }
                case ERoleAttributeIndex.ATTR_LIGHT_POWER:   { return m_roleLightPower; }
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

        public void setQuality(UInt32 value)
        {
            m_roleQuality = value;
        }

        public void setVitality(UInt32 value)
        {
            m_roleVitality = value;
        }

        public void setMaxVitality(UInt32 value)
        {
            m_roleMaxVitality = value;
        }

        public void setExp(UInt64 value)
        {
            m_exp = value;
        }

        public void setGold(UInt64 value)
        {
            m_gold = value;
        }

        public void setLightPower(UInt32 value)
        {
            m_roleLightPower = value;
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

        public UInt32 getMaxVitality()
        {
            return m_roleMaxVitality;
        }

        public UInt64 getExp()
        {
            return m_exp;
        }

        public UInt64 getGold()
        {
            return m_gold;
        }

        public UInt32 getLightPower()
        {
            return m_roleLightPower;
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

        public UInt32 getCombat()
        {
            return m_combat;
        }

        public void setCombat(UInt32 a_combat)
        {
            m_combat = a_combat;
        }

        public UInt32 getHistoryMaxCombatPower()
        {
            return m_historyMaxCombatPower;
        }

        public void setHistoryMaxCombatPower(UInt32 combat)
        {
            m_historyMaxCombatPower = combat;
        }


        private UInt32 _getMaxVitality(UInt32 a_level)
        {
            UInt32 maxVitality = 200 + (a_level * 2 + 5) / 10;
            return maxVitality;
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
            m_roleMaxVitality =_getMaxVitality(m_roleLevel);
            setExp(roleStream.ReadULong());
            setGold(roleStream.ReadULong());
            setLightPower(roleStream.ReadUInt());

            setQuality(roleStream.ReadUInt());
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
            setCombat(roleStream.ReadUInt());
            m_historyMaxCombatPower = roleStream.ReadUInt();
            for (uint i = 0; i < CEquipDefine.g_roleMaxEquipCount; ++i)
            {
                m_equipID[i] = roleStream.ReadUInt();
            }
            for (uint i = 0; i < CEquipDefine.g_roleMaxEquipCount; ++i)
            {
                 m_equipTPID[i] = roleStream.ReadUInt();
            }
        }

        public UInt32 getEquipTPID(EEquipType a_equipType)
        {
            uint index = _getEquipIndex(a_equipType);
            if (!_isEquipIndex(index))
            {
                return 0;
            }
            return m_equipTPID[index];
        }

        public bool setEquipTPID(EEquipType a_equipType, UInt32 a_equipTPID)
        {
            uint index = _getEquipIndex(a_equipType);
            if (!_isEquipIndex(index))
            {
                return false;
            }
            m_equipTPID[index] = a_equipTPID;
            return true;
        }

        public UInt32 getEquipID(EEquipType a_equipType)
        {
            uint index = _getEquipIndex(a_equipType);
            if (!_isEquipIndex(index))
            {
                return 0;
            }
            return m_equipID[index];
        }

        public bool setEquipID(EEquipType a_equipType,UInt32 a_equipID)
        {
            uint index = _getEquipIndex(a_equipType);
            if (!_isEquipIndex(index))
            {
                return false;
            }
            m_equipID[index] = a_equipID;
            return true;
        }

        private uint _getEquipIndex(EEquipType a_equipType)
        {
            uint id = (uint)a_equipType;
            uint index = id - 1;
            return index;
        }

        private bool _isEquipIndex(uint a_index)
        {
            if ((a_index < 0) || (a_index >= CEquipDefine.g_roleMaxEquipCount))
            {
                return false;
            }
            return true;
        }

        public string getLogString()
        {
            string lg = "";
                lg = "[m_accountID=" + RoleKey.m_accountID + "]\r\n"
                + "[m_zoneID=" + RoleKey.m_zoneID + "]\r\n"
                + "[m_roleIndex=" + RoleKey.m_roleIndex + "]\r\n"
                + "[roleName=" + getRoleName() + "]\r\n"
                + "[RoleID:" + getRoleID() + "]\r\n"
                + "[RoleTPID:" + getRoleTPID() + "]\r\n"
                + "[Level:" + getLevel() + "]\r\n"

                + "[SkillPoint:" + getSkillPoint() + "]\r\n"
                + "[PVPCoin:" + getPVPCoin() + "]\r\n"
                + "[Vitality:" + getVitality() + "]\r\n"
                + "[MaxVitality:" + getMaxVitality() + "]\r\n"
                + "[Gold:" + getGold() + "]\r\n"
                + "[Exp:" + getExp() + "]\r\n"
                + "[Diamand:" + getDiamond() + "]\r\n"
                + "[vipScore:" + getVipScore() + "]\r\n"
                + "[vipLevel:" + getVipLevel() + "]\r\n"
                + "[activeDegree:" + getActiveDegree() + "]\r\n";
                lg += "[Combat:" + getCombat() + "]\r\n";
                lg += "[" + m_roleBattleAttr.getLogString() + "]\r\n";
                for (uint i = 0; i < CEquipDefine.g_roleMaxEquipCount; ++i)
                {
                    lg += "[m_equipID[" + ((EEquipType)(i + 1)).ToString() + "]:" + m_equipID[i] + "]\r\n";
                }
            return lg;
        }
    }
}
