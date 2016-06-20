using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CStageData
    {
        public UInt16 m_stageIndex = 0;
        public byte m_star = 0;
        public UInt16 m_dailyEnteredTimes = 0;
        public UInt32 m_dailyRestoreCount = 0;
        public UInt32 m_nextRestoreTicketRequireDiamond = 0;

        public void SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_stageIndex = msgStream.ReadUShort();
            m_star = msgStream.ReadByte();
            m_dailyEnteredTimes = msgStream.ReadUShort();
            m_dailyRestoreCount = msgStream.ReadUInt();
            m_nextRestoreTicketRequireDiamond = msgStream.ReadUInt();
        }
     }
    ////////////////////////////////////////////////////////////////////////////
    public class CStagePrize
    {
        public UInt64 m_exp = 0;
        public UInt64 m_gold = 0;
        public List<CPrizeItem> m_listPrizeItem = new List<CPrizeItem>();
        public List<CPrizeItem> m_elitePrizeItems = new List<CPrizeItem>();

        public void SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_exp = msgStream.ReadULong();
            m_gold = msgStream.ReadULong();
            UInt16 count = msgStream.ReadUShort();
            for (UInt16 i = 0; i < count; ++i)
            {
                CPrizeItem item = new CPrizeItem();
                item.SerializeFrom(msgStream);
                m_listPrizeItem.Add(item);
            }
            count = msgStream.ReadUShort();
            for (UInt16 i = 0; i < count; ++i)
            {
                CPrizeItem item = new CPrizeItem();
                item.SerializeFrom(msgStream);
                m_elitePrizeItems.Add(item);
            }
        }
     }
    ////////////////////////////////////////////////////////////////////////////
    public class CSceneRoleInfo
    {
        public SRoleKey m_roleKey;
        public UInt32 m_roleTPID = 0;
        public string m_roleName;
        public UInt32 m_level = 0;
        public UInt32 m_VIPLevel = 0;
        public UInt32 m_fashionTPID = 0;

        public void SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_roleKey.serializeFrom(msgStream);
            m_roleTPID = msgStream.ReadUInt();
            m_roleName = msgStream.ReadString();
            m_level = msgStream.ReadUInt();
            m_VIPLevel = msgStream.ReadUInt();
            m_fashionTPID = msgStream.ReadUInt();
        }
     }
    ////////////////////////////////////////////////////////////////////////////
    public class CMonster
    {
        public UInt32 m_index = 0;
        public EMonsterType m_type;
        public List<CPrizeItem> m_listDropItems = new List<CPrizeItem>();

        public void SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_index = msgStream.ReadUInt();
            UInt16 type = msgStream.ReadUShort();
            m_type = (EMonsterType)type;
            UInt16 count = msgStream.ReadUShort();
            for (UInt16 i = 0; i < count; ++i )
            {
                CPrizeItem item = new CPrizeItem();
                item.SerializeFrom(msgStream);
                m_listDropItems.Add(item);
            }
        }
    }


    public class CMonsterBatch
    {
        public Int32 m_index = 0;
        public List<CMonster> m_randomMonster = new List<CMonster>();
        public List<CMonster> m_certainlyMonster = new List<CMonster>();
        public CMonster m_boss;
        public void SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_index = msgStream.ReadInt();
            UInt16 count = msgStream.ReadUShort();
            for (UInt16 i = 0; i < count; ++i )
            {
                CMonster monster = new CMonster();
                monster.SerializeFrom(msgStream);
                if (monster.m_type == EMonsterType.RandomDropMonster) {
                    m_randomMonster.Add(monster);
                }
                else if (monster.m_type == EMonsterType.CertainlyDropMonster) {
                    m_certainlyMonster.Add(monster);
                } else if (monster.m_type == EMonsterType.Boss) {
                    m_boss = monster;
                }
            }
        }
    }

    public class CStageUnitMonster
    {
        public List<CMonsterBatch> m_monsterBatches = new List<CMonsterBatch>();
        public CMonster m_randomElite = null;

        public void SerializeFrom(UnityUtility.CStream msgStream)
        {
            UInt16 count = msgStream.ReadUShort();
            for (UInt16 i = 0; i < count; ++i)
            {
                CMonsterBatch monsterBatch = new CMonsterBatch();
                monsterBatch.SerializeFrom(msgStream);
                m_monsterBatches.Add(monsterBatch);
            }
            bool hasElite = msgStream.ReadBoolean();
            if (hasElite) {
                m_randomElite = new CMonster();
                m_randomElite.SerializeFrom(msgStream);
            }
        }
    }

    public class CStageMonster
    {
        public List<CStageUnitMonster> m_stageUnitMonster = new List<CStageUnitMonster>();

        public void serializeFrom(UnityUtility.CStream msgStream)
        {
            UInt16 count = msgStream.ReadUShort();
            for (UInt16 i = 0; i < count; ++i)
            {
                CStageUnitMonster monsterBatch = new CStageUnitMonster();
                monsterBatch.SerializeFrom(msgStream);
                m_stageUnitMonster.Add(monsterBatch);
            }
        }
    }

    public class CGreedLandInfo
    {
        public UInt32 m_ticketsCount;
        public UInt32 m_maxTicketCount;
        public UInt32 m_nextUpdateTimeRemaining;

        public void serializeFrom(UnityUtility.CStream msgStream)
        {
            m_ticketsCount = msgStream.ReadUInt();
            m_maxTicketCount = msgStream.ReadUInt();
            m_nextUpdateTimeRemaining = msgStream.ReadUInt();
        }
    }

    public class CChallengeInfo
    {
        public EChallengeType m_type = EChallengeType.ECHALLENGE_TYPE_RANKING_ROLE;
        public UInt64 m_param = 0;
        public bool m_useDiamond = false;

        public CChallengeInfo()
        {

        }

        public CChallengeInfo(EChallengeType type, UInt64 param, bool useDiamond)
        {
            m_type = type;
            m_param = param;
            m_useDiamond = useDiamond;
        }

        public void serializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write((byte)m_type);
            msgStream.Write(m_param);
            msgStream.Write(m_useDiamond);
        }
    }




}
