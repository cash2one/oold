//////////////////////////////////////////////////////////////////////
//	created:	2012/06/30
//	filename: 	BSLib\utility\thread\thread.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_THREAD_THREAD_H__
#define __BSLIB_UTILITY_THREAD_THREAD_H__

#include <BSLib/utility/pointer.h>
#include <BSLib/utility/thread/mutex.h>
#include <BSLib/utility/function.h>
#include <BSLib/utility/noncopy.h>

namespace BSLib
{

namespace Utility
{
#if defined(WIN32)

	typedef int(*THREAD_START_FUN)(void*);
	typedef HANDLE	HndThread;

	#define BSLIB_INVALID_HNDTHREAD NULL

#elif defined(_LINUX)

	typedef int(*THREAD_START_FUN)(void*);
	typedef pthread_t	HndThread;

	#define BSLIB_INVALID_HNDTHREAD 0

#else

#error "Unknown platform !!"  

#endif

typedef CPointer<BSLib::uint8> CUint8Ptr;

//////////////////////////////////////////////////////////////////////////
/// @brief 线程类，对线程操作的封装，通过createThread创建线程
//////////////////////////////////////////////////////////////////////////
class BSLIB_UTILITY_API CHndThread
{
public:
	CHndThread();
	CHndThread(const CHndThread& thdHandle);

	void join();
	void cancel();

	bool isValid();	
	
	CHndThread operator =(const CHndThread& thdHandle);

	bool operator ==(const HndThread& thdHandle) const;
	bool operator ==(const CHndThread& thdHandle) const;

	bool operator !=(const HndThread& thdHandle) const;
	bool operator !=(const CHndThread& thdHandle) const;

public:
	static CHndThread createThread(THREAD_START_FUN funThread, void* pVoid = NULL, uint32 _stackSize = 0);
	static CHndThread createThread(const CFunction<int, void*>& fun, void* pVoid = NULL, uint32 _stackSize = 0);
	
	template<class NAME>
	static CHndThread createThread(int(NAME::*fun)(void*), NAME* object, void* pVoid = NULL, uint32 _stackSize = 0)
	{
		CFunctionObject<int, NAME, void*> objFun(fun, object);
		return createThread(objFun, pVoid, _stackSize);
	}

protected:
	HndThread m_thdHandle;
	CUint8Ptr m_thdState;
};

//////////////////////////////////////////////////////////////////////////
/// @brief 线程类，对线程操作的封装，纯虚类，通过继承_run实现线程实体
//////////////////////////////////////////////////////////////////////////
class BSLIB_UTILITY_API CThread : private CNoncopy
{
public:
	CThread();
	virtual ~CThread();

	virtual void start();

	void join();
	void cancel();
	bool isValid();

	CHndThread& getHndThread() { return m_thdHandle; }

	void setThreadFun(BSLib::Utility::CFunction<void>& fun);

public:
	static void sleep(uint32 sec);
	static void msleep(uint32 msec);

	static uint32 getNumberOfProcessors();

protected:
	virtual void _run();

private:
	int _threadRunFun(void* pVoid);

private:
	CHndThread m_thdHandle;
	BSLib::Utility::CFunction<void>* m_threadFun;
};
typedef CPointer<CThread> CThreadPtr;

//////////////////////////////////////////////////////////////////////////
/// @brief 线程数组
//////////////////////////////////////////////////////////////////////////
class BSLIB_UTILITY_API CThreadArray : private CNoncopy
{
public:
	CThreadArray();
	virtual ~CThreadArray();

	bool addThread(CThreadPtr& threadPtr);
	CThreadPtr& getThread(uint32 index);
	uint32 getSize();

	void startAll();
	void cancelAll();
	void joinAll();

	CThreadPtr& operator [](uint32 index);

private:
	std::vector<CThreadPtr> m_threadList;
	CMutex m_mutex;
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_THREAD_THREAD_H__
