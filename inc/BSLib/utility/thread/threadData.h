//////////////////////////////////////////////////////////////////////
//	created:	2012/06/26
//	filename: 	BSLib\utility\thread\threadData.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_THREAD_THREADDATA_H__
#define __BSLIB_UTILITY_THREAD_THREADDATA_H__

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CThreadData
{
public:
	CThreadData();
	~CThreadData();

	bool set(void* data);
	void* get();

private:
#if defined( WIN32 )

	uint32 m_dataHandle;

#elif defined(_LINUX)

	pthread_key_t m_dataHandle;

#endif

	bool m_isOk;
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_THREAD_THREADDATA_H__
