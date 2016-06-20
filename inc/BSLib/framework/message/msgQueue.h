//////////////////////////////////////////////////////////////////////
//	created:	2012/07/20
//	filename: 	BSLib\framework\message\msgQueue.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_FRAMEWORK_MESSAGE_MSGQUEUE_H__
#define __BSLIB_FRAMEWORK_MESSAGE_MSGQUEUE_H__

#include <BSLib/utility/memory/allocator.h>
#include <BSLib/utility/ptrQueue.h>
#include <BSLib/utility/thread/event.h>

namespace BSLib
{

namespace Framework
{

//////////////////////////////////////////////////////////////////////////
/// @brief 队列类，可以同时绑定两个值到一个ITEM中
//////////////////////////////////////////////////////////////////////////
template<typename TYPE, typename TEMPTYPE = void>
class CMsgQueueBase
{
private:
	struct CMsgQueueItem
	{
		uint32 m_dataSize;
		uint32 m_tempDataSize;
	};

public:
	CMsgQueueBase(BSLib::Utility::CEvent* msgEvent) : m_msgEvent(msgEvent) {}
	virtual ~CMsgQueueBase()
	{
		clear();
	}

	/// @brief 将data与tempData绑定放入到队列中,类似socket中的readv/writev
	/// @return bool
	/// @param data
	/// @param dataSize
	/// @param tempData
	/// @param tempDataSize
	bool push(const TYPE* data, const uint32 dataSize, const TEMPTYPE* tempData = NULL, const uint32 tempDataSize = 0)
	{
		uint32 tempDataLen = tempDataSize;
		if (tempData == NULL){
			tempDataLen = 0;
		}

		unsigned char* dataBuff = m_allocator.allocate(dataSize + tempDataLen + sizeof(CMsgQueueItem));
		if (dataBuff == NULL) {
			return false;
		}

		CMsgQueueItem* queueItem = (CMsgQueueItem*)dataBuff; 
		
		TYPE* dataQueueItem = (TYPE*)(dataBuff + sizeof(CMsgQueueItem));
		queueItem->m_dataSize = dataSize;
		memcpy(dataQueueItem, data, dataSize);

		if (tempDataLen != 0)	{
			TEMPTYPE* tempDataQueueItem = (TEMPTYPE*)(dataBuff + dataSize + sizeof(CMsgQueueItem));
			queueItem->m_tempDataSize = tempDataLen;
			memcpy(tempDataQueueItem, tempData, tempDataLen);
		} else {
			queueItem->m_tempDataSize = 0;
		}
	
		m_prtQueue.push(queueItem);
		if (m_msgEvent != NULL){
			m_msgEvent->set();
		}
		return true;
	}

	/// @brief 从队列中取出data与tempData,类似socket中的readv/writev
	/// @return int
	/// @param data
	/// @param tempData
	/// @param tempDataSize
	int get(TYPE** data, TEMPTYPE** tempData = NULL, uint32* tempDataSize = NULL)
	{
		if (m_prtQueue.empty()){
			return 0;
		}
		
		CMsgQueueItem* queueItem = NULL;
		m_prtQueue.get(queueItem);

		unsigned char* dataBuff = (unsigned char*)queueItem;
		
		TYPE* dataQueueItem = (TYPE*)(dataBuff + sizeof(CMsgQueueItem));
		*data = dataQueueItem;

		if (queueItem->m_tempDataSize != 0){
			TEMPTYPE* tempDataQueueItem = (TEMPTYPE*)(dataBuff + queueItem->m_dataSize + sizeof(CMsgQueueItem));
			if (tempData != NULL){
				*tempData = tempDataQueueItem;
			}
			if (tempDataSize != NULL){
				*tempDataSize = queueItem->m_tempDataSize;
			}			
		} else {
			if (tempData != NULL){
				*tempData = NULL;
			}
			if (tempDataSize != NULL){
				*tempDataSize = 0;
			}
		}

		return queueItem->m_dataSize;
	}

	/// @brief 弹出队列头，并自动回收内存
	/// @return void
	void pop()
	{
		if (m_prtQueue.empty()){
			return ;
		}
		CMsgQueueItem* queueItem = NULL;
		m_prtQueue.get(queueItem);
		m_allocator.deallocate((unsigned char*)queueItem, queueItem->m_dataSize + queueItem->m_tempDataSize + sizeof(CMsgQueueItem));
		m_prtQueue.pop(queueItem);
	}

	void clear()
	{
		while (!m_prtQueue.empty()){
			CMsgQueueItem* queueItem = NULL;
			m_prtQueue.get(queueItem);
			m_allocator.deallocate((unsigned char*)queueItem, queueItem->m_dataSize + queueItem->m_tempDataSize + sizeof(CMsgQueueItem));
			m_prtQueue.pop(queueItem);
		}
	}

	bool empty()
	{
		return m_prtQueue.empty();
	}
	
private:
	BSLib::Utility::CPtrQueue< CMsgQueueItem* > m_prtQueue;
	//内存分配器
	BSLib::Utility::CAllocatorUint8 m_allocator;
	BSLib::Utility::CEvent* m_msgEvent;
};

#include <BSLib/framework/message/message.h>
#include <BSLib/framework/message/msgLabel.h>

typedef CMsgQueueBase<SMessage, SMsgLabel> CMsgQueue;
typedef int MsgQueueHandle;
const MsgQueueHandle INVALID_MSGQUEUEHANDLE = 0;

}//Framework

}//BSLib

#endif//__BSLIB_FRAMEWORK_MESSAGE_MSGQUEUE_H__

