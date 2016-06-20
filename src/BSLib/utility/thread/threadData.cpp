//////////////////////////////////////////////////////////////////////
//	created:	2012/06/25
//	filename:	src\BSLib\utility\thread\threadData.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/thread/threadData.h>

namespace BSLib
{

namespace Utility
{

CThreadData::CThreadData()
{
#if defined( WIN32 )

	m_dataHandle = ::TlsAlloc();
	if (m_dataHandle == TLS_OUT_OF_INDEXES){
		m_isOk = false;
	} else {
		m_isOk = true;
	}

#elif defined(_LINUX)

	if (pthread_key_create(&m_dataHandle, NULL) != 0){
		m_isOk = false;
	} else{
		m_isOk = true;
	}

#endif
}

CThreadData::~CThreadData()
{
#if defined( WIN32 )

	if (m_isOk) {
		TlsFree(m_dataHandle);
		m_dataHandle = TLS_OUT_OF_INDEXES;
	}

#elif defined(_LINUX)

	if (m_isOk) {
		pthread_key_delete(m_dataHandle);
	}

#endif
	m_isOk = false;
}

bool CThreadData::set(void* data)
{
	if (m_isOk == false){
		return false;
	}

#if defined( WIN32 )

	return TlsSetValue(m_dataHandle, data) != FALSE;

#elif defined(_LINUX)

	return pthread_setspecific(m_dataHandle, data) == 0;

#endif
}

void* CThreadData::get()
{
	if (m_isOk == false){
		return NULL;
	}

#if defined( WIN32 )

	return TlsGetValue(m_dataHandle);

#elif defined(_LINUX)

	return pthread_getspecific(m_dataHandle);

#endif
}

}//Utility

}//BSLib
