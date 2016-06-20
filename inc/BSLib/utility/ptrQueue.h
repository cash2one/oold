//////////////////////////////////////////////////////////////////////
//	created:	2012/07/08
//	filename: 	BSLib\utility\ptrQueue.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_PTRQUEUEE_H__
#define __BSLIB_UTILITY_PTRQUEUEE_H__

#include <BSLib/utility/atomic.h>

namespace BSLib
{

namespace Utility
{
//////////////////////////////////////////////////////////////////////////
/// @brief FIFO����ʵ�֣�ʵ��һ���򵥵Ļ��棬����ǵ��߳�д���̶߳����� �̰߳�ȫ��
///        ���� �̲߳���ȫ
//////////////////////////////////////////////////////////////////////////
template<typename TYPE>
class CPtrQueue
{
private:
	struct SQueueItem
	{
		SQueueItem* m_next;
		TYPE m_data;
		
		SQueueItem()
		{
			m_next = NULL;
			m_data = NULL;
		}
	};

public:
	CPtrQueue()
	{
		m_headItem = new SQueueItem();
		m_endItem = m_headItem;

		m_headRecycle = new SQueueItem();
		m_endRecycle = m_headRecycle;

		m_size = 0;
	}

	~CPtrQueue()
	{
		clear();
		if (m_headRecycle != NULL) {
			delete m_headRecycle;
		}
		if (m_headItem != NULL){
			delete m_headItem;
		}
		m_headItem = NULL;
		m_endItem = NULL;

		m_headRecycle = NULL;
		m_endRecycle = NULL;
	}

	/// @brief
	/// @return	bool
	/// @param	a_data
	bool push(const TYPE& a_data)
	{
		if (m_headItem != NULL){
			SQueueItem* item = NULL;
			if (m_endRecycle != NULL && m_endRecycle->m_next != NULL){
				item = m_endRecycle;
				m_endRecycle = m_endRecycle->m_next;
			}
			if (item == NULL) {
				item = new SQueueItem();
				if (item == NULL){
					return false;
				}
			}
			item->m_next = NULL;
			item->m_data = NULL;
			m_headItem->m_data = a_data;
			m_headItem->m_next = item;
			m_headItem = item;
			m_size.increment();
			return true;
		}
		return false;
	}

	/// @brief
	/// @return	bool
	/// @param	a_data
	bool get(TYPE& a_data)
	{

		if (m_endItem != NULL && m_endItem->m_next != NULL){
			a_data = m_endItem->m_data;
			return true;
		}
		return false;
	}

	/// @brief �Ӷ����е�����һ��item���������Ϊ�գ�����null
	/// @return TYPE
	/// @brief
	/// @return	bool
	/// @param	a_date
	bool pop(TYPE& a_data)
	{
		if (m_endItem != NULL && m_endItem->m_next != NULL){
			SQueueItem* item = m_endItem;
			m_endItem = m_endItem->m_next;
			a_data = item->m_data;
			
			item->m_next = NULL;
			item->m_data = NULL;

			m_headRecycle->m_next = item;
			m_headRecycle = item;
			m_size.decrement();
			return true;
		}
		a_data = NULL;
		return false;
	}

	bool empty()
	{
		return m_endItem == NULL || m_endItem->m_next == NULL;
	}

	void clear()
	{
		SQueueItem* item = NULL;

		while(m_endItem != NULL && m_endItem->m_next != NULL) {
			item = m_endItem;
			m_endItem = m_endItem->m_next;
			delete item;
		}

		while(m_endRecycle != NULL && m_endRecycle->m_next != NULL) {
			item = m_endRecycle;
			m_endRecycle = m_endRecycle->m_next;
			delete item;
		}
		m_size = 0;
	}

	int32 size()
	{
		return m_size.getValue();
	}

private:
	/// ������β
	SQueueItem* m_headItem;
	/// ������ͷ
	SQueueItem* m_endItem;

	/// ���տռ���� ��β
	SQueueItem* m_headRecycle;
	/// ���տռ���� ��ͷ
	SQueueItem* m_endRecycle;

	/// ���е�ǰ����
	CAtomic m_size;
};

}//Uutility

}//BSLib

#endif//__BSLIB_UTILITY_PTRQUEUEE_H__
