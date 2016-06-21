#include <GSLib/taskSystem/GM/taskDataMgr.h>
#include <BSLib/utility/dateTime.h>

namespace GSLib
{

namespace TaskSystem
{

namespace GM
{

//////////////////////////////////////////////////////////////////////////////////////////
CTaskNPC::CTaskNPC()
:m_ID(0)
,m_slotID(0)
,m_isSpawned(0)
{

}

CTaskNPC::~CTaskNPC()
{

}

void CTaskNPC::serializeTo(BSLib::Utility::CStream & stream) const
{
	stream << m_ID;
	stream << m_slotID;
	stream << (m_isSpawned ? (BSLib::int8)1 : (BSLib::int8)0);
}

//////////////////////////////////////////////////////////////////////////////////////////
CMainTaskAttr::CMainTaskAttr()
:m_taskTPID(0)
,m_taskName("")
,m_taskType(EMAIN_TASK_TYPE_NONE)
,m_taskDescription("")
,m_startNPC(0)
,m_endNPC(0)
,m_levelLimit(0)
,m_stageID(0)
,m_monsterID(0)
,m_dropItemTPID(0)
,m_needCount(0)
,m_dialogStart("")
,m_dialogAfterAccept("")
,m_dialogEnd("")
,m_dialogNPC("")
,m_dialogBeforeFight("")
,m_dialogAfterBoss("")
,m_dialogAfterWin("")
{

}

CMainTaskAttr::~CMainTaskAttr()
{

}

void CMainTaskAttr::serializeTo(BSLib::Utility::CStream & stream) const
{
	stream <<  m_taskTPID; 
	stream <<  m_taskName; 
	stream <<  (BSLib::int8)m_taskType; 
	stream << m_taskDescription;
	stream << m_startNPC;
	stream << m_endNPC;
	stream << m_levelLimit;
	m_NPC.serializeTo(stream);
	stream << m_stageID;
	stream << m_monsterID;
	stream << m_dropItemTPID;
	stream << m_needCount;
	stream << m_dialogStart;
	stream << m_dialogAfterAccept;
	stream << m_dialogEnd;
	stream << m_dialogNPC;
	stream << m_dialogBeforeFight;
	stream << m_dialogAfterBoss;
	stream << m_dialogAfterWin;

	stream << (BSLib::uint16)m_vecPrizeItem.size();
	for (std::vector<GSLib::ItemSystem::GM::CPrizeItem>::const_iterator itr = m_vecPrizeItem.begin(); itr != m_vecPrizeItem.end(); ++itr) {
		const GSLib::ItemSystem::GM::CPrizeItem &item = *itr;
		item.serializeTo(stream);
	}
}

BSLib::uint32 CMainTaskAttr::getNeedCount() const
{
	return m_needCount;
}

const SceneSystem::GM::CStagePrizeAttr & CMainTaskAttr::getStagePrizeAttr() const
{
	return m_taskStageDropItem;
}

BSLib::uint32 CMainTaskAttr::getLevelLimit() const
{
	return m_levelLimit;
}

BSLib::uint32 CMainTaskAttr::getDropItemTPID() const
{
	return m_dropItemTPID;
}

BSLib::uint32 CMainTaskAttr::getStageTPID() const
{
	return m_stageID;
}

//////////////////////////////////////////////////////////////////////////////////////////
CDailyTaskAttr::CDailyTaskAttr()
:m_taskTPID(0)
,m_taskName("")
,m_taskType(EDAILY_TASK_TYPE_NONE)
,m_para1(0)
,m_para2(0)
,m_targetCount(0)
,m_minRequiredRoleLevel(0)
,m_maxRequiredRoleLevel(0)
,m_icon("")
,m_taskDescription("")
,m_jumpID(0)
{

}

CDailyTaskAttr::~CDailyTaskAttr()
{

}

void CDailyTaskAttr::serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_taskTPID;
	stream << m_taskName;
	stream << (BSLib::int8)m_taskType;
	stream << m_para1;
	stream << m_para2;
	stream << m_targetCount;
	stream << m_minRequiredRoleLevel;
	stream << m_maxRequiredRoleLevel;
	stream << m_icon;
	stream << m_taskDescription;
	stream << m_jumpID;

	stream << (BSLib::uint16)m_vecItems.size();
	for (std::vector<GSLib::ItemSystem::GM::CPrizeItem>::const_iterator itr = m_vecItems.begin(); itr != m_vecItems.end(); ++itr) {
		const GSLib::ItemSystem::GM::CPrizeItem &item = *itr;
		item.serializeTo(stream);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
CRoleDailyTaskData::CRoleDailyTaskData()
:m_color(EPET_TASK_COLOR_NONE)
,m_taskTPID(0)
,m_taskAcceptTime(0)
,m_count(0)
,m_state(ETASKSTATE_NONE )
,m_taskAttr(NULL)
{

}

CRoleDailyTaskData::CRoleDailyTaskData(const CDailyTaskAttr & taskAttr)
{
	m_taskTPID = taskAttr.m_taskTPID;
	m_taskAcceptTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
	m_count = 0;
	m_state = ETASKSTATE_ACCEPT;
	m_taskAttr = &taskAttr;
}


CRoleDailyTaskData::~CRoleDailyTaskData()
{

}

bool CRoleDailyTaskData::isValid() const
{
	return m_taskAttr != NULL;
}

EDailyTaskType CRoleDailyTaskData::getType() const
{
	if (m_taskAttr != NULL) {
		return m_taskAttr->m_taskType;
	}

	return EDAILY_TASK_TYPE_NONE;
}

ETaskState CRoleDailyTaskData::getState() const
{
	return m_state;
}

bool CRoleDailyTaskData::hasCompleted() const
{
	return m_state > ETASKSTATE_ACCEPT;
}

void CRoleDailyTaskData::update()
{
	if (m_taskAttr != NULL) {
		if (m_count < m_taskAttr->m_targetCount) {
			++m_count;
			if (m_count >= m_taskAttr->m_targetCount) {
				m_state = ETASKSTATE_FINISH;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
CRoleMainTaskData::CRoleMainTaskData()
:m_curTaskTPID(0)
,m_acceptTime(0)
,m_curCount(0)
,m_state(ETASKSTATE_NONE )
,m_taskAttr(NULL)
{

}

CRoleMainTaskData::~CRoleMainTaskData()
{

}

bool CRoleMainTaskData::isValid() const
{
	return m_taskAttr != NULL;
}

ETaskState CRoleMainTaskData::getState() const
{
	return m_state;
}

EMainTaskType CRoleMainTaskData::getType() const
{
	if (m_taskAttr != NULL) {
		return m_taskAttr->m_taskType;
	}

	return EMAIN_TASK_TYPE_NONE;
}

bool CRoleMainTaskData::updateStage(BSLib::uint32 a_taskTPID ,BSLib::uint32 a_curCount)
{
	if (a_taskTPID == m_curTaskTPID) {
		if (isValid()) {
			if (a_curCount > m_curCount) {
				m_curCount = a_curCount > m_taskAttr->getNeedCount() ? m_taskAttr->getNeedCount() : m_taskAttr->getNeedCount();
				if (m_curCount >= m_taskAttr->getNeedCount()) {
					m_state = ETASKSTATE_FINISH;
				}
				return true;
			}
		}
	}
	return false;
}

const CMainTaskAttr * CRoleMainTaskData::getAttr() const
{
	return m_taskAttr;
}

BSLib::uint32 CRoleMainTaskData::getTPID() const
{
	return m_curTaskTPID;
}

////////////////////////////////////////////////////////////////////////////////////////
CRoleDailyTaskDataSend::CRoleDailyTaskDataSend()
:m_count(0)
,m_state(ETASKSTATE_NONE)
{

}

CRoleDailyTaskDataSend::~CRoleDailyTaskDataSend()
{

}

void CRoleDailyTaskDataSend::serializeTo(BSLib::Utility::CStream& stream) const
{
	m_taskAttr.serializeTo(stream);
	stream << m_count;
	stream << (BSLib::int8)m_state;
}

////////////////////////////////////////////////////////////////////////////////////////
CRoleMainTaskDataSend::CRoleMainTaskDataSend()
:m_curCount(0)
,m_state(ETASKSTATE_NONE)
{

}

CRoleMainTaskDataSend::~CRoleMainTaskDataSend()
{

}

void CRoleMainTaskDataSend::serializeTo(BSLib::Utility::CStream& stream) const
{
	m_taskAttr.serializeTo(stream);
	stream << m_curCount;
	stream << (BSLib::int8)m_state;
}



CPetTaskAttr::CPetTaskAttr()
:m_taskTPID(0)
,m_name("")
,m_desc("")
,m_petID(0)
,m_weight(0)
,m_minRoleLevel(0)
,m_maxRoleLevel(0)
,m_type(EPET_TASK_TYPE_NONE)
,m_param1(0)
,m_param2(0)
,m_param3(0)
,m_param4(0)
,m_petFriendlyValue(0)
{

}

CPetTaskAttr::~CPetTaskAttr()
{

}

void CPetTaskAttr::serializeTo(BSLib::Utility::CStream& stream,  EPetTaskColor a_color) const
{
	stream << m_taskTPID;	
	stream << m_name;
	stream << m_desc;
	stream << m_petID;
	BSLib::uint32 weight = 0;
	stream << weight;
	stream << m_minRoleLevel;
	stream << m_maxRoleLevel;
	stream << (BSLib::uint8)m_type;
	stream << m_param1;
	stream << m_param2;
	const CPetTaskColorAttr *petColorAttr = CTaskDataMgr::singleton().getPetTaskColorAttr(a_color);
	if (petColorAttr != NULL) {
		stream << m_param3 * petColorAttr->m_para2 / 100;
		stream << m_petFriendlyValue * petColorAttr->m_para1 / 100;
		stream << (BSLib::uint16)m_prizeItemList.size();
		for (std::vector<ItemSystem::GM::CPrizeItem>::const_iterator itr = m_prizeItemList.begin(); itr != m_prizeItemList.end(); ++itr) {
			ItemSystem::GM::CPrizeItem item = *itr;
			item.m_itemCount = item.m_itemCount * petColorAttr->m_para1 / 100;
			if (item.m_itemCount <= 0) {
				item.m_itemCount = 1;
			}
			item.serializeTo(stream);
		}
	}
}

BSLib::uint32 CPetTaskAttr::getDropItemTPID() const
{
	if (m_type ==EPET_TASK_TYPE_MONSTER_DROP || m_type == EPET_TASK_TYPE_BOSS_DROP) {
		return m_param2;
	}
	return 0;
}

void CPetTaskAttr::getTaskRequiredDropItem(SceneSystem::GM::CDropItem &a_dropItem) const
{
	if (m_type == EPET_TASK_TYPE_MONSTER_DROP || m_type == EPET_TASK_TYPE_BOSS_DROP) {
		a_dropItem.m_itemTPID = m_param2;
		a_dropItem.m_itemCount = m_param3;
		a_dropItem.m_weight = m_param4;
		a_dropItem.m_totalWeight = 10000;
	}
}

////////////////////////////////////////////////////////////////////////////////////////
CRoleTaskSystemData::CRoleTaskSystemData()
:m_taskCompletedCount(0)
,m_dailyRefreshNewTaskCount(0)
,m_lastUpdateTime(0)
,m_curPetTaskIndex(0)
{

}

CRoleTaskSystemData::~CRoleTaskSystemData()
{

}

//////////////////////////////////////////////////////////////////////////////////////////
CRolePetTaskData::CRolePetTaskData()
:m_taskIndex(0)
,m_color(EPET_TASK_COLOR_NONE)
,m_taskAcceptTime(0)
,m_curCount(0)
,m_state(ETASKSTATE_NONE )
,m_taskAttr(NULL)
{

}

CRolePetTaskData::~CRolePetTaskData()
{

}

bool CRolePetTaskData::isValid() const
{
	return m_taskAttr != NULL;
}

BSLib::uint32 CRolePetTaskData::getTPID() const
{
	if (m_taskAttr != NULL) {
		return m_taskAttr->m_taskTPID;
	}
	return 0;
}

EPetTaskType CRolePetTaskData::getType() const
{
	if (m_taskAttr != NULL) {
		return m_taskAttr->m_type;
	}

	return EPET_TASK_TYPE_NONE;
}

ETaskState CRolePetTaskData::getState() const
{
	return m_state;
}

bool CRolePetTaskData::hasCompleted() const
{
	return m_state > ETASKSTATE_ACCEPT;
}

BSLib::uint32 CRolePetTaskData::getDropItemTPID() const
{
	if (m_taskAttr != NULL) {
		if (m_taskAttr->m_type ==EPET_TASK_TYPE_MONSTER_DROP || m_taskAttr->m_type == EPET_TASK_TYPE_BOSS_DROP) {
			return m_taskAttr->m_param2;
		}
	}
	
	return 0;
}

void CRolePetTaskData::serializeTo(BSLib::Utility::CStream& stream) const
{
	if (m_taskAttr != NULL) {
		m_taskAttr->serializeTo(stream, m_color);
		stream << m_taskIndex;
		stream << m_curCount;
		stream << (BSLib::uint8)m_state;
		stream << (BSLib::uint8)m_color;
	}
}

void CRolePetTaskData::getPrize(CPetTaskColorPrize & a_petTaskPrize) const
{
	if (m_taskAttr == NULL) {
		return;
	}
	const CPetTaskColorAttr *petColorAttr = CTaskDataMgr::singleton().getPetTaskColorAttr(m_color);
	if (petColorAttr != NULL) {
		a_petTaskPrize.m_freindlyValue = m_taskAttr->m_petFriendlyValue * petColorAttr->m_para1 / 100;
		a_petTaskPrize.m_prizeItemList = m_taskAttr->m_prizeItemList;
		for (std::vector<ItemSystem::GM::CPrizeItem>::iterator itr = a_petTaskPrize.m_prizeItemList.begin(); itr != a_petTaskPrize.m_prizeItemList.end(); ++itr) {
			ItemSystem::GM::CPrizeItem &item = *itr;
			item.m_itemCount = item.m_itemCount * petColorAttr->m_para1 / 100;
			if (item.m_itemCount <= 0) {
				item.m_itemCount = 1;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
CPetTaskInfo::CPetTaskInfo()
:m_dailyRefreshCount(0)
,m_nextRefreshDiamondCost(0)
,m_taskCompletedCount(0)
{

}

CPetTaskInfo::~CPetTaskInfo()
{

}

void CPetTaskInfo::serializeTo(BSLib::Utility::CStream& stream) const
{
	BSLib::uint16 count = (BSLib::uint16)m_petTaskList.size();
	stream << count;
	for (BSLib::uint16 i = 0; i < count; ++i) {
		m_petTaskList[i].serializeTo(stream);
	}
	stream << m_dailyRefreshCount;
	stream << m_nextRefreshDiamondCost;
	stream << m_taskCompletedCount;
	stream << m_totalCount;
}

/////////////////////////////////////////////////////////////////////////////////////
CRefreshPetTaskInfo::CRefreshPetTaskInfo()
:m_dailyRefreshCount(0)
,m_nextRefreshDiamondCost(0)
{

}

CRefreshPetTaskInfo::~CRefreshPetTaskInfo()
{

}

void CRefreshPetTaskInfo::serializeTo(BSLib::Utility::CStream& stream) const
{
	BSLib::uint16 count = (BSLib::uint16)m_rolePetTaskList.size();
	stream << count;
	for (BSLib::uint16 i = 0; i < count; ++i) {
		m_rolePetTaskList[i].serializeTo(stream);
	}
	stream << m_dailyRefreshCount;
	stream << m_nextRefreshDiamondCost;
}

/////////////////////////////////////////////////////////////////////////////////////
CPetTaskColorAttr::CPetTaskColorAttr(EPetTaskColor color, BSLib::uint32 para1, BSLib::uint32 para2, BSLib::uint32 weight)
:m_color(color)
,m_para1(para1)
,m_para2(para2)
,m_weight(weight)
{

}

CPetTaskColorAttr::~CPetTaskColorAttr()
{

}

/////////////////////////////////////////////////////////////////////////////////////
CPetTaskColorPrize::CPetTaskColorPrize()
:m_freindlyValue(0)
{

}

CPetTaskColorPrize::~CPetTaskColorPrize()
{

}





}//GM

}//TaskSystem

}//GSLib
