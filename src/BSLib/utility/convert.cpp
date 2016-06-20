//////////////////////////////////////////////////////////////////////
//	created:	2012/07/08
//	filename:	src\BSLib\utility\convert.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef _WIN32

#include <stdlib.h>
#include <iconv.h>

#endif

#include <BSLib/utility/convert.h>

#define BSLIB_UTILITY_DATA_MAX 65
#define BSLIB_UTILITY_BUFF_MAX 1024

namespace BSLib
{

namespace Utility
{

#ifndef _WIN32

	int m2w(const char* from, const char* to, wchar_t* outBuff, int buffSize, const char* text, int textSize)
	{
		iconv_t h = iconv_open(to, from);
		if (h == (iconv_t)(-1)) {
			return -1;
		}

		char* pin = (char*)text;
		char* pout = (char*)outBuff;
		size_t inSize = textSize;
		size_t outSize = buffSize * sizeof(wchar_t);

		memset(pout, 0, outSize);

		size_t outLen = outSize;
		if (iconv(h, &pin, &inSize, &pout, &outLen) < 0) {
			iconv_close(h);
			return -1;
		}

		iconv_close(h);

		return (int)((outSize - outLen + sizeof(wchar_t) - 1) / sizeof(wchar_t));
	}

	int w2m(const char* from, const char* to, char* outBuff, int buffSize, const wchar_t* text, int textSize)
	{
		iconv_t h = iconv_open(to, from);

		if (h == (iconv_t)(-1)) {
			return -1;
		}

		char* pin = (char*)text;
		char* pout = outBuff;
		size_t inSize = textSize * sizeof(wchar_t);
		size_t outSize = buffSize;

		memset(pout, 0, outSize);

		size_t outLen = outSize;
		if (iconv(h, &pin, &inSize, &pout, &outLen) < 0) {
			iconv_close(h);
			return -1;
		}

		iconv_close(h);

		return (int)(outSize - outLen);
	}

	int strm2w(const char* from, const char* to, std::wstring& outBuff, const std::string& text)
	{
		iconv_t h = iconv_open(to, from);
		if (h == (iconv_t)(-1)) {
			return -1;
		}

		wchar_t buff[BSLIB_UTILITY_BUFF_MAX + 1] = {0};

		memset(buff, 0, sizeof(buff));
		char* pout = (char*)buff;
		size_t outSize = BSLIB_UTILITY_BUFF_MAX * sizeof(wchar_t);

		char* pin = (char*)text.c_str();
		size_t inSize = text.size();

		size_t inLen = inSize;
		size_t outLen = outSize;

		while(inLen > 0){
			if (iconv(h, &pin, &inLen, &pout, &outLen) < 0) {
				return -1;
			}
			size_t len = (outSize - outLen + sizeof(wchar_t) - 1)/sizeof(wchar_t);
			if (len <= 0){
				return -1;
			}
			outBuff.append(buff, len) ;

			memset(buff, 0, sizeof(buff));
			pout = (char*)buff;

			outLen = outSize;
		}

		iconv_close(h);

		return (int)outBuff.size();
	}

	int strw2m(const char* from, const char* to, std::string& outBuff, const std::wstring& text)
	{
		iconv_t h = iconv_open(to, from);

		if (h == (iconv_t)(-1)) {
			return -1;
		}

		char buff[BSLIB_UTILITY_BUFF_MAX + 1] = {0};

		memset(buff, 0, sizeof(buff));
		char* pout = (char*)buff;
		size_t outSize = BSLIB_UTILITY_BUFF_MAX;

		char* pin = (char*)text.c_str();
		size_t inSize = text.size() * sizeof(wchar_t);

		size_t inLen = inSize;
		size_t outLen = outSize;

		while(inLen > 0){
			if (iconv(h, &pin, &inLen, &pout, &outLen) < 0) {
				return -1;
			}
			size_t len = outSize - outLen;
			if (len <= 0){
				return -1;
			}
			outBuff.append(buff, len) ;

			memset(buff, 0, sizeof(buff));
			pout = (char*)buff;

			outLen = outSize;
		}

		iconv_close(h);

		return (int)outBuff.size();
	}

#endif

int CConvert::utf8ToUnicode(wchar_t* outBuff, int buffSize, const char* text, int textSize)
{
#ifdef _WIN32

	return ::MultiByteToWideChar(CP_UTF8, NULL, text, textSize, outBuff, buffSize);

#else

	if (sizeof(wchar_t) == 4) {
		return m2w("UTF-8", "UCS-4-INTERNAL", outBuff, buffSize, text, textSize);
	} else {
		return m2w("UTF-8", "UCS-2-INTERNAL", outBuff, buffSize, text, textSize);
	}

#endif
}

int CConvert::utf8ToUnicode(std::wstring& outBuff, const std::string& text)
{
#ifdef _WIN32

	outBuff.clear();
	int needSize = (int)::MultiByteToWideChar(CP_UTF8, 0, text.c_str(), (int)text.size(), NULL, 0);
	if (needSize <= 0) {
		return 0;
	}
	outBuff.resize(needSize, 0);
	return (int)::MultiByteToWideChar(CP_UTF8, NULL, text.c_str(), (int)text.size(), (wchar_t*)outBuff.c_str(), (int)outBuff.size());;

#else

	if (sizeof(wchar_t) == 4) {
		return strm2w("UTF-8", "UCS-4-INTERNAL", outBuff, text);
	} else {
		return strm2w("UTF-8", "UCS-2-INTERNAL", outBuff, text);
	}

#endif
}

int CConvert::unicodeToUTF8(char* outBuff, int buffSize, const wchar_t* text, int textSize)
{
#ifdef _WIN32

	return ::WideCharToMultiByte(CP_UTF8, NULL, text, textSize, outBuff, buffSize, NULL, NULL);

#else

	if (sizeof(wchar_t) == 4) {
		return w2m("UCS-4-INTERNAL", "UTF-8", outBuff, buffSize, text, textSize);
	} else {
		return w2m("UCS-2-INTERNAL", "UTF-8", outBuff, buffSize, text, textSize);
	}

#endif
}

int CConvert::unicodeToUTF8(std::string& outBuff, const std::wstring& text)
{
#ifdef _WIN32

	int needSize = ::WideCharToMultiByte(CP_UTF8, NULL, text.c_str(), (int)text.size(), NULL, NULL, NULL, NULL);
	if (needSize <= 0) {
		return 0;
	}
	outBuff.resize(needSize, 0);
	return ::WideCharToMultiByte(CP_UTF8, NULL, text.c_str(), (int)text.size(), (char*)outBuff.c_str(), (int)outBuff.size(), NULL, NULL);

#else

	if (sizeof(wchar_t) == 4) {
		return strw2m("UCS-4-INTERNAL", "UTF-8", outBuff, text);
	} else {
		return strw2m("UCS-2-INTERNAL", "UTF-8", outBuff, text);
	}

#endif
}

int CConvert::unicodeToGB2312(char* outBuff, int buffSize, const wchar_t* text, int textSize)
{
#ifdef _WIN32

	return ::WideCharToMultiByte(CP_ACP, NULL, text, textSize, outBuff, buffSize, NULL, NULL);

#else

	if (sizeof(wchar_t) == 4) {
		return w2m("UCS-4-INTERNAL", "GBK", outBuff, buffSize, text, textSize);
	} else {
		return w2m("UCS-2-INTERNAL", "GBK", outBuff, buffSize, text, textSize);
	}

#endif
}

int CConvert::unicodeToGB2312(std::string& outBuff, const std::wstring& text)
{
#ifdef _WIN32

	int needSize = ::WideCharToMultiByte(CP_ACP, NULL, text.c_str(), (int)text.size(), NULL, NULL, NULL, NULL);
	if (needSize <= 0) {
		return 0;
	}
	outBuff.resize(needSize, 0);
	return ::WideCharToMultiByte(CP_ACP, NULL, text.c_str(), (int)text.size(), (char*)outBuff.c_str(), (int)outBuff.size(), NULL, NULL);

#else

	if (sizeof(wchar_t) == 4) {
		return strw2m("UCS-4-INTERNAL", "GBK", outBuff, text);
	} else {
		return strw2m("UCS-2-INTERNAL", "GBK", outBuff, text);
	}

#endif
}

int CConvert::gb2312ToUnicode(wchar_t* outBuff, int buffSize, const char* text, int textSize)
{
#ifdef _WIN32

	return ::MultiByteToWideChar(CP_ACP, NULL, text, textSize, outBuff, buffSize);

#else

	if (sizeof(wchar_t) == 4) {
		return m2w("GBK", "UCS-4-INTERNAL", outBuff, buffSize, text, textSize);
	} else {
		return m2w("GBK", "UCS-2-INTERNAL", outBuff, buffSize, text, textSize);
	}

#endif
}

int CConvert::gb2312ToUnicode(std::wstring& outBuff, const std::string& text)
{
#ifdef _WIN32

	int needSize = ::MultiByteToWideChar(CP_ACP, NULL, text.c_str(), (int)text.size(), NULL, NULL);
	if (needSize <= 0) {
		return 0;
	}
	outBuff.resize(needSize, 0);
	return ::MultiByteToWideChar(CP_ACP, NULL, text.c_str(), (int)text.size(), (wchar_t*)outBuff.c_str(), (int)outBuff.size());;

#else

	if (sizeof(wchar_t) == 4) {
		return strm2w("GBK", "UCS-4-INTERNAL", outBuff, text);
	} else {
		return strm2w("GBK", "UCS-2-INTERNAL", outBuff, text);
	}


#endif
}

int CConvert::gb2312ToUTF8(char* outBuff, int buffSize, const char* text, int textSize)
{
	std::wstring unicode;
	std::string  txt;
	for (int i=0; text[i] && i < textSize; ++i) {
		txt.push_back(text[i]);
	}
	if (gb2312ToUnicode(unicode, txt) <= 0) {
		return 0;;
	}
	return unicodeToUTF8(outBuff, buffSize, unicode.c_str(), (int)unicode.size());
}

int CConvert::gb2312ToUTF8(std::string& outBuff, const std::string& text)
{
	std::wstring unicode;
	if (gb2312ToUnicode(unicode, text) <= 0) {
		return 0;;
	}
	return unicodeToUTF8(outBuff, unicode);
}

int CConvert::utf8ToGB2312(char* outBuff, int buffSize, const char* text, int textSize)
{
	std::wstring unicode;
	std::string  txt;
	for (int i=0; text[i] && i < textSize; ++i) {
		txt.push_back(text[i]);
	}
	if (utf8ToUnicode(unicode, txt) <= 0) {
		return 0;;
	}
	return unicodeToGB2312(outBuff, buffSize, unicode.c_str(), (int)unicode.size());
}

int CConvert::utf8ToGB2312(std::string& outBuff, const std::string& text)
{
	std::wstring unicode;
	if (utf8ToUnicode(unicode, text) <= 0) {
		return 0;;
	}
	return unicodeToGB2312(outBuff, unicode);
}

std::string CConvert::toStringA(const int32 n)
{
	char buffer[BSLIB_UTILITY_DATA_MAX] = {0};
	
#ifdef _WIN32

	_i64toa_s(n, buffer, BSLIB_UTILITY_DATA_MAX, 10);

#else

	snprintf(buffer, BSLIB_UTILITY_DATA_MAX, "%d", n);

#endif

	return std::string(buffer);
}

std::string CConvert::toStringA(const uint32 n)
{
	char buffer[BSLIB_UTILITY_DATA_MAX] = {0};
	
#ifdef _WIN32

	_ui64toa_s(n, buffer, BSLIB_UTILITY_DATA_MAX, 10);

#else

	snprintf(buffer, BSLIB_UTILITY_DATA_MAX, "%u", n);

#endif

	return std::string(buffer);
}

std::string CConvert::toStringA(const int64 n)
{
	char buffer[BSLIB_UTILITY_DATA_MAX] = {0};
	
#ifdef _WIN32

	_i64toa_s(n, buffer, BSLIB_UTILITY_DATA_MAX, 10);

#else

	snprintf(buffer, BSLIB_UTILITY_DATA_MAX, "%lld", n);

#endif

	return std::string(buffer);
}

std::string CConvert::toStringA(const uint64 n)
{
	char buffer[BSLIB_UTILITY_DATA_MAX] = {0};
	
#ifdef _WIN32

	_ui64toa_s(n, buffer, BSLIB_UTILITY_DATA_MAX, 10);

#else

	snprintf(buffer, BSLIB_UTILITY_DATA_MAX, "%llu", n);

#endif

	return std::string(buffer);
}

std::string CConvert::toStringA(const float f)
{
	char buffer[BSLIB_UTILITY_DATA_MAX] = {0};

#ifdef _WIN32

	sprintf_s(buffer, BSLIB_UTILITY_DATA_MAX, "%g", f);

#else

	snprintf(buffer, BSLIB_UTILITY_DATA_MAX, "%g", f);

#endif

	return std::string(buffer);
}

std::string CConvert::toStringA(const double d)
{
	char buffer[BSLIB_UTILITY_DATA_MAX] = {0};
	
#ifdef _WIN32

	sprintf_s(buffer, BSLIB_UTILITY_DATA_MAX, "%g", d);

#else

	snprintf(buffer, BSLIB_UTILITY_DATA_MAX, "%g", d);

#endif

	return std::string(buffer);
}

std::wstring CConvert::toStringW(const int32 n)
{
	wchar_t buffer[BSLIB_UTILITY_DATA_MAX] = {0};
	
#ifdef _WIN32

	_i64tow_s(n, buffer, BSLIB_UTILITY_DATA_MAX, 10);

#else

	swprintf(buffer, BSLIB_UTILITY_DATA_MAX, L"%ld", n);

#endif

	return std::wstring(buffer);
}

std::wstring CConvert::toStringW(const uint32 n)
{
	wchar_t buffer[BSLIB_UTILITY_DATA_MAX] = {0};
	
#ifdef _WIN32

	_ui64tow_s(n, buffer, BSLIB_UTILITY_DATA_MAX, 10);

#else

	swprintf(buffer, BSLIB_UTILITY_DATA_MAX, L"%lu", n);

#endif

	return std::wstring(buffer);
}

std::wstring CConvert::toStringW(const int64 n)
{
	wchar_t buffer[BSLIB_UTILITY_DATA_MAX] = {0};
	
#ifdef _WIN32

	_i64tow_s(n, buffer, BSLIB_UTILITY_DATA_MAX, 10);

#else

	swprintf(buffer, BSLIB_UTILITY_DATA_MAX, L"%lld", n);

#endif

	return std::wstring(buffer);
}

std::wstring CConvert::toStringW(const uint64 n)
{
	wchar_t buffer[BSLIB_UTILITY_DATA_MAX] = {0};
	
#ifdef _WIN32

	_ui64tow_s(n, buffer, BSLIB_UTILITY_DATA_MAX, 10);

#else

	swprintf(buffer, BSLIB_UTILITY_DATA_MAX, L"%llu", n);

#endif

	return std::wstring(buffer);
}

std::wstring CConvert::toStringW(const float f)
{
	wchar_t buffer[BSLIB_UTILITY_DATA_MAX] = {0};
	
#ifdef _WIN32

	swprintf_s(buffer, BSLIB_UTILITY_DATA_MAX, L"%g", f);

#else

	swprintf(buffer, BSLIB_UTILITY_DATA_MAX, L"%g", f);

#endif

	return std::wstring(buffer);
}

std::wstring CConvert::toStringW(const double d)
{
	wchar_t buffer[BSLIB_UTILITY_DATA_MAX] = {0};
	
#ifdef _WIN32

	swprintf_s(buffer, BSLIB_UTILITY_DATA_MAX, L"%g", d);

#else

	swprintf(buffer, BSLIB_UTILITY_DATA_MAX, L"%g", d);

#endif

	return std::wstring(buffer);
}

int32 CConvert::toInt32(const std::string& str)
{
#ifdef _WIN32

	return (int32)_strtoi64(str.c_str(), NULL, 10);

#else

	return (int32)strtol(str.c_str(), NULL, 10);

#endif
}

uint32 CConvert::toUint32(const std::string& str)
{
#ifdef _WIN32

	return (uint32)_strtoui64(str.c_str(), NULL, 10);

#else

	return (uint32)strtoul(str.c_str(), NULL, 10);

#endif
}

int64 CConvert::toInt64(const std::string& str)
{
#ifdef _WIN32

	return (int64)_strtoi64(str.c_str(), NULL, 10);

#else

	return strtoll(str.c_str(), NULL, 10);

#endif
}

uint64 CConvert::toUint64(const std::string& str)
{
#ifdef _WIN32

	return (uint64)_strtoui64(str.c_str(), NULL, 10);

#else

	return strtoull(str.c_str(), NULL, 10);

#endif
}

float CConvert::toFloat(const std::string& str)
{
	return (float)atof(str.c_str());
}

double CConvert::toDouble(const std::string& str)
{
	return atof(str.c_str());
}

int32  CConvert::toInt32(const std::wstring& str)
{
#ifdef _WIN32

	return (int32)_wcstoi64(str.c_str(), NULL, 10);

#else

	return (int32)wcstol(str.c_str(), NULL, 10);

#endif
}

uint32 CConvert::toUint32(const std::wstring& str)
{
#ifdef _WIN32

	return (uint32)_wcstoui64(str.c_str(), NULL, 10);

#else

	return (int32)wcstoul(str.c_str(), NULL, 10);

#endif
}

int64  CConvert::toInt64(const std::wstring& str)
{
#ifdef _WIN32

	return (int64)_wcstoi64(str.c_str(), NULL, 10);

#else

	return wcstoll(str.c_str(), NULL, 10);

#endif
}

uint64 CConvert::toUint64(const std::wstring& str)
{
#ifdef _WIN32

	return (uint64)_wcstoui64(str.c_str(), NULL, 10);

#else

	return wcstoull(str.c_str(), NULL, 10);

#endif
}

float  CConvert::toFloat(const std::wstring& str)
{
#ifdef _WIN32

	return (float)_wtof(str.c_str());

#else

	return wcstof(str.c_str(), NULL);

#endif
}

double CConvert::toDouble(const std::wstring& str)
{
#ifdef _WIN32

	return _wtof(str.c_str());

#else

	return wcstod(str.c_str(), NULL);

#endif
	
}

}//Utility

}//BSLib
