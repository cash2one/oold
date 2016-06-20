//////////////////////////////////////////////////////////////////////
//	created:	2012/07/09
//	filename:	src\BSLib\utility\memory\memPool.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_MEMORY_MEMPOOL_H__
#define __BSLIB_UTILITY_MEMORY_MEMPOOL_H__

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

struct SMemDebuInfor
{
};

struct SMemHead
{
	uint32 m_size;
	SMemDebuInfor* m_debugInfor;
	uint8 m_buff[1];
};

class CMemPool
{
public:
	CMemPool(int size, int index);

	int getIndex() { return m_index; }
	int getSize() { return m_size; }

	bool isEmpty() { return m_memPoolList.empty(); }

	void push(SMemHead* memHead);
	SMemHead* pop();

private:
	int m_index;
	int m_size;

	std::list<SMemHead*> m_memPoolList;
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_MEMORY_MEMPOOL_H__

