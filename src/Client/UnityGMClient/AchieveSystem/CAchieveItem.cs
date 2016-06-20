using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
// 1=等级成就
// 2=战斗力成就
// 3=击杀BOSS成就
// 4=通关副本成就
// 5=PVP成就
// 6=骰子成就
// 7=连续闯关成就
// 8=装备成就
// 9=宝石成就
// 10=技能成就
// 11=僚机成就
// 12=充值消费成就

    public enum EAchieveType
    {
        ACHIEVE_INVALID = 0,
        ACHIEVE_LEVEL = 1,		    //等级成就
        ACHIEVE_COMBAT = 2,         //战斗力成就
        ACHIEVE_KILL_BOSS = 3,		//击杀BOSS成就	
        ACHIEVE_PASS_INSTANCE = 4,  //通关副本成就	
        ACHIEVE_PVP = 5,			//PVP成就	
        ACHIEVE_DICE = 6,			//骰子成就
        ACHIEVE_PASS_STAGE = 7,	//连续闯关成就
        ACHIEVE_EQUIP = 8,	        //装备成就
        ACHIEVE_GEM = 9,	        //宝石成就
        ACHIEVE_SKILL = 10,	        //技能成就
        ACHIEVE_PET = 11,	        //僚机成就
        ACHIEVE_CHARGE = 12,    	//充值消费成就
    }

    public enum EAchieveStatus
    {
        ACHIEVE_STATUS_DOING,     //进行中
        EACHIEVE_STATUS_FINISHED, //已完成
        ACHIEVE_STATUS_PRIZED,    //已领取奖励
    };


    public class CAchieveItem
    {
        private UInt32 m_achieveID = 0;
        private UInt32 m_achieveSubType;
        private UInt32 m_achieveProgress = 0;
        private EAchieveStatus m_achieveStatus = 0;

        public UInt32 AchieveID
        {
            set { m_achieveID = value; }
            get { return m_achieveID; }
        }

        public UInt32 AchieveProgress 
        {
            set { m_achieveProgress = value; }
            get { return m_achieveProgress; }
        }

        public EAchieveStatus AchieveStatus 
        {
            set { m_achieveStatus = value; }
            get { return m_achieveStatus; }
        }

        public UInt32 AchieveSubType
        {
            set { m_achieveSubType = value; }
            get { return m_achieveSubType; }
        }

        public bool SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_achieveID = msgStream.ReadUInt();
            m_achieveSubType = msgStream.ReadUInt();
            m_achieveProgress = msgStream.ReadUInt();
            m_achieveStatus = (EAchieveStatus)msgStream.ReadUInt();
            return true;
        }
    }
}
