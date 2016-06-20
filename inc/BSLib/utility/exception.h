//////////////////////////////////////////////////////////////////////
//	created:	2015/04/09
//	filename: 	BSLib\utility\exception.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_EXCEPTION_H__
#define __BSLIB_UTILITY_EXCEPTION_H__

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CException : public std::exception
{
public:
	CException();
	CException(const std::string& a_what);
	CException(const CException& a_exception);
	~CException() throw();

#ifdef __GNUC__ 

public:
    virtual const char* what() const throw();
private:
	std::string m_what;

#endif

};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_EXCEPTION_H__