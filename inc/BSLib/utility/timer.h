#ifndef __BSLIB_UTILITY_TIMER_H__
#define __BSLIB_UTILITY_TIMER_H__

#include <BSLib/utility/timerServer.h>

#define BSLIB_UTILITY_TIMER_TEMPLATE_0
#define BSLIB_UTILITY_TIMER_TEMPLATE_1 typename T1=void
#define BSLIB_UTILITY_TIMER_TEMPLATE_2 BSLIB_UTILITY_TIMER_TEMPLATE_1, typename T2=void
#define BSLIB_UTILITY_TIMER_TEMPLATE_3 BSLIB_UTILITY_TIMER_TEMPLATE_2, typename T3=void
#define BSLIB_UTILITY_TIMER_TEMPLATE_4 BSLIB_UTILITY_TIMER_TEMPLATE_3, typename T4=void
#define BSLIB_UTILITY_TIMER_TEMPLATE_5 BSLIB_UTILITY_TIMER_TEMPLATE_4, typename T5=void
#define BSLIB_UTILITY_TIMER_TEMPLATE_6 BSLIB_UTILITY_TIMER_TEMPLATE_5, typename T6=void
#define BSLIB_UTILITY_TIMER_TEMPLATE_7 BSLIB_UTILITY_TIMER_TEMPLATE_6, typename T7=void
#define BSLIB_UTILITY_TIMER_TEMPLATE_8 BSLIB_UTILITY_TIMER_TEMPLATE_7, typename T8=void
#define BSLIB_UTILITY_TIMER_TEMPLATE_9 BSLIB_UTILITY_TIMER_TEMPLATE_8, typename T9=void

#define BSLIB_UTILITY_TIMER_TYPE_PARA_0 
#define BSLIB_UTILITY_TIMER_TYPE_PARA_1 T1 p1
#define BSLIB_UTILITY_TIMER_TYPE_PARA_2 BSLIB_UTILITY_TIMER_TYPE_PARA_1, T2 p2
#define BSLIB_UTILITY_TIMER_TYPE_PARA_3 BSLIB_UTILITY_TIMER_TYPE_PARA_2, T3 p3
#define BSLIB_UTILITY_TIMER_TYPE_PARA_4 BSLIB_UTILITY_TIMER_TYPE_PARA_3, T4 p4
#define BSLIB_UTILITY_TIMER_TYPE_PARA_5 BSLIB_UTILITY_TIMER_TYPE_PARA_4, T5 p5
#define BSLIB_UTILITY_TIMER_TYPE_PARA_6 BSLIB_UTILITY_TIMER_TYPE_PARA_5, T6 p6
#define BSLIB_UTILITY_TIMER_TYPE_PARA_7 BSLIB_UTILITY_TIMER_TYPE_PARA_6, T7 p7
#define BSLIB_UTILITY_TIMER_TYPE_PARA_8 BSLIB_UTILITY_TIMER_TYPE_PARA_7, T8 p8
#define BSLIB_UTILITY_TIMER_TYPE_PARA_9 BSLIB_UTILITY_TIMER_TYPE_PARA_8, T9 p9

#define BSLIB_UTILITY_TIMER_SET_PARA_0 
#define BSLIB_UTILITY_TIMER_SET_PARA_1 m_p1 = p1;
#define BSLIB_UTILITY_TIMER_SET_PARA_2 BSLIB_UTILITY_TIMER_SET_PARA_1 m_p2 = p2;
#define BSLIB_UTILITY_TIMER_SET_PARA_3 BSLIB_UTILITY_TIMER_SET_PARA_2 m_p3 = p3;
#define BSLIB_UTILITY_TIMER_SET_PARA_4 BSLIB_UTILITY_TIMER_SET_PARA_3 m_p4 = p4;
#define BSLIB_UTILITY_TIMER_SET_PARA_5 BSLIB_UTILITY_TIMER_SET_PARA_4 m_p5 = p5;
#define BSLIB_UTILITY_TIMER_SET_PARA_6 BSLIB_UTILITY_TIMER_SET_PARA_5 m_p6 = p6;
#define BSLIB_UTILITY_TIMER_SET_PARA_7 BSLIB_UTILITY_TIMER_SET_PARA_6 m_p7 = p7;
#define BSLIB_UTILITY_TIMER_SET_PARA_8 BSLIB_UTILITY_TIMER_SET_PARA_7 m_p8 = p8;
#define BSLIB_UTILITY_TIMER_SET_PARA_9 BSLIB_UTILITY_TIMER_SET_PARA_8 m_p9 = p9;

#define BSLIB_UTILITY_TIMER_TYPE_0 
#define BSLIB_UTILITY_TIMER_TYPE_1 T1
#define BSLIB_UTILITY_TIMER_TYPE_2 BSLIB_UTILITY_TIMER_TYPE_1, T2
#define BSLIB_UTILITY_TIMER_TYPE_3 BSLIB_UTILITY_TIMER_TYPE_2, T3
#define BSLIB_UTILITY_TIMER_TYPE_4 BSLIB_UTILITY_TIMER_TYPE_3, T4
#define BSLIB_UTILITY_TIMER_TYPE_5 BSLIB_UTILITY_TIMER_TYPE_4, T5
#define BSLIB_UTILITY_TIMER_TYPE_6 BSLIB_UTILITY_TIMER_TYPE_5, T6
#define BSLIB_UTILITY_TIMER_TYPE_7 BSLIB_UTILITY_TIMER_TYPE_6, T7
#define BSLIB_UTILITY_TIMER_TYPE_8 BSLIB_UTILITY_TIMER_TYPE_7, T8
#define BSLIB_UTILITY_TIMER_TYPE_9 BSLIB_UTILITY_TIMER_TYPE_8, T9

#define BSLIB_UTILITY_TIMER_FUNCTION_PARA_0 bool
#define BSLIB_UTILITY_TIMER_FUNCTION_PARA_1	BSLIB_UTILITY_TIMER_FUNCTION_PARA_0, T1
#define BSLIB_UTILITY_TIMER_FUNCTION_PARA_2	BSLIB_UTILITY_TIMER_FUNCTION_PARA_1, T2
#define BSLIB_UTILITY_TIMER_FUNCTION_PARA_3	BSLIB_UTILITY_TIMER_FUNCTION_PARA_2, T3
#define BSLIB_UTILITY_TIMER_FUNCTION_PARA_4	BSLIB_UTILITY_TIMER_FUNCTION_PARA_3, T4
#define BSLIB_UTILITY_TIMER_FUNCTION_PARA_5	BSLIB_UTILITY_TIMER_FUNCTION_PARA_4, T5
#define BSLIB_UTILITY_TIMER_FUNCTION_PARA_6	BSLIB_UTILITY_TIMER_FUNCTION_PARA_5, T6
#define BSLIB_UTILITY_TIMER_FUNCTION_PARA_7	BSLIB_UTILITY_TIMER_FUNCTION_PARA_6, T7
#define BSLIB_UTILITY_TIMER_FUNCTION_PARA_8	BSLIB_UTILITY_TIMER_FUNCTION_PARA_7, T8
#define BSLIB_UTILITY_TIMER_FUNCTION_PARA_9	BSLIB_UTILITY_TIMER_FUNCTION_PARA_8, T9

#define BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_0 bool, C
#define BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_1	BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_0, T1
#define BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_2	BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_1, T2
#define BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_3	BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_2, T3
#define BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_4	BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_3, T4
#define BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_5	BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_4, T5
#define BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_6	BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_5, T6
#define BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_7	BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_6, T7
#define BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_8	BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_7, T8
#define BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_9	BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_8, T9

#define BSLIB_UTILITY_TIMER_DEFINE_PARA_0 
#define BSLIB_UTILITY_TIMER_DEFINE_PARA_1 T1 m_p1;
#define BSLIB_UTILITY_TIMER_DEFINE_PARA_2 BSLIB_UTILITY_TIMER_DEFINE_PARA_1 T2 m_p2;
#define BSLIB_UTILITY_TIMER_DEFINE_PARA_3 BSLIB_UTILITY_TIMER_DEFINE_PARA_2 T3 m_p3;
#define BSLIB_UTILITY_TIMER_DEFINE_PARA_4 BSLIB_UTILITY_TIMER_DEFINE_PARA_3 T4 m_p4;
#define BSLIB_UTILITY_TIMER_DEFINE_PARA_5 BSLIB_UTILITY_TIMER_DEFINE_PARA_4 T5 m_p5;
#define BSLIB_UTILITY_TIMER_DEFINE_PARA_6 BSLIB_UTILITY_TIMER_DEFINE_PARA_5 T6 m_p6;
#define BSLIB_UTILITY_TIMER_DEFINE_PARA_7 BSLIB_UTILITY_TIMER_DEFINE_PARA_6 T7 m_p7;
#define BSLIB_UTILITY_TIMER_DEFINE_PARA_8 BSLIB_UTILITY_TIMER_DEFINE_PARA_7 T8 m_p8;
#define BSLIB_UTILITY_TIMER_DEFINE_PARA_9 BSLIB_UTILITY_TIMER_DEFINE_PARA_8 T9 m_p9;

#define BSLIB_UTILITY_TIMER_PARA_0 
#define BSLIB_UTILITY_TIMER_PARA_1 m_p1
#define BSLIB_UTILITY_TIMER_PARA_2 BSLIB_UTILITY_TIMER_PARA_1, m_p2
#define BSLIB_UTILITY_TIMER_PARA_3 BSLIB_UTILITY_TIMER_PARA_2, m_p3
#define BSLIB_UTILITY_TIMER_PARA_4 BSLIB_UTILITY_TIMER_PARA_3, m_p4
#define BSLIB_UTILITY_TIMER_PARA_5 BSLIB_UTILITY_TIMER_PARA_4, m_p5
#define BSLIB_UTILITY_TIMER_PARA_6 BSLIB_UTILITY_TIMER_PARA_5, m_p6
#define BSLIB_UTILITY_TIMER_PARA_7 BSLIB_UTILITY_TIMER_PARA_6, m_p7
#define BSLIB_UTILITY_TIMER_PARA_8 BSLIB_UTILITY_TIMER_PARA_7, m_p8
#define BSLIB_UTILITY_TIMER_PARA_9 BSLIB_UTILITY_TIMER_PARA_8, m_p9

#define BSLIB_UTILITY_TIMER(N)\
	template<BSLIB_UTILITY_TIMER_TEMPLATE_##N>\
	class CTimer\
	{\
	public:\
		CTimer(BSLib::Utility::CTimerServer* a_timerServer = NULL, BSLib::uint32 a_msInterval = 0,  BSLib::uint32 a_msDelay = 0, BSLib::int32 a_counts = -1)\
		{\
			setTimer(a_timerServer, a_msInterval, a_msDelay, a_counts);\
			m_fun = NULL;\
			setTimerCb(&CTimer::_timerCallback, this);\
		}\
		~CTimer()\
		{\
			close();\
			if (m_fun != NULL) {\
				BSLIB_SAFE_DELETE(m_fun);\
			}\
		}\
		void setTimer(BSLib::Utility::CTimerServer* a_timerServer, BSLib::uint32 a_msInterval,  BSLib::uint32 a_msDelay=0, BSLib::int32 a_counts = -1)\
		{\
			m_timerServer = a_timerServer;\
			m_timerHandle = BSLib::Utility::INVALID_TIMER;\
			m_msInterval = a_msInterval;\
			m_msDelay = a_msDelay;\
			m_counts = a_counts;\
		}\
		bool start(BSLIB_UTILITY_TIMER_TYPE_PARA_##N)\
		{\
			if (m_timerServer == NULL) {\
				return false;\
			}\
			if (m_fun == NULL) {\
				return false;\
			}\
			if (m_timerHandle != BSLib::Utility::INVALID_TIMER && m_timerServer->isValid(m_timerHandle)) {\
				return false;\
			}\
			BSLIB_UTILITY_TIMER_SET_PARA_##N;\
			m_timerHandle = m_timerServer->addTimer(&CTimer::_timerTick, this, (BSLib::uint64)0, NULL, m_msInterval, m_msDelay, m_counts);\
			if (m_timerHandle == BSLib::Utility::INVALID_TIMER) {\
				BSLIB_SAFE_DELETE(m_fun);\
				return false;\
			}\
			return true;\
		}\
		void close()\
		{\
			if (m_timerServer == NULL) {\
				return ;\
			}\
			if (m_timerHandle == BSLib::Utility::INVALID_TIMER) {\
				return ;\
			}\
			m_timerServer->delTimer(m_timerHandle);\
			m_timerHandle = BSLib::Utility::INVALID_TIMER;\
		}\
		bool setTimerCb(bool(*a_fun)(BSLIB_UTILITY_TIMER_TYPE_##N))\
		{\
			if (m_timerServer == NULL) {\
				return false;\
			}\
			if (m_fun != NULL) {\
				BSLIB_SAFE_DELETE(m_fun);\
			}\
			m_fun = new BSLib::Utility::CFunction<BSLIB_UTILITY_TIMER_FUNCTION_PARA_##N>(a_fun);\
			if (m_fun == NULL) {\
				return false;\
			}\
			return true;\
		}\
		bool setTimerCb(BSLib::Utility::CFunction<BSLIB_UTILITY_TIMER_FUNCTION_PARA_##N>& a_fun)\
		{\
			if (m_timerServer == NULL) {\
				return false;\
			}\
			if (m_fun != NULL) {\
				BSLIB_SAFE_DELETE(m_fun);\
			}\
			m_fun = a_fun.clone();\
			if (m_fun == NULL) {\
				return false;\
			}\
			return true;\
		}\
		template<class C>\
		bool setTimerCb(bool(C::*a_fun)(BSLIB_UTILITY_TIMER_TYPE_##N), C* a_object)\
		{\
			BSLib::Utility::CFunctionObject<BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_##N> objFun(a_fun, a_object);\
			return setTimerCb(objFun);\
		}\
	protected:\
		virtual bool _timerCallback(BSLIB_UTILITY_TIMER_TYPE_PARA_##N)\
		{\
			return true;\
		}\
	private:\
	bool _timerTick(BSLib::uint64, void*)\
		{\
			if (m_fun == NULL) {\
				return false;\
			}\
			return (*m_fun)(BSLIB_UTILITY_TIMER_PARA_##N);\
		}\
	private:\
		BSLib::Utility::CTimerServer* m_timerServer;\
		BSLib::Utility::TimerHandle m_timerHandle;\
		BSLib::uint32 m_msInterval;\
		BSLib::uint32 m_msDelay;\
		BSLib::int32 m_counts;\
		BSLib::Utility::CFunction<BSLIB_UTILITY_TIMER_FUNCTION_PARA_##N>* m_fun;\
		BSLIB_UTILITY_TIMER_DEFINE_PARA_##N;\
	};

#define BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_0
#define BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_1	typename T1
#define BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_2	BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_1, typename T2
#define BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_3	BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_2, typename T3
#define BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_4	BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_3, typename T4
#define BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_5	BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_4, typename T5
#define BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_6	BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_5, typename T6
#define BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_7	BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_6, typename T7
#define BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_8	BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_7, typename T8
#define	BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_9	BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_8, typename T9

#define BSLIB_UTILITY_TIMER_TEMPLATE_PARA_0
#define BSLIB_UTILITY_TIMER_TEMPLATE_PARA_1	T1
#define BSLIB_UTILITY_TIMER_TEMPLATE_PARA_2	BSLIB_UTILITY_TIMER_TEMPLATE_PARA_1, T2
#define BSLIB_UTILITY_TIMER_TEMPLATE_PARA_3	BSLIB_UTILITY_TIMER_TEMPLATE_PARA_2, T3
#define BSLIB_UTILITY_TIMER_TEMPLATE_PARA_4	BSLIB_UTILITY_TIMER_TEMPLATE_PARA_3, T4
#define BSLIB_UTILITY_TIMER_TEMPLATE_PARA_5	BSLIB_UTILITY_TIMER_TEMPLATE_PARA_4, T5
#define BSLIB_UTILITY_TIMER_TEMPLATE_PARA_6	BSLIB_UTILITY_TIMER_TEMPLATE_PARA_5, T6
#define BSLIB_UTILITY_TIMER_TEMPLATE_PARA_7	BSLIB_UTILITY_TIMER_TEMPLATE_PARA_6, T7
#define BSLIB_UTILITY_TIMER_TEMPLATE_PARA_8	BSLIB_UTILITY_TIMER_TEMPLATE_PARA_7, T8
#define BSLIB_UTILITY_TIMER_TEMPLATE_PARA_9	BSLIB_UTILITY_TIMER_TEMPLATE_PARA_8, T9

#define BSLIB_UTILITY_TIMER_SPECIAL(N)\
	template<BSLIB_UTILITY_TIMER_TEMPLATE_TYPE_##N>\
	class CTimer<BSLIB_UTILITY_TIMER_TEMPLATE_PARA_##N>\
	{\
	public:\
		CTimer(BSLib::Utility::CTimerServer* a_timerServer = NULL, BSLib::uint32 a_msInterval = 0,  BSLib::uint32 a_msDelay = 0, BSLib::int32 a_counts = -1)\
		{\
			setTimer(a_timerServer, a_msInterval, a_msDelay, a_counts);\
			m_fun = NULL;\
			setTimerCb(&CTimer::_timerCallback, this);\
		}\
		~CTimer()\
		{\
			close();\
			if (m_fun != NULL) {\
				BSLIB_SAFE_DELETE(m_fun);\
			}\
		}\
		void setTimer(BSLib::Utility::CTimerServer* a_timerServer, BSLib::uint32 a_msInterval,  BSLib::uint32 a_msDelay=0, BSLib::int32 a_counts = -1)\
		{\
			m_timerServer = a_timerServer;\
			m_timerHandle = BSLib::Utility::INVALID_TIMER;\
			m_msInterval = a_msInterval;\
			m_msDelay = a_msDelay;\
			m_counts = a_counts;\
		}\
		bool start(BSLIB_UTILITY_TIMER_TYPE_PARA_##N)\
		{\
			if (m_timerServer == NULL) {\
				return false;\
			}\
			if (m_fun == NULL) {\
				return false;\
			}\
			if (m_timerHandle != BSLib::Utility::INVALID_TIMER && m_timerServer->isValid(m_timerHandle)) {\
				return false;\
			}\
			BSLIB_UTILITY_TIMER_SET_PARA_##N;\
			m_timerHandle = m_timerServer->addTimer(&CTimer::_timerTick, this, (BSLib::uint64)0, NULL, m_msInterval, m_msDelay, m_counts);\
			if (m_timerHandle == BSLib::Utility::INVALID_TIMER) {\
				BSLIB_SAFE_DELETE(m_fun);\
				return false;\
			}\
			return true;\
		}\
		void close()\
		{\
			if (m_timerServer == NULL) {\
				return ;\
			}\
			if (m_timerHandle == BSLib::Utility::INVALID_TIMER) {\
				return ;\
			}\
			m_timerServer->delTimer(m_timerHandle);\
			m_timerHandle = BSLib::Utility::INVALID_TIMER;\
		}\
		bool setTimerCb(bool(*a_fun)(BSLIB_UTILITY_TIMER_TYPE_##N))\
		{\
			if (m_timerServer == NULL) {\
				return false;\
			}\
			if (m_fun != NULL) {\
				BSLIB_SAFE_DELETE(m_fun);\
			}\
			m_fun = new BSLib::Utility::CFunction<BSLIB_UTILITY_TIMER_FUNCTION_PARA_##N>(a_fun);\
			if (m_fun == NULL) {\
				return false;\
			}\
			return true;\
		}\
		bool setTimerCb(BSLib::Utility::CFunction<BSLIB_UTILITY_TIMER_FUNCTION_PARA_##N>& a_fun)\
		{\
			if (m_timerServer == NULL) {\
				return false;\
			}\
			if (m_fun != NULL) {\
				BSLIB_SAFE_DELETE(m_fun);\
			}\
			m_fun = a_fun.clone();\
			if (m_fun == NULL) {\
				return false;\
			}\
			return true;\
		}\
		template<class C>\
		bool setTimerCb(bool(C::*a_fun)(BSLIB_UTILITY_TIMER_TYPE_##N), C* a_object)\
		{\
			BSLib::Utility::CFunctionObject<BSLIB_UTILITY_TIMER_FUNCTION_OBJECT_PARA_##N> objFun(a_fun, a_object);\
			return setTimerCb(objFun);\
		}\
	protected:\
	virtual bool _timerCallback(BSLIB_UTILITY_TIMER_TYPE_PARA_##N)\
		{\
			return true;\
		}\
	private:\
	bool _timerTick(BSLib::uint64, void*)\
		{\
			if (m_fun == NULL) {\
				return false;\
			}\
			return (*m_fun)(BSLIB_UTILITY_TIMER_PARA_##N);\
		}\
	private:\
		BSLib::Utility::CTimerServer* m_timerServer;\
		BSLib::Utility::TimerHandle m_timerHandle;\
		BSLib::uint32 m_msInterval;\
		BSLib::uint32 m_msDelay;\
		BSLib::int32 m_counts;\
		BSLib::Utility::CFunction<BSLIB_UTILITY_TIMER_FUNCTION_PARA_##N>* m_fun;\
		BSLIB_UTILITY_TIMER_DEFINE_PARA_##N;\
	};


namespace BSLib
{

namespace Utility
{

BSLIB_UTILITY_TIMER(9);

BSLIB_UTILITY_TIMER_SPECIAL(0);
BSLIB_UTILITY_TIMER_SPECIAL(1);
BSLIB_UTILITY_TIMER_SPECIAL(2);
BSLIB_UTILITY_TIMER_SPECIAL(3);
BSLIB_UTILITY_TIMER_SPECIAL(4);
BSLIB_UTILITY_TIMER_SPECIAL(5);
BSLIB_UTILITY_TIMER_SPECIAL(6);
BSLIB_UTILITY_TIMER_SPECIAL(7);
BSLIB_UTILITY_TIMER_SPECIAL(8);

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> class CTimer;

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_TIMER_H__
