/********************************************************************
	created:	2012/06/29
	filename:	BSLib\utility\atomic.h
	author:		mazhejiang
	
	purpose:	
*********************************************************************/
#ifndef __BSLIB_UTILITY_ATOMIC_H__
#define __BSLIB_UTILITY_ATOMIC_H__

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

//////////////////////////////////////////////////////////////////////////
/// @brief 对整数的原子操作
//////////////////////////////////////////////////////////////////////////
class BSLIB_UTILITY_API CAtomic
{
public:
	CAtomic(int32 data = 0) : m_data(data) {}
	
	/// @brief
	/// @return BSLib::int32 递增后的整数
	int32 increment();
	int32 decrement();

	int32 getValue() { return m_data; }

public:
	static int32 increment(volatile int32& data);
	static int32 decrement(volatile int32& data);

private:
	mutable volatile int32 m_data;
};

}//Utility

}//BSLib


#endif//__BSLIB_UTILITY_ATOMIC_H__



