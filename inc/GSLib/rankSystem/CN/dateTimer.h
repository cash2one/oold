#ifndef dateTimer_h__
#define dateTimer_h__
#include <GSLib/baseDef.h>

namespace GSLib
{
namespace RankSystem
{
namespace CN
{

class CDateTimerCallback
{
public:
	virtual void  cb(BSLib::uint32 a_id)	= 0;
};

enum EDateTimerType
{
	EDATETIMER_DAILY,		// 每日的
	EDATETIMER_WEEKLY,		// 每周的
};

struct STimeHandle
{	
	STimeHandle(EDateTimerType a_type, BSLib::uint32 a_id, BSLib::uint32 a_day, BSLib::uint32 a_hour, BSLib::uint32 a_minute)
		:m_type(a_type),m_id(a_id), m_day(a_day), m_hour(a_hour), m_minute(a_minute) {}
	STimeHandle()
		:m_type(EDATETIMER_DAILY), m_id(0), m_day(0), m_hour(0), m_minute(0){}
	EDateTimerType m_type;
	BSLib::uint32 m_id;
	BSLib::uint32 m_day;
	BSLib::uint32 m_hour;
	BSLib::uint32 m_minute;
};


class CDateTimer
{
public:
	bool  addTimer(STimeHandle a_handle, CDateTimerCallback* a_cb);
	void  update();

private:
	std::vector< std::pair<STimeHandle, CDateTimerCallback *> > m_container;
	std::vector<BSLib::uint64> m_refreshTime;
};

} // CN
} // RankSystem
} // GSLib




#endif // dateTimer_h__
