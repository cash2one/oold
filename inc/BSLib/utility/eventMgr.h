#ifndef __BSLIB_UTILITY_EVENTMGR_H__
#define __BSLIB_UTILITY_EVENTMGR_H__

#include <BSLib/utility/functionEvent.h>
#include <BSLib/utility/ptrQueue.h>
#include <BSLib/utility/stream.h>

namespace BSLib
{

namespace Utility
{

typedef BSLib::int32 EventID;
const EventID INVALID_EVENTID = -1;

class CFunctionEventStream;

//////////////////////////////////////////////////////////////////////////
/// @brief 不可以在多线程中使用
//////////////////////////////////////////////////////////////////////////
class BSLIB_UTILITY_API CEventMgr
{
public:
	CEventMgr();
	~CEventMgr();

	void init(const EventID& a_maxEventID);
	void clear();

	void updateEvent();
	void sendEvent(const EventID& a_eventID, BSLib::int8* a_data, BSLib::uint32 a_dataSize);
	void sendEvent(const EventID& a_eventID, BSLib::Utility::CStream& a_stream);

	BSLib::Utility::CFunctionEventHandle registerEvent(EventID& a_eventID, void(*a_fun)(EventID&, BSLib::Utility::CStream&));
	BSLib::Utility::CFunctionEventHandle registerEvent(EventID& a_eventID, BSLib::Utility::CFunction<void, EventID&, BSLib::Utility::CStream&>& a_fun);

	template<class NAME>
	BSLib::Utility::CFunctionEventHandle registerEvent(EventID& a_eventID, void(NAME::*a_fun)(EventID&, BSLib::Utility::CStream&), NAME* a_object)
	{
		BSLib::Utility::CFunctionObject<void, NAME, EventID&, BSLib::Utility::CStream&> objFun(a_fun, a_object);
		return registerEvent(a_eventID, objFun);
	}

	void unregisterEvent(EventID& a_eventID, BSLib::Utility::CFunctionEventHandle& a_handle);

private:
	BSLib::Utility::CStream m_streamEventMsg;
	BSLib::Utility::CStream m_streamData;
	std::vector< CFunctionEventStream* > m_functionEventList;
};

}//

}//

#endif//__BSLIB_UTILITY_EVENTMGR_H__
