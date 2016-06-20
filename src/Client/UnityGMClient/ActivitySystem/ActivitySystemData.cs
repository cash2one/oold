using System;
using System.Collections.Generic;
using System.Text;


namespace UnityGMClient
{
    public class CAttendenceAttr
    {
    	public UInt32 m_day = 0;
    	public UInt32 m_emoticonID = 0;
    	public bool m_isSpecialPrize = false;
    	public List<CPrizeItem> m_listPrizeItems = new List<CPrizeItem>();

    	public void serializeFrom(UnityUtility.CStream stream)
        {
            m_day = stream.ReadUInt();
            m_emoticonID = stream.ReadUInt();
            m_isSpecialPrize = (stream.ReadByte() == 1);
            UInt16 count = stream.ReadUShort();
            for (Int32 i = 0; i < count; ++i) 
            {
                CPrizeItem item = new CPrizeItem();
                item.SerializeFrom(stream);
                m_listPrizeItems.Add(item);
            }
        }
    };


    public class CRoleAttendenceData
    {
        public UInt32 m_startTime;
        public UInt32 m_endTime;
        public UInt32 m_attendenceCount;
        public List<CAttendenceAttr> m_listAttendenceAttr = new List<CAttendenceAttr>();

        public void serializeFrom(UnityUtility.CStream stream)
        {
            m_startTime = stream.ReadUInt();
            m_endTime = stream.ReadUInt();
            m_attendenceCount = stream.ReadUInt();
            UInt16 count = stream.ReadUShort();
            for (Int32 i = 0; i < count; ++i )
            {
                CAttendenceAttr attr = new CAttendenceAttr();
                attr.serializeFrom(stream);
                m_listAttendenceAttr.Add(attr);
            }
        }
    }

    public class CRolledItem
    {
        public bool m_isPet = false;
        public UInt32 m_TPID = 0;
        public UInt16 m_count = 0;

        public void serializeFrom(UnityUtility.CStream stream)
        {
            byte result = stream.ReadByte();
            m_isPet = result > 0;
            m_TPID = stream.ReadUInt();
            m_count = stream.ReadUShort();
        }
    }

    public class CDrawCardInfo
    {
        public Int32 m_nextFreeGoldDrawCardRemaindTime = 0;
        public Int32 m_nextFreeDiamondDrawCardRemainTime = 0;
        public Int32 m_curFreeGoldDrawCardRemaindCount = 0;
    }

};