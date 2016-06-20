//////////////////////////////////////////////////////////////////////
//	created:	2015/04/09
//	filename: 	BSLib\utility\exception.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/exception.h>

namespace BSLib
{

namespace Utility
{

CException::CException()
{
	;
}

CException::CException(const std::string& a_what)
#ifdef __GNUC__ 

: m_what(a_what)

#else

: std::exception(a_what.c_str())

#endif
{
	;
}

CException::CException(const CException& a_exception)
#ifdef __GNUC__ 

: m_what(a_exception.m_what)

#else

: std::exception(a_exception)

#endif
{
	;
}

CException::~CException() throw()
{
	;
}

#ifdef __GNUC__ 

const char* CException::what() const throw()
{
	return m_what.c_str();
}

#endif



}//Utility

}//BSLib
