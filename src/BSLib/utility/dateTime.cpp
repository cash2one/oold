//////////////////////////////////////////////////////////////////////
//	created:	2012/06/24
//	filename:	src\BSLib\utility\dateTime.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/dateTime.h>

#define  TIME_TEXT_MAX 256

namespace BSLib
{

namespace Utility
{

CDateTime::CDateTime()
{
	setTime(0);
}

CDateTime::CDateTime(time_t t)
{
	setTime(t);
}

CDateTime::CDateTime(const CDateTime& t)
{
	m_datetTime = t.m_datetTime;
}

CDateTime::CDateTime(int year, int month, int day, int hour, int minute , int second)
{
	setDataTime(year, month, day, hour, minute, second);
}

CDateTime& CDateTime::operator =(const CDateTime& t)
{
	m_datetTime = t.m_datetTime;
	return *this;
}

CDateTime::~CDateTime()
{

}

CDateTime CDateTime::getCurrentTime()
{
	time_t t;
	time(&t);
	return CDateTime(t);
}

void CDateTime::setDataTime(int year, int month, int day, int hour, int minute , int second)
{
	m_datetTime.tm_year = year - 1900;
	m_datetTime.tm_mon = month - 1;
	m_datetTime.tm_mday = day;
	m_datetTime.tm_hour = hour;
	m_datetTime.tm_min = minute;
	m_datetTime.tm_sec = second;
}

bool CDateTime::setDataTime(const std::string& datatime)
{
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;

	int res = sscanf(datatime.c_str(), "%d-%d-%d %d:%d:%d",
		&year,
		&month,
		&day,
		&hour,
		&minute,
		&second);

	if (res >= 0) {
		setDataTime(year, month, day, hour, minute, second);
		return true;
	}
	return false;
}

time_t CDateTime::getSeconds() const
{
	return mktime((tm*)&m_datetTime);;
}

bool CDateTime::operator ==(const CDateTime& rhs) const
{
	return getSeconds() == rhs.getSeconds();
}

bool CDateTime::operator !=(const CDateTime& rhs) const
{
	return getSeconds() != rhs.getSeconds();
}

bool CDateTime::operator <(const CDateTime& rhs) const
{
	return getSeconds() < rhs.getSeconds();
}

bool CDateTime::operator <=(const CDateTime& rhs) const
{
	return getSeconds() <= rhs.getSeconds();
}

bool CDateTime::operator >(const CDateTime& rhs) const
{
	return getSeconds() > rhs.getSeconds();
}
bool CDateTime::operator >=(const CDateTime& rhs) const
{
	return getSeconds() >= rhs.getSeconds();
}

CDateTime CDateTime::operator +(const time_t& rhs) const
{
	return CDateTime(getSeconds() + rhs);
}

CDateTime CDateTime::operator -(const time_t& rhs) const
{
	time_t myTime_t = getSeconds();
	if (myTime_t >= rhs) {
		return CDateTime(myTime_t - rhs);
	}
	return CDateTime(0);
}

CDateTime CDateTime::operator -(const CDateTime& other) const
{
	time_t myTime_t = getSeconds();
	time_t otherTime_t = other.getSeconds();
	if (myTime_t >= otherTime_t) {
		return CDateTime(myTime_t - otherTime_t);
	}
	return CDateTime(0);
}

std::string CDateTime::toString() const
{
	char szTime[TIME_TEXT_MAX+1] = {0};
	int len = TIME_TEXT_MAX;

#ifdef WIN32

	strftime(szTime, len, "%Y-%m-%d %H:%M:%S", &m_datetTime);

#else

	strftime(szTime, len, "%F %X", &m_datetTime);

#endif

	return std::string(szTime);
}

std::string CDateTime::toString(const char* pszFormat) const
{
	char szTime[TIME_TEXT_MAX+1] = {0};
	int len = TIME_TEXT_MAX;

#ifdef WIN32

	strftime(szTime, len, pszFormat, &m_datetTime);

#else

	strftime(szTime, len, pszFormat, &m_datetTime);

#endif

	return std::string(szTime);
}

void CDateTime::setTime(time_t timSec)
{
#ifdef WIN32
	
	localtime_s(&m_datetTime, &timSec);

#else

	localtime_r(&timSec, &m_datetTime);

#endif
}

/////////////////////////////////////////////////////////////////////////////

void CRealTime::now()
{
#ifdef WIN32

	FILETIME ft;
	SYSTEMTIME st;
	ULARGE_INTEGER rt;

	rt.QuadPart = 0LL;

	::GetSystemTime(&st);               // gets current time
	::SystemTimeToFileTime(&st, &ft);  // converts to file time format

	rt.HighPart = ft.dwHighDateTime;
	rt.LowPart = ft.dwLowDateTime;

	m_milliseconds = (int64)rt.QuadPart / 10000;

#else

	int64 rt = 0LL;
	timespec currTime;
	clock_gettime(CLOCK_REALTIME, &currTime);
	rt = currTime.tv_sec * 1000LL + currTime.tv_nsec / 1000000LL;
	m_milliseconds = rt;

#endif
}

/////////////////////////////////////////////////////////////////////////////
#ifdef WIN32
	int64 CSurveyTimer::m_frequency = 0;
#endif

CSurveyTimer::CSurveyTimer()
{
#ifdef WIN32

	if (m_frequency == 0){
		LARGE_INTEGER integer;
		QueryPerformanceFrequency(&integer);
		m_frequency = integer.QuadPart;
	}
	QueryPerformanceCounter(&m_lastTime);

#else

	clock_gettime(CLOCK_REALTIME, &m_lastTime);

#endif
}

void CSurveyTimer::reset()
{
#ifdef WIN32
	QueryPerformanceCounter(&m_lastTime);
#else
	clock_gettime(CLOCK_REALTIME, &m_lastTime);
#endif
}

int64 CSurveyTimer::seconds()
{
	return microseconds() / 1000000;
}

int64 CSurveyTimer::milliseconds()
{
	return microseconds() / 1000;
}

int64 CSurveyTimer::microseconds()
{
	int64 secRes = 0;

#ifdef WIN32

	LARGE_INTEGER currInteger;
	QueryPerformanceCounter(&currInteger);
	secRes = (int64)((currInteger.QuadPart - m_lastTime.QuadPart) * 1000000.0) / m_frequency;

#else

	timespec currTime;
	clock_gettime(CLOCK_REALTIME, &currTime);

	int64 begin = m_lastTime.tv_sec * 1000000L + m_lastTime.tv_nsec / 1000L;
	int64 end = currTime.tv_sec * 1000000L + currTime.tv_nsec / 1000L;
	secRes = end - begin;

#endif

	return secRes;
}

}//Utility

}//BSLib
