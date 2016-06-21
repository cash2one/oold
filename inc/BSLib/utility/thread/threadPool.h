#ifndef __BSLIB_UTILITY_THREAD_THREADPOOL_H__
#define __BSLIB_UTILITY_THREAD_THREADPOOL_H__

#include <BSLib/utility/thread/thread.h>
#include <BSLib/utility/pointer.h>

namespace BSLib
{

namespace Utility
{

class CThreadPoolData
{
public:
	virtual ~CThreadPoolData(){}

public:
	virtual void init() = 0;
	virtual void final() = 0;
};
typedef BSLib::Utility::CPointer<CThreadPoolData> CThreadPoolDataPtr;

class CThreadTask
{
public:
	virtual ~CThreadTask(){}

public:
	virtual void executeTask(CThreadPoolDataPtr& a_threadDataPtr) = 0;
};

typedef BSLib::Utility::CPointer<CThreadTask> CThreadTaskPtr;
typedef void(*CREATE_THREAD_DATA_FUN)(CThreadPoolDataPtr&);

class CThreadPool
{
public:
	CThreadPool();
	~CThreadPool();

	bool init(uint32 a_threadCount);
	bool init(uint32 a_threadCount, CREATE_THREAD_DATA_FUN a_fun);
	bool init(uint32 a_threadCount, const CFunction<void, CThreadPoolDataPtr&>& a_fun);
	
	template<class NAME>
	bool init(uint32 a_threadCount, void(NAME::*a_fun)(CThreadPoolDataPtr&), NAME* a_object)
	{
		CFunctionObject<void, NAME, CThreadPoolDataPtr&> objFun(a_fun, a_object);
		return init(a_threadCount, objFun);
	}

	void final();

	bool pushTask(CThreadTaskPtr& a_task);

protected:
	virtual void _createTheadData(CThreadPoolDataPtr& a_threadDataPtr) { }

private:
	BSLib::Utility::CThreadArray m_threadArray;
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_THREAD_THREADPOOL_H__
