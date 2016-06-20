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
	
	//���ù̶���ʽ %Y-%m-%d %H:%M:%S
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
/// @brief ������ʵʱ��,��ȷ������
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

	/// @brief ��ȡ��ǰ�ĺ���
	/// @return void
	void now();

	/// @brief ��ǰ����
	/// @return int64
	int64 seconds() { return m_milliseconds / 1000; }

	/// @brief ��ǰ�ĺ���
	/// @return int64
	int64 milliseconds() { return m_milliseconds; }

	/// @brief ���ú���
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
/// @brief ��ʱ��ʱ�����������Ķ�ʱ��������ȥ�ж��Ƿ�ʱ
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

	/// @brief ���ö�ʱ��
	/// @return void
	/// @param delay �ӳ�ʱ��
	/// @param ct ��һ�γ�ʱ��ʱ��
	void reset(int delay, const CRealTime& ct) 
	{
		m_delay = delay;
		m_realTime = ct;
		m_realTime.addDelay(delay);
	}

	/// @brief �����´γ�ʱʱ��
	/// @return void
	/// @param ct ct + m_delayΪ�´γ�ʱʱ��
	void next(const CRealTime& ct)
	{
		m_realTime = ct;
		m_realTime.addDelay(m_delay);
	}

	/// @brief �ж��Ƿ�ʱ
	/// @return bool
	/// @param ct ��ǰʱ��
	bool operator ()(const CRealTime& ct)
	{
		if (m_realTime <= ct){
			m_realTime = ct;
			m_realTime.addDelay(m_delay);
			return true;
		}
		return false;
	}

	/// @brief �ж��Ƿ�ʱ
	/// @return bool
	/// @param ct ��ǰʱ��
	/// @param delay �������true, �������´��ӳټ��
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
	//�´γ�ʱʱ��
	CRealTime m_realTime;
};

//////////////////////////////////////////////////////////////////////////
/// @brief ���ܲ��ԣ���ʱ��
//////////////////////////////////////////////////////////////////////////
class BSLIB_UTILITY_API CSurveyTimer
{
public:
	CSurveyTimer();

	/// @brief���ü�ʱ��
	/// @return void
	void reset();
	
	/// @brief �ϴ����õ����ھ���������
	/// @return BSLib::int64
	int64 seconds();
	
	//����
	int64 milliseconds();
	
	//΢��
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
