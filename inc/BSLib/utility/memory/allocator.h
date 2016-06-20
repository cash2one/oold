//////////////////////////////////////////////////////////////////////
//	created:	2012/07/20
//	filename: 	BSLib\utility\memory\allocator.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_MEMORY_ALLOCATOR_H__
#define __BSLIB_UTILITY_MEMORY_ALLOCATOR_H__

#ifdef __GNUC__

#include <ext/pool_allocator.h>
#include <ext/mt_allocator.h>

#else

#include <xmemory>

#endif

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

#ifdef __GNUC__

	typedef __gnu_cxx::__mt_alloc<uint8> CAllocatorUint8;

#else

	typedef std::allocator<uint8> CAllocatorUint8;

#endif

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_ALLOCATOR_H__
