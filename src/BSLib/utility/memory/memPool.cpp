//////////////////////////////////////////////////////////////////////
//	created:	2012/07/09
//	filename:	src\BSLib\utility\memory\memPage.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include "memory/memPool.h"

namespace BSLib
{

namespace Utility
{

CMemPool::CMemPool(int size, int index)
{
	m_index = index;
	m_size = size;
}

void CMemPool::push(SMemHead* memHead)
{
	;
}

SMemHead* CMemPool::pop()
{
	return NULL;
}

}//Utility

}//BSLib
