//////////////////////////////////////////////////////////////////////
//	created:	2013/02/13
//	filename:	src\BSLib\utility\memory\memory.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/memory/memory.h>
#include <BSLib/utility/thread/threadData.h>

namespace BSLib
{

namespace Utility
{
/*
//////////////////////////////////////////////////////////////////////////
BSLib::int16 g_pollSize[BSLIB_UTILITY_POOL_INDEX_MAX] = {
	4,		8,		12,		16,		32,		48,		64,		80,		96,		112,
	128,	144,	160,	192,	256,	320,	384,	512,	640,	768,  
	896,	1024,	1280,	1536,	1792,	2048,	2304,	2560,	2816,	3072, 
	3328,	3584,	3840,	4096};

//////////////////////////////////////////////////////////////////////////

class CPoolIndex
{
public:
	CPoolIndex()
	{
		_init();
	}

	BSLib::int16 getIndex(BSLib::uint32 a_size)
	{
		if (a_size > BSLIB_UTILITY_POOL_SIZE_MAX) {
			return -1;
		}
		return g_pollIndex[a_size];
	}


protected:
	void _init()
	{
		BSLib::int16 index = 0;
		for (BSLib::int16 i=0; i <= BSLIB_UTILITY_POOL_SIZE_MAX; ++i) {
			if (i > g_pollSize[index]) {
				index += 1;
			}
			g_pollIndex[i] = index;
		}
	}

private:
	BSLib::int16 g_pollIndex[BSLIB_UTILITY_POOL_SIZE_MAX + 1];
};

struct SUintHead 
{
	BSLib::uint16 m_size;
};

CPoolIndex g_poolIndex;
CThreadData g_threadMemory;

CMemory::CMemory()
{
	for (int i=0; i<BSLIB_UTILITY_POOL_INDEX_MAX; ++i) {
		m_unitPool[i] = NULL;
	}
}

CMemory::~CMemory()
{
	for (int i=0; i<BSLIB_UTILITY_POOL_INDEX_MAX; ++i) {
		if (m_unitPool[i] == NULL) {
			continue;
		}
		BSLIB_SAFE_DELETE(m_unitPool[i]);
	}
}

void* CMemory::allocateMemory(BSLib::uint32 a_size)
{
	CMemory* memory = (CMemory*)g_threadMemory.get();
	if (memory == NULL) {
		memory = new CMemory();
		if (memory == NULL) {
			return NULL;
		}
		g_threadMemory.set(memory);
		_addThreadMemory(memory);
	}
	return memory->_allocateMemory(a_size);
}

void CMemory::deallocateMemory(void* a_data)
{
	CMemory* memory = (CMemory*)g_threadMemory.get();
	if (memory == NULL) {
		memory = new CMemory();
		if (memory == NULL) {
			return ;
		}
		g_threadMemory.set(memory);
		_addThreadMemory(memory);
	}
	memory->_deallocateMemory(a_data);
}

void* CMemory::allocateMemory(BSLib::uint32 a_size, const char* fileName, int line)
{
	void* unit = allocateMemory(a_size);
	if (unit == NULL) {
		return NULL;
	}
	if (!_registerMemoryInfor(unit, fileName, line)) {
		deallocateMemory(unit);
		return NULL;
	}
	return unit;
}

void CMemory::deallocateMemory(void* a_data, const char* fileName, int line)
{
	if (a_data == NULL) {
		return;
	}
	_freeMemoryInfor(a_data);
	deallocateMemory(a_data);
}

void* CMemory::_allocateMemory(BSLib::uint32 a_size)
{
	BSLib::int16 index = g_poolIndex.getIndex(a_size);
	if (index < 0) {
		return NULL;
	}
	if (m_unitPool[index] == NULL) {
		uint32 size = g_pollSize[index] + sizeof(SUintHead);
		m_unitPool[index] = new CUnitPool(size);
		if (m_unitPool[index] == NULL) {
			return NULL;
		}
	}
	SUintHead* unitHead = (SUintHead*)m_unitPool[index]->allocUnit();
	if (unitHead == NULL) {
		return NULL;
	}
	unitHead->m_size = a_size;
	return &unitHead[1];
}

void CMemory::_deallocateMemory(void* a_data)
{
	;
}

bool CMemory::_registerMemoryInfor(void* a_data, const char* a_fileName, int a_line)
{
	return false;
}

void CMemory::_freeMemoryInfor(void* a_data)
{
	;
}

void CMemory::_addThreadMemory(CMemory* a_memory)
{
	;
}
*/
}//Utility

}//BSLib

