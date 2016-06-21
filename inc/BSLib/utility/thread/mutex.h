#ifndef __BSLIB_UTILITY_THREAD_MUTEX_H__
#define __BSLIB_UTILITY_THREAD_MUTEX_H__

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

#if defined(WIN32)

	typedef CRITICAL_SECTION HndMutex;

#elif defined(_LINUX)

	typedef pthread_mutex_t	HndMutex;

#else

	#error "Unknown platform !!"  

#endif

class BSLIB_UTILITY_API IMutex
{
public:
	virtual ~IMutex() {}
	virtual void lock() = 0;
	virtual void unlock() = 0;
};

//进程内部锁
class BSLIB_UTILITY_API CMutex : public IMutex
{
public:
	CMutex();
	virtual ~CMutex();

	virtual void lock();
	virtual void unlock();

private:
	HndMutex m_handle;

};

//进程之间锁
class BSLIB_UTILITY_API CMutexProcess : public IMutex
{
private:
#if defined(WIN32)

	typedef HANDLE HndMutexProcess;

#elif defined(_LINUX)

	typedef int	HndMutexProcess;

#else

#error "Unknown platform !!"  

#endif
	
public:
	CMutexProcess();
	virtual ~CMutexProcess();

	bool create(BSLib::uint32 a_key, bool a_lockNow = false);
	bool open(BSLib::uint32 a_key);

	void close();

	virtual void lock();
	virtual void unlock();

private:
	HndMutexProcess m_hndMutexProcess;
	BSLib::uint32 m_key;
};

//进程内部 读写锁
class BSLIB_UTILITY_API CRWLock
{
public:
	CRWLock();
	~CRWLock();

	void readLock();
	void readUnlock();
	void writeLock();
	void writeUnlock();

private:
#if defined(WIN32)

	CMutex m_readLock;
	CMutex m_writeLock;
	uint32 m_readCount;

#elif defined(_LINUX)

	pthread_rwlock_t m_rwLock;

#endif
};


class BSLIB_UTILITY_API CMutexFun
{
public:
	CMutexFun(IMutex* pMutex) : m_pMutex(pMutex)
	{
		if (m_pMutex){
			m_pMutex->lock();
		}
	}

	~CMutexFun()
	{
		if (m_pMutex){
			m_pMutex->unlock();
		}
	}
private:
	IMutex* m_pMutex;
};


}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_THREAD_MUTEX_H__


