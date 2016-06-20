#include <GSLib/rankSystem/CN/dateTimer.h>
#include <time.h>

namespace GSLib
{
namespace RankSystem
{
namespace CN
{

bool CDateTimer::addTimer(STimeHandle a_handle, CDateTimerCallback* a_cb)
{	
	if(a_handle.m_day > 6)
		return false;
	if( a_handle.m_hour > 23)
		return false;
	if( a_handle.m_minute > 59)
		return false;
	if( NULL == a_cb)
		return false;

	m_container.push_back(std::make_pair(a_handle, a_cb));
	m_refreshTime.push_back(0);
	return true;
}

void CDateTimer::update()
{
	time_t t;
	time(&t);

	struct tm *gm = localtime(&t);
	std::vector< std::pair<STimeHandle, CDateTimerCallback *> >::iterator it = m_container.begin();
	std::vector<BSLib::uint64>::iterator timeIt = m_refreshTime.begin();
	for(; it != m_container.end() && timeIt != m_refreshTime.end(); ++it, ++timeIt)
	{
		std::pair<STimeHandle, CDateTimerCallback *>& cur = *it;
		STimeHandle& first = cur.first;
		if( EDATETIMER_DAILY == first.m_type)
		{
			if(gm->tm_hour != (int)first.m_hour || gm->tm_min != (int)first.m_minute)
				continue;
			
			BSLib::uint64 now = t;
			if( now - *timeIt <= 59)
				continue;

			*timeIt = now;
			cur.second->cb(first.m_id);
		}
		else if( EDATETIMER_WEEKLY == first.m_type)
		{
			if(gm->tm_wday != (int)first.m_day || gm->tm_hour != (int)first.m_hour || gm->tm_min != (int)first.m_minute)
				continue;

			BSLib::uint64 now = t;
			if( now - *timeIt <= 59)
				continue;

			*timeIt = now;
			cur.second->cb(first.m_id);
		}
	}
}

} // CN
} // RankSystem
} // GSLib
