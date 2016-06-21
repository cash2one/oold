#ifndef WIN32

#include <sys/time.h>

#endif

#include <BSLib/utility/thread/event.h>

namespace BSLib
{

namespace Utility
{

CEvent::CEvent(bool manualReset)
: m_manualReset(manualReset)
{
#ifdef _WIN32

	m_event = ::CreateEvent(NULL, m_manualReset, false, NULL); 

#else

	::pthread_mutex_init(&m_mutex, NULL); 
	::pthread_cond_init(&m_cond, NULL);
	m_isSet = false;

#endif
}

CEvent::~CEvent()
{
#ifdef _WIN32

	::CloseHandle(m_event);

#else

	::pthread_mutex_destroy(&m_mutex);
	::pthread_cond_destroy(&m_cond);

#endif
}

void CEvent::set()
{
#ifdef _WIN32

	::SetEvent(m_event);

#else

	if (!m_manualReset){
		::pthread_mutex_lock(&m_mutex);
		::pthread_cond_signal(&m_cond);
		::pthread_mutex_unlock(&m_mutex);
		return ;
	}
	if(!m_isSet) {
		::pthread_mutex_lock(&m_mutex);
		m_isSet = true;
		::pthread_cond_signal(&m_cond);
		::pthread_mutex_unlock(&m_mutex);
	}

#endif
}

void CEvent::reset()
{
#ifdef _WIN32

	::ResetEvent(m_event);

#else

	if (!m_manualReset){
		return ;
	}
	if(m_isSet){
		pthread_mutex_lock(&m_mutex);
		m_isSet = false;
		pthread_mutex_unlock(&m_mutex);
	}

#endif
}

int  CEvent::wait(uint32 timeout)
{
#ifdef _WIN32

	int res = -2;
	DWORD waitResult;
	waitResult = WaitForSingleObject(m_event, timeout);
	switch (waitResult){ 
	case WAIT_OBJECT_0: {
			res = 0;
			break;
		}
	case WAIT_TIMEOUT: {
			res = -1;
			break;
		}
	default:
		break; 
	}
	return res;

#else

	int res = -2;
	int waitResult = 0;
	
	if (timeout != BSLIB_UINT32_MAX) {
		timespec waitTimeout;

		clock_gettime(CLOCK_REALTIME, &waitTimeout);

		waitTimeout.tv_sec += timeout/1000;
		waitTimeout.tv_nsec += (timeout % 1000) * 1000 * 1000;

		if (waitTimeout.tv_nsec >= 1000000000){
			waitTimeout.tv_sec += 1;
			waitTimeout.tv_nsec -= 1000000000;
		}

		pthread_mutex_lock(&m_mutex);
beginwait1:
		waitResult = pthread_cond_timedwait(&m_cond, &m_mutex, &waitTimeout);
		switch (waitResult)
		{ 
		case 0: 
			{
				if (m_manualReset){
					if (!m_isSet){
						goto beginwait1;
					}
				}
				res = 0;
				break;
			}
		case ETIMEDOUT: 
			{
				res = -1;
				break;
			}
		default:
				break; 
		}
		pthread_mutex_unlock(&m_mutex);
		return res;
	}

	pthread_mutex_lock(&m_mutex);
beginwait2:
	waitResult = pthread_cond_wait(&m_cond, &m_mutex);
	switch (waitResult)
	{ 
	case 0: 
		{
			if (m_manualReset){
				if (!m_isSet){
					goto beginwait2;
				}
			}
			res = 0;
			break;
		}
	case ETIMEDOUT: 
		{
			res = -1;
			break;
		}
	default:
		break; 
	}
	pthread_mutex_unlock(&m_mutex);
	return res;

#endif
}

}//Utility

}//BSLib


