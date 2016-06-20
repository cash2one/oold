//////////////////////////////////////////////////////////////////////
//	created:	2012/06/30
//	filename:	src\BSLib\utility\thread\thread.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/thread/thread.h>

namespace BSLib
{

namespace Utility
{

#if defined(WIN32)

	typedef DWORD	ResThread;

#elif defined(_LINUX)

	typedef void*	ResThread;

#else

	#error "Unknown platform !!"  

#endif

typedef ResThread(*_THREAD_START_FUN_)(void*);
#define BSLIB_THREAD_RES(x) ((ResThread)(x))

struct SObjectThreadPara 
{
	CFunction<int, void*>* m_fun;
	void* m_para;
	CUint8Ptr m_thdState;

	SObjectThreadPara() :m_fun(NULL), m_para(NULL), m_thdState(NULL){}
};

ResThread runFunObjectThread(void* para)
{
	SObjectThreadPara* funPara = (SObjectThreadPara*)para;
	if (funPara == NULL) {
		return BSLIB_THREAD_RES(0);
	}
	if (funPara->m_fun == NULL) {
		return BSLIB_THREAD_RES(0);
	}

	BSLib::uint8* thdState = funPara->m_thdState;

	if (thdState != NULL){
		*thdState = 2;
	}

	ResThread res = BSLIB_THREAD_RES((*funPara->m_fun)(funPara->m_para));

	if (thdState != NULL){
		*thdState = 3;
	}

	BSLIB_SAFE_DELETE(funPara->m_fun);
	BSLIB_SAFE_DELETE(funPara);

	return res;
}

HndThread createThread(_THREAD_START_FUN_ funThread, void* pVoid, uint32 _stackSize)
{
#ifdef WIN32

	HndThread thdHandle = ::CreateThread(NULL, _stackSize, (LPTHREAD_START_ROUTINE)funThread, pVoid, 0, NULL) ;
	if (thdHandle == BSLIB_INVALID_HNDTHREAD){
		return BSLIB_INVALID_HNDTHREAD;
	}

#else

	pthread_t thdHandle;
	pthread_attr_t attr;
		pthread_attr_init(&attr);
		if (_stackSize >= 0){
			pthread_attr_setstacksize(&attr, _stackSize);
	}
	if (::pthread_create(&thdHandle, &attr, funThread, pVoid) != 0) {
		return BSLIB_INVALID_HNDTHREAD;
	}

#endif

	return thdHandle;
}

//////////////////////////////////////////////////////////////////////////
// CThreadHandle
//////////////////////////////////////////////////////////////////////////
CHndThread::CHndThread()
: m_thdHandle(BSLIB_INVALID_HNDTHREAD)
, m_thdState(NULL)
{
	;
}

CHndThread::CHndThread(const CHndThread& thdHandle)
: m_thdHandle(thdHandle.m_thdHandle)
, m_thdState(thdHandle.m_thdState)
{
	;
}

void CHndThread::join()
{
	if (m_thdHandle == BSLIB_INVALID_HNDTHREAD) {
		return ;
	}
	uint8* state = m_thdState;
	if (state == NULL){
		return ;
	}
	
	if (*state <= 0 || *state >= 3) {
		return ;
	}
	if (*state == 1) {
		while (*state == 1){
			CThread::msleep(1);
		}
		if (*state != 2) {
			return ;
		}
	}

#ifdef WIN32

	if (::WaitForSingleObject(m_thdHandle, INFINITE) != WAIT_OBJECT_0) {
		// 异常;
	}
	
#elif defined(_LINUX)

// 	if (::pthread_join(m_thdHandle, NULL) != 0){
// 		// 异常;
// 	}
	while (*state == 2){
		CThread::msleep(10);
	}

#endif
	m_thdHandle = BSLIB_INVALID_HNDTHREAD;
	*state = 0;
}

void CHndThread::cancel()
{
	if (m_thdHandle == BSLIB_INVALID_HNDTHREAD) {
		return ;
	}
	uint8* state = m_thdState;
	if (state == NULL){
		return ;
	}
	if (*state <= 0 || *state >= 3) {
		return ;
	}
	if (*state == 1) {
		while (*state == 1){
			CThread::msleep(1);
		}
		if (*state != 2) {
			return ;
		}
	}

#ifdef WIN32

	if (::TerminateThread(m_thdHandle, 0) == NULL) {
		// 异常;
	}

#elif defined(_LINUX)

	if (::pthread_cancel(m_thdHandle) != 0){
		// 异常;
	}

#endif

	m_thdHandle= BSLIB_INVALID_HNDTHREAD;
	*state = 0;
}

bool CHndThread::isValid()
{
	uint8* state = m_thdState;
	if (state == NULL){
		return false;
	}
	return m_thdHandle != BSLIB_INVALID_HNDTHREAD && (*state == 1 || *state == 2);
}	

CHndThread CHndThread::createThread(THREAD_START_FUN funThread, void* pVoid, uint32 _stackSize)
{
	SObjectThreadPara* threadPara = new SObjectThreadPara();
	if (threadPara == NULL) {
		return CHndThread();
	}
	threadPara->m_fun = new CFunction<int, void*>(funThread);
	if (threadPara->m_fun == NULL) {
		BSLIB_SAFE_DELETE(threadPara);
		return CHndThread();
	}
	threadPara->m_para = pVoid;
	threadPara->m_thdState = new uint8(1);
	if (threadPara->m_thdState == NULL) {
		BSLIB_SAFE_DELETE(threadPara->m_fun);
		BSLIB_SAFE_DELETE(threadPara);
		return CHndThread();
	}

	HndThread handle = BSLib::Utility::createThread(runFunObjectThread, threadPara, _stackSize);
	if (handle == BSLIB_INVALID_HNDTHREAD){
		BSLIB_SAFE_DELETE(threadPara->m_fun);
		BSLIB_SAFE_DELETE(threadPara);
		return CHndThread();
	}

	CHndThread thdHandle;
	thdHandle.m_thdHandle = handle;
	thdHandle.m_thdState = (CUint8Ptr)threadPara->m_thdState;

	return thdHandle;
}

CHndThread CHndThread::createThread(const CFunction<int, void*>& fun, void* pVoid, uint32 _stackSize)
{
	SObjectThreadPara* threadPara = new SObjectThreadPara();
	if (threadPara == NULL) {
		return CHndThread();
	}
	threadPara->m_fun = fun.clone();
	if (threadPara->m_fun == NULL) {
		BSLIB_SAFE_DELETE(threadPara);
		return CHndThread();
	}
	threadPara->m_para = pVoid;
	threadPara->m_thdState = new uint8(1);
	if (threadPara->m_thdState == NULL) {
		BSLIB_SAFE_DELETE(threadPara->m_fun);
		BSLIB_SAFE_DELETE(threadPara);
		return CHndThread();
	}

	HndThread handle = BSLib::Utility::createThread(runFunObjectThread, threadPara, _stackSize);
	if (handle == BSLIB_INVALID_HNDTHREAD){
		BSLIB_SAFE_DELETE(threadPara->m_fun);
		BSLIB_SAFE_DELETE(threadPara);
		return CHndThread();
	}

	CHndThread thdHandle;
	thdHandle.m_thdHandle = handle;
	thdHandle.m_thdState = (CUint8Ptr)threadPara->m_thdState;

	return thdHandle;
}

CHndThread CHndThread::operator =(const CHndThread& thdHandle) 
{
	m_thdHandle = thdHandle.m_thdHandle;
	m_thdState = thdHandle.m_thdState;
	return *this;
}

bool CHndThread::operator ==(const HndThread& thdHandle) const
{ 
	return m_thdHandle == thdHandle;
}

bool CHndThread::operator ==(const CHndThread& thdHandle) const
{
	return m_thdHandle == thdHandle.m_thdHandle; 
}

bool CHndThread::operator !=(const HndThread& thdHandle) const
{ 
	return m_thdHandle != thdHandle;
}

bool CHndThread::operator !=(const CHndThread& thdHandle) const
{ 
	return m_thdHandle != thdHandle.m_thdHandle;
}

//////////////////////////////////////////////////////////////////////////
// CThread
//////////////////////////////////////////////////////////////////////////
CThread::CThread()
{
	m_threadFun = new BSLib::Utility::CFunctionObject<void, CThread>(&CThread::_run, this);
}

CThread::~CThread()
{
	if (m_thdHandle.isValid()){
		m_thdHandle.cancel();
	}

	if (m_threadFun != NULL){
		BSLIB_SAFE_DELETE(m_threadFun);
	}
}

void CThread::start()
{
	if (m_thdHandle.isValid()){
		return ;
	}

	m_thdHandle = CHndThread::createThread(&CThread::_threadRunFun, this, NULL);
}

bool CThread::isValid()
{
	return m_thdHandle.isValid();
}

void CThread::join()
{
	m_thdHandle.join();
}
void CThread::cancel()
{
	m_thdHandle.cancel();
}

void CThread::setThreadFun(BSLib::Utility::CFunction<void>& fun)
{
	if (m_threadFun != NULL){
		BSLIB_SAFE_DELETE(m_threadFun);
	}
	m_threadFun = fun.clone();
}

void CThread::_run()
{
	;
}

void CThread::sleep(uint32 sec)
{
#ifdef WIN32

	msleep(sec * 1000);

#elif defined(_LINUX)
	
	::sleep(sec);

#endif
}

void CThread::msleep(uint32 msec)
{
#ifdef WIN32
	
	Sleep(msec);

#elif defined(_LINUX)
	
	::usleep(msec * 1000);

#endif
}

uint32 CThread::getNumberOfProcessors()
{
#ifdef WIN32

	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si.dwNumberOfProcessors;

#elif defined(_LINUX)

	return (uint32)sysconf(_SC_NPROCESSORS_ONLN);;

#endif
}

int CThread::_threadRunFun(void* pVoid)
{
	if (m_threadFun != NULL){
		(*m_threadFun)();
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// CThreadAarry
//////////////////////////////////////////////////////////////////////////
CThreadArray::CThreadArray()
{
	;
}

CThreadArray::~CThreadArray()
{
	;
}

bool CThreadArray::addThread(CThreadPtr& threadPtr)
{
	if (threadPtr == NULL || threadPtr->getHndThread() == 0) {
		return false;
	}
	CMutexFun fun(&m_mutex);
	for (std::vector<CThreadPtr>::iterator it = m_threadList.begin(); it != m_threadList.end(); ++it){
		CThreadPtr& tempThdPtr = *it;
		if (tempThdPtr == NULL){
			continue;
		}
		if (tempThdPtr->getHndThread() == threadPtr->getHndThread()){
			return false;
		}
	}
	m_threadList.push_back(threadPtr);
	return true;
}

CThreadPtr& CThreadArray::getThread(uint32 index)
{
	static CThreadPtr threadPtr(NULL);

	CMutexFun fun(&m_mutex);
	if (index >= m_threadList.size()){
		return threadPtr;
	}
	return m_threadList[index];
}

uint32 CThreadArray::getSize()
{
	CMutexFun fun(&m_mutex);
	return (uint32)m_threadList.size();
}

void CThreadArray::startAll()
{
	CMutexFun fun(&m_mutex);
	for (std::vector<CThreadPtr>::iterator it = m_threadList.begin(); it != m_threadList.end(); ++it){
		CThreadPtr& tempThdPtr = *it;
		if (tempThdPtr == NULL){
			continue;
		}
		if (tempThdPtr->isValid()) {
			continue;
		}
		tempThdPtr->start();
	}
}

void CThreadArray::cancelAll()
{
	CMutexFun fun(&m_mutex);
	while (!m_threadList.empty()) {
		CThreadPtr& tempThdPtr = m_threadList.back();
		if (tempThdPtr == NULL){
			m_threadList.pop_back();
			continue;
		}
		if (!tempThdPtr->isValid()) {
			m_threadList.pop_back();
			continue;
		}
		tempThdPtr->cancel();
		m_threadList.pop_back();
	}
}

void CThreadArray::joinAll()
{
	CMutexFun fun(&m_mutex);
	while (!m_threadList.empty()) {
		CThreadPtr& tempThdPtr = m_threadList.back();
		if (tempThdPtr == NULL){
			m_threadList.pop_back();
			continue;
		}
		if (!tempThdPtr->isValid()) {
			m_threadList.pop_back();
			continue;
		}
		tempThdPtr->join();
		m_threadList.pop_back();
	}
}

CThreadPtr& CThreadArray::operator [](uint32 index)
{
	return getThread(index);
}

}//Utility

}//BSLib
