using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
   public class CAttribute
   {
       private UInt32 m_attrIndex = 0;

       public UInt32 AttrIndex
       {
           get { return m_attrIndex; }
           set { m_attrIndex = value; }
       }
       private EAttrID m_attrID = EAttrID.ATTR_INVALID;

       public EAttrID AttrID
       {
          get { return m_attrID; }
          set { m_attrID = value; }
       }

       private UInt32 m_attrValue = 0;

       public UInt32 AttrValue
       {
         get { return m_attrValue; }
         set { m_attrValue = value; }
       }

       private EQualityID m_quality;
       public EQualityID Quality
       {
           get { return m_quality; }
           set { m_quality = value; }
       }

       public void SerializeFrom(UnityUtility.CStream stream)
       {
           m_attrIndex = stream.ReadUInt();
           m_attrID = (EAttrID)stream.ReadUInt();
           m_attrValue = stream.ReadUInt();
           m_quality = (EQualityID)stream.ReadUInt();
       }

       public void SerializeTo(UnityUtility.CStream stream)
       {
           stream.Write(m_attrIndex);
           UInt32 attrID = (UInt32)m_attrID;
           stream.Write(attrID);
           stream.Write(m_attrValue);
           stream.Write((UInt32)m_quality);
       }
   }

   public class CAttachAttr
   {
       private UInt32 m_attrCount = 0;

       public UInt32 AttrCount
       {
           get { return m_attrCount; }
           set { m_attrCount = value; }
       }
       List<CAttribute> m_attrList = new List<CAttribute>();

       public List<CAttribute> AttrList
       {
           get { return m_attrList; }
           set { m_attrList = value; }
       }


       public bool getTotalAttach(ref CBattleAttribute battleAttr)
       {
           for (int i = 0; i < m_attrCount; ++i)
           {
               CAttribute attr = m_attrList[i];
               battleAttr.addValue(attr.AttrID, attr.AttrValue);
           }
           return true;
       }

       public void SerializeFrom(UnityUtility.CStream stream)
       {
           m_attrCount = stream.ReadUInt();
           for (int i = 0; i < m_attrCount; ++i)
           {
               CAttribute attr = new CAttribute();
               attr.SerializeFrom(stream);
               m_attrList.Add(attr);
           }
       }

       public string getLogString()
       {
           string lg = "m_attrCount:" + m_attrCount +  " ";
           for (int i = 0; i < m_attrCount; ++i)
           {
               CAttribute attr = m_attrList[i];
               lg += ",AttrIndex=" + attr.AttrIndex;
               lg += ",AttrID=" + attr.AttrID;
               lg += ",AttrValue=" + attr.AttrValue;
           }
           lg += " \r\n";
           return lg;
       }
   }

    public class CBattleAttribute
    {
        /// <summary>
        /// 攻击
        /// </summary>
        private UInt32 m_atk;
        /// <summary>
        /// 防御
        /// </summary>
        private UInt32 m_def;

        /// <summary>
        /// 暴击
        /// </summary>
        private UInt32 m_atkCrift;
        /// <summary>
        /// 抗暴
        /// </summary>
        private UInt32 m_defCrift;

        /// <summary>
        /// 命中
        /// </summary>
        private UInt32 m_hitRate;
        /// <summary>
        /// 闪避
        /// </summary>
        private UInt32 m_missRate;
        /// <summary>
        /// 生命
        /// </summary>
        private UInt32 m_maxHP;

        public UInt32 Atk
        {
            get { return m_atk; }
            set { m_atk = value; }
        }

        public UInt32 Def
        {
            get { return m_def; }
            set { m_def = value; }
        }

        public UInt32 AtkCrift
        {
            get { return m_atkCrift; }
            set { m_atkCrift = value; }
        }

        public UInt32 DefCrift
        {
            get { return m_defCrift; }
            set { m_defCrift = value; }
        }

        public UInt32 HitRate
        {
            get { return m_hitRate; }
            set { m_hitRate = value; }
        }

        public UInt32 MissRate
        {
            get { return m_missRate; }
            set { m_missRate = value; }
        }


        public UInt32 MaxHP
        {
            get { return m_maxHP; }
            set { m_maxHP = value; }
        }
        /// <summary>
        /// 设置角色数据
        /// </summary>
        /// <param name="roleStream"></param>
        public void SerializeFrom(UnityUtility.CStream stream)
        {
            m_atk = stream.ReadUInt();
            m_def = stream.ReadUInt();
            m_atkCrift = stream.ReadUInt();
            m_defCrift = stream.ReadUInt();

            m_hitRate = stream.ReadUInt();
            m_missRate = stream.ReadUInt();
            m_maxHP = stream.ReadUInt();
        }

        
    public UInt32 getValue(EAttrID a_attrID)
    {
        switch (a_attrID)
        {
        case EAttrID.ATTR_ATK: { return m_atk; }
        case EAttrID.ATTR_DEF: { return m_def; }

        case EAttrID.ATTR_ATK_CRIFT: { return m_atkCrift; }
        case EAttrID.ATTR_DEF_CRIFT: { return m_defCrift; }

        case EAttrID.ATTR_HIT_RATE: { return m_hitRate; }
        case EAttrID.ATTR_MISS_RATE: { return m_missRate; }
        case EAttrID.ATTR_MAXHP: { return m_maxHP; }
        default: { return 0; }
        }
    }

    public bool setValue(EAttrID a_attrID, UInt32 a_value)
    {
        switch (a_attrID)
        {
        case EAttrID.ATTR_ATK: { m_atk = a_value; } break;
        case EAttrID.ATTR_DEF: { m_def = a_value; } break;

        case EAttrID.ATTR_ATK_CRIFT: { m_atkCrift = a_value; } break;
        case EAttrID.ATTR_DEF_CRIFT: { m_defCrift = a_value; } break;

        case EAttrID.ATTR_HIT_RATE: { m_hitRate = a_value; } break;
        case EAttrID.ATTR_MISS_RATE: { m_missRate = a_value; } break;
        case EAttrID.ATTR_MAXHP: { m_maxHP = a_value; } break;
        default: { return false; }
        }
        return true;
    }

    public bool addValue(EAttrID a_attrID, UInt32 a_value)
    {
        switch (a_attrID)
        {
            case EAttrID.ATTR_ATK: { m_atk += a_value; } break;
            case EAttrID.ATTR_DEF: { m_def += a_value; } break;

            case EAttrID.ATTR_ATK_CRIFT: { m_atkCrift += a_value; } break;
            case EAttrID.ATTR_DEF_CRIFT: { m_defCrift += a_value; } break;

            case EAttrID.ATTR_HIT_RATE: { m_hitRate += a_value; } break;
            case EAttrID.ATTR_MISS_RATE: { m_missRate += a_value; } break;
            case EAttrID.ATTR_MAXHP: { m_maxHP += a_value; } break;
            default: { return false; }
        }
        return true;
    }

        public string getLogString()
        {
            string lg = "";

            if (m_atk != 0)
            {
                lg += "atk:" + m_atk + " ";
            }
            if (m_def != 0)
            {
                lg += "def:" + m_def + " ";
            }
            if (m_atkCrift != 0)
            {
                lg += "atkCrift:" + m_atkCrift + " ";
            }
            if (m_defCrift != 0)
            {
                lg += "defCrift:" + m_defCrift + " ";
            }

            if (m_hitRate != 0)
            {
                lg += "hitRate:" + m_hitRate + " ";
            }
            if (m_missRate != 0)
            {
                lg += "missRate:" + m_missRate + " ";
            }
            if (m_maxHP != 0)
            {
                lg += "maxHP:" + m_maxHP ;
            }
           
            lg += "\r\n";
            return lg;
        }
    }
}
