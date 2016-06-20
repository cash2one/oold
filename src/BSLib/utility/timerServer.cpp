//////////////////////////////////////////////////////////////////////
//	created:	2013/01/13
//	filename:	src\BSLib\utility\timerServer.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/tracer.h>
#include <BSLib/utility/timerServer.h>

namespace BSLib
{

namespace Utility
{

#define BSLIB_UTILITY_TIMER_INTERVAL 15
#define BSLIB_UTILITY_TIEER_STAGE_MAX 256

//////////////////////////////////////////////////////////////////////////

struct STimerItem
{
	TimerHandle m_handle;
	bool m_isUser;
	BSLib::uint32 m_msInterval;
	BSLib::int32 m_counts;
	BSLib::uint64 m_para1;
	void* m_para2;
	CFunction<bool, BSLib::uint64, void*>* m_fun;
	CTimerServer::TimerNumber m_timerPoint;

	STimerItem()
	{
		m_handle = INVALID_TIMER;
		m_isUser = false;
		m_msInterval = 0;
		m_counts = -1;
		m_para1 = 0;
		m_para2 = NULL;
		m_fun = NULL;
		m_timerPoint.m_number = 0;
	}

	~STimerItem()
	{
		if (m_fun != NULL) {
			BSLIB_SAFE_DELETE(m_fun);
		}
	}
};

//////////////////////////////////////////////////////////////////////////

CTimerServer::CTimerServer()
: m_delayTimer(BSLIB_UTILITY_TIMER_INTERVAL, m_realTime)
, m_handles(0)
, m_lastTime(0)
, m_spareTimeInterval(0)
{
	m_stagesPoint.m_number = 0;
	for (int i=0; i<TIMER_NUMBER_BITS_MAX; ++i) {
		m_stages[i].resize(BSLIB_UTILITY_TIEER_STAGE_MAX, NULL);
	}
	m_lastTime = m_realTime.milliseconds();
}

CTimerServer::~CTimerServer()
{
	_clear();
}

TimerHandle CTimerServer::addTimer(CTimerServer::FTimerCallback a_fun, BSLib::uint64 a_para1, void* a_para2, BSLib::uint32 a_msInterval,  BSLib::uint32 a_msDelay,  BSLib::int32 a_counts)
{
	TimerHandle timerHandle = _allocateHandle();
	if (timerHandle == INVALID_TIMER) {
		return INVALID_TIMER;
	}
	STimerItem* timerItem = new STimerItem();
	if (timerItem == NULL) {
		return INVALID_TIMER;
	}
	
	timerItem->m_fun = new CFunction<bool, BSLib::uint64, void*>(a_fun);
	if (timerItem->m_fun == NULL) {
		BSLIB_SAFE_DELETE(timerItem);
		return INVALID_TIMER;
	}
	timerItem->m_handle = timerHandle;
	timerItem->m_para1 = a_para1;
	timerItem->m_para2 = a_para2;
	timerItem->m_msInterval = a_msInterval;
	timerItem->m_counts = a_counts;

// 	if (!_addTimer(timerItem, a_msDelay + a_msInterval)) {
// 		BSLIB_SAFE_DELETE(timerItem);
// 		return INVALID_TIMER;
// 	}

	if (!_addTimer(timerItem, a_msDelay)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "_addTimer Ê§°Ü");
		BSLIB_SAFE_DELETE(timerItem);
		return INVALID_TIMER;
	}

	timerItem->m_isUser = true;
	m_timers.setValue(timerHandle, timerItem);

	return timerHandle;
}

TimerHandle CTimerServer::addTimer(const CFunction<bool, BSLib::uint64, void*>& a_fun, BSLib::uint64 a_para1, void* a_para2, BSLib::uint32 a_msInterval,  BSLib::uint32 a_msDelay,  BSLib::int32 a_counts)
{
	TimerHandle timerHandle = _allocateHandle();
	if (timerHandle == INVALID_TIMER) {
		return INVALID_TIMER;
	}
	STimerItem* timerItem = new STimerItem();
	if (timerItem == NULL) {
		return INVALID_TIMER;
	}

	timerItem->m_fun = a_fun.clone();
	if (timerItem->m_fun == NULL) {
		BSLIB_SAFE_DELETE(timerItem);
		return INVALID_TIMER;
	}
	timerItem->m_handle = timerHandle;
	timerItem->m_para1 = a_para1;
	timerItem->m_para2 = a_para2;
	timerItem->m_msInterval = a_msInterval;
	timerItem->m_counts = a_counts;

// 	if (!_addTimer(timerItem, a_msDelay + a_msInterval)) {
// 		BSLIB_SAFE_DELETE(timerItem);
// 		return INVALID_TIMER;
// 	}

	if (!_addTimer(timerItem, a_msDelay)) {
		BSLIB_SAFE_DELETE(timerItem);
		return INVALID_TIMER;
	}

	timerItem->m_isUser = true;
	m_timers.setValue(timerHandle, timerItem);

	return timerHandle;
}

void CTimerServer::delTimer(TimerHandle a_timerHandle)
{
	if (a_timerHandle == INVALID_TIMER) {
		return ;
	}
	STimerItem* timerItem = NULL;
	m_timers.getValue(a_timerHandle, timerItem);
	if (timerItem == NULL) {
		return ;
	}
	timerItem->m_isUser = false;

	m_timers.remove(a_timerHandle);
}

bool CTimerServer::isValid(TimerHandle a_timerHandle)
{
	if (a_timerHandle == INVALID_TIMER) {
		return false;
	}
	return m_timers.find(a_timerHandle) != m_timers.end();
}

void CTimerServer::update()
{
	m_realTime.now();
	if (!m_delayTimer(m_realTime)) {
		return ;
	};
	update(m_realTime.milliseconds());
}

void CTimerServer::update(BSLib::int64 a_currentTime)
{
	BSLib::int64 currentTime = a_currentTime;
	int timeInterval = (int)(currentTime - m_lastTime + m_spareTimeInterval);
	int tick = timeInterval / BSLIB_UTILITY_TIMER_INTERVAL;
	if (tick <= 0) {
		return ;
	}
	m_lastTime = currentTime;
	m_spareTimeInterval = timeInterval % BSLIB_UTILITY_TIMER_INTERVAL;

	TimerNumber stagesPoint = m_stagesPoint;
	m_stagesPoint.m_number += tick;

	std::list<STimerItem*>::iterator it;
	std::list<STimerItem*> adjustTimerList;
	for (int i=0; i<tick; ++i) {
		std::list<STimerItem*>* itemList = m_stages[0][stagesPoint.m_bits[0]];
		if (itemList != NULL) {
			for (it = itemList->begin(); it != itemList->end(); ++it){
				STimerItem* item = *it;
				if (item == NULL) {
					continue;
				}
				if (!item->m_isUser) {
					BSLIB_SAFE_DELETE(item);
					continue;
				}
				CFunction<bool, BSLib::uint64, void*>* fun = item->m_fun;
				if (fun == NULL) {
					m_timers.remove(item->m_handle);
					BSLIB_SAFE_DELETE(item);
					continue;
				}
				if (!(*fun)(item->m_para1, item->m_para2)) {
					m_timers.remove(item->m_handle);
					BSLIB_SAFE_DELETE(item);
					continue;
				}
				if (item->m_counts > 0) {
					--(item->m_counts);
					if (item->m_counts == 0) {
						m_timers.remove(item->m_handle);
						BSLIB_SAFE_DELETE(item);
						continue;
					}
				}
				adjustTimerList.push_back(item);
			}
			itemList->clear();
		}

		++stagesPoint.m_number;

		if ((stagesPoint.m_number & 0X000000FF) == 0){
			if ((stagesPoint.m_number & 0X0000FFFF) == 0){
				if ((stagesPoint.m_number & 0X00FFFFFF) == 0){
					if (stagesPoint.m_number == 0) {
						//continue;
					}
					_adjustTimer3(stagesPoint.m_bits[3]);
					//continue;
				}
				_adjustTimer2(stagesPoint.m_bits[2]);
				//continue;
			} 
			_adjustTimer1(stagesPoint.m_bits[1]);
		}
	}

	for (it = adjustTimerList.begin(); it != adjustTimerList.end(); ++it){
		STimerItem* item = *it;
		if (!_addTimer(item, item->m_msInterval)) {
			BSLIB_SAFE_DELETE(item);
		}
	}
	adjustTimerList.clear();
}

TimerHandle CTimerServer::_allocateHandle()
{
	for (int i=0; i<BSLIB_INT32_MAX; ++i) {
		m_handles = (m_handles + 1) % BSLIB_INT32_MAX;
		if (m_timers.find(m_handles) == m_timers.end()) {
			return m_handles;
		}
	}
	return INVALID_TIMER;
}

bool CTimerServer::_addTimer(STimerItem* a_timerItem, BSLib::uint32 a_msDelay)
{
	BSLib::int64 point = a_msDelay / BSLIB_UTILITY_TIMER_INTERVAL;
	
	if (point <= BSLIB_UINT8_MAX) {
		a_timerItem->m_timerPoint.m_number = (BSLib::uint32)(m_stagesPoint.m_number + point);
		std::list<STimerItem*>* itemList = m_stages[0][a_timerItem->m_timerPoint.m_bits[0]];
		if (itemList == NULL) {
			itemList = new std::list<STimerItem*>();
			if (itemList == NULL) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "_addTimer[%lld][%lld] Ê§°Ü", point, a_msDelay);
				return false;
			}
			m_stages[0][a_timerItem->m_timerPoint.m_bits[0]] = itemList;
		}
		itemList->push_back(a_timerItem);
		return true;
	} 
	
	if (point <= BSLIB_UINT16_MAX) {
		a_timerItem->m_timerPoint.m_number = (BSLib::uint32)(m_stagesPoint.m_number + point);
		std::list<STimerItem*>* itemList = m_stages[1][a_timerItem->m_timerPoint.m_bits[1]];
		if (itemList == NULL) {
			itemList = new std::list<STimerItem*>();
			if (itemList == NULL) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "_addTimer[%lld][%lld] Ê§°Ü", point, a_msDelay);
				return false;
			}
			m_stages[1][a_timerItem->m_timerPoint.m_bits[1]] = itemList;
		}
		itemList->push_back(a_timerItem);
		return true;
	} 
	
	if (point <= 0X00FFFFFF){
		a_timerItem->m_timerPoint.m_number = (BSLib::uint32)(m_stagesPoint.m_number + point);
		std::list<STimerItem*>* itemList = m_stages[2][a_timerItem->m_timerPoint.m_bits[2]];
		if (itemList == NULL) {
			itemList = new std::list<STimerItem*>();
			if (itemList == NULL) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "_addTimer[%lld][%lld] Ê§°Ü", point, a_msDelay);
				return false;
			}
			m_stages[2][a_timerItem->m_timerPoint.m_bits[2]] = itemList;
		}
		itemList->push_back(a_timerItem);
		return true;
	}
	
	if (point <= BSLIB_UINT32_MAX) {
		a_timerItem->m_timerPoint.m_number = (BSLib::uint32)(m_stagesPoint.m_number + point);
		std::list<STimerItem*>* itemList = m_stages[3][a_timerItem->m_timerPoint.m_bits[3]];
		if (itemList == NULL) {
			itemList = new std::list<STimerItem*>();
			if (itemList == NULL) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "_addTimer[%lld][%lld] Ê§°Ü", point, a_msDelay);
				return false;
			}
			m_stages[3][a_timerItem->m_timerPoint.m_bits[3]] = itemList;
		}
		itemList->push_back(a_timerItem);
		return true;
	}

	BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "_addTimer[%lld][%lld] Ê§°Ü", point, a_msDelay);

	return false;
}

void CTimerServer::_adjustTimer1(BSLib::uint8 point)
{
	std::list<STimerItem*>* currentItemList = m_stages[1][point];
	if (currentItemList == NULL) {
		return ;
	}
	std::list<STimerItem*>::iterator it;
	for (it = currentItemList->begin(); it != currentItemList->end(); ++it){
		STimerItem* item = *it;
		if (item == NULL) {
			continue;
		}
		if (!item->m_isUser) {
			BSLIB_SAFE_DELETE(item);
			continue;
		}
		std::list<STimerItem*>* itemList = m_stages[0][item->m_timerPoint.m_bits[0]];
		if (itemList == NULL) {
			itemList = new std::list<STimerItem*>();
			if (itemList == NULL) {
				currentItemList->clear();
				return ;
			}
			m_stages[0][item->m_timerPoint.m_bits[0]] = itemList;
		}
		itemList->push_back(item);
	}
	currentItemList->clear();
}

void CTimerServer::_adjustTimer2(BSLib::uint8 point)
{
	std::list<STimerItem*>* currentItemList = m_stages[2][point];
	if (currentItemList == NULL) {
		return ;
	}
	std::list<STimerItem*>::iterator it;
	for (it = currentItemList->begin(); it != currentItemList->end(); ++it){
		STimerItem* item = *it;
		if (item == NULL) {
			continue;
		}
		if (!item->m_isUser) {
			BSLIB_SAFE_DELETE(item);
			continue;
		}
		if (item->m_timerPoint.m_bits[1] == 0) {
			std::list<STimerItem*>* itemList0 = m_stages[0][item->m_timerPoint.m_bits[0]];
			if (itemList0 == NULL) {
				itemList0 = new std::list<STimerItem*>();
				if (itemList0 == NULL) {
					currentItemList->clear();
					return ;
				}
				m_stages[0][item->m_timerPoint.m_bits[0]] = itemList0;
			}
			itemList0->push_back(item);
			continue;
		}
		std::list<STimerItem*>* itemList1 = m_stages[1][item->m_timerPoint.m_bits[1]];
		if (itemList1 == NULL) {
			itemList1 = new std::list<STimerItem*>();
			if (itemList1 == NULL) {
				currentItemList->clear();
				return ;
			}
			m_stages[1][item->m_timerPoint.m_bits[1]] = itemList1;
		}
		itemList1->push_back(item);
	}
	currentItemList->clear();
}

void CTimerServer::_adjustTimer3(BSLib::uint8 point)
{
	std::list<STimerItem*>* currentItemList = m_stages[3][point];
	if (currentItemList == NULL) {
		return ;
	}
	std::list<STimerItem*>::iterator it;
	for (it = currentItemList->begin(); it != currentItemList->end(); ++it){
		STimerItem* item = *it;
		if (item == NULL) {
			continue;
		}
		if (!item->m_isUser) {
			BSLIB_SAFE_DELETE(item);
			continue;
		}
		if (item->m_timerPoint.m_bits[2] == 0) {
			if (item->m_timerPoint.m_bits[1] == 0) {
				std::list<STimerItem*>* itemList0 = m_stages[0][item->m_timerPoint.m_bits[0]];
				if (itemList0 == NULL) {
					itemList0 = new std::list<STimerItem*>();
					if (itemList0 == NULL) {
						currentItemList->clear();
						return ;
					}
					m_stages[0][item->m_timerPoint.m_bits[0]] = itemList0;
				}
				itemList0->push_back(item);
				continue;
			}
			std::list<STimerItem*>* itemList1 = m_stages[1][item->m_timerPoint.m_bits[1]];
			if (itemList1 == NULL) {
				itemList1 = new std::list<STimerItem*>();
				if (itemList1 == NULL) {
					currentItemList->clear();
					return ;
				}
				m_stages[1][item->m_timerPoint.m_bits[1]] = itemList1;
			}
			itemList1->push_back(item);
			continue;
		}
		std::list<STimerItem*>* itemList2 = m_stages[2][item->m_timerPoint.m_bits[2]];
		if (itemList2 == NULL) {
			itemList2 = new std::list<STimerItem*>();
			if (itemList2 == NULL) {
				currentItemList->clear();
				return ;
			}
			m_stages[2][item->m_timerPoint.m_bits[2]] = itemList2;
		}
		itemList2->push_back(item);
	}
	currentItemList->clear();
}

void  CTimerServer::_clear()
{
	for (int i=0; i<TIMER_NUMBER_BITS_MAX; ++i) {
		for (BSLib::uint32 j=0; j<m_stages[i].size(); ++j) {
			std::list<STimerItem*>* itemList = m_stages[i][j];
			if (itemList == NULL) {
				continue;
			}
			std::list<STimerItem*>::iterator it = itemList->begin();
			for (; it != itemList->end(); ++it) {
				STimerItem* item = *it;
				if (item == NULL) {
					continue;
				}
				if (item->m_isUser) {
					continue;
				}
				BSLIB_SAFE_DELETE(item);
			}
			itemList->clear();
			BSLIB_SAFE_DELETE(itemList);
		}
		m_stages[i].clear();
	}

	CHashMap<TimerHandle, STimerItem*>::iterator it_timers;
	for (it_timers = m_timers.begin(); it_timers != m_timers.end(); ++it_timers) {
		STimerItem* item = it_timers->second;
		if (item != NULL) {
			BSLIB_SAFE_DELETE(item);
		}
	}
	m_timers.clear();
}
}//Utility

}//BSLib

