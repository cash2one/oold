//////////////////////////////////////////////////////////////////////
//	created:	2012/06/24
//	filename: 	BSLib\utility\dateTime.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_DATETIME_H__
#define __BSLIB_UTILITY_DATETIME_H__

#include <time.h>
#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CDateTime
{
public:
	CDateTime();
	CDateTime(time_t t);
	CDateTime(const CDateTime& t);
	CDateTime(int year, int month = 1, int day = 1, int hour = 0, int minute = 0, int second = 0);
	CDateTime& operator=(const CDateTime& t);
	~CDateTime();

	static CDateTime getCurrentTime();

	void setDataTime(int year, int month, int day, int hour, int minute, int second);
	
	//设置固定格式 %Y-%m-%d %H:%M:%S
	bool setDataTime(const std::string& datatime);

	uint32 getYear() const { return m_datetTime.tm_year + 1900; }
	uint32 getMonth() const { return m_datetTime.tm_mon + 1; }
	uint32 getDay() const { return m_datetTime.tm_mday; }
	uint32 getHour() const { return m_datetTime.tm_hour; }
	uint32 getMinute() const { return m_datetTime.tm_min; }
	uint32 getSecond() const { return m_datetTime.tm_sec; }

	time_t getSeconds() const;
	
	bool operator ==(const CDateTime& rhs) const;
	bool operator !=(const CDateTime& rhs) const;
	bool operator <(const CDateTime& rhs) const;
	bool operator <=(const CDateTime& rhs) const;
	bool operator >(const CDateTime& rhs) const;
	bool operator >=(const CDateTime& rhs) const;

	CDateTime operator + (const time_t& rhs) const;
	CDateTime operator - (const time_t& rhs) const;
	CDateTime operator - (const CDateTime& other) const;

	std::string toString() const;
	std::string toString(const char* pszFormat) const;
	
	void setTime(time_t timSec);

private:
	tm m_datetTime;
};


//////////////////////////////////////////////////////////////////////////
/// @brief 本地真实时间,精确到毫秒
//////////////////////////////////////////////////////////////////////////
class BSLIB_UTILITY_API CRealTime
{
public:
	CRealTime(int delay = 0)
	{
		now();
		addDelay(delay);
	}

	CRealTime(const CRealTime& rt)
	{
		m_milliseconds = rt.m_milliseconds;
	}

	/// @brief 获取当前的毫秒
	/// @return void
	void now();

	/// @brief 当前的秒
	/// @return int64
	int64 seconds() { return m_milliseconds / 1000; }

	/// @brief 当前的毫秒
	/// @return int64
	int64 milliseconds() { return m_milliseconds; }

	/// @brief 设置毫秒
	/// @int64 ms
	void setMilliSeconds(int64 ms) { m_milliseconds = ms; }

	void addDelay(int delay) { m_milliseconds += delay; }

	CRealTime& operator =(const CRealTime& rt) { m_milliseconds = rt.m_milliseconds; return *this; }
	CRealTime& operator +(const CRealTime& rt) { m_milliseconds += rt.m_milliseconds; return *this; }
	CRealTime& operator -(const CRealTime& rt) { m_milliseconds -= rt.m_milliseconds; return *this; }

	bool operator >(const CRealTime& rt) { return m_milliseconds > rt.m_milliseconds; }
	bool operator <(const CRealTime& rt) { return m_milliseconds < rt.m_milliseconds; }
	bool operator >=(const CRealTime& rt) { return m_milliseconds >= rt.m_milliseconds; }
	bool operator <=(const CRealTime& rt) { return m_milliseconds <= rt.m_milliseconds; }
	bool operator ==(const CRealTime& rt) { return m_milliseconds == rt.m_milliseconds; }

private:
	int64 m_milliseconds;
};

//////////////////////////////////////////////////////////////////////////
/// @brief 延时定时器，轻量级的定时器，主动去判断是否超时
///     CRealTime realTime;
///     CDelayTimer delayTime(300);
///
///		realTime.now();
///
///     if(dalayTime(realTime)) {
///        //to do;
///     }
//////////////////////////////////////////////////////////////////////////
class BSLIB_UTILITY_API CDelayTimer
{
public:
	CDelayTimer() : m_delay(0), m_realTime(0) {}
	CDelayTimer(int delay): m_delay(delay), m_realTime(delay) {}
	CDelayTimer(int delay, const CRealTime& rt): m_delay(delay), m_realTime(rt) { m_realTime.addDelay(delay); }

	/// @brief 重置定时器
	/// @return void
	/// @param delay 延迟时间
	/// @param ct 下一次超时的时间
	void reset(int delay, const CRealTime& ct) 
	{
		m_delay = delay;
		m_realTime = ct;
		m_realTime.addDelay(delay);
	}

	/// @brief 更新下次超时时间
	/// @return void
	/// @param ct ct + m_delay为下次超时时间
	void next(const CRealTime& ct)
	{
		m_realTime = ct;
		m_realTime.addDelay(m_delay);
	}

	/// @brief 判断是否超时
	/// @return bool
	/// @param ct 当前时间
	bool operator ()(const CRealTime& ct)
	{
		if (m_realTime <= ct){
			m_realTime = ct;
			m_realTime.addDelay(m_delay);
			return true;
		}
		return false;
	}

	/// @brief 判断是否超时
	/// @return bool
	/// @param ct 当前时间
	/// @param delay 如果返回true, 则设置下次延迟间隔
	bool operator ()(const CRealTime& ct, int delay)
	{
		if (m_realTime <= ct){
			m_realTime = ct;
			m_realTime.addDelay(delay);
			return true;
		}
		return false;
	}

private:
	int m_delay;
	//下次超时时间
	CRealTime m_realTime;
};

//////////////////////////////////////////////////////////////////////////
/// @brief 性能测试，计时器
//////////////////////////////////////////////////////////////////////////
class BSLIB_UTILITY_API CSurveyTimer
{
public:
	CSurveyTimer();

	/// @brief重置计时器
	/// @return void
	void reset();
	
	/// @brief 上次重置到现在经过的秒数
	/// @return BSLib::int64
	int64 seconds();
	
	//毫秒
	int64 milliseconds();
	
	//微妙
	int64 microseconds();

private:
#ifdef WIN32
	LARGE_INTEGER m_lastTime;
	static int64 m_frequency;
#else
	timespec m_lastTime;
#endif
};

}//Utility 

}//BSLib

#endif//__BSLIB_UTILITY_DATETIME_H__
