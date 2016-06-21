#ifndef __BSLIB_UTILITY_MEMORY_MEMPAGE_H__
#define __BSLIB_UTILITY_MEMORY_MEMPAGE_H__

#include <BSLib/utility/baseDef.h>
#include "memory/memPool.h"

namespace BSLib
{

namespace Utility
{

class CMemPage
{
public:
	CMemPage();
	~CMemPage();
	void init(int index, int size);
	void final();

	CMemPool* alloc();
	void free(CMemPool* memPool);

	int getIndex() { return m_index; }
	int getSize() { return m_size; }

private:
	int m_index;
	int m_size;

	std::list<CMemPool*> m_memPoolList;
	std::list<uint8*> m_memBufferList;
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_MEMORY_MEMPAGE_H__


