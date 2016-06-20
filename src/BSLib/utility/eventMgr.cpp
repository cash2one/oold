#include <BSLib/utility/tracer.h>
#include <BSLib/utility/eventMgr.h>

namespace BSLib
{

namespace Utility
{
//////////////////////////////////////////////////////////////////////////
class CFunctionEventStream: public BSLib::Utility::CFunctionEvent<void, EventID&, BSLib::Utility::CStream&>
{
public:
	virtual void operator()(EventID& a_eventID, BSLib::Utility::CStream& a_stream)
	{
		BSLib::Utility::CFunctionEvent<void, EventID&, BSLib::Utility::CStream&>::_updateFunctionEvent();
		
		if (m_functionList.size() <= 1) {
			BSLib::Utility::CFunctionEvent<void, EventID&, BSLib::Utility::CStream&>::CFunctionEventItemListIter it = m_functionList.begin();
			while (it != m_functionList.end()) {
				CFunctionEventItem* item = *it;
				if (item == NULL) {
					it = m_functionList.erase(it);
					continue;
				}
				if (item->m_isValid == false) {
					it = m_functionList.erase(it);
					BSLIB_SAFE_DELETE(item);
					continue;
				}
				BSLib::Utility::CFunction<void, EventID&, BSLib::Utility::CStream& >* fun = item->m_fun;
				if (fun == NULL) {
					++it;
					continue;
				}
				(*fun)(a_eventID, a_stream);
				++it;
			}
			return;
		} 
		BSLib::Utility::CFunctionEvent<void, EventID&, BSLib::Utility::CStream&>::CFunctionEventItemListIter it = m_functionList.begin();
		while (it != m_functionList.end()) {
			CFunctionEventItem* item = *it;
			if (item == NULL) {
				it = m_functionList.erase(it);
				continue;
			}
			if (item->m_isValid == false) {
				it = m_functionList.erase(it);
				BSLIB_SAFE_DELETE(item);
				continue;
			}
			BSLib::Utility::CFunction<void, EventID&, BSLib::Utility::CStream& >* fun = item->m_fun;
			if (fun == NULL) {
				++it;
				continue;
			}
			BSLib::Utility::CStream stream;
			a_stream.copyTo(stream);
			(*fun)(a_eventID, stream);

			++it;
		}
	}
};


//////////////////////////////////////////////////////////////////////////
CEventMgr::CEventMgr()
{
	;
}

CEventMgr::~CEventMgr()
{
	clear();
}

void CEventMgr::init(const EventID& a_maxEventID)
{
	m_functionEventList.resize(a_maxEventID, NULL);
}

void CEventMgr::clear()
{
	for (BSLib::uint32 i=0; i<m_functionEventList.size(); ++i) {
		CFunctionEventStream* funEvent = m_functionEventList[i];
		if (funEvent == NULL) {
			continue;
		}
		BSLIB_SAFE_DELETE(funEvent);
	}
	m_functionEventList.clear();
}

void CEventMgr::updateEvent()
{
	EventID eventID = INVALID_EVENTID;
	BSLib::uint32 dataSize = 0;
	BSLib::uint32 streamSize = 0;
	while ((streamSize = m_streamEventMsg.readSize()) > 0) {
		if (streamSize < sizeof(dataSize) + sizeof(eventID)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "Event异常");
			m_streamEventMsg.reset();
			break;
		}
		m_streamEventMsg >> eventID;
		m_streamEventMsg >> dataSize;
		if (streamSize - (sizeof(dataSize) + sizeof(eventID)) < dataSize) {
			BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "Event异常");
			m_streamEventMsg.reset();
			break;
		}
		m_streamData.reset();
		m_streamData.write(m_streamEventMsg.readPtr(), dataSize);
		m_streamEventMsg.readFlip(dataSize);

		if (eventID < 0 || eventID >= (int)m_functionEventList.size()) {
			BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "无效EventID");
			continue;
		}
		CFunctionEventStream* funEvent = m_functionEventList[eventID];
		if (funEvent == NULL) {
			BSLIB_LOG_TRACE(ETT_BSLIB_UTILITY, "没有处理EventID[%d]的相关函数", eventID);
			continue;
			
		}
		(*funEvent)(eventID, m_streamData);
	}
}

void CEventMgr::sendEvent(const EventID& a_eventID, BSLib::int8* a_data, BSLib::uint32 a_dataSize)
{
	m_streamEventMsg << a_eventID;
	m_streamEventMsg << a_dataSize;
	m_streamEventMsg.write(a_data, a_dataSize);
}

void CEventMgr::sendEvent(const EventID& a_eventID, BSLib::Utility::CStream& a_stream)
{
	BSLib::uint32 dataSize = a_stream.readSize();
	m_streamEventMsg << a_eventID;
	m_streamEventMsg << dataSize;
	m_streamEventMsg << a_stream;
}

BSLib::Utility::CFunctionEventHandle CEventMgr::registerEvent(EventID& a_eventID, void(*a_fun)(EventID&, BSLib::Utility::CStream&))
{
	if (a_eventID < 0 || a_eventID >= (int)m_functionEventList.size()) {
		return NULL;
	}
	CFunctionEventStream* funEvent = m_functionEventList[a_eventID];
	if (funEvent == NULL) {
		funEvent = new CFunctionEventStream();
		if (funEvent == NULL) {
			return NULL;
		}
		m_functionEventList[a_eventID] = funEvent;
	}
	return funEvent->addFunctionEvent(a_fun);
}

BSLib::Utility::CFunctionEventHandle CEventMgr::registerEvent(EventID& a_eventID, BSLib::Utility::CFunction<void, EventID&, BSLib::Utility::CStream&>& a_fun)
{
	if (a_eventID < 0 || a_eventID >= (int)m_functionEventList.size()) {
		return NULL;
	}
	CFunctionEventStream* funEvent = m_functionEventList[a_eventID];
	if (funEvent == NULL) {
		funEvent = new CFunctionEventStream();
		if (funEvent == NULL) {
			return NULL;
		}
		m_functionEventList[a_eventID] = funEvent;
	}
	return funEvent->addFunctionEvent(a_fun);
}

void CEventMgr::unregisterEvent(EventID& a_eventID, BSLib::Utility::CFunctionEventHandle& a_handle)
{
	if (a_eventID < 0 || a_eventID >= (int)m_functionEventList.size()) {
		return ;
	}
	CFunctionEventStream* funEvent = m_functionEventList[a_eventID];
	if (funEvent == NULL) {
		return ;
	}
	funEvent->delFunctionEvent(a_handle);
}

}//BSLib

}//Utility