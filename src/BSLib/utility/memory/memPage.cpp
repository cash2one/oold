#include "memory/memPage.h"

namespace BSLib
{

namespace Utility
{

#define BSLIB_UTILITY_BUFF_COUNT 32

CMemPage::CMemPage()
: m_index(0)
, m_size(0)
{
	;
}

CMemPage::~CMemPage()
{
	;
}

void CMemPage::init(int index, int size)
{
	m_index = index;
	m_size = size;
}

void CMemPage::final()
{
	;	
}

CMemPool* CMemPage::alloc()
{
	if (m_index == 0 || m_size == 0) {
		return NULL;
	}
	if (!m_memPoolList.empty()){
		CMemPool* memPool = *m_memPoolList.begin();
		m_memPoolList.pop_front();
		return memPool;
	}

	int buffSize = (sizeof(SMemHead)-1 + m_size) * BSLIB_UTILITY_BUFF_COUNT;
	uint8* buff = new uint8[buffSize];
	if (buff == NULL) {
		return NULL;
	}
	
	
	CMemPool* memPool = new CMemPool(m_size, m_index);
	if (memPool == NULL) {
		return NULL;
	}
	m_memBufferList.push_back(buff);

	SMemHead* memHead = NULL;
	int i=0;

	do {
		memHead = (SMemHead*)(buff + (sizeof(SMemHead) - 1 + m_size) * i);
		memHead->m_size = m_size;
		memHead->m_debugInfor = NULL;
		memPool->push(memHead);
		++i;
	} while (i < BSLIB_UTILITY_BUFF_COUNT);

	return memPool;
}

void CMemPage::free(CMemPool* memPool)
{
	m_memPoolList.push_back(memPool);
}

}//Utility

}//BSLib

