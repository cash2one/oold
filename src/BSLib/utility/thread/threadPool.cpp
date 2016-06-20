//////////////////////////////////////////////////////////////////////
//	created:	2015/04/01
//	filename: 	src\BSLib\utility\thread\threadPool.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/thread/threadPool.h>
#include <BSLib/utility/ptrQueue.h>
#include <BSLib/utility/thread/event.h>

namespace BSLib
{

namespace Utility
{

typedef BSLib::Utility::CPtrQueue<CThreadTaskPtr> CThreadPtrQueue;

//////////////////////////////////////////////////////////////////////////
class CThreadPoolCtrl : public CThread
{
public:
	CThreadPoolCtrl(CThreadPoolDataPtr& a_threadData)
		: m_isRunning(false)
		, m_threadData(a_threadData)
	{
		;
	}

	virtual void start()
	{
		m_isRunning = true;

		CThread::start();
	}

	virtual void terminate()
	{
		m_isRunning = false;
	}

	BSLib::int32 getTaskSize()
	{
		return m_threadQueue.size();
	}

	bool pushTask(CThreadTaskPtr& a_task)
	{
		if (!m_isRunning) {
			return false;
		}
		m_threadQueue.push(a_task);
		return true;
	}

protected:
	virtual void _run()
	{
		if (m_threadData != NULL) {
			m_threadData->init();
		}
		CThreadTaskPtr task = NULL;
		while (m_isRunning) {
			if (!m_threadQueue.pop(task)){
				if (!m_isRunning) {
					break;
				}
				CThread::msleep(15);
				continue;
			}
			if (task != NULL) {
				task->executeTask(m_threadData);
			}
		}
		if (m_threadData != NULL) {
			m_threadData->final();
		}
		m_threadData = NULL;
	}

private:
	bool m_isRunning;
	CThreadPtrQueue m_threadQueue;
	CThreadPoolDataPtr m_threadData;
};

//////////////////////////////////////////////////////////////////////////

CThreadPool::CThreadPool()
{
	;
}

CThreadPool::~CThreadPool()
{
	;
}

bool CThreadPool::init(uint32 a_threadCount)
{
	return init(a_threadCount, &CThreadPool::_createTheadData, this);
}

bool CThreadPool::init(uint32 a_threadCount,  CREATE_THREAD_DATA_FUN a_fun)
{
	CFunction<void, CThreadPoolDataPtr&> fun(a_fun);
	return init(a_threadCount, fun);
}

bool CThreadPool::init(uint32 a_threadCount, const CFunction<void, CThreadPoolDataPtr&>& a_fun)
{
	BSLib::Utility::CThreadPtr stubThread = NULL;
	for (uint32 i=0; i<a_threadCount; ++i) {

		CThreadPoolDataPtr threadDataPtr = NULL;
		if (a_fun.isValid()) {
			a_fun(threadDataPtr);
		}

		stubThread = new CThreadPoolCtrl(threadDataPtr);
		if (stubThread == NULL) {
			return false;
		}
		stubThread->start();
		m_threadArray.addThread(stubThread);
	}
	return true;
}

void CThreadPool::final()
{
	for (uint32 i=0;  i<m_threadArray.getSize(); ++i){
		BSLib::Utility::CThreadPtr& threadPtr = m_threadArray[i];
		CThreadPoolCtrl* threadCtrlPtr = (CThreadPoolCtrl*)threadPtr;
		if (threadCtrlPtr != NULL) {
			threadCtrlPtr->terminate();
		}
	}
	m_threadArray.joinAll();
}

bool CThreadPool::pushTask(CThreadTaskPtr& a_task)
{
	BSLib::int32 taskCountMax = BSLIB_INT32_MAX;

	CThreadPoolCtrl* threadCtrlPtr = NULL;
	for (uint32 i=0;  i<m_threadArray.getSize(); ++i){
		BSLib::Utility::CThreadPtr& threadPtr = m_threadArray[i];
		CThreadPoolCtrl* tmpThreadCtrlPtr = (CThreadPoolCtrl*)threadPtr;
		if (tmpThreadCtrlPtr == NULL) {
			continue;
		}
		int32 taskCount = tmpThreadCtrlPtr->getTaskSize();
		if (taskCountMax > taskCount) {
			taskCountMax = taskCount;
			threadCtrlPtr = tmpThreadCtrlPtr;
		}
	}
	if (threadCtrlPtr == NULL) {
		return false;
	}
	return threadCtrlPtr->pushTask(a_task);
}

}//Utility

}//BSLib