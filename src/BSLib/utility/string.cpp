//////////////////////////////////////////////////////////////////////
//	created:	2012/07/20
//	filename:	src\BSLib\utility\string.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <stdarg.h>
#include <BSLib/utility/string.h>
#include <BSLib/utility/convert.h>

namespace BSLib
{

namespace Utility
{

//////////////////////////////////////////////////////////////////////////

const std::string::value_type CSpecialCharA::m_A = 'A';
const std::string::value_type CSpecialCharA::m_Z = 'Z';
const std::string::value_type CSpecialCharA::m_a = 'a';
const std::string::value_type CSpecialCharA::m_z = 'z';
const std::string::value_type CSpecialCharA::m_percent = '%';


const std::wstring::value_type CSpecialCharW::m_A = L'A';
const std::wstring::value_type CSpecialCharW::m_Z = L'Z';
const std::wstring::value_type CSpecialCharW::m_a = L'a';
const std::wstring::value_type CSpecialCharW::m_z = L'z';
const std::wstring::value_type CSpecialCharW::m_percent = L'%';

//////////////////////////////////////////////////////////////////////////
CStringW CStringA::toWideString() const
{
	std::wstring outText;
	outText.resize(this->size());
	mbstowcs((wchar_t*)outText.c_str(), this->c_str(), this->size());
	return outText;
}

void CStringA::format(uint32 uParamCnt, const ValueType* pszFormat, ...)
{
	if (!CBasicString<std::string, CSpecialCharA>::_formatSafeCheck(uParamCnt, pszFormat)){
		return;
	}

	va_list args;
	va_start(args, pszFormat);

#ifdef WIN32

	uint32 nLength = _vscprintf(pszFormat, args);
	CBasicString<std::string, CSpecialCharA>::resize(nLength);
	_vsnprintf_s((ValueType*)CBasicString<std::string, CSpecialCharA>::c_str(), nLength + 1, _TRUNCATE, pszFormat, args);

#elif defined(_LINUX)

	uint32 nLength = vsnprintf(NULL, 0, pszFormat, args);
	va_end(args);

	CBasicString<std::string, CSpecialCharA>::resize(nLength);
	va_start(args, pszFormat);
	vsnprintf((ValueType*)CBasicString<std::string, CSpecialCharA>::c_str(), nLength + 1, pszFormat, args);

#else

	#error "Unknown platform !!"  

#endif

	va_end(args);
}

void CStringA::format(const ValueType* pszFormat, ...)
{
	va_list args;
	va_start(args, pszFormat);

#ifdef WIN32

	uint32 nLength = _vscprintf(pszFormat, args);
	CBasicString<std::string, CSpecialCharA>::resize(nLength);
	_vsnprintf_s((ValueType*)CBasicString<std::string, CSpecialCharA>::c_str(), nLength + 1, _TRUNCATE, pszFormat, args);

#elif defined(_LINUX)

	uint32 nLength = vsnprintf(NULL, 0, pszFormat, args);
	va_end(args);

	CBasicString<std::string, CSpecialCharA>::resize(nLength);
	va_start(args, pszFormat);
	vsnprintf((ValueType*)CBasicString<std::string, CSpecialCharA>::c_str(), nLength + 1, pszFormat, args);

#else

	#error "Unknown platform !!"  

#endif

	va_end(args);
}

CStringA& CStringA::operator =(const char data[])
{
	std::string::operator =(data);
	return *this;
}

CStringA& CStringA::operator =(const wchar_t data[])
{
	CStringW srcText(data);
	std::string outText;
	CConvert::unicodeToUTF8(outText, srcText);
	std::string::operator =(outText);
	return *this;
}

CStringA& CStringA::operator =(const CStringA& data)
{
	std::string::operator =(data);
	return *this;
}


CStringA& CStringA::operator =(const CStringW& data)
{
	std::string outText;
	CConvert::unicodeToUTF8(outText, data);
	std::string::operator =(outText);
	return *this;
}


CStringA& CStringA::operator =(const std::string& data)
{
	std::string::operator =(data);
	return *this;
}


CStringA& CStringA::operator =(const std::wstring& data)
{
	std::string outText;
	CConvert::unicodeToUTF8(outText, data);
	std::string::operator =(outText);
	return *this;
}

CStringA& CStringA::operator =(const int8& data)
{
	std::string::operator =(CConvert::toStringA((const int32)data));
	return *this;
}


CStringA& CStringA::operator =(const uint8& data)
{
	std::string::operator =(CConvert::toStringA((const uint32)data));
	return *this;
}


CStringA& CStringA::operator =(const int16& data)
{
	std::string::operator =(CConvert::toStringA((const int32)data));
	return *this;
}


CStringA& CStringA::operator =(const uint16& data)
{
	std::string::operator =(CConvert::toStringA((const uint32)data));
	return *this;
}


CStringA& CStringA::operator =(const int32& data)
{
	std::string::operator =(CConvert::toStringA(data));
	return *this;
}


CStringA& CStringA::operator =(const uint32& data)
{
	std::string::operator =(CConvert::toStringA(data));
	return *this;
}

CStringA& CStringA::operator =(const int64& data)
{
	std::string::operator =(CConvert::toStringA(data));
	return *this;
}

CStringA& CStringA::operator =(const uint64& data)
{
	std::string::operator =(CConvert::toStringA(data));
	return *this;
}

CStringA& CStringA::operator =(const float& data)
{
	std::string::operator =(CConvert::toStringA(data));
	return *this;
}

CStringA& CStringA::operator =(const double& data)
{
	std::string::operator =(CConvert::toStringA(data));
	return *this;
}

CStringA& CStringA::operator <<(const char data[])
{
	std::string::operator +=(data);
	return *this;
}

CStringA& CStringA::operator <<(const wchar_t data[])
{
	CStringW srcText(data);
	std::string outText;
	CConvert::unicodeToUTF8(outText, srcText);
	std::string::operator +=(outText);
	return *this;
}

CStringA& CStringA::operator <<(const CStringA& data)
{
	std::string::operator +=(data);
	return *this;
}

CStringA& CStringA::operator <<(const CStringW& data)
{
	std::string outText;
	CConvert::unicodeToUTF8(outText, data);
	std::string::operator +=(outText);
	return *this;
}

CStringA& CStringA::operator <<(const std::string& data)
{
	std::string::operator +=(data);
	return *this;
}

CStringA& CStringA::operator <<(const std::wstring& data)
{
	std::string outText;
	CConvert::unicodeToUTF8(outText, data);
	std::string::operator +=(outText);
	return *this;
}

CStringA& CStringA::operator <<(const int8& data)
{
	std::string::operator +=(CConvert::toStringA((const int32)data));
	return *this;
}

CStringA& CStringA::operator <<(const uint8& data)
{
	std::string::operator +=(CConvert::toStringA((const uint32)data));
	return *this;
}

CStringA& CStringA::operator <<(const int16& data)
{
	std::string::operator +=(CConvert::toStringA((const int32)data));
	return *this;
}

CStringA& CStringA::operator <<(const uint16& data)
{
	std::string::operator +=(CConvert::toStringA((const uint32)data));
	return *this;
}

CStringA& CStringA::operator <<(const int32& data)
{
	std::string::operator +=(CConvert::toStringA(data));
	return *this;
}

CStringA& CStringA::operator <<(const uint32& data)
{
	std::string::operator +=(CConvert::toStringA(data));
	return *this;
}

CStringA& CStringA::operator <<(const int64& data)
{
	std::string::operator +=(CConvert::toStringA(data));
	return *this;
}

CStringA& CStringA::operator <<(const uint64& data)
{
	std::string::operator +=(CConvert::toStringA(data));
	return *this;
}

CStringA& CStringA::operator <<(const float& data)
{
	std::string::operator +=(CConvert::toStringA(data));
	return *this;
}

CStringA& CStringA::operator <<(const double& data)
{
	std::string::operator +=(CConvert::toStringA(data));
	return *this;
}

const CStringA& CStringA::operator >>(CStringA& data) const
{
	data = *this;
	return *this;
}

const CStringA& CStringA::operator >>(CStringW& data) const
{
	CConvert::utf8ToUnicode(data, *this);
	return *this;
}

const CStringA& CStringA::operator >>(std::string& data) const 
{
	data = *this;
	return *this;
}

const CStringA& CStringA::operator >>(std::wstring& data) const
{
	CConvert::utf8ToUnicode(data, *this);
	return *this;
}

const CStringA& CStringA::operator >>(int8& data) const
{
	data = (int8)CConvert::toInt32(*this);
	return *this;
}

const CStringA& CStringA::operator >>(uint8& data) const
{
	data = (uint8)CConvert::toUint32(*this);
	return *this;
}

const CStringA& CStringA::operator >>(int16& data) const
{
	data = (int16)CConvert::toInt32(*this);
	return *this;
}

const CStringA& CStringA::operator >>(uint16& data) const
{
	data = (uint16)CConvert::toUint32(*this);
	return *this;
}

const CStringA& CStringA::operator >>(int32& data) const
{
	data = CConvert::toInt32(*this);
	return *this;
}

const CStringA& CStringA::operator >>(uint32& data) const
{
	data = CConvert::toUint32(*this);
	return *this;
}

const CStringA& CStringA::operator >>(int64& data) const
{
	data = CConvert::toInt64(*this);
	return *this;
}

const CStringA& CStringA::operator >>(uint64& data) const
{
	data = CConvert::toUint64(*this);
	return *this;
}

const CStringA& CStringA::operator >>(double& data) const
{
	data = CConvert::toDouble(*this);
	return *this;
}

const CStringA& CStringA::operator >>(float& data) const
{
	data = CConvert::toFloat(*this);
	return *this;
}

//////////////////////////////////////////////////////////////////////////

CStringA CStringW::toNarrowString() const
{
	std::string outText;
	outText.resize(this->size());
	wcstombs((char*)outText.c_str(), this->c_str(), this->size());
	return outText;
}


void CStringW::format(uint32 uParamCnt, const ValueType* pszFormat, ...)
{
	if (!CBasicString<std::wstring, CSpecialCharW>::_formatSafeCheck(uParamCnt, pszFormat)){
		return;
	}

	va_list args;
	va_start(args, pszFormat);

#ifdef WIN32

	uint32 nLength = _vscwprintf(pszFormat, args);
	CBasicString<std::wstring, CSpecialCharW>::resize(nLength);
	_vsnwprintf_s((ValueType*)CBasicString<std::wstring, CSpecialCharW>::c_str(), nLength + 1, _TRUNCATE, pszFormat, args);

#elif defined(_LINUX)

	uint32 nLength = vswprintf(NULL, 0, pszFormat, args);
	va_end(args);

	CBasicString<std::wstring, CSpecialCharW>::resize(nLength);
	va_start(args, pszFormat);
	vswprintf((ValueType*)CBasicString<std::wstring, CSpecialCharW>::c_str(), nLength + 1, pszFormat, args);

#else

#error "Unknown platform !!"  

#endif

	va_end(args);
}

void CStringW::format(const ValueType* pszFormat, ...)
{
	va_list args;
	va_start(args, pszFormat);

#ifdef WIN32

	uint32 nLength = _vscwprintf(pszFormat, args);
	CBasicString<std::wstring, CSpecialCharW>::resize(nLength);
	_vsnwprintf_s((ValueType*)CBasicString<std::wstring, CSpecialCharW>::c_str(), nLength + 1, _TRUNCATE, pszFormat, args);

#elif defined(_LINUX)

	uint32 nLength = vswprintf(NULL, 0, pszFormat, args);
	va_end(args);

	CBasicString<std::wstring, CSpecialCharW>::resize(nLength);
	va_start(args, pszFormat);
	vswprintf((ValueType*)CBasicString<std::wstring, CSpecialCharW>::c_str(), nLength + 1, pszFormat, args);

#else

#error "Unknown platform !!"  

#endif

	va_end(args);
}

CStringW& CStringW::operator =(const char data[])
{
	CStringA srcText(data);
	std::wstring outText;
	CConvert::utf8ToUnicode(outText, srcText);
	std::wstring::operator =(outText);
	return *this;
}

CStringW& CStringW::operator =(const wchar_t data[])
{
	std::wstring::operator =(data);
	return *this;
}

CStringW& CStringW::operator =(const CStringA& data)
{
	std::wstring outText;
	CConvert::utf8ToUnicode(outText, data);
	std::wstring::operator =(outText);
	return *this;
}

CStringW& CStringW::operator =(const CStringW& data)
{
	std::wstring::operator =(data);
	return *this;
}

CStringW& CStringW::operator =(const std::string& data)
{
	CStringA srcText(data);
	std::wstring outText;
	CConvert::utf8ToUnicode(outText, srcText);
	std::wstring::operator =(outText);
	return *this;
}

CStringW& CStringW::operator =(const std::wstring& data)
{
	std::wstring::operator =(data);
	return *this;
}

CStringW& CStringW::operator =(const int8& data)
{
	std::wstring::operator =(CConvert::toStringW((const int32)data));
	return *this;
}


CStringW& CStringW::operator =(const uint8& data)
{
	std::wstring::operator =(CConvert::toStringW((const uint32)data));
	return *this;
}


CStringW& CStringW::operator =(const int16& data)
{
	std::wstring::operator =(CConvert::toStringW((const int32)data));
	return *this;
}


CStringW& CStringW::operator =(const uint16& data)
{
	std::wstring::operator =(CConvert::toStringW((const uint32)data));
	return *this;
}


CStringW& CStringW::operator =(const int32& data)
{
	std::wstring::operator =(CConvert::toStringW(data));
	return *this;
}


CStringW& CStringW::operator =(const uint32& data)
{
	std::wstring::operator =(CConvert::toStringW(data));
	return *this;
}

CStringW& CStringW::operator =(const int64& data)
{
	std::wstring::operator =(CConvert::toStringW(data));
	return *this;
}

CStringW& CStringW::operator =(const uint64& data)
{
	std::wstring::operator =(CConvert::toStringW(data));
	return *this;
}

CStringW& CStringW::operator =(const float& data)
{
	std::wstring::operator =(CConvert::toStringW(data));
	return *this;
}

CStringW& CStringW::operator =(const double& data)
{
	std::wstring::operator =(CConvert::toStringW(data));
	return *this;
}

CStringW& CStringW::operator <<(const char data[])
{
	CStringA srcText(data);
	std::wstring outText;
	CConvert::utf8ToUnicode(outText, srcText);
	std::wstring::operator +=(outText);
	return *this;
}

CStringW& CStringW::operator <<(const wchar_t data[])
{
	std::wstring::operator +=(data);
	return *this;
}

CStringW& CStringW::operator <<(const CStringA& data)
{
	std::wstring outText;
	CConvert::utf8ToUnicode(outText, data);
	std::wstring::operator +=(outText);
	return *this;
}

CStringW& CStringW::operator <<(const CStringW& data)
{
	std::wstring::operator +=(data);
	return *this;
}

CStringW& CStringW::operator <<(const std::string& data)
{
	std::wstring outText;
	CConvert::utf8ToUnicode(outText, data);
	std::wstring::operator +=(outText);
	return *this;
}

CStringW& CStringW::operator <<(const std::wstring& data)
{
	std::wstring::operator +=(data);
	return *this;
}

CStringW& CStringW::operator <<(const int8& data)
{
	std::wstring::operator +=(CConvert::toStringW((const int32)data));
	return *this;
}

CStringW& CStringW::operator <<(const uint8& data)
{
	std::wstring::operator +=(CConvert::toStringW((const uint32)data));
	return *this;
}

CStringW& CStringW::operator <<(const int16& data)
{
	std::wstring::operator +=(CConvert::toStringW((const int32)data));
	return *this;
}

CStringW& CStringW::operator <<(const uint16& data)
{
	std::wstring::operator +=(CConvert::toStringW((const uint32)data));
	return *this;
}

CStringW& CStringW::operator <<(const int32& data)
{
	std::wstring::operator +=(CConvert::toStringW(data));
	return *this;
}

CStringW& CStringW::operator <<(const uint32& data)
{
	std::wstring::operator +=(CConvert::toStringW(data));
	return *this;
}

CStringW& CStringW::operator <<(const int64& data)
{
	std::wstring::operator +=(CConvert::toStringW(data));
	return *this;
}

CStringW& CStringW::operator <<(const uint64& data)
{
	std::wstring::operator +=(CConvert::toStringW(data));
	return *this;
}

CStringW& CStringW::operator <<(const float& data)
{
	std::wstring::operator +=(CConvert::toStringW(data));
	return *this;
}

CStringW& CStringW::operator <<(const double& data)
{
	std::wstring::operator +=(CConvert::toStringW(data));
	return *this;
}

const CStringW& CStringW::operator >>(CStringA& data) const
{
	CConvert::unicodeToUTF8(data, *this);
	return *this;
}

const CStringW& CStringW::operator >>(CStringW& data) const 
{
	data = *this;
	return *this;
}

const CStringW& CStringW::operator >>(std::string& data) const 
{
	CConvert::unicodeToUTF8(data, *this);
	return *this;
}

const CStringW& CStringW::operator >>(std::wstring& data) const
{
	data = *this;
	return *this;
}

const CStringW& CStringW::operator >>(int8& data) const
{
	data = (int8)CConvert::toInt32(*this);
	return *this;
}

const CStringW& CStringW::operator >>(uint8& data) const
{
	data = (uint8)CConvert::toUint32(*this);
	return *this;
}

const CStringW& CStringW::operator >>(int16& data) const
{
	data = (int16)CConvert::toInt32(*this);
	return *this;
}

const CStringW& CStringW::operator >>(uint16& data) const
{
	data = (uint16)CConvert::toUint32(*this);
	return *this;
}

const CStringW& CStringW::operator >>(int32& data) const
{
	data = CConvert::toInt32(*this);
	return *this;
}

const CStringW& CStringW::operator >>(uint32& data) const
{
	data = CConvert::toUint32(*this);
	return *this;
}

const CStringW& CStringW::operator >>(int64& data) const
{
	data = CConvert::toInt64(*this);
	return *this;
}

const CStringW& CStringW::operator >>(uint64& data) const
{
	data = CConvert::toUint64(*this);
	return *this;
}

const CStringW& CStringW::operator >>(double& data) const
{
	data = CConvert::toDouble(*this);
	return *this;
}

const CStringW& CStringW::operator >>(float& data) const
{
	data = CConvert::toFloat(*this);
	return *this;
}

}//Utility

}//BSLib
