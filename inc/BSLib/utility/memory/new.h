//////////////////////////////////////////////////////////////////////
//	created:	2013/02/05
//	filename: 	BSLib\utility\memory\new.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_MEMORY_NEW_H__
#define __BSLIB_UTILITY_MEMORY_NEW_H__
/*
#include <BSLib/utility/baseDef.h>

BSLIB_UTILITY_API void* operator new(Base::uint32 a_size);

BSLIB_UTILITY_API void operator delete(void* a_data);

BSLIB_UTILITY_API void* operator new[](Base::uint32 a_size);

BSLIB_UTILITY_API void operator delete[](void* a_data);

BSLIB_UTILITY_API void* operator new(Base::uint32 a_size, const char* fileName, int line);

BSLIB_UTILITY_API void operator delete(void* a_data, const char* fileName, int line);

BSLIB_UTILITY_API void* operator new[](Base::uint32 a_size, const char* fileName, int line);

BSLIB_UTILITY_API void operator delete[](void* a_data, const char* fileName, int line);

#ifdef _DEBUG

#define BSLIB_NEW ::new(__FILE__, __LINE__)
#define BSLIB_DELETE ::delete(__FILE__, __LINE__)

#else

#define BSLIB_NEW ::new
#define BSLIB_DELETE ::delete

#endif//_DEBUG
*/
#define BSLIB_LOCAL_DEFINE_OBJECT(type, para, size) \
	char __tmepBuff##para [size]={0};\
	para = (type*)__tmepBuff##para;\
	new (static_cast<void*>(para)) type();

#endif//__BSLIB_UTILITY_MEMORY_NEW_H__

