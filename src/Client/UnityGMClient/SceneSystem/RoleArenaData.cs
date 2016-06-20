using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CRoleArenaData
    {
        /// <summary>
        /// 下次奖励发送时间
        /// </summary>
        public Int32 m_nextSendArenaPrizeTime = 0;
        /// <summary>
        /// 此次入场券售价
        /// </summary>
        public UInt32 m_ticketPrice = 0;
        /// <summary>
        /// 挑战时间间隔
        /// </summary>
        public Int32 m_chanllengeInterval = 0;
        /// <summary>
        /// 玩家竞技场排名
        /// </summary>
        public UInt32 m_rank = 0;
        /// <summary>
        /// 玩家剩余门票数
        /// </summary>
        public UInt32 m_arenaTicketCount = 0;
        /// <summary>
        /// 当日已购买门票次数
        /// </summary>
        public UInt32 m_dailyTicketPurchasedCount = 0;
        /// <summary>
        /// 剩余的购买次数 
        /// </summary>
        public UInt32 m_remaindPurchaseTicketCount = 0;
        /// <summary>
        /// 消除竞技场挑战CD时间钻石消耗
        /// </summary>
        public UInt32 m_eraseChallengeColdDownDiamondCost = 0;

        /// <summary>
        /// 竞技场战斗记录
        /// </summary>
        public List<CArenaChallengeRecord> m_listChallengeRecords = new List<CArenaChallengeRecord>();
        /// <summary>
        /// 被挑战者信息
        /// </summary>
        public List<CArenaChallengeeData> m_listChallengees = new List<CArenaChallengeeData>();

        public void SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_nextSendArenaPrizeTime = msgStream.ReadInt();
            m_ticketPrice = msgStream.ReadUInt();
            m_rank = msgStream.ReadUInt();
            m_arenaTicketCount = msgStream.ReadUInt();
            m_dailyTicketPurchasedCount = msgStream.ReadUInt();
            m_remaindPurchaseTicketCount = msgStream.ReadUInt();
            m_chanllengeInterval = msgStream.ReadInt();
            m_eraseChallengeColdDownDiamondCost = msgStream.ReadUInt();

            UInt16 recordsCount = msgStream.ReadUShort();
            for (Int32 i = 0; i < recordsCount; ++i )
            {
                CArenaChallengeRecord record = new CArenaChallengeRecord();
                record.SerializeFrom(msgStream);
                m_listChallengeRecords.Add(record);
            }

            UInt16 challengeesCount = msgStream.ReadUShort();
            for (Int32 i = 0; i < challengeesCount; ++i )
            {
                CArenaChallengeeData challengee = new CArenaChallengeeData();
                challengee.SerializeFrom(msgStream);
                m_listChallengees.Add(challengee);
            }
        }



    }

};