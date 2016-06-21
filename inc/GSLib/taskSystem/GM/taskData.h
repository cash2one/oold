#ifndef	__GSLIB_TASKSYSTEM_GM_TASKDATA_H__
#define __GSLIB_TASKSYSTEM_GM_TASKDATA_H__

#include <vector>
#include <BSLib/utility/baseDef.h>
#include <GSLib/taskSystem/GM/taskSystemDefine.h>
#include <GSLib/itemSystem/GM/itemAttributeGM.h>
#include <BSLib/utility/stream.h>
#include <GSLib/sceneSystem/GM/sceneSystemData.h>

namespace GSLib
{

namespace TaskSystem
{

namespace GM
{

/////////////////////////////////////////////////////////////////////////////////////
class CTaskNPC
{
public:
	CTaskNPC();
	~CTaskNPC();
public:
	void serializeTo(BSLib::Utility::CStream & stream) const;
public:
	BSLib::uint32 m_ID;	
	BSLib::uint32 m_slotID;
	bool m_isSpawned;
};

/////////////////////////////////////////////////////////////////////////////////////
class CMainTaskAttr
{
public:
	CMainTaskAttr();
	~CMainTaskAttr();
public:
	void serializeTo(BSLib::Utility::CStream & stream) const;
	BSLib::uint32 getNeedCount() const;
	const SceneSystem::GM::CStagePrizeAttr &getStagePrizeAttr() const;
	BSLib::uint32 getLevelLimit() const;
	BSLib::uint32 getDropItemTPID() const;
	BSLib::uint32 getStageTPID() const;
public:
	BSLib::uint32 m_taskTPID;
	std::string m_taskName;
	EMainTaskType m_taskType;
	std::string m_taskDescription;
	BSLib::uint32 m_startNPC;
	BSLib::uint32 m_endNPC;
	BSLib::uint32 m_levelLimit;
	CTaskNPC m_NPC;
	BSLib::uint32 m_stageID;
	BSLib::uint32 m_monsterID;
	SceneSystem::GM::CStagePrizeAttr m_taskStageDropItem;
	BSLib::uint32 m_dropItemTPID;
	BSLib::uint32 m_needCount;
	std::vector<ItemSystem::GM::CPrizeItem> m_vecPrizeItem;
	std::string m_dialogStart;
	std::string m_dialogAfterAccept;
	std::string m_dialogEnd;
	std::string m_dialogNPC;
	std::string m_dialogBeforeFight;
	std::string m_dialogAfterBoss;
	std::string m_dialogAfterWin;
};

/////////////////////////////////////////////////////////////////////////////////////
class CDailyTaskAttr
{
public:
	CDailyTaskAttr();
	~CDailyTaskAttr();
public:
	void serializeTo(BSLib::Utility::CStream& stream) const;
public:
	BSLib::uint32 m_taskTPID;
	std::string m_taskName;
	EDailyTaskType m_taskType;
	BSLib::uint32 m_para1;
	BSLib::uint32 m_para2;
	BSLib::uint16 m_targetCount;
	BSLib::uint32 m_minRequiredRoleLevel;
	BSLib::uint32 m_maxRequiredRoleLevel;
	std::string m_icon;
	std::string m_taskDescription;
	BSLib::uint16 m_jumpID;
	std::vector<GSLib::ItemSystem::GM::CPrizeItem> m_vecItems;
};

/////////////////////////////////////////////////////////////////////////////////////
class CRoleDailyTaskData
{
public:
	CRoleDailyTaskData();
	CRoleDailyTaskData(const CDailyTaskAttr & taskAttr);
	~CRoleDailyTaskData();
public:
	bool isValid() const;
	EDailyTaskType getType() const;
	ETaskState getState() const;
	bool hasCompleted() const;
	void update();
public:
	BSLib::uint32 m_taskTPID;
	EPetTaskColor m_color;
	BSLib::uint64 m_taskAcceptTime;
	BSLib::uint16 m_count;
	ETaskState m_state;
	const CDailyTaskAttr *m_taskAttr;
};

/////////////////////////////////////////////////////////////////////////////////////
class CRoleMainTaskData
{
public:
	CRoleMainTaskData();
	~CRoleMainTaskData();
public:
	bool isValid() const;
	BSLib::uint32 getTPID() const;
	ETaskState getState() const;
	EMainTaskType getType() const;
	bool updateStage(BSLib::uint32 a_taskTPID ,BSLib::uint32 a_curCount);
	const CMainTaskAttr *getAttr() const;
public:
	BSLib::uint32 m_curTaskTPID;
	BSLib::uint64 m_acceptTime;
	BSLib::uint32 m_curCount;
	ETaskState m_state;
	const CMainTaskAttr *m_taskAttr;
};

/////////////////////////////////////////////////////////////////////////////////////
class CRoleDailyTaskDataSend
{
public:
	CRoleDailyTaskDataSend();
	~CRoleDailyTaskDataSend();
public:
	void serializeTo(BSLib::Utility::CStream& stream) const;
public:
	CDailyTaskAttr m_taskAttr;
	BSLib::uint16 m_count;
	ETaskState m_state;
};

/////////////////////////////////////////////////////////////////////////////////////
class CRoleMainTaskDataSend
{
public:
	CRoleMainTaskDataSend();
	~CRoleMainTaskDataSend();
public:
	void serializeTo(BSLib::Utility::CStream& stream) const;
public:
	CMainTaskAttr m_taskAttr;
	BSLib::uint32 m_curCount;
	ETaskState m_state;
};

class CPetTaskAttr
{
public:
	CPetTaskAttr();
	~CPetTaskAttr();
public:
	BSLib::uint32 getDropItemTPID() const;
public:
	BSLib::uint32 m_taskTPID;
	std::string m_name;
	std::string m_desc;
	BSLib::uint32 m_petID;
	BSLib::uint32 m_weight;
	BSLib::uint32 m_minRoleLevel;
	BSLib::uint32 m_maxRoleLevel;
	EPetTaskType m_type;
	BSLib::uint32 m_param1;
	BSLib::uint32 m_param2;
	BSLib::uint32 m_param3;
	BSLib::uint32 m_param4;
	BSLib::uint32 m_petFriendlyValue;
	std::vector<ItemSystem::GM::CPrizeItem> m_prizeItemList;
public:
	void serializeTo(BSLib::Utility::CStream& stream, EPetTaskColor a_color) const;
	void getTaskRequiredDropItem(SceneSystem::GM::CDropItem &a_dropItem) const;
};

class CRoleTaskSystemData
{
public:
	CRoleTaskSystemData();
	~CRoleTaskSystemData();
public:
	BSLib::uint32 m_taskCompletedCount;
	BSLib::uint32 m_dailyRefreshNewTaskCount;
	BSLib::int32 m_lastUpdateTime;
	BSLib::uint32 m_curPetTaskIndex;
};

/////////////////////////////////////////////////////////////////////////////////////
class CPetTaskColorPrize
{
public:
	CPetTaskColorPrize();
	~CPetTaskColorPrize();
public:
	BSLib::uint32 m_freindlyValue;
	std::vector<ItemSystem::GM::CPrizeItem> m_prizeItemList;
};

/////////////////////////////////////////////////////////////////////////////////////
class CRolePetTaskData
{
public:
	CRolePetTaskData();
	~CRolePetTaskData();
public:
	bool isValid() const;
	BSLib::uint32 getTPID() const;
	EPetTaskType getType() const;
	ETaskState getState() const;
	bool hasCompleted() const;
	BSLib::uint32 getDropItemTPID() const;
	void serializeTo(BSLib::Utility::CStream& stream) const;
	void getPrize(CPetTaskColorPrize & a_petTaskPrize) const;
public:
	BSLib::uint32 m_taskIndex;
	EPetTaskColor m_color;
	BSLib::uint64 m_taskAcceptTime;
	BSLib::uint16 m_curCount;
	ETaskState m_state;
	const CPetTaskAttr *m_taskAttr;
};

/////////////////////////////////////////////////////////////////////////////////////
class CPetTaskInfo
{
public:
	CPetTaskInfo();
	~CPetTaskInfo();
public:
	std::vector<CRolePetTaskData> m_petTaskList;
	BSLib::uint32 m_dailyRefreshCount;
	BSLib::uint32 m_nextRefreshDiamondCost;
	BSLib::uint32 m_taskCompletedCount;
	BSLib::uint32 m_totalCount;
public:
	void serializeTo(BSLib::Utility::CStream& stream) const;
};

/////////////////////////////////////////////////////////////////////////////////////
class CRefreshPetTaskInfo
{
public:
	CRefreshPetTaskInfo();
	~CRefreshPetTaskInfo();
	void serializeTo(BSLib::Utility::CStream& stream) const;
public:
	std::vector<CRolePetTaskData> m_rolePetTaskList;
	BSLib::uint32 m_dailyRefreshCount;
	BSLib::uint32 m_nextRefreshDiamondCost;

};

/////////////////////////////////////////////////////////////////////////////////////
class CPetTaskColorAttr
{
public:
	CPetTaskColorAttr(EPetTaskColor color = EPET_TASK_COLOR_NONE, BSLib::uint32 para1 = 0, BSLib::uint32 para2 = 0, BSLib::uint32 weight = 0);
	~CPetTaskColorAttr();
public:
	EPetTaskColor m_color;		//着色
	BSLib::uint32 m_para1;		//收率倍率
	BSLib::uint32 m_para2;		//数量的倍率
	BSLib::uint32 m_weight;		//出现的权重
};




}//GM

}//TaskSystem

}//GSLib

#endif//__GSLIB_TASKSYSTEM_GM_TASKDATAMGR_H__

