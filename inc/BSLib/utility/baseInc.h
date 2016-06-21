#ifndef __BSLIB_UTILITY_BASEINC_H__
#define __BSLIB_UTILITY_BASEINC_H__

#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>

#if defined(WIN32)

	#include <windows.h>

#elif defined(_LINUX)

	#include <sys/types.h>
	#include <unistd.h>
	#include <pthread.h>
	#include <errno.h>
	#include <signal.h>

#else

	#error "Unknown platform !!"  

#endif

#endif //__BSLIB_UTILITY_BASEINC_H__




