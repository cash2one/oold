//////////////////////////////////////////////////////////////////////
//	created:	2013/06/05
//	filename:	BSLib\utility\memory\shareMemory.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_SHAREMEMORY_H__
#define __BSLIB_UTILITY_SHAREMEMORY_H__

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CShareMemory
{
private:
#if defined(WIN32)

	typedef HANDLE HndShareMemory;

#elif defined(_LINUX)

	typedef int	HndShareMemory;

#else

#error "Unknown platform !!"  

#endif

public:
	CShareMemory();
	~CShareMemory();

	bool create(BSLib::uint32 a_key, BSLib::uint32 size);
	bool open(BSLib::uint32 a_key);

	void* getHeadAddress() { return m_headAddress; }

	void close();

private:
	HndShareMemory m_hndShareMemory;
	void* m_headAddress;
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_SHAREMEMORY_H__


