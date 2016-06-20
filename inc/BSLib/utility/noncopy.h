//////////////////////////////////////////////////////////////////////
//	created:	2012/06/30
//	filename: 	BSLib\utility\noncopy.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_NONCOPYABLE_H__
#define __BSLIB_UTILITY_NONCOPYABLE_H__

#include <BSLib/utility/baseDef.h>

namespace BSLib
{
	
namespace Utility
{
	
class  BSLIB_UTILITY_API CNoncopy
{
private:
	CNoncopy(const CNoncopy&);
	const CNoncopy& operator =(const CNoncopy&);

protected:
	CNoncopy() {}
	virtual ~CNoncopy() {}
};
	
}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_NONCOPYABLE_H__
