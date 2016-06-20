//////////////////////////////////////////////////////////////////////
//	created:	2012/08/08
//	filename: 	BSLib\utility\thread\event.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTLITY_THREAD_EVENT_H__
#define __BSLIB_UTLITY_THREAD_EVENT_H__

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CEvent
{
public:
	CEvent(bool manualReset = false);
	~CEvent();

	void set();
	void reset();
	int  wait(uint32 timeout = (uint32)-1);

private:
	bool m_manualReset;

#ifdef _WIN32
	HANDLE	m_event; 
#else
	pthread_mutex_t     m_mutex;
	bool				m_isSet;
	pthread_cond_t	    m_cond;
#endif

};

}//Utility

}//BSLib

#endif//__BSLIB_UTLITY_THREAD_EVENT_H__
