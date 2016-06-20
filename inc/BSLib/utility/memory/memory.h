//////////////////////////////////////////////////////////////////////
//	created:	2013/02/05
//	filename: 	BSLib\utility\memory\memory.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_MEMORY_MEMORY_H__
#define __BSLIB_UTILITY_MEMORY_MEMORY_H__

#include <BSLib/utility/memory/objectPool.h>

#define BSLIB_UTILITY_POOL_SIZE_MAX 4096
#define BSLIB_UTILITY_POOL_INDEX_MAX 34

namespace BSLib
{

namespace Utility
{
/*
class BSLIB_UTILITY_API CMemory
{
public:
	CMemory();
	~CMemory();

public:
	static void* allocateMemory(BSLib::uint32 a_size);
	static void deallocateMemory(void* a_data);

	static void* allocateMemory(BSLib::uint32 a_size, const char* a_fileName, int a_line);
	static void deallocateMemory(void* a_data, const char* a_fileName, int a_line);

private:
	void* _allocateMemory(BSLib::uint32 a_size);
	void _deallocateMemory(void* a_data);

private:
	static bool _registerMemoryInfor(void* a_data, const char* a_fileName, int a_line);
	static void _freeMemoryInfor(void* a_data);
	static void _addThreadMemory(CMemory* a_memory);

private:
	CUnitPool* m_unitPool[BSLIB_UTILITY_POOL_INDEX_MAX];
};
*/
}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_MEMORY_MEMORY_H__

