#include <BSLib/utility/tracer.h>
#include <BSLib/utility/string.h>
#include <BSLib/utility/thread/mutex.h>

#ifdef _LINUX

#include <sys/ipc.h>
#include <sys/sem.h>

#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
/* union semun is defined by including <sys/sem.h> */
#else
/* according to X/OPEN we have to define it ourselves */
union semun {
	int val;                  /* value for SETVAL */
	struct semid_ds *buf;     /* buffer for IPC_STAT, IPC_SET */
	unsigned short *array;    /* array for GETALL, SETALL */
	/* Linux specific part: */
	struct seminfo *__buf;    /* buffer for IPC_INFO */
};
#endif

#endif // _LINUX

namespace BSLib
{

namespace Utility
{

//////////////////////////////////////////////////////////////////////////

CMutex::CMutex()
{
#ifdef WIN32

	InitializeCriticalSection(&m_handle);

#elif defined(_LINUX)

	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_FAST_NP);
	pthread_mutex_init(&m_handle, &attr);

#endif
}

CMutex::~CMutex()
{
#ifdef WIN32

	DeleteCriticalSection(&m_handle);

#elif defined(_LINUX)
	
	pthread_mutex_destroy(&m_handle);
	
#endif
}

void CMutex::lock()
{


#ifdef WIN32

	EnterCriticalSection(&m_handle);

#elif defined(_LINUX)
	
	pthread_mutex_lock(&m_handle);

#endif
}

void CMutex::unlock()
{
#ifdef WIN32

	LeaveCriticalSection(&m_handle);

#elif defined(_LINUX)

	pthread_mutex_unlock(&m_handle);

#endif
}

//////////////////////////////////////////////////////////////////////////
#if defined(WIN32)

#define BSLIB_UTILITY_HNDMUTEXPROCESS_INVALID NULL

#elif defined(_LINUX)

#define BSLIB_UTILITY_HNDMUTEXPROCESS_INVALID -1

#endif

CMutexProcess::CMutexProcess()
: m_hndMutexProcess(BSLIB_UTILITY_HNDMUTEXPROCESS_INVALID)
, m_key(0)
{
	;
}

CMutexProcess::~CMutexProcess()
{
	close();
}

bool CMutexProcess::create(BSLib::uint32 a_key, bool a_lockNow)
{
	if (m_hndMutexProcess != BSLIB_UTILITY_HNDMUTEXPROCESS_INVALID) {
		return false;
	}

#if defined(WIN32)

	CStringA keyName;
	keyName.format("base_utility_%x", a_key);
	m_hndMutexProcess = ::CreateMutex(NULL, a_lockNow, keyName.c_str());
	if (m_hndMutexProcess == BSLIB_UTILITY_HNDMUTEXPROCESS_INVALID) {
		return false;
	}
	if (::GetLastError() == ERROR_ALREADY_EXISTS) {
		::CloseHandle(m_hndMutexProcess);
		m_hndMutexProcess = BSLIB_UTILITY_HNDMUTEXPROCESS_INVALID;
		return false;
	}

#elif defined(_LINUX)

	m_hndMutexProcess = ::semget(a_key, 1, IPC_CREAT | IPC_EXCL | 0666);
	if(m_hndMutexProcess < 0) {
		return false;
	}
	semun arg; 
	if (a_lockNow) {
		arg.val = 0;
	} else {
		arg.val = 1;;
	}
	if (::semctl(m_hndMutexProcess, 0, SETVAL, arg) < 0){
		::semctl(m_hndMutexProcess, 0, IPC_RMID);
		return false;
	}

#endif

	m_key = a_key;
	return true;
}

bool CMutexProcess::open(BSLib::uint32 a_key)
{
	if (m_hndMutexProcess != BSLIB_UTILITY_HNDMUTEXPROCESS_INVALID) {
		return false;
	}

#if defined(WIN32)

	CStringA keyName;
	keyName.format("base_utility_%x", a_key);
	m_hndMutexProcess = ::OpenMutex(MUTEX_ALL_ACCESS, FALSE, keyName.c_str());
	if (m_hndMutexProcess == BSLIB_UTILITY_HNDMUTEXPROCESS_INVALID) {
		return false;
	}

#elif defined(_LINUX)

	m_hndMutexProcess = ::semget(a_key, 1, IPC_CREAT | 0666);
	if(m_hndMutexProcess < 0) {
		return false;
	}

#endif

	m_key = a_key;
	return true;
}

void CMutexProcess::close()
{
	if (m_hndMutexProcess == BSLIB_UTILITY_HNDMUTEXPROCESS_INVALID) {
		return ;
	}
#if defined(WIN32)

	::CloseHandle(m_hndMutexProcess);
	
#elif defined(_LINUX)

	int semncnt = ::semctl(m_hndMutexProcess, 0, GETNCNT, 0);
	int sempid = ::semctl(m_hndMutexProcess, 0, GETPID, 0);
	int slefpid = ::getpid();

	if (semncnt == 0 && sempid == slefpid) {
		::semctl(m_hndMutexProcess, 0, IPC_RMID);
	} else if (semncnt < 0) {
		::semctl(m_hndMutexProcess, 0, IPC_RMID);
	}

#endif
	
	m_hndMutexProcess = BSLIB_UTILITY_HNDMUTEXPROCESS_INVALID;
}

void CMutexProcess::lock()
{
	if (m_hndMutexProcess == BSLIB_UTILITY_HNDMUTEXPROCESS_INVALID) {
		return ;
	}

#if defined(WIN32)

	UINT32 timeOut = INFINITE;
	DWORD waitResult;
	waitResult = WaitForSingleObject(m_hndMutexProcess, timeOut);
	switch (waitResult) 
	{ 
	case WAIT_OBJECT_0: 
		{
			return;
		}
		break; 
	default:
		break; 
	}

#elif defined(_LINUX)

	sembuf askfor_res;

	askfor_res.sem_num = 0;
	askfor_res.sem_op = -1;
	askfor_res.sem_flg = SEM_UNDO;		

	if (::semop(m_hndMutexProcess, &askfor_res, 1) < 0) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "CMutexProcess::lock error[%d]\n", errno);
		while (errno == EINVAL || errno == EIDRM) {
			m_hndMutexProcess = BSLIB_UTILITY_HNDMUTEXPROCESS_INVALID;
			if (create(m_key, true)) {
				BSLIB_LOG_INFO(ETT_BSLIB_UTILITY, "CMutexProcess::lock create sem\n");
				break;
			}
			if (open(m_key)) {
				if (::semop(m_hndMutexProcess, &askfor_res, 1) >= 0) {
					BSLIB_LOG_INFO(ETT_BSLIB_UTILITY, "CMutexProcess::lock open sem\n");
					break;
				}
			}
			BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "CMutexProcess::lock error[%d]\n", errno);
		}
	}

#endif
}

void CMutexProcess::unlock()
{
	if (m_hndMutexProcess == BSLIB_UTILITY_HNDMUTEXPROCESS_INVALID) {
		return ;
	}

#if defined(WIN32)

	ReleaseMutex(m_hndMutexProcess);

#elif defined(_LINUX)

	sembuf askfor_res;

	askfor_res.sem_num = 0;
	askfor_res.sem_op = 1;
	askfor_res.sem_flg = SEM_UNDO;		

	if (::semop(m_hndMutexProcess, &askfor_res, 1) < 0) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "CMutexProcess::unlock error[%d]\n", errno);
	}

#endif
}

//////////////////////////////////////////////////////////////////////////

#if defined(WIN32)

CRWLock::CRWLock()
: m_readCount(0)
{
	;
}

CRWLock::~CRWLock()
{
	;
}

void CRWLock::readLock()
{
	m_readLock.lock();
	++m_readCount;
	if (m_readCount == 1) {
		m_writeLock.lock();
	}
	m_readLock.unlock();
}

void CRWLock::readUnlock()
{
	if (m_readCount <= 0) {
		return ;
	}
	m_readLock.lock();
	--m_readCount;
	if (m_readCount == 0) {
		m_writeLock.unlock();
	}
	m_readLock.unlock();
}

void CRWLock::writeLock()
{
	m_writeLock.lock();
}

void CRWLock::writeUnlock()
{
	m_writeLock.unlock();
}

#elif defined(_LINUX)

CRWLock::CRWLock()
{
	pthread_rwlock_init(&m_rwLock, NULL);
}

CRWLock::~CRWLock()
{
	pthread_rwlock_destroy(&m_rwLock);
}

void CRWLock::readLock()
{
	pthread_rwlock_rdlock(&m_rwLock);
}

void CRWLock::readUnlock()
{
	pthread_rwlock_unlock(&m_rwLock);
}

void CRWLock::writeLock()
{
	pthread_rwlock_rdlock(&m_rwLock);
}

void CRWLock::writeUnlock()
{
	pthread_rwlock_unlock(&m_rwLock);
}

#endif

}//Utility

}//BSLib

