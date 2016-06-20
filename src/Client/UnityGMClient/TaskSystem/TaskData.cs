using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CTaskNPC
    {
        public UInt32 m_ID;
        public UInt32 m_slotID;
        public bool m_isSpawned;

        public void serializeFrom(UnityUtility.CStream stream)
        {
            m_ID = stream.ReadUInt();
            m_slotID = stream.ReadUInt();
            m_isSpawned = stream.ReadByte() != (byte)0;
        }

    }

    public class CRoleDailyTaskData
    {
        public UInt32 m_TPID = 0;
        public string m_taskName;
        public EDailyTaskType m_taskType;
        public UInt32 m_para1 = 0;
        public UInt32 m_para2 = 0;
        public UInt16 m_targetCount;
    	public UInt32 m_minRequiredRoleLevel = 0;
    	public UInt32 m_maxRequiredRoleLevel = 0;
    	string m_icon;
    	string m_taskDescription;
        public UInt16 m_jumpID = 0;
        public List<CPrizeItem> m_listPrizeItems = new List<CPrizeItem>();
        public UInt16 m_count = 0;
	    public ETaskState m_state = 0;

        public void serializeFrom(UnityUtility.CStream stream)
        {
            m_TPID = stream.ReadUInt();
            m_taskName = stream.ReadString();
            m_taskType = (EDailyTaskType)stream.ReadByte();
            m_para1 = stream.ReadUInt();
            m_para2 = stream.ReadUInt();
            m_targetCount = stream.ReadUShort();
            m_minRequiredRoleLevel = stream.ReadUInt();
            m_maxRequiredRoleLevel = stream.ReadUInt();
            m_icon = stream.ReadString();
            m_taskDescription = stream.ReadString();
            m_jumpID = stream.ReadUShort();
            UInt16 count = stream.ReadUShort();
            for (UInt16 i = 0; i < count; ++i )
            {
                CPrizeItem prizeItem = new CPrizeItem();
                prizeItem.SerializeFrom(stream);
                m_listPrizeItems.Add(prizeItem);
            }
            m_count = stream.ReadUShort();
            m_state = (ETaskState)stream.ReadByte();
        }
    }

    public class CRoleMainTaskData
    {
    	public UInt32 m_taskTPID;
    	public string m_taskName;
    	public EMainTaskType m_taskType;
    	public string m_taskDescription;
    	public UInt32 m_startNPC;
    	public UInt32 m_endNPC;
    	public UInt32 m_levelLimit;
    	public CTaskNPC m_NPC = new CTaskNPC();
    	public UInt32 m_stageID;
    	public UInt32 m_monsterID;
    	public UInt32 m_dropItemTPID;
    	public UInt32 m_needCount;
    	public string m_dialogStart;
        public string m_dialogAfterAccept;
        public string m_dialogEnd;
        public string m_dialogNPC;
        public string m_dialogBeforeFight;
        public string m_dialogAfterBoss;
        public string m_dialogAfterWin;
        public List<CPrizeItem> m_listPrizeItems = new List<CPrizeItem>();
        public UInt32 m_curCount;
        public ETaskState m_state;

        public void serializeFrom(UnityUtility.CStream stream)
        {
            m_taskTPID = stream.ReadUInt();
            m_taskName = stream.ReadString();
            m_taskType = (EMainTaskType)stream.ReadByte();
            m_taskDescription = stream.ReadString();

            m_startNPC = stream.ReadUInt();
            m_endNPC = stream.ReadUInt();
            m_levelLimit = stream.ReadUInt();
            m_NPC.serializeFrom(stream);
            m_stageID = stream.ReadUInt();
            m_monsterID = stream.ReadUInt();
            m_dropItemTPID = stream.ReadUInt();
            m_needCount = stream.ReadUInt();

            m_dialogStart = stream.ReadString();
            m_dialogAfterAccept = stream.ReadString();
            m_dialogEnd = stream.ReadString();
            m_dialogNPC = stream.ReadString();
            m_dialogBeforeFight = stream.ReadString();
            m_dialogAfterBoss = stream.ReadString();
            m_dialogAfterWin = stream.ReadString();

            UInt16 count = stream.ReadUShort();
            for (UInt16 i = 0; i < count; ++i)
            {
                CPrizeItem prizeItem = new CPrizeItem();
                prizeItem.SerializeFrom(stream);
                m_listPrizeItems.Add(prizeItem);
            }
            m_curCount = stream.ReadUInt();
            m_state = (ETaskState)stream.ReadByte();
        }
    }

    public class CRolePetTask
    {
    	public UInt32 m_id;
    	public string m_name;
    	public string m_desc;
    	public UInt32 m_petID;
    	public UInt32 m_weight;
    	public UInt32 m_minRoleLevel;
    	public UInt32 m_maxRoleLevel;
    	public EPetTaskType m_type;
    	public UInt32 m_param1;
    	public UInt32 m_param2;
    	public UInt32 m_param3;
    	public UInt32 m_petFriendlyValue;
        public List<CPrizeItem> m_listPrizeItems = new List<CPrizeItem>();
        public UInt32 m_taskIndex;
        public UInt16 m_curCount;
        public ETaskState m_state;
        public EPetTaskColor m_color;

        public void serializeFrom(UnityUtility.CStream stream)
        {
            m_id = stream.ReadUInt();
            m_name = stream.ReadString();
            m_desc = stream.ReadString();
            m_petID = stream.ReadUInt();
            m_weight = stream.ReadUInt();
            m_minRoleLevel = stream.ReadUInt();
            m_maxRoleLevel = stream.ReadUInt();
            m_type = (EPetTaskType)stream.ReadByte();
            m_param1 = stream.ReadUInt();
            m_param2 = stream.ReadUInt();
            m_param3 = stream.ReadUInt();
            m_petFriendlyValue = stream.ReadUInt();
            UInt16 count = stream.ReadUShort();
            for (UInt16 i = 0; i < count; ++i)
            {
                CPrizeItem prizeItem = new CPrizeItem();
                prizeItem.SerializeFrom(stream);
                m_listPrizeItems.Add(prizeItem);
            }
            m_taskIndex = stream.ReadUInt();
            m_curCount = stream.ReadUShort();
            m_state = (ETaskState)stream.ReadByte();
            m_color = (EPetTaskColor)stream.ReadByte();
        }
    }

    public class CPetTaskInfo
    {
        public List<CRolePetTask> m_rolePetTaskList = new List<CRolePetTask>();
        public UInt32 m_dailyRefreshCount;
        public UInt32 m_nextRefreshDiamondCost;
        public UInt32 m_taskCompletedCount;
        public UInt32 m_totalCount;

        public void serializeFrom(UnityUtility.CStream stream)
        {
            UInt16 count = stream.ReadUShort();
            for (UInt16 i = 0; i < count; ++i)
            {
                CRolePetTask petTask = new CRolePetTask();
                petTask.serializeFrom(stream);
                m_rolePetTaskList.Add(petTask);
            }
            m_dailyRefreshCount = stream.ReadUInt();
            m_nextRefreshDiamondCost = stream.ReadUInt();
            m_taskCompletedCount = stream.ReadUInt();
            m_totalCount = stream.ReadUInt();
        }
    }

    public class CRefreshPetTaskInfo
    {
        public List<CRolePetTask> m_rolePetTaskList = new List<CRolePetTask>();
        public UInt32 m_dailyRefreshCount;
        public UInt32 m_nextRefreshDiamondCost;

        public void serializeFrom(UnityUtility.CStream stream)
        {
            UInt16 count = stream.ReadUShort();
            for (UInt16 i = 0; i < count; ++i)
            {
                CRolePetTask petTask = new CRolePetTask();
                petTask.serializeFrom(stream);
                m_rolePetTaskList.Add(petTask);
            }
            m_dailyRefreshCount = stream.ReadUInt();
            m_nextRefreshDiamondCost = stream.ReadUInt();
        }
    }

}